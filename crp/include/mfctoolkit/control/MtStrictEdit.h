#pragma once

#include"MtImageEdit.h"

/**
 * name: MtStrictEdit
 * breif: �ϸ���ı��༭���ṩһ��ֻ���������ϸ�����
 *        ���ı��༭��
 * author: yameng_he
 * date: 2015-06-25
 * note: Ŀǰ֧�ֶ�����������ϸ����ơ�
 */
class MFC_TOOLKIT_API MtStrictEdit
	:public MtImageEdit{
	DECLARE_DYNAMIC(MtStrictEdit)
//define
public:
	typedef enum{TYPE_INTEGER,TYPE_DECIMALS,TYPE_NUMBER,}Type;
//construction & destruction
public:
	MtStrictEdit(const Type type,const unsigned int decimals=0);
	virtual ~MtStrictEdit();
//overrides
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar,UINT nRepCnt,UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
//variables
private:
	Type _type;
	unsigned int _decimals;
};