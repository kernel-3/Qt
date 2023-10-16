#include"stdafx.h"
#include"HL7QRDSegment.h"
#include"../tool/DataConverter.h"

//����ȫ�ֱ�����
 const String HL7QRDSegment::SegmentName(Text("QRD"));

/**
 * name: HL7QRDSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7QRDSegment::HL7QRDSegment(void)
	:HL7Segment(SegmentName,13)
	,_query_date_time(Text(""))
	,_query_format_code(Text("R"))
	,_query_priority(Text("D"))
	,_query_id(Text(""))
	,_quantity_limited_request(Text("RD"))
	,_specimen_barcode(Text(""))
	,_what_subject_filter(Text("OTH")){
}

/**
 * name: ~HL7QRDSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7QRDSegment::~HL7QRDSegment(void){
}

/**
 * name: set_query_date_time
 * brief: ���ò�ѯ��������ʱ�䡣
 * param: query_date_time - ��ѯ����ʱ�䡣
 * return: --
 */
void HL7QRDSegment::set_query_date_time(const String &query_date_time){
	_query_date_time=query_date_time;
}

/**
 * name: get_query_date_time
 * brief: ��ȡ��ѯ����ʱ�䡣
 * param: --
 * return: ���ز�ѯ����ʱ�䡣
 */
const String &HL7QRDSegment::get_query_date_time() const{
	return(_query_date_time);
}

/**
 * name: get_query_format_code
 * brief: ��ȡ��ѯ��ʽ���롣
 * param: --
 * return: ���ز�ѯ��ʽ���롣
 */
const String &HL7QRDSegment::get_query_format_code() const{
	return(_query_date_time);
}

/**
 * name: get_query_priority
 * brief: ��ȡ��ѯ����Ȩ��
 * param: --
 * return: ���ز�ѯ����Ȩ��
 */
const String &HL7QRDSegment::get_query_priority() const{
	return(_query_priority);
}

/**
 * name: set_query_id
 * brief: ���ò�ѯID��
 * param: query_id - ��ѯID��
 * return: --
 */
void HL7QRDSegment::set_query_id(const String &query_id){
	_query_id=query_id;
}

/**
 * name: get_query_id
 * brief: ��ȡ��ѯID��
 * param: --
 * return: ���ز�ѯID��
 */
const String &HL7QRDSegment::get_query_id() const{
	return(_query_id);
}

/**
 * name: get_quantity_limited_request
 * brief: ��ȡ��������Ҫ��
 * param: --
 * return: ������������Ҫ��
 */
const String &HL7QRDSegment::get_quantity_limited_request() const{
	return(_quantity_limited_request);
}

/**
 * name: set_specimen_barcode
 * brief: �����������롣
 * param: specimen_barcode - �������롣
 * return: --
 */
void HL7QRDSegment::set_specimen_barcode(const String &specimen_barcode){
	_specimen_barcode=specimen_barcode;
}

/**
 * name: get_specimen_barcode
 * brief: ��ȡ�������롣
 * param: --
 * return: �����������롣
 */
const String &HL7QRDSegment::get_specimen_barcode() const{
	return(_specimen_barcode);
}

/**
 * name: get_what_subject_filter
 * brief: ��ȡ��ѯ���ݹ��˷���
 * param: --
 * return: ���ز�ѯ���ݹ��˷���
 */
const String &HL7QRDSegment::get_what_subject_filter() const{
	return(_what_subject_filter);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7QRDSegment::set_field(const unsigned int no,const String &content){
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
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_query_date_time=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("R")!=content){
			return(-3);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		//_query_format_code=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("D")!=content){
			return(-4);
		}
		//4-2.���õ�ǰ���򡱵����ݡ�
		//_query_priority=content;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(content.IsEmpty()){
			return(-5);
		}
		//5-2.���õ�ǰ���򡱵����ݡ�
		//_query_id=content;
		//5-3.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){//���ԡ�
		return(0);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("RD")!=content){
			return(-6);
		}
		//8-2.���õ�ǰ���򡱵����ݡ�
		//_quantity_limited_request=content;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//unfinished: �����Ƿ���Ҫ�ж����벻Ϊ��ʱ����Ϊ���֣�����
		//9-1.���õ�ǰ���򡱵����ݡ�
		_specimen_barcode=content;
		//9-2.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("OTH")!=content){
			return(-7);
		}
		//10-2.���õ�ǰ���򡱵����ݡ�
		//_what_subject_filter=content;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11~13.�����ǰ�������á��Ρ��ĵ�ʮһ����������ʮ�������򡱡�
	else if((no>=11)&&(no<=13)){//���ԡ�
		return(0);
	}
	//14.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-8);
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
int HL7QRDSegment::get_field(const unsigned int no,String &content) const{
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
		if((!_query_date_time.IsEmpty())&&
			((14!=_query_date_time.GetLength())||
			(!DataConverter::is_number(_query_date_time)))){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_date_time;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("R")!=_query_format_code){
			return(-3);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_format_code;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("D")!=_query_priority){
			return(-4);
		}
		//4-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_priority;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(_query_id.IsEmpty()){
			return(-5);
		}
		//5-2.��ȡ��ǰ���򡱵����ݡ�
		content=_query_id;
		//5-3.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){//���ԡ�
		return(0);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("RD")!=_quantity_limited_request){
			return(-6);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		content=_quantity_limited_request;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//unfinished: �����Ƿ���Ҫ�ж����벻Ϊ��ʱ����Ϊ���֣�����
		//9-1.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_barcode;
		//9-2.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("OTH")!=_what_subject_filter){
			return(-7);
		}
		//10-2.��ȡ��ǰ���򡱵����ݡ�
		content=_what_subject_filter;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11~13.�����ǰ������ȡ���Ρ��ĵ�ʮһ����������ʮ�������򡱡�
	else if((no>=11)&&(no<=13)){//���ԡ�
		return(0);
	}
	//14.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-8);
	}
}