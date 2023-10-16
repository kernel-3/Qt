#pragma once

#include"HL7Message.h"

/**
 * name: HL7DSRQ03Message
 * breif: 描述HL7协议中的“DSR^Q03”消息，主要负责根据字符串生成
 *        HL7DSRQ03Message类中数据，以及根据HL7DSRQ03Message
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7DSRQ03Message
	:public HL7Message{
//construction & destruction
public:
	HL7DSRQ03Message(void);
	virtual ~HL7DSRQ03Message(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};