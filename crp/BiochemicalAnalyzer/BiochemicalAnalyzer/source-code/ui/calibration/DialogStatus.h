#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include "afxwin.h"
#include "afxcmn.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageButton;
class MtImageStatic;
class MtComplexListCtrl;

/**
 * name: DialogStatus
 * breif: “定标信息”对话框，负责显示定标信息相关界面。
 * author: yameng_he
 * date: 2015-03-27
 */
class DialogStatus
	:public DialogBase{
	DECLARE_DYNAMIC(DialogStatus)
//define
public:
	enum{IDD=IDD_DIALOG_STATUS};
	typedef MtImageButton MtImageRadioBox;
//construction & destruction
public:
	DialogStatus(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogStatus();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedRadioStartUpCalibration();
	afx_msg void OnBnClickedRadioRepeatCalibration();
//implement
private:
	void init_controls();
	void draw_boder(MtBitmap &memory_bitmap);
//variables
private:
	MtImageRadioBox *_start_up_calibration_radio_box;
	MtImageRadioBox *_repeat_calibration_radio_box;
	MtImageStatic *_calibration_mode_static;
	MtComplexListCtrl *_calibrations_list;
	MtImageButton *_calibration_trace_button;
	MtImageButton *_calibration_information_button;
	MtImageButton *_reaction_monitor_button;
	MtImageButton *_select_calibration_button;
	MtImageButton *_time_out_scheduled_button;
	MtImageButton *_calibrate_now_button;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtVerticalLayout *_main_layout;
};