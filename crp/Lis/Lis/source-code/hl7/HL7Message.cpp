#include"stdafx.h"
#include"HL7Message.h"
#include"HL7Segment.h"
#include"HL7MSHSegment.h"

//��ʼ�����о�̬������
const Char HL7Message::START_CHARACTER=0x0B;
const Char HL7Message::FIRST_END_CHARACTER=0x1C;
const Char HL7Message::SECOND_END_CHARACTER=0x0D;

/**
 * name: HL7Message
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7Message::HL7Message(void)
	:_segments(){
}

/**
 * name: ~HL7Message
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7Message::~HL7Message(void){
}

/**
 * name: add_segment
 * breif: ����Ϣ�����һ�����Ρ���
 * param: segment - ָ��һ�����Ρ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7Message::add_segment(PtrToSegment &segment){
	//1.�����ǰ���ݲ������Ϸ���
	if(!static_cast<bool>(segment)){
		return(-1);
	}
	//2.����ǰ�β���ָ���ġ��Ρ������С�
	_segments.push_back(segment);
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: size_of_segments
 * brief: ��ǰ��Ϣ�д洢���Ρ��ĸ�����
 * param: --
 * return: ������Ϣ�д洢���Ρ��ĸ�����
 */
unsigned int HL7Message::size_of_segments() const{
	return(_segments.size());
}

/**
 * name: clear_segments
 * breif:  ������Ϣ�д洢�ġ��Ρ��ĸ�����
 * param: --
 * return: --
 */
void HL7Message::clear_segments(){
	_segments.clear();
}

/**
 * name: get_segment
 * brief: ��ȡָ���ġ��Ρ���Ϣ��
 * param: no - ���Ρ���ţ�ע�⣬�˱�Ŵ�1��ʼ����
 * return: �������ִ�гɹ�����ָ�򡰶Ρ�������ָ�룬���򷵻ؿյ�����ָ�롣
 */
HL7Message::PtrToCSegment HL7Message::get_segment(
	const unsigned int no) const{
	if((no<1)||(no>_segments.size())){
		return(PtrToCSegment());
	}else{
		return(_segments[no-1]);
	}
}

/**
 * name: from_hl7
 * breif: ����ָ����HL7����Ϣ����䣬���ɡ���Ϣ�����е�������ݡ�
 * param: hl7 - HL7����Ϣ���ַ�����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7Message::from_hl7(const String &hl7){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	const int size=hl7.GetLength();
	if(size<3){
		return(-1);
	}else if((START_CHARACTER!=hl7[0])||
		(FIRST_END_CHARACTER!=hl7[hl7.GetLength()-2])||
		(SECOND_END_CHARACTER!=hl7[hl7.GetLength()-1])){
		return(-2);
	}
	//2.����HL7����Ϣ����䣬������ȡ����Ϣ������еġ��Ρ���Ϣ����Ϊ��ǰ����Ϣ�����ɡ��Ρ�����Ӧʵ����
	//2-1.������ǰ�������������
	int start_index=1;
	int end_index=0;
	unsigned int segment_no=0;
	//2-2.������ǰHL7����Ϣ����䲢��ȡ���Ρ���Ϣ��������Ӧ�ġ��Ρ�ʵ��������жϲ����Ƿ�ɹ���
	while(true){
		//2-2-1.���㡰�Ρ���Ϣ�ڵ�ǰ�ַ����е�λ�á�
		end_index=hl7.Find(HL7Segment::END_CHARACTER,start_index);
		//2-2-2.������㡰�򡱵Ľ���λʧ�ܣ���ֱ�ӷ��ش���
		if((end_index<0)||(end_index<start_index)){
			return(-3);
		}
		//2-2-3.��ȡ���Ρ���Ϣ�ַ�����
		const String segment_content=hl7.Mid(
			start_index,end_index-start_index+1);
		//2-2-4.�����ǰ�ַ����Ѿ�������ɡ�
		if(size-1==end_index){
			if((2!=segment_content.GetLength())||
				(FIRST_END_CHARACTER!=segment_content[0])||
				(SECOND_END_CHARACTER!=segment_content[1])){
				return(-4);
			}else{
				break;
			}
		}
		//2-2-5.�������Ρ��š�
		++segment_no;
		//2-2-6.Ϊ��ǰ����Ϣ�����á��Ρ��������ж������Ƿ�ɹ���
		if(set_segment(segment_no,segment_content)<0){
			return(-5);
		}
		//2-2-7.������ȡ��ʼλ��׼��������һ�εġ��Ρ���Ϣ��ȡ��
		start_index=end_index+1;
	}
	//3.�жϵ�ǰ��Ϣ�д洢�Ķ���Ϣ�Ƿ���Ч��
	if(are_segments_available()<0){
		return(-6);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: to_hl7
 * brief: ����ǰ��Ϣת����HL7�ַ�����
 * param: --
 * return: ���ת���ɹ�����ת�����HL7�ַ��������򷵻ؿ��ַ�����
 */
String HL7Message::to_hl7() const{
	//1.��ȡ��ǰ��Ϣ�д洢�Ķ���Ϣ�����������жϻ�ȡ�Ƿ�ɹ���
	const unsigned int size=size_of_segments();
	if(size<=0){
		return(Text(""));
	}
	//2.�����ǰ��Ϣ�д洢�Ķ���Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(are_segments_available()<0){
		return(Text(""));
	}
	//3.������¼ת������ϢHL7�ַ����ı�����
	String message_hl7(Text(""));
	message_hl7+=START_CHARACTER;
	//4.������ǰ��Ϣ�еĶ���Ϣ�����һ�ȡ����Ϣ��HL7��䡣
	for(unsigned int no=1;no<=size;++no){
		//4-1.��ȡ��ǰ����Ϣ�������жϻ�ȡ�Ƿ�ɹ���
		PtrToCSegment segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(Text(""));
		}
		//4-2.��ȡ��ǰ�ε�HL7��䣬�����жϻ�ȡ�Ƿ�ɹ���
		const String segment_hl7=segment->to_hl7();
		if(segment_hl7.IsEmpty()){
			return(Text(""));
		}
		//4-3.����ǰ�ε�HL7�����ӵ���ϢHL7����С�
		message_hl7+=segment_hl7;
	}
	//5.Ϊ��ǰ��ϢHL7�ַ��������Ϣ��������
	message_hl7+=FIRST_END_CHARACTER;
	message_hl7+=SECOND_END_CHARACTER;
	//6.�������е���ֱ�ӷ�����ϢHL7�ַ�����
	return(message_hl7);
}

/**
 * name: are_segments_available
 * brief: �жϵ�ǰ��Ϣ�����еĶ���Ϣ�Ƿ���Ч��
 * param: --
 * return: �����ǰ��Ϣ�����еĶ���Ϣ���Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7Message::are_segments_available() const{
	//1.��ȡ��ǰ��Ϣ�е�һ���Ρ�
	PtrToCSegment segment=get_segment(1);
	if(!static_cast<bool>(segment)){
		return(-1);
	}
	//2.�жϵ�ǰ��Ϣ�е�һ�����Ƿ�ΪMSH�Σ�������Ϣ�У���һ����һ��ΪMSH�Σ���
	if(HL7MSHSegment::SegmentName!=segment->get_name()){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
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
int HL7Message::set_segment(const unsigned int no,const String &content){
	//1.�����ǰ���Ρ���Ϊһ��
	if(1==no){
		//1-1.������һ����ʵ����HL7��Ϣ�У���һ���ξ�ΪMSH�Σ���
		PtrToSegment segment(new HL7MSHSegment);
		//1-2.�жϵ�һ����ʵ�������Ƿ�ɹ���
		if(!static_cast<bool>(segment)){
			return(-1);
		}
		//1-2.���ݵ�ǰ�ε����ݣ�Ϊָ��������������ݡ�
		if(dynamic_cast<HL7MSHSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-2);
		}
		//1-3.�����ɵĶΣ����뵽��ǰ��Ϣ�С�
		if(add_segment(segment)<0){
			return(-3);
		}
		//1-4.�������е��˳ɹ����ء�
		return(1);
	}
	//2.�����ǰ�κŴ���һ��
	else if(no>1){//���ԡ�
		return(0);
	}
	//3.�����ǰ�κ�Ϊ�����쳣�����
	else{
		return(-4);
	}
}