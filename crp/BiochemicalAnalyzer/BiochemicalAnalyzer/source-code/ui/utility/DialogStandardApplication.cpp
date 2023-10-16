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
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
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
 * brief: 析构函数。
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
 * brief: 支持DDX/DDV。
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
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogStandardApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.初始化当前对话框中控件。
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);// return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: OnCommand
 * brief: 命令消息处理虚拟函数。这里用来拦截控件数据改变消息，
 *        并做出相应的更改。
 * param: wParam - 命令消息类型（高十六位），以及控件ID（低十六位）。
 *        lParam - 未使用。
 * return: --
 */
BOOL DialogStandardApplication::OnCommand(WPARAM wParam,LPARAM lParam){
	//TODO: Add your specialized code here and/or call the base class
	/////////////////////////////////////////////////////////////////
	//1.如果当前是文本编辑框内容或下拉框选择内容改变命令消息。
	if((!_is_command_message_masked)&&((
		EN_CHANGE==HIWORD(wParam))||(
		CBN_SELCHANGE==HIWORD(wParam)))){
		//1-1.如果当前界面控件内容改变。
		if(is_data_of_controls_changed()){
			_ok_button->EnableWindow(TRUE);
		}
		//1-2.如果当前界面控件内容未改变。
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
 * brief: 对话框尺寸调整消息响应函数，此处用来
 *        更新对话框中布局信息。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogStandardApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: “选择项目”下拉框项目变更消息响应函数。
 * param: --
 * return: --
 */
void DialogStandardApplication::OnCbnSelchangeComboSelectTest(){
	//TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.获取当前用户选择的项目标识。
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
	//3.如果用户选择的项目标识，与当前项目标识相同，则直接返回。
	if(item_id==_item_id){
		return;
	}
	//4.如果当前输入的参数发生改变。
	if(is_data_of_controls_changed()){
		//4-1.提问用户是否保存当前参数。
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING480),this);
		//4-2.如果当前用户选择“取消”按钮。
		if(IDCANCEL==result){
			//4-1-1.屏蔽控件数据的更新。
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.回复当前下拉框选择内容。
			_select_test_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_item_id,*_select_test_combo_box));
			//4-1-3.程序运行到此直接返回。
			return;
		}
		//4-3.如果当前用户选择“否”按钮。
		else if(IDNO==result){
		}
		//4-4.如果当前用户选择“是”按钮。
		else{
			if(commit_data_of_controls(*((DatabaseManager::instance())->
				get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){//提交控件中的数据。
				//4-4-1.屏蔽控件数据的更新。
				MtAutoReset<BOOL> auto_reset(
					_is_command_message_masked,TRUE,FALSE);
				//4-4-2.回复当前下拉框选择内容。
				_select_test_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_item_id,*_select_test_combo_box));
				//4-4-3.程序运行到此直接返回。
				return;
			}
		}
	}
	//5.显示新选择的项目的申请参数信息。
	GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		static_cast<WPARAM>(item_id),0);
}

/**
 * name: OnBnClickedButtonDelete
 * brief: 用户点击“删除”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogStandardApplication::OnBnClickedButtonDelete(){
	// TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	Applications *applications=Applications::instance();
	//2.获取当前期望删除的项目标识。
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING481),this);
		return;
	}
	const int item_id=static_cast<int>(_select_test_combo_box->GetItemData(item));
	//3.询问用户是否期望删除当前项目。
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING482),this)){
		return;
	}
	//4.删除当前项目，并且判断删除是否成功。
	if(applications->remove(item_id,*((DatabaseManager::instance())->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)))<0){
		ErrorMessageBox(theme->get_string(IDS_STRING158),this);
		return;
	}
	//5.当前项目删除后，显示最小项目标识的项目申请参数。
	//5-1.对当前的项目申请参数进行排序。
	applications->sort_by_item_id();
	//5-2.获取最小项目标识的项目申请参数。
	Applications::PtrToCApp application=applications->get_by_index(0);
	//5-3.如果获取成功。
	if(static_cast<bool>(application)){
		GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
			static_cast<WPARAM>((application->get_item()).get_id()),0);
	}
	//5-4.如果获取失败。
	else{
		GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
			static_cast<WPARAM>(0),0);
	}
}

/**
 * name: OnBnClickedButtonOk
 * brief: 用户点击“确定”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogStandardApplication::OnBnClickedButtonOk(){
	// TODO: Add your control notification handler code here
	//1.提交当前界面中控件数据。
	if(commit_data_of_controls(*((DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){
		return;
	}
	//2.屏蔽OnCommand响应。
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//3.更新当前界面中控件数据。
	update_data_for_controls(_item_id);
}

/**
 * name: OnUpdateDataForControlsByItemID
 * brief: 通过项目标识更新界面控件数据。
 * param: wParam - 项目标识。
 *        lParam - 无意义。
 * return: 此函数一直返回零。
 */
LRESULT DialogStandardApplication::OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM /*lParam*/){
	//1.屏蔽当前界面命令消息响应。
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.更新当前界面控件数据。
	update_data_for_controls(static_cast<int>(wParam));
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: OnCommitDataOfControls
 * brief: 提交当前控件中的数据到数据库中消息响应函数。
 * param: wParam - 无意义。
 *        lParam - 无意义。
 * return: 如果函数执行成功返回零，否则返回非零。
 */
LRESULT DialogStandardApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.如果界面中的数据没有发生变化，则直接返回。
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.询问用户是否希望保存当前数据。
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING483),this);
	//3.如果当前用户点击了“取消”按钮。
	if(IDCANCEL==result){
		return(1);
	}
	//4.如果当前用户点击了“否”按钮。
	else if(IDNO==result){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		update_data_for_controls(_item_id);
		return(0);
	}
	//5.如果当前用户点击了“是”按钮。
	else{
		//5-1.保存当前控件数据到指定的数据库中。
		if(commit_data_of_controls(*((DatabaseManager::instance())->
			get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){
			return(2);
		}
		//5-2.屏蔽OnCommand的调用。
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		//5-3.如果当前控件数据保存成功，更新界面数据。
		update_data_for_controls(_item_id);
		//5-4.程序运行到此成功返回。
		return(0);
	}
}

/**
 * name: init_controls
 * brief: 初始化界面中控件。
 * param: --
 * return: --
 */
void DialogStandardApplication::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.初始化当前对话框中控件。
	//2-1.初始化静态文本框。
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
	//2-2.初始化下拉框。
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
	//2-3.初始化文本编辑框。
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
	//2-4.初始化按钮。
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化当前对话框中布局。
	//3-1.初始化子布局1。
	_child_layout_1->add_fixed_window(_select_test_static,200);
	_child_layout_1->add_fixed_window(_select_test_combo_box,150);
	//3-2.初始化子布局2。
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
	//3-3.初始化子布局3。
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
	//3-4.初始化子布局4。
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
	//3-5.初始化子布局5。
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
	//3-6.初始化子布局6。
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
	//3-7.初始化子布局7。
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
	//3-8.初始化子布局8。
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
	//3-9.初始化子布局9。
	_child_layout_9->add_fixed_window(_delete_button,200);
	_child_layout_9->add_stretch(1);
	_child_layout_9->add_fixed_window(_ok_button,200);
	_child_layout_9->add_stretch(1);
	//3-10.初始化主布局。
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
	//4.重置当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//5.更新当前界面中控件数据。
	update_data_for_controls(0);
}

/**
 * name: update_data_for_controls
 * brief: 将指定项目标识的申请参数信息更新到控件上。
 * param: item_id - 指定的项目标识。
 * return: --
 * remark: 当item_id小于等于零时，此函数默认显示据有最小项目标识的项目的申请参数。
 */
void DialogStandardApplication::update_data_for_controls(const int item_id/*=0*/){
	//1.将当前的项目项目信息存储到“选择项目”的下拉框中。
	//1-1.将当前下拉框中所有信息一一清除。
	for(int index=_select_test_combo_box->GetCount()-1;index>=0;--index){
		_select_test_combo_box->DeleteString(index);
	}
	//1-2.将当前系统中的项目信息按项目标识排序。
	Applications *applications=Applications::instance();
	applications->sort_by_item_id();
	//1-3.获取当前系统中的项目信息，并将信息插入到“选择项目”下拉框中。
	int item=0;
	for(unsigned int index=0;index<applications->get_size();++index){
		//1-3-1.获取当前系统中指定的项目信息。
		Applications::PtrToCApp application=applications->get_by_index(index);
		//1-3-2.如果获取当前系统中指定的项目信息失败。
		if(!static_cast<bool>(application)){
			continue;
		}
		//1-3-3.将当前的项目信息，插入到“选择项目”下拉框中。
		item=_select_test_combo_box->AddString((
			application->get_item()).get_name());
		_select_test_combo_box->SetItemData(item,static_cast<
			DWORD_PTR>((application->get_item()).get_id()));
	}
	//1-4.根据系统中存储的项目申请信息，更新当前“项目选择”下拉框数据。
	//1-4-1.声明当前操作所需变量。
	int item_count=_select_test_combo_box->GetCount();
	Applications::PtrToCApp application;
	//1-4-2.如果当前下拉框内容为空。
	if(item_count<=0){
		_select_test_combo_box->SetCurSel(-1);
		_select_test_combo_box->EnableWindow(FALSE);
		_item_id=0;
	}
	//1-4-3.如果当前未指定期望显示的项目标识，则显示最小的项目标识。
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
	//1-4-4.如果当前指定了期望显示的项目标识。
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
	//2.设置效准液编号1文本编辑框。
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
	//3.设置效准液编号2文本编辑框。
	if(item_count<=0){
		_calibrator_code_2_edit->SetWindowText(_T(""));
		_calibrator_code_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_2());
		_calibrator_code_2_edit->SetWindowText(text);
		_calibrator_code_2_edit->EnableWindow(TRUE);
	}
	//4.设置效准液编号3文本编辑框。
	if(item_count<=0){
		_calibrator_code_3_edit->SetWindowText(_T(""));
		_calibrator_code_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_3());
		_calibrator_code_3_edit->SetWindowText(text);
		_calibrator_code_3_edit->EnableWindow(TRUE);
	}
	//5.设置效准液编号4文本编辑框。
	if(item_count<=0){
		_calibrator_code_4_edit->SetWindowText(_T(""));
		_calibrator_code_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_4());
		_calibrator_code_4_edit->SetWindowText(text);
		_calibrator_code_4_edit->EnableWindow(TRUE);
	}
	//6.设置效准液编号5文本编辑框。
	if(item_count<=0){
		_calibrator_code_5_edit->SetWindowText(_T(""));
		_calibrator_code_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_5());
		_calibrator_code_5_edit->SetWindowText(text);
		_calibrator_code_5_edit->EnableWindow(TRUE);
	}
	//7.设置效准液编号6文本编辑框。
	if(item_count<=0){
		_calibrator_code_6_edit->SetWindowText(_T(""));
		_calibrator_code_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),(application->get_standard()).
			get_calibrator_code_6());
		_calibrator_code_6_edit->SetWindowText(text);
		_calibrator_code_6_edit->EnableWindow(TRUE);
	}
	//8.设置效准液浓度1文本编辑框。
	if(item_count<=0){
		_concentration_1_edit->SetWindowText(_T(""));
	}else{
	}
	//9.设置效准液浓度2文本编辑框。
	if(item_count<=0){
		_concentration_2_edit->SetWindowText(_T(""));
	}else{
	}
	//10.设置效准液浓度3文本编辑框。
	if(item_count<=0){
		_concentration_3_edit->SetWindowText(_T(""));
	}else{
	}
	//11.设置效准液浓度4文本编辑框。
	if(item_count<=0){
		_concentration_4_edit->SetWindowText(_T(""));
	}else{
	}
	//12.设置效准液浓度5文本编辑框。
	if(item_count<=0){
		_concentration_5_edit->SetWindowText(_T(""));
	}else{
	}
	//13.设置效准液浓度6文本编辑框。
	if(item_count<=0){
		_concentration_6_edit->SetWindowText(_T(""));
	}else{
	}
	//14.设置位置1文本编辑框。
	if(item_count<=0){
		_position_1_edit->SetWindowText(_T(""));
	}else{
	}
	//15.设置位置2文本编辑框。
	if(item_count<=0){
		_position_2_edit->SetWindowText(_T(""));
	}else{
	}
	//16.设置位置3文本编辑框。
	if(item_count<=0){
		_position_3_edit->SetWindowText(_T(""));
	}else{
	}
	//17.设置位置4文本编辑框。
	if(item_count<=0){
		_position_4_edit->SetWindowText(_T(""));
	}else{
	}
	//18.设置位置5文本编辑框。
	if(item_count<=0){
		_position_5_edit->SetWindowText(_T(""));
	}else{
	}
	//19.设置位置6文本编辑框。
	if(item_count<=0){
		_position_6_edit->SetWindowText(_T(""));
	}else{
	}
	//20.设置吸样本体积1文本文本编辑框。
	if(item_count<=0){
		_sample_volume_1_edit->SetWindowText(_T(""));
		_sample_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_1());
		_sample_volume_1_edit->SetWindowText(text);
		_sample_volume_1_edit->EnableWindow(TRUE);
	}
	//21.设置吸样本体积2文本文本编辑框。
	if(item_count<=0){
		_sample_volume_2_edit->SetWindowText(_T(""));
		_sample_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_2());
		_sample_volume_2_edit->SetWindowText(text);
		_sample_volume_2_edit->EnableWindow(TRUE);
	}
	//22.设置吸样本体积3文本文本编辑框。
	if(item_count<=0){
		_sample_volume_3_edit->SetWindowText(_T(""));
		_sample_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_3());
		_sample_volume_3_edit->SetWindowText(text);
		_sample_volume_3_edit->EnableWindow(TRUE);
	}
	//23.设置吸样本体积4文本文本编辑框。
	if(item_count<=0){
		_sample_volume_4_edit->SetWindowText(_T(""));
		_sample_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_4());
		_sample_volume_4_edit->SetWindowText(text);
		_sample_volume_4_edit->EnableWindow(TRUE);
	}
	//24.设置吸样本体积5文本文本编辑框。
	if(item_count<=0){
		_sample_volume_5_edit->SetWindowText(_T(""));
		_sample_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_5());
		_sample_volume_5_edit->SetWindowText(text);
		_sample_volume_5_edit->EnableWindow(TRUE);
	}
	//25.设置吸样本体积6文本文本编辑框。
	if(item_count<=0){
		_sample_volume_6_edit->SetWindowText(_T(""));
		_sample_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_sample_volume_6());
		_sample_volume_6_edit->SetWindowText(text);
		_sample_volume_6_edit->EnableWindow(TRUE);
	}
	//26.设置吸稀释后样本体积1文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_1_edit->SetWindowText(_T(""));
		_diluted_sample_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_1());
		_diluted_sample_volume_1_edit->SetWindowText(text);
		_diluted_sample_volume_1_edit->EnableWindow(TRUE);
	}
	//27.设置吸稀释后样本体积2文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_2_edit->SetWindowText(_T(""));
		_diluted_sample_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_2());
		_diluted_sample_volume_2_edit->SetWindowText(text);
		_diluted_sample_volume_2_edit->EnableWindow(TRUE);
	}
	//28.设置吸稀释后样本体积3文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_3_edit->SetWindowText(_T(""));
		_diluted_sample_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_3());
		_diluted_sample_volume_3_edit->SetWindowText(text);
		_diluted_sample_volume_3_edit->EnableWindow(TRUE);
	}
	//29.设置吸稀释后样本体积4文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_4_edit->SetWindowText(_T(""));
		_diluted_sample_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_4());
		_diluted_sample_volume_4_edit->SetWindowText(text);
		_diluted_sample_volume_4_edit->EnableWindow(TRUE);
	}
	//30.设置吸稀释后样本体积5文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_5_edit->SetWindowText(_T(""));
		_diluted_sample_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_5());
		_diluted_sample_volume_5_edit->SetWindowText(text);
		_diluted_sample_volume_5_edit->EnableWindow(TRUE);
	}
	//31.设置吸稀释后样本体积6文本编辑框。
	if(item_count<=0){
		_diluted_sample_volume_6_edit->SetWindowText(_T(""));
		_diluted_sample_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluted_sample_volume_6());
		_diluted_sample_volume_6_edit->SetWindowText(text);
		_diluted_sample_volume_6_edit->EnableWindow(TRUE);
	}
	//32.设置吸稀释液体积1文本编辑框。
	if(item_count<=0){
		_diluent_volume_1_edit->SetWindowText(_T(""));
		_diluent_volume_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_1());
		_diluent_volume_1_edit->SetWindowText(text);
		_diluent_volume_1_edit->EnableWindow(TRUE);
	}
	//33.设置吸稀释液体积2文本编辑框。
	if(item_count<=0){
		_diluent_volume_2_edit->SetWindowText(_T(""));
		_diluent_volume_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_2());
		_diluent_volume_2_edit->SetWindowText(text);
		_diluent_volume_2_edit->EnableWindow(TRUE);
	}
	//34.设置吸稀释液体积3文本编辑框。
	if(item_count<=0){
		_diluent_volume_3_edit->SetWindowText(_T(""));
		_diluent_volume_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_3());
		_diluent_volume_3_edit->SetWindowText(text);
		_diluent_volume_3_edit->EnableWindow(TRUE);
	}
	//35.设置吸稀释液体积4文本编辑框。
	if(item_count<=0){
		_diluent_volume_4_edit->SetWindowText(_T(""));
		_diluent_volume_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_4());
		_diluent_volume_4_edit->SetWindowText(text);
		_diluent_volume_4_edit->EnableWindow(TRUE);
	}
	//36.设置吸稀释液体积5文本编辑框。
	if(item_count<=0){
		_diluent_volume_5_edit->SetWindowText(_T(""));
		_diluent_volume_5_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_5());
		_diluent_volume_5_edit->SetWindowText(text);
		_diluent_volume_5_edit->EnableWindow(TRUE);
	}
	//37.设置吸稀释液体积6文本编辑框。
	if(item_count<=0){
		_diluent_volume_6_edit->SetWindowText(_T(""));
		_diluent_volume_6_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.1lf"),(application->get_standard()).
			get_diluent_volume_6());
		_diluent_volume_6_edit->SetWindowText(text);
		_diluent_volume_6_edit->EnableWindow(TRUE);
	}
	//38.设置“删除”按钮。
	if(item_count<=0){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//39.设置“确认”按钮。
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: 判断当前控件中的数据是否发生改变。
 * param: --
 * return: 如果当前控件中的数据发生改变则返回TRUE，否则返回FALSE。
 */
BOOL DialogStandardApplication::is_data_of_controls_changed() const{
	//1.获取当前界面中指定项目标识的申请参数信息。
	Applications::PtrToCApp application=Applications::
		instance()->get_by_item_id(_item_id);
	if(!static_cast<bool>(application)){//如果未能获取指定参数信息，则认为无变化。
		return(FALSE);
	}
	//2.检测当前“效准液编号1”文本编辑框是否发生变化。
	CString text(_T(""));
	_calibrator_code_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_1()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//3.检测当前“效准液编号2”文本编辑框是否发生变化。
	_calibrator_code_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_2()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//4.检测当前“效准液编号3”文本编辑框是否发生变化。
	_calibrator_code_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_3()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//5.检测当前“效准液编号4”文本编辑框是否发生变化。
	_calibrator_code_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_4()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//6.检测当前“效准液编号5”文本编辑框是否发生变化。
	_calibrator_code_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_5()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//7.检测当前“效准液编号6”文本编辑框是否发生变化。
	_calibrator_code_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_standard()).
		get_calibrator_code_6()!=MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//8.检测当前“吸样本体积1”文本编辑框是否发生变化。
	_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//9.检测当前“吸样本体积2”文本编辑框是否发生变化。
	_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//10.检测当前“吸样本体积3”文本编辑框是否发生变化。
	_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//11.检测当前“吸样本体积4”文本编辑框是否发生变化。
	_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//12.检测当前“吸样本体积5”文本编辑框是否发生变化。
	_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//13.检测当前“吸样本体积6”文本编辑框是否发生变化。
	_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_sample_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//14.检测当前“吸稀释后样本体积1”文本编辑框是否发生变化。
	_diluted_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//15.检测当前“吸稀释后样本体积2”文本编辑框是否发生变化。
	_diluted_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//16.检测当前“吸稀释后样本体积3”文本编辑框是否发生变化。
	_diluted_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//17.检测当前“吸稀释后样本体积4”文本编辑框是否发生变化。
	_diluted_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//18.检测当前“吸稀释后样本体积5”文本编辑框是否发生变化。
	_diluted_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//19.检测当前“吸稀释后样本体积6”文本编辑框是否发生变化。
	_diluted_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluted_sample_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//21.检测当前“吸稀释液体积1”文本编辑框是否发生变化。
	_diluent_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//22.检测当前“吸稀释液体积2”文本编辑框是否发生变化。
	_diluent_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//23.检测当前“吸稀释液体积3”文本编辑框是否发生变化。
	_diluent_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_3()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//24.检测当前“吸稀释液体积4”文本编辑框是否发生变化。
	_diluent_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_4()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//25.检测当前“吸稀释液体积5”文本编辑框是否发生变化。
	_diluent_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_5()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//26.检测当前“吸稀释液体积6”文本编辑框是否发生变化。
	_diluent_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_standard()).get_diluent_volume_6()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//27程序运行到此直接返回FALSE。
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * brief: 获取控件中的数据。
 * param: item_id - 返回的项目标识。
 *        standard - 返回的标准申请参数。
 * return: 如果当前函数执行成功，返回值大于等于零，否则返回值小于零。
 */
int DialogStandardApplication::get_data_from_controls(
	int &item_id,StandardApplication &sandard){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.获取当前项目标识。
	//int item=0/*_select_test_combo_box->GetCurSel()*/;
	/*
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING175),this);
		_select_test_combo_box->SetFocus();
		return(-1);
	}
	*/
	item_id=_item_id/*static_cast<int>(_select_test_combo_box->GetItemData(item))*/;
	//3.获取当前效准液编号1。
	CString text(_T(""));
	_calibrator_code_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING456),this);
		_calibrator_code_1_edit->SetFocus();
		return(-2);
	}
	sandard.set_calibrator_code_1(MtCharacterSet::to_integer(text));
	//4.获取当前效准液编号2。
	_calibrator_code_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING457),this);
		_calibrator_code_2_edit->SetFocus();
		return(-3);
	}
	sandard.set_calibrator_code_2(MtCharacterSet::to_integer(text));
	//5.获取当前效准液编号3。
	_calibrator_code_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING458),this);
		_calibrator_code_3_edit->SetFocus();
		return(-4);
	}
	sandard.set_calibrator_code_3(MtCharacterSet::to_integer(text));
	//6.获取当前效准液编号4。
	_calibrator_code_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING459),this);
		_calibrator_code_4_edit->SetFocus();
		return(-5);
	}
	sandard.set_calibrator_code_4(MtCharacterSet::to_integer(text));
	//7.获取当前效准液编号5。
	_calibrator_code_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING460),this);
		_calibrator_code_5_edit->SetFocus();
		return(-6);
	}
	sandard.set_calibrator_code_5(MtCharacterSet::to_integer(text));
	//8.获取当前效准液编号6。
	_calibrator_code_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING461),this);
		_calibrator_code_6_edit->SetFocus();
		return(-7);
	}
	sandard.set_calibrator_code_6(MtCharacterSet::to_integer(text));
	//9.获取当前吸样本体积1。
	_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING462),this);
		_sample_volume_1_edit->SetFocus();
		return(-8);
	}
	sandard.set_sample_volume_1(MtCharacterSet::to_decimals(text));
	//10.获取当前吸样本体积2。
	_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING463),this);
		_sample_volume_2_edit->SetFocus();
		return(-9);
	}
	sandard.set_sample_volume_2(MtCharacterSet::to_decimals(text));
	//11.获取当前吸样本体积3。
	_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING464),this);
		_sample_volume_3_edit->SetFocus();
		return(-10);
	}
	sandard.set_sample_volume_3(MtCharacterSet::to_decimals(text));
	//12.获取当前吸样本体积4。
	_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING465),this);
		_sample_volume_4_edit->SetFocus();
		return(-11);
	}
	sandard.set_sample_volume_4(MtCharacterSet::to_decimals(text));
	//13.获取当前吸样本体积5。
	_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING466),this);
		_sample_volume_5_edit->SetFocus();
		return(-12);
	}
	sandard.set_sample_volume_5(MtCharacterSet::to_decimals(text));
	//14.获取当前吸样本体积6。
	_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING467),this);
		_sample_volume_6_edit->SetFocus();
		return(-13);
	}
	sandard.set_sample_volume_6(MtCharacterSet::to_decimals(text));
	//15.获取当前吸稀释后样本体积1。
	_diluted_sample_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING468),this);
		_diluted_sample_volume_1_edit->SetFocus();
		return(-14);
	}
	sandard.set_diluted_sample_volume_1(MtCharacterSet::to_decimals(text));
	//16.获取当前吸稀释后样本体积2。
	_diluted_sample_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING469),this);
		_diluted_sample_volume_2_edit->SetFocus();
		return(-15);
	}
	sandard.set_diluted_sample_volume_2(MtCharacterSet::to_decimals(text));
	//17.获取当前吸稀释后样本体积3。
	_diluted_sample_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING470),this);
		_diluted_sample_volume_3_edit->SetFocus();
		return(-16);
	}
	sandard.set_diluted_sample_volume_3(MtCharacterSet::to_decimals(text));
	//18.获取当前吸稀释后样本体积4。
	_diluted_sample_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING471),this);
		_diluted_sample_volume_4_edit->SetFocus();
		return(-17);
	}
	sandard.set_diluted_sample_volume_4(MtCharacterSet::to_decimals(text));
	//19.获取当前吸稀释后样本体积5。
	_diluted_sample_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING472),this);
		_diluted_sample_volume_5_edit->SetFocus();
		return(-18);
	}
	sandard.set_diluted_sample_volume_5(MtCharacterSet::to_decimals(text));
	//20.获取当前吸稀释后样本体积6。
	_diluted_sample_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING473),this);
		_diluted_sample_volume_6_edit->SetFocus();
		return(-19);
	}
	sandard.set_diluted_sample_volume_6(MtCharacterSet::to_decimals(text));
	//21.获取当前吸稀释液体积1。
	_diluent_volume_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING474),this);
		_diluent_volume_1_edit->SetFocus();
		return(-20);
	}
	sandard.set_diluent_volume_1(MtCharacterSet::to_decimals(text));
	//22.获取当前吸稀释液体积2。
	_diluent_volume_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING475),this);
		_diluent_volume_2_edit->SetFocus();
		return(-21);
	}
	sandard.set_diluent_volume_2(MtCharacterSet::to_decimals(text));
	//23.获取当前吸稀释液体积3。
	_diluent_volume_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING476),this);
		_diluent_volume_3_edit->SetFocus();
		return(-22);
	}
	sandard.set_diluent_volume_3(MtCharacterSet::to_decimals(text));
	//24.获取当前吸稀释液体积4。
	_diluent_volume_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING477),this);
		_diluent_volume_4_edit->SetFocus();
		return(-23);
	}
	sandard.set_diluent_volume_4(MtCharacterSet::to_decimals(text));
	//25.获取当前吸稀释液体积5。
	_diluent_volume_5_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING478),this);
		_diluent_volume_5_edit->SetFocus();
		return(-24);
	}
	sandard.set_diluent_volume_5(MtCharacterSet::to_decimals(text));
	//26.获取当前吸稀释液体积6。
	_diluent_volume_6_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING479),this);
		_diluent_volume_6_edit->SetFocus();
		return(-25);
	}
	sandard.set_diluent_volume_6(MtCharacterSet::to_decimals(text));
	//27.如果当前标准参数不合法，则直接返回错误。
	//27-1.判断当前标准参数是否合法。
	const int result=sandard.is_valid(&text);
	//27-2.如果当前标准参数不合法，则给予用户警告并返回错误。
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
	//28.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: 提交控件的数据到指定的数据库中。
 * param: database - 指定的数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DialogStandardApplication::commit_data_of_controls(Database &database){
	//1.声明当前操作所需变量。
	int item_id=0;
	StandardApplication standard;
	Theme *theme=Theme::instance();
	//2.获取当前界面中输入的数据。
	if(get_data_from_controls(item_id,standard)<0){
		return(-1);
	}
	//3.向数据库提交修改的数据，并且判断提交是否成功。
	if(Applications::instance()->commit(
		item_id,standard,database)<0){
		ErrorMessageBox(theme->get_string(158),this);
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}