#include"stdafx.h"
#include"ReagentDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReagentDisc
 * brief: 构造函数。
 * param: --
 * return: --
 */
ReagentDisc::ReagentDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~ReagentDisc
 * breif: 析构函数。
 * param: --
 * return: --
 */
ReagentDisc::~ReagentDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令试剂盘旋转。
 * param: type - 输入的试剂类型。
 *        position_no - 输入的位置号。
 * return: 如果函数执行成功返回值大于等于零的数，否则返回值小于零。
 */
int ReagentDisc::rotate(const ReagentType type,const unsigned int position_no){
	//1.检测输入是否合法。
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-1);
	}
	//2.创建试剂盘旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_reagent_disc_rotation_command(
		static_cast<unsigned int>(type),position_no)<0){
		return(-2);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除试剂盘旋转握手标记以及试剂盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("试剂盘旋转指令"))<0){
		return(-3);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: 设置试剂盘旋转握手标志。
 * param: flag - 输入的试剂盘旋转握手标志。
 * return: --
 */
void ReagentDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置试剂盘旋转握手标志。
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * breif: 获取试剂盘旋转握手标志。
 * param: --
 * return: 返回试剂盘旋转握手标志。
 */
ReagentDisc::Flag ReagentDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回试剂盘旋转握手标志。
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: 设置试剂盘旋转回复标志。
 * param: flag - 输入的试剂盘旋转回复标志。
 * return: --
 */
void ReagentDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置试剂盘旋转回复标志。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: 获取试剂盘旋转回复标志。
 * param: --
 * return: 返回试剂盘旋转回复标志。
 */
ReagentDisc::Flag ReagentDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回试剂盘旋转回复标志。
	return(_rotation_response_flag);
}