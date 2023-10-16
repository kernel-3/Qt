#pragma once

#include<assert.h>

/**
 * name: MtMatrixDataPtr
 * brief: �����У�����ָ���װ�࣬���ڷ�װ�����������Ϣ��
 *        Ϊ�û��ṩ��ȫ���ʾ�������ݽӿڡ�
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
 * brief: ���캯����
 * param: data - �������ݵ���ʼ��ַ��
 *        size - �������ݵĴ洢�ߴ硣
 * return: --
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::MtMatrixDataPtr(_Tp *data,const unsigned long size)
	:_data(data)
	,_size(size){
}

/**
 * name: MtMatrixDataPtr
 * brief: �������캯����
 * param: source - ����Դ��
 * return: -- 
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::MtMatrixDataPtr(const MtMatrixDataPtr &source)
	:_data(source._data)
	,_size(source._size){
}

/**
 * name: ~MtMatrixDataPtr
 * brief: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp>::~MtMatrixDataPtr(){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��������ָ���Ƿ�Ϸ���
 * param: --
 * return: �����ǰ��������ָ��Ϸ����򷵻�true�����򷵻�false��
 */
template<typename _Tp>
BOOL MtMatrixDataPtr<_Tp>::is_valid() const{
	return((_data!=0)&&(_size>0));
}

/**
 * name: get
 * brief: ��ȡ���������е�ָ��λ��Ԫ�ء�
 * param: index - ����������ָ��Ϊλ�á�
 * return: ���ؾ���������ָ��λ��Ԫ�����á�
 */
template<typename _Tp>
_Tp &MtMatrixDataPtr<_Tp>::get(const unsigned long index){
	assert((is_valid())&&(index>=0)&&(index<_size));
	return(_data[index]);
}

/**
 * name: get
 * brief: ��ȡ���������е�ָ��λ��Ԫ�ء�
 * param: index - ����������ָ��Ϊλ�á�
 * return: ���ؾ���������ָ��λ��Ԫ�����á�
 */
template<typename _Tp>
const _Tp &MtMatrixDataPtr<_Tp>::get(const unsigned long index) const{
	return(const_cast<MtMatrixDataPtr*>(this)->get(index));
}

/**
 * name: operator=
 * brief: ��ֵ���������ء�
 * param: source - ��ֵԴ��
 * return: ���ص�ǰ��ʵ�����á�
 * remark: ����ͨ����Ա���� is_valid �жϸ�ֵ�����Ƿ�ɹ���
 */
template<typename _Tp>
MtMatrixDataPtr<_Tp> &MtMatrixDataPtr<_Tp>::operator=(const MtMatrixDataPtr &source){
	_data=source._data;
	_size=source._size;
	return(*this);
}

/**
 * name: operator[]
 * brief: ����[]�������ţ��ṩ�±���ʹ��ܡ�
 * param: index - �������ݴ洢�ռ��е�ָ��λ�á�
 * return: ���ص�ǰ����ָ��λ�õ��������á�
 */
template<typename _Tp>
_Tp &MtMatrixDataPtr<_Tp>::operator[](const unsigned long index){
	return(get(index));
}

/**
 * name: operator[]
 * brief: ����[]�������ţ��ṩ�±���ʹ��ܡ�
 * param: index - �������ݴ洢�ռ��е�ָ��λ�á�
 * return: ���ص�ǰ����ָ��λ�õ��������á�
 */
template<typename _Tp>
const _Tp &MtMatrixDataPtr<_Tp>::operator[](const unsigned long index) const{
	return(get(index));
}