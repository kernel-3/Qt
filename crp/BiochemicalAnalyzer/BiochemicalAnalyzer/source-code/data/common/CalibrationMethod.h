#pragma once

class MtADORecordset;

/**
 * name: CalibrationMethod
 * breif: 定标方法类，负责描述一个定标方法。
 * author: yameng_he
 * date: 2015-12-22
 */
class CalibrationMethod{
//construction & destruction
public:
	CalibrationMethod(void);
	~CalibrationMethod(void);
//interface
public:
	void set_id(const int id);
	int get_id() const;
	void set_name(const CString &name);
	CString get_name() const;
	void set_alias(const CString &alias);
	CString get_alias() const;
	int is_valid() const;
	int update(MtADORecordset &recordset);
//variables
private:
	int _id;
	CString _name;
	CString _alias;
};
