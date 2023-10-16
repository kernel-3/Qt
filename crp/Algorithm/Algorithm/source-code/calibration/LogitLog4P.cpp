#include"LogitLog4P.h"
#include"../arithmetic/MtMatrix.h"
#include"../arithmetic/MtSolvingEquations.h"
#include<math.h>
#include<float.h>

const double LogitLog4P::TINY(1.0E-20);

/**
 * name: LogitLog4P
 * breif: 构造函数。
 * param: x - 指向x待拟合数据。
 *        y - 指向y待拟合数据。
 *        size - 待拟合数据个数。
 * return: --
 */
LogitLog4P::LogitLog4P(const double* x,
	const double* y, const unsigned int size)
	:MtLMFormula(x, y, size, PARAMETER_COUNT)
	, _parameters(new DMat(PARAMETER_COUNT, 1)) {
}

/**
 * name: ~LogitLog4P
 * brief: 析构函数。
 * param: --
 * return: --
 */
LogitLog4P::~LogitLog4P(void) {
	delete _parameters;
}

/**
 * name: calculate_x
 * brief: 根据指定的参数以及给定的y计算x。
 * param: parameters - 指定参数。
 *        y - 指定的y。
 *        x - 返回的x。
 * return: 如果函数值执行成功返回值大于等于零，否则返回至小于零。
 */
int LogitLog4P::calculate_x(const DMat& parameters, const double y, double& x) {
	//1.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-1);
	}
	//2.从矩阵中获取计算所需参数。
	const double A0 = parameters.get_element(0, 0);
	const double A1 = parameters.get_element(1, 0);
	const double x0 = parameters.get_element(2, 0);
	const double p = parameters.get_element(3, 0);
	//3.根据参数以及发光值计算浓度。
	if (fabs(p) < TINY) {
		return(-2);
	}
	const double temp1 = 1.0 / p;
	if (_isnan(temp1)) {
		return(-3);
	}
	if (fabs(y - A0) < TINY) {
		return(-4);
	}
	const double temp2 = (A1 - y) / (y - A0);
	if (_isnan(temp2) || (fabs(temp2) < TINY) || (temp2 < 0.0)) {
		return(-5);
	}
	const double temp3 = pow(temp2, temp1);
	if (_isnan(temp3)) {
		return(-6);
	}
	x = x0 * temp3;
	//4.程序运行到此，直接返回。
	return(0);
}

/**
 * name: calculate_y
 * brief: 根据指定的参数以及给定的x计算y。
 * param: parameters - 指定参数。
 *        x - 指定的x。
 *        y - 返回的y。
 * return: 如果函数值执行成功返回值大于等于零，否则返回至小于零。
 */
int LogitLog4P::calculate_y(const DMat& parameters, const double x, double& y) {
	//1.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-1);
	}
	//2.从矩阵中获取计算所需参数。
	const double A0 = parameters.get_element(0, 0);
	const double A1 = parameters.get_element(1, 0);
	const double x0 = parameters.get_element(2, 0);
	const double p = parameters.get_element(3, 0);
	//3.根据参数以及发光值计算浓度。
	if (fabs(x0) < TINY) {
		return(-2);
	}
	const double temp1 = x / x0;
	if (_isnan(temp1) || (fabs(temp1) < TINY) || (temp1 < 0.0)) {
		return(-3);
	}
	const double temp2 = exp(p * log(temp1));
	if (_isnan(temp2)) {
		return(-4);
	}
	const double temp3 = 1.0 + temp2;
	if (fabs(temp3) < TINY) {
		return(-5);
	}
	y = ((A1 - A0) / temp3) + A0;
	//4.程序运行到此，直接返回。
	return(0);
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数矩阵引用。
 */
const LogitLog4P::DMat& LogitLog4P::get_parameters() const {
	return(*_parameters);
}

/**
 * name: set_parameters
 * brief: 设置当前参数。
 * param: parameters - 指定参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::set_parameters(const DMat& parameters) {
	if (_parameters->copy(parameters) < 0) {
		return(-1);
	}
	else {
		return(0);
	}
}

/**
 * name: calculate_initialized_parameters
 * brief: 计算当前公式的初始参数。
 * param: parameters - 返回的初始参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_initialized_parameters(DMat& parameters) {
	//1.如果基类相应的虚函数调用失败，则直接返回错误。
	if (MtLMFormula::calculate_initialized_parameters(parameters) < 0) {
		return(-1);
	}
	//2.记录当前公式中A1与A0的初值。
	//2-1.计算当前公式中A0的初值。
	const double A0 = calculate_initialized_A0();
	//2-2.计算当前公式中A1的初值。
	const double A1 = calculate_initialized_A1();
	//3.根据公式y=(A1-A0)/(1+(x/x0)^p)+A0的变形
	//  ln((A1-y)/(y-A0))=pln(x)-pln(x0)求解p以及x0的初值。
	//3-1.根据上述公式，建立方程组的系数矩阵以及结果矩阵。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-2);
	}
	DMat c(size, 2);//系数矩阵。
	DMat b(size, 1);//结果矩阵。
	for (unsigned int i = 0; i != size; ++i) {
		double y = get_y(i);
		if (fabs(y - A0) < TINY) {
			return(-3);
		}
		const double temp1 = (A1 - y) / (y - A0);
		if ((fabs(temp1) < TINY) || (temp1 < 0.0)) {
			return(-4);
		}
		const double temp2 = log(temp1);
		if (_isnan(temp2)) {
			return(-5);
		}
		b.set_element(i, 0, temp2);
		const double x = get_x(i);
		if ((x < 0.0) || (fabs(x) < TINY)) {
			return(-6);
		}
		const double temp3 = log(x);
		if (_isnan(temp3)) {
			return(-7);
		}
		c.set_element(i, 0, temp3);
		c.set_element(i, 1, -1.0);
	}
	//3-2.方程两边同时左乘系数矩阵的转置矩阵（实现最小二乘法求解方程组）。
	DMat c_t;
	if (c.transpose(c_t) < 0) {
		return(-8);
	}
	if (c.copy(c_t.multiply(c)) < 0) {
		return(-9);
	}
	if (b.copy(c_t.multiply(b)) < 0) {
		return(-10);
	}
	//3-3.求解线性方程组。
	if (MtSolvingEquations::solve(c, b) < 0) {
		return(-11);
	}
	//3-4.求解p以及x0的初值。
	if (fabs(b.get_element(0, 0)) < TINY) {
		return(-12);
	}
	const double p = b.get_element(0, 0);
	if (_isnan(p)) {
		return(-13);
	}
	const double x0 = exp(b.get_element(1, 0) /
		b.get_element(0, 0));
	if (_isnan(x0)) {
		return(-14);
	}
	//4.保存当前计算的参数。
	if (parameters.create(4, 1) < 0) {
		return(-15);
	}
	parameters.set_element(0, 0, A0);
	parameters.set_element(1, 0, A1);
	parameters.set_element(2, 0, x0);
	parameters.set_element(3, 0, p);
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: calculate_jacobian_matrix
 * brief: 计算当前公式中，指定参数的雅可比矩阵。
 * param: parameters - 指定的参数矩阵。
 *        jacobian - 返回的雅可比矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_jacobian_matrix(const DMat& parameters, DMat& jacobian) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_jacobian_matrix(parameters, jacobian) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-2);
	}
	//3.为准备计算的雅可比矩阵分配内存空间，并且判断分配是否成功。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	if (jacobian.create(size, 4) < 0) {
		return(-4);
	}
	//4.获取计算偏导数所需的参数信息。
	const double A0 = parameters.get_element(0, 0);
	const double A1 = parameters.get_element(1, 0);
	const double x0 = parameters.get_element(2, 0);
	const double p = parameters.get_element(3, 0);
	//5.为分配的雅可比矩阵赋值。
	for (unsigned int i = 0; i != size; ++i) {
		//5-1.计算(A1-y)/(y-A0)的值。
		double y = get_y(i);
		if (fabs(y - A0) < TINY) {
			return(-5);
		}
		double temp1 = (A1 - y) / (y - A0);
		if ((_isnan(temp1)) || (fabs(temp1) < TINY) || (temp1 < 0.0)) {
			return(-6);
		}
		//5-2.计算1/p的值。
		if (fabs(p) < TINY) {
			return(-7);
		}
		double temp2 = 1.0 / p;
		if (_isnan(temp2)) {
			return(-8);
		}
		//5-3.计算((A1-y)/(y-A0))^(1/p)的值。
		double temp3 = exp(temp2 * log(temp1));
		if (_isnan(temp3)) {
			return(-9);
		}
		//5-4.计算x0/p的值。
		double temp4 = x0 / p;
		if (_isnan(temp4)) {
			return(-10);
		}
		//5-5.计算公式针对A0的偏导数。
		jacobian.set_element(i, 0, temp4 * temp3 / (y - A0));//计算A0的偏导数。
		if (_isnan(jacobian.get_element(i, 0))) {
			return(-11);
		}
		//5-6.计算公式针对A1的偏导数。
		if (fabs(A1 - y) < TINY) {
			return(-12);
		}
		jacobian.set_element(i, 1, temp4 * temp3 / (A1 - y));//计算A1的偏导数。
		if (_isnan(jacobian.get_element(i, 1))) {
			return(-13);
		}
		//5-7.计算公式针对x0的偏导数。
		jacobian.set_element(i, 2, temp3);//计算x0的偏导数。
		//5-8.计算x0/p^2的值。
		double temp5 = x0 / (p * p);
		if (_isnan(temp5)) {
			return(-14);
		}
		//5-9.计算公式针对p的偏导数。
		jacobian.set_element(i, 3, (-1.0) * temp5 *
			temp3 * log(temp1));//计算p的偏导数。
		if (_isnan(jacobian.get_element(i, 3))) {
			return(-15);
		}
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_difference_matrix
 * brief: 计算当前公式下指定参数的差值矩阵。
 * param: parameters - 指定的参数矩阵。
 *        difference - 返回取得的差值矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_difference_matrix(const DMat& parameters, DMat& difference) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_difference_matrix(parameters, difference) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) || (
		1 != parameters.get_cols())) {
		return(-2);
	}
	//3.创建差值矩阵，并且判断创建是否成功。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	if (difference.create(size, 1) < 0) {
		return(-4);
	}
	//4.计算并为差值矩阵赋值。
	for (unsigned int i = 0; i != size; ++i) {
		//4-1.获取当前的y值，并且判断获取是否成功。
		const double y = get_y(i);
		//4-2.获取当前的x值，并且判断获取是否成功。
		double x = get_x(i);
		//4-3.利用当前的y值，计算出x，并且判断计算是否成功。
		double c_x = 0.0;
		if (calculate_x(parameters, y, c_x) < 0) {
			return(-5);
		}
		//4-4.设置差值矩阵的元素。
		difference.set_element(i, 0, x - c_x);
	}
	//5.程序运行到此直接返回。
	return(0);
}

/**
 * name: calculate_sum_of_squares_of_deviations
 * brief: 计算当前公式下指定参数情况的差方和。
 * param: parameters - 指定的参数。
 *        sum - 返回的差方和。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_sum_of_squares_of_deviations(/*const*/ DMat& parameters, double& sum) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_sum_of_squares_of_deviations(
		parameters, sum) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) || (
		1 != parameters.get_cols())) {
		return(-2);
	}
	//3.如果当前A0、A1超过设定的合理理论值，则将其恢复为初始值。
	double& A0 = parameters.get_element(0, 0);
	double& A1 = parameters.get_element(1, 0);
	const double min_y = get_minimum_y();
	const double max_y = get_maximum_y();
	if (A0 > min_y) {
		A0 = calculate_initialized_A0();
	}
	if (A1 < max_y) {
		A1 = calculate_initialized_A1();
	}
	//4.计算当前公式指定参数情况下的差方和。
	double sum_t = 0.0;
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}

	for (unsigned int i = 0; i != size; ++i) {
		const double y = get_y(i);
		double x = get_x(i);
		double c_x = 0.0;
		if (calculate_x(parameters, y, c_x) < 0) {
			return(-4);
		}
		//if(fabs(x-0.001)<=TINY){
		sum_t += (x - c_x) * (x - c_x);
		//}else{
		//	sum_t+=((x-c_x)/x)*((x-c_x)/x);
		//}
	}
	//5.保存当前的差方和。
	sum = sum_t;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_maximum_relative_deviation
 * brief: 计算当前公式中，指定参数下，计算的最大相对偏差。
 * param: parameters - 指定的参数。
 *        relative_deviation - 返回的最大相对偏差值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_maximum_relative_deviation(
	const DMat& parameters, double& relative_deviation) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_maximum_relative_deviation(
		parameters, relative_deviation) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
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
 * name: calculate_correlation_coefficient
 * brief: 计算当前公式下，指定参数计算的相关系数。
 * param: parameters - 指定的参数。
 *        correlation_coefficient - 返回的相关系数。
 *        relative_deviation - 返回的相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog4P::calculate_correlation_coefficient(
	const DMat& parameters, double& correlation_coefficient) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_correlation_coefficient(parameters,
		correlation_coefficient) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (4 != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-2);
	}
	//3.计算相关系数。
	double s0 = 0.0;
	double s1 = 0.0;
	const double avg_y = get_average_y();
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	for (unsigned int i = 0; i != size; ++i) {
		const double y = get_y(i);
		double x = get_x(i);
		double c_y = 0.0;
		if (calculate_y(parameters, x, c_y) < 0) {
			return(-4);
		}
		s0 += (y - c_y) * (y - c_y);
		s1 += (y - avg_y) * (y - avg_y);
	}
	if (fabs(s1) < TINY) {
		return(-5);
	}
	const double temp = 1.0 - (s0 / s1);
	correlation_coefficient = temp;
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_initialized_A0
 * breif: 计算初始的A0值。
 * param: --
 * return: 返回计算初始的A0值。
 */
double LogitLog4P::calculate_initialized_A0() const {
	double A0 = get_minimum_y();
	double t = fabs(A0) * 0.001;
	if (fabs(t) < TINY)
		t = 0.001;
	if (A0 > 1)
		A0 -= 1;
	else
		A0 -= t;
	return(A0);
}

/**
 * name: calculate_initialized_A1
 * breif: 计算初始的A1值。
 * param: --
 * return: 返回计算初始的A1值。
 */
double LogitLog4P::calculate_initialized_A1() const {
	double A1 = get_maximum_y();
	double t = fabs(A1) * 0.001;
	if (A1 > 1)
		A1 += 1;
	else
		A1 += t;
	return(A1);
}
