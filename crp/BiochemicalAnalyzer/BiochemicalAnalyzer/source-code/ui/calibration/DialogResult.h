#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxcmn.h"
#include "afxwin.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MtComplexListCtrl;
class MtImageButton;

/**
 * name: DialogResult
 * breif: “定标结果”对话框，负责显示定标结果相关界面。
 * author: yameng_he
 * date: 2015-03-27
 */
class DialogResult
	:public DialogBase{
	DECLARE_DYNAMIC(DialogResult)
//define
public:
	enum{IDD=IDD_DIALOG_RESULT};
//construction & destruction
public:
	DialogResult(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogResult();
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
	MtComplexListCtrl *_calibration_results_list;
	MtImageButton *_calibration_trace_button;
	MtImageButton *_calibration_information_button;
	MtImageButton *_reaction_monitor_button;
	MtHorizonLayout *_child_layout_1;
	MtVerticalLayout *_main_layout;
};