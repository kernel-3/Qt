#pragma once

#include"Application.h"
#include"../common/Item.h"
#include<memory>

/**
 * name: ApplicationFinder
 * breif: 项目申请参数查找类，负责提供方法查找指定的项目申请参数。
 * author: yameng_he
 * date: 2015-06-16
 */
template<typename _Tp>
class ApplicationFinder{
//define
public:
	typedef enum{FIND_METHOD_BY_ITEM_NO,
		FIND_METHOD_BY_ITEM_ID,}FindMethod;
	typedef std::shared_ptr<Application> PtrToApp;
//construction & destruction
public:
	ApplicationFinder(const _Tp value,
		const FindMethod method);
	~ApplicationFinder();
//interface
public:
	bool operator()(const PtrToApp &application) const;
//variables
private:
	_Tp _value;
	FindMethod _method;
};

/**
 * name: ApplicationFinder
 * brief: 构造函数。
 * param: value - 查找依靠的值。
 *        method - 查找依靠的方法。
 * return: --
 */
template<typename _Tp>
ApplicationFinder<_Tp>::ApplicationFinder(
	const _Tp value,const FindMethod method)
	:_value(value)
	,_method(method){
}

/**
 * name: ~ApplicationFinder
 * brief: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
ApplicationFinder<_Tp>::~ApplicationFinder(){
}

/**
 * name: operator()
 * brief: 重载()操作符，提供项目申请参数查找功能。
 * param: application - 只向指定的项目申请参数。
 * return: 如果当前值等于指定项目申请参数中的相应值返回true，否则返回false。
 */
template<typename _Tp>
bool ApplicationFinder<_Tp>::operator()(const PtrToApp &application) const{
	//1.如果当前传递参数不合法，则直接返回false。
	if(!static_cast<bool>(application)){
		return(false);
	}
	//2.如果当前查找方法为通过项目序号查找。
	if(FIND_METHOD_BY_ITEM_NO==_method){
		return(static_cast<int>(_value)==(application->get_item()).get_no());
	}
	//3.如果当前查找方法为通过项目标识查找。
	else if(FIND_METHOD_BY_ITEM_ID==_method){
		return(static_cast<int>(_value)==(application->get_item()).get_id());
	}
	//4.如果当前查找方法未知，则直接返回false。
	else{
		return(false);
	}
}