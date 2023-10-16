#pragma once

#include"../arithmetic/MtLMFormula.h"

/**
 * name: LogitLog4P
 * brief: 描述LogitLog5P公式。
 * formula: y=(A-D)/(1+((x-E)/C)^B)+D
 */
class LogitLog5P
	:public MtLMFormula {
	//define
public:
	enum { PARAMETER_COUNT = 5, };
	static const double TINY;
	//construction & destruction
public:
	LogitLog5P(const double* x, const double* y,
		const unsigned int size);
	virtual ~LogitLog5P(void);
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
	double calculate_initialized_E() const;
	//variables
private:
	DMat* _parameters;
};
