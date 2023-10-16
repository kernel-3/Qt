#pragma once

#include"HL7Message.h"

/**
 * name: HL7ACKQ03Message
 * breif: ����HL7Э���еġ�ACK^Q03����Ϣ����Ҫ��������ַ�������
 *        HL7ACKQ03Message�������ݣ��Լ�����HL7ACKQ03Message
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7ACKQ03Message
	:public HL7Message{
//construction & destruction
public:
	HL7ACKQ03Message(void);
	virtual ~HL7ACKQ03Message(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};