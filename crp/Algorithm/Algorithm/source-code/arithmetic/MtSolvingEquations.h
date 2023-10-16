#pragma once

#include"../Symbol"
#include<vector>

template<typename _Tp>
class MtMatrix;

/**
 * name: MtSolvingEquations
 * brief: 求解方程组。
 * author: yameng_he
 * date: 2014-09-11
 */
class MtSolvingEquations {
	//define
public:
	typedef MtMatrix<double> DMat;
	typedef std::vector<double> DVec;
	typedef std::vector<unsigned int> UVec;
	static const double TINY;
	//interface
public:
	static int solve(DMat& coef, DMat& result);
	//implement
private:
	static int lup_decompose(DMat& matrix, UVec& pi);
	static int lup_solve(const DMat& lup, const UVec& pi, DMat& result);
	static int court_lup_decompose(DMat& matrix, UVec& pi);
	static int court_lup_solve(const DMat& lup, const UVec& pi, DMat& result);
	//restrict
private:
	MtSolvingEquations(void);
	~MtSolvingEquations(void);
	MtSolvingEquations(const MtSolvingEquations&);
	MtSolvingEquations& operator=(const MtSolvingEquations&);
};