#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"
#include"afxwin.h"

//DialogStandardApplication dialog

class MtImageStatic;
class MtImageComboBox;
class MtImageEdit;
class MtHorizonLayout;
class MtVerticalLayout;
class MtImageButton;
class MtStrictEdit;
class StandardApplication;
class Database;

/**
 * name: DialogStandardApplication
 * breif: “标准”对话框，负责提供用户标准参数
 *        设置修改的交互界面。
 * author: yameng_he
 * date: 2015-06-09
 */
class DialogStandardApplication
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogStandardApplication)
//define
public:
	enum{IDD=IDD_DIALOG_STANDARD_APPLICATION};
//construction & destruction
public:
	DialogStandardApplication(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogStandardApplication();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnCbnSelchangeComboSelectTest();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonOk();
	afx_msg LRESULT OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCommitDataOfControls(WPARAM wParam,LPARAM lParam);
//implement
private:
	void init_controls();
	void update_data_for_controls(const int item_id=0);
	BOOL is_data_of_controls_changed() const;
	int get_data_from_controls(int &item_id,StandardApplication &standard);
	int commit_data_of_controls(Database &database);
//variables
private:
	int _item_id;
	BOOL _is_command_message_masked;
	MtImageStatic *_select_test_static;
	MtImageStatic *_calibrator_code_static;
	MtImageStatic *_concentration_static;
	MtImageStatic *_position_static;
	MtImageStatic *_standard_static;
	MtImageStatic *_standard_1_static;
	MtImageStatic *_standard_2_static;
	MtImageStatic *_standard_3_static;
	MtImageStatic *_standard_4_static;
	MtImageStatic *_standard_5_static;
	MtImageStatic *_standard_6_static;
	MtImageStatic *_sample_volume_static;
	MtImageStatic *_diluted_sample_volume_static;
	MtImageStatic *_diluent_volume_static;
	MtImageComboBox *_select_test_combo_box;
	MtStrictEdit *_calibrator_code_1_edit;
	MtStrictEdit *_calibrator_code_2_edit;
	MtStrictEdit *_calibrator_code_3_edit;
	MtStrictEdit *_calibrator_code_4_edit;
	MtStrictEdit *_calibrator_code_5_edit;
	MtStrictEdit *_calibrator_code_6_edit;
	MtStrictEdit *_concentration_1_edit;
	MtStrictEdit *_concentration_2_edit;
	MtStrictEdit *_concentration_3_edit;
	MtStrictEdit *_concentration_4_edit;
	MtStrictEdit *_concentration_5_edit;
	MtStrictEdit *_concentration_6_edit;
	MtStrictEdit *_position_1_edit;
	MtStrictEdit *_position_2_edit;
	MtStrictEdit *_position_3_edit;
	MtStrictEdit *_position_4_edit;
	MtStrictEdit *_position_5_edit;
	MtStrictEdit *_position_6_edit;
	MtStrictEdit *_sample_volume_1_edit;
	MtStrictEdit *_sample_volume_2_edit;
	MtStrictEdit *_sample_volume_3_edit;
	MtStrictEdit *_sample_volume_4_edit;
	MtStrictEdit *_sample_volume_5_edit;
	MtStrictEdit *_sample_volume_6_edit;
	MtStrictEdit *_diluted_sample_volume_1_edit;
	MtStrictEdit *_diluted_sample_volume_2_edit;
	MtStrictEdit *_diluted_sample_volume_3_edit;
	MtStrictEdit *_diluted_sample_volume_4_edit;
	MtStrictEdit *_diluted_sample_volume_5_edit;
	MtStrictEdit *_diluted_sample_volume_6_edit;
	MtStrictEdit *_diluent_volume_1_edit;
	MtStrictEdit *_diluent_volume_2_edit;
	MtStrictEdit *_diluent_volume_3_edit;
	MtStrictEdit *_diluent_volume_4_edit;
	MtStrictEdit *_diluent_volume_5_edit;
	MtStrictEdit *_diluent_volume_6_edit;
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
	MtVerticalLayout *_main_layout;
};