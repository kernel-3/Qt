#pragma once

#include"MtFormula.h"

template<typename _Tp>
class MtMatrix;

/**
 * name: MtPolynomialFormula
 * brief: 多项式公式类,负责描述一个多项式公式，为多项式
 *　　　　 拟合提供基础公式。
 * author: yameng_he
 * date: 2016-06-15。
 */
class MtPolynomialFormula
	:public MtFormula {
	//define
public:
	typedef MtMatrix<double> DMat;
	static const double TINY;
	//construction & destruction
public:
	explicit MtPolynomialFormula(const double* x,
		const double* y, const unsigned int size,
		const unsigned int highest_power);
	virtual ~MtPolynomialFormula(void);
	//interface
public:
	static int calculate_x(const DMat& parameters,
		const double y, double& x);
	static int calculate_y(const DMat& parameters,
		const double x, double& y);
	//interface
public:
	int set_parameters(const DMat& parameters);
	const DMat& get_parameters() const;
	void set_correlation_coefficient(
		const double correlation_coefficient);
	void set_maximum_relative_deviation(
		const double relative_deviation);
	double get_maximum_relative_deviation() const;
	double get_correlation_coefficient() const;
	int calculate_coefficient_matrix(DMat& a) const;
	int calculate_result_matrix(DMat& b) const;
	int calculate_correlation_coefficient(const DMat& parameters,
		double& correlation_coefficient) const;
	int calculate_maximum_relative_deviation(const DMat& parameters,
		double& relative_deviation) const;
	//overrides
protected:
	virtual bool is_can_fitted() const;
	//variables
private:
	unsigned int _highest_power;
	DMat* _parameters;
	double _correlation_coefficient;
	double _maximum_relative_deviation;
};