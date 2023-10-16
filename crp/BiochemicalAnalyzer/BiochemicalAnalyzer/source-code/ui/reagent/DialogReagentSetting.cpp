// source-code/ui/reagent/DialogReagentSetting.cpp : implementation file
//

#include"stdafx.h"
#include"DialogReagentSetting.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/control/MtComplexListCtrl.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"

IMPLEMENT_DYNAMIC(DialogReagentSetting,DialogBase)

/**
 * name: DialogReagentSetting
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogReagentSetting::DialogReagentSetting(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogReagentSetting::IDD,pParent)
	,_reagent_disk_tests_list(new MtComplexListCtrl)
	,_reagent_disk_idle_position_list(new MtComplexListCtrl)
	,_reagent_disk_idle_position_static(new MtImageStatic)
	,_manual_setting_static(new MtImageStatic)
	,_over_ride_manual_setting_static(new MtImageStatic)
	,_details_button(new MtImageButton)
	,_manual_setting_button(new MtImageButton)
	,_delete_button(new MtImageButton)
	,_ise_reagent_remaining_volumes_button(new MtImageButton)
	,_barcode_button(new MtImageButton)
	,_level_button(new MtImageButton)
	,_volume_reset_button(new MtImageButton)
	,_item_sort_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtVerticalLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtVerticalLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogReagentSetting
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogReagentSetting::~DialogReagentSetting(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	delete _reagent_disk_tests_list;
	delete _reagent_disk_idle_position_list;
	delete _reagent_disk_idle_position_static;
	delete _manual_setting_static;
	delete _over_ride_manual_setting_static;
	delete _details_button;
	delete _manual_setting_button;
	delete _delete_button;
	delete _ise_reagent_remaining_volumes_button;
	delete _barcode_button;
	delete _level_button;
	delete _volume_reset_button;
	delete _item_sort_button;
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogReagentSetting::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_REAGENT_DISK_TESTS,*_reagent_disk_tests_list);
	DDX_Control(pDX,IDC_LIST_REAGENT_DISK_IDLE_POSITION,*_reagent_disk_idle_position_list);
	DDX_Control(pDX,IDC_STATIC_REAGENT_DISK_IDLE_POSITIONS,*_reagent_disk_idle_position_static);
	DDX_Control(pDX,IDC_STATIC_MANUAL_SETTING,*_manual_setting_static);
	DDX_Control(pDX,IDC_STATIC_OVER_RIDE_MANUAL_SETTING,*_over_ride_manual_setting_static);
	DDX_Control(pDX,IDC_BUTTON_DETAILS,*_details_button);
	DDX_Control(pDX,IDC_BUTTON_MANUAL_SETTING,*_manual_setting_button);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
	DDX_Control(pDX,IDC_BUTTON_ISE_REAGENT_REMAINING_VOLUMES,*_ise_reagent_remaining_volumes_button);
	DDX_Control(pDX,IDC_BUTTON_BARCODE,*_barcode_button);
	DDX_Control(pDX,IDC_BUTTON_LEVEL,*_level_button);
	DDX_Control(pDX,IDC_BUTTON_VOLUME_RESET,*_volume_reset_button);
	DDX_Control(pDX,IDC_BUTTON_ITEM_SORT,*_item_sort_button);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogReagentSetting::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.初始化当前对话框控件。
	init_controls();
	////////////////////////////////////////////////////////////////////
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
void DialogReagentSetting::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogReagentSetting,DialogBase)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//DialogReagentSetting message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogReagentSetting::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
	//2.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_1->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_reagent_disk_idle_position_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogReagentSetting::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化控件。
	//2-1.初始化列表框。
	_reagent_disk_tests_list->set_item_text_color(255,50,50,50);
	_reagent_disk_tests_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_reagent_disk_tests_list->load_item_background_image(theme->get_image(33),1,4);
	_reagent_disk_tests_list->set_item_background_image_stretching_factors(3,3,3,3);
	_reagent_disk_tests_list->set_header_item_text_color(255,255,255,255);
	_reagent_disk_tests_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_reagent_disk_tests_list->load_header_item_background_image(theme->get_image(34),1,2);
	_reagent_disk_tests_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_reagent_disk_tests_list->InsertColumn(0,theme->get_string(IDS_STRING123),LVCFMT_LEFT,150);
	_reagent_disk_tests_list->InsertColumn(1,theme->get_string(IDS_STRING124),LVCFMT_LEFT,180);
	_reagent_disk_tests_list->InsertColumn(2,theme->get_string(IDS_STRING125),LVCFMT_LEFT,120);
	_reagent_disk_tests_list->InsertColumn(3,theme->get_string(IDS_STRING126),LVCFMT_LEFT,120);
	_reagent_disk_tests_list->InsertColumn(4,theme->get_string(IDS_STRING127),LVCFMT_LEFT,180);
	_reagent_disk_tests_list->InsertColumn(5,theme->get_string(IDS_STRING128),LVCFMT_LEFT,180);
	_reagent_disk_tests_list->set_item_count(20);
	_reagent_disk_idle_position_list->set_item_text_color(255,50,50,50);
	_reagent_disk_idle_position_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_reagent_disk_idle_position_list->load_item_background_image(theme->get_image(33),1,4);
	_reagent_disk_idle_position_list->set_item_background_image_stretching_factors(3,3,3,3);
	_reagent_disk_idle_position_list->set_header_item_text_color(255,255,255,255);
	_reagent_disk_idle_position_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_reagent_disk_idle_position_list->load_header_item_background_image(theme->get_image(34),1,2);
	_reagent_disk_idle_position_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_reagent_disk_idle_position_list->InsertColumn(0,theme->get_string(IDS_STRING129),LVCFMT_LEFT,80);
	_reagent_disk_idle_position_list->InsertColumn(1,theme->get_string(IDS_STRING130),LVCFMT_LEFT,80);
	_reagent_disk_idle_position_list->set_item_count(20);
	//2-2.初始化静态文本框。
	_reagent_disk_idle_position_static->set_text_color(255,255,255,255);
	_reagent_disk_idle_position_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_reagent_disk_idle_position_static->load_background_image(theme->get_image(25));
	_reagent_disk_idle_position_static->set_background_image_stretching_factors(10,29,10,2);
	_manual_setting_static->set_text_color(255,50,50,50);
	_manual_setting_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	_over_ride_manual_setting_static->set_text_color(255,50,50,50);
	_over_ride_manual_setting_static->set_text_alignment(MtImageStatic::ALIGNMENT_LEFT|
		MtImageStatic::ALIGNMENT_VCENTER);
	//2-3.初始化按钮。
	_details_button->set_text_color(255,50,50,50);
	_details_button->load_background_image(theme->get_image(32),1,4);
	_details_button->set_background_image_stretching_factors(5,5,5,5);
	_manual_setting_button->set_text_color(255,50,50,50);
	_manual_setting_button->load_background_image(theme->get_image(32),1,4);
	_manual_setting_button->set_background_image_stretching_factors(5,5,5,5);
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	_ise_reagent_remaining_volumes_button->set_text_color(255,50,50,50);
	_ise_reagent_remaining_volumes_button->load_background_image(theme->get_image(32),1,4);
	_ise_reagent_remaining_volumes_button->set_background_image_stretching_factors(5,5,5,5);
	_barcode_button->set_text_color(255,50,50,50);
	_barcode_button->load_background_image(theme->get_image(32),1,4);
	_barcode_button->set_background_image_stretching_factors(5,5,5,5);
	_level_button->set_text_color(255,50,50,50);
	_level_button->load_background_image(theme->get_image(32),1,4);
	_level_button->set_background_image_stretching_factors(5,5,5,5);
	_volume_reset_button->set_text_color(255,50,50,50);
	_volume_reset_button->load_background_image(theme->get_image(32),1,4);
	_volume_reset_button->set_background_image_stretching_factors(5,5,5,5);
	_item_sort_button->set_text_color(255,50,50,50);
	_item_sort_button->load_background_image(theme->get_image(32),1,4);
	_item_sort_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化布局。
	//3-1.初始化子布局1。
	_child_layout_1->add_layout(_child_layout_4,1);
	_child_layout_1->add_spacing(10);
	_child_layout_1->add_fixed_layout(_child_layout_2,220);
	//3-2.初始化子布局2。
	_child_layout_2->set_margin(15,40,15,15);
	_child_layout_2->add_window(_reagent_disk_idle_position_list,1);
	//3-3.初始化子布局3。
	_child_layout_3->add_window(_manual_setting_static,1);
	_child_layout_3->add_window(_over_ride_manual_setting_static,1);
	//3-4.初始化子布局4。
	_child_layout_4->add_window(_reagent_disk_tests_list,1);
	_child_layout_4->add_fixed_layout(_child_layout_3,30);
	//3-5.初始化子布局5。
	_child_layout_5->add_window(_details_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_manual_setting_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_delete_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_ise_reagent_remaining_volumes_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_barcode_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_level_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_volume_reset_button,1);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_item_sort_button,1);
	//3-6.初始化主布局。
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_layout(_child_layout_1,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_5,50);
	//_main_layout->add_spacing(10);
	//3-7.调整主布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//4.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_1->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_reagent_disk_idle_position_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogReagentSetting::draw_boder(MtBitmap &memory_bitmap){
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