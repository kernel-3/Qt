#include"stdafx.h"
#include"MtSolvingPolynomial.h"
#include"MtMatrix.h"
#include<complex>
#include<cmath>

//定义类中静态变量。
const double MtSolvingPolynomial::TINY = 1.0E-20;

/**
 * name: solve
 * brief: 求解多项式。
 * param: coefficient - 输入的多项式系数矩阵(n*1维矩阵)。
 *        target_value - 输入的靶值（求解高次多项式时需要靶值，用来确定哪一个解是期望）。
 *        target_value_relative_position - 输入靶值的相对位置（<0 靶值小于待测值 ==0 靶值等于待测值 >0 靶值大于待测值）。
 *        root - 输出的根。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingPolynomial::solve(const DMat& coefficient,
	const double target_value,
	double& root) {
	//1.检测当前输入参数是否合法，如果不合法则直接返回错误。
	if ((!coefficient.is_valid()) || (coefficient.get_rows() < 2) || (
		1 != coefficient.get_cols())) {
		return(-1);
	}
	//2.声明当前操作所需变量。
	const unsigned int hightest_power = coefficient.get_rows() - 1;
	//3.根据多项式的最高次幂，采用不同的方式求解多项式（目前支持三次多项式的求解）。
	if (3 == hightest_power) {
		if (cardano_method(coefficient, target_value,
			root) < 0) {
			return(-2);
		}
		else {
			return(0);
		}
	}
	//4.程序运行到此直接返回错误。
	return(-3);
}

/**
 * name: cardano_method
 * brief: 利用Cardano方法求解三次多项式。
 * param: coefficient - 输入的多项式系数矩阵(n*1维矩阵)。
 *        target_value - 输入的靶值（求解高次多项式时需要靶值，用来确定哪一个解是期望）。
 *        target_value_relative_position - 输入靶值的相对位置（<0 靶值小于待测值 ==0 靶值等于待测值 >0 靶值大于待测值）。
 *        root - 输出的根。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 公式详细情况参看https://proofwiki.org/wiki/Cardano's_Formula。
 */
int MtSolvingPolynomial::cardano_method(
	const DMat& coefficient, const double target_value,
	double& root) {
	//1.如果输入的参数不合法，则直接返回错误。
	if (abs(coefficient.get_element(0, 0)) < TINY) {
		return(-1);
	}
	//2.获取三次多项式中的系数a、b、c、d。
	const double a = coefficient.get_element(0, 0);
	const double b = coefficient.get_element(1, 0);
	const double c = coefficient.get_element(2, 0);
	const double d = coefficient.get_element(3, 0);
	//3.计算Cardano公式中的Q以及R。
	const double Q = (3.0 * a * c - b * b) / (9.0 * a * a);
	const double R = (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b) / (54.0 * a * a * a);
	//4.计算Cardano公式中的判别式D。
	const double D = Q * Q * Q + R * R;
	//5.如果当前存在三个实根，并且至少有两个根相同。
	if (abs(D) < TINY) {
		//5-1.计算Cardano公式中的S和T。
		double S = pow(abs(R), 1.0 / 3.0);
		if (R < 0.0) {
			S *= -1.0;
		}
		const double T = S;
		//5-2.计算三个实根（至少两个相等）。
		double x1 = S + T - (b / (3.0 * a));
		double x2 = (-((S + T) / 2.0)) - (b / (3.0 * a));
		//5-3.对两个根进行排序。
		if (x1 > x2) {
			double temp = x1;
			x1 = x2;
			x2 = temp;
		}
		root = x1;
		//5-5.程序运行到此成功返回。
		return(0);
	}
	//6.如果当前存在一个实根以及两个虚根。
	else if (D > 0.0) {
		//6-1.定义。
		typedef std::complex<double> COMPLEX;
		//6-2.计算Cardano公式中的S和T。
		double S = pow(abs(R + sqrt(D)), 1.0 / 3.0);
		if ((R + sqrt(D)) < 0.0) {
			S *= (-1.0);
		}
		double T = pow(abs(R - sqrt(D)), 1.0 / 3.0);
		if ((R - sqrt(D)) < 0.0) {
			T *= (-1.0);
		}
		//6-3.计算一个实根以及两个共轭虚根。
		COMPLEX temp(0.0, sqrt(3.0) / 2.0);
		double x1 = S + T - (b / (3.0 * a));
		const COMPLEX x2 = (-(static_cast<COMPLEX>(S + T) /
			static_cast<COMPLEX>(2.0))) - static_cast<COMPLEX>(
				b / (3.0 * a)) + (temp * static_cast<COMPLEX>(S - T));
		const COMPLEX x3 = (-(static_cast<COMPLEX>(S + T) /
			static_cast<COMPLEX>(2.0))) - static_cast<COMPLEX>(
				b / (3.0 * a)) - (temp * static_cast<COMPLEX>(S - T));
		//6-4.将虚根转换为实根。
		double x2_r = x2.real() + x2.imag();
		double x3_r = x3.real() - x3.imag();
		//6-5.对三个根进行排序。
		if (x1 > x2_r) {
			double temp_t = x1;
			x1 = x2_r;
			x2_r = temp_t;
		}
		if (x2_r > x3_r) {
			double temp_t = x2_r;
			x2_r = x3_r;
			x3_r = temp_t;
		}
		//6-6.筛选求解的根，找出最符合要求的根。
		//a.声明当前操作所需变量。
		//b.如果当前靶值与待测值重合。
				//6-7.返回求解的根。
		root = x1;
		//6-8.程序运行到此成功返回。
		return(0);
	}
	//7.如果当前存在三个实根，并且三个实根都不相等。
	else {
		//7-1.定义。
		typedef std::complex<double> COMPLEX;
		//7-2.计算Cardano公式中的S和T。
		COMPLEX temp = sqrt(static_cast<COMPLEX>(D));
		const COMPLEX S = pow(static_cast<COMPLEX>(R) + temp, 1.0 / 3.0);
		const COMPLEX T = pow(static_cast<COMPLEX>(R) - temp, 1.0 / 3.0);
		//7-3.计算三个实根。
		COMPLEX x1 = S + T - static_cast<COMPLEX>(b / (3.0 * a));
		temp.real(0.0);
		temp.imag(sqrt(3.0) / 2.0);
		COMPLEX x2 = (-((S + T) / static_cast<COMPLEX>(2.0))) -
			static_cast<COMPLEX>(b / (3.0 * a)) + (temp * (S - T));
		COMPLEX x3 = (-((S + T) / static_cast<COMPLEX>(2.0))) -
			static_cast<COMPLEX>(b / (3.0 * a)) - (temp * (S - T));
		//7-4.对x1、x2、x3进行排序。
		if ((x1.real()) > (x2.real())) {
			COMPLEX temp_t = x1;
			x1 = x2;
			x2 = temp_t;
		}
		if ((x2.real()) > (x3.real())) {
			COMPLEX temp_t = x2;
			x2 = x3;
			x3 = temp_t;
		}
		//7-5.筛选求解的根，找出最符合要求的根。
		//a.声明当前操作所需变量。
		//b.如果当前靶值与待测值重合。
			//7-6.返回求解的根。
		root = x1.real();
		//8.程序运行到此成功返回。
		return(0);
	}
}