#pragma once

#include"HL7Message.h"

/**
 * name: HL7QRYQ02Message
 * breif: 描述HL7协议中的“QRY^Q01”消息，主要负责根据字符串生成
 *        HL7QRYQ02Message类中数据，以及根据HL7QRYQ02Message
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7QRYQ02Message
	:public HL7Message{
//construction & destruction
public:
	HL7QRYQ02Message(void);
	virtual ~HL7QRYQ02Message(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};