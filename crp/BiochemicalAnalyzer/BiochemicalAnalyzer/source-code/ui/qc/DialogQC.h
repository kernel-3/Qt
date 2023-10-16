#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"

/**
 * name: DialogQC
 * breif: “质控”对话框，负责显示质控相关界面。
 * author: yameng_he
 * date: 2015-03-25
 */
class DialogQC
	:public DialogBase{
	DECLARE_DYNAMIC(DialogQC)
//define
public:
	enum{IDD=IDD_DIALOG_QC};
//construction & destruction
public:
	DialogQC(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogQC();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	DECLARE_MESSAGE_MAP()
};