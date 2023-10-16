#include"stdafx.h"
#include"DetectionDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: DetectionDisc
 * breif: 构造函数。
 * param: --
 * return: --
 */
DetectionDisc::DetectionDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_detect_shake_hand_flag(FLAG_IDLE)
	,_detect_response_flag(FLAG_IDLE)
	,_luminous(0){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));
}

/**
 * name: ~DetectionDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
DetectionDisc::~DetectionDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令检测盘指定孔旋转到指定位置。
 * param: hole_no - 输入的孔号。
 *        position - 输入的位置。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DetectionDisc::rotate(const unsigned int hole_no,const Position position){
	//1.如果参数输入不合法，则直接返回错误。
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.创建检测盘旋转指令，并且判断创建是否成功。
	Command command;
	Position position_t(position);
	if(POSITION_EXIT==position_t){//出管位其实就是进管位。
		position_t=POSITION_ENTRY;
	}
	if(command.generate_detection_disc_rotation_command(
		hole_no,static_cast<unsigned int>(position_t))<0){
		return(-2);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除检测盘旋转握手标记以及检测盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("检测盘旋转指令"))<0){
		return(-3);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: detect
 * breif: 命令检测盘检测。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DetectionDisc::detect(){
	//1.创建检测盘检测指令，并且判断创建是否成功。
	Command command;
	if(command.generate_detection_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除检测盘检测握手标记以及检测盘检测回复标记。
	set_detect_shake_hand_flag(FLAG_BUSY);
	set_detect_response_flag(FLAG_BUSY);
	set_luminous(0);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("检测盘检测指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * breif: 设置检测盘旋转握手标记。
 * param: flag - 输入的旋转握手标记。
 * return: --
 */
void DetectionDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置检测盘旋转握手标记。
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: 获取检测盘旋转握手标记。
 * param: --
 * return: 返回检测盘旋转握手标记。
 */
DetectionDisc::Flag DetectionDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回检测盘旋转握手标记。
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: 设置检测盘旋转回复标记。
 * param: flag - 输入清检测旋转回复标记。
 * return: --
 */
void DetectionDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置检测盘旋转回复标记。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: 获取检测盘旋转回复标记。
 * param: --
 * return: 返回检测盘旋转回复标记。
 */
DetectionDisc::Flag DetectionDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回检测盘旋转回复标记。
	return(_rotation_response_flag);
}

/**
 * name: set_detect_shake_hand_flag
 * brief: 设置检测盘检测握手标志。
 * param: flag - 输入的检测盘检测握手标志。
 * return: --
 */
void DetectionDisc::set_detect_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置检测盘检测握手标志。
	_detect_shake_hand_flag=flag;
}

/**
 * name: get_detect_shake_hand_flag
 * brief: 获取检测盘检测握手标志。
 * param: --
 * return: 返回检测盘检测握手标志。
 */
DetectionDisc::Flag DetectionDisc::get_detect_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回检测盘检测握手标志。
	return(_detect_shake_hand_flag);
}

/**
 * name: set_detect_response_flag
 * brief: 设置检测盘检测回复标志。
 * param: flag - 输入的检测盘检测回复标志。
 * return: --
 */
void DetectionDisc::set_detect_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置检测盘检测回复标志。
	_detect_response_flag=flag;
}

/**
 * name: get_detect_response_flag
 * brief: 获取检测盘检测回复标志。
 * param: --
 * return: 返回检测盘检测回复标志。
 */
DetectionDisc::Flag DetectionDisc::get_detect_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回检测盘检测回复标志。
	return(_detect_response_flag);
}

/**
 * name: set_luminous
 * brief: 设置发光值。
 * param: luminous - 输入的发光值。
 * return: --
 */
void DetectionDisc::set_luminous(const unsigned int luminous){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置输入的发光值。
	_luminous=luminous;
}

/**
 * name: get_luminous
 * breif: 获取发光值。
 * param: --
 * return: 返回发光值。
 */
unsigned int DetectionDisc::get_luminous() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回发光值。
	return(_luminous);
}

/**
 * name: set_hole_state
 * breif: 设置检测盘指定孔的状态。
 * param: hole_no - 输入的指定孔。
 *        state - 输入的指定状态。
 * return: --
 */
void DetectionDisc::set_hole_state(
	const unsigned int hole_no,const HoleState state){
	//1.如果输入参数不合法则直接返回。
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return;
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.设置指定孔的状态。
	_hole_state[hole_no-1]=state;
}

/** 
 * name: get_empty_hole_no
 * brief: 获取空孔号。
 * param: --
 * return: 如果获取空孔号成功，则返回孔号，否则返回零。
 */
unsigned int DetectionDisc::get_empty_hole_no() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取空孔号。
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_EMPTY==_hole_state[index]){
			return(index+1);
		}
	}
	//3.程序运行到此直接返回零。
	return(0);
}