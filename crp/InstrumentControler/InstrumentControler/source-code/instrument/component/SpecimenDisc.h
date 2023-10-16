#pragma once

#include"Component.h"

class MtLock;

/**
 * name: SpecimenDisc
 * breif: 样本盘抽象类，负责描述一个样本盘信息。
 * author: yameng_he
 * date: 2016-01-13.
 */
class SpecimenDisc
	:public Component{
//define
public:
	enum{RACK_COUNT=6,POSITION_COUNT=10,};
//construction & destruction
public:
	SpecimenDisc(void);
	~SpecimenDisc(void);
//interface
public:
	int rotate(const unsigned int rack_no,const unsigned int position_no);
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_handle_flag;
	Flag _rotation_response_flag;
};

