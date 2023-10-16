#include"stdafx.h"
#include"MtPolynomialFormula.h"
#include"MtMatrix.h"
#include"MtSolvingPolynomial.h"
#include<math.h>

const double MtPolynomialFormula::TINY = 1.0E-20;

/**
 * name: MtPolynomialFormula
 * brief: 构造函数.
 * param: x - 输入的指向待拟合x数组的指针。
 *        y - 输入的指向待拟合y数组的指针。
 *        size - 输入的待拟合x、y数组的尺寸。
 *        highest_power - 输入的多项式的最高次幂。
 * return: --
 */
MtPolynomialFormula::MtPolynomialFormula(const double* x,
	const double* y, const unsigned int size,
	const unsigned int highest_power)
	:MtFormula(x, y, size, highest_power + 1)
	, _highest_power(highest_power)
	, _parameters(new DMat(_highest_power + 1, 1))
	, _correlation_coefficient(0.0)
	, _maximum_relative_deviation(0.0) {
}

/**
 * name: ~MtPolynomialFormula
 * brief: 析构函数.
 * param: --
 * return: --
 */
MtPolynomialFormula::~MtPolynomialFormula(void) {
	delete _parameters;
}

/**
 * name: calculate_x
 * breif: 根据给定的参数、y值计算x值。
 * param: parameters - 输入的指定参数。
 *        y - 输入的指定y值。
 *        target_x - 输入的指定x靶值。
 *        target_x_relative_position - 输入的指定x靶值的相对位置（<0 靶值小于待测值 ==0靶值等于待测值 >0 靶值大于待测值）。
 *        x - 输出的指定x值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPolynomialFormula::calculate_x(const DMat& parameters,
	const double y, double& x) {
	//1.声明当前操作所需变量。
	const unsigned int rows = parameters.get_rows();
	//2.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (rows <= 1) || (
		1 != parameters.get_cols())) {
		return(-1);
	}
	if (MtSolvingPolynomial::solve(parameters, y, x) < 0) {
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_y
 * breif: 根据给定的参数、x值计算y值。
 * param: parameters - 输入的指定参数。
 *        x - 输入的指定x值。
 *        y - 输出的指定y值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPolynomialFormula::calculate_y(
	const DMat& parameters, const double x, double& y) {
	//1.声明当前操作所需变量。
	const unsigned int rows = parameters.get_rows();
	//2.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (rows <= 1) || (
		1 != parameters.get_cols())) {
		return(-1);
	}
	//3.利用霍纳方法求解多项式。
	//3-1.声明当前操作所需变量。
	double result = parameters.get_element(0, 0) * x +
		parameters.get_element(1, 0);
	//3-2.利用霍纳方法求解多项式。
	for (unsigned int i = 2; i < rows; ++i) {
		result = result * x + parameters.get_element(i, 0);
	}
	//3-3.保存当前的计算结果。
	y = result;
	//4.程序运行到此直接成功返回。
	return(0);
}


/**
 * name: set_parameters
 * brief: 设置当前参数。
 * param: parameters - 指定参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPolynomialFormula::set_parameters(const DMat& parameters) {
	if (_parameters->copy(parameters) < 0) {
		return(-1);
	}
	else {
		return(0);
	}
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数矩阵引用。
 */
const MtPolynomialFormula::DMat&
MtPolynomialFormula::get_parameters() const {
	return(*_parameters);
}

/**
 * name: set_correlation_coefficient
 * breif: 设置相关系数。
 * param: correlation_coefficient - 指定的相关系数。
 * return: --
 */
void MtPolynomialFormula::set_correlation_coefficient(
	const double correlation_coefficient) {
	_correlation_coefficient = correlation_coefficient;
}

/**
 * name: get_correlation_coefficient
 * breif: 获取相关系数。
 * param: --
 * return: 返回当前公式的相关系数。
 */
double MtPolynomialFormula::get_correlation_coefficient() const {
	return(_correlation_coefficient);
}

/**
 * name: set_maximum_relative_deviation
 * brief: 设置最大相对偏差。
 * param: relative_deviation - 输入的最大相对偏差。
 * return: --
 */
void MtPolynomialFormula::set_maximum_relative_deviation(
	const double relative_deviation) {
	_maximum_relative_deviation = relative_deviation;
}

/**
 * name: get_maximum_relative_deviation
 * brief: 获取最大的相对偏差。
 * param: --
 * return: 返回最大的相对偏差。
 */
double MtPolynomialFormula::get_maximum_relative_deviation() const {
	return(_maximum_relative_deviation);
}

/**
 * name: calculate_coefficient_matrix
 * brief: 计算系数矩阵。
 * param: a - 输出生成的系数矩阵(ax=b中的a)。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于等于零。
 */
int MtPolynomialFormula::calculate_coefficient_matrix(DMat& a) const {
	//1.如果当前公式未能满足拟合条件，则直接返回错误。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.计算系数矩阵的行、列数。
	const unsigned int rows = get_size();
	const unsigned int cols = _highest_power + 1;
	//3.创建系数矩阵，并且判断创建是否成功。
	if (a.create(rows, cols) < 0) {
		return(-2);
	}
	//4.计算并为系数矩阵赋值。
	for (unsigned int row = 0; row != rows; ++row) {
		//4-1.声明当前操作所需变量。
		unsigned int exponent = _highest_power;
		//4-2.计算并为系数矩阵的当前行赋值。
		for (unsigned int col = 0; col != cols; ++col) {
			a.set_element(row, col, pow(get_x(row),
				static_cast<int>(exponent)));
			if (exponent > 0) {
				--exponent;
			}
		}
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: calculate_result_matrix
 * brief: 计算结果矩阵。
 * param: b - 输出生成的结果矩阵(ax=b中的b)。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于等于零。
 */
int MtPolynomialFormula::calculate_result_matrix(DMat& b) const {
	//1.如果当前公式未能满足拟合条件，则直接返回错误。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.计算系数矩阵的行、列数。
	const unsigned int rows = get_size();
	const unsigned int cols = 1;
	//3.创建结果矩阵，并且判断创建是否成功。
	if (b.create(rows, cols) < 0) {
		return(-2);
	}
	//4.计算并为结果矩阵赋值。
	for (unsigned int row = 0; row != rows; ++row) {
		for (unsigned int col = 0; col != cols; ++col) {
			b.set_element(row, col, get_y(row));
		}
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * breif: 根据指定的参数，计算当前公式的相关系数。
 * param: parameters - 输入的指定的参数。
 *        correlation_coefficient - 输出的相关系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPolynomialFormula::calculate_correlation_coefficient(
	const DMat& parameters, double& correlation_coefficient) const {
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || ((_highest_power + 1) !=
		parameters.get_rows()) || (1 != parameters.get_cols())) {
		return(-2);
	}
	//3.计算相关系数。
	double avg_y = get_average_y();
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	double ss_res = 0.0;
	double ss_tot = 0.0;
	for (unsigned int i = 0; i != size; ++i) {
		const double t_y = get_y(i);
		const double t_x = get_x(i);
		double c_y = 0.0;
		if (calculate_y(parameters, t_x, c_y) < 0) {
			return(-4);
		}
		ss_res += (t_y - c_y) * (t_y - c_y);
		ss_tot += (t_y - avg_y) * (t_y - avg_y);
	}
	if (fabs(ss_tot) < TINY) {
		return(-5);
	}
	correlation_coefficient = 1.0 - (ss_res / ss_tot);
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
int MtPolynomialFormula::calculate_maximum_relative_deviation(
	const DMat& parameters, double& relative_deviation) const {
	//1.如果当前公式尚未满足拟合条件，则函数直接返回错误。
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || ((_highest_power + 1) !=
		parameters.get_rows()) || (1 != parameters.get_cols())) {
		return(-2);
	}
	//3.计算最大的相对偏差，并且判断计算是否成功。
	//3-1.获取当前x、y的数量。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	//3-2.迭代计算最大的相对偏差。
	double maximum_relative_deviation = 0.0;
	unsigned int b_i = 0;
	if (size >= 6) {
		b_i = 1;
	}
	for (unsigned int i = b_i; i != size; ++i) {
		const double y = get_y(i);
		const double x = get_x(i);
		double c_x = 0.0;
		if (calculate_x(parameters, y, c_x) < 0) {
			return(-4);
		}
		const double temp = fabs((x - c_x) / x);
		if ((b_i == i) || (temp > maximum_relative_deviation)) {
			maximum_relative_deviation = temp;
		}
	}
	//3-3.保存当前最大的相对偏差。
	relative_deviation = maximum_relative_deviation;
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_can_fitted
 * breif: 判断当前公式是否可以被拟合。
 * param: --
 * return: 如果当前公式可被拟合返回TRUE，否则返回FALSE。
 */
bool MtPolynomialFormula::is_can_fitted() const {
	//1.调用基类相应函数，如果基类数据不运行拟合，则直接返回错误。
	if (!MtFormula::is_can_fitted()) {
		return false;
	}
	//2.检测当前多项式的最高次幂是否合法，如果不合法则直接返回错误（
	//  一般最多都是六点定标，所以认为多项式最高幂大于五就不能拟合）。
	if ((0 == _highest_power) || (_highest_power > 5)) {
		return false;
	}
	//3.检测当前输入的拟合数据个数是否达到多项式拟合所需。
	if ((_highest_power + 1) > get_size()) {
		return false;
	}
	//4.程序运行到此直接成功返回。
	return true;
}