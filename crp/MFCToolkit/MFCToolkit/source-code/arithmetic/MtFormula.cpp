#include"stdafx.h"
#include"MtFormula.h"
#include<assert.h>

/**
 * name: MtFormula
 * breif: 构造函数。
 * param: x - 指向待拟合的x数组。
 *        y - 指向待拟合的y数组。
 *        size - 待拟合x、y数组尺寸。
 *        min_size - 待拟合x、y数组最小尺寸。
 * return: --
 */
MtFormula::MtFormula(const double *x,const double *y,
	const unsigned int size,const unsigned int minimum_size)
	:_x(x)
	,_y(y)
	,_size(size)
	,_minimum_size(minimum_size){
}

/**
 * name: ~MtFormula
 * brief: 析构函数，负责类中数据释放。
 * param: --
 * return: --
 */
MtFormula::~MtFormula(void){
}

/**
 * name: get_x
 * brief: 获取公式中指定下标的x值。
 * param: index - 下标值。
 * return: 返回指定下标的x值。
 */
double MtFormula::get_x(const unsigned int index) const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.此处断言参数传递的索引合法。
	assert(index<_size);
	//3.返回当前指定下标的浓度值。
	return(_x[index]);
}

/**
 * name: get_y
 * brief: 获取公式中指定下标的y值。。
 * param: index - 下标值。
 * return: 返回指定下标的y值。
 */
double MtFormula::get_y(const unsigned int index) const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.此处断言参数传递的索引合法。
	assert(index<_size);
	//3.返回当前指定下标的吸光度值。
	return(_y[index]);
}

/**
 * name: get_average_x
 * brief: 获取x的平均值。
 * param: --
 * return: 返回x的平均值。
 */
double MtFormula::get_average_x() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中x的平均值。
	//2-1.声明当前操作所需变量。
	double average_x=0.0;
	//2-2.遍历公式中x数组，累计x的和。
	for(unsigned int index=0;index!=_size;++index){
		average_x+=_x[index];
	}
	//2-3.计算x的平均值。
	average_x=average_x/static_cast<double>(_size);
	//3.程序运行到此，直接返回x的平均值。
	return(average_x);
}

/**
 * name: get_average_y
 * brief: 获取y的平均值。
 * param: --
 * return: 返回y的平均值。
 */
double MtFormula::get_average_y() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中y的平均值。
	//2-1.声明当前操作所需变量。
	double average_y=0.0;
	//2-2.遍历公式中y数组，累计y的和。
	for(unsigned int index=0;index!=_size;++index){
		average_y+=_y[index];
	}
	//2-3.计算y的平均值。
	average_y=average_y/static_cast<double>(_size);
	//3.程序运行到此，直接返回平均吸光度。
	return(average_y);
}

/**
 * name: get_size
 * brief: 获取当前公式中未知数数组的个数。
 * param: --
 * return: 返回当前公式中未知数数组的个数。
 */
unsigned int MtFormula::get_size() const{
	//1.如果当前公式尚未满足拟合条件，则直接返回零。
	if(!MtFormula::is_can_fitted()){
		return(0);
	}
	//2.返回当前前公式中未知数数组的个数。
	else{
		return(_size);
	}
}

/**
 * name: get_maximum_x_index
 * brief: 获取当前公式中，最大x的下标值。
 * param: --
 * return: 返回当前公式中最大x的下标值。
 */
unsigned int MtFormula::get_maximum_x_index() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中最大x的下标值。
	//2-1.声明当前操作所需变量。
	double max_x=0.0;
	unsigned int index=0;
	//2-2.遍历x存储数组，计算最大x的下标值。
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			max_x=_x[i];
			index=i;
		}else if(_x[i]>max_x){
			max_x=_x[i];
			index=i;
		}
	}
	//3.返回计算的下标值。
	return(index);
}

/**
 * name: get_minimum_x_index
 * brief: 获取当前公式中最小x的下标值。
 * param: --
 * return: 返回当前公式中最小x的下标值。
 */
unsigned int MtFormula::get_minimum_x_index() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中最小x的下标值。
	//2-1.声明当前操作所需变量。
	double min_x=0.0;
	unsigned int index=0;
	//2-2.遍历x存储数组，计算最x的下标值。
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			min_x=_x[i];
			index=i;
		}else if(_x[i]<min_x){
			min_x=_x[i];
			index=i;
		}
	}
	//3.返回计算的下标值。
	return(index);
}

/**
 * name: get_maximum_y_index
 * brief: 获取当前公式中最大y的下标。
 * param: --
 * return: 返回当前公式中最大y的下标值。
 */
unsigned int MtFormula::get_maximum_y_index() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中最大y的下标。
	//2-1.声明当前操作所需变量。
	double max_y=0.0;
	unsigned int index=0;
	//2-2.遍历y的存储数组，计算最大y的下标值。
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			max_y=_y[i];
			index=i;
		}else if(_y[i]>max_y){
			max_y=_y[i];
			index=i;
		}
	}
	//3.返回计算的下标值。
	return(index);
}

/**
 * name: get_minimum_y_index
 * brief: 获取当前公式中最小y的下标值。
 * param: --
 * return: 返回当前公式中最小y的下标值。
 */
unsigned int MtFormula::get_minimum_y_index() const{
	//1.此处断言当前公式处于允许被拟合状态。
	assert(MtFormula::is_can_fitted());
	//2.计算当前公式中最小y的下标。
	//2-1.声明当前操作所需变量。
	double min_y=0.0;
	unsigned int index=0;
	//2-2.遍历y的存储数组，计算最小y的下标值。
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			min_y=_y[i];
			index=i;
		}else if(_y[i]<min_y){
			min_y=_y[i];
			index=i;
		}
	}
	//3.返回计算的下标值。
	return(index);
}

/**
 * name: get_maximum_x
 * brief: 获取当前公式中最大的x值。
 * param: --
 * return: 返回公式中最大的x值。
 */
double MtFormula::get_maximum_x() const{
	return(get_x(get_maximum_x_index()));
}

/**
 * name: get_minimum_x
 * brief: 获取当前公式中最小的x值。
 * param: --
 * return: 返回当前公式中最小的x值。
 */
double MtFormula::get_minimum_x() const{
	return(get_x(get_minimum_x_index()));
}

/**
 * name: get_maximum_y
 * brief: 获取当前公式中最大的y值。
 * param: --
 * return: 返回当前公式中最大的y值。
 */
double MtFormula::get_maximum_y() const{
	return(get_y(get_maximum_y_index()));
}

/**
 * name: get_minimum_y
 * brief: 获取当前公式中最小的y值。
 * param: --
 * return: 返回当前公式中最小的y值。
 */
double MtFormula::get_minimum_y() const{
	return(get_y(get_minimum_y_index()));
}

/**
 * name: is_can_fitted
 * breif: 判断当前公式是否可以被拟合。
 * param: --
 * return: 如果当前公式可被拟合返回TRUE，否则返回FALSE。
 */
BOOL MtFormula::is_can_fitted() const{
	return (_size>=_minimum_size
		)&&(_minimum_size>0);
}