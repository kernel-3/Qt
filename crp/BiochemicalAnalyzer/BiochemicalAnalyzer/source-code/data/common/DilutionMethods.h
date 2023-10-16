#pragma once

#include<memory>
#include<vector>

class DilutionMethod;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**  
 * name: DilutionMethods
 * breif: 稀释方法管理类，负责维护系统中全部的稀释方法，
 *        并提供与其相关的全部接口。
 * author: yameng_he
 * date: 2015-12-01
 */
class DilutionMethods{
//define
public:
	typedef std::shared_ptr<DilutionMethod> PtrToMethod;
	typedef std::shared_ptr<const DilutionMethod> PtrToCMethod;
	typedef std::vector<PtrToMethod> Methods;
	typedef MtSingleton<DilutionMethods,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~DilutionMethods(void);
//interface
public:
	static DilutionMethods *instance();
//interface
public:
	unsigned int get_count() const;
	PtrToCMethod get_method(const unsigned int index) const;
	int update(Database &database);
//construction
private:
	DilutionMethods(void);
//restriction
private:
	DilutionMethods(const DilutionMethods &);
	DilutionMethods &operator=(const DilutionMethods &);
//variables
private:
	MtLock *_lock;
	Methods _methods;
};