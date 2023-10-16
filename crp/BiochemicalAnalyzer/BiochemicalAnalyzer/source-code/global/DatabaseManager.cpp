#include"stdafx.h"
#include"DatabaseManager.h"
#include"Database.h"
#include"../global/GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"

//初始化静态变量。
const CString DatabaseManager::DATABASE_PATH(_T("db\\"));
const CString DatabaseManager::MAIN_DATABASE_NAME(_T("Axceed260"));

/**
 * name: ~DatabaseManager
 * breif: 析构函数。
 * param: --
 * return: --
 */
DatabaseManager::~DatabaseManager(void){
	disconnect_from_databases();
	delete _main_database;
}

/**
 * name: DatabaseManager
 * brief: 获取数据库管理类实例对象指针。
 * param: --
 * return: 返回数据库管理类实例对象指针。
 */
DatabaseManager *DatabaseManager::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_database
 * brief: 获取系统中指定的数据库。
 * param: database_name - 数据库名称。
 * return: 如果函数执行成功返回指向数据库操作实例的指针，否则返回空指针。
 */
Database *DatabaseManager::get_database(const DatabaseName database_name){
	//1.如果当前期望获取主数据库。
	if(DATABASE_NAME_MAIN==database_name){
		return(_main_database);
	}
	//2.如果当前期望获取其它未知数据库。
	else{
		return(0);
	}
}

/**
 * name: connect_to_databases
 * brief: 将系统中所有数据库实例对象全部连接到指定数据库上。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DatabaseManager::connect_to_databases(){
	//1.首先连接主数据库，并且判断连接是否成功。
	//SQL Server
	if(_main_database->connect(5,3,_T("Persist Security Info=True;\
		Provider=SQLOLEDB.1;Data Source=HEYAMENG-PC\\SQLEXPRESS;Initial Catalog=")+
		MAIN_DATABASE_NAME+_T(";User ID=sa;Password=123456;"))<0){
		return(-1);
	}
	/*
	//access
	if(_main_database->connect(5,3,
		_T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=")+
		GlobalData::instance()->get_master_directory()+DATABASE_PATH+
		MAIN_DATABASE_NAME+_T(";Jet OLEDB:Database Password=;"))<0){
		return(-1);
	}
	*/
	//2.程序运行到此成功返回。
	return(0);
}

/**
 * name: disconnect_from_databases
 * brief: 断块系统中与所有数据库的连接。
 * param: --
 * return: --
 */
void DatabaseManager::disconnect_from_databases(){
	//1.首先断开与主数据库的连接。
	_main_database->disconnect();
}

/**
 * name: DatabaseManager
 * brief: 构造函数。
 * param: --
 * return: --
 */
DatabaseManager::DatabaseManager(void)
	:_main_database(new Database){
}