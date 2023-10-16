#include"stdafx.h"
#include"MtLMFormula.h"
#include"MtMatrix.h"
#include<cmath>

/**
 * name: MtLMFormula
 * breif: 构造函数。
 * param: x - 指向待拟合的x数组。
 *        y - 指向待拟合的y数组。
 *        size - 待拟合x、y数组尺寸。
 *        min_size - 待拟合x、y数组最小尺寸。
 * return: --
 */
MtLMFormula::MtLMFormula(const double* x, const double* y,
	const unsigned int size, const unsigned int minimum_size)
	:MtFormula(x, y, size, minimum_size)
	, _maximum_relative_deviation(0.0)
	, _correlation_coefficient(0.0)
	, _weight(new DMat) {
	if (is_can_fitted()) {
		const unsigned int size_t = get_size();
		if (_weight->create(size_t, size_t) >= 0) {
			for (unsigned int i = 0; i != size_t; ++i) {
				const double x_t = get_y(i);
				for (unsigned int j = 0; j != size_t; ++j) {
					if (i == j) {
						//if (fabs(x_t) <= 1.0E-6) {
						_weight->set_element(i, j, 1.0);
						/*	}
							else {
								_weight->set_element(i, j, 1.0 / x_t);
							}*/
					}
					else {
						_weight->set_element(i, j, 0.0);
					}
				}
			}
		}
	}
}

/**
 * name: ~MtLMFormula
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLMFormula::~MtLMFormula(void) {
	delete _weight;
}

/**
 * name: set_maximum_relative_deviation
 * brief: 设置当前公式的最大相对偏差。
 * param: maximum_relative_deviation - 最大相对偏差。
 * return: --
 */
void MtLMFormula::set_maximum_relative_deviation(
	const double maximum_relative_deviation) {
	if (is_can_fitted()) {
		_maximum_relative_deviation = maximum_relative_deviation;
	}
	else {
		_maximum_relative_deviation = 0.0;
	}
}

/**
 * name: get_maximum_relative_deviation
 * brief: 获取当前公式的最大相对偏差。
 * param: --
 * return: 返回当前公式的最大相对偏差。
 */
double MtLMFormula::get_maximum_relative_deviation() const {
	if (is_can_fitted()) {
		return(_maximum_relative_deviation);
	}
	else {
		return(0.0);
	}
}

/**
 * name: set_correlation_coefficient
 * breif: 设置当前公式的相关系数。
 * param: correlation_coefficient - 相关系数。
 * return: --
 */
void MtLMFormula::set_correlation_coefficient(
	const double correlation_coefficient) {
	if (is_can_fitted()) {
		_correlation_coefficient = correlation_coefficient;
	}
	else {
		_correlation_coefficient = 0.0;
	}
}

/**
 * name: get_correlation_coefficient
 * breif: 获取当前公式的相关系数。
 * param: --
 * return: 返回当前公式的相关系数。
 */
double MtLMFormula::get_correlation_coefficient() const {
	if (is_can_fitted()) {
		return(_correlation_coefficient);
	}
	else {
		return(0.0);
	}
}

/**
 * name: get_weight_matrix
 * breif: 获取当前公式的系数矩阵。
 * param: --
 * return: 返回当前公式的系数矩阵。
 */
const MtLMFormula::DMat& MtLMFormula::get_weight_matrix() const {
	return(*_weight);
}

/**
 * name: set_parameters
 * brief: 设置当前公式参数。
 * param: parameters - 指定的当前公式参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::set_parameters(const DMat&/*parameters*/) {
	return(0);
}

/**
 * name: calculate_initialized_parameters
 * brief: 计算当前公式的初始参数。
 * param: parameters - 返回的参数。
 * return: 如果计算公式的初始参数成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_initialized_parameters(DMat&/*parameters*/) {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.如果当前公式满足拟合条件。
	else {
		return(0);
	}
}

/**
 * name: calculate_jacobian_matrix
 * brief: 计算当前公式下指定参数的雅可比矩阵。
 * param: parameters - 指定的公式参数。
 *        jacobian - 返回的雅可比矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_jacobian_matrix(
	const DMat&/*parameters*/, DMat&/*jacobian*/) const {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_difference_matrix
 * brief: 计算当前公式下指定参数的差值矩阵。
 * param: parameters - 指定的参数。
 *        difference - 差值矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_difference_matrix(
	const DMat&/*parameters*/, DMat&/*difference*/) const {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_sum_of_squares_of_deviations
 * brief: 计算当前公式下指定参数的差方和。
 * param: parameters - 指定的参数。
 *        sum - 返回的差方和。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_sum_of_squares_of_deviations(
	/*const*/ DMat&/*parameters*/, double&/*sum*/) const {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_maximum_relative_deviation
 * breif: 计算当前公式中，指定参数计算的最大相对偏差。
 * param: parameters - 指定的参数。
 *        relative_deviation - 相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_maximum_relative_deviation(
	const DMat& /*parameters*/, double& /*relative_deviation*/) const {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * brief: 计算当前公式下，指定参数计算的相关系数。
 * param: parameters - 指定的参数。
 *        correlation_coefficient - 返回的相关系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFormula::calculate_correlation_coefficient(
	const DMat&/*parameters*/, double&/*correlation_coefficient*/) const {
	//1.如果当前公式不满足拟合条件。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.程序运行到此成功返回。
	return(0);
}