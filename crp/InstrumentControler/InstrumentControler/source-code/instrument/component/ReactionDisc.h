#pragma once

#include"Component.h"

/**
 * name: ReactionDisc
 * brief: 反应盘类，描述抽象描述设备上反应盘的信息。
 * author: yameng_he 
 * date: 2015-12-29.
 */
class ReactionDisc
	:public Component{
//define
public:
	enum{HOLE_COUNT=90,};
	typedef enum{
		POSITION_ENTRY=0,//进管位。
		POSITION_ADD_REAGENT=1,//加试剂位。
		POSITION_ADD_SPECIMEN=2,//加样本位。
		POSITION_EXIT=3,//出管位。
	}Position;
	typedef enum{
		HOLE_STATE_EMPTY,//当前孔为空状态。
		HOLE_STATE_WAIT,//当前孔为等待状态。
		HOLE_STATE_PROCESSING,//当前孔为处理状态。
		//HOLE_STATE_COMPLETE,//当前孔为完成状态。
		HOLE_STATE_RESERVED,//当前孔为预留状态。
		HOLE_STATE_FAILED,//当前孔为错误状态。
		HOLE_STATE_UNKNOWN,//当前孔为未知状态。
	}HoleState;
//construction & destruction
public:
	ReactionDisc(void);
	virtual ~ReactionDisc(void);
//interface
public:
	int rotate(const unsigned int hole_no,const Position position);
	int inquire_sensor();
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
	void set_having_tube_in_entry_flag(const Flag flag);
	Flag get_having_tube_in_entry_flag() const;
	void set_having_tube_in_entry_flag_expect_value(const Flag value);
	Flag get_having_tube_in_entry_flag_expect_value() const;
	void set_having_tube_in_exit_flag(const Flag flag);
	Flag get_having_tube_in_exit_flag() const;
	void set_having_tube_in_exit_flag_expect_value(const Flag value);
	Flag get_having_tube_in_exit_flag_expect_value() const;
	BOOL are_there_tubes() const;
	unsigned int get_empty_hole_no() const;
	int set_hole_state(const unsigned int hole_no,const HoleState state);
	HoleState get_hole_state(const unsigned int hole_no) const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_hand_flag;
	Flag _rotation_response_flag;
	Flag _having_tube_in_entry_flag;
	Flag _having_tube_in_entry_flag_expect_value;
	Flag _having_tube_in_exit_flag;
	Flag _having_tube_in_exit_flag_expect_value;
	HoleState _hole_state[HOLE_COUNT];
};

