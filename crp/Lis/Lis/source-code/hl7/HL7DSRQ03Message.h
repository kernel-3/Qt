#pragma once

#include"HL7Message.h"

/**
 * name: HL7DSRQ03Message
 * breif: ����HL7Э���еġ�DSR^Q03����Ϣ����Ҫ��������ַ�������
 *        HL7DSRQ03Message�������ݣ��Լ�����HL7DSRQ03Message
 *        ������������HL7Э���ʽ���ַ�����
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