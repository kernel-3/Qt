//source-code/ui/DialogModalBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogModalBase.h"
#include"afxdialogex.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../global/Theme.h"

//DialogModalBase dialog

IMPLEMENT_DYNAMIC(DialogModalBase,DialogBase)

/**
 * name: DialogModalBase
 * breif: 构造函数。
 * param: IDD - 当前对话框ID。
 *        pParent - 指向父对话框。
 * return: --
 */
DialogModalBase::DialogModalBase(const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:DialogBase(IDD,pParent){
}

/**
 * name: ~DialogModalBase
 * breif: 析构函数。
 * param: --
 * return: --
 */
DialogModalBase::~DialogModalBase(){
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV。
 * param: pDX -
 * return: --
 */
void DialogModalBase::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogModalBase::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框标题、边框。
	draw_title_and_border(memory_bitmap);
	//3.绘制对话框标题文本。
	draw_title_text(memory_bitmap,dc);
}

BEGIN_MESSAGE_MAP(DialogModalBase,DialogBase)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

//DialogModalBase message handlers

/**
 * name: OnNcHitTest
 * brief: 对话框边框点击消息响应函数，再次用来实现
 *        对话框标题栏鼠标点击拖拽功能。
 * param: point - 鼠标位置信息。
 * return: ...
 */
LRESULT DialogModalBase::OnNcHitTest(CPoint point){
	// TODO: Add your message handler code here and/or call default
	/////////////////////////////////////////////////////////////////
	//1.计算当前对话框标题栏范围。
	CRect title_range;
	GetClientRect(title_range);
	title_range.bottom=TITLE_SIZE;
	ClientToScreen(title_range);
	//2.如果当前鼠标点击到标题栏范围内。
	if(title_range.PtInRect(point)){
		return(HTCAPTION);
	}
	////////////////////////////////////////////////////////////////
	return(DialogBase::OnNcHitTest(point));
}

/**
 * name: draw_title_and_border
 * breif: 绘制对话框的标题以及边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogModalBase::draw_title_and_border(MtBitmap &memory_bitmap){
	//1.获取当前对话框的标题、边框图片。
	Theme::PtrToImage image=Theme::instance()->get_image(37);
	//2.如果当前对话框标题、边框图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height(),0,0,image->get_width(),image->get_height(),
		BORDER_SIZE,TITLE_SIZE,BORDER_SIZE,BORDER_SIZE);
}

/**
 * name: draw_title_text
 * brief: 绘制当前对话框的标题文本。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogModalBase::draw_title_text(MtBitmap &memory_bitmap,CDC &dc){
	//1.获取当前对话框标题。
	CString title(_T(""));
	GetWindowText(title);
	//2.如果当前对话框标题为空。
	if(_T("")==title){
		return;
	}
	//3.绘制当前对话框标题。
	memory_bitmap.draw_text(title,dc.GetSafeHdc(),
		static_cast<HFONT>(GetFont()->GetSafeHandle()),BORDER_SIZE,
		0,(memory_bitmap.get_width()-(2*BORDER_SIZE)),TITLE_SIZE,
		255,255,255,255,MtBitmap::ALIGNMENT_NEAR,MtBitmap::ALIGNMENT_CENTER);
}