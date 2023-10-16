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
 * brief: ���캯����
 * param: mode - ģʽ
 * =============================================
 *        1   ������Ŀģʽ    ����������Ŀ����
 *        2   �������ģʽ    ����������ϼ���
 *        3   ��������ģʽ    �����������á�
 * =============================================
 *		  pParent - ָ�򸸴��ڡ�
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
 * brief: ����������
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
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogItemAndProfileKeys::OnInitDialog(){
	DialogBase::OnInitDialog();
	///////////////////////////////////////////////////////
	//1.��ʼ���Ի����пؼ���
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
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogItemAndProfileKeys::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * brief: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogItemAndProfileKeys::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.���ٽ�������ҳ�档
	for(unsigned int index=0;index!=PAGES;++index){
		if(IsWindow(_page_dialogs[index].GetSafeHwnd())){
			_page_dialogs[index].DestroyWindow();
		}
	}
}

/**
 * name: OnButtonClicked
 * brief: �û������ť��Ϣ��Ӧ������
 * param: ID - �����ť��ID��š�
 * return: --
 */
void DialogItemAndProfileKeys::OnButtonClicked(const unsigned int ID){
	//1.���㵱ǰ�����ť���±꣬�����жϼ����Ƿ�ɹ���
	const unsigned int index=ID-IDC_BUTTON_PAGE_1;
	if(index>=PAGES){
		return;
	}
	//2.�����ǰ��ť����ѡ��״̬������ֱ�ӷ��ء�
	if(_page_buttons[index].get_checked()){
		return;
	}
	//3.���㵱ǰӦ����ʾ���Ӵ��ڵ�λ�ã������жϼ����Ƿ�ɹ���
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(1,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.�����ǰӦ����ʾ����ҳ����δ�������򴴽�֮�������жϴ����Ƿ�ɹ���
	if(!IsWindow(_page_dialogs[index].GetSafeHwnd())){
		if(!_page_dialogs[index].Create(DialogItemAndProfileKey::IDD,this)){
			return;
		}
	}
	//5.����ǰ�Ӵ��ڷ��벼�֣������жϷ����Ƿ�ɹ���
	if(_main_layout->set_item_window(1,&_page_dialogs[index],1)<0){
		return;
	}
	//6.�������а�ť��ѡ��״̬�Լ�������ҳ����ʾ״̬��
	for(unsigned int i=0;i!=PAGES;++i){
		//6-1.���ð�ťѡ��״̬��
		_page_buttons[i].set_checked(FALSE);
		//6-2.����ҳ����ʾ״̬��
		if(IsWindow(_page_dialogs[i].GetSafeHwnd())){
			_page_dialogs[i].ShowWindow(SW_HIDE);
		}
	}
	//7.������ǰӦ����ʾ���Ӵ��ڵ�λ�á�
	_page_dialogs[index].MoveWindow(rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height());
	//8.���õ�ǰ��ťѡ���Լ�ҳ�����ʾ״̬��
	_page_buttons[index].set_checked(TRUE);
	_page_dialogs[index].ShowWindow(SW_SHOW);
}

/**
 * name: OnItemOrProfileButtonClicked
 * breif: ��Ŀ����ϰ�ť�����Ϣ��Ӧ������
 * param: wParam - 1 ��Ŀ�� 2 ��ϼ���
 *        lParam - ����İ�ť��š�
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogItemAndProfileKeys::OnItemOrProfileButtonClicked(
	WPARAM wParam,LPARAM lParam){
	//1.�����е��ӶԻ����Ͱ�ť�����Ϣ��
	for(unsigned int index=0;index!=PAGES;++index){
		//1-1.�����ǰ�ӶԻ�����δ������
		if(!IsWindow(_page_dialogs[index].GetSafeHwnd())){
			//ʲô��������
		}
		//1-2.�����ǰ�ӶԻ����Ѿ�������
		else{
			LRESULT result=_page_dialogs[index].SendMessage(
				WM_ITEM_OR_PROFILE_BUTTON_CLICKED,wParam,lParam);
			if(1==result){
				OnButtonClicked(IDC_BUTTON_PAGE_1+index);
			}
		}
	}
	//2.�򸸴��ڷ�����Ӧ��Ϣ��
	GetParent()->SendMessage(
		WM_ITEM_OR_PROFILE_BUTTON_CLICKED,wParam,lParam);
	//3.�������е���ֱ�ӷ����㡣
	return(0);
}

/**
 * name: init_controls
 * brief: ��ʼ����ǰ���������пؼ���
 * param: --
 * return: --
 */
void DialogItemAndProfileKeys::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ���ؼ���
	//2-1.��ʼ����ť��
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//2-2.��ʼ���ӶԻ���
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index].Create(DialogItemAndProfileKey::IDD,this);
		assert(IsWindow(_page_dialogs[index].GetSafeHwnd()));
	}
	//3.��ʼ�����֡�
	//3-1.��ʼ���Ӳ���1��
	for(unsigned int index=0;index!=5;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.��ʼ�������֡�
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.�����ӶԻ��򣬲���ʾĬ���ӶԻ���
	//5-1.������ǰ���������������
	BOOL is_dialog_visiable=FALSE;
	//5-2.�������������������Ա����ӶԻ������ʱ�ܸ���ĸ������ݣ���
	Applications::instance()->sort_by_item_no();
	//5-3.���¶Ի����пؼ����ݣ�����ͳ���Ƿ����ӶԻ�����ʾ��
	for(unsigned int index=0;index!=PAGES;++index){
		_page_dialogs[index].SendMessage(WM_UPDATE_DATA_FOR_CONTROLS);
		if(_page_buttons[index].get_checked()){
			is_dialog_visiable=TRUE;
		}
	}
	//5-4.�����ǰû���ӶԻ�����ʾ������ʾĬ���ӶԻ���
	if(!is_dialog_visiable){
		OnButtonClicked(IDC_BUTTON_PAGE_1);
	}
}