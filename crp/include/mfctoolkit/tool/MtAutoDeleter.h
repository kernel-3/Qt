#pragma once

/**
 * name: MtAutoDeleter
 * breif: �Զ�ɾ������ʵ���Զ����ָ������ָ�룬
 *        ͬʱ�ͷ�ָ��ָ�����Դ��
 * author: yameng_he
 * date: 2015-12-30.
 */
template<typename _Tp>
class /*MFC_TOOLKIT_API*/ MtAutoDeleter{
//define
public:
	typedef enum{POINTER_TYPE_NORMAL,POINTER_TYPE_ARRAY,}PointerType;
//construcion & destruction
public:
	MtAutoDeleter(_Tp *pointer,const PointerType 
		pointer_type=POINTER_TYPE_NORMAL);
	~MtAutoDeleter();
//restriction
private:
	MtAutoDeleter(const MtAutoDeleter &);
	MtAutoDeleter &operator=(const MtAutoDeleter &);
//variables
private:
	_Tp *_pointer;
	PointerType _pointer_type;
};

/**
 * name: MtArrayDeleter
 * breif: ���캯����
 * param: pointer - �����ָ�롣
 *        pointer_type - �����ָ�����͡�
 * return: --
 */
template<typename _Tp>
MtAutoDeleter<_Tp>::MtAutoDeleter(_Tp *pointer,
	const PointerType pointer_type/*=POINTER_TYPE_NORMAL*/)
	:_pointer(pointer)
	,_pointer_type(pointer_type){
}

/**
 * name: ~MtArrayDeleter
 * breif: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtAutoDeleter<_Tp>::~MtAutoDeleter(){
	if(0!=_pointer){
		if(POINTER_TYPE_NORMAL==_pointer_type){
			delete _pointer;
		}else if(POINTER_TYPE_ARRAY==_pointer_type){
			delete[] _pointer;
		}
	}
}