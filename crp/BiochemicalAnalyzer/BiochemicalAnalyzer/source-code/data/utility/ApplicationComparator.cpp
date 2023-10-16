#include"stdafx.h"
#include"ApplicationComparator.h"
#include"Application.h"
#include"../common/Item.h"
#include<assert.h>

/**
 * name: ApplicationComparator
 * breif: 构造函数。
 * param: method - 比较方法。
 * return: --
 */
ApplicationComparator::ApplicationComparator(
	const CompareMethod method)
	:_method(method){
}

/**
 * name: ~ApplicationComparator
 * breif: 析构函数。
 * param: --
 * return: --
 */
ApplicationComparator::~ApplicationComparator(void){
}

/**
 * name: operator()
 * breif: 重载()操作符，提供申请参数比较方法。
 * param: left - 指定比较的申请参数。
 *        right - 指定比较的申请参数。
 * return: 如果left小于right则返回true，否则返回false。
 */
bool ApplicationComparator::operator()(
	const PtrToApp &left,const PtrToApp &right) const{
	//1.确保当前函数的参数合法（如果不合法则比较无意义）。
	assert(static_cast<bool>(left)&&static_cast<bool>(right));
	//2.如果当前的比较方法为项目ID比较。
	if(COMPARE_METHOD_BY_ITEM_ID==_method){
		return(((left->get_item()).get_id())<
			((right->get_item()).get_id()));
	}
	//3.如果当前的比较方法为项目序号比较。
	else if(COMPARE_METHOD_BY_ITEM_NO==_method){
		return(((left->get_item()).get_no())<
			((right->get_item()).get_no()));
	}
	//..如果程序运行到此则说明发生异常.
	else{
		assert(0);//运行到此必为异常。
		return(false);
	}
}