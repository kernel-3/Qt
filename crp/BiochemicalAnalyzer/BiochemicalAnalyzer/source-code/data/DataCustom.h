#pragma once

#include<cmath>

/**
 * name: ZERO_THRESHOLD_VALUE
 * brief: ���ô˷�ֵ�ж�һ���������Ƿ�Ϊ�㡣
 * author: yameng_he
 * date: 2015-06-19
 */
#define ZERO_THRESHOLD_VALUE 1.0E-20

/**
 * name: is_zero
 * brief: �ж�һ���������Ƿ�Ϊ�㡣
 * param: value - ָ���ĸ�����ֵ��
 * return: ���ָ���ĸ�����Ϊ���򷵻�TRUE�����򷵻�FALSE��
 */
inline BOOL is_zero(const double value){
	return(fabs(value)<ZERO_THRESHOLD_VALUE);
}

/**
 * name: is_zero
 * brief: �ж�һ���������Ƿ�Ϊ�㡣
 * param: value - ָ���ĸ�����ֵ��
 * return: ���ָ���ĸ�����Ϊ���򷵻�TRUE�����򷵻�FALSE��
 */
inline BOOL is_zero(const float value){
	return(fabs(value)<ZERO_THRESHOLD_VALUE);
}