#include"stdafx.h"
#include"SpecimenDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: SpecimenDisc
 * brief: 构造函数。
 * param: --
 * return: --
 */
SpecimenDisc::SpecimenDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_handle_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~SpecimenDisc
 * breif: 析构函数。
 * param: --
 * return: --
 */
SpecimenDisc::~SpecimenDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令样本盘指定架子上的位置旋转到加样位。
 * param: rack_no - 输入的样本盘上架子号。
 *        position_no - 输入的样本盘上位置号。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenDisc::rotate(const unsigned int rack_no,
	const unsigned int position_no){
	//1.检测输入的参数是否合法。
	if((rack_no<1)||(rack_no>RACK_COUNT)){
		return(-1);
	}
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-2);
	}
	//2.创建反应盘旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_specimen_disc_rotation_command(
		rack_no,position_no)<0){
		return(-2);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除样本盘旋转握手标记以及样本盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("样本盘旋转指令"))<0){
		return(-3);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: 设置旋转握手标志。
 * param: flag - 输入的旋转握手标志。
 * return: --
 */
void SpecimenDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置旋转握手标志。
	_rotation_shake_handle_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: 获取旋转握手标志。
 * param: --
 * return: 返回旋转握手标志。
 */
SpecimenDisc::Flag SpecimenDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回旋转握手标志。
	return(_rotation_shake_handle_flag);
}

/**
 * name: set_rotation_response_flag
 * breif: 设置旋转回复标志。
 * param: --
 * return: --
 */
void SpecimenDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置旋转回复标志。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: 获取旋转回复标志。
 * param: --
 * return: 返回旋转回复标志。
 */
SpecimenDisc::Flag SpecimenDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回旋转回复标志。
	return(_rotation_response_flag);
}