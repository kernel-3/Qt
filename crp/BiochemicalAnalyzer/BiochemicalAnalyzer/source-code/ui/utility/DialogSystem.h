#pragma once

#include"../../../Resource.h"
#include"../DialogPageBase.h"

class MtBitmap;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogSystem
 * brief: ��ϵͳ���Ի����ṩ�û���ϵͳ�����޸����õĽ������档
 * author: yameng_he
 * date: 2015-06-01
 */
class DialogSystem
	:public DialogPageBase{
	DECLARE_DYNAMIC(DialogSystem)
//define
public:
	enum{IDD=IDD_DIALOG_SYSTEM};
//construction & destruction
public:
	DialogSystem(CWnd *pParent=NULL);//standard constructor
	virtual ~DialogSystem();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
//implement
private:
	void init_controls();
//variables
private:
	MtVerticalLayout *_main_layout;
};