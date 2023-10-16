#include"stdafx.h"
#include"TransportTong.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TransportTong
 * breif: 构造函数。
 * param: --
 * return: --
 */
TransportTong::TransportTong(void)
	:Component()
	,_lock(new MtLock)
	,_take_tube_out_of_detection_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_detection_disc_response_flag(FLAG_IDLE)
	,_discard_tube_shake_hand_flag(FLAG_IDLE)
	,_discard_tube_response_flag(FLAG_UNKNOWN)
	,_take_tube_out_of_washing_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_washing_disc_response_flag(FLAG_IDLE)
	,_return_tube_to_reaction_disc_shake_hand_flag(FLAG_IDLE)
	,_return_tube_to_reaction_disc_response_flag(FLAG_IDLE)
	,_put_tube_in_detection_disc_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_detection_disc_response_flag(FLAG_IDLE)
	,_take_tube_out_of_reaction_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_reaction_disc_response_flag(FLAG_IDLE)
	,_put_tube_in_washing_disc_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_washing_disc_response_flag(FLAG_IDLE){
}

/**
 * name: ~TransportTong
 * breif: 析构函数。
 * param: --
 * return: --
 */
TransportTong::~TransportTong(void){
	delete _lock;
}

/**
 * name: take_tube_out_of_detection_disc
 * brief: 命令转运抓手从检测盘取管。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::take_tube_out_of_detection_disc(){
	//1.创建转运抓手从检测盘取管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_take_tube_out_of_detection_disc_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手从检测盘取管握手标记以及转运抓手从检测盘取管回复标记。
	set_take_tube_out_of_detection_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_detection_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手从检测盘取管指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: discard_tube
 * brief: 命令转运抓手丢管。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::discard_tube(){
	//1.创建转运抓手丢管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_discard_tube_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手丢管握手标记以及转运抓手丢管回复标记。
	set_discard_tube_shake_hand_flag(FLAG_BUSY);
	set_discard_tube_response_flag(FLAG_UNKNOWN);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手丢管指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: take_tube_out_of_washing_disc
 * brief: 从清洗盘取管。
 * param: stop_position - 输入的停止位置。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::take_tube_out_of_washing_disc(
	const StopPosition stop_position){
	//1.创建转运抓手从清洗盘取管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_take_tube_out_of_washing_disc_command(
		stop_position)<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手从清洗盘取管握手标记以及转运抓手从清洗盘取管回复标记。
	set_take_tube_out_of_washing_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_washing_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手从清洗盘取管指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: return_tube_to_reaction_disc
 * brief: 回管到反应盘。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::return_tube_to_reaction_disc(){
	//1.创建转运抓手回管到反应盘指令，并且判断创建是否成功。
	Command command;
	if(command.generate_return_tube_to_reaction_disc_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手回管到反应盘握手标记以及转运抓手回管到反应盘回复标记。
	set_return_tube_to_reaction_disc_shake_hand_flag(FLAG_BUSY);
	set_return_tube_to_reaction_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手回管到反应盘指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: put_tube_in_detection_disc
 * brief: 命令转运抓手放管到检测盘。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::put_tube_in_detection_disc(){
	//1.创建转运抓手放管到检测盘指令，并且判断创建是否成功。
	Command command;
	if(command.generate_put_tube_in_detection_disc_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手放管到检测盘握手标记以及转运抓手放管到检测盘回复标记。
	set_put_tube_in_detection_disc_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_detection_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手放管到检测盘指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: take_tube_out_of_reaction_disc
 * brief: 命令转运抓手从反应盘取管。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::take_tube_out_of_reaction_disc(){
	//1.创建转运抓手从反应盘取管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_take_tube_out_of_reaction_disc_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手从反应盘取管握手标记以及转运抓手从反应盘取管回复标记。
	set_take_tube_out_of_reaction_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_reaction_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手从反应盘取管指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: put_tube_in_washing_disc
 * brief: 命令转运抓手放管到清洗盘。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TransportTong::put_tube_in_washing_disc(){
	//1.创建转运抓手放管到清洗盘指令，并且判断创建是否成功。
	Command command;
	if(command.generate_put_tube_in_washing_disc_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除转运抓手放管到清洗盘握手标记以及转运抓手放管到清洗盘回复标记。
	set_put_tube_in_washing_disc_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_washing_disc_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("转运抓手放管到清洗盘指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_take_tube_out_of_detection_disc_shake_hand_flag
 * breif: 设置从检测盘取管握手标志。
 * param: flag - 输入的从检测盘取管握手标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_detection_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置从检测盘取管握手标志。
	_take_tube_out_of_detection_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_detection_disc_shake_hand_flag
 * brief: 获取从检测盘取管握手标志。
 * param: --
 * return: 返回从检测盘取管握手标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_detection_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回从检测盘取管握手标志。
	return(_take_tube_out_of_detection_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_detection_disc_response_flag
 * brief: 设置从检测盘取管回复标志。
 * param: flag - 输入的从检测盘取管回复标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_detection_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置从检测盘取管回复标志。
	_take_tube_out_of_detection_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_detection_disc_response_flag
 * brief: 获取从检测盘取管回复标志。
 * param: --
 * return: 返回从检测盘取管回复标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_detection_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回从检测盘取管回复标志。
	return(_take_tube_out_of_detection_disc_response_flag);
}

/**
 * name: set_discard_tube_shake_hand_flag
 * brief: 设置丢管握手指令。
 * param: flag - 输入的丢管握手指令。
 * return: --
 */
void TransportTong::set_discard_tube_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置丢管握手指令。
	_discard_tube_shake_hand_flag=flag;
}

/**
 * name: get_discard_tube_shake_hand_flag
 * brief: 获取丢管握手指令。
 * param: --
 * return: 返回丢管握手指令。
 */
TransportTong::Flag TransportTong::get_discard_tube_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回丢管握手指令。
	return(_discard_tube_shake_hand_flag);
}

/**
 * name: set_discard_tube_response_flag
 * brief: 设置丢管回复标志。
 * param: flag - 输入的丢管回复标志。
 * return: --
 */
void TransportTong::set_discard_tube_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置丢管回复标志。
	_discard_tube_response_flag=flag;
}

/**
 * name: get_discard_tube_response_flag
 * brief: 获取丢管回复标志。
 * param: --
 * return: 返回丢管回复标志。
 */
TransportTong::Flag TransportTong::get_discard_tube_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回丢管回复标志。
	return(_discard_tube_response_flag);
}

/**
 * name: set_take_tube_out_of_washing_disc_shake_hand_flag
 * brief: 设置从清洗盘取管握手标志。
 * param: flag - 输入的从清洗盘取管握手标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_washing_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置从清洗盘取管握手标志。
	_take_tube_out_of_washing_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_washing_disc_shake_hand_flag
 * brief: 获取从清洗盘取管握手标志。
 * param: --
 * return: 返回从清洗盘取管握手标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_washing_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回从清洗盘取管握手标志。
	return(_take_tube_out_of_washing_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_washing_disc_response_flag
 * brief: 设置从清洗盘取管回复标志。
 * param: flag - 输入的从清洗盘取管回复标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_washing_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置从清洗盘取管回复标志。
	_take_tube_out_of_washing_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_washing_disc_response_flag
 * brief: 获取从清洗盘取管回复标志。
 * param: --
 * return: 返回从清洗盘取管回复标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_washing_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回从清洗盘取管回复标志。
	return(_take_tube_out_of_washing_disc_response_flag);
}

/**
 * name: set_return_tube_to_reaction_disc_shake_hand_flag
 * brief: 设置转运抓手回管到反应盘握手标志。
 * param: flag - 输入的转运抓手回管到反应盘握手标志。
 * return: --
 */
void TransportTong::set_return_tube_to_reaction_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手回管到反应盘握手标志。
	_return_tube_to_reaction_disc_shake_hand_flag=flag;
}

/**
 * name: get_return_tube_to_reaction_disc_shake_hand_flag
 * brief: 获取转运抓手回管到反应盘握手标志。
 * param: --
 * return: 返回转运抓手回管到反应盘握手标志。
 */
TransportTong::Flag TransportTong::get_return_tube_to_reaction_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手回管到反应盘握手标志。
	return(_return_tube_to_reaction_disc_shake_hand_flag);
}


/**
 * name: set_return_tube_to_reaction_disc_response_flag
 * brief: 设置转运抓手回管到反应盘回复标志。
 * param: flag - 输入的转运抓手回管到反应盘回复标志。
 * return: --
 */
void TransportTong::set_return_tube_to_reaction_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手回管到反应盘回复标志。
	_return_tube_to_reaction_disc_response_flag=flag;
}

/**
 * name: get_return_tube_to_reaction_disc_response_flag
 * brief: 获取转运抓手回管到反应盘回复标志。
 * param: --
 * return: 返回转运抓手回管到反应盘回复标志。
 */
TransportTong::Flag TransportTong::get_return_tube_to_reaction_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手回管到反应盘回复标志。
	return(_return_tube_to_reaction_disc_response_flag);
}

/**
 * name: set_put_tube_in_detection_disc_shake_hand_flag
 * brief: 设置转运抓手放管到检测盘握手标志。
 * param: flag - 输入的转运抓手放管到检测盘握手标志。
 * return: --
 */
void TransportTong::set_put_tube_in_detection_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手放管到检测盘握手标志。
	_put_tube_in_detection_disc_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_detection_disc_shake_hand_flag
 * brief: 获取转运抓手放管到检测盘握手标志。
 * param: --
 * return: 返回转运抓手放管到检测盘握手标志。
 */
TransportTong::Flag TransportTong::get_put_tube_in_detection_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手放管到检测盘握手标志。
	return(_put_tube_in_detection_disc_shake_hand_flag);
}

/**
 * name: set_put_tube_in_detection_disc_response_flag
 * brief: 设置转运抓手放管到检测盘回复标志。
 * param: flag - 输入的转运抓手放管到检测盘回复标志。
 * return: --
 */
void TransportTong::set_put_tube_in_detection_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手放管到检测盘回复标志。
	_put_tube_in_detection_disc_response_flag=flag;
}

/**
 * name: get_put_tube_in_detection_disc_response_flag
 * brief: 获取转运抓手放管到检测盘回复标志。
 * param: --
 * return: 返回转运抓手放管到检测盘回复标志。
 */
TransportTong::Flag TransportTong::get_put_tube_in_detection_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手放管到检测盘回复标志。
	return(_put_tube_in_detection_disc_response_flag);
}

/**
 * name: set_take_tube_out_of_reaction_disc_shake_hand_flag
 * brief: 设置转运抓手从反应盘取管握手标志。
 * param: flag - 输入的转运抓手从反应盘取管握手标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_reaction_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手从反应盘取管握手标志。
	_take_tube_out_of_reaction_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_reaction_disc_shake_hand_flag
 * brief: 获取转运抓手从反应盘取管握手标志。
 * param: --
 * return: 返回转运抓手从反应盘取管握手标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_reaction_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手从反应盘取管握手标志。
	return(_take_tube_out_of_reaction_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_reaction_disc_response_flag
 * brief: 设置转运抓手从反应盘取管回复标志。
 * param: flag - 输入的转运抓手从反应盘取管回复标志。
 * return: --
 */
void TransportTong::set_take_tube_out_of_reaction_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置转运抓手从反应盘取管回复标志。
	_take_tube_out_of_reaction_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_reaction_disc_response_flag
 * brief: 获取转运抓手从反应盘取管回复标志。
 * param: --
 * return: 返回转运抓手从反应盘取管回复标志。
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_reaction_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回转运抓手从反应盘取管回复标志。
	return(_take_tube_out_of_reaction_disc_response_flag);
}

/**
 * name: set_put_tube_in_washing_disc_shake_hand_flag
 * brief: 设置放管到清洗盘握手标志。
 * param: flag - 输入的放管到清洗盘握手标志。
 * return: --
 */
void TransportTong::set_put_tube_in_washing_disc_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置放管到清洗盘握手标志。
	_put_tube_in_washing_disc_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_washing_disc_shake_hand_flag
 * brief: 获取放管到清洗盘握手指令标志。
 * param: --
 * return: 返回放管到清洗盘握手指令标志。
 */
TransportTong::Flag TransportTong::get_put_tube_in_washing_disc_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回放管到清洗盘握手标志。
	return(_put_tube_in_washing_disc_shake_hand_flag);
}

/**
 * name: set_put_tube_in_washing_disc_response_flag
 * brief: 设置放管到清洗盘回复标志。
 * param: flag - 输入的放管到清洗盘回复标志。
 * return: --
 */
void TransportTong::set_put_tube_in_washing_disc_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置放管到清洗盘回复标志。
	_put_tube_in_washing_disc_response_flag=flag;
}

/**
 * name: get_put_tube_in_washing_disc_response_flag
 * brief: 获取放管到清洗盘回复指令标志。
 * param: --
 * return: 返回放管到清洗盘回复指令标志。
 */
TransportTong::Flag TransportTong::get_put_tube_in_washing_disc_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回放管到清洗盘回复标志。
	return(_put_tube_in_washing_disc_response_flag);
}