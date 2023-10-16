#include"stdafx.h"
#include"MagneticBeadDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: MagneticBeadDisc
 * brief: 构造函数。
 * param: --
 * return: --
 */
MagneticBeadDisc::MagneticBeadDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_mixing_rotation_shake_hand_flag(FLAG_IDLE)
	,_mixing_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~MagneticBeadDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
MagneticBeadDisc::~MagneticBeadDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令磁珠盘旋转。
 * param: position_no - 输入的位置号。
 * return: 如果函数执行成功返回值大于等于零的数，否则返回值小于零。
 */
int MagneticBeadDisc::rotate(const unsigned int position_no){
	//1.检测输入是否合法。
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-1);
	}
	//2.创建磁珠盘旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_magnetic_bead_disc_rotation_command(
		position_no)<0){
		return(-2);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除磁珠盘旋转握手标记以及磁珠盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("磁珠盘旋转指令"))<0){
		return(-3);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: mix_rotate
 * brief: 命令磁珠盘混匀旋转。
 * param: direction - 输入的转动方向。
 * return: 如果函数执行成功返回值大于等于零的数，否则返回值小于零。
 */
int MagneticBeadDisc::mix_rotate(const Direction direction){
	//1.创建磁珠盘混匀旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_magnetic_bead_disc_mixing_rotation_command(
		static_cast<unsigned int>(direction))<0){
		return(-1);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除磁珠盘混匀旋转握手标记以及磁珠盘混匀旋转回复标记。
	set_mixing_rotation_shake_hand_flag(FLAG_BUSY);
	set_mixing_rotation_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("磁珠盘混匀旋转指令"))<0){
		return(-2);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: 设置磁珠盘旋转握手标志。
 * param: flag - 输入的磁珠盘旋转握手标志。
 * return: --
 */
void MagneticBeadDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置磁珠盘旋转握手标志。
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * breif: 获取磁珠盘旋转握手标志。
 * param: --
 * return: 返回磁珠盘旋转握手标志。
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回磁珠盘旋转握手标志。
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: 设置磁珠盘旋转回复标志。
 * param: flag - 输入的磁珠盘旋转回复标志。
 * return: --
 */
void MagneticBeadDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置磁珠盘旋转回复标志。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: 获取磁珠盘旋转回复标志。
 * param: --
 * return: 返回磁珠盘旋转回复标志。
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回磁珠盘旋转回复标志。
	return(_rotation_response_flag);
}

/**
 * name: set_mixing_rotation_shake_hand_flag
 * brief: 设置磁珠盘混匀旋转握手标志。
 * param: flag - 输入的磁珠盘混匀旋转握手标志。
 * return: --
 */
void MagneticBeadDisc::set_mixing_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置磁珠盘正、负握手标志。
	_mixing_rotation_shake_hand_flag=flag;
}

/** 
 * name: get_mixing_rotation_shake_hand_flag
 * brief: 获取磁珠盘混匀旋转握手标志。
 * param: --
 * return: 返回磁珠盘混匀旋转握手标志。
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_mixing_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回磁珠盘混匀旋转握手标志。
	return(_mixing_rotation_shake_hand_flag);
}

/**
 * name: set_mixing_rotation_response_flag
 * breif: 设置磁珠盘混匀旋转回复标志。
 * param: flag - 输入的磁珠盘混匀旋转回复标志。
 * return: --
 */
void MagneticBeadDisc::set_mixing_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置磁珠盘混匀旋转回复标志。
	_mixing_rotation_response_flag=flag;
}

/**
 * name: get_mixing_rotation_response_flag
 * breif: 获取磁珠盘混匀旋转回复标志。
 * param: --
 * return: 返回磁珠盘混匀旋转回复标志。
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_mixing_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回磁珠盘混匀旋转回复标志。
	return(_mixing_rotation_response_flag);
}