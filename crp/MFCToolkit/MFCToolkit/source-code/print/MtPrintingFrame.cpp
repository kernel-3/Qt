// source-code/print/MtPrintingFrame.cpp : implementation file
//

#include"stdafx.h"
#include"MtPrintingFrame.h"
#include"MtPrintingView.h"

//MtPrintingFrame
IMPLEMENT_DYNCREATE(MtPrintingFrame,CFrameWnd)

/**
 * name: MtPrintingFrame
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtPrintingFrame::MtPrintingFrame()
	:_main_wnd(0)
	,_view(0){
}

/**
 * name: ~MtPrintingFrame
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtPrintingFrame::~MtPrintingFrame(){
}

/**
 * name: create_window
 * brief: 创建窗口。
 * param: title - 窗口标题。
 *        window_rect - 指定窗口尺寸。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPrintingFrame::create_window(
	const CString &title,const CRect &window_rect/*=rectDefault*/){
	//1.如果创建窗口失败返回错误代码。
	if(!Create(0,title,WS_OVERLAPPEDWINDOW,window_rect)){
		return(-1);
	}
	//2.如果创建窗口成功，则直接返回。
	else{
		return(0);
	}
}

/**
 * name: OnCreateClient
 * brief: 窗口创建客户区虚拟函数，在此用来为当前窗口创建子视图。
 * param: lpcs - 指向窗口创建结构体。
 *        pContext - 指向窗口创建上下文结构体。
 * return: 如果当前函数执行成功返回值为TRUE，否则返回值为FALSE。
 */
BOOL MtPrintingFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,CCreateContext *pContext){
	// TODO: Add your specialized code here and/or call the base class
	//1.如果当前打印视图已被创建，则直接返回FALSE。
	if(0!=_view){
		return(FALSE);
	}
	//2.创建打印视图窗口，并且判断创建是否成功。
	_view=new MtPrintingView;
	if(!_view->Create(0,0,WS_CHILD|WS_VISIBLE,
		rectDefault,this,AFX_IDW_PANE_FIRST,pContext)){
		return(FALSE);
	}
	//3.如果当前视图创建成功，则重新设置当前程序的主窗口。
	_main_wnd=AfxGetApp()->m_pMainWnd;
	AfxGetApp()->m_pMainWnd=this;
	//4.程序运行到此直接返回TRUE。
	return(TRUE);
	//return(CFrameWnd::OnCreateClient(lpcs,pContext));
}

BEGIN_MESSAGE_MAP(MtPrintingFrame,CFrameWnd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/**
 * name: OnDestroy
 * brief: 窗口销毁消息响应函数，在此用来销毁子视图。
 * param: --
 * return: --
 */
void MtPrintingFrame::OnDestroy(){
	//1.对当前子视图进行销毁。
	if(0!=_view){
		_view->DestroyWindow();
	}
	//2.销毁当前窗口。
	CFrameWnd::OnDestroy();
	// TODO: Add your message handler code here
	//3.回复当前程序主窗口。
	AfxGetApp()->m_pMainWnd=_main_wnd;
	_main_wnd=0;
}