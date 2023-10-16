#pragma once

#include"Action.h"

/**
 * name: Detect
 * breif: ¼ì²â¶¯×÷¡£
 * author: yameng_he
 * date: 2016-01-25.
 */
class Detect
	:public Action{
//construction & destruction
public:
	Detect(const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~Detect(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

