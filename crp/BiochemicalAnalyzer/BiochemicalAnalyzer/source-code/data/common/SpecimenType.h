#pragma once

class MtADORecordset;
class Database;

/**
 * name: SpecimenType
 * breif: 样本类型类，存储样本的类型信息，并提供
 *        与样本类型相关的所有操作。
 * author: yameng_he
 * date: 2015-11-09
 */
class SpecimenType{
//construction & destruction
public:
	SpecimenType(void);
	~SpecimenType(void);
//interface
public:
	void set_id(const int id);
	int get_id() const;
	void set_name(const CString &name);
	CString get_name() const;
	void set_alias(const CString &alias);
	CString get_alias() const;
	int is_valid(CString *error_message=0) const;
	int update(MtADORecordset &recordset);
	int commit(const int commit_means,Database &database) const;
//variables
private:
	int _id;
	CString _name;
	CString _alias;
};

