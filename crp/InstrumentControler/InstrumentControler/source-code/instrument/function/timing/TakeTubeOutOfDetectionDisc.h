#pragma once

#include"Action.h"

/**
 * name: TakeTubeOutOfDetectionDisc
 * breif: 从检测盘取管动作。
 * author: yameng_he
 * date: 2016-01-25
 */
class TakeTubeOutOfDetectionDisc
	:public Action{
//construction & destruction
public:
	TakeTubeOutOfDetectionDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~TakeTubeOutOfDetectionDisc(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

