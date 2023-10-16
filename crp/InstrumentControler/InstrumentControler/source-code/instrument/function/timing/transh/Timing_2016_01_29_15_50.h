#pragma once

#include<deque>

class SequenceDiagram;
class MtLock;

/**
 * name: Timing
 * brief: ʱ���࣬���������豸�������Թ��̵�ʱ����Ϣ��
 *        ��ά����ʱ����ص��������ݣ��ṩ��Ӧ������
 *        �ӿڡ�
 * author: yameng_he
 * date: 2015-12-30
 */
class Timing{
//define
public:
	enum{
		SEQUENCE_DIAGRAM_COUNT=360,
		TRIGGER_INTERVAL=1000,//ʱ�򴥷������
		TICKTACK=1,
		TIMING_CYCLE=30000,//ʱ���ʱ�����ڡ�
		THREAD_EXITING_TIMEOUT=5000,
	};
	typedef std::deque<int> Ticktacks;
//construction & destruction
public:
	Timing(void);
	~Timing(void);
//interface
public:
	int start();
	void stop();
//implement
private:
	static unsigned int __stdcall clock(void *parameter);
	static unsigned int __stdcall timing(void *parameter);
//implement
private:
	void clock();
	void timing();
	void add_ticktack();
	int pop_ticktack();
	void clear_all_ticktacks();
//restriction
private:
	Timing(const Timing &);
	Timing &operator=(const Timing &);
//variables
private:
	HANDLE _clock;
	HANDLE _timing;
	BOOL _is_cease;
	HANDLE _cease_event;
	MtLock *_lock;
	HANDLE _clock_event;
	Ticktacks _ticktacks;
};

