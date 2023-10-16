#pragma once

#include"../DialogBase.h"
#include"../../../Resource.h"
#include"afxwin.h"

class MtImageStatic;
class MtImageEdit;
class MtImageComboBox;
class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogSpecimenInformation
 * brief: 样本信息对话框，负责在样本保存时提供样本
 *        信息的显示设置功能。
 * author: yameng_he
 * date: 2014-03-02
 */
class DialogSpecimenInformation
	:public DialogBase{
	DECLARE_DYNAMIC(DialogSpecimenInformation)
//define
public:
	enum{IDD=IDD_DIALOG_SPECIMEN_INFORMATION};
	typedef MtImageButton MtImageCheckBox;
	typedef enum{
		MODE_SEQUENCE_ROUTINE,
		MODE_SEQUENCE_EMERGENCY,
		MODE_BARCODE_ROUTINE,
		MODE_BARCODE_EMERGENCY,
		MODE_QC,}Mode;
//construction & destruction
public:
	DialogSpecimenInformation(const Mode mode=
		MODE_SEQUENCE_ROUTINE,CWnd *pParent=NULL);//standard constructor
	virtual ~DialogSpecimenInformation();
//interface
public:
	void set_mode(const Mode mode);
	Mode get_mode() const;
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedCheckUnreadableSpecimenId();
//implement
private:
	void init_controls();
	int load_data_from_database_to_specimen_type_combo_box();
	int load_data_from_database_to_specimen_cup_combo_box();
	int load_data_from_database_to_specimen_volume_combo_box();
//variables
private:
	Mode _mode;
	MtImageStatic *_sequence_no_static;
	MtImageStatic *_disk_no_static;
	MtImageStatic *_position_static;
	MtImageStatic *_specimen_id_static;
	MtImageStatic *_specimen_type_static;
	MtImageStatic *_specimen_cup_static;
	MtImageStatic *_specimen_volume_static;
	MtImageStatic *_control_name_static;
	MtImageStatic *_control_lot_no_static;
	MtImageStatic *_control_type_static;
	MtImageStatic *_control_position_static;
	MtImageEdit *_sequence_no_edit;
	MtImageEdit *_disk_no_edit;
	MtImageEdit *_position_edit;
	MtImageEdit *_specimen_id_edit;
	MtImageEdit *_control_lot_no_edit;
	MtImageEdit *_control_type_edit;
	MtImageEdit *_control_position_edit;
	MtImageComboBox *_specimen_type_combo_box;
	MtImageComboBox *_specimen_cup_combo_box;
	MtImageComboBox *_specimen_volume_combo_box;
	MtImageComboBox *_control_name_combo_box;
	MtImageCheckBox *_unreadable_specimen_id_check_box;
	MtHorizonLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtVerticalLayout *_child_layout_4;
	MtHorizonLayout *_child_layout_5;
	MtHorizonLayout *_child_layout_6;
	MtHorizonLayout *_child_layout_7;
	MtVerticalLayout *_child_layout_8;
	MtHorizonLayout *_main_layout;
};