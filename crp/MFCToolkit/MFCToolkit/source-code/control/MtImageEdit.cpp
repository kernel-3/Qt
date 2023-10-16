// source-code/control/MtImageEdit.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageEdit.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"

// MtImageEdit
IMPLEMENT_DYNAMIC(MtImageEdit,CEdit)

//初始化静态变量
const COLORREF MtImageEdit::DISABLE_TEXT_COLOR=RGB(100,100,100);

/*
 * name: MtImageEdit
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtImageEdit::MtImageEdit()
	:CEdit()
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_is_there_in_focus(FALSE)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0){
}

/*
 * name: MtImageEdit
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageEdit::~MtImageEdit(){
}

/**
 * name: load_background_image
 * brief: 加载按钮背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageEdit::load_background_image(const CString &image_path,
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
int MtImageEdit::load_background_image(PtrToImage image,
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
void MtImageEdit::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: set_text_color
 * brief: 设置文本颜色。
 * param: text_color_r - 颜色r分量。
 *        text_color_g - 颜色g分量。
 *        text_color_b - 颜色b分量。
 *        is_invalidated - 是否更新窗口。
 * return: --
 */
void MtImageEdit::set_text_color(const unsigned char text_color_r,
	const unsigned char text_color_g,const unsigned char text_color_b,
	const BOOL is_invalidated/*=FALSE*/){
	_text_color_r=text_color_r;
	_text_color_g=text_color_g;
	_text_color_b=text_color_b;
	if(is_invalidated){
		Invalidate(TRUE);
	}
}

/**
 * name: PreTranslateMessage
 * breif: 消息转发前调用此虚拟函数。在此负责拦截键
 *        盘消息，更新控件。
 * param: pMsg - 指向消息结构体指针。
 * return: --
 */
BOOL MtImageEdit::PreTranslateMessage(MSG *pMsg){
	//TODO: Add your specialized code here and/or call the base class
	//1.如果当前消息为键盘消息，则拦截，并更新控件。
	if(WM_KEYDOWN==pMsg->message){
		Invalidate(TRUE);
	}
	//2.调用基类相应处理函数。
	return(CEdit::PreTranslateMessage(pMsg));
}

BEGIN_MESSAGE_MAP(MtImageEdit,CEdit)
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_CHANGE,&MtImageEdit::OnEnChange)
END_MESSAGE_MAP()

//MtImageEdit message handlers

/**
 * name: OnEraseBkgnd
 * brief: 窗口背景擦除消息响应函数，在此用来绘制
 *        控件的背景图案。
 * param: pDC - 当前使用的绘图DC设备。
 * return: 如果函数执行成功返回值为TRUE，否则返回值为FALSE。
 */
BOOL MtImageEdit::OnEraseBkgnd(CDC *pDC){
	// TODO: Add your message handler code here and/or call default
	//1.获取当前窗口尺寸。
	CRect window_rect(0,0,0,0);
	GetWindowRect(window_rect);
	ScreenToClient(window_rect);
	//2.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||
		(!memory_bitmap->is_valid())){
		return(TRUE);
	}
	//3.绘制编辑框背景图片。
	int state=0;
	if(!IsWindowEnabled()){
		state=2;
	}else if(_is_there_in_focus){
		state=1;
	}
	draw_background(*memory_bitmap,state);
	//4.将内存位图黏贴到窗口DC设备上。{
	CDC *dc=GetWindowDC();
	memory_bitmap->paste_to_dc(dc->GetSafeHdc(),0,0);
	ReleaseDC(dc);
	//5.程序执行到此直接成功返回。
	//return(TRUE)	//unsolved: 直接返回TRUE时，发现控件绘制时会将文字盖掉，原因尚不明朗，
	                //          感觉上是pDC与dc绘制顺序的问题。
	return(CEdit::OnEraseBkgnd(pDC));
}

/**
 * name: OnSetFocus
 * brief: 编辑框获取焦点消息响应函数，这里用来记录焦点是否获取。
 * param: pOldWnd - 指向上一次焦点所在窗口。
 * return: --
 */
void MtImageEdit::OnSetFocus(CWnd* pOldWnd){
	CEdit::OnSetFocus(pOldWnd);
	//TODO: Add your message handler code here
	_is_there_in_focus=TRUE;
	Invalidate(TRUE);
}

/**
 * name: OnKillFocus
 * brief: 编辑框失去焦点消息响应函数，这里用来记录焦点是否获取。
 * param: pNewWnd - 指向当前焦点所在窗口。
 * return: --
 */
void MtImageEdit::OnKillFocus(CWnd *pNewWnd){
	CEdit::OnKillFocus(pNewWnd);
	//TODO: Add your message handler code here
	_is_there_in_focus=FALSE;
	Invalidate(TRUE);
}

/**
 * name: CtlColor
 * brief: 颜色绘制反映消息响应函数，这里用来将编辑框设置为透明。
 * param: pDC - 绘图设备DC。
 *        nCtlColor - 当前绘制的控件编号。
 * return: 返回绘制控件的背景画刷。
 */
HBRUSH MtImageEdit::CtlColor(CDC *pDC,UINT /*nCtlColor*/){
	// TODO:  Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	if(IsWindowEnabled()){
		pDC->SetTextColor(RGB(_text_color_r,
			_text_color_g,_text_color_b));
	}else{
		pDC->SetTextColor(DISABLE_TEXT_COLOR);
	}
	return((HBRUSH)GetStockObject(NULL_BRUSH));
	//TODO:  Return a non-NULL brush if the parent's handler should not be called
	//return(NULL);
}

/**
 * name: OnEnChange
 * brief: 当编辑框内容改变时，调用此消息响应函数，
 *        此时用来刷新当前编辑框窗口。
 * param: --
 * return: --
 */
void MtImageEdit::OnEnChange(){
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
	Invalidate(TRUE);
}

/**
 * name: draw_background
 * brief: 绘制按钮的背景。
 * param: memory_bitmap - 内存位图。
 *		  state - 按钮当前状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageEdit::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
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