//DialogDataReview.cpp : implementation file
//
#include"stdafx.h"
#include"DialogDataReview.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtComplexListCtrl.h"

//DialogDataReview dialog
IMPLEMENT_DYNAMIC(DialogDataReview,DialogBase)

/**
 * name: DialogDataReview
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogDataReview::DialogDataReview(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogDataReview::IDD,pParent)
	,_display_options_static(new MtImageStatic)
	,_data_source_static(new MtImageStatic)
	,_specimen_record_count_static(new MtImageStatic)
	,_specimen_record_count_value_static(new MtImageStatic)
	,_all_entries_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_search_results_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_current_data_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_history_data_radio_box(new MtImageRadioBox(MtImageRadioBox::TYPE_RADIO_BOX))
	,_specimen_data_list(new MtComplexListCtrl)
	,_item_data_list(new MtComplexListCtrl)
	,_demographics_button(new MtImageButton)
	,_send_to_host_button(new MtImageButton)
	,_reaction_monitor_button(new MtImageButton)
	,_rerun_ts_button(new MtImageButton)
	,_update_results_button(new MtImageButton)
	,_refresh_button(new MtImageButton)
	,_search_button(new MtImageButton)
	,_sort_button(new MtImageButton)
	,_delete_record_button(new MtImageButton)
	,_edit_test_result_button(new MtImageButton)
	,_replace_result_button(new MtImageButton)
	,_backup_button(new MtImageButton)
	,_batch_delete_button(new MtImageButton)
	,_child_layout_1(new MtVerticalLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtVerticalLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_child_layout_6(new MtHorizonLayout)
	,_child_layout_7(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogDataReview
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogDataReview::~DialogDataReview(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	delete _child_layout_6;
	delete _child_layout_7;
	delete _display_options_static;
	delete _data_source_static;
	delete _specimen_record_count_static;
	delete _specimen_record_count_value_static;
	delete _all_entries_radio_box;
	delete _search_results_radio_box;
	delete _current_data_radio_box;
	delete _history_data_radio_box;
	delete _specimen_data_list;
	delete _item_data_list;
	delete _demographics_button;
	delete _send_to_host_button;
	delete _reaction_monitor_button;
	delete _rerun_ts_button;
	delete _update_results_button;
	delete _refresh_button;
	delete _search_button;
	delete _sort_button;
	delete _delete_record_button;
	delete _edit_test_result_button;
	delete _replace_result_button;
	delete _backup_button;
	delete _batch_delete_button;
}

/**
 * name: DoDataExchange
 * brief: 支持DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogDataReview::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_DISPLAY_OPTIONS,*_display_options_static);
	DDX_Control(pDX,IDC_STATIC_DATA_SOURCE,*_data_source_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_RECORD_COUNT,*_specimen_record_count_static);
	DDX_Control(pDX,IDC_STATIC_SPECIMEN_RECORD_COUNT_VALUE,*_specimen_record_count_value_static);
	DDX_Control(pDX,IDC_RADIO_ALL_ENTRIES,*_all_entries_radio_box);
	DDX_Control(pDX,IDC_RADIO_SEARCH_RESULTS,*_search_results_radio_box);
	DDX_Control(pDX,IDC_RADIO_CURRENT_DATA,*_current_data_radio_box);
	DDX_Control(pDX,IDC_RADIO_HISTORY_DATA,*_history_data_radio_box);
	DDX_Control(pDX,IDC_LIST_SPECIMEN_DATA,*_specimen_data_list);
	DDX_Control(pDX,IDC_LIST_ITEM_DATA,*_item_data_list);
	DDX_Control(pDX,IDC_BUTTON_DEMOGRAPHICS,*_demographics_button);
	DDX_Control(pDX,IDC_BUTTON_SEND_TO_HOST,*_send_to_host_button);
	DDX_Control(pDX,IDC_BUTTON_REACTION_MONITOR,*_reaction_monitor_button);
	DDX_Control(pDX,IDC_BUTTON_RERUN_TS,*_rerun_ts_button);
	DDX_Control(pDX,IDC_BUTTON_UPDATE_RESULTS,*_update_results_button);
	DDX_Control(pDX,IDC_BUTTON_REFRESH,*_refresh_button);
	DDX_Control(pDX,IDC_BUTTON_SERACH,*_search_button);
	DDX_Control(pDX,IDC_BUTTON_SORT,*_sort_button);
	DDX_Control(pDX,IDC_BUTTON_DELETE_RECORD,*_delete_record_button);
	DDX_Control(pDX,IDC_BUTTON_EDIT_TEST_RESULT,*_edit_test_result_button);
	DDX_Control(pDX,IDC_BUTTON_REPLACE_RESULT,*_replace_result_button);
	DDX_Control(pDX,IDC_BUTTON_BACKUP,*_backup_button);
	DDX_Control(pDX,IDC_BUTTON_BATCH_DELETE,*_batch_delete_button);
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数。
 * param: memory_bitmap - 对话框内存位图。
 *        dc - 对话框的绘图DC。
 * return: --
 */
void DialogDataReview::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框边框。
	draw_boder(memory_bitmap);
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogDataReview::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.初始化当前对话框控件。
	init_controls();
	////////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogDataReview,DialogBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO_ALL_ENTRIES,&DialogDataReview::OnBnClickedRadioAllEntries)
	ON_BN_CLICKED(IDC_RADIO_SEARCH_RESULTS,&DialogDataReview::OnBnClickedRadioSearchResults)
	ON_BN_CLICKED(IDC_RADIO_CURRENT_DATA,&DialogDataReview::OnBnClickedRadioCurrentData)
	ON_BN_CLICKED(IDC_RADIO_HISTORY_DATA,&DialogDataReview::OnBnClickedRadioHistoryData)
END_MESSAGE_MAP()

// DialogDataReview message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogDataReview::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
	//2.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_4->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_display_options_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_4->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_data_source_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_4->get_item_rect(4,rect_t)>=0)&&(rect_t.is_valid())){
		_specimen_record_count_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: OnBnClickedRadioAllEntries
 * brief: 用户点击“所有输入”单选框消息响应函数。
 * param: --
 * return: --
 */
void DialogDataReview::OnBnClickedRadioAllEntries(){
	// TODO: Add your control notification handler code here
	if(_all_entries_radio_box->get_checked()){
		return;
	}else{
		_all_entries_radio_box->set_checked(TRUE);
		_search_results_radio_box->set_checked(FALSE);
	}
}

/**
 * name: OnBnClickedRadioSearchResults
 * brief: 用户点击“查找结果”单选框消息响应函数。
 * param: --
 * return: --
 */
void DialogDataReview::OnBnClickedRadioSearchResults(){
	// TODO: Add your control notification handler code here
	if(_search_results_radio_box->get_checked()){
		return;
	}else{
		_search_results_radio_box->set_checked(TRUE);
		_all_entries_radio_box->set_checked(FALSE);
	}
}

/**
 * name: OnBnClickedRadioCurrentData
 * breif: 用户点击“当前数据”单选框消息相应函数。
 * param: --
 * return: --
 */
void DialogDataReview::OnBnClickedRadioCurrentData(){
	// TODO: Add your control notification handler code here
	if(_current_data_radio_box->get_checked()){
		return;
	}else{
		_current_data_radio_box->set_checked(TRUE);
		_history_data_radio_box->set_checked(FALSE);
	}
}

/**
 * name: OnBnClickedRadioHistoryData
 * breif: 用户点击“历史数据”单选框消息相应函数。
 * param: --
 * return: --
 */
void DialogDataReview::OnBnClickedRadioHistoryData(){
	// TODO: Add your control notification handler code here
	if(_history_data_radio_box->get_checked()){
		return;
	}else{
		_history_data_radio_box->set_checked(TRUE);
		_current_data_radio_box->set_checked(FALSE);
	}
}

/**
 * name: init_controls
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogDataReview::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化当前对话框中控件。
	//2-1.初始化当前对话框中静态文本框。
	_display_options_static->set_text_color(255,255,255,255);
	_display_options_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_display_options_static->load_background_image(theme->get_image(25));
	_display_options_static->set_background_image_stretching_factors(10,29,10,2);
	_data_source_static->set_text_color(255,255,255,255);
	_data_source_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_data_source_static->load_background_image(theme->get_image(25));
	_data_source_static->set_background_image_stretching_factors(10,29,10,2);
	_specimen_record_count_static->set_text_color(255,255,255,255);
	_specimen_record_count_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_TOP);
	_specimen_record_count_static->load_background_image(theme->get_image(25));
	_specimen_record_count_static->set_background_image_stretching_factors(10,29,10,2);
	_specimen_record_count_value_static->set_text_color(255,50,50,50);
	_specimen_record_count_value_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.初始化当前对话框中单选框。
	_all_entries_radio_box->set_text_color(255,50,50,50);
	_all_entries_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_all_entries_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_all_entries_radio_box->load_background_image(theme->get_image(1),1,6);
	_search_results_radio_box->set_text_color(255,50,50,50);
	_search_results_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_search_results_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_search_results_radio_box->load_background_image(theme->get_image(1),1,6);
	_current_data_radio_box->set_text_color(255,50,50,50);
	_current_data_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_current_data_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_current_data_radio_box->load_background_image(theme->get_image(1),1,6);
	_history_data_radio_box->set_text_color(255,50,50,50);
	_history_data_radio_box->load_foreground_image(theme->get_image(26),1,6);
	_history_data_radio_box->set_foreground_image_alignment(MtImageRadioBox::ALIGNMENT_LEFT|
		MtImageRadioBox::ALIGNMENT_VCENTER);
	_history_data_radio_box->load_background_image(theme->get_image(1),1,6);
	//2-3.初始化列表框。
	_specimen_data_list->set_item_text_color(255,50,50,50);
	_specimen_data_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_specimen_data_list->load_item_background_image(theme->get_image(33),1,4);
	_specimen_data_list->set_item_background_image_stretching_factors(3,3,3,3);
	_specimen_data_list->set_header_item_text_color(255,255,255,255);
	_specimen_data_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_specimen_data_list->load_header_item_background_image(theme->get_image(34),1,2);
	_specimen_data_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_specimen_data_list->InsertColumn(0,theme->get_string(IDS_STRING113),LVCFMT_LEFT,75);
	_specimen_data_list->InsertColumn(1,theme->get_string(IDS_STRING114),LVCFMT_LEFT,100);
	_specimen_data_list->InsertColumn(2,theme->get_string(IDS_STRING115),LVCFMT_LEFT,100);
	_specimen_data_list->InsertColumn(3,theme->get_string(IDS_STRING116),LVCFMT_LEFT,100);
	_specimen_data_list->InsertColumn(4,theme->get_string(IDS_STRING117),LVCFMT_LEFT,100);
	_specimen_data_list->InsertColumn(5,theme->get_string(IDS_STRING118),LVCFMT_LEFT,200);
	_specimen_data_list->InsertColumn(6,theme->get_string(IDS_STRING119),LVCFMT_LEFT,100);
	_specimen_data_list->set_item_count(10);
	_item_data_list->set_item_text_color(255,50,50,50);
	_item_data_list->set_item_text_alignment(MtImageListCtrl::ALIGNMENT_LEFT|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_item_data_list->load_item_background_image(theme->get_image(33),1,4);
	_item_data_list->set_item_background_image_stretching_factors(3,3,3,3);
	_item_data_list->set_header_item_text_color(255,255,255,255);
	_item_data_list->set_header_item_text_alignment(MtImageListCtrl::ALIGNMENT_HCENTER|
		MtImageListCtrl::ALIGNMENT_VCENTER);
	_item_data_list->load_header_item_background_image(theme->get_image(34),1,2);
	_item_data_list->set_header_item_background_image_stretching_factors(3,3,3,3);
	_item_data_list->InsertColumn(0,theme->get_string(IDS_STRING120),LVCFMT_LEFT,120);
	_item_data_list->InsertColumn(1,theme->get_string(IDS_STRING121),LVCFMT_LEFT,120);
	_item_data_list->InsertColumn(2,theme->get_string(IDS_STRING122),LVCFMT_LEFT,120);
	_item_data_list->set_item_count(10);
	//2-4.初始化按钮。
	_demographics_button->set_text_color(255,50,50,50);
	_demographics_button->load_background_image(theme->get_image(32),1,4);
	_demographics_button->set_background_image_stretching_factors(5,5,5,5);
	_send_to_host_button->set_text_color(255,50,50,50);
	_send_to_host_button->load_background_image(theme->get_image(32),1,4);
	_send_to_host_button->set_background_image_stretching_factors(5,5,5,5);
	_reaction_monitor_button->set_text_color(255,50,50,50);
	_reaction_monitor_button->load_background_image(theme->get_image(32),1,4);
	_reaction_monitor_button->set_background_image_stretching_factors(5,5,5,5);
	_rerun_ts_button->set_text_color(255,50,50,50);
	_rerun_ts_button->load_background_image(theme->get_image(32),1,4);
	_rerun_ts_button->set_background_image_stretching_factors(5,5,5,5);
	_update_results_button->set_text_color(255,50,50,50);
	_update_results_button->load_background_image(theme->get_image(32),1,4);
	_update_results_button->set_background_image_stretching_factors(5,5,5,5);
	_refresh_button->set_text_color(255,50,50,50);
	_refresh_button->load_background_image(theme->get_image(32),1,4);
	_refresh_button->set_background_image_stretching_factors(5,5,5,5);
	_search_button->set_text_color(255,50,50,50);
	_search_button->load_background_image(theme->get_image(32),1,4);
	_search_button->set_background_image_stretching_factors(5,5,5,5);
	_sort_button->set_text_color(255,50,50,50);
	_sort_button->load_background_image(theme->get_image(32),1,4);
	_sort_button->set_background_image_stretching_factors(5,5,5,5);
	_delete_record_button->set_text_color(255,50,50,50);
	_delete_record_button->load_background_image(theme->get_image(32),1,4);
	_delete_record_button->set_background_image_stretching_factors(5,5,5,5);
	_edit_test_result_button->set_text_color(255,50,50,50);
	_edit_test_result_button->load_background_image(theme->get_image(32),1,4);
	_edit_test_result_button->set_background_image_stretching_factors(5,5,5,5);
	_replace_result_button->set_text_color(255,50,50,50);
	_replace_result_button->load_background_image(theme->get_image(32),1,4);
	_replace_result_button->set_background_image_stretching_factors(5,5,5,5);
	_backup_button->set_text_color(255,50,50,50);
	_backup_button->load_background_image(theme->get_image(32),1,4);
	_backup_button->set_background_image_stretching_factors(5,5,5,5);
	_batch_delete_button->set_text_color(255,50,50,50);
	_batch_delete_button->load_background_image(theme->get_image(32),1,4);
	_batch_delete_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化布局。
	//3-1.初始化子布局1。
	_child_layout_1->set_margin(10,35,10,10);
	_child_layout_1->add_window(_all_entries_radio_box,1);
	_child_layout_1->add_spacing(1);
	_child_layout_1->add_window(_search_results_radio_box,1);
	//3-2.初始化子布局2。
	_child_layout_2->set_margin(10,35,10,10);
	_child_layout_2->add_fixed_window(_current_data_radio_box,150);
	_child_layout_2->add_spacing(1);
	_child_layout_2->add_fixed_window(_history_data_radio_box,150);
	_child_layout_2->add_stretch(1);
	//3-3.初始化子布局3。
	_child_layout_3->set_margin(10,30,10,10);
	_child_layout_3->add_window(_specimen_record_count_value_static,1);
	//3-4.初始化子布局4。
	_child_layout_4->add_fixed_layout(_child_layout_1,130);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_fixed_layout(_child_layout_2,350);
	_child_layout_4->add_spacing(5);
	_child_layout_4->add_fixed_layout(_child_layout_3,200);
	_child_layout_4->add_stretch(1);
	//3-5.初始化子布局5。
	_child_layout_5->add_window(_specimen_data_list,2);
	_child_layout_5->add_spacing(5);
	_child_layout_5->add_window(_item_data_list,1);
	//3-6.初始化子布局6。
	_child_layout_6->add_window(_demographics_button,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_send_to_host_button,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_reaction_monitor_button,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_rerun_ts_button,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_update_results_button,1);
	_child_layout_6->add_spacing(5);
	_child_layout_6->add_window(_refresh_button,1);
	//3-7.初始化子布局7。
	_child_layout_7->add_window(_search_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_sort_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_delete_record_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_edit_test_result_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_replace_result_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_backup_button,1);
	_child_layout_7->add_spacing(5);
	_child_layout_7->add_window(_batch_delete_button,1);
	_child_layout_7->add_spacing(5);
	//3-6.初始化主布局。
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_4,100);
	_main_layout->add_spacing(5);
	_main_layout->add_layout(_child_layout_5,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_6,40);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_7,40);
	_main_layout->add_spacing(10);
	//3-6.调整当前主布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//4.目前布局无法支持标题框，所以在此手动移动。
	MtLayout::IntRect rect_t;
	if((_child_layout_4->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_display_options_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_4->get_item_rect(2,rect_t)>=0)&&(rect_t.is_valid())){
		_data_source_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_4->get_item_rect(4,rect_t)>=0)&&(rect_t.is_valid())){
		_specimen_record_count_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
}

/**
 * name: draw_boder
 * brief: 绘制对话框边框。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogDataReview::draw_boder(MtBitmap &memory_bitmap){
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