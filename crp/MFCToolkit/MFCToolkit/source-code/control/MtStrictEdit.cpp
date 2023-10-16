// source-code/control/MtStrictEdit.cpp : implementation file
//

#include"stdafx.h"
#include"MtStrictEdit.h"
#include<regex>

/**
 * name: is_integer
 * breif: �ж�ָ���ı��Ƿ�Ϊ������
 * param: text - ָ�����ı���
 * return: �����ǰ�ı�Ϊ�������򷵻�TRUE�����򷵻�FALSE��
 */
static BOOL is_integer(const CString &text){
	//1.�����ǰ�ı�Ϊ�գ���ֱ��FALSE��
	if(_T("")==text){
		return(FALSE);
	}
	//2.�����������������ʽ��
#ifdef _UNICODE
	std::wregex reg(_T("^(-?)|(-?\\d+$)"));
#else
	std::regex reg(_T("^(-?)|(-?\\d+$)"));
#endif
	//3.�жϵ�ǰ�ı��Ƿ���������ʽƥ�䡣
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.���ص�ǰ�����
	if(result){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: is_decimals
 * breif: �ж�ָ���ı��Ƿ�ΪС����
 * param: text - ָ���ı���
 *        decimals - ָ��С��λ����Ϊ��ʱ�������С��λ������
 * return: �����ǰ�ı�ΪС�����򷵻�TRUE�����򷵻�FALSE��
 */
static BOOL is_decimals(const CString &text,const unsigned int decimals=0){
	//1.�����ǰ�ı�Ϊ�գ���ֱ��FALSE��
	if(_T("")==text){
		return(FALSE);
	}
	//2.����С�����������ʽ��
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
	//3.�жϵ�ǰ�ı��Ƿ���������ʽƥ�䡣
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.���ص�ǰ�����
	if(result){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: is_number
 * breif: �ж�ָ���ı��Ƿ�Ϊ���֡�
 * param: text - ָ�����ı���
 * return: �����ǰ�ı�Ϊ���֣��򷵻�TRUE�����򷵻�FALSE��
 */
static BOOL is_number(const CString &text){
	//1.�����ǰ�ı�Ϊ�գ���ֱ��FALSE��
	if(_T("")==text){
		return(FALSE);
	}
	//2.�������ּ��������ʽ��
#ifdef _UNICODE
	std::wregex reg(_T("^[0-9]*$"));
#else
	std::regex reg(_T("^[0-9]*$"));
#endif
	//3.�жϵ�ǰ�ı��Ƿ���������ʽƥ�䡣
	const bool result=std::regex_match(static_cast<LPCTSTR>(text),
		static_cast<LPCTSTR>(text)+text.GetLength(),reg);
	//4.���ص�ǰ�����
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
 * brief: ���캯����
 * param: type - ��ǰ�༭�����͡�
 *        decimals - ��ǰ�༭�����������С��λ����
 *                   ���Ϊ�㣬����Զ�С��λ�����ƣ���
 * return: --
 */
MtStrictEdit::MtStrictEdit(const Type type,const unsigned int decimals/*=0*/)
	:MtImageEdit()
	,_type(type)
	,_decimals(decimals){
}

/**
 * name: ~MtStrictEdit
 * brief: ����������
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
 * brief: ����������Ϣ��Ӧ������
 * param: nChar - ������ַ���
 *        nRepCnt - �����ظ�������
 *        nFlags - ���������־��
 * return: --
 */
void MtStrictEdit::OnChar(UINT nChar,UINT nRepCnt,UINT nFlags){
	//TODO: Add your message handler code here and/or call default
	//1.��ȡ������Чǰ�ı��༭���е����ݡ�
	CString last_text(_T(""));
	GetWindowText(last_text);
	//2.���û�����Ӧ������,���������롣
	MtImageEdit::OnChar(nChar,nRepCnt,nFlags);
	//3.�����ǰ������û���κ���ʾ��һЩ���ܰ�����ֱ�ӷ��ء�
	if((VK_BACK==nChar)||(VK_CANCEL==nChar)||(0x16==nChar)){
		//�����ǰ����Ϊ���˸񡱡���ѡ�С���
		//unfinished: Ŀǰ�����ܽ�Ĳ�ȫ�档
		return;
	}
	//4.�����ǰ�û������������������ء�
	else if(((_T('0')<=static_cast<TCHAR>(nChar))&&
		(_T('9')>=static_cast<TCHAR>(nChar)))||
		(_T('-')==static_cast<TCHAR>(nChar))||
		(_T('.')==static_cast<TCHAR>(nChar))){
		//4-1.��ȡ��ǰ�ı��༭�����ݡ�
		CString text(_T(""));
		GetWindowText(text);
		//4-2.�����ǰ�ı��༭������Ϊ���������ı��༭��
		if(TYPE_INTEGER==_type){
			//4-2-1.�жϵ�ǰ�ı��Ƿ�Ϊ���������������������
			if(is_integer(text)){
				return;
			}
			//4-2-2.�����ǰ�ı���Ϊ��������ظ��ı���ʾ��
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-3.�����ǰ�ı��༭������ΪС�������ı��༭��
		else if(TYPE_DECIMALS==_type){
			//4-3-1.�жϵ�ǰ�ı��Ƿ�ΪС�������������������
			if(is_decimals(text,_decimals)){
				return;
			}
			//4-3-2.�����ǰ�ı���ΪС������ظ��ı���ʾ��
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-4.�����ǰ�ı��༭������Ϊ���������ı��༭��
		else if(TYPE_NUMBER==_type){
			//4-4-1.�жϵ�ǰ�ı��Ƿ�Ϊ���֣����������������
			if(is_number(text)){
				return;
			}
			//4-4-2.�����ǰ�ı���ΪС������ظ��ı���ʾ��
			else{
				int start=0;
				int end=0;
				GetSel(start,end);
				SetWindowText(last_text);
				SetSel(start-1,end-1);
			}
		}
		//4-5.�����ǰ�ı��༭��Ϊ�������͵��ı��༭����ֱ�ӽ������롣
		else{
			return;
		}
	}
	//5.�����ǰ�û������Ϊ�������ݡ�
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
 * brief: �༭��ʧȥ������Ϣ��Ӧ����,��������������
 *        �ı��༭���еķǷ��ַ���
 * param: pNewWnd - ָ���½������ڴ��ڡ�
 * return: --
 */
void MtStrictEdit::OnKillFocus(CWnd *pNewWnd){
	MtImageEdit::OnKillFocus(pNewWnd);
	//TODO: Add your message handler code here
	//1.��ȡ��ǰ�ı��༭���ı���
	CString text(_T(""));
	GetWindowText(text);
	//2.�����ǰ�ı��༭����ı�Ϊ���ţ�������ı���
	if(_T("-")==text){
		SetWindowText(_T(""));
	}
	//3.�����ǰ�ı��������һλΪС���㣬�����С���㡣
	if((_T("")!=text)&&(_T('.')==text[
		text.GetLength()-1])){
		text=text.Left(text.GetLength()-1);
		SetWindowText(text);
	}
}