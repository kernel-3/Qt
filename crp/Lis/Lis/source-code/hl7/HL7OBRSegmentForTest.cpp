#include"stdafx.h"
#include"HL7OBRSegmentForTest.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForTest
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7OBRSegmentForTest::HL7OBRSegmentForTest(void)
	:HL7OBRSegment()
	,_specimen_barcode(Text(""))
	,_specimen_no(Text(""))
	//,_universal_service_id(Text(""))
	,_is_emergency(Text(""))
	,_specimen_collect_date_time(Text(""))
	,_specimen_test_date_time(Text(""))
	,_dilution_ratio(Text(""))
	//,_specimen_position(Text(""))
	,_relevant_clinical_info(Text(""))
	,_specimen_received_date_time(Text(""))
	,_specimen_category(Text(""))
	,_submitting_physician(Text(""))
	,_submitting_department(Text(""))
	,_specimen_shape_and_properties(Text(""))
	,_blood_bag_no(Text(""))
	,_physician_in_charge(Text(""))
	,_department_in_charge(Text("")){
}

/**
 * name: ~HL7OBRSegmentForTest
 * brief: ����������
 * param: --
 * return: --
 */
HL7OBRSegmentForTest::~HL7OBRSegmentForTest(void){
}

/**
 * name: set_specimen_barcode
 * brief: �����������롣
 * param: specimen_barcode - �������롣
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_barcode(const String &specimen_barcode){
	_specimen_barcode=specimen_barcode;
}

/**
 * name: get_specimen_barcode
 * brief: ��ȡ�������롣
 * param: --
 * return: �����������롣
 */
const String &HL7OBRSegmentForTest::get_specimen_barcode() const{
	return(_specimen_barcode);
}

/**
 * name: set_specimen_no
 * brief: ����������š�
 * param: specimen_no - ������š�
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_no(const String &specimen_no){
	_specimen_no=specimen_no;
}

/**
 * name: get_specimen_no
 * breif: ��ȡ������š�
 * param: --
 * return: ����������š�
 */
const String &HL7OBRSegmentForTest::get_specimen_no() const{
	return(_specimen_no);
}

/**
 * name: set_universal_service_id
 * brief: ����ָ����ͨ�÷����ʶ����
 * param: index - ͨ�÷����ʾ��������š�
 *        universal_service_id - ͨ�÷����ʶ����
 * return: --
 */
void HL7OBRSegmentForTest::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: ��ȡָ����ͨ�÷����ʶ����
 * param: index - ͨ�÷����ʾ��������š�
 * return: ����ָ����ͨ�÷����ʶ����
 */
const String &HL7OBRSegmentForTest::get_universal_service_id(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_is_emergency
 * brief: �����Ƿ�Ϊ���
 * param: is_emergency - �Ƿ�Ϊ���
 * return: --
 */
void HL7OBRSegmentForTest::set_is_emergency(const String &is_emergency){
	_is_emergency=is_emergency;
}

/**
 * name: get_is_emergency
 * brief: ��ȡ�Ƿ�Ϊ���
 * param: --
 * return: �����Ƿ�Ϊ���
 */
const String &HL7OBRSegmentForTest::get_is_emergency() const{
	return(_is_emergency);
}

/**
 * name: set_specimen_collect_date_time
 * brief: ���������ɼ�����ʱ�䡣
 * param: specimen_collect_date_time - �����ɼ�����ʱ�䣨��ʽ��20150122102330����
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_collect_date_time(const String &specimen_collect_date_time){
	_specimen_collect_date_time=specimen_collect_date_time;
}

/**
 * name: get_specimen_collect_date_time
 * brief: ��ȡ�����ɼ�����ʱ�䡣
 * param: --
 * return: ���������ɼ�����ʱ�䡣
 */
const String &HL7OBRSegmentForTest::get_specimen_collect_date_time() const{
	return(_specimen_collect_date_time);
}

/**
 * name: set_specimen_test_date_time
 * brief: ����������������ʱ�䡣
 * param: specimen_test_date_time - ������������ʱ�䡣
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_test_date_time(const String &specimen_test_date_time){
	_specimen_test_date_time=specimen_test_date_time;
}

/**
 * name: get_specimen_test_date_time
 * brief: ��ȡ������������ʱ�䡣
 * param: --
 * return: ����������������ʱ�䡣
 */
const String &HL7OBRSegmentForTest::get_specimen_test_date_time() const{
	return(_specimen_test_date_time);
}

/**
 * name: set_dilution_ratio
 * breif: ����ϡ�ͱ�����
 * param: dilution_ratio - ϡ�ͱ�����
 * return: --
 */
void HL7OBRSegmentForTest::set_dilution_ratio(const String &dilution_ratio){
	_dilution_ratio=dilution_ratio;
}

/**
 * name: get_dilution_ratio
 * breif: ��ȡϡ�ͱ�����
 * param: --
 * return: ����ϡ�ͱ�����
 */
const String &HL7OBRSegmentForTest::get_dilution_ratio() const{
	return(_dilution_ratio);
}

/**
 * name: set_specimen_position
 * breif: ��������λ�á�
 * param: index - ������š�
 *        specimen_position - ����λ�á�
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_position(
	const unsigned int index,const String &specimen_position){
	assert((index>=0)&&(index<2));
	_specimen_position[index]=specimen_position;
}

/**
 * name: get_specimen_position
 * breif: ��ȡ����λ�á�
 * param: index - ������š�
 * return: ��������λ�á�
 */
const String &HL7OBRSegmentForTest::get_specimen_position(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_specimen_position[index]);
}

/**
 * name: set_relevant_clinical_info
 * breif: ��������ٴ���Ϣ��
 * param: relevant_clinical_info - ����ٴ���Ϣ��
 * return: --
 */
void HL7OBRSegmentForTest::set_relevant_clinical_info(const String &relevant_clinical_info){
	_relevant_clinical_info=relevant_clinical_info;
}

/**
 * name: get_relevant_clinical_info
 * breif: ��ȡ����ٴ���Ϣ��
 * param: --
 * return: ��������ٴ���Ϣ��
 */
const String &HL7OBRSegmentForTest::get_relevant_clinical_info() const{
	return(_relevant_clinical_info);
}

/**
 * name: set_specimen_received_date_time
 * brief: ���������ͼ�ʱ�䡣
 * param: specimen_received_date_time - �����ͼ�ʱ�䡣
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_received_date_time(const String &specimen_received_date_time){
	_specimen_received_date_time=specimen_received_date_time;
}

/**
 * name: get_specimen_received_date_time
 * brief: ��ȡ�����ͼ�ʱ�䡣
 * param: --
 * return: ���������ͼ�ʱ�䡣
 */
const String &HL7OBRSegmentForTest::get_specimen_received_date_time() const{
	return(_specimen_received_date_time);
}

/**
 * name: set_specimen_category
 * brief: �����������
 * param: specimen_category - �������
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_category(const String &specimen_category){
	_specimen_category=specimen_category;
}

/**
 * name: get_specimen_category
 * brief: ��ȡ�������
 * param: --
 * return: �����������
 */
const String &HL7OBRSegmentForTest::get_specimen_category() const{
	return(_specimen_category);
}

/**
 * name: set_submitting_physician
 * brief: �����ͼ�ҽ����
 * param: submitting_physician - �ͼ�ҽ����
 * return: --
 */
void HL7OBRSegmentForTest::set_submitting_physician(const String &submitting_physician){
	_submitting_physician=submitting_physician;
}

/**
 * name: get_submitting_physician
 * brief: ��ȡ�ͼ�ҽ����
 * param: --
 * return: �����ͼ�ҽ����
 */
const String &HL7OBRSegmentForTest::get_submitting_physician() const{
	return(_submitting_physician);
}

/**
 * name: set_submitting_department
 * breif: �����ͼ���ҡ�
 * param: submitting_department - �ͼ���ҡ�
 * return: --
 */
void HL7OBRSegmentForTest::set_submitting_department(const String &submitting_department){
	_submitting_department=submitting_department;
}

/**
 * name: get_submitting_department
 * breif: ��ȡ�ͼ���ҡ�
 * param: --
 * return: �����ͼ���ҡ�
 */
const String &HL7OBRSegmentForTest::get_submitting_department() const{
	return(_submitting_department);
}

/**
 * name: set_specimen_shape_and_properties
 * breif: ����������״��
 * param: specimen_shape_and_properties
 * return: �����ͼ���ҡ�
 */
void HL7OBRSegmentForTest::set_specimen_shape_and_properties(const String &specimen_shape_and_properties){
	_specimen_shape_and_properties=specimen_shape_and_properties;
}

/**
 * name: get_specimen_shape_and_properties
 * breif: ��ȡ������״��
 * param: --
 * return: ����������״��
 */
const String &HL7OBRSegmentForTest::get_specimen_shape_and_properties() const{
	return(_specimen_shape_and_properties);
}

/**
 * name: set_blood_bag_no
 * brief: ����Ѫ����š�
 * param: blood_bag_no - Ѫ����š�
 * return: --
 */
void HL7OBRSegmentForTest::set_blood_bag_no(const String &blood_bag_no){
	_blood_bag_no=blood_bag_no;
}

/**
 * name: get_blood_bag_no
 * brief: ��ȡѪ����š�
 * param: --
 * return: ����Ѫ����š�
 */
const String &HL7OBRSegmentForTest::get_blood_bag_no() const{
	return(_blood_bag_no);
}

/**
 * name: set_physician_in_charge
 * brief: ��������ҽ����
 * param: physician_in_charge - ����ҽ����
 * return: --
 */
void HL7OBRSegmentForTest::set_physician_in_charge(const String &physician_in_charge){
	_physician_in_charge=physician_in_charge;
}

/**
 * name: get_physician_in_charge
 * brief: ��ȡ����ҽ����
 * param: --
 * return: ��������ҽ����
 */
const String &HL7OBRSegmentForTest::get_physician_in_charge() const{
	return(_physician_in_charge);
}

/**
 * name: set_department_in_charge
 * breif: �������ο��ҡ�
 * param: department_in_charge - ���ο��ҡ�
 * return: --
 */
void HL7OBRSegmentForTest::set_department_in_charge(const String &department_in_charge){
	_department_in_charge=department_in_charge;
}

/**
 * name: get_department_in_charge
 * breif: ��ȡ���ο��ҡ�
 * param: --
 * return: �������ο��ҡ�
 */
const String &HL7OBRSegmentForTest::get_department_in_charge() const{
	return(_department_in_charge);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7OBRSegmentForTest::set_field(const unsigned int no,const String &content){
	//1.���û�����Ӧ��������ָ���ġ��򡱣������ж����ý����
	//1-1.���û�����Ӧ��������ָ���ġ��򡱡�
	const int execute_result=HL7OBRSegment::set_field(no,content);
	//1-2.����ɹ�����ָ���ġ��򡱡�
	if(execute_result>0){
		return(1);
	}
	//1-3.�������ָ���ġ���ʧ�ܡ�
	else if(execute_result<0){
		return(-1);
	}
	//2.���ԡ�
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if(content.IsEmpty()){
			return(-2);
		}
		//unfinished: �Ƿ���Ҫ��⵱ǰ���������Ƿ�Ϊ���֣�����
		//3-2.���õ�ǰ���򡱵����ݡ�
		_specimen_barcode=content;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//unfinished: �Ƿ���Ҫ��⵱ǰ��������Ƿ�Ϊ���֣�����
		//4-1.���õ�ǰ���򡱵����ݡ�
		_specimen_no=content;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.������ǰ�������������
		String contents[2];
		//5-2.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if(extract_group_content_from_field_content(
			content,contents,2)<0){
			return(-3);
		}
		if((contents[0].IsEmpty())||(contents[1].IsEmpty())){
			return(-4);
		}
		//5-3.���õ�ǰ���򡱵����ݡ�
		_universal_service_id[0]=contents[0];
		_universal_service_id[1]=contents[1];
		//5-4.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if((!content.IsEmpty())&&(Text("Y")!=content)&&
			(Text("N")!=content)){
			return(-5);
		}
		//6-2.���õ�ǰ���򡱵����ݡ�
		_is_emergency=content;
		//6-3.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-6);
		}
		//7-2.���õ�ǰ���򡱵����ݡ�
		_specimen_collect_date_time=content;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-7);
		}
		//8-2.���õ�ǰ���򡱵����ݡ�
		_specimen_test_date_time=content;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//unfinished: �����Ƿ���Ҫ�ж�ϡ�ͱ���Ϊ���֣���
		//10-1.���õ�ǰ���򡱵����ݡ�
		_dilution_ratio=content;
		//10-2.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ�������á��Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.������ǰ�������������
		String contents[2];
		//11-2.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if(extract_group_content_from_field_content(
			content,contents,2)<0){
			return(-8);
		}
		if((contents[0].IsEmpty())&&(contents[1].IsEmpty())){
		}else if((!contents[0].IsEmpty())&&(!contents[1].IsEmpty())){
			//unfinished: �����Ƿ���Ҫ�������Ϊ���֣���
		}else{
			return(-9);
		}
		//11-3.���õ�ǰ���򡱵����ݡ�
		_specimen_position[0]=contents[0];
		_specimen_position[1]=contents[1];
		//11-4.�������е��˳ɹ����ء�
		return(1);
	}
	//12.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){//���ԡ�
		return(0);
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.���õ�ǰ���򡱵����ݡ�
		_relevant_clinical_info=content;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-10);
		}
		//15-2.���õ�ǰ���򡱵����ݡ�
		_specimen_received_date_time=content;
		//15-3.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.�жϵ�ǰ׼�����á��򡱵������Ƿ�Ϸ���
		if(content.IsEmpty()){
			return(-11);
		}
		//16-2.���õ�ǰ���򡱵����ݡ�
		_specimen_category=content;
		//16-3.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.���õ�ǰ���򡱵����ݡ�
		_submitting_physician=content;
		//17-1.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.���õ�ǰ���򡱵����ݡ�
		_submitting_department=content;
		//18-1.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ�������á��Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.���õ�ǰ���򡱵����ݡ�
		_specimen_shape_and_properties=content;
		//19-1.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ�������á��Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.���õ�ǰ���򡱵����ݡ�
		_blood_bag_no=content;
		//unfinished: �Ƿ�Ӧ���жϵ�ǰѪ�����Ϊ���֣�����
		//20-1.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ�������á��Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.���õ�ǰ���򡱵����ݡ�
		_physician_in_charge=content;
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22.�����ǰ�������á��Ρ��ĵڶ�ʮ�������򡱡�
	else if(22==no){
		//22-1.���õ�ǰ���򡱵����ݡ�
		_department_in_charge=content;
		//22-2.�������е��˳ɹ����ء�
		return(1);
	}
	//23~48.�����ǰ�������á��Ρ��ĵڶ�ʮ��������ʮ�˸����򡱡�
	else if((no>=23)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ����Ϊ���������򡱣��򷵻ش���
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
int HL7OBRSegmentForTest::get_field(const unsigned int no,String &content) const{
	//1.���û�����Ӧ������ȡָ���ġ��򡱣������жϻ�ȡ�����
	//1-1.���û�����Ӧ������ȡָ���ġ��򡱡�
	const int execute_result=HL7OBRSegment::get_field(no,content);
	//1-2.������û�����Ӧ�����ɹ���ȡָ���ġ��򡱣���ֱ�ӷ��ء�
	if(execute_result>0){
		return(1);
	}
	//1-3.������û�����Ӧ������ȡָ���ġ���ʧ�ܣ���ֱ�ӷ��ء�
	else if(execute_result<0){
		return(-1);
	}
	//2.���ԡ�
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if(_specimen_barcode.IsEmpty()){
			return(-2);
		}
		//unfinished: �Ƿ���Ҫ��⵱ǰ���������Ƿ�Ϊ���֣�����
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_barcode;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//unfinished: �Ƿ���Ҫ��⵱ǰ��������Ƿ�Ϊ���֣�����
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_no;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((_universal_service_id[0].IsEmpty())||
			(_universal_service_id[1].IsEmpty())){
			return(-3);
		}
		//5-2.��ȡ��ǰ���򡱵����ݡ�
		content=_universal_service_id[0];
		content+=GROUP_SEPARATOR;
		content+=_universal_service_id[1];
		//5-3.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if((!_is_emergency.IsEmpty())&&
			(Text("Y")!=_is_emergency)&&
			(Text("N")!=_is_emergency)){
			return(-4);
		}
		//6-2.��ȡ��ǰ���򡱵����ݡ�
		content=_is_emergency;
		//6-3.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if((!_specimen_collect_date_time.IsEmpty())&&
			((14!=_specimen_collect_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_collect_date_time)))){
			return(-5);
		}
		//7-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_collect_date_time;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if((!_specimen_test_date_time.IsEmpty())&&
			((14!=_specimen_test_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_test_date_time)))){
			return(-6);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_test_date_time;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//unfinished: �����Ƿ���Ҫ�ж�ϡ�ͱ���Ϊ���֣���
		//10-1.��ȡ��ǰ���򡱵����ݡ�
		content=_dilution_ratio;
		//10-2.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){
		//11-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((_specimen_position[0].IsEmpty())&&
			(_specimen_position[1].IsEmpty())){
		}else if((!_specimen_position[0].IsEmpty())&&
			(!_specimen_position[1].IsEmpty())){
			//unfinished: �����Ƿ���Ҫ�������Ϊ���֣���
		}else{
			return(-7);
		}
		//11-3.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_position[0];
		content+=GROUP_SEPARATOR;
		content+=_specimen_position[1];
		//11-4.�������е��˳ɹ����ء�
		return(1);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){//���ԡ�
		return(0);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){//���ԡ�
		return(0);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ȡ��ǰ���򡱵����ݡ�
		content=_relevant_clinical_info;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if((!_specimen_received_date_time.IsEmpty())&&
			((14!=_specimen_received_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_received_date_time)))){
			return(-8);
		}
		//15-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_received_date_time;
		//15-3.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.�жϵ�ǰ׼����ȡ���򡱵������Ƿ�Ϸ���
		if(_specimen_category.IsEmpty()){
			return(-9);
		}
		//16-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_category;
		//16-3.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.��ȡ��ǰ���򡱵����ݡ�
		content=_submitting_physician;
		//17-1.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ȡ��ǰ���򡱵����ݡ�
		content=_submitting_department;
		//18-1.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ������ȡ���Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_shape_and_properties;
		//19-1.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.��ȡ��ǰ���򡱵����ݡ�
		content=_blood_bag_no;
		//unfinished: �Ƿ�Ӧ���жϵ�ǰѪ�����Ϊ���֣�����
		//20-1.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ������ȡ���Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.��ȡ��ǰ���򡱵����ݡ�
		content=_physician_in_charge;
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�������򡱡�
	else if(22==no){
		//22-1.��ȡ��ǰ���򡱵����ݡ�
		content=_department_in_charge;
		//22-2.�������е��˳ɹ����ء�
		return(1);
	}
	//23~48.�����ǰ������ȡ���Ρ��ĵڶ�ʮ��������ʮ�˸����򡱡�
	else if((no>=23)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-10);
	}
}