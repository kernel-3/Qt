#include"stdafx.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutSpacingItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutSpacingItem::MtLayoutSpacingItem(void)
	:MtLayoutItem()
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutSpacingItem
 * brief: 构造函数。
 * param: orientation - 方向。
 *        fixed_size - 固定尺寸。
 * return: --
 */
MtLayoutSpacingItem::MtLayoutSpacingItem(
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem()
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: ~MtLayoutSpacingItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutSpacingItem::~MtLayoutSpacingItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前类实例对象是否有效。
 * param: --
 * return: 如果当前实例对象有效返回值大于等于零，否则返回值小于零。
 */
BOOL MtLayoutSpacingItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(ORIENTATION_UNKNOWN!=_orientation)&&(0!=_fixed_size));
}

/**
 * name: get_window_amount
 * brief: 获取当前间隔项中包含的窗口数量。
 * param: --
 * return: 返回当前间隔项中包含的窗口数量。
 */
unsigned int MtLayoutSpacingItem::get_window_amount() const{
	return(0);
}

/**
 * name: get_stretch_factor
 * brief: 获取拉伸系数。
 * param: --
 * return: 返回拉伸系数。
 */
unsigned int MtLayoutSpacingItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: 获取间隔项的固定尺寸。
 * param: --
 * return: 返回间隔项的固定尺寸。
 */
unsigned int MtLayoutSpacingItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: 重新调整布局项的尺寸。
 * param: hdwp - 多窗口调整尺寸内存句柄。
 *        rect - 布局项新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayoutSpacingItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项不合法则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.计算当前布局项新尺寸。
	//2-1.声明当前操作所需变量。
	IntRect rect_t(rect);
	//2-2.如果当前间隔项方向为水平方向。
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(
			get_fixed_size()));
	}
	//2-3.如果当前间隔项方向为垂直方向。
	else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(
			get_fixed_size()));
	}
	//2-4.如果当前间隔项方向未知。
	else{
		return(-2);
	}
	//2-5.如果当前计算的新尺寸不合法，则直接返回错误。
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.调用基类相应函数，并且判断调用是否成功（这里基类函数只用于检验参数是否合法）。
	const int result=MtLayoutItem::resize(hdwp,rect_t);
	if(result<0){
		return(-4);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_orientation
 * brief: 设置间隔方向。
 * param: orientation - 设置间隔方向。
 * return: --
 */
void MtLayoutSpacingItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: 获取间隔方向。
 * param: --
 * return: 返回间隔方向。
 */
MtLayoutSpacingItem::Orientation MtLayoutSpacingItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: 设置固定尺寸（单位：像素）。
 * param: fixed_size - 间隔的固定尺寸（单位：像素）。
 * return: --
 */
void MtLayoutSpacingItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}