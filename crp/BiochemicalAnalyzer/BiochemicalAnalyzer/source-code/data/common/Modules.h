#pragma once

#include<memory>
#include<vector>

class Module;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**
 * name: Modules
 * breif: 模块管理类，负责系统中所有模块信息
 *        数据的维护以及管理。
 * author: yameng_he
 * date: 2015-11-07
 */
class Modules{
//define
public:
	typedef std::shared_ptr<Module> PtrToModule;
	typedef std::shared_ptr<const Module> PtrToCModule;
	typedef std::vector<PtrToModule> VModules;
	typedef MtSingleton<Modules,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~Modules(void);
//interface
public:
	static Modules *instance();
//interface
public:
	unsigned int get_count() const;
	PtrToCModule get_by_id(const int id) const;
	PtrToCModule get_by_index(const unsigned int index) const;
	int update(Database &database);
	int commit(const int commit_means,Database &database) const;
	int commit(const int module_id,const int commit_means,Database &database) const;
//construction
private:
	Modules(void);
//restriction
private:
	Modules(const Modules &);
	Modules &operator=(const Modules &);
//variables
private:
	MtLock *_lock;
	VModules _modules;
};

