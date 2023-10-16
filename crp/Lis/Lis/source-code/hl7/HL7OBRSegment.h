#pragma once

#include"HL7Segment.h"

/**
 * name: HL7OBRSegment
 * brief: 描述HL7协议中的“OBR”段，主要负责根据字符串生成
 *        HL7OBRSegment类中数据，以及根据HL7OBRSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 * remark: 此类是所有“OBR”段变种的基类（抽象类，不能实例化）。
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