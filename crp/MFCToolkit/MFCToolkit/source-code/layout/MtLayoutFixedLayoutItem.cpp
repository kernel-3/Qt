#include"stdafx.h"
#include"MtLayoutFixedLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutFixedLayoutItem
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayoutFixedLayoutItem::MtLayoutFixedLayoutItem(void)
	:MtLayoutItem()
	,_layout(0)
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutFixedLayoutItem
 * brief: 构造函数。
 * param: layout - 布局指针。
 *        orientation - 固定布局的布局项方向。
 *        fixed_size - 固定布局的布局项固定尺寸。
 * return: --
 */
MtLayoutFixedLayoutItem::MtLayoutFixedLayoutItem(MtLayout *layout,
	const Orientation orientation,const unsigned int fixed_size)
	:_layout(layout)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: MtLayoutFixedLayoutItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayoutFixedLayoutItem::~MtLayoutFixedLayoutItem(void){
}

/**
 * name: is_valid
 * brief: 判断当前固定布局的布局项是否有效。
 * param: --
 * return: 如果当前固定布局的布局项有效则返回TRUE、否则返回FALSE。
 */
BOOL MtLayoutFixedLayoutItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(ORIENTATION_UNKNOWN!=_orientation)&&
		(0!=_fixed_size)&&(0!=_layout));
}

/**
 * name: get_window_amount
 * brief: 获取当前固定布局的布局项中包含窗口的数量。
 * param: --
 * return: 返回当前固定布局的布局项中包含窗口的数量。
 */
unsigned int MtLayoutFixedLayoutItem::get_window_amount() const{
	if(is_valid()){
		return(_layout->get_window_amount());
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: 获取当前固定布局的布局项的拉伸系数。
 * param: --
 * return: 返回当前固定布局的布局项的拉伸系数。
 */
unsigned int MtLayoutFixedLayoutItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: 获取当前固定布局的布局项的固定尺寸。
 * param: --
 * return: 返回当前固定布局的布局项的固定尺寸。
 */
unsigned int MtLayoutFixedLayoutItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: 重新调整当前固定布局的布局项的固定尺寸。
 * param: hdwp - 调整多窗口尺寸时内存句柄。
 *        rect - 窗口新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayoutFixedLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前布局项不合法则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//2.根据当前固定布局的布局项方向，计算布局调整后的实际尺寸。
	//2-1.声明当前操作所需变量。
	IntRect rect_t(rect);
	//2-2.根据当前固定布局的布局项的方向，计算实际的布局项尺寸。
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(_fixed_size));
	}else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(_fixed_size));
	}else{
		return(-2);
	}
	//2-3.如果计算的布局尺寸不合法，则直接返回错误。
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.设置记录当前新尺寸，并且判断是否成功。
	if(MtLayoutItem::resize(hdwp,rect_t)<0){
		return(-4);
	}
	//4.调整当前布局尺寸，并且判断是否成功。
	if(_layout->resize(hdwp,rect_t)<0){
		return(-5);
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_layout
 * brief: 设置布局。
 * param: layout - 指向布局。
 * return: --
 */
void MtLayoutFixedLayoutItem::set_layout(MtLayout *layout){
	_layout=layout;
}

/**
 * name: get_layout
 * brief: 获取布局。
 * param: --
 * return: 返回布局。
 */
MtLayout *MtLayoutFixedLayoutItem::get_layout(){
	return(_layout);
}

/**
 * name: get_layout
 * brief: 获取布局。
 * param: --
 * return: 返回布局。
 */
const MtLayout *MtLayoutFixedLayoutItem::get_layout() const{
	return(const_cast<MtLayoutFixedLayoutItem*>(this)->get_layout());
}

/**
 * name: set_orientation
 * brief: 设置固定窗口布局方向。
 * param: orientation - 设置固定窗口布局方向。
 * return: --
 */
void MtLayoutFixedLayoutItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: 获取固定窗口布局方向。
 * param: --
 * return: 返回固定窗口布局方向。
 */
MtLayoutFixedLayoutItem::Orientation MtLayoutFixedLayoutItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: 设置固定窗口布局的固定尺寸（单位：像素）。
 * param: fixed_size - 固定窗口布局的固定尺寸（单位：像素）。
 * return: --
 */
void MtLayoutFixedLayoutItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}