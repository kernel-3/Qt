// source-code/control/MtImageStatic.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageStatic.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"

IMPLEMENT_DYNAMIC(MtImageStatic,CStatic)

/**
 * name: MtImageStatic
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtImageStatic::MtImageStatic()
	:CStatic()
	,_text(_T(""))
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_background_image_index(0)
	,_text_alignment(0)
	,_text_color_a(255)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0){
}

/**
 * name: ~MtImageStatic
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageStatic::~MtImageStatic(){
}

/**
 * name: load_background_image
 * brief: 加载背景图片。
 * param: image_path - 图片路径。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageStatic::load_background_image(
	const CString &image_path,const int image_rows/*=1*/,const int image_cols/*=1*/){
	//1.根据图片路径创建新的背景图片。
	_background_image.reset(new MtImage(image_path));
	//2.判断背景图片创建是否成功。
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
	//3.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
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
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: load_background_image
 * brief: 加载背景图片。
 * param: image - 指向背景图片的智能指针。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageStatic::load_background_image(
	PtrToImage image,const int image_rows/*=1*/,const int image_cols/*=1*/){
	//1.根据图片的只能指针创建的背景图片。
	_background_image=image;
	//2.判断背景图片创建是否成功。
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
	//3.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
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
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: set_background_image_stretching_factors
 * brief: 设置背景图片拉伸系数。
 * param: stretch_left - 背景图片左侧拉伸系数。
 *        stretch_top - 背景图片顶部拉伸系数。
 *        stretch_right - 背景图片右侧拉伸系数。
 *        stretch_bottom - 背景图片底部拉伸系数。
 * return: --
 */
void MtImageStatic::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: clear_background_image_stretching_factors
 * brief: 清除背景图片的拉伸系数。
 * param: --
 * return: --
 */
void MtImageStatic::clear_background_image_stretching_factors(){
	_background_image_stretching_factors.left=0;
	_background_image_stretching_factors.top=0;
	_background_image_stretching_factors.right=0;
	_background_image_stretching_factors.bottom=0;
	_is_background_image_stretched=FALSE;
}

/**
 * name: set_background_image_index
 * brief: 设置当前静态文本框显示的背景图片索引编号。
 * param: index - 当前显示的背景图片编号。
 *        is_invalidate - 是否刷新当前窗口。
 * return: --
 */ 
void MtImageStatic::set_background_image_index(
	const int index,const BOOL is_invalidate/*=TRUE*/){
	_background_image_index=index;
	if(is_invalidate){
		Invalidate(TRUE);
	}
}

/**
 * name: set_text
 * brief: 设置静态文本框文本。
 * param: text - 静态文本框文本。
 *        is_invalidate - 是否刷新静态文本框。
 * return: --
 */
void MtImageStatic::set_text(
	const CString &text,const BOOL is_invalidate/*=FALSE*/){
	SetWindowText(text);
	_text=text;
	if(is_invalidate){
		invalidate_parent_window();
		Invalidate(FALSE);
	}
}

/**
 * name: get_text
 * brief: 获取静态文本框文本。
 * param: --
 * return: 返回静态文本框文本。
 */
CString MtImageStatic::get_text(){
	CString text(_T(""));
	GetWindowText(text);
	if(!text.IsEmpty()){
		_text=text;
		SetWindowText(_T(""));
	}
	return(_text);
}

/**
 * name: set_text_alignment
 * brief: 设置文本停靠方式。
 * param: alignment - 文本停靠方式。
 * return: --
 */
void MtImageStatic::set_text_alignment(const unsigned int alignment){
	_text_alignment=alignment;
}

/**
 * name: get_text_alignment
 * brief: 获取文本停靠方式。
 * param: --
 * return: 返回当前文本停靠方式。
 */
unsigned int MtImageStatic::get_text_alignment() const{
	return(_text_alignment);
}

/**
 * name: set_text_color
 * brief: 设置静态文本框的文本颜色。
 * param: color_a - 文本颜色的a分量。
 *        color_r - 文本颜色的r分量。
 *        color_g - 文本颜色的g分量。
 *        color_b - 文本颜色的b分量。
 *        is_invalidate - 是否刷新静态文本框。
 * return: --
 */
void MtImageStatic::set_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
	if(is_invalidate){
		invalidate_parent_window();
		//Invalidate(FALSE);
	}
}

BEGIN_MESSAGE_MAP(MtImageStatic,CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/**
 * name: OnPaint
 * brief: 控件绘制消息响应函数，在此用来实现
 *        控件的绘制。
 * param: --
 * return: --
 */
void MtImageStatic::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.获取当前窗口尺寸信息。
	CRect window_rect(0,0,0,0);
	GetClientRect(window_rect);
	//2.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||
		(!memory_bitmap->is_valid())){
		return;
	}
	//3.绘制控件背景。
	draw_background(*memory_bitmap);
	//4.绘制控件文本。
	draw_text(*memory_bitmap,dc.GetSafeHdc());
	//5.将当前内存位图黏贴到DC设备上。
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CStatic::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: 窗口擦除消息响应函数。这里用来禁止擦除操作，减轻重绘负担。
 * param: --
 * return: 这里总是返回TRUE。
 */
BOOL MtImageStatic::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return CStatic::OnEraseBkgnd(pDC);
}

/**
 * name: OnSize
 * brief: 窗口尺寸调整消息响应函数。
 * param: nType - 尺寸调整类型。
 *        cx - 宽度。
 *        cy - 高度。
 */
void MtImageStatic::OnSize(UINT nType,int cx,int cy){
	CStatic::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.如果当前尺寸发生变化，更新父窗口相应区域。
	invalidate_parent_window();
	//2.重绘当前窗口。
	OnPaint();
}

/**
 * name: invalidate_parent_window
 * brief: 刷新父窗口。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageStatic::invalidate_parent_window(){
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
 * brief: 绘制控件背景。
 * param: memory_bitmap - 内存位图。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageStatic::draw_background(MtBitmap &memory_bitmap){
	//1.如果当前背景图片不合法，则直接返回错误。
	if((!static_cast<bool>(_background_image))||
		(!_background_image->is_valid())){
		return(-1);
	}
	//2.如果当前背景图片裁剪器不合法。
	if((!static_cast<bool>(_background_image_region_division))||
		(!_background_image_region_division->is_valid())){
		return(-2);
	}
	//2.计算当前背景图片绘制区域。
	const CRect image_rect=_background_image_region_division->
		get_child_region_rect(_background_image_index);
	if(image_rect.IsRectEmpty()){
		return(-3);
	}
	//2.向内存位图黏贴背景图片。
	//2-1.如果当前背景图片拉伸系数启用。
	if(_is_background_image_stretched){
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-4);
		}
	}
	//2-2.如果当前背景图片拉伸系数没有启用。
	else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-5);
		}
	}
	//3.程序运行到此，成功返回。
	return(0);
}

/**
 * name: draw_text
 * brief: 绘制静态文本框文本。
 * param: memory_bitmap - 内存位图。 
 *		  dc - 准备绘制文本的DC设备。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageStatic::draw_text(MtBitmap &memory_bitmap,const HDC dc){
	//1.获取当前静态文本框文本。
	CString text=get_text();
	if(text.IsEmpty()){
		return(0);
	}
	//2.计算当前文本停靠方式。
	MtBitmap::Alignment text_h_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_text_alignment&ALIGNMENT_HCENTER){
		text_h_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_text_alignment&ALIGNMENT_RIGHT){
		text_h_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment text_v_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_text_alignment&ALIGNMENT_VCENTER){
		text_v_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_text_alignment&ALIGNMENT_BOTTOM){
		text_v_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//3.获取当前文本绘制的字体。
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		WINDOW_MARGIN,WINDOW_MARGIN,memory_bitmap.get_width()-WINDOW_MARGIN,
		memory_bitmap.get_height()-WINDOW_MARGIN,
		_text_color_a,_text_color_r,_text_color_g,_text_color_b,
		text_h_alignment,text_v_alignment)<0){
		return(-1);
	}
	//4.成功返回。
	return(0);
}