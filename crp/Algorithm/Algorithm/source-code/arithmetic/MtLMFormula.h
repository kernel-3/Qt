#pragma once

#include"MtFormula.h"

template<typename _Tp>
class MtMatrix;

/**
 * name: MtLMFormula
 * brief: 期望用LM算法拟合的所有公式，均继承此类，
 *        并且实现此类要求的所有接口。
 * author: yameng_he
 * date: 2015-05-06
 */
class MtLMFormula
	:public MtFormula {
	//define
public:
	typedef MtMatrix<double> DMat;
	//construction & destruction
public:
	explicit MtLMFormula(const double* x, const double* y,
		const unsigned int size, const unsigned int minimum_size);
	virtual ~MtLMFormula(void);
	//interface
public:
	void set_maximum_relative_deviation(const double maximum_relative_deviation);
	double get_maximum_relative_deviation() const;
	void set_correlation_coefficient(const double correlation_coefficient);
	double get_correlation_coefficient() const;
	const DMat& get_weight_matrix() const;
	//overrides
public:
	virtual int set_parameters(const DMat& parameters) = 0;
	virtual int calculate_initialized_parameters(DMat& parameters) = 0;
	virtual int calculate_jacobian_matrix(const DMat& parameters, DMat& jacobian) const = 0;
	virtual int calculate_difference_matrix(const DMat& parameters, DMat& difference) const = 0;
	virtual int calculate_sum_of_squares_of_deviations(/*const*/ DMat& parameters, double& sum) const = 0;
	virtual int calculate_maximum_relative_deviation(const DMat& parameters, double& relative_deviation) const = 0;
	virtual int calculate_correlation_coefficient(const DMat& parameters, double& correlation_coefficient) const = 0;
	//variables
private:
	DMat* _weight;
	double _maximum_relative_deviation;
	double _correlation_coefficient;
};