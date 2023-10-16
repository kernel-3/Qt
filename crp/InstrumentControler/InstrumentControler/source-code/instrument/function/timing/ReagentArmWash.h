#pragma once

#include"Action.h"

/**
 * name: ReagentArmWash
 * breif: ÇåÏ´ÊÔ¼Á¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-21.
 */
class ReagentArmWash
	:public Action{
//construction & destruction
public:
	ReagentArmWash(		
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~ReagentArmWash(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

