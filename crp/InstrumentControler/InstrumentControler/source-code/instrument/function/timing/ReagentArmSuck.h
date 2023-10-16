#pragma once

#include"Action.h"

/**
 * name: ReagentArmSuck
 * brief: ÊÔ¼Á±ÛÎüÒº¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-13.
 */
class ReagentArmSuck
	:public Action{
//construction & destruction
public:
	ReagentArmSuck(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~ReagentArmSuck(void);
//interface
public:
	void set_suck_volume(const unsigned int volume);
	unsigned int get_suck_volume() const;
	void set_reagent_type(const unsigned int type);
	unsigned int get_reagent_type() const;
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
	unsigned int _suck_volume;
	unsigned int _reagent_type;
};