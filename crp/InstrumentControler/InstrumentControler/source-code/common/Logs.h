#pragma once

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class MtLog;

/**
 * name: Logs
 * brief: 日志管理类，负责维护系统中的全部日志。
 * author: yameng_he
 * date: 2016-01-28.
 */
class Logs{
//define
public:
	typedef enum{NAME_COMMAND,NAME_EVENT,NAME_ERROR,}Name;
	typedef MtSingleton<Logs,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~Logs(void);
//interface
public:
	static Logs *instance();
//interface
public:
	void write(const Name name,const CString &text);
//construction
private:
	Logs(void);
//restriction
private:
	Logs(const Logs &);
	Logs &operator=(const Logs &);
//variables
private:
	MtLog *_command;
	MtLog *_event;
	MtLog *_error;
};

