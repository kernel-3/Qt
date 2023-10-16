#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxcmn.h"
#include"afxwin.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MtComplexListCtrl;
class MtImageButton;

/**
 * name: DialogStatus
 * breif: “定标液”对话框，负责显示定标信息相关界面。
 * author: yameng_he
 * date: 2015-03-27
 */
class DialogInstallation
	:public DialogBase{
	DECLARE_DYNAMIC(DialogInstallation)
//define
public:
	enum{IDD=IDD_DIALOG_INSTALLATION};
//construction & destruction
public:
	DialogInstallation(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogInstallation();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
//implement
private:
	void init_controls();
	void draw_boder(MtBitmap &memory_bitmap);
//variables
private:
	MtComplexListCtrl *_calibrators_list;
	MtComplexListCtrl *_concentrations_list;
	MtImageButton *_edit_calibrator_button;
	MtImageButton *_edit_concentrations_button;
	MtImageButton *_delete_button;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtVerticalLayout *_main_layout;
};