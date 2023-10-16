#pragma once

#include"HL7Segment.h"

/**
 * name: HL7DSCSegment
 * breif: ����HL7Э���еġ�MSH���Σ���Ҫ��������ַ�������
 *        HL7DSCSegment�������ݣ��Լ�����HL7DSCSegment
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7DSCSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7DSCSegment(void);
	virtual ~HL7DSCSegment(void);
//interface
public:
	void set_continuation_pointer(const String &continuation_pointer);
	const String &get_continuation_pointer() const;
	void set_continuation_pointer_with_number(const unsigned int continuation_pointer);
	unsigned int get_continuation_pointer_with_number() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _continuation_pointer;
};