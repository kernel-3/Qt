#include"stdafx.h"
#include"MtImageButton.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"
#include"../env/MtGdiplus.h"
#include<Gdiplus.h>

IMPLEMENT_DYNAMIC(MtImageButton,CButton)

/**
 * name: MtImageButton
 * brief: 构造函数。
 * param: type - 按钮类型。
 * return: --
 */
MtImageButton::MtImageButton(const Type type)
	:CButton()
	,_type(type)
	,_is_mouse_tracking(FALSE)
	,_is_mouse_hover(FALSE)
	,_is_checked(FALSE)
	//,_last_state(0)
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_foreground_image()
	,_foreground_image_region_division()
	,_foreground_image_alignment(0)
	,_is_foreground_image_stretched(FALSE)
	,_foreground_image_stretching_factors()
	,_text_color_a(255)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0)
	,_light_text_color_a(0)
	,_light_text_color_r(0)
	,_light_text_color_g(0)
	,_light_text_color_b(0){
}

/**
 * name: ~MtImageButton
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageButton::~MtImageButton(){
}

/**
 * name: set_checked
 * brief: 设置按钮Checked状态。
 * param: is_checked - 是否处于Checked状态。
 *        is_invalidated - 是否刷新当前按钮。
 * return: --
 */
void MtImageButton::set_checked(const BOOL is_checked,const BOOL is_invalidated/*=TRUE*/){
	_is_checked=is_checked;
	if(is_invalidated){
		//update_parent_window();
		Invalidate(FALSE);
	}
}

/**
 * name: get_checked
 * brief: 获取按钮Checked状态。
 * param: --
 * return: 返回按钮Checked状态。
 */
BOOL MtImageButton::get_checked() const{
	return(_is_checked);
}

/**
 * name: load_background_image
 * brief: 加载按钮背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::load_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.根据图片路径进行图片加载，并且判断加载是否成功。
	_background_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_background_image)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-1);
	}
	if(!_background_image->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_background_image_region_division.reset(new MtRegionDivision(_background_image->get_width(),
		_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_background_image_region_division)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: load_background_image
 * brief: 加载按钮背景图片。
 * param: image - 指向图片的智能指针引用。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::load_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.根据传递图片设置背景图片，并且判断设置是否成功。
	_background_image=image;
	if(!static_cast<bool>(_background_image)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-1);
	}
	if(!_background_image->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_background_image_region_division.reset(new MtRegionDivision(_background_image->get_width(),
		_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_background_image_region_division)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: set_background_image_stretching_factors
 * brief: 设置背景图片拉伸系数。
 * param: stretch_left - 左侧拉伸系数。
 *        stretch_top - 顶部拉伸系数。
 *        stretch_right - 左侧拉伸系数。
 *        stretch_bottom - 底部拉伸系数。
 * return: --
 */
void MtImageButton::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: load_foreground_image
 * brief: 加载按钮前景图片。
 * param: image_path - 图片路径。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::load_foreground_image(
	const CString &image_path,const int image_rows,const int image_cols){
	//1.根据图片路径进行图片加载，并且判断加载是否成功。
	_foreground_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_foreground_image)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-1);
	}
	if(!_foreground_image->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_foreground_image_region_division.reset(new MtRegionDivision(_foreground_image->get_width(),
		_foreground_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_foreground_image_region_division)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-3);
	}
	if(!_foreground_image_region_division->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: load_foreground_image
 * brief: 加载按钮前景图片。
 * param: foreground_image - 指向图片的智能指针引用。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::load_foreground_image(
	PtrToImage foreground_image,const int image_rows,const int image_cols){
	//1.根据传递的图片设置当前按钮的前景图片，并且判断设置是否成功。
	_foreground_image=foreground_image;
	if(!static_cast<bool>(_foreground_image)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-1);
	}
	if(!_foreground_image->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_foreground_image_region_division.reset(new MtRegionDivision(_foreground_image->get_width(),
		_foreground_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_foreground_image_region_division)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-3);
	}
	if(!_foreground_image_region_division->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: set_foreground_image_alignment
 * brief: 设置按钮前景图片停靠方式。
 * param: alignment - 停靠方式。
 * return: --
 */
void MtImageButton::set_foreground_image_alignment(const unsigned int alignment){
	_foreground_image_alignment=alignment;
}

/**
 * name: set_foreground_image_stretching_factors
 * brief: 设置前景图片拉伸系数。
 * param: stretch_left - 左侧拉伸系数。
 *        stretch_top - 顶部拉伸系数。
 *        stretch_right - 左侧拉伸系数。
 *        stretch_bottom - 底部拉伸系数。
 * return: --
 */
void MtImageButton::set_foreground_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_foreground_image_stretching_factors.left=stretch_left;
	_foreground_image_stretching_factors.top=stretch_top;
	_foreground_image_stretching_factors.right=stretch_right;
	_foreground_image_stretching_factors.bottom=stretch_bottom;
	_is_foreground_image_stretched=TRUE;
}

/**
 * name: set_text_color
 * brief: 设置文本颜色。
 * param: color_a - 文本颜色a分量。
 *		  color_r - 文本颜色r分量。
 *        color_g - 文本颜色g分量。
 *        color_b - 文本颜色b分量。
 * return: --
 */
void MtImageButton::set_text_color(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
}

/**
 * name: set_light_text_color
 * brief: 设置按钮的高亮文本颜色。
 * param: color_a - 文本颜色a分量。
 *		  color_r - 文本颜色r分量。
 *        color_g - 文本颜色g分量。
 *        color_b - 文本颜色b分量。
 * return: --
 * remark: 如果不设置文本高亮文本颜色，
 *         按钮文本只显示一种文本颜色。
 */
void MtImageButton::set_light_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,const unsigned char color_b){
	_light_text_color_a=color_a;
	_light_text_color_r=color_r;
	_light_text_color_g=color_g;
	_light_text_color_b=color_b;
}

/**
 * name: PreSubclassWindow
 * brief: 子类化按钮前调用此虚拟函数，在此用来将按钮
 *        修改为自绘风格。
 * param: --
 * return: --
 */
void MtImageButton::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

/**
 * name: DrawItem
 * brief: 按钮绘制虚拟函数。
 * param: draw_items_info - 按钮绘制信息。
 * return: --
 */
void MtImageButton::DrawItem(LPDRAWITEMSTRUCT draw_items_info){
	// TODO:  Add your code to draw the specified item
	//1.计算当前按钮状态，如果按钮状态发生变化则刷新父窗口。
	//1-1.声明当前操作所需变量。
	int state=0;
	//1-2.如果当前按钮为按钮类型。
	if(TYPE_BUTTON==_type){
		if(ODS_DISABLED&draw_items_info->itemState){
			state=3;
		}else if((_is_checked)||(ODS_SELECTED&draw_items_info->itemState)){
			state=2;
		}else if(_is_mouse_hover){
			state=1;
		}
	}
	//1-3.如果当前按钮为其它类型。
	else{
		if(ODS_DISABLED&draw_items_info->itemState){
			if(_is_checked){
				state=5;
			}else{
				state=4;
			}
		}else if(_is_checked&&_is_mouse_hover){
			state=3;
		}else if(_is_checked){
			state=2;
		}else if(_is_mouse_hover){
			state=1;
		}
	}
	//2.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(
		draw_items_info->rcItem.right-draw_items_info->rcItem.left,
		draw_items_info->rcItem.bottom-draw_items_info->rcItem.top));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//3.绘制按钮背景。
	draw_background(*memory_bitmap,state);
	//4.绘制按钮前景。
	const CRect foreground_image_rect=draw_foreground(*memory_bitmap,draw_items_info->hDC,state);
	//5.绘制按钮文本。
	draw_text(*memory_bitmap,foreground_image_rect,draw_items_info->hDC,state);
	//6.提供子类为按钮添加绘制内容的接口。
	draw_item(*memory_bitmap,draw_items_info->hDC,state);
	//7.将内存位图黏贴到按钮DC上。
	memory_bitmap->paste_to_dc(draw_items_info->hDC,0,0);
}

/**
 * name: draw_item
 * breif: 绘制当前按钮，此函数在此什么也不实现，只是
 *        为了提供接口给子类，用于添加绘制内容。
 * param: memory_bitmap - 当前准备绘制的内容位图。
 *        dc - 当前准备绘制的内存DC。
 *        state - 当前按钮状态。
 * return: 如果函数执行成功返回值大于等于零否则返回值小于零。
 */
int MtImageButton::draw_item(MtBitmap &/*memory_bitmap*/,HDC /*dc*/,const unsigned int /*state*/){
	return(0);
}

BEGIN_MESSAGE_MAP(MtImageButton,CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/**
 * name: OnMouseMove
 * brief: 鼠标移动消息相应函数，在此用来触发鼠标hover、leave事件。
 * param: flags - 鼠标标志
 *        point - 鼠标位置。
 * return: --
 */
void MtImageButton::OnMouseMove(UINT flags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	if(!_is_mouse_tracking){
		TRACKMOUSEEVENT track_mouse_event;
		track_mouse_event.cbSize=sizeof(TRACKMOUSEEVENT);
		track_mouse_event.hwndTrack=m_hWnd;
		track_mouse_event.dwFlags=TME_LEAVE|TME_HOVER;
		track_mouse_event.dwHoverTime=1;
		_is_mouse_tracking=_TrackMouseEvent(&track_mouse_event);	
	}
	CButton::OnMouseMove(flags,point);
}

/**
 * name: OnMouseHover
 * brief: 鼠标在其上消息相应函数，在此用来设置鼠标在其上标记变量。
 * param: flags - 鼠标标志
 *        point - 鼠标位置。
 * return: --
 */
void MtImageButton::OnMouseHover(UINT flags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=TRUE;
	//update_parent_window();
	Invalidate(FALSE);
	CButton::OnMouseHover(flags,point);
}

/**
 * name: OnMouseLeave
 * brief: 鼠标在离开消息响应函数，在此用来取消鼠标相应标记变量。
 * param: --
 * return: --
 */
void MtImageButton::OnMouseLeave(){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=FALSE;
	_is_mouse_tracking=FALSE;
	//update_parent_window();
	Invalidate(FALSE);
	CButton::OnMouseLeave();
}

/**
 * name: OnEraseBkgnd
 * brief: 背景擦出消息响应函数,这里用来消除按钮不必要的重绘。
 * param: dc - 当前设备DC。
 * return: 如果函数执行成功返回TRUE、否则返回FALSE。
 */
BOOL MtImageButton::OnEraseBkgnd(CDC * /*dc*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CButton::OnEraseBkgnd(dc));
}

/**
 * name: update_parent_window
 * brief: 更新按钮父亲窗口的相应区域。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::update_parent_window(){
	CRect rect_parent_window(0,0,0,0);
	GetWindowRect(rect_parent_window);
	CWnd *parent=GetParent();
	if(0==parent){
		return(-1);
	}
	parent->ScreenToClient(rect_parent_window);
	parent->InvalidateRect(rect_parent_window);
	return(0);
}

/**
 * name: draw_background
 * brief: 绘制按钮的背景。
 * param: memory_bitmap - 内存位图。
 *		  state - 按钮当前状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
	//1.判断当前背景图片是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_background_image)){
		return(-1);
	}
	if(!_background_image->is_valid()){
		return(-2);
	}
	//2.判断当前背景图片剪裁器是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_background_image_region_division)){
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		return(-4);
	}
	//3.获取背景图片尺寸，如果获取失败直接返回错误。
	const CRect image_rect=_background_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.将当前背景图片绘制的内存位图上。
	if(_is_background_image_stretched){
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,0,0,
			memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,0,0,
			memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height())<0){
			return(-7);
		}
	}
	//5.成功返回。
	return(0);
}

/**
 * name: draw_foreground
 * brief: 绘制按钮前景。
 * param: memory_bitmap - 内存位图。
 *        dc - 绘图DC.
 *		  state - 按钮状态。
 * return: 如果函数执行成功返回前景图片位置，否则返回一个空的位置信息（
 *         调用CRect::IsRectEmpty函数确认）。
 */
CRect MtImageButton::draw_foreground(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.判断当前前景图片是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_foreground_image)){
		return(CRect(0,0,0,0));
	}
	if(!_foreground_image->is_valid()){
		return(CRect(0,0,0,0));
	}
	//2.判断当前前景图片剪裁器是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_foreground_image_region_division)){
		return(CRect(0,0,0,0));
	}
	if(!_foreground_image_region_division->is_valid()){
		return(CRect(0,0,0,0));
	}
	//3.获取前景图片尺寸，如果获取失败直接返回错误。
	const CRect image_rect=_foreground_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(CRect(0,0,0,0));
	}
	//4.根据前景图片停靠方式，计算前景图片黏贴位置。
	int dest_x=0;
	if(ALIGNMENT_HCENTER&_foreground_image_alignment){
		dest_x=(memory_bitmap.get_width()-image_rect.Width())/2;
	}else if(ALIGNMENT_RIGHT&_foreground_image_alignment){
		dest_x=memory_bitmap.get_width()-image_rect.Width()-IMAGE_MARGIN;
	}else{
		dest_x=IMAGE_MARGIN;
	}
	int dest_y=0;
	if(ALIGNMENT_VCENTER&_foreground_image_alignment){
		dest_y=(memory_bitmap.get_height()-image_rect.Height())/2;
	}else if(ALIGNMENT_BOTTOM&_foreground_image_alignment){
		dest_y=memory_bitmap.get_height()-image_rect.Height()-IMAGE_MARGIN;
	}else{
		/*dest_y=IMAGE_MARGIN;*/
		CSize text_size(0,0);
		CString text(_T(""));
		GetWindowText(text);
		MtGdiplus::calculate_text_size(text,dc,static_cast<HFONT>(
			GetFont()->GetSafeHandle()),text_size);
		dest_y=(memory_bitmap.get_height()-image_rect.Height()-text_size.cy)/2;
	}
	if((TYPE_BUTTON==_type)&&(2==state)){
		++dest_x;
		++dest_y;
	}
	//5.将当前前景图片绘制的内存位图上。
	if(_is_foreground_image_stretched){
		if(_foreground_image->paste_to_bitmap_ex(&memory_bitmap,
			dest_x,dest_y,image_rect.Width(),image_rect.Height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height(),
			_foreground_image_stretching_factors.left,
			_foreground_image_stretching_factors.top,
			_foreground_image_stretching_factors.right,
			_foreground_image_stretching_factors.bottom)<0){
			return(CRect(0,0,0,0));
		}
	}else{
		if(_foreground_image->paste_to_bitmap(&memory_bitmap,
			dest_x,dest_y,image_rect.Width(),image_rect.Height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height())<0){
			return(CRect(0,0,0,0));
		}
	}
	//6.成功返回。
	return(CRect(dest_x,dest_y,dest_x+image_rect.Width(),dest_y+image_rect.Height()));
}

/**
 * name: draw_text
 * brief: 绘制按钮标题。
 * param: memory_bitmap - 内存位图。
 *		  foreground_image_rect - 前景图片位置区域。
 *        dc - 绘图设备DC。
 *        state - 按钮状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageButton::draw_text(MtBitmap &memory_bitmap,
	const CRect &foreground_image_rect,HDC dc,const unsigned int state){
	//1.获取当前按钮标题。
	CString text(_T(""));
	GetWindowText(text);
	if(text.IsEmpty()){
		return(0);
	}
	//2.如果当前按钮前景图片位置为空。
	if(foreground_image_rect.IsRectEmpty()){
		//2-1.计算文本位置。
		int dest_x=0;
		int dest_y=0;
		int dest_width=memory_bitmap.get_width();
		int dest_height=memory_bitmap.get_height();
		if((TYPE_BUTTON==_type)&&(2==state)){
			++dest_x;
			++dest_y;
		}
		//2-2.进行文本绘制。
		//2-2-1.如果当前按钮处于失效状态。
		if(3==state){
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,
				DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B)<0){
				return(-1);
			}
		}
		//2-2-2.如果当前按钮处于使能状态。
		else{
			unsigned char text_color_a=_text_color_a;
			unsigned char text_color_r=_text_color_r;
			unsigned char text_color_g=_text_color_g;
			unsigned char text_color_b=_text_color_b;
			if(0!=_light_text_color_a){
				if((TYPE_BUTTON==_type)&&((1==state)||(2==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}else if(((TYPE_CHECK_BOX==_type)||(TYPE_RADIO_BOX==_type))&&
					((1==state)||(3==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}
			}
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,text_color_a,text_color_r,text_color_g,
				text_color_b)<0){
				return(-2);
			}
		}
	}
	//3.如果当前按钮前景图片位置不为空。
	else{
		//3-1.计算文本位置。
		int dest_x=0;
		int dest_y=0;
		int dest_width=memory_bitmap.get_width();
		int dest_height=memory_bitmap.get_height();
		if(ALIGNMENT_HCENTER&_foreground_image_alignment){
			if(ALIGNMENT_BOTTOM&_foreground_image_alignment){
				dest_y+=IMAGE_MARGIN;
				dest_height=foreground_image_rect.top-IMAGE_MARGIN-dest_y;
			}else{
				dest_y=foreground_image_rect.bottom+IMAGE_MARGIN;
				dest_height=dest_height-IMAGE_MARGIN-dest_y;
			}
		}else if(ALIGNMENT_RIGHT&_foreground_image_alignment){
			dest_x+=IMAGE_MARGIN;
			dest_width=foreground_image_rect.left-IMAGE_MARGIN-dest_x;
		}else{
			dest_x=foreground_image_rect.right+IMAGE_MARGIN;
			dest_width=dest_width-IMAGE_MARGIN-dest_x;
		}
		if((TYPE_BUTTON==_type)&&(2==state)){
			++dest_x;
			++dest_y;
		}
		//3-2.进行文本绘制。
		//3-2-1.如果当前按钮处于失效状态。
		if(((TYPE_BUTTON==_type)&&(3==state))||(4==state)||(5==state)){
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,
				DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B)<0){
				return(-3);
			}
		}
		//3-2-2.如果当前按钮处于使能状态。
		else{
			unsigned char text_color_a=_text_color_a;
			unsigned char text_color_r=_text_color_r;
			unsigned char text_color_g=_text_color_g;
			unsigned char text_color_b=_text_color_b;
			if(0!=_light_text_color_a){
				if((TYPE_BUTTON==_type)&&((1==state)||(2==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}else if(((TYPE_CHECK_BOX==_type)||(TYPE_RADIO_BOX==_type))&&
					((1==state)||(3==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}
			}
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,text_color_a,text_color_r,text_color_g,
				text_color_b)<0){
				return(-4);
			}
		}
	}
	//4.成功返回。
	return(0);
}