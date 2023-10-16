#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MarkButton;

/**
 * name: DialogItemAndProfileKeys
 * brief: 项目和组合按键对话框。此对话框存在四种应用模式，如下：
 * ====================================================
 *        1   配置项目模式    用于设置项目键。
 *        2   配置组合模式    用于设置组合键。
 *        3   样本设置模式    用于样本设置。
 * ====================================================
 * author: yameng_he
 * date: 2015-03-07
 */
class DialogItemAndProfileKey
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogItemAndProfileKey)
//define
public:
	enum{IDD=IDD_DIALOG_ITEM_AND_PROFILE_KEY,BUTTONS=80,
		ITEM_BUTTONS=40,PROFILE_BUTTONS=20,};
//construction & destruction
public:
	DialogItemAndProfileKey(CWnd *pParent=NULL);// standard constructor
	virtual ~DialogItemAndProfileKey();
//interface
public:
	void set_mode(const int mode);
	void set_page_no(const int page_no);
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);// DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnButtonClicked(const unsigned int ID);
	afx_msg LRESULT OnUpdateDataForControls(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnItemOrProfileButtonClicked(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
	void init_controls_in_mode_1();
	void update_data_for_controls();
	void update_data_for_controls_in_mode_1();
	void button_clicked_in_mode_1(const unsigned int ID);
	LRESULT item_or_profile_button_clicked_in_mode_1(
		const int button_type,const int button_no);
	int get_item_button_no(const unsigned int index) const;
//variables
private:
	int _mode;
	int _page_no;
	MarkButton *_mark_buttons;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtVerticalLayout *_main_layout;
};