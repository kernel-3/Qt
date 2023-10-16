// source-code/ui/calibration/DialogCalibration.cpp : implementation file
//
#include"stdafx.h"
#include"DialogCalibration.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"DialogStatus.h"
#include"DialogInstallation.h"
#include"DialogResult.h"

IMPLEMENT_DYNAMIC(DialogCalibration,DialogBase)

/**
 * name: DialogCalibration
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogCalibration::DialogCalibration(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogCalibration::IDD,pParent)
	,_page_buttons(new MtImageButton[PAGES])
	,_page_dialogs(new DialogBase*[PAGES])
	,_child_layout_1(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	memset(_page_dialogs,0,PAGES*sizeof(DialogBase*));
	_page_dialogs[0]=new DialogStatus;
	_page_dialogs[1]=new DialogInstallation;
	_page_dialogs[2]=new DialogResult;
}

/**
 * name: ~DialogCalibration
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogCalibration::~DialogCalibration(){
	delete _main_layout;
	delete _child_layout_1;
	delete[] _page_buttons;
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=_page_dialogs[index]){
			delete _page_dialogs[index];
		}
	}
	delete[] _page_dialogs;
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogCalibration::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	for(unsigned int index=0;index!=PAGES;++index){
		DDX_Control(pDX,IDC_BUTTON_STATUS+index,_page_buttons[index]);
	}
}

/**
 * name: OnInitDialog
 * brief: 初始化对话框虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogCalibration::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	//2.显示当前的子对话框。
	OnPageButtonClicked(IDC_BUTTON_STATUS);
	////////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogCalibration,DialogBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_BUTTON_STATUS,IDC_BUTTON_RESULT,&DialogCalibration::OnPageButtonClicked)
END_MESSAGE_MAP()

// DialogCalibration message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogCalibration::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * brief: 对话框销毁消息响应函数。
 * param: --
 * return: --
 */
void DialogCalibration::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
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
}

/**
 * name: OnPageButtonClicked
 * brief: 用户点击页面按钮消息响应函数。
 * param: ID - 页面按钮ID。
 * return: --
 */
void DialogCalibration::OnPageButtonClicked(const unsigned int ID){
	//1.计算当前点击按钮的下标，并且判断计算是否成功。
	const unsigned int index=ID-IDC_BUTTON_STATUS;
	if(index>=PAGES){
		return;
	}
	//2.如果当前按钮处于选中状态，则函数直接返回。
	if(_page_buttons[index].get_checked()){
		return;
	}
	//3.计算当前应该显示的子窗口的位置，并且判断计算是否成功。
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(1,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.如果当前应当显示的子页面尚未创建，则创建之，并且判断创建是否成功。
	//4-1.计算创建的页面ID。
	unsigned int dialog_id=0;
	if(0==index){
		dialog_id=DialogStatus::IDD;
	}else if(1==index){
		dialog_id=DialogInstallation::IDD;
	}else if(2==index){
		dialog_id=DialogResult::IDD;
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
	if(_main_layout->set_item_window(1,_page_dialogs[index],1)<0){
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
 * name: init_controls
 * brief: 初始化界面中控件。
 * param: --
 * return: --
 */
void DialogCalibration::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化界面中控件。
	//2-1.初始化按钮。
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//3.初始化布局。
	//3-1.初始化子布局1。
	for(unsigned int index=0;index!=PAGES;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.初始化主布局。
	_main_layout->set_margin(10,10,10,10);
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//3-3.调整主布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}