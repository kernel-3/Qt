#include"stdafx.h"
#include"LogitLog4P.h"
#include"../../../../include/mfctoolkit/arithmetic/MtMatrix.h"
#include"../../../../include/mfctoolkit/arithmetic/MtSolvingEquations.h"
#include<math.h>
#include<float.h>


//�������о�̬������
const double LogitLog4P::ZERO=1.0E-10;
const double LogitLog4P::ZERO_THRESHOLD_VALUE=1.0E-20;

/**
 * name: LogitLog4P
 * brief: ���캯����
 * param: --
 * return: --
 */
LogitLog4P::LogitLog4P(void)
	:MtLMFormula(0,0,0,4)
	,_parameters(new DMat){
}

/**
 * name: ~LogitLog4P
 * brief: ����������
 * param: --
 * return: --
 */
LogitLog4P::~LogitLog4P(void){
	delete _parameters;
}

/**
 * name: set_parameters
 * brief: ���õ�ǰ������
 * param: parameters - ָ��������
 * return: --
 */
void LogitLog4P::set_parameters(const DMat &parameters){
	(*_parameters)=parameters;
}

/**
 * name: get_parameters
 * brief: ��ȡ��ǰ������
 * param: --
 * return: ���ص�ǰ������
 */
LogitLog4P::DMat &LogitLog4P::get_parameters(){
	return(*_parameters);
}

/**
 * name: get_parameters
 * brief: ��ȡ��ǰ������
 * param: --
 * return: ���ص�ǰ������
 */
const LogitLog4P::DMat &LogitLog4P::get_parameters() const{
	return((const_cast<LogitLog4P*>(this))->get_parameters());
}

/**
 * name: get_initialized_parameters
 * brief: ����x���顢y�����ȡ��ǰ��ʽ��ʼ������
 * param: x - ָ��x���顣
 *        y - ָ��y���顣
 *        size - δ֪��������
 *        parameters - ���صĲ�����
 * return: ���������ʽ�ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::get_initialized_parameters(const double *x,
	const double *y,const unsigned int size,DMat &parameters){
	//1.������û�����Ӧ������ʧ�ܣ���ֱ�ӷ��ش���
	if(MtLMFormula::get_initialized_parameters(
		x,y,size,parameters)<0){
		return(-1);
	}
	//2.���㹫ʽ�в���B�ĳ�ֵ��
	//2-1.��ȡ��ǰ��׼Һ���Ũ�ȵĵ��±�ֵ��
	const unsigned int max_conc_index=get_maximum_x_index();
	if(0xFFFFFFFF==max_conc_index){
		return(-2);
	}
	//2-2.��ȡ��ǰ��׼Һ�����Ũ�ȶ�Ӧ������ȡ�
	const double max_conc_abs=get_y(max_conc_index);
	if(max_conc_abs<0.0){
		return(-3);
	}
	//2-3.��ȡ��ǰ��׼Һ���������ȵ��±�ֵ��
	const unsigned int max_abs_index=get_maximum_y_index();
	if(0xFFFFFFFF==max_abs_index){
		return(-4);
	}
	//2-3.���ò���B�ĳ�ֵ��
	//2-3-1.������ǰ�������������
	double B=0.0;
	//2-3-2.�����ǰΪ��������
	if(max_conc_index==max_abs_index){
		B=max_conc_abs+(max_conc_abs*0.1);
	}
	//2-3-1.�����ǰΪ��������
	else{
		B=max_conc_abs-(max_conc_abs*0.1);
	}
	//3.���㹫ʽ�еĲ���K�ĳ�ֵ��
	//3-1.��ȡ��ǰ��׼Һ����СŨ�ȵ��±�ֵ��
	const unsigned int min_conc_index=get_minimum_x_index();
	if(0xFFFFFFFF==min_conc_index){
		return(-5);
	}
	//3-2.��ȡ��ǰ��׼Һ����СŨ�ȶ�Ӧ������ȵ�ֵ��
	const double min_conc_abs=get_y(min_conc_index);
	if(min_conc_abs<0.0){
		return(-6);
	}
	//3-3.Ϊ��ǰ����K���ó�ֵ��
	const double K=min_conc_abs-B;
	/*
	//3-3-1.������ǰ�����������������
	double K=0.0;
	//3-3-2.�����ǰΪ��������
	if(max_conc_index==max_abs_index){
		K=(min_conc_abs-max_conc_abs)-((min_conc_abs-max_conc_abs)*0.0025);
	}
	//3-3-3.�����ǰΪ��������
	else{
		K=(min_conc_abs-max_conc_abs)+((min_conc_abs-max_conc_abs)*0.0025);
	}
	*/
	//4.����B��K�ĳ�ʼֵ���������ϵ����a��b���ĳ�ʼֵ��
	//4-1.����ϵ�����󣬲����жϴ����Ƿ�ɹ���
	DMat coef_mat(get_size(),2);
	if(!coef_mat.is_valid()){
		return(-7);
	}
	//4-2.Ϊϵ������ֵ��
	for(unsigned int row=0;row!=coef_mat.get_rows();++row){
		for(unsigned int col=0;col!=coef_mat.get_cols();++col){
			//4-2-1.�����ǰΪϵ�������һ�С�
			if(0==col){
				coef_mat.set_element(row,col,1.0);
			}
			//4-2-2.�����ǰΪϵ������ڶ��С�
			else{
				const double conc=get_x(row);
				if(conc<ZERO_THRESHOLD_VALUE){
					return(-8);
				}
				coef_mat.set_element(row,col,log(conc));
			}
		}
	}
	//4-3.�����������
	DMat result_mat(get_size(),1);
	if(!result_mat.is_valid()){
		return(-9);
	}
	//4-4.Ϊ�������ֵ��
	for(unsigned int row=0;row!=result_mat.get_rows();++row){
		//4-4-1.��ȡ��ǰ������ȡ�
		const double abs=get_y(row);
		if(abs<0.0){
			return(-10);
		}
		//4-4-2.����Ax-B��ֵ��
		double temp1=abs-B;
		if(fabs(temp1)<ZERO_THRESHOLD_VALUE){
			//����Ϊ�㣬��Ϊ��Ҫ��Ϊ��ĸʹ�ã����Ϊ��Ļ���ʽ�����塣
			return(-11);
		}
		//4-4-3.����(K-(Ax-B))/(Ax-B)��ֵ��
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
		//4-4-4.���ý������ָ��Ԫ��ֵ��
		result_mat.set_element(row,0,log(temp2));
	}
	//4-5.����ϵ�������ת�þ���
	DMat coef_mat_trans;
	if(coef_mat.transpose(coef_mat_trans)<0){
		return(-13);
	}
	//4-6.�����������ϵ��ת�þ���������С���˷���ⷽ���顣
	coef_mat=coef_mat_trans*coef_mat;
	if(!coef_mat.is_valid()){
		return(-14);
	}
	result_mat=coef_mat_trans*result_mat;
	if(!result_mat.is_valid()){
		return(-15);
	}
	//4-7.��ϵ���������LU�ֽ⣬���ì�ܷ����顣
	if(MtSolvingEquations::solve(coef_mat,result_mat)<0){
		return(-16);
	}
	//4-8.�������a��ֵ��
	const double a=exp(result_mat[0][0]);
	//4-9.�������b��ֵ��
	const double b=result_mat[1][0];
	//5.�����������󣬲���Ϊ��������ֵ��
	//5-1.���в�������Ĵ����������жϴ����Ƿ�ɹ���
	if(parameters.create(4,1)<0){
		return(-17);
	}
	//5-2.Ϊ��ǰ��������ֵ��
	parameters.set_element(0,0,B);
	parameters.set_element(1,0,K);
	parameters.set_element(2,0,a);
	parameters.set_element(3,0,b);
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_jacobian_matrix
 * brief: ��ȡ��ǰ��ʽ�У�ָ���������ſɱȾ���
 * param: parameters - ָ���Ĳ�������
 *        jacobian - ���ص��ſɱȾ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::get_jacobian_matrix(const DMat &parameters,DMat &jacobian) const{
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(MtLMFormula::get_jacobian_matrix(parameters,jacobian)<0){
		return(-1);
	}
	//2.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.�����ſɱȾ��󣬲����жϴ����Ƿ�ɹ���
	if(jacobian.create(get_size(),4)<0){
		return(-3);
	}
	//4.Ϊ�ſɱȾ���ֵ��
	//4-1.������ǰ�������������
	double abs=0.0;
	double conc=0.0;
	double B=0.0;
	double K=0.0;
	double temp=0.0;
	double temp1=0.0;//Ax-B
	double temp2=0.0;//C^(b-1)
	double a=0.0;
	double b=0.0;
	//4-2.�����ſɱȾ��󣬲�Ϊ�ſɱȾ���ֵ��
	for(unsigned int row=0;row!=get_size();++row){
		//4-2-1.��ȡ��ǰ����Һ����ȣ������жϻ�ȡ�Ƿ�ɹ���
		abs=get_y(row);
		if(abs<0.0){
			return(-4);
		}
		//4-2-2.���㵱ǰ����ҺŨ�ȣ������жϼ����Ƿ�ɹ���
		if(calculate_concentration(parameters,abs,conc)<0){
			return(-5);
		}
		//4-2-3.����Ax-B��ֵ��
		temp1=abs-parameters[0][0];
		//4-2-4.����C^(b-1)��ֵ��
		temp2=pow(conc,(parameters[3][0]-1.0));
		if(_isnan(temp2)){
			return(-6);
		}
		//4-2-5.����B��ƫ������
		temp=parameters[2][0]*temp1*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-7);
		}
		B=parameters[1][0]/temp;
		//4-2-6.����K��ƫ������
		temp=parameters[2][0]*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-8);
		}
		K=1.0/temp;
		//4-2-7.����a��ƫ������
		temp=parameters[2][0]*parameters[2][0]*temp1*parameters[3][0]*temp2;
		if(fabs(temp)<ZERO_THRESHOLD_VALUE){
			return(-9);
		}
		a=(abs-parameters[0][0]-parameters[1][0])/temp;
		//4-2-8.����b��ƫ������
		if(fabs(parameters[3][0])<ZERO_THRESHOLD_VALUE){
			return(-10);
		}
		b=-((conc/parameters[3][0])*log(conc));
		//4-2-9.�����ſɱȾ����ֵ��
		jacobian.set_element(row,0,B);
		jacobian.set_element(row,1,K);
		jacobian.set_element(row,2,a);
		jacobian.set_element(row,3,b);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_difference_matrix
 * brief: ��ȡ��ǰ��ʽ��ָ�������Ĳ�ֵ����
 * param: parameters - ָ���Ĳ�������
 *        difference - ����ȡ�õĲ�ֵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::get_difference_matrix(const DMat &parameters,DMat &difference) const{
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(MtLMFormula::get_difference_matrix(parameters,difference)<0){
		return(-1);
	}
	//2.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.������ֵ���󣬲����жϴ����Ƿ�ɹ���
	if(difference.create(get_size(),1)<0){
		return(-3);
	}
	//4.������ֵ���󣬲�Ϊ��ֵ����ֵ��
	//4-1.������ǰ�������������
	double abs=0.0;
	double c_conc=0.0;
	double t_conc=0.0;
	//4-2.������ֵ���󣬲�Ϊ��ֵ����ֵ��
	for(unsigned int row=0;row!=get_size();++row){
		//4-2-1.��ȡ��ǰ����ȣ������жϻ�ȡ�Ƿ�ɹ���
		abs=get_y(row);
		if(abs<0.0){
			return(-2);
		}
		//4-2-2.����Ũ�ȣ������жϼ����Ƿ�ɹ���
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-3);
		}
		//4-2-3.��ȡʵ���Ũ�ȡ�
		t_conc=get_x(row);
		if(t_conc<0.0){
			return(-4);
		}
		//4-2-4.Ϊ��ֵ����ֵ��
		difference.set_element(row,0,t_conc-c_conc);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_sum_of_squares_of_deviations
 * brief: ��ȡ��ǰ��ʽ��ָ����������Ĳ�͡�
 * param: parameters - ָ���Ĳ�����
 *        sum - ���صĲ�͡�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::get_sum_of_squares_of_deviations(
	const DMat &parameters,double &sum) const{
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(MtLMFormula::get_sum_of_squares_of_deviations(
		parameters,sum)<0){
		return(-1);
	}
	//2.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.�����͡�
	//3-1.������ǰ�������������
	double abs=0.0;
	double c_conc=0.0;
	double t_conc=0.0;
	double sum_t=0.0;
	//3-2.������ǰ��ʽ�еĶ���Һ��Ϣ�������͡�
	for(unsigned int index=0;index!=get_size();++index){
		//3-2-1.��ȡ��ǰ����ȣ������жϻ�ȡ�Ƿ�ɹ���
		abs=get_y(index);
		if(abs<0.0){
			return(-3);
		}
		//3-2-2.����Ũ�ȣ������жϼ����Ƿ�ɹ���
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-4);
		}
		//3-2-3.����ʵ���Ũ�ȡ�
		t_conc=get_x(index);
		if(t_conc<0.0){
			return(-5);
		}
		//3-2-4.�����͡�
		sum_t+=(t_conc-c_conc)*(t_conc-c_conc);
	}
	//3-3.���浱ǰ��͡�
	sum=sum_t;
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_correlation_coefficient
 * brief: ��ȡ��ǰ��ʽ�£�ָ��������������ϵ����
 * param: parameters - ָ���Ĳ�����
 *        correlation_coefficient - ���ص����ϵ����
 *        relative_deviation - ���ص����ƫ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::get_correlation_coefficient(const DMat &parameters,
	double &correlation_coefficient,DMat &relative_deviation) const{
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(MtLMFormula::get_correlation_coefficient(parameters,
		correlation_coefficient,relative_deviation)<0){
		return(-1);
	}
	//2.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((!parameters.is_valid())||(4!=parameters.get_rows())||
		(1!=parameters.get_cols())){
		return(-2);
	}
	//3.�������ƫ��洢���󣬲����жϴ����Ƿ�ɹ���
	if(relative_deviation.create(get_size(),1)<0){
		return(-3);
	}
	//4.���㵱ǰ��ʽ��ָ�����������ƫ������жϼ����Ƿ�ɹ���
	for(unsigned int index=1;index!=get_size();++index){
		//4-1.��ȡ��ǰ����Һ������ȡ�
		const double abs=get_y(index);
		if(abs<0.0){
			return(-4);
		}
		//4-2.���ݵ�ǰ����������ȼ���Ũ�ȣ������жϼ����Ƿ�ɹ���
		double c_conc=0.0;
		if(calculate_concentration(parameters,abs,c_conc)<0){
			return(-5);
		}
		//4-3.��ȡ��ǰ����Һʵ��Ũ�ȡ�
		const double conc=get_x(index);
		if(conc<0.0){
			return(-6);
		}
		//4-4.���㵱ǰ���ƫ�
		const double coef=fabs((conc-c_conc)/conc);
		//4-5.�����ƫ���ֵ���浽���ƫ������С�
		relative_deviation.set_element(index,0,coef);
	}
	//5.���㵱ǰ��ʽ��ָ�����������ϵ���������ж����ϵ���Ƿ�Ϸ���
	//5-1.������ǰ�������������
	double s0=0.0;
	double s1=0.0;
	//5-2.��ȡ��ǰ��ʽ�ж���Һ��ƽ������ȣ������жϻ�ȡ�Ƿ�ɹ���
	const double avg_abs=get_average_y();
	if(avg_abs<0.0){
		return(-7);
	}
	//5-3.��������Һ�����ۼƲ�ͣ�Ϊ������ϵ����׼����
	for(unsigned int index=0;index!=get_size();++index){
		//5-3-1.��ȡ��ǰ����Һ��ʵ��Ũ�ȡ�
		const double conc=get_x(index);
		if(conc<0.0){
			return(-8);
		}
		//5-3-2.���ݵ�ǰ������������ȣ������жϼ����Ƿ�ɹ���
		double cal_abs=0.0;
		if(calculate_absorbance(parameters,conc,cal_abs)<0){
			return(-9);
		}
		//5-3-3.��ȡ��ǰ����Һʵ�ʵ�����ȡ�
		const double abs=get_y(index);
		if(abs<0.0){
			return(-10);
		}
		//5-3-4.�ۼƲ�͡�
		s0+=(abs-cal_abs)*(abs-cal_abs);
		s1+=(abs-avg_abs)*(abs-avg_abs);
	}
	//5-4.�����ǰ����ķ�ĸs1���Ϸ�����ֱ�ӷ��ش���
	if(fabs(s1)<ZERO_THRESHOLD_VALUE){
		return(-11);
	}
	//5-5.�������ϵ����
	const double coef=1.0-(s0/s1);
	//5-6.���浱ǰ���ϵ����
	correlation_coefficient=coef;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_absorbance
 * brief: ��ǰ��ʽ�£�ָ��������Ũ�ȣ���������ȡ�
 * param: parameters - ָ���Ĳ�����
 *        conc - ָ����Ũ�ȡ�
 *        abs - ���ص�����ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::calculate_absorbance(
	const DMat &parameters,const double conc,double &abs) const{
	//remark:�ڴ�Ĭ��paramaeters��conc���ǺϷ��ġ�
	//1.����1.0+a*c^b ��
	const double temp=1.0+(parameters[2][0]*pow(conc,parameters[3][0]));
	if(fabs(temp)<ZERO_THRESHOLD_VALUE){
		return(-1);
	}
	//2.����Ax=B+K/(1.0+a*c^b) ��
	abs=parameters[0][0]+(parameters[1][0]/temp);
	if(_isnan(abs)){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_concentration
 * brief: ��ǰ��ʽ�£�ָ������������ȣ�����Ũ�ȡ�
 * param: parameters - ָ���Ĳ�����
 *        abs - ָ��������ȡ�
 *        conc - ���ص�Ũ�ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LogitLog4P::calculate_concentration(
	const DMat &parameters,const double abs,double &conc) const{
	//remark:�ڴ�Ĭ��paramaeters��abs���ǺϷ��ġ�
	//1.����1.0/b��
	if(fabs(parameters[3][0])<ZERO_THRESHOLD_VALUE){//����Ϊ�㣬������Ҫ��Ϊ��ĸʹ�á�
		return(-1);
	}
	const double temp1=1.0/parameters[3][0];
	//2.����Ax-B��
	const double temp2=abs-parameters[0][0];
	//3.����a*(Ax-B)
	const double temp3=parameters[2][0]*temp2;
	if(fabs(temp3)<ZERO_THRESHOLD_VALUE){//����Ϊ�㣬ӦΪ������Ϊ��ĸʹ�á�
		return(-2);
	}
	//4.����(K-(Ax-B))/(a*(Ax-B))��ֵ��
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
	//5.����Ũ�ȡ�
	conc=pow(temp4,temp1);
	if(_isnan(conc)){
		return(-4);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}