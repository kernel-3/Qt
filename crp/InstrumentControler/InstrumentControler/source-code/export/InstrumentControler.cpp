#include"stdafx.h"
#include"InstrumentControler.h"
#include"../Instrument/Instrument.h"
#include"../Instrument/communication/Communications.h"
#include"../Instrument/communication/ControlPort.h"
#include"../Instrument/function/Functions.h"
#include"../Instrument/function/timing/Timing.h"
#include"TestItem.h"

/**
 * name: open_instrument
 * brief: 打开设备。
 * param: --
 * return: 如果打开设备成功返回值大于等于零，否则返回值小于零。
 */
int InstrumentControler::open_instrument(){
	return((((Instrument::instance())->get_communications())->
		get_control_port())->open());
}

/**
 * name: close_instrument
 * brief: 关闭设备。
 * param: --
 * return: --
 */
void InstrumentControler::close_instrument(){
	(((Instrument::instance())->get_communications())->
		get_control_port())->close();
}

/**
 * name: open_timing
 * brief: 打开时序。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int InstrumentControler::open_timing(){
	return((((Instrument::instance())->get_functions())->
		get_timing())->start());
}

/**
 * name: close_timing
 * brief: 关闭时序。
 * parma: --
 * return: --
 */
void InstrumentControler::close_timing(){
	return((((Instrument::instance())->get_functions())->
		get_timing())->stop());
}

/**
 * name: add_pending_test_item_for_timing
 * brief: 为时序增加待测项目。
 * param: test_item - 输入的待测项目。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int InstrumentControler::add_pending_test_item_for_timing(
	const TestItem test_item){
	return((((Instrument::instance())->get_functions())->
		get_timing())->push_back_pending_test_item(test_item));
}