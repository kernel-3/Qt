//source-code/ui/utility/DialogStandardApplication.cpp : implementation file
//

#include"stdafx.h"
#include"DialogStandardApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/control/MtImageComboBox.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../data/utility/Applications.h"
#include"../../data/utility/Application.h"
#include"../../data/common/Item.h"
#include"../UiCustom.h"
#include"../../data/utility/StandardApplication.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../../data/DataCustom.h"
#include"../common/DialogMessageBox.h"
#include"../../global/DatabaseManager.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoReset.h"

//DialogStandardApplication dialog

IMPLEMENT_DYNAMIC(DialogStandardApplication,DialogPageBase)

/**
 * name: DialogStandardApplication
 * brief: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
 * return: --
 */
DialogStandardApplication::DialogStandardApplication(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogStandardApplication::IDD,pParent)
	,_item_id(0)
	,_is_command_message_masked(FALSE)
	,_select_test_static(new MtImageStatic)
	,_calibrator_code_static(new MtImageStatic)
	,_concentration_static(new MtImageStatic)
	,_position_static(new MtImageStatic)
	,_standard_static(new MtImageStatic)
	,_standard_1_static(new MtImageStatic)
	,_standard_2_static(new MtImageStatic)
	,_standard_3_static(new MtImageStatic)
	,_standard_4_static(new MtImageStatic)
	,_standard_5_static(new MtImageStatic)
	,_standard_6_static(new MtImageStatic)
	,_sample_volume_static(new MtImageStatic)
	,_diluted_sample_volume_static(new MtImageStatic)
	,_diluent_volume_static(new MtImageStatic)
	,_select_test_combo_box(new MtImageComboBox)
	,_calibrator_code_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_calibrator_code_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_calibrator_code_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_calibrator_code_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_calibrator_code_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_calibrator_code_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_concentration_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_concentration_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_concentration_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_concentration_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_concentration_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_concentration_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_position_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_position_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_position_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_position_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_position_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_position_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_sample_volume_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_sample_volume_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_sample_volume_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_sample_volume_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_sample_volume_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_sample_volume_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluted_sample_volume_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
	,_diluent_volume_6_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,1))
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
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogStandardApplication
 * brief: ����������
 * param: --
 * return: --
 */
DialogStandardApplication::~DialogStandardApplication(){
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
	delete _select_test_static;
	delete _calibrator_code_static;
	delete _concentration_static;
	delete _position_static;
	delete _standard_static;
	delete _standard_1_static;
	delete _standard_2_static;
	delete _standard_3_static;
	delete _standard_4_static;
	delete _standard_5_static;
	delete _standard_6_static;
	delete _sample_volume_static;
	delete _diluted_sample_volume_static;
	delete _diluent_volume_static;
	delete _select_test_combo_box;
	delete _calibrator_code_1_edit;
	delete _calibrator_code_2_edit;
	delete _calibrator_code_3_edit;
	delete _calibrator_code_4_edit;
	delete _calibrator_code_5_edit;
	delete _calibrator_code_6_edit;
	delete _concentration_1_edit;
	delete _concentration_2_edit;
	delete _concentration_3_edit;
	delete _concentration_4_edit;
	delete _concentration_5_edit;
	delete _concentration_6_edit;
	delete _position_1_edit;
	delete _position_2_edit;
	delete _position_3_edit;
	delete _position_4_edit;
	delete _position_5_edit;
	delete _position_6_edit;
	delete _sample_volume_1_edit;
	delete _sample_volume_2_edit;
	delete _sample_volume_3_edit;
	delete _sample_volume_4_edit;
	delete _sample_volume_5_edit;
	delete _sample_volume_6_edit;
	delete _diluted_sample_volume_1_edit;
	delete _diluted_sample_volume_2_edit;
	delete _diluted_sample_volume_3_edit;
	delete _diluted_sample_volume_4_edit;
	delete _diluted_sample_volume_5_edit;
	delete _diluted_sample_volume_6_edit;
	delete _diluent_volume_1_edit;
	delete _diluent_volume_2_edit;
	delete _diluent_volume_3_edit;
	delete _diluent_volume_4_edit;
	delete _diluent_volume_5_edit;
	delete _diluent_volume_6_edit;
	delete _delete_button;
	delete _ok_button;
}

/**
 * name: DoDataExchange
 * brief: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogStandardApplication::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SELECT_TEST,*_select_test_static);
	DDX_Control(pDX,IDC_STATIC_CALIBRATOR_CODE,*_calibrator_code_static);
	DDX_Control(pDX,IDC_STATIC_CONCENTRATION,*_concentration_static);
	DDX_Control(pDX,IDC_STATIC_POSITION,*_position_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD,*_standard_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_1,*_standard_1_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_2,*_standard_2_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_3,*_standard_3_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_4,*_standard_4_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_5,*_standard_5_static);
	DDX_Control(pDX,IDC_STATIC_STANDARD_6,*_standard_6_static);
	DDX_Control(pDX,IDC_STATIC_SAMPLE_VOLUME,*_sample_volume_static);
	DDX_Control(pDX,IDC_STATIC_DILUTED_SAMPLE_VOLUME,*_diluted_sample_volume_static);
	DDX_Control(pDX,IDC_STATIC_DILUENT_VOLUME,*_diluent_volume_static);
	DDX_Control(pDX,IDC_COMBO_SELECT_TEST,*_select_test_combo_box);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_1,*_calibrator_code_1_edit);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_2,*_calibrator_code_2_edit);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_3,*_calibrator_code_3_edit);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_4,*_calibrator_code_4_edit);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_5,*_calibrator_code_5_edit);
	DDX_Control(pDX,IDC_EDIT_CALIBRATOR_CODE_6,*_calibrator_code_6_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_1,*_concentration_1_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_2,*_concentration_2_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_3,*_concentration_3_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_4,*_concentration_4_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_5,*_concentration_5_edit);
	DDX_Control(pDX,IDC_EDIT_CONCENTRATION_6,*_concentration_6_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_1,*_position_1_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_2,*_position_2_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_3,*_position_3_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_4,*_position_4_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_5,*_position_5_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION_6,*_position_6_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_1,*_sample_volume_1_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_2,*_sample_volume_2_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_3,*_sample_volume_3_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_4,*_sample_volume_4_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_5,*_sample_volume_5_edit);
	DDX_Control(pDX,IDC_EDIT_SAMPLE_VOLUME_6,*_sample_volume_6_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_1,*_diluted_sample_volume_1_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_2,*_diluted_sample_volume_2_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_3,*_diluted_sample_volume_3_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_4,*_diluted_sample_volume_4_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_5,*_diluted_sample_volume_5_edit);
	DDX_Control(pDX,IDC_EDIT_DILUTED_SAMPLE_VOLUME_6,*_diluted_sample_volume_6_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_1,*_diluent_volume_1_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_2,*_diluent_volume_2_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_3,*_diluent_volume_3_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_4,*_diluent_volume_4_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_5,*_diluent_volume_5_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_VOLUME_6,*_diluent_volume_6_edit);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogStandardApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի����пؼ���
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);// return TRUE unless you set the focus to a control
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
BOOL DialogStandardApplication::OnCommand(WPARAM wParam,LPARAM lParam){
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

BEGIN_MESSAGE_MAP(DialogStandardApplication,DialogPageBase)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_TEST,&DialogStandardApplication::OnCbnSelchangeComboSelectTest)
	ON_BN_CLICKED(IDC_BUTTON_DELETE,&DialogStandardApplication::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogStandardApplication::OnBnClickedButtonOk)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,&DialogStandardApplication::OnUpdateDataForControlsByItemID)
	ON_MESSAGE(WM_COMMIT_DATA_OF_CONTROLS,&DialogStandardApplication::OnCommitDataOfControls)
END_MESSAGE_MAP()

//DialogStandardApplication message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogStandardApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: ��ѡ����Ŀ����������Ŀ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogStandardApplication::OnCbnSelchangeComboSelectTest(){
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
			theme->get_string(IDS_STRING480),this);
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
 * name: OnBnClickedButtonDelete
 * brief: �û������ɾ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogStandardApplication::OnBnClickedButtonDelete(){
	// TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	Applications *applications=Applications::instance();
	//2.��ȡ��ǰ����ɾ������Ŀ��ʶ��
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING481),this);
		return;
	}
	const int item_id=static_cast<int>(_select_test_combo_box->GetItemData(item));
	//3.ѯ���û��Ƿ�����ɾ����ǰ��Ŀ��
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING482),this)){
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
		GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
			static_cast<WPARAM>((application->get_item()).get_id()),0);
	}
	//5-4.�����ȡʧ�ܡ�
	else{
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
void DialogStandardApplication::OnBnClickedButtonOk(){
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
 * name: OnUpdateDataForControlsByItemID
 * brief: ͨ����Ŀ��ʶ���½���ؼ����ݡ�
 * param: wParam - ��Ŀ��ʶ��
 *        lParam - �����塣
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogStandardApplication::OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM /*lParam*/){
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
LRESULT DialogStandardApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.��������е�����û�з����仯����ֱ�ӷ��ء�
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.ѯ���û��Ƿ�ϣ�����浱ǰ���ݡ�
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING483),this);
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
 * brief: ��ʼ�������пؼ���
 * param: --
 * return: --
 */
void DialogStandardApplication::init_controls(){
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
	_calibrator_code_static->set_text_color(255,50,50,50);
	_calibrator_code_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_concentration_static->set_text_color(255,50,50,50);
	_concentration_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_position_static->set_text_color(255,50,50,50);
	_position_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_static->set_text_color(255,50,50,50);
	_standard_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_1_static->set_text_color(255,50,50,50);
	_standard_1_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_2_static->set_text_color(255,50,50,50);
	_standard_2_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_3_static->set_text_color(255,50,50,50);
	_standard_3_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_4_static->set_text_color(255,50,50,50);
	_standard_4_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_5_static->set_text_color(255,50,50,50);
	_standard_5_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_standard_6_static->set_text_color(255,50,50,50);
	_standard_6_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_sample_volume_static->set_text_color(255,50,50,50);
	_sample_volume_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_diluted_sample_volume_static->set_text_color(255,50,50,50);
	_diluted_sample_volume_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);	
	_diluent_volume_static->set_text_color(255,50,50,50);
	_diluent_volume_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
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
	//2-3.��ʼ���ı��༭��
	_calibrator_code_1_edit->set_text_color(50,50,50);
	_calibrator_code_1_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_1_edit->SetLimitText(3);
	_calibrator_code_2_edit->set_text_color(50,50,50);
	_calibrator_code_2_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_2_edit->SetLimitText(3);
	_calibrator_code_3_edit->set_text_color(50,50,50);
	_calibrator_code_3_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_3_edit->SetLimitText(3);
	_calibrator_code_4_edit->set_text_color(50,50,50);
	_calibrator_code_4_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_4_edit->SetLimitText(3);
	_calibrator_code_5_edit->set_text_color(50,50,50);
	_calibrator_code_5_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_5_edit->SetLimitText(3);
	_calibrator_code_6_edit->set_text_color(50,50,50);
	_calibrator_code_6_edit->load_background_image(theme->get_image(29),1,3);
	_calibrator_code_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_calibrator_code_6_edit->SetLimitText(3);
	_concentration_1_edit->set_text_color(50,50,50);
	_concentration_1_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_1_edit->SetLimitText(10);
	_concentration_1_edit->EnableWindow(FALSE);
	_concentration_2_edit->set_text_color(50,50,50);
	_concentration_2_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_2_edit->SetLimitText(10);
	_concentration_2_edit->EnableWindow(FALSE);
	_concentration_3_edit->set_text_color(50,50,50);
	_concentration_3_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_3_edit->SetLimitText(10);
	_concentration_3_edit->EnableWindow(FALSE);
	_concentration_4_edit->set_text_color(50,50,50);
	_concentration_4_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_4_edit->SetLimitText(10);
	_concentration_4_edit->EnableWindow(FALSE);
	_concentration_5_edit->set_text_color(50,50,50);
	_concentration_5_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_5_edit->SetLimitText(10);
	_concentration_5_edit->EnableWindow(FALSE);
	_concentration_6_edit->set_text_color(50,50,50);
	_concentration_6_edit->load_background_image(theme->get_image(29),1,3);
	_concentration_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_concentration_6_edit->SetLimitText(10);
	_concentration_6_edit->EnableWindow(FALSE);
	_position_1_edit->set_text_color(50,50,50);
	_position_1_edit->load_background_image(theme->get_image(29),1,3);
	_position_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_1_edit->SetLimitText(3);
	_position_1_edit->EnableWindow(FALSE);
	_position_2_edit->set_text_color(50,50,50);
	_position_2_edit->load_background_image(theme->get_image(29),1,3);
	_position_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_2_edit->SetLimitText(3);
	_position_2_edit->EnableWindow(FALSE);
	_position_3_edit->set_text_color(50,50,50);
	_position_3_edit->load_background_image(theme->get_image(29),1,3);
	_position_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_3_edit->SetLimitText(3);
	_position_3_edit->EnableWindow(FALSE);
	_position_4_edit->set_text_color(50,50,50);
	_position_4_edit->load_background_image(theme->get_image(29),1,3);
	_position_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_4_edit->SetLimitText(3);
	_position_4_edit->EnableWindow(FALSE);
	_position_5_edit->set_text_color(50,50,50);
	_position_5_edit->load_background_image(theme->get_image(29),1,3);
	_position_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_5_edit->SetLimitText(3);
	_position_5_edit->EnableWindow(FALSE);
	_position_6_edit->set_text_color(50,50,50);
	_position_6_edit->load_background_image(theme->get_image(29),1,3);
	_position_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_6_edit->SetLimitText(3);
	_position_6_edit->EnableWindow(FALSE);
	_sample_volume_1_edit->set_text_color(50,50,50);
	_sample_volume_1_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_1_edit->SetLimitText(4);
	_sample_volume_2_edit->set_text_color(50,50,50);
	_sample_volume_2_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_2_edit->SetLimitText(4);
	_sample_volume_3_edit->set_text_color(50,50,50);
	_sample_volume_3_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_3_edit->SetLimitText(4);
	_sample_volume_4_edit->set_text_color(50,50,50);
	_sample_volume_4_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_4_edit->SetLimitText(4);
	_sample_volume_5_edit->set_text_color(50,50,50);
	_sample_volume_5_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_5_edit->SetLimitText(4);
	_sample_volume_6_edit->set_text_color(50,50,50);
	_sample_volume_6_edit->load_background_image(theme->get_image(29),1,3);
	_sample_volume_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_sample_volume_6_edit->SetLimitText(4);
	_diluted_sample_volume_1_edit->set_text_color(50,50,50);
	_diluted_sample_volume_1_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_1_edit->SetLimitText(4);
	_diluted_sample_volume_2_edit->set_text_color(50,50,50);
	_diluted_sample_volume_2_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_2_edit->SetLimitText(4);
	_diluted_sample_volume_3_edit->set_text_color(50,50,50);
	_diluted_sample_volume_3_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_3_edit->SetLimitText(4);
	_diluted_sample_volume_4_edit->set_text_color(50,50,50);
	_diluted_sample_volume_4_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_4_edit->SetLimitText(4);
	_diluted_sample_volume_5_edit->set_text_color(50,50,50);
	_diluted_sample_volume_5_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_5_edit->SetLimitText(4);
	_diluted_sample_volume_6_edit->set_text_color(50,50,50);
	_diluted_sample_volume_6_edit->load_background_image(theme->get_image(29),1,3);
	_diluted_sample_volume_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluted_sample_volume_6_edit->SetLimitText(4);
	_diluent_volume_1_edit->set_text_color(50,50,50);
	_diluent_volume_1_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_1_edit->SetLimitText(5);
	_diluent_volume_2_edit->set_text_color(50,50,50);
	_diluent_volume_2_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_2_edit->SetLimitText(5);
	_diluent_volume_3_edit->set_text_color(50,50,50);
	_diluent_volume_3_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_3_edit->SetLimitText(5);
	_diluent_volume_4_edit->set_text_color(50,50,50);
	_diluent_volume_4_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_4_edit->SetLimitText(5);
	_diluent_volume_5_edit->set_text_color(50,50,50);
	_diluent_volume_5_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_5_edit->SetLimitText(5);
	_diluent_volume_6_edit->set_text_color(50,50,50);
	_diluent_volume_6_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_volume_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_volume_6_edit->SetLimitText(5);
	//2-4.��ʼ����ť��
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//3.��ʼ����ǰ�Ի����в��֡�
	//3-1.��ʼ���Ӳ���1��
	_child_layout_1->add_fixed_window(_select_test_static,200);
	_child_layout_1->add_fixed_window(_select_test_combo_box,150);
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_standard_static,200);
	_child_layout_2->add_fixed_window(_standard_1_static,80);
	_child_layout_2->add_spacing(20);
	_child_layout_2->add_fixed_window(_standard_2_static,80);
	_child_layout_2->add_spacing(20);
	_child_layout_2->add_fixed_window(_standard_3_static,80);
	_child_layout_2->add_spacing(20);
	_child_layout_2->add_fixed_window(_standard_4_static,80);
	_child_layout_2->add_spacing(20);
	_child_layout_2->add_fixed_window(_standard_5_static,80);
	_child_layout_2->add_spacing(20);
	_child_layout_2->add_fixed_window(_standard_6_static,80);
	//3-3.��ʼ���Ӳ���3��
	_child_layout_3->add_fixed_window(_calibrator_code_static,200);
	_child_layout_3->add_fixed_window(_calibrator_code_1_edit,80);
	_child_layout_3->add_spacing(20);
	_child_layout_3->add_fixed_window(_calibrator_code_2_edit,80);
	_child_layout_3->add_spacing(20);
	_child_layout_3->add_fixed_window(_calibrator_code_3_edit,80);
	_child_layout_3->add_spacing(20);
	_child_layout_3->add_fixed_window(_calibrator_code_4_edit,80);
	_child_layout_3->add_spacing(20);
	_child_layout_3->add_fixed_window(_calibrator_code_5_edit,80);
	_child_layout_3->add_spacing(20);
	_child_layout_3->add_fixed_window(_calibrator_code_6_edit,80);
	//3-4.��ʼ���Ӳ���4��
	_child_layout_4->add_fixed_window(_concentration_static,200);
	_child_layout_4->add_fixed_window(_concentration_1_edit,80);
	_child_layout_4->add_spacing(20);
	_child_layout_4->add_fixed_window(_concentration_2_edit,80);
	_child_layout_4->add_spacing(20);
	_child_layout_4->add_fixed_window(_concentration_3_edit,80);
	_child_layout_4->add_spacing(20);
	_child_layout_4->add_fixed_window(_concentration_4_edit,80);
	_child_layout_4->add_spacing(20);
	_child_layout_4->add_fixed_window(_concentration_5_edit,80);
	_child_layout_4->add_spacing(20);
	_child_layout_4->add_fixed_window(_concentration_6_edit,80);
	//3-5.��ʼ���Ӳ���5��
	_child_layout_5->add_fixed_window(_position_static,200);
	_child_layout_5->add_fixed_window(_position_1_edit,80);
	_child_layout_5->add_spacing(20);
	_child_layout_5->add_fixed_window(_position_2_edit,80);
	_child_layout_5->add_spacing(20);
	_child_layout_5->add_fixed_window(_position_3_edit,80);
	_child_layout_5->add_spacing(20);
	_child_layout_5->add_fixed_window(_position_4_edit,80);
	_child_layout_5->add_spacing(20);
	_child_layout_5->add_fixed_window(_position_5_edit,80);
	_child_layout_5->add_spacing(20);
	_child_layout_5->add_fixed_window(_position_6_edit,80);
	//3-6.��ʼ���Ӳ���6��
	_child_layout_6->add_fixed_window(_sample_volume_static,200);
	_child_layout_6->add_fixed_window(_sample_volume_1_edit,80);
	_child_layout_6->add_spacing(20);
	_child_layout_6->add_fixed_window(_sample_volume_2_edit,80);
	_child_layout_6->add_spacing(20);
	_child_layout_6->add_fixed_window(_sample_volume_3_edit,80);
	_child_layout_6->add_spacing(20);
	_child_layout_6->add_fixed_window(_sample_volume_4_edit,80);
	_child_layout_6->add_spacing(20);
	_child_layout_6->add_fixed_window(_sample_volume_5_edit,80);
	_child_layout_6->add_spacing(20);
	_child_layout_6->add_fixed_window(_sample_volume_6_edit,80);
	//3-7.��ʼ���Ӳ���7��
	_child_layout_7->add_fixed_window(_diluted_sample_volume_static,200);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_1_edit,80);
	_child_layout_7->add_spacing(20);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_2_edit,80);
	_child_layout_7->add_spacing(20);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_3_edit,80);
	_child_layout_7->add_spacing(20);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_4_edit,80);
	_child_layout_7->add_spacing(20);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_5_edit,80);
	_child_layout_7->add_spacing(20);
	_child_layout_7->add_fixed_window(_diluted_sample_volume_6_edit,80);
	//3-8.��ʼ���Ӳ���8��
	_child_layout_8->add_fixed_window(_diluent_volume_static,200);
	_child_layout_8->add_fixed_window(_diluent_volume_1_edit,80);
	_child_layout_8->add_spacing(20);
	_child_layout_8->add_fixed_window(_diluent_volume_2_edit,80);
	_child_layout_8->add_spacing(20);
	_child_layout_8->add_fixed_window(_diluent_volume_3_edit,80);
	_child_layout_8->add_spacing(20);
	_child_layout_8->add_fixed_window(_diluent_volume_4_edit,80);
	_child_layout_8->add_spacing(20);
	_child_layout_8->add_fixed_window(_diluent_volume_5_edit,80);
	_child_layout_8->add_spacing(20);
	_child_layout_8->add_fixed_window(_diluent_volume_6_edit,80);
	//3-9.��ʼ���Ӳ���9��
	_child_layout_9->add_fixed_window(_delete_button,200);
	_child_layout_9->add_stretch(1);
	_child_layout_9->add_fixed_window(_ok_button,200);
	_child_layout_9->add_stretch(1);
	//3-10.��ʼ�������֡�
	_main_layout->add_spacing(BODER_SIZE);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_1,24);
	_main_layout->add_spacing(20);
	_main_layout->add_fixed_layout(_child_layout_2,24);
	_main_layout->add_spacing(20);
	_main_layout->add_fixed_layout(_child_layout_3,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_4,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_5,24);
	_main_layout->add_spacing(20);
	_main_layout->add_fixed_layout(_child_layout_6,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_7,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_8,24);
	_main_layout->add_spacing(20);
	_main_layout->add_fixed_layout(_child_layout_9,40);
	_main_layout->add_stretch(1);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.���µ�ǰ�����пؼ����ݡ�
	update_data_for_controls(0);
}

/**
 * name: update_data_for_controls
 * brief: ��ָ����Ŀ��ʶ�����������Ϣ���µ��ؼ��ϡ�
 * param: item_id - ָ������Ŀ��ʶ��
 * return: --
 * remark: ��item_idС�ڵ�����ʱ���˺���Ĭ����ʾ������С��Ŀ��ʶ����Ŀ�����������
 */
void DialogStandardApplication::update_data_for_controls(const int item_id/*=0*/){
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
	//2.����Ч׼Һ���1�ı��༭��
	CString text(_T(""));
	if(item_count<=0){
		_calibrator_code_1_edit->SetWindowText(_T(""));
		_calibrator_code_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_1());
		_calibrator_code_1_edit->SetWindowText(text);
		_calibrator_code_1_edit->EnableWindow(TRUE);
	}
	//3.����Ч׼Һ���2�ı��༭��
	if(item_count<=0){
		_calibrator_code_2_edit->SetWindowText(_T(""));
		_calibrator_code_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_2());
		_calibrator_code_2_edit->SetWindowText(text);
		_calibrator_code_2_edit->EnableWindow(TRUE);
	}
	//4.����Ч׼Һ���3�ı��༭��
	if(item_count<=0){
		_calibrator_code_3_edit->SetWindowText(_T(""));
		_calibrator_code_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_3());
		_calibrator_code_3_edit->SetWindowText(text);
		_calibrator_code_3_edit->EnableWindow(TRUE);
	}
	//5.����Ч׼Һ���4�ı��༭��
	if(item_count<=0){
		_calibrator_code_4_edit->SetWindowText(_T(""));
		_calibrator_code_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_4());
		_calibrator_code_4_edit->SetWindowText(text);
		_calibrator_code_4_edit->EnableWindow(TRUE);
	}
	//6.����Ч׼Һ���5�ı��༭��
	if(item_count<=0){
		_calibrator_code_5_edit->SetWindowText(_T(""));
		_calibrator_code_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_5());
		_calibrator_code_5_edit->SetWindowText(text);
		_calibrator_code_5_edit->EnableWindow(TRUE);
	}
	//7.����Ч׼Һ���6�ı��༭��
	if(item_count<=0){
		_calibrator_code_6_edit->SetWindowText(_T(""));
		_calibrator_code_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_6());
		_calibrator_code_6_edit->SetWindowText(text);
		_calibrator_code_6_edit->EnableWindow(TRUE);
	}
	//8.����Ч׼ҺŨ��1�ı��༭��
	if(item_count<=0){
		_concentration_1_edit->SetWindowText(_T(""));
	}else{
	}
	//9.����Ч׼ҺŨ��2�ı��༭��
	if(item_count<=0){
		_concentration_2_edit->SetWindowText(_T(""));
	}else{
	}
	//10.����Ч׼ҺŨ��3�ı��༭��
	if(item_count<=0){
		_concentration_3_edit->SetWindowText(_T(""));
	}else{
	}
	//11.����Ч׼ҺŨ��4�ı��༭��
	if(item_count<=0){
		_concentration_4_edit->SetWindowText(_T(""));
	}else{
	}
	//12.����Ч׼ҺŨ��5�ı��༭��
	if(item_count<=0){
		_concentration_5_edit->SetWindowText(_T(""));
	}else{
	}
	//13.����Ч׼ҺŨ��6�ı��༭��
	if(item_count<=0){
		_concentration_6_edit->SetWindowText(_T(""));
	}else{
	}
	//14.����λ��1�ı��༭��
	if(item_count<=0){
		_position_1_edit->SetWindowText(_T(""));
	}else{
	}
	//15.����λ��2�ı��༭��
	if(item_count<=0){
		_position_2_edit->SetWindowText(_T(""));
	}else{
	}
	//16.����λ��3�ı��༭��
	if(item_count<=0){
		_position_3_edit->SetWindowText(_T(""));
	}else{
	}
	//17.����λ��4�ı��༭��
	if(item_count<=0){
		_position_4_edit->SetWindowText(_T(""));
	}else{
	}
	//18.����λ��5�ı��༭��
	if(item_count<=0){
		_position_5_edit->SetWindowText(_T(""));
	}else{
	}
	//19.����λ��6�ı��༭��
	if(item_count<=0){
		_position_6_edit->SetWindowText(_T(""));
	}else{
	}
	//20.�������������1�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_1_edit->SetWindowText(_T(""));
		_sample_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_1());
		_sample_volume_1_edit->SetWindowText(text);
		_sample_volume_1_edit->EnableWindow(TRUE);
	}
	//21.�������������2�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_2_edit->SetWindowText(_T(""));
		_sample_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_2());
		_sample_volume_2_edit->SetWindowText(text);
		_sample_volume_2_edit->EnableWindow(TRUE);
	}
	//22.�������������3�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_3_edit->SetWindowText(_T(""));
		_sample_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_3());
		_sample_volume_3_edit->SetWindowText(text);
		_sample_volume_3_edit->EnableWindow(TRUE);
	}
	//23.�������������4�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_4_edit->SetWindowText(_T(""));
		_sample_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_4());
		_sample_volume_4_edit->SetWindowText(text);
		_sample_volume_4_edit->EnableWindow(TRUE);
	}
	//24.�������������5�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_5_edit->SetWindowText(_T(""));
		_sample_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_5());
		_sample_volume_5_edit->SetWindowText(text);
		_sample_volume_5_edit->EnableWindow(TRUE);
	}
	//25.�������������6�ı��ı��༭��
	if(item_count<=0){
		_sample_volume_6_edit->SetWindowText(_T(""));
		_sample_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_6());
		_sample_volume_6_edit->SetWindowText(text);
		_sample_volume_6_edit->EnableWindow(TRUE);
	}
	//26.������ϡ�ͺ��������1�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_1_edit->SetWindowText(_T(""));
		_diluted_sample_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_1());
		_diluted_sample_volume_1_edit->SetWindowText(text);
		_diluted_sample_volume_1_edit->EnableWindow(TRUE);
	}
	//27.������ϡ�ͺ��������2�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_2_edit->SetWindowText(_T(""));
		_diluted_sample_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_2());
		_diluted_sample_volume_2_edit->SetWindowText(text);
		_diluted_sample_volume_2_edit->EnableWindow(TRUE);
	}
	//28.������ϡ�ͺ��������3�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_3_edit->SetWindowText(_T(""));
		_diluted_sample_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_3());
		_diluted_sample_volume_3_edit->SetWindowText(text);
		_diluted_sample_volume_3_edit->EnableWindow(TRUE);
	}
	//29.������ϡ�ͺ��������4�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_4_edit->SetWindowText(_T(""));
		_diluted_sample_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_4());
		_diluted_sample_volume_4_edit->SetWindowText(text);
		_diluted_sample_volume_4_edit->EnableWindow(TRUE);
	}
	//30.������ϡ�ͺ��������5�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_5_edit->SetWindowText(_T(""));
		_diluted_sample_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_5());
		_diluted_sample_volume_5_edit->SetWindowText(text);
		_diluted_sample_volume_5_edit->EnableWindow(TRUE);
	}
	//31.������ϡ�ͺ��������6�ı��༭��
	if(item_count<=0){
		_diluted_sample_volume_6_edit->SetWindowText(_T(""));
		_diluted_sample_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_6());
		_diluted_sample_volume_6_edit->SetWindowText(text);
		_diluted_sample_volume_6_edit->EnableWindow(TRUE);
	}
	//32.������ϡ��Һ���1�ı��༭��
	if(item_count<=0){
		_diluent_volume_1_edit->SetWindowText(_T(""));
		_diluent_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_1());
		_diluent_volume_1_edit->SetWindowText(text);
		_diluent_volume_1_edit->EnableWindow(TRUE);
	}
	//33.������ϡ��Һ���2�ı��༭��
	if(item_count<=0){
		_diluent_volume_2_edit->SetWindowText(_T(""));
		_diluent_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_2());
		_diluent_volume_2_edit->SetWindowText(text);
		_diluent_volume_2_edit->EnableWindow(TRUE);
	}
	//34.������ϡ��Һ���3�ı��༭��
	if(item_count<=0){
		_diluent_volume_3_edit->SetWindowText(_T(""));
		_diluent_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_3());
		_diluent_volume_3_edit->SetWindowText(text);
		_diluent_volume_3_edit->EnableWindow(TRUE);
	}
	//35.������ϡ��Һ���4�ı��༭��
	if(item_count<=0){
		_diluent_volume_4_edit->SetWindowText(_T(""));
		_diluent_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_4());
		_diluent_volume_4_edit->SetWindowText(text);
		_diluent_volume_4_edit->EnableWindow(TRUE);
	}
	//36.������ϡ��Һ���5�ı��༭��
	if(item_count<=0){
		_diluent_volume_5_edit->SetWindowText(_T(""));
		_diluent_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_5());
		_diluent_volume_5_edit->SetWindowText(text);
		_diluent_volume_5_edit->EnableWindow(TRUE);
	}
	//37.������ϡ��Һ���6�ı��༭��
	if(item_count<=0){
		_diluent_volume_6_edit->SetWindowText(_T(""));
		_diluent_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_6());
		_diluent_volume_6_edit->SetWindowText(text);
		_diluent_volume_6_edit->EnableWindow(TRUE);
	}
	//38.���á�ɾ������ť��
	if(item_count<=0){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//39.���á�ȷ�ϡ���ť��
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: �жϵ�ǰ�ؼ��е������Ƿ����ı䡣
 * param: --
 * return: �����ǰ�ؼ��е����ݷ����ı��򷵻�TRUE�����򷵻�FALSE��
 */
BOOL DialogStandardApplication::is_data_of_controls_changed() const{
	//1.��ȡ��ǰ������ָ����Ŀ��ʶ�����������Ϣ��
	Applications::PtrToCApp application=Applications::
		instance()->get_by_item_id(_item_id);
	if(!static_cast<bool>(application)){//���δ�ܻ�ȡָ��������Ϣ������Ϊ�ޱ仯��
		return(FALSE);
	}
	//2.��⵱ǰ��Ч׼Һ���1���ı��༭���Ƿ����仯��
	CString text(_T(""));
	_calibrator_code_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_1()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//3.��⵱ǰ��Ч׼Һ���2���ı��༭���Ƿ����仯��
	_calibrator_code_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_2()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//4.��⵱ǰ��Ч׼Һ���3���ı��༭���Ƿ����仯��
	_calibrator_code_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_3()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//5.��⵱ǰ��Ч׼Һ���4���ı��༭���Ƿ����仯��
	_calibrator_code_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_4()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//6.��⵱ǰ��Ч׼Һ���5���ı��༭���Ƿ����仯��
	_calibrator_code_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_5()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//7.��⵱ǰ��Ч׼Һ���6���ı��༭���Ƿ����仯��
	_calibrator_code_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_6()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//8.��⵱ǰ�����������1���ı��༭���Ƿ����仯��
	_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//9.��⵱ǰ�����������2���ı��༭���Ƿ����仯��
	_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//10.��⵱ǰ�����������3���ı��༭���Ƿ����仯��
	_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//11.��⵱ǰ�����������4���ı��༭���Ƿ����仯��
	_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//12.��⵱ǰ�����������5���ı��༭���Ƿ����仯��
	_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//13.��⵱ǰ�����������6���ı��༭���Ƿ����仯��
	_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//14.��⵱ǰ����ϡ�ͺ��������1���ı��༭���Ƿ����仯��
	_diluted_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//15.��⵱ǰ����ϡ�ͺ��������2���ı��༭���Ƿ����仯��
	_diluted_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//16.��⵱ǰ����ϡ�ͺ��������3���ı��༭���Ƿ����仯��
	_diluted_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//17.��⵱ǰ����ϡ�ͺ��������4���ı��༭���Ƿ����仯��
	_diluted_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//18.��⵱ǰ����ϡ�ͺ��������5���ı��༭���Ƿ����仯��
	_diluted_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//19.��⵱ǰ����ϡ�ͺ��������6���ı��༭���Ƿ����仯��
	_diluted_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//21.��⵱ǰ����ϡ��Һ���1���ı��༭���Ƿ����仯��
	_diluent_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//22.��⵱ǰ����ϡ��Һ���2���ı��༭���Ƿ����仯��
	_diluent_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//23.��⵱ǰ����ϡ��Һ���3���ı��༭���Ƿ����仯��
	_diluent_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//24.��⵱ǰ����ϡ��Һ���4���ı��༭���Ƿ����仯��
	_diluent_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//25.��⵱ǰ����ϡ��Һ���5���ı��༭���Ƿ����仯��
	_diluent_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//26.��⵱ǰ����ϡ��Һ���6���ı��༭���Ƿ����仯��
	_diluent_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//27�������е���ֱ�ӷ���FALSE��
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * brief: ��ȡ�ؼ��е����ݡ�
 * param: item_id - ���ص���Ŀ��ʶ��
 *        standard - ���صı�׼���������
 * return: �����ǰ����ִ�гɹ�������ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogStandardApplication::get_data_from_controls(
	int &item_id,StandardApplication &sandard){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ��Ŀ��ʶ��
	//int item=0/*_select_test_combo_box->GetCurSel()*/;
	/*
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING175),this);
		_select_test_combo_box->SetFocus();
		return(-1);
	}
	*/
	item_id=_item_id/*static_cast<int>(_select_test_combo_box->GetItemData(item))*/;
	//3.��ȡ��ǰЧ׼Һ���1��
	CString text(_T(""));
	_calibrator_code_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING456),this);
		_calibrator_code_1_edit->SetFocus();
		return(-2);
	}
	sandard.set_calibrator_code_1(MtCharacterSet::to_integer(text));
	//4.��ȡ��ǰЧ׼Һ���2��
	_calibrator_code_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING457),this);
		_calibrator_code_2_edit->SetFocus();
		return(-3);
	}
	sandard.set_calibrator_code_2(MtCharacterSet::to_integer(text));
	//5.��ȡ��ǰЧ׼Һ���3��
	_calibrator_code_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING458),this);
		_calibrator_code_3_edit->SetFocus();
		return(-4);
	}
	sandard.set_calibrator_code_3(MtCharacterSet::to_integer(text));
	//6.��ȡ��ǰЧ׼Һ���4��
	_calibrator_code_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING459),this);
		_calibrator_code_4_edit->SetFocus();
		return(-5);
	}
	sandard.set_calibrator_code_4(MtCharacterSet::to_integer(text));
	//7.��ȡ��ǰЧ׼Һ���5��
	_calibrator_code_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING460),this);
		_calibrator_code_5_edit->SetFocus();
		return(-6);
	}
	sandard.set_calibrator_code_5(MtCharacterSet::to_integer(text));
	//8.��ȡ��ǰЧ׼Һ���6��
	_calibrator_code_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING461),this);
		_calibrator_code_6_edit->SetFocus();
		return(-7);
	}
	sandard.set_calibrator_code_6(MtCharacterSet::to_integer(text));
	//9.��ȡ��ǰ���������1��
	_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING462),this);
		_sample_volume_1_edit->SetFocus();
		return(-8);
	}
	sandard.set_sample_volume_1(MtCharacterSet::to_decimals(text));
	//10.��ȡ��ǰ���������2��
	_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING463),this);
		_sample_volume_2_edit->SetFocus();
		return(-9);
	}
	sandard.set_sample_volume_2(MtCharacterSet::to_decimals(text));
	//11.��ȡ��ǰ���������3��
	_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING464),this);
		_sample_volume_3_edit->SetFocus();
		return(-10);
	}
	sandard.set_sample_volume_3(MtCharacterSet::to_decimals(text));
	//12.��ȡ��ǰ���������4��
	_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING465),this);
		_sample_volume_4_edit->SetFocus();
		return(-11);
	}
	sandard.set_sample_volume_4(MtCharacterSet::to_decimals(text));
	//13.��ȡ��ǰ���������5��
	_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING466),this);
		_sample_volume_5_edit->SetFocus();
		return(-12);
	}
	sandard.set_sample_volume_5(MtCharacterSet::to_decimals(text));
	//14.��ȡ��ǰ���������6��
	_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING467),this);
		_sample_volume_6_edit->SetFocus();
		return(-13);
	}
	sandard.set_sample_volume_6(MtCharacterSet::to_decimals(text));
	//15.��ȡ��ǰ��ϡ�ͺ��������1��
	_diluted_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING468),this);
		_diluted_sample_volume_1_edit->SetFocus();
		return(-14);
	}
	sandard.set_diluted_sample_volume_1(MtCharacterSet::to_decimals(text));
	//16.��ȡ��ǰ��ϡ�ͺ��������2��
	_diluted_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING469),this);
		_diluted_sample_volume_2_edit->SetFocus();
		return(-15);
	}
	sandard.set_diluted_sample_volume_2(MtCharacterSet::to_decimals(text));
	//17.��ȡ��ǰ��ϡ�ͺ��������3��
	_diluted_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING470),this);
		_diluted_sample_volume_3_edit->SetFocus();
		return(-16);
	}
	sandard.set_diluted_sample_volume_3(MtCharacterSet::to_decimals(text));
	//18.��ȡ��ǰ��ϡ�ͺ��������4��
	_diluted_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING471),this);
		_diluted_sample_volume_4_edit->SetFocus();
		return(-17);
	}
	sandard.set_diluted_sample_volume_4(MtCharacterSet::to_decimals(text));
	//19.��ȡ��ǰ��ϡ�ͺ��������5��
	_diluted_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING472),this);
		_diluted_sample_volume_5_edit->SetFocus();
		return(-18);
	}
	sandard.set_diluted_sample_volume_5(MtCharacterSet::to_decimals(text));
	//20.��ȡ��ǰ��ϡ�ͺ��������6��
	_diluted_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING473),this);
		_diluted_sample_volume_6_edit->SetFocus();
		return(-19);
	}
	sandard.set_diluted_sample_volume_6(MtCharacterSet::to_decimals(text));
	//21.��ȡ��ǰ��ϡ��Һ���1��
	_diluent_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING474),this);
		_diluent_volume_1_edit->SetFocus();
		return(-20);
	}
	sandard.set_diluent_volume_1(MtCharacterSet::to_decimals(text));
	//22.��ȡ��ǰ��ϡ��Һ���2��
	_diluent_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING475),this);
		_diluent_volume_2_edit->SetFocus();
		return(-21);
	}
	sandard.set_diluent_volume_2(MtCharacterSet::to_decimals(text));
	//23.��ȡ��ǰ��ϡ��Һ���3��
	_diluent_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING476),this);
		_diluent_volume_3_edit->SetFocus();
		return(-22);
	}
	sandard.set_diluent_volume_3(MtCharacterSet::to_decimals(text));
	//24.��ȡ��ǰ��ϡ��Һ���4��
	_diluent_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING477),this);
		_diluent_volume_4_edit->SetFocus();
		return(-23);
	}
	sandard.set_diluent_volume_4(MtCharacterSet::to_decimals(text));
	//25.��ȡ��ǰ��ϡ��Һ���5��
	_diluent_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING478),this);
		_diluent_volume_5_edit->SetFocus();
		return(-24);
	}
	sandard.set_diluent_volume_5(MtCharacterSet::to_decimals(text));
	//26.��ȡ��ǰ��ϡ��Һ���6��
	_diluent_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING479),this);
		_diluent_volume_6_edit->SetFocus();
		return(-25);
	}
	sandard.set_diluent_volume_6(MtCharacterSet::to_decimals(text));
	//27.�����ǰ��׼�������Ϸ�����ֱ�ӷ��ش���
	//27-1.�жϵ�ǰ��׼�����Ƿ�Ϸ���
	const int result=sandard.is_valid(&text);
	//27-2.�����ǰ��׼�������Ϸ���������û����沢���ش���
	if(result<0){
		WarningMessageBox(text,this);
		if(-1==result){
			_calibrator_code_1_edit->SetFocus();
		}else if(-2==result){
			_calibrator_code_2_edit->SetFocus();
		}else if(-3==result){
			_calibrator_code_3_edit->SetFocus();
		}else if(-4==result){
			_calibrator_code_4_edit->SetFocus();
		}else if(-5==result){
			_calibrator_code_5_edit->SetFocus();
		}else if(-6==result){
			_calibrator_code_6_edit->SetFocus();
		}else if(-7==result){
			_sample_volume_1_edit->SetFocus();
		}else if(-8==result){
			_diluted_sample_volume_1_edit->SetFocus();
		}else if(-9==result){
			_diluent_volume_1_edit->SetFocus();
		}else if(-10==result){
			_sample_volume_2_edit->SetFocus();
		}else if(-11==result){
			_diluted_sample_volume_2_edit->SetFocus();
		}else if(-12==result){
			_diluent_volume_2_edit->SetFocus();
		}else if(-13==result){
			_sample_volume_3_edit->SetFocus();
		}else if(-14==result){
			_diluted_sample_volume_3_edit->SetFocus();
		}else if(-15==result){
			_diluent_volume_3_edit->SetFocus();
		}else if(-16==result){
			_sample_volume_4_edit->SetFocus();
		}else if(-17==result){
			_diluted_sample_volume_4_edit->SetFocus();
		}else if(-18==result){
			_diluent_volume_4_edit->SetFocus();
		}else if(-19==result){
			_sample_volume_5_edit->SetFocus();
		}else if(-20==result){
			_diluted_sample_volume_5_edit->SetFocus();
		}else if(-21==result){
			_diluent_volume_5_edit->SetFocus();
		}else if(-22==result){
			_sample_volume_6_edit->SetFocus();
		}else if(-23==result){
			_diluted_sample_volume_6_edit->SetFocus();
		}else if(-24==result){
			_diluent_volume_6_edit->SetFocus();
		}
		return(-26);
	}
	//28.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: �ύ�ؼ������ݵ�ָ�������ݿ��С�
 * param: database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogStandardApplication::commit_data_of_controls(Database &database){
	//1.������ǰ�������������
	int item_id=0;
	StandardApplication standard;
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ��������������ݡ�
	if(get_data_from_controls(item_id,standard)<0){
		return(-1);
	}
	//3.�����ݿ��ύ�޸ĵ����ݣ������ж��ύ�Ƿ�ɹ���
	if(Applications::instance()->commit(
		item_id,standard,database)<0){
		ErrorMessageBox(theme->get_string(158),this);
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}