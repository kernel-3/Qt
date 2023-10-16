#pragma once

#include"../Symbol"

template<typename _Tp>
class MtMatrix;
class MtSimpleLinearFormula;

/**
 * name: MtSimpleLinearFitting
 * brief: 简单线性拟合（一元线性拟合）实现类。
 * author: yameng_he
 * date: 2015-10-20
 */
class MFC_TOOLKIT_API MtSimpleLinearFitting{
//define
public:
	typedef MtSimpleLinearFormula FORMULA;
	typedef MtMatrix<double> DMat;
//construction & destruction
public:
	MtSimpleLinearFitting(FORMULA &formula);
	virtual ~MtSimpleLinearFitting(void);
//interface
public:
	int fit();
//variables
private:
	FORMULA &_formula;
};