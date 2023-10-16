#pragma once

#include"HL7ORUR01Message.h"

/**
 * name: HL7ORUR01MessageForCalib
 * breif: ����HL7Э���еġ�ORU^R01����Ϣ�����ݶ������ġ�ORU^R01��
 *        ��Ϣ������Ҫ��������ַ�������HL7ORUR01MessageForCalib
 *        �������ݣ��Լ�����HL7ORUR01MessageForCalib������������
 *        HL7Э���ʽ���ַ�����
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