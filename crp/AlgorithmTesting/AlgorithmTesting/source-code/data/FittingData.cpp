#include"stdafx.h"
#include"FittingData.h"
#include<math.h>

/**
 * name: FittingData
 * breif: 构造函数。
 * param: --
 * return: --
 */
FittingData::FittingData(void)
	:_x(0.0)
	,_y(0.0){
}

/**
 * name: FittingData
 * breif: 构造函数。
 * param: x - 指定的x值。
 *        y - 指定的y值。
 * return: --
 */
FittingData::FittingData(const double x,const double y)
	:_x(x)
	,_y(y){
}

/**
 * name: ~FittingData
 * breif: 析构函数。
 * param: --
 * return: --
 */
FittingData::~FittingData(void){
}

/**
 * name: set_x
 * breif: 设置x。
 * param: x - 指定x的值。
 * return: --
 */
void FittingData::set_x(const double x){
	_x=x;
}

/**
 * name: get_x
 * breif: 获取x。
 * param: --
 * return: 返回x。
 */
double FittingData::get_x() const{
	return(_x);
}

/**
 * name: set_y
 * breif: 设置y。
 * param: y - 指定y的值。
 * return: --
 */
void FittingData::set_y(const double y){
	_y=y;
}

/**
 * name: get_y
 * breif: 获取y。
 * parma: --
 * return: 返回y。
 */
double FittingData::get_y() const{
	return(_y);
}