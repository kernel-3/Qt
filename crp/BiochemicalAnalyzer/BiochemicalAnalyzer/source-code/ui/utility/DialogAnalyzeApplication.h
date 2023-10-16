#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"
#include"afxwin.h"

//DialogAnalyzeApplication dialog

class MtImageStatic;
class MtImageComboBox;
class MtImageEdit;
class MtStrictEdit;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageButton;
class Database;
class AnalyzeApplication;
class Item;
class ApplicationAnalysisData;

/**
 * name: DialogAnalyzeApplication
 * breif: “分析”对话框，负责提供用户分析参数
 *        设置修改的交互界面。
 * author: yameng_he
 * date: 2015-06-01
 */
class DialogAnalyzeApplication
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogAnalyzeApplication)
//define
public:
	enum{IDD=IDD_DIALOG_ANALYZE_APPLICATION};
	typedef MtImageButton MtImageCheckBox;
//construction & destruction
public:
	DialogAnalyzeApplication(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogAnalyzeApplication();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnCbnSelchangeComboSelectModule();
	afx_msg void OnCbnSelchangeComboSelectSpecimenType();
	afx_msg void OnCbnSelchangeComboSelectTest();
	afx_msg void OnBnClickedButtonAddApplication();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonOk();
	afx_msg LRESULT OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID(
		WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCommitDataOfControls(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
	void init_combo_boxes();
	void init_select_test_combo_box(const Item &item);
	void update_data_for_controls(const int module_id=0,
		const int specimen_type_id=0,const int item_id=0);
	BOOL is_data_of_controls_changed() const;
	int get_data_from_controls(CString &item_alias,
		ApplicationAnalysisData &data);
	int commit_data_of_controls(Database &database);
//variables
private:
	int _module_id;
	int _specimen_type_id;
	int _item_id;
	BOOL _is_command_message_masked;
	MtImageStatic *_select_module_static;
	MtImageStatic *_assay_detect_incubate_static;
	MtImageStatic *_select_specimen_type_static;
	MtImageStatic *_diluent_stability_ratio_static;
	MtImageStatic *_select_test_static;
	MtImageStatic *_test_name_static;
	MtImageStatic *_test_no_static;
	MtImageStatic *_test_id_static;
	MtImageStatic *_sample_static;
	MtImageStatic *_normal_static;
	MtImageStatic *_decrease_static;
	MtImageStatic *_increase_static;
	MtImageStatic *_reagent_static;
	MtImageStatic *_r1_static;
	MtImageStatic *_r2_static;
	MtImageStatic *_r3_static;
	MtImageStatic *_r4_static;
	MtImageStatic *_substrate_volume_static;
	MtImageStatic *_substrate_code_static;
	MtImageStatic *_substrate_stability_static;
	MtImageStatic *_substrate_1_static;
	MtImageStatic *_substrate_2_static;
	MtImageStatic *_substrate_3_static;
	MtImageStatic *_buffer_solution_volume_code_stability_static;
	MtImageComboBox *_select_module_combo_box;
	MtImageComboBox *_assay_method_combo_box;
	MtImageComboBox *_select_specimen_type_combo_box;
	MtImageComboBox *_dilution_ratio_combo_box;
	MtImageComboBox *_select_test_combo_box;
	MtStrictEdit *_detect_time_edit;
	MtStrictEdit *_incubate_time_1_edit;
	MtStrictEdit *_incubate_time_2_edit;
	MtStrictEdit *_incubate_time_3_edit;
	MtStrictEdit *_incubate_time_4_edit;
	MtStrictEdit *_diluent_code_edit;
	MtStrictEdit *_diluent_stability_edit;
	MtImageEdit *_test_name_edit;
	MtStrictEdit *_test_no_edit;
	MtStrictEdit *_test_id_edit;
	MtStrictEdit *_normal_sample_volume_edit;
	MtStrictEdit *_normal_dilution_sample_volume_edit;
	MtStrictEdit *_normal_dilution_volume_edit;
	MtStrictEdit *_decreased_sample_volume_edit;
	MtStrictEdit *_decreased_dilution_sample_volume_edit;
	MtStrictEdit *_decreased_dilution_volume_edit;
	MtStrictEdit *_increased_sample_volume_edit;
	MtStrictEdit *_increased_dilution_sample_volume_edit;
	MtStrictEdit *_increased_dilution_volume_edit;
	MtStrictEdit *_r1_reagent_volume_edit;
	MtStrictEdit *_r1_diluent_volume_edit;
	MtStrictEdit *_r1_reagent_code_edit;
	MtStrictEdit *_r1_reagent_stability_edit;
	MtStrictEdit *_r2_reagent_volume_edit;
	MtStrictEdit *_r2_diluent_volume_edit;
	MtStrictEdit *_r2_reagent_code_edit;
	MtStrictEdit *_r2_reagent_stability_edit;
	MtStrictEdit *_r3_reagent_volume_edit;
	MtStrictEdit *_r3_diluent_volume_edit;
	MtStrictEdit *_r3_reagent_code_edit;
	MtStrictEdit *_r3_reagent_stability_edit;
	MtStrictEdit *_r4_reagent_volume_edit;
	MtStrictEdit *_r4_diluent_volume_edit;
	MtStrictEdit *_r4_reagent_code_edit;
	MtStrictEdit *_r4_reagent_stability_edit;
	MtStrictEdit *_substrate_1_volume_edit;
	MtStrictEdit *_substrate_1_code_edit;
	MtStrictEdit *_substrate_1_stability_edit;
	MtStrictEdit *_substrate_2_code_edit;
	MtStrictEdit *_substrate_2_stability_edit;
	MtStrictEdit *_substrate_2_volume_edit;
	MtStrictEdit *_substrate_3_code_edit;
	MtStrictEdit *_substrate_3_volume_edit;
	MtStrictEdit *_substrate_3_stability_edit;
	MtStrictEdit *_buffer_solution_volume_edit;
	MtStrictEdit *_buffer_solution_code_edit;
	MtStrictEdit *_buffer_solution_stability_edit;
	MtImageButton *_delete_button;
	MtImageButton *_read_parameters_button;
	MtImageButton *_write_parameters_button;
	MtImageButton *_add_application_button;
	MtImageButton *_ok_button;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtHorizonLayout *_child_layout_6;
	MtVerticalLayout *_child_layout_7;
	MtHorizonLayout *_child_layout_8;
	MtHorizonLayout *_child_layout_9;
	MtHorizonLayout *_child_layout_10;
	MtHorizonLayout *_child_layout_11;
	MtVerticalLayout *_child_layout_12;
	MtHorizonLayout *_child_layout_13;
	MtHorizonLayout *_child_layout_14;
	MtHorizonLayout *_child_layout_15;
	MtHorizonLayout *_child_layout_16;
	MtHorizonLayout *_child_layout_17;
	MtHorizonLayout *_child_layout_18;
	MtVerticalLayout *_main_layout;
};