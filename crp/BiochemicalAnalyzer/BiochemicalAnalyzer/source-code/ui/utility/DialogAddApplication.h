#pragma once

#include"../../../Resource.h"
#include"../DialogModalBase.h"
#include"afxwin.h"

//DialogAddApplication dialog

class MtImageEdit;
class MtStrictEdit;
class MtImageStatic;
class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;
class DialogItemAndProfileKeys;

/**
 * name: DialogAddApplication
 * breif: 添加项目对话框类，负责为用户提供添加项目的
 *        人机交互功能。
 * author: yameng_he 
 * date: 2015-06-15
 */
class DialogAddApplication
	:public DialogModalBase{
	DECLARE_DYNAMIC(DialogAddApplication)
//define
public:
	enum{IDD=IDD_DIALOG_ADD_APPLICATION};
//construction & destruction
public:
	DialogAddApplication(CWnd* pParent=NULL);//standard constructor
	virtual ~DialogAddApplication();
//interface
public:
	int get_module_id() const;
	int get_specimen_type_id() const;
	int get_item_id() const;
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnItemOrProfileButtonClicked(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
//implement
private:
	void init_window();
	void init_controls();
//variables
private:
	int _module_id;
	int _specimen_type_id;
	int _item_id;
	MtImageStatic *_no_static;
	MtImageStatic *_test_name_static;
	MtImageStatic *_app_code_static;
	MtStrictEdit *_no_edit;
	MtImageEdit *_test_name_edit;
	MtStrictEdit *_app_code_edit;
	DialogItemAndProfileKeys *_child_dialog;
	MtImageButton *_ok_button;
	MtImageButton *_cancel_button;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtVerticalLayout *_main_layout;
};