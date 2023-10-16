#pragma once

#include"../../../../include/mfctoolkit/arithmetic/MtLMFormula.h"

/**
 * name: LogitLog4P
 * brief: 生化分析仪中 Logit-Log 4P 公式，负责在定标时进行
 *        公式拟合，在其它情况下进行浓度计算。
 * author: yameng_he
 * date: 2015-05-07
 */
class LogitLog4P
	:public MtLMFormula{
//define
public:
	static const double ZERO;
	static const double ZERO_THRESHOLD_VALUE;
//construction & destruction
public:
	LogitLog4P(void);
	virtual ~LogitLog4P(void);
//interface
public:
	DMat &get_parameters();
	const DMat &get_parameters() const;
//overrides
public:
	virtual void set_parameters(const DMat &parameters);
	virtual int get_initialized_parameters(const double *x,const double *y,
		const unsigned int size,DMat &parameters);
	virtual int get_jacobian_matrix(const DMat &parameters,DMat &jacobian) const;
	virtual int get_difference_matrix(const DMat &parameters,DMat &difference) const;
	virtual int get_sum_of_squares_of_deviations(const DMat &parameters,double &sum) const;
	virtual int get_correlation_coefficient(const DMat &parameters,
		double &correlation_coefficient,DMat &relative_deviation) const;
//restriction
private:
	LogitLog4P(const LogitLog4P &);
	LogitLog4P &operator=(const LogitLog4P &);
//implement
private:
	int calculate_absorbance(const DMat &parameters,const double conc,double &abs) const;
	int calculate_concentration(const DMat &parameters,const double abs,double &conc) const;
//variables
private:
	DMat *_parameters;
};