#pragma once

#include"Component.h"

/**
 * name: TubeStorehouse
 * brief: �Թܲ��࣬������������Թܲ���Ϣ�����ṩ
 *        ���Թܲ���ص�ȫ���ӿڡ�
 * author: yameng_he
 * date: 2016-02-15.
 */
class TubeStorehouse
	:public Component{
//define
public:
	enum{ROW_COUNT=16,COL_COUNT=12,};
//construction & destruction
public:
	TubeStorehouse(void);
	virtual ~TubeStorehouse(void);
//interface
public:
	BOOL are_there_tubes() const;
	int get_tube_position(unsigned int &row,
		unsigned int &col) const;
	void decrease_tube_count();
	void clear_tube_count();
//variables
private:
	MtLock *_lock;
	unsigned int _tube_count;
};

