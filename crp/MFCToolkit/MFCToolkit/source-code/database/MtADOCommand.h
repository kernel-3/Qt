#pragma once

#include"../Symbol"
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" \
	named_guids rename("EOF","adoEOF"),rename("BOF","adoBOF")

/**
 * name: MtADOCommand
 * brief: 对ADO中Command对象的封装，提供所有Command对象的方法实现。
 * author: yameng_he
 * date: 2014-09-02
 */
class MFC_TOOLKIT_API MtADOCommand{
//constructor & destructor
public:
	MtADOCommand(void);
	~MtADOCommand(void);
//property
public:
	void set_active_connection(const _variant_t &connection);
	ADODB::_ConnectionPtr get_active_connection() const;
	void set_command_text(const CString &command_text);
	CString get_command_text() const;
	void set_command_timeout(const long timeout);
	long get_command_timeout() const;
	void set_command_type(const ADODB::CommandTypeEnum type);
	ADODB::CommandTypeEnum get_command_type() const;
	void set_name(const CString &name);
	CString get_name() const;
	void set_prepared(const BOOL yes_or_no);
	BOOL get_prepared() const;
	long get_state() const;
	ADODB::ParametersPtr get_parameters() const;
	ADODB::PropertiesPtr get_properties() const;
//methods
public:
	HRESULT cancel();
	ADODB::_ParameterPtr create_parameter(const CString &name,
		const ADODB::DataTypeEnum data_type,const ADODB::ParameterDirectionEnum diretion,
		const long size,const _variant_t &value=vtMissing);
	ADODB::_RecordsetPtr execute(VARIANT *affect_records,VARIANT *parameters,const long options);
//interface
public:
	long get_last_error_code() const;
	CString get_last_error_message() const;
//implement
private:
	void create_instance();
	void release_instance();
	void clear_last_error() const;
	void record_last_error(const _com_error &error) const;
//restrict
private:
	MtADOCommand(const MtADOCommand &);
	MtADOCommand &operator=(const MtADOCommand &);
//variables
private:
	mutable long _last_error_code;
	mutable CString _last_error_message;
	ADODB::_CommandPtr _command;
};