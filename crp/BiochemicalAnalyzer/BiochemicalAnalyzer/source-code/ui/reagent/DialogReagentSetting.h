#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxcmn.h"
#include"afxwin.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MtComplexListCtrl;
class MtImageStatic;
class MtImageButton;

/**
 * name: DialogReagentSetting
 * brief: “试剂设置”界面，负责实现人机试剂管理的交互。
 * author: yameng_he
 * date: 2015-03-25
 */
class DialogReagentSetting
	:public DialogBase{
	DECLARE_DYNAMIC(DialogReagentSetting)
//define
public:
	enum{IDD=IDD_DIALOG_REAGENT_SETTING};
//construction & destruction
public:
	DialogReagentSetting(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogReagentSetting();
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
	MtComplexListCtrl *_reagent_disk_tests_list;
	MtComplexListCtrl *_reagent_disk_idle_position_list;
	MtImageStatic *_reagent_disk_idle_position_static;
	MtImageStatic *_manual_setting_static;
	MtImageStatic *_over_ride_manual_setting_static;
	MtImageButton *_details_button;
	MtImageButton *_manual_setting_button;
	MtImageButton *_delete_button;
	MtImageButton *_ise_reagent_remaining_volumes_button;
	MtImageButton *_barcode_button;
	MtImageButton *_level_button;
	MtImageButton *_volume_reset_button;
	MtImageButton *_item_sort_button;
	MtHorizonLayout *_child_layout_1;
	MtVerticalLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtVerticalLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtVerticalLayout *_main_layout;
};