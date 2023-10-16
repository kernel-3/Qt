#pragma once

#include"Component.h"

class MtLock;

/**
 * name: MagneticBeadDisc
 * breif: 磁珠盘类，负责描述一个磁珠盘。
 * author: yameng_he
 * date: 2016-01-14.
 */
class MagneticBeadDisc
	:public Component{
//define
public:
	enum{POSITION_COUNT=9,};
	typedef enum{DIRECTION_NEGATIVE=0,DIRECTION_POSITIVE=1,}Direction;
//construction & destruction
public:
	MagneticBeadDisc(void);
	~MagneticBeadDisc(void);
//interface
public:
	int rotate(const unsigned int position_no);
	int mix_rotate(const Direction direction);
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
	void set_mixing_rotation_shake_hand_flag(const Flag flag);
	Flag get_mixing_rotation_shake_hand_flag() const;
	void set_mixing_rotation_response_flag(const Flag flag);
	Flag get_mixing_rotation_response_flag() const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_hand_flag;
	Flag _rotation_response_flag;
	Flag _mixing_rotation_shake_hand_flag;
	Flag _mixing_rotation_response_flag;
};

