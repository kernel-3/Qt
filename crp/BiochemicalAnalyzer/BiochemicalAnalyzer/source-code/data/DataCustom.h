#pragma once

#include<cmath>

/**
 * name: ZERO_THRESHOLD_VALUE
 * brief: 利用此阀值判断一个浮点数是否为零。
 * author: yameng_he
 * date: 2015-06-19
 */
#define ZERO_THRESHOLD_VALUE 1.0E-20

/**
 * name: is_zero
 * brief: 判断一个浮点数是否为零。
 * param: value - 指定的浮点数值。
 * return: 如果指定的浮点数为零则返回TRUE，否则返回FALSE。
 */
inline BOOL is_zero(const double value){
	return(fabs(value)<ZERO_THRESHOLD_VALUE);
}

/**
 * name: is_zero
 * brief: 判断一个浮点数是否为零。
 * param: value - 指定的浮点数值。
 * return: 如果指定的浮点数为零则返回TRUE，否则返回FALSE。
 */
inline BOOL is_zero(const float value){
	return(fabs(value)<ZERO_THRESHOLD_VALUE);
}