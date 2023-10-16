//source-code/uitility/DialogApplication.cpp:implementation file
//

#include"stdafx.h"
#include"DialogApplication.h"
#include"afxdialogex.h"
#include"DialogAnalyzeApplication.h"
#include"DialogRangeApplication.h"
#include"DialogStandardApplication.h"
#include"../../global/Theme.h"
#include"DialogCalibrationApplication.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../UiCustom.h"
#include<assert.h>

//DialogApplication dialog

IMPLEMENT_DYNAMIC(DialogApplication,DialogPageBase)

/**
 * name: DialogApplication
 * breif: ���캯����
 * param: pParent - ָ�򸸴��ڡ�
 * return: --
 */
DialogApplication::DialogApplication(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogApplication::IDD,pParent)
	,_page_buttons(new MtImageButton[PAGES])
	,_page_dialogs(new DialogPageBase*[PAGES])
	,_child_layout_1(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
	memset(_page_dialogs,0,PAGES*sizeof(DialogPageBase*));
	_page_dialogs[0]=new DialogAnalyzeApplication;
	_page_dialogs[1]=new DialogCalibrationApplication;
	_page_dialogs[2]=new DialogRangeApplication;
	_page_dialogs[3]=new DialogStandardApplication;
}

/**
 * name: ~DialogApplication
 * breif: ����������
 * param: --
 * return: --
 */
DialogApplication::~DialogApplication(){
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
 * breif: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogApplication::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
	for(unsigned int index=0;index!=PAGES;++index){
		DDX_Control(pDX,IDC_BUTTON_ANALYZE+index,_page_buttons[index]);
	}
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogApplication::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO:  Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի��������пؼ���
	init_controls();
	//2.Ĭ����ʾ����ҳ�档
	OnPageButtonClicked(IDC_BUTTON_ANALYZE);
	////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogApplication,DialogPageBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_BUTTON_ANALYZE,IDC_BUTTON_STANDARD,&DialogApplication::OnPageButtonClicked)
	ON_MESSAGE(WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,&DialogApplication::OnUpdateDataForControlsByItemID)
END_MESSAGE_MAP()

//DialogApplication message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogApplication::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * brief: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogApplication::OnDestroy(){
	DialogPageBase::OnDestroy();
	//TODO: Add your message handler code here
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
void DialogApplication::OnPageButtonClicked(const unsigned int ID){
	//1.�鿴��ǰ��ҳ�������Ƿ����ı䣬����ı���ʾ�û�����������
	for(unsigned int index=0;index!=PAGES;++index){
		if((IsWindow(_page_dialogs[index]->GetSafeHwnd()))&&(
			0!=_page_dialogs[index]->SendMessage(
			WM_COMMIT_DATA_OF_CONTROLS,0,0))){
			return;
		}
	}
	//1.���㵱ǰ�����ť���±꣬�����жϼ����Ƿ�ɹ���
	const unsigned int index=ID-IDC_BUTTON_ANALYZE;
	if(index>=PAGES){
		return;
	}
	//2.�����ǰ��ť����ѡ��״̬������ֱ�ӷ��ء�
	if(_page_buttons[index].get_checked()){
		return;
	}
	//3.���㵱ǰӦ����ʾ���Ӵ��ڵ�λ�ã������жϼ����Ƿ�ɹ���
	MtLayout::IntRect rect;
	if((_main_layout->get_item_rect(3,rect)<0)||
		(!rect.is_valid())){
		return;
	}
	//4.�����ǰӦ����ʾ����ҳ����δ�������򴴽�֮�������жϴ����Ƿ�ɹ���
	//4-1.���㴴����ҳ��ID��
	unsigned int dialog_id=0;
	if(0==index){
		dialog_id=DialogAnalyzeApplication::IDD;
	}else if(1==index){
		dialog_id=DialogCalibrationApplication::IDD;
	}else if(2==index){
		dialog_id=DialogRangeApplication::IDD;
	}else if(3==index){
		dialog_id=DialogStandardApplication::IDD;
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
	if(_main_layout->set_item_window(3,_page_dialogs[index],500)<0){
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
void DialogApplication::init_controls(){
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
	//2-2.��ʼ���ӶԻ���
	_page_dialogs[0]->Create(DialogAnalyzeApplication::IDD,this);
	assert(IsWindow(_page_dialogs[0]->GetSafeHwnd()));
	_page_dialogs[1]->Create(DialogCalibrationApplication::IDD,this);
	assert(IsWindow(_page_dialogs[1]->GetSafeHwnd()));
	_page_dialogs[2]->Create(DialogRangeApplication::IDD,this);
	assert(IsWindow(_page_dialogs[2]->GetSafeHwnd()));
	_page_dialogs[3]->Create(DialogStandardApplication::IDD,this);
	assert(IsWindow(_page_dialogs[3]->GetSafeHwnd()));
	//3.��ʼ�����֡�
	//3-1.��ʼ���Ӳ���1��
	for(unsigned int index=0;index!=PAGES;++index){
		_child_layout_1->add_fixed_window(&_page_buttons[index],150);
	}
	//3-2.��ʼ�������֡�
	_main_layout->add_spacing(BODER_SIZE);
	_main_layout->add_spacing(5);
	_main_layout->add_layout(_child_layout_1,50);
	_main_layout->add_stretch(500);
	//3-3.���������ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}

/**
 * name: OnUpdateDataForControlsByItemID
 * brief: ͨ����Ŀ��ʶ���½���ؼ����ݡ�
 * param: wParam - ��Ŀ��ʶ��
 *        lParam - �����塣
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogApplication::OnUpdateDataForControlsByItemID(WPARAM wParam,LPARAM lParam){
	//1.�������е��ӶԻ��򣬲��Ҷ����е��ӶԻ����͸��¿ؼ���Ϣ��
	for(unsigned int index=0;index!=PAGES;++index){
		if(IsWindow(_page_dialogs[index]->GetSafeHwnd())){
			_page_dialogs[index]->SendMessage(
				WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID,wParam,lParam);
		}
	}
	//2.�������е��˳ɹ����ء�
	return(0);
}