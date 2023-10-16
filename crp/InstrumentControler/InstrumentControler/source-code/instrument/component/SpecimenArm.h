#pragma once

#include"Component.h"

class MtLock;

/**
 * name: SpecimenArm
 * brief: 样本臂类，负责抽象、描述一个样本臂信息。
 *        并提供与样本臂相关的所有接口。
 * author: yameng_he
 * date: 2016-02-18
 */
class SpecimenArm
	:public Component{
//define
public:
	typedef enum{
		CUP_TYPE_STANDARD=0,//标准杯。
		CUP_TYPE_TUBE=1,//采血管。
		CUP_TYPE_MICROSCALE=2,//微量杯。
	}CupType;
//construction & destruction
public:
	SpecimenArm(void);
	virtual ~SpecimenArm(void);
//interface
public:
	int suck(const unsigned int suck_volume,const CupType cup_type,
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