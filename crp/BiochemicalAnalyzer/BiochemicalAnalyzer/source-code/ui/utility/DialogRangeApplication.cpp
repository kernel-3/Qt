// source-code/ui/utility/DialogRangeApplication.cpp : implementation file
//

#include"stdafx.h"
#include"DialogRangeApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/control/MtImageComboBox.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../global/DatabaseManager.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../data/utility/Application.h"
#include"../../data/utility/Applications.h"
#include"../../data/common/Item.h"
#include"../../data/utility/RangeApplication.h"
#include"../UiCustom.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../../data/DataCustom.h"
#include"../common/DialogMessageBox.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoReset.h"

//DialogRangeApplication dialog

IMPLEMENT_DYNAMIC(DialogRangeApplication,DialogPageBase)

/**
 * name: DialogRangeApplication
 * breif: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
 * return: --
 */
DialogRangeApplication::DialogRangeApplication(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogRangeApplication::IDD,pParent)
	,_item_id(0)
	,_sample_type_id(0)
	,_is_command_message_masked(FALSE)
	,_select_test_static(new MtImageStatic)
	,_report_name_static(new MtImageStatic)
	,_item_name_static(new MtImageStatic)
	,_unit_static(new MtImageStatic)
	,_item_no_static(new MtImageStatic)
	,_data_mode_static(new MtImageStatic)
	,_test_id_static(new MtImageStatic)
	,_instrument_factor_static(new MtImageStatic)
	,_select_sample_type_static(new MtImageStatic)
	,_age_static(new MtImageStatic)
	,_male_static(new MtImageStatic)
	,_female_static(new MtImageStatic)
	,_default_age_static(new MtImageStatic)
	,_default_sex_static(new MtImageStatic)
	,_repeat_range_static(new MtImageStatic)
	,_qualitative_limit_1_static(new MtImageStatic)
	,_qualitative_limit_2_static(new MtImageStatic)
	,_qualitative_limit_3_static(new MtImageStatic)
	,_qualitative_limit_4_static(new MtImageStatic)
	,_qualitative_limit_5_static(new MtImageStatic)
	,_qualitative_limit_6_static(new MtImageStatic)
	,_expected_ranges_static(new MtImageStatic)
	,_range_static(new MtImageStatic)
	,_class_1_technical_range_static(new MtImageStatic)
	,_class_2_technical_range_static(new MtImageStatic)
	,_select_test_combo_box(new MtImageComboBox)
	,_unit_combo_box(new MtImageComboBox)
	,_data_mode_combo_box(new MtImageComboBox)
	,_select_sample_type_combo_box(new MtImageComboBox)
	,_lower_age_unit_combo_box(new MtImageComboBox)
	,_upper_age_unit_combo_box(new MtImageComboBox)
	,_default_age_combo_box(new MtImageComboBox)
	,_default_sex_combo_box(new MtImageComboBox)
	,_report_name_edit(new MtImageEdit)
	,_item_name_edit(new MtImageEdit)
	,_control_interval_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_item_no_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_test_id_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_instrument_factor_a_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_instrument_factor_b_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_lower_age_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_1_lower_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_1_upper_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_1_lower_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_1_upper_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_upper_age_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_2_lower_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_2_upper_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_2_lower_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_2_upper_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_3_lower_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_3_upper_limit_for_male_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_3_lower_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_3_upper_limit_for_female_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_lower_repeat_range_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_upper_repeat_range_limit_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_3_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_4_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_5_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_qualitative_limit_text_1_edit(new MtImageEdit)
	,_qualitative_limit_text_2_edit(new MtImageEdit)
	,_qualitative_limit_text_3_edit(new MtImageEdit)
	,_qualitative_limit_text_4_edit(new MtImageEdit)
	,_qualitative_limit_text_5_edit(new MtImageEdit)
	,_qualitative_limit_text_6_edit(new MtImageEdit)
	,_technical_range_lower_limit_for_class_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_technical_range_upper_limit_for_class_1_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_technical_range_lower_limit_for_class_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_technical_range_upper_limit_for_class_2_edit(new MtStrictEdit(MtStrictEdit::TYPE_DECIMALS,3))
	,_control_interval_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
	,_use_qualitative_table_check_box(new MtImageCheckBox(MtImageCheckBox::TYPE_CHECK_BOX))
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
	,_child_layout_13(new MtVerticalLayout)
	,_child_layout_14(new MtHorizonLayout)
	,_child_layout_15(new MtHorizonLayout)
	,_child_layout_16(new MtHorizonLayout)
	,_child_layout_17(new MtHorizonLayout)
	,_child_layout_18(new MtHorizonLayout)
	,_child_layout_19(new MtHorizonLayout)
	,_child_layout_20(new MtVerticalLayout)
	,_child_layout_21(new MtHorizonLayout)
	,_child_layout_22(new MtVerticalLayout)
	,_child_layout_23(new MtHorizonLayout)
	,_child_layout_24(new MtHorizonLayout)
	,_child_layout_25(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogRangeApplication
 * brief: ����������
 * param: -
 * return: --
 */
DialogRangeApplication::~DialogRangeApplication(){
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
	delete _child_layout_19;
	delete _child_layout_20;
	delete _child_layout_21;
	delete _child_layout_22;
	delete _child_layout_23;
	delete _child_layout_24;
	delete _child_layout_25;
	delete _select_test_static;
	delete _report_name_static;
	delete _item_name_static;
	delete _unit_static;
	delete _item_no_static;
	delete _data_mode_static;
	delete _test_id_static;
	delete _instrument_factor_static;
	delete _select_sample_type_static;
	delete _age_static;
	delete _male_static;
	delete _female_static;
	delete _default_age_static;
	delete _default_sex_static;
	delete _repeat_range_static;
	delete _qualitative_limit_1_static;
	delete _qualitative_limit_2_static;
	delete _qualitative_limit_3_static;
	delete _qualitative_limit_4_static;
	delete _qualitative_limit_5_static;
	delete _qualitative_limit_6_static;
	delete _expected_ranges_static;
	delete _range_static;
	delete _class_1_technical_range_static;
	delete _class_2_technical_range_static;
	delete _select_test_combo_box;
	delete _unit_combo_box;
	delete _data_mode_combo_box;
	delete _select_sample_type_combo_box;
	delete _lower_age_unit_combo_box;
	delete _upper_age_unit_combo_box;
	delete _default_age_combo_box;
	delete _default_sex_combo_box;
	delete _report_name_edit;
	delete _item_name_edit;
	delete _control_interval_edit;
	delete _item_no_edit;
	delete _test_id_edit;
	delete _instrument_factor_a_edit;
	delete _instrument_factor_b_edit;
	delete _lower_age_edit;
	delete _1_lower_limit_for_male_edit;
	delete _1_upper_limit_for_male_edit;
	delete _1_lower_limit_for_female_edit;
	delete _1_upper_limit_for_female_edit;
	delete _upper_age_edit;
	delete _2_lower_limit_for_male_edit;
	delete _2_upper_limit_for_male_edit;
	delete _2_lower_limit_for_female_edit;
	delete _2_upper_limit_for_female_edit;
	delete _3_lower_limit_for_male_edit;
	delete _3_upper_limit_for_male_edit;
	delete _3_lower_limit_for_female_edit;
	delete _3_upper_limit_for_female_edit;
	delete _lower_repeat_range_limit_edit;
	delete _upper_repeat_range_limit_edit;
	delete _control_interval_check_box;
	delete _qualitative_limit_1_edit;
	delete _qualitative_limit_2_edit;
	delete _qualitative_limit_3_edit;
	delete _qualitative_limit_4_edit;
	delete _qualitative_limit_5_edit;
	delete _qualitative_limit_text_1_edit;
	delete _qualitative_limit_text_2_edit;
	delete _qualitative_limit_text_3_edit;
	delete _qualitative_limit_text_4_edit;
	delete _qualitative_limit_text_5_edit;
	delete _qualitative_limit_text_6_edit;
	delete _technical_range_lower_limit_for_class_1_edit;
	delete _technical_range_upper_limit_for_class_1_edit;
	delete _technical_range_lower_limit_for_class_2_edit;
	delete _technical_range_upper_limit_for_class_2_edit;
	delete _use_qualitative_table_check_box;
	delete _delete_button;
	delete _ok_button;
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogRangeApplication::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SELECT_TEST,*_select_test_static);
	DDX_Control(pDX,IDC_STATIC_REPORT_NAME,*_report_name_static);
	DDX_Control(pDX,IDC_STATIC_ITEM_NAME,*_item_name_static);
	DDX_Control(pDX,IDC_STATIC_UNIT,*_unit_static);
	DDX_Control(pDX,IDC_STATIC_ITEM_NO,*_item_no_static);
	DDX_Control(pDX,IDC_STATIC_DATA_MODE,*_data_mode_static);
	DDX_Control(pDX,IDC_STATIC_TEST_ID,*_test_id_static);
	DDX_Control(pDX,IDC_STATIC_INSTRUMENT_FACTOR,*_instrument_factor_static);
	DDX_Control(pDX,IDC_STATIC_SELECT_SAMPLE_TYPE,*_select_sample_type_static);
	DDX_Control(pDX,IDC_STATIC_AGE,*_age_static);
	DDX_Control(pDX,IDC_STATIC_MALE,*_male_static);
	DDX_Control(pDX,IDC_STATIC_FEMALE,*_female_static);
	DDX_Control(pDX,IDC_STATIC_DEFAULT_AGE,*_default_age_static);
	DDX_Control(pDX,IDC_STATIC_DEFAULT_SEX,*_default_sex_static);
	DDX_Control(pDX,IDC_STATIC_REPEAT_RANGE,*_repeat_range_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_1,*_qualitative_limit_1_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_2,*_qualitative_limit_2_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_3,*_qualitative_limit_3_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_4,*_qualitative_limit_4_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_5,*_qualitative_limit_5_static);
	DDX_Control(pDX,IDC_STATIC_QUALITATIVE_LIMIT_6,*_qualitative_limit_6_static);
	DDX_Control(pDX,IDC_STATIC_EXPECTED_RANGES,*_expected_ranges_static);
	DDX_Control(pDX,IDC_STATIC_RANGE,*_range_static);
	DDX_Control(pDX,IDC_STATIC_CLASS_1_TECHNICAL_RANGE,*_class_1_technical_range_static);
	DDX_Control(pDX,IDC_STATIC_CLASS_2_TECHNICAL_RANGE,*_class_2_technical_range_static);
	DDX_Control(pDX,IDC_COMBO_SELECT_TEST,*_select_test_combo_box);
	DDX_Control(pDX,IDC_COMBO_UNIT,*_unit_combo_box);
	DDX_Control(pDX,IDC_COMBO_DATA_MODE,*_data_mode_combo_box);
	DDX_Control(pDX,IDC_COMBO_SELECT_SAMPLE_TYPE,*_select_sample_type_combo_box);
	DDX_Control(pDX,IDC_COMBO_LOWER_AGE_UNIT,*_lower_age_unit_combo_box);
	DDX_Control(pDX,IDC_COMBO_UPPER_AGE_UNIT,*_upper_age_unit_combo_box);
	DDX_Control(pDX,IDC_COMBO_DEFAULT_AGE,*_default_age_combo_box);
	DDX_Control(pDX,IDC_COMBO_DEFAULT_SEX,*_default_sex_combo_box);
	DDX_Control(pDX,IDC_EDIT_REPORT_NAME,*_report_name_edit);
	DDX_Control(pDX,IDC_EDIT_ITEM_NAME,*_item_name_edit);
	DDX_Control(pDX,IDC_EDIT_CONTROL_INTERVAL,*_control_interval_edit);
	DDX_Control(pDX,IDC_EDIT_ITEM_NO,*_item_no_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_ID,*_test_id_edit);
	DDX_Control(pDX,IDC_EDIT_INSTRUMENT_FACTOR_A,*_instrument_factor_a_edit);
	DDX_Control(pDX,IDC_EDIT_INSTRUMENT_FACTOR_B,*_instrument_factor_b_edit);
	DDX_Control(pDX,IDC_EDIT_LOWER_AGE,*_lower_age_edit);
	DDX_Control(pDX,IDC_EDIT_1_LOWER_LIMIT_FOR_MALE,*_1_lower_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_1_UPPER_LIMIT_FOR_MALE,*_1_upper_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_1_LOWER_LIMIT_FOR_FEMALE,*_1_lower_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_1_UPPER_LIMIT_FOR_FEMALE,*_1_upper_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_UPPER_AGE,*_upper_age_edit);
	DDX_Control(pDX,IDC_EDIT_2_LOWER_LIMIT_FOR_MALE,*_2_lower_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_2_UPPER_LIMIT_FOR_MALE,*_2_upper_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_2_LOWER_LIMIT_FOR_FEMALE,*_2_lower_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_2_UPPER_LIMIT_FOR_FEMALE,*_2_upper_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_3_LOWER_LIMIT_FOR_MALE,*_3_lower_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_3_UPPER_LIMIT_FOR_MALE,*_3_upper_limit_for_male_edit);
	DDX_Control(pDX,IDC_EDIT_3_LOWER_LIMIT_FOR_FEMALE,*_3_lower_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_3_UPPER_LIMIT_FOR_FEMALE,*_3_upper_limit_for_female_edit);
	DDX_Control(pDX,IDC_EDIT_LOWER_REPEAT_RANGE_LIMIT,*_lower_repeat_range_limit_edit);
	DDX_Control(pDX,IDC_EDIT_UPPER_REPEAT_RANGE_LIMIT,*_upper_repeat_range_limit_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_1,*_qualitative_limit_1_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_2,*_qualitative_limit_2_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_3,*_qualitative_limit_3_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_4,*_qualitative_limit_4_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_5,*_qualitative_limit_5_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_1,*_qualitative_limit_text_1_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_2,*_qualitative_limit_text_2_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_3,*_qualitative_limit_text_3_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_4,*_qualitative_limit_text_4_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_5,*_qualitative_limit_text_5_edit);
	DDX_Control(pDX,IDC_EDIT_QUALITATIVE_LIMIT_TEXT_6,*_qualitative_limit_text_6_edit);
	DDX_Control(pDX,IDC_EDIT_TECHNICAL_RANGE_LOWER_LIMIT_FOR_CLASS_1,*_technical_range_lower_limit_for_class_1_edit);
	DDX_Control(pDX,IDC_EDIT_TECHNICAL_RANGE_UPPER_LIMIT_FOR_CLASS_1,*_technical_range_upper_limit_for_class_1_edit);
	DDX_Control(pDX,IDC_EDIT_TECHNICAL_RANGE_LOWER_LIMIT_FOR_CLASS_2,*_technical_range_lower_limit_for_class_2_edit);
	DDX_Control(pDX,IDC_EDIT_TECHNICAL_RANGE_UPPER_LIMIT_FOR_CLASS_2,*_technical_range_upper_limit_for_class_2_edit);
	DDX_Control(pDX,IDC_CHECK_CONTROL_INTERVAL,*_control_interval_check_box);
	DDX_Control(pDX,IDC_CHECK_USE_QUALITATIVE_TABLE,*_use_qualitative_table_check_box);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
}

/**
 * name: OnInitDialog
 * breif: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogRangeApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի����пؼ���
	init_controls();
	////////////////////////////////////////////////////////////////
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
BOOL DialogRangeApplication::OnCommand(WPARAM wParam,LPARAM lParam){
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

BEGIN_MESSAGE_MAP(DialogRangeApplication,DialogPageBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_CONTROL_INTERVAL,&DialogRangeApplication::OnBnClickedCheckControlInterval)
	ON_BN_CLICKED(IDC_CHECK_USE_QUALITATIVE_TABLE,&DialogRangeApplication::OnBnClickedCheckUseQualitativeTable)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_TEST,&DialogRangeApplication::OnCbnSelchangeComboSelectTest)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_SAMPLE_TYPE,&DialogRangeApplication::OnCbnSelchangeComboSelectSampleType)
	ON_BN_CLICKED(IDC_BUTTON_DELETE,&DialogRangeApplication::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogRangeApplication::OnBnClickedButtonOk)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,&DialogRangeApplication::OnUpdateDataForControlsByItemID)
	ON_MESSAGE(WM_COMMIT_DATA_OF_CONTROLS,&DialogRangeApplication::OnCommitDataOfControls)
END_MESSAGE_MAP()

//DialogRangeApplication message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogRangeApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType, cx, cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
	//2.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_13->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_expected_ranges_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_23->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_range_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name:  OnBnClickedCheckControlInterval
 * brief: �û�����ʿؼ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnBnClickedCheckControlInterval(){
	//TODO: Add your control notification handler code here
	//1.����������Ϣ�Ĵ�����
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.�����ǰ�ʿؼ����ѡ����ѡ��״̬��
	if(_control_interval_check_box->get_checked()){
		_control_interval_check_box->set_checked(FALSE);
		_control_interval_edit->SetWindowText(_T(""));
		_control_interval_edit->EnableWindow(FALSE);
	}
	//3.�����ǰ�ʿؼ����ѡ���ڷ�ѡ��״̬��
	else{
		_control_interval_check_box->set_checked(TRUE);
		_control_interval_edit->SetWindowText(_T(""));
		_control_interval_edit->EnableWindow(TRUE);
	}
	//4.��⵱ǰ�ؼ������Ƿ����仯��
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnBnClickedCheckUseQualitativeTable
 * breif: �û����ʹ�ö��Ա�ѡ����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnBnClickedCheckUseQualitativeTable(){
	// TODO: Add your control notification handler code here
	//1.����������Ϣ�Ĵ�����
	MtAutoReset<BOOL> auto_reset(
		_is_command_message_masked,TRUE,FALSE);
	//2.�����ǰʹ�ö��Ա�ѡ����ѡ��״̬��
	if(_use_qualitative_table_check_box->get_checked()){
		_use_qualitative_table_check_box->set_checked(FALSE);
		_qualitative_limit_1_edit->SetWindowText(_T(""));
		_qualitative_limit_1_edit->EnableWindow(FALSE);
		_qualitative_limit_text_1_edit->SetWindowText(_T(""));
		_qualitative_limit_text_1_edit->EnableWindow(FALSE);
		_qualitative_limit_2_edit->SetWindowText(_T(""));
		_qualitative_limit_2_edit->EnableWindow(FALSE);
		_qualitative_limit_text_2_edit->SetWindowText(_T(""));
		_qualitative_limit_text_2_edit->EnableWindow(FALSE);
		_qualitative_limit_3_edit->SetWindowText(_T(""));
		_qualitative_limit_3_edit->EnableWindow(FALSE);
		_qualitative_limit_text_3_edit->SetWindowText(_T(""));
		_qualitative_limit_text_3_edit->EnableWindow(FALSE);
		_qualitative_limit_4_edit->SetWindowText(_T(""));
		_qualitative_limit_4_edit->EnableWindow(FALSE);
		_qualitative_limit_text_4_edit->SetWindowText(_T(""));
		_qualitative_limit_text_4_edit->EnableWindow(FALSE);
		_qualitative_limit_5_edit->SetWindowText(_T(""));
		_qualitative_limit_5_edit->EnableWindow(FALSE);
		_qualitative_limit_text_5_edit->SetWindowText(_T(""));
		_qualitative_limit_text_5_edit->EnableWindow(FALSE);
		_qualitative_limit_text_6_edit->SetWindowText(_T(""));
		_qualitative_limit_text_6_edit->EnableWindow(FALSE);
	}
	//3.�����ǰʹ�ö��Ա�ѡ���ڷ�ѡ��״̬��
	else{
		_use_qualitative_table_check_box->set_checked(TRUE);
		_qualitative_limit_1_edit->SetWindowText(_T(""));
		_qualitative_limit_1_edit->EnableWindow(TRUE);
		_qualitative_limit_text_1_edit->SetWindowText(_T(""));
		_qualitative_limit_text_1_edit->EnableWindow(TRUE);
		_qualitative_limit_2_edit->SetWindowText(_T(""));
		_qualitative_limit_2_edit->EnableWindow(TRUE);
		_qualitative_limit_text_2_edit->SetWindowText(_T(""));
		_qualitative_limit_text_2_edit->EnableWindow(TRUE);
		_qualitative_limit_3_edit->SetWindowText(_T(""));
		_qualitative_limit_3_edit->EnableWindow(TRUE);
		_qualitative_limit_text_3_edit->SetWindowText(_T(""));
		_qualitative_limit_text_3_edit->EnableWindow(TRUE);
		_qualitative_limit_4_edit->SetWindowText(_T(""));
		_qualitative_limit_4_edit->EnableWindow(TRUE);
		_qualitative_limit_text_4_edit->SetWindowText(_T(""));
		_qualitative_limit_text_4_edit->EnableWindow(TRUE);
		_qualitative_limit_5_edit->SetWindowText(_T(""));
		_qualitative_limit_5_edit->EnableWindow(TRUE);
		_qualitative_limit_text_5_edit->SetWindowText(_T(""));
		_qualitative_limit_text_5_edit->EnableWindow(TRUE);
		_qualitative_limit_text_6_edit->SetWindowText(_T(""));
		_qualitative_limit_text_6_edit->EnableWindow(TRUE);
	}
	//4.��⵱ǰ�ؼ������Ƿ����仯��
	if(is_data_of_controls_changed()){
		_ok_button->EnableWindow(TRUE);
	}else{
		_ok_button->EnableWindow(FALSE);
	}
}

/**
 * name: OnCbnSelchangeComboSelectTest
 * brief: ��ѡ����Ŀ����������Ŀ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnCbnSelchangeComboSelectTest(){
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
			theme->get_string(IDS_STRING429),this);
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
 * name: OnCbnSelchangeComboSelectSampleType
 * brief: ���������͡���������Ŀ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnCbnSelchangeComboSelectSampleType(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ�û�ѡ����������ͱ�ʶ��
	const int item=_select_sample_type_combo_box->GetCurSel();
	if(item<0){
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_sample_type_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			_sample_type_id,*_select_sample_type_combo_box));
		return;
	}
	const int sample_type_id=static_cast<int>(
		_select_sample_type_combo_box->GetItemData(item));//��ǰ�û�ѡ����������ͱ�ʶ��
	//3.����û�ѡ����������ͱ�ʶ���뵱ǰ�������ͱ�ʶ��ͬ����ֱ�ӷ��ء�
	if(sample_type_id==_sample_type_id){
		return;
	}
	//4.���Ȼָ���ǰ������ѡ�Ϊ�˼���Ƿ��в�����δ���棩��
	{
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_sample_type_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			_sample_type_id,*_select_sample_type_combo_box));
	}
	//5.�����ǰ����Ĳ��������ı䡣
	if(is_data_of_controls_changed()){
		//5-1.�����û��Ƿ񱣴浱ǰ������
		const unsigned int result=QuestionMessageBoxEx(
			theme->get_string(IDS_STRING430),this);
		//5-2.�����ǰ�û�ѡ��ȡ������ť��
		if(IDCANCEL==result){
			/*
			//5-1-1.���οؼ����ݵĸ��¡�
			MtAutoReset<BOOL> auto_reset(
				_is_command_message_masked,TRUE,FALSE);
			//5-1-2.�ظ���ǰ������ѡ�����ݡ�
			_select_sample_type_combo_box->SetCurSel(
				get_combo_box_index_by_item_data(
				_sample_type_id,*_select_sample_type_combo_box));
			//5-1-3.�������е���ֱ�ӷ��ء�
			*/
			return;
		}
		//5-3.�����ǰ�û�ѡ�񡰷񡱰�ť��
		else if(IDNO==result){
		}
		//5-4.�����ǰ�û�ѡ���ǡ���ť��
		else{
			if(commit_data_of_controls(*((DatabaseManager::instance())->
				get_database(DatabaseManager::DATABASE_NAME_MAIN)))<0){//�ύ�ؼ��е����ݡ�
				/*
				//5-4-1.���οؼ����ݵĸ��¡�
				MtAutoReset<BOOL> auto_reset(
					_is_command_message_masked,TRUE,FALSE);
				//5-4-2.�ظ���ǰ������ѡ�����ݡ�
				_select_sample_type_combo_box->SetCurSel(
					get_combo_box_index_by_item_data(
					_sample_type_id,*_select_sample_type_combo_box));
				//5-4-3.�������е���ֱ�ӷ��ء�
				*/
				return;
			}
		}
	}
	//6.����ɹ����е��ˣ� ������������������ѡ�
	{
		MtAutoReset<BOOL> auto_reset(
			_is_command_message_masked,TRUE,FALSE);
		_select_sample_type_combo_box->SetCurSel(
			get_combo_box_index_by_item_data(
			sample_type_id,*_select_sample_type_combo_box));
		_sample_type_id=sample_type_id;
	}
	//7.��ʾ��ѡ�����Ŀ�����������Ϣ��
	GetParent()->SendMessage(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,
		static_cast<WPARAM>(_item_id),0);
}

/**
 * name: OnBnClickedButtonDelete
 * brief: �û����ɾ����ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnBnClickedButtonDelete(){
	//TODO: Add your control notification handler code here
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	Applications *applications=Applications::instance();
	//2.��ȡ��ǰ����ɾ������Ŀ��ʶ��
	const int item=_select_test_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING426),this);
		return;
	}
	const int item_id=static_cast<int>(_select_test_combo_box->GetItemData(item));
	//3.ѯ���û��Ƿ�����ɾ����ǰ��Ŀ��
	if(IDNO==QuestionMessageBox(theme->get_string(IDS_STRING427),this)){
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
 * brief: �û����ȷ�ϰ�ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogRangeApplication::OnBnClickedButtonOk(){
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
LRESULT DialogRangeApplication::OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM /*lParam*/){
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
LRESULT DialogRangeApplication::OnCommitDataOfControls(WPARAM /*wParam*/,LPARAM /*lParam*/){
	//1.��������е�����û�з����仯����ֱ�ӷ��ء�
	if(!is_data_of_controls_changed()){
		return(0);
	}
	//2.ѯ���û��Ƿ�ϣ�����浱ǰ���ݡ�
	Theme *theme=Theme::instance();
	const unsigned int result=QuestionMessageBoxEx(
		theme->get_string(IDS_STRING431),this);
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
void DialogRangeApplication::init_controls(){
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
	_report_name_static->set_text_color(255,50,50,50);
	_report_name_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_item_name_static->set_text_color(255,50,50,50);
	_item_name_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_unit_static->set_text_color(255,50,50,50);
	_unit_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_item_no_static->set_text_color(255,50,50,50);
	_item_no_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_data_mode_static->set_text_color(255,50,50,50);
	_data_mode_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_test_id_static->set_text_color(255,50,50,50);
	_test_id_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_instrument_factor_static->set_text_color(255,50,50,50);
	_instrument_factor_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_select_sample_type_static->set_text_color(255,50,50,50);
	_select_sample_type_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_age_static->set_text_color(255,50,50,50);
	_age_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_male_static->set_text_color(255,50,50,50);
	_male_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_female_static->set_text_color(255,50,50,50);
	_female_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_default_age_static->set_text_color(255,50,50,50);
	_default_age_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_default_sex_static->set_text_color(255,50,50,50);
	_default_sex_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_repeat_range_static->set_text_color(255,50,50,50);
	_repeat_range_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_1_static->set_text_color(255,50,50,50);
	_qualitative_limit_1_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_2_static->set_text_color(255,50,50,50);
	_qualitative_limit_2_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_3_static->set_text_color(255,50,50,50);
	_qualitative_limit_3_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_4_static->set_text_color(255,50,50,50);
	_qualitative_limit_4_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_5_static->set_text_color(255,50,50,50);
	_qualitative_limit_5_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_qualitative_limit_6_static->set_text_color(255,50,50,50);
	_qualitative_limit_6_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_expected_ranges_static->set_text_color(255,255,255,255);
	_expected_ranges_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_expected_ranges_static->load_background_image(theme->get_image(25));
	_expected_ranges_static->set_background_image_stretching_factors(10,29,10,2);
	_range_static->set_text_color(255,255,255,255);
	_range_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_range_static->load_background_image(theme->get_image(36));
	_range_static->set_background_image_stretching_factors(10,29,10,2);
	_class_1_technical_range_static->set_text_color(255,50,50,50);
	_class_1_technical_range_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_class_2_technical_range_static->set_text_color(255,50,50,50);
	_class_2_technical_range_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
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
	_unit_combo_box->set_text_color(255,50,50,50);
	_unit_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_unit_combo_box->set_list_box_text_color(255,50,50,50);
	_unit_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_unit_combo_box->load_background_image(theme->get_image(27),1,4);
	_unit_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_unit_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_unit_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_data_mode_combo_box->set_text_color(255,50,50,50);
	_data_mode_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_data_mode_combo_box->set_list_box_text_color(255,50,50,50);
	_data_mode_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_data_mode_combo_box->load_background_image(theme->get_image(27),1,4);
	_data_mode_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_data_mode_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_data_mode_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_select_sample_type_combo_box->set_text_color(255,50,50,50);
	_select_sample_type_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_select_sample_type_combo_box->set_list_box_text_color(255,50,50,50);
	_select_sample_type_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_select_sample_type_combo_box->load_background_image(theme->get_image(27),1,4);
	_select_sample_type_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_select_sample_type_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_select_sample_type_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_lower_age_unit_combo_box->set_text_color(255,50,50,50);
	_lower_age_unit_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_lower_age_unit_combo_box->set_list_box_text_color(255,50,50,50);
	_lower_age_unit_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_lower_age_unit_combo_box->load_background_image(theme->get_image(27),1,4);
	_lower_age_unit_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_lower_age_unit_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_lower_age_unit_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_upper_age_unit_combo_box->set_text_color(255,50,50,50);
	_upper_age_unit_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_upper_age_unit_combo_box->set_list_box_text_color(255,50,50,50);
	_upper_age_unit_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_upper_age_unit_combo_box->load_background_image(theme->get_image(27),1,4);
	_upper_age_unit_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_upper_age_unit_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_upper_age_unit_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_default_age_combo_box->set_text_color(255,50,50,50);
	_default_age_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_default_age_combo_box->set_list_box_text_color(255,50,50,50);
	_default_age_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_default_age_combo_box->load_background_image(theme->get_image(27),1,4);
	_default_age_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_default_age_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_default_age_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_default_sex_combo_box->set_text_color(255,50,50,50);
	_default_sex_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_default_sex_combo_box->set_list_box_text_color(255,50,50,50);
	_default_sex_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_default_sex_combo_box->load_background_image(theme->get_image(27),1,4);
	_default_sex_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_default_sex_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_default_sex_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	init_combo_boxes(*((DatabaseManager::instance())->get_database(DatabaseManager::DATABASE_NAME_MAIN)));
	//2-3.��ʼ���ı��༭��
	_report_name_edit->set_text_color(50,50,50);
	_report_name_edit->load_background_image(theme->get_image(29),1,3);
	_report_name_edit->set_background_image_stretching_factors(5,5,5,5);
	_item_name_edit->set_text_color(50,50,50);
	_item_name_edit->load_background_image(theme->get_image(29),1,3);
	_item_name_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_interval_edit->set_text_color(50,50,50);
	_control_interval_edit->load_background_image(theme->get_image(29),1,3);
	_control_interval_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_interval_edit->SetLimitText(4);
	_item_no_edit->set_text_color(50,50,50);
	_item_no_edit->load_background_image(theme->get_image(29),1,3);
	_item_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_item_no_edit->EnableWindow(FALSE);
	_item_no_edit->SetLimitText(3);
	_test_id_edit->set_text_color(50,50,50);
	_test_id_edit->load_background_image(theme->get_image(29),1,3);
	_test_id_edit->set_background_image_stretching_factors(5,5,5,5);
	_test_id_edit->EnableWindow(FALSE);
	_test_id_edit->SetLimitText(3);
	_instrument_factor_a_edit->set_text_color(50,50,50);
	_instrument_factor_a_edit->load_background_image(theme->get_image(29),1,3);
	_instrument_factor_a_edit->set_background_image_stretching_factors(5,5,5,5);
	_instrument_factor_a_edit->SetLimitText(10);
	_instrument_factor_b_edit->set_text_color(50,50,50);
	_instrument_factor_b_edit->load_background_image(theme->get_image(29),1,3);
	_instrument_factor_b_edit->set_background_image_stretching_factors(5,5,5,5);
	_instrument_factor_b_edit->SetLimitText(10);
	_lower_age_edit->set_text_color(50,50,50);
	_lower_age_edit->load_background_image(theme->get_image(29),1,3);
	_lower_age_edit->set_background_image_stretching_factors(5,5,5,5);
	_lower_age_edit->SetLimitText(3);
	_1_lower_limit_for_male_edit->set_text_color(50,50,50);
	_1_lower_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_1_lower_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_1_lower_limit_for_male_edit->SetLimitText(10);
	_1_upper_limit_for_male_edit->set_text_color(50,50,50);
	_1_upper_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_1_upper_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_1_upper_limit_for_male_edit->SetLimitText(10);
	_1_lower_limit_for_female_edit->set_text_color(50,50,50);
	_1_lower_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_1_lower_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_1_lower_limit_for_female_edit->SetLimitText(10);
	_1_upper_limit_for_female_edit->set_text_color(50,50,50);
	_1_upper_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_1_upper_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_1_upper_limit_for_female_edit->SetLimitText(10);
	_upper_age_edit->set_text_color(50,50,50);
	_upper_age_edit->load_background_image(theme->get_image(29),1,3);
	_upper_age_edit->set_background_image_stretching_factors(5,5,5,5);
	_upper_age_edit->SetLimitText(3);
	_2_lower_limit_for_male_edit->set_text_color(50,50,50);
	_2_lower_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_2_lower_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_2_lower_limit_for_male_edit->SetLimitText(10);
	_2_upper_limit_for_male_edit->set_text_color(50,50,50);
	_2_upper_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_2_upper_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_2_upper_limit_for_male_edit->SetLimitText(10);
	_2_lower_limit_for_female_edit->set_text_color(50,50,50);
	_2_lower_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_2_lower_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_2_lower_limit_for_female_edit->SetLimitText(10);
	_2_upper_limit_for_female_edit->set_text_color(50,50,50);
	_2_upper_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_2_upper_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_2_upper_limit_for_female_edit->SetLimitText(10);
	_3_lower_limit_for_male_edit->set_text_color(50,50,50);
	_3_lower_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_3_lower_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_3_lower_limit_for_male_edit->SetLimitText(10);
	_3_upper_limit_for_male_edit->set_text_color(50,50,50);
	_3_upper_limit_for_male_edit->load_background_image(theme->get_image(29),1,3);
	_3_upper_limit_for_male_edit->set_background_image_stretching_factors(5,5,5,5);
	_3_upper_limit_for_male_edit->SetLimitText(10);
	_3_lower_limit_for_female_edit->set_text_color(50,50,50);
	_3_lower_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_3_lower_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_3_lower_limit_for_female_edit->SetLimitText(10);
	_3_upper_limit_for_female_edit->set_text_color(50,50,50);
	_3_upper_limit_for_female_edit->load_background_image(theme->get_image(29),1,3);
	_3_upper_limit_for_female_edit->set_background_image_stretching_factors(5,5,5,5);
	_3_upper_limit_for_female_edit->SetLimitText(10);
	_lower_repeat_range_limit_edit->set_text_color(50,50,50);
	_lower_repeat_range_limit_edit->load_background_image(theme->get_image(29),1,3);
	_lower_repeat_range_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_lower_repeat_range_limit_edit->SetLimitText(10);
	_upper_repeat_range_limit_edit->set_text_color(50,50,50);
	_upper_repeat_range_limit_edit->load_background_image(theme->get_image(29),1,3);
	_upper_repeat_range_limit_edit->set_background_image_stretching_factors(5,5,5,5);
	_upper_repeat_range_limit_edit->SetLimitText(10);
	_qualitative_limit_1_edit->set_text_color(50,50,50);
	_qualitative_limit_1_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_1_edit->SetLimitText(10);
	_qualitative_limit_2_edit->set_text_color(50,50,50);
	_qualitative_limit_2_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_2_edit->SetLimitText(10);
	_qualitative_limit_3_edit->set_text_color(50,50,50);
	_qualitative_limit_3_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_3_edit->SetLimitText(10);
	_qualitative_limit_4_edit->set_text_color(50,50,50);
	_qualitative_limit_4_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_4_edit->SetLimitText(10);
	_qualitative_limit_5_edit->set_text_color(50,50,50);
	_qualitative_limit_5_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_5_edit->SetLimitText(10);
	_qualitative_limit_text_1_edit->set_text_color(50,50,50);
	_qualitative_limit_text_1_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_text_2_edit->set_text_color(50,50,50);
	_qualitative_limit_text_2_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_text_3_edit->set_text_color(50,50,50);
	_qualitative_limit_text_3_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_3_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_text_4_edit->set_text_color(50,50,50);
	_qualitative_limit_text_4_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_4_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_text_5_edit->set_text_color(50,50,50);
	_qualitative_limit_text_5_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_5_edit->set_background_image_stretching_factors(5,5,5,5);
	_qualitative_limit_text_6_edit->set_text_color(50,50,50);
	_qualitative_limit_text_6_edit->load_background_image(theme->get_image(29),1,3);
	_qualitative_limit_text_6_edit->set_background_image_stretching_factors(5,5,5,5);
	_technical_range_lower_limit_for_class_1_edit->set_text_color(50,50,50);
	_technical_range_lower_limit_for_class_1_edit->load_background_image(theme->get_image(29),1,3);
	_technical_range_lower_limit_for_class_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_technical_range_lower_limit_for_class_1_edit->SetLimitText(10);
	_technical_range_upper_limit_for_class_1_edit->set_text_color(50,50,50);
	_technical_range_upper_limit_for_class_1_edit->load_background_image(theme->get_image(29),1,3);
	_technical_range_upper_limit_for_class_1_edit->set_background_image_stretching_factors(5,5,5,5);
	_technical_range_upper_limit_for_class_1_edit->SetLimitText(10);
	_technical_range_lower_limit_for_class_2_edit->set_text_color(50,50,50);
	_technical_range_lower_limit_for_class_2_edit->load_background_image(theme->get_image(29),1,3);
	_technical_range_lower_limit_for_class_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_technical_range_lower_limit_for_class_2_edit->SetLimitText(10);
	_technical_range_upper_limit_for_class_2_edit->set_text_color(50,50,50);
	_technical_range_upper_limit_for_class_2_edit->load_background_image(theme->get_image(29),1,3);
	_technical_range_upper_limit_for_class_2_edit->set_background_image_stretching_factors(5,5,5,5);
	_technical_range_upper_limit_for_class_2_edit->SetLimitText(10);
	//2-4.��ʼ����ѡ��
	_control_interval_check_box->set_text_color(255,50,50,50);
	_control_interval_check_box->load_foreground_image(theme->get_image(30),1,6);
	_control_interval_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_control_interval_check_box->load_background_image(theme->get_image(1),1,6);
	_use_qualitative_table_check_box->set_text_color(255,50,50,50);
	_use_qualitative_table_check_box->load_foreground_image(theme->get_image(30),1,6);
	_use_qualitative_table_check_box->set_foreground_image_alignment(MtImageCheckBox::ALIGNMENT_LEFT|
		MtImageCheckBox::ALIGNMENT_VCENTER);
	_use_qualitative_table_check_box->load_background_image(theme->get_image(1),1,6);
	//2-5.��ʼ����ť��
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//3.��ʼ���Ի����в��֡�
	//3-1.��ʼ���Ӳ���1��
	_child_layout_1->add_fixed_window(_select_test_static,100);
	_child_layout_1->add_fixed_window(_select_test_combo_box,150);
	_child_layout_1->add_spacing(50);
	_child_layout_1->add_fixed_window(_report_name_static,150);
	_child_layout_1->add_fixed_window(_report_name_edit,350);
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_item_name_static,100);
	_child_layout_2->add_fixed_window(_item_name_edit,150);
	_child_layout_2->add_spacing(50);
	_child_layout_2->add_fixed_window(_control_interval_check_box,160);
	_child_layout_2->add_fixed_window(_control_interval_edit,100);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_unit_static,50);
	_child_layout_2->add_fixed_window(_unit_combo_box,100);
	//3-3.��ʼ���Ӳ���3��
	_child_layout_3->add_fixed_window(_item_no_static,100);
	_child_layout_3->add_fixed_window(_item_no_edit,50);
	_child_layout_3->add_spacing(100);
	_child_layout_3->add_spacing(50);
	_child_layout_3->add_fixed_window(_instrument_factor_static,200);
	_child_layout_3->add_fixed_window(_instrument_factor_a_edit,100);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_fixed_window(_instrument_factor_b_edit,100);
	//3-4.��ʼ���Ӳ���4��
	_child_layout_4->add_fixed_window(_test_id_static,100);
	_child_layout_4->add_fixed_window(_test_id_edit,50);
	_child_layout_4->add_spacing(100);
	_child_layout_4->add_spacing(50);
	_child_layout_4->add_fixed_window(_data_mode_static,100);
	_child_layout_4->add_fixed_window(_data_mode_combo_box,150);
	//3-5.��ʼ���Ӳ���5��
	_child_layout_5->add_fixed_window(_select_sample_type_static,180);
	_child_layout_5->add_fixed_window(_select_sample_type_combo_box,150);
	//3-6.��ʼ���Ӳ���6��
	_child_layout_6->add_stretch(50);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_age_static,100);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_male_static,205);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_female_static,205);
	//3-7.��ʼ���Ӳ���7��
	_child_layout_7->add_window(_lower_age_edit,50);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_lower_age_unit_combo_box,100);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_1_lower_limit_for_male_edit,100);
	_child_layout_7->add_stretch(5);
	_child_layout_7->add_window(_1_upper_limit_for_male_edit,100);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_1_lower_limit_for_female_edit,100);
	_child_layout_7->add_stretch(5);
	_child_layout_7->add_window(_1_upper_limit_for_female_edit,100);
	//3-8.��ʼ���Ӳ���8��
	_child_layout_8->add_window(_upper_age_edit,50);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_upper_age_unit_combo_box,100);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_2_lower_limit_for_male_edit,100);
	_child_layout_8->add_stretch(5);
	_child_layout_8->add_window(_2_upper_limit_for_male_edit,100);
	_child_layout_8->add_spacing(5);
	_child_layout_8->add_window(_2_lower_limit_for_female_edit,100);
	_child_layout_8->add_stretch(5);
	_child_layout_8->add_window(_2_upper_limit_for_female_edit,100);
	//3-9.��ʼ���Ӳ���9��
	_child_layout_9->add_stretch(50);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_stretch(100);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_3_lower_limit_for_male_edit,100);
	_child_layout_9->add_stretch(5);
	_child_layout_9->add_window(_3_upper_limit_for_male_edit,100);
	_child_layout_9->add_spacing(5);
	_child_layout_9->add_window(_3_lower_limit_for_female_edit,100);
	_child_layout_9->add_stretch(5);
	_child_layout_9->add_window(_3_upper_limit_for_female_edit,100);
	//3-10.��ʼ���Ӳ���10��
	_child_layout_10->set_margin(3,32,3,3);
	_child_layout_10->add_layout(_child_layout_6,24);
	_child_layout_10->add_stretch(3);
	_child_layout_10->add_layout(_child_layout_7,24);
	_child_layout_10->add_stretch(3);
	_child_layout_10->add_layout(_child_layout_8,24);
	_child_layout_10->add_stretch(3);
	_child_layout_10->add_layout(_child_layout_9,24);
	//3-11.��ʼ���Ӳ���11��
	_child_layout_11->add_fixed_window(_default_age_static,120);
	_child_layout_11->add_fixed_window(_default_age_combo_box,150);
	//3-12.��ʼ���Ӳ���12��
	_child_layout_12->add_fixed_window(_default_sex_static,120);
	_child_layout_12->add_fixed_window(_default_sex_combo_box,80);
	_child_layout_12->add_spacing(5);
	_child_layout_12->add_fixed_window(_repeat_range_static,130);
	_child_layout_12->add_fixed_window(_lower_repeat_range_limit_edit,100);
	_child_layout_12->add_spacing(5);
	_child_layout_12->add_fixed_window(_upper_repeat_range_limit_edit,100);
	//3-13.��ʼ���Ӳ���13��
	_child_layout_13->add_layout(_child_layout_10,140);
	_child_layout_13->add_stretch(3);
	_child_layout_13->add_layout(_child_layout_11,24);
	_child_layout_13->add_stretch(3);
	_child_layout_13->add_layout(_child_layout_12,24);
	//3-14.��ʼ���Ӳ���14��
	_child_layout_14->add_fixed_window(_qualitative_limit_1_static,50);
	_child_layout_14->add_window(_qualitative_limit_1_edit,50);
	_child_layout_14->add_stretch(5);
	_child_layout_14->add_window(_qualitative_limit_text_1_edit,100);
	//3-15.��ʼ���Ӳ���15��
	_child_layout_15->add_fixed_window(_qualitative_limit_2_static,50);
	_child_layout_15->add_window(_qualitative_limit_2_edit,50);
	_child_layout_15->add_stretch(5);
	_child_layout_15->add_window(_qualitative_limit_text_2_edit,100);
	//3-16.��ʼ���Ӳ���16��
	_child_layout_16->add_fixed_window(_qualitative_limit_3_static,50);
	_child_layout_16->add_window(_qualitative_limit_3_edit,50);
	_child_layout_16->add_stretch(5);
	_child_layout_16->add_window(_qualitative_limit_text_3_edit,100);
	//3-17.��ʼ���Ӳ���17��
	_child_layout_17->add_fixed_window(_qualitative_limit_4_static,50);
	_child_layout_17->add_window(_qualitative_limit_4_edit,50);
	_child_layout_17->add_stretch(5);
	_child_layout_17->add_window(_qualitative_limit_text_4_edit,100);
	//3-18.��ʼ���Ӳ���18��
	_child_layout_18->add_fixed_window(_qualitative_limit_5_static,50);
	_child_layout_18->add_window(_qualitative_limit_5_edit,50);
	_child_layout_18->add_stretch(5);
	_child_layout_18->add_window(_qualitative_limit_text_5_edit,100);
	//3-19.��ʼ���Ӳ���19��
	_child_layout_19->add_fixed_window(_qualitative_limit_6_static,50);
	_child_layout_19->add_stretch(50);
	_child_layout_19->add_stretch(5);
	_child_layout_19->add_window(_qualitative_limit_text_6_edit,100);
	//3-20.��ʼ���Ӳ���20��
	_child_layout_20->add_fixed_window(_use_qualitative_table_check_box,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_14,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_15,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_16,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_17,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_18,24);
	_child_layout_20->add_stretch(1);
	_child_layout_20->add_fixed_layout(_child_layout_19,24);
	//3-21.��ʼ���Ӳ���21��
	_child_layout_21->add_fixed_layout(_child_layout_13,550);
	_child_layout_21->add_spacing(10);
	_child_layout_21->add_fixed_layout(_child_layout_20,250);
	//3-22.��ʼ���Ӳ���22��
	_child_layout_22->set_margin(3,3,3,3);
	_child_layout_22->add_layout(_child_layout_5,24);
	_child_layout_22->add_stretch(3);
	_child_layout_22->add_layout(_child_layout_21,192);
	//3-23.��ʼ���Ӳ���23��
	_child_layout_23->add_fixed_layout(_child_layout_22,815);
	//3-24.��ʼ���Ӳ���24��
	_child_layout_24->add_fixed_window(_class_1_technical_range_static,210);
	_child_layout_24->add_fixed_window(_technical_range_lower_limit_for_class_1_edit,80);
	_child_layout_24->add_spacing(5);
	_child_layout_24->add_fixed_window(_technical_range_upper_limit_for_class_1_edit,80);
	_child_layout_24->add_spacing(5);
	_child_layout_24->add_fixed_window(_class_2_technical_range_static,210);
	_child_layout_24->add_fixed_window(_technical_range_lower_limit_for_class_2_edit,80);
	_child_layout_24->add_spacing(5);
	_child_layout_24->add_fixed_window(_technical_range_upper_limit_for_class_2_edit,80);
	//3-25.��ʼ���Ӳ���25��
	_child_layout_25->add_fixed_window(_delete_button,200);
	_child_layout_25->add_stretch(1);
	_child_layout_25->add_fixed_window(_ok_button,200);
	_child_layout_25->add_stretch(1);
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
	_main_layout->add_fixed_layout(_child_layout_23,230);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_24,24);
	_main_layout->add_stretch(1);
	_main_layout->add_fixed_layout(_child_layout_25,40);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_13->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_expected_ranges_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_23->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_range_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//6.���µ�ǰ�ؼ��е����ݡ�
	update_data_for_controls();
}

/**
 * name: init_combo_boxes
 * brief: ��ʼ�������е������򣬽����ݿ��е����ݲ��뵽�������С�
 * param: database - ָ�������ݿ⡣
 * return: --
 */
void DialogRangeApplication::init_combo_boxes(Database &database){
	//1.�����ݿ��м��ص�λ��Ϣ�����Ҳ��뵽����λ��Ϣ���������С�
	//1-1.����SQL��䣬׼�������ݿ��м��ص�λ��Ϣ��
	CString sql(_T(""));
	sql.Format(_T("SELECT * FROM [unit] ORDER BY [id] ASC"));
	//1-2.�����ݿ��м��ص�λ��Ϣ��¼����
	Database::PtrToRecordset records=database.get_recordset(sql);
	//1-3.����λ��Ϣ��¼���е����ݲ��뵽����λ��Ϣ���������С�
	//1-3-1.������ǰ�������������
	int id=0;
	int item=0;
	CString name(_T(""));
	_variant_t value;
	Theme *theme=Theme::instance();
	//1-3-2.����λ��Ϣ��¼���е����ݲ��뵽����λ��Ϣ���������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//1-3-2-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//1-3-2-2.��ȡ��ǰ��¼���м�¼�ĵ�λ��ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//1-3-2-3.��ȡ��ǰ��¼���еĵ�λ���ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//1-3-2-5.����ǰ��ȡ�ĵ�λ��Ϣ���뵽����λ��Ϣ���������С�
			item=_unit_combo_box->AddString(name);
			_unit_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//1-3-2-6.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//1-3-3.�򡰵�λ��Ϣ���������в��롰�ޡ���
	item=_unit_combo_box->AddString(theme->get_string(IDS_STRING393));
	_unit_combo_box->SetItemData(item,static_cast<DWORD_PTR>(0));
	//2.�����ݿ��м�������ģʽ��Ϣ�����Ҳ��뵽������ģʽ���������С�
	//2-1.����SQL��䣬׼�������ݿ��м�������ģʽ��Ϣ��
	sql.Format(_T("SELECT * FROM [data_mode] ORDER BY [id] ASC"));
	//2-2.�����ݿ��м��ص�λ��Ϣ��¼����
	records=database.get_recordset(sql);
	//2-3.������ģʽ��Ϣ��¼���е����ݲ��뵽������ģʽ���������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//2-3-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//2-3-2.��ȡ��ǰ��¼���м�¼������ģʽ��ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//2-3-3.��ȡ��ǰ��¼���е�����ģʽ���ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//2-3-4.����ǰ��ȡ������ģʽ��Ϣ���뵽������ģʽ���������С�
			item=_data_mode_combo_box->AddString(name);
			_data_mode_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//2-3-5.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//3.�����ݿ��м�������������Ϣ�����Ҳ��뵽���������͡��������С�
	//3-1.����SQL��䣬׼�������ݿ��м�������������Ϣ��
	sql.Format(_T("SELECT * FROM [specimen_type] ORDER BY [id] ASC"));
	//3-2.�����ݿ��м����������ͼ�¼����
	records=database.get_recordset(sql);
	//3-3.�������������ͼ�¼���е����ݲ��뵽���������͡��������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//3-3-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//3-3-2.��ȡ��ǰ��¼���м�¼���������ͱ�ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//3-3-3.��ȡ��ǰ��¼���е������������ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//3-3-4.���������������ơ�
			if(_T("Ser/PI")==name){
				name=theme->get_string(IDS_STRING102);
			}else if(_T("Urine")==name){
				name=theme->get_string(IDS_STRING103);
			}else if(_T("CSF")==name){
				name=theme->get_string(IDS_STRING104);
			}else if(_T("Suprnt")==name){
				name=theme->get_string(IDS_STRING105);
			}else if(_T("Other")==name){
				name=theme->get_string(IDS_STRING106);
			}
			//3-3-5.����ǰ��ȡ������������Ϣ���뵽���������͡��������С�
			item=_select_sample_type_combo_box->AddString(name);
			_select_sample_type_combo_box->SetItemData(item,
				static_cast<DWORD_PTR>(id));
			//3-3-6.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//3-4.���õ�ǰ������ѡ����������͡�
	if(_select_sample_type_combo_box->GetCount()>0){
		_select_sample_type_combo_box->SetCurSel(0);
		_sample_type_id=static_cast<int>(_select_sample_type_combo_box->GetItemData(0));
	}else{
		_select_sample_type_combo_box->SetCurSel(-1);
		_sample_type_id=0;
	}
	//4.�����ݿ��м������䵥λ��Ϣ�����Ҳ��뵽���䵥λ�������С�
	//4-1.����SQL��䣬׼�������ݿ��м������䵥λ��Ϣ��
	sql.Format(_T("SELECT * FROM [age_unit] ORDER BY [id] ASC"));
	//4-2.�����ݿ��м������䵥λ��¼����
	records=database.get_recordset(sql);
	//4-3.�������������ͼ�¼���е����ݲ��뵽���䵥λ�������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//4-3-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//4-3-2.��ȡ��ǰ��¼���м�¼�����䵥λ��ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//4-3-3.��ȡ��ǰ��¼���е����䵥λ���ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//4-3-4.�������䵥λ���ơ�
			if(_T("Days")==name){
				name=theme->get_string(IDS_STRING394);
			}else if(_T("Months")==name){
				name=theme->get_string(IDS_STRING395);
			}else if(_T("Years")==name){
				name=theme->get_string(IDS_STRING396);
			}
			//4-3-5.����ǰ��ȡ�����䵥λ��Ϣ���뵽�����䵥λ���������С�
			item=_lower_age_unit_combo_box->AddString(name);
			_lower_age_unit_combo_box->SetItemData(item,static_cast<DWORD_PTR>(id));
			item=_upper_age_unit_combo_box->AddString(name);
			_upper_age_unit_combo_box->SetItemData(item,static_cast<DWORD_PTR>(id));
			//4-3-6.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
	//5.��ʼ��Ĭ������������
	item=_default_age_combo_box->AddString(theme->get_string(IDS_STRING399));
	_default_age_combo_box->SetItemData(item,static_cast<DWORD_PTR>(1));
	item=_default_age_combo_box->AddString(theme->get_string(IDS_STRING400));
	_default_age_combo_box->SetItemData(item,static_cast<DWORD_PTR>(2));
	item=_default_age_combo_box->AddString(theme->get_string(IDS_STRING401));
	_default_age_combo_box->SetItemData(item,static_cast<DWORD_PTR>(3));
	//6.�����ݿ��м����Ա���Ϣ�����Ҳ��뵽�Ա��������С�
	//6-1.����SQL��䣬׼�������ݿ��м����Ա���Ϣ��
	sql.Format(_T("SELECT * FROM [sex] ORDER BY [id] ASC"));
	//6-2.�����ݿ��м����Ա��¼����
	records=database.get_recordset(sql);
	//6-3.���Ա��¼���е����ݲ��뵽�Ա��������С�
	if(static_cast<bool>(records)){
		while(!records->get_eof()){
			//6-3-1.��⵱ǰ��¼�������ж��Ƿ�����
			if(0!=records->get_last_error_code()){
				break;
			}
			//6-3-2.��ȡ��ǰ��¼���м�¼���Ա��ʶ��
			value=records->get_collect(MtADODataConverter::to_variant_t(0));
			if(0!=records->get_last_error_code()){
				break;
			}
			id=MtADODataConverter::to_int(value);
			//6-3-3.��ȡ��ǰ��¼���е��Ա����ơ�
			value=records->get_collect(MtADODataConverter::to_variant_t(1));
			if(0!=records->get_last_error_code()){
				break;
			}
			name=MtADODataConverter::to_string(value);
			//6-3-4.�����Ա����ơ�
			if(_T("Male")==name){
				name=theme->get_string(IDS_STRING397);
			}else if(_T("Female")==name){
				name=theme->get_string(IDS_STRING398);
			}
			//6-3-5.����ǰ��ȡ���Ա���Ϣ���뵽���Ա��������С�
			item=_default_sex_combo_box->AddString(name);
			_default_sex_combo_box->SetItemData(item,static_cast<DWORD_PTR>(id));
			//6-3-6.����ǰ��¼������һ��λ�á�
			records->move_next();
			if(0!=records->get_last_error_code()){
				break;
			}
		}
	}
}

/**
 * name: update_data_for_controls
 * brief: ��ָ����Ŀ��ʶ�����������Ϣ���µ��ؼ��ϡ�
 * param: item_id - ָ������Ŀ��ʶ��
 * return: --
 * remark: ��item_idС�ڵ�����ʱ���˺���Ĭ����ʾ������С��Ŀ��ʶ����Ŀ�����������
 */
void DialogRangeApplication::update_data_for_controls(const int item_id/*=0*/){
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
	//2.���á���Ŀ���ơ��ı��༭�����ݡ�
	if(item_count<=0){
		_item_name_edit->SetWindowText(_T(""));
		_item_name_edit->EnableWindow(FALSE);
	}else{
		_item_name_edit->SetWindowText((application->get_item()).get_alias());
		_item_name_edit->EnableWindow(TRUE);
	}
	//3.���á���Ŀ��š��ı��༭�����ݡ�
	CString text(_T(""));
	if(item_count<=0){
		_item_no_edit->SetWindowText(_T(""));
	}else{
		text.Format(_T("%d"),(application->get_item()).get_no());
		_item_no_edit->SetWindowText(text);
	}
	//4.���á���Ŀ��ʶ���ı��༭�����ݡ�
	if(item_count<=0){
		_test_id_edit->SetWindowText(_T(""));
	}else{
		text.Format(_T("%d"),(application->get_item()).get_id());
		_test_id_edit->SetWindowText(text);
	}
	//5.���á��������ơ��ı��༭��
	if(item_count<=0){
		_report_name_edit->SetWindowText(_T(""));
		_report_name_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%s"),(application->get_range()).get_report_name());
		_report_name_edit->SetWindowText(text);
		_report_name_edit->EnableWindow(TRUE);
	}
	//6.���á��ʿؼ������ѡ���ı��༭��
	if(item_count<=0){
		_control_interval_check_box->set_checked(FALSE);
		_control_interval_check_box->EnableWindow(FALSE);
		_control_interval_edit->SetWindowText(_T(""));
		_control_interval_edit->EnableWindow(FALSE);
	}else{
		if(-1==(application->get_range()).get_control_interval()){
			_control_interval_check_box->set_checked(FALSE);
			_control_interval_check_box->EnableWindow(TRUE);
			_control_interval_edit->SetWindowText(_T(""));
			_control_interval_edit->EnableWindow(FALSE);
		}else{
			_control_interval_check_box->set_checked(TRUE);
			_control_interval_check_box->EnableWindow(TRUE);
			text.Format(_T("%d"),(application->get_range()).get_control_interval());
			_control_interval_edit->SetWindowText(text);
			_control_interval_edit->EnableWindow(TRUE);
		}
	}
	//7.���á���λ��������
	if(item_count<=0){
		_unit_combo_box->SetCurSel(-1);
		_unit_combo_box->EnableWindow(FALSE);
	}else{
		_unit_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_range()).get_unit_id(),
			*_unit_combo_box));
		_unit_combo_box->EnableWindow(TRUE);
	}
	//8.���á��豸ϵ��a���ı��༭��
	if(item_count<=0){
		_instrument_factor_a_edit->SetWindowText(_T(""));
		_instrument_factor_a_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_instrument_factor_a());
		_instrument_factor_a_edit->SetWindowText(text);
		_instrument_factor_a_edit->EnableWindow(TRUE);
	}
	//9.���á��豸ϵ��b���ı��༭��
	if(item_count<=0){
		_instrument_factor_b_edit->SetWindowText(_T(""));
		_instrument_factor_b_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_instrument_factor_b());
		_instrument_factor_b_edit->SetWindowText(text);
		_instrument_factor_b_edit->EnableWindow(TRUE);
	}
	//10.���á�����ģʽ��������
	if(item_count<=0){
		_data_mode_combo_box->SetCurSel(-1);
		_data_mode_combo_box->EnableWindow(FALSE);
	}else{
		_data_mode_combo_box->SetCurSel(
			get_combo_box_index_by_item_data<int>((
			application->get_range()).get_data_mode_id(),
			*_data_mode_combo_box));
		_data_mode_combo_box->EnableWindow(FALSE);
	}
	//11.���õ�ǰ��������������
	if(item_count<=0){
		_sample_type_id=0;
		_select_sample_type_combo_box->SetCurSel(-1);
		_select_sample_type_combo_box->EnableWindow(FALSE);
	}else{
		if(_select_sample_type_combo_box->GetCount()>0){
			if(_select_sample_type_combo_box->GetCurSel()<0){
				_select_sample_type_combo_box->SetCurSel(0);
				_sample_type_id=static_cast<int>(
					_select_sample_type_combo_box->GetItemData(0));
			}else{
				_sample_type_id=static_cast<int>(_select_sample_type_combo_box->
					GetItemData(_select_sample_type_combo_box->GetCurSel()));
			}
		}else{
			_sample_type_id=0;
			_select_sample_type_combo_box->SetCurSel(-1);
			_select_sample_type_combo_box->EnableWindow(FALSE);
		}
		_select_sample_type_combo_box->EnableWindow(TRUE);
	}
	//12.��ȡ��ǰ�û�ѡ��ġ��������͡���
	//12-1.��ȡ��ǰ�û�ѡ��ġ��������͡���
	item=_select_sample_type_combo_box->GetCurSel();
	//12-2.�����ȡ��ǰ�û�ѡ��ġ��������͡�ʧ�ܡ�
	if(item<0){
		_lower_age_edit->SetWindowText(_T(""));
		_lower_age_edit->EnableWindow(FALSE);
		_upper_age_edit->SetWindowText(_T(""));
		_upper_age_edit->EnableWindow(FALSE);
		_lower_age_unit_combo_box->SetCurSel(-1);
		_lower_age_unit_combo_box->EnableWindow(FALSE);
		_upper_age_unit_combo_box->SetCurSel(-1);
		_upper_age_unit_combo_box->EnableWindow(FALSE);
		_1_lower_limit_for_male_edit->SetWindowText(_T(""));
		_1_lower_limit_for_male_edit->EnableWindow(FALSE);
		_1_upper_limit_for_male_edit->SetWindowText(_T(""));
		_1_upper_limit_for_male_edit->EnableWindow(FALSE);
		_2_lower_limit_for_male_edit->SetWindowText(_T(""));
		_2_lower_limit_for_male_edit->EnableWindow(FALSE);
		_2_upper_limit_for_male_edit->SetWindowText(_T(""));
		_2_upper_limit_for_male_edit->EnableWindow(FALSE);
		_3_lower_limit_for_male_edit->SetWindowText(_T(""));
		_3_lower_limit_for_male_edit->EnableWindow(FALSE);
		_3_upper_limit_for_male_edit->SetWindowText(_T(""));
		_3_upper_limit_for_male_edit->EnableWindow(FALSE);
		_1_lower_limit_for_female_edit->SetWindowText(_T(""));
		_1_lower_limit_for_female_edit->EnableWindow(FALSE);
		_1_upper_limit_for_female_edit->SetWindowText(_T(""));
		_1_upper_limit_for_female_edit->EnableWindow(FALSE);
		_2_lower_limit_for_female_edit->SetWindowText(_T(""));
		_2_lower_limit_for_female_edit->EnableWindow(FALSE);
		_2_upper_limit_for_female_edit->SetWindowText(_T(""));
		_2_upper_limit_for_female_edit->EnableWindow(FALSE);
		_3_lower_limit_for_female_edit->SetWindowText(_T(""));
		_3_lower_limit_for_female_edit->EnableWindow(FALSE);
		_3_upper_limit_for_female_edit->SetWindowText(_T(""));
		_3_upper_limit_for_female_edit->EnableWindow(FALSE);
		_default_age_combo_box->SetCurSel(-1);
		_default_age_combo_box->EnableWindow(FALSE);
		_default_sex_combo_box->SetCurSel(-1);
		_default_sex_combo_box->EnableWindow(FALSE);
		_lower_repeat_range_limit_edit->SetWindowText(_T(""));
		_lower_repeat_range_limit_edit->EnableWindow(FALSE);
		_upper_repeat_range_limit_edit->SetWindowText(_T(""));
		_upper_repeat_range_limit_edit->EnableWindow(FALSE);
		_use_qualitative_table_check_box->set_checked(FALSE);
		_use_qualitative_table_check_box->EnableWindow(FALSE);
		_qualitative_limit_1_edit->SetWindowText(_T(""));
		_qualitative_limit_1_edit->EnableWindow(FALSE);
		_qualitative_limit_text_1_edit->SetWindowText(_T(""));
		_qualitative_limit_text_1_edit->EnableWindow(FALSE);
		_qualitative_limit_2_edit->SetWindowText(_T(""));
		_qualitative_limit_2_edit->EnableWindow(FALSE);
		_qualitative_limit_text_2_edit->SetWindowText(_T(""));
		_qualitative_limit_text_2_edit->EnableWindow(FALSE);
		_qualitative_limit_3_edit->SetWindowText(_T(""));
		_qualitative_limit_3_edit->EnableWindow(FALSE);
		_qualitative_limit_text_3_edit->SetWindowText(_T(""));
		_qualitative_limit_text_3_edit->EnableWindow(FALSE);
		_qualitative_limit_4_edit->SetWindowText(_T(""));
		_qualitative_limit_4_edit->EnableWindow(FALSE);
		_qualitative_limit_text_4_edit->SetWindowText(_T(""));
		_qualitative_limit_text_4_edit->EnableWindow(FALSE);
		_qualitative_limit_5_edit->SetWindowText(_T(""));
		_qualitative_limit_5_edit->EnableWindow(FALSE);
		_qualitative_limit_text_5_edit->SetWindowText(_T(""));
		_qualitative_limit_text_5_edit->EnableWindow(FALSE);
		_qualitative_limit_text_6_edit->EnableWindow(FALSE);
	}
	//12-3.�����ȡ��ǰ�û�ѡ��ġ��������͡��ɹ���
	else{
		//12-3-1.��ȡ��ǰ�û�ѡ����������ͱ�ʶ��
		const int id=static_cast<int>(
			_select_sample_type_combo_box->GetItemData(item));
		//12-3-2.�������������ı��༭��
		if(item_count<=0){
			_lower_age_edit->SetWindowText(_T(""));
			_lower_age_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%d"),(application->get_range()).get_lower_age_limit(id-1));
			_lower_age_edit->SetWindowText(text);
			_lower_age_edit->EnableWindow(TRUE);
		}
		//12-3-3.�������������ı��༭��
		if(item_count<=0){
			_upper_age_edit->SetWindowText(_T(""));
			_upper_age_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%d"),(application->get_range()).get_upper_age_limit(id-1));
			_upper_age_edit->SetWindowText(text);
			_upper_age_edit->EnableWindow(TRUE);
		}
		//12-3-4.�����������޵�λ������
		if(item_count<=0){
			_lower_age_unit_combo_box->SetCurSel(-1);
			_lower_age_unit_combo_box->EnableWindow(FALSE);
		}else{
			_lower_age_unit_combo_box->SetCurSel(
				get_combo_box_index_by_item_data<int>((
				application->get_range()).get_lower_age_unit_id(id-1),
				*_lower_age_unit_combo_box));
			_lower_age_unit_combo_box->EnableWindow(TRUE);
		}
		//12-3-5.�����������޵�λ������
		if(item_count<=0){
			_upper_age_unit_combo_box->SetCurSel(-1);
			_upper_age_unit_combo_box->EnableWindow(FALSE);
		}else{
			_upper_age_unit_combo_box->SetCurSel(
				get_combo_box_index_by_item_data<int>((
				application->get_range()).get_upper_age_unit_id(id-1),
				*_upper_age_unit_combo_box));
			_upper_age_unit_combo_box->EnableWindow(TRUE);
		}
		//12-3-6.��������������Χ1�������ı��༭��
		if(item_count<=0){
			_1_lower_limit_for_male_edit->SetWindowText(_T(""));
			_1_lower_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_males_1(id-1));
			_1_lower_limit_for_male_edit->SetWindowText(text);
			_1_lower_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-7.��������������Χ1�������ı��༭��
		if(item_count<=0){
			_1_upper_limit_for_male_edit->SetWindowText(_T(""));
			_1_upper_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_males_1(id-1));
			_1_upper_limit_for_male_edit->SetWindowText(text);
			_1_upper_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-8.��������������Χ2�������ı��༭��
		if(item_count<=0){
			_2_lower_limit_for_male_edit->SetWindowText(_T(""));
			_2_lower_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_males_2(id-1));
			_2_lower_limit_for_male_edit->SetWindowText(text);
			_2_lower_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-9.��������������Χ2�������ı��༭��
		if(item_count<=0){
			_2_upper_limit_for_male_edit->SetWindowText(_T(""));
			_2_upper_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_males_2(id-1));
			_2_upper_limit_for_male_edit->SetWindowText(text);
			_2_upper_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-10.��������������Χ3�������ı��༭��
		if(item_count<=0){
			_3_lower_limit_for_male_edit->SetWindowText(_T(""));
			_3_lower_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_males_3(id-1));
			_3_lower_limit_for_male_edit->SetWindowText(text);
			_3_lower_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-11.��������������Χ3�������ı��༭��
		if(item_count<=0){
			_3_upper_limit_for_male_edit->SetWindowText(_T(""));
			_3_upper_limit_for_male_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_males_3(id-1));
			_3_upper_limit_for_male_edit->SetWindowText(text);
			_3_upper_limit_for_male_edit->EnableWindow(TRUE);
		}
		//12-3-12.����Ů��������Χ1�������ı��༭��
		if(item_count<=0){
			_1_lower_limit_for_female_edit->SetWindowText(_T(""));
			_1_lower_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_females_1(id-1));
			_1_lower_limit_for_female_edit->SetWindowText(text);
			_1_lower_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-13.����Ů��������Χ1�������ı��༭��
		if(item_count<=0){
			_1_upper_limit_for_female_edit->SetWindowText(_T(""));
			_1_upper_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_females_1(id-1));
			_1_upper_limit_for_female_edit->SetWindowText(text);
			_1_upper_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-14.����Ů��������Χ2�������ı��༭��
		if(item_count<=0){
			_2_lower_limit_for_female_edit->SetWindowText(_T(""));
			_2_lower_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_females_2(id-1));
			_2_lower_limit_for_female_edit->SetWindowText(text);
			_2_lower_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-15.����Ů��������Χ2�������ı��༭��
		if(item_count<=0){
			_2_upper_limit_for_female_edit->SetWindowText(_T(""));
			_2_upper_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_females_2(id-1));
			_2_upper_limit_for_female_edit->SetWindowText(text);
			_2_upper_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-16.����Ů��������Χ3�������ı��༭��
		if(item_count<=0){
			_3_lower_limit_for_female_edit->SetWindowText(_T(""));
			_3_lower_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_of_normal_for_females_3(id-1));
			_3_lower_limit_for_female_edit->SetWindowText(text);
			_3_lower_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-17.����Ů��������Χ3�������ı��༭��
		if(item_count<=0){
			_3_upper_limit_for_female_edit->SetWindowText(_T(""));
			_3_upper_limit_for_female_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_of_normal_for_females_3(id-1));
			_3_upper_limit_for_female_edit->SetWindowText(text);
			_3_upper_limit_for_female_edit->EnableWindow(TRUE);
		}
		//12-3-18.����Ĭ������������
		if(item_count<=0){
			_default_age_combo_box->SetCurSel(-1);
			_default_age_combo_box->EnableWindow(FALSE);
		}else{
			_default_age_combo_box->SetCurSel(
				get_combo_box_index_by_item_data<int>((
				application->get_range()).get_default_age(id-1),
				*_default_age_combo_box));
			_default_age_combo_box->EnableWindow(TRUE);
		}
		//12-3-19.����Ĭ���Ա�������
		if(item_count<=0){
			_default_sex_combo_box->SetCurSel(-1);
			_default_sex_combo_box->EnableWindow(FALSE);
		}else{
			_default_sex_combo_box->SetCurSel(
				get_combo_box_index_by_item_data<int>((
				application->get_range()).get_default_sex(id-1),
				*_default_sex_combo_box));
			_default_sex_combo_box->EnableWindow(TRUE);
		}
		//12-3-20.���ó��渴�������ı��༭��
		if(item_count<=0){
			_lower_repeat_range_limit_edit->SetWindowText(_T(""));
			_lower_repeat_range_limit_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_lower_limit_for_repeat_range(id-1));
			_lower_repeat_range_limit_edit->SetWindowText(text);
			_lower_repeat_range_limit_edit->EnableWindow(TRUE);
		}
		//12-3-21.���ó��渴�������ı��༭��
		if(item_count<=0){
			_upper_repeat_range_limit_edit->SetWindowText(_T(""));
			_upper_repeat_range_limit_edit->EnableWindow(FALSE);
		}else{
			text.Format(_T("%.3lf"),(application->get_range()).
				get_upper_limit_for_repeat_range(id-1));
			_upper_repeat_range_limit_edit->SetWindowText(text);
			_upper_repeat_range_limit_edit->EnableWindow(TRUE);
		}
		//12-3-22.�����Ƿ����ö��Ա�ѡ��
		int is_use_qualitative_table=0;
		if(item_count<=0){
			is_use_qualitative_table=0;
			_use_qualitative_table_check_box->set_checked(FALSE);
			_use_qualitative_table_check_box->EnableWindow(FALSE);
		}else{
			is_use_qualitative_table=(application->get_range()).
				get_is_use_qualitative_table(id-1);
			if(1==is_use_qualitative_table){
				_use_qualitative_table_check_box->set_checked(TRUE);
				_use_qualitative_table_check_box->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_use_qualitative_table_check_box->set_checked(FALSE);
				_use_qualitative_table_check_box->EnableWindow(TRUE);
			}else{
				_use_qualitative_table_check_box->set_checked(FALSE);
				_use_qualitative_table_check_box->EnableWindow(FALSE);
			}
		}
		//12-3-23.���ö��Խ���1�ı��༭��
		if(item_count<=0){
			_qualitative_limit_1_edit->SetWindowText(_T(""));
			_qualitative_limit_1_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				text.Format(_T("%.3lf"),(application->get_range()).
					get_qualitative_limit_1(id-1));
				_qualitative_limit_1_edit->SetWindowText(text);
				_qualitative_limit_1_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_1_edit->SetWindowText(_T(""));
				_qualitative_limit_1_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_1_edit->SetWindowText(_T(""));
				_qualitative_limit_1_edit->EnableWindow(FALSE);
			}
		}
		//12-3-23.���ö��Խ����ı�1�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_1_edit->SetWindowText(_T(""));
			_qualitative_limit_text_1_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_1_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_1(id-1));
				_qualitative_limit_text_1_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_1_edit->SetWindowText(_T(""));
				_qualitative_limit_text_1_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_1_edit->SetWindowText(_T(""));
				_qualitative_limit_text_1_edit->EnableWindow(FALSE);
			}
		}
		//12-3-24.���ö��Խ���2�ı��༭��
		if(item_count<=0){
			_qualitative_limit_2_edit->SetWindowText(_T(""));
			_qualitative_limit_2_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				text.Format(_T("%.3lf"),(application->get_range()).
					get_qualitative_limit_2(id-1));
				_qualitative_limit_2_edit->SetWindowText(text);
				_qualitative_limit_2_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_2_edit->SetWindowText(_T(""));
				_qualitative_limit_2_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_2_edit->SetWindowText(_T(""));
				_qualitative_limit_2_edit->EnableWindow(FALSE);
			}
		}
		//12-3-25.���ö��Խ����ı�2�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_2_edit->SetWindowText(_T(""));
			_qualitative_limit_text_2_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_2_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_2(id-1));
				_qualitative_limit_text_2_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_2_edit->SetWindowText(_T(""));
				_qualitative_limit_text_2_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_2_edit->SetWindowText(_T(""));
				_qualitative_limit_text_2_edit->EnableWindow(FALSE);
			}
		}
		//12-3-26.���ö��Խ���3�ı��༭��
		if(item_count<=0){
			_qualitative_limit_3_edit->SetWindowText(_T(""));
			_qualitative_limit_3_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				text.Format(_T("%.3lf"),(application->get_range()).
					get_qualitative_limit_3(id-1));
				_qualitative_limit_3_edit->SetWindowText(text);
				_qualitative_limit_3_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_3_edit->SetWindowText(_T(""));
				_qualitative_limit_3_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_3_edit->SetWindowText(_T(""));
				_qualitative_limit_3_edit->EnableWindow(FALSE);
			}
		}
		//12-3-27.���ö��Խ����ı�3�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_3_edit->SetWindowText(_T(""));
			_qualitative_limit_text_3_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_3_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_3(id-1));
				_qualitative_limit_text_3_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_3_edit->SetWindowText(_T(""));
				_qualitative_limit_text_3_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_3_edit->SetWindowText(_T(""));
				_qualitative_limit_text_3_edit->EnableWindow(FALSE);
			}
		}
		//12-3-28.���ö��Խ���4�ı��༭��
		if(item_count<=0){
			_qualitative_limit_4_edit->SetWindowText(_T(""));
			_qualitative_limit_4_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				text.Format(_T("%.3lf"),(application->get_range()).
					get_qualitative_limit_4(id-1));
				_qualitative_limit_4_edit->SetWindowText(text);
				_qualitative_limit_4_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_4_edit->SetWindowText(_T(""));
				_qualitative_limit_4_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_4_edit->SetWindowText(_T(""));
				_qualitative_limit_4_edit->EnableWindow(FALSE);
			}
		}
		//12-3-29.���ö��Խ����ı�4�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_4_edit->SetWindowText(_T(""));
			_qualitative_limit_text_4_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_4_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_4(id-1));
				_qualitative_limit_text_4_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_4_edit->SetWindowText(_T(""));
				_qualitative_limit_text_4_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_4_edit->SetWindowText(_T(""));
				_qualitative_limit_text_4_edit->EnableWindow(FALSE);
			}
		}
		//12-3-30.���ö��Խ���5�ı��༭��
		if(item_count<=0){
			_qualitative_limit_5_edit->SetWindowText(_T(""));
			_qualitative_limit_5_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				text.Format(_T("%.3lf"),(application->get_range()).
					get_qualitative_limit_5(id-1));
				_qualitative_limit_5_edit->SetWindowText(text);
				_qualitative_limit_5_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_5_edit->SetWindowText(_T(""));
				_qualitative_limit_5_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_5_edit->SetWindowText(_T(""));
				_qualitative_limit_5_edit->EnableWindow(FALSE);
			}
		}
		//12-3-31.���ö��Խ����ı�5�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_5_edit->SetWindowText(_T(""));
			_qualitative_limit_text_5_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_5_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_5(id-1));
				_qualitative_limit_text_5_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_5_edit->SetWindowText(_T(""));
				_qualitative_limit_text_5_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_5_edit->SetWindowText(_T(""));
				_qualitative_limit_text_5_edit->EnableWindow(FALSE);
			}
		}
		//12-3-32.���ö��Խ����ı�6�ı��༭��
		if(item_count<=0){
			_qualitative_limit_text_6_edit->SetWindowText(_T(""));
			_qualitative_limit_text_6_edit->EnableWindow(FALSE);
		}else{
			if(1==is_use_qualitative_table){
				_qualitative_limit_text_6_edit->SetWindowText((
					application->get_range()).
					get_qualitative_limit_text_6(id-1));
				_qualitative_limit_text_6_edit->EnableWindow(TRUE);
			}else if(0==is_use_qualitative_table){
				_qualitative_limit_text_6_edit->SetWindowText(_T(""));
				_qualitative_limit_text_6_edit->EnableWindow(FALSE);
			}else{
				_qualitative_limit_text_6_edit->SetWindowText(_T(""));
				_qualitative_limit_text_6_edit->EnableWindow(FALSE);
			}
		}
	}
	//13.������������Ϊ����1�����������鷶Χ�����ı��༭��
	if(item_count<=0){
		_technical_range_lower_limit_for_class_1_edit->SetWindowText(_T(""));
		_technical_range_lower_limit_for_class_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_lower_limit_for_technical_range_for_class_1());
		_technical_range_lower_limit_for_class_1_edit->SetWindowText(text);
		_technical_range_lower_limit_for_class_1_edit->EnableWindow(TRUE);
	}
	//14.������������Ϊ����1�����������鷶Χ�����ı��༭��
	if(item_count<=0){
		_technical_range_upper_limit_for_class_1_edit->SetWindowText(_T(""));
		_technical_range_upper_limit_for_class_1_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_upper_limit_for_technical_range_for_class_1());
		_technical_range_upper_limit_for_class_1_edit->SetWindowText(text);
		_technical_range_upper_limit_for_class_1_edit->EnableWindow(TRUE);
	}
	//15.������������Ϊ����2�����������鷶Χ�����ı��༭��
	if(item_count<=0){
		_technical_range_lower_limit_for_class_2_edit->SetWindowText(_T(""));
		_technical_range_lower_limit_for_class_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_lower_limit_for_technical_range_for_class_2());
		_technical_range_lower_limit_for_class_2_edit->SetWindowText(text);
		_technical_range_lower_limit_for_class_2_edit->EnableWindow(TRUE);
	}
	//16.������������Ϊ����2�����������鷶Χ�����ı��༭��
	if(item_count<=0){
		_technical_range_upper_limit_for_class_2_edit->SetWindowText(_T(""));
		_technical_range_upper_limit_for_class_2_edit->EnableWindow(FALSE);
	}else{
		text.Format(_T("%.3lf"),(application->get_range()).
			get_upper_limit_for_technical_range_for_class_2());
		_technical_range_upper_limit_for_class_2_edit->SetWindowText(text);
		_technical_range_upper_limit_for_class_2_edit->EnableWindow(TRUE);
	}
	//17.����ɾ����ť��
	if(item_count<=0){
		_delete_button->EnableWindow(FALSE);
	}else{
		_delete_button->EnableWindow(TRUE);
	}
	//18.����ȷ����ť��
	_ok_button->EnableWindow(FALSE);
}

/**
 * name: is_data_of_controls_changed
 * brief: �жϵ�ǰ�ؼ��е������Ƿ����ı䡣
 * param: --
 * return: �����ǰ�ؼ��е����ݷ����ı��򷵻�TRUE�����򷵻�FALSE��
 */
BOOL DialogRangeApplication::is_data_of_controls_changed() const{
	//1.��ȡ��ǰ������ָ����Ŀ��ʶ�����������Ϣ��
	Applications::PtrToCApp application=Applications::
		instance()->get_by_item_id(_item_id);
	if(!static_cast<bool>(application)){//���δ�ܻ�ȡָ��������Ϣ������Ϊ�ޱ仯��
		return(FALSE);
	}
	//2.��⵱ǰ����Ŀ���ơ��ı��༭���Ƿ����仯��
	CString text(_T(""));
	_item_name_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if((application->get_item()).get_alias()!=text){
		return(TRUE);
	}
	//3.��⵱ǰ���������ơ��ı��༭���Ƿ����仯��
	_report_name_edit->GetWindowText(text);
	/*
	if(_T("")==text){
		return(TRUE);
	}
	*/
	if((application->get_range()).get_report_name()!=text){
		return(TRUE);
	}
	//4.����ʿؼ����ѡ���ı��༭���Ƿ����仯��
	if(_control_interval_check_box->get_checked()){
		_control_interval_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_range()).get_control_interval()!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
	}else{
		if(-1!=(application->get_range()).get_control_interval()){
			return(TRUE);
		}
	}
	//5.��ⵥλ�������Ƿ����仯��
	int item=_unit_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	int value=static_cast<int>(_unit_combo_box->GetItemData(item));
	if((application->get_range()).get_unit_id()!=value){
		return(TRUE);
	}
	//6.����豸ϵ��a�ı��༭���Ƿ����仯��
	_instrument_factor_a_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_instrument_factor_a()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//7.����豸ϵ��b�ı��༭���Ƿ����仯��
	_instrument_factor_b_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_instrument_factor_b()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//8.�������ģʽ�������Ƿ����仯��
	item=_data_mode_combo_box->GetCurSel();
	if(item<0){
		return(TRUE);
	}
	value=static_cast<int>(_data_mode_combo_box->GetItemData(item));
	if((application->get_range()).get_data_mode_id()!=value){
		return(TRUE);
	}
	//9.���ݵ�ǰѡ����������ͣ��������ķ�Χ��Ϣ�Ƿ����仯��
	//9-1.��ȡ��ǰ�û�ѡ����������͡�
	item=_select_sample_type_combo_box->GetCurSel();
	//9-2.����û�ѡ�����쳣���������͡�
	if(item<0){
		return(TRUE);
	}
	//9-3.����û�ѡ���˺Ϸ����������͡�
	else{
		//9-3-1.��ȡ��ǰ�������ͱ�ʶ��
		const int id=static_cast<int>(
			_select_sample_type_combo_box->GetItemData(item));
		//9-3-2.������������Ƿ����ı䡣
		_lower_age_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_range()).get_lower_age_limit(id-1)!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
		//9-3-3.������������Ƿ����ı䡣
		_upper_age_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if((application->get_range()).get_upper_age_limit(id-1)!=
			MtCharacterSet::to_integer(text)){
			return(TRUE);
		}
		//9-3-4.����������޵�λ�������Ƿ����仯��
		item=_lower_age_unit_combo_box->GetCurSel();
		if(item<0){
			return(TRUE);
		}
		value=static_cast<int>(_lower_age_unit_combo_box->GetItemData(item));
		if((application->get_range()).get_lower_age_unit_id(id-1)!=value){
			return(TRUE);
		}
		//9-3-5.����������޵�λ�������Ƿ����仯��
		item=_upper_age_unit_combo_box->GetCurSel();
		if(item<0){
			return(TRUE);
		}
		value=static_cast<int>(_upper_age_unit_combo_box->GetItemData(item));
		if((application->get_range()).get_upper_age_unit_id(id-1)!=value){
			return(TRUE);
		}
		//9-3-6.�������������Χ1�����ı��༭���Ƿ����仯��
		_1_lower_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_males_1(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-7.�������������Χ1�����ı��༭���Ƿ����仯��
		_1_upper_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_males_1(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-8.�������������Χ2�����ı��༭���Ƿ����仯��
		_2_lower_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_males_2(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-9.�������������Χ2�����ı��༭���Ƿ����仯��
		_2_upper_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_males_2(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-10.�������������Χ3�����ı��༭���Ƿ����仯��
		_3_lower_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_males_3(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-11.�������������Χ3�����ı��༭���Ƿ����仯��
		_3_upper_limit_for_male_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_males_3(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-12.���Ů��������Χ1�����ı��༭���Ƿ����仯��
		_1_lower_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_females_1(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-13.���Ů��������Χ1�����ı��༭���Ƿ����仯��
		_1_upper_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_females_1(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-14.���Ů��������Χ2�����ı��༭���Ƿ����仯��
		_2_lower_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_females_2(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-15.���Ů��������Χ2�����ı��༭���Ƿ����仯��
		_2_upper_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_females_2(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-16.���Ů��������Χ3�����ı��༭���Ƿ����仯��
		_3_lower_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_of_normal_for_females_3(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-17.���Ů��������Χ3�����ı��༭���Ƿ����仯��
		_3_upper_limit_for_female_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_of_normal_for_females_3(
			id-1)-MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-18.���Ĭ�������������Ƿ����仯��
		item=_default_age_combo_box->GetCurSel();
		if(item<0){
			return(TRUE);
		}
		value=static_cast<int>(_default_age_combo_box->GetItemData(item));
		if((application->get_range()).get_default_age(id-1)!=value){
			return(TRUE);
		}
		//9-3-19.���Ĭ���Ա��������Ƿ����仯��
		item=_default_sex_combo_box->GetCurSel();
		if(item<0){
			return(TRUE);
		}
		value=static_cast<int>(_default_sex_combo_box->GetItemData(item));
		if((application->get_range()).get_default_sex(id-1)!=value){
			return(TRUE);
		}
		//9-3-20.��ⳣ�渴�鷶Χ�����ı��༭���Ƿ����仯��
		_lower_repeat_range_limit_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_lower_limit_for_repeat_range(id-1)-
			MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-21.��ⳣ�渴�鷶Χ�����ı��༭���Ƿ����仯��
		_upper_repeat_range_limit_edit->GetWindowText(text);
		if(_T("")==text){
			return(TRUE);
		}
		if(!is_zero((application->get_range()).get_upper_limit_for_repeat_range(id-1)-
			MtCharacterSet::to_decimals(text))){
			return(TRUE);
		}
		//9-3-22.����Ƿ����ö��Ա�ѡ���Ƿ����仯��
		const BOOL is_use_qualitative_table=
			_use_qualitative_table_check_box->get_checked();
		if(is_use_qualitative_table){
		}else{
			if(0!=(application->get_range()).get_is_use_qualitative_table(id-1)){
				return(TRUE);
			}
		}
		//9-3-23.��ⶨ�Խ���1�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_1_edit->GetWindowText(text);
			if(_T("")==text){
				return(TRUE);
			}
			if(!is_zero((application->get_range()).get_qualitative_limit_1(id-1)-
				MtCharacterSet::to_decimals(text))){
				return(TRUE);
			}
		}
		//9-3-24.��ⶨ�Խ����ı�1�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_1_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_1(id-1)!=text){
				return(TRUE);
			}
		}
		//9-3-25.��ⶨ�Խ���2�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_2_edit->GetWindowText(text);
			if(_T("")==text){
				return(TRUE);
			}
			if(!is_zero((application->get_range()).get_qualitative_limit_2(id-1)-
				MtCharacterSet::to_decimals(text))){
				return(TRUE);
			}
		}
		//9-3-26.��ⶨ�Խ����ı�2�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_2_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_2(id-1)!=text){
				return(TRUE);
			}
		}
		//9-3-27.��ⶨ�Խ���3�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_3_edit->GetWindowText(text);
			if(_T("")==text){
				return(TRUE);
			}
			if(!is_zero((application->get_range()).get_qualitative_limit_3(id-1)-
				MtCharacterSet::to_decimals(text))){
				return(TRUE);
			}
		}
		//9-3-28.��ⶨ�Խ����ı�3�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_3_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_3(id-1)!=text){
				return(TRUE);
			}
		}
		//9-3-29.��ⶨ�Խ���4�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_4_edit->GetWindowText(text);
			if(_T("")==text){
				return(TRUE);
			}
			if(!is_zero((application->get_range()).get_qualitative_limit_4(id-1)-
				MtCharacterSet::to_decimals(text))){
				return(TRUE);
			}
		}
		//9-3-30.��ⶨ�Խ����ı�4�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_4_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_4(id-1)!=text){
				return(TRUE);
			}
		}
		//9-3-31.��ⶨ�Խ���5�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_5_edit->GetWindowText(text);
			if(_T("")==text){
				return(TRUE);
			}
			if(!is_zero((application->get_range()).get_qualitative_limit_5(id-1)-
				MtCharacterSet::to_decimals(text))){
				return(TRUE);
			}
		}
		//9-3-32.��ⶨ�Խ����ı�5�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_5_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_5(id-1)!=text){
				return(TRUE);
			}
		}
		//9-3-33.��ⶨ�Խ����ı�6�ı��༭���Ƿ����仯��
		if(is_use_qualitative_table){
			_qualitative_limit_text_6_edit->GetWindowText(text);
			if((application->get_range()).
				get_qualitative_limit_text_6(id-1)!=text){
				return(TRUE);
			}
		}
	}
	//10.�����������Ϊ����1�����������鷶Χ�����ı��༭���Ƿ����仯��
	_technical_range_lower_limit_for_class_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_lower_limit_for_technical_range_for_class_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//11.�����������Ϊ����1�����������鷶Χ�����ı��༭���Ƿ����仯��
	_technical_range_upper_limit_for_class_1_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_upper_limit_for_technical_range_for_class_1()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//12.�����������Ϊ����2�����������鷶Χ�����ı��༭���Ƿ����仯��
	_technical_range_lower_limit_for_class_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_lower_limit_for_technical_range_for_class_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//13.�����������Ϊ����2�����������鷶Χ�����ı��༭���Ƿ����仯��
	_technical_range_upper_limit_for_class_2_edit->GetWindowText(text);
	if(_T("")==text){
		return(TRUE);
	}
	if(!is_zero((application->get_range()).get_upper_limit_for_technical_range_for_class_2()-
		MtCharacterSet::to_decimals(text))){
		return(TRUE);
	}
	//14.�������е���ֱ�ӷ���FALSE��
	return(FALSE);
}

/**
 * name: get_data_from_controls
 * brief: ��ȡ�ؼ��е����ݡ�
 * param: item_id - ���ص���Ŀ��ʶ��
 *        item_alias - ���ص���Ŀ������
 *        range - ���صķ�Χ���������
 * return: �����ǰ����ִ�гɹ�������ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogRangeApplication::get_data_from_controls(
	int &item_id,CString &item_alias,RangeApplication &range){
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
	//3.��ȡ��ǰ�������Ŀ������
	_item_name_edit->GetWindowText(item_alias);
	if(_T("")==item_alias){
		WarningMessageBox(theme->get_string(IDS_STRING402),this);
		_item_name_edit->SetFocus();
		return(-2);
	}
	//4.��ȡ��ǰ����ı������ơ�
	CString text(_T(""));
	_report_name_edit->GetWindowText(text);
	range.set_report_name(text);
	//5.��ȡ��ǰ�ʿؼ����
	if(_control_interval_check_box->get_checked()){
		_control_interval_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING403),this);
			_control_interval_edit->SetFocus();
			return(-3);
		}
		range.set_control_interval(MtCharacterSet::to_integer(text));
	}else{
		range.set_control_interval(-1);
	}
	//6.��ȡ��ǰ���뵥λ��
	item=_unit_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING404),this);
		_unit_combo_box->SetFocus();
		return(-4);
	}
	int value=static_cast<int>(_unit_combo_box->GetItemData(item));
	range.set_unit_id(value);
	//7.��ȡ��ǰ�����豸ϵ��a��
	_instrument_factor_a_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING405),this);
		_instrument_factor_a_edit->SetFocus();
		return(-5);
	}
	range.set_instrument_factor_a(MtCharacterSet::to_decimals(text));
	//8.��ȡ��ǰ�����豸ϵ��b��
	_instrument_factor_b_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING406),this);
		_instrument_factor_b_edit->SetFocus();
		return(-6);
	}
	range.set_instrument_factor_b(MtCharacterSet::to_decimals(text));
	//9.��ȡ��ǰ����ģʽ��
	item=_data_mode_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING407),this);
		_data_mode_combo_box->SetFocus();
		return(-7);
	}
	value=static_cast<int>(_data_mode_combo_box->GetItemData(item));
	range.set_data_mode_id(value);
	//10.��ȡ��ǰ�������͡�
	item=_select_sample_type_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING408),this);
		_select_sample_type_combo_box->SetFocus();
		return(-8);
	}
	const int id=static_cast<int>(_select_sample_type_combo_box->GetItemData(item));
	//11.��ȡ��ǰ�������ޡ�
	_lower_age_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING409),this);
		_lower_age_edit->SetFocus();
		return(-9);
	}
	range.set_lower_age_limit(id-1,MtCharacterSet::to_integer(text));
	//12.��ȡ��ǰ�������ޡ�
	_upper_age_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING410),this);
		_upper_age_edit->SetFocus();
		return(-10);
	}
	range.set_upper_age_limit(id-1,MtCharacterSet::to_integer(text));
	//13.��ȡ��ǰ�������޵�λ��
	item=_lower_age_unit_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING411),this);
		_lower_age_unit_combo_box->SetFocus();
		return(-11);
	}
	value=static_cast<int>(_lower_age_unit_combo_box->GetItemData(item));
	range.set_lower_age_unit_id(id-1,value);
	//14.��ȡ��ǰ�������޵�λ��
	item=_upper_age_unit_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING412),this);
		_upper_age_unit_combo_box->SetFocus();
		return(-12);
	}
	value=static_cast<int>(_upper_age_unit_combo_box->GetItemData(item));
	range.set_upper_age_unit_id(id-1,value);
	//15.��ȡ��ǰ����������Χ1�����ޡ�
	_1_lower_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING413),this);
		_1_lower_limit_for_male_edit->SetFocus();
		return(-13);
	}
	range.set_lower_limit_of_normal_for_males_1(id-1,
		MtCharacterSet::to_decimals(text));
	//16.��ȡ��ǰ����������Χ1�����ޡ�
	_1_upper_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING414),this);
		_1_upper_limit_for_male_edit->SetFocus();
		return(-14);
	}
	range.set_upper_limit_of_normal_for_males_1(id-1,
		MtCharacterSet::to_decimals(text));
	//17.��ȡ��ǰ����������Χ2�����ޡ�
	_2_lower_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING413),this);
		_2_lower_limit_for_male_edit->SetFocus();
		return(-15);
	}
	range.set_lower_limit_of_normal_for_males_2(id-1,
		MtCharacterSet::to_decimals(text));
	//18.��ȡ��ǰ����������Χ2�����ޡ�
	_2_upper_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING414),this);
		_2_upper_limit_for_male_edit->SetFocus();
		return(-16);
	}
	range.set_upper_limit_of_normal_for_males_2(id-1,
		MtCharacterSet::to_decimals(text));
	//19.��ȡ��ǰ����������Χ3�����ޡ�
	_3_lower_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING413),this);
		_3_lower_limit_for_male_edit->SetFocus();
		return(-17);
	}
	range.set_lower_limit_of_normal_for_males_3(id-1,
		MtCharacterSet::to_decimals(text));
	//20.��ȡ��ǰ����������Χ3�����ޡ�
	_3_upper_limit_for_male_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING414),this);
		_3_upper_limit_for_male_edit->SetFocus();
		return(-18);
	}
	range.set_upper_limit_of_normal_for_males_3(id-1,
		MtCharacterSet::to_decimals(text));
	//21.��ȡ��ǰŮ��������Χ1�����ޡ�
	_1_lower_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING415),this);
		_1_lower_limit_for_female_edit->SetFocus();
		return(-19);
	}
	range.set_lower_limit_of_normal_for_females_1(id-1,
		MtCharacterSet::to_decimals(text));
	//22.��ȡ��ǰŮ��������Χ1�����ޡ�
	_1_upper_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING416),this);
		_1_upper_limit_for_female_edit->SetFocus();
		return(-20);
	}
	range.set_upper_limit_of_normal_for_females_1(id-1,
		MtCharacterSet::to_decimals(text));
	//23.��ȡ��ǰŮ��������Χ2�����ޡ�
	_2_lower_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING415),this);
		_2_lower_limit_for_female_edit->SetFocus();
		return(-21);
	}
	range.set_lower_limit_of_normal_for_females_2(id-1,
		MtCharacterSet::to_decimals(text));
	//24.��ȡ��ǰŮ��������Χ2�����ޡ�
	_2_upper_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING416),this);
		_2_upper_limit_for_female_edit->SetFocus();
		return(-22);
	}
	range.set_upper_limit_of_normal_for_females_2(id-1,
		MtCharacterSet::to_decimals(text));
	//25.��ȡ��ǰŮ��������Χ3�����ޡ�
	_3_lower_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING415),this);
		_3_lower_limit_for_female_edit->SetFocus();
		return(-23);
	}
	range.set_lower_limit_of_normal_for_females_3(id-1,
		MtCharacterSet::to_decimals(text));
	//26.��ȡ��ǰŮ��������Χ3�����ޡ�
	_3_upper_limit_for_female_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING416),this);
		_3_upper_limit_for_female_edit->SetFocus();
		return(-24);
	}
	range.set_upper_limit_of_normal_for_females_3(id-1,
		MtCharacterSet::to_decimals(text));
	//27.��ȡ��ǰĬ�����䡣
	item=_default_age_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING417),this);
		_default_age_combo_box->SetFocus();
		return(-25);
	}
	value=static_cast<int>(_default_age_combo_box->GetItemData(item));
	range.set_default_age(id-1,value);
	//28.��ȡ��ǰĬ���Ա�
	item=_default_sex_combo_box->GetCurSel();
	if(item<0){
		WarningMessageBox(theme->get_string(IDS_STRING418),this);
		_default_sex_combo_box->SetFocus();
		return(-26);
	}
	value=static_cast<int>(_default_sex_combo_box->GetItemData(item));
	range.set_default_sex(id-1,value);
	//29.��ȡ���渴�鷶Χ���ޡ�
	_lower_repeat_range_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING419),this);
		_lower_repeat_range_limit_edit->SetFocus();
		return(-27);
	}
	range.set_lower_limit_for_repeat_range(id-1,MtCharacterSet::to_decimals(text));
	//30.��ȡ���渴�鷶Χ���ޡ�
	_upper_repeat_range_limit_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING420),this);
		_upper_repeat_range_limit_edit->SetFocus();
		return(-28);
	}
	range.set_upper_limit_for_repeat_range(id-1,MtCharacterSet::to_decimals(text));
	//31.��ȡ�Ƿ�ʹ�ö��Ա�
	int is_use_qualitative_table=0;
	if(_use_qualitative_table_check_box->get_checked()){
		is_use_qualitative_table=1;
	}else{
		is_use_qualitative_table=0;
	}
	range.set_is_use_qualitative_table(id-1,is_use_qualitative_table);
	//32.��ȡ���Խ���1��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_1_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING421),this);
			_qualitative_limit_1_edit->SetFocus();
			return(-29);
		}
		range.set_qualitative_limit_1(id-1,MtCharacterSet::to_decimals(text));
	}else{
		range.set_qualitative_limit_1(id-1,0.0);
	}
	//33.��ȡ���Խ����ַ���1��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_1_edit->GetWindowText(text);
		range.set_qualitative_limit_text_1(id-1,text);
	}else{
		range.set_qualitative_limit_text_1(id-1,_T(""));
	}
	//34.��ȡ���Խ���2��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_2_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING421),this);
			_qualitative_limit_2_edit->SetFocus();
			return(-30);
		}
		range.set_qualitative_limit_2(id-1,MtCharacterSet::to_decimals(text));
	}else{
		range.set_qualitative_limit_2(id-1,0.0);
	}
	//35.��ȡ���Խ����ַ���2��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_2_edit->GetWindowText(text);
		range.set_qualitative_limit_text_2(id-1,text);
	}else{
		range.set_qualitative_limit_text_2(id-1,_T(""));
	}
	//36.��ȡ���Խ���3��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_3_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING421),this);
			_qualitative_limit_3_edit->SetFocus();
			return(-31);
		}
		range.set_qualitative_limit_3(id-1,MtCharacterSet::to_decimals(text));
	}else{
		range.set_qualitative_limit_3(id-1,0.0);
	}
	//37.��ȡ���Խ����ַ���3��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_3_edit->GetWindowText(text);
		range.set_qualitative_limit_text_3(id-1,text);
	}else{
		range.set_qualitative_limit_text_3(id-1,_T(""));
	}
	//38.��ȡ���Խ���4��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_4_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING421),this);
			_qualitative_limit_4_edit->SetFocus();
			return(-32);
		}
		range.set_qualitative_limit_4(id-1,MtCharacterSet::to_decimals(text));
	}else{
		range.set_qualitative_limit_4(id-1,0.0);
	}
	//39.��ȡ���Խ����ַ���4��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_4_edit->GetWindowText(text);
		range.set_qualitative_limit_text_4(id-1,text);
	}else{
		range.set_qualitative_limit_text_4(id-1,_T(""));
	}
	//40.��ȡ���Խ���5��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_5_edit->GetWindowText(text);
		if(_T("")==text){
			WarningMessageBox(theme->get_string(IDS_STRING421),this);
			_qualitative_limit_5_edit->SetFocus();
			return(-33);
		}
		range.set_qualitative_limit_5(id-1,MtCharacterSet::to_decimals(text));
	}else{
		range.set_qualitative_limit_5(id-1,0.0);
	}
	//41.��ȡ���Խ����ַ���5��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_5_edit->GetWindowText(text);
		range.set_qualitative_limit_text_5(id-1,text);
	}else{
		range.set_qualitative_limit_text_5(id-1,_T(""));
	}
	//42.��ȡ���Խ����ַ���6��ֵ��
	if(1==is_use_qualitative_table){
		_qualitative_limit_text_6_edit->GetWindowText(text);
		range.set_qualitative_limit_text_6(id-1,text);
	}else{
		range.set_qualitative_limit_text_6(id-1,_T(""));
	}
	//43.��ȡ��������Ϊ����1�������������鷶Χ���ޡ�
	_technical_range_lower_limit_for_class_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING422),this);
		_technical_range_lower_limit_for_class_1_edit->SetFocus();
		return(-34);
	}
	range.set_lower_limit_for_technical_range_for_class_1(
		MtCharacterSet::to_decimals(text));
	//44.��ȡ��������Ϊ����1�������������鷶Χ���ޡ�
	_technical_range_upper_limit_for_class_1_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING423),this);
		_technical_range_upper_limit_for_class_1_edit->SetFocus();
		return(-35);
	}
	range.set_upper_limit_for_technical_range_for_class_1(
		MtCharacterSet::to_decimals(text));
	//45.��ȡ��������Ϊ����2�������������鷶Χ���ޡ�
	_technical_range_lower_limit_for_class_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING424),this);
		_technical_range_lower_limit_for_class_2_edit->SetFocus();
		return(-36);
	}
	range.set_lower_limit_for_technical_range_for_class_2(
		MtCharacterSet::to_decimals(text));
	//46.��ȡ��������Ϊ����2�������������鷶Χ���ޡ�
	_technical_range_upper_limit_for_class_2_edit->GetWindowText(text);
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING425),this);
		_technical_range_upper_limit_for_class_2_edit->SetFocus();
		return(-37);
	}
	range.set_upper_limit_for_technical_range_for_class_2(
		MtCharacterSet::to_decimals(text));
	//47.�����ȡ�ķ�Χ�����Ƿ���������û���Ӧ��ʾ��
	//47-1.������ǰ�������������
	const int result=range.is_valid(&text);
	//47-8.�����ǰ��Χ�����Ƿ���
	if(result<0){
		WarningMessageBox(text,this);
		if(-1==result){
			_control_interval_edit->SetFocus();
		}else if(-2==result){
			_unit_combo_box->SetFocus();
		}else if(-3==result){
			_instrument_factor_a_edit->SetFocus();
		}else if(-4==result){
			_instrument_factor_b_edit->SetFocus();
		}else if(-5==result){
			_data_mode_combo_box->SetFocus();
		}else if(-6==result){
			_lower_age_edit->SetFocus();
		}else if(-7==result){
			_upper_age_edit->SetFocus();
		}else if(-8==result){
			_lower_age_unit_combo_box->SetFocus();
		}else if(-9==result){
			_upper_age_unit_combo_box->SetFocus();
		}else if(-10==result){
			_1_lower_limit_for_male_edit->SetFocus();
		}else if(-11==result){
			_1_upper_limit_for_male_edit->SetFocus();
		}else if(-12==result){
			_2_lower_limit_for_male_edit->SetFocus();
		}else if(-13==result){
			_2_upper_limit_for_male_edit->SetFocus();
		}else if(-14==result){
			_3_lower_limit_for_male_edit->SetFocus();
		}else if(-15==result){
			_3_upper_limit_for_male_edit->SetFocus();
		}else if(-16==result){
			_1_lower_limit_for_female_edit->SetFocus();
		}else if(-17==result){
			_1_upper_limit_for_female_edit->SetFocus();
		}else if(-18==result){
			_2_lower_limit_for_female_edit->SetFocus();
		}else if(-19==result){
			_2_upper_limit_for_female_edit->SetFocus();
		}else if(-20==result){
			_3_lower_limit_for_female_edit->SetFocus();
		}else if(-21==result){
			_3_upper_limit_for_female_edit->SetFocus();
		}else if(-22==result){
			_default_age_combo_box->SetFocus();
		}else if(-23==result){
			_default_sex_combo_box->SetFocus();
		}else if(-24==result){
			_lower_repeat_range_limit_edit->SetFocus();
		}else if(-25==result){
			_upper_repeat_range_limit_edit->SetFocus();
		}else if(-26==result){
			_use_qualitative_table_check_box->SetFocus();
		}else if(-27==result){
			_qualitative_limit_1_edit->SetFocus();
		}else if(-28==result){
			_qualitative_limit_2_edit->SetFocus();
		}else if(-29==result){
			_qualitative_limit_3_edit->SetFocus();
		}else if(-30==result){
			_qualitative_limit_4_edit->SetFocus();
		}else if(-31==result){
			_qualitative_limit_5_edit->SetFocus();
		}else if(-32==result){
			_lower_age_edit->SetFocus();
		}else if(-33==result){
			_1_lower_limit_for_male_edit->SetFocus();
		}else if(-34==result){
			_2_lower_limit_for_male_edit->SetFocus();
		}else if(-35==result){
			_3_lower_limit_for_male_edit->SetFocus();
		}else if(-36==result){
			_1_lower_limit_for_female_edit->SetFocus();
		}else if(-37==result){
			_2_lower_limit_for_female_edit->SetFocus();
		}else if(-38==result){
			_3_lower_limit_for_female_edit->SetFocus();
		}else if(-39==result){
			_lower_repeat_range_limit_edit->SetFocus();
		}else if(-40==result){
			_qualitative_limit_1_edit->SetFocus();
		}else if(-41==result){
			_qualitative_limit_2_edit->SetFocus();
		}else if(-42==result){
			_qualitative_limit_3_edit->SetFocus();
		}else if(-43==result){
			_qualitative_limit_4_edit->SetFocus();
		}else if(-44==result){
			_technical_range_lower_limit_for_class_1_edit->SetFocus();
		}else if(-45==result){
			_technical_range_upper_limit_for_class_1_edit->SetFocus();
		}else if(-46==result){
			_technical_range_lower_limit_for_class_2_edit->SetFocus();
		}else if(-47==result){
			_technical_range_upper_limit_for_class_2_edit->SetFocus();
		}else if(-48==result){
			_technical_range_lower_limit_for_class_1_edit->SetFocus();
		}else if(-49==result){
			_technical_range_lower_limit_for_class_2_edit->SetFocus();
		}
		return(-38);
	}
	//48.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit_data_of_controls
 * brief: �ύ�ؼ������ݵ�ָ�������ݿ��С�
 * param: database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DialogRangeApplication::commit_data_of_controls(Database &database){
	//1.������ǰ�������������
	int item_id=0;
	CString item_alias(_T(""));
	Theme *theme=Theme::instance();
	//2.��ȡ��ǰ׼���޸ĵ����������
	Applications::PtrToCApp application=
		(Applications::instance())->get_by_item_id(_item_id);
	if(!static_cast<bool>(application)){
		ErrorMessageBox(theme->get_string(IDS_STRING428),this);
		return(-1);
	}
	//3.��ȡ��ǰ׼���޸ĵķ�Χ���������
	RangeApplication range=application->get_range();
	//4.��ȡ��ǰ��������������ݡ�
	if(get_data_from_controls(item_id,item_alias,range)<0){
		return(-2);
	}
	//5.�����ݿ��ύ�޸ĵ����ݣ������ж��ύ�Ƿ�ɹ���
	if(Applications::instance()->commit(
		item_id,item_alias,range,database)<0){
		ErrorMessageBox(theme->get_string(IDS_STRING158),this);
		return(-3);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}