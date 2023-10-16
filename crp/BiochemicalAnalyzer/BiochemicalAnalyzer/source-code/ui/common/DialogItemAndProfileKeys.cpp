// source-code/ui/DialogItemAndProfileKeys.cpp : implementation file
//

#include"stdafx.h"
#include"DialogItemAndProfileKeys.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"DialogItemAndProfileKey.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../UiCustom.h"
#include"../../data/utility/Applications.h"
#include<assert.h>

// DialogItemAndProfileKeys dialog
IMPLEMENT_DYNAMIC(DialogItemAndProfileKeys,DialogBase)

/**
 * name: DialogItemAndProfileKeys
 * brief: 构造函数。
 * param: mode - 模式
 * =============================================
 *        1   配置项目模式    用于设置项目键。
 *        2   配置组合模式    用于设置组合键。
 *        3   样本设置模式    用于样本设置。
 * =============================================
 *		  pParent - 指向父窗口。
 * return: --
 */
DialogItemAndProfileKeys::DialogItemAndProfileKeys(
	const int mode,CWnd *pParent/*=NULL*/)
	:DialogBase(DialogItemAndProfileKeys::IDD,pParent)
	,_mode(mode)
	,_page_buttons(new MtImageButton[PAGES])
	,_page_dialogs(new DialogItemAndProfileKey[PAGES])
	,_child_layout_1(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index].set_mode(mode);
		_page_dialogs[index].set_page_no(index);
	}
}

/**
 * name: ~DialogItemAndProfileKeys
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogItemAndProfileKeys::~DialogItemAndProfileKeys(){
	delete _main_layout;
	delete _child_layout_1;
	delete[] _page_buttons;
	delete[] _page_dialogs;
}

/**
 * name: DoDataExchange
 * brief: DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogItemAndProfileKeys::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	for(unsigned int index=0;index!=PAGES;++index){
		DDX_Control(pDX,IDC_BUTTON_PAGE_1+index,_page_buttons[index]);
	}
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogItemAndProfileKeys::OnInitDialog(){
	DialogBase::OnInitDialog();
	///////////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	///////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogItemAndProfileKeys,DialogBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_BUTTON_PAGE_1,IDC_BUTTON_PAGE_5/*IDC_BUTTON_PAGE_10*/,&DialogItemAndProfileKeys::OnButtonClicked)
	ON_MESSAGE(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,&DialogItemAndProfileKeys::OnItemOrProfileButtonClicked)
END_MESSAGE_MAP()

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogItemAndProfileKeys::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * brief: 对话框销毁消息响应函数。
 * param: --
 * return: --
 */
void DialogItemAndProfileKeys::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.销毁界面中子页面。
	for(unsigned int index=0;index!=PAGES;++index){
		if(IsWindow(_page_dialogs[index].GetSafeHwnd())){
			_page_dialogs[index].DestroyWindow();
		}
	}
}

/**
 * name: OnButtonClicked
 * brief: 用户点击按钮消息响应函数。
 * param: ID - 点击按钮的ID编号。
 * return: --
 */
void DialogItemAndProfileKeys::OnButtonClicked(const unsigned int ID){
	//1.计算当前点击按钮的下标，并且判断计算是否成功。
	const unsigned int index=ID-IDC_BUTTON_PAGE_1;
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
	if(!IsWindow(_page_dialogs[index].GetSafeHwnd())){
		if(!_page_dialogs[index].Create(DialogItemAndProfileKey::IDD,this)){
			return;
		}
	}
	//5.将当前子窗口放入布局，并且判断放入是否成功。
	if(_main_layout->set_item_window(1,&_page_dialogs[index],1)<0){
		return;
	}
	//6.重置所有按钮的选中状态以及所有子页面显示状态。
	for(unsigned int i=0;i!=PAGES;++i){
		//6-1.重置按钮选中状态。
		_page_buttons[i].set_checked(FALSE);
		//6-2.重置页面显示状态。
		if(IsWindow(_page_dialogs[i].GetSafeHwnd())){
			_page_dialogs[i].ShowWindow(SW_HIDE);
		}
	}
	//7.调整当前应该显示的子窗口的位置。
	_page_dialogs[index].MoveWindow(rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height());
	//8.设置当前按钮选中以及页面的显示状态。
	_page_buttons[index].set_checked(TRUE);
	_page_dialogs[index].ShowWindow(SW_SHOW);
}

/**
 * name: OnItemOrProfileButtonClicked
 * breif: 项目或组合按钮点击消息响应函数。
 * param: wParam - 1 项目键 2 组合键。
 *        lParam - 点击的按钮序号。
 * return: 此函数一直返回零。
 */
LRESULT DialogItemAndProfileKeys::OnItemOrProfileButtonClicked(
	WPARAM wParam,LPARAM lParam){
	//1.向所有的子对话框发送按钮点击消息。
	for(unsigned int index=0;index!=PAGES;++index){
		//1-1.如果当前子对话框尚未创建。
		if(!IsWindow(_page_dialogs[index].GetSafeHwnd())){
			//什么都不做。
		}
		//1-2.如果当前子对话框已经创建。
		else{
			LRESULT result=_page_dialogs[index].SendMessage(
				WM_ITEM_OR_PROFILE_BUTTON_CLICKED,wParam,lParam);
			if(1==result){
				OnButtonClicked(IDC_BUTTON_PAGE_1+index);
			}
		}
	}
	//2.向父窗口发送相应消息。
	GetParent()->SendMessage(
		WM_ITEM_OR_PROFILE_BUTTON_CLICKED,wParam,lParam);
	//3.程序运行到此直接返回零。
	return(0);
}

/**
 * name: init_controls
 * brief: 初始化当前界面中所有控件。
 * param: --
 * return: --
 */
void DialogItemAndProfileKeys::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化控件。
	//2-1.初始化按钮。
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//2-2.初始化子对话框。
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index].Create(DialogItemAndProfileKey::IDD,this);
		assert(IsWindow(_page_dialogs[index].GetSafeHwnd()));
	}
	//3.初始化布局。
	//3-1.初始化子布局1。
	for(unsigned int index=0;index!=5;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.初始化主布局。
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//4.重置当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//5.更新子对话框，并显示默认子对话框。
	//5-1.声明当前操作所需变量。。
	BOOL is_dialog_visiable=FALSE;
	//5-2.对申请参数按序号排序（以便在子对话框更新时能更快的更新数据）。
	Applications::instance()->sort_by_item_no();
	//5-3.更新对话框中控件数据，并且统计是否有子对话框被显示。
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index].SendMessage(WM_UPDATE_DATA_FOR_CONTROLS);
		if(_page_buttons[index].get_checked()){
			is_dialog_visiable=TRUE;
		}
	}
	//5-4.如果当前没有子对话框被显示，则显示默认子对话框。
	if(!is_dialog_visiable){
		OnButtonClicked(IDC_BUTTON_PAGE_1);
	}
}