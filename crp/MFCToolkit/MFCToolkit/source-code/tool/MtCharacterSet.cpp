#include"stdafx.h"
#include"MtCharacterSet.h"
#include<memory>
#include<regex>

/**
 * name: shared_ptr_deletor
 * brief: shared_ptr����ָ��ɾ�������������ṩ���Ƶ�shared_ptrָ��ɾ�����ܡ�
 * param: pointer - shared_ptr�д洢��ָ�롣
 * return: --
 */
static void shared_ptr_deletor(wchar_t *pointer){
	if(0!=pointer){
		delete[] pointer;
	}
}

/**
 * name: to_integer
 * breif: ��ָ�����ı�ת��Ϊ������
 * param: text - ָ�����ı���
 * return: ����ת�����������
 * remark: �˺���ʹ��ʱ�з��գ���ʹ��ʱ����ر�֤
 *         text����Ϊ��Ч������
 */
int MtCharacterSet::to_integer(const CString &text){
#ifdef _UNICODE
	return(_wtoi(text));
#else
	return(atoi(text));
#endif
}

/**
 * name: to_decimals
 * brief: ��ָ�����ı�ת��ΪС���ͣ�˫���ȣ���
 * param: text - ָ�����ı���
 * return: ����ת�����С����
 * remark: �˺���ʹ��ʱ�з��գ���ʹ��ʱ����ر�֤
 *         text����Ϊ��Ч������
 */
double MtCharacterSet::to_decimals(const CString &text){
#ifdef _UNICODE
	return(_wtof(text));
#else
	return(atof(text));
#endif
}

/**
 * name: to_unicode
 * brief: ��ָ���ı�ת����UNICODE���롣
 * param: text - �ı���
 * return: ������Ӧ��UNICODE�����ı���
 */
CStringW MtCharacterSet::to_unicode(const CString &text){
#ifdef _UNICODE
	return(text);
#else
	typedef std::shared_ptr<wchar_t> PtrToArray;
	PtrToArray unicode_array(new wchar_t[text.GetLength()+1],shared_ptr_deletor);
	memset(unicode_array.get(),0,(text.GetLength()+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP,0,static_cast<const char*>(text),(text.GetLength())*sizeof(char),
		unicode_array.get(),(text.GetLength()+1)*sizeof(wchar_t));
	const CStringW unicode_text(unicode_array.get());
	return(unicode_text);
#endif
}

/**
 * name: is_integer
 * breif: �ж�ָ���ı��Ƿ�Ϊ������
 * param: text - ָ�����ı���
 * return: �����ǰ�ı�Ϊ�������򷵻�TRUE�����򷵻�FALSE��
 */
BOOL MtCharacterSet::is_integer(const CString &text){
	//1.�����ǰ�ı�Ϊ�գ���ֱ��FALSE��
	if(_T("")==text){
		return(FALSE);
	}
	//2.�����������������ʽ��
#ifdef _UNICODE
	std::wregex reg(_T("^-?\\d+$"));
#else
	std::regex reg(_T("^-?\\d+$"));
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
BOOL MtCharacterSet::is_decimals(const CString &text,const unsigned int decimals/*=0*/){
	//1.�����ǰ�ı�Ϊ�գ���ֱ��FALSE��
	if(_T("")==text){
		return(FALSE);
	}
	//2.����С�����������ʽ��
	CString regular_expression(_T(""));
	if(0==decimals){
		regular_expression=_T("^(-?\\d+)(\\.\\d+)?");
	}else{
		regular_expression.Format(_T("^(-?\\d+)(\\.\\d{%d})?"),decimals);
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
 * ��֤���ֵ�������ʽ�� 
 * ��֤���֣�^[0-9]*$
 * ��֤nλ�����֣�^\d{n}$
 * ��֤����nλ���֣�^\d{n,}$
 * ��֤m-nλ�����֣�^\d{m,n}$
 * ��֤��ͷ��㿪ͷ�����֣�^(0|[1-9][0-9]*)$
 * ��֤����λС������ʵ����^[0-9]+(.[0-9]{2})?$
 * ��֤��1-3λС������ʵ����^[0-9]+(.[0-9]{1,3})?$
 * ��֤�������������^\+?[1-9][0-9]*$
 * ��֤����ĸ�������^\-[1-9][0-9]*$
 * ��֤�Ǹ������������� + 0�� ^\d+$
 * ��֤���������������� + 0�� ^((-\d+)|(0+))$
 * ��֤����Ϊ3���ַ���^.{3}$
 * ��֤��26��Ӣ����ĸ��ɵ��ַ�����^[A-Za-z]+$
 * ��֤��26����дӢ����ĸ��ɵ��ַ�����^[A-Z]+$
 * ��֤��26��СдӢ����ĸ��ɵ��ַ�����^[a-z]+$
 * ��֤�����ֺ�26��Ӣ����ĸ��ɵ��ַ�����^[A-Za-z0-9]+$
 * ��֤�����֡�26��Ӣ����ĸ�����»�����ɵ��ַ�����^\w+$
 * ��֤�û�����:^[a-zA-Z]\w{5,17}$ ��ȷ��ʽΪ������ĸ��ͷ��������6-18֮�䣬ֻ�ܰ����ַ������ֺ��»��ߡ�
 * ��֤�Ƿ��� ^%&',;=?$\" ���ַ���[^%&',;=?$\x22]+
 * ��֤���֣�^[\u4e00-\u9fa5],{0,}$
 * ��֤Email��ַ��^\w+[-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$
 * ��֤InternetURL��^http://([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)?$ ��^[a-zA-z]+://(w+(-w+)*)(.(w+(-w+)*))*(?S*)?$
 * ��֤�绰���룺^(\(\d{3,4}\)|\d{3,4}-)?\d{7,8}$��--��ȷ��ʽΪ��XXXX-XXXXXXX��XXXX-XXXXXXXX��XXX-XXXXXXX��XXX-XXXXXXXX��XXXXXXX��XXXXXXXX��
 * ��֤���֤�ţ�15λ��18λ���֣���^\d{15}|\d{}18$
 * ��֤һ���12���£�^(0?[1-9]|1[0-2])$ ��ȷ��ʽΪ����01��-��09���͡�1����12��
 * ��֤һ���µ�31�죺^((0?[1-9])|((1|2)[0-9])|30|31)$ ��ȷ��ʽΪ��01��09��1��31��
 * ������^-?\d+$
 * �Ǹ����������������� + 0����^\d+(\.\d+)?$
 * �������� ^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$
 * �������������������� + 0�� ^((-\d+(\.\d+)?)|(0+(\.0+)?))$
 * �������� ^(-(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*)))$
 * ������ ^(-?\d+)(\.\d+)? 
 */