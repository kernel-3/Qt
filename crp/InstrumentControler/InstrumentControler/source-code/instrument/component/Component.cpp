#include"stdafx.h"
#include"Component.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"

//初始化静态变量。
Component::Lock Component::_control_lock(new MtLock);

/**
 * name: Component
 * brief: 构造函数。
 * param: --
 * return: --
 */
Component::Component(void){
}

/**
 * name: ~Component
 * breif: 析构函数。
 * param: --
 * return: --
 */
Component::~Component(void){
}

/**
 * name: get_control_lock
 * brief: 获取当前组件中的控制锁。
 * param: --
 * return: 返回当前指向组件控制锁的指针。
 */
MtLock *Component::get_control_lock(){
	return(_control_lock.get());
}