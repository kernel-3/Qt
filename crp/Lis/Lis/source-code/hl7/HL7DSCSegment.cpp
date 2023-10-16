#include"stdafx.h"
#include"HL7DSCSegment.h"
#include"../tool/DataConverter.h"

//��ʼ����̬������
const String HL7DSCSegment::SegmentName(Text("DSC"));

/**
 * name: HL7DSCSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7DSCSegment::HL7DSCSegment(void)
	:HL7Segment(SegmentName,2)
	,_continuation_pointer(Text("")){
}

/**
 * name: ~HL7DSCSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7DSCSegment::~HL7DSCSegment(void){
}

/**
 * name: set_continuation_pointer
 * brief: ��������ָ�롣
 * param: continuation_pointer - ����ָ�롣
 * return: --
 */
void HL7DSCSegment::set_continuation_pointer(const String &continuation_pointer){
	_continuation_pointer=continuation_pointer;
}

/**
 * name: get_continuation_pointer
 * brief: ��ȡ����ָ�롣
 * param: --
 * return: ��������ָ�롣
 */
const String &HL7DSCSegment::get_continuation_pointer() const{
	return(_continuation_pointer);
}

/**
 * name: set_continuation_pointer_with_number
 * brief: ��������ʽ��������ָ�롣
 * param: continuation_pointer - ����ָ�롣
 * return: --
 */
void HL7DSCSegment::set_continuation_pointer_with_number(const unsigned int continuation_pointer){
	_continuation_pointer=DataConverter::to_string(continuation_pointer);
}

/**
 * name: get_continuation_pointer_with_number
 * brief: ��������ʽ��ȡ����ָ�롣
 * param: --
 * return: �������ִ�гɹ���������ʽ��������ָ�룬���򷵻��㡣
 */
unsigned int HL7DSCSegment::get_continuation_pointer_with_number() const{
	return(DataConverter::to_unsigned_int(_continuation_pointer));
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7DSCSegment::set_field(const unsigned int no,const String &content){
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
		if((!content.IsEmpty())&&
			(0==DataConverter::to_unsigned_int(content))){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_continuation_pointer=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ����Ϊ���������򡱣��򷵻ش���
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
int HL7DSCSegment::get_field(const unsigned int no,String &content) const{
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
		if((!_continuation_pointer.IsEmpty())&&
			(0==get_continuation_pointer_with_number())){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_continuation_pointer;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-3);
	}
}