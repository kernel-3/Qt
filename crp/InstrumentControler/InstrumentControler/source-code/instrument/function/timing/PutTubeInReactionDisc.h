#pragma once

#include"Action.h"

/**
 * name: PutTubeInReactionDisc
 * breif: �Źܵ���Ӧ�̶����࣬��������ʵ�ַŹܵ���Ӧ��
 *        ������
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

