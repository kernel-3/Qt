#pragma once

#include"Component.h"

MtLock;

/**
 * name: WashingDisc
 * brief: ��ϴ���࣬�������������ϴ����Ϣ��
 * author: yameng_he
 * date: 2016-02-23
 */
class WashingDisc
	:public Component{
//define
public:
	enum{HOLE_COUNT=29,};
	typedef enum{
		POSITION_ENTRY,//����λ��
		POSITION_WASHING_1,//��ϴλ��1��
		POSITION_WASHING_2,//��ϴλ��2��
		POSITION_WASHING_3,//��ϴλ��3��
		POSITION_WASHING_4,//��ϴλ��4��
		POSITION_SUBSTRATE,//��ϴλ��5��
		POSITION_EXIT,//����λ��
	}Position;
	typedef enum{
		HOLE_STATE_EMPTY,//��ǰ��Ϊ��״̬��
		//HOLE_STATE_WAIT,//��ǰ��ΪԤ��״̬��
		//HOLE_STATE_PROCESSING,//��ǰ��Ϊ����״̬��
		//HOLE_STATE_COMPLETE,//��ǰ��Ϊ���״̬��
		//HOLE_STATE_RESERVED,//��ǰ��ΪԤ��״̬��
		HOLE_STATE_USED,//��ǰ��Ϊ��ռ��״̬��
		HOLE_STATE_FAILED,//��ǰ��Ϊ����״̬��
	}HoleState;
	typedef enum{
		SUBSTRATE_TYPE_NONE=0,//�޵��
		SUBSTRATE_TYPE_AB=1,//����AB��
		SUBSTRATE_TYPE_C=2,//����C��
		SUBSTRATE_TYPE_BUFFER_SOLUTION=3,//����Һ��
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

