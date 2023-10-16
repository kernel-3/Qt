#pragma once

#include"../Symbol"

class MtLock;

/**
 * name: MtIni
 * brief: ini文件类，负责读取、写入指定的ini文件。
 * author: yameng_he
 * date: 2016-02-16.
 */
class MFC_TOOLKIT_API MtIni{
//define
public:
	enum{MAXIMUM_BUFFER_SIZE=256,};
//construction & destruction
public:
	MtIni(const CString &file_path);
	~MtIni(void);
//interface
public:
	int read(const CString &section_name,
		const CString &item_name,const int default_value);
	double read(const CString &section_name,
		const CString &item_name,const double default_value);
	float read(const CString &section_name,
		const CString &item_name,const float default_value);
	CString read(const CString &section_name,
		const CString &item_name,const CString &default_value);
	BOOL write(const CString &section_name,
		const CString &item_name,const int value);
//restriction
private:
	MtIni(const MtIni &);
	MtIni &operator=(const MtIni &);
//variables
private:
	MtLock *_lock;
	const CString _file_path;
};

