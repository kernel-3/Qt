#pragma once

#include"Action.h"

/**
 * name: SpecimenArmSpit
 * breif: 样本臂吐样动作，负责抽象描述一个样本臂吐样动作。
 * author: yameng_he
 * date: 2016-01-13.
 */
class SpecimenArmSpit
	:public Action{
//construction & destruction
public:
	SpecimenArmSpit(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~SpecimenArmSpit(void);
//interface
public:
	void set_spit_volume(const unsigned int volume);
	unsigned int get_spit_volume() const;
	void set_down_steps(const unsigned int down_steps);
	unsigned int get_down_steps() const;
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
	unsigned int _spit_volume;
	unsigned int _down_steps;
};

