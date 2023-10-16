#include"stdafx.h"
#include"HL7ERRSegment.h"

//��ʼ����̬ȫ�ֱ�����
const String HL7ERRSegment::SegmentName(Text("ERR"));

/**
 * name: HL7ERRSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7ERRSegment::HL7ERRSegment(void)
	:HL7Segment(SegmentName,2)
	,_error_code_and_location(Text("")){
}

/**
 * name: ~HL7ERRSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7ERRSegment::~HL7ERRSegment(void){
}

/**
 * name: set_error_code_and_location
 * brief: ���ô��������λ�á�
 * param: error_code_and_location - ���������λ�á�
 * return: --
 */
void HL7ERRSegment::set_error_code_and_location(
	const String &error_code_and_location){
	_error_code_and_location=error_code_and_location;
}

/**
 * name: get_error_code_and_location
 * brief: ��ȡ���������λ�á�
 * param: --
 * return: ���ش��������λ�á�
 */
const String &HL7ERRSegment::get_error_code_and_location() const{
	return(_error_code_and_location);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7ERRSegment::set_field(const unsigned int no,const String &content){
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
		if((Text("0")!=content)&&(Text("100")!=content)&&
			(Text("101")!=content)&&(Text("102")!=content)&&
			(Text("103")!=content)&&(Text("200")!=content)&&
			(Text("201")!=content)&&(Text("202")!=content)&&
			(Text("203")!=content)&&(Text("204")!=content)&&
			(Text("205")!=content)&&(Text("206")!=content)&&
			(Text("207")!=content)){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_error_code_and_location=content;
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
int HL7ERRSegment::get_field(const unsigned int no,String &content) const{
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
		if((Text("0")!=_error_code_and_location)&&
			(Text("100")!=_error_code_and_location)&&
			(Text("101")!=_error_code_and_location)&&
			(Text("102")!=_error_code_and_location)&&
			(Text("103")!=_error_code_and_location)&&
			(Text("200")!=_error_code_and_location)&&
			(Text("201")!=_error_code_and_location)&&
			(Text("202")!=_error_code_and_location)&&
			(Text("203")!=_error_code_and_location)&&
			(Text("204")!=_error_code_and_location)&&
			(Text("205")!=_error_code_and_location)&&
			(Text("206")!=_error_code_and_location)&&
			(Text("207")!=_error_code_and_location)){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_error_code_and_location;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-3);
	}
}