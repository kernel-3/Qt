#pragma once

#include"../Function.h"

#include<memory>
#include<deque>
#include<map>

class MtLock;
class TestItem;

/**
 * name: Timing
 * brief: 时序功能类，负责实现设备的时序功能。
 * author: yameng_he
 * date: 2015-12-30
 */
class Timing
	:public Function{
//define
public:
	enum{
		SEQUENCE_DIAGRAM_COUNT=360,
		TRIGGER_INTERVAL=1000,
		TIMING_CYCLE=30000,
		THREAD_EXITING_TIMEOUT=5000,
		MAXIMUM_TEST_ITEM_KEY=30000000,
	};
	typedef std::shared_ptr<TestItem> PtrToTestItem;
	typedef std::deque<PtrToTestItem> PendingTestItemQueue;
	typedef std::map<unsigned int,PtrToTestItem> TestedItemMap;
//construction & destruction
public:
	Timing(void);
	~Timing(void);
//interface
public:
	int push_back_pending_test_item(const TestItem &test_item);
	PtrToTestItem get_tested_item(const unsigned int tested_item_key);
//overrides
public:
	virtual int start();
	virtual void stop();
//implement
private:
	static unsigned int __stdcall timing(void *parameter);
//implement
private:
	void timing();
	void set_timing_stopping_flag(const BOOL flag);
	BOOL get_timing_stopping_flag() const;
	PtrToTestItem pop_front_pending_test_item();
	int add_tested_item(PtrToTestItem &test_item);
//variables
private:
	static unsigned int _test_item_key;
//variables
private:
	HANDLE _timing;
	MtLock *_lock;
	BOOL _timing_stopping_flag;
	PendingTestItemQueue _pending_test_item_queue;
	TestedItemMap _tested_item_map;
};