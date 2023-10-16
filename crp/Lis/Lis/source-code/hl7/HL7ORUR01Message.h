#pragma once

#include"HL7Message.h"

/**
 * name: HL7ORUR01Message
 * breif: ����HL7Э���еġ�ORU^R01����Ϣ����Ҫ��������ַ�������
 *        HL7ORUR01Message�������ݣ��Լ�����HL7ORUR01Message
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2014-12-19
 * remark: ���������С�ORU^R01��������Ϣ�Ļ��࣬���ǳ����࣬����ʵ������
 */
class HL7ORUR01Message
	:public HL7Message{
//construction & destruction
public:
	HL7ORUR01Message(void);
	virtual ~HL7ORUR01Message(void);
};