#include"stdafx.h"
#include"MtLMFitting.h"
#include"MtLMFormula.h"
#include"MtMatrix.h"
#include"MtSolvingEquations.h"

//初始化静态变量
const double MtLMFitting::INIT_V=2.0;
const double MtLMFitting::INIT_LAMBDA=1.0E-3;
const double MtLMFitting::MAX_RESIDUAL=1.0E20;
const double MtLMFitting::MAX_LAMBDA=1.0E15;
const double MtLMFitting::MIN_LAMBDA=1.0E-15;

/**
 * name: MtLMFitting
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLMFitting::MtLMFitting(MtLMFormula &formula)
	:_formula(formula)
	,_jacobian(new DMat)
	,_jacobian_transpose(new DMat)
	,_difference(new DMat)
	,_coefficient(new DMat)
	,_delta(new DMat)
	,_beta(new DMat)
	,_temp(new DMat){
}

/**
 * name: ~MtLMFitting
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLMFitting::~MtLMFitting(void){
	delete _jacobian;
	delete _jacobian_transpose;
	delete _difference;
	delete _coefficient;
	delete _delta;
	delete _beta;
	delete _temp;
}

/**
 * name: fit
 * brief: 对当前公式进行拟合。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFitting::fit(){
	//1.获取当前公式的初始参数，并且判断获取是否成功。
	//1-1.声明当前操作所需变量。
	DMat beta;
	//1-2.获取当前公式的初始参数，并且判断获取是否成功。
	if(_formula.calculate_initialized_parameters(beta)<0){
		return(-1);
	}
	//2.定义最初的λ。
	double lambda=INIT_LAMBDA;
	//3.定义最初的v。
	double v=INIT_V;
	//5.计算当前参数下,公式的差方和。
	double s0=0.0;
	if(_formula.calculate_sum_of_squares_of_deviations(beta,s0)<0){
		return(-2);
	}
	//6.开始迭代求解当前公式。
	//6-1.声明当前操作所需变量。
	BOOL is_fitted=FALSE;
	BOOL is_success=FALSE;
	BOOL is_satisfied=FALSE;
	DMat parameters;
	double last_s0=0.0;
	double temp1=0.0;
	double temp2=0.0;
	double correlation_coefficient=0.0;
	double maximum_relative_deviation=0.0;
	//6-2.迭代求解公式。
	for(unsigned int index=0;index!=ITERATIONS;++index){
		//6-2-1.求解最优λ，并且判断求解是否成功。
		if(calculate_lambda(beta,lambda,s0,v)<0){
			break;
		}
		//6-2-2.获取当前参数下，公式拟合的相对偏差以及相关系数。
		if((_formula.calculate_maximum_relative_deviation(beta,temp1)>=0)&&(
			_formula.calculate_correlation_coefficient(beta,temp2)>=0)){
			//TRACE("相关系数=%lf，相对偏差=%lf\r\n",temp1,temp2);
			//a.如果当前第一次允许，则赋初始值。
			if(0==index){
				if(parameters.copy(beta)<0){
					return(-3);
				}
				maximum_relative_deviation=temp1;
				correlation_coefficient=temp2;
				is_fitted=TRUE;
			}
			//b.如果当前拟合已达成功条件（相对偏差小于百分之八并且相关系数大于0.99）。
			else if(temp1<0.5){ //note: relative deviation need to change (0.08 before)
				//b-1.如果以前的相关系数大于0.99，并且相对偏差小于当前的相对偏差。
				if((correlation_coefficient>0.99)&&(
					temp1>maximum_relative_deviation)&&((
					temp2-correlation_coefficient)<0.009)){
					//不对拟合参数做任何更改。
				}
				//b-2.其它情况下，修改当前记录的拟合参数。
				else{
					if(parameters.copy(beta)<0){
						return(-4);
					}
					maximum_relative_deviation=temp1;
					correlation_coefficient=temp2;
					is_success=TRUE;
				}
			}
			//c.如果当前已经抵达满意条件（相关系数大于0.99，但拟合尚未成功）。
			else if((temp2>0.99)&&(!is_success)){
				//c-1.如果以前的相关系数大于0.99，并且相对偏差小于当前的相对偏差。
				if((correlation_coefficient>0.99)&&(
					temp1>maximum_relative_deviation)&&((
					temp2-correlation_coefficient)<0.009)){
					//不对拟合参数做任何更改。
				}
				//c-2.其它情情况下，修改当前记录的拟合参数。
				else{
					if(parameters.copy(beta)<0){
						return(-5);
					}
					maximum_relative_deviation=temp1;
					correlation_coefficient=temp2;
					is_satisfied=TRUE;
				}
			}
			//d.如果当前尚未抵达满意以及成功条件。
			else if((temp2>correlation_coefficient)&&(
				!is_success)&&(!is_satisfied)){
				if(parameters.copy(beta)<0){
					return(-6);
				}
				maximum_relative_deviation=temp1;
				correlation_coefficient=temp2;
			}
		}
		//6-2-3.程序运行到此直接跳出循环。
		else{
			break;
		}
		//6-2-4.如果当前迭代的变化已经小于预期值。
		if(fabs(s0-last_s0)<(1.0E-20)){
			break;
		}
		//6-2-5.记录当前差方和。
		last_s0=s0;
	}
	//7.保存拟合结果。
	if(is_satisfied || is_success){
		_formula.set_maximum_relative_deviation(maximum_relative_deviation);
		_formula.set_correlation_coefficient(correlation_coefficient);
		_formula.set_parameters(parameters);
		return(0);
	}else{
		return(-6);
	}
}

/**
 * name: calculate_lambda
 * brief: 计算λ值。
 * param: beta - 公式参数（β）矩阵。
 *        lambda - 当前的λ值。
 *        s0 - 当前的公式差方和。
 *        v - 当前的v系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFitting::calculate_lambda(DMat &beta,double &lambda,double &s0,double &v){
	//1.利用当前公式参数（β），计算雅可比矩阵，并且判断计算是否成功。
	if(_formula.calculate_jacobian_matrix(beta,*_jacobian)<0){
		return(-1);
	}
	//2.计算当前雅可比矩阵的转置矩阵，并且判断计算是否成功。
	if(_jacobian->transpose(*_jacobian_transpose)<0){
		return(-2);
	}
	//3.利用当前公式参数（β），计算差值矩阵，并且判断计算是否成功。
	if(_formula.calculate_difference_matrix(beta,*_difference)<0){
		return(-3);
	}
	//4.引入λ，并计算引入λ后的公式差方和。
	//4-1.计算λ原值的差方和。
	//4-1-1.声明当前操作所需变量。
	double s1=MAX_RESIDUAL;
	//4-1-2.如果计算引入λ原值的δ失败，则直接返回相应错误。
	if(calculate_delta(lambda)<0){
		//(*_beta)=beta;
		return(-4);
	}
	//4-1-3.如果计算引入λ原值的δ成功，则计算差方和。
	else{
		//4-1-3-1.根据当前的δ、β计算新的β，并且判断计算是否成功。
		if(_delta->add(beta,*_delta)<0){
			return(-5);
		}
		//4-1-3-2.利用新的β计算新的差方和1，如果运算失败，停止此方向上的迭代。
		if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s1)<0){
		}
		//4-1-3-3.记录新的β值。
		_beta->copy(*_delta);
	}
	//4-2.计算λ缩小v倍的差方和。
	//4-2-1.声明当前操作所需变量。
	double lambda_s2=lambda;
	double s2=MAX_RESIDUAL;
	//4-2-2.循环计算λ缩小v倍的差方和。
	for(;;){
		//4-2-2-1.重新计算使用的λ，并且判断当前重新计算的λ是否合法。
		lambda_s2/=v;
		if(lambda_s2<MIN_LAMBDA){
			break;
		}
		//4-2-2-2.如果计算引入λ缩小v倍的δ失败，则直接返回相应错误。
		if(calculate_delta(lambda_s2)<0){
			//(*_delta)=beta;
			return(-6);
		}
		//4-2-2-3.如果计算引入λ缩小v倍的δ成功，则计算差方和。
		else{
			//a.根据当前的δ、β计算新的β，并且判断计算是否成功。
			if(_delta->add(beta,*_delta)<0){
				return(-7);
			}
			//b.利用新的 β 计算新的差方和s2，如果运算失败，则停止此方向上的迭代。
			if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s2)<0){
				continue;
			}
			//c.计算差方和成功，则跳出当前迭代。
			else{
				break;
			}
		}
	}
	//5.如果引入λ以及λ缩小v倍的差方和，比原值更糟，则利用λ=λv^k找到较原值更好的值。
	if((s0<s1)&&(s0<s2)){
		//5-1.声明当前操作所需变量。
		double lambda_t=lambda;
		//5-2.循环，直到找到一个较好的差方和。
		for(;;){
			//5-2-1.计算新的λ值。
 			lambda_t*=v;
			//5-2-2.如果当前λ的值过大。
			if(lambda_t>=MAX_LAMBDA){
				return(-8);
			}
			//5-2-3.计算新的δ，并且判断计算是否成功。
			if(calculate_delta(lambda_t)<0){
				return(-9);
			}
			//5-2-4.计算新的方差和。
			if(_delta->add(beta,*_delta)<0){
				return(-10);
			}
			if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s1)<0){
				continue;
			}
			//5-2-5.如果新的方差和优于原值。
			if(s1<s0){
				beta.copy(*_delta);
				lambda=lambda_t;
				s0=s1;
				v=INIT_V;
				return(0);
			}
		}
	}
	//6.如果λ缩小v倍的差方和优于λ原值。
	else if(s2<s1){
		s0=s2;
		lambda=lambda_s2;
		beta=(*_delta);
		return(0);
	}
	//7.如果λ原值的差方和优于λ缩小v倍。
	else{
		s0=s1;
		beta=(*_beta);
		return(0);
	}
}

/**
 * name: calculate_delta
 * brief: 根据指定的λ值，计算δ的值。
 * param: lambda - 指定的λ值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLMFitting::calculate_delta(const double lambda){
	//1.计算言雅可比矩阵与系数公式系数矩阵的乘积。
	DMat *matrix=_jacobian_transpose;
	if((_formula.get_weight_matrix()).is_valid()){
		if(_jacobian_transpose->multiply(
			_formula.get_weight_matrix(),*_temp)<0){
			return(-1);
		}
		matrix=_temp;
	}
	//2.计算LM算法中迭代公式的系数矩阵（此时认为雅可比矩阵以及其转置矩阵全部合法）。
	if(matrix->multiply(*_jacobian,*_coefficient)<0){
		return(-2);
	}
	for(unsigned long row=0;row!=_coefficient->get_rows();++row){
		for(unsigned long col=0;col!=_coefficient->get_cols();++col){
			if(row==col){
				_coefficient->set_element(
					row,col,(_coefficient->get_element(
					row,col))*(1.0+lambda));
			}
		}
	}
	//3.计算LM算法中迭代公式的结果矩阵（此时认为差值矩阵也合法）。
	if(matrix->multiply(*_difference,*_delta)<0){
		return(-3);
	}
	//4.求解δ。
	if(MtSolvingEquations::solve(*_coefficient,*_delta)<0){
		return(-4);
	}
	//5.程序运行到此成功返回。
	return(0);
}