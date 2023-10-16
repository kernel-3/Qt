#include"stdafx.h"
#include"HL7MSASegment.h"

//��ʼ����̬������
const String HL7MSASegment::SegmentName(Text("MSA"));

/**
 * name: HL7MSASegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7MSASegment::HL7MSASegment(void)
	:HL7Segment(SegmentName,7)
	,_acknowledgment_code(Text(""))
	,_message_control_id(Text(""))
	,_text_message(Text(""))
	,_error_condition(Text("")){
}

/**
 * name: ~HL7MSASegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7MSASegment::~HL7MSASegment(void){
}

/**
 * name: set_acknowledgment_code
 * brief: ����ȷ�ϴ��롣
 * param: acknowledgment_code - ȷ�ϴ���(AA ��ʾ����;AE ��ʾ����AR ��ʾ�ܾ�)��
 * return: --
 */
void HL7MSASegment::set_acknowledgment_code(const String &acknowledgment_code){
	_acknowledgment_code=acknowledgment_code;
}

/**
 * name: get_acknowledgment_code
 * brief: ��ȡȷ�ϴ��롣
 * param: --
 * return: ����ȷ�ϴ���(AA ��ʾ����;AE ��ʾ����AR ��ʾ�ܾ�)��
 */
const String &HL7MSASegment::get_acknowledgment_code() const{
	return(_acknowledgment_code);
}

/**
 * name: set_message_control_id
 * brief: ������Ϣ����ID��
 * param: message_control_id - ��Ϣ����ID��
 * return: --
 */
void HL7MSASegment::set_message_control_id(const String &message_control_id){
	_message_control_id=message_control_id;
}

/**
 * name: get_message_control_id
 * brief: ��ȡ��Ϣ����ID��
 * param: --
 * return: ������Ϣ����ID��
 */
const String &HL7MSASegment::get_message_control_id() const{
	return(_message_control_id);
}

/**
 * name: set_text_message
 * brief: �����ı���Ϣ��
 * param: text_message - �ı���Ϣ�� 
 * return: --
 */
void HL7MSASegment::set_text_message(const String &text_message){
	_text_message=text_message;
}

/**
 * name: get_text_message
 * brief: ��ȡ�ı���Ϣ��
 * param: -- 
 * return: �����ı���Ϣ��
 */
const String &HL7MSASegment::get_text_message() const{
	return(_text_message);
}

/**
 * name: set_error_condition
 * brief: ���ô���������
 * param: error_condition - ����������
 * return: --
 */
void HL7MSASegment::set_error_condition(const String &error_condition){
	_error_condition=error_condition;
}

/**
 * name: get_error_condition
 * brief: ��ȡ����������
 * param: --
 * return: ���ش���������
 */
const String &HL7MSASegment::get_error_condition() const{
	return(_error_condition);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7MSASegment::set_field(const unsigned int no,const String &content){
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
		//2-1.�����ǰ׼�����õڶ������򡱵����ݲ��Ϸ���
		if((Text("AA")!=content)&&(Text("AE")!=content)&&
			(Text("AR")!=content)){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_acknowledgment_code=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼�����õ��������򡱵����ݲ��Ϸ���
		if(content.IsEmpty()){
			return(-3);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		_message_control_id=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ�ǰ���򡱵����ݡ�
		_text_message=content;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){//���ԡ�
		return(0);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�����ǰ׼�����õ��������򡱵����ݲ��Ϸ���
		if((Text("0")!=content)&&(Text("100")!=content)&&
			(Text("101")!=content)&&(Text("102")!=content)&&
			(Text("103")!=content)&&(Text("200")!=content)&&
			(Text("201")!=content)&&(Text("202")!=content)&&
			(Text("203")!=content)&&(Text("204")!=content)&&
			(Text("205")!=content)&&(Text("206")!=content)&&
			(Text("207")!=content)){
			return(-4);
		}
		//7-2.���õ�ǰ���򡱵����ݡ�
		_error_condition=content;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-5);
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
int HL7MSASegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.�����ǰ���򡱵����ݲ��Ϸ���
		if((Text("AA")!=_acknowledgment_code)&&
			(Text("AE")!=_acknowledgment_code)&&
			(Text("AR")!=_acknowledgment_code)){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_acknowledgment_code;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ���򡱵����ݲ��Ϸ���
		if(_message_control_id.IsEmpty()){
			return(-3);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_message_control_id;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_text_message;
		//4-5.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){//���ԡ�
		return(0);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�����ǰ׼����ȡ���߸����򡱵����ݲ��Ϸ���
		if((Text("0")!=_error_condition)&&(Text("100")!=_error_condition)&&
			(Text("101")!=_error_condition)&&(Text("102")!=_error_condition)&&
			(Text("103")!=_error_condition)&&(Text("200")!=_error_condition)&&
			(Text("201")!=_error_condition)&&(Text("202")!=_error_condition)&&
			(Text("203")!=_error_condition)&&(Text("204")!=_error_condition)&&
			(Text("205")!=_error_condition)&&(Text("206")!=_error_condition)&&
			(Text("207")!=_error_condition)){
			return(-4);
		}
		//7-2.��ȡ��ǰ���򡱵����ݡ�
		content=_error_condition;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ��ȡ��Ϊ�������򡱣��򷵻ش���
	else{
		return(-5);
	}
}