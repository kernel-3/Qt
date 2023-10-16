#pragma once

#include"HL7Message.h"

/**
 * name: HL7QRYQ02Message
 * breif: ����HL7Э���еġ�QRY^Q01����Ϣ����Ҫ��������ַ�������
 *        HL7QRYQ02Message�������ݣ��Լ�����HL7QRYQ02Message
 *        ������������HL7Э���ʽ���ַ�����
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