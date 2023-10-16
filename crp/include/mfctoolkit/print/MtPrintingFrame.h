#pragma once

#include"../Symbol"

class MtPrintingView;

/**
 * name: MtPrintingFrame
 * brief: “打印”框架类，为实现打印功能虚拟出
 *        MFC打印时所需的主框架类。
 * author: yameng_he
 * date: 2014-07-17
 */
class MFC_TOOLKIT_API MtPrintingFrame
	:public CFrameWnd{
	DECLARE_DYNCREATE(MtPrintingFrame)
//constructor & destructor
public:
	MtPrintingFrame(); //protected constructor used by dynamic creation
	virtual ~MtPrintingFrame();
//interface
public:
	int create_window(const CString &title,const CRect &window_rect=rectDefault);
//overrides
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext *pContext);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
//variables
private:
	CWnd *_main_wnd;
	MtPrintingView *_view;
};