#pragma once

#include"Action.h"

/**
 * name: SpecimenDiscRotation
 * brief: 样本盘旋转动作。
 * author: yameng_he
 * date: 2016-01-13.
 */
class SpecimenDiscRotation
	:public Action{
//construction & destruction
public:
	SpecimenDiscRotation(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~SpecimenDiscRotation(void);
//interface
public:
	void set_rack_no(const unsigned int rack_no);
	unsigned int get_rack_no() const;
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
	unsigned int _rack_no;
	unsigned int _position_no;
};