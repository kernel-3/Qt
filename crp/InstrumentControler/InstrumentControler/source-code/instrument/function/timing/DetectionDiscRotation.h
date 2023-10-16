#pragma once

#include"Action.h"

/**
 * name: DetectionDiscRotation
 * brief: ¼ì²âÅÌÐý×ª¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-22.
 */
class DetectionDiscRotation
	:public Action{
//construction & destruction
public:
	DetectionDiscRotation(const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~DetectionDiscRotation(void);
//interface
public:
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
	unsigned int _position;
};

