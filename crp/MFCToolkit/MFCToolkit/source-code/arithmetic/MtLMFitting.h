#pragma once

#include"../Symbol"

class MtLMFormula;
template<typename _Tp>
class MtMatrix;

/**
 * name: MtLMFitting
 * brief: "LM"拟合算法实现。
 * author: yameng_he
 * date: 2015-05-12
 */
class MFC_TOOLKIT_API MtLMFitting{
//define
public:
	typedef MtMatrix<double> DMat;
	enum{ITERATIONS=1000,};
	static const double INIT_V;
	static const double INIT_LAMBDA;
	static const double MAX_RESIDUAL;
	static const double MAX_LAMBDA;
	static const double MIN_LAMBDA;
//construction & destruction
public:
	MtLMFitting(MtLMFormula &formula);
	~MtLMFitting(void);
//interface
public:
	int fit();
//restriction
private:
	MtLMFitting(const MtLMFitting &);
	MtLMFitting &operator=(const MtLMFitting &);
//implement
private:
	int calculate_lambda(DMat &beta,double &lambda,double &s0,double &v);
	int calculate_delta(const double lambda);
//variables
private:
	MtLMFormula &_formula;
	DMat *_jacobian;
	DMat *_jacobian_transpose;
	DMat *_difference;
	DMat *_coefficient;
	DMat *_delta;
	DMat *_beta;
	DMat *_temp;
};