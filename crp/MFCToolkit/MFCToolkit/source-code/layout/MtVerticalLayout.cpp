#include"stdafx.h"
#include"MtVerticalLayout.h"
#include"MtLayoutItem.h"
#include"MtLayoutRect.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutFixedLayoutItem.h"
#include"MtLayoutFixedWindowItem.h"

/**
 * name: MtVerticalLayout
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtVerticalLayout::MtVerticalLayout(void)
	:MtLayout(){
}

/**
 * name: ~MtVerticalLayout
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtVerticalLayout::~MtVerticalLayout(void){
}

/**
 * name: resize
 * brief: 重新调整当前布局尺寸。
 * param: hdwp - 多窗口尺寸调整内存句柄。
 *        rect - 当前布局新尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::resize(HDWP &hdwp,const IntRect &rect){
	//1.调用基类相应虚函数，调整当前布局尺寸，并且判断操作是否成功。
	if(MtLayout::resize(hdwp,rect)<0){
		return(-1);
	}
	//2.累计当前布局中，存储窗口数量、拉伸系数以及固定尺寸。
	//2-1.声明当前操作所需变量。
	unsigned int window_amount=0;
	unsigned int stretch_factor=0;
	unsigned int fixed_size=0;
	//2-2.遍历当前布局中窗口，统计窗口数量、拉伸系数以及固定尺寸。
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		window_amount+=(*iterator)->get_window_amount();
		stretch_factor+=(*iterator)->get_stretch_factor();
		fixed_size+=(*iterator)->get_fixed_size();
	}
	//2-3.如果当前布局中窗口数量为零，则直接成功返回。
	/*
	if(0==window_amount){
		return(0);
	}
	*/
	//3.申请多窗口尺寸调整内存句柄，并且判断申请是否成功。
	/*
	HDWP hdwp=::BeginDeferWindowPos(window_amount);
	if(0==hdwp){
		return(-1);
	}
	*/
	//4.根据当前布局留白尺寸，计算当前布局的有效尺寸，并且判断计算是否成功。
	const IntRect valid_rect(_rect->get_left()+static_cast<int>(_margin->get_left()),
		_rect->get_top()+static_cast<int>(_margin->get_top()),
		_rect->get_right()-static_cast<int>(_margin->get_right()),
		_rect->get_bottom()-static_cast<int>(_margin->get_bottom()));
	if(!valid_rect.is_valid()){
		return(-2);
	}
	//5.遍历当前布局中的布局项，调整每一项尺寸。
	//5-1.声明当前操作所需变量。
	int height=0;
	IntRect rect_t(valid_rect);
	//5-2.遍历当前布局项，调整每一个布局项的尺寸。
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		//5-2-1.根据当前布局项拉伸系数，计算当前布局项的新尺寸。
		if(0==stretch_factor){
			height=0;
		}else{
			height=static_cast<int>(static_cast<double>(valid_rect.get_height()-
				static_cast<int>(fixed_size))/static_cast<double>(stretch_factor)*
				static_cast<double>((*iterator)->get_stretch_factor()));
		}
		if(height<0){
			height=0;
		}
		rect_t.set_bottom(rect_t.get_top()+height);
		if(!rect_t.is_valid()){
			return(-3);
		}
		//5-2-2.对布局项进行尺寸调整，并且判断调整是否成功。
		if((*iterator)->resize(hdwp,rect_t)<0){
			return(-4);
		}
		//5-2-3.重新计算当前布局项尺寸的起始左坐标。
		rect_t.set_top(((*iterator)->get_rect()).get_bottom());
	}
	//6.更新全部窗口尺寸,并且判断更新是否成功。
	/*
	if(!EndDeferWindowPos(hdwp)){
		return(-5);
	}
	*/
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: resize
 * brief: 重新调整当前布局尺寸。
 * param: width - 宽度。
 *        height - 高度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::resize(const unsigned int width,const unsigned int height){
	//1.调用基类相应虚函数，调整当前布局尺寸。
	MtLayout::resize(width,height);
	//2.累计当前布局中，存储窗口数量、拉伸系数以及固定尺寸。
	//2-1.声明当前操作所需变量。
	unsigned int window_amount=0;
	unsigned int stretch_factor=0;
	unsigned int fixed_size=0;
	//2-2.遍历布局中所有子窗口，统计窗口数量、拉伸系数以及固定尺寸。
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		window_amount+=(*iterator)->get_window_amount();
		stretch_factor+=(*iterator)->get_stretch_factor();
		fixed_size+=(*iterator)->get_fixed_size();
	}
	//2-3.如果当前布局中窗口数量为零，则直接成功返回。
	/*
	if(0==window_amount){
		return(0);
	}
	*/
	//3.申请多窗口尺寸调整内存句柄，并且判断申请是否成功。
	HDWP hdwp=::BeginDeferWindowPos(window_amount);
	if(0==hdwp){
		return(-1);
	}
	//4.根据当前布局留白尺寸，计算当前布局的有效尺寸，并且判断计算是否成功。
	const IntRect valid_rect(_rect->get_left()+static_cast<int>(_margin->get_left()),
		_rect->get_top()+static_cast<int>(_margin->get_top()),
		_rect->get_right()-static_cast<int>(_margin->get_right()),
		_rect->get_bottom()-static_cast<int>(_margin->get_bottom()));
	if(!valid_rect.is_valid()){
		return(-2);
	}
	//5.遍历当前布局中的布局项，调整每一项尺寸。
	//5-1.声明当前操作所需变量。
	int height_t=0;
	IntRect rect(valid_rect);
	//5-2.遍历当前布局项，调整每一个布局项的尺寸。
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		//5-2-1.根据当前布局项拉伸系数，计算当前布局项的新尺寸。
		if(0==stretch_factor){
			height_t=0;
		}else{
			height_t=static_cast<int>(static_cast<double>(valid_rect.get_height()-
				static_cast<int>(fixed_size))/static_cast<double>(stretch_factor)*
				static_cast<double>((*iterator)->get_stretch_factor()));
		}
		if(height_t<0){
			height_t=0;
		}
		rect.set_bottom(rect.get_top()+height_t);
		if(!rect.is_valid()){
			return(-3);
		}
		//5-2-2.对布局项进行尺寸调整，并且判断调整是否成功。
		if((*iterator)->resize(hdwp,rect)<0){
			return(-4);
		}
		//5-2-3.重新计算当前布局项尺寸的起始左坐标。
		rect.set_top(((*iterator)->get_rect()).get_bottom());
	}
	//6.更新全部窗口尺寸,并且判断更新是否成功。
	if(!EndDeferWindowPos(hdwp)){
		return(-5);
	}
	//7.程序运行到此成功返回。
	return(0);
}

/*
 * name: add_spacing
 * brief: 向当前布局中追加一个间隔项。
 * param: spacing_size - 间隔尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::add_spacing(const unsigned int spacing_size){
	//1.创建一个间隔项。
	PtrToItem item(new MtLayoutSpacingItem(
		MtLayoutSpacingItem::ORIENTATION_VERTICAL,spacing_size));
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
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: add_fixed_layout
 * brief: 添加一个固定尺寸的布局。
 * param: layout - 指向一个布局。
 *        fixed_size - 固定尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::add_fixed_layout(MtLayout *layout,const unsigned int fixed_size){
	//1.创建一个布局项。
	PtrToItem item(new MtLayoutFixedLayoutItem(layout,
		MtLayoutFixedLayoutItem::ORIENTATION_VERTICAL,fixed_size));
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
 * name: add_fixed_window
 * brief: 添加固定尺寸的窗口。
 * param: window - 指向窗口。
 *        fixed_size - 固定尺寸。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::add_fixed_window(CWnd *window,const unsigned int fixed_size){
	//1.创建一个窗口项。
	PtrToItem item(new MtLayoutFixedWindowItem(window,
		MtLayoutFixedWindowItem::ORIENTATION_VERTICAL,fixed_size));
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
 * name: set_item_fixed_window
 * brief: 设置布局项固定窗口。
 * param: index - 布局项索引。
 *        window - 指向指定窗口。
 *        fixed_size - 窗口固定尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtVerticalLayout::set_item_fixed_window(
	const unsigned int index,CWnd *window,const unsigned int fixed_size){
	//1.如果当前索引编号超出范围，则直接返回错误。
	if(index>=_items.size()){
		return(-1);
	}
	//2.创建一个窗口项。
	PtrToItem item(new MtLayoutFixedWindowItem(_items[index]->get_rect(),
		window,MtLayoutFixedWindowItem::ORIENTATION_VERTICAL,fixed_size));
	//3.如果创建失败，返回错误编码。
	if(!static_cast<bool>(item)){
		return(-2);
	}
	//4.如果窗口项无效，则返回错误编码。
	if(!item->is_valid()){
		return(-3);
	}
	//5.将当前窗口向加入存储向量中。
	_items[index]=item;
	//6.程序运行到此直接成功返回。
	return(0);
}