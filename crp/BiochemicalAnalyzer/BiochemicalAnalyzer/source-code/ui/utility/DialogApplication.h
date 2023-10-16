#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"

//DialogApplication dialog

class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogApplication
 * breif: “应用”页面对话框类，负责提供用户
 *        修改设置应用参数的交互界面。
 * author: yameng_he
 * date: 2015-06-01
 */
class DialogApplication
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogApplication)
//define
public:
	enum{IDD=IDD_DIALOG_APPLICATION,PAGES=4,};
//construction & destruction
public:
	DialogApplication(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogApplication();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPageButtonClicked(const unsigned int ID);
	afx_msg LRESULT OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
//variables
private:
	MtImageButton *_page_buttons;
	DialogPageBase **_page_dialogs;
	MtHorizonLayout *_child_layout_1;
	MtVerticalLayout *_main_layout;
};