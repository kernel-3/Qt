#include"stdafx.h"
#include"Communications.h"
#include"ControlPort.h"

/**
 * name: Communications
 * brief: 构造函数。
 * param: --
 * return: --
 */
Communications::Communications(void)
	:_control_port(new ControlPort){
}

/**
 * name: ~Communications
 * breif: 析构函数。
 * param: --
 * return: --
 */
Communications::~Communications(void){
	delete _control_port;
}

/**
 * name: get_control_port
 * brief: 获取控制端口。
 * param: --
 * return: 返回控制端口。
 */
ControlPort *Communications::get_control_port(){
	return(dynamic_cast<ControlPort*>(get_port(
		PORT_ID_CONTROL)));
}

/**
 * name: get_port
 * brief: 获取指定的通信端口。
 * param: port_id - 输入的指定的通信端口。
 * return: 如果函数执行成功返回指向指定的通信端口指针，否则返回空指针。
 */
Port *Communications::get_port(const PortID port_id){
	switch(port_id){
	case PORT_ID_CONTROL:
		return(_control_port);
	default:
		return(0);
	}
}