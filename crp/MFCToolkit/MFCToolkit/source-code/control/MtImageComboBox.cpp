// source-code/control/MtImageComboBox.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageComboBox.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"
#include<assert.h>

IMPLEMENT_DYNAMIC(MtImageComboBox,CComboBox)

/**
 * name: MtImageComboBox
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtImageComboBox::MtImageComboBox()
	:CComboBox()
	,_is_mouse_tracking(FALSE)
	,_is_mouse_hover(FALSE)
	,_is_list_box_visible(FALSE)
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_text_alignment(0)
	,_text_color_a(0)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0)
	,_list_box_background_image()
	,_list_box_background_image_slicer()
	,_is_list_box_background_image_stretched(FALSE)
	,_list_box_background_image_stretching_factors()
	,_list_box_text_alignment(0)
	,_list_box_text_color_a(0)
	,_list_box_text_color_r(0)
	,_list_box_text_color_g(0)
	,_list_box_text_color_b(0){
}

/**
 * name: MtImageComboBox
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageComboBox::~MtImageComboBox(){
}

/**
 * name: load_background_image
 * brief: 加载按钮背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::load_background_image(const CString &image_path,
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
 * param: image - 指向背景图片的智能指针。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::load_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.根据图片智能指针进行图片加载，并且判断加载是否成功。
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
void MtImageComboBox::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: set_text_alignment
 * brief: 设置文本停靠方式。
 * param: alignment - 文本停靠方式。
 * return: --
 */
void MtImageComboBox::set_text_alignment(const unsigned int alignment){
	_text_alignment=alignment;
}

/**
 * name: set_text_color
 * brief: 设置文本颜色。
 * param: color_a - 文本颜色的a分量。
 *        color_r - 文本颜色的r分量。
 *        color_g - 文本颜色的g分量。
 *        color_b - 文本颜色的b分量。
 *        is_invalidate - 是否刷新下拉框。
 * return: --
 */
void MtImageComboBox::set_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
	if(is_invalidate){
		Invalidate(FALSE);
	}
}

/**
 * name: load_list_box_background_image
 * brief: 加载下拉框中列表框背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果 下拉框选项背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::load_list_box_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.根据图片路径进行图片加载，并且判断加载是否成功。
	_list_box_background_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_list_box_background_image)){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_list_box_background_image_slicer.reset(new MtRegionDivision(_list_box_background_image->get_width(),
		_list_box_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: load_list_box_background_image
 * brief: 加载下拉框中列表框背景图片。
 * param: image - 指向图片的智能指针。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果 下拉框选项背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::load_list_box_background_image(
	PtrToImage image,const int image_rows,const int image_cols){
	//1.根据图片智能指针进行图片加载，并且判断加载是否成功。
	_list_box_background_image=image;
	if(!static_cast<bool>(_list_box_background_image)){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_list_box_background_image_slicer.reset(new MtRegionDivision(_list_box_background_image->get_width(),
		_list_box_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: set_list_box_background_image_stretching_factors
 * brief: 设置下拉框中列表框背景图片拉伸系数。
 * param: stretch_left - 左侧拉伸系数。
 *        stretch_top - 顶部拉伸系数。
 *        stretch_right - 左侧拉伸系数。
 *        stretch_bottom - 底部拉伸系数。
 * return: --
 */
void MtImageComboBox::set_list_box_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_list_box_background_image_stretching_factors.left=stretch_left;
	_list_box_background_image_stretching_factors.top=stretch_top;
	_list_box_background_image_stretching_factors.right=stretch_right;
	_list_box_background_image_stretching_factors.bottom=stretch_bottom;
	_is_list_box_background_image_stretched=TRUE;
}

/**
 * name: set_list_box_text_alignment
 * brief: 设置下拉框中列表框文本停靠方式。
 * param: alignment - 停靠方式。
 * return: --
 */
void MtImageComboBox::set_list_box_text_alignment(const unsigned int alignment){
	_list_box_text_alignment=alignment;
}

/**
 * name: set_list_box_text_color
 * brief: 设置下拉框中列表框文本颜色。
 * param: color_a - 文本颜色的a分量。
 *        color_r - 文本颜色的r分量。
 *        color_g - 文本颜色的g分量。
 *        color_b - 文本颜色的b分量。
 *        is_invalidate - 是否刷新下拉框。
 * return: --
 */
void MtImageComboBox::set_list_box_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_list_box_text_color_a=color_a;
	_list_box_text_color_r=color_r;
	_list_box_text_color_g=color_g;
	_list_box_text_color_b=color_b;
	if(is_invalidate){
		Invalidate(FALSE);
	}
}

/**
 * name: PreSubclassWindow
 * brief: 窗口子类化前调用此虚拟函数，在此用来去掉
 *        下拉框中列表框的边框。
 * param: --
 * return: --
 */
void MtImageComboBox::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//1.声明当前函数操作所需变量。
	COMBOBOXINFO combo_box_info;
	combo_box_info.cbSize=sizeof(COMBOBOXINFO);
	//2.获取当前下拉框信息。
	const BOOL result=GetComboBoxInfo(&combo_box_info);
	assert(TRUE==result);
	//3.获取当前列表框类指针。
	CWnd *list_box=CWnd::FromHandle(combo_box_info.hwndList);
	assert(0!=list_box);
	//4.去掉列表框的边框。
	list_box->ModifyStyle(WS_BORDER,0);
	//5.调用基类相应虚拟函数。
	CComboBox::PreSubclassWindow();
}

/**
 * name: DrawItem
 * brief: 按钮绘制虚拟函数。
 * param: lpDrawItemStruct - 按钮绘制信息。
 * return: --
 */
void MtImageComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
	//TODO:  Add your code to draw the specified item
	//A.如果当前绘制的为下拉框文本编辑框中文本，则刷新控件，交给OnPaint函数绘制。
	if((static_cast<int>(lpDrawItemStruct->itemID)>=0)&&(
		ODS_COMBOBOXEDIT&lpDrawItemStruct->itemState)){
		Invalidate(FALSE);
	}
	//B.如果当前绘制的为下拉框中的文本。
	else if(static_cast<int>(lpDrawItemStruct->itemID)>=0){
		//1.计算当前窗口尺寸。
		CRect window_rect(lpDrawItemStruct->rcItem);
		//2.计算当前下拉框状态。
		unsigned int state=0;
		if(ODS_SELECTED&lpDrawItemStruct->itemState){
			state=1;
			/*
			if(GetCount()-1==static_cast<int>(lpDrawItemStruct->itemID)){
				state=3;
			}else{
				state=2;
			}
			*/
		}else{
			state=0;
			/*
			if(GetCount()-1==static_cast<int>(lpDrawItemStruct->itemID)){
				state=1;
			}else{
				state=0;
			}
			*/
		}
		//3.创建内存位图，并且判断创建是否成功。
		PtrToBitmap memory_bitmap(new MtBitmap(
			window_rect.Width(),window_rect.Height()));
		if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
			return;
		}
		//4.根据当前列表框状态，绘制列表框背景。
		draw_list_box_background(*memory_bitmap,state);
		//5.进行当前文本的绘制。
		CString text(_T(""));
		GetLBText(lpDrawItemStruct->itemID,text);
		draw_list_box_text(*memory_bitmap,lpDrawItemStruct->hDC,text);
		//6.将内存位图黏贴到绘图DC设备上。
		memory_bitmap->paste_to_dc(
			lpDrawItemStruct->hDC,window_rect.left,window_rect.top);
	}
}

/**
 * name: MeasureItem
 * brief: 自绘时负责调整下拉框选项尺寸。
 * param: lpMeasureItemStruct - 指向列表选项信息结构体的指针。
 * return: --
 */
void MtImageComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){
	// TODO:  Add your code to determine the size of specified item
	if(static_cast<int>(lpMeasureItemStruct->itemID)>=0){
		/*
		//1.获取当前列表框文本。
		LPCTSTR text=reinterpret_cast<LPCTSTR>(lpMeasureItemStruct->itemData);
		assert(0!=text);
		//2.获取当前文本尺寸。
		CSize text_size(0,0);
		CDC *dc=GetDC();
		assert(0!=dc);
		text_size=dc->GetTextExtent(text);
		ReleaseDC(dc);
		//3.设置当前下拉框高度。
		*/
		lpMeasureItemStruct->itemHeight=25/*static_cast<int>(1.5*text_size.cy)*/;
	}
}

BEGIN_MESSAGE_MAP(MtImageComboBox,CComboBox)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(CBN_DROPDOWN,&MtImageComboBox::OnCbnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP,&MtImageComboBox::OnCbnCloseup)
END_MESSAGE_MAP()

/**
 * name: MtImageComboBox
 * brief: 控件绘制消息响应函数，负责实现控件绘制。
 * param: --
 * return: --
 */
void MtImageComboBox::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.计算当前按钮状态，如果按钮状态发生变化则刷新父窗口。
	int state=0;
	if(!IsWindowEnabled()){
		state=3;
	}else if(_is_list_box_visible){
		state=2;
	}else if(_is_mouse_hover){
		state=1;
	}
	//2.获取当前窗口尺寸。
	CRect window_rect;
	GetClientRect(window_rect);
	//3.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//4.绘制下拉框控件背景。
	draw_background(*memory_bitmap,state);
	//5.绘制当前下拉框文本。
	draw_text(*memory_bitmap,state,dc.GetSafeHdc());
	//6.将内存位图黏贴到绘图DC设备上。
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CComboBox::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: 控件背景擦除消息响应函数，这里主要用来禁止不必要
 *        的重绘。
 * param: pDC - 绘图DC设备。
 * return: 此处一直返回TRUE。
 */
BOOL MtImageComboBox::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CComboBox::OnEraseBkgnd(pDC));
}

/**
 * name: OnMouseMove
 * brief: 鼠标移动消息相应函数，在此用来触发鼠标hover、leave事件。
 * param: flags - 鼠标标志
 *        point - 鼠标位置。
 * return: --
 */
void MtImageComboBox::OnMouseMove(UINT nFlags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	if(!_is_mouse_tracking){
		TRACKMOUSEEVENT track_mouse_event;
		track_mouse_event.cbSize=sizeof(TRACKMOUSEEVENT);
		track_mouse_event.hwndTrack=m_hWnd;
		track_mouse_event.dwFlags=TME_LEAVE|TME_HOVER;
		track_mouse_event.dwHoverTime=1;
		_is_mouse_tracking=_TrackMouseEvent(&track_mouse_event);	
	}
	CComboBox::OnMouseMove(nFlags, point);
}

/**
 * name: OnMouseHover
 * brief: 鼠标在其上消息相应函数，在此用来设置鼠标在其上标记变量。
 * param: flags - 鼠标标志
 *        point - 鼠标位置。
 * return: --
 */
void MtImageComboBox::OnMouseHover(UINT nFlags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=TRUE;
	Invalidate(FALSE);
	CComboBox::OnMouseHover(nFlags, point);
}

/**
 * name: OnMouseLeave
 * brief: 鼠标在离开消息响应函数，在此用来取消鼠标相应标记变量。
 * param: --
 * return: --
 */
void MtImageComboBox::OnMouseLeave(){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=FALSE;
	_is_mouse_tracking=FALSE;
	Invalidate(FALSE);
	CComboBox::OnMouseLeave();
}

/**
 * name: CtlColor
 * brief: 颜色反射消息，这里重要用来将控件透明，只显示自绘部分。
 * param: pDC - 绘图DC设备。
 *        nCtlColor - 控件颜色编码。
 * return: 总是返回空画刷。
 */
HBRUSH MtImageComboBox::CtlColor(CDC *pDC,UINT /*nCtlColor*/){
	// TODO:  Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	return((HBRUSH)GetStockObject(NULL_BRUSH));
	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	//return(NULL);
}


/**
 * name: OnCbnDropdown
 * brief: 当下拉框显示列表框时调用此消息响应函数。这里
 *        用来标记下拉框控件中列表框的显示。
 * param: --
 * return: --
 */
void MtImageComboBox::OnCbnDropdown(){
	// TODO: Add your control notification handler code here
	_is_list_box_visible=TRUE;
	Invalidate(FALSE);
}

/**
 * name: OnCbnCloseup
 * brief: 当下拉框关闭列表框时调用此消息响应函数。这里
 *        用来取消下拉框控件中列表框的显示标记。
 * param: --
 * return: --
 */
void MtImageComboBox::OnCbnCloseup(){
	// TODO: Add your control notification handler code here
	_is_list_box_visible=FALSE;
	Invalidate(FALSE);
}

/**
 * name: draw_background
 * brief: 绘制下拉框的背景。
 * param: memory_bitmap - 内存位图。
 *		  state - 下拉框当前状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
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
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-7);
		}
	}
	//5.成功返回。
	return(0);
}

/**
 * name: draw_text
 * brief: 绘制下拉框文本。
 * param:  state - 当前控件状态。
 *         dc - 绘图设备DC。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::draw_text(MtBitmap &memory_bitmap,const unsigned int state,const HDC dc){
	//1.如果当前DC设备非法，则返回错误编码。
	if(0==dc){
		return(-1);
	}
	//2.获取当前下拉框应该显示的文本。
	int item=GetCurSel();
	if(CB_ERR==item){
		return(0);
	}
	CString text(_T(""));
	GetLBText(item,text);
	if(text.IsEmpty()){
		return(-2);
	}
	//3.计算当前文本停靠方式。
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
	//4.绘制当前文本。
	if(3==state){
		if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
			TEXT_MARGIN,TEXT_MARGIN,
			memory_bitmap.get_width()-_background_image_stretching_factors.right-TEXT_MARGIN,
			memory_bitmap.get_height()-TEXT_MARGIN,
			DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B,
			text_h_alignment,text_v_alignment)<0){
			return(-3);
		}
	}else{
		if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
			TEXT_MARGIN,TEXT_MARGIN,
			memory_bitmap.get_width()-_background_image_stretching_factors.right-TEXT_MARGIN,
			memory_bitmap.get_height()-TEXT_MARGIN,
			_text_color_a,_text_color_r,_text_color_g,_text_color_b,
			text_h_alignment,text_v_alignment)<0){
			return(-4);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: draw_list_box_background
 * breif: 绘制下拉框中列表框背景。
 * param: memory_bitmap - 内存位图。
 *		  state - 当前下拉框中列表框状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::draw_list_box_background(MtBitmap &memory_bitmap,const unsigned int state){
	//1.判断当前背景图片是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_list_box_background_image)){
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		return(-2);
	}
	//2.判断当前背景图片剪裁器是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		return(-4);
	}
	//3.获取背景图片尺寸，如果获取失败直接返回错误。
	const CRect image_rect=_list_box_background_image_slicer->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.将当前背景图片绘制的内存位图上。
	if(_is_list_box_background_image_stretched){
		if(_list_box_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_list_box_background_image_stretching_factors.left,
			_list_box_background_image_stretching_factors.top,
			_list_box_background_image_stretching_factors.right,
			_list_box_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_list_box_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-7);
		}
	}
	//5.成功返回。
	return(0);
}

/**
 * name: draw_list_box_text
 * brief: 绘制下拉框中列表框的文本。
 * param: memory_bitmap - 内存位图。
 *        dc - 绘图使用的设备DC。
 *        text - 文本内容。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageComboBox::draw_list_box_text(
	MtBitmap &memory_bitmap,const HDC dc,const CString &text){
	//1.如果当前DC设备不合法，则直接返回错误编码。
	if(0==dc){
		return(-1);
	}
	//2.如果当前文本为空，则直接返回。
	if(text.IsEmpty()){
		return(0);
	}
	//3.计算当前文本停靠方式。
	MtBitmap::Alignment text_h_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_list_box_text_alignment&ALIGNMENT_HCENTER){
		text_h_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_list_box_text_alignment&ALIGNMENT_RIGHT){
		text_h_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment text_v_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_list_box_text_alignment&ALIGNMENT_VCENTER){
		text_v_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_list_box_text_alignment&ALIGNMENT_BOTTOM){
		text_v_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//3.绘制当前文本。
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		TEXT_MARGIN,TEXT_MARGIN,memory_bitmap.get_width()-TEXT_MARGIN,
		memory_bitmap.get_height()-TEXT_MARGIN,
		_list_box_text_color_a,_list_box_text_color_r,
		_list_box_text_color_g,_list_box_text_color_b,
		text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//4.程序运行到此直接成功返回。
	return(0);
}