#pragma once

#include"../Symbol"

/**
 * name: MtLock
 * brief: ���࣬����ʵ����Ӧ���еĸ��ֲ�����
 * author: yameng_he
 * date: 2014-05-26
 */
class MFC_TOOLKIT_API MtLock{
//constructor & destructor
public:
	MtLock(void);
	~MtLock(void);
//interface
public:
	void lock();
	void unlock();
//restrict
private:
	MtLock(const MtLock &);
	MtLock &operator=(const MtLock &);
//variables
private:
	CRITICAL_SECTION _lock;
};