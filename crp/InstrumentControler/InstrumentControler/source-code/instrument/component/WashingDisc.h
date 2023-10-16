#pragma once

#include"Component.h"

MtLock;

/**
 * name: WashingDisc
 * brief: 清洗盘类，负责抽象描述清洗盘信息。
 * author: yameng_he
 * date: 2016-02-23
 */
class WashingDisc
	:public Component{
//define
public:
	enum{HOLE_COUNT=29,};
	typedef enum{
		POSITION_ENTRY,//进管位。
		POSITION_WASHING_1,//清洗位置1。
		POSITION_WASHING_2,//清洗位置2。
		POSITION_WASHING_3,//清洗位置3。
		POSITION_WASHING_4,//清洗位置4。
		POSITION_SUBSTRATE,//清洗位置5。
		POSITION_EXIT,//出管位。
	}Position;
	typedef enum{
		HOLE_STATE_EMPTY,//当前孔为空状态。
		//HOLE_STATE_WAIT,//当前孔为预订状态。
		//HOLE_STATE_PROCESSING,//当前孔为处理状态。
		//HOLE_STATE_COMPLETE,//当前孔为完成状态。
		//HOLE_STATE_RESERVED,//当前孔为预留状态。
		HOLE_STATE_USED,//当前孔为被占用状态。
		HOLE_STATE_FAILED,//当前孔为错误状态。
	}HoleState;
	typedef enum{
		SUBSTRATE_TYPE_NONE=0,//无底物。
		SUBSTRATE_TYPE_AB=1,//底物AB。
		SUBSTRATE_TYPE_C=2,//底物C。
		SUBSTRATE_TYPE_BUFFER_SOLUTION=3,//缓冲液。
	}SubstrateType;
//construction & destruction
public:
	WashingDisc(void);
	virtual ~WashingDisc(void);
//interface
public:
	int rotate();
	int wash(const SubstrateType substrate_type=SUBSTRATE_TYPE_NONE,
		const unsigned int substrate_volume=0);
	int inquire_sensor();
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
	void set_wash_shake_hand_flag(const Flag flag);
	Flag get_wash_shake_hand_flag() const;
	void set_wash_response_flag(const Flag flag);
	Flag get_wash_response_flag() const;
	void set_having_tube_in_entry_flag(const Flag flag);
	Flag get_having_tube_in_entry_flag() const;
	void set_having_tube_in_entry_flag_expect_value(const Flag flag);
	Flag get_having_tube_in_entry_flag_expect_value() const;
	void set_having_tube_in_exit_flag(const Flag flag);
	Flag get_having_tube_in_exit_flag() const;
	void set_having_tube_in_exit_flag_expect_value(const Flag flag);
	Flag get_having_tube_in_exit_flag_expect_value() const;
	void reset_hole_no_in_entry();
	void decrease_hole_no_in_entry();
	BOOL are_there_tubes() const;
	void set_hole_state(const Position position,const HoleState state);
	HoleState get_hole_state(const Position position) const;
//implement
private:
	unsigned int get_hole_no(const Position position) const;
	unsigned int get_washing_liquid_volume() const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_hand_flag;
	Flag _rotation_response_flag;
	Flag _wash_shake_hand_flag;
	Flag _wash_response_flag;
	Flag _having_tube_in_entry_flag;
	Flag _having_tube_in_entry_flag_expect_value;
	Flag _having_tube_in_exit_flag;
	Flag _having_tube_in_exit_flag_expect_value;
	unsigned int _hole_no_in_entry;
	HoleState _hole_state[HOLE_COUNT];
};

