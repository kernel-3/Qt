#pragma once

#include"HL7ORUR01Message.h"

/**
 * name: HL7ORUR01MessageForCalib
 * breif: 描述HL7协议中的“ORU^R01”消息（传递定标结果的“ORU^R01”
 *        消息），主要负责根据字符串生成HL7ORUR01MessageForCalib
 *        类中数据，以及根据HL7ORUR01MessageForCalib类中数据生成
 *        HL7协议格式的字符串。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7ORUR01MessageForCalib
	:public HL7ORUR01Message{
//construction & destruction
public:
	HL7ORUR01MessageForCalib(void);
	virtual ~HL7ORUR01MessageForCalib(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};