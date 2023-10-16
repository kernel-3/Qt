#include"stdafx.h"
#include"MtLMFormula.h"
#include"MtMatrix.h"
#include<cmath>

/**
 * name: MtLMFormula
 * breif: ���캯����
 * param: x - ָ�����ϵ�x���顣
 *        y - ָ�����ϵ�y���顣
 *        size - �����x��y����ߴ硣
 *        min_size - �����x��y������С�ߴ硣
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
 * brief: ����������
 * param: --
 * return: --
 */
MtLMFormula::~MtLMFormula(void) {
	delete _weight;
}

/**
 * name: set_maximum_relative_deviation
 * brief: ���õ�ǰ��ʽ��������ƫ�
 * param: maximum_relative_deviation - ������ƫ�
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
 * brief: ��ȡ��ǰ��ʽ��������ƫ�
 * param: --
 * return: ���ص�ǰ��ʽ��������ƫ�
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
 * breif: ���õ�ǰ��ʽ�����ϵ����
 * param: correlation_coefficient - ���ϵ����
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
 * breif: ��ȡ��ǰ��ʽ�����ϵ����
 * param: --
 * return: ���ص�ǰ��ʽ�����ϵ����
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
 * breif: ��ȡ��ǰ��ʽ��ϵ������
 * param: --
 * return: ���ص�ǰ��ʽ��ϵ������
 */
const MtLMFormula::DMat& MtLMFormula::get_weight_matrix() const {
	return(*_weight);
}

/**
 * name: set_parameters
 * brief: ���õ�ǰ��ʽ������
 * param: parameters - ָ���ĵ�ǰ��ʽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::set_parameters(const DMat&/*parameters*/) {
	return(0);
}

/**
 * name: calculate_initialized_parameters
 * brief: ���㵱ǰ��ʽ�ĳ�ʼ������
 * param: parameters - ���صĲ�����
 * return: ������㹫ʽ�ĳ�ʼ�����ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_initialized_parameters(DMat&/*parameters*/) {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�����ǰ��ʽ�������������
	else {
		return(0);
	}
}

/**
 * name: calculate_jacobian_matrix
 * brief: ���㵱ǰ��ʽ��ָ���������ſɱȾ���
 * param: parameters - ָ���Ĺ�ʽ������
 *        jacobian - ���ص��ſɱȾ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_jacobian_matrix(
	const DMat&/*parameters*/, DMat&/*jacobian*/) const {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_difference_matrix
 * brief: ���㵱ǰ��ʽ��ָ�������Ĳ�ֵ����
 * param: parameters - ָ���Ĳ�����
 *        difference - ��ֵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_difference_matrix(
	const DMat&/*parameters*/, DMat&/*difference*/) const {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_sum_of_squares_of_deviations
 * brief: ���㵱ǰ��ʽ��ָ�������Ĳ�͡�
 * param: parameters - ָ���Ĳ�����
 *        sum - ���صĲ�͡�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_sum_of_squares_of_deviations(
	/*const*/ DMat&/*parameters*/, double&/*sum*/) const {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_maximum_relative_deviation
 * breif: ���㵱ǰ��ʽ�У�ָ�����������������ƫ�
 * param: parameters - ָ���Ĳ�����
 *        relative_deviation - ���ƫ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_maximum_relative_deviation(
	const DMat& /*parameters*/, double& /*relative_deviation*/) const {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_correlation_coefficient
 * brief: ���㵱ǰ��ʽ�£�ָ��������������ϵ����
 * param: parameters - ָ���Ĳ�����
 *        correlation_coefficient - ���ص����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFormula::calculate_correlation_coefficient(
	const DMat&/*parameters*/, double&/*correlation_coefficient*/) const {
	//1.�����ǰ��ʽ���������������
	if (!is_can_fitted()) {
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}