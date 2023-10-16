#pragma once

#include"HL7Segment.h"

/**
 * name: HL7MSASegment
 * brief: ����HL7Э���еġ�MSA���Σ���Ҫ��������ַ�������
 *        HL7MSASegment�������ݣ��Լ�����HL7MSASegment
 *        ������������HL7Э���ʽ���ַ�����
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
	String _acknowledgment_code;//����
	String _message_control_id;//����
	String _text_message;
	String _error_condition;//����
};