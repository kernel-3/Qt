#pragma once

#include"Action.h"

/**
 * name: DiscardTube
 * brief: ¶ª¹Ü¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-25.
 */
class DiscardTube
	:public Action{
//construction & destruction
public:
	DiscardTube(const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~DiscardTube(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

