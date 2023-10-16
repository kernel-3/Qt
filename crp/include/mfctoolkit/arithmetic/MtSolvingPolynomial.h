#pragma once

#include"../Symbol"

template<typename _Tp>
class MtMatrix;

/**
 * name: MtSolvingPolynomial
 * brief: 求解多项式(求多项式的根).
 * author: yameng_he
 * date: 2015-06-17
 */
class MFC_TOOLKIT_API MtSolvingPolynomial{
//define
public:
	typedef MtMatrix<double> DMat;
	static const double TINY;
//interface
public:
	static int solve(
		const DMat &coefficient,const double target_value,
		const int target_value_relative_position,double &root);
//implement
private:
	static int cardano_method(
		const DMat &coefficient,const double target_value,
		const int target_value_relative_position,double &root);
//restriction
private:
	MtSolvingPolynomial(void);
	MtSolvingPolynomial(const MtSolvingPolynomial &);
	~MtSolvingPolynomial(void);
	MtSolvingPolynomial &operator=(const MtSolvingPolynomial &);
};

