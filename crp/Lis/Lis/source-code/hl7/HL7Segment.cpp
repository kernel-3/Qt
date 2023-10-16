#include"stdafx.h"
#include"HL7Segment.h"
#include<algorithm>

//��ʼ��ȫ�ֱ�����
const Char HL7Segment::END_CHARACTER=0x0D;
const Char HL7Segment::FIELD_SEPARATOR=Text('|');
const Char HL7Segment::GROUP_SEPARATOR=Text('^');

/**
 * name: HL7Segment
 * brief: ���캯����
 * param: name - ���Ρ�����
 *        field_amount - ���Ρ��а������򡱵�������
 * return: --
 */
HL7Segment::HL7Segment(const String &name,const unsigned int field_amount)
	:_name(name)
	,_field_amount(field_amount){
}

/**
 * name: ~HL7Segment
 * brief: ����������
 * param: --
 * return: --
 */
HL7Segment::~HL7Segment(void){
}

/**
 * name: get_name
 * brief: ��ȡ��ǰ���Ρ������ơ�
 * param: --
 * return: ���ص�ǰ���Ρ������ơ�
 */
const String &HL7Segment::get_name() const{
	return(_name);
}

/**
 * name: get_field_amount
 * brief: ��ȡ��ǰ���Ρ��С��򡱵�������
 * param: --
 * return: ���ص�ǰ���Ρ��С��򡱵�������
 */
unsigned int HL7Segment::get_field_amount() const{
	return(_field_amount);
}

/**
 * name: from_hl7
 * brief: ����ָ����HL7���Ρ���䣬���ɡ��Ρ����е�������ݡ�
 * param: hl7 - HL7���Ρ��ַ�����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7Segment::from_hl7(const String &hl7){
	//1.�жϵ�ǰ���Ρ��ַ����Ƿ�Ϊ�գ����Ϊ��ֱ�ӷ��ش���
	const int size=hl7.GetLength();
	if(size<=0){
		return(-1);
	}
	//2.�����ǰ���Ρ��ַ���û����ֹ�ַ�����ֱ�ӷ��ش���
	if(END_CHARACTER!=hl7[size-1]){
		return(-2);
	}
	//3.�����ǰ���Ρ�����ĸ������Ϸ�����ֱ�ӷ��ش���
	if(static_cast<int>(_field_amount)!=std::count(
		static_cast<const Char *>(hl7),static_cast<
		const Char *>(hl7)+size,FIELD_SEPARATOR)){
		return(-3);
	}
	//4.�������Ρ��ַ�������ȡ���и��������ݽ��з��롣
	//4-1.������ǰ�������������
	int start_index=0;//��¼��ǰ�������Ρ��ַ�������ʼλ�á�
	int end_index=0;//��¼��ǰ�������Ρ��ַ����Ľ���λ�á�
	//4-2.�������Ρ��ַ�������ȡ���Ρ��С��򡱵����ݡ�
	for(unsigned int index=1;index<=_field_amount;++index){
		//4-2-1.���㵱ǰ���򡱵Ľ���λ��
		end_index=hl7.Find(FIELD_SEPARATOR,start_index);
		//4-2-2.������㡰�򡱵Ľ���λʧ�ܣ���ֱ�ӷ��ش���
		if((end_index<0)||(end_index<start_index)){
			return(-4);
		}
		//4-2-3.��ȡ��ǰ�����е����ݡ�
		const String field_content=hl7.Mid(start_index,
			end_index-start_index);
		//4-2-4.���¼�����ʼλ�á�
		start_index=end_index+1;
		//4-2-5.���������õ���ǰ�����У������ж������Ƿ�ɹ���
		if(set_field(index,field_content)<0){
			return(-5);
		}
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: to_hl7
 * brief: ����ǰ���Ρ�ת����HL7�ַ�����
 * param: --
 * return: ����ת�����HL7�ַ�����
 */
String HL7Segment::to_hl7() const{
	//1.������ǰ�������������
	String hl7_statement(Text(""));
	//2.�������Ρ��ġ��򡱣����á�����������HL7�ַ�����
	//2-1.���ӡ��Ρ��С��򡱵����ݣ������á��򡱷ָ���������
	for(unsigned int index=1;index<=_field_amount;++index){
		//2-1-1.������ǰ�������������
		String content(Text(""));
		//2-1-2.��ȡ��ǰ���򡱵����ݡ�
		if(get_field(index,content)<0){
			return(Text(""));
		}
		//2-1-3.�����γ�HL7�ַ�����
		hl7_statement+=content;//��ӡ��򡱵����ݡ�
		hl7_statement+=FIELD_SEPARATOR;//��ӡ��򡱷ָ�����
	}
	//2-2.��ӡ��Ρ��Ľ����ַ���
	hl7_statement+=END_CHARACTER;
	//3.�������е��˷���HL7�ַ�����
	return(hl7_statement);
}

/**
 * name: extract_group_content_from_field_content
 * brief: ��һ��ָ�����򡱵������У���ȡ���顱�����ݡ�
 * param: field_content - ׼�������ġ��򡱵����ݡ�
 *        group_content - ���صġ��顱�����ݣ���������һ������ָ�룩��
 *        group_content_amount - ���顱���ݵ�������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7Segment::extract_group_content_from_field_content(const String &field_content,
	String *group_content,const unsigned int group_content_amount) const{
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((0==group_content)||(0==group_content_amount)){
		return(-1);
	}
	//2.���㵱ǰ���顱�ָ���������������жϷָ�������Ƿ�Ϸ���
	//2-1.���㵱ǰ���ݡ������ݵĳߴ硣
	const unsigned int field_content_size=field_content.GetLength();
	//2-2.���㵱ǰ���顱�ָ��������
	const unsigned int group_separator_amount=std::count(static_cast<const Char *>(
		field_content),static_cast<const Char *>(field_content)+field_content_size,
		GROUP_SEPARATOR);
	//2-3.�����ǰ���顱�ָ���������Ϸ���
	if((group_content_amount-1)!=group_separator_amount){
		return(-2);
	}
	//3.������ϡ��򡱵����ݣ�������ȡ���顱���ݡ�
	//3-1.������ǰ�������������
	int start_index=0;//��¼��ǰ�����������ݵ���ʼλ�á�
	int end_index=0;//��¼��ǰ�����������ݵĽ���λ�á�
	//3-2.�������򡱵����ݣ���ȡ�����С��顱�����ݡ�
	for(unsigned int index=0;index<group_content_amount;++index){
		//3-2-1.���ҵ�ǰ���顱���ݵĽ���λ��
		end_index=field_content.Find(GROUP_SEPARATOR,start_index);
		//3-2-2.������ҡ��顱���ݵĽ���λʧ�ܣ�����Ϊ��ǰ���򡱵������в������顱�ָ����
		if((end_index<0)||(end_index<start_index)){
			end_index=field_content_size;
		}
		//3-2-3.��ȡ��ǰ�����С��顱�����ݣ��������ݷ��ء�
		if(1==group_content_amount){
			*group_content=field_content.Mid(
				start_index,end_index-start_index);
		}else{
			group_content[index]=field_content.Mid(
				start_index,end_index-start_index);
		}
		//3-2-4.���¼�����ʼλ�á�
		start_index=end_index+1;
	}
	//4.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7Segment::set_field(const unsigned int no,const String &content){
	//1.�����ǰ���򡱱��Ϊ1������С��򡱵����á�
	if(1==no){
		//1-1.����������óɹ���
		if(_name==content){
			return(1);
		}
		//1-2.�����������ʧ�ܡ�
		else{
			return(-1);
		}
	}
	//2.�����ǰ���򡱵ı�Ŵ���1������Ե�ǰ���ò�����
	else if(no>1){
		return(0);
	}
	//3.�����ǰ���򡱵ı��Ϊ�����쳣�����
	else{
		return(-2);
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
int HL7Segment::get_field(const unsigned int no,String &content) const{
	//1.�����ǰ���򡱱��Ϊ1������С������ݵĻ�ȡ��
	if(1==no){
		//1-1.��ȡ��ǰ���򡱵����ݡ�
		content=_name;
		//1-2.�������е��˳ɹ����ء�
		return(1);
	}
	//2.�����ǰ���򡱵ı�Ŵ���1������Ե�ǰ���ò�����
	else if(no>1){
		return(0);
	}
	//3.�����ǰ���򡱵ı��Ϊ�����쳣�����
	else{
		return(-2);
	}
}