#include"stdafx.h"
#include"DatabaseManager.h"
#include"Database.h"
#include"../global/GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"

//��ʼ����̬������
const CString DatabaseManager::DATABASE_PATH(_T("db\\"));
const CString DatabaseManager::MAIN_DATABASE_NAME(_T("Axceed260"));

/**
 * name: ~DatabaseManager
 * breif: ����������
 * param: --
 * return: --
 */
DatabaseManager::~DatabaseManager(void){
	disconnect_from_databases();
	delete _main_database;
}

/**
 * name: DatabaseManager
 * brief: ��ȡ���ݿ������ʵ������ָ�롣
 * param: --
 * return: �������ݿ������ʵ������ָ�롣
 */
DatabaseManager *DatabaseManager::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_database
 * brief: ��ȡϵͳ��ָ�������ݿ⡣
 * param: database_name - ���ݿ����ơ�
 * return: �������ִ�гɹ�����ָ�����ݿ����ʵ����ָ�룬���򷵻ؿ�ָ�롣
 */
Database *DatabaseManager::get_database(const DatabaseName database_name){
	//1.�����ǰ������ȡ�����ݿ⡣
	if(DATABASE_NAME_MAIN==database_name){
		return(_main_database);
	}
	//2.�����ǰ������ȡ����δ֪���ݿ⡣
	else{
		return(0);
	}
}

/**
 * name: connect_to_databases
 * brief: ��ϵͳ���������ݿ�ʵ������ȫ�����ӵ�ָ�����ݿ��ϡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DatabaseManager::connect_to_databases(){
	//1.�������������ݿ⣬�����ж������Ƿ�ɹ���
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
	//2.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: disconnect_from_databases
 * brief: �Ͽ�ϵͳ�����������ݿ�����ӡ�
 * param: --
 * return: --
 */
void DatabaseManager::disconnect_from_databases(){
	//1.���ȶϿ��������ݿ�����ӡ�
	_main_database->disconnect();
}

/**
 * name: DatabaseManager
 * brief: ���캯����
 * param: --
 * return: --
 */
DatabaseManager::DatabaseManager(void)
	:_main_database(new Database){
}