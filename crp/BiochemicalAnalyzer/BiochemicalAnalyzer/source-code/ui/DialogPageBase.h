#pragma once

#include"DialogBase.h"

/**
 * name: DialogPageBase
 * brief: ��������ҳ��Ի�������ҳ��Ի�����Ӵ����м̳С�
 * author: yameng_he
 * date: 2015-06-01
 */
class DialogPageBase
	:public DialogBase{
	DECLARE_DYNAMIC(DialogPageBase)
//define
public:
	enum{BODER_SIZE=2,};
//construction & destruction
public:
	DialogPageBase(const unsigned int IDD,CWnd *pParent=NULL);//standard constructor
	virtual ~DialogPageBase();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual void draw(MtBitmap &memory_bitmap,CDC &dc);
	DECLARE_MESSAGE_MAP()
//implement
private:
	void draw_boder(MtBitmap &memory_bitmap);
};