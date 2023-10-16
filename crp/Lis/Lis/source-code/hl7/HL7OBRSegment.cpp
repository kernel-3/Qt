#include"stdafx.h"
#include"HL7OBRSegment.h"

//�����ʼ��ȫ�ֱ�����
const String HL7OBRSegment::SegmentName(Text("OBR"));

/**
 * name: HL7OBRSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7OBRSegment::HL7OBRSegment(void)
	:HL7Segment(SegmentName,48)
	,_segment_id(Text("1")){
}

/**
 * name: ~HL7OBRSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7OBRSegment::~HL7OBRSegment(void){
}

/**
 * name: get_segment_id
 * breif: ��ȡ���Ρ���ID��
 * param: --
 * return: ���ء��Ρ���ID��
 */
const String &HL7OBRSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7OBRSegment::set_field(const unsigned int no,const String &content){
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
		if(content!=_segment_id){
			return(-2);
		}
		//2-1.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ġ��򡱴��ڵڶ�����
	else if(no>2){
		return(0);
	}
	//4.�����ǰ�������á��Ρ��ġ���Ϊ�쳣���򡱡�
	else{
		return(-3);
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
int HL7OBRSegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.��ȡ�ڶ������򡱵����ݡ�
		content=_segment_id;
		//2-2.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ġ��򡱴��ڵڶ�����
	else if(no>2){
		return(0);
	}
	//4.�����ǰ������ȡ���Ρ��ġ���Ϊ�쳣���򡱡�
	else{
		return(-2);
	}
}