// source-code/ui/common/DialogItemAndProfileKey.cpp : implementation file
//

#include"stdafx.h"
#include"DialogItemAndProfileKey.h"
#include"DialogItemAndProfileKeys.h"
#include"afxdialogex.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../control/MarkButton.h"
#include"../../data/common/Item.h"
#include"../UiCustom.h"
#include"../../data/common/Items.h"
#include<assert.h>

//DialogItemAndProfileKey dialog
IMPLEMENT_DYNAMIC(DialogItemAndProfileKey,DialogPageBase)

/**
 * name: DialogItemAndProfileKey
 * breif: 构造函数。
 * param: pParent - 指向父窗口。
 * return: --
 */
DialogItemAndProfileKey::DialogItemAndProfileKey(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogItemAndProfileKey::IDD,pParent)
	,_mode(0)
	,_page_no(0)
	,_mark_buttons(new MarkButton[BUTTONS])
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_child_layout_5(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogItemAndProfileKey
 * brief: 析构函数。
 * param: --
 * return:
 */
DialogItemAndProfileKey::~DialogItemAndProfileKey(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _child_layout_5;
	delete[] _mark_buttons;
}

/**
 * name: set_mode
 * brief: 设置当前对话框模式。
 * param: mode - 对话框模式。
 * =============================================
 *        1   配置项目模式    用于设置项目键。
 *        2   配置组合模式    用于设置组合键。
 *        3   样本设置模式    用于样本设置。
 * =============================================
 * return: --
 */
void DialogItemAndProfileKey::set_mode(const int mode){
	assert((mode>=1)&&(mode<=3));
	_mode=mode;
}

/**
 * name: set_page_no
 * brief: 设置当前对话框页码。
 * param: page_no - 页码（0~9）。
 * return: --
 */
void DialogItemAndProfileKey::set_page_no(const int page_no){
	assert((page_no>=0)&&(page_no<static_cast<int>(
		DialogItemAndProfileKeys::PAGES)));
	_page_no=page_no;
}

/**
 * name: DoDataExchange
 * brief: 支持DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogItemAndProfileKey::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	for(unsigned int index=0;index!=BUTTONS;++index){
		DDX_Control(pDX,IDC_BUTTON_1+index,_mark_buttons[index]);
	}
}

/**
 * name: OnInitDialog
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL DialogItemAndProfileKey::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	///////////////////////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	//2.为对话框中控件更新数据。
	//update_data_for_controls();
	///////////////////////////////////////////////////////////////////
	return(TRUE);  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogItemAndProfileKey,DialogPageBase)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(IDC_BUTTON_1,IDC_BUTTON_80,&DialogItemAndProfileKey::OnButtonClicked)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS,&DialogItemAndProfileKey::OnUpdateDataForControls)
	ON_MESSAGE(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,&DialogItemAndProfileKey::OnItemOrProfileButtonClicked)
END_MESSAGE_MAP()

/**
 * name: OnSize
 * breif: 对话框尺寸变更消息相应函数。
 * param: nType - 指定重新调整尺寸时的情况类型。
 *        cx - 当前对话框客户区宽度。
 *        cy - 当前对话框客户区高度。
 * return: --
 */
void DialogItemAndProfileKey::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_main_layout->resize(cx,cy);
}

/**
 * name: OnButtonClicked
 * brief: 用户点击按钮消息响应函数。
 * param: ID - 点击按钮的ID编号。
 * return: --
 */
void DialogItemAndProfileKey::OnButtonClicked(const unsigned int ID){
	//1.如果当前对话框处于模式1下。
	if(1==_mode){
		button_clicked_in_mode_1(ID);
	}
	//..如果当前对话框处于其它模式。
	else{
	}
}

/**
 * name: OnUpdateDataForControls
 * brief: 更新控件数据消息相应函数。
 * param: wParam - 无意义。
 *        lParam - 无意义。
 * return: 此函数一直返回零。
 */
LRESULT DialogItemAndProfileKey::OnUpdateDataForControls(
	WPARAM /*wParam*/,LPARAM /*lParam*/){
	update_data_for_controls();
	return(0);
}

/**
 * name: OnItemOrProfileButtonClicked
 * breif: 项目获组合按钮点击消息响应函数。
 * param: wParam - 1 项目键 2 组合键。
 *        lParam - 点击的按钮序号。
 * return: 模式1下：当当前函数处理了指定序号的按钮，则返回1，否则返回0。
 *         其它情况下： 此函数一直返回0。
 */
LRESULT DialogItemAndProfileKey::OnItemOrProfileButtonClicked(
	WPARAM wParam,LPARAM lParam){
	//1.如果当前对话框处于模式1。
	if(1==_mode){
		return(item_or_profile_button_clicked_in_mode_1(
			static_cast<int>(wParam),static_cast<int>(lParam)));
	}
	//..如果当前对话框处于其它模式。
	else{
		//此处不进行任何处理。
		return(0);
	}
}

/**
 * name: init_controls
 * brief: 初始化对话框中控件。
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::init_controls(){
	//1.如果当前对话框模式为添加项目模式。
	if(1==_mode){
		init_controls_in_mode_1();
	}
	//..如果当前对话框模式为其它。
	else{
		//1.声明初始化当前操作所需变量。
		CRect rect;
		GetClientRect(rect);
		Theme *theme=Theme::instance();
		//2.初始化按钮。
		for(unsigned int index=0;index!=BUTTONS;++index){
			//2-1.设置按钮标题颜色。
			_mark_buttons[index].set_text_color(255,50,50,50);
			//2-2.设置按钮背景图片。
			_mark_buttons[index].load_background_image(theme->get_image(31),1,4);
			_mark_buttons[index].set_background_image_stretching_factors(5,5,5,5);
			//2-..隐藏不需要的按钮。
			if(index>=(ITEM_BUTTONS+PROFILE_BUTTONS)){
				_mark_buttons[index].ShowWindow(SW_HIDE);
			}
		}
		//3.初始化布局。
		//3-1.加入项目键。
		for(unsigned int col=0;col!=(ITEM_BUTTONS/5);++col){
			_child_layout_1->add_window(&_mark_buttons[col],1);
			_child_layout_2->add_window(&_mark_buttons[(
				ITEM_BUTTONS/5)+col],1);
			_child_layout_3->add_window(&_mark_buttons[(
				2*(ITEM_BUTTONS/5))+col],1);
			_child_layout_4->add_window(&_mark_buttons[(
				3*(ITEM_BUTTONS/5))+col],1);
			_child_layout_5->add_window(&_mark_buttons[(
				4*(ITEM_BUTTONS/5))+col],1);
			if(col!=(ITEM_BUTTONS/5)-1){
				_child_layout_1->add_spacing(1);
				_child_layout_2->add_spacing(1);
				_child_layout_3->add_spacing(1);
				_child_layout_4->add_spacing(1);
				_child_layout_5->add_spacing(1);
			}
		}
		//3-2.设置项目键与组合键空白。
		_child_layout_1->add_spacing(20);
		_child_layout_2->add_spacing(20);
		_child_layout_3->add_spacing(20);
		_child_layout_4->add_spacing(20);
		_child_layout_5->add_spacing(20);
		//3-3.加入组合键。
		for(unsigned int col=0;col!=(PROFILE_BUTTONS/5);++col){
			_child_layout_1->add_window(&_mark_buttons[
				ITEM_BUTTONS+col],1);
			_child_layout_2->add_window(&_mark_buttons[
				ITEM_BUTTONS+(PROFILE_BUTTONS/5)+col],1);
			_child_layout_3->add_window(&_mark_buttons[
				ITEM_BUTTONS+(2*(PROFILE_BUTTONS/5))+col],1);
			_child_layout_4->add_window(&_mark_buttons[
				ITEM_BUTTONS+(3*(PROFILE_BUTTONS/5))+col],1);
			_child_layout_5->add_window(&_mark_buttons[
				ITEM_BUTTONS+(4*(PROFILE_BUTTONS/5))+col],1);
			if(col!=(PROFILE_BUTTONS/5)-1){
				_child_layout_1->add_spacing(1);
				_child_layout_2->add_spacing(1);
				_child_layout_3->add_spacing(1);
				_child_layout_4->add_spacing(1);
				_child_layout_5->add_spacing(1);
			}
		}
		//3-4.设置主布局。
		_main_layout->add_spacing(2);
		_main_layout->add_spacing(10);
		_main_layout->add_layout(_child_layout_1,1);
		_main_layout->add_spacing(1);
		_main_layout->add_layout(_child_layout_2,1);
		_main_layout->add_spacing(1);
		_main_layout->add_layout(_child_layout_3,1);
		_main_layout->add_spacing(1);
		_main_layout->add_layout(_child_layout_4,1);
		_main_layout->add_spacing(1);
		_main_layout->add_layout(_child_layout_5,1);
		//4.调整当前布局尺寸。
		_main_layout->resize(rect.Width(),rect.Height());
	}
}

/**
 * name: init_controls_in_mode_1
 * brief: 对话框处于模式1时，初始化对话框中控件。
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::init_controls_in_mode_1(){
	//1.声明初始化当前操作所需变量。
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	CString mark_text(_T(""));
	//2.初始化按钮。
	for(unsigned int index=0;index!=BUTTONS;++index){
		//2-1.将不是项目按键的按键隐藏（去掉组合键）。
		if(index>=ITEM_BUTTONS){
			_mark_buttons[index].EnableWindow(FALSE);
			_mark_buttons[index].ShowWindow(SW_HIDE);
		}
		//2-2.如果当前是项目按键。
		else{
			//2-2-1.设置按钮文本。
			_mark_buttons[index].set_text_color(255,50,50,50);
			_mark_buttons[index].set_mark_text_color(255,50,50,50);
			_mark_buttons[index].set_mark_text_alignment(
				MarkButton::ALIGNMENT_RIGHT|MarkButton::ALIGNMENT_BOTTOM);
			mark_text.Format(_T("%d"),get_item_button_no(index));
			_mark_buttons[index].set_mark_text(mark_text);
			//2-2-2.设置按钮背景图片。
			_mark_buttons[index].load_background_image(theme->get_image(31),1,4);
			_mark_buttons[index].set_background_image_stretching_factors(5,5,5,5);
			//_mark_buttons[index].EnableWindow(FALSE);
		}
	}
	//3.初始化布局。
	//3-1.将项目按键加入布局。
	for(unsigned int col=0;col!=(ITEM_BUTTONS/5);++col){
		_child_layout_1->add_window(&_mark_buttons[col],1);
		_child_layout_2->add_window(&_mark_buttons[(ITEM_BUTTONS/5)+col],1);
		_child_layout_3->add_window(&_mark_buttons[(2*(ITEM_BUTTONS/5))+col],1);
		_child_layout_4->add_window(&_mark_buttons[(3*(ITEM_BUTTONS/5))+col],1);
		_child_layout_5->add_window(&_mark_buttons[(4*(ITEM_BUTTONS/5))+col],1);
		if(col!=(ITEM_BUTTONS/5)-1){
			_child_layout_1->add_spacing(1);
			_child_layout_2->add_spacing(1);
			_child_layout_3->add_spacing(1);
			_child_layout_4->add_spacing(1);
			_child_layout_5->add_spacing(1);
		}
	}
	//3-2.设置主布局。
	_main_layout->add_spacing(2);
	_main_layout->add_spacing(10);
	_main_layout->add_layout(_child_layout_1,1);
	_main_layout->add_spacing(1);
	_main_layout->add_layout(_child_layout_2,1);
	_main_layout->add_spacing(1);
	_main_layout->add_layout(_child_layout_3,1);
	_main_layout->add_spacing(1);
	_main_layout->add_layout(_child_layout_4,1);
	_main_layout->add_spacing(1);
	_main_layout->add_layout(_child_layout_5,1);
	//4.调整当前布局尺寸。
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: update_data_for_controls
 * brief: 为对话框中控件更新数据。
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::update_data_for_controls(){
	//1.如果当前对话框模式为添加项目模式。
	if(1==_mode){
		update_data_for_controls_in_mode_1();
	}
	//..如果当前对话框模式为其它模式。
	else{
		//此时什么也不做。
	}
}

/**
 * name: update_data_for_controls_in_mode_1
 * breif: 在对话框为模式1下，为当前对话框中控件更新数据。
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::update_data_for_controls_in_mode_1(){
	//1.声明当前操作所需变量。
	static BOOL is_button_checked=FALSE;
	if(0==_page_no){//如果当前第一页更新时，则重置标记变量。
		is_button_checked=FALSE;
	}
	//2.遍历当前对话框中按钮，为按钮赋值。
	for(unsigned int index=0;index!=ITEM_BUTTONS;++index){//当前模式下,更新数据时，只对项目按键更新即可。
		//2-1.获取当前按钮对应的项目申请信息。
		Items::PtrToCItem item=Items::instance()->get_by_no(
			get_item_button_no(index));
		//2-2.如果尝试获取当前按钮对应的项目申请信息失败。
		if(!static_cast<bool>(item)){
			_mark_buttons[index].SetWindowText(_T(""));
			_mark_buttons[index].EnableWindow(TRUE);
			if(!is_button_checked){
				button_clicked_in_mode_1(IDC_BUTTON_1+index);
				is_button_checked=TRUE;
			}
		}
		//2-3.如果尝试获取当前按钮对应的项目申请信息成功。
		else{
			_mark_buttons[index].SetWindowText(item->get_name());//此时应该显示名称，而不是别名。
			_mark_buttons[index].EnableWindow(FALSE);
			_mark_buttons[index].set_checked(FALSE);
		}
	}
}

/**
 * name: button_clicked_in_mode_1
 * brief: 对话框在模式1下点击按钮。
 * param: ID - 点击的按钮ID。
 * return: --
 */
void DialogItemAndProfileKey::button_clicked_in_mode_1(const unsigned int ID){
	//1.计算当前点击的按钮索引。
	unsigned int index=ID-IDC_BUTTON_1;
	if(index>=ITEM_BUTTONS){//如果当前按钮不是项目按钮则直接返回。
		return;
	}
	//2.如果当前页面中标记按钮处于选中状态，则直接返回。
	if(_mark_buttons[index].get_checked()){
		return;
	}
	//3.向父窗口发送项目按钮点击消息。
	GetParent()->SendMessage(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,static_cast<WPARAM>(1),
		static_cast<LPARAM>(get_item_button_no(index)));
}

/**
 * name: item_or_profile_button_clicked_in_mode_1
 * breif: 对话框在模式1下点击项目或组合按钮。
 * param: button_type - 当前点击的按钮类型（1.项目键 2.组合键）。
 *        button_no - 点击按钮的序号。
 * return: 如果当前处理函数处理了指定序号的按钮，则返回1，否则返回0。
 */
LRESULT DialogItemAndProfileKey::item_or_profile_button_clicked_in_mode_1(
	const int button_type,const int button_no){
	//1.如果当前点击的为项目按键。
	if(1==button_type){
		//1-1.声明当前操作所需变量。
		LRESULT result=0;
		//1-2.遍历标记按钮数组，设置标记按钮状态。
		for(unsigned int index=0;index!=ITEM_BUTTONS;++index){
			if(button_no==get_item_button_no(index)){
				_mark_buttons[index].set_checked(TRUE);
				result=1;
			}else{
				_mark_buttons[index].set_checked(FALSE);
			}
		}
		//1-3.返回操作结果。
		return(result);
	}
	//2.如果当前点击的为组合按键。
	else if(2==button_type){
		//此时什么都不做。
		return(0);
	}
	//3.如果当前点击的为其它按键。
	else{
		//此时什么都不做。
		return(0);
	}
}

/**
 * name: get_item_button_no
 * breif: 计算项目按钮序号。
 * param: index - 项目按钮索引。
 * return: 返回计算的项目按钮序号。
 */
int DialogItemAndProfileKey::get_item_button_no(const unsigned int index) const{
	//remark.此时调用函数必须确保index为项目按钮合法的下标。
	return(ITEM_BUTTONS*_page_no+index+1);
}