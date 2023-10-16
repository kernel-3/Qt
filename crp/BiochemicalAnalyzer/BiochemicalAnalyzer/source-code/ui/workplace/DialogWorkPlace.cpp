//source-code/ui/DialogWorkPlace.cpp : implementation file
//

#include"stdafx.h"
#include"DialogWorkPlace.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"DialogTestSelection.h"
#include"DialogDataReview.h"

// DialogWorkPlace dialog
IMPLEMENT_DYNAMIC(DialogWorkPlace,DialogBase)

/**
 * name: DialogWorkPlace
 * brief: 构造函数。
 * param: pParent - 指向父窗口。
 * return: --
 */
DialogWorkPlace::DialogWorkPlace(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogWorkPlace::IDD,pParent)
	,_page_buttons(new MtImageButton[PAGES])
	,_page_dialogs(new DialogBase*[PAGES])
	,_child_layout_1(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index]=0;
		if(0==index){
			_page_dialogs[index]=new DialogTestSelection;
		}else if(1==index){
			_page_dialogs[1]=new DialogDataReview;
		}
	}
}

/**
 * name: ~DialogWorkPlace
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogWorkPlace::~DialogWorkPlace(){
	delete _main_layout;
	delete _child_layout_1;
	for(unsigned int index=0;index!=PAGES;++index){
		if(0!=_page_dialogs[index]){
			delete _page_dialogs[index];
		}
	}
	delete[] _page_dialogs;
	delete[] _page_buttons;
}

/**
 * name: DoDataExchange
 * brief: 
 * param: pDX -
 * return: --
 */
void DialogWorkPlace::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
	for(unsigned int index=0;index!=PAGES;++index){
		DDX_Control(pDX,IDC_BUTTON_TEST_SELECTION+index,_page_buttons[index]);
	}
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogWorkPlace::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	//2.触发消息，显示“Test Selection”页面。
	OnButtonClicked(IDC_BUTTON_TEST_SELECTION);
	/////////////////////////////////////////////////////////////////
	return(TRUE); //return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogWorkPlace,DialogBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_BUTTON_TEST_SELECTION,IDC_BUTTON_DATA_REVIEW,&DialogWorkPlace::OnButtonClicked)
END_MESSAGE_MAP()

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogWorkPlace::OnSize(UINT nType,int cx,int cy){
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
void DialogWorkPlace::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.销毁子对话框。
	for(unsigned int index=0;index!=PAGES;++index){
		if((0!=_page_dialogs[index])&&(
			IsWindow(_page_dialogs[index]->GetSafeHwnd()))){
			_page_dialogs[index]->DestroyWindow();
		}
	}
}

/**
 * name: OnButtonClicked
 * brief: 用户点击按钮消息响应函数。
 * param: ID - 点击按钮的ID编号。
 * return: --
 */
void DialogWorkPlace::OnButtonClicked(const unsigned int ID){
	//1.计算当前点击按钮的下标，并且判断计算是否成功。
	const unsigned int index=ID-IDC_BUTTON_TEST_SELECTION;
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
	if(!IsWindow(_page_dialogs[index]->GetSafeHwnd())){
		//4-1.计算当前页面ID。
		unsigned int page_dialog_id=0;
		if(0==index){
			page_dialog_id=DialogTestSelection::IDD;
		}else if(1==index){
			page_dialog_id=DialogDataReview::IDD;
		}else{
			return;
		}
		//4-2.创建当前子对话框，并且判断创建是否成功。
		if(!_page_dialogs[index]->Create(page_dialog_id,this)){
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
 * brief: 初始化当前对话框中控件。
 * param: --
 * return: --
 */
void DialogWorkPlace::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化当前对话框中按钮控件。
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//3.初始化当前对话框中的布局。
	//3-1.初始化子布局。
	for(unsigned int index=0;index!=PAGES;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.初始化主布局。
	_main_layout->set_margin(10,10,10,0);
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//3-3.调整主布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}