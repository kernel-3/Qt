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
 * brief: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
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
 * brief: ����������
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
 * brief: ֧��DDX/DDV
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
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogTestSelection::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	///////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի����пؼ���
	init_controls();
	///////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * name: draw
 * brief: �Ի���������⺯����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - �Ի���Ļ�ͼDC��
 * return: --
 */
void DialogTestSelection::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.���û�����Ӧ�������ƶԻ��򱳾���
	DialogBase::draw(memory_bitmap,dc);
	//2.���ƶԻ���߿�
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogTestSelection,DialogBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_RADIO_ROUTINE,IDC_RADIO_QC,&DialogTestSelection::OnRadioBoxesClicked)
END_MESSAGE_MAP()

/**
 * name: OnSize
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogTestSelection::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.������ǰ�����ֵĳߴ硣
	_main_layout->resize(cx,cy);
	//2.��Ϊ���ڲ����޷��������������ڴ��ֶ����䲼�֡�
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
 * brief: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogTestSelection::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.����������Ϣ�ӶԻ���
	for(unsigned int index=0;index!=
		SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT;++index){
		if(IsWindow(_specimen_information_child_dialogs[index].GetSafeHwnd())){
			_specimen_information_child_dialogs[index].DestroyWindow();
		}
	}
	//2.������Ŀ����ϼ��ӶԻ���
	_item_and_profile_keys_child_dialog->DestroyWindow();
}

/**
 * name: OnRadioBoxesClicked
 * brief: �����ѡ������Ϣ��Ӧ������
 * param: ID - ��ǰ����ĵ�ѡ��ؼ�ID��
 * return: --
 */
void DialogTestSelection::OnRadioBoxesClicked(const unsigned int ID){
	//1.�����ǰ����ĵ�ѡ��Ϊ�����桱��ѡ��
	if(ID==IDC_RADIO_ROUTINE){
		//1-1.�жϵ�ǰ�����桱��ѡ���Ƿ��ѱ�ѡ�С�
		if(_routine_radio_box->get_checked()){
			return;
		}
		//1-2.����������ѡ��״̬��
		_routine_radio_box->set_checked(TRUE);
		_emergency_radio_box->set_checked(FALSE);
		_qc_radio_box->set_checked(FALSE);
		//1-3.��ʾ�����кų���������Ϣ���ӶԻ���
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_ROUTINE);
	}
	//2.�����ǰ����ĵ�ѡ��Ϊ�������ѡ��
	else if(ID==IDC_RADIO_EMERGENCY){
		//2-1.�жϵ�ǰ�������ѡ���Ƿ��ѱ�ѡ�С�
		if(_emergency_radio_box->get_checked()){
			return;
		}
		//2-2.����������ѡ��״̬��
		_routine_radio_box->set_checked(FALSE);
		_emergency_radio_box->set_checked(TRUE);
		_qc_radio_box->set_checked(FALSE);
		//2-3.��ʾ�����кż���������Ϣ���ӶԻ���
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_SEQUENCE_EMERGENCY);
	}
	//3.�����ǰ����ĵ�ѡ��Ϊ���ʿء���ѡ��
	else{
		//3-1.�жϵ�ǰ���ʿء���ѡ���Ƿ��ѱ�ѡ�С�
		if(_qc_radio_box->get_checked()){
			return;
		}
		//3-2.����������ѡ��״̬��
		_routine_radio_box->set_checked(FALSE);
		_emergency_radio_box->set_checked(FALSE);
		_qc_radio_box->set_checked(TRUE);
		//3-3.��ʾ���ʿ�������Ϣ���ӶԻ���
		show_specimen_information_child_dialog(
			SPECIMEN_INFORMATION_CHILD_DIALOG_ID_QC);
	}
}

/**
 * name: init_controls
 * brief: ��ʼ����ǰ�Ի����пؼ���
 * param: --
 * return: --
 */
void DialogTestSelection::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ����ǰ�Ի����а�ť�ؼ���
	//��̬�ı���
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
	//��ѡ��
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
	//��ť
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
	//�ӶԻ���
	_item_and_profile_keys_child_dialog->Create(DialogItemAndProfileKeys::IDD,this);
	//3.��ʼ����ǰ�Ի����еĲ��֡�
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
	//4.Ŀǰ�����޷�֧�ֱ���������ڴ��ֶ��ƶ���
	MtLayout::IntRect rect_t;
	if((_child_layout_3->get_item_rect(0,rect_t)>=0)&&(rect_t.is_valid())){
		_test_type_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	if((_child_layout_3->get_item_rect(4,rect_t)>=0)&&(rect_t.is_valid())){
		_specimen_status_static->MoveWindow(rect_t.get_left(),rect_t.get_top(),
			rect_t.get_width(),rect_t.get_height());
	}
	//5.�����¼�����ʾ��Ӧ�ӽ��档
	OnRadioBoxesClicked(IDC_RADIO_ROUTINE);
	_item_and_profile_keys_child_dialog->ShowWindow(SW_SHOW);
}

/**
 * name: draw_boder
 * brief: ���ƶԻ���߿�
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogTestSelection::draw_boder(MtBitmap &memory_bitmap){
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

/**
 * name: show_specimen_information_child_dialog
 * brief: ��ʾ������Ϣ�ӶԻ���
 * param: child_dialog_id - ������ʾ���ӶԻ���ID��
 * return: --
 */
void DialogTestSelection::show_specimen_information_child_dialog(
	const SpecimenInformationChildDialogID child_dialog_id){
	//1.�����ǰ������ʾ���ӶԻ���ID�Ƿ�����ֱ�ӷ��ء�
	if(SPECIMEN_INFORMATION_CHILD_DIALOG_ID_UNKNOWN==child_dialog_id){
		return;
	}
	//2.�����ǰ������ʾ���ӶԻ����뵱ǰ��ʾ���ӶԻ���һ�£���ֱ�ӷ��ء�
	if(child_dialog_id==_current_specimen_information_child_dialog){
		return;
	}
	//3.�����ǰ������Ϣ�ӶԻ�����δ����������д���������
	if(!IsWindow(_specimen_information_child_dialogs[child_dialog_id].GetSafeHwnd())){
		if(!_specimen_information_child_dialogs[child_dialog_id].Create(
			DialogSpecimenInformation::IDD,this)){
			return;
		}
	}
	//4.������ǰ������ʾ��������Ϣ�ӶԻ���ߴ硣
	//4-1.��ȡ��ǰ������Ϣ�ӶԻ���Ӧ����ʾ�ĳߴ�,�����жϻ�ȡ�Ƿ�ɹ���
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(2,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4-2.������ǰ������ʾ��������Ϣ�ӶԻ���ߴ硣
	_specimen_information_child_dialogs[child_dialog_id].MoveWindow(
		rect.get_left(),rect.get_top(),rect.get_width(),rect.get_height());
	//4-3.����ǰ������ʾ���ӶԻ�����벼�ֹ����У������жϲ����Ƿ�ɹ���
	if(_child_layout_3->set_item_window(2,&_specimen_information_child_dialogs[
		child_dialog_id],1)<0){
		return;
	}
	//5.�������е�������Ϣ�ӶԻ���
	for(unsigned int index=0;index!=SPECIMEN_INFORMATION_CHILD_DIALOG_AMOUNT;++index){
		if(IsWindow(_specimen_information_child_dialogs[index].GetSafeHwnd())){
			_specimen_information_child_dialogs[index].ShowWindow(SW_HIDE);
		}
	}
	//6.��ʾ��ǰ������ʾ��������Ϣ�ӶԻ���
	_specimen_information_child_dialogs[child_dialog_id].ShowWindow(SW_SHOW);
	//7.��¼��ǰ��ʾ��������Ϣ�ӶԻ���
	_current_specimen_information_child_dialog=child_dialog_id;
}