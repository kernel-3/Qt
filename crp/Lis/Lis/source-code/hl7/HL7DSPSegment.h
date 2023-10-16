#pragma once

#include"HL7Segment.h"

/**
 * name: HL7DSPSegment
 * breif: 描述HL7协议中的“MSH”段，主要负责根据字符串生成
 *        HL7DSPSegment类中数据，以及根据HL7DSPSegment
 *        类中数据生成HL7协议格式的字符串。
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