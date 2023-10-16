#pragma once

#include"../arithmetic/MtLMFormula.h"

/**
 * name: LogitLog4P
 * brief: ÃèÊöLogitLog4P¹«Ê½¡£
 * author: yameng_he
 * date: 2015-09-25
 * formula: y=(A1-A0)/(1+(x/x0)^p)+A0
 */
class LogitLog4P
	:public MtLMFormula {
	//define
public:
	enum { PARAMETER_COUNT = 4, };
	static const double TINY;
	//construction & destruction
public:
	LogitLog4P(const double* x, const double* y,
		const unsigned int size);
	virtual ~LogitLog4P(void);
	//interface
public:
	static int calculate_x(const DMat& parameters, const double y, double& x);
	static int calculate_y(const DMat& parameters, const double x, double& y);
	//interface
public:
	const DMat& get_parameters() const;
	//overrides
public:
	virtual int set_parameters(const DMat& parameters);
	virtual int calculate_initialized_parameters(DMat& parameters);
	virtual int calculate_jacobian_matrix(const DMat& parameters, DMat& jacobian) const;
	virtual int calculate_difference_matrix(const DMat& parameters, DMat& difference) const;
	virtual int calculate_sum_of_squares_of_deviations(/*const*/ DMat& parameters, double& sum) const;
	virtual int calculate_maximum_relative_deviation(const DMat& parameters, double& relative_deviation) const;
	virtual int calculate_correlation_coefficient(const DMat& parameters, double& correlation_coefficient) const;
	//implement
private:
	double calculate_initialized_A0() const;
	double calculate_initialized_A1() const;
	//variables
private:
	DMat* _parameters;
};