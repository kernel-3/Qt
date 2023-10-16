#include"stdafx.h"
#include"MtSimpleLinearFormula.h"
#include"MtMatrix.h"
#include<math.h>

const double MtSimpleLinearFormula::TINY=1.0E-20;

/**
 * name: MtSimpleLinearFormula
 * breif: 构造函数。
 * param: x - 指向待拟合的x数组。
 *        y - 指向待拟合的y数组。
 *        size - 待拟合x、y数组尺寸。
 * return: --
 */
MtSimpleLinearFormula::MtSimpleLinearFormula(
	const double *x,const double *y,const unsigned int size)
	:MtFormula(x,y,size,PARAMETER_COUNT)
	,_parameters(new DMat(PARAMETER_COUNT,1))
	,_correlation_coefficient(0.0)
	,_maximum_relative_deviation(0.0){
}

/**
 * name: ~MtSimpleLinearFormula
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtSimpleLinearFormula::~MtSimpleLinearFormula(void){
	delete _parameters;
}

/**
 * name: calculate_x
 * brief: 根据给定的参数、y值计算x值。
 * param: parameters - 公式参数。
 *        y - 指定的y值。
 *        x - 返回计算的x值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_x(
	const DMat &parameters,const double y,double &x){
	//1.如果当前传递的参数不合法，则直接返回错误。
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-1);
	}
	//2.根据给定的y，计算x。
	const double a=parameters.get_element(0,0);
	const double b=parameters.get_element(1,0);
	if(fabs(a)<TINY){
		return(-2);
	}
	x=(y-b)/a;
	//3.程序运行到此直接返回。
	return(0);
}

/**
 * name: calculate_y
 * breif: 根据给定的参数，x值计算y值。
 * param: parameters - 指定的参数。
 *        x - 指定的x值。
 *        y - 指定的y值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_y(
	const DMat &parameters,const double x,double &y){
	//1.如果当前传递的参数不合法，则直接返回错误。
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-1);
	}
	//2.根据给定的x，计算y。
	const double a=parameters.get_element(0,0);
	const double b=parameters.get_element(1,0);
	y=a*x+b;
	//3.程序运行到此直接返回。
	return(0);
}

/**
 * name: set_parameters
 * brief: 设置当前参数。
 * param: parameters - 指定参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::set_parameters(const DMat &parameters){
	if(_parameters->copy(parameters)<0){
		return(-1);
	}else{
		return(0);
	}
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数矩阵引用。
 */
const MtSimpleLinearFormula::DMat &
	MtSimpleLinearFormula::get_parameters() const{
	return(*_parameters);
}

/**
 * name: set_correlation_coefficient
 * breif: 设置相关系数。
 * param: correlation_coefficient - 指定的相关系数。
 * return: --
 */
void MtSimpleLinearFormula::set_correlation_coefficient(
	const double correlation_coefficient){
	_correlation_coefficient=correlation_coefficient;
}

/**
 * name: get_correlation_coefficient
 * breif: 获取相关系数。
 * param: --
 * return: 返回当前公式的相关系数。
 */
double MtSimpleLinearFormula::get_correlation_coefficient() const{
	return(_correlation_coefficient);
}

/**
 * name: set_maximum_relative_deviation
 * brief: 设置最大相对偏差。
 * param: relative_deviation - 输入的最大相对偏差。
 * return: --
 */
void MtSimpleLinearFormula::set_maximum_relative_deviation(
	const double relative_deviation){
	_maximum_relative_deviation=relative_deviation;
}

/**
 * name: get_maximum_relative_deviation
 * brief: 获取最大的相对偏差。
 * param: --
 * return: 返回最大的相对偏差。
 */
double MtSimpleLinearFormula::get_maximum_relative_deviation() const{
	return(_maximum_relative_deviation);
}

/**
 * name: calculate_coefficient_matrix
 * brief: 计算系数矩阵。
 * param: c - 计算后返回的系数矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_coefficient_matrix(DMat &c) const{
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if(!is_can_fitted()){
		return(-1);
	}
	//2.获取当前公式拟合数据个数。
	const unsigned int size=get_size();
	if(0==size){
		return(-2);
	}
	//3.创建系数矩阵，并且判断创建是否成功。
	if(c.create(size,PARAMETER_COUNT)<0){
		return(-3);
	}
	//4.遍历拟合数据，计算系数矩阵。
	for(unsigned int i=0;i!=size;++i){
		const double x=get_x(i);
		c.set_element(i,0,x);
		c.set_element(i,1,1.0);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_result_matrix
 * breif: 计算结果矩阵。
 * param: b - 计算后返回的结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_result_matrix(DMat &b) const{
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if(!is_can_fitted()){
		return(-1);
	}
	//2.获取当前公式拟合数据个数。
	const unsigned int size=get_size();
	if(0==size){
		return(-2);
	}
	//3.创建结果矩阵，并且判断创建是否成功。
	if(b.create(size,1)<0){
		return(-3);
	}
	//4.遍历拟合数据，计算结果矩阵。
	for(unsigned int i=0;i!=size;++i){
		const double y=get_y(i);
		b.set_element(i,0,y);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * breif: 根据指定的参数，计算当前公式的相关系数。
 * param: parameters - 指定的参数。
 *        correlation_coefficient - 计算返回的相关系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_correlation_coefficient(
	const DMat &parameters,double &correlation_coefficient) const{
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if(!is_can_fitted()){
		return(-1);
	}
	//2.如果当前传递的参数不合法，则直接返回错误。
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-2);
	}
	//3.计算相关系数。
	double avg_y=get_average_y();
	const unsigned int size=get_size();
	if(0==size){
		return(-3);
	}
	double ss_res=0.0;
	double ss_tot=0.0;
	for(unsigned int i=0;i!=size;++i){
		const double t_y=get_y(i);
		const double t_x=get_x(i);
		double c_y=0.0;
		if(calculate_y(parameters,t_x,c_y)<0){
			return(-4);
		}
		ss_res+=(t_y-c_y)*(t_y-c_y);
		ss_tot+=(t_y-avg_y)*(t_y-avg_y);
	}
	if(fabs(ss_tot)<TINY){
		return(-5);
	}
	correlation_coefficient=1.0-(ss_res/ss_tot);
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_maximum_relative_deviation
 * brief: 计算当前公式中，指定参数下，计算的最大相对偏差。
 * param: parameters - 指定的参数。
 *        relative_deviation - 返回的最大相对偏差值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSimpleLinearFormula::calculate_maximum_relative_deviation(
	const DMat &parameters,double &relative_deviation) const{
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if(!is_can_fitted()){
		return(-1);
	}
	//2.如果当前传递的参数不合法，则直接返回错误。
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-2);
	}
	//3.计算最大的相对偏差，并且判断计算是否成功。
	//3-1.获取当前x、y的数量。
	const unsigned int size=get_size();
	if(0==size){
		return(-3);
	}
	//3-2.迭代计算最大的相对偏差。
	double maximum_relative_deviation=0.0;
	unsigned int b_i=0;
	if(size>=6){
		b_i=1;
	}
	for(unsigned int i=b_i;i!=size;++i){
		const double y=get_y(i);
		const double x=get_x(i);
		double c_x=0.0;
		if(calculate_x(parameters,y,c_x)<0){
			return(-4);
		}
		const double temp=fabs((x-c_x)/x);
		if((b_i==i)||(temp>maximum_relative_deviation)){
			maximum_relative_deviation=temp;
		}
	}
	//3-3.保存当前最大的相对偏差。
	relative_deviation=maximum_relative_deviation;
	//4.程序运行到此直接成功返回。
	return(0);
}