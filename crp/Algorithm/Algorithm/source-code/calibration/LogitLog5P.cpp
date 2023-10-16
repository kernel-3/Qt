#include"LogitLog5P.h"
#include"../arithmetic/MtMatrix.h"
#include"../arithmetic/MtSolvingEquations.h"
#include<math.h>
#include<float.h>

const double LogitLog5P::TINY(1.0E-20);

/**
 * name: LogitLog4P
 * breif: 构造函数。
 * param: x - 指向x待拟合数据。
 *        y - 指向y待拟合数据。
 *        size - 待拟合数据个数。
 * return: --
 */
LogitLog5P::LogitLog5P(const double* x,
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
LogitLog5P::~LogitLog5P(void) {
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
int LogitLog5P::calculate_x(const DMat& parameters, const double y, double& x) {
	//1.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-1);
	}
	//2.从矩阵中获取计算所需参数。
	const double D = parameters.get_element(0, 0);
	const double A = parameters.get_element(1, 0);
	const double C = parameters.get_element(2, 0);
	const double B = parameters.get_element(3, 0);
	const double E = parameters.get_element(4, 0);
	//3.根据参数以及发光值计算浓度。
	if (fabs(B) < TINY) {
		return(-2);
	}
	const double temp1 = 1.0 / B;
	if (_isnan(temp1)) {
		return(-3);
	}
	if (fabs(y - D) < TINY) {
		return(-4);
	}
	const double temp2 = (A - y) / (y - D);
	if (_isnan(temp2) || (fabs(temp2) < TINY) || (temp2 < 0.0)) {
		return(-5);
	}
	const double temp3 = exp(temp1 * log(temp2));
	if (_isnan(temp3)) {
		return(-6);
	}
	x = C * temp3 + E;
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
int LogitLog5P::calculate_y(const DMat& parameters, const double x, double& y) {
	//1.如果当前传递的参数不合法，则直接返回错误。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-1);
	}

	//2.从矩阵中获取计算所需参数。
	const double D = parameters.get_element(0, 0);
	const double A = parameters.get_element(1, 0);
	const double C = parameters.get_element(2, 0);
	const double B = parameters.get_element(3, 0);
	double E = parameters.get_element(4, 0);
	//3.根据参数以及发光值计算浓度。
	if (fabs(C) < TINY) {
		return(-2);
	}
	const double temp1 = (x - E) / C;

	if (_isnan(temp1) || temp1 < TINY)
		return -6;

	const double temp2 = exp(B * log(temp1));
	if (_isnan(temp2)) {
		return(-4);
	}
	const double temp3 = 1.0 + temp2;
	if (fabs(temp3) < TINY) {
		return(-5);
	}
	y = ((A - D) / temp3) + D;
	//4.程序运行到此，直接返回。
	return(0);
}

/**
 * name: get_parameters
 * brief: 获取当前参数。
 * param: --
 * return: 返回当前参数矩阵引用。
 */
const LogitLog5P::DMat& LogitLog5P::get_parameters() const {
	return(*_parameters);
}

/**
 * name: set_parameters
 * brief: 设置当前参数。
 * param: parameters - 指定参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog5P::set_parameters(const DMat& parameters) {
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
int LogitLog5P::calculate_initialized_parameters(DMat& parameters) {
	//1.如果基类相应的虚函数调用失败，则直接返回错误。
	if (MtLMFormula::calculate_initialized_parameters(parameters) < 0) {
		return(-1);
	}
	//2.记录当前公式中A与D。
	//2-1.计算当前公式中D。
	const double D = calculate_initialized_A0();
	//2-2.计算当前公式中A的初值。
	const double A = calculate_initialized_A1();
	const double E = calculate_initialized_E();

	//3.根据公式，建立方程组的系数矩阵以及结果矩阵。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-2);
	}
	DMat c(size, 2);//系数矩阵。
	DMat b(size, 1);//结果矩阵。
	for (unsigned int i = 0; i != size; ++i) {
		double y = get_y(i);
		if (fabs(y - D) < TINY) {
			return(-3);
		}
		const double temp1 = (A - y) / (y - D);
		if ((fabs(temp1) < TINY) || (temp1 < 0.0)) {
			return(-4);
		}
		const double temp2 = log(temp1);
		if (_isnan(temp2)) {
			return(-5);
		}
		b.set_element(i, 0, temp2);
		const double x = get_x(i);
		const double temp3 = log(x - E);
		if (_isnan(temp3) || isinf(temp3)) {
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
	//3-4.求解B以及C的初值。
	if (fabs(b.get_element(0, 0)) < TINY) {
		return(-12);
	}
	const double B = b.get_element(0, 0);
	if (_isnan(B)) {
		return(-13);
	}
	const double C = exp(b.get_element(1, 0) /
		b.get_element(0, 0));
	if (_isnan(C)) {
		return(-14);
	}
	//4.保存当前计算的参数。
	if (parameters.create(PARAMETER_COUNT, 1) < 0) {
		return(-15);
	}
	parameters.set_element(0, 0, D);
	parameters.set_element(1, 0, A);
	parameters.set_element(2, 0, C);
	parameters.set_element(3, 0, B);
	parameters.set_element(4, 0, E);

	//parameters.set_element(0, 0, 16.926);
	//parameters.set_element(1, 0, 3.009);
	//parameters.set_element(2, 0, 7.424);
	//parameters.set_element(3, 0, 2.402);
	//parameters.set_element(4, 0, 0.);

	//5.程序运行到此直接成功返回。
	return 0;
}

/**
 * name: calculate_jacobian_matrix
 * brief: 计算当前公式中，指定参数的雅可比矩阵。
 * param: parameters - 指定的参数矩阵。
 *        jacobian - 返回的雅可比矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LogitLog5P::calculate_jacobian_matrix(const DMat& parameters, DMat& jacobian) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_jacobian_matrix(parameters, jacobian) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) ||
		(1 != parameters.get_cols())) {
		return(-2);
	}
	//3.为准备计算的雅可比矩阵分配内存空间，并且判断分配是否成功。
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	if (jacobian.create(size, PARAMETER_COUNT) < 0) {
		return(-4);
	}
	//4.获取计算偏导数所需的参数信息。
	const double D = parameters.get_element(0, 0);
	const double A = parameters.get_element(1, 0);
	const double C = parameters.get_element(2, 0);
	const double B = parameters.get_element(3, 0);
	const double E = parameters.get_element(4, 0);
	//5.为分配的雅可比矩阵赋值。
	for (unsigned int i = 0; i != size; ++i) {

		if (fabs(C) < TINY) {
			return(-7);
		}

		double x = get_x(i);
		double temp1 = (x - E) / C;
		if ((_isnan(temp1)) || temp1 < 0.0) {
			return(-6);
		}
		//((x-E)/C)^B
		double temp2 = log(temp1);
		double temp3 = exp(B * temp2);
		//1 /(1+((x-E)/C)^B)^2
		double temp4 = 1. / exp(2. * log(1. + temp3));
		double temp5 = B / C;
		double temp6 = exp((B - 1.) * temp2);
		double temp7 = (A - D) * temp4;

		//5-5.计算公式针对D的偏导数。
		jacobian.set_element(i, 0, 1. - 1. / (1. + temp3));//计算D的偏导数。
		if (_isnan(jacobian.get_element(i, 0))) {
			return(-11);
		}

		jacobian.set_element(i, 1, 1. / (1. + temp3));//计算A的偏导数。
		if (_isnan(jacobian.get_element(i, 1))) {
			return(-13);
		}
		//5-7.计算公式针对C的偏导数。
		jacobian.set_element(i, 2, temp7 * temp5 * temp3);//计算C的偏导数。
		if (_isnan(jacobian.get_element(i, 2))) {
			return(-13);
		}

		jacobian.set_element(i, 3, -1.0 * temp7 * temp3 * temp2);//计算B的偏导数。
		if (_isnan(jacobian.get_element(i, 3))) {
			return(-15);
		}

		jacobian.set_element(i, 4, temp7 * temp5 * temp6);//计算E的偏导数。
		if (_isnan(jacobian.get_element(i, 4))) {
			return(-13);
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
int LogitLog5P::calculate_difference_matrix(const DMat& parameters, DMat& difference) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_difference_matrix(parameters, difference) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) || (
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
		double c_y = 0.0;
		if (calculate_y(parameters, x, c_y) < 0) {
			return(-5);
		}
		//4-4.设置差值矩阵的元素。
		difference.set_element(i, 0, y - c_y);
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
int LogitLog5P::calculate_sum_of_squares_of_deviations(/*const*/ DMat& parameters, double& sum) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_sum_of_squares_of_deviations(
		parameters, sum) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) || (
		1 != parameters.get_cols())) {
		return(-2);
	}
	//3.如果当前A0、A1超过设定的合理理论值，则将其恢复为初始值。
	/*double& D = parameters.get_element(0, 0);
	double& A = parameters.get_element(1, 0);
	const double min_y = get_minimum_y();
	const double max_y = get_maximum_y();
	if (D > min_y) {
		D = calculate_initialized_A0();
	}
	if (A < max_y) {
		A = calculate_initialized_A1();
	}*/
	//4.计算当前公式指定参数情况下的差方和。
	double sum_t = 0.0;
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}

	for (unsigned int i = 0; i != size; ++i) {
		const double y = get_y(i);
		double x = get_x(i);
		double c_y = 0.0;
		int ret = calculate_y(parameters, x, c_y);		//if(fabs(x-0.001)<=TINY){
		if (ret == -6)
			parameters.set_element(4, 0, calculate_initialized_E());
		ret = calculate_y(parameters, x, c_y);
		if (ret < 0)
			return -4;
		sum_t += (y - c_y) * (y - c_y);
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
int LogitLog5P::calculate_maximum_relative_deviation(
	const DMat& parameters, double& relative_deviation) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_maximum_relative_deviation(
		parameters, relative_deviation) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) ||
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

	for (unsigned int i = b_i; i != size; ++i) {
		const double y = get_y(i);
		const double x = get_x(i);
		double c_y = 0.0;
		if (calculate_y(parameters, x, c_y) < 0) {
			return(-4);
		}
		const double temp = fabs((y - c_y) / y);
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
int LogitLog5P::calculate_correlation_coefficient(
	const DMat& parameters, double& correlation_coefficient) const {
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if (MtLMFormula::calculate_correlation_coefficient(parameters,
		correlation_coefficient) < 0) {
		return(-1);
	}
	//2.判断当前传递参数是否合法。
	if ((!parameters.is_valid()) || (PARAMETER_COUNT != parameters.get_rows()) ||
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
double LogitLog5P::calculate_initialized_A0() const {
	double A0 = get_minimum_y();
	double t = fabs(A0) * 0.001;
	if (fabs(t) < TINY)
		t = 0.001;

	A0 -= t;
	return(A0);
}

/**
 * name: calculate_initialized_A1
 * breif: 计算初始的A1值。
 * param: --
 * return: 返回计算初始的A1值。
 */
double LogitLog5P::calculate_initialized_A1() const {
	double A1 = get_maximum_y();
	double t = fabs(A1) * 0.001;
	if (fabs(t) < TINY)
		t = 0.001;
	A1 += t;
	return(A1);
}

double LogitLog5P::calculate_initialized_E() const
{
	double E = get_minimum_x();
	if (fabs(E) < 1e-7)
		return 0.;

	return E - fabs(E) * 0.01;
}
