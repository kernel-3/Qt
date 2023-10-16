// source-code/ui/DialogBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogBase.h"
#include"afxdialogex.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../global/Theme.h"

// DialogBase dialog
IMPLEMENT_DYNAMIC(DialogBase,CDialogEx)

/**
 * name: DialogBase
 * brief: 构造函数。
 * param: IDD - 对话框ID。
 *		  pParent - 指向父窗口。
 * return: --
 */
DialogBase::DialogBase(
	const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:CDialogEx(IDD,pParent)
	,_window_rect(){
}

/**
 * name: ~DialogBase
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogBase::~DialogBase(){
}

/**
 * name: DoDataExchange
 * brief: DDX/DDV 支持。
 * param: pDX -
 * return: --
 */
void DialogBase::DoDataExchange(CDataExchange *pDX){
	CDialogEx::DoDataExchange(pDX);
}

/**
 * name: PreTranslateMessage
 * breif: 消息转发前调用此虚拟函数。
 *        在此负责屏蔽用户的ESC、Enter按键。
 * param: pMsg - 指向消息结构体指针。
 * return: --
 */
BOOL DialogBase::PreTranslateMessage(MSG *pMsg){
	// TODO: Add your specialized code here and/or call the base class
	///////////////////////////////////////////////////////////////////
	if(WM_KEYDOWN==pMsg->message){
		const int key=(int)pMsg->wParam;
		if(key==VK_RETURN){
			return(TRUE);
		}
		if(key==VK_ESCAPE){
			return(TRUE);
		}
	}
	///////////////////////////////////////////////////////////////////
	return(CDialogEx::PreTranslateMessage(pMsg));
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 此时绘制的内存DC。
 * return: --
 */
void DialogBase::draw(MtBitmap &memory_bitmap,CDC &/*dc*/){
	//1.绘制当前对话框背景。
	draw_background(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogBase,CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//DialogBase message handlers

/**
 * name: OnSize
 * brief: 对话框尺寸变化时，调用此消息响应函数。
 * param: nType - 尺寸变化类型。
 *        cx - 宽度。
 *        cy - 高度。
 * return: --
 */
void DialogBase::OnSize(UINT nType,int cx,int cy){
	//1.调用基类相应消息响应函数。
	CDialogEx::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_window_rect.SetRect(0,0,cx,cy);
}

/**
 * name: OnPaint
 * brief: 对话框需要绘制时，系统调用此消息相应函数。此函数用来
 *        绘制对话框。
 * param: --
 * return: --
 */
void DialogBase::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(_window_rect.Width(),_window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//2.清空内存位图数据。
	memory_bitmap->fill(0,0,0,0);
	//3.调用对话框绘制虚拟函数。
	draw(*memory_bitmap,dc);
	//4.将内存位图黏贴到对话框中。
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CDialogEx::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: 对话框背景擦除消息相应函数。
 * param: pDC - 指向当前绘图DC。
 * return: 此函数直接返回TRUE，使得绘制对话框时不再进行不必要的擦除操作。
 */
BOOL DialogBase::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return CDialogEx::OnEraseBkgnd(pDC);
}

/**
 * name: draw_background
 * breif: 绘制对话框背景。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogBase::draw_background(MtBitmap &memory_bitmap){
	//1.获取当前对话框的背景图片。
	Theme::PtrToImage image=Theme::instance()->get_image(1);
	//2.如果当前对话框背景图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap(&memory_bitmap,0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height(),0,0,image->get_width(),image->get_height());
}