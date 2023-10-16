//source-code/ui/DialogPageBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogPageBase.h"
#include"afxdialogex.h"
#include"../global/Theme.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"

//DialogPageBase dialog
IMPLEMENT_DYNAMIC(DialogPageBase,DialogBase)

/**
 * name: DialogPageBase
 * breif: 构造函数。
 * param: IDD - 对话框ID。
 *        pParent - 指向父对话框。
 * return: --
 */
DialogPageBase::DialogPageBase(
	const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:DialogBase(IDD,pParent){
}

/**
 * name: ~DialogPageBase
 * breif: 析构函数。
 * param: --
 * return: --
 */
DialogPageBase::~DialogPageBase(){
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogPageBase::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogPageBase::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogPageBase,DialogBase)
END_MESSAGE_MAP()

//DialogPageBase message handlers

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogPageBase::draw_boder(MtBitmap &memory_bitmap){
	//1.获取当前对话框的边框图片。
	Theme::PtrToImage image=Theme::instance()->get_image(24);
	//2.如果当前对话框边框图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框边框位置信息。
	const CRect rect(0,0,memory_bitmap.get_width(),BODER_SIZE);
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap(&memory_bitmap,rect.left,rect.top,
		rect.Width(),rect.Height(),0,0,image->get_width(),
		image->get_height());
}