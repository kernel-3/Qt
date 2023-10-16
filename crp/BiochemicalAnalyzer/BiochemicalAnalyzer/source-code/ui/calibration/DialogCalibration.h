#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxwin.h"

class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogReagent
 * breif: “定标”对话框，负责显示定标相关界面。
 * author: yameng_he
 * date: 2015-03-25
 */
class DialogCalibration
	:public DialogBase{
	DECLARE_DYNAMIC(DialogCalibration)
//define
public:
	enum{IDD=IDD_DIALOG_CALIBRATION,PAGES=3};
//construction & destruction
public:
	DialogCalibration(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogCalibration();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPageButtonClicked(const unsigned int ID);
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