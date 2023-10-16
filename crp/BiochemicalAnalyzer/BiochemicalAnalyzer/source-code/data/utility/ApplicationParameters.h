#pragma once

#include<memory>
#include<map>

class ApplicationParameter;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;
class ApplicationAnalysisData;

/**
 * name: ApplicationParameters
 * breif: 应用参数管理类，负责维护系统中全部的应用参数。
 * author: yameng_he
 * date: 2015-11-16
 */
class ApplicationParameters{
//define
public:
	typedef std::shared_ptr<ApplicationParameter> PtrToParameter;
	typedef std::shared_ptr<const ApplicationParameter> PtrToCParameter;
	typedef std::map<int,PtrToParameter> Parameters;
	typedef MtSingleton<ApplicationParameters,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~ApplicationParameters(void);
//interface
public:
	static ApplicationParameters *instance();
//interface
public:
	int add(const PtrToParameter &parameter);
	PtrToCParameter get(const int module_id,
		const int specimen_type_id,const int item_id) const;
	int modify(const ApplicationAnalysisData &parameter);
	int remove(const int item_id);
	int update(Database &database);
	int commit(const int item_id,const int commit_means,
		Database &database,const BOOL is_transaction=TRUE) const;
//construction
private:
	ApplicationParameters(void);
//restriction
private:
	ApplicationParameters(const ApplicationParameters &);
	ApplicationParameters &operator=(const ApplicationParameters &);
//variables
private:
	MtLock *_lock;
	Parameters _parameters;
};

