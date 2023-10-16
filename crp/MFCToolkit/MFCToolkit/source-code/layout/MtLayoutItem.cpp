#include"stdafx.h"
#include"MtLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutItem::MtLayoutItem(void)
	:_rect(new IntRect(-1,-1,-1,-1)){
}

/**
 * name: MtLayoutItem
 * brief: 构造函数。
 * param: rect - 布局项尺寸。
 * return: --
 */
MtLayoutItem::MtLayoutItem(const IntRect &rect)
	:_rect(new IntRect(rect)){
}

/**
 * name: ~MtLayoutItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutItem::~MtLayoutItem(void){
	delete _rect;
}

/**
 * name: is_valid
 * brief: 是否为有效的布局项。
 * param: --
 * return: 如果函数执行成功返回值为TRUE，否则返回值为FALSE。
 */
BOOL MtLayoutItem::is_valid() const{
	return(_rect->is_valid());
}

/**
 * name: resize
 * brief: 重新调整布局项尺寸。
 * param: hdwp - 窗口尺寸调整内存句柄。
 *        rect - 新布局尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.判断当前传递参数是否合法。
	if(0==hdwp){
		return(-1);
	}
	if(!rect.is_valid()){
		return(-2);
	}
	//2.记录当前布局项的尺寸。
	*_rect=rect;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_width
 * brief: 获取当前布局项宽度。
 * param: --
 * return: 返回当前布局项宽度。
 */
int MtLayoutItem::get_width() const{
	return(_rect->get_width());
}

/**
 * name: get_height
 * brief: 获取当前布局项高度。
 * param: --
 * return: 返回当前布局项高度。
 */
int MtLayoutItem::get_height() const{
	return(_rect->get_height());
}

/**
 * name: get_rect
 * brief: 获取当前布局项的尺寸。
 * param: --
 * return: 返回当前布局项的尺寸。
 */
const MtLayoutItem::IntRect &MtLayoutItem::get_rect() const{
	return(*_rect);
}