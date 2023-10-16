// DlgMultipleInput.cpp : implementation file
//

#include "stdafx.h"
#include "DlgMultipleInput.h"
#include "afxdialogex.h"


// DlgMultipleInput dialog

IMPLEMENT_DYNAMIC(DlgMultipleInput, CDialogEx)

DlgMultipleInput::DlgMultipleInput(bool luminous,CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgMultipleInput::IDD, pParent),
	m_luminous(luminous)
{

}

DlgMultipleInput::~DlgMultipleInput()
{
}

void DlgMultipleInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LUMINOUS_EDIT, m_luminous_edit);
}


BEGIN_MESSAGE_MAP(DlgMultipleInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgMultipleInput::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgMultipleInput message handlers

/*
 * name:OnBnClickedOk
 * brief:保存用户输入的发光值
 * param: --
 * return: --
 */
void DlgMultipleInput::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if(m_luminous==true)
	{
		CString text;
		m_luminous_edit.GetWindowText(text);
		if(text==_T(""))
		{
			MessageBox(_T("请输入发光值！"),_T("警告"),MB_ICONWARNING|MB_OK);
		    m_luminous_edit.SetFocus();
		    return;
		}
		else
		{
			m_luminous_text=text;
		}
	}
	OnOK();
}
/*
 * name:get_luminous
 * brief: 获取当前用户输入的发光值
 * param: --
 * return: --
 */
CString DlgMultipleInput::get_luminous()
{
	return m_luminous_text;
}
