//source-code/ui/common/DialogMessageBox.cpp : implementation file
//

#include"stdafx.h"
#include"DialogMessageBox.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"

//DialogMessageBox dialog

IMPLEMENT_DYNAMIC(DialogMessageBox,DialogModalBase)

/**
 * name: DialogMessageBox
 * brief: ���캯����
 * param: title - �Ի�����⡣
 *        width - �Ի����ȡ�
 *        height - �Ի���߶ȡ�
 *        image_no - ͼƬ��š�
 *        message - ��ʾ����Ϣ��
 *        operation_1_name - ����1�����ơ�
 *        operation_2_name - ����2�����ơ�
 *		  pParent - ָ�򸸴���ָ�롣
 * return: --
 */
DialogMessageBox::DialogMessageBox(const CString &title,const int width,
	const int height,const int image_no,const CString &message,
	const CString &operation_1_name,const CString &operation_2_name,
	const CString &operation_3_name,CWnd *pParent/*=NULL*/)
	:DialogModalBase(DialogMessageBox::IDD,pParent)
	,_title(title)
	,_width(width)
	,_height(height)
	,_image_no(image_no)
	,_message(message)
	,_operation_1_name(operation_1_name)
	,_operation_2_name(operation_2_name)
	,_operation_3_name(operation_3_name)
	,_image_static(new MtImageStatic)
	,_message_static(new MtImageStatic)
	,_operation_1_button(new MtImageButton)
	,_operation_2_button(new MtImageButton)
	,_operation_3_button(new MtImageButton)
	,_child_layout_1(new MtVerticalLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogMessageBox
 * brief: ����������
 * param: --
 * return: --
 */
DialogMessageBox::~DialogMessageBox(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _image_static;
	delete _message_static;
	delete _operation_1_button;
	delete _operation_2_button;
	delete _operation_3_button;
}

/**
 * name: DoDataExchange
 * brief: ֧��DDX/DDV��
 * param: --
 * return: --
 */
void DialogMessageBox::DoDataExchange(CDataExchange *pDX){
	DialogModalBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_IMAGE,*_image_static);
	DDX_Control(pDX,IDC_STATIC_MESSAGE,*_message_static);
	DDX_Control(pDX,IDC_BUTTON_OPERATION_1,*_operation_1_button);
	DDX_Control(pDX,IDC_BUTTON_OPERATION_2,*_operation_2_button);
	DDX_Control(pDX,IDC_BUTTON_OPERATION_3,*_operation_3_button);
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE�� 
 */
BOOL DialogMessageBox::OnInitDialog(){
	DialogModalBase::OnInitDialog();
	//TODO: Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի��򴰿ڡ�
	init_window();
	//2.��ʼ���Ի����пؼ���
	init_controls();
	////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogMessageBox,DialogModalBase)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OPERATION_1,&DialogMessageBox::OnBnClickedButtonOperation1)
	ON_BN_CLICKED(IDC_BUTTON_OPERATION_2,&DialogMessageBox::OnBnClickedButtonOperation2)
	ON_BN_CLICKED(IDC_BUTTON_OPERATION_3,&DialogMessageBox::OnBnClickedButtonOperation3)
END_MESSAGE_MAP()

//DialogMessageBox message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogMessageBox::OnSize(UINT nType,int cx,int cy){
	DialogModalBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: OnBnClickedButtonOperation1
 * brief: �û��������1��ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation1(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION1);
}

/**
 * name: OnBnClickedButtonOperation2
 * brief: �û��������2��ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation2(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION2);
}

/**
 * name: OnBnClickedButtonOperation3
 * brief: �û��������3��ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation3(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION3);
}

/**
 * name: init_window
 * brief: ��ʼ����ǰ�Ի��򴰿ڡ�
 * param: --
 * return: --
 */
void DialogMessageBox::init_window(){
	//1.��ʼ����ǰ�Ի�����⡣
	SetWindowText(_title);
	//2.��ʼ����ǰ�Ի���ߴ硣
	MoveWindow(0,0,_width,_height);
	CenterWindow();
}

/**
 * name: init_controls
 * brief: ��ʼ�������пؼ���
 * param: --
 * return: --
 */
void DialogMessageBox::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ���Ի����пؼ���
	//2-1.��ʼ����̬�ı���
	if(_image_no>0){
		_image_static->load_background_image(theme->get_image(_image_no));
	}else{
		_image_static->ShowWindow(SW_HIDE);
	}
	_message_static->set_text_color(255,50,50,50);
	_message_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_message_static->SetWindowText(_message);
	//2-2.��ʼ��ͼƬ��ť��
	_operation_1_button->set_text_color(255,50,50,50);
	_operation_1_button->load_background_image(theme->get_image(32),1,4);
	_operation_1_button->set_background_image_stretching_factors(5,5,5,5);
	_operation_1_button->SetWindowText(_operation_1_name);
	if(_T("")==_operation_1_name){
		_operation_1_button->EnableWindow(FALSE);
		_operation_1_button->ShowWindow(SW_HIDE);
	}
	_operation_2_button->set_text_color(255,50,50,50);
	_operation_2_button->load_background_image(theme->get_image(32),1,4);
	_operation_2_button->set_background_image_stretching_factors(5,5,5,5);
	_operation_2_button->SetWindowText(_operation_2_name);
	if(_T("")==_operation_2_name){
		_operation_2_button->EnableWindow(FALSE);
		_operation_2_button->ShowWindow(SW_HIDE);
	}
	_operation_3_button->set_text_color(255,50,50,50);
	_operation_3_button->load_background_image(theme->get_image(32),1,4);
	_operation_3_button->set_background_image_stretching_factors(5,5,5,5);
	_operation_3_button->SetWindowText(_operation_3_name);
	if(_T("")==_operation_3_name){
		_operation_3_button->EnableWindow(FALSE);
		_operation_3_button->ShowWindow(SW_HIDE);
	}
	//3.��ʼ���Ի����в��֡�
	//3-1.��ʼ���Ӳ���1��
	if(_image_no>0){
		_child_layout_1->add_stretch(1);
		_child_layout_1->add_fixed_window(_image_static,
			(theme->get_image(_image_no))->get_height());
		_child_layout_1->add_stretch(1);
	}
	//3-2.��ʼ���Ӳ���2��
	if(_image_no>0){
		_child_layout_2->add_fixed_layout(_child_layout_1,
			(theme->get_image(_image_no))->get_width());
		_child_layout_2->add_spacing(5);
	}
	_child_layout_2->add_window(_message_static,1);
	//3-3.��ʼ���Ӳ���3��
	_child_layout_3->add_stretch(1);
	if(_T("")!=_operation_1_name){
		_child_layout_3->add_fixed_window(_operation_1_button,100);
		_child_layout_3->add_stretch(1);
	}
	if(_T("")!=_operation_2_name){
		_child_layout_3->add_fixed_window(_operation_2_button,100);
		_child_layout_3->add_stretch(1);
	}
	if(_T("")!=_operation_3_name){
		_child_layout_3->add_fixed_window(_operation_3_button,100);
		_child_layout_3->add_stretch(1);
	}
	//3-4.��ʼ�������֡�
	_main_layout->set_margin(BORDER_SIZE+5,TITLE_SIZE+5,
		BORDER_SIZE+5,BORDER_SIZE+5);
	_main_layout->add_layout(_child_layout_2,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,40);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: WarningMessageBox
 * breif: ��ʾ������Ϣ��
 * param: message - ������Ϣ��
 *        parent - ָ�򸸴��ڡ�
 *        width - ���ڿ�ȡ�
 *        height - ���ڸ߶ȡ�
 * return: ���ص����ť�İ�ť��ʶ�����磺IDOK��IDCANCEL��IDYES��IDNO�ȵȣ���
 * auhtor: yameng_he
 * date: 2015-06-17
 */
unsigned int WarningMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=400*/,const int height/*=300*/){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.����MessageBox�Ի���
	DialogMessageBox message_box(theme->get_string(IDS_STRING149),width,height,
		38,message,theme->get_string(IDS_STRING150),_T(""),_T(""),parent);
	//3.��ʾMessageBox�Ի���
	message_box.DoModal();
	//4.���ذ�ť��ʶ��
	return(IDOK);
}

/**
 * name: ErrorMessageBox
 * breif: ��ʾ������Ϣ��
 * param: message - ������Ϣ��
 *        parent - ָ�򸸴��ڡ�
 *        width - ���ڿ�ȡ�
 *        height - ���ڸ߶ȡ�
 * return: ���ص����ť�İ�ť��ʶ�����磺IDOK��IDCANCEL��IDYES��IDNO�ȵȣ���
 * auhtor: yameng_he
 * date: 2015-06-18
 */
unsigned int ErrorMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=300*/,const int height/*=200*/){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.����MessageBox�Ի���
	DialogMessageBox message_box(theme->get_string(IDS_STRING156),width,height,
		39,message,theme->get_string(IDS_STRING150),_T(""),_T(""),parent);
	//3.��ʾMessageBox�Ի���
	message_box.DoModal();
	//4.���ذ�ť��ʶ��
	return(IDOK);
}

/**
 * name: QuestionMessageBox
 * breif: ��ʾ������Ϣ��
 * param: message - ������Ϣ��
 *        parent - ָ�򸸴��ڡ�
 *        width - ���ڿ�ȡ�
 *        height - ���ڸ߶ȡ�
 * return: ���ص����ť�İ�ť��ʶ�����磺IDOK��IDCANCEL��IDYES��IDNO�ȵȣ���
 * auhtor: yameng_he
 * date: 2015-06-19
 */
unsigned int QuestionMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=300*/,const int height/*=200*/){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.����MessageBox�Ի���
	DialogMessageBox message_box(theme->get_string(IDS_STRING161),width,height,
		40,message,theme->get_string(IDS_STRING162),theme->get_string(IDS_STRING163),
		_T(""),parent);
	//3.��ʾMessageBox�Ի���
	const unsigned int result=message_box.DoModal();
	//4.���ذ�ť��ʶ��
	if(DialogMessageBox::IDOPERATION1==result){
		return(IDYES);
	}else{
		return(IDNO);
	}
}

/**
 * name: QuestionMessageBoxEx
 * breif: ��ʾ������չ��Ϣ��
 * param: message - ������Ϣ��
 *        parent - ָ�򸸴��ڡ�
 *        width - ���ڿ�ȡ�
 *        height - ���ڸ߶ȡ�
 * return: ���ص����ť�İ�ť��ʶ�����磺IDOK��IDCANCEL��IDYES��IDNO�ȵȣ���
 * auhtor: yameng_he
 * date: 2015-06-19
 */
unsigned int QuestionMessageBoxEx(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=400*/,const int height/*=200*/){
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.����MessageBox�Ի���
	DialogMessageBox message_box(theme->get_string(IDS_STRING161),width,height,
		40,message,theme->get_string(IDS_STRING162),theme->get_string(IDS_STRING163),
		theme->get_string(IDS_STRING306),parent);
	//3.��ʾMessageBox�Ի���
	const unsigned int result=message_box.DoModal();
	//4.���ذ�ť��ʶ��
	if(DialogMessageBox::IDOPERATION1==result){
		return(IDYES);
	}else if(DialogMessageBox::IDOPERATION2==result){
		return(IDNO);
	}else{
		return(IDCANCEL);
	}
}