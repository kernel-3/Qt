#pragma once

#include"HL7Segment.h"

/**
 * name: HL7QAKSegment
 * brief: 描述HL7协议中的“PID”段，主要负责根据字符串生成
 *        HL7QAKSegment类中数据，以及根据HL7QAKSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7QAKSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7QAKSegment(void);
	virtual ~HL7QAKSegment(void);
//interface
public:
	const String &get_query_tag() const;
	void set_query_response_status(const String &query_response_status);
	const String &get_query_response_status() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	/*const*/ String _query_tag;
	String _query_response_status;
};