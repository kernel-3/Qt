#pragma once

#include"HL7Segment.h"

/**
 * name: HL7DSCSegment
 * breif: 描述HL7协议中的“MSH”段，主要负责根据字符串生成
 *        HL7DSCSegment类中数据，以及根据HL7DSCSegment
 *        类中数据生成HL7协议格式的字符串。
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