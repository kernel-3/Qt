#pragma once

#include"DialogBase.h"

//DialogModalBase dialog

/**
 * name: DialogModalBase
 * breif: 模式对话框基类，为所有的模式对话框提供
 *        基础操作。
 * author: yameng_he
 * date: 2015-06-15
 */
class DialogModalBase
	:public DialogBase{
	DECLARE_DYNAMIC(DialogModalBase)
//define
public:
	enum{TITLE_SIZE=37,BORDER_SIZE=10,};
//construction & destruction
public:
	DialogModalBase(const unsigned int IDD,CWnd*pParent=NULL);//standard constructor
	virtual ~DialogModalBase();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNcHitTest(CPoint point);
//implement
private:
	void draw_title_and_border(MtBitmap &memory_bitmap);
	void draw_title_text(MtBitmap &memory_bitmap,CDC &dc);
};