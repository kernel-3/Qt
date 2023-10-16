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
 * brief: ���豸��
 * param: --
 * return: ������豸�ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int InstrumentControler::open_instrument(){
	return((((Instrument::instance())->get_communications())->
		get_control_port())->open());
}

/**
 * name: close_instrument
 * brief: �ر��豸��
 * param: --
 * return: --
 */
void InstrumentControler::close_instrument(){
	(((Instrument::instance())->get_communications())->
		get_control_port())->close();
}

/**
 * name: open_timing
 * brief: ��ʱ��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int InstrumentControler::open_timing(){
	return((((Instrument::instance())->get_functions())->
		get_timing())->start());
}

/**
 * name: close_timing
 * brief: �ر�ʱ��
 * parma: --
 * return: --
 */
void InstrumentControler::close_timing(){
	return((((Instrument::instance())->get_functions())->
		get_timing())->stop());
}

/**
 * name: add_pending_test_item_for_timing
 * brief: Ϊʱ�����Ӵ�����Ŀ��
 * param: test_item - ����Ĵ�����Ŀ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int InstrumentControler::add_pending_test_item_for_timing(
	const TestItem test_item){
	return((((Instrument::instance())->get_functions())->
		get_timing())->push_back_pending_test_item(test_item));
}