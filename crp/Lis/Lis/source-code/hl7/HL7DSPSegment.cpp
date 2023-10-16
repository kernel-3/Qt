#include"stdafx.h"
#include"HL7DSPSegment.h"
#include"../tool/DataConverter.h"

//��ʼ����̬������
const String HL7DSPSegment::SegmentName(Text("DSP"));

/**
 * name: HL7DSPSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7DSPSegment::HL7DSPSegment(void)
	:HL7Segment(SegmentName,6)
	,_segment_id(Text(""))
	,_data_content(Text("")){
}

/**
 * name: ~HL7DSPSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7DSPSegment::~HL7DSPSegment(void){
}

/**
 * name: set_segment_id
 * brief: ���ö�ID��
 * param: segment_id - ��ID��
 * return: --
 */
void HL7DSPSegment::set_segment_id(const String &segment_id){
	_segment_id=segment_id;
}

/**
 * name: get_segment_id
 * brief: ��ȡ��ID��
 * param: --
 * return: ���ض�ID��
 */
const String &HL7DSPSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_segment_id_with_number
 * brief: ��������ʽ���ö�ID��
 * param: segment_id - ��ID��
 * return: --
 */
void HL7DSPSegment::set_segment_id_with_number(const unsigned int segment_id){
	_segment_id=DataConverter::to_string(segment_id);
}

/**
 * name: get_segment_id_with_number
 * brief: ��������ʽ��ȡ��ID��
 * param: --
 * return: �������ִ�гɹ����ض�ID�����򷵻��㡣
 */
const unsigned int HL7DSPSegment::get_segment_id_with_number() const{
	return(DataConverter::to_unsigned_int(_segment_id));
}

/**
 * name: set_data_content
 * brief: �����������ݡ�
 * param: data_content - �������ݡ�
 * return: --
 */
void HL7DSPSegment::set_data_content(const String &data_content){
	_data_content=data_content;
}

/**
 * name: get_data_content
 * brief: ��ȡ�������ݡ�
 * param: --
 * return: �����������ݡ�
 */
const String &HL7DSPSegment::get_data_content() const{
	return(_data_content);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7DSPSegment::set_field(const unsigned int no,const String &content){
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
		if(0==DataConverter::to_unsigned_int(content)){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_segment_id=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){//���ԡ�
		return(0);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ�ǰ���򡱵����ݡ�
		_data_content=content;
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
	//7.�����ǰ����Ϊ���������򡱣��򷵻ش���
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
int HL7DSPSegment::get_field(const unsigned int no,String &content) const{
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
		if(0==get_segment_id_with_number()){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_segment_id;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){//���ԡ�
		return(0);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_data_content;
		//4-2.�������е��˳ɹ����ء�
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
	//7.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-3);
	}
}