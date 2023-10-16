#pragma once

#include"../DialogBase.h"
#include"../../../Resource.h"
#include"afxwin.h"

class MtBitmap;
class MtVerticalLayout;
class MtHorizonLayout;
class MtImageStatic;
class MtImageButton;
class DialogSpecimenInformation;
class DialogItemAndProfileKeys;

/**
 * name: DialogTestSelection
 * brief: “项目选择”页面对话框。
 * author: yameng_he
 * date: 2015-02-11
 */
class DialogTestSelection
	:public DialogBase{
	DECLARE_DYNAMIC(DialogTestSelection)
//define
public:
	enum{IDD=IDD_DIALOG_TEST_SELECTION,
		SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT=5,};
	typedef MtImageButton MtImageRadioBox;
	typedef enum{
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_ROUTINE=0,
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_EMERGENCY=1,
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_BARCODE_ROUTINE=2,
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_BARCODE_EMERGENCY=3,
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_QC=4,
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_UNKNOWN=6,
	}SpecimenInformationChildDialogID;
//construction & destruction
public:
	DialogTestSelection(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogTestSelection();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnDestroy();
	afx_msg void OnRadioBoxesClicked(const unsigned int ID);
//implement
private:
	void init_controls();
	void draw_boder(MtBitmap &memory_bitmap);
	void show_specimen_information_child_dialog(
		const SpecimenInformationChildDialogID child_dialog_id);
//variables
private:
	MtImageStatic *_test_type_static;
	MtImageStatic *_specimen_status_static;
	MtImageStatic *_specimen_condition_static;
	MtImageRadioBox *_routine_radio_box;
	MtImageRadioBox *_emergency_radio_box;
	MtImageRadioBox *_qc_radio_box;
	MtImageButton *_demographics_button;
	MtImageButton *_define_profile_button;
	MtImageButton *_go_to_specimen_button;
	MtImageButton *_previous_button;
	MtImageButton *_next_button;
	MtImageButton *_repeat_button;
	MtImageButton *_id_assignment_list_button;
	MtImageButton *_ok_button;
	SpecimenInformationChildDialogID 
		_current_specimen_information_child_dialog;
	DialogSpecimenInformation 
		*_specimen_information_child_dialogs;
	DialogItemAndProfileKeys *_item_and_profile_keys_child_dialog;
	MtVerticalLayout *_child_layout_1;
	MtVerticalLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtHorizonLayout *_child_layout_4;
	MtVerticalLayout *_main_layout;
};