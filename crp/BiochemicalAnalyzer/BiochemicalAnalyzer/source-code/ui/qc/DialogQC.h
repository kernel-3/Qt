#pragma once

#include"../../../Resource.h"
#include"../DialogBase.h"

/**
 * name: DialogQC
 * breif: ���ʿء��Ի��򣬸�����ʾ�ʿ���ؽ��档
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