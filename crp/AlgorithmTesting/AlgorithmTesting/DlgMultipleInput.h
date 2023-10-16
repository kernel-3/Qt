#pragma once
#include"Resource.h"
#include "afxwin.h"

// DlgMultipleInput dialog

class DlgMultipleInput : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMultipleInput)

public:
	DlgMultipleInput(bool luminous,CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgMultipleInput();

// Dialog Data
	enum { IDD=IDD_DIALOG_LUMINOUS_INPUT };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_luminous_edit;	
	afx_msg void OnBnClickedOk();
	CString get_luminous();//��ȡ����ֵ
private:
	bool m_luminous;//�û��Ƿ���ӷ���ֵ�ñ�־λ
	CString m_luminous_text;//�洢�û�����ķ���ֵ����
};
