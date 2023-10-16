#include"stdafx.h"
#include"LogitLog4P.h"
#include"../../../../include/mfctoolkit/arithmetic/MtMatrix.h"
#include"../../../../include/mfctoolkit/arithmetic/MtSolvingEquations.h"
#include<math.h>
#include<float.h>


//定义类中静态变量。
const double LogitLog4P::ZERO=1.0E-10;
const double LogitLog4P::ZERO_THRESHOLD_VALUE=1.0E-20;

/**
 * name: LogitLog4P
 * brief: 构造函数。
 * param: --
 * return: --
 */
LogitLog4P::LogitLog4P(void)
	:MtLMFormula(0,0,0,4)
	,_parameters(new DMat){
}

/**
 * name: ~LogitLog4P
 * brief: 析构函数。
 * param: --
 * return: --
 */
LogitLog4P::~LogitLog4P(void){
	delete _parameters;
}

/**
 * name: set_parameters
 * brief: 设置当前参数。
 * param: parameters - 指定参数。
 * return: --
 */
void LogitLog4P::set_parameters(const DMat &parameters){
	(*_parameters)=parameters;
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数。
 */
LogitLog4P::DMat &LogitLog4P::get_parameters(){
	return(*_parameters);
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数。
 */
const LogitLog4P::DMat &LogitLog4P::get_parameters() const{
	return((const_cast<LogitLog4P*>(this))->get_parameters());
}

/**
 * name: get_initialized_parameters
 * brief: 利用x数组、y数组获取当前公式初始参数。
 * param: x - 指向x数组。
 *        y - 指向y数组。
 *        size - 未知数数量。
 *        parameters - 返回的参数。
 * return: 如果创建公式成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::get_initialized_parameters(const double *x,
	const double *y,const unsigned int size,DMat &parameters){
	//1.如果调用基类相应处理函数失败，则直接返回错误。
	if(MtLMFormula::get_initialized_parameters(
		x,y,size,parameters)<0){
		return(-1);
	}
	//2.计算公式中参数B的初值。
	//2-1.获取当前标准液最大浓度的的下标值。
	const unsigned int max_conc_index=get_maximum_x_index();
	if(0xFFFFFFFF==max_conc_index){
		return(-2);
	}
	//2-2.获取当前标准液中最大浓度对应的吸光度。
	const double max_conc_abs=get_y(max_conc_index);
	if(max_conc_abs<0.0){
		return(-3);
	}
	//2-3.获取当前标准液中最大吸光度的下标值。
	const unsigned int max_abs_index=get_maximum_y_index();
	if(0xFFFFFFFF==max_abs_index){
		return(-4);
	}
	//2-3.设置参数B的初值。
	//2-3-1.声明当前操作所需变量。
	double B=0.0;
	//2-3-2.如果当前为增函数。
	if(max_conc_index==max_abs_index){
		B=max_conc_abs+(max_conc_abs*0.1);
	}
	//2-3-1.如果当前为减函数。
	else{
		B=max_conc_abs-(max_conc_abs*0.1);
	}
	//3.计算公式中的参数K的初值。
	//3-1.获取当前标准液中最小浓度的下标值。
	const unsigned int min_conc_index=get_minimum_x_index();
	if(0xFFFFFFFF==min_conc_index){
		return(-5);
	}
	//3-2.获取当前标准液中最小浓度对应的吸光度的值。
	const double min_conc_abs=get_y(min_conc_index);
	if(min_conc_abs<0.0){
		return(-6);
	}
	//3-3.为当前参数K设置初值。
	const double K=min_conc_abs-B;
	/*
	//3-3-1.声明当前函数操作所需变量。
	double K=0.0;
	//3-3-2.如果当前为增函数。
	if(max_conc_index==max_abs_index){
		K=(min_conc_abs-max_conc_abs)-((min_conc_abs-max_conc_abs)*0.0025);
	}
	//3-3-3.如果当前为减函数。
	else{
		K=(min_conc_abs-max_conc_abs)+((min_conc_abs-max_conc_abs)*0.0025);
	}
	*/
	//4.根据B、K的初始值，求解其它系数（a，b）的初始值。
	//4-1.创建系数矩阵，并且判断创建是否成功。
	DMat coef_mat(get_size(),2);
	if(!coef_mat.is_valid()){
		return(-7);
	}
	//4-2.为系数矩阵赋值。
	for(unsigned int row=0;row!=coef_mat.get_rows();++row){
		for(unsigned int col=0;col!=coef_mat.get_cols();++col){
			//4-2-1.如果当前为系数矩阵第一列。
			if(0==col){
				coef_mat.set_element(row,col,1.0);
			}
			//4-2-2.如果当前为系数矩阵第二列。
			else{
				const double conc=get_x(row);
				if(conc<ZERO_THRESHOLD_VALUE){
					return(-8);
				}
				coef_mat.set_element(row,col,log(conc));
			}
		}
	}
	//4-3.创建结果矩阵。
	DMat result_mat(get_size(),1);
	if(!result_mat.is_valid()){
		return(-9);
	}
	//4-4.为结果矩阵赋值。
	for(unsigned int row=0;row!=result_mat.get_rows();++row){
		//4-4-1.获取当前的吸光度。
		const double abs=get_y(row);
		if(abs<0.0){
			return(-10);
		}
		//4-4-2.计算Ax-B的值。
		double temp1=abs-B;
		if(fabs(temp1)<ZERO_THRESHOLD_VALUE){
			//不能为零，因为需要做为分母使用，如果为零的话公式无意义。
			return(-11);
		}
		//4-4-3.计算(K-(Ax-B))/(Ax-B)的值。
		double temp2=K-temp1;
		if(fabs(temp2)<ZERO_THRESHOLD_VALUE){
			if(temp1<0.0){
				temp2=-ZERO;
			}else{
				temp2=ZERO;
			}
		}
		temp2/=temp1;
		if(fabs(temp2)<ZERO_THRESHOLD_VALUE){
			temp2=ZERO;
		}else if(temp2<0.0){
			return(-12);
		}
		//4-4-4.设置结果矩阵指定元素值。
		result_mat.set_element(row,0,log(temp2));
	}
	//4-5.计算系数矩阵的转置矩阵。
	DMat coef_mat_trans;
	if(coef_mat.transpose(coef_mat_trans)<0){
		return(-13);
	}
	//4-6.方程两边左程系数转置矩阵，利用最小二乘法求解方程组。
	coef_mat=coef_mat_trans*coef_mat;
	if(!coef_mat.is_valid()){
		return(-14);
	}
	result_mat=coef_mat_trans*result_mat;
	if(!result_mat.is_valid()){
		return(-15);
	}
	//4-7.对系数矩阵进行LU分解，求解矛盾方程组。
	if(MtSolvingEquations::solve(coef_mat,result_mat)<0){
		return(-16);
	}
	//4-8.计算参数a的值。
	const double a=exp(result_mat[0][0]);
	//4-9.计算参数b的值。
	const double b=result_mat[1][0];
	//5.创建参数矩阵，并且为参数矩阵赋值。
	//5-1.进行参数矩阵的创建，并且判断创建是否成功。
	if(parameters.create(4,1)<0){
		return(-17);
	}
	//5-2.为当前参数矩阵赋值。
	parameters.set_element(0,0,B);
	parameters.set_element(1,0,K);
	parameters.set_element(2,0,a);
	parameters.set_element(3,0,b);
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_jacobian_matrix
 * brief: 获取当前公式中，指定参数的雅可比矩阵。
 * param: parameters - 指定的参数矩阵。
 *        jacobian - 返回的雅可比矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::get_jacobian_matrix(const DMat &parameters,DMat &jacobian) const{
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(MtLMFormula::get_jacobian_matrix(parameters,jacobian)<0){
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.创建雅可比矩阵，并且判断创建是否成功。
	if(jacobian.create(get_size(),4)<0){
		return(-3);
	}
	//4.为雅可比矩阵赋值。
	//4-1.声明当前操作所需变量。
	double abs=0.0;
	double conc=0.0;
	double B=0.0;
	double K=0.0;
	double temp=0.0;
	double temp1=0.0;//Ax-B
	double temp2=0.0;//C^(b-1)
	double a=0.0;
	double b=0.0;
	//4-2.遍历雅可比矩阵，并为雅可比矩阵赋值。
	for(unsigned int row=0;row!=get_size();++row){
		//4-2-1.获取当前定标液吸光度，并且判断获取是否成功。
		abs=get_y(row);
		if(abs<0.0){
			return(-4);
		}
		//4-2-2.计算当前定标液浓度，并且判断计算是否成功。
		if(calculate_concentration(parameters,abs,conc)<0){
			return(-5);
		}
		//4-2-3.计算Ax-B的值。
		temp1=abs-parameters[0][0];
		//4-2-4.计算C^(b-1)的值。
		temp2=pow(conc,(parameters[3][0]-1.0));
		if(_isnan(temp2)){
			return(-6);
		}
		//4-2-5.计算B的偏导数。
		temp=parameters[2][0]*temp1*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-7);
		}
		B=parameters[1][0]/temp;
		//4-2-6.计算K的偏导数。
		temp=parameters[2][0]*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-8);
		}
		K=1.0/temp;
		//4-2-7.计算a的偏导数。
		temp=parameters[2][0]*parameters[2][0]*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-9);
		}
		a=(abs-parameters[0][0]-parameters[1][0])/temp;
		//4-2-8.计算b的偏导数。
		if(fabs(parameters[3][0])<ZERO_THRESHOLD_VALUE){
			return(-10);
		}
		b=-((conc/parameters[3][0])*log(conc));
		//4-2-9.设置雅可比矩阵的值。
		jacobian.set_element(row,0,B);
		jacobian.set_element(row,1,K);
		jacobian.set_element(row,2,a);
		jacobian.set_element(row,3,b);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_difference_matrix
 * brief: 获取当前公式下指定参数的差值矩阵。
 * param: parameters - 指定的参数矩阵。
 *        difference - 返回取得的差值矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::get_difference_matrix(const DMat &parameters,DMat &difference) const{
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(MtLMFormula::get_difference_matrix(parameters,difference)<0){
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.创建差值矩阵，并且判断创建是否成功。
	if(difference.create(get_size(),1)<0){
		return(-3);
	}
	//4.遍历差值矩阵，并为差值矩阵赋值。
	//4-1.声明当前操作所需变量。
	double abs=0.0;
	double c_conc=0.0;
	double t_conc=0.0;
	//4-2.遍历差值矩阵，并为差值矩阵赋值。
	for(unsigned int row=0;row!=get_size();++row){
		//4-2-1.获取当前吸光度，并且判断获取是否成功。
		abs=get_y(row);
		if(abs<0.0){
			return(-2);
		}
		//4-2-2.计算浓度，并且判断计算是否成功。
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-3);
		}
		//4-2-3.获取实测的浓度。
		t_conc=get_x(row);
		if(t_conc<0.0){
			return(-4);
		}
		//4-2-4.为差值矩阵赋值。
		difference.set_element(row,0,t_conc-c_conc);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_sum_of_squares_of_deviations
 * brief: 获取当前公式下指定参数情况的差方和。
 * param: parameters - 指定的参数。
 *        sum - 返回的差方和。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::get_sum_of_squares_of_deviations(
	const DMat &parameters,double &sum) const{
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(MtLMFormula::get_sum_of_squares_of_deviations(
		parameters,sum)<0){
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.计算差方和。
	//3-1.声明当前操作所需变量。
	double abs=0.0;
	double c_conc=0.0;
	double t_conc=0.0;
	double sum_t=0.0;
	//3-2.遍历当前公式中的定标液信息，计算差方和。
	for(unsigned int index=0;index!=get_size();++index){
		//3-2-1.获取当前吸光度，并且判断获取是否成功。
		abs=get_y(index);
		if(abs<0.0){
			return(-3);
		}
		//3-2-2.计算浓度，并且判断计算是否成功。
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-4);
		}
		//3-2-3.计算实测的浓度。
		t_conc=get_x(index);
		if(t_conc<0.0){
			return(-5);
		}
		//3-2-4.计算差方和。
		sum_t+=(t_conc-c_conc)*(t_conc-c_conc);
	}
	//3-3.保存当前差方和。
	sum=sum_t;
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_correlation_coefficient
 * brief: 获取当前公式下，指定参数计算的相关系数。
 * param: parameters - 指定的参数。
 *        correlation_coefficient - 返回的相关系数。
 *        relative_deviation - 返回的相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::get_correlation_coefficient(const DMat &parameters,
	double &correlation_coefficient,DMat &relative_deviation) const{
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(MtLMFormula::get_correlation_coefficient(parameters,
		correlation_coefficient,relative_deviation)<0){
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.创建相对偏差存储矩阵，并且判断创建是否成功。
	if(relative_deviation.create(get_size(),1)<0){
		return(-3);
	}
	//4.计算当前公式下指定参数的相对偏差，并且判断计算是否成功。
	for(unsigned int index=1;index!=get_size();++index){
		//4-1.获取当前定标液的吸光度。
		const double abs=get_y(index);
		if(abs<0.0){
			return(-4);
		}
		//4-2.根据当前参数、吸光度计算浓度，并且判断计算是否成功。
		double c_conc=0.0;
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-5);
		}
		//4-3.获取当前定标液实际浓度。
		const double conc=get_x(index);
		if(conc<0.0){
			return(-6);
		}
		//4-4.计算当前相对偏差。
		const double coef=fabs((conc-c_conc)/conc);
		//4-5.将相对偏差的值保存到相对偏差矩阵中。
		relative_deviation.set_element(index,0,coef);
	}
	//5.计算当前公式下指定参数的相关系数，并且判断相关系数是否合法。
	//5-1.声明当前操作所需变量。
	double s0=0.0;
	double s1=0.0;
	//5-2.获取当前公式中定标液的平均吸光度，并且判断获取是否成功。
	const double avg_abs=get_average_y();
	if(avg_abs<0.0){
		return(-7);
	}
	//5-3.遍历定标液数组累计差方和，为求解相关系数做准备。
	for(unsigned int index=0;index!=get_size();++index){
		//5-3-1.获取当前定标液的实际浓度。
		const double conc=get_x(index);
		if(conc<0.0){
			return(-8);
		}
		//5-3-2.根据当前参数计算吸光度，并且判断计算是否成功。
		double cal_abs=0.0;
		if(calculate_absorbance(parameters,conc,cal_abs)<0){
			return(-9);
		}
		//5-3-3.获取当前定标液实际的吸光度。
		const double abs=get_y(index);
		if(abs<0.0){
			return(-10);
		}
		//5-3-4.累计差方和。
		s0+=(abs-cal_abs)*(abs-cal_abs);
		s1+=(abs-avg_abs)*(abs-avg_abs);
	}
	//5-4.如果当前计算的分母s1不合法，则直接返回错误。
	if(fabs(s1)<ZERO_THRESHOLD_VALUE){
		return(-11);
	}
	//5-5.计算相关系数。
	const double coef=1.0-(s0/s1);
	//5-6.保存当前相关系数。
	correlation_coefficient=coef;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_absorbance
 * brief: 当前公式下，指定参数、浓度，计算吸光度。
 * param: parameters - 指定的参数。
 *        conc - 指定的浓度。
 *        abs - 返回的吸光度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_absorbance(
	const DMat &parameters,const double conc,double &abs) const{
	//remark:在此默认paramaeters、conc都是合法的。
	//1.计算1.0+a*c^b 。
	const double temp=1.0+(parameters[2][0]*pow(conc,parameters[3][0]));
	if(fabs(temp)<ZERO_THRESHOLD_VALUE){
		return(-1);
	}
	//2.计算Ax=B+K/(1.0+a*c^b) 。
	abs=parameters[0][0]+(parameters[1][0]/temp);
	if(_isnan(abs)){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_concentration
 * brief: 当前公式下，指定参数、吸光度，计算浓度。
 * param: parameters - 指定的参数。
 *        abs - 指定的吸光度。
 *        conc - 返回的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_concentration(
	const DMat &parameters,const double abs,double &conc) const{
	//remark:在此默认paramaeters、abs都是合法的。
	//1.计算1.0/b。
	if(fabs(parameters[3][0])<ZERO_THRESHOLD_VALUE){//不能为零，后面需要做为分母使用。
		return(-1);
	}
	const double temp1=1.0/parameters[3][0];
	//2.计算Ax-B。
	const double temp2=abs-parameters[0][0];
	//3.计算a*(Ax-B)
	const double temp3=parameters[2][0]*temp2;
	if(fabs(temp3)<ZERO_THRESHOLD_VALUE){//不能为零，应为后面做为分母使用。
		return(-2);
	}
	//4.计算(K-(Ax-B))/(a*(Ax-B))的值。
	double temp4=parameters[1][0]-temp2;
	if(fabs(temp4)<ZERO_THRESHOLD_VALUE){
		if(temp3<0.0){
			temp4=-ZERO;
		}else{
			temp4=ZERO;
		}
	}
	temp4/=temp3;
	if(fabs(temp4)<ZERO_THRESHOLD_VALUE){
		temp4=ZERO;
	}else if(temp4<0.0){
		return(-3);
	}
	//5.计算浓度。
	conc=pow(temp4,temp1);
	if(_isnan(conc)){
		return(-4);
	}
	//6.程序运行到此成功返回。
	return(0);
}