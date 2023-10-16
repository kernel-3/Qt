//source-code/ui/utility/DialogAnalyzeApplication.cpp: implementation file
//

#include"stdafx.h"
#include"DialogAnalyzeApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/control/MtImageComboBox.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"DialogAddApplication.h"
#include"../../data/utility/Applications.h"
#include"../../data/utility/Application.h"
#include"../../data/common/Item.h"
#include"../../global/DatabaseManager.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../data/utility/AnalyzeApplication.h"
#include"../UiCustom.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoReset.h"
#include"../../data/DataCustom.h"
#include"../common/DialogMessageBox.h"
#include"../../data/utility/AnalyzeApplication.h"
#include"../../data/common/Module.h"
#include"../../data/common/Modules.h"
#include"../../data/common/SpecimenType.h"
#include"../../data/common/SpecimenTypes.h"
#include"../../data/common/AnalysisMethod.h"
#include"../../data/common/AnalysisMethods.h"
#include"../../data/common/DilutionMethod.h"
#include"../../data/common/DilutionMethods.h"
#include"../../data/common/Item.h"
#include"../../data/common/Items.h"
#include"../../data/utility/ApplicationParameter.h"
#include"../../data/utility/ApplicationParameters.h"
#include"../../data/utility/ApplicationAnalysisData.h"
#include<assert.h>
#include<functional>

//DialogAnalyzeApplication dialog
IMPLEMENT_DYNAMIC(DialogAnalyzeApplication,DialogPageBase)

/**
 * name: DialogAnalyzeApplication
 * brief: 构造函数。
 * param: pParent - 指向父窗口。
 * return: --
 */
DialogAnalyzeApplication::DialogAnalyzeApplication(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogAnalyzeApplication::IDD,pParent)
	,_module_id(0)
	,_specimen_type_id(0)
	,_item_id(0)
	,_is_command_message_masked(FALSE)
	,_select_module_static(new MtImageStatic)
	,_assay_detect_incubate_static(new MtImageStatic)
	,_select_specimen_type_static(new MtImageStatic)
	,_diluent_stability_ratio_static(new MtImageStatic)
	,_select_test_static(new MtImageStatic)
	,_test_name_static(new MtImageStatic)
	,_test_no_static(new MtImageStatic)
	,_test_id_static(new MtImageStatic)
	,_sample_static(new MtImageStatic)
	,_normal_static(new MtImageStatic)
	,_decrease_static(new MtImageStatic)
	,_increase_static(new MtImageStatic)
	,_reagent_static(new MtImageStatic)
	,_r1_static(new MtImageStatic)
	,_r2_static(new MtImageStatic)
	,_r3_static(new MtImageStatic)
	,_r4_static(new MtImageStatic)
	,_substrate_volume_static(new MtImageStatic)
	,_substrate_code_static(new MtImageStatic)
	,_substrate_stability_static(new MtImageStatic)
	,_substrate_1_static(new MtImageStatic)
	,_substrate_2_static(new MtImageStatic)
	,_substrate_3_static(new MtImageStatic)
	,_buffer_solution_volume_code_stability_static(new MtImageStatic)
	,_select_module_combo_box(new MtImageComboBox)
	,_assay_method_combo_box(new MtImageComboBox)
	,_select_specimen_type_combo_box(new MtImageComboBox)
	,_dilution_ratio_combo_box(new MtImageComboBox)
	,_select_test_combo_box(new MtImageComboBox)
	,_detect_time_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_incubate_time_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_incubate_time_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_incubate_time_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_incubate_time_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_diluent_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_diluent_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_test_name_edit(new MtImageEdit)
	,_test_no_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_test_id_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_normal_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_normal_dilution_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_normal_dilution_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_decreased_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_decreased_dilution_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_decreased_dilution_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_increased_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_increased_dilution_sample_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_increased_dilution_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r1_reagent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r1_diluent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r1_reagent_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r1_reagent_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r2_reagent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r2_diluent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r2_reagent_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r2_reagent_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r3_reagent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r3_diluent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r3_reagent_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r3_reagent_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r4_reagent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r4_diluent_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r4_reagent_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_r4_reagent_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_1_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_1_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_1_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_2_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_2_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_2_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_3_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_3_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_substrate_3_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_buffer_solution_volume_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_buffer_solution_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_buffer_solution_stability_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_delete_button(new MtImageButton)
	,_read_parameters_button(new MtImageButton)
	,_write_parameters_button(new MtImageButton)
	,_add_application_button(new MtImageButton)
	,_ok_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_child_layout_6(new MtHorizonLayout)
	,_child_layout_7(new MtVerticalLayout)
	,_child_layout_8(new MtHorizonLayout)
	,_child_layout_9(new MtHorizonLayout)
	,_child_layout_10(new MtHorizonLayout)
	,_child_layout_11(new MtHorizonLayout)
	,_child_layout_12(new MtVerticalLayout)
	,_child_layout_13(new MtHorizonLayout)
	,_child_layout_14(new MtHorizonLayout)
	,_child_layout_15(new MtHorizonLayout)
	,_child_layout_16(new MtHorizonLayout)
	,_child_layout_17(new MtHorizonLayout)
	,_child_layout_18(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogAnalyzeApplication
 * breif: 析构函数。
 * param: --
 * return: --
 */
DialogAnalyzeApplication::~DialogAnalyzeApplication(){
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
	delete _child_layout_18;
	delete _select_module_static;
	delete _assay_detect_incubate_static;
	delete _select_specimen_type_static;
	delete _diluent_stability_ratio_static;
	delete _select_test_static;
	delete _test_name_static;
	delete _test_no_static;
	delete _test_id_static;
	delete _sample_static;
	delete _normal_static;
	delete _decrease_static;
	delete _increase_static;
	delete _reagent_static;
	delete _r1_static;
	delete _r2_static;
	delete _r3_static;
	delete _r4_static;
	delete _substrate_code_static;
	delete _substrate_volume_static;
	delete _substrate_stability_static;
	delete _substrate_1_static;
	delete _substrate_2_static;
	delete _substrate_3_static;
	delete _buffer_solution_volume_code_stability_static;
	delete _select_module_combo_box;
	delete _assay_method_combo_box;
	delete _select_specimen_type_combo_box;
	delete _dilution_ratio_combo_box;
	delete _select_test_combo_box;
	delete _detect_time_edit;
	delete _incubate_time_1_edit;
	delete _incubate_time_2_edit;
	delete _incubate_time_3_edit;
	delete _incubate_time_4_edit;
	delete _diluent_code_edit;
	delete _diluent_stability_edit;
	delete _test_name_edit;
	delete _test_no_edit;
	delete _test_id_edit;
	delete _normal_sample_volume_edit;
	delete _normal_dilution_sample_volume_edit;
	delete _normal_dilution_volume_edit;
	delete _decreased_sample_volume_edit;
	delete _decreased_dilution_sample_volume_edit;
	delete _decreased_dilution_volume_edit;
	delete _increased_sample_volume_edit;
	delete _increased_dilution_sample_volume_edit;
	delete _increased_dilution_volume_edit;
	delete _r1_reagent_volume_edit;
	delete _r1_diluent_volume_edit;
	delete _r1_reagent_code_edit;
	delete _r1_reagent_stability_edit;
	delete _r2_reagent_volume_edit;
	delete _r2_diluent_volume_edit;
	delete _r2_reagent_code_edit;
	delete _r2_reagent_stability_edit;
	delete _r3_reagent_volume_edit;
	delete _r3_diluent_volume_edit;
	delete _r3_reagent_code_edit;
	delete _r3_reagent_stability_edit;
	delete _r4_reagent_volume_edit;
	delete _r4_diluent_volume_edit;
	delete _r4_reagent_code_edit;
	delete _r4_reagent_stability_edit;
	delete _substrate_1_volume_edit;
	delete _substrate_1_code_edit;
	delete _substrate_1_stability_edit;
	delete _substrate_2_volume_edit;
	delete _substrate_2_code_edit;
	delete _substrate_2_stability_edit;
	delete _substrate_3_volume_edit;
	delete _substrate_3_code_edit;
	delete _substrate_3_stability_edit;
	delete _buffer_solution_volume_edit;
	delete _buffer_solution_code_edit;
	delete _buffer_solution_stability_edit;
	delete _delete_button;
	delete _read_parameters_button;
	delete _write_parameters_button;
	delete _add_application_button;
	delete _ok_button;
}

/**
 * name: DoDataExchange
 * brief: 支持DDV/DDX。
 * param: pDX - 
 * return: --
 */
void DialogAnalyzeApplication::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SELECT_MODULE,*_select_module_static);
	DDX_Control(pDX,IDC_STATIC_ASSAY_DETECT_INCUBATE,*_assay_detect_incubate_static);
	DDX_Control(pDX,IDC_STATIC_SELECT_SPECIMEN_TYPE,*_select_specimen_type_static);
	DDX_Control(pDX,IDC_STATIC_DILUENT_STABILITY_RATIO,*_diluent_stability_ratio_static);
	DDX_Control(pDX,IDC_STATIC_SELECT_TEST,*_select_test_static);
	DDX_Control(pDX,IDC_STATIC_TEST_NAME,*_test_name_static);
	DDX_Control(pDX,IDC_STATIC_TEST_NO,*_test_no_static);
	DDX_Control(pDX,IDC_STATIC_TEST_ID,*_test_id_static);
	DDX_Control(pDX,IDC_STATIC_SAMPLE,*_sample_static);
	DDX_Control(pDX,IDC_STATIC_NORMAL,*_normal_static);
	DDX_Control(pDX,IDC_STATIC_DECREASE,*_decrease_static);
	DDX_Control(pDX,IDC_STATIC_INCREASE,*_increase_static);
	DDX_Control(pDX,IDC_STATIC_REAGENT,*_reagent_static);
	DDX_Control(pDX,IDC_STATIC_R1,*_r1_static);
	DDX_Control(pDX,IDC_STATIC_R2,*_r2_static);
	DDX_Control(pDX,IDC_STATIC_R3,*_r3_static);
	DDX_Control(pDX,IDC_STATIC_R4,*_r4_static);
	DDX_Control(pDX,IDC_STATIC_SUBSTRATE_CODE,*_substrate_code_static);
	DDX_Control(pDX,IDC_STATIC_SUBSTRATE_VOLUME,*_substrate_volume_static);
	DDX_Control(pDX,IDC_STATIC_SUBSTRATE_STABILITY,*_substrate_stability_static);
	DDX_Control(pDX,IDC_STATIC_SUBSTRATE_1,*_substrate_1_static);
	DDX_Control(pDX,IDC_STATIC_ABS_LIMIT,*_substrate_2_static);
	DDX_Control(pDX,IDC_STATIC_SUBSTRATE_3,*_substrate_3_static);
	DDX_Control(pDX,IDC_STATIC_BUFFER_SOLUTION_VOLUME_CODE_STABILITY,*_buffer_solution_volume_code_stability_static);
	DDX_Control(pDX,IDC_COMBO_SELECT_MODULE,*_select_module_combo_box);
	DDX_Control(pDX,IDC_COMBO_ASSAY_METHOD,*_assay_method_combo_box);
	DDX_Control(pDX,IDC_COMBO_SELECT_SPECIMEN_TYPE,*_select_specimen_type_combo_box);
	DDX_Control(pDX,IDC_COMBO_DILUTION_RATIO,*_dilution_ratio_combo_box);
	DDX_Control(pDX,IDC_COMBO_SELECT_TEST,*_select_test_combo_box);
	DDX_Control(pDX,IDC_EDIT_DETECT_TIME,*_detect_time_edit);
	DDX_Control(pDX,IDC_EDIT_INCUBATE_TIME_1,*_incubate_time_1_edit);
	DDX_Control(pDX,IDC_EDIT_INCUBATE_TIME_2,*_incubate_time_2_edit);
	DDX_Control(pDX,IDC_EDIT_INCUBATE_TIME_3,*_incubate_time_3_edit);
	DDX_Control(pDX,IDC_EDIT_INCUBATE_TIME_4,*_incubate_time_4_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_CODE,*_diluent_code_edit);
	DDX_Control(pDX,IDC_EDIT_DILUENT_STABILITY,*_diluent_stability_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_NAME,*_test_name_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_NO,*_test_no_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_ID,*_test_id_edit);
	DDX_Control(pDX,IDC_EDIT_NORMAL_SAMPLE_VOLUME,*_normal_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_NORMAL_DILUTION_SAMPLE_VOLUME,*_normal_dilution_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_NORMAL_DILUTION_VOLUME,*_normal_dilution_volume_edit);
	DDX_Control(pDX,IDC_EDIT_DECREASED_SAMPLE_VOLUME,*_decreased_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_DECREASED_DILUTION_SAMPLE_VOLUME,*_decreased_dilution_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_DECREASED_DILUTION_VOLUME,*_decreased_dilution_volume_edit);
	DDX_Control(pDX,IDC_EDIT_INCREASED_SAMPLE_VOLUME,*_increased_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_INCREASED_DILUTION_SAMPLE_VOLUME,*_increased_dilution_sample_volume_edit);
	DDX_Control(pDX,IDC_EDIT_INCREASED_DILUTION_VOLUME,*_increased_dilution_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R1_REAGENT_VOLUME,*_r1_reagent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R1_DILUENT_VOLUME,*_r1_diluent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R1_REAGENT_CODE,*_r1_reagent_code_edit);
	DDX_Control(pDX,IDC_EDIT_R1_REAGENT_STABILITY,*_r1_reagent_stability_edit);
	DDX_Control(pDX,IDC_EDIT_R2_REAGENT_VOLUME,*_r2_reagent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R2_DILUENT_VOLUME,*_r2_diluent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R2_REAGENT_CODE,*_r2_reagent_code_edit);
	DDX_Control(pDX,IDC_EDIT_R2_REAGENT_STABILITY,*_r2_reagent_stability_edit);
	DDX_Control(pDX,IDC_EDIT_R3_REAGENT_VOLUME,*_r3_reagent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R3_DILUENT_VOLUME,*_r3_diluent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R3_REAGENT_CODE,*_r3_reagent_code_edit);
	DDX_Control(pDX,IDC_EDIT_R3_REAGENT_STABILITY,*_r3_reagent_stability_edit);
	DDX_Control(pDX,IDC_EDIT_R4_REAGENT_VOLUME,*_r4_reagent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R4_DILUENT_VOLUME,*_r4_diluent_volume_edit);
	DDX_Control(pDX,IDC_EDIT_R4_REAGENT_CODE,*_r4_reagent_code_edit);
	DDX_Control(pDX,IDC_EDIT_R4_REAGENT_STABILITY,*_r4_reagent_stability_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_1_VOLUME,*_substrate_1_volume_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_1_CODE,*_substrate_1_code_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_1_STABILITY,*_substrate_1_stability_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_2_VOLUME,*_substrate_2_volume_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_2_CODE,*_substrate_2_code_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_2_STABILITY,*_substrate_2_stability_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_3_VOLUME,*_substrate_3_volume_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_3_CODE,*_substrate_3_code_edit);
	DDX_Control(pDX,IDC_EDIT_SUBSTRATE_3_STABILITY,*_substrate_3_stability_edit);
	DDX_Control(pDX,IDC_EDIT_BUFFER_SOLUTION_VOLUME,*_buffer_solution_volume_edit);
	DDX_Control(pDX,IDC_EDIT_BUFFER_SOLUTION_CODE,*_buffer_solution_code_edit);
	DDX_Control(pDX,IDC_EDIT_BUFFER_SOLUTION_STABILITY,*_buffer_solution_stability_edit);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
	DDX_Control(pDX,IDC_BUTTON_READ_PARAMETERS,*_read_parameters_button);
	DDX_Control(pDX,IDC_BUTTON_WRITE_PARAMETERS,*_write_parameters_button);
	DDX_Control(pDX,IDC_BUTTON_ADD_APPLICATION,*_add_application_button);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
}

/**
 * name: OnInitDialog
 * breif: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogAnalyzeApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.初始化当前对话框中控件。
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
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
BOOL DialogAnalyzeApplication::OnCommand(WPARAM wParam,LPARAM lParam){
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

BEGIN_MESSAGE_MAP(DialogAnalyzeApplication,DialogPageBase)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_MODULE,&DialogAnalyzeApplication::OnCbnSelchangeComboSelectModule)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_SPECIMEN_TYPE,&DialogAnalyzeApplication::OnCbnSelchangeComboSelectSpecimenType)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_TEST,&DialogAnalyzeApplication::OnCbnSelchangeComboSelectTest)
	ON_BN_CLICKED(IDC_BUTTON_ADD_APPLICATION,&DialogAnalyzeApplication::OnBnClickedButtonAddApplication)
	ON_BN_CLICKED(IDC_BUTTON_DELETE,&DialogAnalyzeApplication::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogAnalyzeApplication::OnBnClickedButtonOk)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,&
		DialogAnalyzeApplication::OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID)
	ON_MESSAGE(WM_COMMIT_DATA_OF_CONTROLS,&DialogAnalyzeApplication::OnCommitDataOfControls)
END_MESSAGE_MAP()

//DialogAnalyzeApplication message handlers

/**
 * name: OnSize
 * brief: 对话框尺寸调整消息响应函数，此处用来
 *        更新对话框中布局信息。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogAnalyzeApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
	//2.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_13->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_sample_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_13->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_reagent_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: OnCbnSelchangeComboSelectModule
 * breif: “选择模块”下拉框模块变更消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectModule(){
	// TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.获取当前用户选择的模块标识。
	const int item=_select_module_combo_box->GetCurSel();
	if(item<0){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_module_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			_module_id,*_select_module_combo_box));
		return;
	}
	const int module_id=static_cast<int>(
		_select_module_combo_box->GetItemData(item));
	//3.如果用户选择的模块标识，与当前模块标识相同，则直接返回。
	if(module_id==_module_id){
		return;
	}
	//4.如果当前输入的参数发生改变。
	if(is_data_of_controls_changed()){
		//4-1.提问用户是否保存当前参数。
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING307),this);
		//4-2.如果当前用户选择“取消”按钮。
		if(IDCANCEL==result){
			//4-1-1.屏蔽控件数据的更新。
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.回复当前下拉框选择内容。
			_select_module_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_module_id,*_select_module_combo_box));
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
				_select_module_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_module_id,*_select_module_combo_box));
				//4-4-3.程序运行到此直接返回。
				return;
			}
		}
	}
	//5.显示新选择的模块的应用参数信息。
	//5-1.计算生成消息参数。
	WPARAM wParam=0;
	wParam|=(module_id&0xFF);
	wParam<<=8;
	wParam|=(_specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(_item_id&0xFFFF);
	//5-2.发送相应消息，更新界面数据。
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnCbnSelchangeComboSelectSpecimenType
 * brief: “选择样本类型”下拉框样本类型变更消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectSpecimenType(){
	//TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.获取当前用户选择的样本类型标识。
	const int item=_select_specimen_type_combo_box->GetCurSel();
	if(item<0){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_specimen_type_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			_specimen_type_id,*_select_specimen_type_combo_box));
		return;
	}
	const int specimen_type_id=static_cast<int>(
		_select_specimen_type_combo_box->GetItemData(item));
	//3.如果用户选择的样本类型标识，与当前样本类型标识相同，则直接返回。
	if(specimen_type_id==_specimen_type_id){
		return;
	}
	//4.如果当前输入的参数发生改变。
	if(is_data_of_controls_changed()){
		//4-1.提问用户是否保存当前参数。
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING307),this);
		//4-2.如果当前用户选择“取消”按钮。
		if(IDCANCEL==result){
			//4-1-1.屏蔽控件数据的更新。
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.回复当前下拉框选择内容。
			_select_specimen_type_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_specimen_type_id,*_select_specimen_type_combo_box));
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
				_select_specimen_type_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_specimen_type_id,*_select_specimen_type_combo_box));
				//4-4-3.程序运行到此直接返回。
				return;
			}
		}
	}
	//5.显示新选择的模块的应用参数信息。
	//5-1.计算生成消息参数。
	WPARAM wParam=0;
	wParam|=(_module_id&0xFF);
	wParam<<=8;
	wParam|=(specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(_item_id&0xFFFF);
	//5-2.发送相应消息，更新界面数据。
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: “选择项目”下拉框项目变更消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectTest(){
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
			theme->get_string(IDS_STRING307),this);
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
	//5-1.计算生成消息参数。
	WPARAM wParam=0;
	wParam|=(_module_id&0xFF);
	wParam<<=8;
	wParam|=(_specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(item_id&0xFFFF);
	//5-2.发送相应消息，更新界面数据。
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnBnClickedButtonAddApplication
 * brief: 用户点击“添加项目”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonAddApplication(){
	// TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	DialogAddApplication dlg;
	//2.如果项目添加对话框失败退出。
	if(IDCANCEL==dlg.DoModal()){
		return;
	}
	//3.如果项目添加对话框成功退出，更新控件。
	//3-1.计算消息参数。
	const int module_id=dlg.get_module_id();
	const int specimen_type_id=dlg.get_specimen_type_id();
	const int item_id=dlg.get_item_id();
	WPARAM wParam=0;
	wParam|=(module_id&0xFF);
	wParam<<=8;
	wParam|=(specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(item_id&0xFFFF);
	//3-2.发送更新控件消息。
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnBnClickedButtonDelete
 * brief: 用户点击“删除”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonDelete(){
	//TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	Database *database=(DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//2.获取当前期望删除的项目标识。
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING182),this);
		return;
	}
	const int item_id=static_cast<int>(
		_select_test_combo_box->GetItemData(item));
	//3.询问用户是否期望删除当前项目。
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING305),this)){
		return;
	}
	//4.删除当前项目的参数信息，并且判断删除是否成功。
	//4-1.开启数据库事务。
	if(database->begin_trans()<0){
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-2.删除当前项目参数在数据库中的相关信息，并且判断删除是否成功。
	if((ApplicationParameters::instance())->commit(item_id,3,*database,FALSE)<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-3.删除当前项目在数据库中的相关信息，并且判断删除是否成功。
	if((Items::instance())->commit(item_id,3,*database)<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-4.删除当前项目参数对应的内存数据，并且判断删除是否成功。
	if((ApplicationParameters::instance())->remove(item_id)<0){
		database->rollback_trans();
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-5.删除当前项目对应的内存数据，并且判断删除是否成功。
	if((Items::instance())->remove(item_id)<0){
		database->rollback_trans();
		Items::instance()->update(*database);
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-6.提交当前数据库事务，并且判断提交是否成功。
	if(database->commit_trans()<0){
		database->rollback_trans();
		Items::instance()->update(*database);
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//5.刷新当前界面。
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		0,0);
}

/**
 * name: OnBnClickedButtonOk
 * brief: 用户点击“确定”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonOk(){
	// TODO: Add your control notification handler code here
	//1.提交当前界面中控件数据。
	const int result=commit_data_of_controls(*((
		DatabaseManager::instance())->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)));
	if(result<0){
		if(-1==result){
			return;
		}else{
			WarningMessageBox(Theme::instance()->
				get_string(IDS_STRING293));
		}
	}
	//2.屏蔽OnCommand响应。
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//3.更新当前界面中控件数据。
	update_data_for_controls(_module_id,_specimen_type_id,_item_id);
}

/**
 * name: OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID
 * brief: 通过模块标识、样本类型标识、项目标识更新界面控件数据。
 * param: wParam - 模块标识（高8位）、样本类型标识（中8位）、项目标识（低16位）。
 *        lParam - 无意义。
 * return: 此函数一直返回零。
 */
LRESULT DialogAnalyzeApplication::
	OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID(
	WPARAM wParam,LPARAM /*lParam*/){
	//1.屏蔽当前界面命令消息响应。
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.解析出模块标识、样本类型标识以及项目标识。
	const int item_id=wParam&0xFFFF;
	const int specimen_type_id=(wParam>>16)&0xFF;
	const int module_id=(wParam>>24)&0xFF;
	//2.更新当前界面控件数据。
	update_data_for_controls(module_id,specimen_type_id,item_id);
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
LRESULT DialogAnalyzeApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.如果界面中的数据没有发生变化，则直接返回。
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.询问用户是否希望保存当前数据。
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING307),this);
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
void DialogAnalyzeApplication::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	MtAutoReset<BOOL> auto_reset(_is_command_message_masked,TRUE,FALSE);
	//2.初始化当前对话框中控件。
	//2-1.初始化静态文本框。
	_select_module_static->set_text_color(255,50,50,50);
	_select_module_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_assay_detect_incubate_static->set_text_color(255,50,50,50);
	_assay_detect_incubate_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_select_specimen_type_static->set_text_color(255,50,50,50);
	_select_specimen_type_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_diluent_stability_ratio_static->set_text_color(255,50,50,50);
	_diluent_stability_ratio_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_select_test_static->set_text_color(255,50,50,50);
	_select_test_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_test_name_static->set_text_color(255,50,50,50);
	_test_name_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_test_no_static->set_text_color(255,50,50,50);
	_test_no_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_test_id_static->set_text_color(255,50,50,50);
	_test_id_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_sample_static->set_text_color(255,255,255,255);
	_sample_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_HCENTER|MtImageStatic::ALIGNMENT_TOP);
	_sample_static->load_background_image(theme->get_image(25));
	_sample_static->set_background_image_stretching_factors(10,29,10,2);
	_normal_static->set_text_color(255,50,50,50);
	_normal_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_decrease_static->set_text_color(255,50,50,50);
	_decrease_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_increase_static->set_text_color(255,50,50,50);
	_increase_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_reagent_static->set_text_color(255,255,255,255);
	_reagent_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_HCENTER|MtImageStatic::ALIGNMENT_TOP);
	_reagent_static->load_background_image(theme->get_image(25));
	_reagent_static->set_background_image_stretching_factors(10,29,10,2);
	_r1_static->set_text_color(255,50,50,50);
	_r1_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_r2_static->set_text_color(255,50,50,50);
	_r2_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_r3_static->set_text_color(255,50,50,50);
	_r3_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_r4_static->set_text_color(255,50,50,50);
	_r4_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_volume_static->set_text_color(255,50,50,50);
	_substrate_volume_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_HCENTER|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_code_static->set_text_color(255,50,50,50);
	_substrate_code_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_HCENTER|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_stability_static->set_text_color(255,50,50,50);
	_substrate_stability_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_HCENTER|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_1_static->set_text_color(255,50,50,50);
	_substrate_1_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_2_static->set_text_color(255,50,50,50);
	_substrate_2_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_substrate_3_static->set_text_color(255,50,50,50);
	_substrate_3_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_buffer_solution_volume_code_stability_static->set_text_color(255,50,50,50);
	_buffer_solution_volume_code_stability_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.初始化下拉框。
	_select_module_combo_box->set_text_color(255,50,50,50);
	_select_module_combo_box->set_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_select_module_combo_box->set_list_box_text_color(255,50,50,50);
	_select_module_combo_box->set_list_box_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_select_module_combo_box->load_background_image(theme->get_image(27),1,4);
	_select_module_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_select_module_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_select_module_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_assay_method_combo_box->set_text_color(255,50,50,50);
	_assay_method_combo_box->set_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_assay_method_combo_box->set_list_box_text_color(255,50,50,50);
	_assay_method_combo_box->set_list_box_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_assay_method_combo_box->load_background_image(theme->get_image(27),1,4);
	_assay_method_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_assay_method_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_assay_method_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_select_specimen_type_combo_box->set_text_color(255,50,50,50);
	_select_specimen_type_combo_box->set_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_select_specimen_type_combo_box->set_list_box_text_color(255,50,50,50);
	_select_specimen_type_combo_box->set_list_box_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_select_specimen_type_combo_box->load_background_image(theme->get_image(27),1,4);
	_select_specimen_type_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_select_specimen_type_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_select_specimen_type_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_dilution_ratio_combo_box->set_text_color(255,50,50,50);
	_dilution_ratio_combo_box->set_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_dilution_ratio_combo_box->set_list_box_text_color(255,50,50,50);
	_dilution_ratio_combo_box->set_list_box_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_dilution_ratio_combo_box->load_background_image(theme->get_image(27),1,4);
	_dilution_ratio_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_dilution_ratio_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_dilution_ratio_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_select_test_combo_box->set_text_color(255,50,50,50);
	_select_test_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_select_test_combo_box->set_list_box_text_color(255,50,50,50);
	_select_test_combo_box->set_list_box_text_alignment(
		MtImageComboBox::ALIGNMENT_LEFT|MtImageComboBox::ALIGNMENT_VCENTER);
	_select_test_combo_box->load_background_image(theme->get_image(27),1,4);
	_select_test_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_select_test_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_select_test_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	init_combo_boxes();
	//2-3.初始化文本编辑框。
	_detect_time_edit->set_text_color(50,50,50);
	_detect_time_edit->load_background_image(theme->get_image(29),1,3);
	_detect_time_edit->set_background_image_stretching_factors(5,5,5,5);
	_detect_time_edit->SetLimitText(4);
	_incubate_time_1_edit->set_text_color(50,50,50);
	_incubate_time_1_edit->load_background_image(theme->get_image(29),1,3);
	_incubate_time_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_incubate_time_1_edit->SetLimitText(4);
	_incubate_time_2_edit->set_text_color(50,50,50);
	_incubate_time_2_edit->load_background_image(theme->get_image(29),1,3);
	_incubate_time_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_incubate_time_2_edit->SetLimitText(4);
	_incubate_time_3_edit->set_text_color(50,50,50);
	_incubate_time_3_edit->load_background_image(theme->get_image(29),1,3);
	_incubate_time_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_incubate_time_3_edit->SetLimitText(4);
	_incubate_time_4_edit->set_text_color(50,50,50);
	_incubate_time_4_edit->load_background_image(theme->get_image(29),1,3);
	_incubate_time_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_incubate_time_4_edit->SetLimitText(4);
	_diluent_code_edit->set_text_color(50,50,50);
	_diluent_code_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_code_edit->SetLimitText(3);
	_diluent_stability_edit->set_text_color(50,50,50);
	_diluent_stability_edit->load_background_image(theme->get_image(29),1,3);
	_diluent_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_diluent_stability_edit->SetLimitText(3);
	_test_name_edit->set_text_color(50,50,50);
	_test_name_edit->load_background_image(theme->get_image(29),1,3);
	_test_name_edit->set_background_image_stretching_factors(5,5,5,5);
	_test_no_edit->set_text_color(50,50,50);
	_test_no_edit->load_background_image(theme->get_image(29),1,3);
	_test_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_test_no_edit->SetLimitText(3);
	_test_no_edit->EnableWindow(FALSE);
	_test_id_edit->set_text_color(50,50,50);
	_test_id_edit->load_background_image(theme->get_image(29),1,3);
	_test_id_edit->set_background_image_stretching_factors(5,5,5,5);
	_test_id_edit->SetLimitText(3);
	_test_id_edit->EnableWindow(FALSE);
	_normal_sample_volume_edit->set_text_color(50,50,50);
	_normal_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_normal_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_normal_sample_volume_edit->SetLimitText(2);
	_normal_dilution_sample_volume_edit->set_text_color(50,50,50);
	_normal_dilution_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_normal_dilution_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_normal_dilution_sample_volume_edit->SetLimitText(2);
	_normal_dilution_volume_edit->set_text_color(50,50,50);
	_normal_dilution_volume_edit->load_background_image(theme->get_image(29),1,3);
	_normal_dilution_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_normal_dilution_volume_edit->SetLimitText(3);
	_decreased_sample_volume_edit->set_text_color(50,50,50);
	_decreased_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_decreased_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_decreased_sample_volume_edit->SetLimitText(2);
	_decreased_dilution_sample_volume_edit->set_text_color(50,50,50);
	_decreased_dilution_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_decreased_dilution_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_decreased_dilution_sample_volume_edit->SetLimitText(2);
	_decreased_dilution_volume_edit->set_text_color(50,50,50);
	_decreased_dilution_volume_edit->load_background_image(theme->get_image(29),1,3);
	_decreased_dilution_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_decreased_dilution_volume_edit->SetLimitText(3);
	_increased_sample_volume_edit->set_text_color(50,50,50);
	_increased_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_increased_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_increased_sample_volume_edit->SetLimitText(2);
	_increased_dilution_sample_volume_edit->set_text_color(50,50,50);
	_increased_dilution_sample_volume_edit->load_background_image(theme->get_image(29),1,3);
	_increased_dilution_sample_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_increased_dilution_sample_volume_edit->SetLimitText(2);
	_increased_dilution_volume_edit->set_text_color(50,50,50);
	_increased_dilution_volume_edit->load_background_image(theme->get_image(29),1,3);
	_increased_dilution_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_increased_dilution_volume_edit->SetLimitText(3);
	_r1_reagent_volume_edit->set_text_color(50,50,50);
	_r1_reagent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r1_reagent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r1_reagent_volume_edit->SetLimitText(3);
	_r1_diluent_volume_edit->set_text_color(50,50,50);
	_r1_diluent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r1_diluent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r1_diluent_volume_edit->SetLimitText(3);
	_r1_reagent_code_edit->set_text_color(50,50,50);
	_r1_reagent_code_edit->load_background_image(theme->get_image(29),1,3);
	_r1_reagent_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_r1_reagent_code_edit->SetLimitText(3);
	_r1_reagent_stability_edit->set_text_color(50,50,50);
	_r1_reagent_stability_edit->load_background_image(theme->get_image(29),1,3);
	_r1_reagent_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_r1_reagent_stability_edit->SetLimitText(3);
	_r2_reagent_volume_edit->set_text_color(50,50,50);
	_r2_reagent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r2_reagent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r2_reagent_volume_edit->SetLimitText(3);
	_r2_diluent_volume_edit->set_text_color(50,50,50);
	_r2_diluent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r2_diluent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r2_diluent_volume_edit->SetLimitText(3);
	_r2_reagent_code_edit->set_text_color(50,50,50);
	_r2_reagent_code_edit->load_background_image(theme->get_image(29),1,3);
	_r2_reagent_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_r2_reagent_code_edit->SetLimitText(3);
	_r2_reagent_stability_edit->set_text_color(50,50,50);
	_r2_reagent_stability_edit->load_background_image(theme->get_image(29),1,3);
	_r2_reagent_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_r2_reagent_stability_edit->SetLimitText(3);
	_r3_reagent_volume_edit->set_text_color(50,50,50);
	_r3_reagent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r3_reagent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r3_reagent_volume_edit->SetLimitText(3);
	_r3_diluent_volume_edit->set_text_color(50,50,50);
	_r3_diluent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r3_diluent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r3_diluent_volume_edit->SetLimitText(3);
	_r3_reagent_code_edit->set_text_color(50,50,50);
	_r3_reagent_code_edit->load_background_image(theme->get_image(29),1,3);
	_r3_reagent_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_r3_reagent_code_edit->SetLimitText(3);
	_r3_reagent_stability_edit->set_text_color(50,50,50);
	_r3_reagent_stability_edit->load_background_image(theme->get_image(29),1,3);
	_r3_reagent_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_r3_reagent_stability_edit->SetLimitText(3);
	_r4_reagent_volume_edit->set_text_color(50,50,50);
	_r4_reagent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r4_reagent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r4_reagent_volume_edit->SetLimitText(3);
	_r4_diluent_volume_edit->set_text_color(50,50,50);
	_r4_diluent_volume_edit->load_background_image(theme->get_image(29),1,3);
	_r4_diluent_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_r4_diluent_volume_edit->SetLimitText(3);
	_r4_reagent_code_edit->set_text_color(50,50,50);
	_r4_reagent_code_edit->load_background_image(theme->get_image(29),1,3);
	_r4_reagent_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_r4_reagent_code_edit->SetLimitText(3);
	_r4_reagent_stability_edit->set_text_color(50,50,50);
	_r4_reagent_stability_edit->load_background_image(theme->get_image(29),1,3);
	_r4_reagent_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_r4_reagent_stability_edit->SetLimitText(3);
	_substrate_1_volume_edit->set_text_color(50,50,50);
	_substrate_1_volume_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_1_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_1_volume_edit->SetLimitText(3);
	_substrate_1_code_edit->set_text_color(50,50,50);
	_substrate_1_code_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_1_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_1_code_edit->SetLimitText(3);
	_substrate_1_stability_edit->set_text_color(50,50,50);
	_substrate_1_stability_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_1_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_1_stability_edit->SetLimitText(3);
	_substrate_2_volume_edit->set_text_color(50,50,50);
	_substrate_2_volume_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_2_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_2_volume_edit->SetLimitText(3);
	_substrate_2_code_edit->set_text_color(50,50,50);
	_substrate_2_code_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_2_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_2_code_edit->SetLimitText(3);
	_substrate_2_stability_edit->set_text_color(50,50,50);
	_substrate_2_stability_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_2_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_2_stability_edit->SetLimitText(3);
	_substrate_3_volume_edit->set_text_color(50,50,50);
	_substrate_3_volume_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_3_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_3_volume_edit->SetLimitText(3);
	_substrate_3_code_edit->set_text_color(50,50,50);
	_substrate_3_code_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_3_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_3_code_edit->SetLimitText(3);
	_substrate_3_stability_edit->set_text_color(50,50,50);
	_substrate_3_stability_edit->load_background_image(theme->get_image(29),1,3);
	_substrate_3_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_substrate_3_stability_edit->SetLimitText(3);
	_buffer_solution_volume_edit->set_text_color(50,50,50);
	_buffer_solution_volume_edit->load_background_image(theme->get_image(29),1,3);
	_buffer_solution_volume_edit->set_background_image_stretching_factors(5,5,5,5);
	_buffer_solution_volume_edit->SetLimitText(3);
	_buffer_solution_code_edit->set_text_color(50,50,50);
	_buffer_solution_code_edit->load_background_image(theme->get_image(29),1,3);
	_buffer_solution_code_edit->set_background_image_stretching_factors(5,5,5,5);
	_buffer_solution_code_edit->SetLimitText(3);
	_buffer_solution_stability_edit->set_text_color(50,50,50);
	_buffer_solution_stability_edit->load_background_image(theme->get_image(29),1,3);
	_buffer_solution_stability_edit->set_background_image_stretching_factors(5,5,5,5);
	_buffer_solution_stability_edit->SetLimitText(3);
	//2-5.初始化按钮。
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_read_parameters_button->set_text_color(255,50,50,50);
	_read_parameters_button->load_background_image(theme->get_image(32),1,4);
	_read_parameters_button->set_background_image_stretching_factors(5,5,5,5);
	_write_parameters_button->set_text_color(255,50,50,50);
	_write_parameters_button->load_background_image(theme->get_image(32),1,4);
	_write_parameters_button->set_background_image_stretching_factors(5,5,5,5);
	_add_application_button->set_text_color(255,50,50,50);
	_add_application_button->load_background_image(theme->get_image(32),1,4);
	_add_application_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化布局。
	//3-1.初始化子布局1。
	_child_layout_1->add_fixed_window(_select_module_static,100);
	_child_layout_1->add_fixed_window(_select_module_combo_box,100);
	_child_layout_1->add_spacing(10);
	_child_layout_1->add_fixed_window(_assay_detect_incubate_static,150);
	_child_layout_1->add_fixed_window(_assay_method_combo_box,200);
	_child_layout_1->add_spacing(5);
	_child_layout_1->add_fixed_window(_detect_time_edit,50);
	_child_layout_1->add_spacing(5);
	_child_layout_1->add_fixed_window(_incubate_time_1_edit,50);
	_child_layout_1->add_spacing(1);
	_child_layout_1->add_fixed_window(_incubate_time_2_edit,50);
	_child_layout_1->add_spacing(1);
	_child_layout_1->add_fixed_window(_incubate_time_3_edit,50);
	_child_layout_1->add_spacing(1);
	_child_layout_1->add_fixed_window(_incubate_time_4_edit,50);
	//3-2.初始化子布局2。
	_child_layout_2->add_fixed_window(_select_specimen_type_static,120);
	_child_layout_2->add_fixed_window(_select_specimen_type_combo_box,150);
	_child_layout_2->add_spacing(10);
	_child_layout_2->add_fixed_window(_diluent_stability_ratio_static,200);
	_child_layout_2->add_fixed_window(_diluent_code_edit,100);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_diluent_stability_edit,50);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_dilution_ratio_combo_box,100);
	//3-3.初始化子布局3。
	_child_layout_3->add_fixed_window(_select_test_static,100);
	_child_layout_3->add_fixed_window(_select_test_combo_box,100);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_fixed_window(_test_name_static,100);
	_child_layout_3->add_fixed_window(_test_name_edit,100);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_fixed_window(_test_id_static,100);
	_child_layout_3->add_fixed_window(_test_id_edit,100);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_fixed_window(_test_no_static,100);
	_child_layout_3->add_fixed_window(_test_no_edit,100);
	//3-4.初始化子布局4。
	_child_layout_4->add_fixed_window(_normal_static,100);
	_child_layout_4->add_window(_normal_sample_volume_edit,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_normal_dilution_sample_volume_edit,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_normal_dilution_volume_edit,1);
	//3-7.初始化子布局5。
	_child_layout_5->add_fixed_window(_decrease_static,100);
	_child_layout_5->add_window(_decreased_sample_volume_edit,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_decreased_dilution_sample_volume_edit,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_decreased_dilution_volume_edit,1);
	//3-8.初始化子布局6。
	_child_layout_6->add_fixed_window(_increase_static,100);
	_child_layout_6->add_window(_increased_sample_volume_edit,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_increased_dilution_sample_volume_edit,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_increased_dilution_volume_edit,1);
	//3-9.初始化子布局7。
	_child_layout_7->set_margin(5,34,5,5);
	_child_layout_7->add_stretch(1);
	_child_layout_7->add_fixed_layout(_child_layout_4,24);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_fixed_layout(_child_layout_5,24);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_fixed_layout(_child_layout_6,24);
	_child_layout_7->add_stretch(1);
	//3-10.初始化子布局8。
	_child_layout_8->add_fixed_window(_r1_static,50);
	_child_layout_8->add_window(_r1_reagent_volume_edit,1);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_diluent_volume_edit,1);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_reagent_code_edit,2);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_reagent_stability_edit,1);
	//3-11.初始化子布局9。
	_child_layout_9->add_fixed_window(_r2_static,50);
	_child_layout_9->add_window(_r2_reagent_volume_edit,1);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_diluent_volume_edit,1);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_reagent_code_edit,2);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_reagent_stability_edit,1);
	//3-12.初始化子布局10。
	_child_layout_10->add_fixed_window(_r3_static,50);
	_child_layout_10->add_window(_r3_reagent_volume_edit,1);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_diluent_volume_edit,1);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_reagent_code_edit,2);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_reagent_stability_edit,1);
	//3-13.初始化子布局11。
	_child_layout_11->add_fixed_window(_r4_static,50);
	_child_layout_11->add_window(_r4_reagent_volume_edit,1);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_diluent_volume_edit,1);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_reagent_code_edit,2);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_reagent_stability_edit,1);
	//3-14.初始化子布局12。
	_child_layout_12->set_margin(5,34,5,5);
	_child_layout_12->add_fixed_layout(_child_layout_8,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_9,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_10,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_11,24);
	//3-15.初始化子布局13。
	_child_layout_13->add_fixed_layout(_child_layout_7,410);
	_child_layout_13->add_spacing(5);
	_child_layout_13->add_fixed_layout(_child_layout_12,410);
	//3-16.初始化子布局14。
	_child_layout_14->add_spacing(80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_volume_static,80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_code_static,80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_stability_static,80);
	//3-17.初始化子布局15.
	_child_layout_15->add_fixed_window(_substrate_1_static,80);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_substrate_1_volume_edit,80);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_substrate_1_code_edit,80);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_substrate_1_stability_edit,80);
	_child_layout_15->add_spacing(10);
	_child_layout_15->add_fixed_window(_buffer_solution_volume_code_stability_static,220);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_buffer_solution_volume_edit,80);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_buffer_solution_code_edit,80);
	_child_layout_15->add_spacing(5);
	_child_layout_15->add_fixed_window(_buffer_solution_stability_edit,80);
	//3-18.初始化子布局16.
	_child_layout_16->add_fixed_window(_substrate_2_static,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_volume_edit,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_code_edit,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_stability_edit,80);
	//3-19.初始化子布局17。
	_child_layout_17->add_fixed_window(_substrate_3_static,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_volume_edit,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_code_edit,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_stability_edit,80);
	//3-20.初始化子布局18。
	_child_layout_18->add_fixed_window(_delete_button,100);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_read_parameters_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_add_application_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_write_parameters_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_ok_button,100);
	//3-21.初始化主布局。
	_main_layout->add_spacing(BODER_SIZE);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_1,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_2,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_3,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_13,140);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_14,24);
	_main_layout->add_fixed_layout(_child_layout_15,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_16,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_17,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_18,50);
	//4.重置当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//5.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_13->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_sample_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_13->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_reagent_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//6.更新当前界面中控件的值。
	update_data_for_controls();
}

/**
 * name: init_combo_boxes
 * brief: 初始化界面中全部的下拉框，并将初始数据
 *        插入到下拉框中。
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::init_combo_boxes(){
	//1.获取系统中的模块信息，并将这些信息插入到指定的下拉框中。
	//1-1.声明当前操作所需变量。
	Modules *modules=Modules::instance();
	unsigned int count=modules->get_count();
	int item=0;
	//1-2.遍历模块信息，并将模块信息插入到指定下拉框中。
	for(unsigned int index=0;index<count;++index){
		//1-2-1.获取当前模块信息，并且判断获取是否成功。
		Modules::PtrToCModule module=modules->get_by_index(index);
		//1-2-1.断言当前模块信息存在合法。
		assert(static_cast<bool>(module));
		//1-2-3.向下拉框中插入模块信息数据。
		item=_select_module_combo_box->AddString(module->get_alias());
		_select_module_combo_box->SetItemData(item,static_cast<
			DWORD_PTR>(module->get_id()));
	}
	//2.获取系统中样本类型信息，并将这些信息插入到指定的下拉框中。
	//2-1.声明当前操作所需变量。
	SpecimenTypes *specimen_types=SpecimenTypes::instance();
	count=specimen_types->get_count();
	//2-2.遍历样本类型信息，并将样本类型信息插入到指定下拉框中。
	for(unsigned int index=0;index<count;++index){
		//2-2-1.获取当前样本类型信息，并且判断获取是否成功。
		SpecimenTypes::PtrToCSpecimenType specimen_type=
			specimen_types->get_by_index(index);
		//2-2-2.断言当前样本类型信息存在合法。
		assert(static_cast<bool>(specimen_type));
		//2-2-3.向下拉框中插入样本类型信息数据。
		item=_select_specimen_type_combo_box->AddString(
			specimen_type->get_alias());
		_select_specimen_type_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(specimen_type->get_id()));
	}
	//3.获取系统中分析方法信息，并将这些信息插入到指定的下拉框中。
	//3-1.声明当前操作所需变量。
	AnalysisMethods *analysis_methods=AnalysisMethods::instance();
	count=analysis_methods->get_count();
	//3-2.遍历分析方法，并将分析方法插入到指定的下拉框中。
	for(unsigned int index=0;index<count;++index){
		//3-2-1.获取当前分析方法。
		AnalysisMethods::PtrToCMethod analysis_method=
			analysis_methods->get_method(index);
		//3-2-2.断言当前分析方法存在合法。
		assert(static_cast<bool>(analysis_method));
		//3-2-3.向下拉框中插入分析方法数据。
		item=_assay_method_combo_box->AddString(
			analysis_method->get_alias());
		_assay_method_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(analysis_method->get_id()));
	}
	//4.获取系统中稀释方法信息，并将这些信息插入到指定的下拉框中。
	//4-1.声明当前操作所需变量。
	DilutionMethods *dilution_methods=DilutionMethods::instance();
	count=dilution_methods->get_count();
	//4-2.向下拉框插入不稀释项。
	item=_dilution_ratio_combo_box->AddString(
		Theme::instance()->get_string(IDS_STRING494));
	_dilution_ratio_combo_box->SetItemData(
		item,static_cast<DWORD_PTR>(0));
	//4-3.遍历稀释方法，并将稀释方法插入到指定的下拉框中。
	for(unsigned int index=0;index<count;++index){
		//4-3-1.获取当前稀释方法。
		DilutionMethods::PtrToCMethod dilution_method=
			dilution_methods->get_method(index);
		//4-3-2.断言当前稀释方法存在合法。
		assert(static_cast<bool>(dilution_method));
		//4-3-3.向下拉框中插入稀释方法数据。
		item=_dilution_ratio_combo_box->AddString(
			dilution_method->get_alias());
		_dilution_ratio_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(dilution_method->get_id()));
	}
}

/**
 * name: init_select_test_combo_box
 * breif: 初始化“选择项目”下拉框。
 * param: item - 输入的项目信息引用。
 * return: --
 */
void DialogAnalyzeApplication::init_select_test_combo_box(const Item &item){
	const int index=_select_test_combo_box->AddString(item.get_name());
	_select_test_combo_box->SetItemData(index,static_cast<DWORD_PTR>(item.get_id()));
}

/**
 * name: update_data_for_controls
 * brief: 将指定项目标识的申请参数信息更新到控件上。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本类型标识。
 *        item_id - 输入的项目标识。
 * return: --
 * remark: 当模块标识、样本类型标识以及项目标识输入值为零时，则其值取最小有效值。
 */
void DialogAnalyzeApplication::update_data_for_controls(
	const int module_id/*=0*/,const int specimen_type_id/*=0*/,const int item_id/*=0*/){
	//1.设置“选择模块”下拉框内容。
	//1-1.声明当前操作所需变量。
	int item_count=_select_module_combo_box->GetCount();
	//1-2.如果当前下拉框内容为空。
	if(item_count<=0){
		_select_module_combo_box->SetCurSel(-1);
		_select_module_combo_box->EnableWindow(FALSE);
		_module_id=0;
	}
	//1-3.如果当前未指定期望显示的模块标识，则显示默认的模块标识（下拉框中的第一个项目）。
	else if(module_id<=0){
		Modules::PtrToCModule module=(Modules::instance())->get_by_id(
			static_cast<int>(_select_module_combo_box->GetItemData(0)));
		if(!static_cast<bool>(module)){
			_select_module_combo_box->SetCurSel(-1);
			_select_module_combo_box->EnableWindow(FALSE);
			_module_id=0;
		}else{
			_select_module_combo_box->SetCurSel(0);
			_select_module_combo_box->EnableWindow(TRUE);
			_module_id=module->get_id();
		}
	}	
	//1-4.如果当前指定了期望显示的模块标识。
	else{
		Modules::PtrToCModule module=(Modules::instance())->
			get_by_id(module_id);
		int index=get_combo_box_index_by_item_data<int>(
			module_id,*_select_module_combo_box);
		if((!static_cast<bool>(module))||(index<0)){
			_select_module_combo_box->SetCurSel(-1);
			_select_module_combo_box->EnableWindow(FALSE);
			_module_id=0;
		}else{
			_select_module_combo_box->SetCurSel(index);
			_select_module_combo_box->EnableWindow(TRUE);
			_module_id=module_id;
		}
	}
	//2.设置“选择样本类型”下拉框内容。
	//2-1.声明当前操作所需变量。
	item_count=_select_specimen_type_combo_box->GetCount();
	//2-2.如果当前下拉框内容为空。
	if(item_count<=0){
		_select_specimen_type_combo_box->SetCurSel(-1);
		_select_specimen_type_combo_box->EnableWindow(FALSE);
		_specimen_type_id=0;
	}
	//2-3.如果当前未指定期望显示的样本类型标识，则显示默认的样本类型标识（下拉框中的第一个样本类型）。
	else if(specimen_type_id<=0){
		SpecimenTypes::PtrToCSpecimenType specimen_type=
			(SpecimenTypes::instance())->get_by_id(static_cast<int>(
			_select_specimen_type_combo_box->GetItemData(0)));
		if(!static_cast<bool>(specimen_type)){
			_select_specimen_type_combo_box->SetCurSel(-1);
			_select_specimen_type_combo_box->EnableWindow(FALSE);
			_specimen_type_id=0;
		}else{
			_select_specimen_type_combo_box->SetCurSel(0);
			_select_specimen_type_combo_box->EnableWindow(TRUE);
			_specimen_type_id=specimen_type->get_id();
		}
	}
	//2-4.如果当前指定了期望显示的样本类型标识。
	else{
		SpecimenTypes::PtrToCSpecimenType specimen_type=
			(SpecimenTypes::instance())->get_by_id(specimen_type_id);
		int index=get_combo_box_index_by_item_data<int>(
			specimen_type_id,*_select_specimen_type_combo_box);
		if((!static_cast<bool>(specimen_type))||(index<0)){
			_select_specimen_type_combo_box->SetCurSel(-1);
			_select_specimen_type_combo_box->EnableWindow(FALSE);
			_specimen_type_id=0;
		}else{
			_select_specimen_type_combo_box->SetCurSel(index);
			_select_specimen_type_combo_box->EnableWindow(TRUE);
			_specimen_type_id=specimen_type_id;
		}
	}
	//3.设置“选择项目”下拉框内容。
	//3-1.将当前下拉框中所有信息清除。
	for(int index=_select_test_combo_box->GetCount()-1;index>=0;--index){
		_select_test_combo_box->DeleteString(index);
	}
	//3-2.获取当前系统中的项目信息，并将信息插入到“选择项目”下拉框中。
	Items::TraverseCallback callback=std::bind(&DialogAnalyzeApplication::
		init_select_test_combo_box,this,std::placeholders::_1);
	(Items::instance())->traverse(callback);
	//3-3.设置当前“项目选择”下拉框选择的内容。
	//3-3-1.声明当前操作所需变量。
	item_count=_select_test_combo_box->GetCount();
	//3-3-2.如果当前下拉框内容为空，则将其设置为无效状态。
	if(item_count<=0){
		_select_test_combo_box->SetCurSel(-1);
		_select_test_combo_box->EnableWindow(FALSE);
		_item_id=0;
	}
	//3-3-3.如果当前未指定期望显示的项目标识，则显示默认的项目标识（下拉框中的第一个项目）。
	else if(item_id<=0){
		Items::PtrToCItem item=(Items::instance())->get_by_id(
			static_cast<int>(_select_test_combo_box->GetItemData(0)));
		if(!static_cast<bool>(item)){
			_select_test_combo_box->SetCurSel(-1);
			_select_test_combo_box->EnableWindow(FALSE);
			item_count=0;
			_item_id=0;
		}else{
			_select_test_combo_box->SetCurSel(0);
			_select_test_combo_box->EnableWindow(TRUE);
			_item_id=item->get_id();
		}
	}
	//3-3-4.如果当前指定了期望显示的项目标识。
	else{
		Items::PtrToCItem item=(Items::instance())->
			get_by_id(item_id);
		int index=get_combo_box_index_by_item_data<int>(
			item_id,*_select_test_combo_box);
		if((!static_cast<bool>(item))||(index<0)){
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
	//4.获取指定模块、样本类型以及项目的分析参数，并且判断获取是否成功。
	ApplicationParameters::PtrToCParameter parameter=ApplicationParameters::
		instance()->get(_module_id,_specimen_type_id,_item_id);
	const ApplicationAnalysisData *analysis_data=0;
	if(!static_cast<bool>(parameter)){
		_select_module_combo_box->SetCurSel(-1);
		_select_module_combo_box->EnableWindow(FALSE);
		_module_id=0;
		_select_specimen_type_combo_box->SetCurSel(-1);
		_select_specimen_type_combo_box->EnableWindow(FALSE);
		_specimen_type_id=0;
		_select_test_combo_box->SetCurSel(-1);
		_select_test_combo_box->EnableWindow(FALSE);
		_item_id=0;
	}else{
		ApplicationParameter::PtrToCData data=parameter->get(
			ApplicationParameter::DATA_NAME_ANALYSIS);
		if(static_cast<bool>(data)){
			analysis_data=dynamic_cast<
				const ApplicationAnalysisData*>(data.get());
		}
	}
	//5.设置“分析方法”下拉框内容。
	if(0==analysis_data){
		_assay_method_combo_box->SetCurSel(-1);
		_assay_method_combo_box->EnableWindow(FALSE);
	}else{
		const int index=get_combo_box_index_by_item_data<int>(
			analysis_data->get_analysis_method_id(),*
			_assay_method_combo_box);
		if(index<0){
			_assay_method_combo_box->SetCurSel(-1);
			_assay_method_combo_box->EnableWindow(FALSE);
		}else{
			_assay_method_combo_box->SetCurSel(index);
			_assay_method_combo_box->EnableWindow(TRUE);
		}
	}
	//6.设置“检测时间”文本编辑框内容。
	CString text(_T(""));
	if(0==analysis_data){
		_detect_time_edit->SetWindowText(_T(""));
		_detect_time_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_checkout_incubation_time());
		_detect_time_edit->SetWindowText(text);
		_detect_time_edit->EnableWindow(TRUE);
	}
	//7.设置“孵育时间1”文本编辑框内容。
	if(0==analysis_data){
		_incubate_time_1_edit->SetWindowText(_T(""));
		_incubate_time_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_1());
		_incubate_time_1_edit->SetWindowText(text);
		_incubate_time_1_edit->EnableWindow(TRUE);
	}
	//8.设置“孵育时间2”文本编辑框内容。
	if(0==analysis_data){
		_incubate_time_2_edit->SetWindowText(_T(""));
		_incubate_time_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_2());
		_incubate_time_2_edit->SetWindowText(text);
		_incubate_time_2_edit->EnableWindow(TRUE);
	}
	//9.设置“孵育时间3”文本编辑框内容。
	if(0==analysis_data){
		_incubate_time_3_edit->SetWindowText(_T(""));
		_incubate_time_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_3());
		_incubate_time_3_edit->SetWindowText(text);
		_incubate_time_3_edit->EnableWindow(TRUE);
	}
	//10.设置“孵育时间4”文本编辑框内容。
	if(0==analysis_data){
		_incubate_time_4_edit->SetWindowText(_T(""));
		_incubate_time_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_4());
		_incubate_time_4_edit->SetWindowText(text);
		_incubate_time_4_edit->EnableWindow(TRUE);
	}
	//11.设置“稀释液编号”文本编辑框内容。
	if(0==analysis_data){
		_diluent_code_edit->SetWindowText(_T(""));
		_diluent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_diluent_code());
		_diluent_code_edit->SetWindowText(text);
		_diluent_code_edit->EnableWindow(TRUE);
	}
	//12.设置“稀释液有效期”文本编辑框内容。
	if(0==analysis_data){
		_diluent_stability_edit->SetWindowText(_T(""));
		_diluent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_diluent_stability());
		_diluent_stability_edit->SetWindowText(text);
		_diluent_stability_edit->EnableWindow(TRUE);
	}
	//13.设置“稀释方法”下拉框内容。
	if(0==analysis_data){
		_dilution_ratio_combo_box->SetCurSel(-1);
		_dilution_ratio_combo_box->EnableWindow(FALSE);
	}else{
		const int index=get_combo_box_index_by_item_data<int>(
			analysis_data->get_dilution_method_id(),*
			_dilution_ratio_combo_box);
		if(index<0){
			_dilution_ratio_combo_box->SetCurSel(-1);
			_dilution_ratio_combo_box->EnableWindow(FALSE);
		}else{
			_dilution_ratio_combo_box->SetCurSel(index);
			_dilution_ratio_combo_box->EnableWindow(TRUE);
		}
	}
	//14.设置“项目名称”文本编辑框。
	if(0==analysis_data){
		_test_name_edit->SetWindowText(_T(""));
		_test_name_edit->EnableWindow(FALSE);
	}else{
		Items::PtrToCItem item=Items::instance()->get_by_id(
			analysis_data->get_item_id());
		if(!static_cast<bool>(item)){
			_test_name_edit->SetWindowText(_T(""));
			_test_name_edit->EnableWindow(FALSE);
		}else{
			_test_name_edit->SetWindowText(item->get_alias());
			_test_name_edit->EnableWindow(TRUE);
		}
	}
	//15.设置“项目标识”文本编辑框。
	if(0==analysis_data){
		_test_id_edit->SetWindowText(_T(""));
		_test_id_edit->EnableWindow(FALSE);
	}else{
		Items::PtrToCItem item=Items::instance()->get_by_id(
			analysis_data->get_item_id());
		if(!static_cast<bool>(item)){
			_test_id_edit->SetWindowText(_T(""));
			_test_id_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%d"),item->get_id());
			_test_id_edit->SetWindowText(text);
			_test_id_edit->EnableWindow(FALSE);
		}
	}
	//16.设置“项目序号”文本编辑框。
	if(0==analysis_data){
		_test_no_edit->SetWindowText(_T(""));
		_test_no_edit->EnableWindow(FALSE);
	}else{
		Items::PtrToCItem item=Items::instance()->get_by_id(
			analysis_data->get_item_id());
		if(!static_cast<bool>(item)){
			_test_no_edit->SetWindowText(_T(""));
			_test_no_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%d"),item->get_no());
			_test_no_edit->SetWindowText(text);
			_test_no_edit->EnableWindow(FALSE);
		}
	}
	//17.设置“普通测定样本体积”文本编辑框。
	if(0==analysis_data){
		_normal_sample_volume_edit->SetWindowText(_T(""));
		_normal_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_sample_volume());
		_normal_sample_volume_edit->SetWindowText(text);
		_normal_sample_volume_edit->EnableWindow(TRUE);
	}
	//18.设置“普通测定稀释后样本体积”文本编辑框。
	if(0==analysis_data){
		_normal_dilution_sample_volume_edit->SetWindowText(_T(""));
		_normal_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_dilution_sample_volume());
		_normal_dilution_sample_volume_edit->SetWindowText(text);
		_normal_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//19.设置“普通测试稀释液体积”文本编辑框。
	if(0==analysis_data){
		_normal_dilution_volume_edit->SetWindowText(_T(""));
		_normal_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_diluent_volume());
		_normal_dilution_volume_edit->SetWindowText(text);
		_normal_dilution_volume_edit->EnableWindow(FALSE);
	}
	//20.设置“减量测定样本体积”文本编辑框。
	if(0==analysis_data){
		_decreased_sample_volume_edit->SetWindowText(_T(""));
		_decreased_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_sample_volume());
		_decreased_sample_volume_edit->SetWindowText(text);
		_decreased_sample_volume_edit->EnableWindow(FALSE);
	}
	//21.设置“减量测定稀释后样本体积”文本编辑框。
	if(0==analysis_data){
		_decreased_dilution_sample_volume_edit->SetWindowText(_T(""));
		_decreased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_dilution_sample_volume());
		_decreased_dilution_sample_volume_edit->SetWindowText(text);
		_decreased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//22.设置“减量测试稀释液体积”文本编辑框。
	if(0==analysis_data){
		_decreased_dilution_volume_edit->SetWindowText(_T(""));
		_decreased_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_diluent_volume());
		_decreased_dilution_volume_edit->SetWindowText(text);
		_decreased_dilution_volume_edit->EnableWindow(FALSE);
	}
	//23.设置“增量测定样本体积”文本编辑框。
	if(0==analysis_data){
		_increased_sample_volume_edit->SetWindowText(_T(""));
		_increased_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_sample_volume());
		_increased_sample_volume_edit->SetWindowText(text);
		_increased_sample_volume_edit->EnableWindow(FALSE);
	}
	//24.设置“增量测定稀释后样本体积”文本编辑框。
	if(0==analysis_data){
		_increased_dilution_sample_volume_edit->SetWindowText(_T(""));
		_increased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_dilution_sample_volume());
		_increased_dilution_sample_volume_edit->SetWindowText(text);
		_increased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//25.设置“增量测试稀释液体积”文本编辑框。
	if(0==analysis_data){
		_increased_dilution_volume_edit->SetWindowText(_T(""));
		_increased_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_diluent_volume());
		_increased_dilution_volume_edit->SetWindowText(text);
		_increased_dilution_volume_edit->EnableWindow(FALSE);
	}
	//26.设置“R1试剂体积”文本编辑框。
	if(0==analysis_data){
		_r1_reagent_volume_edit->SetWindowText(_T(""));
		_r1_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_volume());
		_r1_reagent_volume_edit->SetWindowText(text);
		_r1_reagent_volume_edit->EnableWindow(TRUE);
	}
	//27.设置“R1稀释液体积”文本编辑框。
	if(0==analysis_data){
		_r1_diluent_volume_edit->SetWindowText(_T(""));
		_r1_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_diluent_volume());
		_r1_diluent_volume_edit->SetWindowText(text);
		_r1_diluent_volume_edit->EnableWindow(FALSE);
	}
	//28.设置“R1试剂编码”文本编辑框。
	if(0==analysis_data){
		_r1_reagent_code_edit->SetWindowText(_T(""));
		_r1_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_code());
		_r1_reagent_code_edit->SetWindowText(text);
		_r1_reagent_code_edit->EnableWindow(TRUE);
	}
	//29.设置“R1试剂有效期”文本编辑框。
	if(0==analysis_data){
		_r1_reagent_stability_edit->SetWindowText(_T(""));
		_r1_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_stability());
		_r1_reagent_stability_edit->SetWindowText(text);
		_r1_reagent_stability_edit->EnableWindow(TRUE);
	}
	//30.设置“R2试剂体积”文本编辑框。
	if(0==analysis_data){
		_r2_reagent_volume_edit->SetWindowText(_T(""));
		_r2_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_volume());
		_r2_reagent_volume_edit->SetWindowText(text);
		_r2_reagent_volume_edit->EnableWindow(TRUE);
	}
	//31.设置“R2稀释液体积”文本编辑框。
	if(0==analysis_data){
		_r2_diluent_volume_edit->SetWindowText(_T(""));
		_r2_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_diluent_volume());
		_r2_diluent_volume_edit->SetWindowText(text);
		_r2_diluent_volume_edit->EnableWindow(FALSE);
	}
	//32.设置“R2试剂编码”文本编辑框。
	if(0==analysis_data){
		_r2_reagent_code_edit->SetWindowText(_T(""));
		_r2_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_code());
		_r2_reagent_code_edit->SetWindowText(text);
		_r2_reagent_code_edit->EnableWindow(TRUE);
	}
	//33.设置“R2试剂有效期”文本编辑框。
	if(0==analysis_data){
		_r2_reagent_stability_edit->SetWindowText(_T(""));
		_r2_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_stability());
		_r2_reagent_stability_edit->SetWindowText(text);
		_r2_reagent_stability_edit->EnableWindow(TRUE);
	}
	//34.设置“R3试剂体积”文本编辑框。
	if(0==analysis_data){
		_r3_reagent_volume_edit->SetWindowText(_T(""));
		_r3_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_volume());
		_r3_reagent_volume_edit->SetWindowText(text);
		_r3_reagent_volume_edit->EnableWindow(TRUE);
	}
	//35.设置“R2稀释液体积”文本编辑框。
	if(0==analysis_data){
		_r3_diluent_volume_edit->SetWindowText(_T(""));
		_r3_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_diluent_volume());
		_r3_diluent_volume_edit->SetWindowText(text);
		_r3_diluent_volume_edit->EnableWindow(FALSE);
	}
	//36.设置“R3试剂编码”文本编辑框。
	if(0==analysis_data){
		_r3_reagent_code_edit->SetWindowText(_T(""));
		_r3_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_code());
		_r3_reagent_code_edit->SetWindowText(text);
		_r3_reagent_code_edit->EnableWindow(TRUE);
	}
	//37.设置“R3试剂有效期”文本编辑框。
	if(0==analysis_data){
		_r3_reagent_stability_edit->SetWindowText(_T(""));
		_r3_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_stability());
		_r3_reagent_stability_edit->SetWindowText(text);
		_r3_reagent_stability_edit->EnableWindow(TRUE);
	}
	//38.设置“R4试剂体积”文本编辑框。
	if(0==analysis_data){
		_r4_reagent_volume_edit->SetWindowText(_T(""));
		_r4_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_volume());
		_r4_reagent_volume_edit->SetWindowText(text);
		_r4_reagent_volume_edit->EnableWindow(TRUE);
	}
	//39.设置“R4稀释液体积”文本编辑框。
	if(0==analysis_data){
		_r4_diluent_volume_edit->SetWindowText(_T(""));
		_r4_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_diluent_volume());
		_r4_diluent_volume_edit->SetWindowText(text);
		_r4_diluent_volume_edit->EnableWindow(FALSE);
	}
	//40.设置“R4试剂编码”文本编辑框。
	if(0==analysis_data){
		_r4_reagent_code_edit->SetWindowText(_T(""));
		_r4_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_code());
		_r4_reagent_code_edit->SetWindowText(text);
		_r4_reagent_code_edit->EnableWindow(TRUE);
	}
	//41.设置“R4试剂有效期”文本编辑框。
	if(0==analysis_data){
		_r4_reagent_stability_edit->SetWindowText(_T(""));
		_r4_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_stability());
		_r4_reagent_stability_edit->SetWindowText(text);
		_r4_reagent_stability_edit->EnableWindow(TRUE);
	}
	//42.设置“底物1体积”文本编辑框。
	if(0==analysis_data){
		_substrate_1_volume_edit->SetWindowText(_T(""));
		_substrate_1_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_volume());
		_substrate_1_volume_edit->SetWindowText(text);
		_substrate_1_volume_edit->EnableWindow(TRUE);
	}
	//43.设置“底物1编号”文本编辑框。
	if(0==analysis_data){
		_substrate_1_code_edit->SetWindowText(_T(""));
		_substrate_1_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_code());
		_substrate_1_code_edit->SetWindowText(text);
		_substrate_1_code_edit->EnableWindow(TRUE);
	}
	//44.设置“底物1有效期”文本编辑框。
	if(0==analysis_data){
		_substrate_1_stability_edit->SetWindowText(_T(""));
		_substrate_1_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_stability());
		_substrate_1_stability_edit->SetWindowText(text);
		_substrate_1_stability_edit->EnableWindow(TRUE);
	}
	//45.设置“底物2体积”文本编辑框。
	if(0==analysis_data){
		_substrate_2_volume_edit->SetWindowText(_T(""));
		_substrate_2_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_volume());
		_substrate_2_volume_edit->SetWindowText(text);
		_substrate_2_volume_edit->EnableWindow(TRUE);
	}
	//46.设置“底物2编号”文本编辑框。
	if(0==analysis_data){
		_substrate_2_code_edit->SetWindowText(_T(""));
		_substrate_2_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_2_code());
		_substrate_2_code_edit->SetWindowText(text);
		_substrate_2_code_edit->EnableWindow(TRUE);
	}
	//47.设置“底物2有效期”文本编辑框。
	if(0==analysis_data){
		_substrate_2_stability_edit->SetWindowText(_T(""));
		_substrate_2_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_2_stability());
		_substrate_2_stability_edit->SetWindowText(text);
		_substrate_2_stability_edit->EnableWindow(TRUE);
	}
	//48.设置“底物3体积”文本编辑框。
	if(0==analysis_data){
		_substrate_3_volume_edit->SetWindowText(_T(""));
		_substrate_3_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_volume());
		_substrate_3_volume_edit->SetWindowText(text);
		_substrate_3_volume_edit->EnableWindow(TRUE);
	}
	//49.设置“底物3编号”文本编辑框。
	if(0==analysis_data){
		_substrate_3_code_edit->SetWindowText(_T(""));
		_substrate_3_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_code());
		_substrate_3_code_edit->SetWindowText(text);
		_substrate_3_code_edit->EnableWindow(TRUE);
	}
	//50.设置“底物3有效期”文本编辑框。
	if(0==analysis_data){
		_substrate_3_stability_edit->SetWindowText(_T(""));
		_substrate_3_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_stability());
		_substrate_3_stability_edit->SetWindowText(text);
		_substrate_3_stability_edit->EnableWindow(TRUE);
	}
	//51.设置“缓冲液体积”文本编辑框。
	if(0==analysis_data){
		_buffer_solution_volume_edit->SetWindowText(_T(""));
		_buffer_solution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_volume());
		_buffer_solution_volume_edit->SetWindowText(text);
		_buffer_solution_volume_edit->EnableWindow(TRUE);
	}
	//52.设置“缓冲液编号”文本编辑框。
	if(0==analysis_data){
		_buffer_solution_code_edit->SetWindowText(_T(""));
		_buffer_solution_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_code());
		_buffer_solution_code_edit->SetWindowText(text);
		_buffer_solution_code_edit->EnableWindow(TRUE);
	}
	//53.设置“缓冲液有效期”文本编辑框。
	if(0==analysis_data){
		_buffer_solution_stability_edit->SetWindowText(_T(""));
		_buffer_solution_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_stability());
		_buffer_solution_stability_edit->SetWindowText(text);
		_buffer_solution_stability_edit->EnableWindow(TRUE);
	}
	//54.设置“删除”按钮。
	if(0==analysis_data){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//55.设置“读取参数”按钮。
	_read_parameters_button->EnableWindow(TRUE);
	//56.设置“添加项目”按钮。
	_add_application_button->EnableWindow(TRUE);
	//57.设置“写参数”按钮。
	if(0==analysis_data){
		_write_parameters_button->EnableWindow(FALSE);
	}else{
		_write_parameters_button->EnableWindow(TRUE);
	}
	//58.设置“确认”按钮。
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: 判断当前控件中的数据是否发生改变。
 * param: --
 * return: 如果当前控件中的数据发生改变则返回TRUE，否则返回FALSE。
 */
BOOL DialogAnalyzeApplication::is_data_of_controls_changed() const{
	//1.获取当前界面中指定项目标识的应用参数，并且判断获取是否成功。
	ApplicationParameters::PtrToCParameter parameter=
		ApplicationParameters::instance()->get(
		_module_id,_specimen_type_id,_item_id);
	if(!static_cast<bool>(parameter)){//如果未能获取指定参数信息，则认为无变化。
		return(FALSE);
	}
	ApplicationParameter::PtrToCData data=parameter->get(
		ApplicationParameter::DATA_NAME_ANALYSIS);
	assert(static_cast<bool>(data));//断言获取的分析数据合法有效。
	const ApplicationAnalysisData *analysis_data=
		dynamic_cast<const ApplicationAnalysisData*>(data.get());
	//2.检测“分析方法”下拉框是否发生变化。
	int item=_assay_method_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	int value=static_cast<int>(_assay_method_combo_box->GetItemData(item));
	if(analysis_data->get_analysis_method_id()!=value){
		return(TRUE);
	}
	//3.检测“检测时间”文本编辑框是否发生变化。
	CString text(_T(""));
	_detect_time_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_checkout_incubation_time()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//4.检测“孵育时间1”文本编辑框是否发生变化。
	_incubate_time_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_1()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//5.检测“孵育时间2”文本编辑框是否发生变化。
	_incubate_time_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_2()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//6.检测“孵育时间3”文本编辑框是否发生变化。
	_incubate_time_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_3()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//7.检测“孵育时间4”文本编辑框是否发生变化。
	_incubate_time_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_4()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//8.检测“稀释液编号”文本编辑框是否发生变化。
	_diluent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_diluent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//9.检测“稀释液有效期”文本编辑框是否发生变化。
	_diluent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_diluent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//10.检测“稀释方法”下拉框是否发生变化。
	item=_dilution_ratio_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_dilution_ratio_combo_box->
		GetItemData(item));
	if(analysis_data->get_dilution_method_id()!=value){
		return(TRUE);
	}
	//11.检测“项目名称”文本编辑框是否发生变化。
	_test_name_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	Items::PtrToCItem item_t=(Items::instance())->
		get_by_id(_item_id);
	assert(static_cast<bool>(item_t));
	if(item_t->get_alias()!=text){
		return(TRUE);
	}
	//12.检测“项目标识”文本编辑框是否发生变化。
	_test_id_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(item_t->get_id()!=MtCharacterSet::
		to_integer(text)){
		return(TRUE);
	}
	//13.检测“项目序号”文本编辑框是否发生变化。
	_test_no_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(item_t->get_no()!=MtCharacterSet::
		to_integer(text)){
		return(TRUE);
	}
	//14.检测“普通测定样本体积”文本编辑框是否发生变化。
	_normal_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//15.检测“普通测定稀释后样本体积”文本编辑框是否发生变化。
	_normal_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//16.检测“普通测定稀释液体积”文本编辑框是否发生变化。
	_normal_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//17.检测“减量测定样本体积”文本编辑框是否发生变化。
	_decreased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//18.检测“减量测定稀释后样本体积”文本编辑框是否发生变化。
	_decreased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//19.检测“减量测定稀释液体积”文本编辑框是否发生变化。
	_decreased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//20.检测“增量测定样本体积”文本编辑框是否发生变化。
	_increased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//21.检测“增量测定稀释后样本体积”文本编辑框是否发生变化。
	_increased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//22.检测“增量测定稀释液体积”文本编辑框是否发生变化。
	_increased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//23.检测“R1试剂体积”文本编辑框是否发生变化。
	_r1_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//24.检测“R1稀释液体积”文本编辑框是否发生变化。
	_r1_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//25.检测“R1试剂编号”文本编辑框是否发生变化。
	_r1_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//26.检测“R1试剂有效期”文本编辑框是否发生变化。
	_r1_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//27.检测“R2试剂体积”文本编辑框是否发生变化。
	_r2_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//28.检测“R2稀释液体积”文本编辑框是否发生变化。
	_r2_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//29.检测“R2试剂编号”文本编辑框是否发生变化。
	_r2_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//30.检测“R2试剂有效期”文本编辑框是否发生变化。
	_r2_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//31.检测“R3试剂体积”文本编辑框是否发生变化。
	_r3_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//32.检测“R3稀释液体积”文本编辑框是否发生变化。
	_r3_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//33.检测“R3试剂编号”文本编辑框是否发生变化。
	_r3_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//34.检测“R3试剂有效期”文本编辑框是否发生变化。
	_r3_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//35.检测“R4试剂体积”文本编辑框是否发生变化。
	_r4_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//36.检测“R4稀释液体积”文本编辑框是否发生变化。
	_r4_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//37.检测“R4试剂编号”文本编辑框是否发生变化。
	_r4_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//38.检测“R4试剂有效期”文本编辑框是否发生变化。
	_r4_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//39.检测“底物1体积”文本编辑框是否发生变化。
	_substrate_1_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//40.检测“底物1编号”文本编辑框是否发生变化。
	_substrate_1_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//41.检测“底物1有效期”文本编辑框是否发生变化。
	_substrate_1_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}

	//42.检测“底物2体积”文本编辑框是否发生变化。
	_substrate_2_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//43.检测“底物2编号”文本编辑框是否发生变化。
	_substrate_2_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//44.检测“底物2有效期”文本编辑框是否发生变化。
	_substrate_2_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//45.检测“底物3体积”文本编辑框是否发生变化。
	_substrate_3_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//46.检测“底物3编号”文本编辑框是否发生变化。
	_substrate_3_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//47.检测“底物3有效期”文本编辑框是否发生变化。
	_substrate_3_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//48.检测“缓冲液体积”文本编辑框是否发生变化。
	_buffer_solution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//49.检测“缓冲液编号”文本编辑框是否发生变化。
	_buffer_solution_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//50.检测“缓冲液有效期”文本编辑框是否发生变化。
	_buffer_solution_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//51.程序运行到此直接返回。
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * brief: 获取控件中的数据。
 * param: item_alias - 输出的项目别名。
 *        data - 输出的应用分析参数。
 * return: 如果当前函数执行成功，返回值大于等于零，否则返回值小于零。
 */
int DialogAnalyzeApplication::get_data_from_controls(
	CString &item_alias,ApplicationAnalysisData &data){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.获取当前“选择模块”下拉框内容。
	if(_module_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING175),this);
		_select_module_combo_box->SetFocus();
		return(-1);
	}
	data.set_module_id(_module_id);
	//3.获取当前的“选择样本类型”下拉框内容。
	if(_specimen_type_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING176),this);
		_select_specimen_type_combo_box->SetFocus();
		return(-2);
	}
	data.set_specimen_type_id(_specimen_type_id);
	//4.获取当前“选择项目”下拉框内容。
	if(_item_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING159),this);
		_select_test_combo_box->SetFocus();
		return(-3);
	}
	data.set_item_id(_item_id);
	//5.获取当前的“分析方法”下拉框内容。
	int selection=_assay_method_combo_box->GetCurSel();
	if(selection<0){
		WarningMessageBox(theme->get_string(IDS_STRING183),this);
		_assay_method_combo_box->SetFocus();
		return(-4);
	}
	data.set_analysis_method_id(static_cast<int>(
		_assay_method_combo_box->GetItemData(selection)));
	//6.获取当前“检测孵育时间”文本编辑框内容。
	CString text(_T(""));
	_detect_time_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING184),this);
		_detect_time_edit->SetFocus();
		return(-5);
	}
	data.set_checkout_incubation_time(MtCharacterSet::to_integer(text));
	//7.获取当前“孵育时间1”文本编辑框内容。
	_incubate_time_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING185),this);
		_incubate_time_1_edit->SetFocus();
		return(-6);
	}
	data.set_incubation_time_1(MtCharacterSet::to_integer(text));
	//8.获取当前“孵育时间2”文本编辑框内容。
	_incubate_time_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING186),this);
		_incubate_time_2_edit->SetFocus();
		return(-7);
	}
	data.set_incubation_time_2(MtCharacterSet::to_integer(text));
	//9.获取当前“孵育时间3”文本编辑框内容。
	_incubate_time_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING187),this);
		_incubate_time_3_edit->SetFocus();
		return(-8);
	}
	data.set_incubation_time_3(MtCharacterSet::to_integer(text));
	//10.获取当前“孵育时间4”文本编辑框内容。
	_incubate_time_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING188),this);
		_incubate_time_4_edit->SetFocus();
		return(-9);
	}
	data.set_incubation_time_4(MtCharacterSet::to_integer(text));
	//11.获取当前“稀释液编号”文本编辑框内容。
	_diluent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING189),this);
		_diluent_code_edit->SetFocus();
		return(-10);
	}
	data.set_diluent_code(MtCharacterSet::to_integer(text));
	//12.获取当前“稀释液有效期”文本编辑框内容。
	_diluent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING190),this);
		_diluent_stability_edit->SetFocus();
		return(-11);
	}
	data.set_diluent_stability(MtCharacterSet::to_integer(text));
	//13.获取当前“稀释方法”下拉框内容。
	selection=_dilution_ratio_combo_box->GetCurSel();
	if(selection<0){
		WarningMessageBox(theme->get_string(IDS_STRING191),this);
		_dilution_ratio_combo_box->SetFocus();
		return(-12);
	}
	data.set_dilution_method_id(static_cast<int>(
		_dilution_ratio_combo_box->GetItemData(selection)));
	//14.获取当前“项目名称”文本编辑框内容。
	_test_name_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING192),this);
		_test_name_edit->SetFocus();
		return(-13);
	}
	item_alias=text;
	//15.获取当前“普通测定样本体积”文本编辑框内容。
	_normal_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING193),this);
		_normal_sample_volume_edit->SetFocus();
		return(-14);
	}
	data.set_normal_sample_volume(MtCharacterSet::to_integer(text));
	//16.获取当前“普通测定稀释后样本体积”文本编辑框内容。
	_normal_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING194),this);
		_normal_dilution_sample_volume_edit->SetFocus();
		return(-15);
	}
	data.set_normal_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//17.获取当前“普通测定稀释液体积”文本编辑框内容。
	_normal_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING195),this);
		_normal_dilution_volume_edit->SetFocus();
		return(-16);
	}
	data.set_normal_diluent_volume(MtCharacterSet::to_integer(text));
	//18.获取当前“减量测定样本体积”文本编辑框内容。
	_decreased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING196),this);
		_decreased_sample_volume_edit->SetFocus();
		return(-17);
	}
	data.set_decrease_sample_volume(MtCharacterSet::to_integer(text));
	//19.获取当前“减量测定稀释后样本体积”文本编辑框内容。
	_decreased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING197),this);
		_decreased_dilution_sample_volume_edit->SetFocus();
		return(-18);
	}
	data.set_decrease_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//20.获取当前“减量测定稀释液体积”文本编辑框内容。
	_decreased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING198),this);
		_decreased_dilution_volume_edit->SetFocus();
		return(-19);
	}
	data.set_decrease_diluent_volume(MtCharacterSet::to_integer(text));
	//21.获取当前“增量测定样本体积”文本编辑框内容。
	_increased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING199),this);
		_increased_sample_volume_edit->SetFocus();
		return(-20);
	}
	data.set_increase_sample_volume(MtCharacterSet::to_integer(text));
	//22.获取当前“增量测定稀释后样本体积”文本编辑框内容。
	_increased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING200),this);
		_increased_dilution_sample_volume_edit->SetFocus();
		return(-21);
	}
	data.set_increase_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//23.获取当前“减量测定稀释液体积”文本编辑框内容。
	_increased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING201),this);
		_increased_dilution_volume_edit->SetFocus();
		return(-22);
	}
	data.set_increase_diluent_volume(MtCharacterSet::to_integer(text));
	//24.获取当前“R1试剂体积”文本编辑框内容。
	_r1_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING202),this);
		_r1_reagent_volume_edit->SetFocus();
		return(-23);
	}
	data.set_r1_reagent_volume(MtCharacterSet::to_integer(text));
	//25.获取当前“R1稀释液体积”文本编辑框内容。
	_r1_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING203),this);
		_r1_diluent_volume_edit->SetFocus();
		return(-24);
	}
	data.set_r1_diluent_volume(MtCharacterSet::to_integer(text));
	//26.获取当前“R1试剂编号”文本编辑框内容。
	_r1_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING204),this);
		_r1_reagent_code_edit->SetFocus();
		return(-25);
	}
	data.set_r1_reagent_code(MtCharacterSet::to_integer(text));
	//27.获取当前“R1试剂有效期”文本编辑框内容。
	_r1_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING205),this);
		_r1_reagent_stability_edit->SetFocus();
		return(-26);
	}
	data.set_r1_reagent_stability(MtCharacterSet::to_integer(text));
	//28.获取当前“R2试剂体积”文本编辑框内容。
	_r2_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING206),this);
		_r2_reagent_volume_edit->SetFocus();
		return(-27);
	}
	data.set_r2_reagent_volume(MtCharacterSet::to_integer(text));
	//29.获取当前“R2稀释液体积”文本编辑框内容。
	_r2_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING207),this);
		_r2_diluent_volume_edit->SetFocus();
		return(-28);
	}
	data.set_r2_diluent_volume(MtCharacterSet::to_integer(text));
	//30.获取当前“R2试剂编号”文本编辑框内容。
	_r2_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING208),this);
		_r2_reagent_code_edit->SetFocus();
		return(-29);
	}
	data.set_r2_reagent_code(MtCharacterSet::to_integer(text));
	//31.获取当前“R2试剂有效期”文本编辑框内容。
	_r2_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING209),this);
		_r2_reagent_stability_edit->SetFocus();
		return(-30);
	}
	data.set_r2_reagent_stability(MtCharacterSet::to_integer(text));
	//32.获取当前“R3试剂体积”文本编辑框内容。
	_r3_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING210),this);
		_r3_reagent_volume_edit->SetFocus();
		return(-31);
	}
	data.set_r3_reagent_volume(MtCharacterSet::to_integer(text));
	//33.获取当前“R3稀释液体积”文本编辑框内容。
	_r3_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING211),this);
		_r3_diluent_volume_edit->SetFocus();
		return(-32);
	}
	data.set_r3_diluent_volume(MtCharacterSet::to_integer(text));
	//34.获取当前“R3试剂编号”文本编辑框内容。
	_r3_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING212),this);
		_r3_reagent_code_edit->SetFocus();
		return(-33);
	}
	data.set_r3_reagent_code(MtCharacterSet::to_integer(text));
	//35.获取当前“R3试剂有效期”文本编辑框内容。
	_r3_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING213),this);
		_r3_reagent_stability_edit->SetFocus();
		return(-34);
	}
	data.set_r3_reagent_stability(MtCharacterSet::to_integer(text));
	//36.获取当前“R4试剂体积”文本编辑框内容。
	_r4_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING214),this);
		_r4_reagent_volume_edit->SetFocus();
		return(-35);
	}
	data.set_r4_reagent_volume(MtCharacterSet::to_integer(text));
	//37.获取当前“R4稀释液体积”文本编辑框内容。
	_r4_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING215),this);
		_r4_diluent_volume_edit->SetFocus();
		return(-36);
	}
	data.set_r4_diluent_volume(MtCharacterSet::to_integer(text));
	//38.获取当前“R4试剂编号”文本编辑框内容。
	_r4_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING216),this);
		_r4_reagent_code_edit->SetFocus();
		return(-37);
	}
	data.set_r4_reagent_code(MtCharacterSet::to_integer(text));
	//39.获取当前“R4试剂有效期”文本编辑框内容。
	_r4_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING217),this);
		_r4_reagent_stability_edit->SetFocus();
		return(-38);
	}
	data.set_r4_reagent_stability(MtCharacterSet::to_integer(text));
	//40.获取当前“底物1体积”文本编辑框内容。
	_substrate_1_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING218),this);
		_substrate_1_volume_edit->SetFocus();
		return(-39);
	}
	data.set_substrate_1_volume(MtCharacterSet::to_integer(text));
	//41.获取当前“底物1编号”文本编辑框内容。
	_substrate_1_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING219),this);
		_substrate_1_code_edit->SetFocus();
		return(-40);
	}
	data.set_substrate_1_code(MtCharacterSet::to_integer(text));
	//42.获取当前“底物1有效期”文本编辑框内容。
	_substrate_1_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING220),this);
		_substrate_1_stability_edit->SetFocus();
		return(-41);
	}
	data.set_substrate_1_stability(MtCharacterSet::to_integer(text));
	//43.获取当前“底物2体积”文本编辑框内容。
	_substrate_2_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING221),this);
		_substrate_2_volume_edit->SetFocus();
		return(-42);
	}
	data.set_substrate_2_volume(MtCharacterSet::to_integer(text));
	//44.获取当前“底物2编号”文本编辑框内容。
	_substrate_2_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING222),this);
		_substrate_2_code_edit->SetFocus();
		return(-43);
	}
	data.set_substrate_2_code(MtCharacterSet::to_integer(text));
	//45.获取当前“底物2有效期”文本编辑框内容。
	_substrate_2_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING223),this);
		_substrate_2_stability_edit->SetFocus();
		return(-44);
	}
	data.set_substrate_2_stability(MtCharacterSet::to_integer(text));
	//46.获取当前“底物3体积”文本编辑框内容。
	_substrate_3_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING224),this);
		_substrate_3_volume_edit->SetFocus();
		return(-45);
	}
	data.set_substrate_3_volume(MtCharacterSet::to_integer(text));
	//47.获取当前“底物3编号”文本编辑框内容。
	_substrate_3_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING225),this);
		_substrate_3_code_edit->SetFocus();
		return(-46);
	}
	data.set_substrate_3_code(MtCharacterSet::to_integer(text));
	//48.获取当前“底物3有效期”文本编辑框内容。
	_substrate_3_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING226),this);
		_substrate_3_stability_edit->SetFocus();
		return(-47);
	}
	data.set_substrate_3_stability(MtCharacterSet::to_integer(text));
	//49.获取当前“缓冲液体积”文本编辑框内容。
	_buffer_solution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING227),this);
		_buffer_solution_volume_edit->SetFocus();
		return(-48);
	}
	data.set_buffer_solution_volume(MtCharacterSet::to_integer(text));
	//50.获取当前“缓冲液编号”文本编辑框内容。
	_buffer_solution_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING228),this);
		_buffer_solution_code_edit->SetFocus();
		return(-49);
	}
	data.set_buffer_solution_code(MtCharacterSet::to_integer(text));
	//51.获取当前“缓冲液有效期”文本编辑框内容。
	_buffer_solution_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING229),this);
		_buffer_solution_stability_edit->SetFocus();
		return(-50);
	}
	data.set_buffer_solution_stability(MtCharacterSet::to_integer(text));
	//52.如果当前应用分析参数不合法，则直接返回错误。
	//52-1.判断当前分析参数是否合法。
	const int result=data.is_valid(&text);
	//52-2.如果当前分析参数不合法，则给予用户警告并返回错误。
	if(result<0){
		WarningMessageBox(text,this);
		if(-1==result){
			_select_module_combo_box->SetFocus();
		}else if(-2==result){
			_select_specimen_type_combo_box->SetFocus();
		}else if(-3==result){
			_select_test_combo_box->SetFocus();
		}else if(-4==result){
			_assay_method_combo_box->SetFocus();
		}else if(-5==result){
			_detect_time_edit->SetFocus();
		}else if(-6==result){
			_incubate_time_1_edit->SetFocus();
		}else if(-7==result){
			_incubate_time_2_edit->SetFocus();
		}else if(-8==result){
			_incubate_time_3_edit->SetFocus();
		}else if(-9==result){
			_incubate_time_4_edit->SetFocus();
		}else if(-10==result){
			_diluent_code_edit->SetFocus();
		}else if(-11==result){
			_diluent_stability_edit->SetFocus();
		}else if(-12==result){
			_dilution_ratio_combo_box->SetFocus();
		}else if(-13==result){
			_normal_sample_volume_edit->SetFocus();
		}else if(-14==result){
			_normal_dilution_sample_volume_edit->SetFocus();
		}else if(-15==result){
			_normal_dilution_volume_edit->SetFocus();
		}else if(-16==result){
			_decreased_dilution_volume_edit->SetFocus();
		}else if(-17==result){
			_decreased_dilution_sample_volume_edit->SetFocus();
		}else if(-18==result){
			_decreased_dilution_volume_edit->SetFocus();
		}else if(-19==result){
			_increased_dilution_volume_edit->SetFocus();
		}else if(-20==result){
			_increased_dilution_sample_volume_edit->SetFocus();
		}else if(-21==result){
			_increased_dilution_volume_edit->SetFocus();
		}else if(-22==result){
			_r1_reagent_volume_edit->SetFocus();
		}else if(-23==result){
			_r1_diluent_volume_edit->SetFocus();
		}else if(-24==result){
			_r1_reagent_code_edit->SetFocus();
		}else if(-25==result){
			_r1_reagent_stability_edit->SetFocus();
		}else if(-26==result){
			_r2_reagent_volume_edit->SetFocus();
		}else if(-27==result){
			_r2_diluent_volume_edit->SetFocus();
		}else if(-28==result){
			_r2_reagent_code_edit->SetFocus();
		}else if(-29==result){
			_r2_reagent_stability_edit->SetFocus();
		}else if(-30==result){
			_r3_reagent_volume_edit->SetFocus();
		}else if(-31==result){
			_r3_diluent_volume_edit->SetFocus();
		}else if(-32==result){
			_r3_reagent_code_edit->SetFocus();
		}else if(-33==result){
			_r3_reagent_stability_edit->SetFocus();
		}else if(-34==result){
			_r4_reagent_volume_edit->SetFocus();
		}else if(-35==result){
			_r4_diluent_volume_edit->SetFocus();
		}else if(-36==result){
			_r4_reagent_code_edit->SetFocus();
		}else if(-37==result){
			_r4_reagent_stability_edit->SetFocus();
		}else if(-38==result){
			_substrate_1_volume_edit->SetFocus();
		}else if(-39==result){
			_substrate_1_code_edit->SetFocus();
		}else if(-40==result){
			_substrate_1_stability_edit->SetFocus();
		}else if(-41==result){
			_substrate_2_volume_edit->SetFocus();
		}else if(-42==result){
			_substrate_2_code_edit->SetFocus();
		}else if(-43==result){
			_substrate_2_stability_edit->SetFocus();
		}else if(-44==result){
			_substrate_3_volume_edit->SetFocus();
		}else if(-45==result){
			_substrate_3_code_edit->SetFocus();
		}else if(-46==result){
			_substrate_3_stability_edit->SetFocus();
		}else if(-47==result){
			_buffer_solution_volume_edit->SetFocus();
		}else if(-48==result){
			_buffer_solution_code_edit->SetFocus();
		}else if(-49==result){
			_buffer_solution_stability_edit->SetFocus();
		}
		return(-51);
	}
	//53.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: 提交控件的数据到指定的数据库中。
 * param: database - 指定的数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DialogAnalyzeApplication::commit_data_of_controls(Database &database){
	//1.获取当前界面中输入的数据，并且判断获取是否成功。
	CString item_alias(_T(""));
	ApplicationAnalysisData data;
	if(get_data_from_controls(item_alias,data)<0){
		return(-1);
	}
	//2.向数据库提交修改的数据，并且判断提交是否成功。
	//2-1.开启数据库事务，准备向数据库中提交修改数据。
	if(database.begin_trans()<0){
		return(-2);
	}
	//2-2.先向数据库提交修改的项目信息。
	Items::PtrToCItem item=(Items::instance())->get_by_id(_item_id);
	if(!static_cast<bool>(item)){
		database.rollback_trans();
		return(-3);
	}
	Item item_t(*item);
	item_t.set_alias(item_alias);
	if(item_t.commit(2,database)<0){
		database.rollback_trans();
		return(-4);
	}
	//2-3.向数据库提交修改的应用分析参数。
	if(data.commit(2,database)<0){
		database.rollback_trans();
		return(-5);
	}
	//2-4.修改应用分析参数中的内存数据。
	if(ApplicationParameters::instance()->modify(data)<0){
		database.rollback_trans();
		return(-6);
	}
	//2-5.修改项目信息的相应内存数据。
	Items::instance()->modify(item_t);
	//2-6.提交数据库事务，并且判断提交是否成功。
	if(database.commit_trans()<0){
		database.rollback_trans();
		Items::instance()->update(database);
		ApplicationParameters::instance()->update(database);
		return(-7);
	}
	//3.程序运行到此成功返回。
	return(0);
}