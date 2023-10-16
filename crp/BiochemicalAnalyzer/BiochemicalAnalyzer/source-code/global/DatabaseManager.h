#pragma once

class Database;
template<typename _Tp,typename _Lock>
class MtSingleton;
class MtLock;

/**
 * name: DatabaseManager
 * brief: 数据库管理类，负责维护管理系统中所有数据库连接实例。
 * author: yameng_he
 * date: 2015-02-13
 */
class DatabaseManager{
//define
public:
	typedef enum{DATABASE_NAME_MAIN,}DatabaseName;
	static const CString DATABASE_PATH;
	static const CString MAIN_DATABASE_NAME;
	typedef MtSingleton<DatabaseManager,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~DatabaseManager(void);
//static interface
public:
	static DatabaseManager *instance();
//interface
public:
	Database *get_database(const DatabaseName database_name);
	int connect_to_databases();
	void disconnect_from_databases();
//construction
private:
	DatabaseManager(void);
//restruction
private:
	DatabaseManager(const DatabaseManager &);
	DatabaseManager &operator=(const DatabaseManager &);
//variables
private:
	Database *_main_database;
};