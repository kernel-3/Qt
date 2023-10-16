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
 * brief: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
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
 * brief: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
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
 * breif: ֧��DDX/DDV
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
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogInstallation::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի���ؼ���
	init_controls();
	////////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: draw
 * brief: �Ի���������⺯����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - �Ի����ͼDC��
 * return: --
 */
void DialogInstallation::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.���û�����Ӧ�������ƶԻ��򱳾���
	DialogBase::draw(memory_bitmap,dc);
	//2.���ƶԻ���߿�
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogInstallation,DialogBase)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// DialogInstallation message handlers

/**
 * name: OnSize
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogInstallation::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: init_controls
 * brief: ��ʼ����ǰ�Ի����пؼ���
 * param: --
 * return: --
 */
void DialogInstallation::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ���Ի����пؼ���
	//2-1.��ʼ����ǰ�Ի������б��ؼ���
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
	//2-2.��ʼ���Ի����а�ť��
	_edit_calibrator_button->set_text_color(255,50,50,50);
	_edit_calibrator_button->load_background_image(theme->get_image(32),1,4);
	_edit_calibrator_button->set_background_image_stretching_factors(5,5,5,5);
	_edit_concentrations_button->set_text_color(255,50,50,50);
	_edit_concentrations_button->load_background_image(theme->get_image(32),1,4);
	_edit_concentrations_button->set_background_image_stretching_factors(5,5,5,5);
	_delete_button->set_text_color(255,50,50,50);
	_delete_button->load_background_image(theme->get_image(32),1,4);
	_delete_button->set_background_image_stretching_factors(5,5,5,5);
	//3.��ʼ���Ի����в��֡�
	//3-1.��ʼ���Ӳ���1��
	_child_layout_1->add_window(_calibrators_list,1);
	_child_layout_1->add_spacing(5);
	_child_layout_1->add_window(_concentrations_list,1);
	//_child_layout_1->add_stretch(1);
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_edit_calibrator_button,150);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_edit_concentrations_button,150);
	_child_layout_2->add_spacing(5);
	_child_layout_2->add_fixed_window(_delete_button,150);
	_child_layout_2->add_stretch(1);
	//3-3.��ʼ���Ի����������֡�
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(5);
	_main_layout->add_layout(_child_layout_1,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_2,50);
	_main_layout->add_spacing(10);
	//3-4.������ǰ�Ի��򲼾ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: draw_boder
 * brief: ���ƶԻ���߿�
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogInstallation::draw_boder(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���ı߿�ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(24);
	//2.�����ǰ�Ի���߿�ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի���߿�λ����Ϣ��
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height());
}