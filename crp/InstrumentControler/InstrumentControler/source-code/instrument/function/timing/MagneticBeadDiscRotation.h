#pragma once

#include"Action.h"

/**
 * name: MagneticBeadDiscRotation
 * breif: ´ÅÖéÅÌÐý×ª¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-14.
 */
class MagneticBeadDiscRotation
	:public Action{
//construction & destruction
public:
	MagneticBeadDiscRotation(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~MagneticBeadDiscRotation(void);
//interface
public:
	void set_position_no(const int position_no);
	int get_position_no() const;
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
	static unsigned int _direction;
//variables
private:
	BOOL _rotation_flag;
	unsigned int _position_no;
};

