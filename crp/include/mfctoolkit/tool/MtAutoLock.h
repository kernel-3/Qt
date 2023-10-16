#pragma once

/**
 * name: MtAutoLock
 * brief: 自动锁，在构造函数中实现加锁，在析构函数中实现解锁。
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
 * brief: 构造函数，负责初始化锁对象指针，以及对锁加锁。
 * param: lock - 指向锁的指针。
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
 * brief: 析构函数，负责对锁解锁。
 * param: --
 * return: --
 */
template<typename _Tp>
MtAutoLock<_Tp>::~MtAutoLock(){
	if(0!=_lock){
		_lock->unlock();
	}
}