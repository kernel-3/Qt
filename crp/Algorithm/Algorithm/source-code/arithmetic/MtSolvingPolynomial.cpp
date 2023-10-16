#include"stdafx.h"
#include"MtSolvingPolynomial.h"
#include"MtMatrix.h"
#include<complex>
#include<cmath>

//�������о�̬������
const double MtSolvingPolynomial::TINY = 1.0E-20;

/**
 * name: solve
 * brief: ������ʽ��
 * param: coefficient - ����Ķ���ʽϵ������(n*1ά����)��
 *        target_value - ����İ�ֵ�����ߴζ���ʽʱ��Ҫ��ֵ������ȷ����һ��������������
 *        target_value_relative_position - �����ֵ�����λ�ã�<0 ��ֵС�ڴ���ֵ ==0 ��ֵ���ڴ���ֵ >0 ��ֵ���ڴ���ֵ����
 *        root - ����ĸ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingPolynomial::solve(const DMat& coefficient,
	const double target_value,
	double& root) {
	//1.��⵱ǰ��������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if ((!coefficient.is_valid()) || (coefficient.get_rows() < 2) || (
		1 != coefficient.get_cols())) {
		return(-1);
	}
	//2.������ǰ�������������
	const unsigned int hightest_power = coefficient.get_rows() - 1;
	//3.���ݶ���ʽ����ߴ��ݣ����ò�ͬ�ķ�ʽ������ʽ��Ŀǰ֧�����ζ���ʽ����⣩��
	if (3 == hightest_power) {
		if (cardano_method(coefficient, target_value,
			root) < 0) {
			return(-2);
		}
		else {
			return(0);
		}
	}
	//4.�������е���ֱ�ӷ��ش���
	return(-3);
}

/**
 * name: cardano_method
 * brief: ����Cardano����������ζ���ʽ��
 * param: coefficient - ����Ķ���ʽϵ������(n*1ά����)��
 *        target_value - ����İ�ֵ�����ߴζ���ʽʱ��Ҫ��ֵ������ȷ����һ��������������
 *        target_value_relative_position - �����ֵ�����λ�ã�<0 ��ֵС�ڴ���ֵ ==0 ��ֵ���ڴ���ֵ >0 ��ֵ���ڴ���ֵ����
 *        root - ����ĸ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ��ʽ��ϸ����ο�https://proofwiki.org/wiki/Cardano's_Formula��
 */
int MtSolvingPolynomial::cardano_method(
	const DMat& coefficient, const double target_value,
	double& root) {
	//1.�������Ĳ������Ϸ�����ֱ�ӷ��ش���
	if (abs(coefficient.get_element(0, 0)) < TINY) {
		return(-1);
	}
	//2.��ȡ���ζ���ʽ�е�ϵ��a��b��c��d��
	const double a = coefficient.get_element(0, 0);
	const double b = coefficient.get_element(1, 0);
	const double c = coefficient.get_element(2, 0);
	const double d = coefficient.get_element(3, 0);
	//3.����Cardano��ʽ�е�Q�Լ�R��
	const double Q = (3.0 * a * c - b * b) / (9.0 * a * a);
	const double R = (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b) / (54.0 * a * a * a);
	//4.����Cardano��ʽ�е��б�ʽD��
	const double D = Q * Q * Q + R * R;
	//5.�����ǰ��������ʵ����������������������ͬ��
	if (abs(D) < TINY) {
		//5-1.����Cardano��ʽ�е�S��T��
		double S = pow(abs(R), 1.0 / 3.0);
		if (R < 0.0) {
			S *= -1.0;
		}
		const double T = S;
		//5-2.��������ʵ��������������ȣ���
		double x1 = S + T - (b / (3.0 * a));
		double x2 = (-((S + T) / 2.0)) - (b / (3.0 * a));
		//5-3.����������������
		if (x1 > x2) {
			double temp = x1;
			x1 = x2;
			x2 = temp;
		}
		root = x1;
		//5-5.�������е��˳ɹ����ء�
		return(0);
	}
	//6.�����ǰ����һ��ʵ���Լ����������
	else if (D > 0.0) {
		//6-1.���塣
		typedef std::complex<double> COMPLEX;
		//6-2.����Cardano��ʽ�е�S��T��
		double S = pow(abs(R + sqrt(D)), 1.0 / 3.0);
		if ((R + sqrt(D)) < 0.0) {
			S *= (-1.0);
		}
		double T = pow(abs(R - sqrt(D)), 1.0 / 3.0);
		if ((R - sqrt(D)) < 0.0) {
			T *= (-1.0);
		}
		//6-3.����һ��ʵ���Լ��������������
		COMPLEX temp(0.0, sqrt(3.0) / 2.0);
		double x1 = S + T - (b / (3.0 * a));
		const COMPLEX x2 = (-(static_cast<COMPLEX>(S + T) /
			static_cast<COMPLEX>(2.0))) - static_cast<COMPLEX>(
				b / (3.0 * a)) + (temp * static_cast<COMPLEX>(S - T));
		const COMPLEX x3 = (-(static_cast<COMPLEX>(S + T) /
			static_cast<COMPLEX>(2.0))) - static_cast<COMPLEX>(
				b / (3.0 * a)) - (temp * static_cast<COMPLEX>(S - T));
		//6-4.�����ת��Ϊʵ����
		double x2_r = x2.real() + x2.imag();
		double x3_r = x3.real() - x3.imag();
		//6-5.����������������
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
		//6-6.ɸѡ���ĸ����ҳ������Ҫ��ĸ���
		//a.������ǰ�������������
		//b.�����ǰ��ֵ�����ֵ�غϡ�
				//6-7.�������ĸ���
		root = x1;
		//6-8.�������е��˳ɹ����ء�
		return(0);
	}
	//7.�����ǰ��������ʵ������������ʵ��������ȡ�
	else {
		//7-1.���塣
		typedef std::complex<double> COMPLEX;
		//7-2.����Cardano��ʽ�е�S��T��
		COMPLEX temp = sqrt(static_cast<COMPLEX>(D));
		const COMPLEX S = pow(static_cast<COMPLEX>(R) + temp, 1.0 / 3.0);
		const COMPLEX T = pow(static_cast<COMPLEX>(R) - temp, 1.0 / 3.0);
		//7-3.��������ʵ����
		COMPLEX x1 = S + T - static_cast<COMPLEX>(b / (3.0 * a));
		temp.real(0.0);
		temp.imag(sqrt(3.0) / 2.0);
		COMPLEX x2 = (-((S + T) / static_cast<COMPLEX>(2.0))) -
			static_cast<COMPLEX>(b / (3.0 * a)) + (temp * (S - T));
		COMPLEX x3 = (-((S + T) / static_cast<COMPLEX>(2.0))) -
			static_cast<COMPLEX>(b / (3.0 * a)) - (temp * (S - T));
		//7-4.��x1��x2��x3��������
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
		//7-5.ɸѡ���ĸ����ҳ������Ҫ��ĸ���
		//a.������ǰ�������������
		//b.�����ǰ��ֵ�����ֵ�غϡ�
			//7-6.�������ĸ���
		root = x1.real();
		//8.�������е��˳ɹ����ء�
		return(0);
	}
}