#include"stdafx.h"
#include"HL7OBRSegmentForCalib.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForCalib
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7OBRSegmentForCalib::HL7OBRSegmentForCalib(void)
	:HL7OBRSegment()
	,_item_no(Text(""))
	,_item_name(Text(""))
	/*,_universal_service_id[2]*/
	,_calibration_date_time(Text(""))
	,_calibration_method(Text(""))
	,_calibration_liquid_amount(Text(""))
	/*,_calibration_liquid_no[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_name[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_lot_no[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_period_of_validity[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_standard_concentration[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_concentration_level[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_test_concentration[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	,_calibration_parameter_amount(Text(""))
	/*,_calibration_parameter_value[MAX_CALIBRATION_PARAMETER_AMOUNT]*/{
}

/**
 * name: ~HL7OBRSegmentForCalib
 * brief: ����������
 * param: --
 * return: --
 */
HL7OBRSegmentForCalib::~HL7OBRSegmentForCalib(void){
}

/**
 * name: set_item_no
 * brief: ������Ŀ��š�
 * param: item_no - ��Ŀ��š�
 * return: --
 */
void HL7OBRSegmentForCalib::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: ��ȡ��Ŀ��š�
 * param: --
 * return: ������Ŀ��š�
 */
const String &HL7OBRSegmentForCalib::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: ������Ŀ���ơ�
 * param: item_name - ��Ŀ���ơ�
 * return: --
 */
void HL7OBRSegmentForCalib::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: ��ȡ��Ŀ���ơ�
 * param: --
 * return: ������Ŀ���ơ�
 */
const String &HL7OBRSegmentForCalib::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_universal_service_id
 * brief: ����ͨ�÷����ʶ����
 * param: index - ������š�
 *        universal_service_id - ͨ�÷����ʶ����
 * return: --
 */
void HL7OBRSegmentForCalib::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: ��ȡͨ�÷����ʶ����
 * param: index - ������š�
 * return: ����ͨ�÷����ʶ����
 */
const String &HL7OBRSegmentForCalib::get_universal_service_id(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_calibration_date_time
 * brief: ���ö�������ʱ�䡣
 * param: calibration_date_time - ��������ʱ�䡣
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_date_time(const String &calibration_date_time){
	_calibration_date_time=calibration_date_time;
}

/**
 * name: get_calibration_date_time
 * brief: ��ȡ��������ʱ�䡣
 * param: --
 * return: ���ض�������ʱ�䡣
 */
const String &HL7OBRSegmentForCalib::get_calibration_date_time() const{
	return(_calibration_date_time);
}

/**
 * name: set_calibration_method
 * brief: ���ö��귽����
 * param: calibration_method - ���귽����
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_method(const String &calibration_method){
	_calibration_method=calibration_method;
}

/**
 * name: get_calibration_method
 * brief: ��ȡ���귽����
 * param: --
 * return: ���ض��귽����
 */
const String &HL7OBRSegmentForCalib::get_calibration_method() const{
	return(_calibration_method);
}

/**
 * name: set_calibration_method_with_number
 * brief: �����������ö��귽����
 * param: calibration_method - ���귽����
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_method_with_number(const unsigned int calibration_method){
	_calibration_method=DataConverter::to_string(calibration_method);
}

/**
 * name: get_calibration_method_with_number
 * breif: ��ȡ���귽��������������
 * param: --
 * return: �������ִ�гɹ����ض��귽�����������������򷵻��㡣
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_method_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_method));
}

/**
 * name: set_calibration_liquid_amount
 * brief: ���ö���Һ������
 * param: calibration_liquid_amount - ����Һ������
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_amount(const String &calibration_liquid_amount){
	_calibration_liquid_amount=calibration_liquid_amount;
}

/**
 * name: get_calibration_liquid_amount
 * brief: ��ȡ����Һ������
 * param: --
 * return: ���ض���Һ������
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_amount() const{
	return(_calibration_liquid_amount);
}

/**
 * name: set_calibration_liquid_amount_with_number
 * breif: ͨ���������ö���Һ��������
 * param: calibration_liquid_amount - ����Һ������
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_amount_with_number(const unsigned int calibration_liquid_amount){
	_calibration_liquid_amount=DataConverter::to_string(calibration_liquid_amount);
}

/**
 * name: get_calibration_liquid_amount_width_number
 * brief: ��ȡ����Һ����������������
 * param: --
 * return: �������ִ�гɹ����ض���Һ�������������������򷵻�ֵ�����㡣
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_liquid_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_liquid_amount));
}

/**
 * name: set_calibration_liquid_no
 * brief: ���ö���Һ��š�
 * param: index - ������š�
 *        calibration_liquid_no - ����Һ��š�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_no(
	const unsigned int index,const String &calibration_liquid_no){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_no[index]=calibration_liquid_no;
}

/**
 * name: get_calibration_liquid_no
 * brief: ��ȡ����Һ��š�
 * param: index - ������š�
 * return: ���ض���Һ��š�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_no[index]);
}

/**
 * name: set_calibration_liquid_name
 * brief: ���ö���Һ���ơ�
 * param: index - ������š�
 *        calibration_liquid_name - ����Һ���ơ�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_name(
	const unsigned int index,const String &calibration_liquid_name){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_name[index]=calibration_liquid_name;
}

/**
 * name: get_calibration_liquid_name
 * brief: ��ȡ����Һ���ơ�
 * param: index - ������š�
 * return: ���ض���Һ���ơ�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_name(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_name[index]);
}

/**
 * name: set_calibration_liquid_lot_no
 * brief: ���ö���Һ���š�
 * param: index - ������š�
 *        calibration_liquid_lot_no - ����Һ���š�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_lot_no(
	const unsigned int index,const String &calibration_liquid_lot_no){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_lot_no[index]=calibration_liquid_lot_no;
}

/**
 * name: get_calibration_liquid_lot_no
 * brief: ��ȡ����Һ���š�
 * param: index - ������š�
 * return: ���ض���Һ���š�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_lot_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_lot_no[index]);
}

/**
 * name: set_calibration_liquid_period_of_validity
 * brief: ���ö���Һ��Ч�ڡ�
 * param: index - ������š�
 *        calibration_liquid_period_of_validity - ����Һ��Ч�ڡ�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_period_of_validity(
	const unsigned int index,const String &calibration_liquid_period_of_validity){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_period_of_validity[index]=calibration_liquid_period_of_validity;
}

/**
 * name: get_calibration_liquid_period_of_validity
 * brief: ��ȡ����Һ��Ч�ڡ�
 * param: index - ������š�
 * return: ���ض���Һ��Ч�ڡ�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_period_of_validity(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_period_of_validity[index]);
}

/**
 * name: set_calibration_liquid_standard_concentration
 * brief: ���ö���Һ��׼Ũ�ȡ�
 * param: index - ������š�
 *        calibration_standard_concentration - ����Һ��׼Ũ�ȡ�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_standard_concentration(
	const unsigned int index,const String &calibration_standard_concentration){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_standard_concentration[index]=calibration_standard_concentration;
}

/**
 * name: get_calibration_liquid_standard_concentration
 * brief: ��ȡ����Һ��׼Ũ�ȡ�
 * param: index - ������š�
 * return: ���ض���Һ��׼Ũ�ȡ�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_standard_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_standard_concentration[index]);
}

/**
 * name: set_calibration_liquid_concentration_level
 * brief: ���ö���ҺŨ��ˮƽ��
 * param: index - ������š�
 *        calibration_liquid_concentration_level - ����ҺŨ��ˮƽ��
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_concentration_level(
	const unsigned int index,const String &calibration_liquid_concentration_level){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_concentration_level[index]=calibration_liquid_concentration_level;
}

/**
 * name: get_calibration_liquid_concentration_level
 * brief: ��ȡ����ҺŨ��ˮƽ��
 * param: index - ������š�
 * return: ���ض���ҺŨ��ˮƽ��
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_concentration_level(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_concentration_level[index]);
}

/**
 * name: set_calibration_liquid_test_concentration
 * brief: ���ö���Һ����Ũ�ȡ�
 * param: index - ������š�
 *        calibration_liquid_test_concentration - ����Һ����Ũ�ȡ�
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_test_concentration(
	const unsigned int index,const String &calibration_liquid_test_concentration){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_test_concentration[index]=calibration_liquid_test_concentration;
}

/**
 * name: get_calibration_liquid_test_concentration
 * brief: ��ȡ����Һ����Ũ�ȡ�
 * param: index - ������š�
 * return: ���ض���Һ����Ũ�ȡ�
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_test_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_test_concentration[index]);
}

/**
 * name: set_calibration_parameter_amount
 * brief: ���ö������������
 * param: calibration_parameter_amount - �������������
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_amount(const String &calibration_parameter_amount){
	_calibration_parameter_amount=calibration_parameter_amount;
}

/**
 * name: get_calibration_parameter_amount
 * breif: ��ȡ�������������
 * param: --
 * return: ���ض������������
 */
const String &HL7OBRSegmentForCalib::get_calibration_parameter_amount() const{
	return(_calibration_parameter_amount);
}

/**
 * name: set_calibration_parameter_amount_with_number
 * brief: ��������ʽ���ö������������
 * param: calibration_parameter_amount - �������������
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_amount_with_number(
	const unsigned int calibration_parameter_amount){
	_calibration_parameter_amount=DataConverter::to_string(calibration_parameter_amount);
}

/**
 * name: get_calibration_parameter_amount_with_number
 * brief: ��������ʽ��ȡ�������������
 * param: --
 * return: �������ִ�гɹ����ض���������������򷵻��㡣
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_parameter_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_parameter_amount));
}

/**
 * name: set_calibration_parameter_value
 * brief: ���ö������ֵ��
 * param: index - ������š�
 *        calibration_parameter_value - �������ֵ��
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_value(
	const unsigned int index,const String &calibration_parameter_value){
	assert((index>=0)&&(index<MAX_CALIBRATION_PARAMETER_AMOUNT));
	_calibration_parameter_value[index]=calibration_parameter_value;
}

/**
 * name: get_calibration_parameter_value
 * brief: ��ȡ�������ֵ��
 * param: index - ������š�
 * return: ���ض������ֵ��
 */
const String &HL7OBRSegmentForCalib::get_calibration_parameter_value(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_PARAMETER_AMOUNT));
	return(_calibration_parameter_value[index]);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7OBRSegmentForCalib::set_field(const unsigned int no,const String &content){
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
		//unfinished: �Ƿ���Ҫ��⵱ǰ��Ŀ����Ƿ�Ϊ���֣�����
		//3-2.���õ�ǰ���򡱵����ݡ�
		_item_no=content;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ�ǰ���򡱵����ݡ�
		_item_name=content;
		//4-2.�������еĵ��˳ɹ����ء�
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
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){//���ԡ�
		return(0);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-5);
		}
		//8-2.���õ�ǰ���򡱵����ݡ�
		_calibration_date_time=content;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!content.IsEmpty())&&
			(0==DataConverter::to_unsigned_int(content))){
			return(-6);
		}
		//unfinished: �Ƿ�Ӧ���ڴ��ж϶��귽����ֵ�Ƿ���Ϸ�Χ???
		//10-2.���õ�ǰ���򡱵����ݡ�
		_calibration_method=content;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ�������á��Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){//���ԡ�
		return(0);
	}
	//12.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if((content.IsEmpty())||
			(0==DataConverter::to_unsigned_int(content))||
			(DataConverter::to_unsigned_int(content)>
			MAX_CALIBRATION_LIQUID_AMOUNT)){
			return(-7);
		}
		//12-2.���õ�ǰ���򡱵����ݡ�
		_calibration_liquid_amount=content;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.��ָ����������ȡ����Һ�����Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_no,
			get_calibration_liquid_amount_with_number(),1)<0){
			return(-8);
		}
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ָ����������ȡ����Һ������Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_name,
			get_calibration_liquid_amount_with_number(),2)<0){
			return(-9);
		}
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.��ָ����������ȡ����Һ������Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_lot_no,
			get_calibration_liquid_amount_with_number(),3)<0){
			return(-10);
		}
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.��ָ����������ȡ����Һ��Ч����Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_period_of_validity,
			get_calibration_liquid_amount_with_number(),4)<0){
			return(-11);
		}
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.��ָ����������ȡ����Һ��׼Ũ����Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_standard_concentration,
			get_calibration_liquid_amount_with_number(),5)<0){
			return(-12);
		}
		//17-2.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ָ����������ȡ����ҺŨ��ˮƽ��Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_concentration_level,
			get_calibration_liquid_amount_with_number(),6)<0){
			return(-13);
		}
		//18-2.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ�������á��Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ָ����������ȡ����ҺŨ��ˮƽ��Ϣ��
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_test_concentration,
			get_calibration_liquid_amount_with_number(),7)<0){
			return(-14);
		}
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ�������á��Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.������ǰ׼�����á��򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!content.IsEmpty())&&
			((!DataConverter::is_number(content))||
			(0==DataConverter::to_unsigned_int(content))||
			(DataConverter::to_unsigned_int(content)>
			MAX_CALIBRATION_PARAMETER_AMOUNT))){
			return(-15);
		}
		//20-2.���õ�ǰ���򡱵����ݡ�
		_calibration_parameter_amount=content;
		//20-3.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ�������á��Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.�����ǰϵͳ�м�¼�Ķ����������Ϊ�ա�
		if(_calibration_parameter_amount.IsEmpty()){
			//21-1-1.�����ǰ׼�����á��򡱵����ݲ�Ϊ�ա�
			if(!content.IsEmpty()){
				return(-16);
			}
			//21-1-2.���õ�ǰ���򡱵����ݡ�
			for(unsigned int index=0;index!=
				MAX_CALIBRATION_PARAMETER_AMOUNT;++index){
				_calibration_parameter_value[index]=Text("");
			}
			//21-1-3.�������е��˳ɹ����ء�
			return(1);
		}
		//21-2.�����ǰϵͳ�м�¼�Ķ������������Ϊ�ա�
		else{
			//21-2-1.��ȡ��ǰϵͳ�м�¼�Ķ������������
			const unsigned int calibration_parameter_amount=
				get_calibration_parameter_amount_with_number();
			if((0==calibration_parameter_amount)||(calibration_parameter_amount>
				MAX_CALIBRATION_PARAMETER_AMOUNT)){
				return(-17);
			}
			//21-2-2.���ݵ�ǰϵͳ�м�¼�Ķ���������������������ֵ���顣
			String *calibration_parameter_value=new String[calibration_parameter_amount];
			if(0==calibration_parameter_value){
				return(-18);
			}
			//21-2-3.������ǰ���ݵ����ݣ������жϷ����Ƿ�ɹ���
			if(extract_group_content_from_field_content(content,calibration_parameter_value,
				calibration_parameter_amount)<0){
				delete[] calibration_parameter_value;
				return(-19);
			}
			//21-2-4.ͳ����ȡ�Ķ���������ж��ж��ٸ��ǿ����ݡ�
			//21-2-4-1.������ǰ�������������
			unsigned int not_empty_amount=0;
			//21-2-4-2.ͳ����ȡ�Ķ��������
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(!calibration_parameter_value[index].IsEmpty()){
					++not_empty_amount;
				}
			}
			//21-2-4-3.�жϵ�ǰ��ͳ����Ϣ�Ƿ�Ϸ���
			if(not_empty_amount!=calibration_parameter_amount){
				delete[] calibration_parameter_value;
				return(-20);
			}
			//21-2-5.���浱ǰ�������ֵ��
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				_calibration_parameter_value[index]=calibration_parameter_value[index];
			}
			//21-2-6.ɾ���������ֵ�洢��ʱ���顣
			delete[] calibration_parameter_value;
			//21-2-7.�������е��˳ɹ����ء�
			return(1);
		}
	}
	//22~48.�����ǰ�������á��Ρ��ĵڶ�ʮ������ʮ�˸����򡱡�
	else if((no>=22)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-21);
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
int HL7OBRSegmentForCalib::get_field(const unsigned int no,String &content) const{
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
		if(_item_no.IsEmpty()){
			return(-2);
		}
		//unfinished: �Ƿ���Ҫ��⵱ǰ��Ŀ����Ƿ�Ϊ���֣�����
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_item_no;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_item_name;
		//4-2.�������еĵ��˳ɹ����ء�
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
		String content_t(Text(""));
		content_t=_universal_service_id[0];
		content_t+=GROUP_SEPARATOR;
		content_t+=_universal_service_id[1];
		content=content_t;
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
		//8-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!_calibration_date_time.IsEmpty())&&
			((14!=_calibration_date_time.GetLength())||
			(!DataConverter::is_number(_calibration_date_time)))){
			return(-4);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		content=_calibration_date_time;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!_calibration_method.IsEmpty())&&
			(0==get_calibration_method_with_number())){
			return(-5);
		}
		//unfinished: �Ƿ�Ӧ���ڴ��ж϶��귽����ֵ�Ƿ���Ϸ�Χ???
		//10-2.��ȡ��ǰ���򡱵����ݡ�
		content=_calibration_method;
		//10-3.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){//���ԡ�
		return(0);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((_calibration_liquid_amount.IsEmpty())||
			(0==get_calibration_liquid_amount_with_number())||
			(get_calibration_liquid_amount_with_number()>
			MAX_CALIBRATION_LIQUID_AMOUNT)){
			return(-6);
		}
		//12-2.��ȡ��ǰ���򡱵����ݡ�
		content=_calibration_liquid_amount;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.��ָ����������ȡ����Һ�����Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_no,
			get_calibration_liquid_amount_with_number(),
			1,content)<0){
			return(-7);
		}
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ָ����������ȡ����Һ������Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_name,
			get_calibration_liquid_amount_with_number(),
			2,content)<0){
			return(-8);
		}
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.��ָ����������ȡ����Һ������Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_lot_no,
			get_calibration_liquid_amount_with_number(),
			3,content)<0){
			return(-9);
		}
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.��ָ����������ȡ����Һ��Ч����Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_period_of_validity,
			get_calibration_liquid_amount_with_number(),
			4,content)<0){
			return(-10);
		}
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){
		//17-1.��ָ����������ȡ����Һ��׼Ũ����Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_standard_concentration,
			get_calibration_liquid_amount_with_number(),
			5,content)<0){
			return(-11);
		}
		//17-2.�������е��˳ɹ����ء�
		return(1);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ָ����������ȡ����ҺŨ��ˮƽ��Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_concentration_level,
			get_calibration_liquid_amount_with_number(),
			6,content)<0){
			return(-12);
		}
		//18-2.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ������ȡ���Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ָ����������ȡ����ҺŨ��ˮƽ��Ϣ��
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_test_concentration,
			get_calibration_liquid_amount_with_number(),
			7,content)<0){
			return(-13);
		}
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((!_calibration_parameter_amount.IsEmpty())&&
			((!DataConverter::is_number(_calibration_parameter_amount))||
			(0==DataConverter::to_unsigned_int(_calibration_parameter_amount))||
			(DataConverter::to_unsigned_int(_calibration_parameter_amount)>
			MAX_CALIBRATION_PARAMETER_AMOUNT))){
			return(-14);
		}
		//20-2.��ȡ��ǰ���򡱵����ݡ�
		content=_calibration_parameter_amount;
		//20-3.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ������ȡ���Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.�����ǰϵͳ�м�¼�Ķ����������Ϊ�ա�
		if(_calibration_parameter_amount.IsEmpty()){
			//21-1-1.�����ǰ׼����ȡ���򡱵����ݲ�Ϊ�ա�
			for(unsigned int index=0;index!=MAX_CALIBRATION_PARAMETER_AMOUNT;++index){
				if(!_calibration_parameter_value[index].IsEmpty()){
					return(-15);
				}
			}
			//21-1-2.��ȡ��ǰ���򡱵����ݡ�
			content=Text("");
			//21-1-3.�������е��˳ɹ����ء�
			return(1);
		}
		//21-2.�����ǰϵͳ�м�¼�Ķ������������Ϊ�ա�
		else{
			//21-2-1.��ȡ��ǰϵͳ�м�¼�Ķ������������
			const unsigned int calibration_parameter_amount=
				get_calibration_parameter_amount_with_number();
			if((0==calibration_parameter_amount)||(calibration_parameter_amount>
				MAX_CALIBRATION_PARAMETER_AMOUNT)){
				return(-16);
			}
			//21-2-2.ͳ�Ƶ�ǰ���������Ϣ���ж��ж��ٸ��ǿ����ݡ�
			//21-2-2-1.������ǰ�������������
			unsigned int not_empty_amount=0;
			//21-2-2-2.ͳ�Ƶ�ǰ���������Ϣ��
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(!_calibration_parameter_value[index].IsEmpty()){
					++not_empty_amount;
				}
			}
			//21-2-2-3.�жϵ�ǰ��ͳ����Ϣ�Ƿ�Ϸ���
			if(not_empty_amount!=calibration_parameter_amount){
				//unfinished: �����Ƿ���Ҫ�ж϶�������Ƿ�Ϊ���֣�����
				return(-17);
			}
			//21-2-3.���õ�ǰ���������Ϣ�γ�ָ�������ݡ�
			//21-2-3-1.������ǰ�������������
			String temporary_content(Text(""));
			//21-2-3-2.��������������飬�γ�ָ�������ݡ�
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(0!=index){
					temporary_content+=GROUP_SEPARATOR;
				}
				temporary_content+=_calibration_parameter_value[index];
			}
			//21-2-3-3.��ȡ��ǰָ�����򡱵����ݡ�
			content=temporary_content;
			//21-2-4.�������е��˳ɹ����ء�
			return(1);
		}
	}
	//22~48.�����ǰ������ȡ���Ρ��ĵڶ�ʮ������ʮ�˸����򡱡�
	else if((no>=22)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-18);
	}
}

/**
 * name: extract_calibration_liquid_information_from_content
 * brief: ��ָ������������ȡ����Һ��Ϣ��
 * param: content - ָ�������ݡ�
 *        calibration_liquid_information - ָ�򶨱�Һ��Ϣ�洢���顣
 *        calibration_liquid_amount - ����Һ������
 *        calibration_liquid_information_type - ����Һ��Ϣ���͡�
 *        =====================================================
 *          1  ����Һ��š�
 *          2  ����Һ���ơ�
 *          3  ����Һ���š�
 *          4  ����Һ��Ч�ڡ�
 *          5  ����Һ��׼Ũ�ȡ�
 *          6  ����ҺŨ��ˮƽ��
 *          7  ����Һ����Ũ�ȡ�
 *        ======================================================
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ע��˺������趨��Һ�����Ѿ��ɹ���ȡ��
 */
int HL7OBRSegmentForCalib::extract_calibration_liquid_information_from_content(
	const String &content,String *calibration_liquid_information,const unsigned int
	calibration_liquid_amount,const unsigned int calibration_liquid_information_type){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if((0==calibration_liquid_information)||(0==calibration_liquid_amount)||
		(calibration_liquid_amount>MAX_CALIBRATION_LIQUID_AMOUNT)||
		(calibration_liquid_information_type<1)||
		(calibration_liquid_information_type>7)){
		return(-1);
	}
	//2.���ݵ�ǰϵͳ��¼�Ķ���Һ��������������Һ��Ϣ�洢���飬�����жϴ����Ƿ�ɹ���
	String *calibration_liquid_information_array=new String[calibration_liquid_amount];
	if(0==calibration_liquid_information_array){
		return(-2);
	}
	//3.������ǰ���ݵ����ݣ������жϷ����Ƿ�ɹ���
	if(extract_group_content_from_field_content(content,calibration_liquid_information_array,
		calibration_liquid_amount)<0){
		delete[] calibration_liquid_information_array;
		return(-3);
	}
	//4.ͳ�ƶ���Һ��Ϣ�洢�����е����ݣ��鿴�м����ա������ǿյ����ݡ�
	//4-1.������ǰ�������������
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//4-2.ͳ�ƶ���Һ��Ϣ�洢�����е����ݡ�
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(calibration_liquid_information_array[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//4-3.����ͳ�ƽ�����жϵ�ǰ����Һ�洢������������Ƿ�Ϸ���
	//unfinished: �����Ƿ���Ҫ�Զ�����Ϣ��һЩ������Ϣ��������ʶ���жϡ�
	if((1==calibration_liquid_information_type)||
		(2==calibration_liquid_information_type)||
		(3==calibration_liquid_information_type)||
		(4==calibration_liquid_information_type)){
		if((empty_amount!=calibration_liquid_amount)&&
			(not_empty_amount!=calibration_liquid_amount)){
			delete[] calibration_liquid_information_array;
			return(-4);
		}else if((calibration_liquid_amount==not_empty_amount)&&
			(4==calibration_liquid_information_type)){			
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((8!=calibration_liquid_information_array[index].GetLength())||
					(!DataConverter::is_number(calibration_liquid_information_array[index]))){
					delete[] calibration_liquid_information_array;
					return(-5);
				}
			}
		}
	}else{
		if(not_empty_amount!=calibration_liquid_amount){
			delete[] calibration_liquid_information_array;
			return(-6);
		}else if(6==calibration_liquid_information_type){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((Text('H')!=calibration_liquid_information_array[index])&&
					(Text('M')!=calibration_liquid_information_array[index])&&
					((Text('L')!=calibration_liquid_information_array[index]))){
					delete[] calibration_liquid_information_array;
					return(-7);
				}
			}
		}
	}
	//5.���浱ǰ��ȡ�Ķ���Һ��Ϣ��
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		calibration_liquid_information[index]=calibration_liquid_information_array[index];
	}
	//6.ɾ������Һ��Ϣ�洢���顣
	delete[] calibration_liquid_information_array;
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: pack_calibration_liquid_information_to_content
 * brief: �����ǰ�Ķ�����Ϣ�������γ�ָ���ַ��������ݡ�
 * param: calibration_liquid_information - ָ�򶨱���Ϣ���顣
 *        calibration_liquid_amount - ����Һ������
 *        calibration_liquid_information_type - ������Ϣ���͡�
 *        =====================================================
 *          1  ����Һ��š�
 *          2  ����Һ���ơ�
 *          3  ����Һ���š�
 *          4  ����Һ��Ч�ڡ�
 *          5  ����Һ��׼Ũ�ȡ�
 *          6  ����ҺŨ��ˮƽ��
 *          7  ����Һ����Ũ�ȡ�
 *        ======================================================
 *        content - ���ص����ݡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
 int HL7OBRSegmentForCalib::pack_calibration_liquid_information_to_content(
	 const String *calibration_liquid_information,const unsigned int calibration_liquid_amount,
	const unsigned int calibration_liquid_information_type,String &content) const{
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if((0==calibration_liquid_information)||(0==calibration_liquid_amount)||
		(calibration_liquid_amount>MAX_CALIBRATION_LIQUID_AMOUNT)||
		(calibration_liquid_information_type<1)||(calibration_liquid_information_type>7)){
		return(-1);
	}
	//2.ͳ�Ƶ�ǰ����Һ��Ϣ�У�����ǿյ�������
	//2-1.������ǰ�������������
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//2-2.��������Һ��Ϣ�洢���飬ͳ�Ƶ�ǰ����Һ��Ϣ�еĿ���ǿռ�����
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(calibration_liquid_information[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//2-3.����ͳ�ƽ�����жϵ�ǰ����Һ��Ϣ�洢�����е������Ƿ�Ϸ���
	//unfinished: �����Ƿ���Ҫ�Զ�����Ϣ��һЩ������Ϣ��������ʶ���жϡ�
	if((1==calibration_liquid_information_type)||
		(2==calibration_liquid_information_type)||
		(3==calibration_liquid_information_type)||
		(4==calibration_liquid_information_type)){
		if((empty_amount!=calibration_liquid_amount)&&
			(not_empty_amount!=calibration_liquid_amount)){
			return(-2);
		}else if((calibration_liquid_amount==not_empty_amount)&&
			(4==calibration_liquid_information_type)){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((8!=calibration_liquid_information[index].GetLength())||
					(!DataConverter::is_number(calibration_liquid_information[index]))){
					return(-3);
				}
			}
		}
	}else{
		if(not_empty_amount!=calibration_liquid_amount){
			return(-4);
		}else if(6==calibration_liquid_information_type){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((Text('H')!=calibration_liquid_information[index])&&
					(Text('M')!=calibration_liquid_information[index])&&
					((Text('L')!=calibration_liquid_information[index]))){
					return(-5);
				}
			}
		}
	}
	//3.���õ�ǰ����Һ��Ϣ�γ�ָ�������ݡ�
	//3-1.������ǰ�������������
	String temporary_content(Text(""));
	//3-2.����������Ϣ���飬�γ�ָ�������ݡ�
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(0!=index){
			temporary_content+=GROUP_SEPARATOR;
		}
		temporary_content+=calibration_liquid_information[index];
	}
	//3-3.����Ŀ�����ݡ�
	content=temporary_content;
	//4.�������е��˳ɹ����ء�
	return(0);
}