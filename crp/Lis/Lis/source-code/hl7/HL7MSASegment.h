#pragma once

#include"HL7Segment.h"

/**
 * name: HL7MSASegment
 * brief: 描述HL7协议中的“MSA”段，主要负责根据字符串生成
 *        HL7MSASegment类中数据，以及根据HL7MSASegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7MSASegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//constructor & destructor
public:
	HL7MSASegment(void);
	virtual ~HL7MSASegment(void);
//interface
public:
	void set_acknowledgment_code(const String &acknowledgment_code);
	const String &get_acknowledgment_code() const;
	void set_message_control_id(const String &message_control_id);
	const String &get_message_control_id() const;
	void set_text_message(const String &text_message);
	const String &get_text_message() const;
	void set_error_condition(const String &error_condition);
	const String &get_error_condition() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _acknowledgment_code;//必须
	String _message_control_id;//必须
	String _text_message;
	String _error_condition;//必须
};