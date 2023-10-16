#pragma once

#include"../../Resource.h"
#include "afxwin.h"

//CDlgInput dialog

/**
 * name: CDlgInput
 * breif: 输入对话框类，负责实现用户数据输入。
 * author: yameng_he
 * date: 2015-10-31
 */
class CDlgInput
	:public CDialogEx{
	DECLARE_DYNAMIC(CDlgInput)
//define
public:
	enum{IDD=IDD_DIALOG_INPUT};
	typedef enum{MODE_ADD,MODE_EDIT}Mode;
//construction & destruction
public:
	CDlgInput(CWnd *pParent=NULL);//standard constructor
	CDlgInput(const double conc,
		const double rlu,CWnd *pParent=NULL);
	virtual ~CDlgInput();
//interface
public:
	double get_conc() const;
	double get_rlu() const;
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
//implement
private:
	void init_control();
//variables
private:
	Mode _mode;
	double _conc;
	double _rlu;
	CEdit _conc_edit;
	CEdit _rlu_edit;
};