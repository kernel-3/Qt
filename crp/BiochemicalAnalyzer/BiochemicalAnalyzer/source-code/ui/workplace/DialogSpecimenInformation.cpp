// source-code/workplace/DialogSpecimenInformation.cpp : implementation file
//

#include"stdafx.h"
#include"DialogSpecimenInformation.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageComboBox.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../global/Theme.h"
#include"../../global/Database.h"
#include"../../global/DatabaseManager.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"

//DialogSpecimenInformation dialog
IMPLEMENT_DYNAMIC(DialogSpecimenInformation,DialogBase)

/**
 * name: DialogSpecimenInformation
 * brief: 构造函数。
 * param: mode - 当前对话框模式。
 *		  pParent - 指向父窗口指针。
 * return: --
 */
DialogSpecimenInformation::DialogSpecimenInformation(
	const Mode mode/*=MODE_SEQUENCE_ROUTINE*/,CWnd *pParent/*=NULL*/)
	:DialogBase(DialogSpecimenInformation::IDD,pParent)
	,_mode(mode)
	//静态文本框
	,_sequence_no_static(new MtImageStatic)
	,_disk_no_static(new MtImageStatic)
	,_position_static(new MtImageStatic)
	,_specimen_id_static(new MtImageStatic)
	,_specimen_type_static(new MtImageStatic)
	,_specimen_cup_static(new MtImageStatic)
	,_specimen_volume_static(new MtImageStatic)
	,_control_name_static(new MtImageStatic)
	,_control_lot_no_static(new MtImageStatic)
	,_control_type_static(new MtImageStatic)
	,_control_position_static(new MtImageStatic)
	//文本编辑框
	,_sequence_no_edit(new MtImageEdit)
	,_disk_no_edit(new MtImageEdit)
	,_position_edit(new MtImageEdit)
	,_specimen_id_edit(new MtImageEdit)
	,_control_lot_no_edit(new MtImageEdit)
	,_control_type_edit(new MtImageEdit)
	,_control_position_edit(new MtImageEdit)
	//下拉框
	,_specimen_type_combo_box(new MtImageComboBox)
	,_specimen_cup_combo_box(new MtImageComboBox)
	,_specimen_volume_combo_box(new MtImageComboBox)
	,_control_name_combo_box(new MtImageComboBox)
	//复选框
	,_unreadable_specimen_id_check_box(new MtImageCheckBox(
		MtImageCheckBox::TYPE_CHECK_BOX))
	//布局
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtVerticalLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_child_layout_6(new MtHorizonLayout)
	,_child_layout_7(new MtHorizonLayout)
	,_child_layout_8(new MtVerticalLayout)
	,_main_layout(new MtHorizonLayout){
}

/**
 * name: ~DialogSpecimenInformation
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogSpecimenInformation::~DialogSpecimenInformation(){
	//布局
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	delete _child_layout_6;
	delete _child_layout_7;
	delete _child_layout_8;
	//静态文本框。
	delete _sequence_no_static;
	delete _disk_no_static;
	delete _position_static;
	delete _specimen_id_static;
	delete _specimen_type_static;
	delete _specimen_cup_static;
	delete _specimen_volume_static;
	delete _control_name_static;
	delete _control_lot_no_static;
	delete _control_type_static;
	delete _control_position_static;
	//文本编辑框。
	delete _sequence_no_edit;
	delete _disk_no_edit;
	delete _position_edit;
	delete _specimen_id_edit;
	delete _control_lot_no_edit;
	delete _control_type_edit;
	delete _control_position_edit;
	//下拉框。
	delete _specimen_type_combo_box;
	delete _specimen_cup_combo_box;
	delete _specimen_volume_combo_box;
	delete _control_name_combo_box;
	//复选框
	delete _unreadable_specimen_id_check_box;
}

/**
 * name: set_mode
 * brief: 设置当前对话框模式。
 * param: mode - 对话框模式。
 * return: --
 */
void DialogSpecimenInformation::set_mode(const Mode mode){
	_mode=mode;
}

/**
 * name: get_mode
 * brief: 获取当前对话框模式。
 * param: --
 * return: 返回当前对话框模式。
 */
DialogSpecimenInformation::Mode DialogSpecimenInformation::get_mode() const{
	return(_mode);
}

/**
 * name: DoDataExchange
 * brief: 支持DDX、DDV。
 * param: pDX -
 * return:
 */
void DialogSpecimenInformation::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SEQUENCE_NO,*_sequence_no_static);
	DDX_Control(pDX,IDC_STATIC_DISK_NO,*_disk_no_static);
	DDX_Control(pDX,IDC_STATIC_POSITION,*_position_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_ID,*_specimen_id_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_TYPE,*_specimen_type_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_CUP,*_specimen_cup_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_VOLUME,*_specimen_volume_static);
	DDX_Control(pDX,IDC_STATIC_CONTROL_NAME,*_control_name_static);
	DDX_Control(pDX,IDC_STATIC_CONTROL_LOT_NO,*_control_lot_no_static);
	DDX_Control(pDX,IDC_STATIC_CONTROL_TYPE,*_control_type_static);
	DDX_Control(pDX,IDC_STATIC_CONTROL_POSITION,*_control_position_static);
	DDX_Control(pDX,IDC_EDIT_SEQUENCE_NO,*_sequence_no_edit);
	DDX_Control(pDX,IDC_EDIT_DISK_NO,*_disk_no_edit);
	DDX_Control(pDX,IDC_EDIT_POSITION,*_position_edit);
	DDX_Control(pDX,IDC_EDIT_SPECIMEN_ID,*_specimen_id_edit);
	DDX_Control(pDX,IDC_EDIT_CONTROL_LOT_NO,*_control_lot_no_edit);
	DDX_Control(pDX,IDC_EDIT_CONTROL_TYPE,*_control_type_edit);
	DDX_Control(pDX,IDC_EDIT_CONTROL_POSITION,*_control_position_edit);
	DDX_Control(pDX,IDC_COMBO_SPECIMEN_TYPE,*_specimen_type_combo_box);
	DDX_Control(pDX,IDC_COMBO_SPECIMEN_CUP,*_specimen_cup_combo_box);
	DDX_Control(pDX,IDC_COMBO_SPECIMEN_VOLUME,*_specimen_volume_combo_box);
	DDX_Control(pDX,IDC_COMBO_CONTROL_NAME,*_control_name_combo_box);
	DDX_Control(pDX,IDC_CHECK_UNREADABLE_SPECIMEN_ID,*_unreadable_specimen_id_check_box);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogSpecimenInformation::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.初始化对话框控件。
	init_controls();
	////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogSpecimenInformation,DialogBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_UNREADABLE_SPECIMEN_ID,&DialogSpecimenInformation::OnBnClickedCheckUnreadableSpecimenId)
END_MESSAGE_MAP()

//DialogSpecimenInformation message handlers
/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogSpecimenInformation::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前主布局的尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: OnBnClickedCheckUnreadableSpecimenId
 * brief: 用户点击“未能读取样本标识”复选框消息响应函数。
 * param: --
 * reutrn: --
 */
void DialogSpecimenInformation::OnBnClickedCheckUnreadableSpecimenId(){
	// TODO: Add your control notification handler code here
	if(_unreadable_specimen_id_check_box->get_checked()){
		_position_static->ShowWindow(SW_HIDE);
		_position_edit->ShowWindow(SW_HIDE);
		_unreadable_specimen_id_check_box->set_checked(FALSE);
	}else{
		_position_static->ShowWindow(SW_SHOW);
		_position_edit->ShowWindow(SW_SHOW);
		_unreadable_specimen_id_check_box->set_checked(TRUE);
	}
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogSpecimenInformation::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化当前对话框中所有空间。
	//2-1.初始化静态文本框。
	_sequence_no_static->set_text_color(255,50,50,50);
	_sequence_no_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_disk_no_static->set_text_color(255,50,50,50);
	_disk_no_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_position_static->set_text_color(255,50,50,50);
	_position_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_specimen_id_static->set_text_color(255,50,50,50);
	_specimen_id_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_specimen_type_static->set_text_color(255,50,50,50);
	_specimen_type_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_specimen_cup_static->set_text_color(255,50,50,50);
	_specimen_cup_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_specimen_volume_static->set_text_color(255,50,50,50);
	_specimen_volume_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_control_name_static->set_text_color(255,50,50,50);
	_control_name_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_control_lot_no_static->set_text_color(255,50,50,50);
	_control_lot_no_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_control_type_static->set_text_color(255,50,50,50);
	_control_type_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_control_position_static->set_text_color(255,50,50,50);
	_control_position_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.初始化文本编辑框。
	_sequence_no_edit->set_text_color(50,50,50);
	_sequence_no_edit->load_background_image(theme->get_image(29),1,3);
	_sequence_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_disk_no_edit->set_text_color(50,50,50);
	_disk_no_edit->load_background_image(theme->get_image(29),1,3);
	_disk_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_position_edit->set_text_color(50,50,50);
	_position_edit->load_background_image(theme->get_image(29),1,3);
	_position_edit->set_background_image_stretching_factors(5,5,5,5);
	_specimen_id_edit->set_text_color(50,50,50);
	_specimen_id_edit->load_background_image(theme->get_image(29),1,3);
	_specimen_id_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_lot_no_edit->load_background_image(theme->get_image(29),1,3);
	_control_lot_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_lot_no_edit->EnableWindow(FALSE);
	//_control_lot_no_edit->SetWindowText(_T("00000001"));
	_control_type_edit->load_background_image(theme->get_image(29),1,3);
	_control_type_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_type_edit->EnableWindow(FALSE);
	//_control_type_edit->SetWindowText(_T("Class 1"));
	_control_position_edit->load_background_image(theme->get_image(29),1,3);
	_control_position_edit->set_background_image_stretching_factors(5,5,5,5);
	_control_position_edit->EnableWindow(FALSE);
	//_control_position_edit->SetWindowText(_T("1"));
	//2-3.初始化下拉框。
	_specimen_type_combo_box->set_text_color(255,50,50,50);
	_specimen_type_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_type_combo_box->set_list_box_text_color(255,50,50,50);
	_specimen_type_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_type_combo_box->load_background_image(theme->get_image(27),1,4);
	_specimen_type_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_specimen_type_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_specimen_type_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_specimen_cup_combo_box->set_text_color(255,50,50,50);
	_specimen_cup_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_cup_combo_box->set_list_box_text_color(255,50,50,50);
	_specimen_cup_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_cup_combo_box->load_background_image(theme->get_image(27),1,4);
	_specimen_cup_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_specimen_cup_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_specimen_cup_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_specimen_volume_combo_box->set_text_color(255,50,50,50);
	_specimen_volume_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_volume_combo_box->set_list_box_text_color(255,50,50,50);
	_specimen_volume_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_specimen_volume_combo_box->load_background_image(theme->get_image(27),1,4);
	_specimen_volume_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_specimen_volume_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_specimen_volume_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_control_name_combo_box->set_text_color(255,50,50,50);
	_control_name_combo_box->set_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_control_name_combo_box->set_list_box_text_color(255,50,50,50);
	_control_name_combo_box->set_list_box_text_alignment(MtImageComboBox::ALIGNMENT_LEFT|
		MtImageComboBox::ALIGNMENT_VCENTER);
	_control_name_combo_box->load_background_image(theme->get_image(27),1,4);
	_control_name_combo_box->set_background_image_stretching_factors(5,12,15,5);
	_control_name_combo_box->load_list_box_background_image(theme->get_image(28),1,2);
	_control_name_combo_box->set_list_box_background_image_stretching_factors(5,5,5,5);
	_control_name_combo_box->EnableWindow(FALSE);
	//2-4.初始化复选框。
	_unreadable_specimen_id_check_box->set_text_color(255,50,50,50);
	_unreadable_specimen_id_check_box->load_background_image(theme->get_image(1),1,6);
	_unreadable_specimen_id_check_box->load_foreground_image(theme->get_image(30),1,6);
	_unreadable_specimen_id_check_box->set_foreground_image_alignment(
		MtImageCheckBox::ALIGNMENT_LEFT|MtImageCheckBox::ALIGNMENT_VCENTER);
	//3.根据当前对话框模式设定控件的初始值。
	if(MODE_SEQUENCE_ROUTINE==_mode){
		load_data_from_database_to_specimen_type_combo_box();
		load_data_from_database_to_specimen_cup_combo_box();
		load_data_from_database_to_specimen_volume_combo_box();
	}else if(MODE_SEQUENCE_EMERGENCY==_mode){
		load_data_from_database_to_specimen_type_combo_box();
		load_data_from_database_to_specimen_cup_combo_box();
		load_data_from_database_to_specimen_volume_combo_box();
	}else if(MODE_BARCODE_ROUTINE==_mode){
		load_data_from_database_to_specimen_type_combo_box();
		load_data_from_database_to_specimen_cup_combo_box();
		load_data_from_database_to_specimen_volume_combo_box();
	}else if(MODE_BARCODE_EMERGENCY==_mode){
		load_data_from_database_to_specimen_type_combo_box();
		load_data_from_database_to_specimen_cup_combo_box();
		load_data_from_database_to_specimen_volume_combo_box();
	}else{
	}
	//4.根据当前对话框模式设定控件的隐现。
	if(MODE_SEQUENCE_ROUTINE==_mode){
		_unreadable_specimen_id_check_box->ShowWindow(SW_HIDE);
		_control_name_static->ShowWindow(SW_HIDE);
		_control_name_combo_box->ShowWindow(SW_HIDE);
		_control_lot_no_static->ShowWindow(SW_HIDE);
		_control_lot_no_edit->ShowWindow(SW_HIDE);
		_control_type_static->ShowWindow(SW_HIDE);
		_control_type_edit->ShowWindow(SW_HIDE);
		_control_position_static->ShowWindow(SW_HIDE);
		_control_position_edit->ShowWindow(SW_HIDE);
	}else if(MODE_SEQUENCE_EMERGENCY==_mode){
		_sequence_no_static->ShowWindow(SW_HIDE);
		_sequence_no_edit->ShowWindow(SW_HIDE);
		_disk_no_static->ShowWindow(SW_HIDE);
		_disk_no_edit->ShowWindow(SW_HIDE);
		_unreadable_specimen_id_check_box->ShowWindow(SW_HIDE);
		_control_name_static->ShowWindow(SW_HIDE);
		_control_name_combo_box->ShowWindow(SW_HIDE);
		_control_lot_no_static->ShowWindow(SW_HIDE);
		_control_lot_no_edit->ShowWindow(SW_HIDE);
		_control_type_static->ShowWindow(SW_HIDE);
		_control_type_edit->ShowWindow(SW_HIDE);
		_control_position_static->ShowWindow(SW_HIDE);
		_control_position_edit->ShowWindow(SW_HIDE);
	}else if(MODE_BARCODE_ROUTINE==_mode){
		_sequence_no_static->ShowWindow(SW_HIDE);
		_sequence_no_edit->ShowWindow(SW_HIDE);
		_disk_no_static->ShowWindow(SW_HIDE);
		_disk_no_edit->ShowWindow(SW_HIDE);
		_position_static->ShowWindow(SW_HIDE);
		_position_edit->ShowWindow(SW_HIDE);
		_control_name_static->ShowWindow(SW_HIDE);
		_control_name_combo_box->ShowWindow(SW_HIDE);
		_control_lot_no_static->ShowWindow(SW_HIDE);
		_control_lot_no_edit->ShowWindow(SW_HIDE);
		_control_type_static->ShowWindow(SW_HIDE);
		_control_type_edit->ShowWindow(SW_HIDE);
		_control_position_static->ShowWindow(SW_HIDE);
		_control_position_edit->ShowWindow(SW_HIDE);
	}else if(MODE_BARCODE_EMERGENCY==_mode){
		_sequence_no_static->ShowWindow(SW_HIDE);
		_sequence_no_edit->ShowWindow(SW_HIDE);
		_disk_no_static->ShowWindow(SW_HIDE);
		_disk_no_edit->ShowWindow(SW_HIDE);
		_unreadable_specimen_id_check_box->ShowWindow(SW_HIDE);
		_control_name_static->ShowWindow(SW_HIDE);
		_control_name_combo_box->ShowWindow(SW_HIDE);
		_control_lot_no_static->ShowWindow(SW_HIDE);
		_control_lot_no_edit->ShowWindow(SW_HIDE);
		_control_type_static->ShowWindow(SW_HIDE);
		_control_type_edit->ShowWindow(SW_HIDE);
		_control_position_static->ShowWindow(SW_HIDE);
		_control_position_edit->ShowWindow(SW_HIDE);
	}else{
		_sequence_no_static->ShowWindow(SW_HIDE);
		_sequence_no_edit->ShowWindow(SW_HIDE);
		_disk_no_static->ShowWindow(SW_HIDE);
		_disk_no_edit->ShowWindow(SW_HIDE);
		_position_static->ShowWindow(SW_HIDE);
		_position_edit->ShowWindow(SW_HIDE);
		_specimen_id_static->ShowWindow(SW_HIDE);
		_specimen_id_edit->ShowWindow(SW_HIDE);
		_unreadable_specimen_id_check_box->ShowWindow(SW_HIDE);
		_specimen_type_static->ShowWindow(SW_HIDE);
		_specimen_type_combo_box->ShowWindow(SW_HIDE);
		_specimen_cup_static->ShowWindow(SW_HIDE);
		_specimen_cup_combo_box->ShowWindow(SW_HIDE);
		_specimen_volume_static->ShowWindow(SW_HIDE);
		_specimen_volume_static->ShowWindow(SW_HIDE);
	}
	//5.根据当前对话框模式设置界面布局。
	if(MODE_SEQUENCE_ROUTINE==_mode){
		_child_layout_1->add_fixed_window(_sequence_no_static,100);
		_child_layout_1->add_fixed_window(_sequence_no_edit,50);
		_child_layout_1->add_stretch(1);
		_child_layout_2->add_fixed_window(_disk_no_static,100);
		_child_layout_2->add_fixed_window(_disk_no_edit,50);
		_child_layout_2->add_spacing(10);
		_child_layout_2->add_fixed_window(_position_static,100);
		_child_layout_2->add_fixed_window(_position_edit,50);
		_child_layout_2->add_stretch(1);
		_child_layout_3->add_fixed_window(_specimen_id_static,100);
		_child_layout_3->add_window(_specimen_id_edit,1);
		_child_layout_4->add_stretch(1);
		_child_layout_4->add_fixed_layout(_child_layout_1,24);
		_child_layout_4->add_spacing(5);
		_child_layout_4->add_fixed_layout(_child_layout_2,24);
		_child_layout_4->add_spacing(5);
		_child_layout_4->add_fixed_layout(_child_layout_3,24);
		_child_layout_4->add_stretch(1);
		_child_layout_5->add_fixed_window(_specimen_type_static,120);
		_child_layout_5->add_window(_specimen_type_combo_box,1);
		_child_layout_6->add_fixed_window(_specimen_cup_static,120);
		_child_layout_6->add_window(_specimen_cup_combo_box,1);
		_child_layout_7->add_fixed_window(_specimen_volume_static,120);
		_child_layout_7->add_window(_specimen_volume_combo_box,1);
		_child_layout_8->add_stretch(1);
		_child_layout_8->add_fixed_layout(_child_layout_5,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_6,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_7,24);
		_child_layout_8->add_stretch(1);
	}else if(MODE_SEQUENCE_EMERGENCY==_mode){
		_child_layout_1->add_fixed_window(_position_static,100);
		_child_layout_1->add_fixed_window(_position_edit,50);
		_child_layout_1->add_stretch(1);
		_child_layout_2->add_fixed_window(_specimen_id_static,100);
		_child_layout_2->add_window(_specimen_id_edit,1);
		_child_layout_4->add_stretch(1);
		_child_layout_4->add_fixed_layout(_child_layout_1,24);
		_child_layout_4->add_spacing(5);
		_child_layout_4->add_fixed_layout(_child_layout_2,24);
		_child_layout_4->add_stretch(1);
		_child_layout_5->add_fixed_window(_specimen_type_static,120);
		_child_layout_5->add_window(_specimen_type_combo_box,1);
		_child_layout_6->add_fixed_window(_specimen_cup_static,120);
		_child_layout_6->add_window(_specimen_cup_combo_box,1);
		_child_layout_7->add_fixed_window(_specimen_volume_static,120);
		_child_layout_7->add_window(_specimen_volume_combo_box,1);
		_child_layout_8->add_stretch(1);
		_child_layout_8->add_fixed_layout(_child_layout_5,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_6,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_7,24);
		_child_layout_8->add_stretch(1);
	}else if(MODE_BARCODE_ROUTINE==_mode){
		_child_layout_1->add_fixed_window(_unreadable_specimen_id_check_box,170);
		_child_layout_1->add_spacing(10);
		_child_layout_1->add_fixed_window(_position_static,100);
		_child_layout_1->add_fixed_window(_position_edit,50);
		_child_layout_1->add_stretch(1);
		_child_layout_2->add_fixed_window(_specimen_id_static,100);
		_child_layout_2->add_window(_specimen_id_edit,1);
		_child_layout_4->add_stretch(1);
		_child_layout_4->add_fixed_layout(_child_layout_1,24);
		_child_layout_4->add_spacing(5);
		_child_layout_4->add_fixed_layout(_child_layout_2,24);
		_child_layout_4->add_stretch(1);
		_child_layout_5->add_fixed_window(_specimen_type_static,120);
		_child_layout_5->add_window(_specimen_type_combo_box,1);
		_child_layout_6->add_fixed_window(_specimen_cup_static,120);
		_child_layout_6->add_window(_specimen_cup_combo_box,1);
		_child_layout_7->add_fixed_window(_specimen_volume_static,120);
		_child_layout_7->add_window(_specimen_volume_combo_box,1);
		_child_layout_8->add_stretch(1);
		_child_layout_8->add_fixed_layout(_child_layout_5,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_6,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_7,24);
		_child_layout_8->add_stretch(1);
	}else if(MODE_BARCODE_EMERGENCY==_mode){
		_child_layout_1->add_fixed_window(_position_static,100);
		_child_layout_1->add_fixed_window(_position_edit,50);
		_child_layout_1->add_stretch(1);
		_child_layout_2->add_fixed_window(_specimen_id_static,100);
		_child_layout_2->add_window(_specimen_id_edit,1);
		_child_layout_4->add_stretch(1);
		_child_layout_4->add_fixed_layout(_child_layout_1,24);
		_child_layout_4->add_spacing(5);
		_child_layout_4->add_fixed_layout(_child_layout_2,24);
		_child_layout_4->add_stretch(1);
		_child_layout_5->add_fixed_window(_specimen_type_static,120);
		_child_layout_5->add_window(_specimen_type_combo_box,1);
		_child_layout_6->add_fixed_window(_specimen_cup_static,120);
		_child_layout_6->add_window(_specimen_cup_combo_box,1);
		_child_layout_7->add_fixed_window(_specimen_volume_static,120);
		_child_layout_7->add_window(_specimen_volume_combo_box,1);
		_child_layout_8->add_stretch(1);
		_child_layout_8->add_fixed_layout(_child_layout_5,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_6,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_7,24);
		_child_layout_8->add_stretch(1);
	}else{
		_child_layout_1->add_fixed_window(_control_name_static,100);
		_child_layout_1->add_window(_control_name_combo_box,1);
		_child_layout_4->add_stretch(1);
		_child_layout_4->add_fixed_layout(_child_layout_1,24);
		_child_layout_4->add_stretch(1);
		_child_layout_2->add_fixed_window(_control_lot_no_static,100);
		_child_layout_2->add_window(_control_lot_no_edit,1);
		_child_layout_3->add_fixed_window(_control_type_static,100);
		_child_layout_3->add_window(_control_type_edit,1);
		_child_layout_5->add_fixed_window(_control_position_static,100);
		_child_layout_5->add_window(_control_position_edit,1);
		_child_layout_8->add_stretch(1);
		_child_layout_8->add_fixed_layout(_child_layout_2,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_3,24);
		_child_layout_8->add_spacing(5);
		_child_layout_8->add_fixed_layout(_child_layout_5,24);
		_child_layout_8->add_stretch(1);
	}
	_main_layout->add_layout(_child_layout_4,15);
	_main_layout->add_spacing(20);
	_main_layout->add_layout(_child_layout_8,10);
	//6.调整当前主布局。
	_main_layout->resize(rect.Width(),rect.Height());
}

 /**
  * name: load_data_from_database_to_specimen_type_combo_box
  * brief: 从数据库中加载相应数据到“样本类型”下拉框中。
  * param: --
  * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
  */
int DialogSpecimenInformation::load_data_from_database_to_specimen_type_combo_box(){
	//1.获取数据库中相应的记录集。
	Database::PtrToRecordset recordset=DatabaseManager::instance()->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)->get_recordset(
		_T("SELECT * FROM [specimen_type] ORDER BY [ID] ASC"));
	//2.如果记录集获取失败，则直接返回相应错误。
	if(!static_cast<bool>(recordset)){
		return(-1);
	}
	//3.声明当前操作所需变量。
	int item=0;
	int specimen_type=0;
	CString specimen_type_name(_T(""));
	//4.遍历记录集，将记录集内的数据绑定到“样本类型”下拉框中。
	while(!recordset->get_eof()){
		//4-1.如果数据库操作失败，则直接返回错误。
		if(0!=recordset->get_last_error_code()){
			return(-2);
		}
		//4-2.获取记录集中的样本类型ID。
		specimen_type=MtADODataConverter::to_int(recordset->
			get_collect(MtADODataConverter::to_variant_t(0)));
		if(0!=recordset->get_last_error_code()){
			return(-3);
		}
		//4-3.获取记录集中的样本类型名称。
		specimen_type_name=MtADODataConverter::to_string(recordset->
			get_collect(MtADODataConverter::to_variant_t(1)));
		if(0!=recordset->get_last_error_code()){
			return(-4);
		}
		//4-4.将获取的数据绑定到样本类型下拉框中。
		if(_T("Ser/PI")==specimen_type_name){
			item=_specimen_type_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING102));
			_specimen_type_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_type));
		}else if(_T("Urine")==specimen_type_name){
			item=_specimen_type_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING103));
			_specimen_type_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_type));
		}else if(_T("CSF")==specimen_type_name){
			item=_specimen_type_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING104));
			_specimen_type_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_type));
		}else if(_T("Suprnt")==specimen_type_name){
			item=_specimen_type_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING105));
			_specimen_type_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_type));
		}else if(_T("Other")==specimen_type_name){
			item=_specimen_type_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING106));
			_specimen_type_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_type));
		}
		//4-4.记录集向下移动一个位置。
		recordset->move_next();
		if(0!=recordset->get_last_error_code()){
			return(-5);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: load_data_from_database_to_specimen_cup_combo_box
 * brief: 从数据库中加载相应数据到“样本杯”下拉框中。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DialogSpecimenInformation::load_data_from_database_to_specimen_cup_combo_box(){
	//1.获取数据库中相应的记录集。
	Database::PtrToRecordset recordset=DatabaseManager::instance()->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)->get_recordset(
		_T("SELECT * FROM [specimen_cup] ORDER BY [ID] ASC"));
	//2.如果记录集获取失败，则直接返回相应错误。
	if(!static_cast<bool>(recordset)){
		return(-1);
	}
	//3.声明当前操作所需变量。
	int item=0;
	int specimen_cup=0;
	CString specimen_cup_name(_T(""));
	//4.遍历记录集，将记录集内的数据绑定到“样本杯”下拉框中。
	while(!recordset->get_eof()){
		//4-1.如果数据库操作失败，则直接返回错误。
		if(0!=recordset->get_last_error_code()){
			return(-2);
		}
		//4-2.获取记录集中的样本杯信息。
		specimen_cup=MtADODataConverter::to_int(recordset->
			get_collect(MtADODataConverter::to_variant_t(0)));
		if(0!=recordset->get_last_error_code()){
			return(-3);
		}
		//4-3.获取记录集中的样本杯名称信息。
		specimen_cup_name=MtADODataConverter::to_string(recordset->
			get_collect(MtADODataConverter::to_variant_t(1)));
		if(0!=recordset->get_last_error_code()){
			return(-4);
		}
		//4-4.将获取的数据绑定到样本类型下拉框中。
		if(_T("Standard Cup")==specimen_cup_name){
			item=_specimen_cup_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING107));
			_specimen_cup_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_cup));
		}else if(_T("Micro Cup")==specimen_cup_name){
			item=_specimen_cup_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING108));
			_specimen_cup_combo_box->SetItemData(item,static_cast<
		DWORD_PTR>(specimen_cup));
		}else if(_T("Sample Tube")==specimen_cup_name){
			item=_specimen_cup_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING109));
			_specimen_cup_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(specimen_cup));
		}
		//4-5.记录集向下移动一个位置。
		recordset->move_next();
		if(0!=recordset->get_last_error_code()){
			return(-5);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: load_data_from_database_to_specimen_volume_combo_box
 * brief: 从数据库中加载相应数据到“样本体积”下拉框中。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DialogSpecimenInformation::load_data_from_database_to_specimen_volume_combo_box(){
	//1.获取数据库中相应的记录集。
	Database::PtrToRecordset recordset=DatabaseManager::instance()->get_database(
		DatabaseManager::DATABASE_NAME_MAIN)->get_recordset(
		_T("SELECT * FROM [piped_specimen_type] ORDER BY [ID] ASC"));
	//2.如果记录集获取失败，则直接返回相应错误。
	if(!static_cast<bool>(recordset)){
		return(-1);
	}
	//3.声明当前操作所需变量。
	int item=0;
	int piped_specimen_type=0;
	CString piped_specimen_type_name(_T(""));
	//4.遍历记录集，将记录集内的数据绑定到“样本体积”下拉框中。
	while(!recordset->get_eof()){
		//4-1.如果数据库操作失败，则直接返回错误。
		if(0!=recordset->get_last_error_code()){
			return(-2);
		}
		//4-2.获取记录集中的样本体积信息。
		piped_specimen_type=MtADODataConverter::to_int(
			recordset->get_collect(MtADODataConverter::to_variant_t(0)));
		if(0!=recordset->get_last_error_code()){
			return(-3);
		}
		//4-3.获取记录集中的样本类型名称。
		piped_specimen_type_name=MtADODataConverter::to_string(recordset->
			get_collect(MtADODataConverter::to_variant_t(1)));
		if(0!=recordset->get_last_error_code()){
			return(-4);
		}
		//4-4.将获取的数据绑定到样本体积下拉框中。
		if(_T("Normal")==piped_specimen_type_name){
			item=_specimen_volume_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING110));
			_specimen_volume_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(piped_specimen_type));
		}else if(_T("Decrease")==piped_specimen_type_name){
			item=_specimen_volume_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING111));
			_specimen_volume_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(piped_specimen_type));
		}else if(_T("Increase")==piped_specimen_type_name){
			item=_specimen_volume_combo_box->AddString(
				Theme::instance()->get_string(IDS_STRING112));
			_specimen_volume_combo_box->SetItemData(item,static_cast<
				DWORD_PTR>(piped_specimen_type));
		}
		//4-5.记录集向下移动一个位置。
		recordset->move_next();
		if(0!=recordset->get_last_error_code()){
			return(-5);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}