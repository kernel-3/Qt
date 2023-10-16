#include"stdafx.h"
#include"MtLayoutWindowItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutWindowItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(void)
	:MtLayoutItem()
	,_window(0)
	,_stretch_factor(0){
}

/**
 * name: MtLayoutWindowItem
 * brief: 构造函数。
 * param: window - 指向窗口。
 *        stretch_factor - 拉伸系数。
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(CWnd *window,const unsigned int stretch_factor)
	:MtLayoutItem()
	,_window(window)
	,_stretch_factor(stretch_factor){
}

/**
 * name: MtLayoutWindowItem
 * brief: 构造函数。
 * param: rect - 布局项尺寸。
 *        window - 指向窗口。
 *        stretch_factor - 拉伸系数。
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(const IntRect &rect,CWnd *window,const unsigned int stretch_factor)
	:MtLayoutItem(rect)
	,_window(window)
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutWindowItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutWindowItem::~MtLayoutWindowItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前类实例对象是否有效。
 * param: --
 * return: 如果当前实例对象有效返回值大于等于零，否则返回值小于零。
 */
BOOL MtLayoutWindowItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(_stretch_factor>0)&&
		(0!=_window)&&(0!=_window->GetSafeHwnd())&&
		(INVALID_HANDLE_VALUE!=_window->GetSafeHwnd())&&
		(IsWindow(_window->GetSafeHwnd())));
}

/**
 * name: get_window_amount
 * brief: 获取当前间隔项中包含的窗口数量。
 * param: --
 * return: 返回当前间隔项中包含的窗口数量。
 */
unsigned int MtLayoutWindowItem::get_window_amount() const{
	if(is_valid()){
		return(1);
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: 获取拉伸系数。
 * param: --
 * return: 返回拉伸系数。
 */
unsigned int MtLayoutWindowItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: 获取当前窗口布局项的固定尺寸。
 * param: --
 * return: 返回当前窗口布局项的固定尺寸。
 */
unsigned int MtLayoutWindowItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: 重新调整布局项尺寸。
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 布局项新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayoutWindowItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项为非法，则直接返回。
	if(!is_valid()){
		return(-1);
	}
	//2.计算当前布局项窗口调整标记。
	unsigned int flag=SWP_NOZORDER|SWP_NOACTIVATE|
		SWP_NOOWNERZORDER;
	if((_rect->get_left()==rect.get_left())&&
		(_rect->get_top()==rect.get_top())){
		flag|=SWP_NOMOVE;
	}
	if((_rect->get_width()==rect.get_width())&&
		(_rect->get_height()==rect.get_height())){
		flag|=SWP_NOSIZE;
	}else{
		flag|=SWP_NOCOPYBITS;
	}
	//3.调用基类相应函数，保存当前布局项的新尺寸，并且判断保存是否成功。
	const int result=MtLayoutItem::resize(hdwp,rect);
	if(result<0){
		return(-2);
	}
	//4.调用API函数，调整当前布局项中窗口尺寸。
	hdwp=DeferWindowPos(hdwp,_window->GetSafeHwnd(),0,_rect->get_left(),
		_rect->get_top(),_rect->get_width(),_rect->get_height(),flag);
	if(0==hdwp){
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_window
 * brief: 设置窗口。
 * param: window - 指向窗口。
 * return: --
 */
void MtLayoutWindowItem::set_window(CWnd *window){
	_window=window;
}

/**
 * name: get_window
 * brief: 获取窗口。
 * param: --
 * return: 返回窗口。
 */
CWnd *MtLayoutWindowItem::get_window(){
	return(_window);
}

/**
 * name: get_window
 * brief: 获取窗口。
 * param: --
 * return: 返回窗口。
 */
const CWnd *MtLayoutWindowItem::get_window() const{
	return(const_cast<MtLayoutWindowItem*>(this)->get_window());
}

/**
 * name: set_stretch_factor
 * brief: 设置拉伸系数。
 * param: stretch_factor - 拉伸系数。
 * return: --
 */
void MtLayoutWindowItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}