//source-code/ui/utility/DialogSystem.cpp: implementation file
//

#include"stdafx.h"
#include"DialogSystem.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"

//DialogSystem dialog
IMPLEMENT_DYNAMIC(DialogSystem,DialogPageBase)

/**
 * name: DialogSystem
 * brief: 构造函数。
 * param: pParent - 指向父对话框。
 * return: --
 */
DialogSystem::DialogSystem(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogSystem::IDD,pParent)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogSystem
 * breif: 析构函数。
 * param: --
 * return: --
 */
DialogSystem::~DialogSystem(){
	delete _main_layout;
}

/**
 * name: DoDataExchange
 * brief: 支持DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogSystem::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
}

/**
 * name: OnInitDialog
 * breif: 初始化对话框虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogSystem::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogSystem,DialogPageBase)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//DialogSystem message handlers

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogSystem::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: init_controls
 * brief: 对对话框中所有控件进行初始化。
 * param: --
 * return: --
 */
void DialogSystem::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	//Theme *theme=Theme::instance();
	//2.初始话对话框中控件。
	//3.初始化对话框中布局。
	_main_layout->add_spacing(BODER_SIZE);
	//4.调整当前对话框布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}