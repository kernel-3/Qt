#include"stdafx.h"
#include"MtPolynomialFormula.h"
#include"MtMatrix.h"
#include"MtSolvingPolynomial.h"
#include<math.h>

const double MtPolynomialFormula::TINY = 1.0E-20;

/**
 * name: MtPolynomialFormula
 * brief: ���캯��.
 * param: x - �����ָ������x�����ָ�롣
 *        y - �����ָ������y�����ָ�롣
 *        size - ����Ĵ����x��y����ĳߴ硣
 *        highest_power - ����Ķ���ʽ����ߴ��ݡ�
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
 * brief: ��������.
 * param: --
 * return: --
 */
MtPolynomialFormula::~MtPolynomialFormula(void) {
	delete _parameters;
}

/**
 * name: calculate_x
 * breif: ���ݸ����Ĳ�����yֵ����xֵ��
 * param: parameters - �����ָ��������
 *        y - �����ָ��yֵ��
 *        target_x - �����ָ��x��ֵ��
 *        target_x_relative_position - �����ָ��x��ֵ�����λ�ã�<0 ��ֵС�ڴ���ֵ ==0��ֵ���ڴ���ֵ >0 ��ֵ���ڴ���ֵ����
 *        x - �����ָ��xֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPolynomialFormula::calculate_x(const DMat& parameters,
	const double y, double& x) {
	//1.������ǰ�������������
	const unsigned int rows = parameters.get_rows();
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if ((!parameters.is_valid()) || (rows <= 1) || (
		1 != parameters.get_cols())) {
		return(-1);
	}
	if (MtSolvingPolynomial::solve(parameters, y, x) < 0) {
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_y
 * breif: ���ݸ����Ĳ�����xֵ����yֵ��
 * param: parameters - �����ָ��������
 *        x - �����ָ��xֵ��
 *        y - �����ָ��yֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPolynomialFormula::calculate_y(
	const DMat& parameters, const double x, double& y) {
	//1.������ǰ�������������
	const unsigned int rows = parameters.get_rows();
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if ((!parameters.is_valid()) || (rows <= 1) || (
		1 != parameters.get_cols())) {
		return(-1);
	}
	//3.���û��ɷ���������ʽ��
	//3-1.������ǰ�������������
	double result = parameters.get_element(0, 0) * x +
		parameters.get_element(1, 0);
	//3-2.���û��ɷ���������ʽ��
	for (unsigned int i = 2; i < rows; ++i) {
		result = result * x + parameters.get_element(i, 0);
	}
	//3-3.���浱ǰ�ļ�������
	y = result;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}


/**
 * name: set_parameters
 * brief: ���õ�ǰ������
 * param: parameters - ָ��������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
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
 * brief: ��ȡ��ǰ������
 * param: --
 * return: ���ص�ǰ�����������á�
 */
const MtPolynomialFormula::DMat&
MtPolynomialFormula::get_parameters() const {
	return(*_parameters);
}

/**
 * name: set_correlation_coefficient
 * breif: �������ϵ����
 * param: correlation_coefficient - ָ�������ϵ����
 * return: --
 */
void MtPolynomialFormula::set_correlation_coefficient(
	const double correlation_coefficient) {
	_correlation_coefficient = correlation_coefficient;
}

/**
 * name: get_correlation_coefficient
 * breif: ��ȡ���ϵ����
 * param: --
 * return: ���ص�ǰ��ʽ�����ϵ����
 */
double MtPolynomialFormula::get_correlation_coefficient() const {
	return(_correlation_coefficient);
}

/**
 * name: set_maximum_relative_deviation
 * brief: ����������ƫ�
 * param: relative_deviation - �����������ƫ�
 * return: --
 */
void MtPolynomialFormula::set_maximum_relative_deviation(
	const double relative_deviation) {
	_maximum_relative_deviation = relative_deviation;
}

/**
 * name: get_maximum_relative_deviation
 * brief: ��ȡ�������ƫ�
 * param: --
 * return: �����������ƫ�
 */
double MtPolynomialFormula::get_maximum_relative_deviation() const {
	return(_maximum_relative_deviation);
}

/**
 * name: calculate_coefficient_matrix
 * brief: ����ϵ������
 * param: a - ������ɵ�ϵ������(ax=b�е�a)��
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС�ڵ����㡣
 */
int MtPolynomialFormula::calculate_coefficient_matrix(DMat& a) const {
	//1.�����ǰ��ʽδ�����������������ֱ�ӷ��ش���
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.����ϵ��������С�������
	const unsigned int rows = get_size();
	const unsigned int cols = _highest_power + 1;
	//3.����ϵ�����󣬲����жϴ����Ƿ�ɹ���
	if (a.create(rows, cols) < 0) {
		return(-2);
	}
	//4.���㲢Ϊϵ������ֵ��
	for (unsigned int row = 0; row != rows; ++row) {
		//4-1.������ǰ�������������
		unsigned int exponent = _highest_power;
		//4-2.���㲢Ϊϵ������ĵ�ǰ�и�ֵ��
		for (unsigned int col = 0; col != cols; ++col) {
			a.set_element(row, col, pow(get_x(row),
				static_cast<int>(exponent)));
			if (exponent > 0) {
				--exponent;
			}
		}
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: calculate_result_matrix
 * brief: ����������
 * param: b - ������ɵĽ������(ax=b�е�b)��
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС�ڵ����㡣
 */
int MtPolynomialFormula::calculate_result_matrix(DMat& b) const {
	//1.�����ǰ��ʽδ�����������������ֱ�ӷ��ش���
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.����ϵ��������С�������
	const unsigned int rows = get_size();
	const unsigned int cols = 1;
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	if (b.create(rows, cols) < 0) {
		return(-2);
	}
	//4.���㲢Ϊ�������ֵ��
	for (unsigned int row = 0; row != rows; ++row) {
		for (unsigned int col = 0; col != cols; ++col) {
			b.set_element(row, col, get_y(row));
		}
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * breif: ����ָ���Ĳ��������㵱ǰ��ʽ�����ϵ����
 * param: parameters - �����ָ���Ĳ�����
 *        correlation_coefficient - ��������ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPolynomialFormula::calculate_correlation_coefficient(
	const DMat& parameters, double& correlation_coefficient) const {
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if ((!parameters.is_valid()) || ((_highest_power + 1) !=
		parameters.get_rows()) || (1 != parameters.get_cols())) {
		return(-2);
	}
	//3.�������ϵ����
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
int MtPolynomialFormula::calculate_maximum_relative_deviation(
	const DMat& parameters, double& relative_deviation) const {
	//1.�����ǰ��ʽ��δ�����������������ֱ�ӷ��ش���
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if ((!parameters.is_valid()) || ((_highest_power + 1) !=
		parameters.get_rows()) || (1 != parameters.get_cols())) {
		return(-2);
	}
	//3.�����������ƫ������жϼ����Ƿ�ɹ���
	//3-1.��ȡ��ǰx��y��������
	const unsigned int size = get_size();
	if (0 == size) {
		return(-3);
	}
	//3-2.���������������ƫ�
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
	//3-3.���浱ǰ�������ƫ�
	relative_deviation = maximum_relative_deviation;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_can_fitted
 * breif: �жϵ�ǰ��ʽ�Ƿ���Ա���ϡ�
 * param: --
 * return: �����ǰ��ʽ�ɱ���Ϸ���TRUE�����򷵻�FALSE��
 */
bool MtPolynomialFormula::is_can_fitted() const {
	//1.���û�����Ӧ����������������ݲ�������ϣ���ֱ�ӷ��ش���
	if (!MtFormula::is_can_fitted()) {
		return false;
	}
	//2.��⵱ǰ����ʽ����ߴ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	//  һ����඼�����㶨�꣬������Ϊ����ʽ����ݴ�����Ͳ�����ϣ���
	if ((0 == _highest_power) || (_highest_power > 5)) {
		return false;
	}
	//3.��⵱ǰ�����������ݸ����Ƿ�ﵽ����ʽ������衣
	if ((_highest_power + 1) > get_size()) {
		return false;
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return true;
}