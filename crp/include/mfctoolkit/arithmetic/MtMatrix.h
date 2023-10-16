#pragma once

#include"MtMatrixDataPtr.h"

/**
 * name: MtMatrix
 * brief: 矩阵类，用来封装矩阵的全部操作。
 * author: yameng_he
 * date: 2014-09-09
 */
template<typename _Tp>
class MtMatrix{
//define
public:
	typedef MtMatrixDataPtr<_Tp> PtrToData;
//constructor & destructor
public:
	MtMatrix();
	explicit MtMatrix(const unsigned int rows,const unsigned int cols);
	MtMatrix(const MtMatrix &source);
	~MtMatrix();
//interface
public:
	BOOL is_valid() const;
	unsigned int get_rows() const;
	unsigned int get_cols() const;
	int create(const unsigned int rows,const unsigned int cols);
	void release();
	int zero();
	int copy(const MtMatrix &source);
	void set_element(const unsigned int row,const unsigned int col,const _Tp &value);
	_Tp &get_element(const unsigned int row,const unsigned int col);
	const _Tp &get_element(const unsigned int row,const unsigned int col) const;
	MtMatrix add(const _Tp &addend) const;
	int add(const _Tp &addend,MtMatrix &result) const;
	MtMatrix add(const MtMatrix &addend) const;
	int add(const MtMatrix &addend,MtMatrix &result) const;
	MtMatrix subtract(const _Tp &subtractor) const;
	int subtract(const _Tp &subtractor,MtMatrix &result) const;
	MtMatrix subtract(const MtMatrix &subtractor) const;
	int subtract(const MtMatrix &subtractor,MtMatrix &result) const;
	MtMatrix multiply(const _Tp &multiplier) const;
	int multiply(const _Tp &multiplier,MtMatrix &result) const;
	MtMatrix multiply(const MtMatrix &multiplier) const;
	int multiply(const MtMatrix &multiplier,MtMatrix &result) const;
	MtMatrix transpose() const;
	int transpose(MtMatrix &result) const;
	MtMatrix &operator=(const MtMatrix &source);
	PtrToData operator[](const unsigned int row);
	const PtrToData operator[](const unsigned int row) const;
	MtMatrix operator+(const _Tp &addend) const;
	MtMatrix operator+(const MtMatrix &addend) const;
	MtMatrix &operator+=(const _Tp &addend);
	MtMatrix &operator+=(const MtMatrix &addend);
	MtMatrix operator-(const _Tp &subtractor) const;
	MtMatrix operator-(const MtMatrix &subtractor) const;
	MtMatrix &operator-=(const _Tp &subtractor);
	MtMatrix &operator-=(const MtMatrix &subtractor);
	MtMatrix operator*(const _Tp &multiplier) const;
	MtMatrix operator*(const MtMatrix &multiplier) const;
	MtMatrix &operator*=(const _Tp &multiplier);
	MtMatrix &operator*=(const MtMatrix &multiplier);
//implement
private:
	unsigned int convert_to_index(const unsigned int row,
		const unsigned int col) const;
//variables
private:
	_Tp *_data;
	unsigned int _rows;
	unsigned int _cols;
};

/**
 * name: MtMatrix
 * brief: 构造函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtMatrix<_Tp>::MtMatrix()
	:_data(0)
	,_rows(0)
	,_cols(0){
}

/**
 * name: MtMatrix
 * brief: 构造函数。
 * param: rows - 行数。
 *        cols - 列数。
 * return: --
 * remark: 矩阵创建是否成功可以通过调用 is_valid 函数来判断。
 */
template<typename _Tp>
MtMatrix<_Tp>::MtMatrix(const unsigned int rows,const unsigned int cols)
	:_data(0)
	,_rows(0)
	,_cols(0){
	if(create(rows,cols)<0){
		assert(0);
	}
}

/**
 * name: MtMatrix
 * brief: 拷贝构造函数。
 * param: source - 源矩阵。
 * return: --
 * remark: 矩阵创建是否成功可以通过调用 is_valid 函数来判断。
 */
template<typename _Tp>
MtMatrix<_Tp>::MtMatrix(const MtMatrix &source)
	:_data(0)
	,_rows(0)
	,_cols(0){
	if(copy(source)<0){
		assert(0);
	}
}

/**
 * name: ~MtMatrix
 * brief: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtMatrix<_Tp>::~MtMatrix(){
	release();
}

/**
 * name: is_valid
 * brief: 判断当前矩阵是否有效。
 * param: --
 * return: 如果当前矩阵有效则返回true、否则返回false。
 */
template<typename _Tp>
BOOL MtMatrix<_Tp>::is_valid() const{
	return((_data!=0)&&(_rows>0)&&(_cols>0));
}

/**
 * name: get_rows
 * brief: 获取当前矩阵行数。
 * param: --
 * return: 返回当前矩阵行数。
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::get_rows() const{
	return(_rows);
}

/**
 * name: get_cols
 * brief: 获取当前矩阵列数。
 * param: --
 * return: 返回当前矩阵列数。
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::get_cols() const{
	return(_cols);
}

/**
 * name: create
 * brief: 根据给定的行、列数量创建一个矩阵。
 * param: rows - 行数。
 *        cols - 列数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::create(const unsigned int rows,const unsigned int cols){
	//1.判断当前传递的参数是否合法，如果不合法则直接返回错误。
	if((rows<=0)||(cols<=0)){
		return(-1);
	}
	//2.根据行、列数为矩阵创建数据，并且判断创建是否成功。
	//2-1.创建矩阵数据存储空间。
	_Tp *data=0;
	bool is_new=false;
	if((!is_valid())||((_rows*_cols)!=(rows*cols))){
		is_new=true;
		data=new _Tp[rows*cols];
	}else{
		data=_data;
	}
	//2-2.判断创建是否成功。
	if(0==data){
		return(-2);
	}
	//2-3.初始化空间中的数据。
	memset(data,0,rows*cols*sizeof(_Tp));
	//3.释放当前矩阵。
	if(is_new){
		release();
	}
	//4.设置当前矩阵相应标记变量。
	_data=data;
	_rows=rows;
	_cols=cols;
	//5.程序运行到此直接返回。
	return(0);
}

/**
 * name: release
 * brief: 释放当前矩阵，并且立即清理内存。
 * param: --
 * return: --
 */
template<typename _Tp>
void MtMatrix<_Tp>::release(){
	//1.如果当前矩阵有效，则进行矩阵释放操作。
	if(0!=_data){
		delete[] _data;
	}
	//2.重置当前矩阵类标记变量。
	_data=0;
	_rows=0;
	_cols=0;
}

/**
 * name: zero
 * brief: 将矩阵数据清零。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::zero(){
	//1.如果当前矩阵不合法，则直接返回错误编码。
	if(!is_valid()){
		return(-1);
	}
	//2.将当前矩阵数据清零。
	memset(_data,0,_rows*_cols*sizeof(_Tp));
	//3.程序运行到此，直接成功返回。
	return(0);
}

/**
 * name: copy
 * brief: 使当前矩阵从指定的矩阵中拷贝数据。
 * param: source - 源矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::copy(const MtMatrix &source){
	//1.如果源矩阵与当前矩阵为同一个矩阵。
	if(this==&source){
		return(0);
	}
	//2.如果当前传递的源矩阵无效，则直接返回错误。
	if(!source.is_valid()){
		return(-1);
	}
	//3.如果当前源矩阵有效，则将进行矩阵拷贝操作。
	else{
		//3-1.根据源矩阵的行、列数为矩阵创建数据，并且判断创建是否成功。
		//3-1-1.创建矩阵数据存储空间。
		_Tp *data=0;
		bool is_new=false;
		if((!is_valid())||((_rows*_cols)!=(
			source._rows*source._cols))){
			is_new=true;
			data=new _Tp[source._rows*source._cols];
		}else{
			data=_data;
		}
		//3-1-2.判断创建是否成功。
		if(0==data){
			return(-2);
		}
		//3-2.从源矩阵复制数据到当前矩阵。
		memcpy(data,source._data,source._rows*source._cols*sizeof(_Tp));
		//3-3.释放当前矩阵。
		if(is_new){
			release();
		}
		//3-4.设置矩阵相应变量。
		_data=data;
		_rows=source._rows;
		_cols=source._cols;
		//3-5.程序运行到此成功返回。
		return(0);
	}
}

/**
 * name: set_element
 * brief: 为矩阵指定位置赋值。
 * param: row - 行号。
 *        col - 列号。
 * return: --
 */
template<typename _Tp>
void MtMatrix<_Tp>::set_element(const unsigned int row,
	const unsigned int col,const _Tp &value){
	//1.断言当前矩阵是否合法。
	assert(is_valid());
	//2.断言参数传递是否合法。
	assert((row>=0)&&(row<_rows));
	assert((col>=0)&&(col<_cols));
	//3.为矩阵指定位置赋值。
	_data[convert_to_index(row,col)]=value;
}

/**
 * name: get_element
 * brief: 获取当前矩阵中指定位置元素。
 * param: row - 行号。
 *        col - 列号。
 * return: 返回当前矩阵中指定位置元素。
 */
template<typename _Tp>
_Tp &MtMatrix<_Tp>::get_element(
	const unsigned int row,const unsigned int col){
	//1.断言当前矩阵是否合法。
	assert(is_valid());
	//2.断言参数传递是否合法。
	assert((row>=0)&&(row<_rows));
	assert((col>=0)&&(col<_cols));
	//3.获取当前矩阵中指定位置元素，并且返回元素引用。
	return(_data[convert_to_index(row,col)]);
}

/**
 * name: get_element
 * brief: 获取当前矩阵中指定位置元素。
 * param: row - 行索引。
 *        col - 列索引。
 * return: 返回当前矩阵中指定位置元素。
 */
template<typename _Tp>
const _Tp &MtMatrix<_Tp>::get_element(
	const unsigned int row,const unsigned int col) const{
	return(const_cast<MtMatrix*>(this)->get_element(row,col));
}

/**
 * name: add
 * brief: 计算当前矩阵与指定值的加法运算。
 * param: addend - 加数。
 * return: 如果执行成功返回计算后的结果矩阵，否则返回空矩阵
 *		  （无效矩阵，可以通过矩阵类成员函数 is_valid 判断）。 
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::add(const _Tp &addend) const{
	//1.判断当前矩阵是否合法，如果不合法则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.创建结果矩阵，并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+addend);
		}
	}
	//4.程序运行到此直接返回结果矩阵。
	return(result);
}

/**
 * name: add
 * brief: 计算当前矩阵与指定值的加法运算。
 * param: addend - 加数。
 *        result - 计算后返回的结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::add(const _Tp &addend,MtMatrix &result) const{
	//1.判断当前矩阵是否有效，如果无效则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.创建结果矩阵，并且判断创建是否成功。
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+addend);
		}
	}
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: add
 * brief: 计算当前矩阵与指定矩阵的加法运算。
 * param: addend - 加数矩阵。
 * return: 如果函数执行成功则返回计算后的结果矩阵，否则返回空矩阵（
 *         无效矩阵，可以通过矩阵类成员函数is_valid判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::add(const MtMatrix &addend) const{
	//1.如果当前矩阵无效，则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.如果加数矩阵与当前矩阵不相容，则直接返回空矩阵。
	if((!addend.is_valid())||(_rows!=addend._rows)||
		(_cols!=addend._cols)){
		return(MtMatrix());
	}
	//3.创建结果矩阵，并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//4.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+
				addend.get_element(row,col));
		}
	}
	//5.返回计算成功后的结果矩阵。
	return(result);
}

/**
 * name: add
 * brief: 计算当前矩阵与指定矩阵的加法运算。
 * param: addend - 加数矩阵。
 *        result - 计算后返回的结果矩阵。
 * return： 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::add(const MtMatrix &addend,MtMatrix &result) const{
	//1.如果当前矩阵不合法，则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.如果当前加数矩阵与当前矩阵不相容，则直接返回错误。
	if((!addend.is_valid())||(_rows!=addend._rows)||
		(_cols!=addend._cols)){
		return(-2);
	}
	//3.创建结果矩阵，并且判断创建是否成功。
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-3);
		}
	}
	//4.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+
				addend.get_element(row,col));
		}
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: subtract
 * brief: 计算当前矩阵与指定值的减法运算。
 * param: subtractor - 减数。
 * return: 如果函数执行成功则返回计算后的结果矩阵，否则返回空矩阵（
 *         无效矩阵，可以通过矩阵类成员函数 is_valid 判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::subtract(const _Tp &subtractor) const{
	//1.如果当前矩阵无效，则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.创建结果矩阵,并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)-subtractor);
		}
	}
	//4.程序运行到此直接返回结果矩阵。
	return(result);
}

/**
 * name: subtract
 * brief: 计算当前矩阵与指定值的减法运算。
 * param: subtractor - 减数。
 *        result - 计算后返回的结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::subtract(const _Tp &subtractor,MtMatrix &result) const{
	//1.如果当前矩阵不合法，则直接返回错误信息。
	if(!is_valid()){
		return(-1);
	}
	//2.创建结果矩阵，并且判断创建是否成功。
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._row_number;++row){
		for(unsigned int col=0;col!=result._col_number;++col){
			result.set_element(row,col,get_element(row,col)-subtractor);
		}
	}
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: subtract
 * brief: 计算当前矩阵与指定矩阵的减法运算。
 * param: subtractor - 减数矩阵。
 * return: 如果函数执行成功则返回计算后的结果矩阵，否则返回空矩阵（
 *         无效矩阵，可以通过矩阵类成员函数is_valid判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::subtract(const MtMatrix &subtractor) const{
	//1.如果当前矩阵不合法，则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.如果减数矩阵与当前矩阵不相容，则直接返回空矩阵。
	if((!subtractor.is_valid())||(_rows!=subtractor._rows)||
		(_cols!=subtractor._cols)){
		return(MtMatrix());
	}
	//3.创建结果矩阵，并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//4.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)-
				subtractor.get_element(row,col));
		}
	}
	//5.返回计算成功后的结果矩阵。
	return(result);
}

/**
 * name: subtract
 * brief: 计算当前矩阵与指定矩阵的减法运算。
 * param: subtractor - 减数矩阵。
 *        result - 计算后返回的结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::subtract(const MtMatrix &subtractor,MtMatrix &result) const{
	//1.如果当前矩阵无效，则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.如果减数矩阵无效或与当前矩阵不相容,则直接返回错误。
	if((!subtractor.is_valid())||(_rows!=subtractor._rows)||
		(_cols!=subtractor._cols)){
		return(-2);
	}
	//3.创建结果矩阵，并且判断创建是否成功。
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-3);
		}
	}
	//4.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)-
				subtractor.get_element(row,col));
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: multiply
 * brief: 计算当前矩阵乘以一个数值的结果。
 * param: multiplier - 值。
 * return: 如果函数执行成功则返回计算后的结果矩阵，否则返回空矩阵（
 *         无效矩阵，可以通过矩阵类成员函数 is_valid 判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::multiply(const _Tp &multiplier) const{
	//1.如果当前矩阵不合法，则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.创建结果矩阵，并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)*multiplier);
		}
	}
	//4.程序运行到此直接返回结果矩阵。
	return(result);
}

/**
 * name: multiply
 * brief: 计算当前矩阵乘以一个数值的结果。
 * param: multiplier - 乘数。
 *        result - 计算后返回的结果矩阵。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。 
 */
template<typename _Tp>
int MtMatrix<_Tp>::multiply(const _Tp &multiplier,MtMatrix &result) const{
	//1.如果当前矩阵不合法，直接返回错误编码。
	if(!is_valid()){
		return(-1);
	}
	//2.创建结果矩阵，并且判断创建是否成功。
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.计算结果矩阵数据。
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)*multiplier);
		}
	}
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: multiply
 * brief: 计算当前矩阵乘以目标矩阵的值。
 * param: multiplier - 作为乘数的矩阵引用。
 * return: 如果函数执行成功则返回计算后的结果矩阵，否则返回空矩阵（
 *         无效矩阵，可以通过矩阵类成员函数is_valid判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::multiply(const MtMatrix &multiplier) const{
	//1.如果当前矩阵不合法，则直接返回无效矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.如果乘数矩阵不合法或与当前矩阵不相容，则直接返回无效矩阵。
	if((!multiplier.is_valid())||(_cols!=multiplier._rows)){
		return(MtMatrix());
	}
	//3.创建相乘结果存储矩阵，并且判断创建是否成功。
	MtMatrix result;
	if(result.create(_rows,multiplier._cols)<0){
		return(MtMatrix());
	}
	//4.计算相乘结果。
	for(unsigned int row=0;row!=_rows;++row){
		for(unsigned int col=0;col!=multiplier._cols;++col){
			_Tp sum=0;
			for(unsigned int index=0;index!=_cols;++index){
				sum+=get_element(row,index)*
					multiplier.get_element(index,col);
			}
			result.set_element(row,col,sum);
		}
	}
	//5.程序运行到此直接返回结果矩阵。
	return(result);
}

/**
 * name: multiply
 * brief: 计算当前矩阵乘以目标矩阵的值。
 * param: multiplier - 作为乘数的矩阵引用。
 *        result - 计算后返回的结果矩阵。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::multiply(const MtMatrix &multiplier,MtMatrix &result) const{
	//1.如果当前矩阵不合法，则直接返回错误编号。
	if(!is_valid()){
		return(-1);
	}
	//2.如果乘数矩阵不合法或与当前矩阵不相容，则直接返回错误编码。
	if((!multiplier.is_valid())||(_cols!=multiplier._rows)){
		return(-2);
	}
	//3.如果结果矩阵就是当前矩阵，则直接返回错误编码。
	if(this==&result){
		return(-3);
	}
	//4.创建结果矩阵，并且判断创建是否成功。
	if(result.create(_rows,multiplier._cols)<0){
		return(-4);
	}
	//5.计算相乘结果。
	for(unsigned int row=0;row!=_rows;++row){
		for(unsigned int col=0;col!=multiplier._cols;++col){
			_Tp sum=0;
			for(unsigned int index=0;index!=_cols;++index){
				sum+=get_element(row,index)*
					multiplier.get_element(index,col);
			}
			result.set_element(row,col,sum);
		}
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: transpose
 * brief: 计算当前矩阵的转置矩阵。
 * param: --
 * return: 如果函数执行成功则返回当前矩阵的转置矩阵，否则返回空矩阵（无效矩阵，
 *         用户可以通过矩阵成员函数 is_valid 来判断）。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::transpose() const{
	//1.判断当前矩阵是否合法，如果不合法则直接返回空矩阵。
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.创建转置矩阵，并且判断创建是否成功。
	MtMatrix transpose_matrix;
	if(transpose_matrix.create(_cols,_rows)<0){
		return(MtMatrix());
	}
	//3.计算设置转置矩阵的数据。
	for(unsigned int row=0;row!=transpose_matrix._rows;++row){
		for(unsigned int col=0;col!=transpose_matrix._cols;++col){
			transpose_matrix.set_element(row,col,get_element(col,row));
		}
	}
	//4.返回转置矩阵。
	return(transpose_matrix);
}

/**
 * name: transpose
 * brief: 计算当前矩阵的转置矩阵。
 * param: trans - 计算后返回的转置矩阵。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
template<typename _Tp>
int MtMatrix<_Tp>::transpose(MtMatrix &trans) const{
	//1.判断当前矩阵是否合法，如果不合法则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.如果转置矩阵就是当前矩阵，则直接返回错误。
	if(this==&trans){
		return(-2);
	}
	//3.创建转置矩阵，并且判断创建是否成功。
	if(trans.create(_cols,_rows)<0){
		return(-3);
	}
	//4.计算设置转置矩阵的数据。
	for(unsigned int row=0;row!=trans._rows;++row){
		for(unsigned int col=0;col!=trans._cols;++col){
			trans.set_element(row,col,get_element(col,row));
		}
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: operator=
 * brief: 重载等于操作符。
 * param: source - 源矩阵引用。
 * return: 返回矩阵引用。
 * remark: 可以通过 is_valid 成员函数，查看矩阵赋值是否成功。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator=(const MtMatrix &source){
	if(copy(source)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator[]
 * brief: 重载[]操作符。
 * param: row - 行号。
 * return: 返回矩阵中指定行的数组智能指针。
 */
template<typename _Tp>
typename MtMatrix<_Tp>::PtrToData MtMatrix<_Tp>::operator[](
	const unsigned int row){
	//1.确保当前矩阵有效。
	assert(is_valid());
	//2.确保当前传递参数合法。
	assert((row>=0)&&(row<_rows));
	//3.返回矩阵中指定数组引用。
	return(PtrToData(_data+row*_cols,_cols));
}

/**
 * name: operator[]
 * brief: 重载[]操作符。
 * param: row - 行号。
 * return: 返回矩阵中指定行的数组智能指针。
 */
template<typename _Tp>
const typename MtMatrix<_Tp>::PtrToData MtMatrix<_Tp>::operator[](
	const unsigned int row) const{
	return(const_cast<MtMatrix*>(this)->operator[](row));
}

/**
 * name: operator+
 * brief: 重载+操作符。
 * param: addend - 加数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator+(const _Tp &addend) const{
	return(add(addend));
}

/**
 * name: operator+
 * brief: 重载+操作符。
 * param: addend - 加数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator+(const MtMatrix &addend) const{
	return(add(addend));
}

/**
 * name: operator+=
 * brief: 重载+=操作符。
 * param: addend - 加数。
 * return: 返回计算后的自身引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator+=(const _Tp &addend){
	if(add(addend,*this)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator+=
 * brief: 重载+=操作符。
 * param: addend - 加数。
 * return: 返回计算后的自身引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator+=(const MtMatrix &addend){
	if(add(addend,*this)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator-
 * brief: 重载-操作符。
 * param: subtractor - 减数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator-(const _Tp &subtractor) const{
	return(subtract(subtractor));
}

/**
 * name: operator-
 * brief: 重载-操作符。
 * param: subtractor - 减数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator-(const MtMatrix &subtractor) const{
	return(subtract(subtractor));
}

/**
 * name: operator-=
 * brief: 重载-=操作符。
 * param: subtractor - 减数。
 * return: 返回计算后的自身引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator-=(const _Tp &subtractor){
	if(subtract(subtractor,*this)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator-=
 * brief: 重载-=操作符。
 * param: subtractor - 减数。
 * return: 返回计算后的自身引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator-=(const MtMatrix &subtractor){
	if(subtract(subtractor,*this)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator*
 * brief: 重载*操作符。
 * param: multiplier - 乘数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator*(const _Tp &multiplier) const{
	return(multiply(multiplier));
}

/**
 * name: operator*
 * brief: 重载*操作符。
 * param: multiplier - 乘数。
 * return: 返回计算后的结果矩阵。
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator*(const MtMatrix &multiplier) const{
	return(multiply(multiplier));
}

/**
 * name: operator*=
 * brief: 重载*=操作符。
 * param: multiplier - 乘数。
 * return: 返回计算后的自身矩阵引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator*=(const _Tp &multiplier){
	if(multiply(multiplier,*this)<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: operator*=
 * brief: 重载*=操作符。
 * param: multiplier - 乘数。
 * return: 返回计算后的自身矩阵引用。
 */
template<typename _Tp>
MtMatrix<_Tp> &MtMatrix<_Tp>::operator*=(const MtMatrix &multiplier){
	if(copy(multiply(multiplier))<0){
		assert(0);
	}
	return(*this);
}

/**
 * name: convert_to_index
 * brief: 将行、列转换为矩阵数据数组的下标值。
 * param: row - 行号。
 *        col - 列号。
 * return: 返回根据行、列号计算得出的下标值。
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::convert_to_index(
	const unsigned int row,const unsigned int col) const{
	return(row*_cols+col);
}