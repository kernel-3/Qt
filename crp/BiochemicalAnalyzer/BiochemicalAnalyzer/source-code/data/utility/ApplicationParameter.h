#pragma once

#include<memory>

class ApplicationData;
class MtADORecordset;
class Database;
class ApplicationAnalysisData;

/**
 * name: ApplicationParameter
 * breif: 应用参数类，负责描述一个项目的应用参数。
 * author: yameng_he
 * date: 2015-11-16
 */
class ApplicationParameter{
//define
public:
	enum{DATA_COUNT=1,};
	typedef enum{DATA_NAME_ANALYSIS=0,} DataName;
	typedef std::shared_ptr<ApplicationData> PtrToData;
	typedef std::shared_ptr<const ApplicationData> PtrToCData;
//construction & destruction
public:
	ApplicationParameter(void);
	ApplicationParameter(const int module_id,
		const int specimen_type_id,const int item_id);
	~ApplicationParameter(void);
//interface
public:
	int get_module_id() const;
	int get_specimen_type_id() const;
	int get_item_id() const;
	PtrToCData get(const DataName data_name) const;
	int modify(const ApplicationAnalysisData &data);
	int modify(const DataName data_name,const ApplicationData *data);
	int is_valid(CString *error_message=0) const;
	void reset_default_value(const int reagent_code);
	int update(MtADORecordset &recordset);
	int commit(const int commit_means,Database &database,
		const BOOL is_transaction=TRUE) const;
//restriction
private:
	ApplicationParameter(const ApplicationParameter &);
	ApplicationParameter &operator=(const ApplicationParameter &);
//variables
private:
	PtrToData *_data;
};