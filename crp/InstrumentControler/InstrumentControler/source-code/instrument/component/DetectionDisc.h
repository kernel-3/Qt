#pragma once

#include"Component.h"

class MtLock;

/**
 * name: DetectionDisc
 * breif: 检测盘类，负责抽象描述检测盘信息。
 * author: yameng_he
 * date: 2016-01-22.
 */
class DetectionDisc
	:public Component{
//define
public:
	enum{HOLE_COUNT=6,};
	typedef enum{
		POSITION_ENTRY=0,
		POSITION_DETECTION=1,
		POSITION_EXIT=2,
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
//construction & destruction
public:
	DetectionDisc(void);
	virtual ~DetectionDisc(void);
//interface
public:
	int rotate(const unsigned int hole_no,const Position position);
	int detect();
	void set_rotation_shake_hand_flag(const Flag flag);
	Flag get_rotation_shake_hand_flag() const;
	void set_rotation_response_flag(const Flag flag);
	Flag get_rotation_response_flag() const;
	void set_detect_shake_hand_flag(const Flag flag);
	Flag get_detect_shake_hand_flag() const;
	void set_detect_response_flag(const Flag flag);
	Flag get_detect_response_flag() const;
	void set_luminous(const unsigned int luminous);
	unsigned int get_luminous() const;
	void set_hole_state(const unsigned int hole_no,const HoleState state);
	unsigned int get_empty_hole_no() const;
//variables
private:
	MtLock *_lock;
	Flag _rotation_shake_hand_flag;
	Flag _rotation_response_flag;
	Flag _detect_shake_hand_flag;
	Flag _detect_response_flag;
	unsigned int _luminous;
	HoleState _hole_state[HOLE_COUNT];
};