#include"stdafx.h"
#include"MtSolvingEquations.h"
#include"MtMatrix.h"
#include<math.h>
#include<assert.h>

//定义类中静态变量。
const double MtSolvingEquations::TINY=1.0E-20;

/**
 * name: solve
 * brief: 利用当前的系数矩阵、结果矩阵求解线性方程组，
 *        并将计算的结果存储在结果矩阵中返回。
 * param: coef - 系数矩阵。
 *        result - 结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingEquations::solve(DMat &coef,DMat &result){
	//1.如果当前求解线性方程组的条件不合法。
	if(!((coef.is_valid())&&(result.is_valid())&&
		(coef.get_rows()==coef.get_cols())&&
		(coef.get_rows()>=2&&coef.get_cols()>=2)&&
		(coef.get_rows()==result.get_rows())&&
		(1==result.get_cols()))){
		return(-1);
	}
	//2.计算系数矩阵的LUP分解。
	//2-1.创建LUP分解所需的临时π数组。
	UVec pi(result.get_rows(),0);
	//2-2.计算系数矩阵的LUP分解。
	if(lup_decompose(coef,pi)<0){
		return(-2);
	}
	//3.求解线性方程组，并且判断求解是否成功。
	if(lup_solve(coef,pi,result)<0){
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: lup_decompose
 * breif:　对指定的矩阵进行LUP分解。
 * param:　matrix - 待分解的矩阵。
 *         pi - 在进LUP分解时，所需要的临时π数组。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingEquations::lup_decompose(DMat &matrix,UVec &pi){
	//remark: 此处假设matrix、pi合法、有效。
	//1.记录当前待分解矩阵行数。
	const unsigned int matrix_rows=matrix.get_rows();
	//2.为当前的π数组赋除值。
	for(unsigned int index=0;index!=matrix_rows;++index){
		pi[index]=index;
	}
	//3.循环，开始进行矩阵的LUP分解。
	for(unsigned int k=0;k!=matrix_rows;++k){
		//3-1.选主元。
		//3-1-1.声明当前操作所需变量。
		double pivot=0.0;
		unsigned int pivot_k=0;
		//3-1-2.遍历当前矩阵行，为当前矩阵选取主元，并记录主元位置。
		for(unsigned int i=k;i!=matrix_rows;++i){
			if(fabs(matrix.get_element(i,k))>pivot){
				pivot=fabs(matrix.get_element(i,k));
				pivot_k=i;
			}
		}
		//3-1-3.如果待分解矩阵当前列，主元为零，则说明矩阵奇异，不能进行LUP分解。
		if(fabs(pivot)<TINY){
			return(-1);
		}
		//3-2.跟据主元交换π数组内容。
		unsigned int temp=pi[k];
		pi[k]=pi[pivot_k];
		pi[pivot_k]=temp;
		//3-3.交换矩阵的行，使得矩阵左上角元素最大。
		for(unsigned int i=0;i!=matrix_rows;++i){
			double temp_t=matrix.get_element(k,i);
			matrix.set_element(k,i,matrix.get_element(pivot_k,i));
			matrix.set_element(pivot_k,i,temp_t);
		}
		//3-4.循环，开始计算待分解矩阵的上三角矩阵以及下三角矩阵。
		for(unsigned int i=k+1;i!=matrix_rows;++i){
			matrix.set_element(i,k,matrix.get_element(i,k)/
				matrix.get_element(k,k));
			for(unsigned int j=k+1;j!=matrix_rows;++j){
				matrix.set_element(i,j,matrix.get_element(i,j)-(
					matrix.get_element(i,k)*matrix.get_element(k,j)));
			}
		}
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: lup_solve
 * brief: 解线性方程组。
 * param: lup - 经过LUP分解的矩阵。
 *        pi - LUP分解过程中的π数组。
 *        result - 等式右侧的结果矩阵（这里一定是列向量），
 *                 计算的结果同时保存在这个矩阵中，并且将
 *                 矩阵原值覆盖。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingEquations::lup_solve(const DMat &lup,const UVec &pi,DMat &result){
	//remark: 此时确保lup、pi、result满足解方程组的条件。
	//1.声明当前操作所需变量。
	const DMat b(result);
	const unsigned int n=lup.get_rows();
	//2.向前迭代过程。
	for(unsigned int i=0;i!=n;++i){
		//2-1.获取当前对应的bπ[i]的值。
		double bpi=b.get_element(pi[i],0);
		//2-2.如果当前并不是第一次迭代。
		if(0!=i){
			for(unsigned int j=0;j!=i;++j){
				bpi-=lup.get_element(i,j)*result.get_element(j,0);
			}
		}
		//2-3.存储当前计算的yi。
		result.set_element(i,0,bpi);
	}
	//3.向后迭代过程。
	for(unsigned int i=n-1;static_cast<int>(i)>=0;--i){
		//3-1.计算yi的值。
		double yi=result.get_element(i,0);
		//3-2.跟据公式计算。
		for(unsigned int j=i+1;j!=n;++j){
			yi-=lup.get_element(i,j)*result.get_element(j,0);
		}
		//3-3.计算向后迭代结果。
		result.set_element(i,0,yi/lup.get_element(i,i));
	}
	//4.程序运行到此直接返回。
	return(0);
}

/**
 * name: court_lup_decompose
 * brief: 对指定的矩阵进行LUP分解（使用Court算法）。
 * param: matrix - 待分解的矩阵。
 *        pi - 在进LUP分解时，所需要的临时π数组。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingEquations::court_lup_decompose(DMat &matrix,UVec &pi){
	//remark: 此处假设matrix、pi合法、有效。
	//1.遍历矩阵的每一行，提取每一行的最大值。
	//1-1.声明当前操作所需变量。
	const unsigned int n=matrix.get_rows();
	DVec maxes(n);
	//1-2.遍历矩阵的每一行，求出最大值，并且存储到指定的容器中。
	for(unsigned int i=0;i!=n;++i){
		//1-2-1.声明当前操作所需变量。
		double big=0.0;
		//1-2-2.遍历矩阵的列，求出矩阵当前行的最大值。
		for(unsigned int j=0;j!=n;++j){
			const double temp=fabs(matrix.get_element(i,j));
			if(temp>big){
				big=temp;
			}
		}
		//1-2-3.如果当前矩阵奇异（不能进行LUP分解）。
		if(fabs(big)<TINY){
			return(-1);
		}
		//1-2-4.存储最大值的倒数，实现所谓的“隐式主元”法。
		maxes[i]=1.0/big;
	}
	//2.利用Court算法，进行矩阵的LUP分解。
	unsigned int max_index=0;
	for(unsigned int j=0;j!=n;++j){
		//2-1.Court算法第一步： 计算分解后上三角矩阵的值（不包括对角线）。
		for(unsigned int i=0;i!=j;++i){
			double temp=matrix.get_element(i,j);
			for(unsigned int k=0;k!=i;++k){
				temp-=matrix.get_element(i,k)*
					matrix.get_element(k,j);
			}
			matrix.set_element(i,j,temp);
		}
		//2-2.Court算法第二步： 计算上三角矩阵中只在对角线上的值以及下三角矩阵中所有的值。
		double big=0.0;
		for(unsigned int i=j;i!=n;++i){
			//2-2-1.计算上三角矩阵中只在对角线上的值以及下三角矩阵中所有的值。
			double temp=matrix.get_element(i,j);
			for(unsigned int k=0;k!=j;++k){
				temp-=matrix.get_element(i,k)*matrix.get_element(k,j);
			}
			matrix.set_element(i,j,temp);
			//2-2-2.计算最大值以及最大值所在行号。
			temp=maxes[i]*fabs(temp);
			if(temp>big){
				big=temp;
				max_index=i;
			}
		}
		//2-3.如果当前最大值并不再对角线上，则进行调整。
		if(max_index!=j){
			//2-3-1.声明当前操作所需变量。
			double temp=0.0;
			//2-3-2.交换矩阵行。
			for(unsigned int k=0;k!=n;++k){
				temp=matrix.get_element(max_index,k);
				matrix.set_element(max_index,k,matrix.get_element(j,k));
				matrix.set_element(j,k,temp);
			}
			//2-3-3.交换矩阵行的最大值。
			temp=maxes[max_index];
			maxes[max_index]=maxes[j];
			maxes[j]=temp;
		}
		//2-4.记录下当前最大值原始行号，在解线性方程组时，用来与结果矩阵对应。
		pi[j]=max_index;
		//2-5.计算分解后下矩阵的值。
		//2-5-1.如果矩阵当前列最大值为零，则矩阵奇异，不能进行分解。
		if(fabs(matrix.get_element(j,j))<TINY){//奇异矩阵判断。
			return(-2);
		}
		//2-5-2.计算除求下矩阵时所乘的系数。
		double temp=1.0/matrix.get_element(j,j);
		//2-5-3.将计算的下矩阵值写回原矩阵。
		for(unsigned int k=j+1;k!=n;++k){
			(matrix[k][j])*=temp;
		}
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: court_lup_solve
 * brief: 解线性方程组。
 * param: lup - 经过LUP分解的矩阵。
 *        pi - LUP分解过程中的π数组。
 *        result - 等式右侧的结果矩阵（这里一定是列向量），
 *                 计算的结果同时保存在这个矩阵中，并且将
 *                 矩阵原值覆盖。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSolvingEquations::court_lup_solve(const DMat &lup,const UVec &pi,DMat &result){
	//remark: 此时确保lup、pi、result满足解方程组的条件。
	//1.声明当前操作所需变量。
	const unsigned int n=lup.get_cols();
	//2.向前迭代过程实现。
	for(unsigned int i=0;i!=n;++i){
		//2-1.根据LU分解过程中的换行信息，调整结果矩阵的行。
		double temp=result.get_element(pi[i],0);
		result.set_element(pi[i],0,result.get_element(i,0));
		//2-2.如果当前并不是第一次循环。
		if(0!=i){
			for(unsigned int j=0;j!=i;++j){
				temp-=lup.get_element(i,j)*result.get_element(j,0);
			}
		}
		//2-3.将计算的结果放回到正确的位置。
		result.set_element(i,0,temp);
	}
	//3.向后迭代过程实现。
	for(unsigned int i=n-1;static_cast<long>(i)>=0;--i){
		double temp=result.get_element(i,0);
		for(unsigned int j=i+1;j!=n;++j){
			temp-=lup.get_element(i,j)*result.get_element(j,0);
		}
		//这里分母永远不可能为零，因为在分解阶段其值已经被保证不为零。
		result.set_element(i,0,temp/lup.get_element(i,i));
	}
	//3.程序运行到此成功返回。
	return(0);
}