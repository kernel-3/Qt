#pragma once

#include<memory>

class MtLock;

/**
 * name: Component
 * breif: 设备组件类，它是设备全部组件的基类。
 * auhtor: yameng_he
 * date: 2016-01-27.
 */
class Component{
//define
public:
	enum{ANSWER_TIMEOUT=500,};
	typedef std::auto_ptr<MtLock> Lock;
	typedef enum{FLAG_IDLE,FLAG_BUSY,FLAG_UNKNOWN,FLAGE_EMPTY,FLAGE_USED,}Flag;
//construction & destruction
public:
	Component(void);
	virtual ~Component(void)=0;
//interface
protected:
	static MtLock *get_control_lock();
//restriction
private:
	Component(const Component &);
	Component &operator=(const Component &);
//variables
private:
	static Lock _control_lock;
};