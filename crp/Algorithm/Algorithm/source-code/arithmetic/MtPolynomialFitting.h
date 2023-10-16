#pragma once

#include"../Symbol"

template<typename _Tp>
class MtMatrix;
class MtPolynomialFormula;

/**
 * name: MtPolynomialFitting
 * breif: ����ʽ����࣬����Ը��ֶ���ʽ������ϡ�
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

