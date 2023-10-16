#pragma once

class MtADORecordset;

/**
 * name: DilutionMethod
 * brief: 稀释方法类，负责描述一个稀释方法，并实现
 *        与其相关的全部接口。
 * author: yameng_he
 * date: 2015-11-30
 */
class DilutionMethod{
//construction & destruction
public:
	DilutionMethod(void);
	~DilutionMethod(void);
//interface
public:
	void set_id(const int id);
	int get_id() const;
	void set_name(const CString &name);
	CString get_name() const;
	void set_alias(const CString &alias);
	CString get_alias() const;
	void set_specimen_ratio(const int specimen_ratio);
	int get_specimen_ratio() const;
	void set_diluent_ratio(const int diluent_ratio);
	int get_diluent_ratio() const;
	int is_valid() const;
	int update(MtADORecordset &recordset);
//variables
private:
	int _id;
	CString _name;
	CString _alias;
	int _specimen_ratio;
	int _diluent_ratio;
};