#pragma once

#include"../Symbol"
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" \
	named_guids rename("EOF","adoEOF"),rename("BOF","adoBOF")

/**
 * name: MtADORecordset
 * brief: 对ADO中Recordset对象的封装，提供所有Recordset对象的方法实现。
 * author: yameng_he
 * date: 2014-08-20
 */
class MFC_TOOLKIT_API MtADORecordset{
//constructor & destructor
public:
	MtADORecordset(void);
	~MtADORecordset(void);
//property
public:
	void set_absolute_page(const ADODB::PositionEnum page);
	ADODB::PositionEnum get_absolute_page() const;
	void set_absolute_position(const ADODB::PositionEnum position);
	ADODB::PositionEnum get_absolute_position() const;
	ADODB::_CommandPtr get_active_command() const;
	void set_active_connection(ADODB::_ConnectionPtr connection);
	ADODB::_ConnectionPtr get_active_connection() const;
	BOOL get_bof() const;
	BOOL get_eof() const;
	void set_bookmark(const _variant_t &bookmark);
	_variant_t get_bookmark() const;
	void set_catch_size(const long size);
	long get_catch_size() const;
	void set_cursor_location(const ADODB::CursorLocationEnum location);
	ADODB::CursorLocationEnum get_cursor_location() const;
	void set_cursor_type(const ADODB::CursorTypeEnum type);
	ADODB::CursorTypeEnum get_cursor_type() const;
	void set_data_member(const CString &member);
	CString get_data_member() const;
	IUnknownPtr get_data_source() const;//含义未知？
	ADODB::EditModeEnum get_edit_mode() const;
	void set_filter(const _variant_t &filter);
	_variant_t get_filter() const;
	void set_lock_type(const ADODB::LockTypeEnum type);
	ADODB::LockTypeEnum get_lock_type() const;
	void set_marshal_options(const ADODB::MarshalOptionsEnum options);
	ADODB::MarshalOptionsEnum get_marshal_options() const;
	void set_max_records(const long records);
	long get_max_records() const;
	long get_page_count() const;
	void set_page_size(const long size);
	long get_page_size() const;
	long get_record_count() const;
	void set_sort(const CString &sort);
	CString get_sort() const;
	void set_source(const CString &source);
	_variant_t get_source() const;
	long get_state() const;
	long get_status() const;
	void set_stay_in_sync(const BOOL is_stay_in_sync);
	BOOL get_stay_in_sync() const;
	ADODB::FieldsPtr get_fileds() const;
	ADODB::PropertiesPtr get_properties() const;
//methods
public:
	HRESULT add_new(const _variant_t &field_list=vtMissing,const _variant_t &values=vtMissing);
	HRESULT cancel();
	HRESULT cancel_bantch(const ADODB::AffectEnum affect_records=ADODB::adAffectAll);
	HRESULT cancel_update();
	ADODB::_RecordsetPtr clone(const ADODB::LockTypeEnum type);
	HRESULT close();
	ADODB::CompareEnum compare_bookmarks(const _variant_t &bookmark_left,const _variant_t &bookmark_right);
	HRESULT deletes(const ADODB::AffectEnum affect_records=ADODB::adAffectCurrent);
	HRESULT find(const CString &criteria,const long skip_rows,
		const ADODB::SearchDirectionEnum search_direction,const _variant_t &start=vtMissing);
	_variant_t get_rows(const long rows,const _variant_t start=vtMissing,const _variant_t &fields=vtMissing);
	HRESULT move(const long records,const ADODB::BookmarkEnum start=ADODB::adBookmarkCurrent);
	HRESULT move_first();
	HRESULT move_last();
	HRESULT move_next();
	HRESULT move_previous();
	ADODB::_RecordsetPtr next_record(VARIANT *affect_records);
	HRESULT open(const _variant_t &source,const _variant_t &active_connection,
		const ADODB::CursorTypeEnum cursor_type,ADODB::LockTypeEnum lock_type,const long options);
	HRESULT requery(const long options);
	HRESULT resync(const ADODB::AffectEnum affect_records,const ADODB::ResyncEnum resync_values);
	HRESULT save(const CString &file_name,const ADODB::PersistFormatEnum persist_format);
	BOOL supports(const ADODB::CursorOptionEnum options);
	HRESULT update(const _variant_t &fields=vtMissing,const _variant_t &values=vtMissing);
	HRESULT update_batch(const ADODB::AffectEnum affect_records);
	void put_collect(const _variant_t &index,const _variant_t &value);
	_variant_t get_collect(const _variant_t &index);
	BOOL is_null_value_in_collect(const _variant_t &index);
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
	MtADORecordset(const MtADORecordset &);
	MtADORecordset &operator=(const MtADORecordset &);
//variables
private:
	mutable long _last_error_code;
	mutable CString _last_error_message;
	ADODB::_RecordsetPtr _recordset;
};