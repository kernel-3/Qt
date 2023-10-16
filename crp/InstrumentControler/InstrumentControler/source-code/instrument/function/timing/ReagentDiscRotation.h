#pragma once

#include"Action.h"

/**
 * name: ReagentDiscRotation
 * brief: ÊÔ¼ÁÅÌÐý×ª¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-14.
 */
class ReagentDiscRotation
	:public Action{
//construction & destruction
public:
	ReagentDiscRotation(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~ReagentDiscRotation(void);
//interface
public:
	void set_reagent_type(const unsigned int reagent_type);
	unsigned int get_reagent_type() const;
	void set_position_no(const unsigned int position_no);
	unsigned int get_position_no() const;
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
	unsigned int _reagent_type;
	unsigned int _position_no;
};

