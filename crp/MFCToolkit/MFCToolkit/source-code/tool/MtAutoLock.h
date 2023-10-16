#pragma once

/**
 * name: MtAutoLock
 * brief: �Զ������ڹ��캯����ʵ�ּ�����������������ʵ�ֽ�����
 * author: yameng_he
 * date: 2014-05-26
 */
template<typename _Tp>
class /*MFC_TOOLKIT_API*/ MtAutoLock{
//constructor & destructor
public:
	MtAutoLock(_Tp *lock);
	~MtAutoLock();
//restrict
private:
	MtAutoLock(const MtAutoLock &);
	MtAutoLock &operator=(const MtAutoLock &);
//variables
private:
	_Tp *_lock;
};

/**
 * name: MtAutoLock
 * brief: ���캯���������ʼ��������ָ�룬�Լ�����������
 * param: lock - ָ������ָ�롣
 * return: --
 */
template<typename _Tp>
MtAutoLock<_Tp>::MtAutoLock(_Tp *lock)
	:_lock(lock){
	if(0!=_lock){
		_lock->lock();
	}
}

/**
 * name: MtAutoLock
 * brief: �����������������������
 * param: --
 * return: --
 */
template<typename _Tp>
MtAutoLock<_Tp>::~MtAutoLock(){
	if(0!=_lock){
		_lock->unlock();
	}
}