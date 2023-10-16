//source-code/ui/DlgInput.cpp : implementation file
//

#include"stdafx.h"
#include"DlgInput.h"
#include"afxdialogex.h"

//CDlgInput dialog

IMPLEMENT_DYNAMIC(CDlgInput,CDialogEx)

/**
 * name: CDlgInput
 * breif: ���캯����
 * param: pParent - ָ�򸸶Ի���
 * return: --
 */
CDlgInput::CDlgInput(CWnd *pParent/*=NULL*/)
	:CDialogEx(CDlgInput::IDD,pParent)
	,_mode(MODE_ADD)
	,_conc(0.0)
	,_rlu(0.0){
}

/**
 * name: CDlgInput
 * brief: ���캯����
 * param: conc - Ũ�ȡ�
 *        rlu - ����ֵ��
 * return: --
 */
CDlgInput::CDlgInput(const double conc,
	const double rlu,CWnd *pParent/*=NULL*/)
	:CDialogEx(CDlgInput::IDD,pParent)
	,_mode(MODE_EDIT)
	,_conc(conc)
	,_rlu(rlu){
}

/**
 * name: ~CDlgInput
 * breif: ����������
 * param: --
 * return: --
 */
CDlgInput::~CDlgInput(){
}

/**
 * name: get_conc
 * breif: ��ȡŨ�ȡ�
 * param: --
 * return: ����Ũ�ȡ�
 */
double CDlgInput::get_conc() const{
	return(_conc);
}

/**
 * name: get_rlu
 * breif: ��ȡ����ֵ��
 * param: --
 * return: ���ط���ֵ��
 */
double CDlgInput::get_rlu() const{
	return(_rlu);
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV
 * param: pDX -
 * return: --
 */
void CDlgInput::DoDataExchange(CDataExchange *pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_CONC,_conc_edit);
	DDX_Control(pDX,IDC_EDIT_RLU,_rlu_edit);
	DDX_Text(pDX,IDC_EDIT_CONC,_conc);
	DDX_Text(pDX,IDC_EDIT_RLU,_rlu);
}

/**
 * name: OnInitDialog
 * brief: �Ի����ʼ�����⺯����
 * param: --
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
BOOL CDlgInput::OnInitDialog(){
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	//1.��ʼ����ǰ�Ի����пؼ���
	init_control();
	// EXCEPTION: OCX Property Pages should return FALSE
	return(TRUE);
}

BEGIN_MESSAGE_MAP(CDlgInput,CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE,&CDlgInput::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL,&CDlgInput::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

//CDlgInput message handlers
/**
 * name: OnBnClickedButtonSave
 * breif: �û���������桱��ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void CDlgInput::OnBnClickedButtonSave(){
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)){
		EndDialog(IDOK);
	}
}

/**
 * name: OnBnClickedButtonCancel
 * breif: �û������ȡ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void CDlgInput::OnBnClickedButtonCancel(){
	// TODO: Add your control notification handler code here
	EndDialog(IDCANCEL);
}

/**
 * name: init_control
 * breif: ��ʼ���Ի����пؼ���
 * param: --
 * return: --
 */
void CDlgInput::init_control(){
	//1.�����ǰ�Ի���ģʽ�ǡ���ӡ���
	if(MODE_ADD==_mode){
		_conc_edit.SetWindowText(_T(""));
		_rlu_edit.SetWindowText(_T(""));
	}
	//2.�����ǰ�Ի���ģʽ�ǡ��༭����
	else if(MODE_EDIT==_mode){
		UpdateData(FALSE);
	}
}