#pragma once

#include<memory>
#include<vector>

class Application;
template<typename _Tp,typename _Lock>
class MtSingleton;
class MtLock;
class Database;
class AnalyzeApplication;
class CalibrationApplication;
class RangeApplication;
class StandardApplication;

/**
 * name: Applications
 * brief: 系统中项目申请参数存储类，负责存储系统中
 *        所有项目的申请参数。
 * author: yameng_he
 * date: 2015-06-16
 */
class Applications{
//define
public:
	typedef std::shared_ptr<Application> PtrToApp;
	typedef std::shared_ptr<const Application> PtrToCApp;
	typedef std::vector<PtrToApp> VecApps;
	typedef MtSingleton<Applications,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~Applications(void);
//static interface
public:
	static Applications *instance();
//interface
public:
	PtrToCApp get_by_item_no(const int item_no) const;
	PtrToCApp get_by_item_id(const int item_id) const;
	PtrToCApp get_by_index(const unsigned int index) const;
	BOOL is_item_id_existing(const int item_id) const;
	BOOL is_item_no_existing(const int item_no) const;
	void sort_by_item_no();
	void sort_by_item_id();
	int add(const PtrToApp &application,Database &database);
	int remove(const int item_id,Database &database);
	int update(Database &database);
	int commit(const int item_id,const CString &item_alias,
		const AnalyzeApplication &analyze,Database &database);
	int commit(const int item_id,
		const CalibrationApplication &calibration,Database &database);
	int commit(const int item_id,const CString &item_alias,
		const RangeApplication &analyze,Database &database);
	int commit(const int item_id,const StandardApplication &standard,
		Database &database);
	unsigned int get_size() const;
	int assign_item_id();
//construction
private:
	Applications(void);
//restriction
private:
	Applications(const Applications &);
	Applications &operator=(const Applications &);
//variables
private:
	MtLock *_lock;
	VecApps _applications;
};