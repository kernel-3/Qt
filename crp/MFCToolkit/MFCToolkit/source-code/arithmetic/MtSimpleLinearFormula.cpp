#include"stdafx.h"
#include"MtSimpleLinearFormula.h"
#include"MtMatrix.h"
#include<math.h>

const double MtSimpleLinearFormula::TINY=1.0E-20;

/**
 * name: MtSimpleLinearFormula
 * breif: ���캯����
 * param: x - ָ�����ϵ�x���顣
 *        y - ָ�����ϵ�y���顣
 *        size - �����x��y����ߴ硣
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
 * breif: ����������
 * param: --
 * return: --
 */
MtSimpleLinearFormula::~MtSimpleLinearFormula(void){
	delete _parameters;
}

/**
 * name: calculate_x
 * brief: ���ݸ����Ĳ�����yֵ����xֵ��
 * param: parameters - ��ʽ������
 *        y - ָ����yֵ��
 *        x - ���ؼ����xֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_x(
	const DMat &parameters,const double y,double &x){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-1);
	}
	//2.���ݸ�����y������x��
	const double a=parameters.get_element(0,0);
	const double b=parameters.get_element(1,0);
	if(fabs(a)<TINY){
		return(-2);
	}
	x=(y-b)/a;
	//3.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: calculate_y
 * breif: ���ݸ����Ĳ�����xֵ����yֵ��
 * param: parameters - ָ���Ĳ�����
 *        x - ָ����xֵ��
 *        y - ָ����yֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_y(
	const DMat &parameters,const double x,double &y){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-1);
	}
	//2.���ݸ�����x������y��
	const double a=parameters.get_element(0,0);
	const double b=parameters.get_element(1,0);
	y=a*x+b;
	//3.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: set_parameters
 * brief: ���õ�ǰ������
 * param: parameters - ָ��������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
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
 * brief: ��ȡ��ǰ������
 * param: --
 * return: ���ص�ǰ�����������á�
 */
const MtSimpleLinearFormula::DMat &
	MtSimpleLinearFormula::get_parameters() const{
	return(*_parameters);
}

/**
 * name: set_correlation_coefficient
 * breif: �������ϵ����
 * param: correlation_coefficient - ָ�������ϵ����
 * return: --
 */
void MtSimpleLinearFormula::set_correlation_coefficient(
	const double correlation_coefficient){
	_correlation_coefficient=correlation_coefficient;
}

/**
 * name: get_correlation_coefficient
 * breif: ��ȡ���ϵ����
 * param: --
 * return: ���ص�ǰ��ʽ�����ϵ����
 */
double MtSimpleLinearFormula::get_correlation_coefficient() const{
	return(_correlation_coefficient);
}

/**
 * name: set_maximum_relative_deviation
 * brief: ����������ƫ�
 * param: relative_deviation - �����������ƫ�
 * return: --
 */
void MtSimpleLinearFormula::set_maximum_relative_deviation(
	const double relative_deviation){
	_maximum_relative_deviation=relative_deviation;
}

/**
 * name: get_maximum_relative_deviation
 * brief: ��ȡ�������ƫ�
 * param: --
 * return: �����������ƫ�
 */
double MtSimpleLinearFormula::get_maximum_relative_deviation() const{
	return(_maximum_relative_deviation);
}

/**
 * name: calculate_coefficient_matrix
 * brief: ����ϵ������
 * param: c - ����󷵻ص�ϵ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_coefficient_matrix(DMat &c) const{
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if(!is_can_fitted()){
		return(-1);
	}
	//2.��ȡ��ǰ��ʽ������ݸ�����
	const unsigned int size=get_size();
	if(0==size){
		return(-2);
	}
	//3.����ϵ�����󣬲����жϴ����Ƿ�ɹ���
	if(c.create(size,PARAMETER_COUNT)<0){
		return(-3);
	}
	//4.����������ݣ�����ϵ������
	for(unsigned int i=0;i!=size;++i){
		const double x=get_x(i);
		c.set_element(i,0,x);
		c.set_element(i,1,1.0);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_result_matrix
 * breif: ����������
 * param: b - ����󷵻صĽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_result_matrix(DMat &b) const{
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if(!is_can_fitted()){
		return(-1);
	}
	//2.��ȡ��ǰ��ʽ������ݸ�����
	const unsigned int size=get_size();
	if(0==size){
		return(-2);
	}
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	if(b.create(size,1)<0){
		return(-3);
	}
	//4.����������ݣ�����������
	for(unsigned int i=0;i!=size;++i){
		const double y=get_y(i);
		b.set_element(i,0,y);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * breif: ����ָ���Ĳ��������㵱ǰ��ʽ�����ϵ����
 * param: parameters - ָ���Ĳ�����
 *        correlation_coefficient - ���㷵�ص����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_correlation_coefficient(
	const DMat &parameters,double &correlation_coefficient) const{
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if(!is_can_fitted()){
		return(-1);
	}
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-2);
	}
	//3.�������ϵ����
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
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_maximum_relative_deviation
 * brief: ���㵱ǰ��ʽ�У�ָ�������£������������ƫ�
 * param: parameters - ָ���Ĳ�����
 *        relative_deviation - ���ص�������ƫ��ֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFormula::calculate_maximum_relative_deviation(
	const DMat &parameters,double &relative_deviation) const{
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if(!is_can_fitted()){
		return(-1);
	}
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((!parameters.is_valid())||(
		PARAMETER_COUNT!=parameters.get_rows())||(
		1!=parameters.get_cols())){
		return(-2);
	}
	//3.�����������ƫ������жϼ����Ƿ�ɹ���
	//3-1.��ȡ��ǰx��y��������
	const unsigned int size=get_size();
	if(0==size){
		return(-3);
	}
	//3-2.���������������ƫ�
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
	//3-3.���浱ǰ�������ƫ�
	relative_deviation=maximum_relative_deviation;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}