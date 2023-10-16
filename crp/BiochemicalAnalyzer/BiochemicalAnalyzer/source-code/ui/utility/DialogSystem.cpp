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
 * brief: ���캯����
 * param: pParent - ָ�򸸶Ի���
 * return: --
 */
DialogSystem::DialogSystem(CWnd *pParent/*=NULL*/)
	:DialogPageBase(DialogSystem::IDD,pParent)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogSystem
 * breif: ����������
 * param: --
 * return: --
 */
DialogSystem::~DialogSystem(){
	delete _main_layout;
}

/**
 * name: DoDataExchange
 * brief: ֧��DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogSystem::DoDataExchange(CDataExchange *pDX){
	DialogPageBase::DoDataExchange(pDX);
}

/**
 * name: OnInitDialog
 * breif: ��ʼ���Ի������⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogSystem::OnInitDialog(){
	DialogPageBase::OnInitDialog();
	//TODO: Add extra initialization here
	////////////////////////////////////////////////////////////////
	//1.��ʼ���Ի����пؼ���
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
 * breif: �Ի���ߴ�����Ϣ��Ӧ������
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogSystem::OnSize(UINT nType,int cx,int cy){
	DialogPageBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: init_controls
 * brief: �ԶԻ��������пؼ����г�ʼ����
 * param: --
 * return: --
 */
void DialogSystem::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	//Theme *theme=Theme::instance();
	//2.��ʼ���Ի����пؼ���
	//3.��ʼ���Ի����в��֡�
	_main_layout->add_spacing(BODER_SIZE);
	//4.������ǰ�Ի��򲼾ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
}