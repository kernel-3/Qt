#include"stdafx.h"
#include"MtPolynomialFitting.h"
#include"MtMatrix.h"
#include"MtPolynomialFormula.h"
#include"MtSolvingEquations.h"

/**
 * name: MtPolynomialFitting
 * brief: 构造函数。
 * param: formula - 输入的待拟合公式。
 * return: --
 */
MtPolynomialFitting::MtPolynomialFitting(FORMULA &formula)
	:_formula(formula){
}

/**
 * name: ~MtPolynomialFitting
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtPolynomialFitting::~MtPolynomialFitting(void){
}

/**
 * name: fit
 * brief: 对当前公式进行拟合。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPolynomialFitting::fit(){
	//1.计算当前公式的系数矩阵以及结果矩阵。
	DMat a,b;
	if((_formula.calculate_coefficient_matrix(a)<0)||(
		_formula.calculate_result_matrix(b)<0)){
		return(-1);
	}
	//2.计算当前系数矩阵的转置矩阵，并且判断计算是否成功。
	DMat a_t;
	if(a.transpose(a_t)<0){
		return(-2);
	}
	//3.计算系数矩阵的转置矩阵乘以系数矩阵以及结果矩阵。
	if(a.copy(a_t.multiply(a))<0){
		return(-3);
	}
	if(b.copy(a_t.multiply(b))<0){
		return(-4);
	}
	//4.求解方程组，并且判断求解是否成功。
	if(MtSolvingEquations::solve(a,b)<0){
		return(-5);
	}
	//5.计算相关系数。
	double correlation_coefficient=0.0;
	if(_formula.calculate_correlation_coefficient(
		b,correlation_coefficient)<0){
		return(-6);
	}
	//6.计算最大相对偏差。
	double maximum_relative_deviation=0.0;
	if(_formula.calculate_maximum_relative_deviation(
		b,maximum_relative_deviation)<0){
		return(-7);
	}
	//7.公式中保存拟合结果。
	if(_formula.set_parameters(b)<0){
		return(-8);
	}
	_formula.set_correlation_coefficient(
		correlation_coefficient);
	_formula.set_maximum_relative_deviation(
		maximum_relative_deviation);
	//8.程序运行到此直接成功返回。
	return(0);
}