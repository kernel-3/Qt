#include"stdafx.h"
#include"SpecimenArm.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include"../../common/Inis.h"
#include<MMSystem.h>

/**
 * name: SpecimenArm
 * brief: 构造函数。
 * param: --
 * return: --
 */
SpecimenArm::SpecimenArm(void)
	:_lock(new MtLock)
	,_suck_shake_hand_flag(FLAG_IDLE)
	,_suck_response_flag(FLAG_IDLE)
	,_liquid_level_height(0)
	,_spit_shake_hand_flag(FLAG_IDLE)
	,_spit_response_flag(FLAG_IDLE)
	,_wash_shake_hand_flag(FLAG_IDLE)
	,_wash_response_flags(FLAG_IDLE){
}

/**
 * name: ~SpecimenArm
 * brief: 析构函数。
 * param: --
 * return: --
 */
SpecimenArm::~SpecimenArm(void){
	delete _lock;
}

/**
 * name: suck
 * brief: 命令样本臂吸液。
 * param: suck_volume - 输入的吸取体积（单位：微升）。
 *        cup_type - 输入的样本杯类型。
 *        liquid_level_probe_switch - 输入的液位探测开关。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenArm::suck(const unsigned int suck_volume,
	const CupType cup_type,const BOOL liquid_level_probe_switch/*=TRUE*/){
	//1.创建样本臂吸液指令，并且判断创建是否成功。
	Command command;
	if(command.generate_specimen_arm_suck_command(
		suck_volume,static_cast<unsigned int>(cup_type),
		liquid_level_probe_switch)<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除样本臂吸液握手标记以及样本臂吸液回复标记。
	set_suck_shake_hand_flag(FLAG_BUSY);
	set_suck_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("样本臂吸液指令"))<0){
		return(-2);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: spit
 * brief: 命令样本臂吐液。
 * param: spit_volume - 输入的吐液体积。
 *        down_steps - 输入的样本臂下降步数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenArm::spit(const unsigned int spit_volume,const unsigned int down_steps){
	//1.创建样本臂吐液指令，并且判断创建是否成功。
	Command command;
	if(command.generate_specimen_arm_spit_command(
		spit_volume,down_steps)<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除样本臂吐液握手标记以及样本臂吐液回复标记。
	set_spit_shake_hand_flag(FLAG_BUSY);
	set_spit_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("样本臂吐液指令"))<0){
		return(-2);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: wash
 * brief: 命令样本臂清洗。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenArm::wash(){
	//1.创建样本臂清洗指令，并且判断创建是否成功。
	Command command;
	if(command.generate_specimen_arm_wash_command(
		get_outer_wash_time(),get_inner_wash_time())<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除样本臂清洗握手标记以及样本臂清洗回复标记。
	set_wash_shake_hand_flag(FLAG_BUSY);
	set_wash_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("样本臂清洗指令"))<0){
		return(-2);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_suck_shake_hand_flag
 * breif: 设置吸取握手标志。
 * param: flag - 输入的吸取握手标志。
 * return: --
 */
void SpecimenArm::set_suck_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置吸取握手标志。
	_suck_shake_hand_flag=flag;
}

/**
 * name: get_suck_shake_hand_flag
 * breif: 获取吸取握手标志。
 * param: --
 * return: 返回吸取握手标志。
 */
SpecimenArm::Flag SpecimenArm::get_suck_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回吸取握手标志。
	return(_suck_shake_hand_flag);
}

/**
 * name: set_suck_response_flag
 * brief: 设置吸取回复标志。
 * param: --
 * return: --
 */
void SpecimenArm::set_suck_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置吸取回复标志。
	_suck_response_flag=flag;
}

/**
 * name: get_suck_response_flag
 * breif: 获取吸取回复标志。
 * param: --
 * return: 返回吸取回复标志。
 */
SpecimenArm::Flag SpecimenArm::get_suck_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回吸取回复标志。
	return(_suck_response_flag);
}

/**
 * name: set_liquid_level_height
 * brief: 设置液位高度。
 * param: height - 输入的液位高度。
 * return: --
 */
void SpecimenArm::set_liquid_level_height(const unsigned int height){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置液位高度。
	_liquid_level_height=height;
}

/**
 * name: get_liquid_level_height
 * brief: 获取液位高度。
 * param: --
 * return: 返回液位高度。
 */
unsigned int SpecimenArm::get_liquid_level_height() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回液位高度。
	return(_liquid_level_height);
}

/**
 * name: set_spit_shake_hand_flag
 * brief: 设置吐液握手标志。
 * param: flag - 输入的添加握手标志。
 * return: --
 */
void SpecimenArm::set_spit_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.输入的添加握手标志。
	_spit_shake_hand_flag=flag;
}

/**
 * name: get_spit_shake_hand_flag
 * brief: 获取吐液握手标志。
 * param: --
 * return: 返回吐液握手标志。
 */
SpecimenArm::Flag SpecimenArm::get_spit_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回添加握手标志。
	return(_spit_shake_hand_flag);
}

/**
 * name: set_spit_response_flag
 * brief: 设置吐液回复标志。
 * param: flag - 输入的添加回复标志。
 * return: --
 */
void SpecimenArm::set_spit_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置吐液回复标志。
	_spit_response_flag=flag;
}

/**
 * name: get_spit_response_flag
 * brief: 获取吐液回复标志。
 * param: --
 * return: 返回吐液回复标志。
 */
SpecimenArm::Flag SpecimenArm::get_spit_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回吐液回复标志。
	return(_spit_response_flag);
}

/**
 * name: set_wash_shake_hand_flag
 * brief: 设置清洗握手标志。
 * param: flag - 输入的清洗握手标志。
 * return: --
 */
void SpecimenArm::set_wash_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗握手标志。
	_wash_shake_hand_flag=flag;
}

/**
 * name: get_wash_shake_hand_flag
 * brief: 获取清洗握手标志。
 * param: --
 * return: 返回清洗握手标志。
 */
SpecimenArm::Flag SpecimenArm::get_wash_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗握手标志。
	return(_wash_shake_hand_flag);
}

/**
 * name: set_wash_response_flag
 * brief: 设置清洗回复标志。
 * param: flag - 输入的清洗回复标志。
 * return: --
 */
void SpecimenArm::set_wash_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗回复标志。
	_wash_response_flags=flag;
}

/**
 * name: get_wash_response_flag
 * brief: 获取清洗回复标志。
 * param: --
 * return: 返回清洗回复标志。
 */
SpecimenArm::Flag SpecimenArm::get_wash_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗回复标志。
	return(_wash_response_flags);
}

/**
 * name: get_outer_wash_time
 * brief: 获取外壁清洗时间。
 * param: --
 * return: 返回外壁清洗时间。
 */
unsigned int SpecimenArm::get_outer_wash_time() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前配置文件中保存的外壁清洗时间。
	int wash_time=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("SPECIMENARM"),_T("OUTER_WASH_TIME"));
	if(wash_time<0){
		wash_time=0;
	}else if(wash_time>5000){
		wash_time=5000;
	}
	//3.程序运行到此直接返回外壁清洗时间。
	return(static_cast<unsigned int>(wash_time));
}

/**
 * name: get_inner_wash_time
 * brief: 获取内壁清洗时间。
 * param: --
 * return: 返回内壁清洗时间。
 */
unsigned int SpecimenArm::get_inner_wash_time() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前配置文件中保存的壁清洗时间。
	int wash_time=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("SPECIMENARM"),_T("INNER_WASH_TIME"));
	if(wash_time<0){
		wash_time=0;
	}else if(wash_time>5000){
		wash_time=5000;
	}
	//3.程序运行到此直接返回外壁清洗时间。
	return(static_cast<unsigned int>(wash_time));
}