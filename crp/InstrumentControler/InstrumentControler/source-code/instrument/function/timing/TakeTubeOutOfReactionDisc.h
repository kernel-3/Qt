#pragma once

#include"Action.h"

/**
 * name: TakeTubeOutOfReactionDisc
 * breif: 从反应盘中取出管动作。
 * author: yameng_he
 * date: 2016-01-25.
 */
class TakeTubeOutOfReactionDisc
	:public Action{
//construction & destruction
public:
	TakeTubeOutOfReactionDisc(
		const unsigned id,
		const unsigned sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~TakeTubeOutOfReactionDisc(void);
//interface
public:
	void set_reserve_reaction_disc_hole_flag(const BOOL flag);
	BOOL get_reserve_reaction_disc_hole_flag() const;
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
	BOOL _reserve_reaction_disc_hole_flag;
};

