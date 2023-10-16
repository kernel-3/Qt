// source-code/ui/calibration/DialogStatus.cpp : implementation file
//

#include"stdafx.h"
#include"DialogStatus.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtComplexListCtrl.h"

//DialogStatus dialog

IMPLEMENT_DYNAMIC(DialogStatus,DialogBase)

/**
 * name: DialogStatus
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogStatus::DialogStatus(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogStatus::IDD,pParent)
	,_start_up_calibration_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_repeat_calibration_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_calibration_mode_static(new MtImageStatic)
	,_calibrations_list(new MtComplexListCtrl)
	,_calibration_trace_button(new MtImageButton)
	,_calibration_information_button(new MtImageButton)
	,_reaction_monitor_button(new MtImageButton)
	,_select_calibration_button(new MtImageButton)
	,_time_out_scheduled_button(new MtImageButton)
	,_calibrate_now_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogStatus
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogStatus::~DialogStatus(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _start_up_calibration_radio_box;
	delete _repeat_calibration_radio_box;
	delete _calibration_mode_static;
	delete _calibrations_list;
	delete _calibration_trace_button;
	delete _calibration_information_button;
	delete _reaction_monitor_button;
	delete _select_calibration_button;
	delete _time_out_scheduled_button;
	delete _calibrate_now_button;
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogStatus::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_RADIO_START_UP_CALIBRATION,*_start_up_calibration_radio_box);
	DDX_Control(pDX,IDC_RADIO_REPEAT_CALIBRATION,*_repeat_calibration_radio_box);
	DDX_Control(pDX,IDC_STATIC_CALIBRATION_MODE,*_calibration_mode_static);
	DDX_Control(pDX,IDC_LIST_CALIBRATIONS,*_calibrations_list);
	DDX_Control(pDX,IDC_BUTTON_CALIBRATION_TRACE,*_calibration_trace_button);
	DDX_Control(pDX,IDC_BUTTON_CALIBRATION_INFORMATION,*_calibration_information_button);
	DDX_Control(pDX,IDC_BUTTON_REACTION_MONITOR,*_reaction_monitor_button);
	DDX_Control(pDX,IDC_BUTTON_SELECT_CALIBRATION,*_select_calibration_button);
	DDX_Control(pDX,IDC_BUTTON_TIME_OUT_SCHEDULED,*_time_out_scheduled_button);
	DDX_Control(pDX,IDC_BUTTON_CALIBRATE_NOW,*_calibrate_now_button);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogStatus::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.初始化当前对话框控件。
	init_controls();
	//2.默认“启动定标”被选中。
	OnBnClickedRadioStartUpCalibration();
	////////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogStatus::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogStatus,DialogBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO_START_UP_CALIBRATION,&DialogStatus::OnBnClickedRadioStartUpCalibration)
	ON_BN_CLICKED(IDC_RADIO_REPEAT_CALIBRATION, &DialogStatus::OnBnClickedRadioRepeatCalibration)
END_MESSAGE_MAP()

//DialogStatus message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogStatus::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
	//2.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_2->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_calibration_mode_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: OnBnClickedRadioStartUpCalibration
 * brief: 用户点击“启动定标”单选框消息响应函数。
 * param: --
 * return: --
 */
void DialogStatus::OnBnClickedRadioStartUpCalibration(){
	// TODO: Add your control notification handler code here
	//1.如果当前“启动定标”单选框处于选中状态，则直接返回。
	if(_start_up_calibration_radio_box->get_checked()){
		return;
	}
	//2.设置其它控件状态。
	_repeat_calibration_radio_box->set_checked(FALSE);
	_time_out_scheduled_button->ShowWindow(SW_HIDE);
	_calibrate_now_button->ShowWindow(SW_HIDE);
	//3.设置当前“启动定标”单选框选中状态。
	_start_up_calibration_radio_box->set_checked(TRUE);
}

/**
 * name: OnBnClickedRadioRepeatCalibration
 * brief: 用户点击“再定标”单选框消息响应函数。
 * param: --
 * return: --
 */
void DialogStatus::OnBnClickedRadioRepeatCalibration(){
	// TODO: Add your control notification handler code here
	//1.如果当前“再定标”单选框处于选中状态，则直接返回。
	if(_repeat_calibration_radio_box->get_checked()){
		return;
	}
	//2.设置其它控件状态。
	_start_up_calibration_radio_box->set_checked(FALSE);
	_time_out_scheduled_button->ShowWindow(SW_SHOW);
	_calibrate_now_button->ShowWindow(SW_SHOW);
	//3.设置当前“再定标”单选框选中状态。
	_repeat_calibration_radio_box->set_checked(TRUE);
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogStatus::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始话对话框中控件。
	//2-1.初始化对话框中单选框。
	_start_up_calibration_radio_box->set_text_color(255,50,50,50);
	_start_up_calibration_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_start_up_calibration_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_start_up_calibration_radio_box->load_background_image(theme->get_image(1),1,6);
	_repeat_calibration_radio_box->set_text_color(255,50,50,50);
	_repeat_calibration_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_repeat_calibration_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_repeat_calibration_radio_box->load_background_image(theme->get_image(1),1,6);
	//2-2.初始化对话框中静态文本框。
	_calibration_mode_static->set_text_color(255,255,255,255);
	_calibration_mode_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_calibration_mode_static->load_background_image(theme->get_image(25));
	_calibration_mode_static->set_background_image_stretching_factors(10,29,10,2);
	//2-3.初始化对话框中的列表框。
	_calibrations_list->set_item_text_color(255,50,50,50);
	_calibrations_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_calibrations_list->load_item_background_image(theme->get_image(33),1,4);
	_calibrations_list->set_item_background_image_stretching_factors(3,3,3,3);
	_calibrations_list->set_header_item_text_color(255,255,255,255);
	_calibrations_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_calibrations_list->load_header_item_background_image(theme->get_image(34),1,2);
	_calibrations_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_calibrations_list->InsertColumn(0,theme->get_string(IDS_STRING131),LVCFMT_LEFT,160);
	_calibrations_list->InsertColumn(1,theme->get_string(IDS_STRING132),LVCFMT_LEFT,160);
	_calibrations_list->InsertColumn(2,theme->get_string(IDS_STRING133),LVCFMT_LEFT,160);
	_calibrations_list->InsertColumn(3,theme->get_string(IDS_STRING134),LVCFMT_LEFT,160);
	_calibrations_list->InsertColumn(4,theme->get_string(IDS_STRING135),LVCFMT_LEFT,160);
	_calibrations_list->set_item_count(10);
	//2-4.初始化对话框中的按钮。
	_calibration_trace_button->set_text_color(255,50,50,50);
	_calibration_trace_button->load_background_image(theme->get_image(32),1,4);
	_calibration_trace_button->set_background_image_stretching_factors(5,5,5,5);
	_calibration_information_button->set_text_color(255,50,50,50);
	_calibration_information_button->load_background_image(theme->get_image(32),1,4);
	_calibration_information_button->set_background_image_stretching_factors(5,5,5,5);
	_reaction_monitor_button->set_text_color(255,50,50,50);
	_reaction_monitor_button->load_background_image(theme->get_image(32),1,4);
	_reaction_monitor_button->set_background_image_stretching_factors(5,5,5,5);
	_select_calibration_button->set_text_color(255,50,50,50);
	_select_calibration_button->load_background_image(theme->get_image(32),1,4);
	_select_calibration_button->set_background_image_stretching_factors(5,5,5,5);
	_time_out_scheduled_button->set_text_color(255,50,50,50);
	_time_out_scheduled_button->load_background_image(theme->get_image(32),1,4);
	_time_out_scheduled_button->set_background_image_stretching_factors(5,5,5,5);
	_calibrate_now_button->set_text_color(255,50,50,50);
	_calibrate_now_button->load_background_image(theme->get_image(32),1,4);
	_calibrate_now_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化对话框中布局。
	//3-1.初始化子布局1。
	_child_layout_1->set_margin(10,35,10,10);
	_child_layout_1->add_fixed_window(_start_up_calibration_radio_box,120);
	_child_layout_1->add_stretch(1);
	_child_layout_1->add_fixed_window(_repeat_calibration_radio_box,120);
	//3-2.初始化子布局2。
	_child_layout_2->add_fixed_layout(_child_layout_1,300);
	_child_layout_2->add_stretch(1);
	//3-3.初始化子布局3。
	_child_layout_3->add_window(_calibration_trace_button,1);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_window(_calibration_information_button,1);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_window(_reaction_monitor_button,1);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_window(_select_calibration_button,1);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_window(_time_out_scheduled_button,1);
	_child_layout_3->add_spacing(5);
	_child_layout_3->add_window(_calibrate_now_button,1);
	//3-4.初始化对话框中主布局。
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_2,100);
	_main_layout->add_spacing(5);
	_main_layout->add_window(_calibrations_list,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,50);
	_main_layout->add_spacing(10);
	//3-5.调整当前对话框布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//4.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_2->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_calibration_mode_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogStatus::draw_boder(MtBitmap &memory_bitmap){
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