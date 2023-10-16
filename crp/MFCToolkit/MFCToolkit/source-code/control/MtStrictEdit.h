#pragma once

#include"MtImageEdit.h"

/**
 * name: MtStrictEdit
 * breif: 严格的文本编辑框，提供一个只允许输入严格限制
 *        的文本编辑框。
 * author: yameng_he
 * date: 2015-06-25
 * note: 目前支持对数字输入的严格限制。
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