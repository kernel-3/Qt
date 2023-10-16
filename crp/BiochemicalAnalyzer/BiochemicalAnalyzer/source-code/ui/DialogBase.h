#pragma once

#include<memory>

class MtBitmap;

//DialogBase dialog
/**
 * name: DialogBase
 * breif: 基础定制对话框，为定制对话框提供最一般的定制操作，它是
 *        所有定制对话框的基类。
 * author: yameng_he
 * date: 2014-12-04
 */
class DialogBase
	:public CDialogEx{
	DECLARE_DYNAMIC(DialogBase)
//define
public:
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
//constructor & destructor
public:
	DialogBase(const unsigned int IDD,CWnd *pParent=NULL);//standard constructor
	virtual ~DialogBase()=0;
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
//implement
private:
	void draw_background(MtBitmap &memory_bitmap);
//variables
private:
	CRect _window_rect;
};