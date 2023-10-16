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
 * brief: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
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
 * brief: ����������
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
 * breif: ֧��DDX/DDV
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
 * brief: ��ʼ���Ի������⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogCalibration::OnInitDialog(){
	DialogBase::OnInitDialog();
	// TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////////
	//1.��ʼ���Ի����пؼ���
	init_controls();
	//2.��ʾ��ǰ���ӶԻ���
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
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogCalibration::OnSize(UINT nType,int cx,int cy){
	DialogBase::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * brief: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogCalibration::OnDestroy(){
	DialogBase::OnDestroy();
	// TODO: Add your message handler code here
	//1.���ٵ�ǰ�ӶԻ���
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
 * brief: �û����ҳ�水ť��Ϣ��Ӧ������
 * param: ID - ҳ�水ťID��
 * return: --
 */
void DialogCalibration::OnPageButtonClicked(const unsigned int ID){
	//1.���㵱ǰ�����ť���±꣬�����жϼ����Ƿ�ɹ���
	const unsigned int index=ID-IDC_BUTTON_STATUS;
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
	//4-1.���㴴����ҳ��ID��
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
	//4-2.����ҳ�棬�����жϴ����Ƿ�ɹ���
	if(!IsWindow(_page_dialogs[index]->GetSafeHwnd())){
		if(!_page_dialogs[index]->Create(dialog_id,this)){
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
 * brief: ��ʼ�������пؼ���
 * param: --
 * return: --
 */
void DialogCalibration::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ�������пؼ���
	//2-1.��ʼ����ť��
	for(unsigned int index=0;index!=PAGES;++index){
		_page_buttons[index].set_text_color(255,50,50,50);
		_page_buttons[index].set_light_text_color(255,255,255,255);
		_page_buttons[index].load_background_image(theme->get_image(23),1,4);
		_page_buttons[index].set_background_image_stretching_factors(5,5,5,5);
	}
	//3.��ʼ�����֡�
	//3-1.��ʼ���Ӳ���1��
	for(unsigned int index=0;index!=PAGES;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	_child_layout_1->add_stretch(1);
	//3-2.��ʼ�������֡�
	_main_layout->set_margin(10,10,10,10);
	_main_layout->add_fixed_layout(_child_layout_1,50);
	_main_layout->add_stretch(1);
	//3-3.���������ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}