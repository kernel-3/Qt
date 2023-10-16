#include"stdafx.h"
#include"HL7QRFSegment.h"
#include"../tool/DataConverter.h"

//��ʼ����̬������
const String HL7QRFSegment::SegmentName(Text("QRF"));

/**
 * name: HL7QRDSegment
 * brief: ���캯����
 * param: --
 * return: --
 */
HL7QRFSegment::HL7QRFSegment(void)
	:HL7Segment(SegmentName,10)
	,_facility_model(Text(""))
	,_specimen_receipt_start_date_time(Text(""))
	,_specimen_receipt_end_date_time(Text(""))
	,_target_type(Text("RCT"))
	,_target_status(Text("COR"))
	,_date_Time_selection_qualifier(Text("ALL")){
}

/**
 * name: ~HL7QRDSegment
 * brief: ����������
 * param: --
 * return: --
 */
HL7QRFSegment::~HL7QRFSegment(void){
}

/**
 * name: set_facility_model
 * brief: �����豸�ͺš�
 * param: facility_model - �豸�ͺš�
 * return: --
 */
void HL7QRFSegment::set_facility_model(const String &facility_model){
	_facility_model=facility_model;
}

/**
 * name: get_facility_model
 * brief: ��ȡ�豸�ͺš�
 * param: --
 * return: �����豸�ͺš�
 */
const String &HL7QRFSegment::get_facility_model() const{
	return(_facility_model);
}

/**
 * name: set_specimen_receipt_start_date_time
 * brief: ���ò�ѯʱ����������ʱ��֮ʼ��
 * param: specimen_receipt_start_date_time - ��ѯʱ����������ʱ��֮ʼ��
 * return: --
 */
void HL7QRFSegment::set_specimen_receipt_start_date_time(
	const String &specimen_receipt_start_date_time){
	_specimen_receipt_start_date_time=specimen_receipt_start_date_time;
}

/**
 * name: get_specimen_receipt_start_date_time
 * breif: ��ȡ��ѯʱ����������ʱ��֮ʼ��
 * param: --
 * return: ���ز�ѯʱ����������ʱ��֮ʼ�� 
 */
const String &HL7QRFSegment::get_specimen_receipt_start_date_time() const{
	return(_specimen_receipt_start_date_time);
}

/**
 * name: set_specimen_receipt_end_date_time
 * brief: ���ò�ѯʱ����������ʱ��֮ĩ��
 * param: specimen_receipt_end_date_time - ��ѯʱ����������ʱ��֮ĩ��
 * return: --
 */
void HL7QRFSegment::set_specimen_receipt_end_date_time(
	const String &specimen_receipt_end_date_time){
	_specimen_receipt_end_date_time=specimen_receipt_end_date_time;
}

/**
 * name: get_specimen_receipt_end_date_time
 * brief: ��ȡ��ѯʱ����������ʱ��֮ĩ��
 * param: --
 * return: ���ز�ѯʱ����������ʱ��֮ĩ��
 */
const String &HL7QRFSegment::get_specimen_receipt_end_date_time() const{
	return(_specimen_receipt_end_date_time);
}

/**
 * name: get_target_type
 * brief: ��ȡĿ�����͡�
 * param: --
 * return: ����Ŀ�����͡�
 */
const String &HL7QRFSegment::get_target_type() const{
	return(_target_type);
}

/**
 * name: get_target_status
 * brief: ��ȡĿ��״̬��
 * param: --
 * return: ����Ŀ��״̬��
 */
const String &HL7QRFSegment::get_target_status() const{
	return(_target_status);
}

/**
 * name: get_date_Time_selection_qualifier
 * brief: ��ȡ����/ ʱ��ѡ���޶�����
 * param: --
 * return: ��������/ ʱ��ѡ���޶�����
 */
const String &HL7QRFSegment::get_date_Time_selection_qualifier() const{
	return(_date_Time_selection_qualifier);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7QRFSegment::set_field(const unsigned int no,const String &content){
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
		if(content.IsEmpty()){
			return(-2);
		}
		//2-2.���õ�ǰ���򡱵����ݡ�
		_facility_model=content;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-3);
		}
		//3-2.���õ�ǰ���򡱵����ݡ�
		_specimen_receipt_start_date_time=content;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-4);
		}
		//4-2.���õ�ǰ���򡱵����ݡ�
		_specimen_receipt_end_date_time=content;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){//���ԡ�
		return(0);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("RCT")!=content){
			return(-5);
		}
		//7-2.���õ�ǰ���򡱵����ݡ�
		//_target_type=content;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("COR")!=content){
			return(-6);
		}
		//8-2.���õ�ǰ���򡱵����ݡ�
		//_target_status=content;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼�����á��򡱵����ݲ��Ϸ���
		if(Text("ALL")!=content){
			return(-7);
		}
		//9-2.���õ�ǰ���򡱵����ݡ�
		//_date_Time_selection_qualifier=content;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){//���ԡ�
		return(0);
	}
	//11.�����ǰ����Ϊ���������򡱣��򷵻ش���
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
int HL7QRFSegment::get_field(const unsigned int no,String &content) const{
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
		if(_facility_model.IsEmpty()){
			return(-2);
		}
		//2-2.��ȡ��ǰ���򡱵����ݡ�
		content=_facility_model;
		//2-3.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((!_specimen_receipt_start_date_time.IsEmpty())&&
			((14!=_specimen_receipt_start_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_receipt_start_date_time)))){
			return(-3);
		}
		//3-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_receipt_start_date_time;
		//3-3.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if((!_specimen_receipt_end_date_time.IsEmpty())&&
			((14!=_specimen_receipt_end_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_receipt_end_date_time)))){
			return(-4);
		}
		//4-2.��ȡ��ǰ���򡱵����ݡ�
		content=_specimen_receipt_end_date_time;
		//4-3.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){//���ԡ�
		return(0);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){//���ԡ�
		return(0);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("RCT")!=_target_type){
			return(-5);
		}
		//7-2.��ȡ��ǰ���򡱵����ݡ�
		content=_target_type;
		//7-3.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("COR")!=_target_status){
			return(-6);
		}
		//8-2.��ȡ��ǰ���򡱵����ݡ�
		content=_target_status;
		//8-3.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼����ȡ���򡱵����ݲ��Ϸ���
		if(Text("ALL")!=_date_Time_selection_qualifier){
			return(-7);
		}
		//9-2.��ȡ��ǰ���򡱵����ݡ�
		content=_date_Time_selection_qualifier;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){//���ԡ�
		return(0);
	}
	//11.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-8);
	}
}