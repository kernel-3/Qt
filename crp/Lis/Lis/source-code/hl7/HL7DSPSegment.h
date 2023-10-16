#pragma once

#include"HL7Segment.h"

/**
 * name: HL7DSPSegment
 * breif: ����HL7Э���еġ�MSH���Σ���Ҫ��������ַ�������
 *        HL7DSPSegment�������ݣ��Լ�����HL7DSPSegment
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7DSPSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7DSPSegment(void);
	virtual ~HL7DSPSegment(void);
//interface
public:
	void set_segment_id(const String &segment_id);
	const String &get_segment_id() const;
	void set_segment_id_with_number(const unsigned int segment_id);
	const unsigned int get_segment_id_with_number() const;
	void set_data_content(const String &data_content);
	const String &get_data_content() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _segment_id;
	String _data_content;
};