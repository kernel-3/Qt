#include"stdafx.h"
#include"MtSimpleLinearFitting.h"
#include"MtSimpleLinearFormula.h"
#include"MtMatrix.h"
#include"MtSolvingEquations.h"

/**
 * name: MtSimpleLinearFitting
 * breif: ���캯����
 * param: formula - ����Ϲ�ʽ��
 * return: --
 */
MtSimpleLinearFitting::MtSimpleLinearFitting(FORMULA &formula)
	:_formula(formula){
}

/**
 * name: ~MtSimpleLinearFitting
 * brief: ����������
 * param: --
 * return: --
 */
MtSimpleLinearFitting::~MtSimpleLinearFitting(void){
}

/**
 * name: fit
 * brief: �Ե�ǰ��ʽ������ϡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSimpleLinearFitting::fit(){
	//1.���㵱ǰ��ʽ��ϵ�������Լ��������
	DMat c,b;
	if((_formula.calculate_coefficient_matrix(c)<0)||(
		_formula.calculate_result_matrix(b)<0)){
		return(-1);
	}
	//2.���㵱ǰϵ�������ת�þ��󣬲����жϼ����Ƿ�ɹ���
	DMat c_t;
	if(c.transpose(c_t)<0){
		return(-2);
	}
	//3.����ϵ�������ת�þ������ϵ�������Լ��������
	if(c.copy(c_t.multiply(c))<0){
		return(-3);
	}
	if(b.copy(c_t.multiply(b))<0){
		return(-4);
	}
	//4.��ⷽ���飬�����ж�����Ƿ�ɹ���
	if(MtSolvingEquations::solve(c,b)<0){
		return(-5);
	}
	//5.�������ϵ����
	double correlation_coefficient=0.0;
	if(_formula.calculate_correlation_coefficient(
		b,correlation_coefficient)<0){
		return(-6);
	}
	//6.����������ƫ�
	double maximum_relative_deviation=0.0;
	if(_formula.calculate_maximum_relative_deviation(
		b,maximum_relative_deviation)<0){
		return(-7);
	}
	//6.��ʽ�б�����Ͻ����
	if(_formula.set_parameters(b)<0){
		return(-8);
	}
	_formula.set_correlation_coefficient(
		correlation_coefficient);
	_formula.set_maximum_relative_deviation(
		maximum_relative_deviation);
	//7.�������е���ֱ�ӳɹ����ء�
	return(0);
}