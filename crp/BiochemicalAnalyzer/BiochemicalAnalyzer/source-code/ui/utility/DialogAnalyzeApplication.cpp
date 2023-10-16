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
 * brief: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
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
 * breif: ����������
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
 * brief: ֧��DDV/DDX��
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
 * breif: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogAnalyzeApplication::OnInitDialog(){
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
BOOL DialogAnalyzeApplication::OnCommand(WPARAM wParam,LPARAM lParam){
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
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogAnalyzeApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
	//2.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
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
 * breif: ��ѡ��ģ�顱������ģ������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectModule(){
	// TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ�û�ѡ���ģ���ʶ��
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
	//3.����û�ѡ���ģ���ʶ���뵱ǰģ���ʶ��ͬ����ֱ�ӷ��ء�
	if(module_id==_module_id){
		return;
	}
	//4.�����ǰ����Ĳ��������ı䡣
	if(is_data_of_controls_changed()){
		//4-1.�����û��Ƿ񱣴浱ǰ������
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING307),this);
		//4-2.�����ǰ�û�ѡ��ȡ������ť��
		if(IDCANCEL==result){
			//4-1-1.���οؼ����ݵĸ��¡�
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.�ظ���ǰ������ѡ�����ݡ�
			_select_module_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_module_id,*_select_module_combo_box));
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
				_select_module_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_module_id,*_select_module_combo_box));
				//4-4-3.�������е���ֱ�ӷ��ء�
				return;
			}
		}
	}
	//5.��ʾ��ѡ���ģ���Ӧ�ò�����Ϣ��
	//5-1.����������Ϣ������
	WPARAM wParam=0;
	wParam|=(module_id&0xFF);
	wParam<<=8;
	wParam|=(_specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(_item_id&0xFFFF);
	//5-2.������Ӧ��Ϣ�����½������ݡ�
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnCbnSelchangeComboSelectSpecimenType
 * brief: ��ѡ���������͡��������������ͱ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectSpecimenType(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ�û�ѡ����������ͱ�ʶ��
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
	//3.����û�ѡ����������ͱ�ʶ���뵱ǰ�������ͱ�ʶ��ͬ����ֱ�ӷ��ء�
	if(specimen_type_id==_specimen_type_id){
		return;
	}
	//4.�����ǰ����Ĳ��������ı䡣
	if(is_data_of_controls_changed()){
		//4-1.�����û��Ƿ񱣴浱ǰ������
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING307),this);
		//4-2.�����ǰ�û�ѡ��ȡ������ť��
		if(IDCANCEL==result){
			//4-1-1.���οؼ����ݵĸ��¡�
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//4-1-2.�ظ���ǰ������ѡ�����ݡ�
			_select_specimen_type_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_specimen_type_id,*_select_specimen_type_combo_box));
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
				_select_specimen_type_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_specimen_type_id,*_select_specimen_type_combo_box));
				//4-4-3.�������е���ֱ�ӷ��ء�
				return;
			}
		}
	}
	//5.��ʾ��ѡ���ģ���Ӧ�ò�����Ϣ��
	//5-1.����������Ϣ������
	WPARAM wParam=0;
	wParam|=(_module_id&0xFF);
	wParam<<=8;
	wParam|=(specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(_item_id&0xFFFF);
	//5-2.������Ӧ��Ϣ�����½������ݡ�
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: ��ѡ����Ŀ����������Ŀ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnCbnSelchangeComboSelectTest(){
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
			theme->get_string(IDS_STRING307),this);
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
	//5-1.����������Ϣ������
	WPARAM wParam=0;
	wParam|=(_module_id&0xFF);
	wParam<<=8;
	wParam|=(_specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(item_id&0xFFFF);
	//5-2.������Ӧ��Ϣ�����½������ݡ�
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnBnClickedButtonAddApplication
 * brief: �û�����������Ŀ����ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonAddApplication(){
	// TODO: Add your control notification handler code here
	//1.������ǰ�������������
	DialogAddApplication dlg;
	//2.�����Ŀ��ӶԻ���ʧ���˳���
	if(IDCANCEL==dlg.DoModal()){
		return;
	}
	//3.�����Ŀ��ӶԻ���ɹ��˳������¿ؼ���
	//3-1.������Ϣ������
	const int module_id=dlg.get_module_id();
	const int specimen_type_id=dlg.get_specimen_type_id();
	const int item_id=dlg.get_item_id();
	WPARAM wParam=0;
	wParam|=(module_id&0xFF);
	wParam<<=8;
	wParam|=(specimen_type_id&0xFF);
	wParam<<=16;
	wParam|=(item_id&0xFFFF);
	//3-2.���͸��¿ؼ���Ϣ��
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		wParam,0);
}

/**
 * name: OnBnClickedButtonDelete
 * brief: �û������ɾ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonDelete(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	Database *database=(DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//2.��ȡ��ǰ����ɾ������Ŀ��ʶ��
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING182),this);
		return;
	}
	const int item_id=static_cast<int>(
		_select_test_combo_box->GetItemData(item));
	//3.ѯ���û��Ƿ�����ɾ����ǰ��Ŀ��
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING305),this)){
		return;
	}
	//4.ɾ����ǰ��Ŀ�Ĳ�����Ϣ�������ж�ɾ���Ƿ�ɹ���
	//4-1.�������ݿ�����
	if(database->begin_trans()<0){
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-2.ɾ����ǰ��Ŀ���������ݿ��е������Ϣ�������ж�ɾ���Ƿ�ɹ���
	if((ApplicationParameters::instance())->commit(item_id,3,*database,FALSE)<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-3.ɾ����ǰ��Ŀ�����ݿ��е������Ϣ�������ж�ɾ���Ƿ�ɹ���
	if((Items::instance())->commit(item_id,3,*database)<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-4.ɾ����ǰ��Ŀ������Ӧ���ڴ����ݣ������ж�ɾ���Ƿ�ɹ���
	if((ApplicationParameters::instance())->remove(item_id)<0){
		database->rollback_trans();
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-5.ɾ����ǰ��Ŀ��Ӧ���ڴ����ݣ������ж�ɾ���Ƿ�ɹ���
	if((Items::instance())->remove(item_id)<0){
		database->rollback_trans();
		Items::instance()->update(*database);
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//4-6.�ύ��ǰ���ݿ����񣬲����ж��ύ�Ƿ�ɹ���
	if(database->commit_trans()<0){
		database->rollback_trans();
		Items::instance()->update(*database);
		ApplicationParameters::instance()->update(*database);
		WarningMessageBox(theme->get_string(IDS_STRING230),this);
		return;
	}
	//5.ˢ�µ�ǰ���档
	GetParent()->SendMessage(
		WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		0,0);
}

/**
 * name: OnBnClickedButtonOk
 * brief: �û������ȷ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::OnBnClickedButtonOk(){
	// TODO: Add your control notification handler code here
	//1.�ύ��ǰ�����пؼ����ݡ�
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
	//2.����OnCommand��Ӧ��
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//3.���µ�ǰ�����пؼ����ݡ�
	update_data_for_controls(_module_id,_specimen_type_id,_item_id);
}

/**
 * name: OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID
 * brief: ͨ��ģ���ʶ���������ͱ�ʶ����Ŀ��ʶ���½���ؼ����ݡ�
 * param: wParam - ģ���ʶ����8λ�����������ͱ�ʶ����8λ������Ŀ��ʶ����16λ����
 *        lParam - �����塣
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogAnalyzeApplication::
	OnUpdateDataForControlsByModuleIDAndSpecimenTypeIDAndItemID(
	WPARAM wParam,LPARAM /*lParam*/){
	//1.���ε�ǰ����������Ϣ��Ӧ��
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.������ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ��
	const int item_id=wParam&0xFFFF;
	const int specimen_type_id=(wParam>>16)&0xFF;
	const int module_id=(wParam>>24)&0xFF;
	//2.���µ�ǰ����ؼ����ݡ�
	update_data_for_controls(module_id,specimen_type_id,item_id);
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
LRESULT DialogAnalyzeApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.��������е�����û�з����仯����ֱ�ӷ��ء�
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.ѯ���û��Ƿ�ϣ�����浱ǰ���ݡ�
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING307),this);
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
void DialogAnalyzeApplication::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	MtAutoReset<BOOL> auto_reset(_is_command_message_masked,TRUE,FALSE);
	//2.��ʼ����ǰ�Ի����пؼ���
	//2-1.��ʼ����̬�ı���
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
	//2-2.��ʼ��������
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
	//2-3.��ʼ���ı��༭��
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
	//2-5.��ʼ����ť��
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
	//3.��ʼ�����֡�
	//3-1.��ʼ���Ӳ���1��
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
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_select_specimen_type_static,120);
	_child_layout_2->add_fixed_window(_select_specimen_type_combo_box,150);
	_child_layout_2->add_spacing(10);
	_child_layout_2->add_fixed_window(_diluent_stability_ratio_static,200);
	_child_layout_2->add_fixed_window(_diluent_code_edit,100);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_diluent_stability_edit,50);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_dilution_ratio_combo_box,100);
	//3-3.��ʼ���Ӳ���3��
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
	//3-4.��ʼ���Ӳ���4��
	_child_layout_4->add_fixed_window(_normal_static,100);
	_child_layout_4->add_window(_normal_sample_volume_edit,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_normal_dilution_sample_volume_edit,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_normal_dilution_volume_edit,1);
	//3-7.��ʼ���Ӳ���5��
	_child_layout_5->add_fixed_window(_decrease_static,100);
	_child_layout_5->add_window(_decreased_sample_volume_edit,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_decreased_dilution_sample_volume_edit,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_decreased_dilution_volume_edit,1);
	//3-8.��ʼ���Ӳ���6��
	_child_layout_6->add_fixed_window(_increase_static,100);
	_child_layout_6->add_window(_increased_sample_volume_edit,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_increased_dilution_sample_volume_edit,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_increased_dilution_volume_edit,1);
	//3-9.��ʼ���Ӳ���7��
	_child_layout_7->set_margin(5,34,5,5);
	_child_layout_7->add_stretch(1);
	_child_layout_7->add_fixed_layout(_child_layout_4,24);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_fixed_layout(_child_layout_5,24);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_fixed_layout(_child_layout_6,24);
	_child_layout_7->add_stretch(1);
	//3-10.��ʼ���Ӳ���8��
	_child_layout_8->add_fixed_window(_r1_static,50);
	_child_layout_8->add_window(_r1_reagent_volume_edit,1);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_diluent_volume_edit,1);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_reagent_code_edit,2);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_r1_reagent_stability_edit,1);
	//3-11.��ʼ���Ӳ���9��
	_child_layout_9->add_fixed_window(_r2_static,50);
	_child_layout_9->add_window(_r2_reagent_volume_edit,1);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_diluent_volume_edit,1);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_reagent_code_edit,2);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_r2_reagent_stability_edit,1);
	//3-12.��ʼ���Ӳ���10��
	_child_layout_10->add_fixed_window(_r3_static,50);
	_child_layout_10->add_window(_r3_reagent_volume_edit,1);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_diluent_volume_edit,1);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_reagent_code_edit,2);
	_child_layout_10->add_spacing(5);
	_child_layout_10->add_window(_r3_reagent_stability_edit,1);
	//3-13.��ʼ���Ӳ���11��
	_child_layout_11->add_fixed_window(_r4_static,50);
	_child_layout_11->add_window(_r4_reagent_volume_edit,1);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_diluent_volume_edit,1);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_reagent_code_edit,2);
	_child_layout_11->add_spacing(5);
	_child_layout_11->add_window(_r4_reagent_stability_edit,1);
	//3-14.��ʼ���Ӳ���12��
	_child_layout_12->set_margin(5,34,5,5);
	_child_layout_12->add_fixed_layout(_child_layout_8,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_9,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_10,24);
	_child_layout_12->add_stretch(1);
	_child_layout_12->add_fixed_layout(_child_layout_11,24);
	//3-15.��ʼ���Ӳ���13��
	_child_layout_13->add_fixed_layout(_child_layout_7,410);
	_child_layout_13->add_spacing(5);
	_child_layout_13->add_fixed_layout(_child_layout_12,410);
	//3-16.��ʼ���Ӳ���14��
	_child_layout_14->add_spacing(80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_volume_static,80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_code_static,80);
	_child_layout_14->add_spacing(5);
	_child_layout_14->add_fixed_window(_substrate_stability_static,80);
	//3-17.��ʼ���Ӳ���15.
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
	//3-18.��ʼ���Ӳ���16.
	_child_layout_16->add_fixed_window(_substrate_2_static,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_volume_edit,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_code_edit,80);
	_child_layout_16->add_spacing(5);
	_child_layout_16->add_fixed_window(_substrate_2_stability_edit,80);
	//3-19.��ʼ���Ӳ���17��
	_child_layout_17->add_fixed_window(_substrate_3_static,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_volume_edit,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_code_edit,80);
	_child_layout_17->add_spacing(5);
	_child_layout_17->add_fixed_window(_substrate_3_stability_edit,80);
	//3-20.��ʼ���Ӳ���18��
	_child_layout_18->add_fixed_window(_delete_button,100);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_read_parameters_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_add_application_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_write_parameters_button,200);
	_child_layout_18->add_spacing(5);
	_child_layout_18->add_fixed_window(_ok_button,100);
	//3-21.��ʼ�������֡�
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
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_13->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_sample_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_13->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_reagent_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//6.���µ�ǰ�����пؼ���ֵ��
	update_data_for_controls();
}

/**
 * name: init_combo_boxes
 * brief: ��ʼ��������ȫ���������򣬲�����ʼ����
 *        ���뵽�������С�
 * param: --
 * return: --
 */
void DialogAnalyzeApplication::init_combo_boxes(){
	//1.��ȡϵͳ�е�ģ����Ϣ��������Щ��Ϣ���뵽ָ�����������С�
	//1-1.������ǰ�������������
	Modules *modules=Modules::instance();
	unsigned int count=modules->get_count();
	int item=0;
	//1-2.����ģ����Ϣ������ģ����Ϣ���뵽ָ���������С�
	for(unsigned int index=0;index<count;++index){
		//1-2-1.��ȡ��ǰģ����Ϣ�������жϻ�ȡ�Ƿ�ɹ���
		Modules::PtrToCModule module=modules->get_by_index(index);
		//1-2-1.���Ե�ǰģ����Ϣ���ںϷ���
		assert(static_cast<bool>(module));
		//1-2-3.���������в���ģ����Ϣ���ݡ�
		item=_select_module_combo_box->AddString(module->get_alias());
		_select_module_combo_box->SetItemData(item,static_cast<
			DWORD_PTR>(module->get_id()));
	}
	//2.��ȡϵͳ������������Ϣ��������Щ��Ϣ���뵽ָ�����������С�
	//2-1.������ǰ�������������
	SpecimenTypes *specimen_types=SpecimenTypes::instance();
	count=specimen_types->get_count();
	//2-2.��������������Ϣ����������������Ϣ���뵽ָ���������С�
	for(unsigned int index=0;index<count;++index){
		//2-2-1.��ȡ��ǰ����������Ϣ�������жϻ�ȡ�Ƿ�ɹ���
		SpecimenTypes::PtrToCSpecimenType specimen_type=
			specimen_types->get_by_index(index);
		//2-2-2.���Ե�ǰ����������Ϣ���ںϷ���
		assert(static_cast<bool>(specimen_type));
		//2-2-3.���������в�������������Ϣ���ݡ�
		item=_select_specimen_type_combo_box->AddString(
			specimen_type->get_alias());
		_select_specimen_type_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(specimen_type->get_id()));
	}
	//3.��ȡϵͳ�з���������Ϣ��������Щ��Ϣ���뵽ָ�����������С�
	//3-1.������ǰ�������������
	AnalysisMethods *analysis_methods=AnalysisMethods::instance();
	count=analysis_methods->get_count();
	//3-2.�����������������������������뵽ָ�����������С�
	for(unsigned int index=0;index<count;++index){
		//3-2-1.��ȡ��ǰ����������
		AnalysisMethods::PtrToCMethod analysis_method=
			analysis_methods->get_method(index);
		//3-2-2.���Ե�ǰ�����������ںϷ���
		assert(static_cast<bool>(analysis_method));
		//3-2-3.���������в�������������ݡ�
		item=_assay_method_combo_box->AddString(
			analysis_method->get_alias());
		_assay_method_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(analysis_method->get_id()));
	}
	//4.��ȡϵͳ��ϡ�ͷ�����Ϣ��������Щ��Ϣ���뵽ָ�����������С�
	//4-1.������ǰ�������������
	DilutionMethods *dilution_methods=DilutionMethods::instance();
	count=dilution_methods->get_count();
	//4-2.����������벻ϡ���
	item=_dilution_ratio_combo_box->AddString(
		Theme::instance()->get_string(IDS_STRING494));
	_dilution_ratio_combo_box->SetItemData(
		item,static_cast<DWORD_PTR>(0));
	//4-3.����ϡ�ͷ���������ϡ�ͷ������뵽ָ�����������С�
	for(unsigned int index=0;index<count;++index){
		//4-3-1.��ȡ��ǰϡ�ͷ�����
		DilutionMethods::PtrToCMethod dilution_method=
			dilution_methods->get_method(index);
		//4-3-2.���Ե�ǰϡ�ͷ������ںϷ���
		assert(static_cast<bool>(dilution_method));
		//4-3-3.���������в���ϡ�ͷ������ݡ�
		item=_dilution_ratio_combo_box->AddString(
			dilution_method->get_alias());
		_dilution_ratio_combo_box->SetItemData(item,
			static_cast<DWORD_PTR>(dilution_method->get_id()));
	}
}

/**
 * name: init_select_test_combo_box
 * breif: ��ʼ����ѡ����Ŀ��������
 * param: item - �������Ŀ��Ϣ���á�
 * return: --
 */
void DialogAnalyzeApplication::init_select_test_combo_box(const Item &item){
	const int index=_select_test_combo_box->AddString(item.get_name());
	_select_test_combo_box->SetItemData(index,static_cast<DWORD_PTR>(item.get_id()));
}

/**
 * name: update_data_for_controls
 * brief: ��ָ����Ŀ��ʶ�����������Ϣ���µ��ؼ��ϡ�
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - ������������ͱ�ʶ��
 *        item_id - �������Ŀ��ʶ��
 * return: --
 * remark: ��ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ����ֵΪ��ʱ������ֵȡ��С��Чֵ��
 */
void DialogAnalyzeApplication::update_data_for_controls(
	const int module_id/*=0*/,const int specimen_type_id/*=0*/,const int item_id/*=0*/){
	//1.���á�ѡ��ģ�顱���������ݡ�
	//1-1.������ǰ�������������
	int item_count=_select_module_combo_box->GetCount();
	//1-2.�����ǰ����������Ϊ�ա�
	if(item_count<=0){
		_select_module_combo_box->SetCurSel(-1);
		_select_module_combo_box->EnableWindow(FALSE);
		_module_id=0;
	}
	//1-3.�����ǰδָ��������ʾ��ģ���ʶ������ʾĬ�ϵ�ģ���ʶ���������еĵ�һ����Ŀ����
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
	//1-4.�����ǰָ����������ʾ��ģ���ʶ��
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
	//2.���á�ѡ���������͡����������ݡ�
	//2-1.������ǰ�������������
	item_count=_select_specimen_type_combo_box->GetCount();
	//2-2.�����ǰ����������Ϊ�ա�
	if(item_count<=0){
		_select_specimen_type_combo_box->SetCurSel(-1);
		_select_specimen_type_combo_box->EnableWindow(FALSE);
		_specimen_type_id=0;
	}
	//2-3.�����ǰδָ��������ʾ���������ͱ�ʶ������ʾĬ�ϵ��������ͱ�ʶ���������еĵ�һ���������ͣ���
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
	//2-4.�����ǰָ����������ʾ���������ͱ�ʶ��
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
	//3.���á�ѡ����Ŀ�����������ݡ�
	//3-1.����ǰ��������������Ϣ�����
	for(int index=_select_test_combo_box->GetCount()-1;index>=0;--index){
		_select_test_combo_box->DeleteString(index);
	}
	//3-2.��ȡ��ǰϵͳ�е���Ŀ��Ϣ��������Ϣ���뵽��ѡ����Ŀ���������С�
	Items::TraverseCallback callback=std::bind(&DialogAnalyzeApplication::
		init_select_test_combo_box,this,std::placeholders::_1);
	(Items::instance())->traverse(callback);
	//3-3.���õ�ǰ����Ŀѡ��������ѡ������ݡ�
	//3-3-1.������ǰ�������������
	item_count=_select_test_combo_box->GetCount();
	//3-3-2.�����ǰ����������Ϊ�գ���������Ϊ��Ч״̬��
	if(item_count<=0){
		_select_test_combo_box->SetCurSel(-1);
		_select_test_combo_box->EnableWindow(FALSE);
		_item_id=0;
	}
	//3-3-3.�����ǰδָ��������ʾ����Ŀ��ʶ������ʾĬ�ϵ���Ŀ��ʶ���������еĵ�һ����Ŀ����
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
	//3-3-4.�����ǰָ����������ʾ����Ŀ��ʶ��
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
	//4.��ȡָ��ģ�顢���������Լ���Ŀ�ķ��������������жϻ�ȡ�Ƿ�ɹ���
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
	//5.���á��������������������ݡ�
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
	//6.���á����ʱ�䡱�ı��༭�����ݡ�
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
	//7.���á�����ʱ��1���ı��༭�����ݡ�
	if(0==analysis_data){
		_incubate_time_1_edit->SetWindowText(_T(""));
		_incubate_time_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_1());
		_incubate_time_1_edit->SetWindowText(text);
		_incubate_time_1_edit->EnableWindow(TRUE);
	}
	//8.���á�����ʱ��2���ı��༭�����ݡ�
	if(0==analysis_data){
		_incubate_time_2_edit->SetWindowText(_T(""));
		_incubate_time_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_2());
		_incubate_time_2_edit->SetWindowText(text);
		_incubate_time_2_edit->EnableWindow(TRUE);
	}
	//9.���á�����ʱ��3���ı��༭�����ݡ�
	if(0==analysis_data){
		_incubate_time_3_edit->SetWindowText(_T(""));
		_incubate_time_3_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_3());
		_incubate_time_3_edit->SetWindowText(text);
		_incubate_time_3_edit->EnableWindow(TRUE);
	}
	//10.���á�����ʱ��4���ı��༭�����ݡ�
	if(0==analysis_data){
		_incubate_time_4_edit->SetWindowText(_T(""));
		_incubate_time_4_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_incubation_time_4());
		_incubate_time_4_edit->SetWindowText(text);
		_incubate_time_4_edit->EnableWindow(TRUE);
	}
	//11.���á�ϡ��Һ��š��ı��༭�����ݡ�
	if(0==analysis_data){
		_diluent_code_edit->SetWindowText(_T(""));
		_diluent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_diluent_code());
		_diluent_code_edit->SetWindowText(text);
		_diluent_code_edit->EnableWindow(TRUE);
	}
	//12.���á�ϡ��Һ��Ч�ڡ��ı��༭�����ݡ�
	if(0==analysis_data){
		_diluent_stability_edit->SetWindowText(_T(""));
		_diluent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_diluent_stability());
		_diluent_stability_edit->SetWindowText(text);
		_diluent_stability_edit->EnableWindow(TRUE);
	}
	//13.���á�ϡ�ͷ��������������ݡ�
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
	//14.���á���Ŀ���ơ��ı��༭��
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
	//15.���á���Ŀ��ʶ���ı��༭��
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
	//16.���á���Ŀ��š��ı��༭��
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
	//17.���á���ͨ�ⶨ����������ı��༭��
	if(0==analysis_data){
		_normal_sample_volume_edit->SetWindowText(_T(""));
		_normal_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_sample_volume());
		_normal_sample_volume_edit->SetWindowText(text);
		_normal_sample_volume_edit->EnableWindow(TRUE);
	}
	//18.���á���ͨ�ⶨϡ�ͺ�����������ı��༭��
	if(0==analysis_data){
		_normal_dilution_sample_volume_edit->SetWindowText(_T(""));
		_normal_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_dilution_sample_volume());
		_normal_dilution_sample_volume_edit->SetWindowText(text);
		_normal_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//19.���á���ͨ����ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_normal_dilution_volume_edit->SetWindowText(_T(""));
		_normal_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_normal_diluent_volume());
		_normal_dilution_volume_edit->SetWindowText(text);
		_normal_dilution_volume_edit->EnableWindow(FALSE);
	}
	//20.���á������ⶨ����������ı��༭��
	if(0==analysis_data){
		_decreased_sample_volume_edit->SetWindowText(_T(""));
		_decreased_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_sample_volume());
		_decreased_sample_volume_edit->SetWindowText(text);
		_decreased_sample_volume_edit->EnableWindow(FALSE);
	}
	//21.���á������ⶨϡ�ͺ�����������ı��༭��
	if(0==analysis_data){
		_decreased_dilution_sample_volume_edit->SetWindowText(_T(""));
		_decreased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_dilution_sample_volume());
		_decreased_dilution_sample_volume_edit->SetWindowText(text);
		_decreased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//22.���á���������ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_decreased_dilution_volume_edit->SetWindowText(_T(""));
		_decreased_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_decrease_diluent_volume());
		_decreased_dilution_volume_edit->SetWindowText(text);
		_decreased_dilution_volume_edit->EnableWindow(FALSE);
	}
	//23.���á������ⶨ����������ı��༭��
	if(0==analysis_data){
		_increased_sample_volume_edit->SetWindowText(_T(""));
		_increased_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_sample_volume());
		_increased_sample_volume_edit->SetWindowText(text);
		_increased_sample_volume_edit->EnableWindow(FALSE);
	}
	//24.���á������ⶨϡ�ͺ�����������ı��༭��
	if(0==analysis_data){
		_increased_dilution_sample_volume_edit->SetWindowText(_T(""));
		_increased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_dilution_sample_volume());
		_increased_dilution_sample_volume_edit->SetWindowText(text);
		_increased_dilution_sample_volume_edit->EnableWindow(FALSE);
	}
	//25.���á���������ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_increased_dilution_volume_edit->SetWindowText(_T(""));
		_increased_dilution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_increase_diluent_volume());
		_increased_dilution_volume_edit->SetWindowText(text);
		_increased_dilution_volume_edit->EnableWindow(FALSE);
	}
	//26.���á�R1�Լ�������ı��༭��
	if(0==analysis_data){
		_r1_reagent_volume_edit->SetWindowText(_T(""));
		_r1_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_volume());
		_r1_reagent_volume_edit->SetWindowText(text);
		_r1_reagent_volume_edit->EnableWindow(TRUE);
	}
	//27.���á�R1ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_r1_diluent_volume_edit->SetWindowText(_T(""));
		_r1_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_diluent_volume());
		_r1_diluent_volume_edit->SetWindowText(text);
		_r1_diluent_volume_edit->EnableWindow(FALSE);
	}
	//28.���á�R1�Լ����롱�ı��༭��
	if(0==analysis_data){
		_r1_reagent_code_edit->SetWindowText(_T(""));
		_r1_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_code());
		_r1_reagent_code_edit->SetWindowText(text);
		_r1_reagent_code_edit->EnableWindow(TRUE);
	}
	//29.���á�R1�Լ���Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_r1_reagent_stability_edit->SetWindowText(_T(""));
		_r1_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r1_reagent_stability());
		_r1_reagent_stability_edit->SetWindowText(text);
		_r1_reagent_stability_edit->EnableWindow(TRUE);
	}
	//30.���á�R2�Լ�������ı��༭��
	if(0==analysis_data){
		_r2_reagent_volume_edit->SetWindowText(_T(""));
		_r2_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_volume());
		_r2_reagent_volume_edit->SetWindowText(text);
		_r2_reagent_volume_edit->EnableWindow(TRUE);
	}
	//31.���á�R2ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_r2_diluent_volume_edit->SetWindowText(_T(""));
		_r2_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_diluent_volume());
		_r2_diluent_volume_edit->SetWindowText(text);
		_r2_diluent_volume_edit->EnableWindow(FALSE);
	}
	//32.���á�R2�Լ����롱�ı��༭��
	if(0==analysis_data){
		_r2_reagent_code_edit->SetWindowText(_T(""));
		_r2_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_code());
		_r2_reagent_code_edit->SetWindowText(text);
		_r2_reagent_code_edit->EnableWindow(TRUE);
	}
	//33.���á�R2�Լ���Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_r2_reagent_stability_edit->SetWindowText(_T(""));
		_r2_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r2_reagent_stability());
		_r2_reagent_stability_edit->SetWindowText(text);
		_r2_reagent_stability_edit->EnableWindow(TRUE);
	}
	//34.���á�R3�Լ�������ı��༭��
	if(0==analysis_data){
		_r3_reagent_volume_edit->SetWindowText(_T(""));
		_r3_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_volume());
		_r3_reagent_volume_edit->SetWindowText(text);
		_r3_reagent_volume_edit->EnableWindow(TRUE);
	}
	//35.���á�R2ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_r3_diluent_volume_edit->SetWindowText(_T(""));
		_r3_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_diluent_volume());
		_r3_diluent_volume_edit->SetWindowText(text);
		_r3_diluent_volume_edit->EnableWindow(FALSE);
	}
	//36.���á�R3�Լ����롱�ı��༭��
	if(0==analysis_data){
		_r3_reagent_code_edit->SetWindowText(_T(""));
		_r3_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_code());
		_r3_reagent_code_edit->SetWindowText(text);
		_r3_reagent_code_edit->EnableWindow(TRUE);
	}
	//37.���á�R3�Լ���Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_r3_reagent_stability_edit->SetWindowText(_T(""));
		_r3_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r3_reagent_stability());
		_r3_reagent_stability_edit->SetWindowText(text);
		_r3_reagent_stability_edit->EnableWindow(TRUE);
	}
	//38.���á�R4�Լ�������ı��༭��
	if(0==analysis_data){
		_r4_reagent_volume_edit->SetWindowText(_T(""));
		_r4_reagent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_volume());
		_r4_reagent_volume_edit->SetWindowText(text);
		_r4_reagent_volume_edit->EnableWindow(TRUE);
	}
	//39.���á�R4ϡ��Һ������ı��༭��
	if(0==analysis_data){
		_r4_diluent_volume_edit->SetWindowText(_T(""));
		_r4_diluent_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_diluent_volume());
		_r4_diluent_volume_edit->SetWindowText(text);
		_r4_diluent_volume_edit->EnableWindow(FALSE);
	}
	//40.���á�R4�Լ����롱�ı��༭��
	if(0==analysis_data){
		_r4_reagent_code_edit->SetWindowText(_T(""));
		_r4_reagent_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_code());
		_r4_reagent_code_edit->SetWindowText(text);
		_r4_reagent_code_edit->EnableWindow(TRUE);
	}
	//41.���á�R4�Լ���Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_r4_reagent_stability_edit->SetWindowText(_T(""));
		_r4_reagent_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_r4_reagent_stability());
		_r4_reagent_stability_edit->SetWindowText(text);
		_r4_reagent_stability_edit->EnableWindow(TRUE);
	}
	//42.���á�����1������ı��༭��
	if(0==analysis_data){
		_substrate_1_volume_edit->SetWindowText(_T(""));
		_substrate_1_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_volume());
		_substrate_1_volume_edit->SetWindowText(text);
		_substrate_1_volume_edit->EnableWindow(TRUE);
	}
	//43.���á�����1��š��ı��༭��
	if(0==analysis_data){
		_substrate_1_code_edit->SetWindowText(_T(""));
		_substrate_1_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_code());
		_substrate_1_code_edit->SetWindowText(text);
		_substrate_1_code_edit->EnableWindow(TRUE);
	}
	//44.���á�����1��Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_substrate_1_stability_edit->SetWindowText(_T(""));
		_substrate_1_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_stability());
		_substrate_1_stability_edit->SetWindowText(text);
		_substrate_1_stability_edit->EnableWindow(TRUE);
	}
	//45.���á�����2������ı��༭��
	if(0==analysis_data){
		_substrate_2_volume_edit->SetWindowText(_T(""));
		_substrate_2_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_1_volume());
		_substrate_2_volume_edit->SetWindowText(text);
		_substrate_2_volume_edit->EnableWindow(TRUE);
	}
	//46.���á�����2��š��ı��༭��
	if(0==analysis_data){
		_substrate_2_code_edit->SetWindowText(_T(""));
		_substrate_2_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_2_code());
		_substrate_2_code_edit->SetWindowText(text);
		_substrate_2_code_edit->EnableWindow(TRUE);
	}
	//47.���á�����2��Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_substrate_2_stability_edit->SetWindowText(_T(""));
		_substrate_2_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_2_stability());
		_substrate_2_stability_edit->SetWindowText(text);
		_substrate_2_stability_edit->EnableWindow(TRUE);
	}
	//48.���á�����3������ı��༭��
	if(0==analysis_data){
		_substrate_3_volume_edit->SetWindowText(_T(""));
		_substrate_3_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_volume());
		_substrate_3_volume_edit->SetWindowText(text);
		_substrate_3_volume_edit->EnableWindow(TRUE);
	}
	//49.���á�����3��š��ı��༭��
	if(0==analysis_data){
		_substrate_3_code_edit->SetWindowText(_T(""));
		_substrate_3_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_code());
		_substrate_3_code_edit->SetWindowText(text);
		_substrate_3_code_edit->EnableWindow(TRUE);
	}
	//50.���á�����3��Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_substrate_3_stability_edit->SetWindowText(_T(""));
		_substrate_3_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_substrate_3_stability());
		_substrate_3_stability_edit->SetWindowText(text);
		_substrate_3_stability_edit->EnableWindow(TRUE);
	}
	//51.���á�����Һ������ı��༭��
	if(0==analysis_data){
		_buffer_solution_volume_edit->SetWindowText(_T(""));
		_buffer_solution_volume_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_volume());
		_buffer_solution_volume_edit->SetWindowText(text);
		_buffer_solution_volume_edit->EnableWindow(TRUE);
	}
	//52.���á�����Һ��š��ı��༭��
	if(0==analysis_data){
		_buffer_solution_code_edit->SetWindowText(_T(""));
		_buffer_solution_code_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_code());
		_buffer_solution_code_edit->SetWindowText(text);
		_buffer_solution_code_edit->EnableWindow(TRUE);
	}
	//53.���á�����Һ��Ч�ڡ��ı��༭��
	if(0==analysis_data){
		_buffer_solution_stability_edit->SetWindowText(_T(""));
		_buffer_solution_stability_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%d"),analysis_data->
			get_buffer_solution_stability());
		_buffer_solution_stability_edit->SetWindowText(text);
		_buffer_solution_stability_edit->EnableWindow(TRUE);
	}
	//54.���á�ɾ������ť��
	if(0==analysis_data){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//55.���á���ȡ��������ť��
	_read_parameters_button->EnableWindow(TRUE);
	//56.���á������Ŀ����ť��
	_add_application_button->EnableWindow(TRUE);
	//57.���á�д��������ť��
	if(0==analysis_data){
		_write_parameters_button->EnableWindow(FALSE);
	}else{
		_write_parameters_button->EnableWindow(TRUE);
	}
	//58.���á�ȷ�ϡ���ť��
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: �жϵ�ǰ�ؼ��е������Ƿ����ı䡣
 * param: --
 * return: �����ǰ�ؼ��е����ݷ����ı��򷵻�TRUE�����򷵻�FALSE��
 */
BOOL DialogAnalyzeApplication::is_data_of_controls_changed() const{
	//1.��ȡ��ǰ������ָ����Ŀ��ʶ��Ӧ�ò����������жϻ�ȡ�Ƿ�ɹ���
	ApplicationParameters::PtrToCParameter parameter=
		ApplicationParameters::instance()->get(
		_module_id,_specimen_type_id,_item_id);
	if(!static_cast<bool>(parameter)){//���δ�ܻ�ȡָ��������Ϣ������Ϊ�ޱ仯��
		return(FALSE);
	}
	ApplicationParameter::PtrToCData data=parameter->get(
		ApplicationParameter::DATA_NAME_ANALYSIS);
	assert(static_cast<bool>(data));//���Ի�ȡ�ķ������ݺϷ���Ч��
	const ApplicationAnalysisData *analysis_data=
		dynamic_cast<const ApplicationAnalysisData*>(data.get());
	//2.��⡰�����������������Ƿ����仯��
	int item=_assay_method_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	int value=static_cast<int>(_assay_method_combo_box->GetItemData(item));
	if(analysis_data->get_analysis_method_id()!=value){
		return(TRUE);
	}
	//3.��⡰���ʱ�䡱�ı��༭���Ƿ����仯��
	CString text(_T(""));
	_detect_time_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_checkout_incubation_time()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//4.��⡰����ʱ��1���ı��༭���Ƿ����仯��
	_incubate_time_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_1()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//5.��⡰����ʱ��2���ı��༭���Ƿ����仯��
	_incubate_time_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_2()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//6.��⡰����ʱ��3���ı��༭���Ƿ����仯��
	_incubate_time_3_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_3()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//7.��⡰����ʱ��4���ı��༭���Ƿ����仯��
	_incubate_time_4_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_incubation_time_4()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//8.��⡰ϡ��Һ��š��ı��༭���Ƿ����仯��
	_diluent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_diluent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//9.��⡰ϡ��Һ��Ч�ڡ��ı��༭���Ƿ����仯��
	_diluent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_diluent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//10.��⡰ϡ�ͷ������������Ƿ����仯��
	item=_dilution_ratio_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_dilution_ratio_combo_box->
		GetItemData(item));
	if(analysis_data->get_dilution_method_id()!=value){
		return(TRUE);
	}
	//11.��⡰��Ŀ���ơ��ı��༭���Ƿ����仯��
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
	//12.��⡰��Ŀ��ʶ���ı��༭���Ƿ����仯��
	_test_id_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(item_t->get_id()!=MtCharacterSet::
		to_integer(text)){
		return(TRUE);
	}
	//13.��⡰��Ŀ��š��ı��༭���Ƿ����仯��
	_test_no_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(item_t->get_no()!=MtCharacterSet::
		to_integer(text)){
		return(TRUE);
	}
	//14.��⡰��ͨ�ⶨ����������ı��༭���Ƿ����仯��
	_normal_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//15.��⡰��ͨ�ⶨϡ�ͺ�����������ı��༭���Ƿ����仯��
	_normal_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//16.��⡰��ͨ�ⶨϡ��Һ������ı��༭���Ƿ����仯��
	_normal_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_normal_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//17.��⡰�����ⶨ����������ı��༭���Ƿ����仯��
	_decreased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//18.��⡰�����ⶨϡ�ͺ�����������ı��༭���Ƿ����仯��
	_decreased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//19.��⡰�����ⶨϡ��Һ������ı��༭���Ƿ����仯��
	_decreased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_decrease_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//20.��⡰�����ⶨ����������ı��༭���Ƿ����仯��
	_increased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//21.��⡰�����ⶨϡ�ͺ�����������ı��༭���Ƿ����仯��
	_increased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_dilution_sample_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//22.��⡰�����ⶨϡ��Һ������ı��༭���Ƿ����仯��
	_increased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_increase_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//23.��⡰R1�Լ�������ı��༭���Ƿ����仯��
	_r1_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//24.��⡰R1ϡ��Һ������ı��༭���Ƿ����仯��
	_r1_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//25.��⡰R1�Լ���š��ı��༭���Ƿ����仯��
	_r1_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//26.��⡰R1�Լ���Ч�ڡ��ı��༭���Ƿ����仯��
	_r1_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r1_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//27.��⡰R2�Լ�������ı��༭���Ƿ����仯��
	_r2_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//28.��⡰R2ϡ��Һ������ı��༭���Ƿ����仯��
	_r2_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//29.��⡰R2�Լ���š��ı��༭���Ƿ����仯��
	_r2_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//30.��⡰R2�Լ���Ч�ڡ��ı��༭���Ƿ����仯��
	_r2_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r2_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//31.��⡰R3�Լ�������ı��༭���Ƿ����仯��
	_r3_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//32.��⡰R3ϡ��Һ������ı��༭���Ƿ����仯��
	_r3_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//33.��⡰R3�Լ���š��ı��༭���Ƿ����仯��
	_r3_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//34.��⡰R3�Լ���Ч�ڡ��ı��༭���Ƿ����仯��
	_r3_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r3_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//35.��⡰R4�Լ�������ı��༭���Ƿ����仯��
	_r4_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//36.��⡰R4ϡ��Һ������ı��༭���Ƿ����仯��
	_r4_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_diluent_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//37.��⡰R4�Լ���š��ı��༭���Ƿ����仯��
	_r4_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//38.��⡰R4�Լ���Ч�ڡ��ı��༭���Ƿ����仯��
	_r4_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_r4_reagent_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//39.��⡰����1������ı��༭���Ƿ����仯��
	_substrate_1_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//40.��⡰����1��š��ı��༭���Ƿ����仯��
	_substrate_1_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//41.��⡰����1��Ч�ڡ��ı��༭���Ƿ����仯��
	_substrate_1_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_1_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}

	//42.��⡰����2������ı��༭���Ƿ����仯��
	_substrate_2_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//43.��⡰����2��š��ı��༭���Ƿ����仯��
	_substrate_2_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//44.��⡰����2��Ч�ڡ��ı��༭���Ƿ����仯��
	_substrate_2_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_2_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//45.��⡰����3������ı��༭���Ƿ����仯��
	_substrate_3_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//46.��⡰����3��š��ı��༭���Ƿ����仯��
	_substrate_3_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//47.��⡰����3��Ч�ڡ��ı��༭���Ƿ����仯��
	_substrate_3_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_substrate_3_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//48.��⡰����Һ������ı��༭���Ƿ����仯��
	_buffer_solution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_volume()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//49.��⡰����Һ��š��ı��༭���Ƿ����仯��
	_buffer_solution_code_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_code()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}	
	//50.��⡰����Һ��Ч�ڡ��ı��༭���Ƿ����仯��
	_buffer_solution_stability_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(analysis_data->get_buffer_solution_stability()!=
		MtCharacterSet::to_integer(text)){
		return(TRUE);
	}
	//51.�������е���ֱ�ӷ��ء�
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * brief: ��ȡ�ؼ��е����ݡ�
 * param: item_alias - �������Ŀ������
 *        data - �����Ӧ�÷���������
 * return: �����ǰ����ִ�гɹ�������ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogAnalyzeApplication::get_data_from_controls(
	CString &item_alias,ApplicationAnalysisData &data){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ��ѡ��ģ�顱���������ݡ�
	if(_module_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING175),this);
		_select_module_combo_box->SetFocus();
		return(-1);
	}
	data.set_module_id(_module_id);
	//3.��ȡ��ǰ�ġ�ѡ���������͡����������ݡ�
	if(_specimen_type_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING176),this);
		_select_specimen_type_combo_box->SetFocus();
		return(-2);
	}
	data.set_specimen_type_id(_specimen_type_id);
	//4.��ȡ��ǰ��ѡ����Ŀ�����������ݡ�
	if(_item_id<=0){
		WarningMessageBox(theme->get_string(IDS_STRING159),this);
		_select_test_combo_box->SetFocus();
		return(-3);
	}
	data.set_item_id(_item_id);
	//5.��ȡ��ǰ�ġ��������������������ݡ�
	int selection=_assay_method_combo_box->GetCurSel();
	if(selection<0){
		WarningMessageBox(theme->get_string(IDS_STRING183),this);
		_assay_method_combo_box->SetFocus();
		return(-4);
	}
	data.set_analysis_method_id(static_cast<int>(
		_assay_method_combo_box->GetItemData(selection)));
	//6.��ȡ��ǰ��������ʱ�䡱�ı��༭�����ݡ�
	CString text(_T(""));
	_detect_time_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING184),this);
		_detect_time_edit->SetFocus();
		return(-5);
	}
	data.set_checkout_incubation_time(MtCharacterSet::to_integer(text));
	//7.��ȡ��ǰ������ʱ��1���ı��༭�����ݡ�
	_incubate_time_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING185),this);
		_incubate_time_1_edit->SetFocus();
		return(-6);
	}
	data.set_incubation_time_1(MtCharacterSet::to_integer(text));
	//8.��ȡ��ǰ������ʱ��2���ı��༭�����ݡ�
	_incubate_time_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING186),this);
		_incubate_time_2_edit->SetFocus();
		return(-7);
	}
	data.set_incubation_time_2(MtCharacterSet::to_integer(text));
	//9.��ȡ��ǰ������ʱ��3���ı��༭�����ݡ�
	_incubate_time_3_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING187),this);
		_incubate_time_3_edit->SetFocus();
		return(-8);
	}
	data.set_incubation_time_3(MtCharacterSet::to_integer(text));
	//10.��ȡ��ǰ������ʱ��4���ı��༭�����ݡ�
	_incubate_time_4_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING188),this);
		_incubate_time_4_edit->SetFocus();
		return(-9);
	}
	data.set_incubation_time_4(MtCharacterSet::to_integer(text));
	//11.��ȡ��ǰ��ϡ��Һ��š��ı��༭�����ݡ�
	_diluent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING189),this);
		_diluent_code_edit->SetFocus();
		return(-10);
	}
	data.set_diluent_code(MtCharacterSet::to_integer(text));
	//12.��ȡ��ǰ��ϡ��Һ��Ч�ڡ��ı��༭�����ݡ�
	_diluent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING190),this);
		_diluent_stability_edit->SetFocus();
		return(-11);
	}
	data.set_diluent_stability(MtCharacterSet::to_integer(text));
	//13.��ȡ��ǰ��ϡ�ͷ��������������ݡ�
	selection=_dilution_ratio_combo_box->GetCurSel();
	if(selection<0){
		WarningMessageBox(theme->get_string(IDS_STRING191),this);
		_dilution_ratio_combo_box->SetFocus();
		return(-12);
	}
	data.set_dilution_method_id(static_cast<int>(
		_dilution_ratio_combo_box->GetItemData(selection)));
	//14.��ȡ��ǰ����Ŀ���ơ��ı��༭�����ݡ�
	_test_name_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING192),this);
		_test_name_edit->SetFocus();
		return(-13);
	}
	item_alias=text;
	//15.��ȡ��ǰ����ͨ�ⶨ����������ı��༭�����ݡ�
	_normal_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING193),this);
		_normal_sample_volume_edit->SetFocus();
		return(-14);
	}
	data.set_normal_sample_volume(MtCharacterSet::to_integer(text));
	//16.��ȡ��ǰ����ͨ�ⶨϡ�ͺ�����������ı��༭�����ݡ�
	_normal_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING194),this);
		_normal_dilution_sample_volume_edit->SetFocus();
		return(-15);
	}
	data.set_normal_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//17.��ȡ��ǰ����ͨ�ⶨϡ��Һ������ı��༭�����ݡ�
	_normal_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING195),this);
		_normal_dilution_volume_edit->SetFocus();
		return(-16);
	}
	data.set_normal_diluent_volume(MtCharacterSet::to_integer(text));
	//18.��ȡ��ǰ�������ⶨ����������ı��༭�����ݡ�
	_decreased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING196),this);
		_decreased_sample_volume_edit->SetFocus();
		return(-17);
	}
	data.set_decrease_sample_volume(MtCharacterSet::to_integer(text));
	//19.��ȡ��ǰ�������ⶨϡ�ͺ�����������ı��༭�����ݡ�
	_decreased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING197),this);
		_decreased_dilution_sample_volume_edit->SetFocus();
		return(-18);
	}
	data.set_decrease_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//20.��ȡ��ǰ�������ⶨϡ��Һ������ı��༭�����ݡ�
	_decreased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING198),this);
		_decreased_dilution_volume_edit->SetFocus();
		return(-19);
	}
	data.set_decrease_diluent_volume(MtCharacterSet::to_integer(text));
	//21.��ȡ��ǰ�������ⶨ����������ı��༭�����ݡ�
	_increased_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING199),this);
		_increased_sample_volume_edit->SetFocus();
		return(-20);
	}
	data.set_increase_sample_volume(MtCharacterSet::to_integer(text));
	//22.��ȡ��ǰ�������ⶨϡ�ͺ�����������ı��༭�����ݡ�
	_increased_dilution_sample_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING200),this);
		_increased_dilution_sample_volume_edit->SetFocus();
		return(-21);
	}
	data.set_increase_dilution_sample_volume(MtCharacterSet::to_integer(text));
	//23.��ȡ��ǰ�������ⶨϡ��Һ������ı��༭�����ݡ�
	_increased_dilution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING201),this);
		_increased_dilution_volume_edit->SetFocus();
		return(-22);
	}
	data.set_increase_diluent_volume(MtCharacterSet::to_integer(text));
	//24.��ȡ��ǰ��R1�Լ�������ı��༭�����ݡ�
	_r1_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING202),this);
		_r1_reagent_volume_edit->SetFocus();
		return(-23);
	}
	data.set_r1_reagent_volume(MtCharacterSet::to_integer(text));
	//25.��ȡ��ǰ��R1ϡ��Һ������ı��༭�����ݡ�
	_r1_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING203),this);
		_r1_diluent_volume_edit->SetFocus();
		return(-24);
	}
	data.set_r1_diluent_volume(MtCharacterSet::to_integer(text));
	//26.��ȡ��ǰ��R1�Լ���š��ı��༭�����ݡ�
	_r1_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING204),this);
		_r1_reagent_code_edit->SetFocus();
		return(-25);
	}
	data.set_r1_reagent_code(MtCharacterSet::to_integer(text));
	//27.��ȡ��ǰ��R1�Լ���Ч�ڡ��ı��༭�����ݡ�
	_r1_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING205),this);
		_r1_reagent_stability_edit->SetFocus();
		return(-26);
	}
	data.set_r1_reagent_stability(MtCharacterSet::to_integer(text));
	//28.��ȡ��ǰ��R2�Լ�������ı��༭�����ݡ�
	_r2_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING206),this);
		_r2_reagent_volume_edit->SetFocus();
		return(-27);
	}
	data.set_r2_reagent_volume(MtCharacterSet::to_integer(text));
	//29.��ȡ��ǰ��R2ϡ��Һ������ı��༭�����ݡ�
	_r2_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING207),this);
		_r2_diluent_volume_edit->SetFocus();
		return(-28);
	}
	data.set_r2_diluent_volume(MtCharacterSet::to_integer(text));
	//30.��ȡ��ǰ��R2�Լ���š��ı��༭�����ݡ�
	_r2_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING208),this);
		_r2_reagent_code_edit->SetFocus();
		return(-29);
	}
	data.set_r2_reagent_code(MtCharacterSet::to_integer(text));
	//31.��ȡ��ǰ��R2�Լ���Ч�ڡ��ı��༭�����ݡ�
	_r2_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING209),this);
		_r2_reagent_stability_edit->SetFocus();
		return(-30);
	}
	data.set_r2_reagent_stability(MtCharacterSet::to_integer(text));
	//32.��ȡ��ǰ��R3�Լ�������ı��༭�����ݡ�
	_r3_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING210),this);
		_r3_reagent_volume_edit->SetFocus();
		return(-31);
	}
	data.set_r3_reagent_volume(MtCharacterSet::to_integer(text));
	//33.��ȡ��ǰ��R3ϡ��Һ������ı��༭�����ݡ�
	_r3_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING211),this);
		_r3_diluent_volume_edit->SetFocus();
		return(-32);
	}
	data.set_r3_diluent_volume(MtCharacterSet::to_integer(text));
	//34.��ȡ��ǰ��R3�Լ���š��ı��༭�����ݡ�
	_r3_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING212),this);
		_r3_reagent_code_edit->SetFocus();
		return(-33);
	}
	data.set_r3_reagent_code(MtCharacterSet::to_integer(text));
	//35.��ȡ��ǰ��R3�Լ���Ч�ڡ��ı��༭�����ݡ�
	_r3_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING213),this);
		_r3_reagent_stability_edit->SetFocus();
		return(-34);
	}
	data.set_r3_reagent_stability(MtCharacterSet::to_integer(text));
	//36.��ȡ��ǰ��R4�Լ�������ı��༭�����ݡ�
	_r4_reagent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING214),this);
		_r4_reagent_volume_edit->SetFocus();
		return(-35);
	}
	data.set_r4_reagent_volume(MtCharacterSet::to_integer(text));
	//37.��ȡ��ǰ��R4ϡ��Һ������ı��༭�����ݡ�
	_r4_diluent_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING215),this);
		_r4_diluent_volume_edit->SetFocus();
		return(-36);
	}
	data.set_r4_diluent_volume(MtCharacterSet::to_integer(text));
	//38.��ȡ��ǰ��R4�Լ���š��ı��༭�����ݡ�
	_r4_reagent_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING216),this);
		_r4_reagent_code_edit->SetFocus();
		return(-37);
	}
	data.set_r4_reagent_code(MtCharacterSet::to_integer(text));
	//39.��ȡ��ǰ��R4�Լ���Ч�ڡ��ı��༭�����ݡ�
	_r4_reagent_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING217),this);
		_r4_reagent_stability_edit->SetFocus();
		return(-38);
	}
	data.set_r4_reagent_stability(MtCharacterSet::to_integer(text));
	//40.��ȡ��ǰ������1������ı��༭�����ݡ�
	_substrate_1_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING218),this);
		_substrate_1_volume_edit->SetFocus();
		return(-39);
	}
	data.set_substrate_1_volume(MtCharacterSet::to_integer(text));
	//41.��ȡ��ǰ������1��š��ı��༭�����ݡ�
	_substrate_1_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING219),this);
		_substrate_1_code_edit->SetFocus();
		return(-40);
	}
	data.set_substrate_1_code(MtCharacterSet::to_integer(text));
	//42.��ȡ��ǰ������1��Ч�ڡ��ı��༭�����ݡ�
	_substrate_1_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING220),this);
		_substrate_1_stability_edit->SetFocus();
		return(-41);
	}
	data.set_substrate_1_stability(MtCharacterSet::to_integer(text));
	//43.��ȡ��ǰ������2������ı��༭�����ݡ�
	_substrate_2_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING221),this);
		_substrate_2_volume_edit->SetFocus();
		return(-42);
	}
	data.set_substrate_2_volume(MtCharacterSet::to_integer(text));
	//44.��ȡ��ǰ������2��š��ı��༭�����ݡ�
	_substrate_2_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING222),this);
		_substrate_2_code_edit->SetFocus();
		return(-43);
	}
	data.set_substrate_2_code(MtCharacterSet::to_integer(text));
	//45.��ȡ��ǰ������2��Ч�ڡ��ı��༭�����ݡ�
	_substrate_2_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING223),this);
		_substrate_2_stability_edit->SetFocus();
		return(-44);
	}
	data.set_substrate_2_stability(MtCharacterSet::to_integer(text));
	//46.��ȡ��ǰ������3������ı��༭�����ݡ�
	_substrate_3_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING224),this);
		_substrate_3_volume_edit->SetFocus();
		return(-45);
	}
	data.set_substrate_3_volume(MtCharacterSet::to_integer(text));
	//47.��ȡ��ǰ������3��š��ı��༭�����ݡ�
	_substrate_3_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING225),this);
		_substrate_3_code_edit->SetFocus();
		return(-46);
	}
	data.set_substrate_3_code(MtCharacterSet::to_integer(text));
	//48.��ȡ��ǰ������3��Ч�ڡ��ı��༭�����ݡ�
	_substrate_3_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING226),this);
		_substrate_3_stability_edit->SetFocus();
		return(-47);
	}
	data.set_substrate_3_stability(MtCharacterSet::to_integer(text));
	//49.��ȡ��ǰ������Һ������ı��༭�����ݡ�
	_buffer_solution_volume_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING227),this);
		_buffer_solution_volume_edit->SetFocus();
		return(-48);
	}
	data.set_buffer_solution_volume(MtCharacterSet::to_integer(text));
	//50.��ȡ��ǰ������Һ��š��ı��༭�����ݡ�
	_buffer_solution_code_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING228),this);
		_buffer_solution_code_edit->SetFocus();
		return(-49);
	}
	data.set_buffer_solution_code(MtCharacterSet::to_integer(text));
	//51.��ȡ��ǰ������Һ��Ч�ڡ��ı��༭�����ݡ�
	_buffer_solution_stability_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING229),this);
		_buffer_solution_stability_edit->SetFocus();
		return(-50);
	}
	data.set_buffer_solution_stability(MtCharacterSet::to_integer(text));
	//52.�����ǰӦ�÷����������Ϸ�����ֱ�ӷ��ش���
	//52-1.�жϵ�ǰ���������Ƿ�Ϸ���
	const int result=data.is_valid(&text);
	//52-2.�����ǰ�����������Ϸ���������û����沢���ش���
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
	//53.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: �ύ�ؼ������ݵ�ָ�������ݿ��С�
 * param: database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogAnalyzeApplication::commit_data_of_controls(Database &database){
	//1.��ȡ��ǰ��������������ݣ������жϻ�ȡ�Ƿ�ɹ���
	CString item_alias(_T(""));
	ApplicationAnalysisData data;
	if(get_data_from_controls(item_alias,data)<0){
		return(-1);
	}
	//2.�����ݿ��ύ�޸ĵ����ݣ������ж��ύ�Ƿ�ɹ���
	//2-1.�������ݿ�����׼�������ݿ����ύ�޸����ݡ�
	if(database.begin_trans()<0){
		return(-2);
	}
	//2-2.�������ݿ��ύ�޸ĵ���Ŀ��Ϣ��
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
	//2-3.�����ݿ��ύ�޸ĵ�Ӧ�÷���������
	if(data.commit(2,database)<0){
		database.rollback_trans();
		return(-5);
	}
	//2-4.�޸�Ӧ�÷��������е��ڴ����ݡ�
	if(ApplicationParameters::instance()->modify(data)<0){
		database.rollback_trans();
		return(-6);
	}
	//2-5.�޸���Ŀ��Ϣ����Ӧ�ڴ����ݡ�
	Items::instance()->modify(item_t);
	//2-6.�ύ���ݿ����񣬲����ж��ύ�Ƿ�ɹ���
	if(database.commit_trans()<0){
		database.rollback_trans();
		Items::instance()->update(database);
		ApplicationParameters::instance()->update(database);
		return(-7);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}