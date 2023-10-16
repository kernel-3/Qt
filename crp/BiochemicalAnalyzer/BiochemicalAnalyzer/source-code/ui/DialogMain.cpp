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
 * brief: 构造函数。
 * param: pParent - 指向父窗口。
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
 * brief: 析构函数。
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
 * brief: DDX/DDV 支持。
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
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
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
	//1.连接数据库，并且判断连接是否成功。
	if(DatabaseManager::instance()->connect_to_databases()<0){
		//EndDialog(IDCANCEL);//这会导致OnInitDialog被调用两次。
		SendMessage(WM_CLOSE);
		return(TRUE);
	}
	//2.更新当前系统中全部的数据信息。
	//2-1.声明当前操作所需变量。
	Database *database=DatabaseManager::instance()->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//2-1.更新系统中模块信息。
	Modules::instance()->update(*database);
	//2-2.更新系统中样本类型信息。
	SpecimenTypes::instance()->update(*database);
	//2-3.更新系统中项目信息。
	Items::instance()->update(*database);
	//2-4.更新系统中分析方法信息。
	AnalysisMethods::instance()->update(*database);
	//2-5.更新系统中的稀释方法信息。
	DilutionMethods::instance()->update(*database);
	//2-6.更新系统中的定标方法信息。
	CalibrationMethods::instance()->update(*database);
	//2-7.更新系统中的参数信息。
	ApplicationParameters::instance()->update(*database);
	/*
	Applications::instance()->update(*((DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN)));
	*/
	//2.初始化当前对话框窗口。
	init_window();
	//3.初始化对话框中控件信息。
	init_controls();
	//4.显示当前的子对话框。
	OnPageButtonClicked(IDC_BUTTON_WORKPLACE);
	///////////////////////////////////////////////////////
	return(TRUE);//return TRUE  unless you set the focus to a control
}

/**
 * name: draw
 * brief: 对话框绘制虚拟函数，此函数用来实现对话框绘制。
 * param: memory_bitmap - 对话框内存位图引用。
 *        dc - 对话框绘图DC。
 * return: --
 */
void DialogMain::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.调用基类相应函数绘制对话框背景。
	DialogBase::draw(memory_bitmap,dc);
	//2.绘制对话框标题栏。
	draw_title_bar(memory_bitmap);
	//3.绘制对话框状态栏。
	draw_status_bar(memory_bitmap);
	//4.绘制对话框工具拦。
	draw_tool_bar(memory_bitmap);
	//5.绘制主功能栏。
	draw_main_function_bar(memory_bitmap);
	//6.绘制主功能区域。
	draw_main_function_region(memory_bitmap);
	//7.绘制对话框工具栏。
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
 * brief: 控制菜单命令消息响应函数。
 * param: nID - 命令ID。
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
 * brief: 对话框背景绘制消息响应函数。
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
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
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
 * brief: 对话框销毁消息响应函数。
 * param: --
 * return: --
 */
void DialogMain::OnDestroy(){
	DialogBase::OnDestroy();
	//TODO: Add your message handler code here
	//1.销毁当前子对话框。
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=_page_dialogs[index]){
			if(IsWindow(_page_dialogs[index]->GetSafeHwnd())){
				_page_dialogs[index]->DestroyWindow();
			}
			delete _page_dialogs[index];
			_page_dialogs[index]=0;
		}
	}
	//2.断开当前系统中数据库的连接。
	DatabaseManager::instance()->disconnect_from_databases();
}

/**
 * name: OnSizing
 * brief: 用户拖拽窗口消息响应函数。这里用来控制主窗口
 *        的最小、最大拖拽尺寸。
 * param: fwSide - 用户正在拖拽的边。
 *        =====================================
 *        1 - 窗口左边被拖拽。
 *        2 - 窗口右边被拖拽。
 *        3 - 窗口上边被拖拽。
 *        4 - 窗口左上角被拖拽。
 *        5 - 窗口右上角被拖拽。
 *        6 - 窗口下边被拖拽。
 *        7 - 窗口左下角被拖拽。
 *        8 - 窗口右下角被拖拽。
 *        =====================================
 *        pRect - 当前窗口尺寸。
 * return: --
 */
void DialogMain::OnSizing(UINT fwSide,LPRECT pRect){
	//1.如果当前对话框宽度小于最小对话框宽度。
	if((pRect->right-pRect->left)<MINIMUM_DIALOG_WIDTH){
		if((1==fwSide)||(4==fwSide)||(7==fwSide)){
			pRect->left=pRect->right-MINIMUM_DIALOG_WIDTH;
		}else if((2==fwSide)||(5==fwSide)||(8==fwSide)){
			pRect->right=pRect->left+MINIMUM_DIALOG_WIDTH;
		}
	}
	//2.如果当前对话框高度小于最小对话框高度。
	if((pRect->bottom-pRect->top)<MINIMUM_DIALOG_HEIGHT){
		if((3==fwSide)||(4==fwSide)||(5==fwSide)){
			pRect->top=pRect->bottom-MINIMUM_DIALOG_HEIGHT;
		}else if((6==fwSide)||(7==fwSide)||(8==fwSide)){
			pRect->bottom=pRect->top+MINIMUM_DIALOG_HEIGHT;
		}
	}
	//3.调用基类相应消息响应函数。
	DialogBase::OnSizing(fwSide,pRect);
	// TODO: Add your message handler code here
}

/**
 * name: OnPageButtonClicked
 * brief: 用户点击页面按钮消息响应函数。
 * param: ID - 页面按钮ID。
 * return: --
 */
void DialogMain::OnPageButtonClicked(const unsigned int ID){
	//1.计算当前点击按钮的下标，并且判断计算是否成功。
	const unsigned int index=ID-IDC_BUTTON_WORKPLACE;
	if(index>=PAGES){
		return;
	}
	//2.如果当前按钮处于选中状态，则函数直接返回。
	if(_page_buttons[index].get_checked()){
		return;
	}
	//3.计算当前应该显示的子窗口的位置，并且判断计算是否成功。
	MtLayout::IntRect rect;
	if((_child_layout_2->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.如果当前应当显示的子页面尚未创建，则创建之，并且判断创建是否成功。
	//4-1.计算创建的页面ID。
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
	//4-2.创建页面，并且判断创建是否成功。
	if(!IsWindow(_page_dialogs[index]->GetSafeHwnd())){
		if(!_page_dialogs[index]->Create(dialog_id,this)){
			return;
		}
	}
	//5.将当前子窗口放入布局，并且判断放入是否成功。
	if(_child_layout_2->set_item_window(0,_page_dialogs[index],870)<0){
		return;
	}
	//6.重置所有按钮的选中状态以及所有子页面显示状态。
	for(unsigned int i=0;i!=PAGES;++i){
		//6-1.重置按钮选中状态。
		_page_buttons[i].set_checked(FALSE);
		//6-2.重置页面显示状态。
		if(IsWindow(_page_dialogs[i]->GetSafeHwnd())){
			_page_dialogs[i]->ShowWindow(SW_HIDE);
		}
	}
	//7.调整当前应该显示的子窗口的位置。
	_page_dialogs[index]->MoveWindow(rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height());
	//8.设置当前按钮选中以及页面的显示状态。
	_page_buttons[index].set_checked(TRUE);
	_page_dialogs[index]->ShowWindow(SW_SHOW);
}

/**
 * name: init_window
 * brief: 初始化当前对话框窗口。
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
 * brief: 初始化对话框中的控件。
 * param: --
 * return: --
 */
void DialogMain::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化静态文本框。
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
	//3.初始化按钮。
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
	//4.初始化对话框中布局。
	//4-1.初始化子布局1。
	_child_layout_1->set_margin(5,5,5,5);
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=index){
			_child_layout_1->add_spacing(5);
		}
		_child_layout_1->add_window(&_page_buttons[index],110);
	}
	_child_layout_1->add_stretch(500);
	//4-2.初始化子布局2。
	_child_layout_2->add_stretch(870);
	_child_layout_2->add_layout(_child_layout_3,210);
	//4-3.初始化子布局3。
	_child_layout_3->add_fixed_window(_main_function_bar_static,50);
	_child_layout_3->add_layout(_child_layout_4,1);
	//4-4.初始化子布局4。
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
	//4-5.初始化子布局5。
	_child_layout_5->set_margin(5,3,5,0);
	_child_layout_5->add_fixed_window(_status_led_static,26);
	_child_layout_5->add_spacing(10);
	_child_layout_5->add_window(_status_bar_static,1);
	//4-6.初始化主布局。
	_main_layout->add_window(_title_bar_static,37);
	_main_layout->add_fixed_layout(_child_layout_5,29);
	_main_layout->add_layout(_child_layout_1,90);
	_main_layout->add_layout(_child_layout_2,544);
	_main_layout->add_window(_information_bar_static,30);
	//4-7.调整对话框中布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: draw_title_bar
 * breif: 绘制当前对话框的标题栏。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_title_bar(MtBitmap &memory_bitmap){
	//1.获取当前对话框的标题栏图片。
	Theme::PtrToImage image=Theme::instance()->get_image(2);
	//2.如果当前对话框标题栏图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框标题栏位置信息。
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
 * name: draw_status_bar
 * breif: 绘制当前对话框的状态栏。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_status_bar(MtBitmap &memory_bitmap){
	//1.获取当前对话框的状态栏图片。
	Theme::PtrToImage image=Theme::instance()->get_image(3);
	//2.如果当前对话框状态栏图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框状态栏位置信息。
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(1,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,0);
}

/**
 * name: draw_tool_bar
 * breif: 绘制当前对话框的工具栏。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_tool_bar(MtBitmap &memory_bitmap){
	//1.获取当前对话框的工具栏图片。
	Theme::PtrToImage image=Theme::instance()->get_image(4);
	//2.如果当前对话框工具栏图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框工具栏位置信息。
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(2,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,5);
}

/**
 * name: draw_main_function_bar
 * breif: 绘制当前对话框的主功能栏。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_main_function_bar(MtBitmap &memory_bitmap){
	//1.获取当前对话框的主功能栏图片。
	Theme::PtrToImage image=Theme::instance()->get_image(6);
	//2.如果当前对话框主功能栏图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框主功能栏位置信息。
	MtLayout::IntRect rect;
	if((_child_layout_3->get_item_rect(0,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),5,0,5,5);
}

/**
 * name: draw_main_function_region
 * breif: 绘制当前对话框的主功能区域。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_main_function_region(MtBitmap &memory_bitmap){
	//1.获取当前对话框的主功能区域图片。
	Theme::PtrToImage image=Theme::instance()->get_image(7);
	//2.如果当前对话框主功能区域图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框主功能区域位置信息。
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
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),5,0,5,0);
}

/**
 * name: draw_information_bar
 * breif: 绘制当前对话框的信息栏。
 * param: memory_bitmap - 对话框内存位图。
 * return: --
 */
void DialogMain::draw_information_bar(MtBitmap &memory_bitmap){
	//1.获取当前对话框的信息栏图片。
	Theme::PtrToImage image=Theme::instance()->get_image(5);
	//2.如果当前对话框信息栏图片获取失败，则直接返回。
	if(!static_cast<bool>(image)){
		return;
	}
	//3.计算当前对话框信息栏位置信息。
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(4,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.将当前图片黏贴到指定的内存位图上。
	image->paste_to_bitmap_ex(&memory_bitmap,rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height(),0,0,image->get_width(),
		image->get_height(),0,5,0,0);
}