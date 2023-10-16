// source-code/ui/control/MarkButton.cpp : implementation file
//
#include"stdafx.h"
#include"MarkButton.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"

IMPLEMENT_DYNAMIC(MarkButton,MtImageButton)

/**
 * name: MarkButton
 * brief: 构造函数。
 * param: --
 * return: --
 */
MarkButton::MarkButton()
	:MtImageButton(TYPE_BUTTON)
	,_mark_text(_T(""))
	,_mark_text_font()
	,_mark_text_alignment(0)
	,_mark_text_color_a(255)
	,_mark_text_color_r(0)
	,_mark_text_color_g(0)
	,_mark_text_color_b(0){
}

/**
 * name: ~MarkButton
 * brief: 
 * param:
 * return:
 */
MarkButton::~MarkButton(){
	if(0!=_mark_text_font.GetSafeHandle()){
		_mark_text_font.DeleteObject();
	}
}

/**
 * name: set_mark_text
 * brief: 设置当前按钮标记文本。
 * param: mark_text - 标记文本。
 * return: --
 */
void MarkButton::set_mark_text(const CString &mark_text){
	_mark_text=mark_text;
}

/**
 * name: set_mark_text_alignment
 * brief: 设置标记文本停靠方式。
 * param: mark_text_alignment - 标记文本停靠方式。
 * return: --
 */
void MarkButton::set_mark_text_alignment(const unsigned int mark_text_alignment){
	_mark_text_alignment=mark_text_alignment;
}

/**
 * name: set_mark_text_color
 * brief: 设置当前标记文本颜色。
 * param: color_a - 文本颜色a分量。
 *        color_r - 文本颜色r分量。
 *        color_g - 文本颜色g分量。
 *        color_b - 文本颜色b分量。
 * return: --
 */
void MarkButton::set_mark_text_color(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_mark_text_color_a=color_a;
	_mark_text_color_r=color_r;
	_mark_text_color_g=color_g;
	_mark_text_color_b=color_b;
}

/**
 * name: PreSubclassWindow
 * brief: 子类化按钮前调用此虚拟函数，在此用来创建
 *        按钮标记文本绘制字体。
 * param: --
 * return: --
 */
void MarkButton::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////
	//1.获取当前按钮字体内容。
	LOGFONT log_font;
	GetFont()->GetLogFont(&log_font);
	//2.缩小当前按钮字体。
	if(abs(log_font.lfHeight)>3){
		if(log_font.lfHeight<0){
			log_font.lfHeight+=3;
		}else{
			log_font.lfHeight-=3;
		}
	}
	log_font.lfWeight=FW_DONTCARE;
	//3.创建当前按钮标记文本字体。
	_mark_text_font.CreateFontIndirect(&log_font);
	//////////////////////////////////////////////////////////////////
	MtImageButton::PreSubclassWindow();
}

/**
 * name: draw_item
 * breif: 按钮绘制虚拟函数，负责实现按钮绘制。
 * param: memory_bitmap - 当前按钮内存位图。
 *        dc - 当前按钮绘制DC。
 *        state - 当前按钮状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MarkButton::draw_item(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.调用基类相应虚拟函数。
	MtImageButton::draw_item(memory_bitmap,dc,state);
	//2.绘制当前按钮标记文本。
	draw_mark_text(memory_bitmap,dc,state);
	//3.程序运行到此成功返回。
	return(0);
}

BEGIN_MESSAGE_MAP(MarkButton,MtImageButton)
END_MESSAGE_MAP()

//MarkButton message handlers

/**
 * name: draw_mark_text
 * brief: 绘制当前按钮标记文本。
 * param: memory_bitmap - 当前按钮内存位图。
 *        dc - 当前按钮绘制DC。
 *        state - 当前按钮状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MarkButton::draw_mark_text(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.如果当前按钮标记文本不存在，则直接返回。
	if(_T("")==_mark_text){
		return(0);
	}
	//2.计算当前标记文本绘制范围。
	CRect text_range(0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height());
	text_range.InflateRect(-MARK_TEXT_MARGIN,-MARK_TEXT_MARGIN,
		-MARK_TEXT_MARGIN,-MARK_TEXT_MARGIN);
	if(2==state){
		text_range.InflateRect(-1,-1,1,1);
	}
	//3.计算当前标记文本的停靠方式。
	MtBitmap::Alignment horizontal_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_mark_text_alignment&ALIGNMENT_HCENTER){
		horizontal_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_mark_text_alignment&ALIGNMENT_RIGHT){
		horizontal_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment vertical_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_mark_text_alignment&ALIGNMENT_VCENTER){
		vertical_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_mark_text_alignment&ALIGNMENT_BOTTOM){
		vertical_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//4.根据当前按钮状态绘制文本。
	//4-1.如果当前按钮处于失效状态。
	if(3==state){
		if(memory_bitmap.draw_text(_mark_text,dc,static_cast<HFONT>(
			_mark_text_font.GetSafeHandle()),text_range.left,text_range.top,
			text_range.Width(),text_range.Height(),DISABLE_TEXT_COLOR_A,
			DISABLE_TEXT_COLOR_R,DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B,
			horizontal_alignment,vertical_alignment)<0){
			return(-1);
		}
	}
	//4-2.如果当前按钮处于其它状态。
	else{
		if(memory_bitmap.draw_text(_mark_text,dc,static_cast<HFONT>(
			_mark_text_font.GetSafeHandle()),text_range.left,text_range.top,
			text_range.Width(),text_range.Height(),_mark_text_color_a,
			_mark_text_color_r,_mark_text_color_g,_mark_text_color_b,
			horizontal_alignment,vertical_alignment)<0){
			return(-2);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}