#pragma once

#include"Component.h"

/**
 * name: ReactionDisc
 * brief: ��Ӧ���࣬�������������豸�Ϸ�Ӧ�̵���Ϣ��
 * author: yameng_he 
 * date: 2015-12-29.
 */
class ReactionDisc
	:public Component{
//define
public:
	enum{HOLE_COUNT=90,};
	typedef enum{
		POSITION_ENTRY=0,//����λ��
		POSITION_ADD_REAGENT=1,//���Լ�λ��
		POSITION_ADD_SPECIMEN=2,//������λ��
		POSITION_EXIT=3,//����λ��
	}Position;
	typedef enum{
		HOLE_STATE_EMPTY,//��ǰ��Ϊ��״̬��
		HOLE_STATE_WAIT,//��ǰ��Ϊ�ȴ�״̬��
		HOLE_STATE_PROCESSING,//��ǰ��Ϊ����״̬��
		//HOLE_STATE_COMPLETE,//��ǰ��Ϊ���״̬��
		HOLE_STATE_RESERVED,//��ǰ��ΪԤ��״̬��
		HOLE_STATE_FAILED,//��ǰ��Ϊ����״̬��
		HOLE_STATE_UNKNOWN,//��ǰ��Ϊδ֪״̬��
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

