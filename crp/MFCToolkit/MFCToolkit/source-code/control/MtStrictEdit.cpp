// source-code/control/MtStrictEdit.cpp : implementation file
//

#include"stdafx.h"
#include"MtStrictEdit.h"
#include<regex>

/**
 * name: is_integer
 * breif: 判断指定文本是否为整数。
 * param: text - 指定的文本。
 * return: 如果当前文本为整数，则返回TRUE，否则返回FALSE。
 */
static BOOL is_integer(const CString &text){
	//1.如果当前文本为空，则直接FALSE。
	if(_T("")==text){
		return(FALSE);
	}
	//2.创建整数检测正则表达式。
#ifdef _UNICODE
	std::wregex reg(_T("^(-?)|(-?\\d+$)"));
#else
	std::regex reg(_T("^(-?)|(-?\\d+$)"));
#endif
	//3.判断当前文本是否与正则表达式匹配。
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.返回当前结果。
	if(result){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: is_decimals
 * breif: 判断指定文本是否为小数。
 * param: text - 指定文本。
 *        decimals - 指定小数位数（为零时，不检查小数位数）。
 * return: 如果当前文本为小数，则返回TRUE，否则返回FALSE。
 */
static BOOL is_decimals(const CString &text,const unsigned int decimals=0){
	//1.如果当前文本为空，则直接FALSE。
	if(_T("")==text){
		return(FALSE);
	}
	//2.创建小数检测正则表达式。
	CString regular_expression(_T(""));
	if(0==decimals){
		regular_expression=_T("^(-?)|((-?\\d+)(\\.)?(\\d+)?)");
	}else if(1==decimals){
		regular_expression=_T("^(-?)|((-?\\d+)(\\.)?(\\d{1})?)");
	}else{
		regular_expression.Format(_T("^(-?)|((-?\\d+)(\\.)?(\\d{1,%d})?)"),decimals);
	}
#ifdef _UNICODE
	std::wregex reg(regular_expression);
#else
	std::regex reg(regular_expression);
#endif
	//3.判断当前文本是否与正则表达式匹配。
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.返回当前结果。
	if(result){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: is_number
 * breif: 判断指定文本是否为数字。
 * param: text - 指定的文本。
 * return: 如果当前文本为数字，则返回TRUE，否则返回FALSE。
 */
static BOOL is_number(const CString &text){
	//1.如果当前文本为空，则直接FALSE。
	if(_T("")==text){
		return(FALSE);
	}
	//2.创建数字检测正则表达式。
#ifdef _UNICODE
	std::wregex reg(_T("^[0-9]*$"));
#else
	std::regex reg(_T("^[0-9]*$"));
#endif
	//3.判断当前文本是否与正则表达式匹配。
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.返回当前结果。
	if(result){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

//MtStrictEdit

IMPLEMENT_DYNAMIC(MtStrictEdit,MtImageEdit)

/**
 * name: MtStrictEdit
 * brief: 构造函数。
 * param: type - 当前编辑框类型。
 *        decimals - 当前编辑框允许输入的小数位数（
 *                   如果为零，则忽略对小数位的限制）。
 * return: --
 */
MtStrictEdit::MtStrictEdit(const Type type,const unsigned int decimals/*=0*/)
	:MtImageEdit()
	,_type(type)
	,_decimals(decimals){
}

/**
 * name: ~MtStrictEdit
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtStrictEdit::~MtStrictEdit(){
}

BEGIN_MESSAGE_MAP(MtStrictEdit,MtImageEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

//MtStrictEdit message handlers

/**
 * name: OnChar
 * brief: 键盘输入消息响应函数。
 * param: nChar - 输入的字符。
 *        nRepCnt - 键盘重复次数。
 *        nFlags - 键盘输入标志。
 * return: --
 */
void MtStrictEdit::OnChar(UINT nChar,UINT nRepCnt,UINT nFlags){
	//TODO: Add your message handler code here and/or call default
	//1.获取输入生效前文本编辑框中的内容。
	CString last_text(_T(""));
	GetWindowText(last_text);
	//2.调用基类相应处理函数,将内容输入。
	MtImageEdit::OnChar(nChar,nRepCnt,nFlags);
	//3.如果当前输入是没有任何显示的一些功能按键则直接返回。
	if((VK_BACK==nChar)||(VK_CANCEL==nChar)||(0x16==nChar)){
		//如果当前输入为“退格”、“选中”。
		//unfinished: 目前可能总结的不全面。
		return;
	}
	//4.如果当前用户输入的内容与数字相关。
	else if(((_T('0')<=static_cast<TCHAR>(nChar))&&
		(_T('9')>=static_cast<TCHAR>(nChar)))||
		(_T('-')==static_cast<TCHAR>(nChar))||
		(_T('.')==static_cast<TCHAR>(nChar))){
		//4-1.获取当前文本编辑框内容。
		CString text(_T(""));
		GetWindowText(text);
		//4-2.如果当前文本编辑框类型为整数输入文本编辑框。
		if(TYPE_INTEGER==_type){
			//4-2-1.判断当前文本是否为整数，如果是则输入允许。
			if(is_integer(text)){
				return;
			}
			//4-2-2.如果当前文本不为整数，则回复文本显示。
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-3.如果当前文本编辑框类型为小数输入文本编辑框。
		else if(TYPE_DECIMALS==_type){
			//4-3-1.判断当前文本是否为小数，如果是则输入允许。
			if(is_decimals(text,_decimals)){
				return;
			}
			//4-3-2.如果当前文本不为小数，则回复文本显示。
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-4.如果当前文本编辑框类型为数字输入文本编辑框。
		else if(TYPE_NUMBER==_type){
			//4-4-1.判断当前文本是否为数字，如果是则输入允许。
			if(is_number(text)){
				return;
			}
			//4-4-2.如果当前文本不为小数，则回复文本显示。
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-5.如果当前文本编辑框为其它类型的文本编辑框，则直接接受输入。
		else{
			return;
		}
	}
	//5.如果当前用户输入的为其它内容。
	else{
		int start=0;
		int end=0;
		GetSel(start,end);
		SetWindowText(last_text);
		SetSel(start-1,end-1);
	}
}

/**
 * name: OnKillFocus
 * brief: 编辑框失去焦点消息响应函数,在这里用来清理
 *        文本编辑框中的非法字符。
 * param: pNewWnd - 指向新焦点所在窗口。
 * return: --
 */
void MtStrictEdit::OnKillFocus(CWnd *pNewWnd){
	MtImageEdit::OnKillFocus(pNewWnd);
	//TODO: Add your message handler code here
	//1.获取当前文本编辑框文本。
	CString text(_T(""));
	GetWindowText(text);
	//2.如果当前文本编辑框的文本为负号，则清除文本。
	if(_T("-")==text){
		SetWindowText(_T(""));
	}
	//3.如果当前文本内容最后一位为小数点，则清除小数点。
	if((_T("")!=text)&&(_T('.')==text[
		text.GetLength()-1])){
		text=text.Left(text.GetLength()-1);
		SetWindowText(text);
	}
}