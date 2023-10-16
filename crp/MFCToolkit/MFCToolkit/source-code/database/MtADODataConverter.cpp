#include"stdafx.h"
#include"MtADODataConverter.h"
#include<assert.h>

/**
 * name: to_unsigned_char
 * brief: 将 _variant_t 类型数据转化为 unsigned char 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
unsigned char MtADODataConverter::to_unsigned_char(const _variant_t &value){
	if(VT_UI1==value.vt){
		return(value.bVal);
	}else{
		assert(0);
		return(0);
	}
}

/**
 * name: to_string
 * brief: 将 _variant_t 类型数据转化为 CString 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
CString MtADODataConverter::to_string(const _variant_t &value){
	if(VT_BSTR==value.vt){
		return(static_cast<LPCTSTR>(static_cast<_bstr_t>(value.bstrVal)));
	}else if(VT_DATE==value.vt){
		return(COleDateTime(value).Format());
	}else{
		assert(0);
		return(_T(""));
	}
}

/**
 * name: to_long
 * brief: 将 _variant_t 类型数据转化为 long 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
long MtADODataConverter::to_long(const _variant_t &value){
	if(VT_I4==value.vt){
		return(value.lVal);
	}else{
		assert(0);
		return(0);
	}
}

/**
 * name: to_int
 * brief: 将 _variant_t 类型数据转化为 int 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
int MtADODataConverter::to_int(const _variant_t &value){
	if(VT_I4==value.vt){
		return(value.lVal);
	}else{
		assert(0);
		return(0);
	}
}

/**
 * name: to_unsigned_int
 * brief: 将 _variant_t 类型数据转化为 unsigned int 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
int MtADODataConverter::to_unsigned_int(const _variant_t &value){
	if(VT_I4==value.vt){
		return(static_cast<unsigned int>(value.lVal));
	}else{
		assert(0);
		return(0);
	}
}

/**
 * name: to_double
 * brief: 将 _variant_t 类型数据转化为 double 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
double MtADODataConverter::to_double(const _variant_t &value){
	if(VT_R8==value.vt){
		return(value.dblVal);
	}else{
		assert(0);
		return(0);
	}
}

/**
 * name: to_boolen
 * brief: 将 _variant_t 类型数据转化为 BOOL 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
BOOL MtADODataConverter::to_boolen(const _variant_t &value){
	if(VT_BOOL==value.vt){
		if(0==value.boolVal){
			return(FALSE);
		}else{
			return(TRUE);
		}
	}else{
		assert(0);
		return(FALSE);
	}
}

/**
 * name: to_variant_t
 * brief: 将 long 类型数据转化为 _variant_t 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
_variant_t MtADODataConverter::to_variant_t(const long value){
	return(_variant_t(value));
}

/**
 * name: to_variant_t
 * brief: 将 CString 类型数据转化为 _variant_t 类型。
 * param: value - 将要转换的数据。
 * return: 返回转换后的值。
 */
_variant_t MtADODataConverter::to_variant_t(const CString &value){
	return(_variant_t(static_cast<LPCTSTR>(value)));
}