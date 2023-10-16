#include"stdafx.h"
#include"MtLayoutStretchItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutStretchItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutStretchItem::MtLayoutStretchItem(void)
	:MtLayoutItem()
	,_stretch_factor(0){
}

/**
 * name: MtLayoutStretchItem
 * brief: 构造函数。
 * param: stretch_factor - 拉伸系数。
 * return: --
 */
MtLayoutStretchItem::MtLayoutStretchItem(const unsigned int stretch_factor)
	:MtLayoutItem()
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutStretchItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutStretchItem::~MtLayoutStretchItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前类实例对象是否有效。
 * param: --
 * return: 如果当前实例对象有效返回值大于等于零，否则返回值小于零。
 */
BOOL MtLayoutStretchItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(_stretch_factor>0));
}

/**
 * name: get_window_amount
 * brief: 获取当前间隔项中包含的窗口数量。
 * param: --
 * return: 返回当前间隔项中包含的窗口数量。
 */
unsigned int MtLayoutStretchItem::get_window_amount() const{
	return(0);
}

/**
 * name: get_stretch_factor
 * brief: 获取拉伸系数。
 * param: --
 * return: 返回拉伸系数。
 */
unsigned int MtLayoutStretchItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: 获取当前布局拉伸项的固定尺寸。
 * param: --
 * return: 返回当前布局拉伸项的固定尺寸。
 */
unsigned int MtLayoutStretchItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: 重新调整布局项尺寸。
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 布局项新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayoutStretchItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项非法，则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.调用基类相应函数，用来记录当前布局项的新尺寸。
	if(MtLayoutItem::resize(hdwp,rect)<0){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_stretch_factor
 * brief: 设置拉伸系数。
 * param: stretch_factor - 拉伸系数。
 * return: --
 */
void MtLayoutStretchItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}