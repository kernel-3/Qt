#include"stdafx.h"
#include"HL7MSHSegment.h"
#include"../tool/DataConverter.h"

//��ʼ��ȫ�ֱ�����
const String HL7MSHSegment::SegmentName(Text("MSH"));

/**
 * name: HL7MSHSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7MSHSegment::HL7MSHSegment(void)
	:HL7Segment(SegmentName,20)
	,_separator(Text("^~\\&"))
	,_sending_application(Text(""))
	,_sending_facility(Text(""))
	,_receiving_application(Text(""))
	,_receiving_facility(Text(""))
	,_message_date_time(Text(""))
	,_message_type(Text(""))
	,_message_control_id(Text(""))
	,_processing_id(Text("P"))
	,_version_id(Text("2.3.1"))
	,_accept_acknowledgment_type(Text(""))
	,_application_acknowledgment_type(Text(""))
	,_character_set(Text("ASCII")){
}

/**
 * name: ~HL7MSHSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7MSHSegment::~HL7MSHSegment(void){
}

/**
 * name: get_separator
 * brief: ��ȡ��ǰ���Ρ��ķָ�����
 * param: --
 * return: ���ص�ǰ���Ρ��ķָ�����
 */
const String &HL7MSHSegment::get_separator() const{
	return(_separator);
}

/**
 * name: set_sending_application
 * brief: ���÷��Ͷ˳���
 * param: sending_application - ���Ͷ˳���
 * return: --
 */
void HL7MSHSegment::set_sending_application(const String &sending_application){
	_sending_application=sending_application;
}

/**
 * name: get_sending_application
 * brief: ��ȡ���Ͷ˳���
 * param: --
 * return: ���ط��Ͷ˳���
 */
const String &HL7MSHSegment::get_sending_application() const{
	return(_sending_application);
}

/**
 * name: set_sending_facility
 * brief: ���÷��Ͷ��豸��
 * param: sending_facility - ���Ͷ��豸��
 * return: --
 */
void HL7MSHSegment::set_sending_facility(const String &sending_facility){
	_sending_facility=sending_facility;
}

/**
 * name: get_sending_facility
 * brief: ��ȡ���Ͷ��豸��
 * param: --
 * return: ���ط��Ͷ��豸��
 */
const String &HL7MSHSegment::get_sending_facility() const{
	return(_sending_facility);
}

/**
 * name: set_receiving_application
 * brief: ���ý��ն˳���
 * param: receiving_application - ���ն˳���
 * return: --
 */
void HL7MSHSegment::set_receiving_application(const String &receiving_application){
	_receiving_application=receiving_application;
}

/**
 * name: get_receiving_application
 * brief: ��ȡ���ն˳���
 * param: --
 * return: ���ؽ��ն˳���
 */
const String &HL7MSHSegment::get_receiving_application() const{
	return(_receiving_application);
}

/**
 * name: set_receiving_facility
 * brief: ���ý��ն��豸��
 * param: receiving_facility - ���ն��豸��
 * return: --
 */
void HL7MSHSegment::set_receiving_facility(const String &receiving_facility){
	_receiving_facility=receiving_facility;
}

/**
 * name: get_receiving_facility
 * brief: ��ȡ���ն��豸��
 * param: --
 * return: ���ؽ��ն��豸��
 */
const String &HL7MSHSegment::get_receiving_facility() const{
	return(_receiving_facility);
}

/**
 * name: set_message_date_time
 * brief: ������Ϣ������ʱ�䡣
 * param: message_date_time - ��Ϣ������ʱ�䡣
 * return: --
 */
void HL7MSHSegment::set_message_date_time(const String &message_date_time){
	_message_date_time=message_date_time;
}

/**
 * name: get_message_date_time
 * brief: ��ȡ��Ϣ������ʱ�䡣
 * param: --
 * return: ������Ϣ������ʱ�䡣
 */
const String &HL7MSHSegment::get_message_date_time() const{
	return(_message_date_time);
}

/**
 * name: set_message_type
 * brief: ������Ϣ���͡�
 * param: message_type - ��Ϣ���͡�
 * return: --
 */
void HL7MSHSegment::set_message_type(const String &message_type){
	_message_type=message_type;
}

/**
 * name: get_message_type
 * brief: ��ȡ��Ϣ���͡�
 * param: --
 * return: ������Ϣ���͡�
 */
const String &HL7MSHSegment::get_message_type() const{
	return(_message_type);
}

/**
 * name: set_message_control_id
 * brief: ������Ϣ����ID��
 * param: message_control_id - ��Ϣ����ID��
 * return: --
 */
void HL7MSHSegment::set_message_control_id(const String &message_control_id){
	_message_control_id=message_control_id;
}

/**
 * name: get_message_control_id
 * brief: ��ȡ��Ϣ����ID��
 * param: --
 * return: ������Ϣ����ID��
 */
const String &HL7MSHSegment::get_message_control_id() const{
	return(_message_control_id);
}

/**
 * name: get_processing_id
 * brief: ��ȡ����ID��
 * param: --
 * return: ���ش���ID��
 */
const String &HL7MSHSegment::get_processing_id() const{
	return(_processing_id);
}

/**
 * name: get_version_id
 * brief: ��ȡ�汾ID��
 * param: --
 * return: ���ذ汾ID��
 */
const String &HL7MSHSegment::get_version_id() const{
	return(_version_id);
}

/**
 * name: set_accept_acknowledgment_type
 * brief: ���ý���Ӧ�����͡������ͽ����� DSR^Q03 ��Ϣ��Ч��
 *        ȡֵΪ P ����ʾ LIS ϵͳ�������͵�������Ϣ������
 *        ֵ��ʾ��Ӧ LIS ��ѯ��������Ϣ�����ÿա�
 * param: accept_acknowledgment_type - ����Ӧ�����͡�
 * return: --
 */
void HL7MSHSegment::set_accept_acknowledgment_type(
	const String &accept_acknowledgment_type){
	_accept_acknowledgment_type=accept_acknowledgment_type;
}

/**
 * name: get_accept_acknowledgment_type
 * brief: ��ȡ����Ӧ�����͡������ͽ����� DSR^Q03 ��Ϣ��Ч��
 *        ȡֵΪ P ����ʾ LIS ϵͳ�������͵�������Ϣ������
 *        ֵ��ʾ��Ӧ LIS ��ѯ��������Ϣ�����ÿա�
 * param: --
 * return: ���ؽ���Ӧ�����͡�
 */
const String &HL7MSHSegment::get_accept_acknowledgment_type() const{
	return(_accept_acknowledgment_type);
}

/**
 * name: set_application_acknowledgment_type
 * brief: ����Ӧ�ó���Ӧ�����͡���������Ϊ���͵Ľ����
 *		  �͡�1-�����������Խ����2-��������3-�ʿ�
 *		  �����
 * param: application_acknowledgment_type - Ӧ�ó���Ӧ�����͡�
 * return: --
 */
void HL7MSHSegment::set_application_acknowledgment_type(
	const String &application_acknowledgment_type){
	_application_acknowledgment_type=application_acknowledgment_type;
}

/**
 * name: get_application_acknowledgment_type
 * brief: ��ȡӦ�ó���Ӧ�����͡���������Ϊ���͵Ľ����
 *		  �͡�1-�����������Խ����2-��������3-�ʿ�
 *		  �����
 * param: --
 * return: ����Ӧ�ó���Ӧ�����͡�
 */
const String &HL7MSHSegment::get_application_acknowledgment_type() const{
	return(_application_acknowledgment_type);
}

/**
 * name: set_application_acknowledgment_type_with_number
 * brief: ��������ʽ����Ӧ�ó���Ӧ�����͡���������Ϊ���͵Ľ����
 *		  �͡�1-�����������Խ����2-��������3-�ʿؽ����
 * param: application_acknowledgment_type - Ӧ�ó���Ӧ�����͡�
 * return: --
 */
void HL7MSHSegment::set_application_acknowledgment_type_with_number(
	const unsigned int application_acknowledgment_type){
	_application_acknowledgment_type=DataConverter::to_string(
		application_acknowledgment_type);
}

/**
 * name: get_application_acknowledgment_type_with_number
 * brief: ��������ʽ��ȡӦ�ó���Ӧ�����͡���������Ϊ���͵Ľ����
 *		  �͡�1-�����������Խ����2-��������3-�ʿؽ����
 * param: --
 * return: �������ִ�гɹ�����Ӧ�ó���Ӧ�����͵�������ʽ�����򷵻��㡣
 */
unsigned int HL7MSHSegment::get_application_acknowledgment_type_with_number() const{
	return(DataConverter::to_unsigned_int(_application_acknowledgment_type));
}

/**
 * name: get_character_set
 * brief: ��ȡ�ַ�����
 * param: --
 * return: �����ַ�����
 */
const String &HL7MSHSegment::get_character_set() const{
	return(_character_set);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7MSHSegment::set_field(const unsigned int no,const String &content){
	//1.���û�����Ӧ��������ָ���ġ��򡱣������ж����ý����
	//1-1.���û�����Ӧ��������ָ���ġ��򡱡�
	const int execute_result=HL7Segment::set_field(no,content);
	//1-2.����ɹ�����ָ���ġ��򡱡�
	if(execute_result>0){
		return(1);
	}
	//1-3.�������ָ���ġ���ʧ�ܡ�
	else if(execute_result<0){
		return(-1);
	}
	//2.�����ǰ�������á��Ρ��ĵڶ������򡱡�
	else if(2==no){
		//2-1.�����ǰ���õĵڶ������򡱺Ϸ���
		if(content==_separator){
			return(1);
		}
		//2-2.�����ǰ���õĵڶ������򡱲��Ϸ���
		else{
			return(-2);
		}
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.���õ��������򡱡�
		_sending_application=content;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ��ĸ����򡱡�
		_sending_facility=content;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.���õ�������򡱡�
		_receiving_application=content;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.���õ��������򡱡�
		_receiving_facility=content;
		//6-2.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.���õ��߸����򡱡�
		_message_date_time=content;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){//���ԡ�
		return(0);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if(content.IsEmpty()){//�����ǰ����Ϊ�գ���ֱ�ӷ��ش���
			return(-3);
		}else /*if(...)*/{//������ݲ��Ϸ�����ֱ�ӷ��ش���
			//return(-4);
			//unfinished.
		}
		//9-2.���õھŸ����򡱡�
		_message_type=content;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if(content.IsEmpty()){
			return(-5);
		}
		//10-2.���õ�ʮ�����򡱡�
		_message_control_id=content;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ�������á��Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.�����ǰ���õĵ�ʮһ�����򡱺Ϸ���
		if(_processing_id==content){
			return(1);
		}
		//11-2.�����ǰ���õĵ�ʮһ�����򡱲��Ϸ���
		else{
			return(-6);
		}
	}
	//12.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.�����ǰ���õĵ�ʮ�������򡱺Ϸ���
		if(_version_id==content){
			return(1);
		}
		//12-2.�����ǰ���õĵ�ʮ�������򡱲��Ϸ���
		else{
			return(-7);
		}
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){//���ԡ�
		return(0);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.���õ�ʮ������򡱡�
		_accept_acknowledgment_type=content;
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((!content.IsEmpty())&&(Text("0")!=content)&&
			(Text("1")!=content)&&(Text("2")!=content)){
			return(-8);
		}
		//16-2.���õ�ʮ�������򡱡�
		_application_acknowledgment_type=content;
		//16-3.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		/*
		//18-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(_character_set!=content){
			return(-9);
		}
		//18-2.�������е��˳ɹ����ء�
		else{*/
		return(1);
		/*}*/
	}
	//19.�����ǰ�������á��Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){//���ԡ�
		return(0);
	}
	//20.�����ǰ�������á��Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){//���ԡ�
		return(0);
	}
	//21.�����ǰ����Ϊ���������򡱣���ֱ�ӷ��ش���
	else{
		return(-9);
	}
}

/**
 * name: get_field
 * brief: ��ȡ���Ρ���ָ�����򡱵����ݡ�
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���ء��򡱵����ݡ�
 * return: ����������ݻ�ȡ�ɹ�����ֵ�����㣬������ԡ���
 *         ���ݵĻ�ȡ�����򷵻��㣬����������ݵĻ�ȡʧ��
 *         ���ظ�����
 */
int HL7MSHSegment::get_field(const unsigned int no,String &content) const{
	//1.���û�����Ӧ������ȡָ���ġ��򡱣������жϻ�ȡ�����
	//1-1.���û�����Ӧ������ȡָ���ġ��򡱡�
	const int execute_result=HL7Segment::get_field(no,content);
	//1-2.������û�����Ӧ�����ɹ���ȡָ���ġ��򡱣���ֱ�ӷ��ء�
	if(execute_result>0){
		return(1);
	}
	//1-3.������û�����Ӧ������ȡָ���ġ���ʧ�ܣ���ֱ�ӷ��ء�
	else if(execute_result<0){
		return(-1);
	}
	//2.�����ǰ������ȡ���Ρ��ĵڶ������򡱡�
	else if(2==no){
		//2-1.��ȡ��ǰ���򡱵����ݡ�
		content=_separator;
		//2-2.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.��ȡ��ǰ���򡱵����ݡ�
		content=_sending_application;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_sending_facility;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.��ȡ��ǰ���򡱵����ݡ�
		content=_receiving_application;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.��ȡ��ǰ���򡱵����ݡ�
		content=_receiving_facility;
		//6-2.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.��ȡ��ǰ���򡱵����ݡ�
		content=_message_date_time;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){//���ԡ�
		return(0);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�жϵ�ǰ���򡱵������Ƿ�Ϸ���
		if(_message_type.IsEmpty()){//�����ǰ����Ϊ�գ���ֱ�ӷ��ش���
			return(-2);
		}else/*if(...)*/{//������ݲ��Ϸ�����ֱ�ӷ��ش���
			//return(-3);
			//unfinished.
		}
		//9-2.��ȡ��ǰ���򡱵����ݡ�
		content=_message_type;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�жϵ�ǰ���򡱵������Ƿ�Ϸ���
		if(_message_control_id.IsEmpty()){
			return(-4);
		}
		//10-2.��ȡ��ǰ���򡱵����ݡ�
		content=_message_control_id;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.��ȡ��ǰ���򡱵����ݡ�
		content=_processing_id;
		//11-2.�������е��˳ɹ����ء�
		return(1);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.��ȡ��ǰ���򡱵����ݡ�
		content=_version_id;
		//12-2.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){//���ԡ�
		return(0);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.��ȡ��ǰ���򡱵����ݡ�
		content=_accept_acknowledgment_type;
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.�жϵ�ǰ���򡱵������Ƿ�Ϸ���
		if((!_application_acknowledgment_type.IsEmpty())&&
			(Text("0")!=_application_acknowledgment_type)&&
			(Text("1")!=_application_acknowledgment_type)&&
			(Text("2")!=_application_acknowledgment_type)){
			return(-5);
		}
		//16-2.��ȡ��ǰ���򡱵����ݡ�
		content=_application_acknowledgment_type;
		//16-3.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ȡ��ǰ���򡱵����ݡ�
		content=_character_set;
		//18-2.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ������ȡ���Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){//���ԡ�
		return(0);
	}
	//20.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){//���ԡ�
		return(0);
	}
	//21.�������е��ˣ�ֱ�ӷ��ش��󡣡�
	else{
		return(-6);
	}
}