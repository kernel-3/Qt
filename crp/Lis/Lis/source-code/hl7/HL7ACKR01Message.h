#pragma once

#include"HL7Message.h"

/**
 * name: HL7ACKR01Message
 * breif: ����HL7Э���еġ�ACK^R01����Ϣ����Ҫ��������ַ�������
 *        HL7ACKR01Message�������ݣ��Լ�����HL7ACKR01Message
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7ACKR01Message
	:public HL7Message{
//construction & destruction
public:
	HL7ACKR01Message(void);
	virtual ~HL7ACKR01Message(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};