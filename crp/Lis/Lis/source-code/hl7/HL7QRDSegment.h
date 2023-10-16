#pragma once

#include"HL7Segment.h"

/**
 * name: HL7QRDSegment
 * brief: 描述HL7协议中的“QRD”段，主要负责根据字符串生成
 *        HL7QRDSegment类中数据，以及根据HL7QRDSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7QRDSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7QRDSegment(void);
	virtual ~HL7QRDSegment(void);
//interface
public:
	void set_query_date_time(const String &query_date_time);
	const String &get_query_date_time() const;
	const String &get_query_format_code() const;
	const String &get_query_priority() const;
	void set_query_id(const String &query_id);
	const String &get_query_id() const;
	const String &get_quantity_limited_request() const;
	void set_specimen_barcode(const String &specimen_barcode);
	const String &get_specimen_barcode() const;
	const String &get_what_subject_filter() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _query_date_time;
	/*const*/ String _query_format_code;
	/*const*/ String _query_priority;
	String _query_id;
	/*const*/ String _quantity_limited_request;
	String _specimen_barcode;
	/*const*/ String _what_subject_filter;
};