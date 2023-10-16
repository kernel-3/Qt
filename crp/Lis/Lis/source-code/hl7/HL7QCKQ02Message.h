#pragma once

#include"HL7Message.h"

/**
 * name: HL7QCKQ02Message
 * breif: ����HL7Э���еġ�QCK^Q02����Ϣ����Ҫ��������ַ�������
 *        HL7QCKQ02Message�������ݣ��Լ�����HL7QCKQ02Message
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7QCKQ02Message
	:public HL7Message{
//construction & destruction
public:
	HL7QCKQ02Message(void);
	virtual ~HL7QCKQ02Message(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};