#include"stdafx.h"
#include"CalibrationApplication.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../data/DataCustom.h"

/**
 * name: CalibrationApplication
 * brief: ���캯����
 * param: --
 * return: --
 */
CalibrationApplication::CalibrationApplication(void)
	:_calibration_method_id(0)
	,_calibration_method_item_id(0)
	,_point(0)
	,_span_point(0)
	,_weight(0)
	,_blank_time_out(0)
	,_span_time_out(0)
	,_2_point_time_out(0)
	,_full_time_out(0)
	,_lot_no_change_over_calibration_type_id(0)
	,_bottle_change_over_calibration_type_id(0)
	,_sd_limit(0.0)
	,_duplicate_limit_percent(0)
	,_duplicate_limit_abs(0)
	,_sensitivity_range_lower_limit(0.0)
	,_sensitivity_range_upper_limit(0.0)
	,_s1_abs_range_lower_limit(0)
	,_s1_abs_range_upper_limit(0){
}

/**
 * name: ~CalibrationApplication
 * brief: ����������
 * param: --
 * return: --
 */
CalibrationApplication::~CalibrationApplication(void){
}

/**
 * name: set_calibration_method_id
 * brief: ����Ч׼������ʶ��
 * param: calibration_method_id - Ч׼������ʶ��
 * return: --
 */
void CalibrationApplication::set_calibration_method_id(
	const int calibration_method_id){
	_calibration_method_id=calibration_method_id;
}

/**
 * name: get_calibration_method_id
 * brief: ��ȡЧ׼������ʶ��
 * param: --
 * return: ����Ч׼������ʶ��
 */
int CalibrationApplication::get_calibration_method_id() const{
	return(_calibration_method_id);
}

/**
 * name: set_calibration_method_item_id
 * brief: ����Ч׼����������Ŀ��ʶ��
 * param: calibration_method_item_id - Ч׼����������Ŀ��ʶ��
 * return: --
 */
void CalibrationApplication::set_calibration_method_item_id(
	const int calibration_method_item_id){
	_calibration_method_item_id=calibration_method_item_id;
}

/**
 * name: get_calibration_method_item_id
 * brief: ��ȡЧ׼����������Ŀ��ʶ��
 * param: --
 * return: ����Ч׼����������Ŀ��ʶ��
 */
int CalibrationApplication::get_calibration_method_item_id() const{
	return(_calibration_method_item_id);
}

/**
 * name: set_point
 * brief: ����Ч׼�������
 * param: point - Ч׼�������
 * return: --
 */
void CalibrationApplication::set_point(const int point){
	_point=point;
}

/**
 * name: get_point
 * brief: ��ȡЧ׼�������
 * param: --
 * return: ����Ч׼�������
 */
int CalibrationApplication::get_point() const{
	return(_point);
}

/**
 * name: set_span_point
 * brief: �������̵㡣
 * param: span_point - ���̵㡣
 * return: --
 */
void CalibrationApplication::set_span_point(const int span_point){
	_span_point=span_point;
}

/**
 * name: get_span_point
 * brief: ��ȡ���̵㡣
 * param: --
 * return: �������̵㡣
 */
int CalibrationApplication::get_span_point() const{
	return(_span_point);
}

/**
 * name: set_weight
 * brief: ����Ȩ�ء�
 * param: weight - Ȩ�ء�
 * return: --
 */
void CalibrationApplication::set_weight(const int weight){
	_weight=weight;
}

/**
 * name: get_weight
 * brief: ��ȡȨ�ء�
 * param: --
 * return: ����Ȩ�ء�
 */
int CalibrationApplication::get_weight() const{
	return(_weight);
}

/**
 * name: set_blank_time_out
 * brief: ���ÿհ�Ч׼��ʱ��
 * param: blank_time_out - �հ�Ч׼��ʱ��
 * return: --
 */
void CalibrationApplication::set_blank_time_out(const int blank_time_out){
	_blank_time_out=blank_time_out;
}

/**
 * name: get_blank_time_out
 * brief: ��ȡ�հ�Ч׼��ʱ��
 * param: --
 * return: ���ؿհ�Ч׼��ʱ��
 */
int CalibrationApplication::get_blank_time_out() const{
	return(_blank_time_out);
}

/**
 * name: set_span_time_out
 * brief: ��������Ч׼��ʱ��
 * param: span_time_out - ����Ч׼��ʱ��
 * return: --
 */
void CalibrationApplication::set_span_time_out(const int span_time_out){
	_span_time_out=span_time_out;
}

/**
 * name: get_span_time_out
 * brief: ��ȡ����Ч׼��ʱ��
 * param: --
 * return: ��������Ч׼��ʱ��
 */
int CalibrationApplication::get_span_time_out() const{
	return(_span_time_out);
}

/**
 * name: set_2_point_time_out
 * brief: ��������Ч׼��ʱ��
 * param: two_point_time_out - ����Ч׼��ʱ��
 * return: --
 */
void CalibrationApplication::set_2_point_time_out(const int two_point_time_out){
	_2_point_time_out=two_point_time_out;
}

/**
 * name: get_2_point_time_out
 * brief: ��ȡ����Ч׼��ʱ��
 * param: --
 * return: ��������Ч׼��ʱ��
 */
int CalibrationApplication::get_2_point_time_out() const{
	return(_2_point_time_out);
}

/**
 * name: set_full_time_out
 * brief: ����ȫ��Ч׼��ʱ��
 * param: full_time_out - ȫ��Ч׼��ʱ��
 * return: --
 */
void CalibrationApplication::set_full_time_out(const int full_time_out){
	_full_time_out=full_time_out;
}

/**
 * name: get_full_time_out
 * brief: ��ȡȫ��Ч׼��ʱ��
 * param: --
 * return: ����ȫ��Ч׼��ʱ��
 */
int CalibrationApplication::get_full_time_out() const{
	return(_full_time_out);
}

/**
 * name: set_lot_no_change_over_calibration_type_id
 * brief: �������Ÿı䶨�����ͱ�ʶ��
 * param: lot_no_change_over_calibration_type_id - ���Ÿı䶨�����ͱ�ʶ��
 * return: --
 */
void CalibrationApplication::set_lot_no_change_over_calibration_type_id(
	const int lot_no_change_over_calibration_type_id){
	_lot_no_change_over_calibration_type_id=lot_no_change_over_calibration_type_id;
}

/**
 * name: get_lot_no_change_over_calibration_type_id
 * brief: ��ȡ���Ÿı䶨�����ͱ�ʶ��
 * param: --
 * return: �������Ÿı䶨�����ͱ�ʶ��
 */
int CalibrationApplication::get_lot_no_change_over_calibration_type_id() const{
	return(_lot_no_change_over_calibration_type_id);
}

/**
 * name: set_bottle_change_over_calibration_type_id
 * brief: ����ƿ�Ӹı䶨�����ͱ�ʶ��
 * param: bottle_change_over_calibration_type_id - ƿ�Ӹı䶨�����ͱ�ʶ��
 * return: --
 */
void CalibrationApplication::set_bottle_change_over_calibration_type_id(
	const int bottle_change_over_calibration_type_id){
	_bottle_change_over_calibration_type_id=bottle_change_over_calibration_type_id;
}

/**
 * name: get_bottle_change_over_calibration_type_id
 * brief: ��ȡƿ�Ӹı䶨�����ͱ�ʶ��
 * param: --
 * return: ����ƿ�Ӹı䶨�����ͱ�ʶ��
 */
int CalibrationApplication::get_bottle_change_over_calibration_type_id() const{
	return(_bottle_change_over_calibration_type_id);
}

/**
 * name: set_sd_limit
 * brief: ����SDֵ���ޡ�
 * param: sd_limit - SDֵ���ޡ�
 * return: --
 */
void CalibrationApplication::set_sd_limit(const double sd_limit){
	_sd_limit=sd_limit;
}

/**
 * name: get_sd_limit
 * brief: ��ȡSDֵ���ޡ�
 * param: --
 * return: ����SDֵ���ޡ�
 */
double CalibrationApplication::get_sd_limit() const{
	return(_sd_limit);
}

/**
 * name: set_duplicate_limit_percent
 * brief: ���òβ�ٷֱȡ�
 * param: duplicate_limit_percent - �β�ٷֱȡ�
 * return: --
 */
void CalibrationApplication::set_duplicate_limit_percent(
	const int duplicate_limit_percent){
	_duplicate_limit_percent=duplicate_limit_percent;
}

/**
 * name: get_duplicate_limit_percent
 * brief: ��ȡ�β�ٷֱȡ�
 * param: --
 * return: ���زβ�ٷֱȡ�
 */
int CalibrationApplication::get_duplicate_limit_percent() const{
	return(_duplicate_limit_percent);
}

/**
 * name: set_duplicate_limit_abs
 * brief: ���òβ�����ȡ�
 * param: duplicate_limit_abs - �β�����ȡ�
 * return: --
 */
void CalibrationApplication::set_duplicate_limit_abs(
	const int duplicate_limit_abs){
	_duplicate_limit_abs=duplicate_limit_abs;
}

/**
 * name: get_duplicate_limit_abs
 * brief: ��ȡ�β�����ȡ�
 * param: --
 * return: ���زβ�����ȡ�
 */
int CalibrationApplication::get_duplicate_limit_abs() const{
	return(_duplicate_limit_abs);
}

/**
 * name: set_sensitivity_range_lower_limit
 * brief: ���������ȷ�Χ���ޡ�
 * param: sensitivity_range_lower_limit - �����ȷ�Χ���ޡ�
 * return: --
 */
void CalibrationApplication::set_sensitivity_range_lower_limit(
	const double sensitivity_range_lower_limit){
	_sensitivity_range_lower_limit=sensitivity_range_lower_limit;
}

/**
 * name: get_sensitivity_range_lower_limit
 * brief: ��ȡ�����ȷ�Χ���ޡ�
 * param: --
 * return: ���������ȷ�Χ���ޡ�
 */
double CalibrationApplication::get_sensitivity_range_lower_limit() const{
	return(_sensitivity_range_lower_limit);
}

/**
 * name: set_sensitivity_range_upper_limit
 * brief: ���������ȷ�Χ���ޡ�
 * param: sensitivity_range_upper_limit - �����ȷ�Χ���ޡ�
 * return: --
 */
void CalibrationApplication::set_sensitivity_range_upper_limit(
	const double sensitivity_range_upper_limit){
	_sensitivity_range_upper_limit=sensitivity_range_upper_limit;
}

/**
 * name: get_sensitivity_range_upper_limit
 * brief: ��ȡ�����ȷ�Χ���ޡ�
 * param: --
 * return: ���������ȷ�Χ���ޡ�
 */
double CalibrationApplication::get_sensitivity_range_upper_limit() const{
	return(_sensitivity_range_upper_limit);
}

/**
 * name: set_s1_abs_range_lower_limit
 * brief: ���ÿհ���������ޡ�
 * param: s1_abs_range_lower_limit - �հ���������ޡ�
 * return: --
 */
void CalibrationApplication::set_s1_abs_range_lower_limit(
	const int s1_abs_range_lower_limit){
	_s1_abs_range_lower_limit=s1_abs_range_lower_limit;
}

/**
 * name: get_s1_abs_range_lower_limit
 * brief: ��ȡ�հ���������ޡ�
 * param: --
 * return: ���ؿհ���������ޡ�
 */
int CalibrationApplication::get_s1_abs_range_lower_limit() const{
	return(_s1_abs_range_lower_limit);
}

/**
 * name: set_s1_abs_range_upper_limit
 * brief: ���ÿհ���������ޡ�
 * param: s1_abs_range_upper_limit - �հ���������ޡ�
 * return: --
 */
void CalibrationApplication::set_s1_abs_range_upper_limit(
	const int s1_abs_range_upper_limit){
	_s1_abs_range_upper_limit=s1_abs_range_upper_limit;
}

/**
 * name: get_s1_abs_range_upper_limit
 * brief: ��ȡ�հ���������ޡ�
 * param: --
 * return: ���ؿհ���������ޡ�
 */
int CalibrationApplication::get_s1_abs_range_upper_limit() const{
	return(_s1_abs_range_upper_limit);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ������������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ������������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int CalibrationApplication::is_valid(CString *error_message/*=0*/) const{
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.����û�ѡ��Ķ������Ͳ��Ϸ���
	if(_calibration_method_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING320));
		}
		return(-1);
	}
	//3.����û�ѡ��Ķ��긽����Ŀ���Ϸ���
	if(_calibration_method_item_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING321));
		}
		return(-2);
	}
	//4.����û�����Ķ���㲻�Ϸ���
	if((_point<1)||(_point>6)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING322),1,6);
		}
		return(-3);
	}
	//5.����û���������̵㲻�Ϸ���
	if((0!=_span_point)&&((_span_point<2)||(_span_point>6))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING323),0,2,6);
		}
		return(-4);
	}
	//6.����û������Ȩ�ز��Ϸ���
	if((_weight<0)||(_weight>2)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING324),0,2);
		}
		return(-5);
	}
	//7.����û�����Ŀհ�Ч׼��ʱʱ�䲻�Ϸ���
	if((-1!=_blank_time_out)&&((_blank_time_out<1)||(_blank_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING325),1,999);
		}
		return(-6);
	}
	//8.����û����������Ч׼��ʱʱ�䲻�Ϸ���
	if((-1!=_span_time_out)&&((_span_time_out<1)||(_span_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING326),1,999);
		}
		return(-7);
	}
	//9.����û������2��Ч׼��ʱʱ�䲻�Ϸ���
	if((-1!=_2_point_time_out)&&((_2_point_time_out<1)||(_2_point_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING327),1,999);
		}
		return(-8);
	}
	//10.����û������ȫ��Ч׼��ʱʱ�䲻�Ϸ���
	if((-1!=_full_time_out)&&((_full_time_out<1)||(_full_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING328),1,999);
		}
		return(-9);
	}
	//11.���ѡ����Լ����Ÿı��Ч׼�������Ϸ���
	if(_lot_no_change_over_calibration_type_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING329));
		}
		return(-10);
	}
	//12.���ѡ����Լ�ƿ�Ÿı��Ч׼�������Ϸ���
	if(_bottle_change_over_calibration_type_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING330));
		}
		return(-11);
	}
	//13.��������SD����ֵ���Ϸ���
	if((_sd_limit<0.1)||(_sd_limit>999.9)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING331),0.1,999.9);
		}
		return(-12);
	}
	//14.�������Ĳβ���İٷֱȲ��Ϸ���
	if((_duplicate_limit_percent<0)||(_duplicate_limit_percent>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING332),0,99);
		}
		return(-13);
	}
	//15.�������Ĳβ��������Ȳ��Ϸ���
	if((_duplicate_limit_abs<0)||(_duplicate_limit_abs>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING333),0,32000);
		}
		return(-14);
	}
	//16.�������������ȼ������޲��Ϸ���
	if((_sensitivity_range_lower_limit<-99999.0)||(
		_sensitivity_range_lower_limit>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING334),-99999.0,999999.0);
		}
		return(-15);
	}
	//17.�������������ȼ������޲��Ϸ���
	if((_sensitivity_range_upper_limit<-99999.0)||(
		_sensitivity_range_upper_limit>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING335),-99999.0,999999.0);
		}
		return(-16);
	}
	//18.�������Ŀհ�����ȼ������޲��Ϸ���
	if((_s1_abs_range_lower_limit<-32000)||(_s1_abs_range_lower_limit>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING336),-32000,32000);
		}
		return(-17);
	}
	//19.�������Ŀհ�����ȼ������޲��Ϸ���
	if((_s1_abs_range_upper_limit<-32000)||(_s1_abs_range_upper_limit>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING337),-32000,32000);
		}
		return(-18);
	}
	//20.��������ȼ������޴��������ȼ������ޡ�
	if((_sensitivity_range_lower_limit>=_sensitivity_range_upper_limit)||
		is_zero(_sensitivity_range_lower_limit-_sensitivity_range_upper_limit)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING338));
		}
		return(-19);
	}
	//21.����հ�����ȼ������޴��ڿհ�����ȼ������ޡ�
	if(_s1_abs_range_lower_limit>=_s1_abs_range_upper_limit){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING339));
		}
		return(-20);
	}
	//22.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * brief: ����ǰЧ׼�����������ΪĬ��ֵ��
 * param: --
 * return: --
 */
void CalibrationApplication::reset_default_value(){
	_calibration_method_id=1;
	_calibration_method_item_id=0;
	_point=1;
	_span_point=0;
	_weight=0;
	_blank_time_out=-1;
	_span_time_out=-1;
	_2_point_time_out=-1;
	_full_time_out=-1;
	_lot_no_change_over_calibration_type_id=0;
	_bottle_change_over_calibration_type_id=0;
	_sd_limit=999.9;
	_duplicate_limit_percent=99;
	_duplicate_limit_abs=32000;
	_sensitivity_range_lower_limit=-99999.0;
	_sensitivity_range_upper_limit=999999.0;
	_s1_abs_range_lower_limit=-32000;
	_s1_abs_range_upper_limit=32000;
}

/**
 * name: commit
 * brief: ����ǰ����Ŀ��Ϣ�ύ�����ݿ��С�
 * param: item_id - ��Ӧ����Ŀ��ʶ��
 *        method - �ύ�����ݿ�ķ�����1 ���� 2 ���£���
 *        database - ׼���ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int CalibrationApplication::commit(
	const int item_id,const int method,Database &database) const{
	//1.�жϵ�ǰ���ݵ���Ŀ��ʶ�Ƿ�Ϸ���
	if((item_id<1)||(item_id>999)){
		return(-1);
	}
	//2.�����ݿ��ύǰ��Ҫ��⵱ǰ������Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-2);
	}
	//3.�����ǰ�����Բ���ķ�ʽ�������ύ�����ݿ��С�
	if(1==method){
		//3-1.���õ�ǰ���������γ��ύ���ݿ��SQL��䡣
		CString calibration_method_item_id(_T(""));
		if(0==_calibration_method_item_id){
			calibration_method_item_id=_T("null");
		}else{
			calibration_method_item_id.Format(_T("'%d'"),_calibration_method_item_id);
		}
		CString lot_no_change_over_calibration_type_id(_T(""));
		if(0==_lot_no_change_over_calibration_type_id){
			lot_no_change_over_calibration_type_id=_T("null");
		}else{
			lot_no_change_over_calibration_type_id.Format(_T("'%d'"),
				_lot_no_change_over_calibration_type_id);
		}
		CString bottle_change_over_calibration_type_id(_T(""));
		if(0==_bottle_change_over_calibration_type_id){
			bottle_change_over_calibration_type_id=_T("null");
		}else{
			bottle_change_over_calibration_type_id.Format(_T("'%d'"),
				_bottle_change_over_calibration_type_id);
		}
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [calibration_application]([item_id],[calibration_method_id],\
					  [calibration_method_item_id],[points],[span_point],[weight],[blank_time_out],\
					  [span_time_out],[2_point_time_out],[full_time_out],[lot_no_change_over_calibration_type_id],\
					  [bottle_change_over_calibration_type_id],[sd_limit],[duplicate_limit_percent],\
					  [duplicate_limit_abs],[sensitivity_range_lower_limit],[sensitivity_range_upper_limit],\
					  [s1_abs_range_lower_limit],[s1_abs_range_upper_limit])VALUES('%d','%d',%s,'%d','%d','%d',\
					  '%d','%d','%d','%d',%s,%s,'%lf','%d','%d','%lf','%lf','%d','%d')"),
					  item_id,_calibration_method_id,calibration_method_item_id,_point,_span_point,_weight,
					  _blank_time_out,_span_time_out,_2_point_time_out,_full_time_out,
					  lot_no_change_over_calibration_type_id,bottle_change_over_calibration_type_id,
					  _sd_limit,_duplicate_limit_percent,_duplicate_limit_abs,_sensitivity_range_lower_limit,
					  _sensitivity_range_upper_limit,_s1_abs_range_lower_limit,_s1_abs_range_upper_limit);
		//3-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-3);
		}
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
	//4.�����ǰ�����Ը��µķ�ʽ�������ύ�����ݿ��С�
	else if(2==method){
		//4-1.���õ�ǰ��Ŀ�����γ��ύ���ݿ��SQL��䡣
		CString calibration_method_item_id(_T(""));
		if(0==_calibration_method_item_id){
			calibration_method_item_id=_T("null");
		}else{
			calibration_method_item_id.Format(_T("'%d'"),_calibration_method_item_id);
		}
		CString lot_no_change_over_calibration_type_id(_T(""));
		if(0==_lot_no_change_over_calibration_type_id){
			lot_no_change_over_calibration_type_id=_T("null");
		}else{
			lot_no_change_over_calibration_type_id.Format(_T("'%d'"),
				_lot_no_change_over_calibration_type_id);
		}
		CString bottle_change_over_calibration_type_id(_T(""));
		if(0==_bottle_change_over_calibration_type_id){
			bottle_change_over_calibration_type_id=_T("null");
		}else{
			bottle_change_over_calibration_type_id.Format(_T("'%d'"),
				_bottle_change_over_calibration_type_id);
		}
		CString sql(_T(""));
		sql.Format(_T("UPDATE [calibration_application] SET [calibration_method_id]='%d',\
					  [calibration_method_item_id]=%s,[points]='%d',[span_point]='%d',\
					  [weight]='%d',[blank_time_out]='%d',[span_time_out]='%d',\
					  [2_point_time_out]='%d',[full_time_out]='%d',\
					  [lot_no_change_over_calibration_type_id]=%s,[bottle_change_over_calibration_type_id]=%s,\
					  [sd_limit]='%lf',[duplicate_limit_percent]='%d',[duplicate_limit_abs]='%d',\
					  [sensitivity_range_lower_limit]='%lf',[sensitivity_range_upper_limit]='%lf',\
					  [s1_abs_range_lower_limit]='%d',[s1_abs_range_upper_limit]='%d' WHERE [item_id]='%d'"),
					  _calibration_method_id,calibration_method_item_id,_point,_span_point,
					  _weight,_blank_time_out,_span_time_out,_2_point_time_out,_full_time_out,
					  lot_no_change_over_calibration_type_id,bottle_change_over_calibration_type_id,
					  _sd_limit,_duplicate_limit_percent,_duplicate_limit_abs,_sensitivity_range_lower_limit,
					  _sensitivity_range_upper_limit,_s1_abs_range_lower_limit,_s1_abs_range_upper_limit,item_id);
		//4-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-4);
		}
		//4-3.�������е��˳ɹ����ء�
		return(0);
	}	
	//5.�����ǰ������������ʽ�������ύ�����ݿ��С�
	else{
		return(-5);
	}
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ�Ķ�����Ϣ��
 * param: record - ָ���ļ�¼����
 * return: �������ִ�г¹�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int CalibrationApplication::update(MtADORecordset &record){
	//1.������ǰ�������������
	CalibrationApplication calibration;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡ���귽����ʶ��
	value=record.get_collect(MtADODataConverter::to_variant_t(67));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	calibration._calibration_method_id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡ���귽��������Ŀ��ʶ��
	value=record.get_collect(MtADODataConverter::to_variant_t(68));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	if(VT_NULL==value.vt){
		calibration._calibration_method_item_id=0;
	}else{
		calibration._calibration_method_item_id=MtADODataConverter::to_int(value);
	}
	//4.��ָ���ļ�¼���л�ȡЧ׼���������
	value=record.get_collect(MtADODataConverter::to_variant_t(69));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	calibration._point=MtADODataConverter::to_int(value);
	//5.��ָ���ļ�¼���л�ȡ����Ч׼��ĸ�����
	value=record.get_collect(MtADODataConverter::to_variant_t(70));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	calibration._span_point=MtADODataConverter::to_int(value);
	//6.��ָ���ļ�¼���л�ȡЧ׼Ȩ�ء�
	value=record.get_collect(MtADODataConverter::to_variant_t(71));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	calibration._weight=MtADODataConverter::to_int(value);
	//7.��ָ���ļ�¼���л�ȡ�հ�Ч׼��ʱʱ�䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(72));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	calibration._blank_time_out=MtADODataConverter::to_int(value);
	//8.��ָ���ļ�¼���л�ȡ����Ч׼��ʱʱ�䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(73));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	calibration._span_time_out=MtADODataConverter::to_int(value);
	//9.��ָ���ļ�¼���л�ȡ����Ч׼��ʱʱ�䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(74));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	calibration._2_point_time_out=MtADODataConverter::to_int(value);
	//10.��ָ���ļ�¼���л�ȡȫ��Ч׼��ʱʱ�䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(75));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	calibration._full_time_out=MtADODataConverter::to_int(value);
	//11.��ָ���ļ�¼���л�ȡ���Ÿı�ʱ��Ч׼���ͱ�ʶ��
	value=record.get_collect(MtADODataConverter::to_variant_t(76));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	if(VT_NULL==value.vt){
		calibration._lot_no_change_over_calibration_type_id=0;
	}else{
		calibration._lot_no_change_over_calibration_type_id=MtADODataConverter::to_int(value);
	}
	//12.��ָ���ļ�¼���л�ȡƿ�Ӹı�ʱ��Ч׼���ͱ�ʶ��
	value=record.get_collect(MtADODataConverter::to_variant_t(77));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	if(VT_NULL==value.vt){
		calibration._bottle_change_over_calibration_type_id=0;
	}else{
		calibration._bottle_change_over_calibration_type_id=MtADODataConverter::to_int(value);
	}
	//13.��ָ���ļ�¼���л�ȡSDֵ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(78));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	calibration._sd_limit=MtADODataConverter::to_double(value);
	//14.��ָ���ļ�¼���л�ȡ�β�ٷֱȡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(79));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	calibration._duplicate_limit_percent=MtADODataConverter::to_int(value);
	//15.��ָ���ļ�¼���л�ȡ�β�����ȡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(80));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	calibration._duplicate_limit_abs=MtADODataConverter::to_int(value);
	//16.��ָ���ļ�¼���л�ȡ����������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(81));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	calibration._sensitivity_range_lower_limit=MtADODataConverter::to_double(value);
	//17.��ָ���ļ�¼���л�ȡ����������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(82));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	calibration._sensitivity_range_upper_limit=MtADODataConverter::to_double(value);
	//18.��ָ���ļ�¼���л�ȡ�հ�����ȷ�Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(83));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	calibration._s1_abs_range_lower_limit=MtADODataConverter::to_int(value);
	//19.��ָ���ļ�¼���л�ȡ�հ�����ȷ�Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(84));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	calibration._s1_abs_range_upper_limit=MtADODataConverter::to_int(value);
	//20.�����ǰ��ȡ�Ķ�����Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(calibration.is_valid()<0){
		return(-19);
	}
	//21.���浱ǰ�ĴӼ�¼���л�ȡ�Ķ�����Ϣ��
	(*this)=calibration;
	//22.�������е��˳ɹ����ء�
	return(0);
}