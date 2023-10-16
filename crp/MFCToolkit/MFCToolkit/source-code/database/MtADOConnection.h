#pragma once

#include"../Symbol"
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" \
	named_guids rename("EOF","adoEOF"),rename("BOF","adoBOF")

/**
 * name: MtADOConnection
 * brief: 对ADO中connection对象的封装，提供所有connection对象的方法实现。
 * author: yameng_he
 * date: 2014-08-19
 */
class MFC_TOOLKIT_API MtADOConnection{
//constructor & destructor
public:
	MtADOConnection(void);
	~MtADOConnection(void);
//property
public:
	void set_attribute(const long attribute);
	long get_attribute() const;
	void set_command_timeout(const long timeout);
	long get_command_timeout() const;
	void set_connection_string(const CString &string);
	CString get_connection_string() const;
	void set_connection_timeout(const long timeout);
	long get_connection_timeout() const;
	void set_cursor_location(const ADODB::CursorLocationEnum location);
	ADODB::CursorLocationEnum get_cursor_location() const;
	void set_default_database(const CString &database);
	CString get_default_database() const;
	void set_isolation_level(const ADODB::IsolationLevelEnum level);
	ADODB::IsolationLevelEnum get_isolation_level() const;
	void set_mode(const ADODB::ConnectModeEnum mode);
	ADODB::ConnectModeEnum get_mode() const;
	void set_provider(const CString &provider);
	CString get_provider() const;
	long get_state() const;
	CString get_version() const;
	ADODB::PropertiesPtr get_properties() const;
	ADODB::ErrorsPtr get_errors() const;
//method
public:
	long begin_trans();
	void commit_trans();
	void rollback_trans();
	void cancel();
	void close();
	ADODB::_RecordsetPtr execute(const CString &command,
		const long options=ADODB::adCmdText,long *records_affected=0);
	void open(const CString &connection_string,const CString &user_id,
		const CString &password,const long options);
	ADODB::_RecordsetPtr open_schema(const ADODB::SchemaEnum schema);
//interface
public:
	int is_open() const;
	long get_last_error_code() const;
	CString get_last_error_message() const;
	ADODB::_ConnectionPtr get_connection() const;
//implement
private:
	void create_instance();
	void release_instance();
	void clear_last_error() const;
	void record_last_error(const _com_error &error) const;
//restrict
private:
	MtADOConnection(const MtADOConnection &);
	MtADOConnection &operator=(const MtADOConnection &);
//variables
private:
	mutable long _last_error_code;
	mutable CString _last_error_message;
	ADODB::_ConnectionPtr _connection;
};