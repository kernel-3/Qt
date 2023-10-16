#pragma once

#include"Action.h"

/**
 * name: TakeTubeOutOfTubeStoreHouse
 * breif: 从试管仓中取管动作。
 * author: yameng_he
 * date: 2016-01-11.
 */
class TakeTubeOutOfTubeStoreHouse
	:public Action{
//construction & destruction
public:
	TakeTubeOutOfTubeStoreHouse(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~TakeTubeOutOfTubeStoreHouse(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

