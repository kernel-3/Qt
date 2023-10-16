#pragma once

#include<memory>
#include<vector>

class SpecimenType;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**
 * name: SpecimenTypes
 * breif: 样本信息管理类，负责维护管理系统中全部的
 *        样本类型信息。
 * author: yameng_he
 * date: 2015-11-09
 */
class SpecimenTypes{
//define
public:
	typedef std::shared_ptr<SpecimenType> PtrToSpecimenType;
	typedef std::shared_ptr<const SpecimenType> PtrToCSpecimenType;
	typedef std::vector<PtrToSpecimenType> VSpecimenTypes;
	typedef MtSingleton<SpecimenTypes,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~SpecimenTypes(void);
//construction
private:
	SpecimenTypes(void);
//interface
public:
	static SpecimenTypes *instance();
//interface
public:
	unsigned int get_count() const;
	PtrToCSpecimenType get_by_id(const int id) const;
	PtrToCSpecimenType get_by_index(const unsigned int index) const;
	int update(Database &database);
	int commit(const int commit_means,Database &database) const;
	int commit(const int specimen_type_id,const int commit_means,Database &database) const;
//restriction
private:
	SpecimenTypes(const SpecimenTypes &);
	SpecimenTypes &operator=(const SpecimenTypes &);
//variables
private:
	MtLock *_lock;
	VSpecimenTypes _specimen_types;
};

