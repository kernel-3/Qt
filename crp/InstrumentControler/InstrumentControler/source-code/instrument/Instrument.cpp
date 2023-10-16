#include"stdafx.h"
#include"Instrument.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtAutoDeleter.h"
#include"Communication/Communications.h"
#include"Communication/ControlPort.h"
#include"component/Components.h"
#include"function/Functions.h"
#include"component/ReactionDisc.h"

/**
 * name: ~Instrument
 * breif: 析构函数。
 * param: --
 * return: --
 */
Instrument::~Instrument(void){
	delete _functions;
	delete _components;
	delete _communications;
}

/**
 * name: instance
 * brief: 为当前类创建系统中唯一实例。
 * param: --
 * return: 返回系统中指向当前类的唯一实例指针。
 */
Instrument *Instrument::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_functions
 * brief: 获取设备中的功能类。
 * param: --
 * return: 返回设备中的功能类。
 */
Functions *Instrument::get_functions(){
	return(_functions);
}

/**
 * name: get_components
 * brief: 获取当前设备中的组件管理类。
 * param: --
 * return: 返回当前设备中的组件管理类。
 */
Components *Instrument::get_components(){
	return(_components);
}

/**
 * name: get_communications
 * breif: 获取当前设备中的通讯管理类。
 * param: --
 * return: 返回当前设备中的通讯管理类。
 */
Communications *Instrument::get_communications(){
	return(_communications);
}

/**
 * name: Instrument
 * brief: 构造函数。
 * param: --
 * return: --
 */
Instrument::Instrument(void)
	:_functions(new Functions)
	,_components(new Components)
	,_communications(new Communications){
}