#pragma once

#include"Action.h"

/**
 * name: SpecimenArmWash
 * brief: 样本臂清洗动作。
 * author: yameng_he
 * date: 2016-01-14.
 */
class SpecimenArmWash
	:public Action{
//construction & destruction
public:
	SpecimenArmWash(		
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~SpecimenArmWash(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

