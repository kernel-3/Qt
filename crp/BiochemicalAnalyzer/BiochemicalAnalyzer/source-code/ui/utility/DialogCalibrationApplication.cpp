// source-code/ui/utility/DialogCalibrationApplication.cpp : implementation file
//

#include"stdafx.h"
#include"DialogCalibrationApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/control/MtImageComboBox.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../global/Database.h"
#include"../../global/DatabaseManager.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../data/utility/Applications.h"
#include"../../data/utility/Application.h"
#include"../../data/common/Item.h"
#include"../UiCustom.h"
#include"../../data/utility/CalibrationApplication.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../../data/DataCustom.h"
#include"../common/DialogMessageBox.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoReset.h"

//DialogCalibrationApplication dialog
IMPLEMENT_DYNAMIC(DialogCalibrationApplication,DialogPageBase)

/**
 * name: DialogCalibrationApplication
 * breif: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
 * return: --
 */
DialogCalibrationApplication::DialogCalibrationApplication(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogCalibrationApplication::IDD,pParent)
	,_item_id(0)
	,_is_command_message_masked(FALSE)
	,_select_test_static(new MtImageStatic)
	,_calibration_type_static(new MtImageStatic)
	,_points_static(new MtImageStatic)
	,_span_point_static(new MtImageStatic)
	,_weight_static(new MtImageStatic)
	,_time_out_static(new MtImageStatic)
	,_lot_no_static(new MtImageStatic)
	,_bottle_static(new MtImageStatic)
	,_change_over_static(new MtImageStatic)
	,_auto_calibration_static(new MtImageStatic)
	,_sd_limit_static(new MtImageStatic)
	,_duplicate_limit_static(new MtImageStatic)
	,_percent_unit_static(new MtImageStatic)
	,_abs_unit_static(new MtImageStatic)
	,_sensitivity_limit_static(new MtImageStatic)
	,_s1_abs_range_static(new MtImageStatic)
	,_select_test_combo_box(new MtImageComboBox)
	,_calibration_type_combo_box(new MtImageComboBox)
	,_test_name_combo_box(new MtImageComboBox)
	,_lot_to_lot_calibration_method_combo_box(new MtImageComboBox)
	,_bottle_to_bottle_calibration_method_combo_box(new MtImageComboBox)
	,_points_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_span_point_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_weight_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_time_for_blank_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_time_for_span_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_time_for_2_point_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_time_for_full_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_sd_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_percent_for_duplicate_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_abs_for_duplicate_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_sensitivity_lower_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_sensitivity_upper_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_s1_abs_lower_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_INTEGER))
	,_s1_abs_upper_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_INTEGER))
	,_blank_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
	,_span_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
	,_2_point_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
	,_full_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
	,_delete_button(new MtImageButton)
	,_ok_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_child_layout_6(new MtHorizonLayout)
	,_child_layout_7(new MtHorizonLayout)
	,_child_layout_8(new MtHorizonLayout)
	,_child_layout_9(new MtHorizonLayout)
	,_child_layout_10(new MtVerticalLayout)
	,_child_layout_11(new MtHorizonLayout)
	,_child_layout_12(new MtHorizonLayout)
	,_child_layout_13(new MtHorizonLayout)
	,_child_layout_14(new MtHorizonLayout)
	,_child_layout_15(new MtVerticalLayout)
	,_child_layout_16(new MtHorizonLayout)
	,_child_layout_17(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogCalibrationApplication
 * breif: ����������
 * param: --
 * return: --
 */
DialogCalibrationApplication::~DialogCalibrationApplication(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	delete _child_layout_6;
	delete _child_layout_7;
	delete _child_layout_8;
	delete _child_layout_9;
	delete _child_layout_10;
	delete _child_layout_11;
	delete _child_layout_12;
	delete _child_layout_13;
	delete _child_layout_14;
	delete _child_layout_15;
	delete _child_layout_16;
	delete _child_layout_17;
	delete _select_test_static;
	delete _calibration_type_static;
	delete _points_static;
	delete _span_point_static;
	delete _weight_static;
	delete _time_out_static;
	delete _lot_no_static;
	delete _bottle_static;
	delete _change_over_static;
	delete _auto_calibration_static;
	delete _sd_limit_static;
	delete _duplicate_limit_static;
	delete _percent_unit_static;
	delete _abs_unit_static;
	delete _sensitivity_limit_static;
	delete _s1_abs_range_static;
	delete _select_test_combo_box;
	delete _calibration_type_combo_box;
	delete _test_name_combo_box;
	delete _lot_to_lot_calibration_method_combo_box;
	delete _bottle_to_bottle_calibration_method_combo_box;
	delete _points_edit;
	delete _span_point_edit;
	delete _weight_edit;
	delete _time_for_blank_edit;
	delete _time_for_span_edit;
	delete _time_for_2_point_edit;
	delete _time_for_full_edit;
	delete _sd_limit_edit;
	delete _percent_for_duplicate_limit_edit;
	delete _abs_for_duplicate_limit_edit;
	delete _sensitivity_lower_limit_edit;
	delete _sensitivity_upper_limit_edit;
	delete _s1_abs_lower_limit_edit;
	delete _s1_abs_upper_limit_edit;
	delete _blank_check_box;
	delete _span_check_box;
	delete _2_point_check_box;
	delete _full_check_box;
	delete _delete_button;
	delete _ok_button;
}

/**
 * name: DoDataExchange
 * brief: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogCalibrationApplication::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SELECT_TEST,*_select_test_static);
	DDX_Control(pDX,IDC_STATIC_CALIBRATION_TYPE,*_calibration_type_static);
	DDX_Control(pDX,IDC_STATIC_POINTS,*_points_static);
	DDX_Control(pDX,IDC_STATIC_SPAN_POINT,*_span_point_static);
	DDX_Control(pDX,IDC_STATIC_WEIGHT,*_weight_static);
	DDX_Control(pDX,IDC_STATIC_TIME_OUT,*_time_out_static);
	DDX_Control(pDX,IDC_STATIC_LOT_NO,*_lot_no_static);
	DDX_Control(pDX,IDC_STATIC_BOTTLE,*_bottle_static);
	DDX_Control(pDX,IDC_STATIC_CHANGE_OVER,*_change_over_static);
	DDX_Control(pDX,IDC_STATIC_AUTO_CALIBRATION,*_auto_calibration_static);
	DDX_Control(pDX,IDC_STATIC_SD_LIMIT,*_sd_limit_static);
	DDX_Control(pDX,IDC_STATIC_DUPLICATE_LIMIT,*_duplicate_limit_static);
	DDX_Control(pDX,IDC_STATIC_PERCENT_UNIT,*_percent_unit_static);
	DDX_Control(pDX,IDC_STATIC_ABS_UNIT,*_abs_unit_static);
	DDX_Control(pDX,IDC_STATIC_SENSITIVITY_LIMIT,*_sensitivity_limit_static);
	DDX_Control(pDX,IDC_STATIC_S1_ABS_RANGE,*_s1_abs_range_static);
	DDX_Control(pDX,IDC_COMBO_SELECT_TEST,*_select_test_combo_box);
	DDX_Control(pDX,IDC_COMBO_CALIBRATION_TYPE,*_calibration_type_combo_box);
	DDX_Control(pDX,IDC_COMBO_TEST_NAME,*_test_name_combo_box);
	DDX_Control(pDX,IDC_COMBO_LOT_TO_LOT_CALIBRATION_METHOD,*_lot_to_lot_calibration_method_combo_box);
	DDX_Control(pDX,IDC_COMBO_BOTTLE_TO_BOTTLE_CALIBRATION_METHOD,*_bottle_to_bottle_calibration_method_combo_box);
	DDX_Control(pDX,IDC_EDIT_POINTS,*_points_edit);
	DDX_Control(pDX,IDC_EDIT_SPAN_POINT,*_span_point_edit);
	DDX_Control(pDX,IDC_EDIT_WEIGHT,*_weight_edit);
	DDX_Control(pDX,IDC_EDIT_TIME_FOR_BLANK,*_time_for_blank_edit);
	DDX_Control(pDX,IDC_EDIT_TIME_FOR_SPAN,*_time_for_span_edit);
	DDX_Control(pDX,IDC_EDIT_TIME_FOR_2_POINT,*_time_for_2_point_edit);
	DDX_Control(pDX,IDC_EDIT_TIME_FOR_FULL,*_time_for_full_edit);
	DDX_Control(pDX,IDC_EDIT_SD_LIMIT,*_sd_limit_edit);
	DDX_Control(pDX,IDC_EDIT_PERCENT_FOR_DUPLICATE_LIMIT,*_percent_for_duplicate_limit_edit);
	DDX_Control(pDX,IDC_EDIT_ABS_FOR_DUPLICATE_LIMIT,*_abs_for_duplicate_limit_edit);
	DDX_Control(pDX,IDC_EDIT_SENSITIVITY_LOWER_LIMIT,*_sensitivity_lower_limit_edit);
	DDX_Control(pDX,IDC_EDIT_SENSITIVITY_UPPER_LIMIT,*_sensitivity_upper_limit_edit);
	DDX_Control(pDX,IDC_EDIT_S1_ABS_LOWER_LIMIT,*_s1_abs_lower_limit_edit);
	DDX_Control(pDX,IDC_EDIT_S1_ABS_UPPER_LIMIT,*_s1_abs_upper_limit_edit);
	DDX_Control(pDX,IDC_CHECK_BLANK,*_blank_check_box);
	DDX_Control(pDX,IDC_CHECK_SPAN,*_span_check_box);
	DDX_Control(pDX,IDC_CHECK_2_POINT,*_2_point_check_box);
	DDX_Control(pDX,IDC_CHECK_FULL,*_full_check_box);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogCalibrationApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի����пؼ���
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: OnCommand
 * brief: ������Ϣ�������⺯���������������ؿؼ����ݸı���Ϣ��
 *        ��������Ӧ�ĸ��ġ�
 * param: wParam - ������Ϣ���ͣ���ʮ��λ�����Լ��ؼ�ID����ʮ��λ����
 *        lParam - δʹ�á�
 * return: --
 */
BOOL DialogCalibrationApplication::OnCommand(WPARAM wParam,LPARAM lParam){
	//TODO: Add your specialized code here and/or call the base class
	/////////////////////////////////////////////////////////////////
	//1.�����ǰ���ı��༭�����ݻ�������ѡ�����ݸı�������Ϣ��
	if((!_is_command_message_masked)&&((
		EN_CHANGE==HIWORD(wParam))||(
		CBN_SELCHANGE==HIWORD(wParam)))){
		//1-1.�����ǰ����ؼ����ݸı䡣
		if(is_data_of_controls_changed()){
			_ok_button->EnableWindow(TRUE);
		}
		//1-2.�����ǰ����ؼ�����δ�ı䡣
		else{
			_ok_button->EnableWindow(FALSE);
		}
	}
	/////////////////////////////////////////////////////////////////
	return(DialogPageBase::OnCommand(wParam,lParam));
}

BEGIN_MESSAGE_MAP(DialogCalibrationApplication,DialogPageBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_BLANK,&DialogCalibrationApplication::OnBnClickedCheckBlank)
	ON_BN_CLICKED(IDC_CHECK_SPAN,&DialogCalibrationApplication::OnBnClickedCheckSpan)
	ON_BN_CLICKED(IDC_CHECK_2_POINT,&DialogCalibrationApplication::OnBnClickedCheck2Point)
	ON_BN_CLICKED(IDC_CHECK_FULL,&DialogCalibrationApplication::OnBnClickedCheckFull)
	ON_BN_CLICKED(IDC_BUTTON_DELETE,&DialogCalibrationApplication::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogCalibrationApplication::OnBnClickedButtonOk)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_TEST,&DialogCalibrationApplication::OnCbnSelchangeComboSelectTest)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,&DialogCalibrationApplication::OnUpdateDataForControlsByItemID)
	ON_MESSAGE(WM_COMMIT_DATA_OF_CONTROLS,&DialogCalibrationApplication::OnCommitDataOfControls)
END_MESSAGE_MAP()

//DialogCalibrationApplication message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogCalibrationApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
	//2.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_16->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_auto_calibration_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: OnBnClickedCheckBlank
 * brief: �û�������հ�Ч׼����ѡ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedCheckBlank(){
	//TODO: Add your control notification handler code here
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	if(_blank_check_box->get_checked()){
		_blank_check_box->set_checked(FALSE);
		_time_for_blank_edit->SetWindowText(_T(""));
		_time_for_blank_edit->EnableWindow(FALSE);
	}else{
		_blank_check_box->set_checked(TRUE);
		_time_for_blank_edit->SetWindowText(_T(""));
		_time_for_blank_edit->EnableWindow(TRUE);
	}
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnBnClickedCheckBlank
 * brief: �û����������Ч׼����ѡ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedCheckSpan(){
	//TODO: Add your control notification handler code here
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	if(_span_check_box->get_checked()){
		_span_check_box->set_checked(FALSE);
		_time_for_span_edit->SetWindowText(_T(""));
		_time_for_span_edit->EnableWindow(FALSE);
	}else{
		_span_check_box->set_checked(TRUE);
		_time_for_span_edit->SetWindowText(_T(""));
		_time_for_span_edit->EnableWindow(TRUE);
	}
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnBnClickedCheckBlank
 * brief: �û������2��Ч׼����ѡ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedCheck2Point(){
	//TODO: Add your control notification handler code here
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	if(_2_point_check_box->get_checked()){
		_2_point_check_box->set_checked(FALSE);
		_time_for_2_point_edit->SetWindowText(_T(""));
		_time_for_2_point_edit->EnableWindow(FALSE);
	}else{
		_2_point_check_box->set_checked(TRUE);
		_time_for_2_point_edit->SetWindowText(_T(""));
		_time_for_2_point_edit->EnableWindow(TRUE);
	}
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnBnClickedCheckFull
 * brief: �û������ȫ��Ч׼����ѡ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedCheckFull(){
	//TODO: Add your control notification handler code here
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	if(_full_check_box->get_checked()){
		_full_check_box->set_checked(FALSE);
		_time_for_full_edit->SetWindowText(_T(""));
		_time_for_full_edit->EnableWindow(FALSE);
	}else{
		_full_check_box->set_checked(TRUE);
		_time_for_full_edit->SetWindowText(_T(""));
		_time_for_full_edit->EnableWindow(TRUE);
	}
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnBnClickedButtonDelete
 * brief: �û������ɾ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedButtonDelete(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	Applications *applications=Applications::instance();
	//2.��ȡ��ǰ����ɾ������Ŀ��ʶ��
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING361),this);
		return;
	}
	const int item_id=static_cast<int>(_select_test_combo_box->GetItemData(item));
	//3.ѯ���û��Ƿ�����ɾ����ǰ��Ŀ��
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING362),this)){
		return;
	}
	//4.ɾ����ǰ��Ŀ�������ж�ɾ���Ƿ�ɹ���
	if(applications->remove(item_id,*((DatabaseManager::instance())->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)))<0){
		ErrorMessageBox(theme->get_string(IDS_STRING158),this);
		return;
	}
	//5.��ǰ��Ŀɾ������ʾ��С��Ŀ��ʶ����Ŀ���������
	//5-1.�Ե�ǰ����Ŀ���������������
	applications->sort_by_item_id();
	//5-2.��ȡ��С��Ŀ��ʶ����Ŀ���������
	Applications::PtrToCApp application=applications->get_by_index(0);
	//5-3.�����ȡ�ɹ���
	if(static_cast<bool>(application)){
		//update_data_for_controls((application->get_item()).get_id());
		GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
			static_cast<WPARAM>((application->get_item()).get_id()),0);
	}
	//5-4.�����ȡʧ�ܡ�
	else{
		//update_data_for_controls(0);
		GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
			static_cast<WPARAM>(0),0);
	}
}

/**
 * name: OnBnClickedButtonOk
 * brief: �û������ȷ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnBnClickedButtonOk(){
	// TODO: Add your control notification handler code here
	//1.�ύ��ǰ�����пؼ����ݡ�
	if(commit_data_of_controls(*((DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){
		return;
	}
	//2.����OnCommand��Ӧ��
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//3.���µ�ǰ�����пؼ����ݡ�
	update_data_for_controls(_item_id);
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: ��ѡ����Ŀ����������Ŀ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibrationApplication::OnCbnSelchangeComboSelectTest(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ�û�ѡ�����Ŀ��ʶ��
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_test_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			_item_id,*_select_test_combo_box));
		return;
	}
	const int item_id=static_cast<int>(_select_test_combo_box->GetItemData(item));
	//3.����û�ѡ�����Ŀ��ʶ���뵱ǰ��Ŀ��ʶ��ͬ����ֱ�ӷ��ء�
	if(item_id==_item_id){
		return;
	}
	//4.�����ǰ����Ĳ��������ı䡣
	if(is_data_of_controls_changed()){
		//4-1.�����û��Ƿ񱣴浱ǰ������
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING359),this);
		//4-2.�����ǰ�û�ѡ��ȡ������ť��
		if(IDCANCEL==result){
			//4-1-1.���οؼ����ݵĸ��¡�
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.�ظ���ǰ������ѡ�����ݡ�
			_select_test_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_item_id,*_select_test_combo_box));
			//4-1-3.�������е���ֱ�ӷ��ء�
			return;
		}
		//4-3.�����ǰ�û�ѡ�񡰷񡱰�ť��
		else if(IDNO==result){
		}
		//4-4.�����ǰ�û�ѡ���ǡ���ť��
		else{
			if(commit_data_of_controls(*((DatabaseManager::instance())->
				get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){//�ύ�ؼ��е����ݡ�
				//4-4-1.���οؼ����ݵĸ��¡�
				MtAutoReset<BOOL> auto_reset(
					_is_command_message_masked,TRUE,FALSE);
				//4-4-2.�ظ���ǰ������ѡ�����ݡ�
				_select_test_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_item_id,*_select_test_combo_box));
				//4-4-3.�������е���ֱ�ӷ��ء�
				return;
			}
		}
	}
	//5.��ʾ��ѡ�����Ŀ�����������Ϣ��
	GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		static_cast<WPARAM>(item_id),0);
}

/**
 * name: OnUpdateDataForControlsByItemID
 * brief: ͨ����Ŀ��ʶ���½���ؼ����ݡ�
 * param: wParam - ��Ŀ��ʶ��
 *        lParam - �����塣
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogCalibrationApplication::OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM /*lParam*/){
	//1.���ε�ǰ����������Ϣ��Ӧ��
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.���µ�ǰ����ؼ����ݡ�
	update_data_for_controls(static_cast<int>(wParam));
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: OnCommitDataOfControls
 * brief: �ύ��ǰ�ؼ��е����ݵ����ݿ�����Ϣ��Ӧ������
 * param: wParam - �����塣
 *        lParam - �����塣
 * return: �������ִ�гɹ������㣬���򷵻ط��㡣
 */
LRESULT DialogCalibrationApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.��������е�����û�з����仯����ֱ�ӷ��ء�
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.ѯ���û��Ƿ�ϣ�����浱ǰ���ݡ�
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING360),this);
	//3.�����ǰ�û�����ˡ�ȡ������ť��
	if(IDCANCEL==result){
		return(1);
	}
	//4.�����ǰ�û�����ˡ��񡱰�ť��
	else if(IDNO==result){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		update_data_for_controls(_item_id);
		return(0);
	}
	//5.�����ǰ�û�����ˡ��ǡ���ť��
	else{
		//5-1.���浱ǰ�ؼ����ݵ�ָ�������ݿ��С�
		if(commit_data_of_controls(*((DatabaseManager::instance())->
			get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){
			return(2);
		}
		//5-2.����OnCommand�ĵ��á�
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		//5-3.�����ǰ�ؼ����ݱ���ɹ������½������ݡ�
		update_data_for_controls(_item_id);
		//5-4.�������е��˳ɹ����ء�
		return(0);
	}
}

/**
 * name: init_controls
 * brief: ��ʼ����ǰ�Ի����пؼ���
 * param: --
 * return: --
 */
void DialogCalibrationApplication::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.��ʼ����ǰ�Ի����пؼ���
	//2-1.��ʼ����̬�ı���
	_select_test_static->set_text_color(255,50,50,50);
	_select_test_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_calibration_type_static->set_text_color(255,50,50,50);
	_calibration_type_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_points_static->set_text_color(255,50,50,50);
	_points_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_span_point_static->set_text_color(255,50,50,50);
	_span_point_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_weight_static->set_text_color(255,50,50,50);
	_weight_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_time_out_static->set_text_color(255,50,50,50);
	_time_out_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_lot_no_static->set_text_color(255,50,50,50);
	_lot_no_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_bottle_static->set_text_color(255,50,50,50);
	_bottle_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_change_over_static->set_text_color(255,50,50,50);
	_change_over_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_auto_calibration_static->set_text_color(255,255,255,255);
	_auto_calibration_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_auto_calibration_static->load_background_image(theme->get_image(25));
	_auto_calibration_static->set_background_image_stretching_factors(10,29,10,2);
	_sd_limit_static->set_text_color(255,50,50,50);
	_sd_limit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_duplicate_limit_static->set_text_color(255,50,50,50);
	_duplicate_limit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_percent_unit_static->set_text_color(255,50,50,50);
	_percent_unit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_abs_unit_static->set_text_color(255,50,50,50);
	_abs_unit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_sensitivity_limit_static->set_text_color(255,50,50,50);
	_sensitivity_limit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_s1_abs_range_static->set_text_color(255,50,50,50);
	_s1_abs_range_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.��ʼ��������
	_select_test_combo_box->set_text_color(255,50,50,50);
	_select_test_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_select_test_combo_box->set_list_box_text_color(255,50,50,50);
	_select_test_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_select_test_combo_box->load_background_image(theme->get_image(27),1,4);
	_select_test_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_select_test_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_select_test_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_calibration_type_combo_box->set_text_color(255,50,50,50);
	_calibration_type_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_calibration_type_combo_box->set_list_box_text_color(255,50,50,50);
	_calibration_type_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_calibration_type_combo_box->load_background_image(theme->get_image(27),1,4);
	_calibration_type_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_calibration_type_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_calibration_type_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_test_name_combo_box->set_text_color(255,50,50,50);
	_test_name_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_test_name_combo_box->set_list_box_text_color(255,50,50,50);
	_test_name_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_test_name_combo_box->load_background_image(theme->get_image(27),1,4);
	_test_name_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_test_name_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_test_name_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_lot_to_lot_calibration_method_combo_box->set_text_color(255,50,50,50);
	_lot_to_lot_calibration_method_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_lot_to_lot_calibration_method_combo_box->set_list_box_text_color(255,50,50,50);
	_lot_to_lot_calibration_method_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_lot_to_lot_calibration_method_combo_box->load_background_image(theme->get_image(27),1,4);
	_lot_to_lot_calibration_method_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_lot_to_lot_calibration_method_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_lot_to_lot_calibration_method_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_bottle_to_bottle_calibration_method_combo_box->set_text_color(255,50,50,50);
	_bottle_to_bottle_calibration_method_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_bottle_to_bottle_calibration_method_combo_box->set_list_box_text_color(255,50,50,50);
	_bottle_to_bottle_calibration_method_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_bottle_to_bottle_calibration_method_combo_box->load_background_image(theme->get_image(27),1,4);
	_bottle_to_bottle_calibration_method_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_bottle_to_bottle_calibration_method_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_bottle_to_bottle_calibration_method_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	init_combo_boxes(*((DatabaseManager::instance())->get_database(DatabaseManager::DATABASE_NAME_MAIN)));
	//2-3.��ʼ���ı��༭��
	_points_edit->set_text_color(50,50,50);
	_points_edit->load_background_image(theme->get_image(29),1,3);
	_points_edit->set_background_image_stretching_factors(5,5,5,5);
	_points_edit->SetLimitText(1);
	_span_point_edit->set_text_color(50,50,50);
	_span_point_edit->load_background_image(theme->get_image(29),1,3);
	_span_point_edit->set_background_image_stretching_factors(5,5,5,5);
	_span_point_edit->SetLimitText(1);
	_weight_edit->set_text_color(50,50,50);
	_weight_edit->load_background_image(theme->get_image(29),1,3);
	_weight_edit->set_background_image_stretching_factors(5,5,5,5);
	_weight_edit->SetLimitText(1);
	_time_for_blank_edit->set_text_color(50,50,50);
	_time_for_blank_edit->load_background_image(theme->get_image(29),1,3);
	_time_for_blank_edit->set_background_image_stretching_factors(5,5,5,5);
	_time_for_blank_edit->SetLimitText(3);
	_time_for_span_edit->set_text_color(50,50,50);
	_time_for_span_edit->load_background_image(theme->get_image(29),1,3);
	_time_for_span_edit->set_background_image_stretching_factors(5,5,5,5);
	_time_for_span_edit->SetLimitText(3);
	_time_for_2_point_edit->set_text_color(50,50,50);
	_time_for_2_point_edit->load_background_image(theme->get_image(29),1,3);
	_time_for_2_point_edit->set_background_image_stretching_factors(5,5,5,5);
	_time_for_2_point_edit->SetLimitText(3);
	_time_for_full_edit->set_text_color(50,50,50);
	_time_for_full_edit->load_background_image(theme->get_image(29),1,3);
	_time_for_full_edit->set_background_image_stretching_factors(5,5,5,5);
	_time_for_full_edit->SetLimitText(3);
	_sd_limit_edit->set_text_color(50,50,50);
	_sd_limit_edit->load_background_image(theme->get_image(29),1,3);
	_sd_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_sd_limit_edit->SetLimitText(7);
	_percent_for_duplicate_limit_edit->set_text_color(50,50,50);
	_percent_for_duplicate_limit_edit->load_background_image(theme->get_image(29),1,3);
	_percent_for_duplicate_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_percent_for_duplicate_limit_edit->SetLimitText(2);
	_abs_for_duplicate_limit_edit->set_text_color(50,50,50);
	_abs_for_duplicate_limit_edit->load_background_image(theme->get_image(29),1,3);
	_abs_for_duplicate_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_abs_for_duplicate_limit_edit->SetLimitText(5);
	_sensitivity_lower_limit_edit->set_text_color(50,50,50);
	_sensitivity_lower_limit_edit->load_background_image(theme->get_image(29),1,3);
	_sensitivity_lower_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_sensitivity_lower_limit_edit->SetLimitText(10);
	_sensitivity_upper_limit_edit->set_text_color(50,50,50);
	_sensitivity_upper_limit_edit->load_background_image(theme->get_image(29),1,3);
	_sensitivity_upper_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_sensitivity_upper_limit_edit->SetLimitText(10);
	_s1_abs_lower_limit_edit->set_text_color(50,50,50);
	_s1_abs_lower_limit_edit->load_background_image(theme->get_image(29),1,3);
	_s1_abs_lower_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_s1_abs_lower_limit_edit->SetLimitText(6);
	_s1_abs_upper_limit_edit->set_text_color(50,50,50);
	_s1_abs_upper_limit_edit->load_background_image(theme->get_image(29),1,3);
	_s1_abs_upper_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_s1_abs_upper_limit_edit->SetLimitText(6);
	//2-4.��ʼ����ѡ��
	_blank_check_box->set_text_color(255,50,50,50);
	_blank_check_box->load_foreground_image(theme->get_image(30),1,6);
	_blank_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_blank_check_box->load_background_image(theme->get_image(1),1,6);
	_span_check_box->set_text_color(255,50,50,50);
	_span_check_box->load_foreground_image(theme->get_image(30),1,6);
	_span_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_span_check_box->load_background_image(theme->get_image(1),1,6);
	_2_point_check_box->set_text_color(255,50,50,50);
	_2_point_check_box->load_foreground_image(theme->get_image(30),1,6);
	_2_point_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_2_point_check_box->load_background_image(theme->get_image(1),1,6);
	_full_check_box->set_text_color(255,50,50,50);
	_full_check_box->load_foreground_image(theme->get_image(30),1,6);
	_full_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_full_check_box->load_background_image(theme->get_image(1),1,6);
	//2-5.��ʼ����ť��
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//3.��ʼ�����֡�
	//3-1.��ʼ���Ӳ���1��
	_child_layout_1->add_fixed_window(_select_test_static,150);
	_child_layout_1->add_fixed_window(_select_test_combo_box,150);
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_calibration_type_static,150);
	_child_layout_2->add_fixed_window(_calibration_type_combo_box,200);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_test_name_combo_box,100);
	//3-3.��ʼ���Ӳ���3��
	_child_layout_3->add_fixed_window(_points_static,150);
	_child_layout_3->add_fixed_window(_points_edit,50);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_fixed_window(_span_point_static,150);
	_child_layout_3->add_fixed_window(_span_point_edit,50);
	//3-4.��ʼ���Ӳ���4��
	_child_layout_4->add_fixed_window(_weight_static,150);
	_child_layout_4->add_fixed_window(_weight_edit,50);
	//3-5.��ʼ���Ӳ���5��
	_child_layout_5->add_window(_time_out_static,1);
	_child_layout_5->add_spacing(10);
	_child_layout_5->add_window(_change_over_static,1);
	//3-6.��ʼ���Ӳ���6��
	_child_layout_6->add_fixed_window(_blank_check_box,100);
	_child_layout_6->add_window(_time_for_blank_edit,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_fixed_window(_lot_no_static,100);
	_child_layout_6->add_window(_lot_to_lot_calibration_method_combo_box,1);
	//3-7.��ʼ���Ӳ���7��
	_child_layout_7->add_fixed_window(_span_check_box,100);
	_child_layout_7->add_window(_time_for_span_edit,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_fixed_window(_bottle_static,100);
	_child_layout_7->add_window(_bottle_to_bottle_calibration_method_combo_box,1);
	//3-8.��ʼ���Ӳ���8��
	_child_layout_8->add_fixed_window(_2_point_check_box,100);
	_child_layout_8->add_window(_time_for_2_point_edit,1);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_spacing(100);
	_child_layout_8->add_stretch(1);
	//3-9.��ʼ���Ӳ���9��
	_child_layout_9->add_fixed_window(_full_check_box,100);
	_child_layout_9->add_window(_time_for_full_edit,1);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_spacing(100);
	_child_layout_9->add_stretch(1);
	//3-10.��ʼ���Ӳ���10��
	_child_layout_10->set_margin(10,34,10,10);
	_child_layout_10->add_fixed_layout(_child_layout_5,24);
	_child_layout_10->add_stretch(1);
	_child_layout_10->add_fixed_layout(_child_layout_6,24);
	_child_layout_10->add_stretch(1);
	_child_layout_10->add_fixed_layout(_child_layout_7,24);
	_child_layout_10->add_stretch(1);
	_child_layout_10->add_fixed_layout(_child_layout_8,24);
	_child_layout_10->add_stretch(1);
	_child_layout_10->add_fixed_layout(_child_layout_9,24);
	//3-11.��ʼ���Ӳ���11��
	_child_layout_11->add_fixed_window(_sd_limit_static,150);
	_child_layout_11->add_window(_sd_limit_edit,1);
	//3-12.��ʼ���Ӳ���12��
	_child_layout_12->add_fixed_window(_duplicate_limit_static,150);
	_child_layout_12->add_window(_percent_for_duplicate_limit_edit,1);
	_child_layout_12->add_fixed_window(_percent_unit_static,30);
	_child_layout_12->add_window(_abs_for_duplicate_limit_edit,1);
	_child_layout_12->add_fixed_window(_abs_unit_static,50);
	//3-13.��ʼ���Ӳ���13��
	_child_layout_13->add_fixed_window(_sensitivity_limit_static,150);
	_child_layout_13->add_window(_sensitivity_lower_limit_edit,1);
	_child_layout_13->add_spacing(5);
	_child_layout_13->add_window(_sensitivity_upper_limit_edit,1);
	//3-14.��ʼ���Ӳ���14��
	_child_layout_14->add_fixed_window(_s1_abs_range_static,150);
	_child_layout_14->add_window(_s1_abs_lower_limit_edit,1);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_window(_s1_abs_upper_limit_edit,1);
	//3-15.��ʼ���Ӳ���15��
	_child_layout_15->add_stretch(2);
	_child_layout_15->add_fixed_layout(_child_layout_11,24);
	_child_layout_15->add_stretch(1);
	_child_layout_15->add_fixed_layout(_child_layout_12,24);
	_child_layout_15->add_stretch(1);
	_child_layout_15->add_fixed_layout(_child_layout_13,24);
	_child_layout_15->add_stretch(1);
	_child_layout_15->add_fixed_layout(_child_layout_14,24);
	_child_layout_15->add_stretch(2);
	//3-16.��ʼ���Ӳ���16��
	_child_layout_16->add_fixed_layout(_child_layout_10,450);
	_child_layout_16->add_spacing(10);
	_child_layout_16->add_fixed_layout(_child_layout_15,350);
	//3-17.��ʼ���Ӳ���17��
	_child_layout_17->add_fixed_window(_delete_button,200);
	_child_layout_17->add_stretch(1);
	_child_layout_17->add_fixed_window(_ok_button,200);
	_child_layout_17->add_stretch(1);
	//3-2.��ʼ�������֡�
	_main_layout->add_spacing(BODER_SIZE);
	_main_layout->add_spacing(10);
	_main_layout->add_fixed_layout(_child_layout_1,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_2,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_3,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_4,24);
	_main_layout->add_stretch(1);
	_main_layout->add_layout(_child_layout_16,15);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_17,50);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_16->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_auto_calibration_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//6.���µ�ǰ�����пؼ���ֵ��
	update_data_for_controls();
}

/**
 * name: init_combo_boxes
 * brief: ��ʼ�������е������򣬽����ݿ��е����ݲ��뵽�������С�
 * param: database - ָ�������ݿ⡣
 * return: --
 */
void DialogCalibrationApplication::init_combo_boxes(Database &database){
	//1.�����ݿ��м��ض��귽�������Ҳ��뵽�����귽�����������С�
	//1-1.����SQL��䣬׼�������ݿ��м��ض��귽����Ϣ��
	CString sql(_T(""));
	sql.Format(_T("SELECT * FROM [calibration_method] ORDER BY [id] ASC"));
	//1-2.�����ݿ��м��ط���������¼����
	Database::PtrToRecordset records=database.get_recordset(sql);
	//1-3.�����귽����¼���е����ݲ��뵽�����귽�����������С�
	//1-3-1.������ǰ�������������
	int id=0;
	int item=0;
	CString name(_T(""));
	_variant_t value;
	Theme *theme=Theme::instance();
	//1-3-2.�����귽����¼���е����ݲ��뵽�����귽�����������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//1-3-2-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//1-3-2-2.��ȡ��ǰ��¼���м�¼�Ķ��귽����ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//1-3-2-3.��ȡ��ǰ��¼���еĶ��귽�����ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//1-3-2-4.���ݴ����ݿ��м��صĶ��귽������,�Զ������ƽ��з��롣
			if(_T("Linear")==name){
				name=theme->get_string(IDS_STRING308);
			}else if(_T("Logit-Log( 3P )")==name){
				name=theme->get_string(IDS_STRING309);
			}else if(_T("Logit-Log( 4P )")==name){
				name=theme->get_string(IDS_STRING310);
			}else if(_T("Logit-Log( 5P )")==name){
				name=theme->get_string(IDS_STRING311);
			}else if(_T("Exponential")==name){
				name=theme->get_string(IDS_STRING312);
			}else if(_T("Spline")==name){
				name=theme->get_string(IDS_STRING313);
			}else if(_T("Polygonal")==name){
				name=theme->get_string(IDS_STRING314);
			}
			//1-3-2-5.����ǰ��ȡ�Ķ��귽����Ϣ���뵽�����귽�����������С�
			item=_calibration_type_combo_box->AddString(name);
			_calibration_type_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//1-3-2-6.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//2.�����ݿ��м��ض������ͣ������������Ͳ��뵽�����ű仯������ƿ�ű仯���������С�
	//2-1.����SQL��䣬׼�������ݿ��м��ض���������Ϣ��
	sql.Format(_T("SELECT * FROM [calibration_type] ORDER BY [id] ASC"));
	//2-2.�����ݿ��м��ض������ͼ�¼����
	records=database.get_recordset(sql);
	//2-3.����¼���м�¼�Ķ������Ͳ��뵽�����ű仯������ƿ�ű仯���������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//2-3-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//2-3-2.��ȡ��ǰ��¼���м�¼�Ķ������ͱ�ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//2-3-3.��ȡ��ǰ��¼���еĶ����������ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//2-3-4.��Ӧ�����������ơ�
			if(_T("Blank")==name){
				name=theme->get_string(IDS_STRING315);
			}else if(_T("Span")==name){
				name=theme->get_string(IDS_STRING316);
			}else if(_T("2 Point")==name){
				name=theme->get_string(IDS_STRING317);
			}else if(_T("Full")==name){
				name=theme->get_string(IDS_STRING318);
			}
			//2-3-5.����ǰ��ȡ�Ķ���������Ϣ���뵽�����Ÿı䡱�������С�
			item=_lot_to_lot_calibration_method_combo_box->AddString(name);
			_lot_to_lot_calibration_method_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//2-3-6.����ǰ��ȡ�Ķ���������Ϣ���뵽���Լ�ƿ�ı䡱�������С�
			item=_bottle_to_bottle_calibration_method_combo_box->AddString(name);
			_bottle_to_bottle_calibration_method_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//2-3-7.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//2-4.�����Ÿı䡱�������в��롰ȡ����ѡ�
	item=_lot_to_lot_calibration_method_combo_box->AddString(
		theme->get_string(IDS_STRING319));
	_lot_to_lot_calibration_method_combo_box->SetItemData(item,
		static_cast<DWORD_PTR>(0));
	//2-5.��ƿ�Ÿı䡱�������в��롰ȡ����ѡ�
	item=_bottle_to_bottle_calibration_method_combo_box->AddString(
		theme->get_string(IDS_STRING319));
	_bottle_to_bottle_calibration_method_combo_box->SetItemData(item,
		static_cast<DWORD_PTR>(0));
}

/**
 * name: update_data_for_controls
 * brief: ��ָ����Ŀ��ʶ�����������Ϣ���µ��ؼ��ϡ�
 * param: item_id - ָ������Ŀ��ʶ��
 * return: --
 * remark: ��item_idС�ڵ�����ʱ���˺���Ĭ����ʾ������С��Ŀ��ʶ����Ŀ�����������
 */
void DialogCalibrationApplication::update_data_for_controls(const int item_id/*=0*/){
	//1.����ǰ����Ŀ��Ŀ��Ϣ�洢����ѡ����Ŀ�����������С�
	//1-1.����ǰ��������������Ϣһһ�����
	for(int index=_select_test_combo_box->GetCount()-1;index>=0;--index){
		_select_test_combo_box->DeleteString(index);
	}
	//1-2.����ǰϵͳ�е���Ŀ��Ϣ����Ŀ��ʶ����
	Applications *applications=Applications::instance();
	applications->sort_by_item_id();
	//1-3.��ȡ��ǰϵͳ�е���Ŀ��Ϣ��������Ϣ���뵽��ѡ����Ŀ���������С�
	int item=0;
	for(unsigned int index=0;index<applications->get_size();++index){
		//1-3-1.��ȡ��ǰϵͳ��ָ������Ŀ��Ϣ��
		Applications::PtrToCApp application=applications->get_by_index(index);
		//1-3-2.�����ȡ��ǰϵͳ��ָ������Ŀ��Ϣʧ�ܡ�
		if(!static_cast<bool>(application)){
			continue;
		}
		//1-3-3.����ǰ����Ŀ��Ϣ�����뵽��ѡ����Ŀ���������С�
		item=_select_test_combo_box->AddString((
			application->get_item()).get_name());
		_select_test_combo_box->SetItemData(item,static_cast<
			DWORD_PTR>((application->get_item()).get_id()));
	}
	//1-4.����ϵͳ�д洢����Ŀ������Ϣ�����µ�ǰ����Ŀѡ�����������ݡ�
	//1-4-1.������ǰ�������������
	int item_count=_select_test_combo_box->GetCount();
	Applications::PtrToCApp application;
	//1-4-2.�����ǰ����������Ϊ�ա�
	if(item_count<=0){
		_select_test_combo_box->SetCurSel(-1);
		_select_test_combo_box->EnableWindow(FALSE);
		_item_id=0;
	}
	//1-4-3.�����ǰδָ��������ʾ����Ŀ��ʶ������ʾ��С����Ŀ��ʶ��
	else if(item_id<=0){
		application=applications->get_by_item_id(
			static_cast<int>(_select_test_combo_box->GetItemData(0)));
		if(!static_cast<bool>(application)){
			_select_test_combo_box->SetCurSel(-1);
			_select_test_combo_box->EnableWindow(FALSE);
			item_count=0;
			_item_id=0;
		}else{
			_select_test_combo_box->SetCurSel(0);
			_select_test_combo_box->EnableWindow(TRUE);
			_item_id=static_cast<int>(
				_select_test_combo_box->GetItemData(0));
		}
	}
	//1-4-4.�����ǰָ����������ʾ����Ŀ��ʶ��
	else{
		application=applications->get_by_item_id(item_id);
		int index=get_combo_box_index_by_item_data<int>(
			item_id,*_select_test_combo_box);
		if((!static_cast<bool>(application))||(index<0)){
			_select_test_combo_box->SetCurSel(-1);
			_select_test_combo_box->EnableWindow(FALSE);
			item_count=0;
			_item_id=0;
		}else{
			_select_test_combo_box->SetCurSel(index);
			_select_test_combo_box->EnableWindow(TRUE);
			_item_id=item_id;
		}
	}
	//2.���á��������͡����������ݡ�
	if(item_count<=0){
		_calibration_type_combo_box->SetCurSel(-1);
		_calibration_type_combo_box->EnableWindow(FALSE);
	}else{
		_calibration_type_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_calibration()).get_calibration_method_id(),
			*_calibration_type_combo_box));
		_calibration_type_combo_box->EnableWindow(TRUE);
	}
	//3.���á��������͸�����Ŀ��ʶ����Ŀ���ƣ������������ݡ�
	//3-1.�����ǰ���������͸�����Ŀ��ʶ����Ŀ���ƣ����������������ݡ�
	for(int index=_test_name_combo_box->GetCount()-1;index>=0;--index){
		_test_name_combo_box->DeleteString(index);
	}
	//3-2.�����ǰ���������͸�����Ŀ��ʶ����Ŀ���ƣ�����������Ҫ�κ����ݡ�
	if(item_count<=0){
		_test_name_combo_box->SetCurSel(-1);
		_test_name_combo_box->EnableWindow(FALSE);
	}
	//3-3.�����ǰ���������͸�����Ŀ��ʶ����Ŀ���ƣ�����������Ҫ���ݡ�
	else{
		//3-3-1.������Ŀ���������������ǰ��Ŀ���������Ŀ���뵽���������͸�����Ŀ��ʶ����Ŀ���ƣ����������С�
		for(unsigned int index=0;index<applications->get_size();++index){
			//3-3-1-1.��ȡ��ǰϵͳ��ָ������Ŀ��Ϣ��
			Applications::PtrToCApp application_t=applications->get_by_index(index);
			//3-3-1-2.�����ȡ��ǰϵͳ��ָ������Ŀ��Ϣʧ�ܡ�
			if(!static_cast<bool>(application_t)){
				continue;
			}
			//3-3-1-3.����뵱ǰѡ�е���Ŀһ�¡�
			if((application_t->get_item()).get_id()==(
				application->get_item()).get_id()){
				continue;
			}
			//3-3-1-4.����ǰ����Ŀ��Ϣ�����뵽���������͸�����Ŀ��ʶ����Ŀ���ƣ����������С�
			item=_test_name_combo_box->AddString((
				application_t->get_item()).get_name());
			_test_name_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>((application_t->get_item()).get_id()));
		}
		//3-3-2.����ȡ������Ϣ�����뵽���������͸�����Ŀ��ʶ����Ŀ���ƣ����������С�
		item=_test_name_combo_box->AddString(
			Theme::instance()->get_string(IDS_STRING340));
		_test_name_combo_box->SetItemData(item,static_cast<DWORD_PTR>(0));
		//3-3-3.���á��������͸�����Ŀ��ʶ����Ŀ���ƣ���������ѡ���
		_test_name_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_calibration()).get_calibration_method_item_id(),
			*_test_name_combo_box));
		_test_name_combo_box->EnableWindow(FALSE);//��ʱ�رմ˲������á�
	}
	//4.���á�Ч׼�㡱�ı��༭�����ݡ�
	CString text(_T(""));
	if(item_count<=0){
		_points_edit->SetWindowText(_T(""));
		_points_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).get_point());
		_points_edit->SetWindowText(text);
		_points_edit->EnableWindow(TRUE);
	}
	//5.���á����̵㡱�ı��༭�����ݡ�
	if(item_count<=0){
		_span_point_edit->SetWindowText(_T(""));
		_span_point_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).get_span_point());
		_span_point_edit->SetWindowText(text);
		_span_point_edit->EnableWindow(TRUE);
	}
	//6.���á�Ȩ�ء��ı��༭�����ݡ�
	if(item_count<=0){
		_weight_edit->SetWindowText(_T(""));
		_weight_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).get_weight());
		_weight_edit->SetWindowText(text);
		_weight_edit->EnableWindow(TRUE);
	}
	//7.���á��հ�Ч׼��ʱ����ѡ���ı��༭�����ݡ�
	if(item_count<=0){
		_blank_check_box->set_checked(FALSE);
		_blank_check_box->EnableWindow(FALSE);
		_time_for_blank_edit->SetWindowText(_T(""));
		_time_for_blank_edit->EnableWindow(FALSE);
	}else{
		if(-1==(application->get_calibration()).get_blank_time_out()){
			_blank_check_box->set_checked(FALSE);
			_blank_check_box->EnableWindow(TRUE);
			_time_for_blank_edit->SetWindowText(_T(""));
			_time_for_blank_edit->EnableWindow(FALSE);
		}else{
			_blank_check_box->set_checked(TRUE);
			_blank_check_box->EnableWindow(TRUE);
			text.Format(_T("%d"),(application->get_calibration()).get_blank_time_out());
			_time_for_blank_edit->SetWindowText(text);
			_time_for_blank_edit->EnableWindow(TRUE);
		}
	}
	//8.���á�����Ч׼��ʱ����ѡ���ı��༭�����ݡ�
	if(item_count<=0){
		_span_check_box->set_checked(FALSE);
		_span_check_box->EnableWindow(FALSE);
		_time_for_span_edit->SetWindowText(_T(""));
		_time_for_span_edit->EnableWindow(FALSE);
	}else{
		if(-1==(application->get_calibration()).get_span_time_out()){
			_span_check_box->set_checked(FALSE);
			_span_check_box->EnableWindow(TRUE);
			_time_for_span_edit->SetWindowText(_T(""));
			_time_for_span_edit->EnableWindow(FALSE);
		}else{
			_span_check_box->set_checked(TRUE);
			_span_check_box->EnableWindow(TRUE);
			text.Format(_T("%d"),(application->get_calibration()).get_span_time_out());
			_time_for_span_edit->SetWindowText(text);
			_time_for_span_edit->EnableWindow(TRUE);
		}
	}
	//9.���á�����Ч׼��ʱ����ѡ���ı��༭�����ݡ�
	if(item_count<=0){
		_2_point_check_box->set_checked(FALSE);
		_2_point_check_box->EnableWindow(FALSE);
		_time_for_2_point_edit->SetWindowText(_T(""));
		_time_for_2_point_edit->EnableWindow(FALSE);
	}else{
		if(-1==(application->get_calibration()).get_2_point_time_out()){
			_2_point_check_box->set_checked(FALSE);
			_2_point_check_box->EnableWindow(TRUE);
			_time_for_2_point_edit->SetWindowText(_T(""));
			_time_for_2_point_edit->EnableWindow(FALSE);
		}else{
			_2_point_check_box->set_checked(TRUE);
			_2_point_check_box->EnableWindow(TRUE);
			text.Format(_T("%d"),(application->get_calibration()).get_2_point_time_out());
			_time_for_2_point_edit->SetWindowText(text);
			_time_for_2_point_edit->EnableWindow(TRUE);
		}
	}
	//10.���á�ȫ��Ч׼��ʱ����ѡ���ı��༭�����ݡ�
	if(item_count<=0){
		_full_check_box->set_checked(FALSE);
		_full_check_box->EnableWindow(FALSE);
		_time_for_full_edit->SetWindowText(_T(""));
		_time_for_full_edit->EnableWindow(FALSE);
	}else{
		if(-1==(application->get_calibration()).get_full_time_out()){
			_full_check_box->set_checked(FALSE);
			_full_check_box->EnableWindow(TRUE);
			_time_for_full_edit->SetWindowText(_T(""));
			_time_for_full_edit->EnableWindow(FALSE);
		}else{
			_full_check_box->set_checked(TRUE);
			_full_check_box->EnableWindow(TRUE);
			text.Format(_T("%d"),(application->get_calibration()).get_full_time_out());
			_time_for_full_edit->SetWindowText(text);
			_time_for_full_edit->EnableWindow(TRUE);
		}
	}
	//11.���á����ű�������������ݡ� 
	if(item_count<=0){
		_lot_to_lot_calibration_method_combo_box->SetCurSel(-1);
		_lot_to_lot_calibration_method_combo_box->EnableWindow(FALSE);
	}else{
		_lot_to_lot_calibration_method_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_calibration()).get_lot_no_change_over_calibration_type_id(),
			*_lot_to_lot_calibration_method_combo_box));
		_lot_to_lot_calibration_method_combo_box->EnableWindow(TRUE);
	}
	//12.���á�ƿ�ű�������������ݡ� 
	if(item_count<=0){
		_bottle_to_bottle_calibration_method_combo_box->SetCurSel(-1);
		_bottle_to_bottle_calibration_method_combo_box->EnableWindow(FALSE);
	}else{
		_bottle_to_bottle_calibration_method_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_calibration()).get_bottle_change_over_calibration_type_id(),
			*_bottle_to_bottle_calibration_method_combo_box));
		_bottle_to_bottle_calibration_method_combo_box->EnableWindow(TRUE);
	}
	//13.���á�SD���ơ��ı��༭�����ݡ�
	if(item_count<=0){
		_sd_limit_edit->SetWindowText(_T(""));
		_sd_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_calibration()).
			get_sd_limit());
		_sd_limit_edit->SetWindowText(text);
		_sd_limit_edit->EnableWindow(TRUE);
	}
	//14.���á��β�ٷֱȡ��ı��༭�����ݡ�
	if(item_count<=0){
		_percent_for_duplicate_limit_edit->SetWindowText(_T(""));
		_percent_for_duplicate_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).
			get_duplicate_limit_percent());
		_percent_for_duplicate_limit_edit->SetWindowText(text);
		_percent_for_duplicate_limit_edit->EnableWindow(TRUE);
	}
	//15.���á��β�����ȡ��ı��༭�����ݡ�
	if(item_count<=0){
		_abs_for_duplicate_limit_edit->SetWindowText(_T(""));
		_abs_for_duplicate_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).
			get_duplicate_limit_abs());
		_abs_for_duplicate_limit_edit->SetWindowText(text);
		_abs_for_duplicate_limit_edit->EnableWindow(TRUE);
	}
	//16.���á����������ޡ��ı��༭�����ݡ�
	if(item_count<=0){
		_sensitivity_lower_limit_edit->SetWindowText(_T(""));
		_sensitivity_lower_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_calibration()).
			get_sensitivity_range_lower_limit());
		_sensitivity_lower_limit_edit->SetWindowText(text);
		_sensitivity_lower_limit_edit->EnableWindow(TRUE);
	}
	//17.���á����������ޡ��ı��༭�����ݡ�
	if(item_count<=0){
		_sensitivity_upper_limit_edit->SetWindowText(_T(""));
		_sensitivity_upper_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_calibration()).
			get_sensitivity_range_upper_limit());
		_sensitivity_upper_limit_edit->SetWindowText(text);
		_sensitivity_upper_limit_edit->EnableWindow(TRUE);
	}
	//18.���á��հ�����ȷ������ޡ��ı��༭�����ݡ�
	if(item_count<=0){
		_s1_abs_lower_limit_edit->SetWindowText(_T(""));
		_s1_abs_lower_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).
			get_s1_abs_range_lower_limit());
		_s1_abs_lower_limit_edit->SetWindowText(text);
		_s1_abs_lower_limit_edit->EnableWindow(TRUE);
	}
	//19.���á��հ�����ȷ������ޡ��ı��༭�����ݡ�
	if(item_count<=0){
		_s1_abs_upper_limit_edit->SetWindowText(_T(""));
		_s1_abs_upper_limit_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_calibration()).
			get_s1_abs_range_upper_limit());
		_s1_abs_upper_limit_edit->SetWindowText(text);
		_s1_abs_upper_limit_edit->EnableWindow(TRUE);
	}
	//20.���á�ɾ������ť��
	if(item_count<=0){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//21.���á�ȷ�ϡ���ť��
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: �жϵ�ǰ�ؼ��е������Ƿ����ı䡣
 * param: --
 * return: �����ǰ�ؼ��е����ݷ����ı��򷵻�TRUE�����򷵻�FALSE��
 */
BOOL DialogCalibrationApplication::is_data_of_controls_changed() const{
	//1.��ȡ��ǰ������ָ����Ŀ��ʶ�����������Ϣ��
	Applications::PtrToCApp application=Applications::
		instance()->get_by_item_id(_item_id);
	if(!static_cast<bool>(application)){//���δ�ܻ�ȡָ��������Ϣ������Ϊ�ޱ仯��
		return(FALSE);
	}
	//2.��⡰���귽�����������Ƿ����仯��
	int item=_calibration_type_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	int value=static_cast<int>(_calibration_type_combo_box->GetItemData(item));
	if((application->get_calibration()).get_calibration_method_id()!=value){
		return(TRUE);
	}
	//3.��⡰���귽��������Ŀ���������Ƿ����仯��
	item=_test_name_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_test_name_combo_box->GetItemData(item));
	if((application->get_calibration()).get_calibration_method_item_id()!=value){
		return(TRUE);
	}
	//4.��⡰Ч׼�������ı��༭���Ƿ����仯��
	CString text(_T(""));
	_points_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_calibration()).get_point()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//5.��⡰���̵㡱�ı��༭���Ƿ����仯��
	_span_point_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_calibration()).get_span_point()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//6.��⡰Ȩ�ء��ı��༭���Ƿ����仯��
	_weight_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_calibration()).get_weight()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//7.��⡰�հ�Ч׼��ʱʱ�䡱��ѡ���ı��༭���Ƿ����仯��
	if(_blank_check_box->get_checked()){
		_time_for_blank_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_calibration()).get_blank_time_out()!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
	}else{
		if(-1!=(application->get_calibration()).get_blank_time_out()){
			return(TRUE);
		}
	}
	//8.��⡰����Ч׼��ʱʱ�䡱��ѡ���ı��༭���Ƿ����仯��
	if(_span_check_box->get_checked()){
		_time_for_span_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_calibration()).get_span_time_out()!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
	}else{
		if(-1!=(application->get_calibration()).get_span_time_out()){
			return(TRUE);
		}
	}
	//9.��⡰2��Ч׼��ʱʱ�䡱��ѡ���ı��༭���Ƿ����仯��
	if(_2_point_check_box->get_checked()){
		_time_for_2_point_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_calibration()).get_2_point_time_out()!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
	}else{
		if(-1!=(application->get_calibration()).get_2_point_time_out()){
			return(TRUE);
		}
	}
	//10.��⡰ȫ��Ч׼��ʱʱ�䡱��ѡ���ı��༭���Ƿ����仯��
	if(_full_check_box->get_checked()){
		_time_for_full_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_calibration()).get_full_time_out()!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
	}else{
		if(-1!=(application->get_calibration()).get_full_time_out()){
			return(TRUE);
		}
	}
	//11.��⡰���ű�����������Ƿ����仯��
	item=_lot_to_lot_calibration_method_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_lot_to_lot_calibration_method_combo_box->GetItemData(item));
	if((application->get_calibration()).get_lot_no_change_over_calibration_type_id()!=value){
		return(TRUE);
	}
	//12.��⡰ƿ������������Ƿ����仯��
	item=_bottle_to_bottle_calibration_method_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_bottle_to_bottle_calibration_method_combo_box->GetItemData(item));
	if((application->get_calibration()).get_bottle_change_over_calibration_type_id()!=value){
		return(TRUE);
	}
	//13.��⡰SD���ޡ��ı��༭���Ƿ����仯��
	_sd_limit_edit->GetWindowText(text);
	if((_T("")==text)||(_T("-")==text)){
		return(TRUE);
	}
	if(!is_zero((application->get_calibration()).get_sd_limit()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//14.��⡰�β�ٷֱȡ��ı��༭���Ƿ�����仯��
	_percent_for_duplicate_limit_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_calibration()).get_duplicate_limit_percent()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//15.��⡰�β�Ũ�ȡ��ı��༭���Ƿ�����仯��
	_abs_for_duplicate_limit_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_calibration()).get_duplicate_limit_abs()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//16.��⡰���������ޡ��ı��༭���Ƿ����仯��
	_sensitivity_lower_limit_edit->GetWindowText(text);
	if((_T("")==text)||(_T("-")==text)){
		return(TRUE);
	}
	if(!is_zero((application->get_calibration()).
		get_sensitivity_range_lower_limit()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//17.��⡰���������ޡ��ı��༭���Ƿ����仯��
	_sensitivity_upper_limit_edit->GetWindowText(text);
	if((_T("")==text)||(_T("-")==text)){
		return(TRUE);
	}
	if(!is_zero((application->get_calibration()).
		get_sensitivity_range_upper_limit()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//18.��⡰�Լ��հ׷�Χ���ޡ��ı��༭��
	_s1_abs_lower_limit_edit->GetWindowText(text);
	if((_T("")==text)||(_T("-")==text)){
		return(TRUE);
	}
	if((application->get_calibration()).get_s1_abs_range_lower_limit()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//19.��⡰�Լ��հ׷�Χ���ޡ��ı��༭��
	_s1_abs_upper_limit_edit->GetWindowText(text);
	if((_T("")==text)||(_T("-")==text)){
		return(TRUE);
	}
	if((application->get_calibration()).get_s1_abs_range_upper_limit()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//20.�������е���ֱ�ӷ���FALSE��
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * breif: ��ȡ�ؼ��е�������Ϣ��
 * param: item_id - ��Ŀ��ʶ��
 *        calibration - Ч׼������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogCalibrationApplication::get_data_from_controls(
	int &item_id,CalibrationApplication &calibration){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ��Ŀ��ʶ��
	int item=0/*_select_test_combo_box->GetCurSel()*/;
	/*
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING175),this);
		_select_test_combo_box->SetFocus();
		return(-1);
	}
	*/
	item_id=_item_id/*static_cast<int>(_select_test_combo_box->GetItemData(item))*/;
	//3.��ȡ��ǰѡ��Ķ������͡�
	item=_calibration_type_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING341),this);
		_calibration_type_combo_box->SetFocus();
		return(-1);
	}
	calibration.set_calibration_method_id(static_cast<int>(
		_calibration_type_combo_box->GetItemData(item)));
	//4.��ȡ��ǰѡ��Ķ��긽����Ŀ��
	item=_test_name_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING342),this);
		_test_name_combo_box->SetFocus();
		return(-2);
	}
	calibration.set_calibration_method_item_id(static_cast<int>(
		_test_name_combo_box->GetItemData(item)));
	//5.��ȡ��ǰ��Ч׼�㡣
	CString text(_T(""));
	_points_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING343),this);
		_points_edit->SetFocus();
		return(-3);
	}
	calibration.set_point(MtCharacterSet::to_integer(text));
	//6.��ȡ��ǰ���̵㡣
	_span_point_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING344),this);
		_span_point_edit->SetFocus();
		return(-4);
	}
	calibration.set_span_point(MtCharacterSet::to_integer(text));
	//7.��ȡ��ǰȨ�ء�
	_weight_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING345),this);
		_weight_edit->SetFocus();
		return(-4);
	}
	calibration.set_weight(MtCharacterSet::to_integer(text));
	//9.��ȡ��ǰ�հ�Ч׼�ĳ�ʱʱ�䡣
	if(_blank_check_box->get_checked()){
		_time_for_blank_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING346),this);
			_time_for_blank_edit->SetFocus();
			return(-5);
		}
		calibration.set_blank_time_out(MtCharacterSet::to_integer(text));
	}else{
		calibration.set_blank_time_out(-1);
	}
	//10.��ȡ��ǰ����Ч׼�ĳ�ʱʱ�䡣
	if(_span_check_box->get_checked()){
		_time_for_span_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING347),this);
			_time_for_span_edit->SetFocus();
			return(-6);
		}
		calibration.set_span_time_out(MtCharacterSet::to_integer(text));
	}else{
		calibration.set_span_time_out(-1);
	}
	//11.��ȡ��ǰ2��Ч׼�ĳ�ʱʱ�䡣
	if(_2_point_check_box->get_checked()){
		_time_for_2_point_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING348),this);
			_time_for_2_point_edit->SetFocus();
			return(-7);
		}
		calibration.set_2_point_time_out(MtCharacterSet::to_integer(text));
	}else{
		calibration.set_2_point_time_out(-1);
	}
	//12.��ȡ��ǰȫ��Ч׼�ĳ�ʱʱ�䡣
	if(_full_check_box->get_checked()){
		_time_for_full_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING349),this);
			_time_for_full_edit->SetFocus();
			return(-8);
		}
		calibration.set_full_time_out(MtCharacterSet::to_integer(text));
	}else{
		calibration.set_full_time_out(-1);
	}
	//13.��ȡ���ű����Ч׼���͡�
	item=_lot_to_lot_calibration_method_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING350),this);
		_lot_to_lot_calibration_method_combo_box->SetFocus();
		return(-9);
	}
	calibration.set_lot_no_change_over_calibration_type_id(
		static_cast<int>(_lot_to_lot_calibration_method_combo_box->GetItemData(item)));
	//14.��ȡƿ���Ч׼���͡�
	item=_bottle_to_bottle_calibration_method_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING351),this);
		_bottle_to_bottle_calibration_method_combo_box->SetFocus();
		return(-10);
	}
	calibration.set_bottle_change_over_calibration_type_id(
		static_cast<int>(_bottle_to_bottle_calibration_method_combo_box->GetItemData(item)));
	//15.��ȡSD����ֵ��
	_sd_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING352),this);
		_sd_limit_edit->SetFocus();
		return(-11);
	}
	calibration.set_sd_limit(MtCharacterSet::to_decimals(text));
	//16.��ȡ�β���İٷֱȡ�
	_percent_for_duplicate_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING353),this);
		_percent_for_duplicate_limit_edit->SetFocus();
		return(-12);
	}
	calibration.set_duplicate_limit_percent(MtCharacterSet::to_integer(text));
	//17.��ȡ�β��������ȡ�
	_abs_for_duplicate_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING354),this);
		_abs_for_duplicate_limit_edit->SetFocus();
		return(-13);
	}
	calibration.set_duplicate_limit_abs(MtCharacterSet::to_integer(text));
	//18.��ȡ�����ȼ������ޡ�
	_sensitivity_lower_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING355),this);
		_sensitivity_lower_limit_edit->SetFocus();
		return(-14);
	}
	calibration.set_sensitivity_range_lower_limit(MtCharacterSet::to_decimals(text));
	//19.��ȡ�����ȼ������ޡ�
	_sensitivity_upper_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING356),this);
		_sensitivity_upper_limit_edit->SetFocus();
		return(-15);
	}
	calibration.set_sensitivity_range_upper_limit(MtCharacterSet::to_decimals(text));
	//20.��ȡ�հ�����ȼ������ޡ�
	_s1_abs_lower_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING357),this);
		_s1_abs_lower_limit_edit->SetFocus();
		return(-16);
	}
	calibration.set_s1_abs_range_lower_limit(MtCharacterSet::to_integer(text));
	//21.��ȡ�հ�����ȼ������ޡ�
	_s1_abs_upper_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING358),this);
		_s1_abs_upper_limit_edit->SetFocus();
		return(-16);
	}
	calibration.set_s1_abs_range_upper_limit(MtCharacterSet::to_integer(text));
	//22.��ⶨ����Ϣ�Ƿ�Ϸ���������Ϸ�ֱ�ӷ��ش���
	//22-1.��ⶨ����Ϣ�Ƿ�Ϸ���
	const int result=calibration.is_valid(&text);
	//22-2.���������Ϣ���Ϸ�������ʾ�û���
	if(result<0){
		WarningMessageBox(text,this);
		if(-1==result){
			_select_test_combo_box->SetFocus();
		}else if(-2==result){
			_test_name_combo_box->SetFocus();
		}else if(-3==result){
			_points_edit->SetFocus();
		}else if(-4==result){
			_span_point_edit->SetFocus();
		}else if(-5==result){
			_weight_edit->SetFocus();
		}else if(-6==result){
			_time_for_blank_edit->SetFocus();
		}else if(-7==result){
			_time_for_span_edit->SetFocus();
		}else if(-8==result){
			_time_for_2_point_edit->SetFocus();
		}else if(-9==result){
			_time_for_full_edit->SetFocus();
		}else if(-10==result){
			_lot_to_lot_calibration_method_combo_box->SetFocus();
		}else if(-11==result){
			_bottle_to_bottle_calibration_method_combo_box->SetFocus();
		}else if(-12==result){
			_sd_limit_edit->SetFocus();
		}else if(-13==result){
			_percent_for_duplicate_limit_edit->SetFocus();
		}else if(-14==result){
			_abs_for_duplicate_limit_edit->SetFocus();
		}else if(-15==result){
			_sensitivity_lower_limit_edit->SetFocus();
		}else if(-16==result){
			_sensitivity_upper_limit_edit->SetFocus();
		}else if(-17==result){
			_s1_abs_lower_limit_edit->SetFocus();
		}else if(-18==result){
			_s1_abs_upper_limit_edit->SetFocus();
		}else if(-19==result){
			_sensitivity_lower_limit_edit->SetFocus();
		}else if(-20==result){
			_s1_abs_lower_limit_edit->SetFocus();
		}
		return(-17);
	}
	//23.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: �ύ�ؼ������ݵ�ָ�������ݿ��С�
 * param: database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogCalibrationApplication::commit_data_of_controls(Database &database){
	//1.������ǰ�������������
	int item_id=0;
	CalibrationApplication calibration;
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ��������������ݡ�
	if(get_data_from_controls(item_id,calibration)<0){
		return(-1);
	}
	//3.�����ݿ��ύ�޸ĵ����ݣ������ж��ύ�Ƿ�ɹ���
	if(Applications::instance()->commit(
		item_id,calibration,database)<0){
		ErrorMessageBox(theme->get_string(158),this);
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}