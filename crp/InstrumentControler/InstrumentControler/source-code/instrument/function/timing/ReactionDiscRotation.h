#pragma once

#include"Action.h"

/**
 * name: ReactionDiscRotation
 * breif: 反应盘旋转动作，负责描述一个反应盘的旋转动作。
 * author: yameng_he
 * date: 2015-12-24
 */
class ReactionDiscRotation
	:public Action{
//define
public:
	typedef enum{DIRECTION_POSITIVE,DIRECTION_NEGATIVE,}Direction;
//construction & destruction
public:
	ReactionDiscRotation(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~ReactionDiscRotation(void);
//interface
public:
	void set_hole_no(const unsigned int hole_no);
	unsigned int get_hole_no() const;
	void set_position(const unsigned int position);
	unsigned int get_position() const;
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
	static Direction _rotation_direction;
//variables
private:
	BOOL _rotation_flag;
	unsigned int _hole_no;
	unsigned int _position;
};