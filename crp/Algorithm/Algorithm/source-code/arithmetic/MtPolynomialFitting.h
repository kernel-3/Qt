#pragma once

#include"../Symbol"

template<typename _Tp>
class MtMatrix;
class MtPolynomialFormula;

/**
 * name: MtPolynomialFitting
 * breif: 多项式拟合类，负责对各种多项式进行拟合。
 * author: yameng_he
 * date: 2016-06-16
 */
class MtPolynomialFitting {
	//define
public:
	typedef MtPolynomialFormula FORMULA;
	typedef MtMatrix<double> DMat;
	//construction & destruction
public:
	MtPolynomialFitting(FORMULA& formula);
	virtual ~MtPolynomialFitting(void);
	//interface
public:
	int fit();
	//variables
private:
	FORMULA& _formula;
};

