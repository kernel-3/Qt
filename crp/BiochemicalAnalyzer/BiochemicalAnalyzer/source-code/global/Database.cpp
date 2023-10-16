#include"stdafx.h"
#include"Database.h"
#include"../../../../include/mfctoolkit/database/MtADOConnection.h"
#include"../../../../include/mfctoolkit/database/MtADORecordset.h"
#include<assert.h>

/**
 * name: ~Database
 * brief: ����������
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
 * brief: ���ӵ����ݿ⡣
 * param: connection_timeout - ���ӳ�ʱʱ�䣨��λ���룩��
 *        command_timeout - ָ�ʱʱ�䣨��λ���룩��
 *        connection_string - ���ݿ������ַ�����
 *        user - �û���
 *        password - ���롣
 *        options - ���������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Database::connect(const long connection_timeout,const long command_timeout,
	const CString &connection_string,const CString &user/*=_T("")*/,const CString &password/*=_T("")*/,
	const long options/*=-1*/){
	//1.�����µ����ݿ�����ʵ���������жϴ����Ƿ�ɹ���
	PtrToConnection connection(new MtADOConnection);
	if(!static_cast<bool>(connection)){
		return(-1);
	}
	//2.�������ӳ�ʱʱ�䡣
	connection->set_connection_timeout(connection_timeout);
	if(0!=connection->get_last_error_code()){
		return(-2);
	}
	//3.����ָ��ִ�г�ʱʱ�䡣
	connection->set_command_timeout(command_timeout);
	if(0!=connection->get_last_error_code()){
		return(-3);
	}
	//4.�������ݿ����ӣ������ж������Ƿ�ɹ���
	connection->open(connection_string,user,password,options);
	if(0!=connection->get_last_error_code()){
		return(-4);
	}
	//5.���浱ǰ����ʵ���Լ����Ӳ�����
	_connection_timeout=connection_timeout;
	_command_timeout=command_timeout;
	_connection_string=connection_string;
	_user=user;
	_password=password;
	_options=options;
	_connection=connection;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: disconnect
 * brief: �Ͽ���ǰ�����ݿ�����ӡ�
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
 * brief: ��ȡ��¼����
 * param: command - �����ı���SQL��䣩��
 *        cursor_location - �α�λ�ã�1 δ֪ 2 ������ 3 �ͻ��ˣ�
 *        cursor_type - �α�����( -1 δ�����α����� 0 ����ǰ�����α� 1 ���������α� 2 ��̬�����α� 3 ��̬�����α�)��
 *        lock_type - �����ͣ� -1 δ���������� 1 ֻ�� 2 ����ʽ���� 3 ����ʽ���� 4 ����ʽ�����£�
 *        options - ���ӷ�ʽ��-1 δ���� 8 δ֪ 1 �ı� 2 �� 4 �洢���� 256 �ļ� 512 �������� 16 �첽ִ�� 32 ��ȡ 64 ��ȡ��������
 * return: �������ִ�гɹ����ؼ�¼������ָ�룬���򷵻ؿյ�����ָ�롣
 */
Database::PtrToRecordset Database::get_recordset(const CString &command,const long cursor_location/*=3*/,
	const long cursor_type/*=3*/,const long lock_type/*=1*/,const long options/*=1*/){
	//1.�����ǰ Connection ������δ�򿪡�
	if(_connection->is_open()<=0){
		return(PtrToRecordset());
	}
	//2.������¼������ָ�룬�����жϴ����Ƿ�ɹ���
	PtrToRecordset recordset(new MtADORecordset);
	if(!static_cast<bool>(recordset)){
		return(PtrToRecordset());
	}
	//3.���ü�¼���α�λ�á�
	recordset->set_cursor_location(static_cast<ADODB::CursorLocationEnum>(cursor_location));
	if(0!=recordset->get_last_error_code()){
		return(PtrToRecordset());
	}
	//4.�򿪼�¼���������жϴ��Ƿ�ɹ���
	if(FAILED(recordset->open(static_cast<_variant_t>(static_cast<LPCTSTR>(command)),
		_variant_t(static_cast<IDispatch*>(_connection->get_connection()),true),
		static_cast<ADODB::CursorTypeEnum>(cursor_type),static_cast<ADODB::LockTypeEnum>(lock_type),
		options))){
		return(PtrToRecordset());
	}
	//5.�����¼���򿪳ɹ����򷵻ؼ�¼����
	return(recordset);
}

/**
 * name: execute
 * breif: �����ݿ�ִ��һ���������ص�SQL��䣨����: ���롢ɾ�������µȵȣ���
 * param: sql - SQL��䡣
 * return: �������ִ�гɹ�������ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Database::execute(const CString &sql){
	//1.�����ǰSQL���Ϊ�գ���ֱ�ӷ��ش���
	if(_T("")==sql){
		return(-1);
	}
	//2.�����ǰ Connection ������δ�򿪡�
	if(_connection->is_open()<=0){
		return(-2);
	}
	//3.ִ�е�ǰSQL��䣬�����ж�ִ���Ƿ�ɹ���
	_connection->execute(sql);
	if(0!=_connection->get_last_error_code()){
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: begin_trans
 * breif: Ϊ���ݿ⿪��һ������
 * param: --
 * return: �����������ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ���������Ƕ�ף��������ʹ��Ƕ������������ϸ�Ķ�
 *         ��ADO�����ֲᡷ������½ڡ�
 */
int Database::begin_trans(){
	//1.�����ǰ Connection ������δ�򿪡�
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.Ϊ���ݿ⿪��һ������
	_connection->begin_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit_trans
 * breif: Ϊ���ݿ��ύһ������
 * param: --
 * return: ����ύ����ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ���������Ƕ�ף��������ʹ��Ƕ������������ϸ�Ķ�
 *         ��ADO�����ֲᡷ������½ڡ�
 */
int Database::commit_trans(){
	//1.�����ǰ Connection ������δ�򿪡�
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.Ϊ���ݿ��ύһ������
	_connection->commit_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: rollback_trans
 * breif: Ϊ���ݿ�ع�һ������
 * param: --
 * return: ����ع�����ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ���������Ƕ�ף��������ʹ��Ƕ������������ϸ�Ķ�
 *         ��ADO�����ֲᡷ������½ڡ�
 */
int Database::rollback_trans(){
	//1.�����ǰ Connection ������δ�򿪡�
	if(_connection->is_open()<=0){
		return(-1);
	}
	//2.Ϊ���ݿ�ع�һ������
	_connection->rollback_trans();
	if(0!=_connection->get_last_error_code()){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clone
 * brief: ���ݵ�ǰ���ݿ���ʵ������¡����һ���µ����ݿ�ʵ����
 * param: --
 * return: �����ǰ���������ɹ������µ����ݿ�ʵ������ָ�룬���򷵻ؿ�ָ�롣
 */
Database::PtrToDatabase Database::clone() const{
	return(PtrToDatabase(new Database(*this)));
}

/**
 * name: is_connected
 * brief: �жϵ�ǰ���ݿ��Ƿ�������״̬��
 * param: --
 * return: �����ǰ���ݿ⴦������״̬�򷵻�TRUE�����򷵻�FALSE��
 */
BOOL Database::is_connected() const{
	return(0!=_connection.get());
}

/**
 * name: Database
 * brief: ���캯����
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
 * brief: �������캯����
 * param: database - ����Դ���ݿ⡣
 * return: --
 * note: ����ͨ������is_connected�������жϿ������캯���Ƿ�ɹ���
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
 * brief: ���ӵ����ݿ⡣
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Database::connect(){
	//1.�����µ����ݿ�����ʵ���������жϴ����Ƿ�ɹ���
	PtrToConnection connection(new MtADOConnection);
	if(!static_cast<bool>(connection)){
		return(-1);
	}
	//2.�������ӳ�ʱʱ�䡣
	connection->set_connection_timeout(_connection_timeout);
	if(0!=connection->get_last_error_code()){
		return(-2);
	}
	//3.����ָ��ִ�г�ʱʱ�䡣
	connection->set_command_timeout(_command_timeout);
	if(0!=connection->get_last_error_code()){
		return(-3);
	}
	//4.�������ݿ����ӣ������ж������Ƿ�ɹ���
	connection->open(_connection_string,_user,_password,_options);
	if(0!=connection->get_last_error_code()){
		return(-4);
	}
	//5.���浱ǰ����ʵ����
	_connection=connection;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: operator=
 * brief: ���ݿ��ำֵ�������ء�
 * param: database - ����Դ���ݿ⡣
 * return: ���ص�ǰ���ݿ���ʵ�����á�
 * remark: ����ͨ������is_connected�������жϸ�ֵ�����Ƿ�ɹ���
 */
Database &Database::operator=(const Database &database){
	//1.Ϊ��ǰ���ݿ��������ݸ�ֵ��
	_connection_timeout=database._connection_timeout;
	_command_timeout=database._command_timeout;
	_connection_string=database._connection_string;
	_user=database._user;
	_password=database._password;
	_options=database._options;
	//2.���õ�ǰ���ݿ�����������ݿ�,�����ж������Ƿ�ɹ���
	if(connect()<0){
		disconnect();
	}
	//3.���ص�ǰ���ݿ�ʵ�����á�
	return(*this);
}