#include"stdafx.h"
#include"MtLayout.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutStretchItem.h"
#include"MtLayoutLayoutItem.h"
#include"MtLayoutWindowItem.h"
#include"MtLayoutRect.h"
#include"MtLayoutSize.h"

/**
 * name: MtLayout
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtLayout::MtLayout(void)
	:_items()
	,_margin(new UintRect)
	,_rect(new IntRect){
}

/**
 * name: ~MtLayout
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtLayout::~MtLayout(void){
	delete _margin;
	delete _rect;
}

/**
 * name: resize
 * brief: 重新调整当前布局尺寸。
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 当前布局新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::resize(HDWP &hdwp,const IntRect &rect){
	//1.如果当前参数不合法则直接返回错误。
	if(0==hdwp){
		return(-1);
	}
	if(!rect.is_valid()){
		return(-2);
	}
	//2.记录当前布局新尺寸。
	*_rect=rect;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: resize
 * brief: 重置当前布局尺寸。
 * param: width - 宽度。
 *        height - 高度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::resize(const unsigned int width,const unsigned int height){
	_rect->set_rect(0,0,static_cast<int>(width),static_cast<int>(height));
	return(0);
}

/**
 * name: add_stretch
 * brief: 向当前布局中追加一个拉伸项。
 * param: stretch_factor - 拉伸系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::add_stretch(const unsigned int stretch_factor){
	//1.创建一个拉伸项。
	PtrToItem item(new MtLayoutStretchItem(stretch_factor));
	//2.如果创建失败，返回错误编码。
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.如果拉伸项无效，则返回错误编码。
	if(!item->is_valid()){
		return(-2);
	}
	//4.将当前拉伸向加入存储向量中。
	_items.push_back(item);
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: add_layout
 * brief: 向当前布局中追加一个布局。
 * param: layout - 指向布局。
 *        stretch_factor - 拉伸系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::add_layout(MtLayout *layout,const unsigned int stretch_factor){
	//1.创建一个布局项。
	PtrToItem item(new MtLayoutLayoutItem(layout,stretch_factor));
	//2.如果创建失败，返回错误编码。
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.如果布局项无效，则返回错误编码。
	if(!item->is_valid()){
		return(-2);
	}
	//4.将当前布局向加入存储向量中。
	_items.push_back(item);
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: add_layout
 * brief: 向当前布局中追加一个窗口。
 * param: window - 指向窗口。
 *        stretch_factor - 拉伸系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::add_window(CWnd *window,const unsigned int stretch_factor){
	//1.创建一个窗口项。
	PtrToItem item(new MtLayoutWindowItem(window,stretch_factor));
	//2.如果创建失败，返回错误编码。
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.如果窗口项无效，则返回错误编码。
	if(!item->is_valid()){
		return(-2);
	}
	//4.将当前窗口向加入存储向量中。
	_items.push_back(item);
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_margin
 * brief: 设置布局留白。
 * param: margin - 留白尺寸。
 * return: --
 */
void MtLayout::set_margin(const UintRect &margin){
	(*_margin)=margin;
}

/**
 * name: set_margin
 * brief: 设置布局留白。
 * param: left_margin - 左侧留白。
 *        top_margin - 顶部留白。
 *        right_margin - 右侧留白。
 *        bottom_margin - 底部留白。
 * return: --
 */
void MtLayout::set_margin(const unsigned int left_margin,
  const unsigned int top_margin,const unsigned int right_margin,
  const unsigned int bottom_margin){
	_margin->set_rect(left_margin,top_margin,right_margin,bottom_margin);
}

/**
 * name: get_margin
 * brief: 获取布局留白。
 * param: --
 * return: 返回布局留白。
 */
const MtLayout::UintRect &MtLayout::get_margin() const{
	return(*_margin);
}

/**
 * name: get_window_amount
 * brief: 获取窗口数量。
 * param: --
 * return: 返回窗口数量。
 */
unsigned int MtLayout::get_window_amount() const{
	//1.声明当前操作所需变量。
	unsigned int window_amount=0;
	//2.统计布局子项中窗口个数。
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		if(!static_cast<bool>(*iterator)){
			continue;
		}else{
			window_amount+=(*iterator)->get_window_amount();
		}
	}
	//3.返回当前布局子项中窗口个数。
	return(window_amount);
}

/**
 * name: get_rect
 * brief: 获取当前布局尺寸。
 * param: --
 * return: 返回当前布局尺寸。
 */
const MtLayout::IntRect &MtLayout::get_rect() const{
	return(*_rect);
} 

/**
 * name: get_item_size
 * brief: 获取布局中指定子项的尺寸。
 * param: index - 子项索引。
 *        size - 返回的尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::get_item_size(const unsigned int index,IntSize &size) const{
	//1.如果当前索引编号超出范围，则直接返回错误。
	if(index>=_items.size()){
		return(-1);
	}
	//2.如果当前子项为空，则直接返回错误。
	if(!static_cast<bool>(_items[index])){
		return(-2);
	}
	//3.计算当前子项尺寸。
	size.set_size(_items[index]->get_width(),_items[index]->get_height());
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_item_rect
 * brief: 获取布局中指定子项的矩形尺寸。
 * param: index - 子项索引。
 *        rect - 返回的矩形尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::get_item_rect(const unsigned int index,IntRect &rect) const{
	//1.如果当前索引编号超出范围，则直接返回错误。
	if(index>=_items.size()){
		return(-1);
	}
	//2.如果当前子项为空，则直接返回错误。
	if(!static_cast<bool>(_items[index])){
		return(-2);
	}
	//3.计算当前子项尺寸。
	rect=_items[index]->get_rect();
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_item_window
 * brief: 设置指定布局项窗口。
 * param: index - 指定布局项索引。
 *        window - 指向指定窗口。
 *        stretch_factor - 拉伸系数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLayout::set_item_window(const unsigned int index,CWnd *window,const unsigned int stretch_factor){
	//1.如果当前索引编号超出范围，则直接返回错误。
	if(index>=_items.size()){
		return(-1);
	}
	//2.创建一个窗口项。
	PtrToItem item(new MtLayoutWindowItem(_items[index]->get_rect(),window,stretch_factor));
	//3.如果创建失败，返回错误编码。
	if(!static_cast<bool>(item)){
		return(-2);
	}
	//4.如果窗口项无效，则返回错误编码。
	if(!item->is_valid()){
		return(-3);
	}
	//5.设置当前子布局项窗口。
	_items[index]=item;
	//6.程序运行到此，成功返回。
	return(0);
}