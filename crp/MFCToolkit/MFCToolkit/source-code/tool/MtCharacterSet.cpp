#include"stdafx.h"
#include"MtCharacterSet.h"
#include<memory>
#include<regex>

/**
 * name: shared_ptr_deletor
 * brief: shared_ptr智能指针删除函数，负责提供定制的shared_ptr指针删除功能。
 * param: pointer - shared_ptr中存储的指针。
 * return: --
 */
static void shared_ptr_deletor(wchar_t *pointer){
	if(0!=pointer){
		delete[] pointer;
	}
}

/**
 * name: to_integer
 * breif: 将指定的文本转换为整数。
 * param: text - 指定的文本。
 * return: 返回转换后的整数。
 * remark: 此函数使用时有风险，在使用时请务必保证
 *         text内容为有效整数。
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
 * brief: 将指定的文本转换为小数型（双精度）。
 * param: text - 指定的文本。
 * return: 返回转换后的小数。
 * remark: 此函数使用时有风险，在使用时请务必保证
 *         text内容为有效整数。
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
 * brief: 将指定文本转换成UNICODE编码。
 * param: text - 文本。
 * return: 返回相应的UNICODE编码文本。
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
 * breif: 判断指定文本是否为整数。
 * param: text - 指定的文本。
 * return: 如果当前文本为整数，则返回TRUE，否则返回FALSE。
 */
BOOL MtCharacterSet::is_integer(const CString &text){
	//1.如果当前文本为空，则直接FALSE。
	if(_T("")==text){
		return(FALSE);
	}
	//2.创建整数检测正则表达式。
#ifdef _UNICODE
	std::wregex reg(_T("^-?\\d+$"));
#else
	std::regex reg(_T("^-?\\d+$"));
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
BOOL MtCharacterSet::is_decimals(const CString &text,const unsigned int decimals/*=0*/){
	//1.如果当前文本为空，则直接FALSE。
	if(_T("")==text){
		return(FALSE);
	}
	//2.创建小数检测正则表达式。
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
 * 验证数字的正则表达式集 
 * 验证数字：^[0-9]*$
 * 验证n位的数字：^\d{n}$
 * 验证至少n位数字：^\d{n,}$
 * 验证m-n位的数字：^\d{m,n}$
 * 验证零和非零开头的数字：^(0|[1-9][0-9]*)$
 * 验证有两位小数的正实数：^[0-9]+(.[0-9]{2})?$
 * 验证有1-3位小数的正实数：^[0-9]+(.[0-9]{1,3})?$
 * 验证非零的正整数：^\+?[1-9][0-9]*$
 * 验证非零的负整数：^\-[1-9][0-9]*$
 * 验证非负整数（正整数 + 0） ^\d+$
 * 验证非正整数（负整数 + 0） ^((-\d+)|(0+))$
 * 验证长度为3的字符：^.{3}$
 * 验证由26个英文字母组成的字符串：^[A-Za-z]+$
 * 验证由26个大写英文字母组成的字符串：^[A-Z]+$
 * 验证由26个小写英文字母组成的字符串：^[a-z]+$
 * 验证由数字和26个英文字母组成的字符串：^[A-Za-z0-9]+$
 * 验证由数字、26个英文字母或者下划线组成的字符串：^\w+$
 * 验证用户密码:^[a-zA-Z]\w{5,17}$ 正确格式为：以字母开头，长度在6-18之间，只能包含字符、数字和下划线。
 * 验证是否含有 ^%&',;=?$\" 等字符：[^%&',;=?$\x22]+
 * 验证汉字：^[\u4e00-\u9fa5],{0,}$
 * 验证Email地址：^\w+[-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$
 * 验证InternetURL：^http://([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)?$ ；^[a-zA-z]+://(w+(-w+)*)(.(w+(-w+)*))*(?S*)?$
 * 验证电话号码：^(\(\d{3,4}\)|\d{3,4}-)?\d{7,8}$：--正确格式为：XXXX-XXXXXXX，XXXX-XXXXXXXX，XXX-XXXXXXX，XXX-XXXXXXXX，XXXXXXX，XXXXXXXX。
 * 验证身份证号（15位或18位数字）：^\d{15}|\d{}18$
 * 验证一年的12个月：^(0?[1-9]|1[0-2])$ 正确格式为：“01”-“09”和“1”“12”
 * 验证一个月的31天：^((0?[1-9])|((1|2)[0-9])|30|31)$ 正确格式为：01、09和1、31。
 * 整数：^-?\d+$
 * 非负浮点数（正浮点数 + 0）：^\d+(\.\d+)?$
 * 正浮点数 ^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$
 * 非正浮点数（负浮点数 + 0） ^((-\d+(\.\d+)?)|(0+(\.0+)?))$
 * 负浮点数 ^(-(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*)))$
 * 浮点数 ^(-?\d+)(\.\d+)? 
 */