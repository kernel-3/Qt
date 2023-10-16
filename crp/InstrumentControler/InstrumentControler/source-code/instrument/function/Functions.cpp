#include"stdafx.h"
#include"Functions.h"
#include"timing/Timing.h"

/**
 * name: Functions
 * brief: 构造函数。
 * param: --
 * return: --
 */
Functions::Functions(void)
	:_timing(new Timing){
}

/**
 * name: ~Functions
 * breif: 析构函数。
 * param: --
 * return: --
 */
Functions::~Functions(void){
	delete _timing;
}

/**
 * name: get_timing
 * brief: 获取时序功能。
 * param: --
 * return: 返回时序功能。
 */
Timing *Functions::get_timing(){
	return(dynamic_cast<Timing*>(get_function(
		FUNCTION_ID_TIMING)));
}

/**
 * name: get_function
 * brief: 获取指定的功能。
 * param: function_id - 输入的功能标识。
 * return: 如果函数执行成功返回指向指定功能的指针，否则
 *         返回空指针。
 */
Function *Functions::get_function(const FunctionID function_id){
	//1.如果当前期望获取时序功能，则直接返回时序功能。
	if(FUNCTION_ID_TIMING==function_id){
		return(_timing);
	}
	//..如果当前期望获取其它功能，则直接返回空指针。
	else{
		return(0);
	}
}