#pragma once

#include"Action.h"

/**
 * name: TakeTubeOutOfWashingDisc
 * breif: 转运抓手从清洗盘取管动作。
 * author: yameng_he
 * date: 2016-01-25.
 */
class TakeTubeOutOfWashingDisc
	:public Action{
//construction & destruction
public:
	TakeTubeOutOfWashingDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~TakeTubeOutOfWashingDisc(void);
//interface
public:
	void set_stop_position(const unsigned int stop_position);
	unsigned int get_stop_position() const;
//overrides
public:
	virtual int clear();
	virtual int reset();
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
//variables
private:
	unsigned int _stop_position;
};