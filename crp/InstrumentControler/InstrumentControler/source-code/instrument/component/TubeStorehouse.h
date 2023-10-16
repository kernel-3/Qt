#pragma once

#include"Component.h"

/**
 * name: TubeStorehouse
 * brief: 试管仓类，负责抽象、描述试管仓信息，并提供
 *        与试管仓相关的全部接口。
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

