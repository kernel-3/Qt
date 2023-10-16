#include"stdafx.h"
#include"ReactionDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReactionDisc
 * breif: 构造函数。
 * param: --
 * return: --
 */
ReactionDisc::ReactionDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_having_tube_in_entry_flag(FLAG_UNKNOWN)
	,_having_tube_in_entry_flag_expect_value(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag_expect_value(FLAG_UNKNOWN){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));
}

/**
 * name: ~ReactionDisc
 * breif: 析构函数。
 * param: --
 * return: --
 */
ReactionDisc::~ReactionDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令反应盘指定洞号旋转到指定位置。
 * param: hole_no - 输入的反应盘洞号。
 *        position - 输入的反应盘位置。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ReactionDisc::rotate(const unsigned int hole_no,const Position position){
	//1.检测输入的参数是否合法。
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.创建反应盘旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_reaction_disc_rotation_command(
		hole_no,static_cast<unsigned int>(position))<0){
		return(-2);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除反应盘旋转握手标记以及反应盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("反应盘旋转指令"))<0){
		return(-3);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: inquire_sensor
 * brief: 查询反应盘上的传感器，并且判断查询是否成功。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ReactionDisc::inquire_sensor(){
	//1.创建查询传感器指令，并且判断创建是否成功。
	Command command;
	if(command.generate_inquire_sensors_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除反应盘上各个传感器标志。
	set_having_tube_in_entry_flag(FLAG_UNKNOWN);
	set_having_tube_in_exit_flag(FLAG_UNKNOWN);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("查询反应盘位置传感器指令"))<0){
		return(-2);
	}
	//6.循环等待反应盘上位置传感器状态返回，并且判断是否超时。
	//6-1.记录当前起始时间。
	DWORD last_time=timeGetTime();
	//6-2.循环检测反应盘上位置传感器状态是否成功返回。
	while(1){
		//6-2-1.如果反应盘上位置传感器状态成功返回。
		if((FLAG_UNKNOWN!=get_having_tube_in_entry_flag())&&(
			FLAG_UNKNOWN!=get_having_tube_in_exit_flag())){
			return(0);
		}
		//6-2-2.如果反应盘上位置传感器状态尚未返回。
		else{
			//a.获取当前时间。
			const DWORD current_time=timeGetTime();
			//b.检测当前时间是否溢出。
			if(last_time>current_time){
				last_time=current_time;
			}
			//c.如果当前发生指令超时错误。
			if((current_time-last_time)>ANSWER_TIMEOUT){
				return(-3);
			}
			//d.如果当前尚未发生超时，则继续下次循环。
			else{
				//d-1.释放时间片。
				timeBeginPeriod(1);
				Sleep(5);
				timeEndPeriod(1);
				//d-2.继续下次循环。
				continue;
			}
		}
	}
	//7.程序运行到此直接返回错误。
	return(-4);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: 设置反应盘旋转握手标志。
 * param: flag - 输入的反应盘旋转握手标志。
 * return: --
 */
void ReactionDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置标记。
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: 获取反应盘旋转握手标志。
 * param: --
 * return: 返回反应盘旋转握手标志。
 */
ReactionDisc::Flag ReactionDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回标记。
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: 设置反应盘旋转回复标志。
 * param: flag - 输入的反应盘旋转回复标志。
 * return: --
 */
void ReactionDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置标记。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: 获取反应盘旋转回复标志。
 * param: --
 * return: 返回反应盘旋转回复标志。
 */
ReactionDisc::Flag ReactionDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回标记。
	return(_rotation_response_flag);
}

/**
 * name: set_having_tube_in_entry_flag
 * brief: 设置反应盘进管位有管标志。
 * param: flag - 输入的反应盘进管位有管标志。
 * return: --
 */
void ReactionDisc::set_having_tube_in_entry_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置反应盘进管位有管标志。
	_having_tube_in_entry_flag=flag;
}

/**
 * name: get_having_tube_in_entry_flag
 * breif: 获取反应盘进管位有管标志。
 * param: --
 * return: 返回反应盘进管位有管标志。
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_entry_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回反应盘进管位有管标志。
	return(_having_tube_in_entry_flag);
}

/**
 * name: set_having_tube_in_entry_flag_expect_value
 * breif: 设置反应盘进管位有管标志的期望值。
 * param: value - 输入的反应盘进管位有管标志的期望值。
 * return: --
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
void ReactionDisc::set_having_tube_in_entry_flag_expect_value(const Flag value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置反应盘进管位有管标志的期望值。
	_having_tube_in_entry_flag_expect_value=value;
}

/**
 * name: get_having_tube_in_entry_flag_expect_value
 * brief: 获取反应盘进管位有管标志的期望值。
 * param: --
 * return: 返回反应盘进管位有管标志的期望值。
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_entry_flag_expect_value() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回反应盘进管位有管标志的期望值。
	return(_having_tube_in_entry_flag_expect_value);
}

/**
 * name: set_having_tube_in_exit_flag
 * brief: 设置反应盘出管位有管标志。
 * param: flag - 输入的反应盘出管位有管标志。
 * return: --
 */
void ReactionDisc::set_having_tube_in_exit_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置反应盘出管位有管标志。
	_having_tube_in_exit_flag=flag;
}

/**
 * name: get_having_tube_in_exit_flag
 * breif: 获取反应盘出管位有管标志。
 * param: --
 * return: 返回反应盘出管位有管标志。
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_exit_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回反应盘出管位有管标志。
	return(_having_tube_in_exit_flag);
}

/**
 * name: set_having_tube_in_exit_flag_expect_value
 * breif: 设置反应盘出管位有管标志的期望值。
 * param: value - 输入的反应盘出管位有管标志的期望值。
 * return: --
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
void ReactionDisc::set_having_tube_in_exit_flag_expect_value(const Flag value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置反应盘出管位有管标志的期望值。
	_having_tube_in_exit_flag_expect_value=value;
}

/**
 * name: get_having_tube_in_exit_flag_expect_value
 * brief: 获取反应盘出管位有管标志的期望值。
 * param: --
 * return: 返回反应盘出管位有管标志的期望值。
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_exit_flag_expect_value() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回反应盘出管位有管标志的期望值。
	return(_having_tube_in_exit_flag_expect_value);
}

/**
 * name: are_there_tubes
 * breif: 检测当前反应盘上是否有管。
 * param: --
 * return: 如果当前反应盘上有管返回TRUE，否则返回FALSE。
 */
BOOL ReactionDisc::are_there_tubes() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.循环遍历反应盘位置，检测是否有管。
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_WAIT==_hole_state[index]){
			//remark: 因为当反应盘孔处于HOLE_STATE_PROCESSING（处理状态）时，
			//        反应盘肯定是不允许旋转的，所以这里没有讨论HOLE_STATE_PROCESSING
			//        状态。
			return(TRUE);
		}
	}
	//3.程序运行到此直接返回无管。
	return(FALSE);
}

/**
 * name: get_empty_hole_no
 * brief: 获取当前反应盘上空孔的孔号。
 * param: --
 * return: 如果函数执行成功，返回当前反应盘上空孔的孔号，
 *         否则返回零。
 */
unsigned int ReactionDisc::get_empty_hole_no() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.循环遍历反应盘位置，计算反应盘上空孔的孔号。
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_EMPTY==_hole_state[index]){
			return(index+1);
		}
	}
	//3.程序运行到此直接返回零。
	return(0);
}

/**
 * name: set_hole_state
 * brief: 设置反应盘上指定空的状态。
 * param: hole_no - 输入的指定孔号。
 *        state - 输入的孔的状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ReactionDisc::set_hole_state(
	const unsigned int hole_no,const HoleState state){
	//1.检测输入是否合法。
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.设置指定孔的状态。
	_hole_state[hole_no-1]=state;
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: get_hole_state
 * brief: 获取反应盘上指定孔的状态。
 * param: hole_no - 输入指定的孔号。
 * return: 如果当前函数执行成功，返回执行孔的状态，否则返回未知状态。
 */
ReactionDisc::HoleState ReactionDisc::get_hole_state(
	const unsigned int hole_no) const{
	//1.检测输入是否合法。
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(HOLE_STATE_UNKNOWN);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.返回指定孔的位置。
	return(_hole_state[hole_no-1]);
}