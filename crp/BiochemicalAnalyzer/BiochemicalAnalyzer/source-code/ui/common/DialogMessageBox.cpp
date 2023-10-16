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
 * brief: 构造函数。
 * param: title - 对话框标题。
 *        width - 对话框宽度。
 *        height - 对话框高度。
 *        image_no - 图片序号。
 *        message - 显示的消息。
 *        operation_1_name - 操作1的名称。
 *        operation_2_name - 操作2的名称。
 *		  pParent - 指向父窗口指针。
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
 * brief: 析构函数。
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
 * brief: 支持DDX/DDV。
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
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。 
 */
BOOL DialogMessageBox::OnInitDialog(){
	DialogModalBase::OnInitDialog();
	//TODO: Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.初始化当前对话框窗口。
	init_window();
	//2.初始化对话框中控件。
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
 * brief: 对话框尺寸调整消息响应函数，此处用来
 *        更新对话框中布局信息。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogMessageBox::OnSize(UINT nType,int cx,int cy){
	DialogModalBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: OnBnClickedButtonOperation1
 * brief: 用户点击操作1按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation1(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION1);
}

/**
 * name: OnBnClickedButtonOperation2
 * brief: 用户点击操作2按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation2(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION2);
}

/**
 * name: OnBnClickedButtonOperation3
 * brief: 用户点击操作3按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogMessageBox::OnBnClickedButtonOperation3(){
	// TODO: Add your control notification handler code here
	EndDialog(IDOPERATION3);
}

/**
 * name: init_window
 * brief: 初始化当前对话框窗口。
 * param: --
 * return: --
 */
void DialogMessageBox::init_window(){
	//1.初始化当前对话框标题。
	SetWindowText(_title);
	//2.初始化当前对话框尺寸。
	MoveWindow(0,0,_width,_height);
	CenterWindow();
}

/**
 * name: init_controls
 * brief: 初始化界面中控件。
 * param: --
 * return: --
 */
void DialogMessageBox::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化对话框中控件。
	//2-1.初始化静态文本框。
	if(_image_no>0){
		_image_static->load_background_image(theme->get_image(_image_no));
	}else{
		_image_static->ShowWindow(SW_HIDE);
	}
	_message_static->set_text_color(255,50,50,50);
	_message_static->set_text_alignment(MtImageStatic::ALIGNMENT_HCENTER|
		MtImageStatic::ALIGNMENT_VCENTER);
	_message_static->SetWindowText(_message);
	//2-2.初始化图片按钮。
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
	//3.初始化对话框中布局。
	//3-1.初始化子布局1。
	if(_image_no>0){
		_child_layout_1->add_stretch(1);
		_child_layout_1->add_fixed_window(_image_static,
			(theme->get_image(_image_no))->get_height());
		_child_layout_1->add_stretch(1);
	}
	//3-2.初始化子布局2。
	if(_image_no>0){
		_child_layout_2->add_fixed_layout(_child_layout_1,
			(theme->get_image(_image_no))->get_width());
		_child_layout_2->add_spacing(5);
	}
	_child_layout_2->add_window(_message_static,1);
	//3-3.初始化子布局3。
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
	//3-4.初始化主布局。
	_main_layout->set_margin(BORDER_SIZE+5,TITLE_SIZE+5,
		BORDER_SIZE+5,BORDER_SIZE+5);
	_main_layout->add_layout(_child_layout_2,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,40);
	//4.重置当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: WarningMessageBox
 * breif: 显示警告消息框。
 * param: message - 警告消息。
 *        parent - 指向父窗口。
 *        width - 窗口宽度。
 *        height - 窗口高度。
 * return: 返回点击按钮的按钮标识（例如：IDOK、IDCANCEL、IDYES、IDNO等等）。
 * auhtor: yameng_he
 * date: 2015-06-17
 */
unsigned int WarningMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=400*/,const int height/*=300*/){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.创建MessageBox对话框。
	DialogMessageBox message_box(theme->get_string(IDS_STRING149),width,height,
		38,message,theme->get_string(IDS_STRING150),_T(""),_T(""),parent);
	//3.显示MessageBox对话框。
	message_box.DoModal();
	//4.返回按钮标识。
	return(IDOK);
}

/**
 * name: ErrorMessageBox
 * breif: 显示错误消息框。
 * param: message - 警告消息。
 *        parent - 指向父窗口。
 *        width - 窗口宽度。
 *        height - 窗口高度。
 * return: 返回点击按钮的按钮标识（例如：IDOK、IDCANCEL、IDYES、IDNO等等）。
 * auhtor: yameng_he
 * date: 2015-06-18
 */
unsigned int ErrorMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=300*/,const int height/*=200*/){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.创建MessageBox对话框。
	DialogMessageBox message_box(theme->get_string(IDS_STRING156),width,height,
		39,message,theme->get_string(IDS_STRING150),_T(""),_T(""),parent);
	//3.显示MessageBox对话框。
	message_box.DoModal();
	//4.返回按钮标识。
	return(IDOK);
}

/**
 * name: QuestionMessageBox
 * breif: 显示提问消息框。
 * param: message - 警告消息。
 *        parent - 指向父窗口。
 *        width - 窗口宽度。
 *        height - 窗口高度。
 * return: 返回点击按钮的按钮标识（例如：IDOK、IDCANCEL、IDYES、IDNO等等）。
 * auhtor: yameng_he
 * date: 2015-06-19
 */
unsigned int QuestionMessageBox(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=300*/,const int height/*=200*/){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.创建MessageBox对话框。
	DialogMessageBox message_box(theme->get_string(IDS_STRING161),width,height,
		40,message,theme->get_string(IDS_STRING162),theme->get_string(IDS_STRING163),
		_T(""),parent);
	//3.显示MessageBox对话框。
	const unsigned int result=message_box.DoModal();
	//4.返回按钮标识。
	if(DialogMessageBox::IDOPERATION1==result){
		return(IDYES);
	}else{
		return(IDNO);
	}
}

/**
 * name: QuestionMessageBoxEx
 * breif: 显示提问拓展消息框。
 * param: message - 警告消息。
 *        parent - 指向父窗口。
 *        width - 窗口宽度。
 *        height - 窗口高度。
 * return: 返回点击按钮的按钮标识（例如：IDOK、IDCANCEL、IDYES、IDNO等等）。
 * auhtor: yameng_he
 * date: 2015-06-19
 */
unsigned int QuestionMessageBoxEx(const CString &message,CWnd *parent/*=NULL*/,
	const int width/*=400*/,const int height/*=200*/){
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.创建MessageBox对话框。
	DialogMessageBox message_box(theme->get_string(IDS_STRING161),width,height,
		40,message,theme->get_string(IDS_STRING162),theme->get_string(IDS_STRING163),
		theme->get_string(IDS_STRING306),parent);
	//3.显示MessageBox对话框。
	const unsigned int result=message_box.DoModal();
	//4.返回按钮标识。
	if(DialogMessageBox::IDOPERATION1==result){
		return(IDYES);
	}else if(DialogMessageBox::IDOPERATION2==result){
		return(IDNO);
	}else{
		return(IDCANCEL);
	}
}