//source-code/ui/DlgInput.cpp : implementation file
//

#include"stdafx.h"
#include"DlgInput.h"
#include"afxdialogex.h"

//CDlgInput dialog

IMPLEMENT_DYNAMIC(CDlgInput,CDialogEx)

/**
 * name: CDlgInput
 * breif: 构造函数。
 * param: pParent - 指向父对话框。
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
 * brief: 构造函数。
 * param: conc - 浓度。
 *        rlu - 发光值。
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
 * breif: 析构函数。
 * param: --
 * return: --
 */
CDlgInput::~CDlgInput(){
}

/**
 * name: get_conc
 * breif: 获取浓度。
 * param: --
 * return: 返回浓度。
 */
double CDlgInput::get_conc() const{
	return(_conc);
}

/**
 * name: get_rlu
 * breif: 获取发光值。
 * param: --
 * return: 返回发光值。
 */
double CDlgInput::get_rlu() const{
	return(_rlu);
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
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
 * brief: 对话框初始化虚拟函数。
 * param: --
 * return: 如果函数执行成功返回TRUE、否则返回FALSE。
 */
BOOL CDlgInput::OnInitDialog(){
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	//1.初始化当前对话框中控件。
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
 * breif: 用户点击“保存”按钮消息响应函数。
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
 * breif: 用户点击“取消”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgInput::OnBnClickedButtonCancel(){
	// TODO: Add your control notification handler code here
	EndDialog(IDCANCEL);
}

/**
 * name: init_control
 * breif: 初始化对话框中控件。
 * param: --
 * return: --
 */
void CDlgInput::init_control(){
	//1.如果当前对话框模式是“添加”。
	if(MODE_ADD==_mode){
		_conc_edit.SetWindowText(_T(""));
		_rlu_edit.SetWindowText(_T(""));
	}
	//2.如果当前对话框模式是“编辑”。
	else if(MODE_EDIT==_mode){
		UpdateData(FALSE);
	}
}