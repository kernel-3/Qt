// source-code/print/MtPrintingView.cpp : implementation file
//

#include"stdafx.h"
#include"MtPrintingView.h"

//MtPrintingView
IMPLEMENT_DYNCREATE(MtPrintingView,CScrollView)

/**
 * name: MtPrintingView
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtPrintingView::MtPrintingView(){
}

/**
 * name: ~MtPrintingView
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtPrintingView::~MtPrintingView(){
}

/**
 * name: OnInitialUpdate
 * biref: 视图初始化虚拟函数，负责实现对视图
 *        的初始化操作。
 * param: --
 * return: --
 */
void MtPrintingView::OnInitialUpdate(){
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx=sizeTotal.cy=100;
	SetScrollSizes(MM_TEXT,sizeTotal);
}

/**
 * name: OnDraw
 * brief: 视图绘制虚拟函数，负责对视图进行绘制。
 * param: --
 * return: --
 */
void MtPrintingView::OnDraw(CDC * /*pDC*/){
	//CDocument *pDoc=GetDocument();
	// TODO: add draw code here
}

/**
 * name: OnPreparePrinting
 * brief: 准备打印虚拟函数，进行打印的准备工作。
 * param: pInfo - 指向打印信息结构体。
 * return: 如果函数执行成功返回TRUE，否则返回FALSE。
 */
BOOL MtPrintingView::OnPreparePrinting(CPrintInfo *pInfo){
	// TODO:  call DoPreparePrinting to invoke the Print dialog box
	//1.如果准备打印失败。
	if(!DoPreparePrinting(pInfo)){
		GetParent()->DestroyWindow();
		return(FALSE);
	}
	//2.如果准备打印成功。
	else{
		return(TRUE);
	}
	//return(CScrollView::OnPreparePrinting(pInfo));
}

/**
 * name: OnBeginPrinting
 * brief: 开始打印虚拟函数。
 * param: pDC - 指向打印设备DC。
 *        pInfo - 指向打印信息结构体。
 * return: --
 */
void MtPrintingView::OnBeginPrinting(CDC *pDC,CPrintInfo *pInfo){
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnBeginPrinting(pDC,pInfo);
}

/**
 * name: OnPrint
 * brief: 打印虚拟函数，负责实现打印绘制。
 * param: pDC - 指向打印设备DC。
 *        pInfo - 指向打印信息结构体。
 * return: --
 */
void MtPrintingView::OnPrint(CDC *pDC,CPrintInfo *pInfo){
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnPrint(pDC,pInfo);
}

// MtPrintingView diagnostics
#ifdef _DEBUG
void MtPrintingView::AssertValid() const{
	CScrollView::AssertValid();
}
#ifndef _WIN32_WCE
void MtPrintingView::Dump(CDumpContext& dc) const{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

BEGIN_MESSAGE_MAP(MtPrintingView,CScrollView)
END_MESSAGE_MAP()

// MtPrintingView message handlers
