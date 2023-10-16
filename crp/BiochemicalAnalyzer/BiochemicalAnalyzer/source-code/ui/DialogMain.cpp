// DialogMain.cpp : implementation file
//
#include"stdafx.h"
#include"../AppMain.h"
#include"DialogMain.h"
#include"afxdialogex.h"
#include"../global/theme.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../include/mfctoolkit/layout/MtLayoutFixedWindowItem.h"
#include"../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../include/mfctoolkit/control/MtImageButton.h"
#include"workplace/DialogWorkPlace.h"
#include"../global/DatabaseManager.h"
#include"reagent/DialogReagent.h"
#include"calibration/DialogCalibration.h"
#include"qc/DialogQC.h"
#include"utility/DialogUtility.h"
#include"../data/utility/Applications.h"
#include"../data/common/Modules.h"
#include"../data/common/SpecimenTypes.h"
#include"../data/common/Items.h"
#include"../data/common/AnalysisMethods.h"
#include"../data/common/DilutionMethods.h"
#include"../data/common/CalibrationMethods.h"
#include"../data/utility/ApplicationParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// DialogMain dialog

/**
 * name: DialogMain
 * brief: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
 * return: --
 */
DialogMain::DialogMain(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogMain::IDD,pParent)
	,_title_bar_static(new MtImageStatic)
	,_status_led_static(new MtImageStatic)
	,_status_bar_static(new MtImageStatic)
	,_main_function_bar_static(new MtImageStatic)
	,_information_bar_static(new MtImageStatic)
	,_page_buttons(new MtImageButton[PAGES])
	,_start_button(new MtImageButton)
	,_emergency_button(new MtImageButton)
	,_pause_button(new MtImageButton)
	,_stop_button(new MtImageButton)
	,_alarm_button(new MtImageButton)
	,_monitor_button(new MtImageButton)
	,_print_button(new MtImageButton)
	,_exit_button(new MtImageButton)
	,_page_dialogs(new DialogBase*[PAGES])
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtVerticalLayout)
	,_child_layout_4(new MtVerticalLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(_page_dialogs,0,PAGES*sizeof(DialogBase*));
	_page_dialogs[0]=new DialogWorkPlace;
	_page_dialogs[1]=new DialogReagent;
	_page_dialogs[2]=new DialogCalibration;
	_page_dialogs[3]=new DialogQC;
	_page_dialogs[4]=new DialogUtility;
}

/**
 * name: ~DialogMain
 * brief: ����������
 * param: --
 * return: --
 */
DialogMain::~DialogMain(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=_page_dialogs[index]){
			delete _page_dialogs[index];
		}
	}
	delete[] _page_dialogs;
	delete _title_bar_static;
	delete _status_led_static;
	delete _status_bar_static;
	delete _main_function_bar_static;
	delete _information_bar_static;
	delete[] _page_buttons;
	delete _start_button;
	delete _emergency_button;
	delete _pause_button;
	delete _stop_button;
	delete _alarm_button;
	delete _monitor_button;
	delete _print_button;
	delete _exit_button;
}

/**
 * name: DoDataExchange
 * brief: DDX/DDV ֧�֡�
 * param: pDX -
 * return:
 */
void DialogMain::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_TITLE_BAR,*_title_bar_static);
	DDX_Control(pDX,IDC_STATIC_STATUS_LED,*_status_led_static);
	DDX_Control(pDX,IDC_STATIC_STATUS_BAR,*_status_bar_static);
	DDX_Control(pDX,IDC_STATIC_MAIN_FUNCTION_BAR,*_main_function_bar_static);
	DDX_Control(pDX,IDC_STATIC_INFORMATION_BAR,*_information_bar_static);
	for(unsigned int index=0;index!=PAGES;++index){
		DDX_Control(pDX,IDC_BUTTON_WORKPLACE+index,_page_buttons[index]);
	}
	DDX_Control(pDX,IDC_BUTTON_START,*_start_button);
	DDX_Control(pDX,IDC_BUTTON_EMERGENCY,*_emergency_button);
	DDX_Control(pDX,IDC_BUTTON_PAUSE,*_pause_button);
	DDX_Control(pDX,IDC_BUTTON_STOP,*_stop_button);
	DDX_Control(pDX,IDC_BUTTON_ALARM,*_alarm_button);
	DDX_Control(pDX,IDC_BUTTON_MONITOR,*_monitor_button);
	DDX_Control(pDX,IDC_BUTTON_PRINT,*_print_button);
	DDX_Control(pDX,IDC_BUTTON_EXIT,*_exit_button);
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogMain::OnInitDialog(){
	DialogBase::OnInitDialog();
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX&0xFFF0)==IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX<0xF000);
	CMenu *pSysMenu=GetSystemMenu(FALSE);
	if(pSysMenu!=NULL){
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid=strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if(!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING,IDM_ABOUTBOX,strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon,TRUE);			// Set big icon
	SetIcon(m_hIcon,FALSE);		// Set small icon
	// TODO: Add extra initialization here
	////////////////////////////////////////////////////////
	//1.�������ݿ⣬�����ж������Ƿ�ɹ���
	if(DatabaseManager::instance()->connect_to_databases()<0){
		//EndDialog(IDCANCEL);//��ᵼ��OnInitDialog���������Ρ�
		SendMessage(WM_CLOSE);
		return(TRUE);
	}
	//2.���µ�ǰϵͳ��ȫ����������Ϣ��
	//2-1.������ǰ�������������
	Database *database=DatabaseManager::instance()->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//2-1.����ϵͳ��ģ����Ϣ��
	Modules::instance()->update(*database);
	//2-2.����ϵͳ������������Ϣ��
	SpecimenTypes::instance()->update(*database);
	//2-3.����ϵͳ����Ŀ��Ϣ��
	Items::instance()->update(*database);
	//2-4.����ϵͳ�з���������Ϣ��
	AnalysisMethods::instance()->update(*database);
	//2-5.����ϵͳ�е�ϡ�ͷ�����Ϣ��
	DilutionMethods::instance()->update(*database);
	//2-6.����ϵͳ�еĶ��귽����Ϣ��
	CalibrationMethods::instance()->update(*database);
	//2-7.����ϵͳ�еĲ�����Ϣ��
	ApplicationParameters::instance()->update(*database);
	/*
	Applications::instance()->update(*((DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN)));
	*/
	//2.��ʼ����ǰ�Ի��򴰿ڡ�
	init_window();
	//3.��ʼ���Ի����пؼ���Ϣ��
	init_controls();
	//4.��ʾ��ǰ���ӶԻ���
	OnPageButtonClicked(IDC_BUTTON_WORKPLACE);
	///////////////////////////////////////////////////////
	return(TRUE);//return TRUE  unless you set the focus to a control
}

/**
 * name: draw
 * brief: �Ի���������⺯�����˺�������ʵ�ֶԻ�����ơ�
 * param: memory_bitmap - �Ի����ڴ�λͼ���á�
 *        dc - �Ի����ͼDC��
 * return: --
 */
void DialogMain::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.���û�����Ӧ�������ƶԻ��򱳾���
	DialogBase::draw(memory_bitmap,dc);
	//2.���ƶԻ����������
	draw_title_bar(memory_bitmap);
	//3.���ƶԻ���״̬����
	draw_status_bar(memory_bitmap);
	//4.���ƶԻ��򹤾�����
	draw_tool_bar(memory_bitmap);
	//5.��������������
	draw_main_function_bar(memory_bitmap);
	//6.��������������
	draw_main_function_region(memory_bitmap);
	//7.���ƶԻ��򹤾�����
	draw_information_bar(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogMain,DialogBase)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_SIZING()
	ON_COMMAND_RANGE(IDC_BUTTON_WORKPLACE,IDC_BUTTON_UTILITY,
	&DialogMain::OnPageButtonClicked)
END_MESSAGE_MAP()

// DialogMain message handlers
/**
 * name: OnSysCommand
 * brief: ���Ʋ˵�������Ϣ��Ӧ������
 * param: nID - ����ID��
 *        lParam - 
 * return: --
 */
void DialogMain::OnSysCommand(UINT nID,LPARAM lParam){
	if((nID&0xFFF0)==IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}else{
		DialogBase::OnSysCommand(nID,lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
/**
 * name: OnPaint
 * brief: �Ի��򱳾�������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogMain::OnPaint(){
	if(IsIconic()){
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND,reinterpret_cast<WPARAM>(dc.GetSafeHdc()),0);
		// Center icon in client rectangle
		int cxIcon=GetSystemMetrics(SM_CXICON);
		int cyIcon=GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x=(rect.Width()-cxIcon+1)/2;
		int y=(rect.Height()-cyIcon+1)/2;
		// Draw the icon
		dc.DrawIcon(x,y,m_hIcon);
	}else{
		DialogBase::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
// the minimized window.
/**
 * name: OnQueryDragIcon
 * brief:
 * param: --
 * return: 
 */
HCURSOR DialogMain::OnQueryDragIcon(){
	return(static_cast<HCURSOR>(m_hIcon));
}

/**
 * name: OnSize
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogMain::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_main_layout->resize(cx,cy);
	Invalidate(FALSE);
}

/**
 * name: OnDestroy
 * brief: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogMain::OnDestroy(){
	DialogBase::OnDestroy();
	//TODO: Add your message handler code here
	//1.���ٵ�ǰ�ӶԻ���
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=_page_dialogs[index]){
			if(IsWindow(_page_dialogs[index]->GetSafeHwnd())){
				_page_dialogs[index]->DestroyWindow();
			}
			delete _page_dialogs[index];
			_page_dialogs[index]=0;
		}
	}
	//2.�Ͽ���ǰϵͳ�����ݿ�����ӡ�
	DatabaseManager::instance()->disconnect_from_databases();
}

/**
 * name: OnSizing
 * brief: �û���ק������Ϣ��Ӧ������������������������
 *        ����С�������ק�ߴ硣
 * param: fwSide - �û�������ק�ıߡ�
 *        =====================================
 *        1 - ������߱���ק��
 *        2 - �����ұ߱���ק��
 *        3 - �����ϱ߱���ק��
 *        4 - �������ϽǱ���ק��
 *        5 - �������ϽǱ���ק��
 *        6 - �����±߱���ק��
 *        7 - �������½Ǳ���ק��
 *        8 - �������½Ǳ���ק��
 *        =====================================
 *        pRect - ��ǰ���ڳߴ硣
 * return: --
 */
void DialogMain::OnSizing(UINT fwSide,LPRECT pRect){
	//1.�����ǰ�Ի�����С����С�Ի����ȡ�
	if((pRect->right-pRect->left)<MINIMUM_DIALOG_WIDTH){
		if((1==fwSide)||(4==fwSide)||(7==fwSide)){
			pRect->left=pRect->right-MINIMUM_DIALOG_WIDTH;
		}else if((2==fwSide)||(5==fwSide)||(8==fwSide)){
			pRect->right=pRect->left+MINIMUM_DIALOG_WIDTH;
		}
	}
	//2.�����ǰ�Ի���߶�С����С�Ի���߶ȡ�
	if((pRect->bottom-pRect->top)<MINIMUM_DIALOG_HEIGHT){
		if((3==fwSide)||(4==fwSide)||(5==fwSide)){
			pRect->top=pRect->bottom-MINIMUM_DIALOG_HEIGHT;
		}else if((6==fwSide)||(7==fwSide)||(8==fwSide)){
			pRect->bottom=pRect->top+MINIMUM_DIALOG_HEIGHT;
		}
	}
	//3.���û�����Ӧ��Ϣ��Ӧ������
	DialogBase::OnSizing(fwSide,pRect);
	// TODO: Add your message handler code here
}

/**
 * name: OnPageButtonClicked
 * brief: �û����ҳ�水ť��Ϣ��Ӧ������
 * param: ID - ҳ�水ťID��
 * return: --
 */
void DialogMain::OnPageButtonClicked(const unsigned int ID){
	//1.���㵱ǰ�����ť���±꣬�����жϼ����Ƿ�ɹ���
	const unsigned int index=ID-IDC_BUTTON_WORKPLACE;
	if(index>=PAGES){
		return;
	}
	//2.�����ǰ��ť����ѡ��״̬������ֱ�ӷ��ء�
	if(_page_buttons[index].get_checked()){
		return;
	}
	//3.���㵱ǰӦ����ʾ���Ӵ��ڵ�λ�ã������жϼ����Ƿ�ɹ���
	MtLayout::IntRect rect;
	if((_child_layout_2->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.�����ǰӦ����ʾ����ҳ����δ�������򴴽�֮�������жϴ����Ƿ�ɹ���
	//4-1.���㴴����ҳ��ID��
	unsigned int dialog_id=0;
	if(0==index){
		dialog_id=DialogWorkPlace::IDD;
	}else if(1==index){
		dialog_id=DialogReagent::IDD;
	}else if(2==index){
		dialog_id=DialogCalibration::IDD;
	}else if(3==index){
		dialog_id=DialogQC::IDD;
	}else if(4==index){
		dialog_id=DialogUtility::IDD;
	}else{
		return;
	}
	//4-2.����ҳ�棬�����жϴ����Ƿ�ɹ���
	if(!IsWindow(_page_dialogs[index]->GetSafeHwnd())){
		if(!_page_dialogs[index]->Create(dialog_id,this)){
			return;
		}
	}
	//5.����ǰ�Ӵ��ڷ��벼�֣������жϷ����Ƿ�ɹ���
	if(_child_layout_2->set_item_window(0,_page_dialogs[index],870)<0){
		return;
	}
	//6.�������а�ť��ѡ��״̬�Լ�������ҳ����ʾ״̬��
	for(unsigned int i=0;i!=PAGES;++i){
		//6-1.���ð�ťѡ��״̬��
		_page_buttons[i].set_checked(FALSE);
		//6-2.����ҳ����ʾ״̬��
		if(IsWindow(_page_dialogs[i]->GetSafeHwnd())){
			_page_dialogs[i]->ShowWindow(SW_HIDE);
		}
	}
	//7.������ǰӦ����ʾ���Ӵ��ڵ�λ�á�
	_page_dialogs[index]->MoveWindow(rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height());
	//8.���õ�ǰ��ťѡ���Լ�ҳ�����ʾ״̬��
	_page_buttons[index].set_checked(TRUE);
	_page_dialogs[index]->ShowWindow(SW_SHOW);
}

/**
 * name: init_window
 * brief: ��ʼ����ǰ�Ի��򴰿ڡ�
 * param: --
 * return: --
 */
void DialogMain::init_window(){
	//MoveWindow(0,0,1920/*MINIMUM_DIALOG_WIDTH*/,
		//1080/*MINIMUM_DIALOG_HEIGHT*/,FALSE);
	MoveWindow(0,0,/*1920*/MINIMUM_DIALOG_WIDTH,
		/*1080*/MINIMUM_DIALOG_HEIGHT,FALSE);
	CenterWindow();
}

/**
 * name: int_controls
 * brief: ��ʼ���Ի����еĿؼ���
 * param: --
 * return: --
 */
void DialogMain::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ����̬�ı���
	_title_bar_static->set_text_color(255,255,255,255);
	_title_bar_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_status_led_static->load_background_image(theme->get_image(35),1,7);
	_status_led_static->set_background_image_stretching_factors(12,12,12,12);
	_status_bar_static->set_text_color(255,50,50,50);
	_main_function_bar_static->set_text_color(255,255,255,255);
	_main_function_bar_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_information_bar_static->set_text_color(255,255,255,255);
	_information_bar_static->set_text_alignment(MtImageStatic::ALIGNMENT_RIGHT|
		MtImageStatic::ALIGNMENT_VCENTER);
	//3.��ʼ����ť��
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(8),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
		_page_buttons[index].load_foreground_image(theme->get_image(9+index),1,4);
		_page_buttons[index].set_foreground_image_alignment(
			MtImageButton::ALIGNMENT_TOP|MtImageButton::ALIGNMENT_HCENTER);
	}
	_start_button->set_text_color(255,255,255,255);
	_start_button->load_background_image(theme->get_image(14),1,4);
	_start_button->set_background_image_stretching_factors(5,5,5,5);
	_start_button->load_foreground_image(theme->get_image(15),1,4);
	_start_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_emergency_button->set_text_color(255,255,255,255);
	_emergency_button->load_background_image(theme->get_image(14),1,4);
	_emergency_button->set_background_image_stretching_factors(5,5,5,5);
	_emergency_button->load_foreground_image(theme->get_image(16),1,4);
	_emergency_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_pause_button->set_text_color(255,255,255,255);
	_pause_button->load_background_image(theme->get_image(14),1,4);
	_pause_button->set_background_image_stretching_factors(5,5,5,5);
	_pause_button->load_foreground_image(theme->get_image(17),1,4);
	_pause_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_stop_button->set_text_color(255,255,255,255);
	_stop_button->load_background_image(theme->get_image(14),1,4);
	_stop_button->set_background_image_stretching_factors(5,5,5,5);
	_stop_button->load_foreground_image(theme->get_image(18),1,4);
	_stop_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_alarm_button->set_text_color(255,255,255,255);
	_alarm_button->load_background_image(theme->get_image(14),1,4);
	_alarm_button->set_background_image_stretching_factors(5,5,5,5);
	_alarm_button->load_foreground_image(theme->get_image(19),1,4);
	_alarm_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_monitor_button->set_text_color(255,255,255,255);
	_monitor_button->load_background_image(theme->get_image(14),1,4);
	_monitor_button->set_background_image_stretching_factors(5,5,5,5);
	_monitor_button->load_foreground_image(theme->get_image(20),1,4);
	_monitor_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_print_button->set_text_color(255,255,255,255);
	_print_button->load_background_image(theme->get_image(14),1,4);
	_print_button->set_background_image_stretching_factors(5,5,5,5);
	_print_button->load_foreground_image(theme->get_image(21),1,4);
	_print_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	_exit_button->set_text_color(255,255,255,255);
	_exit_button->load_background_image(theme->get_image(14),1,4);
	_exit_button->set_background_image_stretching_factors(5,5,5,5);
	_exit_button->load_foreground_image(theme->get_image(22),1,4);
	_exit_button->set_foreground_image_alignment(
		MtImageButton::ALIGNMENT_LEFT|MtImageButton::ALIGNMENT_VCENTER);
	//4.��ʼ���Ի����в��֡�
	//4-1.��ʼ���Ӳ���1��
	_child_layout_1->set_margin(5,5,5,5);
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=index){
			_child_layout_1->add_spacing(5);
		}
		_child_layout_1->add_window(&_page_buttons[index],110);
	}
	_child_layout_1->add_stretch(500);
	//4-2.��ʼ���Ӳ���2��
	_child_layout_2->add_stretch(870);
	_child_layout_2->add_layout(_child_layout_3,210);
	//4-3.��ʼ���Ӳ���3��
	_child_layout_3->add_fixed_window(_main_function_bar_static,50);
	_child_layout_3->add_layout(_child_layout_4,1);
	//4-4.��ʼ���Ӳ���4��
	_child_layout_4->set_margin(10,10,10,10);
	_child_layout_4->add_window(_start_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_emergency_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_pause_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_stop_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_alarm_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_monitor_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_print_button,1);
	_child_layout_4->add_spacing(10);
	_child_layout_4->add_window(_exit_button,1);
	//4-5.��ʼ���Ӳ���5��
	_child_layout_5->set_margin(5,3,5,0);
	_child_layout_5->add_fixed_window(_status_led_static,26);
	_child_layout_5->add_spacing(10);
	_child_layout_5->add_window(_status_bar_static,1);
	//4-6.��ʼ�������֡�
	_main_layout->add_window(_title_bar_static,37);
	_main_layout->add_fixed_layout(_child_layout_5,29);
	_main_layout->add_layout(_child_layout_1,90);
	_main_layout->add_layout(_child_layout_2,544);
	_main_layout->add_window(_information_bar_static,30);
	//4-7.�����Ի����в��ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: draw_title_bar
 * breif: ���Ƶ�ǰ�Ի���ı�������
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_title_bar(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���ı�����ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(2);
	//2.�����ǰ�Ի��������ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի��������λ����Ϣ��
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
 * name: draw_status_bar
 * breif: ���Ƶ�ǰ�Ի����״̬����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_status_bar(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի����״̬��ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(3);
	//2.�����ǰ�Ի���״̬��ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի���״̬��λ����Ϣ��
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(1,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,0);
}

/**
 * name: draw_tool_bar
 * breif: ���Ƶ�ǰ�Ի���Ĺ�������
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_tool_bar(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���Ĺ�����ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(4);
	//2.�����ǰ�Ի��򹤾���ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի��򹤾���λ����Ϣ��
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(2,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,5);
}

/**
 * name: draw_main_function_bar
 * breif: ���Ƶ�ǰ�Ի��������������
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_main_function_bar(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի������������ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(6);
	//2.�����ǰ�Ի�����������ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի�����������λ����Ϣ��
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),5,0,5,5);
}

/**
 * name: draw_main_function_region
 * breif: ���Ƶ�ǰ�Ի��������������
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_main_function_region(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի��������������ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(7);
	//2.�����ǰ�Ի�������������ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի�������������λ����Ϣ��
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	MtLayout::IntRect rect_t;
	if((_main_layout->get_item_rect(4,rect_t)<0)||
		(!rect_t.is_valid())){
		return;
	}
	rect.set_top(rect.get_bottom());
	rect.set_bottom(rect_t.get_top());
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),5,0,5,0);
}

/**
 * name: draw_information_bar
 * breif: ���Ƶ�ǰ�Ի������Ϣ����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogMain::draw_information_bar(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի������Ϣ��ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(5);
	//2.�����ǰ�Ի�����Ϣ��ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի�����Ϣ��λ����Ϣ��
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(4,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,0);
}