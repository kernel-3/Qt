#pragma once

#include"MtFormula.h"

template<typename _Tp>
class MtMatrix;

/**
 * name: MtSimpleLinearFormula
 * brief: 简单线性公式。
 * author: yameng_he
 * date: 2015-10-20
 * formula: y=ax+b
 */
class MFC_TOOLKIT_API MtSimpleLinearFormula
	:public MtFormula{
//define
public:
	enum{PARAMETER_COUNT=2,};
	typedef MtMatrix<double> DMat;
	static const double TINY;
//construction & destruction
public:
	MtSimpleLinearFormula(const double *x,
		const double *y,const unsigned int size);
	virtual ~MtSimpleLinearFormula(void);
//static interface
public:
	static int calculate_x(const DMat &parameters,const double y,double &x);
	static int calculate_y(const DMat &parameters,const double x,double &y);
//interface
public:
	int set_parameters(const DMat &parameters);
	const DMat &get_parameters() const;
	void set_correlation_coefficient(
		const double correlation_coefficient);
	double get_correlation_coefficient() const;
	void set_maximum_relative_deviation(
		const double relative_deviation);
	double get_maximum_relative_deviation() const;
	int calculate_coefficient_matrix(DMat &c) const;
	int calculate_result_matrix(DMat &b) const;
	int calculate_correlation_coefficient(const DMat &parameters,
		double &correlation_coefficient) const;
	int calculate_maximum_relative_deviation(const DMat &parameters,
		double &relative_deviation) const;
//variables
private:
	DMat *_parameters;
	double _correlation_coefficient;
	double _maximum_relative_deviation;
};
