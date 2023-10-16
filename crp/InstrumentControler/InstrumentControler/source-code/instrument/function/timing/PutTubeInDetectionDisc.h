#pragma once

#include"Action.h"

/**
 * name: PutTubeInDetectionDisc
 * brief: 转运抓手放管到检测盘动作。
 * author: yameng_he
 * date: 2016-01-25.
 */
class PutTubeInDetectionDisc
	:public Action{
//construction & destruction
public:
	PutTubeInDetectionDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~PutTubeInDetectionDisc(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

