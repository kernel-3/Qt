#pragma once

#include"HL7Segment.h"

/**
 * name: HL7ERRSegment
 * breif: 描述HL7协议中的“MSH”段，主要负责根据字符串生成
 *        HL7ERRSegment类中数据，以及根据HL7ERRSegment
 *        类中数据生成HL7协议格式的字符串。
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