#pragma once

#include"../Symbol"

/**
 * name: MtCharacterSet
 * brief: 字符集类，负责实现字符集相关功能。
 * author: yameng_he
 * date: 2014-05-26
 */
class MFC_TOOLKIT_API MtCharacterSet{
//interface
public:
	static int to_integer(const CString &text);
	static double to_decimals(const CString &text);
	static CStringW to_unicode(const CString &text);
	static BOOL is_integer(const CString &text);
	static BOOL is_decimals(const CString &text,const unsigned int decimals=0);
//restrict
private:
	MtCharacterSet(void);
	MtCharacterSet(const MtCharacterSet &);
	~MtCharacterSet(void);
	MtCharacterSet &operator=(const MtCharacterSet &);
};