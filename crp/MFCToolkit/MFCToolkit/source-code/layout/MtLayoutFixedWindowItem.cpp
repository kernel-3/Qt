#include"stdafx.h"
#include"MtLayoutFixedWindowItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutFixedWindowItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(void)
	:MtLayoutItem()
	,_window(0)
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutFixedWindowItem
 * brief: 构造函数。
 * param: window - 指向一个窗口。
 *        orientation - 当前布局项方向。
 *        fixed_size - 当前布局项固定尺寸。
 * return:
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(CWnd *window,
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem()
	,_window(window)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: MtLayoutFixedWindowItem
 * brief: 构造函数。
 * param: rect - 布局项尺寸。
 *        window - 指向一个窗口。
 *        orientation - 当前布局项方向。
 *        fixed_size - 当前布局项固定尺寸。
 * return:
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(const IntRect &rect,CWnd *window,
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem(rect)
	,_window(window)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: ~MtLayoutFixedWindowItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutFixedWindowItem::~MtLayoutFixedWindowItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前固定窗口布局项是否有效。
 * param: --
 * return: 如果当前窗口布局项有效返回TRUE，否则返回FALSE。
 */
BOOL MtLayoutFixedWindowItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(0!=_window)&&
		(0!=_window->GetSafeHwnd())&&
		(INVALID_HANDLE_VALUE!=_window->GetSafeHwnd())&&
		(IsWindow(_window->GetSafeHwnd()))&&
		(ORIENTATION_UNKNOWN!=_orientation)&&(_fixed_size!=0));
}

/**
 * name: get_window_amount
 * brief: 获取当前固定窗口布局项中窗口数量。
 * param: --
 * return: 返回当前固定窗口布局项中窗口数量。
 */
unsigned int MtLayoutFixedWindowItem::get_window_amount() const{
	if(is_valid()){
		return(1);
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: 获取当前固定窗口布局项的拉伸系数。
 * param: --
 * return: 返回当前固定窗口布局项的拉伸系数。
 */
unsigned int MtLayoutFixedWindowItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: 获取当前窗口布局项的固定尺寸。
 * param: --
 * return: 返回当前窗口布局项的固定尺寸。
 */
unsigned int MtLayoutFixedWindowItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: 重新调整固定窗口布局项的尺寸。
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 布局项新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则小于零。
 */
int MtLayoutFixedWindowItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项为非法，则直接返回。
	if(!is_valid()){
		return(-1);
	}
	//2.根据当前固定窗口布局项的方向，重新调整固定窗口布局项的尺寸。
	//2-1.声明当前操作所需变量。
	IntRect rect_t(rect);
	//2-2.重新调整当前固定窗口布局项的尺寸。
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(_fixed_size));
	}else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(_fixed_size));
	}else{
		return(-2);
	}
	//2-3.如果当前计算的尺寸不合法，则直接返回错误。
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.计算当前布局项窗口调整标记。
	unsigned int flag=SWP_NOZORDER|SWP_NOACTIVATE|
		SWP_NOOWNERZORDER;
	if((_rect->get_left()==rect_t.get_left())&&
		(_rect->get_top()==rect_t.get_top())){
		flag|=SWP_NOMOVE;
	}
	if((_rect->get_width()==rect_t.get_width())&&
		(_rect->get_height()==rect_t.get_height())){
		flag|=SWP_NOSIZE;
	}else{
		flag|=SWP_NOCOPYBITS;
	}
	//4.调用基类相应函数，保存当前布局项的新尺寸，并且判断保存是否成功。
	const int result=MtLayoutItem::resize(hdwp,rect_t);
	if(result<0){
		return(-4);
	}
	//5.调用API函数，调整当前布局项中窗口尺寸。
	hdwp=DeferWindowPos(hdwp,_window->GetSafeHwnd(),0,_rect->get_left(),
		_rect->get_top(),_rect->get_width(),_rect->get_height(),flag);
	if(0==hdwp){
		return(-5);
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_window
 * brief: 设置窗口。
 * param: window - 指向窗口。
 * return: --
 */
void MtLayoutFixedWindowItem::set_window(CWnd *window){
	_window=window;
}

/**
 * name: get_window
 * brief: 获取窗口。
 * param: --
 * return: 返回窗口。
 */
CWnd *MtLayoutFixedWindowItem::get_window(){
	return(_window);
}

/**
 * name: get_window
 * brief: 获取窗口。
 * param: --
 * return: 返回窗口。
 */
const CWnd *MtLayoutFixedWindowItem::get_window() const{
	return(const_cast<MtLayoutFixedWindowItem*>(this)->get_window());
}

/**
 * name: set_orientation
 * brief: 设置固定窗口布局方向。
 * param: orientation - 设置固定窗口布局方向。
 * return: --
 */
void MtLayoutFixedWindowItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: 获取固定窗口布局方向。
 * param: --
 * return: 返回固定窗口布局方向。
 */
MtLayoutFixedWindowItem::Orientation MtLayoutFixedWindowItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: 设置固定窗口布局的固定尺寸（单位：像素）。
 * param: fixed_size - 固定窗口布局的固定尺寸（单位：像素）。
 * return: --
 */
void MtLayoutFixedWindowItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}