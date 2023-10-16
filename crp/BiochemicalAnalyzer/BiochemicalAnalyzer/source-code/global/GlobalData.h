#pragma once

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;

/**
 * name: GlobalData
 * brief: 全局数据管理类，负责维护系统中一些常规的全局数据。
 * author: yameng_he
 * date: 2014-12-04
 */
class GlobalData{
//define
public:
	typedef MtSingleton<GlobalData,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~GlobalData(void);
//static interface
public:
	static GlobalData *instance();
//interface
public:
	const CString &get_master_directory() const;
//construction
private:
	GlobalData(void);
//implement
private:
	void init();
//restrict
private:
	GlobalData(const GlobalData &);
	GlobalData &operator=(const GlobalData &);
//variables
private:
	CString _master_directory;
};