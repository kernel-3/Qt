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
 * breif: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
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
 * brief: ����������
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
 * brief: ���õ�ǰ�Ի���ģʽ��
 * param: mode - �Ի���ģʽ��
 * =============================================
 *        1   ������Ŀģʽ    ����������Ŀ����
 *        2   �������ģʽ    ����������ϼ���
 *        3   ��������ģʽ    �����������á�
 * =============================================
 * return: --
 */
void DialogItemAndProfileKey::set_mode(const int mode){
	assert((mode>=1)&&(mode<=3));
	_mode=mode;
}

/**
 * name: set_page_no
 * brief: ���õ�ǰ�Ի���ҳ�롣
 * param: page_no - ҳ�루0~9����
 * return: --
 */
void DialogItemAndProfileKey::set_page_no(const int page_no){
	assert((page_no>=0)&&(page_no<static_cast<int>(
		DialogItemAndProfileKeys::PAGES)));
	_page_no=page_no;
}

/**
 * name: DoDataExchange
 * brief: ֧��DDX/DDV
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
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogItemAndProfileKey::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	///////////////////////////////////////////////////////////////////
	//1.��ʼ���Ի����пؼ���
	init_controls();
	//2.Ϊ�Ի����пؼ��������ݡ�
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
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogItemAndProfileKey::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_main_layout->resize(cx,cy);
}

/**
 * name: OnButtonClicked
 * brief: �û������ť��Ϣ��Ӧ������
 * param: ID - �����ť��ID��š�
 * return: --
 */
void DialogItemAndProfileKey::OnButtonClicked(const unsigned int ID){
	//1.�����ǰ�Ի�����ģʽ1�¡�
	if(1==_mode){
		button_clicked_in_mode_1(ID);
	}
	//..�����ǰ�Ի���������ģʽ��
	else{
	}
}

/**
 * name: OnUpdateDataForControls
 * brief: ���¿ؼ�������Ϣ��Ӧ������
 * param: wParam - �����塣
 *        lParam - �����塣
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogItemAndProfileKey::OnUpdateDataForControls(
	WPARAM /*wParam*/,LPARAM /*lParam*/){
	update_data_for_controls();
	return(0);
}

/**
 * name: OnItemOrProfileButtonClicked
 * breif: ��Ŀ����ϰ�ť�����Ϣ��Ӧ������
 * param: wParam - 1 ��Ŀ�� 2 ��ϼ���
 *        lParam - ����İ�ť��š�
 * return: ģʽ1�£�����ǰ����������ָ����ŵİ�ť���򷵻�1�����򷵻�0��
 *         ��������£� �˺���һֱ����0��
 */
LRESULT DialogItemAndProfileKey::OnItemOrProfileButtonClicked(
	WPARAM wParam,LPARAM lParam){
	//1.�����ǰ�Ի�����ģʽ1��
	if(1==_mode){
		return(item_or_profile_button_clicked_in_mode_1(
			static_cast<int>(wParam),static_cast<int>(lParam)));
	}
	//..�����ǰ�Ի���������ģʽ��
	else{
		//�˴��������κδ���
		return(0);
	}
}

/**
 * name: init_controls
 * brief: ��ʼ���Ի����пؼ���
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::init_controls(){
	//1.�����ǰ�Ի���ģʽΪ�����Ŀģʽ��
	if(1==_mode){
		init_controls_in_mode_1();
	}
	//..�����ǰ�Ի���ģʽΪ������
	else{
		//1.������ʼ����ǰ�������������
		CRect rect;
		GetClientRect(rect);
		Theme *theme=Theme::instance();
		//2.��ʼ����ť��
		for(unsigned int index=0;index!=BUTTONS;++index){
			//2-1.���ð�ť������ɫ��
			_mark_buttons[index].set_text_color(255,50,50,50);
			//2-2.���ð�ť����ͼƬ��
			_mark_buttons[index].load_background_image(theme->get_image(31),1,4);
			_mark_buttons[index].set_background_image_stretching_factors(5,5,5,5);
			//2-..���ز���Ҫ�İ�ť��
			if(index>=(ITEM_BUTTONS+PROFILE_BUTTONS)){
				_mark_buttons[index].ShowWindow(SW_HIDE);
			}
		}
		//3.��ʼ�����֡�
		//3-1.������Ŀ����
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
		//3-2.������Ŀ������ϼ��հס�
		_child_layout_1->add_spacing(20);
		_child_layout_2->add_spacing(20);
		_child_layout_3->add_spacing(20);
		_child_layout_4->add_spacing(20);
		_child_layout_5->add_spacing(20);
		//3-3.������ϼ���
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
		//3-4.���������֡�
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
		//4.������ǰ���ֳߴ硣
		_main_layout->resize(rect.Width(),rect.Height());
	}
}

/**
 * name: init_controls_in_mode_1
 * brief: �Ի�����ģʽ1ʱ����ʼ���Ի����пؼ���
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::init_controls_in_mode_1(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	CString mark_text(_T(""));
	//2.��ʼ����ť��
	for(unsigned int index=0;index!=BUTTONS;++index){
		//2-1.��������Ŀ�����İ������أ�ȥ����ϼ�����
		if(index>=ITEM_BUTTONS){
			_mark_buttons[index].EnableWindow(FALSE);
			_mark_buttons[index].ShowWindow(SW_HIDE);
		}
		//2-2.�����ǰ����Ŀ������
		else{
			//2-2-1.���ð�ť�ı���
			_mark_buttons[index].set_text_color(255,50,50,50);
			_mark_buttons[index].set_mark_text_color(255,50,50,50);
			_mark_buttons[index].set_mark_text_alignment(
				MarkButton::ALIGNMENT_RIGHT|MarkButton::ALIGNMENT_BOTTOM);
			mark_text.Format(_T("%d"),get_item_button_no(index));
			_mark_buttons[index].set_mark_text(mark_text);
			//2-2-2.���ð�ť����ͼƬ��
			_mark_buttons[index].load_background_image(theme->get_image(31),1,4);
			_mark_buttons[index].set_background_image_stretching_factors(5,5,5,5);
			//_mark_buttons[index].EnableWindow(FALSE);
		}
	}
	//3.��ʼ�����֡�
	//3-1.����Ŀ�������벼�֡�
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
	//3-2.���������֡�
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
	//4.������ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: update_data_for_controls
 * brief: Ϊ�Ի����пؼ��������ݡ�
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::update_data_for_controls(){
	//1.�����ǰ�Ի���ģʽΪ�����Ŀģʽ��
	if(1==_mode){
		update_data_for_controls_in_mode_1();
	}
	//..�����ǰ�Ի���ģʽΪ����ģʽ��
	else{
		//��ʱʲôҲ������
	}
}

/**
 * name: update_data_for_controls_in_mode_1
 * breif: �ڶԻ���Ϊģʽ1�£�Ϊ��ǰ�Ի����пؼ��������ݡ�
 * param: --
 * return: --
 */
void DialogItemAndProfileKey::update_data_for_controls_in_mode_1(){
	//1.������ǰ�������������
	static BOOL is_button_checked=FALSE;
	if(0==_page_no){//�����ǰ��һҳ����ʱ�������ñ�Ǳ�����
		is_button_checked=FALSE;
	}
	//2.������ǰ�Ի����а�ť��Ϊ��ť��ֵ��
	for(unsigned int index=0;index!=ITEM_BUTTONS;++index){//��ǰģʽ��,��������ʱ��ֻ����Ŀ�������¼��ɡ�
		//2-1.��ȡ��ǰ��ť��Ӧ����Ŀ������Ϣ��
		Items::PtrToCItem item=Items::instance()->get_by_no(
			get_item_button_no(index));
		//2-2.������Ի�ȡ��ǰ��ť��Ӧ����Ŀ������Ϣʧ�ܡ�
		if(!static_cast<bool>(item)){
			_mark_buttons[index].SetWindowText(_T(""));
			_mark_buttons[index].EnableWindow(TRUE);
			if(!is_button_checked){
				button_clicked_in_mode_1(IDC_BUTTON_1+index);
				is_button_checked=TRUE;
			}
		}
		//2-3.������Ի�ȡ��ǰ��ť��Ӧ����Ŀ������Ϣ�ɹ���
		else{
			_mark_buttons[index].SetWindowText(item->get_name());//��ʱӦ����ʾ���ƣ������Ǳ�����
			_mark_buttons[index].EnableWindow(FALSE);
			_mark_buttons[index].set_checked(FALSE);
		}
	}
}

/**
 * name: button_clicked_in_mode_1
 * brief: �Ի�����ģʽ1�µ����ť��
 * param: ID - ����İ�ťID��
 * return: --
 */
void DialogItemAndProfileKey::button_clicked_in_mode_1(const unsigned int ID){
	//1.���㵱ǰ����İ�ť������
	unsigned int index=ID-IDC_BUTTON_1;
	if(index>=ITEM_BUTTONS){//�����ǰ��ť������Ŀ��ť��ֱ�ӷ��ء�
		return;
	}
	//2.�����ǰҳ���б�ǰ�ť����ѡ��״̬����ֱ�ӷ��ء�
	if(_mark_buttons[index].get_checked()){
		return;
	}
	//3.�򸸴��ڷ�����Ŀ��ť�����Ϣ��
	GetParent()->SendMessage(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,static_cast<WPARAM>(1),
		static_cast<LPARAM>(get_item_button_no(index)));
}

/**
 * name: item_or_profile_button_clicked_in_mode_1
 * breif: �Ի�����ģʽ1�µ����Ŀ����ϰ�ť��
 * param: button_type - ��ǰ����İ�ť���ͣ�1.��Ŀ�� 2.��ϼ�����
 *        button_no - �����ť����š�
 * return: �����ǰ������������ָ����ŵİ�ť���򷵻�1�����򷵻�0��
 */
LRESULT DialogItemAndProfileKey::item_or_profile_button_clicked_in_mode_1(
	const int button_type,const int button_no){
	//1.�����ǰ�����Ϊ��Ŀ������
	if(1==button_type){
		//1-1.������ǰ�������������
		LRESULT result=0;
		//1-2.������ǰ�ť���飬���ñ�ǰ�ť״̬��
		for(unsigned int index=0;index!=ITEM_BUTTONS;++index){
			if(button_no==get_item_button_no(index)){
				_mark_buttons[index].set_checked(TRUE);
				result=1;
			}else{
				_mark_buttons[index].set_checked(FALSE);
			}
		}
		//1-3.���ز��������
		return(result);
	}
	//2.�����ǰ�����Ϊ��ϰ�����
	else if(2==button_type){
		//��ʱʲô��������
		return(0);
	}
	//3.�����ǰ�����Ϊ����������
	else{
		//��ʱʲô��������
		return(0);
	}
}

/**
 * name: get_item_button_no
 * breif: ������Ŀ��ť��š�
 * param: index - ��Ŀ��ť������
 * return: ���ؼ������Ŀ��ť��š�
 */
int DialogItemAndProfileKey::get_item_button_no(const unsigned int index) const{
	//remark.��ʱ���ú�������ȷ��indexΪ��Ŀ��ť�Ϸ����±ꡣ
	return(ITEM_BUTTONS*_page_no+index+1);
}