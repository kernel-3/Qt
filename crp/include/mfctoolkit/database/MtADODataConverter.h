#pragma once

#include"../Symbol"
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" \
	named_guids rename("EOF","adoEOF"),rename("BOF","adoBOF")

/**
 * name: MtADODataConverter
 * brief: ADO 数据转换类，负责在 ADO 操作过程中的数据类型变换实现。
 * author: yameng_he
 * date: 2014-09-03
 */
class MFC_TOOLKIT_API MtADODataConverter{
//static interface
public:
	static unsigned char to_unsigned_char(const _variant_t &value);
	static CString to_string(const _variant_t &value);
	static long to_long(const _variant_t &value);
	static int to_int(const _variant_t &value);
	static int to_unsigned_int(const _variant_t &value);
	static double to_double(const _variant_t &value);
	static BOOL to_boolen(const _variant_t &value);
	static _variant_t to_variant_t(const long value);
	static _variant_t to_variant_t(const CString &value);
//restrict
private:
	MtADODataConverter(void);
	MtADODataConverter(const MtADODataConverter &);
	~MtADODataConverter(void);
	MtADODataConverter &operator=(const MtADODataConverter &);
};

