#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"
#include"afxwin.h"

//DialogRangeApplication dialog

class MtImageStatic;
class MtImageComboBox;
class MtImageEdit;
class MtImageComboBox;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageButton;
class Database;
class MtStrictEdit;
class RangeApplication;

/**
 * name: DialogAnalyzeApplication
 * breif: “范围”对话框，负责提供用户范围参数
 *        设置修改的交互界面。
 * author: yameng_he
 * date: 2015-06-05
 */
class DialogRangeApplication
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogRangeApplication)
//define
public:
	enum{IDD=IDD_DIALOG_RANGE_APPLICATION};
	typedef MtImageButton MtImageCheckBox;
//construction & destruction
public:
	DialogRangeApplication(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogRangeApplication();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedCheckControlInterval();
	afx_msg void OnBnClickedCheckUseQualitativeTable();
	afx_msg void OnCbnSelchangeComboSelectTest();
	afx_msg void OnCbnSelchangeComboSelectSampleType();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonOk();
	afx_msg LRESULT OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCommitDataOfControls(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
	void init_combo_boxes(Database &database);
	void update_data_for_controls(const int item_id=0);
	BOOL is_data_of_controls_changed() const;
	int get_data_from_controls(int &item_id,
		CString &item_alias,RangeApplication &range);
	int commit_data_of_controls(Database &database);
//variables
private:
	int _item_id;
	int _sample_type_id;
	BOOL _is_command_message_masked;
	MtImageStatic *_select_test_static;
	MtImageStatic *_report_name_static;
	MtImageStatic *_item_name_static;
	MtImageStatic *_unit_static;
	MtImageStatic *_item_no_static;
	MtImageStatic *_data_mode_static;
	MtImageStatic *_test_id_static;
	MtImageStatic *_instrument_factor_static;
	MtImageStatic *_select_sample_type_static;
	MtImageStatic *_age_static;
	MtImageStatic *_male_static;
	MtImageStatic *_female_static;
	MtImageStatic *_default_age_static;
	MtImageStatic *_default_sex_static;
	MtImageStatic *_repeat_range_static;
	MtImageStatic *_qualitative_limit_1_static;
	MtImageStatic *_qualitative_limit_2_static;
	MtImageStatic *_qualitative_limit_3_static;
	MtImageStatic *_qualitative_limit_4_static;
	MtImageStatic *_qualitative_limit_5_static;
	MtImageStatic *_qualitative_limit_6_static;
	MtImageStatic *_expected_ranges_static;
	MtImageStatic *_range_static;
	MtImageStatic *_class_1_technical_range_static;
	MtImageStatic *_class_2_technical_range_static;
	MtImageComboBox *_select_test_combo_box;
	MtImageComboBox *_unit_combo_box;
	MtImageComboBox *_data_mode_combo_box;
	MtImageComboBox *_select_sample_type_combo_box;
	MtImageComboBox *_lower_age_unit_combo_box;
	MtImageComboBox *_upper_age_unit_combo_box;
	MtImageComboBox *_default_age_combo_box;
	MtImageComboBox *_default_sex_combo_box;
	MtImageEdit *_report_name_edit;
	MtImageEdit *_item_name_edit;
	MtStrictEdit *_control_interval_edit;
	MtStrictEdit *_item_no_edit;
	MtStrictEdit *_test_id_edit;
	MtStrictEdit *_instrument_factor_a_edit;
	MtStrictEdit *_instrument_factor_b_edit;
	MtStrictEdit *_lower_age_edit;
	MtStrictEdit *_1_lower_limit_for_male_edit;
	MtStrictEdit *_1_upper_limit_for_male_edit;
	MtStrictEdit *_1_lower_limit_for_female_edit;
	MtStrictEdit *_1_upper_limit_for_female_edit;
	MtStrictEdit *_upper_age_edit;
	MtStrictEdit *_2_lower_limit_for_male_edit;
	MtStrictEdit *_2_upper_limit_for_male_edit;
	MtStrictEdit *_2_lower_limit_for_female_edit;
	MtStrictEdit *_2_upper_limit_for_female_edit;
	MtStrictEdit *_3_lower_limit_for_male_edit;
	MtStrictEdit *_3_upper_limit_for_male_edit;
	MtStrictEdit *_3_lower_limit_for_female_edit;
	MtStrictEdit *_3_upper_limit_for_female_edit;
	MtStrictEdit *_lower_repeat_range_limit_edit;
	MtStrictEdit *_upper_repeat_range_limit_edit;
	MtStrictEdit *_qualitative_limit_1_edit;
	MtStrictEdit *_qualitative_limit_2_edit;
	MtStrictEdit *_qualitative_limit_3_edit;
	MtStrictEdit *_qualitative_limit_4_edit;
	MtStrictEdit *_qualitative_limit_5_edit;
	MtImageEdit *_qualitative_limit_text_1_edit;
	MtImageEdit *_qualitative_limit_text_2_edit;
	MtImageEdit *_qualitative_limit_text_3_edit;
	MtImageEdit *_qualitative_limit_text_4_edit;
	MtImageEdit *_qualitative_limit_text_5_edit;
	MtImageEdit *_qualitative_limit_text_6_edit;
	MtStrictEdit *_technical_range_lower_limit_for_class_1_edit;
	MtStrictEdit *_technical_range_upper_limit_for_class_1_edit;
	MtStrictEdit *_technical_range_lower_limit_for_class_2_edit;
	MtStrictEdit *_technical_range_upper_limit_for_class_2_edit;
	MtImageCheckBox *_control_interval_check_box;
	MtImageCheckBox *_use_qualitative_table_check_box;
	MtImageButton *_delete_button;
	MtImageButton *_ok_button;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtHorizonLayout *_child_layout_6;
	MtHorizonLayout *_child_layout_7;
	MtHorizonLayout *_child_layout_8;
	MtHorizonLayout *_child_layout_9;
	MtVerticalLayout *_child_layout_10;
	MtHorizonLayout *_child_layout_11;
	MtHorizonLayout *_child_layout_12;
	MtVerticalLayout *_child_layout_13;
	MtHorizonLayout *_child_layout_14;
	MtHorizonLayout *_child_layout_15;
	MtHorizonLayout *_child_layout_16;
	MtHorizonLayout *_child_layout_17;
	MtHorizonLayout *_child_layout_18;
	MtHorizonLayout *_child_layout_19;
	MtVerticalLayout *_child_layout_20;
	MtHorizonLayout *_child_layout_21;
	MtVerticalLayout *_child_layout_22;
	MtHorizonLayout *_child_layout_23;
	MtHorizonLayout *_child_layout_24;
	MtHorizonLayout *_child_layout_25;
	MtVerticalLayout *_main_layout;
};