// source-code/print/MtPrintingFrame.cpp : implementation file
//

#include"stdafx.h"
#include"MtPrintingFrame.h"
#include"MtPrintingView.h"

//MtPrintingFrame
IMPLEMENT_DYNCREATE(MtPrintingFrame,CFrameWnd)

/**
 * name: MtPrintingFrame
 * brief: ���캯����
 * param: --
 * return: --
 */
MtPrintingFrame::MtPrintingFrame()
	:_main_wnd(0)
	,_view(0){
}

/**
 * name: ~MtPrintingFrame
 * brief: ����������
 * param: --
 * return: --
 */
MtPrintingFrame::~MtPrintingFrame(){
}

/**
 * name: create_window
 * brief: �������ڡ�
 * param: title - ���ڱ��⡣
 *        window_rect - ָ�����ڳߴ硣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPrintingFrame::create_window(
	const CString &title,const CRect &window_rect/*=rectDefault*/){
	//1.�����������ʧ�ܷ��ش�����롣
	if(!Create(0,title,WS_OVERLAPPEDWINDOW,window_rect)){
		return(-1);
	}
	//2.����������ڳɹ�����ֱ�ӷ��ء�
	else{
		return(0);
	}
}

/**
 * name: OnCreateClient
 * brief: ���ڴ����ͻ������⺯�����ڴ�����Ϊ��ǰ���ڴ�������ͼ��
 * param: lpcs - ָ�򴰿ڴ����ṹ�塣
 *        pContext - ָ�򴰿ڴ��������Ľṹ�塣
 * return: �����ǰ����ִ�гɹ�����ֵΪTRUE�����򷵻�ֵΪFALSE��
 */
BOOL MtPrintingFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,CCreateContext *pContext){
	// TODO: Add your specialized code here and/or call the base class
	//1.�����ǰ��ӡ��ͼ�ѱ���������ֱ�ӷ���FALSE��
	if(0!=_view){
		return(FALSE);
	}
	//2.������ӡ��ͼ���ڣ������жϴ����Ƿ�ɹ���
	_view=new MtPrintingView;
	if(!_view->Create(0,0,WS_CHILD|WS_VISIBLE,
		rectDefault,this,AFX_IDW_PANE_FIRST,pContext)){
		return(FALSE);
	}
	//3.�����ǰ��ͼ�����ɹ������������õ�ǰ����������ڡ�
	_main_wnd=AfxGetApp()->m_pMainWnd;
	AfxGetApp()->m_pMainWnd=this;
	//4.�������е���ֱ�ӷ���TRUE��
	return(TRUE);
	//return(CFrameWnd::OnCreateClient(lpcs,pContext));
}

BEGIN_MESSAGE_MAP(MtPrintingFrame,CFrameWnd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/**
 * name: OnDestroy
 * brief: ����������Ϣ��Ӧ�������ڴ�������������ͼ��
 * param: --
 * return: --
 */
void MtPrintingFrame::OnDestroy(){
	//1.�Ե�ǰ����ͼ�������١�
	if(0!=_view){
		_view->DestroyWindow();
	}
	//2.���ٵ�ǰ���ڡ�
	CFrameWnd::OnDestroy();
	// TODO: Add your message handler code here
	//3.�ظ���ǰ���������ڡ�
	AfxGetApp()->m_pMainWnd=_main_wnd;
	_main_wnd=0;
}