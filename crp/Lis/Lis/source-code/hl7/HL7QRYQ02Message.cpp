#include"stdafx.h"
#include"HL7QRYQ02Message.h"
#include"HL7QRDSegment.h"
#include"HL7QRFSegment.h"

/**
 * name: HL7QRYQ02Message
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7QRYQ02Message::HL7QRYQ02Message(void)
	:HL7Message(){
}

/**
 * name: ~HL7QRYQ02Message
 * brief: ����������
 * param: --
 * return: --
 */
HL7QRYQ02Message::~HL7QRYQ02Message(void){
}

/**
 * name: are_segments_available
 * brief: �жϵ�ǰ��Ϣ�����еĶ���Ϣ�Ƿ���Ч��
 * param: --
 * return: �����ǰ��Ϣ�����еĶ���Ϣ���Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7QRYQ02Message::are_segments_available() const{
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(HL7Message::are_segments_available()<0){
		return(-1);
	}
	//2.�жϵ�ǰ��Ϣ�ڶ������Ƿ���Ч�Ϸ���
	//2-1.��ȡ��ǰ��Ϣ�ĵڶ����Ρ�
	PtrToCSegment segment=get_segment(2);
	if(!static_cast<bool>(segment)){
		return(-2);
	}
	//2-2.�жϵ�ǰ��Ϣ�ĵڶ������Ƿ�ΪPID�Ρ�
	if(HL7QRDSegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.�жϵ�ǰ��Ϣ���������Ƿ���Ч�Ϸ���
	//3-1.��ȡ��ǰ��Ϣ�ĵڶ����Ρ�
	segment=get_segment(3);
	if(!static_cast<bool>(segment)){
		return(-4);
	}
	//3-2.�жϵ�ǰ��Ϣ�ĵڶ������Ƿ�ΪPID�Ρ�
	if(HL7QRFSegment::SegmentName!=segment->get_name()){
		return(-5);
	}
	//4.�жϵ�ǰ��Ϣ�жε������Ƿ�Ϸ���
	if(3!=size_of_segments()){
		return(-6);
	}
	//5.�������е��˳ɹ����ء�
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
int HL7QRYQ02Message::set_segment(const unsigned int no,const String &content){
	//1.���û�����Ӧ������,�����жϴ����Ƿ���ɡ�
	//1-1.���û�����Ӧ�����������Ҽ�¼��������
	const int execute_result=HL7Message::set_segment(no,content);
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
		PtrToSegment segment(new HL7QRDSegment);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7QRDSegment*>(
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
		PtrToSegment segment(new HL7QRFSegment);
		if(!static_cast<bool>(segment)){
			return(-5);
		}
		//3-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7QRFSegment*>(
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
	//4.�����ǰ���õĶ�Ϊ�����������ֱ�ӷ��ش���
	else{
		return(-8);
	}
}