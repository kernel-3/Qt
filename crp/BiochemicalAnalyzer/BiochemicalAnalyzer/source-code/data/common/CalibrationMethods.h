#pragma once

#include<memory>
#include<vector>

class CalibrationMethod;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**
 * name: CalibrationMethods
 * brief: 定标方法管理类，负责管理维护管理
 *        系统中全部的定标方法。
 * author: yameng_he
 * date: 2015-12-22
 */
class CalibrationMethods{
//define
public:
	typedef std::shared_ptr<CalibrationMethod> PtrToMethod;
	typedef std::shared_ptr<const CalibrationMethod> PtrToCMethod;
	typedef std::vector<PtrToMethod> Methods;
	typedef MtSingleton<CalibrationMethods,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~CalibrationMethods(void);
//interface
public:
	static CalibrationMethods *instance();
//interface
public:
	unsigned int get_count() const;
	PtrToCMethod get_method(const unsigned int index) const;
	int update(Database &database);
//construction
private:
	CalibrationMethods(void);
//restriction
private:
	CalibrationMethods(const CalibrationMethods &);
	CalibrationMethods &operator=(const CalibrationMethods &);
//variables
private:
	MtLock *_lock;
	Methods _methods;
};

