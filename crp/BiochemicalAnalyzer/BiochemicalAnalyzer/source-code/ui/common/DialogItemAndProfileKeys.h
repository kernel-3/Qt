#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxwin.h"

class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;
class DialogItemAndProfileKey;

/**
 * name: DialogItemAndProfileKeys
 * brief: 项目和组合按键对话框。此对话框存在四种应用模式，如下：
 *        =============================================
 *        1 配置项目模式	用于设置项目键。
 *        2 配置组合模式  用于设置组合键。
 *        3 样本设置模式  用于样本设置。
 *        =============================================
 * author: yameng_he
 * date: 2015-03-06
 */
class DialogItemAndProfileKeys
	:public DialogBase{
	DECLARE_DYNAMIC(DialogItemAndProfileKeys)
//define
public:
	enum{IDD=IDD_DIALOG_ITEM_AND_PROFILE_KEYS,PAGES=5,};
//construction & destruction
public:
	DialogItemAndProfileKeys(const int mode,CWnd *pParent=NULL);   // standard constructor
	virtual ~DialogItemAndProfileKeys();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnButtonClicked(const unsigned int ID);
	afx_msg LRESULT OnItemOrProfileButtonClicked(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
//variables
private:
	const int _mode;
	MtImageButton *_page_buttons;
	DialogItemAndProfileKey *_page_dialogs;
	MtHorizonLayout *_child_layout_1;
	MtVerticalLayout *_main_layout;
};