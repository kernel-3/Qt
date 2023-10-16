#include"stdafx.h"
#include"HL7ORUR01MessageForTest.h"
#include"HL7PIDSegment.h"
#include"HL7OBRSegment.h"
#include"HL7OBRSegmentForTest.h"
#include"HL7OBXSegment.h"

/**
 * name: HL7ORUR01MessageForTest
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7ORUR01MessageForTest::HL7ORUR01MessageForTest(void)
	:HL7ORUR01Message(){
}

/**
 * name: ~HL7ORUR01MessageForTest
 * brief: ����������
 * param: --
 * return: --
 */
HL7ORUR01MessageForTest::~HL7ORUR01MessageForTest(void){
}

/**
 * name: are_segments_available
 * brief: �жϵ�ǰ��Ϣ�����еĶ���Ϣ�Ƿ���Ч��
 * param: --
 * return: �����ǰ��Ϣ�����еĶ���Ϣ���Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7ORUR01MessageForTest::are_segments_available() const{
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(HL7ORUR01Message::are_segments_available()<0){
		return(-1);
	}
	//2.�жϵ�ǰ��Ϣ�ڶ������Ƿ���Ч�Ϸ���
	//2-1.��ȡ��ǰ��Ϣ�ĵڶ����Ρ�
	PtrToCSegment segment=get_segment(2);
	if(!static_cast<bool>(segment)){
		return(-2);
	}
	//2-2.�жϵ�ǰ��Ϣ�ĵڶ������Ƿ�ΪPID�Ρ�
	if(HL7PIDSegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.�жϵ�ǰ��Ϣ���������Ƿ���Ч�Ϸ���
	//3-1.��ȡ��ǰ��Ϣ�ĵ������Ρ�
	segment=get_segment(3);
	if(!static_cast<bool>(segment)){
		return(-4);
	}
	//3-2.�жϵ�ǰ��Ϣ�ĵ��������Ƿ�ΪOBR�Ρ�
	if(HL7OBRSegment::SegmentName!=segment->get_name()){
		return(-5);
	}
	//4.�жϵ�ǰ��Ϣ���ĸ����Ƿ���Ч�Ϸ���
	//4-1.��ȡ��ǰ��Ϣ�ĵ��ĸ��Ρ�
	segment=get_segment(4);
	if(!static_cast<bool>(segment)){
		return(-6);
	}
	//4-2.�жϵ�ǰ��Ϣ�ĵ��ĸ����Ƿ�ΪOBX�Ρ�
	if(HL7OBXSegment::SegmentName!=segment->get_name()){
		return(-7);
	}
	//5.�жϵ�ǰ��Ϣ������ε�����������Ƿ�ΪOBX�Ρ�
	for(unsigned int no=5;no<=size_of_segments();++no){
		//5-1.��ȡ��ǰ��Ϣ�ĵ�no���Ρ�
		segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//5-2.�жϵ�ǰ��Ϣ�ĵ�no�����Ƿ�ΪOBX�Ρ�
		if(HL7OBXSegment::SegmentName!=segment->get_name()){
			return(-9);
		}
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_segment
 * brief: ���õ�ǰ����Ϣ����ָ�����Ρ���
 * param: no - ���Ρ��ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���Ρ������ݡ�
 * return: ������Ρ����óɹ�����ֵ�����㣬������ԡ��Ρ��������򷵻��㣬
 *         ������Ρ�����ʧ�ܷ��ظ�����
 */
int HL7ORUR01MessageForTest::set_segment(const unsigned int no,const String &content){
	//1.���û�����Ӧ������,�����жϴ����Ƿ���ɡ�
	//1-1.���û�����Ӧ�����������Ҽ�¼��������
	const int execute_result=HL7ORUR01Message::set_segment(no,content);
	//1-2.��������Ѿ�������ɡ�
	if(execute_result>0){
		return(1);
	}
	//1-3.������ദ��ʧ�ܡ�
	if(execute_result<0){
		return(-1);
	}
	//2.�����ǰ�������õڶ����ε����ݡ�
	else if(2==no){
		//2-1.�����ڶ�����ʵ����
		PtrToSegment segment(new HL7PIDSegment);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7PIDSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-3);
		}
		//2-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-4);
		}
		//2-4.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������õ������ε����ݡ�
	else if(3==no){
		//3-1.������������ʵ����
		PtrToSegment segment(new HL7OBRSegmentForTest);
		if(!static_cast<bool>(segment)){
			return(-5);
		}
		//3-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7OBRSegmentForTest*>(
			segment.get())->from_hl7(content)<0){
			return(-6);
		}
		//3-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-7);
		}
		//3-4.�������е��˳ɹ����ء�
		return(1);
	}
	//4~��.�����ǰ�������õ��ĸ����ڡ޸��ε����ݡ�
	else if(4<=no){
		//4-1.�������ĸ����ڡ޸���ʵ����
		PtrToSegment segment(new HL7OBXSegment);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//4-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7OBXSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-9);
		}
		//4-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-10);
		}
		//4-4.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ���õĶ�Ϊ�����������ֱ�ӷ��ش���
	else{
		return(-11);
	}
}