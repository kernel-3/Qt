#include"stdafx.h"
#include"MtSolvingEquations.h"
#include"MtMatrix.h"
#include<math.h>
#include<assert.h>

//�������о�̬������
const double MtSolvingEquations::TINY=1.0E-20;

/**
 * name: solve
 * brief: ���õ�ǰ��ϵ�����󡢽������������Է����飬
 *        ��������Ľ���洢�ڽ�������з��ء�
 * param: coef - ϵ������
 *        result - �������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingEquations::solve(DMat &coef,DMat &result){
	//1.�����ǰ������Է�������������Ϸ���
	if(!((coef.is_valid())&&(result.is_valid())&&
		(coef.get_rows()==coef.get_cols())&&
		(coef.get_rows()>=2&&coef.get_cols()>=2)&&
		(coef.get_rows()==result.get_rows())&&
		(1==result.get_cols()))){
		return(-1);
	}
	//2.����ϵ�������LUP�ֽ⡣
	//2-1.����LUP�ֽ��������ʱ�����顣
	UVec pi(result.get_rows(),0);
	//2-2.����ϵ�������LUP�ֽ⡣
	if(lup_decompose(coef,pi)<0){
		return(-2);
	}
	//3.������Է����飬�����ж�����Ƿ�ɹ���
	if(lup_solve(coef,pi,result)<0){
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: lup_decompose
 * breif:����ָ���ľ������LUP�ֽ⡣
 * param:��matrix - ���ֽ�ľ���
 *         pi - �ڽ�LUP�ֽ�ʱ������Ҫ����ʱ�����顣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingEquations::lup_decompose(DMat &matrix,UVec &pi){
	//remark: �˴�����matrix��pi�Ϸ�����Ч��
	//1.��¼��ǰ���ֽ����������
	const unsigned int matrix_rows=matrix.get_rows();
	//2.Ϊ��ǰ�Ħ����鸳��ֵ��
	for(unsigned int index=0;index!=matrix_rows;++index){
		pi[index]=index;
	}
	//3.ѭ������ʼ���о����LUP�ֽ⡣
	for(unsigned int k=0;k!=matrix_rows;++k){
		//3-1.ѡ��Ԫ��
		//3-1-1.������ǰ�������������
		double pivot=0.0;
		unsigned int pivot_k=0;
		//3-1-2.������ǰ�����У�Ϊ��ǰ����ѡȡ��Ԫ������¼��Ԫλ�á�
		for(unsigned int i=k;i!=matrix_rows;++i){
			if(fabs(matrix.get_element(i,k))>pivot){
				pivot=fabs(matrix.get_element(i,k));
				pivot_k=i;
			}
		}
		//3-1-3.������ֽ����ǰ�У���ԪΪ�㣬��˵���������죬���ܽ���LUP�ֽ⡣
		if(fabs(pivot)<TINY){
			return(-1);
		}
		//3-2.������Ԫ�������������ݡ�
		unsigned int temp=pi[k];
		pi[k]=pi[pivot_k];
		pi[pivot_k]=temp;
		//3-3.����������У�ʹ�þ������Ͻ�Ԫ�����
		for(unsigned int i=0;i!=matrix_rows;++i){
			double temp_t=matrix.get_element(k,i);
			matrix.set_element(k,i,matrix.get_element(pivot_k,i));
			matrix.set_element(pivot_k,i,temp_t);
		}
		//3-4.ѭ������ʼ������ֽ����������Ǿ����Լ������Ǿ���
		for(unsigned int i=k+1;i!=matrix_rows;++i){
			matrix.set_element(i,k,matrix.get_element(i,k)/
				matrix.get_element(k,k));
			for(unsigned int j=k+1;j!=matrix_rows;++j){
				matrix.set_element(i,j,matrix.get_element(i,j)-(
					matrix.get_element(i,k)*matrix.get_element(k,j)));
			}
		}
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: lup_solve
 * brief: �����Է����顣
 * param: lup - ����LUP�ֽ�ľ���
 *        pi - LUP�ֽ�����еĦ����顣
 *        result - ��ʽ�Ҳ�Ľ����������һ��������������
 *                 ����Ľ��ͬʱ��������������У����ҽ�
 *                 ����ԭֵ���ǡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingEquations::lup_solve(const DMat &lup,const UVec &pi,DMat &result){
	//remark: ��ʱȷ��lup��pi��result����ⷽ�����������
	//1.������ǰ�������������
	const DMat b(result);
	const unsigned int n=lup.get_rows();
	//2.��ǰ�������̡�
	for(unsigned int i=0;i!=n;++i){
		//2-1.��ȡ��ǰ��Ӧ��b��[i]��ֵ��
		double bpi=b.get_element(pi[i],0);
		//2-2.�����ǰ�����ǵ�һ�ε�����
		if(0!=i){
			for(unsigned int j=0;j!=i;++j){
				bpi-=lup.get_element(i,j)*result.get_element(j,0);
			}
		}
		//2-3.�洢��ǰ�����yi��
		result.set_element(i,0,bpi);
	}
	//3.���������̡�
	for(unsigned int i=n-1;static_cast<int>(i)>=0;--i){
		//3-1.����yi��ֵ��
		double yi=result.get_element(i,0);
		//3-2.���ݹ�ʽ���㡣
		for(unsigned int j=i+1;j!=n;++j){
			yi-=lup.get_element(i,j)*result.get_element(j,0);
		}
		//3-3.���������������
		result.set_element(i,0,yi/lup.get_element(i,i));
	}
	//4.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: court_lup_decompose
 * brief: ��ָ���ľ������LUP�ֽ⣨ʹ��Court�㷨����
 * param: matrix - ���ֽ�ľ���
 *        pi - �ڽ�LUP�ֽ�ʱ������Ҫ����ʱ�����顣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingEquations::court_lup_decompose(DMat &matrix,UVec &pi){
	//remark: �˴�����matrix��pi�Ϸ�����Ч��
	//1.���������ÿһ�У���ȡÿһ�е����ֵ��
	//1-1.������ǰ�������������
	const unsigned int n=matrix.get_rows();
	DVec maxes(n);
	//1-2.���������ÿһ�У�������ֵ�����Ҵ洢��ָ���������С�
	for(unsigned int i=0;i!=n;++i){
		//1-2-1.������ǰ�������������
		double big=0.0;
		//1-2-2.����������У��������ǰ�е����ֵ��
		for(unsigned int j=0;j!=n;++j){
			const double temp=fabs(matrix.get_element(i,j));
			if(temp>big){
				big=temp;
			}
		}
		//1-2-3.�����ǰ�������죨���ܽ���LUP�ֽ⣩��
		if(fabs(big)<TINY){
			return(-1);
		}
		//1-2-4.�洢���ֵ�ĵ�����ʵ����ν�ġ���ʽ��Ԫ������
		maxes[i]=1.0/big;
	}
	//2.����Court�㷨�����о����LUP�ֽ⡣
	unsigned int max_index=0;
	for(unsigned int j=0;j!=n;++j){
		//2-1.Court�㷨��һ���� ����ֽ�������Ǿ����ֵ���������Խ��ߣ���
		for(unsigned int i=0;i!=j;++i){
			double temp=matrix.get_element(i,j);
			for(unsigned int k=0;k!=i;++k){
				temp-=matrix.get_element(i,k)*
					matrix.get_element(k,j);
			}
			matrix.set_element(i,j,temp);
		}
		//2-2.Court�㷨�ڶ����� ���������Ǿ�����ֻ�ڶԽ����ϵ�ֵ�Լ������Ǿ��������е�ֵ��
		double big=0.0;
		for(unsigned int i=j;i!=n;++i){
			//2-2-1.���������Ǿ�����ֻ�ڶԽ����ϵ�ֵ�Լ������Ǿ��������е�ֵ��
			double temp=matrix.get_element(i,j);
			for(unsigned int k=0;k!=j;++k){
				temp-=matrix.get_element(i,k)*matrix.get_element(k,j);
			}
			matrix.set_element(i,j,temp);
			//2-2-2.�������ֵ�Լ����ֵ�����кš�
			temp=maxes[i]*fabs(temp);
			if(temp>big){
				big=temp;
				max_index=i;
			}
		}
		//2-3.�����ǰ���ֵ�����ٶԽ����ϣ�����е�����
		if(max_index!=j){
			//2-3-1.������ǰ�������������
			double temp=0.0;
			//2-3-2.���������С�
			for(unsigned int k=0;k!=n;++k){
				temp=matrix.get_element(max_index,k);
				matrix.set_element(max_index,k,matrix.get_element(j,k));
				matrix.set_element(j,k,temp);
			}
			//2-3-3.���������е����ֵ��
			temp=maxes[max_index];
			maxes[max_index]=maxes[j];
			maxes[j]=temp;
		}
		//2-4.��¼�µ�ǰ���ֵԭʼ�кţ��ڽ����Է�����ʱ���������������Ӧ��
		pi[j]=max_index;
		//2-5.����ֽ���¾����ֵ��
		//2-5-1.�������ǰ�����ֵΪ�㣬��������죬���ܽ��зֽ⡣
		if(fabs(matrix.get_element(j,j))<TINY){//��������жϡ�
			return(-2);
		}
		//2-5-2.��������¾���ʱ���˵�ϵ����
		double temp=1.0/matrix.get_element(j,j);
		//2-5-3.��������¾���ֵд��ԭ����
		for(unsigned int k=j+1;k!=n;++k){
			(matrix[k][j])*=temp;
		}
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: court_lup_solve
 * brief: �����Է����顣
 * param: lup - ����LUP�ֽ�ľ���
 *        pi - LUP�ֽ�����еĦ����顣
 *        result - ��ʽ�Ҳ�Ľ����������һ��������������
 *                 ����Ľ��ͬʱ��������������У����ҽ�
 *                 ����ԭֵ���ǡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSolvingEquations::court_lup_solve(const DMat &lup,const UVec &pi,DMat &result){
	//remark: ��ʱȷ��lup��pi��result����ⷽ�����������
	//1.������ǰ�������������
	const unsigned int n=lup.get_cols();
	//2.��ǰ��������ʵ�֡�
	for(unsigned int i=0;i!=n;++i){
		//2-1.����LU�ֽ�����еĻ�����Ϣ���������������С�
		double temp=result.get_element(pi[i],0);
		result.set_element(pi[i],0,result.get_element(i,0));
		//2-2.�����ǰ�����ǵ�һ��ѭ����
		if(0!=i){
			for(unsigned int j=0;j!=i;++j){
				temp-=lup.get_element(i,j)*result.get_element(j,0);
			}
		}
		//2-3.������Ľ���Żص���ȷ��λ�á�
		result.set_element(i,0,temp);
	}
	//3.����������ʵ�֡�
	for(unsigned int i=n-1;static_cast<long>(i)>=0;--i){
		double temp=result.get_element(i,0);
		for(unsigned int j=i+1;j!=n;++j){
			temp-=lup.get_element(i,j)*result.get_element(j,0);
		}
		//�����ĸ��Զ������Ϊ�㣬��Ϊ�ڷֽ�׶���ֵ�Ѿ�����֤��Ϊ�㡣
		result.set_element(i,0,temp/lup.get_element(i,i));
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}