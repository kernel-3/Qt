#include"stdafx.h"
#include"WashingDisc.h"
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
 * name: WashingDisc
 * brief: 构造函数。
 * param: --
 * return: --
 */
WashingDisc::WashingDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_wash_shake_hand_flag(FLAG_IDLE)
	,_wash_response_flag(FLAG_IDLE)
	,_having_tube_in_entry_flag(FLAG_UNKNOWN)
	,_having_tube_in_entry_flag_expect_value(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag_expect_value(FLAG_UNKNOWN)
	,_hole_no_in_entry(1){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));//将洞的所有状态设备为空。
}

/**
 * name: ~WashingDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
WashingDisc::~WashingDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: 命令清洗盘旋转。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int WashingDisc::rotate(){
	//1.创建清洗盘旋转指令，并且判断创建是否成功。
	Command command;
	if(command.generate_washing_disc_rotation_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除清洗盘旋转握手标记以及清洗盘旋转完成标记。
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("清洗盘旋转指令"))<0){
		return(-2);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: wash
 * brief: 命令清洗盘清洗。
 * param: substrate_type - 输入的底物类型。
 *        substrate_volume - 输入的底物体积。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int WashingDisc::wash(const SubstrateType substrate_type/*=SUBSTRATE_TYPE_NONE*/,
	const unsigned int substrate_volume/*=0*/){
	//1.计算清洗盘清洗所需参数。
	const unsigned int washing_liquid_volume=get_washing_liquid_volume();
	const BOOL is_washing_position_1_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_1))?TRUE:FALSE);
	const BOOL is_washing_position_2_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_2))?TRUE:FALSE);
	const BOOL is_washing_position_3_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_3))?TRUE:FALSE);
	const BOOL is_washing_position_4_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_4))?TRUE:FALSE);
	//2.创建清洗盘清洗指令，并且判断创建是否成功。
	Command command;
	if(command.generate_washing_disc_wash_command(
		static_cast<unsigned int>(substrate_type),substrate_volume,washing_liquid_volume,
		is_washing_position_1_need_washing,is_washing_position_2_need_washing,
		is_washing_position_3_need_washing,is_washing_position_4_need_washing)<0){
		return(-1);
	}
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.清除清洗盘清洗握手标记以及清洗盘清洗完成标记。
	set_wash_shake_hand_flag(FLAG_BUSY);
	set_wash_response_flag(FLAG_BUSY);
	//5.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("清洗盘清洗指令"))<0){
		return(-2);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: inquire_sensor
 * brief: 查询清洗盘上的传感器，并且判断查询是否成功。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int WashingDisc::inquire_sensor(){
	//1.创建查询传感器指令，并且判断创建是否成功。
	Command command;
	if(command.generate_inquire_sensors_command()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.清除清洗盘上各个传感器标志。
	set_having_tube_in_entry_flag(FLAG_UNKNOWN);
	set_having_tube_in_exit_flag(FLAG_UNKNOWN);
	//4.发送指令，并且判断指令发送是否成功。
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("查询设备上的位置传感器指令"))<0){
		return(-2);
	}
	//5.循环等待清洗盘上位置传感器状态返回，并且判断是否超时。
	//5-1.记录当前起始时间。
	DWORD last_time=timeGetTime();
	//5-2.循环检测清洗盘上位置传感器状态是否成功返回。
	while(1){
		//5-2-1.如果清洗盘上位置传感器状态成功返回。
		if((FLAG_UNKNOWN!=get_having_tube_in_entry_flag())&&(
			FLAG_UNKNOWN!=get_having_tube_in_exit_flag())){
			return(0);
		}
		//5-2-2.如果清洗盘上位置传感器状态尚未返回。
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
	//6.程序运行到此直接返回错误。
	return(-4);
}

/**
 * name: set_rotation_shake_hand_flag
 * breif: 设置清洗盘旋转握手标记。
 * param: flag - 输入的旋转握手标记。
 * return: --
 */
void WashingDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘旋转握手标记。
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: 获取清洗盘旋转握手标记。
 * param: --
 * return: 返回清洗盘旋转握手标记。
 */
WashingDisc::Flag WashingDisc::get_rotation_shake_hand_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘旋转握手标记。
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: 设置清洗盘旋转回复标记。
 * param: flag - 输入清洗盘旋转回复标记。
 * return: --
 */
void WashingDisc::set_rotation_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘旋转回复标记。
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: 获取清洗盘旋转回复标记。
 * param: --
 * return: 返回清洗盘旋转回复标记。
 */
WashingDisc::Flag WashingDisc::get_rotation_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘旋转回复标记。
	return(_rotation_response_flag);
}

/**
 * name: set_wash_shake_hand_flag
 * brief: 设置清洗握手标志。
 * param: flag - 输入的清洗握手标志。
 * return: --
 */
void WashingDisc::set_wash_shake_hand_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗握手标志。
	_wash_shake_hand_flag=flag;
}

/**
 * name: get_wash_shake_hand_flag
 * breif: 获取清洗握手标志。
 * param: --
 * return: 返回清洗握手标志。
 */
WashingDisc::Flag WashingDisc::get_wash_shake_hand_flag() const{
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
void WashingDisc::set_wash_response_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗回复标志。
	_wash_response_flag=flag;
}

/**
 * name: get_wash_response_flag
 * brief: 获取清洗回复标志。
 * param: --
 * return: 返回清洗回复标志。
 */
WashingDisc::Flag WashingDisc::get_wash_response_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗回复标志。
	return(_wash_response_flag);
}

/**
 * name: set_having_tube_in_entry_flag
 * breif: 设置清洗盘进管位有管标志。
 * param: flag - 输入的清洗盘进管位有管标志。
 * return: --
 */
void WashingDisc::set_having_tube_in_entry_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘进管位有管标志。
	_having_tube_in_entry_flag=flag;
}

/**
 * name: get_having_tube_in_entry_flag
 * brief: 获取清洗盘进管位有管标志。
 * param: --
 * return: 返回清洗盘进管位有管标志。
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_entry_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘进管位有管标志。
	return(_having_tube_in_entry_flag);
}

/**
 * name: set_having_tube_in_entry_flag_expect_value
 * breif: 设置清洗盘进管位有管标志的期望值。
 * param: value - 输入的反应盘进管位有管标志的期望值。
 * return: --
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
void WashingDisc::set_having_tube_in_entry_flag_expect_value(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘进管位有管标志的期望值。
	_having_tube_in_entry_flag_expect_value=flag;
}

/**
 * name: get_having_tube_in_entry_flag_expect_value
 * brief: 获取清洗盘进管位有管标志的期望值。
 * param: --
 * return: 返回清洗盘进管位有管标志的期望值。
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_entry_flag_expect_value() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘进管位有管标志的期望值。
	return(_having_tube_in_entry_flag_expect_value);
}

/**
 * name: set_having_tube_in_exit_flag
 * brief: 设置清洗盘出管位有管标志。
 * param: flag - 输入的清洗盘出管位有管标志。
 * return: --
 */
void WashingDisc::set_having_tube_in_exit_flag(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘出管位有管标志。
	_having_tube_in_exit_flag=flag;
}

/**
 * name: get_having_tube_in_exit_flag
 * brief: 获取清洗盘出管位有管标志。
 * param: --
 * return: 返回清洗盘出管位有管标志。
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_exit_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘出管位有管标志。
	return(_having_tube_in_exit_flag);
}

/**
 * name: set_having_tube_in_exit_flag_expect_value
 * brief: 设置清洗盘出管位有管标志的期望值。
 * param: flag - 输入的清洗盘出管位有管标志的期望值。
 * return: --
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
void WashingDisc::set_having_tube_in_exit_flag_expect_value(const Flag flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘进管位有管标志的期望值。
	_having_tube_in_exit_flag_expect_value=flag;
}

/**
 * name: get_having_tube_in_exit_flag_expect_value
 * brief: 获取清洗盘出管位有管标志的期望值。
 * param: --
 * return: 返回清洗盘出管位有管标志的期望值。
 * remark: 此函数只在自发自收的调试环境下起作用。
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_exit_flag_expect_value() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘进管位有管标志的期望值。
	return(_having_tube_in_exit_flag_expect_value);
}

/**
 * name: reset_hole_no_in_entry
 * brief: 重置清洗盘进管位孔号。
 * param: --
 * return: --
 */
void WashingDisc::reset_hole_no_in_entry(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.重置清洗盘进管位孔号。
	_hole_no_in_entry=1;
}

/**
 * name: decrease_hole_no_in_entry
 * breif: 递减清洗盘进管位孔号。
 * param: --
 * return: --
 */
void WashingDisc::decrease_hole_no_in_entry(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.递减清洗盘进管位孔号。
	if(_hole_no_in_entry<=1){
		_hole_no_in_entry=29;
	}else{
		--_hole_no_in_entry;
	}
}

/**
 * name: are_there_tubes
 * brief: 检测清洗盘上是否有管。
 * param: --
 * return: 如果清洗盘上有管返回TRUE，否则返回FALSE。
 */
BOOL WashingDisc::are_there_tubes() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历清洗盘上的孔，检测孔中是否有管。
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if((HOLE_STATE_USED==_hole_state[index])||
			(HOLE_STATE_FAILED==_hole_state[index])){
			return(TRUE);
		}
	}
	//3.程序运行到此，则认为清洗盘上无管。
	return(FALSE);
}

/**
 * name: set_hole_state
 * brief: 设置清洗盘指定位置的孔状态。
 * param: position - 输入的指定位置。
 *        state - 输入的孔状态。
 * return: --
 */
void WashingDisc::set_hole_state(
	const Position position,const HoleState state){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置清洗盘指定位置的孔状态。
	_hole_state[get_hole_no(position)-1]=state;
}

/**
 * name: get_hole_state
 * brief: 获取清洗盘指定位置的孔状态。
 * param: position - 输入的指定位置。
 * return: 返回清洗盘指定位置的孔状态。
 */
WashingDisc::HoleState WashingDisc::get_hole_state(
	const Position position) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回清洗盘指定位置的孔状态。
	return(_hole_state[get_hole_no(position)-1]);
}

/**
 * name: get_hole_no
 * breif: 获取指定位置上的孔号。
 * param: position - 输入的指定位置。
 * return: 返回指定位置上的孔号。
 */
unsigned int WashingDisc::get_hole_no(const Position position) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.声明当前操作所需变量。
	unsigned int hole_no=_hole_no_in_entry;
	//3.如果当前期望获取清洗盘第一清洗位上的孔号。
	if(POSITION_WASHING_1==position){
		hole_no+=5;
	}
	//4.如果当前期望获取清洗盘第二清洗位上的孔号。
	else if(POSITION_WASHING_2==position){
		hole_no+=9;
	}
	//5.如果当前获取清洗盘第三清洗位上的孔号。
	else if(POSITION_WASHING_3==position){
		hole_no+=13;
	}
	//6.如果当前获取清洗盘第四清洗位上的孔号。
	else if(POSITION_WASHING_4==position){
		hole_no+=17;
	}
	//7.如果当前获取清洗盘底物位上的孔号。
	else if(POSITION_SUBSTRATE==position){
		hole_no+=18;
	}
	//8.如果当前获取清洗盘出管位上的孔号。
	else if(POSITION_EXIT==position){
		hole_no+=19;
	}
	//9.将孔号限定在合法范围内。
	if(hole_no>HOLE_COUNT){
		hole_no=hole_no-HOLE_COUNT;
	}
	//10.程序运行到此直接返回孔号。
	return(hole_no);
}

/**
 * name: get_washing_liquid_volume
 * brief: 获取清洗液体积。
 * param: --
 * return: 返回清洗液体积。
 */
unsigned int WashingDisc::get_washing_liquid_volume() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前配置文件中保存的清洗液体积。
	int washing_liquid_volume=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("WASHINGDISC"),_T("WASHING_LIQUID_VOLUME"));
	if(washing_liquid_volume<0){
		washing_liquid_volume=0;
	}else if(washing_liquid_volume>1000){
		washing_liquid_volume=1000;
	}
	//3.返回当前获取的清洗液体积。
	return(static_cast<unsigned int>(washing_liquid_volume));
}