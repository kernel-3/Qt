#pragma once

#include"HL7ORUR01Message.h"

/**
 * name: HL7ORUR01MessageForTest
 * breif: ����HL7Э���еġ�ORU^R01����Ϣ�����ݲ��Խ���ġ�ORU^R01��
 *        ��Ϣ������Ҫ��������ַ�������HL7ORUR01MessageForTest
 *        �������ݣ��Լ�����HL7ORUR01MessageForTest������������
 *        HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7ORUR01MessageForTest
	:public HL7ORUR01Message{
//construction & destruction
public:
	HL7ORUR01MessageForTest(void);
	virtual ~HL7ORUR01MessageForTest(void);
//overrides
protected:
	virtual int are_segments_available() const;
	virtual int set_segment(const unsigned int no,const String &content);
};