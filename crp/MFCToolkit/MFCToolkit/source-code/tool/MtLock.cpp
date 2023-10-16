#include"stdafx.h"
#include"MtLock.h"

/**
 * name: MtLock
 * brief: ���캯�����ڴ˸����ʼ���ٽ�����
 * param: --
 * return: --
 */
MtLock::MtLock(void){
	InitializeCriticalSection(&_lock);
}

/**
 * name: ~MtLock
 * brief: �����������ڴ˸����ͷ��ٽ�����
 * param: --
 * return: --
 */
MtLock::~MtLock(void){
	DeleteCriticalSection(&_lock);
}

/**
 * name: lock
 * brief: �Ե�ǰ����������
 * param: --
 * return: --
 */
void MtLock::lock(){
	EnterCriticalSection(&_lock);
}

/**
 * name: unlock
 * brief: �Ե�ǰ����������
 * param: --
 * return: --
 */
void MtLock::unlock(){
	LeaveCriticalSection(&_lock);
}