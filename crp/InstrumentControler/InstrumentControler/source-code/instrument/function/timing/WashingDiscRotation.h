#pragma once

#include"Action.h"

/**
 * name: WashingDiscRotation
 * brief: 清洗盘旋转动作。
 * author: yameng_he
 * date: 2016-01-21.
 */
class WashingDiscRotation
	:public Action{
//construction & destruction
public:
	WashingDiscRotation(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~WashingDiscRotation(void);
//overrides
public:
	virtual int reset();
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
//variables
private:
	BOOL _rotation_flag;
};