#pragma once

#include"Component.h"

class MtLock;

/**
 * name: ReagentDisc
 * breif: 试剂盘类，负责抽象描述一个试剂盘信息。
 * author: yameng_he
 * date: 2016-01-14.
 */
class ReagentDisc
	:public Component{
//define
public:
	enum{POSITION_COUNT=30,};
	typedef enum{REAGENT_TYPE_R1=0,REAGENT_TYPE_R2=1,}ReagentType;
//construction & destruction
public:
	ReagentDisc(void);
	~ReagentDisc(void);
//interface
public:
	int rotate(const ReagentType type,const unsigned int position_no);
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_hand_flag;
	Flag _rotation_response_flag;
};

