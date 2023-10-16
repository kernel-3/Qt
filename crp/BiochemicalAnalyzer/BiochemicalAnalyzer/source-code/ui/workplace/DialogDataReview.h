#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"
#include"afxwin.h"
#include"afxcmn.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageStatic;
class MtImageButton;
class MtComplexListCtrl;

/**
 * name: DialogDataReview
 * brief: “数据浏览”页面对话框。
 * auhtor: yameng_he
 * date: 2015-03-18
 */
class DialogDataReview
	:public DialogBase{
	DECLARE_DYNAMIC(DialogDataReview)
//defnine
public:
	enum{IDD=IDD_DIALOG_DATA_REVIEW};
	typedef MtImageButton MtImageRadioBox;
//construction & destruction
public:
	DialogDataReview(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogDataReview();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedRadioAllEntries();
	afx_msg void OnBnClickedRadioSearchResults();
	afx_msg void OnBnClickedRadioCurrentData();
	afx_msg void OnBnClickedRadioHistoryData();
//implement
private:
	void init_controls();
	void draw_boder(MtBitmap &memory_bitmap);
//variables
private:
	MtImageStatic *_display_options_static;
	MtImageStatic *_data_source_static;
	MtImageStatic *_specimen_record_count_static;
	MtImageStatic *_specimen_record_count_value_static;
	MtImageRadioBox *_all_entries_radio_box;
	MtImageRadioBox *_search_results_radio_box;
	MtImageRadioBox *_current_data_radio_box;
	MtImageRadioBox *_history_data_radio_box;
	MtComplexListCtrl *_specimen_data_list;
	MtComplexListCtrl *_item_data_list;
	MtImageButton *_demographics_button;
	MtImageButton *_send_to_host_button;
	MtImageButton *_reaction_monitor_button;
	MtImageButton *_rerun_ts_button;
	MtImageButton *_update_results_button;
	MtImageButton *_refresh_button;
	MtImageButton *_search_button;
	MtImageButton *_sort_button;
	MtImageButton *_delete_record_button;
	MtImageButton *_edit_test_result_button;
	MtImageButton *_replace_result_button;
	MtImageButton *_backup_button;
	MtImageButton *_batch_delete_button;
	MtVerticalLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtVerticalLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtHorizonLayout *_child_layout_6;
	MtHorizonLayout *_child_layout_7;
	MtVerticalLayout *_main_layout;
};