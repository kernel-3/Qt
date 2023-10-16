#pragma once

#include"../DialogBase.h"
#include"../../../Resource.h"
#include"afxwin.h"

class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogWorkPlace
 * brief: “样本管理”页面对话框。
 * author: yameng_he
 * date: 2015-02-10
 */
class DialogWorkPlace
	:public DialogBase{
	DECLARE_DYNAMIC(DialogWorkPlace)
//define
public:
	enum{IDD=IDD_DIALOG_WORK_PLACE,PAGES=2,};
//construction & destruction
public:
	DialogWorkPlace(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogWorkPlace();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnButtonClicked(const unsigned int ID);
//implement
private:
	void init_controls();
//variables
private:
	MtImageButton *_page_buttons;
	DialogBase **_page_dialogs;
	MtHorizonLayout *_child_layout_1;
	MtVerticalLayout *_main_layout;
};