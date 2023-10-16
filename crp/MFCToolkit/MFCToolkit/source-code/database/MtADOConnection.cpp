#include"stdafx.h"
#include"MtADOConnection.h"
#include<assert.h>

/**
 * name: MtADOConnection
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtADOConnection::MtADOConnection(void)
	:_last_error_code(0)
	,_last_error_message(_T(""))
	,_connection(0){
	create_instance();
}

/**
 * name: ~MtADOConnection
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtADOConnection::~MtADOConnection(void){
	release_instance();
}

/**
 * name: set_attribute
 * brief: 设置connection对象的attribute属性。
 * param: attribute - attribute属性值。
 * return: --
 * note: attributes属性为读/写,并且其值可能为以下任意一个或多个
 *       ADODB::XactAttributeEnum值的和（默认为零）。
 *       ADODB::XactAttributeEnum
 *       常量                         说明
 *       =======================================================================================================
 *       adXactCommitRetaining       执行保留的提交，即通过自动调用 CommitTrans 启动新事务。并非所有提供者都支持该常量。 
 *       adXactAbortRetaining        执行保留的中止，即通过自动调用 RollbackTrans 启动新事务。并非所有提供者都支持该常量。 
 *       adXactAsyncPhaseOne
 *       adXactSyncPhaseOne
 *       ========================================================================================================
 * remark: 使用attribute属性可设置或返回Connection对象、Parameter对象、Field对象或,Property对象的特性。
 *         设置多个属性时，可以将相应的常量相加。如果将属性值设置为包括不兼容常量的总和，那么将产生错误。
 *        【远程数据服务用法】该属性在客户端的Connection对象上无效。
 */
void MtADOConnection::set_attribute(const long attribute){
	clear_last_error();
	try{
		_connection->PutAttributes(attribute);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_attribute
 * brief: 获取connection对象的attribute属性。
 * param: --
 * return: 返回connection对象的attribute属性。
 * note: attributes属性为读/写,并且其值可能为以下任意一个或多个
 *       ADODB::XactAttributeEnum值的和（默认为零）。
 *       ADODB::XactAttributeEnum
 *       常量                         说明
 *       =======================================================================================================
 *       adXactCommitRetaining       执行保留的提交，即通过自动调用 CommitTrans 启动新事务。并非所有提供者都支持该常量。 
 *       adXactAbortRetaining        执行保留的中止，即通过自动调用 RollbackTrans 启动新事务。并非所有提供者都支持该常量。 
 *       adXactAsyncPhaseOne
 *       adXactSyncPhaseOne
 *       ========================================================================================================
 * remark: 使用attribute属性可设置或返回Connection对象、Parameter对象、Field对象或,Property对象的特性。
 *         设置多个属性时，可以将相应的常量相加。如果将属性值设置为包括不兼容常量的总和，那么将产生错误。
 *        【远程数据服务用法】该属性在客户端的Connection对象上无效。
 */
long MtADOConnection::get_attribute() const{
	clear_last_error();
	try{
		return(_connection->GetAttributes());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_command_timeout
 * brief: 设置connection对象执行指令时在终止尝试和产生错误之前执行命令期间需等待的时间。
 * param: timeout - 等待的超时时间（单位为秒）。
 * return: --
 * note: 该值指示等待命令执行的时间（单位为秒）。默认值为30。
 * remark: 使用Connection对象或Command上的CommandTimeout属性，允许由于网络拥塞或服务器
 *         负载过重产生的延迟而取消Execute方法调用。如果在CommandTimeout属性中设置的时间
 *         间隔内没有完成命令执行，将产生错误，然后ADO将取消该命令。如果将该属性设置为零，ADO
 *         将无限期等待直到命令执行完毕。请确保正在写入代码的提供者和数据源支持CommandTimeout功能。
 *         Connection对象的CommandTimeout设置不会对相同Connection上Command对象的CommandTimeout
 *         设置产生影响，即Command对象的CommandTimeout属性不继承Connection对象的CommandTimeout的值。
 *         在Connection对象上，打开Connection后，CommandTimeout属性将保持读/写。
 */
void MtADOConnection::set_command_timeout(const long timeout){
	clear_last_error();
	try{
		_connection->PutCommandTimeout(timeout);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_timeout
 * brief: 获取connection对象执行指令时在终止尝试和产生错误之前执行命令期间需等待的时间。
 * param: --
 * return: 返回connection对象执行指令时在终止尝试和产生错误之前执行命令期间需等待的时间。
 * note: 该值指示等待命令执行的时间（单位为秒）。默认值为30。
 * remark: 使用Connection对象或Command上的CommandTimeout属性，允许由于网络拥塞或服务器
 *         负载过重产生的延迟而取消Execute方法调用。如果在CommandTimeout属性中设置的时间
 *         间隔内没有完成命令执行，将产生错误，然后ADO将取消该命令。如果将该属性设置为零，ADO
 *         将无限期等待直到命令执行完毕。请确保正在写入代码的提供者和数据源支持CommandTimeout功能。
 *         Connection对象的CommandTimeout设置不会对相同Connection上Command对象的CommandTimeout
 *         设置产生影响，即Command对象的CommandTimeout属性不继承Connection对象的CommandTimeout的值。
 *         在Connection对象上，打开Connection后，CommandTimeout属性将保持读/写。
 */
long MtADOConnection::get_command_timeout() const{
	clear_last_error();
	try{
		return(_connection->GetCommandTimeout());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_connection_string
 * brief: 设置Connection对象的数据库连接字符串。
 * param: string - 数据库连接字符串。
 * return: --
 * note: 使用ConnectionString属性，通过传递包含一系列由分号分隔的argument=value
 *       语句的详细连接字符串可指定数据源。
 * remark: ADO支持ConnectionString属性的四个参数，任何其他参数将直接传递到提供者而不经过
 *         ADO处理。
 *         ADO支持的参数如下：
 *         参数                             说明 
 *         ==================================================================================================
 *         Provider=                        指定用来连接的提供者名称。 
 *         File Name=                       指定包含预先设置连接信息的特定提供者的文件名称（例如，持久数据源对象）。 
 *         Remote Provider=                 指定打开客户端连接时使用的提供者名称。（仅限于远程数据服务） 
 *         Remote Server=                   指定打开客户端连接时使用的服务器的路径名称。（仅限于远程数据服务） 
 *         ==================================================================================================
 *         设置ConnectionString属性并打开Connection对象后，提供者可以更改属性的内容，例如通过将ADO定义的参数名映射到其提供者
 *         等价项来更改属性的内容。ConnectionString属性将自动继承用于Open方法的ConnectionString参数的值，以便在Open方法调用
 *         期间覆盖当前的ConnectionString属性。由于File Name参数使得ADO加载关联的提供者，因此无法传递Provider和File Name参数。
 *         连接关闭时ConnectionString属性为读/写，打开时其属性为只读。
 *        【远程数据服务用法】 在客户端Connection对象上使用该服务时，ConnectionString属性只能包括Remote Provider和Remote Server参数。
 */
void MtADOConnection::set_connection_string(const CString &string){
	clear_last_error();
	try{
		_connection->PutConnectionString(static_cast<_bstr_t>(string));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_connection_string
 * brief: 获取Connection对象的数据库连接字符串。
 * param: --
 * return: 返回连接字符串。
 * note: 使用ConnectionString属性，通过传递包含一系列由分号分隔的argument=value
 *       语句的详细连接字符串可指定数据源。
 * remark: ADO支持ConnectionString属性的四个参数，任何其他参数将直接传递到提供者而不经过
 *         ADO处理。
 *         ADO支持的参数如下：
 *         参数                             说明 
 *         ==================================================================================================
 *         Provider=                        指定用来连接的提供者名称。 
 *         File Name=                       指定包含预先设置连接信息的特定提供者的文件名称（例如，持久数据源对象）。 
 *         Remote Provider=                 指定打开客户端连接时使用的提供者名称。（仅限于远程数据服务） 
 *         Remote Server=                   指定打开客户端连接时使用的服务器的路径名称。（仅限于远程数据服务） 
 *         ==================================================================================================
 *         设置ConnectionString属性并打开Connection对象后，提供者可以更改属性的内容，例如通过将ADO定义的参数名映射到其提供者
 *         等价项来更改属性的内容。ConnectionString属性将自动继承用于Open方法的ConnectionString参数的值，以便在Open方法调用
 *         期间覆盖当前的ConnectionString属性。由于File Name参数使得ADO加载关联的提供者，因此无法传递Provider和File Name参数。
 *         连接关闭时ConnectionString属性为读/写，打开时其属性为只读。
 *        【远程数据服务用法】 在客户端Connection对象上使用该服务时，ConnectionString属性只能包括Remote Provider和Remote Server参数。
 */
CString MtADOConnection::get_connection_string() const{
	try{
		return(static_cast<LPCTSTR>(
			_connection->GetConnectionString()));
	}catch(const _com_error &error){
		_last_error_code=error.Error();
		_last_error_message=error.ErrorMessage();
		return(_T(""));
	}
}

/**
 * name: set_connection_timeout
 * brief: 设置在终止尝试和产生错误前建立连接期间所等待的时间。
 * param: timeout - 超时时间（单位秒）。
 * return: --
 * note: 设置或返回指示等待连接打开的时间的长整型值（单位为秒）。默认值为15。
 * remark: 如果由于网络拥塞或服务器负载过重导致的延迟使得必须放弃连接尝试时，
 *         请使用 Connection 对象的 ConnectionTimeout 属性。如果打开连接前
 *         所经过的时间超过 ConnectionTimeout 属性上设置的时间，将产生错误，
 *         并且 ADO 将取消该尝试。如果将该属性设置为零，ADO 将无限等待直到连接打开。
 *         请确认正在对其编写代码的提供者会支持 ConnectionTimeout 功能。连接关闭时 
 *         ConnectionTimeout 属性为读/写，而打开时其属性为只读。
 */
void MtADOConnection::set_connection_timeout(const long timeout){
	clear_last_error();
	try{
		_connection->PutConnectionTimeout(timeout);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_connection_timeout
 * brief: 获取在终止尝试和产生错误前建立连接期间所等待的时间。
 * param: timeout - 超时时间（单位秒）。
 * return: 返回在终止尝试和产生错误前建立连接期间所等待的时间。
 * note: 设置或返回指示等待连接打开的时间的长整型值（单位为秒）。默认值为15。
 * remark: 如果由于网络拥塞或服务器负载过重导致的延迟使得必须放弃连接尝试时，
 *         请使用 Connection 对象的 ConnectionTimeout 属性。如果打开连接前
 *         所经过的时间超过 ConnectionTimeout 属性上设置的时间，将产生错误，
 *         并且 ADO 将取消该尝试。如果将该属性设置为零，ADO 将无限等待直到连接打开。
 *         请确认正在对其编写代码的提供者会支持 ConnectionTimeout 功能。连接关闭时 
 *         ConnectionTimeout 属性为读/写，而打开时其属性为只读。
 */
long MtADOConnection::get_connection_timeout() const{
	clear_last_error();
	try{
		return(_connection->GetConnectionTimeout());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_cursor_location
 * brief: 设置游标服务的位置。
 * param: location - 游标服务的位置。
 * return: --
 * note: 设置或返回可设置为以下某个常量的长整型值。
 *       常量                        说明 
 *       ===============================================================================================
 *       adUseNone                  没有使用游标服务。（该常量已过时并且只为了向后兼容才出现）。 
 *       adUseClient                使用由本地游标库提供的客户端游标。本地游标服务通常允许使用的许多功能可能是驱动程序
 *                                  提供的游标无法使用的，因此使用该设置对于那些将要启用的功能是有好处的。AdUseClient 
 *                                  具有向后兼容性，也支持同义的 adUseClientBatch。 
 *       adUseServer                默认值。使用数据提供者的或驱动程序提供的游标。这些游标有时非常灵活，对于其他用户对数
 *                                  据源所作的更改具有额外的敏感性。但是，Microsoft Client Cursor Provider（如已断
 *                                  开关联的记录集）的某些功能无法由服务器端游标模拟，通过该设置将无法使用这些功能。 
 *       ===============================================================================================
 * remark: 该属性允许在可用于提供者的各种游标库中进行选择。通常，可以选择使用客户端游标库或位于服务器上的某个游标库。
 *         该属性设置仅对属性已经设置后才建立的连接有影响。更改 CursorLocation 属性不会影响现有的连接。对于Connection或关闭的
 *         Recordset该属性为读/写，而对打开的Recordset该属性为只读。由Execute方法返回的游标继承该设置。Recordset将自动从与之
 *         关联的连接中继承该设置。
 *        【远程数据服务用法】 当用于客户端(ADOR)Recordset或Connection对象时，只能将CursorLocation属性设置为adUseClient。
 */
void MtADOConnection::set_cursor_location(const ADODB::CursorLocationEnum location){
	clear_last_error();
	try{
		_connection->PutCursorLocation(location);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_cursor_location
 * brief: 返回游标服务的位置。
 * param: location - 游标服务的位置。
 * return: 返回游标服务的位置。
 * note: 设置或返回可设置为以下某个常量的长整型值。
 *       常量                        说明 
 *       ===============================================================================================
 *       adUseNone                  没有使用游标服务。（该常量已过时并且只为了向后兼容才出现）。 
 *       adUseClient                使用由本地游标库提供的客户端游标。本地游标服务通常允许使用的许多功能可能是驱动程序
 *                                  提供的游标无法使用的，因此使用该设置对于那些将要启用的功能是有好处的。AdUseClient 
 *                                  具有向后兼容性，也支持同义的 adUseClientBatch。 
 *       adUseServer                默认值。使用数据提供者的或驱动程序提供的游标。这些游标有时非常灵活，对于其他用户对数
 *                                  据源所作的更改具有额外的敏感性。但是，Microsoft Client Cursor Provider（如已断
 *                                  开关联的记录集）的某些功能无法由服务器端游标模拟，通过该设置将无法使用这些功能。 
 *       ===============================================================================================
 * remark: 该属性允许在可用于提供者的各种游标库中进行选择。通常，可以选择使用客户端游标库或位于服务器上的某个游标库。
 *         该属性设置仅对属性已经设置后才建立的连接有影响。更改 CursorLocation 属性不会影响现有的连接。对于Connection或关闭的
 *         Recordset该属性为读/写，而对打开的Recordset该属性为只读。由Execute方法返回的游标继承该设置。Recordset将自动从与之
 *         关联的连接中继承该设置。
 *        【远程数据服务用法】 当用于客户端(ADOR)Recordset或Connection对象时，只能将CursorLocation属性设置为adUseClient。
 */
ADODB::CursorLocationEnum MtADOConnection::get_cursor_location() const{
	clear_last_error();
	try{
		return(_connection->GetCursorLocation());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adUseNone);
	}
}

/**
 * name: set_default_database
 * brief: 设置字符串来计算出从提供者处可用的数据库的名称。
 * param: database - 数据库的名称。
 * return: --
 * note: 设置或返回字符串来计算出从提供者处可用的数据库的名称。
 * remark: 使用DefaultDatabase属性可设置或返回指定Connection对象上默认数据库的名称。
 *         如果有默认数据库，SQL字符串可使用非限定语法访问该数据库中的对象。如要访问DefaultDatabase
 *         属性中指定数据库以外的数据库中的对象，对象名必须与所需的数据库名称匹配。连接时，
 *         提供者将默认数据库信息写入DefaultDatabase属性。某些提供者对于每个连接只允许一个数据库，
 *         在此情况下将不能更改DefaultDatabase属性。某些数据源和提供者可能不支持此项功能，这时将
 *         返回错误或空的字符串。
 *        【远程数据服务用法】 该属性在客户端的Connection对象上无效。
 */
void MtADOConnection::set_default_database(const CString &database){
	clear_last_error();
	try{
		_connection->PutDefaultDatabase(static_cast<_bstr_t>(database));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_default_database
 * brief: 获取字符串来计算出从提供者处可用的数据库的名称。
 * param: database - 数据库的名称。
 * return: 返回提供者处可用的数据库的名称。
 * note: 设置或返回字符串来计算出从提供者处可用的数据库的名称。
 * remark: 使用DefaultDatabase属性可设置或返回指定Connection对象上默认数据库的名称。
 *         如果有默认数据库，SQL字符串可使用非限定语法访问该数据库中的对象。如要访问DefaultDatabase
 *         属性中指定数据库以外的数据库中的对象，对象名必须与所需的数据库名称匹配。连接时，
 *         提供者将默认数据库信息写入DefaultDatabase属性。某些提供者对于每个连接只允许一个数据库，
 *         在此情况下将不能更改DefaultDatabase属性。某些数据源和提供者可能不支持此项功能，这时将
 *         返回错误或空的字符串。
 *        【远程数据服务用法】 该属性在客户端的Connection对象上无效。
 */
CString MtADOConnection::get_default_database() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_connection->GetDefaultDatabase()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_isolation_level
 * brief: 设置Connection对象的隔离级别。
 * param: level - 隔离级别。
 * return: --
 * note: 设置或返回以下某个 IsolationLevelEnum 值。
 *       常数                         说明 
 *       ====================================================================================
 *       adXactUnspecified           指示提供者正在使用非指定的 IsolationLevel，但其级别无法确定。 
 *       adXactChaos                 默认值。指示无法从更高级隔离事务覆盖挂起的更改。 
 *       adXactBrowse                指示从某事务中可以查看其他事务中未提交的更改。 
 *       adXactReadUncommitted       同 adXactBrowse。 
 *       adXactCursorStability       默认值。表明只有在事务提交后才能从某事务中查看它们的更改。 
 *       adXactReadCommitted         同 adXactCursorStability。 
 *       adXactRepeatableRead        指示无法从某事务中查看其他事务中所作的更改，但通过查询可以得到新记录集。
 *       adXactIsolated              指示该事务在与其他事务隔离的情况下执行。 
 *       adXactSerializable          同 adXactIsolated。 
 *       =====================================================================================
 * remark: 使用IsolationLevel属性可设置Connection对象的隔离级别。IsolationLevel的属性为读/写。直到下次调用
 *         BeginTrans方法时，该设置才可以生效。如果您请求的隔离级别不可用，提供者可能返回下一个更高的隔离级别。
 *        【远程数据服务用法】 当用于客户端Connection对象时，只能将IsolationLevel属性设置为adXactUnspecified。
 *                          由于用户正在使用客户端缓冲区中已断开的 Recordset 对象，所以可能会出现多用户问题。例如，
 *                          当两个不同的用户对同一记录进行更新时，Remote Data Service 只允许首先更新该记录的用户
 *                          实现更新操作。第二个用户的更新请求将失败，并产生错误。
 */
void MtADOConnection::set_isolation_level(const ADODB::IsolationLevelEnum level){
	clear_last_error();
	try{
		_connection->PutIsolationLevel(level);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_isolation_level
 * brief: 获取Connection对象的隔离级别。
 * param: --
 * return: 返回Connection对象的隔离级别。
 * note: 设置或返回以下某个 IsolationLevelEnum 值。
 *       常数                         说明 
 *       ====================================================================================
 *       adXactUnspecified           指示提供者正在使用非指定的 IsolationLevel，但其级别无法确定。 
 *       adXactChaos                 默认值。指示无法从更高级隔离事务覆盖挂起的更改。 
 *       adXactBrowse                指示从某事务中可以查看其他事务中未提交的更改。 
 *       adXactReadUncommitted       同 adXactBrowse。 
 *       adXactCursorStability       默认值。表明只有在事务提交后才能从某事务中查看它们的更改。 
 *       adXactReadCommitted         同 adXactCursorStability。 
 *       adXactRepeatableRead        指示无法从某事务中查看其他事务中所作的更改，但通过查询可以得到新记录集。
 *       adXactIsolated              指示该事务在与其他事务隔离的情况下执行。 
 *       adXactSerializable          同 adXactIsolated。 
 *       =====================================================================================
 * remark: 使用IsolationLevel属性可设置Connection对象的隔离级别。IsolationLevel的属性为读/写。直到下次调用
 *         BeginTrans方法时，该设置才可以生效。如果您请求的隔离级别不可用，提供者可能返回下一个更高的隔离级别。
 *        【远程数据服务用法】 当用于客户端Connection对象时，只能将IsolationLevel属性设置为adXactUnspecified。
 *                          由于用户正在使用客户端缓冲区中已断开的 Recordset 对象，所以可能会出现多用户问题。例如，
 *                          当两个不同的用户对同一记录进行更新时，Remote Data Service 只允许首先更新该记录的用户
 *                          实现更新操作。第二个用户的更新请求将失败，并产生错误。
 */
ADODB::IsolationLevelEnum MtADOConnection::get_isolation_level() const{
	clear_last_error();
	try{
		return(_connection->GetIsolationLevel());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adXactUnspecified);
	}
}

/**
 * name: set_mode
 * brief: 设置Connection对象的模式，也就是Connection对象中修改数据的可用权限。
 * param: mode - Connection对象模式。
 * return: --
 * note: 设置或返回以下某个ConnectModeEnum 的值。
 *       常量                                 说明 
 *       =====================================================================================================
 *       AdModeUnknown                       默认值。表明权限尚未设置或无法确定。 
 *       AdModeRead                          表明权限为只读。 
 *       AdModeWrite                         表明权限为只写。 
 *       AdModeReadWrite                     表明权限为读/写。 
 *       AdModeShareDenyRead                 防止其他用户使用读权限打开连接。 
 *       AdModeShareDenyWrite                防止其他用户使用写权限打开连接。 
 *       AdModeShareExclusive                防止其他用户打开连接。 
 *       AdModeShareDenyNone                 防止其他用户使用任何权限打开连接。 
 *       =====================================================================================================
 * remark: 使用Mode属性可设置或返回当前连接上提供者正在使用的访问权限。Mode属性只能在关闭Connection对象时方可设置。
 *         【远程数据服务用法】 当用于客户端Connection对象时，Mode属性只能设置为adModeUnknown。
 */
void MtADOConnection::set_mode(const ADODB::ConnectModeEnum mode){
	clear_last_error();
	try{
		_connection->PutMode(mode);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_mode
 * brief: 获取Connection对象的模式，也就是Connection对象中修改数据的可用权限。
 * param: --
 * return: 返回Connection对象的模式，也就是Connection对象中修改数据的可用权限。
 * note: 设置或返回以下某个ConnectModeEnum 的值。
 *       常量                                 说明 
 *       =====================================================================================================
 *       AdModeUnknown                       默认值。表明权限尚未设置或无法确定。 
 *       AdModeRead                          表明权限为只读。 
 *       AdModeWrite                         表明权限为只写。 
 *       AdModeReadWrite                     表明权限为读/写。 
 *       AdModeShareDenyRead                 防止其他用户使用读权限打开连接。 
 *       AdModeShareDenyWrite                防止其他用户使用写权限打开连接。 
 *       AdModeShareExclusive                防止其他用户打开连接。 
 *       AdModeShareDenyNone                 防止其他用户使用任何权限打开连接。 
 *       =====================================================================================================
 * remark: 使用Mode属性可设置或返回当前连接上提供者正在使用的访问权限。Mode属性只能在关闭Connection对象时方可设置。
 *        【远程数据服务用法】 当用于客户端Connection对象时，Mode属性只能设置为adModeUnknown。
 */
ADODB::ConnectModeEnum MtADOConnection::get_mode() const{
	clear_last_error();
	try{
		return(_connection->GetMode());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adModeUnknown);
	}
}

/**
 * name: set_provider
 * brief: 设置Connection对象提供者的名称。
 * param: provider - 提供者名称。
 * return: --
 * note: 设置或返回字符串值。
 * remark: 使用Provider属性可设置或返回连接提供者的名称。也可以通过ConnectionString属性的内容或Open
 *         方法的ConnectionString参数设置该属性。但是，调用Open方法时在多处指定提供者可能会产生无法预
 *         料的后果。如果没有指定提供者，该属性将默认为 MSDASQL (Microsoft OLE DB Provider for ODBC ）。
 *         关闭连接时Provider属性为读/写，打开连接时该属性为只读。打开Connection对象或访问Connection
 *         对象的Properties集合后该设置才生效。如果该设置无效，将产生错误。
 */
void MtADOConnection::set_provider(const CString &provider){
	clear_last_error();
	try{
		_connection->PutProvider(static_cast<_bstr_t>(provider));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_provider
 * brief: 获取Connection对象提供者的名称。
 * param: --
 * return: 返回Connection对象提供者的名称
 * note: 设置或返回字符串值。
 * remark: 使用Provider属性可设置或返回连接提供者的名称。也可以通过ConnectionString属性的内容或Open
 *         方法的ConnectionString参数设置该属性。但是，调用Open方法时在多处指定提供者可能会产生无法预
 *         料的后果。如果没有指定提供者，该属性将默认为 MSDASQL (Microsoft OLE DB Provider for ODBC ）。
 *         关闭连接时Provider属性为读/写，打开连接时该属性为只读。打开Connection对象或访问Connection
 *         对象的Properties集合后该设置才生效。如果该设置无效，将产生错误。
 */
CString MtADOConnection::get_provider() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_connection->GetProvider()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: get_state
 * brief: 获取当前Connection对象的状态。
 * param: --
 * return: 返回当前Connection对象的状态。
 * note: 返回下列常量之一的长整型值。
 *       常量                                  说明 
 *       ============================================================================================
 *       AdStateClosed                        默认，指示对象是关闭的。 
 *       AdStateOpen                          指示对象是打开的。 
 *       AdStateConnecting                    指示Recordset对象正在连接。 
 *       AdStateExecuting                     指示Recordset对象正在执行命令。 
 *       AdStateFetching                      指示Recordset对象的行正在被读取。 
 *       ============================================================================================
 * remark: 可以随时使用State属性确定指定对象的当前状态。该属性是只读的。Recordset对象的State属性可以是组合值。
 *         例如，如果正在执行语句，该属性将是adStateOpen和adStateExecuting的组合值。
 */
long MtADOConnection::get_state() const{
	clear_last_error();
	try{
		return(_connection->GetState());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_version
 * brief: 获取ADO版本号。
 * param: --
 * return: 返回ADO版本号。
 * note: 返回字符串值。
 * remark: 使用Version属性返回ADO执行的版本号。
 *         提供者的版本作为动态属性可从Properties集合中获得。
 */
CString MtADOConnection::get_version() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_connection->GetVersion()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: get_properties
 * brief: 获取Connection对象的属性信息。
 * param: --
 * return: 返回Connection对象的属性信息。
 */
ADODB::PropertiesPtr MtADOConnection::get_properties() const{
	clear_last_error();
	try{
		return(_connection->GetProperties());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_errors
 * brief: 获取Connection对象的错误信息。
 * param: --
 * return: 返回Connection对象的错误信息。
 */
ADODB::ErrorsPtr MtADOConnection::get_errors() const{
	clear_last_error();
	try{
		return(_connection->GetErrors());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: begin_trans
 * brief: 开始新事务。
 * param: --
 * return: 返回指示事务嵌套层次的长整型变量。
 * remark: 如果希望以独立单元保存或取消对源数据所做的一系列更改，请使用这些具有Connection对象的方法。
 *         例如在货币转帐时，必须从帐户中减去某个数额并将其对等数额添加到另一个帐户。无论其中的哪个更
 *         新失败，都将导致帐户收支不平衡。在打开的事务中进行这些更改可确保只能选择进行全部更改或不作
 *         任何更改。
 *         注意: 并非所有提供者都支持事务。需验证提供者定义的属性“Transaction DDL”是否出现在Connection
 *         对象的Properties集合中，如果在则表示提供者支持事务。如果提供者不支持事务，调用其中的某个
 *         方法将返回错误。一旦调用了BeginTrans方法，在调用CommitTrans或RollbackTrans结束事务之前，
 *         提供者将不再立即提交所作的任何更改。对于支持嵌套事务的提供者来说，调用已打开事务中的BeginTrans
 *         方法将开始新的嵌套事务。返回值将指示嵌套层次：返回值为 1 表示已打开顶层事务（即事务不被另一个事务所嵌套），
 *         返回值为 2 表示已打开第二层事务（嵌套在顶层事务中的事务），依次类推。调用 CommitTrans 或 RollbackTrans 
 *         只影响最新打开的事务；在处理任何更高层事务之前必须关闭或回卷当前事务。调用 CommitTrans 方法将保存连接上
 *         打开的事务中所做的更改并结束事务。调用 RollbackTrans 方法还原打开事务中所做的更改并结束事务。在未打开事
 *         务时调用其中任何一种方法都将引发错误。取决于 Connection 对象的 Attributes 属性，调用 CommitTrans 或 
 *         RollbackTrans 方法都可以自动启动新事务。如果 Attributes 属性设置为 adXactCommitRetaining，提供者在
 *         CommitTrans 调用后会自动启动新事务。如果 Attributes 属性设置为 adXactAbortRetaining，提供者在调用 
 *         RollbackTrans 之后将自动启动新事务。
 *        【远程数据服务】BeginTrans、CommitTrans 和 RollbackTrans 方法在客户端 Connection 对象上无效。
 */
long MtADOConnection::begin_trans(){
	clear_last_error();
	try{
		return(_connection->BeginTrans());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: commit_trans
 * brief: 提交事务。
 * param: --
 * return: --
 * remark: 如果希望以独立单元保存或取消对源数据所做的一系列更改，请使用这些具有Connection对象的方法。
 *         例如在货币转帐时，必须从帐户中减去某个数额并将其对等数额添加到另一个帐户。无论其中的哪个更
 *         新失败，都将导致帐户收支不平衡。在打开的事务中进行这些更改可确保只能选择进行全部更改或不作
 *         任何更改。
 *         注意: 并非所有提供者都支持事务。需验证提供者定义的属性“Transaction DDL”是否出现在Connection
 *         对象的Properties集合中，如果在则表示提供者支持事务。如果提供者不支持事务，调用其中的某个
 *         方法将返回错误。一旦调用了BeginTrans方法，在调用CommitTrans或RollbackTrans结束事务之前，
 *         提供者将不再立即提交所作的任何更改。对于支持嵌套事务的提供者来说，调用已打开事务中的BeginTrans
 *         方法将开始新的嵌套事务。返回值将指示嵌套层次：返回值为 1 表示已打开顶层事务（即事务不被另一个事务所嵌套），
 *         返回值为 2 表示已打开第二层事务（嵌套在顶层事务中的事务），依次类推。调用 CommitTrans 或 RollbackTrans 
 *         只影响最新打开的事务；在处理任何更高层事务之前必须关闭或回卷当前事务。调用 CommitTrans 方法将保存连接上
 *         打开的事务中所做的更改并结束事务。调用 RollbackTrans 方法还原打开事务中所做的更改并结束事务。在未打开事
 *         务时调用其中任何一种方法都将引发错误。取决于 Connection 对象的 Attributes 属性，调用 CommitTrans 或 
 *         RollbackTrans 方法都可以自动启动新事务。如果 Attributes 属性设置为 adXactCommitRetaining，提供者在
 *         CommitTrans 调用后会自动启动新事务。如果 Attributes 属性设置为 adXactAbortRetaining，提供者在调用 
 *         RollbackTrans 之后将自动启动新事务。
 *        【远程数据服务】BeginTrans、CommitTrans 和 RollbackTrans 方法在客户端 Connection 对象上无效。
 */
void MtADOConnection::commit_trans(){
	clear_last_error();
	try{
		_connection->CommitTrans();
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: rollback_trans
 * brief: 回滚事务。
 * param: --
 * return: --
 * remark: 如果希望以独立单元保存或取消对源数据所做的一系列更改，请使用这些具有Connection对象的方法。
 *         例如在货币转帐时，必须从帐户中减去某个数额并将其对等数额添加到另一个帐户。无论其中的哪个更
 *         新失败，都将导致帐户收支不平衡。在打开的事务中进行这些更改可确保只能选择进行全部更改或不作
 *         任何更改。
 *         注意: 并非所有提供者都支持事务。需验证提供者定义的属性“Transaction DDL”是否出现在Connection
 *         对象的Properties集合中，如果在则表示提供者支持事务。如果提供者不支持事务，调用其中的某个
 *         方法将返回错误。一旦调用了BeginTrans方法，在调用CommitTrans或RollbackTrans结束事务之前，
 *         提供者将不再立即提交所作的任何更改。对于支持嵌套事务的提供者来说，调用已打开事务中的BeginTrans
 *         方法将开始新的嵌套事务。返回值将指示嵌套层次：返回值为 1 表示已打开顶层事务（即事务不被另一个事务所嵌套），
 *         返回值为 2 表示已打开第二层事务（嵌套在顶层事务中的事务），依次类推。调用 CommitTrans 或 RollbackTrans 
 *         只影响最新打开的事务；在处理任何更高层事务之前必须关闭或回卷当前事务。调用 CommitTrans 方法将保存连接上
 *         打开的事务中所做的更改并结束事务。调用 RollbackTrans 方法还原打开事务中所做的更改并结束事务。在未打开事
 *         务时调用其中任何一种方法都将引发错误。取决于 Connection 对象的 Attributes 属性，调用 CommitTrans 或 
 *         RollbackTrans 方法都可以自动启动新事务。如果 Attributes 属性设置为 adXactCommitRetaining，提供者在
 *         CommitTrans 调用后会自动启动新事务。如果 Attributes 属性设置为 adXactAbortRetaining，提供者在调用 
 *         RollbackTrans 之后将自动启动新事务。
 *        【远程数据服务】BeginTrans、CommitTrans 和 RollbackTrans 方法在客户端 Connection 对象上无效。
 */
void MtADOConnection::rollback_trans(){
	clear_last_error();
	try{
		_connection->RollbackTrans();
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: cancel
 * breif: 取消执行挂起的异步Execute或Open方法的调用。
 * param: --
 * return: --
 * remark: 使用Cancel方法终止执行异步Execute或Open方法调用（即通过adAsyncConnect、
 *         adAsyncExecute或adAsyncFetch选项调用该方法）。如果在试图终止的方法中没有
 *         使用adAsyncExecute，则Cancel将返回运行时错误。
 *         下表显示在特定类型对象上使用Cancel方法时将终止的任务。
 *         如果对象为                        将终止对该方法的上一次异步调用 
 *         ==========================================================
 *         Command                         Execute 
 *         Connection                      Execute或Open 
 *         Recordset                       Open 
 *         ==========================================================
 */
void MtADOConnection::cancel(){
	clear_last_error();
	try{
		_connection->Cancel();
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: close
 * brief: 关闭打开的对象及任何相关对象。
 * param: --
 * return: --
 * remark: 使用Close方法可关闭Connection对象或Recordset对象以便释放所有关联的系统资源。
 *         关闭对象并非将它从内存中删除，可以更改它的属性设置并且在此后再次打开。要将对象从
 *         内存中完全删除，可将对象变量设置为Nothing。
 *         使用Close方法关闭Connection对象的同时，也将关闭与连接相关联的任何活动Recordset对象。
 *         与正在关闭的Connection对象相关联的Command对象将被持久保留，但不再与Connection对象关联，
 *         即它的ActiveConnection属性将被设置为Nothing，同时，Command对象的Parameters集合将清除
 *         任何提供者定义的参数。可以随后调用Open方法重新建立与相同数据源或其他数据源的连接，关闭Connection
 *         对象后，调用任何需要打开与对数据源连接的方法都将产生错误。当连接上有打开的Recordset对象时，关闭
 *         Connection对象将回卷所有Recordset对象的挂起更改。在事务进行过程中显式关闭Connection对象（调用
 *         Close方法）将产生错误。如果在事务进行过程中Connection对象超出范围，那么ADO将自动回卷事务。
 */
void MtADOConnection::close(){
	clear_last_error();
	try{
		_connection->Close();
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: execute
 * brief: 执行指定的查询、SQL 语句、存储过程或特定提供者的文本等内容。
 * param: command - 字符串，包含要执行的 SQL 语句、表名、存储过程或特定提供者的文本。
 *        options - 可选，长整型值，指示提供者应如何计算command参数,可为下列值：
 *        常量                    说明 
 *        ===============================================================================================
 *        AdCmdText              指示提供者应按命令的文本定义计算 CommandText。 
 *        AdCmdTable             指示 ADO 应生成 SQL 查询以便从 CommandText 命名的表中返回所有行。 
 *        AdCmdTableDirect       指示提供者应从 CommandText 命名的表中返回所有行。 
 *        AdCmdTable             指示提供者应按表名计算 CommandText。 
 *        AdCmdStoredProc        指示提供者应按存储过程计算 CommandText。 
 *        AdCmdUnknown           指示 CommandText 参数中的命令类型未知。 
 *        adAsyncExecute         指示命令应该异步执行。 
 *        adAsyncFetch           指示对在 CacheSize 属性指定的初始数量之后的剩余行使用异步提取。
 *        ================================================================================================
 *        records_affected - 可选，长整型变量，提供者向其返回操作所影响的记录数目。
 * return: 返回 Recordset 对象引用。
 * remark: 使用 Connection 对象的 Execute 方法，可执行任何在指定连接的 CommandText 参数中传送给方法的查询。
 *         如果 CommandText 参数指定按行返回的查询，执行产生的任何结果将存储在新的 Recordset 对象中。如果命令
 *         不是按行返回的查询，则提供者返回关闭的 Recordset 对象。返回的 Recordset 对象始终为只读、仅向前的游标。
 *         如需要具有更多功能的 Recordset 对象，应首先创建具有所需属性设置的 Recordset 对象，然后使用 Recordset 
 *         对象的 Open 方法执行查询并返回所需游标类型。CommandText 参数的内容对提供者是特定的，并可以是标准的 SQL 
 *         语法或提供者支持的任何特殊命令格式。该操作完成后将产生 ExecuteComplete 事件。
 */
ADODB::_RecordsetPtr MtADOConnection::execute(
	const CString &command,const long options/*=ADODB::adCmdText*/,long *records_affected/*=0*/){
	clear_last_error();
	try{
		ADODB::_RecordsetPtr recordset=_connection->Execute(
			static_cast<_bstr_t>(command),NULL,options);
		if(0!=records_affected){
		}
		return(recordset);
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: open
 * brief: 打开到数据源的连接。
 * param: connection_string - 可选，字符串，包含连接信息。参阅 ConnectionString 属性可获得有效设置的详细信息。
 *        user_id - 可选，字符串，包含建立连接时所使用用户名。
 *        password - 可选，字符串，包含建立连接时所使用密码。
 *        options - 可选，ConnectOptionEnum 值。决定该方法是在连接建立之后（异步）还是连接建立之前（同步）返回。
 *                  可以是如下某个常量：
 *        常量                            说明 
 *        ==========================================================================================
 *        adConnectUnspecified          （默认）同步打开连接。 
 *        adAsyncConnect                异步打开连接。ConnectComplete 事件可以用于决定连接何时可用。
 *        ==========================================================================================
 * return: --
 * remark: 使用 Connection 对象的 Open 方法可建立到数据源的物理连接。在该方法成功完成后连接是活跃的，可以对它发出命令并且处理结果。
 *         使用可选的 ConnectionString 参数指定连接字符串，它包含由分号分隔的一系列 argument = value 语句。ConnectionString 
 *         属性自动继承用于 ConnectionString 参数的值，因此可在打开之前设置 Connection 对象的 ConnectionString 属性，或在 Open 
 *         方法调用时使用 ConnectionString 参数设置或覆盖当前连接参数。如果在 ConnectionString 参数和可选的 UserID 及 Password 
 *         参数中传送用户和密码信息，那么 UserID 和 Password 参数将覆盖 ConnectionString 中指定的值。在对打开的 Connection 的操作
 *         结束后，可使用 Close 方法释放所有关联的系统资源。关闭对象并非将它从内存中删除；可以更改它的属性设置并在以后再次使用 Open 方法
 *         打开它。要将对象完全从内存中删除，可将对象变量设置为 Nothing。
 *        【远程数据服务】 当在客户端的 Connection 对象上使用 Open 方法时，在 Connection 对象上打开 Recordset 之前 Open 方法其实并
 *         未建立到服务器的连接。
 */
void MtADOConnection::open(const CString &connection_string,
	const CString &user_id,const CString &password,const long options){
	clear_last_error();
	try{
		_connection->Open(static_cast<_bstr_t>(connection_string),
			static_cast<_bstr_t>(user_id),static_cast<_bstr_t>(password),options);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: open_schema
 * brief: 从提供者获取数据库模式信息。
 * param: schema - 所要运行的模式查询类型，可以为下列任意常量。
 *        criteria - 可选。每个 QueryType 选项的查询限制条件数组，如下所列：
 *        schema值                                 criteria值 
 *        =======================================================================
 *        AdSchemaAsserts                          CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME 
 *        AdSchemaCatalogs                         CATALOG_NAME 
 *        AdSchemaCharacterSets                    CHARACTER_SET_CATALOG
 *                                                 CHARACTER_SET_SCHEMA
 *                                                 CHARACTER_SET_NAME 
 *        AdSchemaCheckConstraints                 CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME 
 *        AdSchemaCollations                       COLLATION_CATALOG
 *                                                 COLLATION_SCHEMA
 *                                                 COLLATION_NAME 
 *        AdSchemaColumnDomainUsage                DOMAIN_CATALOG
 *                                                 DOMAIN_SCHEMA
 *                                                 DOMAIN_NAME
 *                                                 COLUMN_NAME 
 *        AdSchemaColumnPrivileges                 TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 COLUMN_NAME
 *                                                 GRANTOR
 *                                                 GRANTEE 
 *        adSchemaColumns                          TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 COLUMN_NAME 
 *        adSchemaConstraintColumnUsage            TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 COLUMN_NAME 
 *        adSchemaConstraintTableUsage             TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME 
 *        adSchemaForeignKeys                      PK_TABLE_CATALOG
 *                                                 PK_TABLE_SCHEMA
 *                                                 PK_TABLE_NAME
 *                                                 FK_TABLE_CATALOG
 *                                                 FK_TABLE_SCHEMA
 *                                                 FK_TABLE_NAME 
 *        adSchemaIndexes                          TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 INDEX_NAME
 *                                                 TYPE
 *                                                 TABLE_NAME 
 *        adSchemaKeyColumnUsage                   CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME
 *                                                 TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 COLUMN_NAME 
 *        adSchemaPrimaryKeys                      PK_TABLE_CATALOG
 *                                                 PK_TABLE_SCHEMA
 *                                                 PK_TABLE_NAME 
 *        adSchemaProcedureColumns                 PROCEDURE_CATALOG
 *                                                 PROCEDURE_SCHEMA
 *                                                 PROCEDURE_NAME
 *                                                 COLUMN_NAME 
 *        adSchemaProcedureParameters              PROCEDURE_CATALOG
 *                                                 PROCEDURE_SCHEMA
 *                                                 PROCEDURE_NAME
 *                                                 PARAMTER_NAME 
 *        adSchemaProcedures                       PROCEDURE_CATALOG
 *                                                 PROCEDURE_SCHEMA
 *                                                 PROCEDURE_NAME
 *                                                 PROCEDURE_TYPE 
 *        adSchemaProviderSpecific                 参见说明 
 *        adSchemaProviderTypes                    DATA_TYPE
 *                                                 BEST_MATCH 
 *        adSchemaReferentialConstraints           CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME 
 *        adSchemaSchemata                         CATALOG_NAME
 *                                                 SCHEMA_NAME
 *                                                 SCHEMA_OWNER 
 *        adSchemaSQLLanguages                     <无> 
 *        adSchemaStatistics                       TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME 
 *        adSchemaTableConstraints                 CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME
 *                                                 TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 CONSTRAINT_TYPE 
 *        adSchemaTablePrivileges                  TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 GRANTOR
 *                                                 GRANTEE 
 *        adSchemaTables                           TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME
 *                                                 TABLE_TYPE 
 *        adSchemaTranslations                     TRANSLATION_CATALOG
 *                                                 TRANSLATION_SCHEMA
 *                                                 TRANSLATION_NAME 
 *        adSchemaUsagePrivileges                  OBJECT_CATALOG
 *                                                 OBJECT_SCHEMA
 *                                                 OBJECT_NAME
 *                                                 OBJECT_TYPE
 *                                                 GRANTOR
 *                                                 GRANTEE 
 *        adSchemaViewColumnUsage                  VIEW_CATALOG
 *                                                 VIEW_SCHEMA
 *                                                 VIEW_NAME 
 *        adSchemaViewTableUsage                   VIEW_CATALOG
 *                                                 VIEW_SCHEMA
 *                                                 VIEW_NAME 
 *        adSchemaViews                            TABLE_CATALOG
 *                                                 TABLE_SCHEMA
 *                                                 TABLE_NAME 
 *        ========================================================================
 *        schema_id -  OLE DB 规范没有定义用于提供者模式查询的 GUID。如果 QueryType 设置为 adSchemaProviderSpecific，
 *                     则需要该参数，否则不使用它。
 * return: 返回包含模式信息的 Recordset 对象。Recordset 将以只读、静态游标打开。
 * remark: open_schema 方法返回与数据源有关的信息，例如关于服务器上的表以及表中的列等信息。
 *         criteria 参数是可用于限制模式查询结果的值数组。每个模式查询有它支持的不同参数集。实际模式由 IDBSchemaRowset 接口下的 
 *         OLE DB 规范定义。ADO 中所支持的参数集已在上面列出。如果提供者定义未在上面列出的非标准模式查询，则常量 adSchemaProviderSpecific 
 *         将用于 schema 参数。在使用该常量时需要 schema_id 参数传递模式查询的 GUID 以用于执行。如果 schema 设置为 
 *         adSchemaProviderSpecific 但是没有提供 schema_id，将导致错误。提供者不需要支持所有的 OLE DB 标准模式查询，只有 
 *         adSchemaTables、adSchemaColumns 和 adSchemaProviderTypes 是 OLE DB 规范需要的。但是对于这些模式查询，提供者不需要支持上面
 *         列出的 criteria 条件约束。
 *        【远程数据服务】   OpenSchema 方法在客户端 Connection 对象上无效。
 *         注意: 在 Visual Basic 中，在由 Connection 对象的 open_schema 方法所返回的 Recordset 中有 4 字节无符号整型 (DBTYPE UI4) 
 *         的列无法与其他变量比较。有关 OLE DB 数据类型的详细信息，请参阅“Microsoft OLE DB 程序员参考”的第十章和附录 A。
 */
ADODB::_RecordsetPtr MtADOConnection::open_schema(const ADODB::SchemaEnum schema){
	clear_last_error();
	try{
		return(_connection->OpenSchema(schema,vtMissing,vtMissing));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: is_open
 * brief: 判断 Connection 对象是否处于打开状态。
 * param:
 * return: 如果 Connection 对象处于打开状态则返回一，否则返回零。如果
 *         判断过程中出现错误，则返回负数做为错误编码。
 */
int MtADOConnection::is_open() const{
	//1.如果当前 Connection 对象尚未创建，则直接返回零。
	if(0==_connection){
		return(0);
	}
	//2.获取 Connection 对象状态，并且判断获取是否成功。
	const long state=get_state();
	if(0!=get_last_error_code()){
		return(-1);
	}
	//3.如果当前 Connection 对象处于关闭状态，则直接返回零。
	if(ADODB::adStateClosed==state){
		return(0);
	}
	//4.如果当前 Connection 对象处于打开状态，则直接返回一。
	return(1);
}

/**
 * name: get_last_error_code
 * brief: 获取最近的错误编码。
 * param: --
 * return: 返回最近的错误编码。
 */
long MtADOConnection::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: 获取最近的错误描述。
 * param: --
 * return: 返回最近的错误描述。
 */
CString MtADOConnection::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: get_connection
 * brief: 获取当前 ADO 连接实例对象（ Connection 对象）。
 * param: --
 * return: 返回当前 ADO 连接实例对象（ Connection 对象）。
 */
ADODB::_ConnectionPtr MtADOConnection::get_connection() const{
	return(_connection);
}

/**
 * name: create_instance
 * brief: 创建实例。
 * param: --
 * return: --
 */
void MtADOConnection::create_instance(){
	const HRESULT result=
		_connection.CreateInstance(_T("ADODB.Connection"));
	assert((SUCCEEDED(result))&&(0!=_connection));
}

/**
 * name: release_instance
 * brief: 释放实例。
 * param: --
 * return: --
 */
void MtADOConnection::release_instance(){
	if(0!=_connection){
		const long state=get_state();
		assert(0==get_last_error_code());
		if(ADODB::adStateOpen==state){
			close();
			assert(0==get_last_error_code());
		}
		_connection.Release();
		_connection=0;
	}
}

/**
 * name: clear_last_error
 * brief: 清除最近错误信息。
 * param: --
 * return: --
 */
void MtADOConnection::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: 记录最近错误信息。
 * param: error - 最近错误信息。
 * return: --
 */
void MtADOConnection::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}