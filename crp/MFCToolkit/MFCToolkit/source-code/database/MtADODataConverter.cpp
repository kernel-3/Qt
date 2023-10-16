#include"stdafx.h"
#include"MtADODataConverter.h"
#include<assert.h>

/**
 * name: to_unsigned_char
 * brief: �� _variant_t ��������ת��Ϊ unsigned char ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ CString ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ long ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ int ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ unsigned int ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ double ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� _variant_t ��������ת��Ϊ BOOL ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
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
 * brief: �� long ��������ת��Ϊ _variant_t ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
 */
_variant_t MtADODataConverter::to_variant_t(const long value){
	return(_variant_t(value));
}

/**
 * name: to_variant_t
 * brief: �� CString ��������ת��Ϊ _variant_t ���͡�
 * param: value - ��Ҫת�������ݡ�
 * return: ����ת�����ֵ��
 */
_variant_t MtADODataConverter::to_variant_t(const CString &value){
	return(_variant_t(static_cast<LPCTSTR>(value)));
}