#pragma once

#include<memory>

class MtADOConnection;
class MtADORecordset;

/**
 * name: Database
 * brief: 数据库管理类，负责为系统提供统一的数据库访问接口。
 * author: yameng_he
 * date: 2015-04-29
 */
class Database{
//define
public:
	typedef std::shared_ptr<Database> PtrToDatabase;
	typedef std::shared_ptr<MtADOConnection> PtrToConnection;
	typedef std::shared_ptr<MtADORecordset> PtrToRecordset;
	friend class DatabaseManager;
//destructor
public:
	~Database(void);
//interface
public:
	int connect(const long connection_timeout,const long command_timeout,
		const CString &connection_string,const CString &user=_T(""),
		const CString &password=_T(""),const long options=-1);
	void disconnect();
	PtrToRecordset get_recordset(const CString &command,const long cursor_location=3,
		const long cursor_type=3,const long lock_type=1,const long options=1);
	int execute(const CString &sql);
	int begin_trans();
	int commit_trans();
	int rollback_trans();
	PtrToDatabase clone() const;
	BOOL is_connected() const;
//constructor
private:
	Database(void);
	Database(const Database &database);
//implement
private:
	int connect();
	Database &operator=(const Database &database);
//variables
private:
	long _connection_timeout;
	long _command_timeout;
	CString _connection_string;
	CString _user;
	CString _password;
	long _options;
	PtrToConnection _connection;
};