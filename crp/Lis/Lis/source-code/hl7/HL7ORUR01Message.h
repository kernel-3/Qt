#pragma once

#include"HL7Message.h"

/**
 * name: HL7ORUR01Message
 * breif: 描述HL7协议中的“ORU^R01”消息，主要负责根据字符串生成
 *        HL7ORUR01Message类中数据，以及根据HL7ORUR01Message
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2014-12-19
 * remark: 此类是所有“ORU^R01”变种消息的基类，它是抽象类，不能实例化。
 */
class HL7ORUR01Message
	:public HL7Message{
//construction & destruction
public:
	HL7ORUR01Message(void);
	virtual ~HL7ORUR01Message(void);
};