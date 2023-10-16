#pragma once

#include"MtMatrixDataPtr.h"

/**
 * name: MtMatrix
 * brief: �����࣬������װ�����ȫ��������
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
 * brief: ���캯����
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
 * brief: ���캯����
 * param: rows - ������
 *        cols - ������
 * return: --
 * remark: ���󴴽��Ƿ�ɹ�����ͨ������ is_valid �������жϡ�
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
 * brief: �������캯����
 * param: source - Դ����
 * return: --
 * remark: ���󴴽��Ƿ�ɹ�����ͨ������ is_valid �������жϡ�
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
 * brief: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtMatrix<_Tp>::~MtMatrix(){
	release();
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�����Ƿ���Ч��
 * param: --
 * return: �����ǰ������Ч�򷵻�true�����򷵻�false��
 */
template<typename _Tp>
BOOL MtMatrix<_Tp>::is_valid() const{
	return((_data!=0)&&(_rows>0)&&(_cols>0));
}

/**
 * name: get_rows
 * brief: ��ȡ��ǰ����������
 * param: --
 * return: ���ص�ǰ����������
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::get_rows() const{
	return(_rows);
}

/**
 * name: get_cols
 * brief: ��ȡ��ǰ����������
 * param: --
 * return: ���ص�ǰ����������
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::get_cols() const{
	return(_cols);
}

/**
 * name: create
 * brief: ���ݸ������С�����������һ������
 * param: rows - ������
 *        cols - ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::create(const unsigned int rows,const unsigned int cols){
	//1.�жϵ�ǰ���ݵĲ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if((rows<=0)||(cols<=0)){
		return(-1);
	}
	//2.�����С�����Ϊ���󴴽����ݣ������жϴ����Ƿ�ɹ���
	//2-1.�����������ݴ洢�ռ䡣
	_Tp *data=0;
	bool is_new=false;
	if((!is_valid())||((_rows*_cols)!=(rows*cols))){
		is_new=true;
		data=new _Tp[rows*cols];
	}else{
		data=_data;
	}
	//2-2.�жϴ����Ƿ�ɹ���
	if(0==data){
		return(-2);
	}
	//2-3.��ʼ���ռ��е����ݡ�
	memset(data,0,rows*cols*sizeof(_Tp));
	//3.�ͷŵ�ǰ����
	if(is_new){
		release();
	}
	//4.���õ�ǰ������Ӧ��Ǳ�����
	_data=data;
	_rows=rows;
	_cols=cols;
	//5.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: release
 * brief: �ͷŵ�ǰ���󣬲������������ڴ档
 * param: --
 * return: --
 */
template<typename _Tp>
void MtMatrix<_Tp>::release(){
	//1.�����ǰ������Ч������о����ͷŲ�����
	if(0!=_data){
		delete[] _data;
	}
	//2.���õ�ǰ�������Ǳ�����
	_data=0;
	_rows=0;
	_cols=0;
}

/**
 * name: zero
 * brief: �������������㡣
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::zero(){
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ش�����롣
	if(!is_valid()){
		return(-1);
	}
	//2.����ǰ�����������㡣
	memset(_data,0,_rows*_cols*sizeof(_Tp));
	//3.�������е��ˣ�ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: copy
 * brief: ʹ��ǰ�����ָ���ľ����п������ݡ�
 * param: source - Դ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::copy(const MtMatrix &source){
	//1.���Դ�����뵱ǰ����Ϊͬһ������
	if(this==&source){
		return(0);
	}
	//2.�����ǰ���ݵ�Դ������Ч����ֱ�ӷ��ش���
	if(!source.is_valid()){
		return(-1);
	}
	//3.�����ǰԴ������Ч���򽫽��о��󿽱�������
	else{
		//3-1.����Դ������С�����Ϊ���󴴽����ݣ������жϴ����Ƿ�ɹ���
		//3-1-1.�����������ݴ洢�ռ䡣
		_Tp *data=0;
		bool is_new=false;
		if((!is_valid())||((_rows*_cols)!=(
			source._rows*source._cols))){
			is_new=true;
			data=new _Tp[source._rows*source._cols];
		}else{
			data=_data;
		}
		//3-1-2.�жϴ����Ƿ�ɹ���
		if(0==data){
			return(-2);
		}
		//3-2.��Դ���������ݵ���ǰ����
		memcpy(data,source._data,source._rows*source._cols*sizeof(_Tp));
		//3-3.�ͷŵ�ǰ����
		if(is_new){
			release();
		}
		//3-4.���þ�����Ӧ������
		_data=data;
		_rows=source._rows;
		_cols=source._cols;
		//3-5.�������е��˳ɹ����ء�
		return(0);
	}
}

/**
 * name: set_element
 * brief: Ϊ����ָ��λ�ø�ֵ��
 * param: row - �кš�
 *        col - �кš�
 * return: --
 */
template<typename _Tp>
void MtMatrix<_Tp>::set_element(const unsigned int row,
	const unsigned int col,const _Tp &value){
	//1.���Ե�ǰ�����Ƿ�Ϸ���
	assert(is_valid());
	//2.���Բ��������Ƿ�Ϸ���
	assert((row>=0)&&(row<_rows));
	assert((col>=0)&&(col<_cols));
	//3.Ϊ����ָ��λ�ø�ֵ��
	_data[convert_to_index(row,col)]=value;
}

/**
 * name: get_element
 * brief: ��ȡ��ǰ������ָ��λ��Ԫ�ء�
 * param: row - �кš�
 *        col - �кš�
 * return: ���ص�ǰ������ָ��λ��Ԫ�ء�
 */
template<typename _Tp>
_Tp &MtMatrix<_Tp>::get_element(
	const unsigned int row,const unsigned int col){
	//1.���Ե�ǰ�����Ƿ�Ϸ���
	assert(is_valid());
	//2.���Բ��������Ƿ�Ϸ���
	assert((row>=0)&&(row<_rows));
	assert((col>=0)&&(col<_cols));
	//3.��ȡ��ǰ������ָ��λ��Ԫ�أ����ҷ���Ԫ�����á�
	return(_data[convert_to_index(row,col)]);
}

/**
 * name: get_element
 * brief: ��ȡ��ǰ������ָ��λ��Ԫ�ء�
 * param: row - ��������
 *        col - ��������
 * return: ���ص�ǰ������ָ��λ��Ԫ�ء�
 */
template<typename _Tp>
const _Tp &MtMatrix<_Tp>::get_element(
	const unsigned int row,const unsigned int col) const{
	return(const_cast<MtMatrix*>(this)->get_element(row,col));
}

/**
 * name: add
 * brief: ���㵱ǰ������ָ��ֵ�ļӷ����㡣
 * param: addend - ������
 * return: ���ִ�гɹ����ؼ����Ľ�����󣬷��򷵻ؿվ���
 *		  ����Ч���󣬿���ͨ���������Ա���� is_valid �жϣ��� 
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::add(const _Tp &addend) const{
	//1.�жϵ�ǰ�����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.����������󣬲����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+addend);
		}
	}
	//4.�������е���ֱ�ӷ��ؽ������
	return(result);
}

/**
 * name: add
 * brief: ���㵱ǰ������ָ��ֵ�ļӷ����㡣
 * param: addend - ������
 *        result - ����󷵻صĽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::add(const _Tp &addend,MtMatrix &result) const{
	//1.�жϵ�ǰ�����Ƿ���Ч�������Ч��ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.����������󣬲����жϴ����Ƿ�ɹ���
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+addend);
		}
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: add
 * brief: ���㵱ǰ������ָ������ļӷ����㡣
 * param: addend - ��������
 * return: �������ִ�гɹ��򷵻ؼ����Ľ�����󣬷��򷵻ؿվ���
 *         ��Ч���󣬿���ͨ���������Ա����is_valid�жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::add(const MtMatrix &addend) const{
	//1.�����ǰ������Ч����ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.������������뵱ǰ�������ݣ���ֱ�ӷ��ؿվ���
	if((!addend.is_valid())||(_rows!=addend._rows)||
		(_cols!=addend._cols)){
		return(MtMatrix());
	}
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//4.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+
				addend.get_element(row,col));
		}
	}
	//5.���ؼ���ɹ���Ľ������
	return(result);
}

/**
 * name: add
 * brief: ���㵱ǰ������ָ������ļӷ����㡣
 * param: addend - ��������
 *        result - ����󷵻صĽ������
 * return�� �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::add(const MtMatrix &addend,MtMatrix &result) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.�����ǰ���������뵱ǰ�������ݣ���ֱ�ӷ��ش���
	if((!addend.is_valid())||(_rows!=addend._rows)||
		(_cols!=addend._cols)){
		return(-2);
	}
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-3);
		}
	}
	//4.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)+
				addend.get_element(row,col));
		}
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: subtract
 * brief: ���㵱ǰ������ָ��ֵ�ļ������㡣
 * param: subtractor - ������
 * return: �������ִ�гɹ��򷵻ؼ����Ľ�����󣬷��򷵻ؿվ���
 *         ��Ч���󣬿���ͨ���������Ա���� is_valid �жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::subtract(const _Tp &subtractor) const{
	//1.�����ǰ������Ч����ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.�����������,�����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)-subtractor);
		}
	}
	//4.�������е���ֱ�ӷ��ؽ������
	return(result);
}

/**
 * name: subtract
 * brief: ���㵱ǰ������ָ��ֵ�ļ������㡣
 * param: subtractor - ������
 *        result - ����󷵻صĽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::subtract(const _Tp &subtractor,MtMatrix &result) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ش�����Ϣ��
	if(!is_valid()){
		return(-1);
	}
	//2.����������󣬲����жϴ����Ƿ�ɹ���
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._row_number;++row){
		for(unsigned int col=0;col!=result._col_number;++col){
			result.set_element(row,col,get_element(row,col)-subtractor);
		}
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: subtract
 * brief: ���㵱ǰ������ָ������ļ������㡣
 * param: subtractor - ��������
 * return: �������ִ�гɹ��򷵻ؼ����Ľ�����󣬷��򷵻ؿվ���
 *         ��Ч���󣬿���ͨ���������Ա����is_valid�жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::subtract(const MtMatrix &subtractor) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.������������뵱ǰ�������ݣ���ֱ�ӷ��ؿվ���
	if((!subtractor.is_valid())||(_rows!=subtractor._rows)||
		(_cols!=subtractor._cols)){
		return(MtMatrix());
	}
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//4.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)-
				subtractor.get_element(row,col));
		}
	}
	//5.���ؼ���ɹ���Ľ������
	return(result);
}

/**
 * name: subtract
 * brief: ���㵱ǰ������ָ������ļ������㡣
 * param: subtractor - ��������
 *        result - ����󷵻صĽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::subtract(const MtMatrix &subtractor,MtMatrix &result) const{
	//1.�����ǰ������Ч����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.�������������Ч���뵱ǰ��������,��ֱ�ӷ��ش���
	if((!subtractor.is_valid())||(_rows!=subtractor._rows)||
		(_cols!=subtractor._cols)){
		return(-2);
	}
	//3.����������󣬲����жϴ����Ƿ�ɹ���
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-3);
		}
	}
	//4.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,get_element(row,col)-
				subtractor.get_element(row,col));
		}
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: multiply
 * brief: ���㵱ǰ�������һ����ֵ�Ľ����
 * param: multiplier - ֵ��
 * return: �������ִ�гɹ��򷵻ؼ����Ľ�����󣬷��򷵻ؿվ���
 *         ��Ч���󣬿���ͨ���������Ա���� is_valid �жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::multiply(const _Tp &multiplier) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.����������󣬲����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,_cols)<0){
		return(MtMatrix());
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)*multiplier);
		}
	}
	//4.�������е���ֱ�ӷ��ؽ������
	return(result);
}

/**
 * name: multiply
 * brief: ���㵱ǰ�������һ����ֵ�Ľ����
 * param: multiplier - ������
 *        result - ����󷵻صĽ������
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣 
 */
template<typename _Tp>
int MtMatrix<_Tp>::multiply(const _Tp &multiplier,MtMatrix &result) const{
	//1.�����ǰ���󲻺Ϸ���ֱ�ӷ��ش�����롣
	if(!is_valid()){
		return(-1);
	}
	//2.����������󣬲����жϴ����Ƿ�ɹ���
	if((!result.is_valid())||(_rows!=result.get_rows())||
		(_cols!=result.get_cols())){
		if(result.create(_rows,_cols)<0){
			return(-2);
		}
	}
	//3.�������������ݡ�
	for(unsigned int row=0;row!=result._rows;++row){
		for(unsigned int col=0;col!=result._cols;++col){
			result.set_element(row,col,
				get_element(row,col)*multiplier);
		}
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: multiply
 * brief: ���㵱ǰ�������Ŀ������ֵ��
 * param: multiplier - ��Ϊ�����ľ������á�
 * return: �������ִ�гɹ��򷵻ؼ����Ľ�����󣬷��򷵻ؿվ���
 *         ��Ч���󣬿���ͨ���������Ա����is_valid�жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::multiply(const MtMatrix &multiplier) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ�����Ч����
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.����������󲻺Ϸ����뵱ǰ�������ݣ���ֱ�ӷ�����Ч����
	if((!multiplier.is_valid())||(_cols!=multiplier._rows)){
		return(MtMatrix());
	}
	//3.������˽���洢���󣬲����жϴ����Ƿ�ɹ���
	MtMatrix result;
	if(result.create(_rows,multiplier._cols)<0){
		return(MtMatrix());
	}
	//4.������˽����
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
	//5.�������е���ֱ�ӷ��ؽ������
	return(result);
}

/**
 * name: multiply
 * brief: ���㵱ǰ�������Ŀ������ֵ��
 * param: multiplier - ��Ϊ�����ľ������á�
 *        result - ����󷵻صĽ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::multiply(const MtMatrix &multiplier,MtMatrix &result) const{
	//1.�����ǰ���󲻺Ϸ�����ֱ�ӷ��ش����š�
	if(!is_valid()){
		return(-1);
	}
	//2.����������󲻺Ϸ����뵱ǰ�������ݣ���ֱ�ӷ��ش�����롣
	if((!multiplier.is_valid())||(_cols!=multiplier._rows)){
		return(-2);
	}
	//3.������������ǵ�ǰ������ֱ�ӷ��ش�����롣
	if(this==&result){
		return(-3);
	}
	//4.����������󣬲����жϴ����Ƿ�ɹ���
	if(result.create(_rows,multiplier._cols)<0){
		return(-4);
	}
	//5.������˽����
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
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: transpose
 * brief: ���㵱ǰ�����ת�þ���
 * param: --
 * return: �������ִ�гɹ��򷵻ص�ǰ�����ת�þ��󣬷��򷵻ؿվ�����Ч����
 *         �û�����ͨ�������Ա���� is_valid ���жϣ���
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::transpose() const{
	//1.�жϵ�ǰ�����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ؿվ���
	if(!is_valid()){
		return(MtMatrix());
	}
	//2.����ת�þ��󣬲����жϴ����Ƿ�ɹ���
	MtMatrix transpose_matrix;
	if(transpose_matrix.create(_cols,_rows)<0){
		return(MtMatrix());
	}
	//3.��������ת�þ�������ݡ�
	for(unsigned int row=0;row!=transpose_matrix._rows;++row){
		for(unsigned int col=0;col!=transpose_matrix._cols;++col){
			transpose_matrix.set_element(row,col,get_element(col,row));
		}
	}
	//4.����ת�þ���
	return(transpose_matrix);
}

/**
 * name: transpose
 * brief: ���㵱ǰ�����ת�þ���
 * param: trans - ����󷵻ص�ת�þ���
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
template<typename _Tp>
int MtMatrix<_Tp>::transpose(MtMatrix &trans) const{
	//1.�жϵ�ǰ�����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.���ת�þ�����ǵ�ǰ������ֱ�ӷ��ش���
	if(this==&trans){
		return(-2);
	}
	//3.����ת�þ��󣬲����жϴ����Ƿ�ɹ���
	if(trans.create(_cols,_rows)<0){
		return(-3);
	}
	//4.��������ת�þ�������ݡ�
	for(unsigned int row=0;row!=trans._rows;++row){
		for(unsigned int col=0;col!=trans._cols;++col){
			trans.set_element(row,col,get_element(col,row));
		}
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: operator=
 * brief: ���ص��ڲ�������
 * param: source - Դ�������á�
 * return: ���ؾ������á�
 * remark: ����ͨ�� is_valid ��Ա�������鿴����ֵ�Ƿ�ɹ���
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
 * brief: ����[]��������
 * param: row - �кš�
 * return: ���ؾ�����ָ���е���������ָ�롣
 */
template<typename _Tp>
typename MtMatrix<_Tp>::PtrToData MtMatrix<_Tp>::operator[](
	const unsigned int row){
	//1.ȷ����ǰ������Ч��
	assert(is_valid());
	//2.ȷ����ǰ���ݲ����Ϸ���
	assert((row>=0)&&(row<_rows));
	//3.���ؾ�����ָ���������á�
	return(PtrToData(_data+row*_cols,_cols));
}

/**
 * name: operator[]
 * brief: ����[]��������
 * param: row - �кš�
 * return: ���ؾ�����ָ���е���������ָ�롣
 */
template<typename _Tp>
const typename MtMatrix<_Tp>::PtrToData MtMatrix<_Tp>::operator[](
	const unsigned int row) const{
	return(const_cast<MtMatrix*>(this)->operator[](row));
}

/**
 * name: operator+
 * brief: ����+��������
 * param: addend - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator+(const _Tp &addend) const{
	return(add(addend));
}

/**
 * name: operator+
 * brief: ����+��������
 * param: addend - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator+(const MtMatrix &addend) const{
	return(add(addend));
}

/**
 * name: operator+=
 * brief: ����+=��������
 * param: addend - ������
 * return: ���ؼ������������á�
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
 * brief: ����+=��������
 * param: addend - ������
 * return: ���ؼ������������á�
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
 * brief: ����-��������
 * param: subtractor - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator-(const _Tp &subtractor) const{
	return(subtract(subtractor));
}

/**
 * name: operator-
 * brief: ����-��������
 * param: subtractor - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator-(const MtMatrix &subtractor) const{
	return(subtract(subtractor));
}

/**
 * name: operator-=
 * brief: ����-=��������
 * param: subtractor - ������
 * return: ���ؼ������������á�
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
 * brief: ����-=��������
 * param: subtractor - ������
 * return: ���ؼ������������á�
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
 * brief: ����*��������
 * param: multiplier - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator*(const _Tp &multiplier) const{
	return(multiply(multiplier));
}

/**
 * name: operator*
 * brief: ����*��������
 * param: multiplier - ������
 * return: ���ؼ����Ľ������
 */
template<typename _Tp>
MtMatrix<_Tp> MtMatrix<_Tp>::operator*(const MtMatrix &multiplier) const{
	return(multiply(multiplier));
}

/**
 * name: operator*=
 * brief: ����*=��������
 * param: multiplier - ������
 * return: ���ؼ���������������á�
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
 * brief: ����*=��������
 * param: multiplier - ������
 * return: ���ؼ���������������á�
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
 * brief: ���С���ת��Ϊ��������������±�ֵ��
 * param: row - �кš�
 *        col - �кš�
 * return: ���ظ����С��кż���ó����±�ֵ��
 */
template<typename _Tp>
unsigned int MtMatrix<_Tp>::convert_to_index(
	const unsigned int row,const unsigned int col) const{
	return(row*_cols+col);
}