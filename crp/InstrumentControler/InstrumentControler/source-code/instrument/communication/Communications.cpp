#include"stdafx.h"
#include"Communications.h"
#include"ControlPort.h"

/**
 * name: Communications
 * brief: ���캯����
 * param: --
 * return: --
 */
Communications::Communications(void)
	:_control_port(new ControlPort){
}

/**
 * name: ~Communications
 * breif: ����������
 * param: --
 * return: --
 */
Communications::~Communications(void){
	delete _control_port;
}

/**
 * name: get_control_port
 * brief: ��ȡ���ƶ˿ڡ�
 * param: --
 * return: ���ؿ��ƶ˿ڡ�
 */
ControlPort *Communications::get_control_port(){
	return(dynamic_cast<ControlPort*>(get_port(
		PORT_ID_CONTROL)));
}

/**
 * name: get_port
 * brief: ��ȡָ����ͨ�Ŷ˿ڡ�
 * param: port_id - �����ָ����ͨ�Ŷ˿ڡ�
 * return: �������ִ�гɹ�����ָ��ָ����ͨ�Ŷ˿�ָ�룬���򷵻ؿ�ָ�롣
 */
Port *Communications::get_port(const PortID port_id){
	switch(port_id){
	case PORT_ID_CONTROL:
		return(_control_port);
	default:
		return(0);
	}
}