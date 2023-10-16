#pragma once

#include"Action.h"

/**
 * name: ReturnTubeToReactionDisc
 * brief: ת��ץ�ֻعܵ���Ӧ�̶�����
 * author: yameng_he
 * date: 2016-01-25.
 */
class ReturnTubeToReactionDisc
	:public Action{
//construction & destruction
public:
	ReturnTubeToReactionDisc(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~ReturnTubeToReactionDisc(void);
//overrides
public:
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
};

