#include"stdafx.h"
#include"HL7OBRSegmentForQC.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForQC
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7OBRSegmentForQC::HL7OBRSegmentForQC(void)
	:HL7OBRSegment()
	,_item_no(Text(""))
	,_item_name(Text(""))
	/*,_universal_service_id[2]*/
	,_qc_date_time(Text(""))
	,_qc_liquid_amount(Text(""))
	/*,_qc_liquid_no[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_name[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_lot_no[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_period_of_validity[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_concentration_level[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_average_concentration[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_standard_deviation[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_test_result_concentration[MAX_QC_LIQUID_AMOUNT]*/{
}

/**
 * name: ~HL7OBRSegmentForQC
 * brief: ����������
 * param: --
 * return: --
 */
HL7OBRSegmentForQC::~HL7OBRSegmentForQC(void){
}

/**
 * name: set_item_no
 * brief: ������Ŀ��š�
 * param: item_no - ��Ŀ��š�
 * return: --
 */
void HL7OBRSegmentForQC::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: ��ȡ��Ŀ��š�
 * param: --
 * return: ������Ŀ��š�
 */
const String &HL7OBRSegmentForQC::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: ������Ŀ���ơ�
 * param: item_name - ��Ŀ���ơ�
 * return: --
 */
void HL7OBRSegmentForQC::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: ��ȡ��Ŀ���ơ�
 * param: --
 * return: ������Ŀ���ơ�
 */
const String &HL7OBRSegmentForQC::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_universal_service_id
 * brief: ����ָ����ͨ�÷����ʶ����
 * param: index - ������š�
 *        universal_service_id - ָ����ͨ�÷����ʶ����
 * return: --
 */
void HL7OBRSegmentForQC::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: ��ȡָ����ͨ�÷����ʶ����
 * param: index - ������š�
 * return: ����ָ����ͨ�÷����ʶ����
 */
const String &HL7OBRSegmentForQC::get_universal_service_id(
	const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_qc_date_time
 * brief: ����ָ������ʱ�䣨��ʽ��20150128123730����
 * param: qc_date_time - ָ������ʱ�䣨��ʽ��20150128123730����
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_date_time(const String &qc_date_time){
	_qc_date_time=qc_date_time;
}

/**
 * name: get_qc_date_time
 * brief: ��ȡ�ʿ�����ʱ�䣨��ʽ��20150128123730����
 * param: --
 * return: �����ʿ�����ʱ�䣨��ʽ��20150128123730����
 */
const String &HL7OBRSegmentForQC::get_qc_date_time() const{
	return(_qc_date_time);
}

/**
 * name: set_qc_liquid_amount
 * brief: �����ʿ�Һ������
 * param: qc_liquid_amount - �ʿ�Һ������
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_amount(const String &qc_liquid_amount){
	_qc_liquid_amount=qc_liquid_amount;
}

/**
 * name: get_qc_liquid_amount
 * brief: ��ȡ�ʿ�Һ������
 * param: --
 * return: �����ʿ�Һ������
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_amount() const{
	return(_qc_liquid_amount);
}

/**
 * name: set_qc_liquid_amount_with_number
 * brief: �����ֵ���ʽ�����ʿ�Һ������
 * param: qc_liquid_amount - �ʿ�Һ������
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_amount_with_number(const unsigned int qc_liquid_amount){
	_qc_liquid_amount=DataConverter::to_string(qc_liquid_amount);
}

/**
 * name: get_qc_liquid_amount_with_number
 * brief: ��ȡ�ʿ�Һ����������������
 * param: --
 * return: �������ִ�гɹ������ʿ�Һ�������������������򷵻�ֵ�����㡣
 */
unsigned int HL7OBRSegmentForQC::get_qc_liquid_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_qc_liquid_amount));
}

/**
 * name: set_qc_liquid_no
 * brief: ����ָ�����ʿ�Һ��š�
 * param: index - ������š�
 *        qc_liquid_no - �ʿ�Һ��š�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_no(const unsigned int index,const String &qc_liquid_no){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_no[index]=qc_liquid_no;
}

/**
 * name: get_qc_liquid_no
 * brief: ��ȡָ�����ʿ�Һ��š�
 * param: index - ������š�
 * return: ����ָ�����ʿ�Һ��š�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_no[index]);
}

/**
 * name: set_qc_liquid_name
 * brief: ����ָ���ʿ�Һ�����ơ�
 * param: index - ������š�
 *        qc_liquid_name - �ʿ�Һ���ơ�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_name(
	const unsigned int index,const String &qc_liquid_name){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_name[index]=qc_liquid_name;
}

/**
 * name: get_qc_liquid_name
 * brief: ��ȡָ�����ʿ�Һ���ơ�
 * param: index - ������š�
 * return: ����ָ�����ʿ�Һ���ơ�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_name(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_name[index]);
}

/**
 * name: set_qc_liquid_lot_no
 * brief: ����ָ�����ʿ�Һ���š�
 * param: index - ������š�
 *        qc_liquid_lot_no - �ʿ�Һ���š�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_lot_no(const unsigned int index,const String &qc_liquid_lot_no){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_lot_no[index]=qc_liquid_lot_no;
}

/**
 * name: get_qc_liquid_lot_no
 * brief: ��ȡָ�����ʿ�Һ���š�
 * param: index - ������š�
 * return: ����ָ�����ʿ�Һ���š�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_lot_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_lot_no[index]);
}

/**
 * name: set_qc_liquid_period_of_validity
 * brief: ����ָ���ʿ�Һ����Ч�ڡ�
 * param: index - ������š�
 *        qc_liquid_period_of_validity - �ʿ�Һ��Ч�ڡ�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_period_of_validity(
	const unsigned int index,const String &qc_liquid_period_of_validity){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_period_of_validity[index]=qc_liquid_period_of_validity;
}

/**
 * name: get_qc_liquid_period_of_validity
 * brief: ��ȡָ���ʿ�Һ����Ч�ڡ�
 * param: index - ������š�
 * return: ����ָ���ʿ�Һ����Ч�ڡ�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_period_of_validity(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_period_of_validity[index]);
}

/**
 * name: set_qc_liquid_concentration_level
 * brief: ����ָ����Ũ��ҺŨ��ˮƽ��
 * param: index - ������š�
 *        qc_liquid_concentration_level - �ʿ�ҺŨ��ˮƽ��
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_concentration_level(
	const unsigned int index,const String &qc_liquid_concentration_level){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_concentration_level[index]=qc_liquid_concentration_level;
}

/**
 * name: get_qc_liquid_concentration_level
 * brief: ��ȡָ�����ʿ�ҺŨ��ˮƽ��
 * param: index - ������š�
 * return: ����ָ�����ʿ�ҺŨ��ˮƽ��
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_concentration_level(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_concentration_level[index]);
}

/**
 * name: set_qc_liquid_average_concentration
 * brief: ����ָ���ʿ�Һ��ƽ��Ũ�ȡ�
 * param: index - ������š�
 *        qc_liquid_average_concentration - �ʿ�Һƽ��Ũ�ȡ�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_average_concentration(
	const unsigned int index,const String &qc_liquid_average_concentration){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_average_concentration[index]=qc_liquid_average_concentration;
}

/**
 * name: get_qc_liquid_average_concentration
 * brief: ��ȡָ���ʿ�Һ��ƽ��Ũ�ȡ�
 * param: index - ������š�
 * return: ����ָ���ʿ�Һ��ƽ��Ũ�ȡ�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_average_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_average_concentration[index]);
}

/**
 * name: set_qc_liquid_standard_deviation
 * brief: ����ָ���ʿ�Һ�ı�׼�
 * param: index - ������š�
 *        qc_liquid_standard_deviation - ָ���ʿ�Һ�ı�׼�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_standard_deviation(
	const unsigned int index,const String &qc_liquid_standard_deviation){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_standard_deviation[index]=qc_liquid_standard_deviation;
}

/**
 * name: get_qc_liquid_standard_deviation
 * brief: ��ȡָ���ʿ�Һ�ı�׼�
 * param: index - ������š�
 * return: ����ָ���ʿ�Һ�ı�׼�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_standard_deviation(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_standard_deviation[index]);
}

/**
 * name: set_qc_liquid_test_result_concentration
 * brief: ����ָ���ʿ�Һ�Ĳ��Խ��Ũ�ȡ�
 * param: index - ������š�
 *        qc_liquid_test_result_concentration - �ʿ�Һ�Ĳ��Խ��Ũ�ȡ�
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_test_result_concentration(
	const unsigned int index,const String &qc_liquid_test_result_concentration){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_test_result_concentration[index]=qc_liquid_test_result_concentration;
}

/**
 * name: get_qc_liquid_test_result_concentration
 * brief: ��ȡָ�����ʿ�Һ���Խ��Ũ�ȡ�
 * param: index - ������š�
 * return: ����ָ�����ʿ�Һ���Խ��Ũ�ȡ�
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_test_result_concentration(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_test_result_concentration[index]);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7OBRSegmentForQC::set_field(const unsigned int no,const String &content){
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
			//unfinished: �Ƿ���Ҫ�ж��ʿ�Һ���Ϊ���֣�����
			return(-2);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		_item_no=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ�ǰ���򡱵����ݡ�
		_item_name=content;
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
		_qc_date_time=content;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){//���ԡ�
		return(0);
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
			(DataConverter::to_unsigned_int(content)>MAX_QC_LIQUID_AMOUNT)){
				return(-6);
		}
		//12-2.���õ�ǰ���򡱵����ݡ�
		_qc_liquid_amount=content;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_no,get_qc_liquid_amount_with_number(),1)<0){
			return(-7);
		}
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_name,get_qc_liquid_amount_with_number(),2)<0){
			return(-8);
		}
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_lot_no,get_qc_liquid_amount_with_number(),3)<0){
			return(-9);
		}
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_period_of_validity,get_qc_liquid_amount_with_number(),4)<0){
			return(-10);
		}
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_concentration_level,get_qc_liquid_amount_with_number(),5)<0){
			return(-11);
		}
		//18-2.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ�������á��Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_average_concentration,get_qc_liquid_amount_with_number(),6)<0){
			return(-12);
		}
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ�������á��Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_standard_deviation,get_qc_liquid_amount_with_number(),7)<0){
			return(-13);
		}
		//20-2.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ�������á��Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_test_result_concentration,get_qc_liquid_amount_with_number(),8)<0){
			return(-14);
		}
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22~48.�����ǰ������ȡ���Ρ��ĵڶ�ʮ������ʮ�˸����򡱡�
	else if((no>=22)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-15);
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
int HL7OBRSegmentForQC::get_field(const unsigned int no,String &content) const{
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
			//unfinished: �Ƿ���Ҫ�ж��ʿ�Һ���Ϊ���֣�����
			return(-2);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_item_no;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_item_name;
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
		if((!_qc_date_time.IsEmpty())&&((14!=_qc_date_time.GetLength())||
			(!DataConverter::is_number(_qc_date_time)))){
			return(-4);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		content=_qc_date_time;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){//���ԡ�
		return(0);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){//���ԡ�
		return(0);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){//���ԡ�
		return(0);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.������ǰ׼����ȡ���򡱵����ݣ������ж������Ƿ�Ϸ���
		if((_qc_liquid_amount.IsEmpty())||
			(0==get_qc_liquid_amount_with_number())||
			(get_qc_liquid_amount_with_number()>MAX_QC_LIQUID_AMOUNT)){
			return(-5);
		}
		//12-2.��ȡ��ǰ���򡱵����ݡ�
		content=_qc_liquid_amount;
		//12-3.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_no,
			get_qc_liquid_amount_with_number(),1,content)<0){
			return(-6);
		}
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_name,
			get_qc_liquid_amount_with_number(),2,content)<0){
			return(-7);
		}
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){
		//15-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_lot_no,
			get_qc_liquid_amount_with_number(),3,content)<0){
			return(-8);
		}
		//15-2.�������е��˳ɹ����ء�
		return(1);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){
		//16-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_period_of_validity,
			get_qc_liquid_amount_with_number(),4,content)<0){
			return(-9);
		}
		//16-2.�������е��˳ɹ����ء�
		return(1);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){
		//18-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_concentration_level,
			get_qc_liquid_amount_with_number(),5,content)<0){
			return(-10);
		}
		//18-2.�������е��˳ɹ����ء�
		return(1);
	}
	//19.�����ǰ������ȡ���Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_average_concentration,
			get_qc_liquid_amount_with_number(),6,content)<0){
			return(-11);
		}
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_standard_deviation,
			get_qc_liquid_amount_with_number(),7,content)<0){
			return(-12);
		}
		//20-2.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ������ȡ���Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.��ָ������������ȡ���򡱵����ݣ������ж���ȡ�Ƿ�ɹ���
		if(pack_qc_liquid_information_to_content(_qc_liquid_test_result_concentration,
			get_qc_liquid_amount_with_number(),8,content)<0){
			return(-13);
		}
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22~48.�����ǰ������ȡ���Ρ��ĵڶ�ʮ������ʮ�˸����򡱡�
	else if((no>=22)&&(no<=48)){//���ԡ�
		return(0);
	}
	//49.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-14);
	}
}

/**
 * name: extract_qc_liquid_information_from_content
 * brief: ��ָ�������У���ȡ�ʿ�Һ��Ϣ��
 * param: content - ָ�������ݡ�
 *        qc_liquid_information - ָ���ʿ�Һ��Ϣ�洢���顣
 *        qc_liquid_amount - �ʿ�Һ������
 *        qc_liquid_information_type - �ʿ�Һ��Ϣ���͡�
 *        ================================================
 *						  1  �ʿ�Һ��š�
 *                        2  �ʿ�Һ���ơ�
 *                        3  �ʿ�Һ���š�
 *                        4  �ʿ�Һ��Ч�ڡ�
 *                        5  �ʿ�ҺŨ��ˮƽ��
 *                        6  �ʿ�Һƽ��Ũ�ȡ�
 *                        7  �ʿ�Һ��׼�
 *                        8  �ʿ�Һ���Խ��Ũ�ȡ�
 *        ================================================
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7OBRSegmentForQC::extract_qc_liquid_information_from_content(
	const String &content,String *qc_liquid_information,const unsigned int 
	qc_liquid_amount,const unsigned int qc_liquid_information_type){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((0==qc_liquid_information)||(0==qc_liquid_amount)||(qc_liquid_amount>
		MAX_QC_LIQUID_AMOUNT)||(qc_liquid_information_type<1)||(
		qc_liquid_information_type>8)){
		return(-1);
	}
	//2.���ݵ�ǰ�ʿ�Һ�����������ʿ�Һ��Ϣ��ʱ�洢�ռ䣬�����жϴ����Ƿ�ɹ���
	String *qc_liquid_information_temp=new String[qc_liquid_amount];
	if(0==qc_liquid_information_temp){
		return(-2);
	}
	//3.����ָ�������ݣ�������ȡָ�����ʿ�Һ��Ϣ�������жϷ����Ƿ�ɹ���
	if(extract_group_content_from_field_content(content,
		qc_liquid_information_temp,qc_liquid_amount)<0){
		delete[] qc_liquid_information_temp;
		return(-3);
	}
	//4.ͳ���ʿ�Һ��Ϣ�пա���ǿյ��������Ӷ��жϻ�ȡ���ʿ�Һ��Ϣ�Ƿ�Ϸ���
	//4-1.������ǰ�������������
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//4-2.�����ʿ�Һ��Ϣ�洢��ʱ���飬����ͳ���ʿ�Һ��Ϣ����ǿյ�������
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(qc_liquid_information_temp[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//4-3.���ݿա��ǿյ�ͳ���������жϵ�ǰ��ȡ���ʿ�Һ��Ϣ�Ƿ�Ϸ���
	//unfinished: �����Ƿ���Ҫ�Զ�����Ϣ��һЩ������Ϣ��������ʶ���жϡ�
	if((1==qc_liquid_information_type)||(2==qc_liquid_information_type)||
		(3==qc_liquid_information_type)||(4==qc_liquid_information_type)){
		if((empty_amount!=qc_liquid_amount)&&
			(not_empty_amount!=qc_liquid_amount)){
			delete[] qc_liquid_information_temp;
			return(-4);
		}else if((qc_liquid_amount==not_empty_amount)&&
			(4==qc_liquid_information_type)){			
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((8!=qc_liquid_information_temp[index].GetLength())||
					(!DataConverter::is_number(qc_liquid_information_temp[index]))){
					delete[] qc_liquid_information_temp;
					return(-5);
				}
			}
		}
	}else{
		if(not_empty_amount!=qc_liquid_amount){
			delete[] qc_liquid_information_temp;
			return(-6);
		}else if(5==qc_liquid_information_type){
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((Text('H')!=qc_liquid_information_temp[index])&&
					(Text('M')!=qc_liquid_information_temp[index])&&
					((Text('L')!=qc_liquid_information_temp[index]))){
					delete[] qc_liquid_information_temp;
					return(-7);
				}
			}
		}
	}
	//5.����ǰ��ȡ����ʱ�ʿ�Һ��Ϣ�洢���ʿ�Һ��Ϣ�洢�����С�
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		qc_liquid_information[index]=qc_liquid_information_temp[index];
	}
	//6.ɾ���ʿ�Һ��Ϣ�洢��ʱ���顣
	delete[] qc_liquid_information_temp;
	//7.�������е��˳ɹ����ء�
	return(1);
}

/**
 * name: pack_qc_liquid_information_to_content
 * brief: ����ǰ���ʿ�Һ��Ϣ�������ָ�������ݡ�
 * param: qc_liquid_information - ָ���ʿ�Һ��Ϣ�洢���顣
 *        qc_liquid_amount - �ʿ�Һ������
 *        qc_liquid_information_type - �ʿ�Һ���͡�
 *        ================================================
 *						  1  �ʿ�Һ��š�
 *                        2  �ʿ�Һ���ơ�
 *                        3  �ʿ�Һ���š�
 *                        4  �ʿ�Һ��Ч�ڡ�
 *                        5  �ʿ�ҺŨ��ˮƽ��
 *                        6  �ʿ�Һƽ��Ũ�ȡ�
 *                        7  �ʿ�Һ��׼�
 *                        8  �ʿ�Һ���Խ��Ũ�ȡ�
 *        ================================================
 *        content - �������ɵ����ݡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int HL7OBRSegmentForQC::pack_qc_liquid_information_to_content(
	const String *qc_liquid_information,const unsigned int qc_liquid_amount,
	const unsigned int qc_liquid_information_type,String &content) const{
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if((0==qc_liquid_information)||(0==qc_liquid_amount)||(qc_liquid_amount>
		MAX_QC_LIQUID_AMOUNT)||(qc_liquid_information_type<1)||(
		qc_liquid_information_type>8)){
		return(-1);
	}
	//2.ͳ���ʿ�Һ��Ϣ�пա���ǿյ��������Ӷ��жϻ�ȡ���ʿ�Һ��Ϣ�Ƿ�Ϸ���
	//2-1.������ǰ�������������
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//2-2.�����ʿ�Һ��Ϣ�洢���飬����ͳ���ʿ�Һ��Ϣ����ǿյ�������
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(qc_liquid_information[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//2-3.���ݿա��ǿյ�ͳ���������жϵ�ǰ��ȡ���ʿ�Һ��Ϣ�Ƿ�Ϸ���
	//unfinished: �����Ƿ���Ҫ���ʿ���Ϣ��һЩ������Ϣ��������ʶ���жϡ�
	if((1==qc_liquid_information_type)||(2==qc_liquid_information_type)||
		(3==qc_liquid_information_type)||(4==qc_liquid_information_type)){
		if((empty_amount!=qc_liquid_amount)&&
			(not_empty_amount!=qc_liquid_amount)){
			return(-2);
		}else if((qc_liquid_amount==not_empty_amount)&&(
			4==qc_liquid_information_type)){			
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((8!=qc_liquid_information[index].GetLength())||
					(!DataConverter::is_number(qc_liquid_information[index]))){
					return(-3);
				}
			}
		}
	}else{
		if(not_empty_amount!=qc_liquid_amount){
			return(-4);
		}else if(5==qc_liquid_information_type){
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((Text('H')!=qc_liquid_information[index])&&
					(Text('M')!=qc_liquid_information[index])&&
					((Text('L')!=qc_liquid_information[index]))){
					return(-5);
				}
			}
		}
	}
	//3.���õ�ǰ�ʿ�Һ��Ϣ�γ�ָ�������ݡ�
	//3-1.������ǰ�������������
	String content_t(Text(""));
	//3-2.����������Ϣ���飬�γ�ָ�������ݡ�
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(0!=index){
			content_t+=GROUP_SEPARATOR;
		}
		content_t+=qc_liquid_information[index];
	}
	//3-3.����Ŀ�����ݡ�
	content=content_t;
	//4.�������е��˳ɹ����ء�
	return(0);
}