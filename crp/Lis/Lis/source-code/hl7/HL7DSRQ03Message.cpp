#include"stdafx.h"
#include"HL7DSRQ03Message.h"
#include"HL7MSASegment.h"
#include"HL7ERRSegment.h"
#include"HL7QAKSegment.h"
#include"HL7QRDSegment.h"
#include"HL7QRFSegment.h"
#include"HL7DSPSegment.h"
#include"HL7DSCSegment.h"

/**
 * name: HL7DSRQ03Message
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7DSRQ03Message::HL7DSRQ03Message(void)
	:HL7Message(){
}

/**
 * name: ~HL7DSRQ03Message
 * brief: ����������
 * param: --
 * return: --
 */
HL7DSRQ03Message::~HL7DSRQ03Message(void){
}

/**
 * name: are_segments_available
 * brief: �жϵ�ǰ��Ϣ�����еĶ���Ϣ�Ƿ���Ч��
 * param: --
 * return: �����ǰ��Ϣ�����еĶ���Ϣ���Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7DSRQ03Message::are_segments_available() const{
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
	if(HL7MSASegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.�жϵ�ǰ��Ϣ���������Ƿ���Ч�Ϸ���
	//3-1.��ȡ��ǰ��Ϣ�ĵ������Ρ�
	segment=get_segment(3);
	if(!static_cast<bool>(segment)){
		return(-4);
	}
	//3-2.�жϵ�ǰ��Ϣ�ĵ��������Ƿ�ΪERR�Ρ�
	if(HL7ERRSegment::SegmentName!=segment->get_name()){
		return(-5);
	}
	//4.�жϵ�ǰ��Ϣ���ĸ����Ƿ���Ч�Ϸ���
	//4-1.��ȡ��ǰ��Ϣ�ĵ��ĸ��Ρ�
	segment=get_segment(4);
	if(!static_cast<bool>(segment)){
		return(-6);
	}
	//4-2.�жϵ�ǰ��Ϣ�ĵ��ĸ����Ƿ�ΪQAK�Ρ�
	if(HL7QAKSegment::SegmentName!=segment->get_name()){
		return(-7);
	}
	//5.�жϵ�ǰ��Ϣ��������Ƿ���Ч�Ϸ���
	//5-1.��ȡ��ǰ��Ϣ�ĵ�����Ρ�
	segment=get_segment(5);
	if(!static_cast<bool>(segment)){
		return(-8);
	}
	//5-2.�жϵ�ǰ��Ϣ�ĵ��ĸ����Ƿ�ΪQRD�Ρ�
	if(HL7QRDSegment::SegmentName!=segment->get_name()){
		return(-9);
	}
	//6.�жϵ�ǰ��Ϣ���������Ƿ���Ч�Ϸ���
	//6-1.��ȡ��ǰ��Ϣ�ĵ������Ρ�
	segment=get_segment(6);
	if(!static_cast<bool>(segment)){
		return(-10);
	}
	//6-2.�жϵ�ǰ��Ϣ�ĵ��������Ƿ�ΪQRF�Ρ�
	if(HL7QRFSegment::SegmentName!=segment->get_name()){
		return(-11);
	}
	//7~37.�жϵ�ǰ��Ϣ�ĵ��߸���������ʮ�߸����Ƿ�Ϸ���Ч��
	for(unsigned int no=7;no<=37;++no){
		//7~37-1.��ȡ��ǰ��Ϣ�ĵ�no���Ρ�
		segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(-12);
		}
		//7~37-2.�жϵ�ǰ��Ϣ�ĵ�no�����Ƿ�ΪDSP�Ρ�
		if(HL7DSPSegment::SegmentName!=segment->get_name()){
			return(-13);
		}
	}
	//38.�жϵ�ǰ��Ϣ�ĵ���ʮ�˸����Ƿ�Ϸ���Ч��
	//38-1.��ȡ��ǰ��Ϣ�ĵ���ʮ�˸��Ρ�
	segment=get_segment(38);
	if(!static_cast<bool>(segment)){
		return(-14);
	}
	//38-2.�жϵ�ǰ��Ϣ�ĵ���ʮ�˸����Ƿ�ΪDSC�Ρ�
	if(HL7DSCSegment::SegmentName!=segment->get_name()){
		return(-15);
	}
	//39.�жϵ�ǰ��Ϣ�жε������Ƿ�Ϸ���
	if(38!=size_of_segments()){
		return(-16);
	}
	//40.�������е��˳ɹ����ء�
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
int HL7DSRQ03Message::set_segment(const unsigned int no,const String &content){
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
		PtrToSegment segment(new HL7MSASegment);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7MSASegment*>(
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
		PtrToSegment segment(new HL7ERRSegment);
		if(!static_cast<bool>(segment)){
			return(-5);
		}
		//3-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7ERRSegment*>(
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
	//4.�����ǰ�������õ��ĸ��ε����ݡ�
	else if(4==no){
		//4-1.�������ĸ���ʵ����
		PtrToSegment segment(new HL7QAKSegment);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//4-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7QAKSegment*>(
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
	//5.�����ǰ�������õ�����ε����ݡ�
	else if(5==no){
		//5-1.�����������ʵ����
		PtrToSegment segment(new HL7QRDSegment);
		if(!static_cast<bool>(segment)){
			return(-11);
		}
		//5-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7QRDSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-12);
		}
		//5-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-13);
		}
		//5-4.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������õ������ε����ݡ�
	else if(6==no){
		//6-1.������������ʵ����
		PtrToSegment segment(new HL7QRFSegment);
		if(!static_cast<bool>(segment)){
			return(-14);
		}
		//6-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7QRFSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-15);
		}
		//6-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-16);
		}
		//6-4.�������е��˳ɹ����ء�
		return(1);
	}
	//7~37.�����ǰ�������õ��ߵ�����ʮ�߸��ε����ݡ�
	else if((no>=7)&&(no<=37)){
		//7-1.������no����ʵ����
		PtrToSegment segment(new HL7DSPSegment);
		if(!static_cast<bool>(segment)){
			return(-17);
		}
		//7-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7DSPSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-18);
		}
		//7-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-19);
		}
		//7-4.�������е��˳ɹ����ء�
		return(1);
	}
	//38.�����ǰ�������õ���ʮ�˸��ε����ݡ�
	else if(38==no){
		//38-1.��������ʮ�˸���ʵ����
		PtrToSegment segment(new HL7DSCSegment);
		if(!static_cast<bool>(segment)){
			return(-20);
		}
		//38-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7DSCSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-21);
		}
		//38-3.����ǰ�β��뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-22);
		}
		//38-4.�������е��˳ɹ����ء�
		return(1);
	}
	//39.�����ǰ���õĶ�Ϊ�����������ֱ�ӷ��ش���
	else{
		return(-23);
	}
}