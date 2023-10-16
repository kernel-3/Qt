#include"stdafx.h"
#include"MtLayoutLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutLayoutItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutLayoutItem::MtLayoutLayoutItem(void)
	:MtLayoutItem()
	,_layout(0)
	,_stretch_factor(0){
}

/**
 * name: MtLayoutLayoutItem
 * brief: 构造函数。
 * param: layout - 指向布局。
 *        stretch_factor - 拉伸系数。
 * return: --
 */
MtLayoutLayoutItem::MtLayoutLayoutItem(MtLayout *layout,const unsigned int stretch_factor)
	:MtLayoutItem()
	,_layout(layout)
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutLayoutItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutLayoutItem::~MtLayoutLayoutItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前类实例对象是否有效。
 * param: --
 * return: 如果当前实例对象有效返回值大于等于零，否则返回值小于零。
 */
BOOL MtLayoutLayoutItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(_stretch_factor>0)&&(0!=_layout));
}

/**
 * name: get_window_amount
 * brief: 获取当前间隔项中包含的窗口数量。
 * param: --
 * return: 返回当前间隔项中包含的窗口数量。
 */
unsigned int MtLayoutLayoutItem::get_window_amount() const{
	if(is_valid()){
		return(_layout->get_window_amount());
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
unsigned int MtLayoutLayoutItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: 获取布局项固定尺寸。
 * param: --
 * return: 返回布局项固定尺寸。
 */
unsigned int MtLayoutLayoutItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: 重新调整布局项尺寸。 
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 布局项新尺寸。
 * return: 如果函数执行成功返回值大于零，否则返回值小于零。
 */
int MtLayoutLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项不合法则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.设置记录当前新尺寸，并且判断是否成功。
	if(MtLayoutItem::resize(hdwp,rect)<0){
		return(-2);
	}
	//3.调整当前布局尺寸，并且判断是否成功。
	if(_layout->resize(hdwp,rect)<0){
		return(-3);
	}
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_layout
 * brief: 设置布局。
 * param: layout - 指向布局。
 * return: --
 */
void MtLayoutLayoutItem::set_layout(MtLayout *layout){
	_layout=layout;
}

/**
 * name: get_layout
 * brief: 获取布局。
 * param: --
 * return: 返回布局。
 */
MtLayout *MtLayoutLayoutItem::get_layout(){
	return(_layout);
}

/**
 * name: get_layout
 * brief: 获取布局。
 * param: --
 * return: 返回布局。
 */
const MtLayout *MtLayoutLayoutItem::get_layout() const{
	return(const_cast<MtLayoutLayoutItem*>(this)->get_layout());
}

/**
 * name: set_stretch_factor
 * brief: 设置拉伸系数。
 * param: stretch_factor - 拉伸系数。
 * return: --
 */
void MtLayoutLayoutItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}