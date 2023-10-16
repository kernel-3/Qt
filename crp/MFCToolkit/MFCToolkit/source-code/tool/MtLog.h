#pragma once

#include"../Symbol"
#include<fstream>

#ifdef _UNICODE
typedef std::wfstream FStream;
#else
typedef std::fstream FStream;
#endif

class MtLock;

/**
 * name: MtLog
 * brief: 日志类，负责实现日志输出功能。
 * author: yameng_he
 * date: 2016-01-28.
 */
class MFC_TOOLKIT_API MtLog{
//construction & destruction
public:
	MtLog(const CString &directory);
	~MtLog(void);
//interface
public:
	void write(const CString &text);
//implement
private:
	int open(const BOOL is_locked=TRUE);
	void close(const BOOL is_locked=TRUE);
//restriction
private:
	MtLog(const MtLog &);
	MtLog &operator=(const MtLog &);
//variables
private:
	MtLock *_lock;
	CString _directory;
	FStream _file;
};

