#pragma once

#include"Action.h"

/**
 * name: PutTubeInReactionDisc
 * breif: 放管到反应盘动作类，负责描述实现放管到反应盘
 *        动作。
 * author: yameng_he
 * date: 2016-01-11.
 */
class PutTubeInReactionDisc
	:public Action{
//define
public:
	enum{MAX_PUT_TUBE_IN_FAILED_TIMES=10,};
//construction & destruction
public:
	PutTubeInReactionDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~PutTubeInReactionDisc(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
//variables
private:
	static unsigned int _put_tube_in_failed_times;
};

