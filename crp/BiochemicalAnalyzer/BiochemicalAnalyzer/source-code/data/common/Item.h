#pragma once

class Database;
class MtADORecordset;

/**
 * name: Item
 * breif: 项目类，负责描述一个项目。
 * author: yameng_he
 * date: 2015-06-12
 */
class Item{
//define
public:
	typedef enum{STATUS_UNKNOWN=0,STATUS_NORMAL=1,STATUS_MASK=2,}Status;
//construction & destruction
public:
	Item(void);
	~Item(void);
//interface
public:
	void set_id(const int id);
	int get_id() const;
	void set_no(const int no);
	int get_no() const;
	void set_name(const CString &name);
	const CString &get_name() const;
	void set_alias(const CString &alias);
	const CString &get_alias() const;
	void set_status(const Status status);
	Status get_status() const;
	int is_valid(CString *error_message=0) const;
	int update(MtADORecordset &record);
	int commit(const int commit_means,Database &database) const;
//variables
private:
	int _id;
	int _no;
	CString _name;
	CString _alias;
	Status _status;
};