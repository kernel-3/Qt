#include"stdafx.h"
#include"LoadTong.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"TubeStorehouse.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: LoadTong
 * brief: 构造函数。
 * param: --
 * return: --
 */
LoadTong::LoadTong(void)
	:Component()
	,_lock(new MtLock)
	,_take_tube_out_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_response_flag(FLAG_IDLE)
	,_put_tube_in_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_response_flag(FLAG_IDLE)
	,_having_tube_flag(FALSE){
}

/**
 * name: ~LoadTong
 * brief: 析构函数。
 * param: --
 * return: --
 */
LoadTong::~LoadTong(void){
	delete _lock;
}

/**
 * name: take_tube_out
 * brief: 命令装载抓手到指定位置取管。
 * param: row - 输入指定取管位置的行。
 *        col - 输入指定取管位置的列。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LoadTong::take_tube_out(const unsigned int row,const unsigned int col){
	//1.检测输入的参数是否合法。
	if((row<1)||(row>TubeStorehouse::ROW_COUNT)){
		return(-1);
	}
	if((col<1)||(col>TubeStorehouse::COL_COUNT)){
		return(-2);
	}
	//2.创建装载抓手取管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_load_tong_take_tube_out_command(row,col)<0){
		return(-3);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除装载抓手取管握手标记以及装载抓手取管回复标记。
	set_take_tube_out_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("装载抓手取管指令"))<0){
		return(-4);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: put_tube_in
 * breif: 命令装载抓手放管。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int LoadTong::put_tube_in(){
	//1.创建装载抓手放管指令，并且判断创建是否成功。
	Command command;
	if(command.generate_load_tong_put_tube_in_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除装载抓手放管握手标记以及装载抓手放管回复标记。
	set_put_tube_in_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("装载抓手放管指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_take_tube_out_shake_hand_flag
 * brief: 设置取管握手标记。
 * param: flag - 输入的取管握手标记。
 * return: --
 */
void LoadTong::set_take_tube_out_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置取管握手标记。
	_take_tube_out_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_shake_hand_flag
 * brief: 获取取管握手标记。
 * param: --
 * return: 返回取管握手标记。
 */
LoadTong::Flag LoadTong::get_take_tube_out_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回取管握手标记。
	return(_take_tube_out_shake_hand_flag);
}

/**
 * name: set_take_tube_out_response_flag
 * brief: 设置取管回复标记。
 * param: flag - 输入的取管回复标记。
 * return: --
 */
void LoadTong::set_take_tube_out_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置取管完成标记。
	_take_tube_out_response_flag=flag;
}

/**
 * name: get_take_tube_out_finish_flag
 * brief: 获取取管回复标识。
 * param: --
 * return: 返回取管回复标识。
 */
LoadTong::Flag LoadTong::get_take_tube_out_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回取管完成标记。
	return(_take_tube_out_response_flag);
}

/**
 * name: set_put_tube_in_shake_hand_flag
 * brief: 设置放管握手标记。
 * param: flag - 输入的放管握手标记。
 * return: --
 */
void LoadTong::set_put_tube_in_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置放管握手标记。
	_put_tube_in_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_shake_hand_flag
 * breif: 获取放管握手标记。
 * param: --
 * return: 返回放管握手标记。
 */
LoadTong::Flag LoadTong::get_put_tube_in_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回放管握手标记。
	return(_put_tube_in_shake_hand_flag);
}

/**
 * name: set_put_tube_in_response_flag
 * breif: 设置放管回复标记。
 * param: flag - 输入的放管回复标记。
 * return: --
 */
void LoadTong::set_put_tube_in_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置放管握手标记。
	_put_tube_in_response_flag=flag;
}

/**
 * name: get_put_tube_in_response_flag
 * breif: 获取放管回复标记。
 * param: --
 * return: 返回放管回复标记。
 */
LoadTong::Flag LoadTong::get_put_tube_in_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回放管握手标记。
	return(_put_tube_in_response_flag);
}

/**
 * name: set_having_tube_flag
 * brief: 设置装载抓手有管标记。
 * param: flag - 输入的装载抓手有管标记。
 * return: --
 */
void LoadTong::set_having_tube_flag(const BOOL flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置装载抓手有管标记。
	_having_tube_flag=flag;
}

/**
 * name: get_having_tube_flag
 * brief: 获取装载抓手有管标记。
 * param: --
 * return: 返回装载抓手有管标记。
 */
BOOL LoadTong::get_having_tube_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回状态抓手有管标记。
	return(_having_tube_flag);
}