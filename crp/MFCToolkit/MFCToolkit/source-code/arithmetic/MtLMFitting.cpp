#include"stdafx.h"
#include"MtLMFitting.h"
#include"MtLMFormula.h"
#include"MtMatrix.h"
#include"MtSolvingEquations.h"

//��ʼ����̬����
const double MtLMFitting::INIT_V=2.0;
const double MtLMFitting::INIT_LAMBDA=1.0E-3;
const double MtLMFitting::MAX_RESIDUAL=1.0E20;
const double MtLMFitting::MAX_LAMBDA=1.0E15;
const double MtLMFitting::MIN_LAMBDA=1.0E-15;

/**
 * name: MtLMFitting
 * brief: ���캯����
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
 * brief: ����������
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
 * brief: �Ե�ǰ��ʽ������ϡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFitting::fit(){
	//1.��ȡ��ǰ��ʽ�ĳ�ʼ�����������жϻ�ȡ�Ƿ�ɹ���
	//1-1.������ǰ�������������
	DMat beta;
	//1-2.��ȡ��ǰ��ʽ�ĳ�ʼ�����������жϻ�ȡ�Ƿ�ɹ���
	if(_formula.calculate_initialized_parameters(beta)<0){
		return(-1);
	}
	//2.��������Ħˡ�
	double lambda=INIT_LAMBDA;
	//3.���������v��
	double v=INIT_V;
	//5.���㵱ǰ������,��ʽ�Ĳ�͡�
	double s0=0.0;
	if(_formula.calculate_sum_of_squares_of_deviations(beta,s0)<0){
		return(-2);
	}
	//6.��ʼ������⵱ǰ��ʽ��
	//6-1.������ǰ�������������
	BOOL is_fitted=FALSE;
	BOOL is_success=FALSE;
	BOOL is_satisfied=FALSE;
	DMat parameters;
	double last_s0=0.0;
	double temp1=0.0;
	double temp2=0.0;
	double correlation_coefficient=0.0;
	double maximum_relative_deviation=0.0;
	//6-2.������⹫ʽ��
	for(unsigned int index=0;index!=ITERATIONS;++index){
		//6-2-1.������Ŧˣ������ж�����Ƿ�ɹ���
		if(calculate_lambda(beta,lambda,s0,v)<0){
			break;
		}
		//6-2-2.��ȡ��ǰ�����£���ʽ��ϵ����ƫ���Լ����ϵ����
		if((_formula.calculate_maximum_relative_deviation(beta,temp1)>=0)&&(
			_formula.calculate_correlation_coefficient(beta,temp2)>=0)){
			//TRACE("���ϵ��=%lf�����ƫ��=%lf\r\n",temp1,temp2);
			//a.�����ǰ��һ�������򸳳�ʼֵ��
			if(0==index){
				if(parameters.copy(beta)<0){
					return(-3);
				}
				maximum_relative_deviation=temp1;
				correlation_coefficient=temp2;
				is_fitted=TRUE;
			}
			//b.�����ǰ����Ѵ�ɹ����������ƫ��С�ڰٷ�֮�˲������ϵ������0.99����
			else if(temp1<0.5){ //note: relative deviation need to change (0.08 before)
				//b-1.�����ǰ�����ϵ������0.99���������ƫ��С�ڵ�ǰ�����ƫ�
				if((correlation_coefficient>0.99)&&(
					temp1>maximum_relative_deviation)&&((
					temp2-correlation_coefficient)<0.009)){
					//������ϲ������κθ��ġ�
				}
				//b-2.��������£��޸ĵ�ǰ��¼����ϲ�����
				else{
					if(parameters.copy(beta)<0){
						return(-4);
					}
					maximum_relative_deviation=temp1;
					correlation_coefficient=temp2;
					is_success=TRUE;
				}
			}
			//c.�����ǰ�Ѿ��ִ��������������ϵ������0.99���������δ�ɹ�����
			else if((temp2>0.99)&&(!is_success)){
				//c-1.�����ǰ�����ϵ������0.99���������ƫ��С�ڵ�ǰ�����ƫ�
				if((correlation_coefficient>0.99)&&(
					temp1>maximum_relative_deviation)&&((
					temp2-correlation_coefficient)<0.009)){
					//������ϲ������κθ��ġ�
				}
				//c-2.����������£��޸ĵ�ǰ��¼����ϲ�����
				else{
					if(parameters.copy(beta)<0){
						return(-5);
					}
					maximum_relative_deviation=temp1;
					correlation_coefficient=temp2;
					is_satisfied=TRUE;
				}
			}
			//d.�����ǰ��δ�ִ������Լ��ɹ�������
			else if((temp2>correlation_coefficient)&&(
				!is_success)&&(!is_satisfied)){
				if(parameters.copy(beta)<0){
					return(-6);
				}
				maximum_relative_deviation=temp1;
				correlation_coefficient=temp2;
			}
		}
		//6-2-3.�������е���ֱ������ѭ����
		else{
			break;
		}
		//6-2-4.�����ǰ�����ı仯�Ѿ�С��Ԥ��ֵ��
		if(fabs(s0-last_s0)<(1.0E-20)){
			break;
		}
		//6-2-5.��¼��ǰ��͡�
		last_s0=s0;
	}
	//7.������Ͻ����
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
 * brief: �����ֵ��
 * param: beta - ��ʽ�������£�����
 *        lambda - ��ǰ�Ħ�ֵ��
 *        s0 - ��ǰ�Ĺ�ʽ��͡�
 *        v - ��ǰ��vϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFitting::calculate_lambda(DMat &beta,double &lambda,double &s0,double &v){
	//1.���õ�ǰ��ʽ�������£��������ſɱȾ��󣬲����жϼ����Ƿ�ɹ���
	if(_formula.calculate_jacobian_matrix(beta,*_jacobian)<0){
		return(-1);
	}
	//2.���㵱ǰ�ſɱȾ����ת�þ��󣬲����жϼ����Ƿ�ɹ���
	if(_jacobian->transpose(*_jacobian_transpose)<0){
		return(-2);
	}
	//3.���õ�ǰ��ʽ�������£��������ֵ���󣬲����жϼ����Ƿ�ɹ���
	if(_formula.calculate_difference_matrix(beta,*_difference)<0){
		return(-3);
	}
	//4.����ˣ�����������˺�Ĺ�ʽ��͡�
	//4-1.�����ԭֵ�Ĳ�͡�
	//4-1-1.������ǰ�������������
	double s1=MAX_RESIDUAL;
	//4-1-2.������������ԭֵ�Ħ�ʧ�ܣ���ֱ�ӷ�����Ӧ����
	if(calculate_delta(lambda)<0){
		//(*_beta)=beta;
		return(-4);
	}
	//4-1-3.������������ԭֵ�Ħĳɹ���������͡�
	else{
		//4-1-3-1.���ݵ�ǰ�Ħġ��¼����µĦ£������жϼ����Ƿ�ɹ���
		if(_delta->add(beta,*_delta)<0){
			return(-5);
		}
		//4-1-3-2.�����µĦ¼����µĲ��1���������ʧ�ܣ�ֹͣ�˷����ϵĵ�����
		if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s1)<0){
		}
		//4-1-3-3.��¼�µĦ�ֵ��
		_beta->copy(*_delta);
	}
	//4-2.�������Сv���Ĳ�͡�
	//4-2-1.������ǰ�������������
	double lambda_s2=lambda;
	double s2=MAX_RESIDUAL;
	//4-2-2.ѭ���������Сv���Ĳ�͡�
	for(;;){
		//4-2-2-1.���¼���ʹ�õĦˣ������жϵ�ǰ���¼���Ħ��Ƿ�Ϸ���
		lambda_s2/=v;
		if(lambda_s2<MIN_LAMBDA){
			break;
		}
		//4-2-2-2.��������������Сv���Ħ�ʧ�ܣ���ֱ�ӷ�����Ӧ����
		if(calculate_delta(lambda_s2)<0){
			//(*_delta)=beta;
			return(-6);
		}
		//4-2-2-3.��������������Сv���Ħĳɹ���������͡�
		else{
			//a.���ݵ�ǰ�Ħġ��¼����µĦ£������жϼ����Ƿ�ɹ���
			if(_delta->add(beta,*_delta)<0){
				return(-7);
			}
			//b.�����µ� �� �����µĲ��s2���������ʧ�ܣ���ֹͣ�˷����ϵĵ�����
			if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s2)<0){
				continue;
			}
			//c.�����ͳɹ�����������ǰ������
			else{
				break;
			}
		}
	}
	//5.���������Լ�����Сv���Ĳ�ͣ���ԭֵ���㣬�����æ�=��v^k�ҵ���ԭֵ���õ�ֵ��
	if((s0<s1)&&(s0<s2)){
		//5-1.������ǰ�������������
		double lambda_t=lambda;
		//5-2.ѭ����ֱ���ҵ�һ���ϺõĲ�͡�
		for(;;){
			//5-2-1.�����µĦ�ֵ��
 			lambda_t*=v;
			//5-2-2.�����ǰ�˵�ֵ����
			if(lambda_t>=MAX_LAMBDA){
				return(-8);
			}
			//5-2-3.�����µĦģ������жϼ����Ƿ�ɹ���
			if(calculate_delta(lambda_t)<0){
				return(-9);
			}
			//5-2-4.�����µķ���͡�
			if(_delta->add(beta,*_delta)<0){
				return(-10);
			}
			if(_formula.calculate_sum_of_squares_of_deviations(*_delta,s1)<0){
				continue;
			}
			//5-2-5.����µķ��������ԭֵ��
			if(s1<s0){
				beta.copy(*_delta);
				lambda=lambda_t;
				s0=s1;
				v=INIT_V;
				return(0);
			}
		}
	}
	//6.�������Сv���Ĳ�����ڦ�ԭֵ��
	else if(s2<s1){
		s0=s2;
		lambda=lambda_s2;
		beta=(*_delta);
		return(0);
	}
	//7.�����ԭֵ�Ĳ�����ڦ���Сv����
	else{
		s0=s1;
		beta=(*_beta);
		return(0);
	}
}

/**
 * name: calculate_delta
 * brief: ����ָ���Ħ�ֵ������ĵ�ֵ��
 * param: lambda - ָ���Ħ�ֵ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLMFitting::calculate_delta(const double lambda){
	//1.�������ſɱȾ�����ϵ����ʽϵ������ĳ˻���
	DMat *matrix=_jacobian_transpose;
	if((_formula.get_weight_matrix()).is_valid()){
		if(_jacobian_transpose->multiply(
			_formula.get_weight_matrix(),*_temp)<0){
			return(-1);
		}
		matrix=_temp;
	}
	//2.����LM�㷨�е�����ʽ��ϵ�����󣨴�ʱ��Ϊ�ſɱȾ����Լ���ת�þ���ȫ���Ϸ�����
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
	//3.����LM�㷨�е�����ʽ�Ľ�����󣨴�ʱ��Ϊ��ֵ����Ҳ�Ϸ�����
	if(matrix->multiply(*_difference,*_delta)<0){
		return(-3);
	}
	//4.���ġ�
	if(MtSolvingEquations::solve(*_coefficient,*_delta)<0){
		return(-4);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}