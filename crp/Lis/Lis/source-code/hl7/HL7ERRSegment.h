#pragma once

#include"HL7Segment.h"

/**
 * name: HL7ERRSegment
 * breif: ����HL7Э���еġ�MSH���Σ���Ҫ��������ַ�������
 *        HL7ERRSegment�������ݣ��Լ�����HL7ERRSegment
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7ERRSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7ERRSegment(void);
	virtual ~HL7ERRSegment(void);
//interface
public:
	void set_error_code_and_location(
		const String &error_code_and_location);
	const String &get_error_code_and_location() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _error_code_and_location;
};