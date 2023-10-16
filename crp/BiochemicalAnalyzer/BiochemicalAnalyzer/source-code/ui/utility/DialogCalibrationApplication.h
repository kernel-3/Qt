#pragma once

//DialogCalibrationApplication dialog

#include"../../../Resource.h"
#include"../DialogPageBase.h"
#include"afxwin.h"

class MtImageEdit;
class MtImageStatic;
class MtImageComboBox;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageButton;
class MtStrictEdit;
class Database;
class CalibrationApplication;

/**
 * name: DialogCalibrationApplication
 * breif: “定标”对话框，负责提供用户定标参数
 *        设置修改的交互界面。 
 * auhtor: yameng_he
 * date: 2015-06-04
 */
class DialogCalibrationApplication
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogCalibrationApplication)
//define
public:
	enum{IDD=IDD_DIALOG_CALIBRATION_APPLICATION};
	typedef MtImageButton MtImageCheckBox;
//construction & destruction
public:
	DialogCalibrationApplication(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogCalibrationApplication();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedCheckBlank();
	afx_msg void OnBnClickedCheckSpan();
	afx_msg void OnBnClickedCheck2Point();
	afx_msg void OnBnClickedCheckFull();
	afx_msg void OnCbnSelchangeComboSelectTest();
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
	int get_data_from_controls(int &item_id,CalibrationApplication &calibration);
	int commit_data_of_controls(Database &database);
//variables
private:
	int _item_id;
	BOOL _is_command_message_masked;
	MtImageStatic *_select_test_static;
	MtImageStatic *_calibration_type_static;
	MtImageStatic *_points_static;
	MtImageStatic *_span_point_static;
	MtImageStatic *_weight_static;
	MtImageStatic *_time_out_static;
	MtImageStatic *_lot_no_static;
	MtImageStatic *_bottle_static;
	MtImageStatic *_change_over_static;
	MtImageStatic *_auto_calibration_static;
	MtImageStatic *_sd_limit_static;
	MtImageStatic *_duplicate_limit_static;
	MtImageStatic *_percent_unit_static;
	MtImageStatic *_abs_unit_static;
	MtImageStatic *_sensitivity_limit_static;
	MtImageStatic *_s1_abs_range_static;
	MtImageComboBox *_select_test_combo_box;
	MtImageComboBox *_calibration_type_combo_box;
	MtImageComboBox *_test_name_combo_box;
	MtImageComboBox *_lot_to_lot_calibration_method_combo_box;
	MtImageComboBox *_bottle_to_bottle_calibration_method_combo_box;
	MtStrictEdit *_points_edit;
	MtStrictEdit *_span_point_edit;
	MtStrictEdit *_weight_edit;
	MtStrictEdit *_time_for_blank_edit;
	MtStrictEdit *_time_for_span_edit;
	MtStrictEdit *_time_for_2_point_edit;
	MtStrictEdit *_time_for_full_edit;
	MtStrictEdit *_sd_limit_edit;
	MtStrictEdit *_percent_for_duplicate_limit_edit;
	MtStrictEdit *_abs_for_duplicate_limit_edit;
	MtStrictEdit *_sensitivity_lower_limit_edit;
	MtStrictEdit *_sensitivity_upper_limit_edit;
	MtStrictEdit *_s1_abs_lower_limit_edit;
	MtStrictEdit *_s1_abs_upper_limit_edit;
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
	MtHorizonLayout *_child_layout_13;
	MtHorizonLayout *_child_layout_14;
	MtVerticalLayout *_child_layout_15;
	MtHorizonLayout *_child_layout_16;
	MtHorizonLayout *_child_layout_17;
	MtVerticalLayout *_main_layout;
	MtImageCheckBox *_blank_check_box;
	MtImageCheckBox *_span_check_box;
	MtImageCheckBox *_2_point_check_box;
	MtImageCheckBox *_full_check_box;
	MtImageButton *_delete_button;
	MtImageButton *_ok_button;
};