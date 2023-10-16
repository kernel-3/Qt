#pragma once

#include"Action.h"

/**
 * name: PutTubeInWashingDisc
 * brief: 清洗盘进管动作。
 * author: yameng_he
 * date: 2016-01-25.
 */
class PutTubeInWashingDisc
	:public Action{
//construction & destruction
public:
	PutTubeInWashingDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~PutTubeInWashingDisc(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

