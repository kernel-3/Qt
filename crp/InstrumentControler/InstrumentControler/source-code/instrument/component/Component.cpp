#include"stdafx.h"
#include"Component.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"

//��ʼ����̬������
Component::Lock Component::_control_lock(new MtLock);

/**
 * name: Component
 * brief: ���캯����
 * param: --
 * return: --
 */
Component::Component(void){
}

/**
 * name: ~Component
 * breif: ����������
 * param: --
 * return: --
 */
Component::~Component(void){
}

/**
 * name: get_control_lock
 * brief: ��ȡ��ǰ����еĿ�������
 * param: --
 * return: ���ص�ǰָ�������������ָ�롣
 */
MtLock *Component::get_control_lock(){
	return(_control_lock.get());
}