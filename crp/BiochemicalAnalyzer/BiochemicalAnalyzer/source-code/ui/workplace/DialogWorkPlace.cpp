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
 * brief: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
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
 * brief: ����������
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
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogWorkPlace::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.��ʼ���Ի����пؼ���
	init_controls();
	//2.������Ϣ����ʾ��Test Selection��ҳ�档
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
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogWorkPlace::OnSize(UINT nType,int cx,int cy){
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
void DialogWorkPlace::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.�����ӶԻ���
	for(unsigned int index=0;index!=PAGES;++index){
		if((0!=_page_dialogs[index])&&(
			IsWindow(_page_dialogs[index]->GetSafeHwnd()))){
			_page_dialogs[index]->DestroyWindow();
		}
	}
}

/**
 * name: OnButtonClicked
 * brief: �û������ť��Ϣ��Ӧ������
 * param: ID - �����ť��ID��š�
 * return: --
 */
void DialogWorkPlace::OnButtonClicked(const unsigned int ID){
	//1.���㵱ǰ�����ť���±꣬�����жϼ����Ƿ�ɹ���
	const unsigned int index=ID-IDC_BUTTON_TEST_SELECTION;
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
	if(!IsWindow(_page_dialogs[index]->GetSafeHwnd())){
		//4-1.���㵱ǰҳ��ID��
		unsigned int page_dialog_id=0;
		if(0==index){
			page_dialog_id=DialogTestSelection::IDD;
		}else if(1==index){
			page_dialog_id=DialogDataReview::IDD;
		}else{
			return;
		}
		//4-2.������ǰ�ӶԻ��򣬲����жϴ����Ƿ�ɹ���
		if(!_page_dialogs[index]->Create(page_dialog_id,this)){
			return;
		}
	}
	//5.����ǰ�Ӵ��ڷ��벼�֣������жϷ����Ƿ�ɹ���
	if(_main_layout->set_item_window(1,_page_dialogs[index],1)<0){
		return;
	}
	//6.�������а�ť��ѡ��״̬�Լ�������ҳ����ʾ״̬��
	for(unsigned int i=0;i!=PAGES;++i){
		//6-1.���ð�ťѡ��״̬��
		_page_buttons[i].set_checked(FALSE);
		//6-2.����ҳ����ʾ״̬��
		if(IsWindow(_page_dialogs[i]->GetSafeHwnd())){
			_page_dialogs[i]->ShowWindow(SW_HIDE);
		}
	}
	//7.������ǰӦ����ʾ���Ӵ��ڵ�λ�á�
	_page_dialogs[index]->MoveWindow(rect.get_left(),rect.get_top(),
		rect.get_width(),rect.get_height());
	//8.���õ�ǰ��ťѡ���Լ�ҳ�����ʾ״̬��
	_page_buttons[index].set_checked(TRUE);
	_page_dialogs[index]->ShowWindow(SW_SHOW);
}

/**
 * name: init_controls
 * brief: ��ʼ����ǰ�Ի����пؼ���
 * param: --
 * return: --
 */
void DialogWorkPlace::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ����ǰ�Ի����а�ť�ؼ���
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//3.��ʼ����ǰ�Ի����еĲ��֡�
	//3-1.��ʼ���Ӳ��֡�
	for(unsigned int index=0;index!=PAGES;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.��ʼ�������֡�
	_main_layout->set_margin(10,10,10,0);
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//3-3.���������ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}