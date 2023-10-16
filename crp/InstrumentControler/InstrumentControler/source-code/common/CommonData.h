#pragma once

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;

/**
 * name: CommonData
 * brief: 通用数据类，负责维护管理一些系统通用的
 *        数据。
 * author: yameng_he
 * date: 2016-01-28.
 */
class CommonData{
//define
public:
	typedef MtSingleton<CommonData,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~CommonData(void);
//static interface
public:
	static CommonData *instance();
//interface
public:
	CString get_master_directory() const;
//construction
private:
	CommonData(void);
//implement
private:
	void init();
//restriction
private:
	CommonData(const CommonData &);
	CommonData &operator=(const CommonData &);
//variables
private:
	CString _master_directory;
};

