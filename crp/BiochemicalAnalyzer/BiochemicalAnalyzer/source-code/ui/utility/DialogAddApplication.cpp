// source-code/ui/utility/DialogAddApplication.cpp : implementation file
//

#include"stdafx.h"
#include"DialogAddApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../common/DialogMessageBox.h"
#include"../common/DialogItemAndProfileKey.h"
#include"../common/DialogItemAndProfileKeys.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../UiCustom.h"
#include"../../data/utility/Application.h"
#include"../../data/utility/Applications.h"
#include"../../data/common/Item.h"
#include"../../data/utility/AnalyzeApplication.h"
#include"../../global/Database.h"
#include"../../global/DatabaseManager.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../data/utility/CalibrationApplication.h"
#include"../../data/utility/RangeApplication.h"
#include"../../data/utility/StandardApplication.h"
#include"../../data/common/Items.h"
#include"../../data/common/Module.h"
#include"../../data/common/SpecimenType.h"
#include"../../data/common/Modules.h"
#include"../../data/common/SpecimenTypes.h"
#include"../../data/utility/ApplicationParameter.h"
#include"../../data/utility/ApplicationParameters.h"
#include<vector>

//DialogAddApplication dialog

IMPLEMENT_DYNAMIC(DialogAddApplication,DialogModalBase)

/**
 * name: DialogAddApplication
 * breif: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogAddApplication::DialogAddApplication(CWnd *pParent/*=NULL*/)
	:DialogModalBase(DialogAddApplication::IDD,pParent)
	,_module_id(0)
	,_specimen_type_id(0)
	,_item_id(0)
	,_no_static(new MtImageStatic)
	,_test_name_static(new MtImageStatic)
	,_app_code_static(new MtImageStatic)
	,_no_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_test_name_edit(new MtImageEdit)
	,_app_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_child_dialog(new DialogItemAndProfileKeys(1))
	,_ok_button(new MtImageButton)
	,_cancel_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogAddApplication
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogAddApplication::~DialogAddApplication(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _no_static;
	delete _test_name_static;
	delete _app_code_static;
	delete _no_edit;
	delete _test_name_edit;
	delete _app_code_edit;
	delete _child_dialog;
	delete _ok_button;
	delete _cancel_button;
}

/**
 * name: get_module_id
 * breif: 获取模块标识。
 * param: --
 * return: 返回模块标识。
 */
int DialogAddApplication::get_module_id() const{
	return(_module_id);
}

/**
 * name: get_specimen_type_id
 * breif: 获取样本类型标识。
 * param: --
 * return: 返回样本类型标识。
 */
int DialogAddApplication::get_specimen_type_id() const{
	return(_specimen_type_id);
}

/**
 * name: get_item_id
 * brief: 获取项目标识。
 * param: --
 * return: 返回项目标识。
 */
int DialogAddApplication::get_item_id() const{
	return(_item_id);
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV。
 * param: pDX -
 * return: --
 */
void DialogAddApplication::DoDataExchange(CDataExchange *pDX){
	DialogModalBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NO,*_no_static);
	DDX_Control(pDX,IDC_STATIC_TEST_NAME,*_test_name_static);
	DDX_Control(pDX,IDC_STATIC_APP_CODE,*_app_code_static);
	DDX_Control(pDX,IDC_EDIT_NO,*_no_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_NAME,*_test_name_edit);
	DDX_Control(pDX,IDC_EDIT_APP_CODE,*_app_code_edit);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
	DDX_Control(pDX,IDC_BUTTON_CANCEL,*_cancel_button);
}

/**
 * name: OnInitDialog
 * breif: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogAddApplication::OnInitDialog(){
	DialogModalBase::OnInitDialog();
	//TODO:Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.初始化当前对话框窗口。
	init_window();
	//2.初始化当前对话框中控件。
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogAddApplication,DialogModalBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,&DialogAddApplication::OnItemOrProfileButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogAddApplication::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL,&DialogAddApplication::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

//DialogAddApplication message handlers

/**
 * name: OnSize
 * brief: 对话框尺寸调整消息响应函数，此处用来
 *        更新对话框中布局信息。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogAddApplication::OnSize(UINT nType,int cx,int cy){
	DialogModalBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.调整当前布局尺寸。
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * breif: 对话框销毁消息响应函数。
 * param: --
 * return: --
 */
void DialogAddApplication::OnDestroy(){
	DialogModalBase::OnDestroy();
	//TODO: Add your message handler code here
	//1.如果当前子对话框已经创建，则进行销毁操作。
	if(0!=_child_dialog->GetSafeHwnd()){
		_child_dialog->DestroyWindow();
	}
}

/**
 * name: OnItemOrProfileButtonClicked
 * brief: 用户点击项目或组合按钮消息响应函数。
 * param: wParam - 按键类型（1.项目 2.组合）。
 *        lParam - 按键序号。
 * return: 此函数一直返回零。
 */
LRESULT DialogAddApplication::OnItemOrProfileButtonClicked(WPARAM wParam,LPARAM lParam){
	//1.如果当前按键为项目按键。
	if(1==static_cast<int>(wParam)){
		CString item_no(_T(""));
		item_no.Format(_T("%d"),static_cast<int>(lParam));
		_no_edit->SetWindowText(item_no);
	}
	//2.如果当前按键为其它按键。
	else{
		//此时什么也不做。
	}
	//3.程序运行到此，直接返回零。
	return(0);
}

/**
 * name: OnBnClickedButtonOk
 * brief: 用户点击“确定”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogAddApplication::OnBnClickedButtonOk(){
	//TODO: Add your control notification handler code here
	//1.定义。
	typedef std::shared_ptr<Item> PtrToItem;
	typedef std::shared_ptr<ApplicationParameter> PtrToParameter;
	typedef std::vector<PtrToParameter> Parameters;
	//2.检测输入的项目序号是否合法。
	//2-1.获取当前输入的项目序号。
	CString text(_T(""));
	_no_edit->GetWindowText(text);
	//2-2.如果输入的项目序号为空，则提示并返回。
	Theme *theme=Theme::instance();
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING151),this);
		_no_edit->SetFocus();
		return;
	}
	//2-3.检测当前输入的项目序号是否重复。
	Items *items=Items::instance();
	int temp=MtCharacterSet::to_integer(text);
	if(items->is_no_existed(temp)>=0){
		WarningMessageBox(theme->get_string(IDS_STRING160),this);
		_no_edit->SetFocus();
		return;
	}
	//2-4.记录输入的项目序号。
	PtrToItem item(new Item);
	if(!static_cast<bool>(item)){
		WarningMessageBox(theme->get_string(IDS_STRING157),this);
		return;
	}
	item->set_no(temp);
	//3.判断输入的项目名称是否合法。
	//3-1.获取输入的项目名称。
	_test_name_edit->GetWindowText(text);
	//项目名称是否为空将在后面判断。
	//3-2.记录输入的项目名称。
	item->set_name(text);
	item->set_alias(text);//别名默认与项目名称相同。
	//4.检测输入的项目标识是否合法。
	//4-1.获取输入的项目标识。
	_app_code_edit->GetWindowText(text);
	//4-2.如果输入的项目标识为空，则提示并返回。
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING153),this);
		_app_code_edit->SetFocus();
		return;
	}
	//4-3.检测当前输入的项目标识是否重复。
	temp=MtCharacterSet::to_integer(text);
	if(items->is_id_existed(temp)>=0){
		WarningMessageBox(theme->get_string(IDS_STRING155),this);
		_app_code_edit->SetFocus();
		return;
	}
	//4-4.记录输入的项目标识。
	item->set_id(temp);
	//5.设置项目的默认状态。
	item->set_status(Item::STATUS_NORMAL);//项目默认状态为普通状态。
	//6.检测用户输入的项目信息是否合法，如果不合法则提示用户，并直接返回。
	//6-1.检测输入的项目信息是否合法。
	int result=item->is_valid(&text);
	//6-2.如果输入的项目标识不合法。
	if(-1==result){
		WarningMessageBox(text,this);
		_app_code_edit->SetFocus();
		return;
	}
	//6-3.如果输入的项目序号不合法。
	else if(-2==result){
		WarningMessageBox(text,this);
		_no_edit->SetFocus();
		return;
	}
	//6-4.如果输入的项目名称不合法。
	else if(-3==result){
		WarningMessageBox(text,this);
		_test_name_edit->SetFocus();
		return;
	}
	//6-5.如果其它未知原因不合法。
	else if(result<0){
		ErrorMessageBox(theme->get_string(IDS_STRING152),this);
		_test_name_edit->SetFocus();
		return;
	}
	//7.询问用户是否确认保存当前项目。
	if(IDNO==QuestionMessageBox(theme->get_string(
		IDS_STRING164),this)){
		return;
	}
	//8.保存用户输入的项目信息，并为项目生成默认的项目参数，并保存这些参数。
	//8-1.获取目标数据库操作实例指针。
	Database *database=(DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//8-2.启动目标数据库处理事务，并且判断启动是否成功。
	if(database->begin_trans()<0){
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-3.将项目信息提交到数据库中，并且判断提交是否成功。
	if(item->commit(1,(*database))<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-4.为当前项目创建默认参数，并将默认参数提交到数据库中。
	//8-4-1.获取当前系统中模块数量以及样本类型数量。
	const unsigned int module_count=Modules::instance()->get_count();
	const unsigned int specimen_type_count=SpecimenTypes::instance()->get_count();
	if((module_count<=0)||(specimen_type_count<=0)){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING490),this);
		return;
	}
	//8-4-2.为项目创建默认参数，并将默认参数提交到数据库中。
	//8-4-2-1.创建参数存储向量。
	Parameters parameters;
	//8-4-2-2.迭代为项目创建默认参数，将参数提交到数据库中，并保存到向量中。
	for(unsigned int m=0;m!=module_count;++m){
		//a.获取当前的模块标识。
		const int module_id=((Modules::instance())->get_by_index(m))->get_id();
		//b.遍历样本类型，为项目创建相应的默认参数。
		for(unsigned int s=0;s!=specimen_type_count;++s){
			//b-1.获取当前样本类型标识。
			const int specimen_type_id=((SpecimenTypes::instance())->
				get_by_index(s))->get_id();
			//b-2.创建一个默认参数。
			PtrToParameter parameter(new ApplicationParameter(
				module_id,specimen_type_id,item->get_id()));
			//b-3.判断默认参数创建是否合法。
			if(!static_cast<bool>(parameter)){
				database->rollback_trans();
				WarningMessageBox(theme->get_string(IDS_STRING491),this);
				return;
			}
			//b-4.将默认参数设置为默认值。
			parameter->reset_default_value(item->get_no());
			//b-5.向数据库提交默认参数，并且判断提交是否成功。
			if(parameter->commit(1,*database,FALSE)<0){
				database->rollback_trans();
				WarningMessageBox(theme->get_string(IDS_STRING492),this);
				return;
			}
			//b-5.将默认参数保存到向量中。
			parameters.push_back(parameter);
		}
	}
	//8-4-2-3.提交数据库任务,并且判断提交是否成功。
	if(database->commit_trans()<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-5.保存用户输入的项目以及项目参数信息。
	//8-5-1.保存项目信息。
	if((Items::instance())->add(item)<0){
		ErrorMessageBox(theme->get_string(IDS_STRING493),this);
		return;
	}
	//8-5-2.保存项目参数信息。
	for(unsigned int index=0;index!=parameters.size();++index){
		if((ApplicationParameters::instance())->add(parameters[index])<0){
			ErrorMessageBox(theme->get_string(IDS_STRING493),this);
			return;
		}
	}
	//9.保存模块标识、样本类型标识、项目标识。
	_module_id=((Modules::instance())->get_by_index(0))->get_id();
	_specimen_type_id=((SpecimenTypes::instance())->
		get_by_index(0))->get_id();
	_item_id=item->get_id();
	//10.程序运行到此立即退出当前对话框。
	EndDialog(IDOK);
}

/**
 * name: OnBnClickedButtonCancel
 * brief: 用户点击“取消”按钮消息响应函数。
 * param: --
 * return: --
 */
void DialogAddApplication::OnBnClickedButtonCancel(){
	//TODO: Add your control notification handler code here
	EndDialog(IDCANCEL);
}

/**
 * name: init_window
 * brief: 初始化当前对话框窗口。
 * param: --
 * return: --
 */
void DialogAddApplication::init_window(){
	//1.声明初始化当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.设置当前对话框窗口标题。
	SetWindowText(theme->get_string(IDS_STRING148));
}

/**
 * name: init_controls
 * brief: 初始化界面中控件。
 * param: --
 * return: --
 */
void DialogAddApplication::init_controls(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.初始化当前对话框中控件。
	//2-1.初始化静态文本框。
	_no_static->set_text_color(255,50,50,50);
	_no_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_test_name_static->set_text_color(255,50,50,50);
	_test_name_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_app_code_static->set_text_color(255,50,50,50);
	_app_code_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.初始化文本编辑框。	
	_no_edit->set_text_color(50,50,50);
	_no_edit->load_background_image(theme->get_image(29),1,3);
	_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_no_edit->EnableWindow(FALSE);
	_no_edit->SetLimitText(3);
	_test_name_edit->set_text_color(50,50,50);
	_test_name_edit->load_background_image(theme->get_image(29),1,3);
	_test_name_edit->set_background_image_stretching_factors(5,5,5,5);
	_app_code_edit->set_text_color(50,50,50);
	_app_code_edit->load_background_image(theme->get_image(29),1,3);
	_app_code_edit->set_background_image_stretching_factors(5,5,5,5);
	CString text(_T(""));
	text.Format(_T("%d"),(Items::instance())->assign_id());
	_app_code_edit->SetWindowText(text);
	_app_code_edit->SetLimitText(3);
	//2-3.初始化子对话框。
	_child_dialog->Create(DialogItemAndProfileKeys::IDD,this);
	//2-4.初始化按钮。
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	_cancel_button->set_text_color(255,50,50,50);
	_cancel_button->load_background_image(theme->get_image(32),1,4);
	_cancel_button->set_background_image_stretching_factors(5,5,5,5);
	//3.初始化对话框中布局。
	//3-1.初始化子布局1。
	_child_layout_1->add_fixed_window(_no_static,100);
	_child_layout_1->add_fixed_window(_no_edit,50);
	//3-2.初始化子布局2。
	_child_layout_2->add_fixed_window(_test_name_static,100);
	_child_layout_2->add_fixed_window(_test_name_edit,150);
	//3-3.初始化子布局3。
	_child_layout_3->add_fixed_window(_app_code_static,100);
	_child_layout_3->add_fixed_window(_app_code_edit,50);
	//3-4.初始化子布局4。
	_child_layout_4->add_fixed_window(_ok_button,200);
	_child_layout_4->add_stretch(1);
	_child_layout_4->add_fixed_window(_cancel_button,200);
	_child_layout_4->add_stretch(1);
	//3-5.初始主布局。
	_main_layout->set_margin(BORDER_SIZE+5,TITLE_SIZE+5,BORDER_SIZE+5,BORDER_SIZE+5);
	_main_layout->add_fixed_layout(_child_layout_1,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_2,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,24);
	_main_layout->add_spacing(5);
	_main_layout->add_window(_child_dialog,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_4,40);
	//4.重置当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
	//5.显示当前子对话框。
	_child_dialog->ShowWindow(SW_SHOW);
}