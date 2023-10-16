#include"stdafx.h"
#include"MtADOCommand.h"
#include<assert.h>

/**
 * name: MtADOCommand
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtADOCommand::MtADOCommand(void)
	:_last_error_code(0)
	,_last_error_message(_T(""))
	,_command(0){
	create_instance();
}

/**
 * name: ~MtADOCommand
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtADOCommand::~MtADOCommand(void){
	release_instance();
}

/**
 * name: set_active_connection
 * breif: 指示指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * param: connection - 包含了定义连接或 Connection 对象的字符串。默认情况下为 Null 对象引用。
 * return: --
 * note: 使用 ActiveConnection 属性可确定在其上将执行指定 Command 对象或打开指定 Recordset 的 Connection 对象。
 * remark: 对于 Command 对象，ActiveConnection 属性为读/写。在将该属性设置为打开的 Connection 对象或有效连接字符串之前，
 *         试图调用 Command 对象的 Execute 方法将产生错误。Microsoft Visual Basic   将 ActiveConnection 属性设置为 
 *         Nothing 可使 Command 对象与当前 Connection 脱离关联，并使提供者释放数据源上所有关联的资源。然后，可以使 Command 
 *         对象与相同的 Connection 对象或其他 Connection 对象关联。某些提供者允许将该属性设置从一个 Connection 更改到另一个
 *         Connection，而不必首先将该属性设置为 Nothing。如果 Command 对象的 Parameter 集合包含提供者提供的参数，那么假如将 
 *         ActiveConnection 属性设置为 Nothing 或设置为其他 Connection 对象，将清除集合。如果手工创建 Parameter 对象并使用
 *         这些参数填充 Command 对象的 Parameters 集合，则将 ActiveConnection 属性设置为 Nothing 或其他 Connection 对象
 *         不会影响 Parameters 集合。关闭与 Command 对象相关联的 Connection 对象将把 ActiveConnection 属性设置为 Nothing。
 *         将该属性设置为已关闭的 Connection 对象将产生错误。
 *         Recordset
 *         对于打开的 Recordset 对象或其 Source 属性被设置为有效 Command 对象的 Recordset 对象，ActiveConnection 属性为只读。
 *         否则，该属性为读/写。可以将该属性设置为有效的 Connection 对象，或设置为有效的连接字符串。这时，提供者可使用该定义创建新的 
 *         Connection 对象，并打开连接。另外，提供者可以将该属性设置为新的 Connection 对象，以便向您提供访问扩展错误信息的 Connection 
 *         对象或执行其他命令。如果使用 Open 方法的 ActiveConnection 参数打开 Recordset 对象，ActiveConnection 属性将继承该参数的值。
 *         如果将 Recordset 对象的 Source 属性设置为有效 Command 对象变量，Recordset 的 ActiveConnection 属性将继承 Command 对象的
 *         ActiveConnection 属性的设置。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，只能将该属性设置为连接字符串或（Microsoft Visual Basic 或 VBScript
 *         中）Nothing
 */
void MtADOCommand::set_active_connection(const _variant_t &connection){
	clear_last_error();
	try{
		_command->PutActiveConnection(connection);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_active_connection
 * breif: 指示指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * param: connection - 包含了定义连接或 Connection 对象的字符串。默认情况下为 Null 对象引用。
 * return: 返回指示指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * note: 使用 ActiveConnection 属性可确定在其上将执行指定 Command 对象或打开指定 Recordset 的 Connection 对象。
 * remark: 对于 Command 对象，ActiveConnection 属性为读/写。在将该属性设置为打开的 Connection 对象或有效连接字符串之前，
 *         试图调用 Command 对象的 Execute 方法将产生错误。Microsoft Visual Basic   将 ActiveConnection 属性设置为 
 *         Nothing 可使 Command 对象与当前 Connection 脱离关联，并使提供者释放数据源上所有关联的资源。然后，可以使 Command 
 *         对象与相同的 Connection 对象或其他 Connection 对象关联。某些提供者允许将该属性设置从一个 Connection 更改到另一个
 *         Connection，而不必首先将该属性设置为 Nothing。如果 Command 对象的 Parameter 集合包含提供者提供的参数，那么假如将 
 *         ActiveConnection 属性设置为 Nothing 或设置为其他 Connection 对象，将清除集合。如果手工创建 Parameter 对象并使用
 *         这些参数填充 Command 对象的 Parameters 集合，则将 ActiveConnection 属性设置为 Nothing 或其他 Connection 对象
 *         不会影响 Parameters 集合。关闭与 Command 对象相关联的 Connection 对象将把 ActiveConnection 属性设置为 Nothing。
 *         将该属性设置为已关闭的 Connection 对象将产生错误。
 *         Recordset
 *         对于打开的 Recordset 对象或其 Source 属性被设置为有效 Command 对象的 Recordset 对象，ActiveConnection 属性为只读。
 *         否则，该属性为读/写。可以将该属性设置为有效的 Connection 对象，或设置为有效的连接字符串。这时，提供者可使用该定义创建新的 
 *         Connection 对象，并打开连接。另外，提供者可以将该属性设置为新的 Connection 对象，以便向您提供访问扩展错误信息的 Connection 
 *         对象或执行其他命令。如果使用 Open 方法的 ActiveConnection 参数打开 Recordset 对象，ActiveConnection 属性将继承该参数的值。
 *         如果将 Recordset 对象的 Source 属性设置为有效 Command 对象变量，Recordset 的 ActiveConnection 属性将继承 Command 对象的
 *         ActiveConnection 属性的设置。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，只能将该属性设置为连接字符串或（Microsoft Visual Basic 或 VBScript
 *         中）Nothing
 */
ADODB::_ConnectionPtr MtADOCommand::get_active_connection() const{
	clear_last_error();
	try{
		return(_command->GetActiveConnection());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_command_text
 * brief: 设置包含提供者命令（如 SOL 语句、表格名称或存储的过程调用）的字符串值。默认值为 ""（零长度字符串）。
 * param: command_text - 提供者命令。
 * return: --
 * remark: 使用 CommandText 属性可设置或返回 Command 对象的文本。通常，该属性为 SQL 语句，但也可以是提供者识别的任何其他类型的
 *         命令语句（如存储的过程调用）。SQL 语句必须是提供者查询处理程序支持的特定语法或版本。如果设置 CommandText 属性时将 Command 
 *         对象的 Prepared 属性设置为 True，并将 Command 对象绑定到打开的连接，则在调用 Execute 或 Open 方法时 ADO 将准备查询（即，
 *         提供者保存已编译的查询格式）。取决于 CommandType 属性的设置，ADO 可能改变 CommandText 属性。请随时阅读 CommandText 属性
 *         查看在执行过程中 ADO 将要使用的实际命令文本。
 */
void MtADOCommand::set_command_text(const CString &command_text){
	clear_last_error();
	try{
		_command->PutCommandText(static_cast<LPCTSTR>(command_text));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_text
 * brief: 获取包含提供者命令（如 SOL 语句、表格名称或存储的过程调用）的字符串值。默认值为 ""（零长度字符串）。
 * param: command_text - 提供者命令。
 * return: 返回包含提供者命令（如 SOL 语句、表格名称或存储的过程调用）的字符串值。默认值为 ""（零长度字符串）。
 * remark: 使用 CommandText 属性可设置或返回 Command 对象的文本。通常，该属性为 SQL 语句，但也可以是提供者识别的任何其他类型的
 *         命令语句（如存储的过程调用）。SQL 语句必须是提供者查询处理程序支持的特定语法或版本。如果设置 CommandText 属性时将 Command 
 *         对象的 Prepared 属性设置为 True，并将 Command 对象绑定到打开的连接，则在调用 Execute 或 Open 方法时 ADO 将准备查询（即，
 *         提供者保存已编译的查询格式）。取决于 CommandType 属性的设置，ADO 可能改变 CommandText 属性。请随时阅读 CommandText 属性
 *         查看在执行过程中 ADO 将要使用的实际命令文本。
 */
CString MtADOCommand::get_command_text() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_command->GetCommandText()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_command_timeout
 * brief: 设置长整型值，该值指示等待命令执行的时间（单位为秒）。默认值为 30。
 * param: timeout - 指示等待命令执行的时间（单位为秒）。
 * return: --
 * remark: 使用 Connection 对象或 Command 上的 CommandTimeout 属性，允许由于网络拥塞或服务器负载过重产生的延迟而取消 Execute 方法调用。
 *         如果在 CommandTimeout 属性中设置的时间间隔内没有完成命令执行，将产生错误，然后 ADO 将取消该命令。如果将该属性设置为零，ADO 将无
 *         限期等待直到命令执行完毕。请确保正在写入代码的提供者和数据源支持 CommandTimeout 功能。Connection 对象的 CommandTimeout 设置
 *         不会对相同 Connection 上 Command 对象的 CommandTimeout 设置产生影响，即 Command 对象的 CommandTimeout 属性不继承 
 *         Connection 对象的 CommandTimeout 的值。在 Connection 对象上，打开 Connection 后，CommandTimeout 属性将保持读/写。
 */
void MtADOCommand::set_command_timeout(const long timeout){
	clear_last_error();
	try{
		_command->PutCommandTimeout(timeout);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_timeout
 * brief: 获取长整型值，该值指示等待命令执行的时间（单位为秒）。默认值为 30。
 * param: --
 * return: 返回长整型值，该值指示等待命令执行的时间（单位为秒）。默认值为 30。
 * remark: 使用 Connection 对象或 Command 上的 CommandTimeout 属性，允许由于网络拥塞或服务器负载过重产生的延迟而取消 Execute 方法调用。
 *         如果在 CommandTimeout 属性中设置的时间间隔内没有完成命令执行，将产生错误，然后 ADO 将取消该命令。如果将该属性设置为零，ADO 将无
 *         限期等待直到命令执行完毕。请确保正在写入代码的提供者和数据源支持 CommandTimeout 功能。Connection 对象的 CommandTimeout 设置
 *         不会对相同 Connection 上 Command 对象的 CommandTimeout 设置产生影响，即 Command 对象的 CommandTimeout 属性不继承 
 *         Connection 对象的 CommandTimeout 的值。在 Connection 对象上，打开 Connection 后，CommandTimeout 属性将保持读/写。
 */
long MtADOCommand::get_command_timeout() const{
	clear_last_error();
	try{
		return(_command->GetCommandTimeout());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_command_type
 * breif: 设置 Command 对象的类型。
 * param: type - 指示 Command 对象的类型。
 *               常量                               说明 
 *               =======================================================================================================
 *               AdCmdText                          将 CommandText 作为命令或存储过程调用的文本化定义进行计算。 
 *               AdCmdTable                         将 CommandText 作为其列全部由内部生成的 SQL 查询返回的表格的名称进行计算。 
 *               AdCmdTableDirect                   将 CommandText 作为其列全部返回的表格的名称进行计算。 
 *               AdCmdStoredProc                    将 CommandText 作为存储过程名进行计算。 
 *               AdCmdUnknown                       默认值。CommandText 属性中的命令类型未知。 
 *               adCmdFile                          将 CommandText 作为持久 Recordset 文件名进行计算。 
 *               AdExecuteNoRecords                 指示 CommandText 为不返回行的命令或存储过程（例如，插入数据的命令）。如果检索任意行，
 *                                                  则将丢弃这些行且并不返回。它总是与 adCmdText 或 adCmdStoredProc 进行组合。 
 *               ========================================================================================================
 * return: --
 * remark: 使用 CommandType 属性可优化 CommandText 属性的计算。如果 CommandType 属性的值等于 adCmdUnknown（默认值），系统的性能将会降低，
 *         因为 ADO 必须调用提供者以确定 CommandText 属性是 SQL 语句、还是存储过程或表格名称。如果知道正在使用的命令的类型，可通过设置 
 *         CommandType 属性指令 ADO 直接转到相关代码。如果 CommandType 属性与 CommandText 属性中的命令类型不匹配，调用 Execute 方法时将
 *         产生错误。adExecuteNoRecords 常量通过最小化内部处理来提高性能。该常量不独立使用，它总是与 adCmdText 或 adCmdStoredProc 组合（
 *         如 adCmdText+adExecuteNoRecords）一起使用。如果与 Recordset.Open 一起使用 adExecuteNoRecords，或者该方法使用 Command 对象
 *         都将产生错误。
 */
void MtADOCommand::set_command_type(const ADODB::CommandTypeEnum type){
	clear_last_error();
	try{
		_command->PutCommandType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_type
 * breif: 获取 Command 对象的类型。
 * param: --
 * return: 返回 Command 对象的类型。
 *         常量                               说明 
 *         =======================================================================================================
 *         AdCmdText                          将 CommandText 作为命令或存储过程调用的文本化定义进行计算。 
 *         AdCmdTable                         将 CommandText 作为其列全部由内部生成的 SQL 查询返回的表格的名称进行计算。 
 *         AdCmdTableDirect                   将 CommandText 作为其列全部返回的表格的名称进行计算。 
 *         AdCmdStoredProc                    将 CommandText 作为存储过程名进行计算。 
 *         AdCmdUnknown                       默认值。CommandText 属性中的命令类型未知。 
 *         adCmdFile                          将 CommandText 作为持久 Recordset 文件名进行计算。 
 *         AdExecuteNoRecords                 指示 CommandText 为不返回行的命令或存储过程（例如，插入数据的命令）。如果检索任意行，
 *                                            则将丢弃这些行且并不返回。它总是与 adCmdText 或 adCmdStoredProc 进行组合。 
 *         ========================================================================================================
 * remark: 使用 CommandType 属性可优化 CommandText 属性的计算。如果 CommandType 属性的值等于 adCmdUnknown（默认值），系统的性能将会降低，
 *         因为 ADO 必须调用提供者以确定 CommandText 属性是 SQL 语句、还是存储过程或表格名称。如果知道正在使用的命令的类型，可通过设置 
 *         CommandType 属性指令 ADO 直接转到相关代码。如果 CommandType 属性与 CommandText 属性中的命令类型不匹配，调用 Execute 方法时将
 *         产生错误。adExecuteNoRecords 常量通过最小化内部处理来提高性能。该常量不独立使用，它总是与 adCmdText 或 adCmdStoredProc 组合（
 *         如 adCmdText+adExecuteNoRecords）一起使用。如果与 Recordset.Open 一起使用 adExecuteNoRecords，或者该方法使用 Command 对象
 *         都将产生错误。
 */
ADODB::CommandTypeEnum MtADOCommand::get_command_type() const{
	clear_last_error();
	try{
		return(_command->GetCommandType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adCmdText);
	}
}

/** 
 * name: set_name
 * brief: 设置对象名称。
 * param: name - 对象名称。
 * return: --
 * remark: 使用 Name 属性可将名称赋给  Command、Field、Parameter 或 Property 对象，或检索它们的名称。对于还没有追加到 Parameters 集合
 *         中的 Parameter 对象，Name 属性为读/写。对于已经追加的 Parameter 对象以及所有其他对象，Name 属性为只读。在集合中名称不必唯一。
 *         可以按照序列索引检索对象的  Name 属性，在此之后则可以直接使用名称引用对象。例如，如果 rstMain.Properties(20).Name 为 
 *         Updatability，可以随后将该属性引用为 rstMain.Properties("Updatability")。
 */
void MtADOCommand::set_name(const CString &name){
	clear_last_error();
	try{
		_command->PutName(static_cast<LPCTSTR>(name));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/** 
 * name: get_name
 * brief: 获取对象名称。
 * param: --
 * return: 返回对象名称。
 * remark: 使用 Name 属性可将名称赋给  Command、Field、Parameter 或 Property 对象，或检索它们的名称。对于还没有追加到 Parameters 集合
 *         中的 Parameter 对象，Name 属性为读/写。对于已经追加的 Parameter 对象以及所有其他对象，Name 属性为只读。在集合中名称不必唯一。
 *         可以按照序列索引检索对象的  Name 属性，在此之后则可以直接使用名称引用对象。例如，如果 rstMain.Properties(20).Name 为 
 *         Updatability，可以随后将该属性引用为 rstMain.Properties("Updatability")。
 */
CString MtADOCommand::get_name() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_command->GetName()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_prepared
 * brief: 设置指示执行前是否保存命令的编译版本。
 * param: yes_or_no - 指示执行前是否保存命令的编译版本。
 * return: --
 * remark: 使用 Prepared 属性可使提供者在首次执行 Command 对象前保存 CommandText 属性中指定的已准备好（已编译）的查询版本。
 *         该属性会降低命令首次执行的速度，但提供者对命令进行编译后，在后继的命令执行中提供者可使用已编译好命令版本，这样可以提
 *         高执行性能。如果该属性为 False，提供者将直接执行 Command 对象而不创建编译版本。如果提供者不支持命令准备，将该属性
 *         设置为 True 时也许将返回错误。如果没有返回错误，则只需要忽略准备命令的请求并将 Prepared 属性设置为 False 即可。
 */
void MtADOCommand::set_prepared(const BOOL yes_or_no){
	clear_last_error();
	try{
		const short prepared=((TRUE==yes_or_no)?(-1):0);
		_command->PutPrepared(prepared);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_prepared
 * brief: 获取指示执行前是否保存命令的编译版本。
 * param: --
 * return: 返回指示执行前是否保存命令的编译版本。
 * remark: 使用 Prepared 属性可使提供者在首次执行 Command 对象前保存 CommandText 属性中指定的已准备好（已编译）的查询版本。
 *         该属性会降低命令首次执行的速度，但提供者对命令进行编译后，在后继的命令执行中提供者可使用已编译好命令版本，这样可以提
 *         高执行性能。如果该属性为 False，提供者将直接执行 Command 对象而不创建编译版本。如果提供者不支持命令准备，将该属性
 *         设置为 True 时也许将返回错误。如果没有返回错误，则只需要忽略准备命令的请求并将 Prepared 属性设置为 False 即可。
 */
BOOL MtADOCommand::get_prepared() const{
	clear_last_error();
	try{
		if(-1==_command->GetPrepared()){
			return(TRUE);
		}else{
			return(FALSE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: get_state
 * brief: 获取当前 Command 对象状态。
 * param: --
 * return: 返回当前 Command 对象状态。
 *         常量                                    说明 
 *         ================================================================================================
 *         AdStateClosed                           默认，指示对象是关闭的。 
 *         AdStateOpen                             指示对象是打开的。 
 *         AdStateConnecting                       指示 Recordset 对象正在连接。 
 *         AdStateExecuting                        指示 Recordset 对象正在执行命令。 
 *         AdStateFetching                         指示 Recordset 对象的行正在被读取。 
 *         ================================================================================================
 * remark: 可以随时使用 State 属性确定指定对象的当前状态。该属性是只读的。
 *         Recordset 对象的 State 属性可以是组合值。例如，如果正在执行语句，该属性将是 adStateOpen 和 adStateExecuting 的组合值。
 */
long MtADOCommand::get_state() const{
	clear_last_error();
	try{
		return(_command->GetState());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adStateClosed);
	}
}

/**
 * name: get_parameters
 * brief: 获取 Command 对象的参数信息。
 * param: --
 * return: 返回 Command 对象的参数信息。
 */
ADODB::ParametersPtr MtADOCommand::get_parameters() const{
	clear_last_error();
	try{
		return(_command->GetParameters());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_properties
 * brief: 获取 Command 对象的属性信息。
 * param: --
 * return: 返回 Command 对象的属性信息。
 */
ADODB::PropertiesPtr MtADOCommand::get_properties() const{
	clear_last_error();
	try{
		return(_command->GetProperties());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: cancel
 * brief: 取消执行挂起的异步 Execute 或 Open 方法的调用。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Cancel 方法终止执行异步 Execute 或 Open 方法调用（即通过 adAsyncConnect、adAsyncExecute 或 adAsyncFetch 
 *         选项调用该方法）。如果在试图终止的方法中没有使用 adAsyncExecute，则 Cancel 将返回运行时错误。下表显示在特定类型对象上
 *         使用 Cancel 方法时将终止的任务。
 *         如果对象为                                              将终止对该方法的上一次异步调用 
 *         ========================================================================================================
 *         Command                                                Execute 
 *         Connection                                             Execute 或 Open 
 *         Recordset                                              Open 
 *         ========================================================================================================
 */
HRESULT MtADOCommand::cancel(){
	clear_last_error();
	try{
		return(_command->Cancel());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: create_parameter
 * breif: 使用指定属性创建新的 Parameter 对象。
 * param: name - 可选，字符串，代表 Parameter 对象名称。
 *        data_type - 可选，长整型值，指定 Parameter 对象数据类型。关于有效设置请参见 Type 属性。
 *        diretion - 可选，长整型值，指定 Parameter 对象类型。关于有效设置请参见 Direction 属性。
 *        size - 可选，长整型值，指定参数值最大长度（以字符或字节数为单位）。
 *        value - 可选，变体型，指定 Parameter 对象的值。
 * return: 返回使用指定属性创建新的 Parameter 对象。
 * remark: 使用 CreateParameter 方法可用指定的名称、类型、方向、大小和值创建新的 Parameter 对象。
 *         在参数中传送的所有值都将写入相应的 Parameter 属性。该方法无法自动将 Parameter 对象追加到 Command 对象的 Parameter 集合，
 *         这样就可以设置附加属性。如果将 Parameter 对象追加到集合，则 ADO 将使该附加属性的值生效。如果在 Type 参数中指定可变长度的数
 *         据类型，那么在将它追加到 Parameters 集合之前必须传送 Size 参数或者设置 Parameter 对象的 Size 属性；否则将产生错误。
 */
ADODB::_ParameterPtr MtADOCommand::create_parameter(const CString &name,const ADODB::DataTypeEnum data_type,
	const ADODB::ParameterDirectionEnum diretion,const long size,const _variant_t &value/*=vtMissing*/){
	clear_last_error();
	try{
		return(_command->CreateParameter(
			static_cast<LPCTSTR>(name),data_type,diretion,size,value));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: execute
 * breif: 执行在 CommandText 属性中指定的查询、SQL 语句或存储过程。
 * param: affect_records - 可选，长整型变量，提供者向其返回操作所影响的记录数目。RecordsAffected 参数仅应用于操作查询或存储过程。
 *                         RecordsAffected 不返回由返回结果的查询或存储过程所返回的记录数目。详细信息，请使用 RecordCount 属性。
 *        parameters - 可选，变体型数组，使用 SQL 语句传送的参数值。（用该参数传送时输出参数将不返回正确值。）
 *        options - 可选，长整型值，指示提供者如何计算 Command 对象的 CommandText 属性。该值可为下列常量之一：
 *                  常量                                   说明 
 *                  =================================================================================================
 *                  AdCmdText                             指示提供者应按命令的文本定义（如 SQL 语句）来计算 CommandText。 
 *                  AdCmdTable                            指示 ADO 应生成 SQL 查询以便从 CommandText 命名的表中返回所有行。 
 *                  AdCmdTableDirect                      指示提供者应从 CommandText 命名的表中返回所有行。 
 *                  AdCmdStoredProc                       指示提供者应按存储过程计算 CommandText。 
 *                  AdCmdUnknown                          指示 CommandText 中的命令类型未知。 
 *                  adAsyncExecute                        指示命令应异步执行。 
 *                  adAsyncFetch                          指示对由 CacheSize 属性指定的初始数量之后的剩余行应使用异步提取。 
 *                  ==================================================================================================
 * return: 返回相应的 Recordset 对象。
 * remark: 使用 Command 对象的 Execute 方法可执行在对象的 CommandText 属性中指定的查询。如果 CommandText 属性指定按行返回查询，
 *         执行所产生的任何结果都将存储在新的 Recordset 对象中。如果该命令不是按行返回查询，则提供者返回关闭的 Recordset 对象。某
 *         些应用程序语言允许忽略该返回值（如果不需要任何 Recordset）。如果查询带有参数，将使用 Command 对象中参数的当前值，除非通
 *         过 Execute 调用传送的参数覆盖它们。可以在调用 Execute 方法时通过省略某些参数的新值来覆盖参数子集。指定参数的次序与其在方
 *         法中被传送的次序相同。例如，如果有 4 个（或更多）参数并且希望只为第一个和第四个参数传送新值，则可以将 Array(var1,,,var4) 
 *         作为 Parameters 参数传送。注意: 在 Parameters 参数中传送时输出参数将不返回正确的值。该操作结束后将发出 ExecuteComplete 
 *         事件。
 */
ADODB::_RecordsetPtr MtADOCommand::execute(VARIANT *affect_records,VARIANT *parameters,const long options){
	clear_last_error();
	try{
		return(_command->Execute(affect_records,parameters,options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_last_error_code
 * brief: 获取最近的错误编码。
 * param: --
 * return: 返回最近的错误编码。
 */
long MtADOCommand::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: 获取最近的错误描述。
 * param: --
 * return: 返回最近的错误描述。
 */
CString MtADOCommand::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: create_instance
 * brief: 创建实例。
 * param: --
 * return: --
 */
void MtADOCommand::create_instance(){
	const HRESULT result=
		_command.CreateInstance(_T("ADODB.Command"));
	assert((SUCCEEDED(result))&&(0!=_command));
}

/**
 * name: release_instance
 * brief: 释放实例。
 * param: --
 * return: --
 */
void MtADOCommand::release_instance(){
	if(0!=_command){
		_command.Release();
		_command=0;
	}
}

/**
 * name: clear_last_error
 * brief: 清除最近错误信息。
 * param: --
 * return: --
 */
void MtADOCommand::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: 记录最近错误信息。
 * param: error - 最近错误信息。
 * return: --
 */
void MtADOCommand::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}