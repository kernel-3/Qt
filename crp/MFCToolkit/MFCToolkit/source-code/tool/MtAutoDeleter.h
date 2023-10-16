#pragma once

/**
 * name: MtAutoDeleter
 * breif: 自动删除器，实现自动清除指定类型指针，
 *        同时释放指针指向的资源。
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
 * breif: 构造函数。
 * param: pointer - 输入的指针。
 *        pointer_type - 输入的指针类型。
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
 * breif: 析构函数。
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