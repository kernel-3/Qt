#pragma once

#include<assert.h>

/**
 * name: MtMatrixDataPtr
 * brief: 矩阵（行）数据指针封装类，用于封装矩阵的数据信息。
 *        为用户提供安全访问矩阵的数据接口。
 * author: yameng_he
 * date: 2014-09-23
 */
template<typename _Tp>
class MtMatrixDataPtr{
//constructor & destructor
public:
	explicit MtMatrixDataPtr(_Tp *data,const unsigned long size);
	MtMatrixDataPtr(const MtMatrixDataPtr &source);
	~MtMatrixDataPtr();
//interace
public:
	BOOL is_valid() const;
	_Tp &get(const unsigned long index);
	const _Tp &get(const unsigned long index) const;
	MtMatrixDataPtr &operator=(const MtMatrixDataPtr &source);
	_Tp &operator[](const unsigned long index);
	const _Tp &operator[](const unsigned long index) const;
//variables
private:
	_Tp *_data;
	unsigned long _size;
};

/**
 * name: MtMatrixDataPtr
 * brief: 构造函数。
 * param: data - 矩阵数据的起始地址。
 *        size - 矩阵数据的存储尺寸。
 * return: --
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::MtMatrixDataPtr(_Tp *data,const unsigned long size)
	:_data(data)
	,_size(size){
}

/**
 * name: MtMatrixDataPtr
 * brief: 拷贝构造函数。
 * param: source - 拷贝源。
 * return: -- 
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::MtMatrixDataPtr(const MtMatrixDataPtr &source)
	:_data(source._data)
	,_size(source._size){
}

/**
 * name: ~MtMatrixDataPtr
 * brief: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::~MtMatrixDataPtr(){
}

/**
 * name: is_valid
 * brief: 判断当前矩阵数据指针是否合法。
 * param: --
 * return: 如果当前矩阵数据指针合法，则返回true，否则返回false。
 */
template<typename _Tp>
BOOL MtMatrixDataPtr<_Tp>::is_valid() const{
	return((_data!=0)&&(_size>0));
}

/**
 * name: get
 * brief: 获取矩阵数据中的指定位置元素。
 * param: index - 矩阵数据中指定为位置。
 * return: 返回矩阵数据中指定位置元素引用。
 */
template<typename _Tp>
_Tp &MtMatrixDataPtr<_Tp>::get(const unsigned long index){
	assert((is_valid())&&(index>=0)&&(index<_size));
	return(_data[index]);
}

/**
 * name: get
 * brief: 获取矩阵数据中的指定位置元素。
 * param: index - 矩阵数据中指定为位置。
 * return: 返回矩阵数据中指定位置元素引用。
 */
template<typename _Tp>
const _Tp &MtMatrixDataPtr<_Tp>::get(const unsigned long index) const{
	return(const_cast<MtMatrixDataPtr*>(this)->get(index));
}

/**
 * name: operator=
 * brief: 赋值操作符重载。
 * param: source - 赋值源。
 * return: 返回当前类实例引用。
 * remark: 可以通过成员函数 is_valid 判断赋值操作是否成功。
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp> &MtMatrixDataPtr<_Tp>::operator=(const MtMatrixDataPtr &source){
	_data=source._data;
	_size=source._size;
	return(*this);
}

/**
 * name: operator[]
 * brief: 重载[]操作符号，提供下标访问功能。
 * param: index - 矩阵数据存储空间中的指定位置。
 * return: 返回当前矩阵指定位置的数据引用。
 */
template<typename _Tp>
_Tp &MtMatrixDataPtr<_Tp>::operator[](const unsigned long index){
	return(get(index));
}

/**
 * name: operator[]
 * brief: 重载[]操作符号，提供下标访问功能。
 * param: index - 矩阵数据存储空间中的指定位置。
 * return: 返回当前矩阵指定位置的数据引用。
 */
template<typename _Tp>
const _Tp &MtMatrixDataPtr<_Tp>::operator[](const unsigned long index) const{
	return(get(index));
}