#include"stdafx.h"
#include"MtPolynomialFitting.h"
#include"MtMatrix.h"
#include"MtPolynomialFormula.h"
#include"MtSolvingEquations.h"

/**
 * name: MtPolynomialFitting
 * brief: ���캯����
 * param: formula - ����Ĵ���Ϲ�ʽ��
 * return: --
 */
MtPolynomialFitting::MtPolynomialFitting(FORMULA &formula)
	:_formula(formula){
}

/**
 * name: ~MtPolynomialFitting
 * brief: ����������
 * param: --
 * return: --
 */
MtPolynomialFitting::~MtPolynomialFitting(void){
}

/**
 * name: fit
 * brief: �Ե�ǰ��ʽ������ϡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPolynomialFitting::fit(){
	//1.���㵱ǰ��ʽ��ϵ�������Լ��������
	DMat a,b;
	if((_formula.calculate_coefficient_matrix(a)<0)||(
		_formula.calculate_result_matrix(b)<0)){
		return(-1);
	}
	//2.���㵱ǰϵ�������ת�þ��󣬲����жϼ����Ƿ�ɹ���
	DMat a_t;
	if(a.transpose(a_t)<0){
		return(-2);
	}
	//3.����ϵ�������ת�þ������ϵ�������Լ��������
	if(a.copy(a_t.multiply(a))<0){
		return(-3);
	}
	if(b.copy(a_t.multiply(b))<0){
		return(-4);
	}
	//4.��ⷽ���飬�����ж�����Ƿ�ɹ���
	if(MtSolvingEquations::solve(a,b)<0){
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
	//7.��ʽ�б�����Ͻ����
	if(_formula.set_parameters(b)<0){
		return(-8);
	}
	_formula.set_correlation_coefficient(
		correlation_coefficient);
	_formula.set_maximum_relative_deviation(
		maximum_relative_deviation);
	//8.�������е���ֱ�ӳɹ����ء�
	return(0);
}