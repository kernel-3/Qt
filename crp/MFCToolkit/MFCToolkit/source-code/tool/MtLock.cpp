#include"stdafx.h"
#include"MtLock.h"

/**
 * name: MtLock
 * brief: 构造函数，在此负责初始化临界区。
 * param: --
 * return: --
 */
MtLock::MtLock(void){
	InitializeCriticalSection(&_lock);
}

/**
 * name: ~MtLock
 * brief: 析构函数，在此负责释放临界区。
 * param: --
 * return: --
 */
MtLock::~MtLock(void){
	DeleteCriticalSection(&_lock);
}

/**
 * name: lock
 * brief: 对当前的锁加锁。
 * param: --
 * return: --
 */
void MtLock::lock(){
	EnterCriticalSection(&_lock);
}

/**
 * name: unlock
 * brief: 对当前的锁解锁。
 * param: --
 * return: --
 */
void MtLock::unlock(){
	LeaveCriticalSection(&_lock);
}