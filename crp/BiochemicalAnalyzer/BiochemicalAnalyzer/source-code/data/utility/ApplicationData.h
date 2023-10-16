#pragma once

class MtADORecordset;
class Database;

/**
 * name: ApplicationData
 * breif: 应用数据类，抽象类，它是全部应用数据类的基类。
 * author: yameng_he
 * date: 2015-11-13
 */
class ApplicationData{
//construction & destruction
public:
	ApplicationData(void);
	ApplicationData(const int module_id,
		const int specimen_type_id,const int item_id);
	virtual ~ApplicationData(void);
//interface
public:
	void set_module_id(const int module_id);
	int get_module_id() const;
	void set_specimen_type_id(const int specimen_type_id);
	int get_specimen_type_id() const;
	void set_item_id(const int item_id);
	int get_item_id() const;
//overrides
public:
	virtual int is_valid(CString *error_message=0) const=0;
	virtual void reset_default_value(const int reagent_code=0)=0;
	virtual int update(MtADORecordset &recordset,int &column)=0;
	virtual int commit(const int commit_means,Database &database) const=0;
//variables
private:
	int _module_id;
	int _specimen_type_id;
	int _item_id;
};
