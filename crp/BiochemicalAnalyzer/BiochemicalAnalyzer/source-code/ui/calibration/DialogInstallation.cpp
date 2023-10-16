// source-code/ui/calibration/DialogInstallation.cpp : implementation file
//

#include"stdafx.h"
#include"DialogInstallation.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/control/MtComplexListCtrl.h"

//DialogInstallation dialog

IMPLEMENT_DYNAMIC(DialogInstallation,DialogBase)

/**
 * name: DialogInstallation
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogInstallation::DialogInstallation(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogInstallation::IDD,pParent)
	,_calibrators_list(new MtComplexListCtrl)
	,_concentrations_list(new MtComplexListCtrl)
	,_edit_calibrator_button(new MtImageButton)
	,_edit_concentrations_button(new MtImageButton)
	,_delete_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogInstallation
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogInstallation::~DialogInstallation(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _calibrators_list;
	delete _concentrations_list;
	delete _edit_calibrator_button;
	delete _edit_concentrations_button;
	delete _delete_button;
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogInstallation::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_CALIBRATORS,*_calibrators_list);
	DDX_Control(pDX,IDC_LIST_CONCENTRATIONS,*_concentrations_list);
	DDX_Control(pDX,IDC_BUTTON_EDIT_CALIBRATOR,*_edit_calibrator_button);
	DDX_Control(pDX,IDC_BUTTON_EDIT_CONCENTRATIONS,*_edit_concentrations_button);
	DDX_Control(pDX,IDC_BUTTON_DELETE,*_delete_button);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogInstallation::OnInitDialog(){
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
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogInstallation::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogInstallation,DialogBase)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// DialogInstallation message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogInstallation::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogInstallation::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始话对话框中控件。
	//2-1.初始化当前对话框中列表框控件。
	_calibrators_list->set_item_text_color(255,50,50,50);
	_calibrators_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_calibrators_list->load_item_background_image(theme->get_image(33),1,4);
	_calibrators_list->set_item_background_image_stretching_factors(3,3,3,3);
	_calibrators_list->set_header_item_text_color(255,255,255,255);
	_calibrators_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_calibrators_list->load_header_item_background_image(theme->get_image(34),1,2);
	_calibrators_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_calibrators_list->InsertColumn(0,theme->get_string(IDS_STRING136),LVCFMT_LEFT,130);
	_calibrators_list->InsertColumn(1,theme->get_string(IDS_STRING137),LVCFMT_LEFT,130);
	_calibrators_list->InsertColumn(2,theme->get_string(IDS_STRING138),LVCFMT_LEFT,130);
	_calibrators_list->set_item_count(20);
	_concentrations_list->set_item_text_color(255,50,50,50);
	_concentrations_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_concentrations_list->load_item_background_image(theme->get_image(33),1,4);
	_concentrations_list->set_item_background_image_stretching_factors(3,3,3,3);
	_concentrations_list->set_header_item_text_color(255,255,255,255);
	_concentrations_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_concentrations_list->load_header_item_background_image(theme->get_image(34),1,2);
	_concentrations_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_concentrations_list->InsertColumn(0,theme->get_string(IDS_STRING139),LVCFMT_LEFT,130);
	_concentrations_list->InsertColumn(1,theme->get_string(IDS_STRING140),LVCFMT_LEFT,130);
	_concentrations_list->InsertColumn(2,theme->get_string(IDS_STRING141),LVCFMT_LEFT,130);
	_concentrations_list->set_item_count(20);
	//2-2.初始化对话框中按钮。
	_edit_calibrator_button->set_text_color(255,50,50,50);
	_edit_calibrator_button->load_background_image(theme->get_image(32),1,4);
	_edit_calibrator_button->set_background_image_stretching_factors(5,5,5,5);
	_edit_concentrations_button->set_text_color(255,50,50,50);
	_edit_concentrations_button->load_background_image(theme->get_image(32),1,4);
	_edit_concentrations_button->set_background_image_stretching_factors(5,5,5,5);
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化对话框中布局。
	//3-1.初始化子布局1。
	_child_layout_1->add_window(_calibrators_list,1);
	_child_layout_1->add_spacing(5);
	_child_layout_1->add_window(_concentrations_list,1);
	//_child_layout_1->add_stretch(1);
	//3-2.初始化子布局2。
	_child_layout_2->add_fixed_window(_edit_calibrator_button,150);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_edit_concentrations_button,150);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_delete_button,150);
	_child_layout_2->add_stretch(1);
	//3-3.初始化对话框中主布局。
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_layout(_child_layout_1,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_2,50);
	_main_layout->add_spacing(10);
	//3-4.调整当前对话框布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogInstallation::draw_boder(MtBitmap &memory_bitmap){
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