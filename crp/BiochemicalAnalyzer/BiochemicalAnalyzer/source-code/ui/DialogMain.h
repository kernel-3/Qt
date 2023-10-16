//DialogMain.h : header file
//
#pragma once

#include"DialogBase.h"
#include"afxwin.h"

class MtVerticalLayout;
class MtHorizonLayout;
class MtImageStatic;
class MtImageButton;
class DialogWorkPlace;

// DialogMain dialog
/**
 * name: DialogMain
 * brief: 主对话框类，负责为用户提供人机交互主界面。
 * author: yameng_he
 * date: 2014-12-04
 */
class DialogMain
	:public DialogBase{
//define
public:
	enum{IDD=IDD_DIALOG_MAIN,MINIMUM_DIALOG_WIDTH=1080,
		MINIMUM_DIALOG_HEIGHT=768,PAGES=5,};
//construction & destruction
public:
	DialogMain(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogMain();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID,LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnSizing(UINT fwSide,LPRECT pRect);
	afx_msg void OnPageButtonClicked(const unsigned int ID);
//variables
protected:
	HICON m_hIcon;
//implement
private:
	void init_window();
	void init_controls();
	void draw_title_bar(MtBitmap &memory_bitmap);
	void draw_status_bar(MtBitmap &memory_bitmap);
	void draw_tool_bar(MtBitmap &memory_bitmap);
	void draw_main_function_bar(MtBitmap &memory_bitmap);
	void draw_main_function_region(MtBitmap &memory_bitmap);
	void draw_information_bar(MtBitmap &memory_bitmap);
//variables
private:
	MtImageStatic *_title_bar_static;
	MtImageStatic *_status_led_static;
	MtImageStatic *_status_bar_static;
	MtImageStatic *_main_function_bar_static;
	MtImageStatic *_information_bar_static;
	MtImageButton *_page_buttons;
	MtImageButton *_start_button;
	MtImageButton *_emergency_button;
	MtImageButton *_pause_button;
	MtImageButton *_stop_button;
	MtImageButton *_alarm_button;
	MtImageButton *_monitor_button;
	MtImageButton *_print_button;
	MtImageButton *_exit_button;
	DialogBase **_page_dialogs;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtVerticalLayout *_child_layout_3;
	MtVerticalLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtVerticalLayout *_main_layout;
};