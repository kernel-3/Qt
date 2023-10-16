#include"stdafx.h"
#include"HL7OBXSegment.h"
#include"../tool/DataConverter.h"
#include<assert.h>

//��ʼ��ȫ�ֱ�����
const String HL7OBXSegment::SegmentName(Text("OBX"));

/**
 * name: HL7OBXSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7OBXSegment::HL7OBXSegment(void)
	:HL7Segment(SegmentName,18)
	,_segment_id(Text(""))
	,_test_result_type(Text(""))
	,_item_no(Text(""))
	,_item_name(Text(""))
	,_quantitative_test_result(Text(""))
	,_test_result_unit(Text(""))
	/*,_normal_test_result_range[2]*/
	,_abnormal_flags(Text(""))
	,_qualitative_test_result(Text(""))
	,_qualitative_reference_value(Text(""))
	,_test_result_status(Text("F"))
	,_original_test_result(Text(""))
	,_test_date_time(Text(""))
	,_test_department(Text(""))
	,_test_physician(Text("")){
}

/**
 * name: ~HL7OBXSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7OBXSegment::~HL7OBXSegment(void){
}

/**
 * name: set_segment_id
 * brief: ���ö�ID��
 * param: segment_id - ��ID��
 * return: --
 */
void HL7OBXSegment::set_segment_id(const String &segment_id){
	_segment_id=segment_id;
}

/**
 * name: get_segment_id
 * brief: ��ȡ��ID��
 * param: --
 * return: ���ض�ID��
 */
const String &HL7OBXSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_segment_id_with_number
 * brief: ��������ʽ���ö�ID��
 * param: segment_id - ��ID��
 * return: --
 */
void HL7OBXSegment::set_segment_id_with_number(const unsigned int segment_id){
	_segment_id=DataConverter::to_string(segment_id);
}

/**
 * name: get_segment_id_with_number
 * brief: ��������ʽ��ȡ��ID��
 * param: --
 * return: �������ִ�гɹ����ض�ID�����򷵻��㡣
 */
const unsigned int HL7OBXSegment::get_segment_id_with_number() const{
	return(DataConverter::to_unsigned_int(_segment_id));
}

/**
 * name: set_test_result_type
 * brief: ���ò��Խ�����͡�
 * param: test_result_type - ���Խ�����͡�
 * return: --
 */
void HL7OBXSegment::set_test_result_type(const String &test_result_type){
	_test_result_type=test_result_type;
}

/**
 * name: get_test_result_type
 * brief: ��ȡ���Խ�����͡�
 * param: --
 * return: ���ز��Խ�����͡�
 */
const String &HL7OBXSegment::get_test_result_type() const{
	return(_test_result_type);
}

/**
 * name: set_item_no
 * brief: ������Ŀ��š�
 * param: item_no - ��Ŀ��š�
 * return: --
 */
void HL7OBXSegment::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: ��ȡ��Ŀ��š�
 * param: --
 * return: ������Ŀ��š�
 */
const String &HL7OBXSegment::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: ������Ŀ���ơ�
 * param: item_name - ��Ŀ���ơ�
 * return: --
 */
void HL7OBXSegment::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: ��ȡ��Ŀ���ơ�
 * param: --
 * return: ������Ŀ���ơ�
 */
const String &HL7OBXSegment::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_quantitative_test_result
 * brief: ���ö����Ĳ��Խ����
 * param: quantitative_test_result - �����Ĳ��Խ����
 * return: --
 */
void HL7OBXSegment::set_quantitative_test_result(const String &quantitative_test_result){
	_quantitative_test_result=quantitative_test_result;
}

/**
 * name: get_quantitative_test_result
 * brief: ��ȡ�����Ĳ��Խ����
 * param: --
 * return: ���ض����Ĳ��Խ����
 */
const String &HL7OBXSegment::get_quantitative_test_result() const{
	return(_quantitative_test_result);
}

/**
 * name: set_test_result_unit
 * brief: ���ô�������λ��
 * param: test_result_unit - ���Խ����λ��
 * return: --
 */
void HL7OBXSegment::set_test_result_unit(const String &test_result_unit){
	_test_result_unit=test_result_unit;
}

/**
 * name: get_test_result_unit
 * brief: ��ȡ���Խ����λ��
 * param: --
 * return: ���ش�������λ��
 */
const String &HL7OBXSegment::get_test_result_unit() const{
	return(_test_result_unit);
}

/**
 * name: set_normal_test_result_range
 * brief: �����������Խ����Χ��
 * param: index - ������š�
 *        normal_test_result_range - �������Խ����Χ��
 * return: --
 */
void HL7OBXSegment::set_normal_test_result_range(
	const unsigned int index,const String &normal_test_result_range){
	assert((index>=0)&&(index<2));
	_normal_test_result_range[index]=normal_test_result_range;
}

/**
 * name: get_normal_test_result_range
 * brief: ��ȡ�������Խ����Χ��
 * param: --
 * return: �����������Խ����Χ��
 */
const String &HL7OBXSegment::get_normal_test_result_range(
	const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_normal_test_result_range[index]);
}

/**
 * name: set_abnormal_flags
 * brief: �����쳣��־��
 * param: abnormal_flags - �쳣��־��
 * return: --
 */
void HL7OBXSegment::set_abnormal_flags(const String &abnormal_flags){
	_abnormal_flags=abnormal_flags;
}

/**
 * name: get_abnormal_flags
 * brief: ��ȡ�쳣��־��
 * param: --
 * return: �����쳣��־��
 */
const String &HL7OBXSegment::get_abnormal_flags() const{
	return(_abnormal_flags);
}

/**
 * name: set_qualitative_test_result
 * brief: ���ö��Բ��Խ����
 * param: qualitative_test_result - ���Բ��Խ����
 * return: --
 */
void HL7OBXSegment::set_qualitative_test_result(const String &qualitative_test_result){
	_qualitative_test_result=qualitative_test_result;
}

/**
 * name: get_qualitative_test_result
 * brief: ��ȡ���Բ��Խ����
 * param: --
 * return: ���ض��Բ��Խ����
 */
const String &HL7OBXSegment::get_qualitative_test_result() const{
	return(_qualitative_test_result);
}

/**
 * name: set_qualitative_reference_value
 * brief: ���ö��Բο�ֵ��
 * param: qualitative_reference_value - ���Բο�ֵ��
 * return: --
 */
void HL7OBXSegment::set_qualitative_reference_value(const String &qualitative_reference_value){
	_qualitative_reference_value=qualitative_reference_value;
}

/**
 * name: get_qualitative_reference_value
 * brief: ��ȡ���Բο�ֵ��
 * param: --
 * return: ���ض��Բο�ֵ��
 */
const String &HL7OBXSegment::get_qualitative_reference_value() const{
	return(_qualitative_reference_value);
}

/**
 * name: get_test_result_status
 * brief: ��ȡ���Խ��״̬��
 * param: --
 * return: ���ز��Խ��״̬��
 */
const String &HL7OBXSegment::get_test_result_status() const{
	return(_test_result_status);
}

/**
 * name: set_original_test_result
 * brief: ����ԭʼ���Խ����
 * param: original_test_result - ԭʼ���Խ����
 * return: --
 */
void HL7OBXSegment::set_original_test_result(const String &original_test_result){
	_original_test_result=original_test_result;
}

/**
 * name: get_original_test_result
 * brief: ��ȡԭʼ���Խ����
 * param: --
 * return: ����ԭʼ���Խ����
 */
const String &HL7OBXSegment::get_original_test_result() const{
	return(_original_test_result);
}

/**
 * name: set_test_date_time
 * brief: ���ò�������ʱ�䡣
 * param: test_date_time - ��������ʱ�䡣
 * return: --
 */
void HL7OBXSegment::set_test_date_time(const String &test_date_time){
	_test_date_time=test_date_time;
}

/**
 * name: get_test_date_time
 * brief: ��ȡ��������ʱ�䡣
 * param: --
 * return: ���ز�������ʱ�䡣
 */
const String &HL7OBXSegment::get_test_date_time() const{
	return(_test_date_time);
}

/**
 * name: set_test_department
 * brief: ���ü�����ҡ�
 * param: test_department - ������ҡ�
 * return: --
 */
void HL7OBXSegment::set_test_department(const String &test_department){
	_test_department=test_department;
}

/**
 * name: get_test_department
 * brief: ��ȡ������ҡ�
 * param: --
 * return: ���ؼ�����ҡ�
 */
const String &HL7OBXSegment::get_test_department() const{
	return(_test_department);
}

/**
 * name: set_test_physician
 * brief: ���ü���ҽ����
 * param: test_physician - ����ҽ����
 * return: --
 */
void HL7OBXSegment::set_test_physician(const String &test_physician){
	_test_physician=test_physician;
}

/**
 * name: get_test_physician
 * breif: ��ȡ����ҽ����
 * param: --
 * return: ���ؼ���ҽ����
 */
const String &HL7OBXSegment::get_test_physician() const{
	return(_test_physician);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7OBXSegment::set_field(const unsigned int no,const String &content){
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
	else if(3==no){
		//3-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((Text("NM")!=content)&&(Text("ST")!=content)){
			return(-3);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		_test_result_type=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(content.IsEmpty()){
			//unfinished: �˴��Ƿ���Ҫ�ж���Ŀ���Ϊ���֣�����
			return(-4);
		}
		//4-2.���õ�ǰ���򡱵����ݡ�
		_item_no=content;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.���õ�ǰ���򡱵����ݡ�
		_item_name=content;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((Text("NM")==_test_result_type)&&
			(content.IsEmpty())){
			//unfinished: �����Ƿ�Ӧ���жϵ�ǰ���Խ������Ϊ����ʱ����ֵһ��Ϊ�ա�
			return(-5);
		}
		//6-2.���õ�ǰ���򡱵����ݡ�
		_quantitative_test_result=content;
		//6-3.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.���õ�ǰ���򡱵����ݡ�
		_test_result_unit=content;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.������ǰ�������������
		String group_content[2];
		//8-2.��ȡ��ǰ׼�����á��򡱵������еġ��顱���ݡ�
		if(extract_group_content_from_field_content(
			content,group_content,2)<0){
			return(-6);
		}
		//8-3.�жϵ�ǰ���顱�������Ƿ�Ϸ���
		if(!(((group_content[0].IsEmpty())&&(group_content[1].IsEmpty()))||
			((!group_content[0].IsEmpty())&&(!group_content[1].IsEmpty())))){
			//unfinished: �����Ƿ�Ӧ���жϷ�Χ�Ĵ�С˳���Լ��Ƿ�Ϊ���֣�������
			return(-7);
		}
		//8-4.���õ�ǰ���򡱵����ݡ�
		_normal_test_result_range[0]=group_content[0];
		_normal_test_result_range[1]=group_content[1];
		//8-5.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((!content.IsEmpty())&&(Text("L")!=content)&&
			(Text("H")!=content)&&(Text("N")!=content)){
			return(-8);
		}
		//9-2.���õ�ǰ���򡱵����ݡ�
		_abnormal_flags=content;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((Text("ST")==_test_result_type)&&
			(content.IsEmpty())){
			return(-9);
		}
		//10-2.���õ�ǰ���򡱵����ݡ�
		_qualitative_test_result=content;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ�������á��Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.���õ�ǰ���򡱵����ݡ�
		_qualitative_reference_value=content;
		//11-2.�������е��˳ɹ����ء�
		return(1);
	}
	//12.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("F")!=content){
			return(-10);
		}
		//12-2.���õ�ǰ���򡱵����ݡ�
		//_test_result_status=content;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//unfinished: �˴��Ƿ���Ҫ�ж�ԭʼ���Ϊ���룬�Լ���ֵΪ���֣�����
		//14-1.���õ�ǰ���򡱵����ݡ�
		_original_test_result=content;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-11);
		}
		//15-2.���õ�ǰ���򡱵����ݡ�
		_test_date_time=content;
		//15-3.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.���õ�ǰ���򡱵����ݡ�
		_test_department=content;
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.���õ�ǰ���򡱵����ݡ�
		_test_physician=content;
		//17-2.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){//���ԡ�
		return(0);
	}
	//19.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-12);
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
int HL7OBXSegment::get_field(const unsigned int no,String &content) const{
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
	else if(3==no){
		//3-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((Text("NM")!=_test_result_type)&&
			(Text("ST")!=_test_result_type)){
			return(-3);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_test_result_type;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(_item_no.IsEmpty()){
			//unfinished: �˴��Ƿ���Ҫ�ж���Ŀ���Ϊ���֣�����
			return(-4);
		}
		//4-2.��ȡ��ǰ���򡱵����ݡ�
		content=_item_no;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.��ȡ��ǰ���򡱵����ݡ�
		content=_item_name;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((Text("NM")==_test_result_type)&&
			(_quantitative_test_result.IsEmpty())){
			//unfinished: �����Ƿ�Ӧ���жϵ�ǰ���Խ������Ϊ����ʱ����ֵһ��Ϊ�ա�
			return(-5);
		}
		//6-2.��ȡ��ǰ���򡱵����ݡ�
		content=_quantitative_test_result;
		//6-3.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.��ȡ��ǰ���򡱵����ݡ�
		content=_test_result_unit;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(!(((_normal_test_result_range[0].IsEmpty())&&
			(_normal_test_result_range[1].IsEmpty()))||
			((!_normal_test_result_range[0].IsEmpty())&&
			(!_normal_test_result_range[1].IsEmpty())))){
			//unfinished: �����Ƿ�Ӧ���жϷ�Χ�Ĵ�С˳���Լ��Ƿ�Ϊ���֣�������
			return(-6);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		String content_t(Text(""));
		content_t+=_normal_test_result_range[0];
		content_t+=HL7Segment::GROUP_SEPARATOR;
		content_t+=_normal_test_result_range[1];
		content=content_t;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((!_abnormal_flags.IsEmpty())&&
			(Text("L")!=_abnormal_flags)&&
			(Text("H")!=_abnormal_flags)&&
			(Text("N")!=_abnormal_flags)){
			return(-7);
		}
		//9-2.��ȡ��ǰ���򡱵����ݡ�
		content=_abnormal_flags;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((Text("ST")==_test_result_type)&&
			(_qualitative_test_result.IsEmpty())){
			return(-8);
		}
		//10-2.��ȡ��ǰ���򡱵����ݡ�
		content=_qualitative_test_result;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.��ȡ��ǰ���򡱵����ݡ�
		content=_qualitative_reference_value;
		//11-2.�������е��˳ɹ����ء�
		return(1);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("F")!=_test_result_status){
			return(-9);
		}
		//12-2.��ȡ��ǰ���򡱵����ݡ�
		content=_test_result_status;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//unfinished: �˴��Ƿ���Ҫ�ж�ԭʼ���Ϊ���룬�Լ���ֵΪ���֣�����
		//14-1.��ȡ��ǰ���򡱵����ݡ�
		content=_original_test_result;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((!_test_date_time.IsEmpty())&&
			((14!=_test_date_time.GetLength())||
			(!DataConverter::is_number(_test_date_time)))){
			return(-10);
		}
		//15-2.��ȡ��ǰ���򡱵����ݡ�
		content=_test_date_time;
		//15-3.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.��ȡ��ǰ���򡱵����ݡ�
		content=_test_department;
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.��ȡ��ǰ���򡱵����ݡ�
		content=_test_physician;
		//17-2.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){//���ԡ�
		return(0);
	}
	//19.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-12);
	}
}