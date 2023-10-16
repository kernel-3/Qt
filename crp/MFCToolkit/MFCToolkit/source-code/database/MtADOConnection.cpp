#include"stdafx.h"
#include"MtADOConnection.h"
#include<assert.h>

/**
 * name: MtADOConnection
 * brief: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
MtADOConnection::~MtADOConnection(void){
	release_instance();
}

/**
 * name: set_attribute
 * brief: ����connection�����attribute���ԡ�
 * param: attribute - attribute����ֵ��
 * return: --
 * note: attributes����Ϊ��/д,������ֵ����Ϊ��������һ������
 *       ADODB::XactAttributeEnumֵ�ĺͣ�Ĭ��Ϊ�㣩��
 *       ADODB::XactAttributeEnum
 *       ����                         ˵��
 *       =======================================================================================================
 *       adXactCommitRetaining       ִ�б������ύ����ͨ���Զ����� CommitTrans ���������񡣲��������ṩ�߶�֧�ָó����� 
 *       adXactAbortRetaining        ִ�б�������ֹ����ͨ���Զ����� RollbackTrans ���������񡣲��������ṩ�߶�֧�ָó����� 
 *       adXactAsyncPhaseOne
 *       adXactSyncPhaseOne
 *       ========================================================================================================
 * remark: ʹ��attribute���Կ����û򷵻�Connection����Parameter����Field�����,Property��������ԡ�
 *         ���ö������ʱ�����Խ���Ӧ�ĳ�����ӡ����������ֵ����Ϊ���������ݳ������ܺͣ���ô����������
 *        ��Զ�����ݷ����÷����������ڿͻ��˵�Connection��������Ч��
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
 * brief: ��ȡconnection�����attribute���ԡ�
 * param: --
 * return: ����connection�����attribute���ԡ�
 * note: attributes����Ϊ��/д,������ֵ����Ϊ��������һ������
 *       ADODB::XactAttributeEnumֵ�ĺͣ�Ĭ��Ϊ�㣩��
 *       ADODB::XactAttributeEnum
 *       ����                         ˵��
 *       =======================================================================================================
 *       adXactCommitRetaining       ִ�б������ύ����ͨ���Զ����� CommitTrans ���������񡣲��������ṩ�߶�֧�ָó����� 
 *       adXactAbortRetaining        ִ�б�������ֹ����ͨ���Զ����� RollbackTrans ���������񡣲��������ṩ�߶�֧�ָó����� 
 *       adXactAsyncPhaseOne
 *       adXactSyncPhaseOne
 *       ========================================================================================================
 * remark: ʹ��attribute���Կ����û򷵻�Connection����Parameter����Field�����,Property��������ԡ�
 *         ���ö������ʱ�����Խ���Ӧ�ĳ�����ӡ����������ֵ����Ϊ���������ݳ������ܺͣ���ô����������
 *        ��Զ�����ݷ����÷����������ڿͻ��˵�Connection��������Ч��
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
 * brief: ����connection����ִ��ָ��ʱ����ֹ���ԺͲ�������֮ǰִ�������ڼ���ȴ���ʱ�䡣
 * param: timeout - �ȴ��ĳ�ʱʱ�䣨��λΪ�룩��
 * return: --
 * note: ��ֵָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��Ĭ��ֵΪ30��
 * remark: ʹ��Connection�����Command�ϵ�CommandTimeout���ԣ�������������ӵ���������
 *         ���ع��ز������ӳٶ�ȡ��Execute�������á������CommandTimeout���������õ�ʱ��
 *         �����û���������ִ�У�����������Ȼ��ADO��ȡ����������������������Ϊ�㣬ADO
 *         �������ڵȴ�ֱ������ִ����ϡ���ȷ������д�������ṩ�ߺ�����Դ֧��CommandTimeout���ܡ�
 *         Connection�����CommandTimeout���ò������ͬConnection��Command�����CommandTimeout
 *         ���ò���Ӱ�죬��Command�����CommandTimeout���Բ��̳�Connection�����CommandTimeout��ֵ��
 *         ��Connection�����ϣ���Connection��CommandTimeout���Խ����ֶ�/д��
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
 * brief: ��ȡconnection����ִ��ָ��ʱ����ֹ���ԺͲ�������֮ǰִ�������ڼ���ȴ���ʱ�䡣
 * param: --
 * return: ����connection����ִ��ָ��ʱ����ֹ���ԺͲ�������֮ǰִ�������ڼ���ȴ���ʱ�䡣
 * note: ��ֵָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��Ĭ��ֵΪ30��
 * remark: ʹ��Connection�����Command�ϵ�CommandTimeout���ԣ�������������ӵ���������
 *         ���ع��ز������ӳٶ�ȡ��Execute�������á������CommandTimeout���������õ�ʱ��
 *         �����û���������ִ�У�����������Ȼ��ADO��ȡ����������������������Ϊ�㣬ADO
 *         �������ڵȴ�ֱ������ִ����ϡ���ȷ������д�������ṩ�ߺ�����Դ֧��CommandTimeout���ܡ�
 *         Connection�����CommandTimeout���ò������ͬConnection��Command�����CommandTimeout
 *         ���ò���Ӱ�죬��Command�����CommandTimeout���Բ��̳�Connection�����CommandTimeout��ֵ��
 *         ��Connection�����ϣ���Connection��CommandTimeout���Խ����ֶ�/д��
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
 * brief: ����Connection��������ݿ������ַ�����
 * param: string - ���ݿ������ַ�����
 * return: --
 * note: ʹ��ConnectionString���ԣ�ͨ�����ݰ���һϵ���ɷֺŷָ���argument=value
 *       ������ϸ�����ַ�����ָ������Դ��
 * remark: ADO֧��ConnectionString���Ե��ĸ��������κ�����������ֱ�Ӵ��ݵ��ṩ�߶�������
 *         ADO����
 *         ADO֧�ֵĲ������£�
 *         ����                             ˵�� 
 *         ==================================================================================================
 *         Provider=                        ָ���������ӵ��ṩ�����ơ� 
 *         File Name=                       ָ������Ԥ������������Ϣ���ض��ṩ�ߵ��ļ����ƣ����磬�־�����Դ���󣩡� 
 *         Remote Provider=                 ָ���򿪿ͻ�������ʱʹ�õ��ṩ�����ơ���������Զ�����ݷ��� 
 *         Remote Server=                   ָ���򿪿ͻ�������ʱʹ�õķ�������·�����ơ���������Զ�����ݷ��� 
 *         ==================================================================================================
 *         ����ConnectionString���Բ���Connection������ṩ�߿��Ը������Ե����ݣ�����ͨ����ADO����Ĳ�����ӳ�䵽���ṩ��
 *         �ȼ������������Ե����ݡ�ConnectionString���Խ��Զ��̳�����Open������ConnectionString������ֵ���Ա���Open��������
 *         �ڼ串�ǵ�ǰ��ConnectionString���ԡ�����File Name����ʹ��ADO���ع������ṩ�ߣ�����޷�����Provider��File Name������
 *         ���ӹر�ʱConnectionString����Ϊ��/д����ʱ������Ϊֻ����
 *        ��Զ�����ݷ����÷��� �ڿͻ���Connection������ʹ�ø÷���ʱ��ConnectionString����ֻ�ܰ���Remote Provider��Remote Server������
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
 * brief: ��ȡConnection��������ݿ������ַ�����
 * param: --
 * return: ���������ַ�����
 * note: ʹ��ConnectionString���ԣ�ͨ�����ݰ���һϵ���ɷֺŷָ���argument=value
 *       ������ϸ�����ַ�����ָ������Դ��
 * remark: ADO֧��ConnectionString���Ե��ĸ��������κ�����������ֱ�Ӵ��ݵ��ṩ�߶�������
 *         ADO����
 *         ADO֧�ֵĲ������£�
 *         ����                             ˵�� 
 *         ==================================================================================================
 *         Provider=                        ָ���������ӵ��ṩ�����ơ� 
 *         File Name=                       ָ������Ԥ������������Ϣ���ض��ṩ�ߵ��ļ����ƣ����磬�־�����Դ���󣩡� 
 *         Remote Provider=                 ָ���򿪿ͻ�������ʱʹ�õ��ṩ�����ơ���������Զ�����ݷ��� 
 *         Remote Server=                   ָ���򿪿ͻ�������ʱʹ�õķ�������·�����ơ���������Զ�����ݷ��� 
 *         ==================================================================================================
 *         ����ConnectionString���Բ���Connection������ṩ�߿��Ը������Ե����ݣ�����ͨ����ADO����Ĳ�����ӳ�䵽���ṩ��
 *         �ȼ������������Ե����ݡ�ConnectionString���Խ��Զ��̳�����Open������ConnectionString������ֵ���Ա���Open��������
 *         �ڼ串�ǵ�ǰ��ConnectionString���ԡ�����File Name����ʹ��ADO���ع������ṩ�ߣ�����޷�����Provider��File Name������
 *         ���ӹر�ʱConnectionString����Ϊ��/д����ʱ������Ϊֻ����
 *        ��Զ�����ݷ����÷��� �ڿͻ���Connection������ʹ�ø÷���ʱ��ConnectionString����ֻ�ܰ���Remote Provider��Remote Server������
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
 * brief: ��������ֹ���ԺͲ�������ǰ���������ڼ����ȴ���ʱ�䡣
 * param: timeout - ��ʱʱ�䣨��λ�룩��
 * return: --
 * note: ���û򷵻�ָʾ�ȴ����Ӵ򿪵�ʱ��ĳ�����ֵ����λΪ�룩��Ĭ��ֵΪ15��
 * remark: �����������ӵ������������ع��ص��µ��ӳ�ʹ�ñ���������ӳ���ʱ��
 *         ��ʹ�� Connection ����� ConnectionTimeout ���ԡ����������ǰ
 *         ��������ʱ�䳬�� ConnectionTimeout ���������õ�ʱ�䣬����������
 *         ���� ADO ��ȡ���ó��ԡ����������������Ϊ�㣬ADO �����޵ȴ�ֱ�����Ӵ򿪡�
 *         ��ȷ�����ڶ����д������ṩ�߻�֧�� ConnectionTimeout ���ܡ����ӹر�ʱ 
 *         ConnectionTimeout ����Ϊ��/д������ʱ������Ϊֻ����
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
 * brief: ��ȡ����ֹ���ԺͲ�������ǰ���������ڼ����ȴ���ʱ�䡣
 * param: timeout - ��ʱʱ�䣨��λ�룩��
 * return: ��������ֹ���ԺͲ�������ǰ���������ڼ����ȴ���ʱ�䡣
 * note: ���û򷵻�ָʾ�ȴ����Ӵ򿪵�ʱ��ĳ�����ֵ����λΪ�룩��Ĭ��ֵΪ15��
 * remark: �����������ӵ������������ع��ص��µ��ӳ�ʹ�ñ���������ӳ���ʱ��
 *         ��ʹ�� Connection ����� ConnectionTimeout ���ԡ����������ǰ
 *         ��������ʱ�䳬�� ConnectionTimeout ���������õ�ʱ�䣬����������
 *         ���� ADO ��ȡ���ó��ԡ����������������Ϊ�㣬ADO �����޵ȴ�ֱ�����Ӵ򿪡�
 *         ��ȷ�����ڶ����д������ṩ�߻�֧�� ConnectionTimeout ���ܡ����ӹر�ʱ 
 *         ConnectionTimeout ����Ϊ��/д������ʱ������Ϊֻ����
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
 * brief: �����α�����λ�á�
 * param: location - �α�����λ�á�
 * return: --
 * note: ���û򷵻ؿ�����Ϊ����ĳ�������ĳ�����ֵ��
 *       ����                        ˵�� 
 *       ===============================================================================================
 *       adUseNone                  û��ʹ���α���񡣣��ó����ѹ�ʱ����ֻΪ�������ݲų��֣��� 
 *       adUseClient                ʹ���ɱ����α���ṩ�Ŀͻ����αꡣ�����α����ͨ������ʹ�õ���๦�ܿ�������������
 *                                  �ṩ���α��޷�ʹ�õģ����ʹ�ø����ö�����Щ��Ҫ���õĹ������кô��ġ�AdUseClient 
 *                                  �����������ԣ�Ҳ֧��ͬ��� adUseClientBatch�� 
 *       adUseServer                Ĭ��ֵ��ʹ�������ṩ�ߵĻ����������ṩ���αꡣ��Щ�α���ʱ�ǳ������������û�����
 *                                  ��Դ�����ĸ��ľ��ж���������ԡ����ǣ�Microsoft Client Cursor Provider�����Ѷ�
 *                                  �������ļ�¼������ĳЩ�����޷��ɷ��������α�ģ�⣬ͨ�������ý��޷�ʹ����Щ���ܡ� 
 *       ===============================================================================================
 * remark: �����������ڿ������ṩ�ߵĸ����α���н���ѡ��ͨ��������ѡ��ʹ�ÿͻ����α���λ�ڷ������ϵ�ĳ���α�⡣
 *         ���������ý��������Ѿ����ú�Ž�����������Ӱ�졣���� CursorLocation ���Բ���Ӱ�����е����ӡ�����Connection��رյ�
 *         Recordset������Ϊ��/д�����Դ򿪵�Recordset������Ϊֻ������Execute�������ص��α�̳и����á�Recordset���Զ�����֮
 *         �����������м̳и����á�
 *        ��Զ�����ݷ����÷��� �����ڿͻ���(ADOR)Recordset��Connection����ʱ��ֻ�ܽ�CursorLocation��������ΪadUseClient��
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
 * brief: �����α�����λ�á�
 * param: location - �α�����λ�á�
 * return: �����α�����λ�á�
 * note: ���û򷵻ؿ�����Ϊ����ĳ�������ĳ�����ֵ��
 *       ����                        ˵�� 
 *       ===============================================================================================
 *       adUseNone                  û��ʹ���α���񡣣��ó����ѹ�ʱ����ֻΪ�������ݲų��֣��� 
 *       adUseClient                ʹ���ɱ����α���ṩ�Ŀͻ����αꡣ�����α����ͨ������ʹ�õ���๦�ܿ�������������
 *                                  �ṩ���α��޷�ʹ�õģ����ʹ�ø����ö�����Щ��Ҫ���õĹ������кô��ġ�AdUseClient 
 *                                  �����������ԣ�Ҳ֧��ͬ��� adUseClientBatch�� 
 *       adUseServer                Ĭ��ֵ��ʹ�������ṩ�ߵĻ����������ṩ���αꡣ��Щ�α���ʱ�ǳ������������û�����
 *                                  ��Դ�����ĸ��ľ��ж���������ԡ����ǣ�Microsoft Client Cursor Provider�����Ѷ�
 *                                  �������ļ�¼������ĳЩ�����޷��ɷ��������α�ģ�⣬ͨ�������ý��޷�ʹ����Щ���ܡ� 
 *       ===============================================================================================
 * remark: �����������ڿ������ṩ�ߵĸ����α���н���ѡ��ͨ��������ѡ��ʹ�ÿͻ����α���λ�ڷ������ϵ�ĳ���α�⡣
 *         ���������ý��������Ѿ����ú�Ž�����������Ӱ�졣���� CursorLocation ���Բ���Ӱ�����е����ӡ�����Connection��رյ�
 *         Recordset������Ϊ��/д�����Դ򿪵�Recordset������Ϊֻ������Execute�������ص��α�̳и����á�Recordset���Զ�����֮
 *         �����������м̳и����á�
 *        ��Զ�����ݷ����÷��� �����ڿͻ���(ADOR)Recordset��Connection����ʱ��ֻ�ܽ�CursorLocation��������ΪadUseClient��
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
 * brief: �����ַ�������������ṩ�ߴ����õ����ݿ�����ơ�
 * param: database - ���ݿ�����ơ�
 * return: --
 * note: ���û򷵻��ַ�������������ṩ�ߴ����õ����ݿ�����ơ�
 * remark: ʹ��DefaultDatabase���Կ����û򷵻�ָ��Connection������Ĭ�����ݿ�����ơ�
 *         �����Ĭ�����ݿ⣬SQL�ַ�����ʹ�÷��޶��﷨���ʸ����ݿ��еĶ�����Ҫ����DefaultDatabase
 *         ������ָ�����ݿ���������ݿ��еĶ��󣬶�������������������ݿ�����ƥ�䡣����ʱ��
 *         �ṩ�߽�Ĭ�����ݿ���Ϣд��DefaultDatabase���ԡ�ĳЩ�ṩ�߶���ÿ������ֻ����һ�����ݿ⣬
 *         �ڴ�����½����ܸ���DefaultDatabase���ԡ�ĳЩ����Դ���ṩ�߿��ܲ�֧�ִ���ܣ���ʱ��
 *         ���ش����յ��ַ�����
 *        ��Զ�����ݷ����÷��� �������ڿͻ��˵�Connection��������Ч��
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
 * brief: ��ȡ�ַ�������������ṩ�ߴ����õ����ݿ�����ơ�
 * param: database - ���ݿ�����ơ�
 * return: �����ṩ�ߴ����õ����ݿ�����ơ�
 * note: ���û򷵻��ַ�������������ṩ�ߴ����õ����ݿ�����ơ�
 * remark: ʹ��DefaultDatabase���Կ����û򷵻�ָ��Connection������Ĭ�����ݿ�����ơ�
 *         �����Ĭ�����ݿ⣬SQL�ַ�����ʹ�÷��޶��﷨���ʸ����ݿ��еĶ�����Ҫ����DefaultDatabase
 *         ������ָ�����ݿ���������ݿ��еĶ��󣬶�������������������ݿ�����ƥ�䡣����ʱ��
 *         �ṩ�߽�Ĭ�����ݿ���Ϣд��DefaultDatabase���ԡ�ĳЩ�ṩ�߶���ÿ������ֻ����һ�����ݿ⣬
 *         �ڴ�����½����ܸ���DefaultDatabase���ԡ�ĳЩ����Դ���ṩ�߿��ܲ�֧�ִ���ܣ���ʱ��
 *         ���ش����յ��ַ�����
 *        ��Զ�����ݷ����÷��� �������ڿͻ��˵�Connection��������Ч��
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
 * brief: ����Connection����ĸ��뼶��
 * param: level - ���뼶��
 * return: --
 * note: ���û򷵻�����ĳ�� IsolationLevelEnum ֵ��
 *       ����                         ˵�� 
 *       ====================================================================================
 *       adXactUnspecified           ָʾ�ṩ������ʹ�÷�ָ���� IsolationLevel�����伶���޷�ȷ���� 
 *       adXactChaos                 Ĭ��ֵ��ָʾ�޷��Ӹ��߼��������񸲸ǹ���ĸ��ġ� 
 *       adXactBrowse                ָʾ��ĳ�����п��Բ鿴����������δ�ύ�ĸ��ġ� 
 *       adXactReadUncommitted       ͬ adXactBrowse�� 
 *       adXactCursorStability       Ĭ��ֵ������ֻ���������ύ����ܴ�ĳ�����в鿴���ǵĸ��ġ� 
 *       adXactReadCommitted         ͬ adXactCursorStability�� 
 *       adXactRepeatableRead        ָʾ�޷���ĳ�����в鿴���������������ĸ��ģ���ͨ����ѯ���Եõ��¼�¼����
 *       adXactIsolated              ָʾ���������������������������ִ�С� 
 *       adXactSerializable          ͬ adXactIsolated�� 
 *       =====================================================================================
 * remark: ʹ��IsolationLevel���Կ�����Connection����ĸ��뼶��IsolationLevel������Ϊ��/д��ֱ���´ε���
 *         BeginTrans����ʱ�������òſ�����Ч�����������ĸ��뼶�𲻿��ã��ṩ�߿��ܷ�����һ�����ߵĸ��뼶��
 *        ��Զ�����ݷ����÷��� �����ڿͻ���Connection����ʱ��ֻ�ܽ�IsolationLevel��������ΪadXactUnspecified��
 *                          �����û�����ʹ�ÿͻ��˻��������ѶϿ��� Recordset �������Կ��ܻ���ֶ��û����⡣���磬
 *                          ��������ͬ���û���ͬһ��¼���и���ʱ��Remote Data Service ֻ�������ȸ��¸ü�¼���û�
 *                          ʵ�ָ��²������ڶ����û��ĸ�������ʧ�ܣ�����������
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
 * brief: ��ȡConnection����ĸ��뼶��
 * param: --
 * return: ����Connection����ĸ��뼶��
 * note: ���û򷵻�����ĳ�� IsolationLevelEnum ֵ��
 *       ����                         ˵�� 
 *       ====================================================================================
 *       adXactUnspecified           ָʾ�ṩ������ʹ�÷�ָ���� IsolationLevel�����伶���޷�ȷ���� 
 *       adXactChaos                 Ĭ��ֵ��ָʾ�޷��Ӹ��߼��������񸲸ǹ���ĸ��ġ� 
 *       adXactBrowse                ָʾ��ĳ�����п��Բ鿴����������δ�ύ�ĸ��ġ� 
 *       adXactReadUncommitted       ͬ adXactBrowse�� 
 *       adXactCursorStability       Ĭ��ֵ������ֻ���������ύ����ܴ�ĳ�����в鿴���ǵĸ��ġ� 
 *       adXactReadCommitted         ͬ adXactCursorStability�� 
 *       adXactRepeatableRead        ָʾ�޷���ĳ�����в鿴���������������ĸ��ģ���ͨ����ѯ���Եõ��¼�¼����
 *       adXactIsolated              ָʾ���������������������������ִ�С� 
 *       adXactSerializable          ͬ adXactIsolated�� 
 *       =====================================================================================
 * remark: ʹ��IsolationLevel���Կ�����Connection����ĸ��뼶��IsolationLevel������Ϊ��/д��ֱ���´ε���
 *         BeginTrans����ʱ�������òſ�����Ч�����������ĸ��뼶�𲻿��ã��ṩ�߿��ܷ�����һ�����ߵĸ��뼶��
 *        ��Զ�����ݷ����÷��� �����ڿͻ���Connection����ʱ��ֻ�ܽ�IsolationLevel��������ΪadXactUnspecified��
 *                          �����û�����ʹ�ÿͻ��˻��������ѶϿ��� Recordset �������Կ��ܻ���ֶ��û����⡣���磬
 *                          ��������ͬ���û���ͬһ��¼���и���ʱ��Remote Data Service ֻ�������ȸ��¸ü�¼���û�
 *                          ʵ�ָ��²������ڶ����û��ĸ�������ʧ�ܣ�����������
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
 * brief: ����Connection�����ģʽ��Ҳ����Connection�������޸����ݵĿ���Ȩ�ޡ�
 * param: mode - Connection����ģʽ��
 * return: --
 * note: ���û򷵻�����ĳ��ConnectModeEnum ��ֵ��
 *       ����                                 ˵�� 
 *       =====================================================================================================
 *       AdModeUnknown                       Ĭ��ֵ������Ȩ����δ���û��޷�ȷ���� 
 *       AdModeRead                          ����Ȩ��Ϊֻ���� 
 *       AdModeWrite                         ����Ȩ��Ϊֻд�� 
 *       AdModeReadWrite                     ����Ȩ��Ϊ��/д�� 
 *       AdModeShareDenyRead                 ��ֹ�����û�ʹ�ö�Ȩ�޴����ӡ� 
 *       AdModeShareDenyWrite                ��ֹ�����û�ʹ��дȨ�޴����ӡ� 
 *       AdModeShareExclusive                ��ֹ�����û������ӡ� 
 *       AdModeShareDenyNone                 ��ֹ�����û�ʹ���κ�Ȩ�޴����ӡ� 
 *       =====================================================================================================
 * remark: ʹ��Mode���Կ����û򷵻ص�ǰ�������ṩ������ʹ�õķ���Ȩ�ޡ�Mode����ֻ���ڹر�Connection����ʱ�������á�
 *         ��Զ�����ݷ����÷��� �����ڿͻ���Connection����ʱ��Mode����ֻ������ΪadModeUnknown��
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
 * brief: ��ȡConnection�����ģʽ��Ҳ����Connection�������޸����ݵĿ���Ȩ�ޡ�
 * param: --
 * return: ����Connection�����ģʽ��Ҳ����Connection�������޸����ݵĿ���Ȩ�ޡ�
 * note: ���û򷵻�����ĳ��ConnectModeEnum ��ֵ��
 *       ����                                 ˵�� 
 *       =====================================================================================================
 *       AdModeUnknown                       Ĭ��ֵ������Ȩ����δ���û��޷�ȷ���� 
 *       AdModeRead                          ����Ȩ��Ϊֻ���� 
 *       AdModeWrite                         ����Ȩ��Ϊֻд�� 
 *       AdModeReadWrite                     ����Ȩ��Ϊ��/д�� 
 *       AdModeShareDenyRead                 ��ֹ�����û�ʹ�ö�Ȩ�޴����ӡ� 
 *       AdModeShareDenyWrite                ��ֹ�����û�ʹ��дȨ�޴����ӡ� 
 *       AdModeShareExclusive                ��ֹ�����û������ӡ� 
 *       AdModeShareDenyNone                 ��ֹ�����û�ʹ���κ�Ȩ�޴����ӡ� 
 *       =====================================================================================================
 * remark: ʹ��Mode���Կ����û򷵻ص�ǰ�������ṩ������ʹ�õķ���Ȩ�ޡ�Mode����ֻ���ڹر�Connection����ʱ�������á�
 *        ��Զ�����ݷ����÷��� �����ڿͻ���Connection����ʱ��Mode����ֻ������ΪadModeUnknown��
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
 * brief: ����Connection�����ṩ�ߵ����ơ�
 * param: provider - �ṩ�����ơ�
 * return: --
 * note: ���û򷵻��ַ���ֵ��
 * remark: ʹ��Provider���Կ����û򷵻������ṩ�ߵ����ơ�Ҳ����ͨ��ConnectionString���Ե����ݻ�Open
 *         ������ConnectionString�������ø����ԡ����ǣ�����Open����ʱ�ڶദָ���ṩ�߿��ܻ�����޷�Ԥ
 *         �ϵĺ�������û��ָ���ṩ�ߣ������Խ�Ĭ��Ϊ MSDASQL (Microsoft OLE DB Provider for ODBC ����
 *         �ر�����ʱProvider����Ϊ��/д��������ʱ������Ϊֻ������Connection��������Connection
 *         �����Properties���Ϻ�����ò���Ч�������������Ч������������
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
 * brief: ��ȡConnection�����ṩ�ߵ����ơ�
 * param: --
 * return: ����Connection�����ṩ�ߵ�����
 * note: ���û򷵻��ַ���ֵ��
 * remark: ʹ��Provider���Կ����û򷵻������ṩ�ߵ����ơ�Ҳ����ͨ��ConnectionString���Ե����ݻ�Open
 *         ������ConnectionString�������ø����ԡ����ǣ�����Open����ʱ�ڶദָ���ṩ�߿��ܻ�����޷�Ԥ
 *         �ϵĺ�������û��ָ���ṩ�ߣ������Խ�Ĭ��Ϊ MSDASQL (Microsoft OLE DB Provider for ODBC ����
 *         �ر�����ʱProvider����Ϊ��/д��������ʱ������Ϊֻ������Connection��������Connection
 *         �����Properties���Ϻ�����ò���Ч�������������Ч������������
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
 * brief: ��ȡ��ǰConnection�����״̬��
 * param: --
 * return: ���ص�ǰConnection�����״̬��
 * note: �������г���֮һ�ĳ�����ֵ��
 *       ����                                  ˵�� 
 *       ============================================================================================
 *       AdStateClosed                        Ĭ�ϣ�ָʾ�����ǹرյġ� 
 *       AdStateOpen                          ָʾ�����Ǵ򿪵ġ� 
 *       AdStateConnecting                    ָʾRecordset�����������ӡ� 
 *       AdStateExecuting                     ָʾRecordset��������ִ����� 
 *       AdStateFetching                      ָʾRecordset����������ڱ���ȡ�� 
 *       ============================================================================================
 * remark: ������ʱʹ��State����ȷ��ָ������ĵ�ǰ״̬����������ֻ���ġ�Recordset�����State���Կ��������ֵ��
 *         ���磬�������ִ����䣬�����Խ���adStateOpen��adStateExecuting�����ֵ��
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
 * brief: ��ȡADO�汾�š�
 * param: --
 * return: ����ADO�汾�š�
 * note: �����ַ���ֵ��
 * remark: ʹ��Version���Է���ADOִ�еİ汾�š�
 *         �ṩ�ߵİ汾��Ϊ��̬���Կɴ�Properties�����л�á�
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
 * brief: ��ȡConnection�����������Ϣ��
 * param: --
 * return: ����Connection�����������Ϣ��
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
 * brief: ��ȡConnection����Ĵ�����Ϣ��
 * param: --
 * return: ����Connection����Ĵ�����Ϣ��
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
 * brief: ��ʼ������
 * param: --
 * return: ����ָʾ����Ƕ�ײ�εĳ����ͱ�����
 * remark: ���ϣ���Զ�����Ԫ�����ȡ����Դ����������һϵ�и��ģ���ʹ����Щ����Connection����ķ�����
 *         �����ڻ���ת��ʱ��������ʻ��м�ȥĳ���������Ե�������ӵ���һ���ʻ����������е��ĸ���
 *         ��ʧ�ܣ����������ʻ���֧��ƽ�⡣�ڴ򿪵������н�����Щ���Ŀ�ȷ��ֻ��ѡ�����ȫ�����Ļ���
 *         �κθ��ġ�
 *         ע��: ���������ṩ�߶�֧����������֤�ṩ�߶�������ԡ�Transaction DDL���Ƿ������Connection
 *         �����Properties�����У���������ʾ�ṩ��֧����������ṩ�߲�֧�����񣬵������е�ĳ��
 *         ���������ش���һ��������BeginTrans�������ڵ���CommitTrans��RollbackTrans��������֮ǰ��
 *         �ṩ�߽����������ύ�������κθ��ġ�����֧��Ƕ��������ṩ����˵�������Ѵ������е�BeginTrans
 *         ��������ʼ�µ�Ƕ�����񡣷���ֵ��ָʾǶ�ײ�Σ�����ֵΪ 1 ��ʾ�Ѵ򿪶������񣨼����񲻱���һ��������Ƕ�ף���
 *         ����ֵΪ 2 ��ʾ�Ѵ򿪵ڶ�������Ƕ���ڶ��������е����񣩣��������ơ����� CommitTrans �� RollbackTrans 
 *         ֻӰ�����´򿪵������ڴ����κθ��߲�����֮ǰ����رջ�ؾ�ǰ���񡣵��� CommitTrans ����������������
 *         �򿪵������������ĸ��Ĳ��������񡣵��� RollbackTrans ������ԭ�������������ĸ��Ĳ�����������δ����
 *         ��ʱ���������κ�һ�ַ���������������ȡ���� Connection ����� Attributes ���ԣ����� CommitTrans �� 
 *         RollbackTrans �����������Զ�������������� Attributes ��������Ϊ adXactCommitRetaining���ṩ����
 *         CommitTrans ���ú���Զ�������������� Attributes ��������Ϊ adXactAbortRetaining���ṩ���ڵ��� 
 *         RollbackTrans ֮���Զ�����������
 *        ��Զ�����ݷ���BeginTrans��CommitTrans �� RollbackTrans �����ڿͻ��� Connection ��������Ч��
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
 * brief: �ύ����
 * param: --
 * return: --
 * remark: ���ϣ���Զ�����Ԫ�����ȡ����Դ����������һϵ�и��ģ���ʹ����Щ����Connection����ķ�����
 *         �����ڻ���ת��ʱ��������ʻ��м�ȥĳ���������Ե�������ӵ���һ���ʻ����������е��ĸ���
 *         ��ʧ�ܣ����������ʻ���֧��ƽ�⡣�ڴ򿪵������н�����Щ���Ŀ�ȷ��ֻ��ѡ�����ȫ�����Ļ���
 *         �κθ��ġ�
 *         ע��: ���������ṩ�߶�֧����������֤�ṩ�߶�������ԡ�Transaction DDL���Ƿ������Connection
 *         �����Properties�����У���������ʾ�ṩ��֧����������ṩ�߲�֧�����񣬵������е�ĳ��
 *         ���������ش���һ��������BeginTrans�������ڵ���CommitTrans��RollbackTrans��������֮ǰ��
 *         �ṩ�߽����������ύ�������κθ��ġ�����֧��Ƕ��������ṩ����˵�������Ѵ������е�BeginTrans
 *         ��������ʼ�µ�Ƕ�����񡣷���ֵ��ָʾǶ�ײ�Σ�����ֵΪ 1 ��ʾ�Ѵ򿪶������񣨼����񲻱���һ��������Ƕ�ף���
 *         ����ֵΪ 2 ��ʾ�Ѵ򿪵ڶ�������Ƕ���ڶ��������е����񣩣��������ơ����� CommitTrans �� RollbackTrans 
 *         ֻӰ�����´򿪵������ڴ����κθ��߲�����֮ǰ����رջ�ؾ�ǰ���񡣵��� CommitTrans ����������������
 *         �򿪵������������ĸ��Ĳ��������񡣵��� RollbackTrans ������ԭ�������������ĸ��Ĳ�����������δ����
 *         ��ʱ���������κ�һ�ַ���������������ȡ���� Connection ����� Attributes ���ԣ����� CommitTrans �� 
 *         RollbackTrans �����������Զ�������������� Attributes ��������Ϊ adXactCommitRetaining���ṩ����
 *         CommitTrans ���ú���Զ�������������� Attributes ��������Ϊ adXactAbortRetaining���ṩ���ڵ��� 
 *         RollbackTrans ֮���Զ�����������
 *        ��Զ�����ݷ���BeginTrans��CommitTrans �� RollbackTrans �����ڿͻ��� Connection ��������Ч��
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
 * brief: �ع�����
 * param: --
 * return: --
 * remark: ���ϣ���Զ�����Ԫ�����ȡ����Դ����������һϵ�и��ģ���ʹ����Щ����Connection����ķ�����
 *         �����ڻ���ת��ʱ��������ʻ��м�ȥĳ���������Ե�������ӵ���һ���ʻ����������е��ĸ���
 *         ��ʧ�ܣ����������ʻ���֧��ƽ�⡣�ڴ򿪵������н�����Щ���Ŀ�ȷ��ֻ��ѡ�����ȫ�����Ļ���
 *         �κθ��ġ�
 *         ע��: ���������ṩ�߶�֧����������֤�ṩ�߶�������ԡ�Transaction DDL���Ƿ������Connection
 *         �����Properties�����У���������ʾ�ṩ��֧����������ṩ�߲�֧�����񣬵������е�ĳ��
 *         ���������ش���һ��������BeginTrans�������ڵ���CommitTrans��RollbackTrans��������֮ǰ��
 *         �ṩ�߽����������ύ�������κθ��ġ�����֧��Ƕ��������ṩ����˵�������Ѵ������е�BeginTrans
 *         ��������ʼ�µ�Ƕ�����񡣷���ֵ��ָʾǶ�ײ�Σ�����ֵΪ 1 ��ʾ�Ѵ򿪶������񣨼����񲻱���һ��������Ƕ�ף���
 *         ����ֵΪ 2 ��ʾ�Ѵ򿪵ڶ�������Ƕ���ڶ��������е����񣩣��������ơ����� CommitTrans �� RollbackTrans 
 *         ֻӰ�����´򿪵������ڴ����κθ��߲�����֮ǰ����رջ�ؾ�ǰ���񡣵��� CommitTrans ����������������
 *         �򿪵������������ĸ��Ĳ��������񡣵��� RollbackTrans ������ԭ�������������ĸ��Ĳ�����������δ����
 *         ��ʱ���������κ�һ�ַ���������������ȡ���� Connection ����� Attributes ���ԣ����� CommitTrans �� 
 *         RollbackTrans �����������Զ�������������� Attributes ��������Ϊ adXactCommitRetaining���ṩ����
 *         CommitTrans ���ú���Զ�������������� Attributes ��������Ϊ adXactAbortRetaining���ṩ���ڵ��� 
 *         RollbackTrans ֮���Զ�����������
 *        ��Զ�����ݷ���BeginTrans��CommitTrans �� RollbackTrans �����ڿͻ��� Connection ��������Ч��
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
 * breif: ȡ��ִ�й�����첽Execute��Open�����ĵ��á�
 * param: --
 * return: --
 * remark: ʹ��Cancel������ִֹ���첽Execute��Open�������ã���ͨ��adAsyncConnect��
 *         adAsyncExecute��adAsyncFetchѡ����ø÷��������������ͼ��ֹ�ķ�����û��
 *         ʹ��adAsyncExecute����Cancel����������ʱ����
 *         �±���ʾ���ض����Ͷ�����ʹ��Cancel����ʱ����ֹ������
 *         �������Ϊ                        ����ֹ�Ը÷�������һ���첽���� 
 *         ==========================================================
 *         Command                         Execute 
 *         Connection                      Execute��Open 
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
 * brief: �رմ򿪵Ķ����κ���ض���
 * param: --
 * return: --
 * remark: ʹ��Close�����ɹر�Connection�����Recordset�����Ա��ͷ����й�����ϵͳ��Դ��
 *         �رն��󲢷ǽ������ڴ���ɾ�������Ը��������������ò����ڴ˺��ٴδ򿪡�Ҫ�������
 *         �ڴ�����ȫɾ�����ɽ������������ΪNothing��
 *         ʹ��Close�����ر�Connection�����ͬʱ��Ҳ���ر���������������κλRecordset����
 *         �����ڹرյ�Connection�����������Command���󽫱��־ñ�������������Connection���������
 *         ������ActiveConnection���Խ�������ΪNothing��ͬʱ��Command�����Parameters���Ͻ����
 *         �κ��ṩ�߶���Ĳ���������������Open�������½�������ͬ����Դ����������Դ�����ӣ��ر�Connection
 *         ����󣬵����κ���Ҫ���������Դ���ӵķ��������������󡣵��������д򿪵�Recordset����ʱ���ر�
 *         Connection���󽫻ؾ�����Recordset����Ĺ�����ġ���������й�������ʽ�ر�Connection���󣨵���
 *         Close���������������������������й�����Connection���󳬳���Χ����ôADO���Զ��ؾ�����
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
 * brief: ִ��ָ���Ĳ�ѯ��SQL ��䡢�洢���̻��ض��ṩ�ߵ��ı������ݡ�
 * param: command - �ַ���������Ҫִ�е� SQL ��䡢�������洢���̻��ض��ṩ�ߵ��ı���
 *        options - ��ѡ��������ֵ��ָʾ�ṩ��Ӧ��μ���command����,��Ϊ����ֵ��
 *        ����                    ˵�� 
 *        ===============================================================================================
 *        AdCmdText              ָʾ�ṩ��Ӧ��������ı�������� CommandText�� 
 *        AdCmdTable             ָʾ ADO Ӧ���� SQL ��ѯ�Ա�� CommandText �����ı��з��������С� 
 *        AdCmdTableDirect       ָʾ�ṩ��Ӧ�� CommandText �����ı��з��������С� 
 *        AdCmdTable             ָʾ�ṩ��Ӧ���������� CommandText�� 
 *        AdCmdStoredProc        ָʾ�ṩ��Ӧ���洢���̼��� CommandText�� 
 *        AdCmdUnknown           ָʾ CommandText �����е���������δ֪�� 
 *        adAsyncExecute         ָʾ����Ӧ���첽ִ�С� 
 *        adAsyncFetch           ָʾ���� CacheSize ����ָ���ĳ�ʼ����֮���ʣ����ʹ���첽��ȡ��
 *        ================================================================================================
 *        records_affected - ��ѡ�������ͱ������ṩ�����䷵�ز�����Ӱ��ļ�¼��Ŀ��
 * return: ���� Recordset �������á�
 * remark: ʹ�� Connection ����� Execute ��������ִ���κ���ָ�����ӵ� CommandText �����д��͸������Ĳ�ѯ��
 *         ��� CommandText ����ָ�����з��صĲ�ѯ��ִ�в������κν�����洢���µ� Recordset �����С��������
 *         ���ǰ��з��صĲ�ѯ�����ṩ�߷��عرյ� Recordset ���󡣷��ص� Recordset ����ʼ��Ϊֻ��������ǰ���αꡣ
 *         ����Ҫ���и��๦�ܵ� Recordset ����Ӧ���ȴ������������������õ� Recordset ����Ȼ��ʹ�� Recordset 
 *         ����� Open ����ִ�в�ѯ�����������α����͡�CommandText ���������ݶ��ṩ�����ض��ģ��������Ǳ�׼�� SQL 
 *         �﷨���ṩ��֧�ֵ��κ����������ʽ���ò�����ɺ󽫲��� ExecuteComplete �¼���
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
 * brief: �򿪵�����Դ�����ӡ�
 * param: connection_string - ��ѡ���ַ���������������Ϣ������ ConnectionString ���Կɻ����Ч���õ���ϸ��Ϣ��
 *        user_id - ��ѡ���ַ�����������������ʱ��ʹ���û�����
 *        password - ��ѡ���ַ�����������������ʱ��ʹ�����롣
 *        options - ��ѡ��ConnectOptionEnum ֵ�������÷����������ӽ���֮���첽���������ӽ���֮ǰ��ͬ�������ء�
 *                  ����������ĳ��������
 *        ����                            ˵�� 
 *        ==========================================================================================
 *        adConnectUnspecified          ��Ĭ�ϣ�ͬ�������ӡ� 
 *        adAsyncConnect                �첽�����ӡ�ConnectComplete �¼��������ھ������Ӻ�ʱ���á�
 *        ==========================================================================================
 * return: --
 * remark: ʹ�� Connection ����� Open �����ɽ���������Դ���������ӡ��ڸ÷����ɹ���ɺ������ǻ�Ծ�ģ����Զ�����������Ҵ�������
 *         ʹ�ÿ�ѡ�� ConnectionString ����ָ�������ַ������������ɷֺŷָ���һϵ�� argument = value ��䡣ConnectionString 
 *         �����Զ��̳����� ConnectionString ������ֵ����˿��ڴ�֮ǰ���� Connection ����� ConnectionString ���ԣ����� Open 
 *         ��������ʱʹ�� ConnectionString �������û򸲸ǵ�ǰ���Ӳ���������� ConnectionString �����Ϳ�ѡ�� UserID �� Password 
 *         �����д����û���������Ϣ����ô UserID �� Password ���������� ConnectionString ��ָ����ֵ���ڶԴ򿪵� Connection �Ĳ���
 *         �����󣬿�ʹ�� Close �����ͷ����й�����ϵͳ��Դ���رն��󲢷ǽ������ڴ���ɾ�������Ը��������������ò����Ժ��ٴ�ʹ�� Open ����
 *         ������Ҫ��������ȫ���ڴ���ɾ�����ɽ������������Ϊ Nothing��
 *        ��Զ�����ݷ��� ���ڿͻ��˵� Connection ������ʹ�� Open ����ʱ���� Connection �����ϴ� Recordset ֮ǰ Open ������ʵ��
 *         δ�����������������ӡ�
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
 * brief: ���ṩ�߻�ȡ���ݿ�ģʽ��Ϣ��
 * param: schema - ��Ҫ���е�ģʽ��ѯ���ͣ�����Ϊ�������ⳣ����
 *        criteria - ��ѡ��ÿ�� QueryType ѡ��Ĳ�ѯ�����������飬�������У�
 *        schemaֵ                                 criteriaֵ 
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
 *        adSchemaProviderSpecific                 �μ�˵�� 
 *        adSchemaProviderTypes                    DATA_TYPE
 *                                                 BEST_MATCH 
 *        adSchemaReferentialConstraints           CONSTRAINT_CATALOG
 *                                                 CONSTRAINT_SCHEMA
 *                                                 CONSTRAINT_NAME 
 *        adSchemaSchemata                         CATALOG_NAME
 *                                                 SCHEMA_NAME
 *                                                 SCHEMA_OWNER 
 *        adSchemaSQLLanguages                     <��> 
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
 *        schema_id -  OLE DB �淶û�ж��������ṩ��ģʽ��ѯ�� GUID����� QueryType ����Ϊ adSchemaProviderSpecific��
 *                     ����Ҫ�ò���������ʹ������
 * return: ���ذ���ģʽ��Ϣ�� Recordset ����Recordset ����ֻ������̬�α�򿪡�
 * remark: open_schema ��������������Դ�йص���Ϣ��������ڷ������ϵı��Լ����е��е���Ϣ��
 *         criteria �����ǿ���������ģʽ��ѯ�����ֵ���顣ÿ��ģʽ��ѯ����֧�ֵĲ�ͬ��������ʵ��ģʽ�� IDBSchemaRowset �ӿ��µ� 
 *         OLE DB �淶���塣ADO ����֧�ֵĲ��������������г�������ṩ�߶���δ�������г��ķǱ�׼ģʽ��ѯ������ adSchemaProviderSpecific 
 *         ������ schema ��������ʹ�øó���ʱ��Ҫ schema_id ��������ģʽ��ѯ�� GUID ������ִ�С���� schema ����Ϊ 
 *         adSchemaProviderSpecific ����û���ṩ schema_id�������´����ṩ�߲���Ҫ֧�����е� OLE DB ��׼ģʽ��ѯ��ֻ�� 
 *         adSchemaTables��adSchemaColumns �� adSchemaProviderTypes �� OLE DB �淶��Ҫ�ġ����Ƕ�����Щģʽ��ѯ���ṩ�߲���Ҫ֧������
 *         �г��� criteria ����Լ����
 *        ��Զ�����ݷ���   OpenSchema �����ڿͻ��� Connection ��������Ч��
 *         ע��: �� Visual Basic �У����� Connection ����� open_schema ���������ص� Recordset ���� 4 �ֽ��޷������� (DBTYPE UI4) 
 *         �����޷������������Ƚϡ��й� OLE DB �������͵���ϸ��Ϣ������ġ�Microsoft OLE DB ����Ա�ο����ĵ�ʮ�º͸�¼ A��
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
 * brief: �ж� Connection �����Ƿ��ڴ�״̬��
 * param:
 * return: ��� Connection �����ڴ�״̬�򷵻�һ�����򷵻��㡣���
 *         �жϹ����г��ִ����򷵻ظ�����Ϊ������롣
 */
int MtADOConnection::is_open() const{
	//1.�����ǰ Connection ������δ��������ֱ�ӷ����㡣
	if(0==_connection){
		return(0);
	}
	//2.��ȡ Connection ����״̬�������жϻ�ȡ�Ƿ�ɹ���
	const long state=get_state();
	if(0!=get_last_error_code()){
		return(-1);
	}
	//3.�����ǰ Connection �����ڹر�״̬����ֱ�ӷ����㡣
	if(ADODB::adStateClosed==state){
		return(0);
	}
	//4.�����ǰ Connection �����ڴ�״̬����ֱ�ӷ���һ��
	return(1);
}

/**
 * name: get_last_error_code
 * brief: ��ȡ����Ĵ�����롣
 * param: --
 * return: ��������Ĵ�����롣
 */
long MtADOConnection::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: ��ȡ����Ĵ���������
 * param: --
 * return: ��������Ĵ���������
 */
CString MtADOConnection::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: get_connection
 * brief: ��ȡ��ǰ ADO ����ʵ������ Connection ���󣩡�
 * param: --
 * return: ���ص�ǰ ADO ����ʵ������ Connection ���󣩡�
 */
ADODB::_ConnectionPtr MtADOConnection::get_connection() const{
	return(_connection);
}

/**
 * name: create_instance
 * brief: ����ʵ����
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
 * brief: �ͷ�ʵ����
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
 * brief: ������������Ϣ��
 * param: --
 * return: --
 */
void MtADOConnection::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: ��¼���������Ϣ��
 * param: error - ���������Ϣ��
 * return: --
 */
void MtADOConnection::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}