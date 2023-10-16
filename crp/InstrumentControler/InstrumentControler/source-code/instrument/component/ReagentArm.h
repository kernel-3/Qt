#pragma once

#include"Component.h"

class MtLock;

/**
 * name: ReagentArm
 * brief: 试剂臂类，负责抽象、描述一个试剂臂信息。
 *        并提供与试剂臂相关的所有接口。
 * author: yameng_he
 * date: 2016-02-20
 */
class ReagentArm
	:public Component{
//define
public:
	typedef enum{
		REAGENT_TYPE_R1=0,
		REAGENT_TYPE_R2=1,
		REAGENT_TYPE_MAGNETIC_BEAD_1=3,
		REAGENT_TYPE_MAGNETIC_BEAD_2=4,
	}ReagentType;
//construction & destruction
public:
	ReagentArm(void);
	virtual ~ReagentArm(void);
//interface
public:
	int suck(const unsigned int suck_volume,const ReagentType reagent_type,
		const BOOL liquid_level_probe_switch=TRUE);
	int spit(const unsigned int spit_volume,const unsigned int down_steps);
	int wash();
	void set_suck_shake_hand_flag(const Flag flag);
	Flag get_suck_shake_hand_flag() const;
	void set_suck_response_flag(const Flag flag);
	Flag get_suck_response_flag() const;
	void set_liquid_level_height(const unsigned int height);
	unsigned int get_liquid_level_height() const;
	void set_spit_shake_hand_flag(const Flag flag);
	Flag get_spit_shake_hand_flag() const;
	void set_spit_response_flag(const Flag flag);
	Flag get_spit_response_flag() const;
	void set_wash_shake_hand_flag(const Flag flag);
	Flag get_wash_shake_hand_flag() const;
	void set_wash_response_flag(const Flag flag);
	Flag get_wash_response_flag() const;
//implement
private:
	unsigned int get_outer_wash_time() const;
	unsigned int get_inner_wash_time() const;
//variables
private:
	MtLock *_lock;
	Flag _suck_shake_hand_flag;
	Flag _suck_response_flag;
	unsigned int _liquid_level_height;
	Flag _spit_shake_hand_flag;
	Flag _spit_response_flag;
	Flag _wash_shake_hand_flag;
	Flag _wash_response_flags;
};

