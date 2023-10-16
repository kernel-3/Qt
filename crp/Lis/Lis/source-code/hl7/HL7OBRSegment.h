#pragma once

#include"HL7Segment.h"

/**
 * name: HL7OBRSegment
 * brief: ����HL7Э���еġ�OBR���Σ���Ҫ��������ַ�������
 *        HL7OBRSegment�������ݣ��Լ�����HL7OBRSegment
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2015-01-06
 * remark: ���������С�OBR���α��ֵĻ��ࣨ�����࣬����ʵ��������
 */
class HL7OBRSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7OBRSegment(void);
	virtual ~HL7OBRSegment(void);
//interface
public:
	const String &get_segment_id() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content)=0;
	virtual int get_field(const unsigned int no,String &content) const=0;
//variables
private:
	/*const*/ String _segment_id;
};