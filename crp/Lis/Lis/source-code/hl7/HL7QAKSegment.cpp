#include"stdafx.h"
#include"HL7QAKSegment.h"

//��ʼ����̬������
const String HL7QAKSegment::SegmentName(Text("QAK"));

/**
 * name: HL7QAKSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7QAKSegment::HL7QAKSegment(void)
	:HL7Segment(SegmentName,3)
	,_query_tag(Text("SR"))
	,_query_response_status(Text("")){
}

/**
 * name: ~HL7QAKSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7QAKSegment::~HL7QAKSegment(void){
}

/**
 * name: get_query_tag
 * brief: ��ȡ��ѯ��ǡ�
 * param: --
 * return: ���ز�ѯ��ǡ�
 */
const String &HL7QAKSegment::get_query_tag() const{
	return(_query_tag);
}

/**
 * name: set_query_response_status
 * brief: ���ò�ѯӦ��״̬��
 * param: query_response_status - ��ѯӦ��״̬��
 * return: --
 */
void HL7QAKSegment::set_query_response_status(const String &query_response_status){
	_query_response_status=query_response_status;
}

/**
 * name: get_query_response_status
 * brief: ��ȡ��ѯӦ��״̬��
 * param: --
 * return: ���ز�ѯӦ��״̬��
 */
const String &HL7QAKSegment::get_query_response_status() const{
	return(_query_response_status);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7QAKSegment::set_field(const unsigned int no,const String &content){
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
		//2-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("SR")!=content){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		//_query_tag=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((Text("OK")!=content)&&
			(Text("NF")!=content)&&
			(Text("AE")!=content)&&
			(Text("AR")!=content)){
			return(-3);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		_query_response_status=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-4);
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
int HL7QAKSegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("SR")!=_query_tag){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_tag;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((Text("OK")!=_query_response_status)&&
			(Text("NF")!=_query_response_status)&&
			(Text("AE")!=_query_response_status)&&
			(Text("AR")!=_query_response_status)){
			return(-3);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_response_status;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-4);
	}
}