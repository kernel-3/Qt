//source-code/ui/workplace/DialogTestSelection.cpp : implementation file
//
#include"stdafx.h"
#include"DialogTestSelection.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"DialogSpecimenInformation.h"
#include"../common/DialogItemAndProfileKeys.h"

// DialogTestSelection dialog
IMPLEMENT_DYNAMIC(DialogTestSelection,DialogBase)

/**
 * name: DialogTestSelection
 * brief: 构造函数。
 * param: pParent - 指向父窗口。
 * return: --
 */
DialogTestSelection::DialogTestSelection(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogTestSelection::IDD,pParent)
	,_test_type_static(new MtImageStatic)
	,_specimen_status_static(new MtImageStatic)
	,_specimen_condition_static(new MtImageStatic)
	,_routine_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_emergency_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_qc_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_demographics_button(new MtImageButton)
	,_define_profile_button(new MtImageButton)
	,_go_to_specimen_button(new MtImageButton)
	,_previous_button(new MtImageButton)
	,_next_button(new MtImageButton)
	,_repeat_button(new MtImageButton)
	,_id_assignment_list_button(new MtImageButton)
	,_ok_button(new MtImageButton)
	,_current_specimen_information_child_dialog(
		SPECIMEN_INFORMATION_CHILD_DIALOG_ID_UNKNOWN)
	,_specimen_information_child_dialogs(new DialogSpecimenInformation[
		SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT])
	,_item_and_profile_keys_child_dialog(new DialogItemAndProfileKeys(3))
	,_child_layout_1(new MtVerticalLayout)
	,_child_layout_2(new MtVerticalLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	_specimen_information_child_dialogs[SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_ROUTINE].
		set_mode(DialogSpecimenInformation::MODE_SEQUENCE_ROUTINE);
	_specimen_information_child_dialogs[SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_EMERGENCY].
		set_mode(DialogSpecimenInformation::MODE_SEQUENCE_EMERGENCY);
	_specimen_information_child_dialogs[SPECIMEN_INFORMATION_CHILD_DIALOG_ID_BARCODE_ROUTINE].
		set_mode(DialogSpecimenInformation::MODE_BARCODE_ROUTINE);
	_specimen_information_child_dialogs[SPECIMEN_INFORMATION_CHILD_DIALOG_ID_BARCODE_EMERGENCY].
		set_mode(DialogSpecimenInformation::MODE_BARCODE_EMERGENCY);
	_specimen_information_child_dialogs[SPECIMEN_INFORMATION_CHILD_DIALOG_ID_QC].
		set_mode(DialogSpecimenInformation::MODE_QC);
}

/**
 * name: ~DialogTestSelection
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogTestSelection::~DialogTestSelection(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _test_type_static;
	delete _specimen_status_static;
	delete _specimen_condition_static;
	delete _routine_radio_box;
	delete _emergency_radio_box;
	delete _qc_radio_box;
	delete _demographics_button;
	delete _define_profile_button;
	delete _go_to_specimen_button;
	delete _previous_button;
	delete _next_button;
	delete _repeat_button;
	delete _id_assignment_list_button;
	delete _ok_button;
	delete[] _specimen_information_child_dialogs;
	delete _item_and_profile_keys_child_dialog;
}

/**
 * name: DoDataExchange
 * brief: 支持DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogTestSelection::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_TEST_TYPE,*_test_type_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_STATUS,*_specimen_status_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_CONDITION,*_specimen_condition_static);
	DDX_Control(pDX,IDC_RADIO_ROUTINE,*_routine_radio_box);
	DDX_Control(pDX,IDC_RADIO_EMERGENCY,*_emergency_radio_box);
	DDX_Control(pDX,IDC_RADIO_QC,*_qc_radio_box);
	DDX_Control(pDX,IDC_BUTTON_DEMOGRAPHICS,*_demographics_button);
	DDX_Control(pDX,IDC_BUTTON_DEFINE_PROFILE,*_define_profile_button);
	DDX_Control(pDX,IDC_BUTTON_GO_TO_SPECIMEN,*_go_to_specimen_button);
	DDX_Control(pDX,IDC_BUTTON_PREVIOUS,*_previous_button);
	DDX_Control(pDX,IDC_BUTTON_NEXT,*_next_button);
	DDX_Control(pDX,IDC_BUTTON_REPEAT,*_repeat_button);
	DDX_Control(pDX,IDC_BUTTON_ID_ASSIGNMENT_LIST,*_id_assignment_list_button);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogTestSelection::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	///////////////////////////////////////////////////////////////////
	//1.初始化当前对话框中控件。
	init_controls();
	///////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框的绘图DC。
 * return: --
 */
void DialogTestSelection::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogTestSelection,DialogBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_RADIO_ROUTINE,IDC_RADIO_QC,&DialogTestSelection::OnRadioBoxesClicked)
END_MESSAGE_MAP()

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogTestSelection::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前主布局的尺寸。
	_main_layout->resize(cx,cy);
	//2.因为现在布局无法管理标题框，所以在此手动对其布局。
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(0,rect)>=0)&&
		(rect.is_valid())&&(IsWindow(_test_type_static->GetSafeHwnd()))){
		_test_type_static->MoveWindow(rect.get_left(),rect.get_top(),
			rect.get_width(),rect.get_height());
	}
	if((_child_layout_3->get_item_rect(4,rect)>=0)&&
		(rect.is_valid())&&(IsWindow(_specimen_status_static->GetSafeHwnd()))){
		_specimen_status_static->MoveWindow(rect.get_left(),rect.get_top(),
			rect.get_width(),rect.get_height());
	}
}

/**
 * name: OnDestroy
 * brief: 对话框销毁消息相应函数。
 * param: --
 * return: --
 */
void DialogTestSelection::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.销毁样本信息子对话框。
	for(unsigned int index=0;index!=
		SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT;++index){
		if(IsWindow(_specimen_information_child_dialogs[index].GetSafeHwnd())){
			_specimen_information_child_dialogs[index].DestroyWindow();
		}
	}
	//2.销毁项目、组合键子对话框。
	_item_and_profile_keys_child_dialog->DestroyWindow();
}

/**
 * name: OnRadioBoxesClicked
 * brief: 点击单选框们消息相应函数。
 * param: ID - 当前点击的单选框控件ID。
 * return: --
 */
void DialogTestSelection::OnRadioBoxesClicked(const unsigned int ID){
	//1.如果当前点击的单选框为“常规”单选框。
	if(ID==IDC_RADIO_ROUTINE){
		//1-1.判断当前“常规”单选框是否已被选中。
		if(_routine_radio_box->get_checked()){
			return;
		}
		//1-2.设置其它单选框状态。
		_routine_radio_box->set_checked(TRUE);
		_emergency_radio_box->set_checked(FALSE);
		_qc_radio_box->set_checked(FALSE);
		//1-3.显示“序列号常规样本信息”子对话框。
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_ROUTINE);
	}
	//2.如果当前点击的单选框为“急诊”单选框。
	else if(ID==IDC_RADIO_EMERGENCY){
		//2-1.判断当前“急诊”单选框是否已被选中。
		if(_emergency_radio_box->get_checked()){
			return;
		}
		//2-2.设置其它单选框状态。
		_routine_radio_box->set_checked(FALSE);
		_emergency_radio_box->set_checked(TRUE);
		_qc_radio_box->set_checked(FALSE);
		//2-3.显示“序列号急诊样本信息”子对话框。
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_EMERGENCY);
	}
	//3.如果当前点击的单选框为“质控”单选框。
	else{
		//3-1.判断当前“质控”单选框是否已被选中。
		if(_qc_radio_box->get_checked()){
			return;
		}
		//3-2.设置其它单选框状态。
		_routine_radio_box->set_checked(FALSE);
		_emergency_radio_box->set_checked(FALSE);
		_qc_radio_box->set_checked(TRUE);
		//3-3.显示“质控样本信息”子对话框。
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_QC);
	}
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogTestSelection::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化当前对话框中按钮控件。
	//静态文本框
	_test_type_static->set_text_color(255,255,255,255);
	_test_type_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_test_type_static->load_background_image(theme->get_image(25));
	_test_type_static->set_background_image_stretching_factors(10,29,10,2);
	_specimen_status_static->set_text_color(255,255,255,255);
	_specimen_status_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_specimen_status_static->load_background_image(theme->get_image(25));
	_specimen_status_static->set_background_image_stretching_factors(10,29,10,2);
	_specimen_condition_static->set_text_color(255,50,50,50);
	_specimen_condition_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	//单选框
	_routine_radio_box->set_text_color(255,50,50,50);
	_routine_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_routine_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_routine_radio_box->load_background_image(theme->get_image(1),1,6);
	_emergency_radio_box->set_text_color(255,50,50,50);
	_emergency_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_emergency_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_emergency_radio_box->load_background_image(theme->get_image(1),1,6);
	_qc_radio_box->set_text_color(255,50,50,50);
	_qc_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_qc_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_qc_radio_box->load_background_image(theme->get_image(1),1,6);
	//按钮
	_demographics_button->set_text_color(255,50,50,50);
	_demographics_button->load_background_image(theme->get_image(32),1,4);
	_demographics_button->set_background_image_stretching_factors(5,5,5,5);
	_define_profile_button->set_text_color(255,50,50,50);
	_define_profile_button->load_background_image(theme->get_image(32),1,4);
	_define_profile_button->set_background_image_stretching_factors(5,5,5,5);
	_go_to_specimen_button->set_text_color(255,50,50,50);
	_go_to_specimen_button->load_background_image(theme->get_image(32),1,4);
	_go_to_specimen_button->set_background_image_stretching_factors(5,5,5,5);
	_previous_button->set_text_color(255,50,50,50);
	_previous_button->load_background_image(theme->get_image(32),1,4);
	_previous_button->set_background_image_stretching_factors(5,5,5,5);
	_next_button->set_text_color(255,50,50,50);
	_next_button->load_background_image(theme->get_image(32),1,4);
	_next_button->set_background_image_stretching_factors(5,5,5,5);
	_repeat_button->set_text_color(255,50,50,50);
	_repeat_button->load_background_image(theme->get_image(32),1,4);
	_repeat_button->set_background_image_stretching_factors(5,5,5,5);
	_id_assignment_list_button->set_text_color(255,50,50,50);
	_id_assignment_list_button->load_background_image(theme->get_image(32),1,4);
	_id_assignment_list_button->set_background_image_stretching_factors(5,5,5,5);
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	//子对话框。
	_item_and_profile_keys_child_dialog->Create(DialogItemAndProfileKeys::IDD,this);
	//3.初始化当前对话框中的布局。
	_child_layout_1->set_margin(10,10,10,5);
	_child_layout_1->add_stretch(15);
	_child_layout_1->add_window(_routine_radio_box,20);
	_child_layout_1->add_window(_emergency_radio_box,20);
	_child_layout_1->add_window(_qc_radio_box,20);
	_child_layout_2->set_margin(10,20,10,5);
	_child_layout_2->add_window(_specimen_condition_static,1);
	_child_layout_3->add_fixed_layout(_child_layout_1,100);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_stretch(1);
	_child_layout_3->add_spacing(10);
	_child_layout_3->add_fixed_layout(_child_layout_2,100);
	_child_layout_4->add_window(_demographics_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_define_profile_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_go_to_specimen_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_previous_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_next_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_repeat_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_id_assignment_list_button,1);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_window(_ok_button,1);
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,120);
	_main_layout->add_spacing(5);
	_main_layout->add_window(_item_and_profile_keys_child_dialog,1);
	_main_layout->add_spacing(10);
	_main_layout->add_fixed_layout(_child_layout_4,50);
	_main_layout->add_spacing(10);
	_main_layout->resize(rect.Width(),rect.Height());
	//4.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_3->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_test_type_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_3->get_item_rect(4,rect_t)>=0)&&(rect_t.is_valid())){
		_specimen_status_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//5.触发事件，显示相应子界面。
	OnRadioBoxesClicked(IDC_RADIO_ROUTINE);
	_item_and_profile_keys_child_dialog->ShowWindow(SW_SHOW);
}

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogTestSelection::draw_boder(MtBitmap &memory_bitmap){
	//1.获取当前对话框的边框图片。
	Theme::PtrToImage image=Theme::instance()->get_image(24);
	//2.如果当前对话框边框图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框边框位置信息。
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height());
}

/**
 * name: show_specimen_information_child_dialog
 * brief: 显示样本信息子对话框。
 * param: child_dialog_id - 期望显示的子对话框ID。
 * return: --
 */
void DialogTestSelection::show_specimen_information_child_dialog(
	const SpecimenInformationChildDialogID child_dialog_id){
	//1.如果当前期望显示的子对话框ID非法，则直接返回。
	if(SPECIMEN_INFORMATION_CHILD_DIALOG_ID_UNKNOWN==child_dialog_id){
		return;
	}
	//2.如果当前期望显示的子对话框与当前显示的子对话框一致，则直接返回。
	if(child_dialog_id==_current_specimen_information_child_dialog){
		return;
	}
	//3.如果当前样本信息子对话框尚未创建，则进行创建操作。
	if(!IsWindow(_specimen_information_child_dialogs[child_dialog_id].GetSafeHwnd())){
		if(!_specimen_information_child_dialogs[child_dialog_id].Create(
			DialogSpecimenInformation::IDD,this)){
			return;
		}
	}
	//4.调整当前期望显示的样本信息子对话框尺寸。
	//4-1.获取当前样本信息子对话框应该显示的尺寸,并且判断获取是否成功。
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(2,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4-2.调整当前期望显示的样本信息子对话框尺寸。
	_specimen_information_child_dialogs[child_dialog_id].MoveWindow(
		rect.get_left(),rect.get_top(),rect.get_width(),rect.get_height());
	//4-3.将当前期望显示的子对话框放入布局管理中，并且判断操作是否成功。
	if(_child_layout_3->set_item_window(2,&_specimen_information_child_dialogs[
		child_dialog_id],1)<0){
		return;
	}
	//5.隐藏所有的样本信息子对话框。
	for(unsigned int index=0;index!=SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT;++index){
		if(IsWindow(_specimen_information_child_dialogs[index].GetSafeHwnd())){
			_specimen_information_child_dialogs[index].ShowWindow(SW_HIDE);
		}
	}
	//6.显示当前期望显示的样本信息子对话框。
	_specimen_information_child_dialogs[child_dialog_id].ShowWindow(SW_SHOW);
	//7.记录当前显示的样本信息子对话框。
	_current_specimen_information_child_dialog=child_dialog_id;
}