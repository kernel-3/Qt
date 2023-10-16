#include"stdafx.h"
#include"Database.h"
#include"../../../../include/mfctoolkit/database/MtADOConnection.h"
#include"../../../../include/mfctoolkit/database/MtADORecordset.h"
#include<assert.h>

/**
 * name: ~Database
 * brief: 析构函数。
 * param: --
 * return: --
 */
Database::~Database(void){
	if(static_cast<bool>(_connection)){
		disconnect();
	}
}

/**
 * name: connect
 * brief: 连接到数据库。
 * param: connection_timeout - 连接超时时间（单位：秒）。
 *        command_timeout - 指令超时时间（单位：秒）。
 *        connection_string - 数据库连接字符串。
 *        user - 用户。
 *        password - 密码。
 *        options - 连接设置项。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Database::connect(const long connection_timeout,const long command_timeout,
	const CString &connection_string,const CString &user/*=_T("")*/,const CString &password/*=_T("")*/,
	const long options/*=-1*/){
	//1.创建新的数据库连接实例，并且判断创建是否成功。
	PtrToConnection connection(new MtADOConnection);
	if(!static_cast<bool>(connection)){
		return(-1);
	}
	//2.设置连接超时时间。
	connection->set_connection_timeout(connection_timeout);
	if(0!=connection->get_last_error_code()){
		return(-2);
	}
	//3.设置指令执行超时时间。
	connection->set_command_timeout(command_timeout);
	if(0!=connection->get_last_error_code()){
		return(-3);
	}
	//4.进行数据库连接，并且判断连接是否成功。
	connection->open(connection_string,user,password,options);
	if(0!=connection->get_last_error_code()){
		return(-4);
	}
	//5.保存当前连接实例以及连接参数。
	_connection_timeout=connection_timeout;
	_command_timeout=command_timeout;
	_connection_string=connection_string;
	_user=user;
	_password=password;
	_options=options;
	_connection=connection;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: disconnect
 * brief: 断开当前到数据库的连接。
 * param: --
 * return: --
 */
void Database::disconnect(){
	_connection.reset();
	_connection_timeout=0;
	_command_timeout=0;
	_connection_string=_T("");
	_user=_T("");
	_password=_T("");
	_options=0;
}

/**
 * name: get_recordset
 * brief: 获取记录集。
 * param: command - 命令文本（SQL语句）。
 *        cursor_location - 游标位置（1 未知 2 服务器 3 客户端）
 *        cursor_type - 游标类型( -1 未定义游标类型 0 仅向前类型游标 1 键集类型游标 2 动态类型游标 3 静态类型游标)。
 *        lock_type - 锁类型（ -1 未定义锁类型 1 只读 2 保守式锁定 3 开放式锁定 4 开放式批更新）
 *        options - 连接方式（-1 未定义 8 未知 1 文本 2 表 4 存储过程 256 文件 512 表所有行 16 异步执行 32 提取 64 提取不阻塞）
 * return: 如果函数执行成功返回记录集智能指针，否则返回空的智能指针。
 */
Database::PtrToRecordset Database::get_recordset(const CString &command,const long cursor_location/*=3*/,
	const long cursor_type/*=3*/,const long lock_type/*=1*/,const long options/*=1*/){
	//1.如果当前 Connection 对象尚未打开。
	if(_connection->is_open()<=0){
		return(PtrToRecordset());
	}
	//2.创建记录集智能指针，并且判断创建是否成功。
	PtrToRecordset recordset(new MtADORecordset);
	if(!static_cast<bool>(recordset)){
		return(PtrToRecordset());
	}
	//3.设置记录集游标位置。
	recordset->set_cursor_location(static_cast<ADODB::CursorLocationEnum>(cursor_location));
	if(0!=recordset->get_last_error_code()){
		return(PtrToRecordset());
	}
	//4.打开记录集，并且判断打开是否成功。
	if(FAILED(recordset->open(static_cast<_variant_t>(static_cast<LPCTSTR>(command)),
		_variant_t(static_cast<IDispatch*>(_connection->get_connection()),true),
		static_cast<ADODB::CursorTypeEnum>(cursor_type),static_cast<ADODB::LockTypeEnum>(lock_type),
		options))){
		return(PtrToRecordset());
	}
	//5.如果记录集打开成功，则返回记录集。
	return(recordset);
}

/**
 * name: execute
 * breif: 对数据库执行一条不带返回的SQL语句（例如: 插入、删除、更新等等）。
 * param: sql - SQL语句。
 * return: 如果函数执行成功，返回值大于等于零，否则返回值小于零。
 */
int Database::execute(const CString &sql){
	//1.如果当前SQL语句为空，则直接返回错误。
	if(_T("")==sql){
		return(-1);
	}
	//2.如果当前 Connection 对象尚未打开。
	if(_connection->is_open()<=0){
		return(-2);
	}
	//3.执行当前SQL语句，并且判断执行是否成功。
	_connection->execute(sql);
	if(0!=_connection->get_last_error_code()){
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: begin_trans
 * breif: 为数据库开启一个任务。
 * param: --
 * return: 如果开启任务成功返回值大于等于零，否则返回值小于零。
 * remark: 请避免任务嵌套，如果期望使用嵌套任务，则请详细阅读
 *         《ADO操作手册》中相关章节。
 */
int Database::begin_trans(){
	//1.如果当前 Connection 对象尚未打开。
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.为数据库开启一个任务。
	_connection->begin_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit_trans
 * breif: 为数据库提交一个任务。
 * param: --
 * return: 如果提交任务成功返回值大于等于零，否则返回值小于零。
 * remark: 请避免任务嵌套，如果期望使用嵌套任务，则请详细阅读
 *         《ADO操作手册》中相关章节。
 */
int Database::commit_trans(){
	//1.如果当前 Connection 对象尚未打开。
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.为数据库提交一个任务。
	_connection->commit_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: rollback_trans
 * breif: 为数据库回滚一个任务。
 * param: --
 * return: 如果回滚任务成功返回值大于等于零，否则返回值小于零。
 * remark: 请避免任务嵌套，如果期望使用嵌套任务，则请详细阅读
 *         《ADO操作手册》中相关章节。
 */
int Database::rollback_trans(){
	//1.如果当前 Connection 对象尚未打开。
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.为数据库回滚一个任务。
	_connection->rollback_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: clone
 * brief: 根据当前数据库类实例，科隆出来一个新的数据库实例。
 * param: --
 * return: 如果当前函数操作成功返回新的数据库实例智能指针，否则返回空指针。
 */
Database::PtrToDatabase Database::clone() const{
	return(PtrToDatabase(new Database(*this)));
}

/**
 * name: is_connected
 * brief: 判断当前数据库是否处于连接状态。
 * param: --
 * return: 如果当前数据库处于连接状态则返回TRUE、否则返回FALSE。
 */
BOOL Database::is_connected() const{
	return(0!=_connection.get());
}

/**
 * name: Database
 * brief: 构造函数。
 * param: --
 * return: --
 */
Database::Database(void)
	:_connection_timeout(0)
	,_command_timeout(0)
	,_connection_string(_T(""))
	,_user(_T(""))
	,_password(_T(""))
	,_options(0)
	,_connection(){
}

/**
 * name: Database
 * brief: 拷贝构造函数。
 * param: database - 拷贝源数据库。
 * return: --
 * note: 可以通过调用is_connected函数来判断拷贝构造函数是否成功。
 */
Database::Database(const Database &database)
	:_connection_timeout(database._connection_timeout)
	,_command_timeout(database._command_timeout)
	,_connection_string(database._connection_string)
	,_user(database._user)
	,_password(database._password)
	,_options(database._options)
	,_connection(){
	connect();
}

/**
 * name: connect
 * brief: 连接到数据库。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Database::connect(){
	//1.创建新的数据库连接实例，并且判断创建是否成功。
	PtrToConnection connection(new MtADOConnection);
	if(!static_cast<bool>(connection)){
		return(-1);
	}
	//2.设置连接超时时间。
	connection->set_connection_timeout(_connection_timeout);
	if(0!=connection->get_last_error_code()){
		return(-2);
	}
	//3.设置指令执行超时时间。
	connection->set_command_timeout(_command_timeout);
	if(0!=connection->get_last_error_code()){
		return(-3);
	}
	//4.进行数据库连接，并且判断连接是否成功。
	connection->open(_connection_string,_user,_password,_options);
	if(0!=connection->get_last_error_code()){
		return(-4);
	}
	//5.保存当前连接实例。
	_connection=connection;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: operator=
 * brief: 数据库类赋值符号重载。
 * param: database - 拷贝源数据库。
 * return: 返回当前数据库类实例引用。
 * remark: 可以通过调用is_connected函数来判断赋值操作是否成功。
 */
Database &Database::operator=(const Database &database){
	//1.为当前数据库类中数据赋值。
	_connection_timeout=database._connection_timeout;
	_command_timeout=database._command_timeout;
	_connection_string=database._connection_string;
	_user=database._user;
	_password=database._password;
	_options=database._options;
	//2.利用当前数据库参数连接数据库,并且判断连接是否成功。
	if(connect()<0){
		disconnect();
	}
	//3.返回当前数据库实例引用。
	return(*this);
}