#include"stdafx.h"
#include"HL7ORUR01MessageForCalib.h"
#include"HL7OBRSegment.h"
#include"HL7OBRSegmentForCalib.h"

/**
 * name: HL7ORUR01MessageForCalib
 * breif: ���캯����
 * param: --
 * return: --
 */
HL7ORUR01MessageForCalib::HL7ORUR01MessageForCalib(void)
	:HL7ORUR01Message(){
}

/**
 * name: ~HL7ORUR01MessageForCalib
 * breif: ����������
 * param: --
 * return: --
 */
HL7ORUR01MessageForCalib::~HL7ORUR01MessageForCalib(void){
}

/**
 * name: are_segments_available
 * brief: �жϵ�ǰ��Ϣ�����еĶ���Ϣ�Ƿ���Ч��
 * param: --
 * return: �����ǰ��Ϣ�����еĶ���Ϣ���Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7ORUR01MessageForCalib::are_segments_available() const{
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
	if(HL7OBRSegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.�жϵ�ǰ��Ϣ�жε������Ƿ�Ϸ���
	if(2!=size_of_segments()){
		return(-4);
	}
	//4.�������е��˳ɹ����ء�
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
int HL7ORUR01MessageForCalib::set_segment(const unsigned int no,const String &content){
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
		PtrToSegment segment(new HL7OBRSegmentForCalib);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7OBRSegmentForCalib*>(
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
	//3.�����ǰ���õĶ�Ϊ�����������ֱ�ӷ��ش���
	else{
		return(-5);
	}
}