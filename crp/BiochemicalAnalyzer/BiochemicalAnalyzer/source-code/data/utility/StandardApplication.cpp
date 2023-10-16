#include"stdafx.h"
#include"StandardApplication.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../DataCustom.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: StandardApplication
 * brief: ��׼���캯����
 * param: --
 * return: --
 */
StandardApplication::StandardApplication(void)
	:_calibrator_code_1(0)
	,_calibrator_code_2(0)
	,_calibrator_code_3(0)
	,_calibrator_code_4(0)
	,_calibrator_code_5(0)
	,_calibrator_code_6(0)
	,_sample_volume_1(0.0)
	,_diluted_sample_volume_1(0.0)
	,_diluent_volume_1(0.0)
	,_sample_volume_2(0.0)
	,_diluted_sample_volume_2(0.0)
	,_diluent_volume_2(0.0)
	,_sample_volume_3(0.0)
	,_diluted_sample_volume_3(0.0)
	,_diluent_volume_3(0.0)
	,_sample_volume_4(0.0)
	,_diluted_sample_volume_4(0.0)
	,_diluent_volume_4(0.0)
	,_sample_volume_5(0.0)
	,_diluted_sample_volume_5(0.0)
	,_diluent_volume_5(0.0)
	,_sample_volume_6(0.0)
	,_diluted_sample_volume_6(0.0)
	,_diluent_volume_6(0.0){
}

/**
 * name: ~StandardApplication
 * brief: ��׼����������
 * param: --
 * return: --
 */
StandardApplication::~StandardApplication(void){
}

/**
 * name: set_calibrator_code_1
 * breif: ���ö���Һ1��š�
 * param: calibrator_code - ����Һ1��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_1(const int calibrator_code){
	_calibrator_code_1=calibrator_code;
}

/**
 * name: get_calibrator_code_1
 * breif: ��ȡ����Һ1��š�
 * param: --
 * return: ���ض���Һ1��š�
 */
int StandardApplication::get_calibrator_code_1() const{
	return(_calibrator_code_1);
}

/**
 * name: set_calibrator_code_2
 * breif: ���ö���Һ2��š�
 * param: calibrator_code - ����Һ2��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_2(const int calibrator_code){
	_calibrator_code_2=calibrator_code;
}

/**
 * name: get_calibrator_code_2
 * breif: ��ȡ����Һ2��š�
 * param: --
 * return: ���ض���Һ2��š�
 */
int StandardApplication::get_calibrator_code_2() const{
	return(_calibrator_code_2);
}

/**
 * name: set_calibrator_code_3
 * breif: ���ö���Һ3��š�
 * param: calibrator_code - ����Һ3��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_3(const int calibrator_code){
	_calibrator_code_3=calibrator_code;
}

/**
 * name: get_calibrator_code_3
 * breif: ��ȡ����Һ3��š�
 * param: --
 * return: ���ض���Һ3��š�
 */
int StandardApplication::get_calibrator_code_3() const{
	return(_calibrator_code_3);
}

/**
 * name: set_calibrator_code_4
 * breif: ���ö���Һ4��š�
 * param: calibrator_code - ����Һ4��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_4(const int calibrator_code){
	_calibrator_code_4=calibrator_code;
}

/**
 * name: get_calibrator_code_4
 * breif: ��ȡ����Һ4��š�
 * param: --
 * return: ���ض���Һ4��š�
 */
int StandardApplication::get_calibrator_code_4() const{
	return(_calibrator_code_4);
}

/**
 * name: set_calibrator_code_5
 * breif: ���ö���Һ5��š�
 * param: calibrator_code - ����Һ5��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_5(const int calibrator_code){
	_calibrator_code_5=calibrator_code;
}

/**
 * name: get_calibrator_code_5
 * breif: ��ȡ����Һ5��š�
 * param: --
 * return: ���ض���Һ5��š�
 */
int StandardApplication::get_calibrator_code_5() const{
	return(_calibrator_code_5);
}

/**
 * name: set_calibrator_code_6
 * breif: ���ö���Һ6��š�
 * param: calibrator_code - ����Һ6��š�
 * return: --
 */
void StandardApplication::set_calibrator_code_6(const int calibrator_code){
	_calibrator_code_6=calibrator_code;
}

/**
 * name: get_calibrator_code_6
 * breif: ��ȡ����Һ6��š�
 * param: --
 * return: ���ض���Һ6��š�
 */
int StandardApplication::get_calibrator_code_6() const{
	return(_calibrator_code_6);
}

/**
 * name: set_sample_volume_1
 * breif: �������������1��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_1(const double sample_volume){
	_sample_volume_1=sample_volume;
}

/**
 * name: get_sample_volume_1
 * brief: ��ȡ���������1��
 * param: --
 * return: �������������1��
 */
double StandardApplication::get_sample_volume_1() const{
	return(_sample_volume_1);
}

/**
 * name: set_diluted_sample_volume_1
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_1(const double diluted_sample_volume){
	_diluted_sample_volume_1=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_1
 * brief: ��ȡ��ϡ�ͺ��������1��
 * param: --
 * return: ������ϡ�ͺ��������1��
 */
double StandardApplication::get_diluted_sample_volume_1() const{
	return(_diluted_sample_volume_1);
}

/**
 * name: set_diluent_volume_1
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_1(const double diluent_volume){
	_diluent_volume_1=diluent_volume;
}

/**
 * name: get_diluent_volume_1
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_1() const{
	return(_diluent_volume_1);
}

/**
 * name: set_sample_volume_2
 * breif: �������������2��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_2(const double sample_volume){
	_sample_volume_2=sample_volume;
}

/**
 * name: get_sample_volume_2
 * brief: ��ȡ���������2��
 * param: --
 * return: �������������2��
 */
double StandardApplication::get_sample_volume_2() const{
	return(_sample_volume_2);
}

/**
 * name: set_diluted_sample_volume_2
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_2(const double diluted_sample_volume){
	_diluted_sample_volume_2=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_2
 * brief: ��ȡ��ϡ�ͺ��������2��
 * param: --
 * return: ������ϡ�ͺ��������2��
 */
double StandardApplication::get_diluted_sample_volume_2() const{
	return(_diluted_sample_volume_2);
}

/**
 * name: set_diluent_volume_2
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_2(const double diluent_volume){
	_diluent_volume_2=diluent_volume;
}

/**
 * name: get_diluent_volume_2
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_2() const{
	return(_diluent_volume_2);
}

/**
 * name: set_sample_volume_3
 * breif: �������������3��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_3(const double sample_volume){
	_sample_volume_3=sample_volume;
}

/**
 * name: get_sample_volume_3
 * brief: ��ȡ���������3��
 * param: --
 * return: �������������3��
 */
double StandardApplication::get_sample_volume_3() const{
	return(_sample_volume_3);
}

/**
 * name: set_diluted_sample_volume_3
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_3(const double diluted_sample_volume){
	_diluted_sample_volume_3=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_3
 * brief: ��ȡ��ϡ�ͺ��������3��
 * param: --
 * return: ������ϡ�ͺ��������3��
 */
double StandardApplication::get_diluted_sample_volume_3() const{
	return(_diluted_sample_volume_3);
}

/**
 * name: set_diluent_volume_3
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_3(const double diluent_volume){
	_diluent_volume_3=diluent_volume;
}

/**
 * name: get_diluent_volume_3
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_3() const{
	return(_diluent_volume_3);
}

/**
 * name: set_sample_volume_4
 * breif: �������������4��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_4(const double sample_volume){
	_sample_volume_4=sample_volume;
}

/**
 * name: get_sample_volume_4
 * brief: ��ȡ���������4��
 * param: --
 * return: �������������4��
 */
double StandardApplication::get_sample_volume_4() const{
	return(_sample_volume_4);
}

/**
 * name: set_diluted_sample_volume_4
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_4(const double diluted_sample_volume){
	_diluted_sample_volume_4=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_4
 * brief: ��ȡ��ϡ�ͺ��������4��
 * param: --
 * return: ������ϡ�ͺ��������4��
 */
double StandardApplication::get_diluted_sample_volume_4() const{
	return(_diluted_sample_volume_4);
}

/**
 * name: set_diluent_volume_4
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_4(const double diluent_volume){
	_diluent_volume_4=diluent_volume;
}

/**
 * name: get_diluent_volume_4
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_4() const{
	return(_diluent_volume_4);
}

/**
 * name: set_sample_volume_5
 * breif: �������������5��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_5(const double sample_volume){
	_sample_volume_5=sample_volume;
}

/**
 * name: get_sample_volume_5
 * brief: ��ȡ���������5��
 * param: --
 * return: �������������5��
 */
double StandardApplication::get_sample_volume_5() const{
	return(_sample_volume_5);
}

/**
 * name: set_diluted_sample_volume_5
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_5(const double diluted_sample_volume){
	_diluted_sample_volume_5=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_5
 * brief: ��ȡ��ϡ�ͺ��������5��
 * param: --
 * return: ������ϡ�ͺ��������5��
 */
double StandardApplication::get_diluted_sample_volume_5() const{
	return(_diluted_sample_volume_5);
}

/**
 * name: set_diluent_volume_5
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_5(const double diluent_volume){
	_diluent_volume_5=diluent_volume;
}

/**
 * name: get_diluent_volume_5
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_5() const{
	return(_diluent_volume_5);
}

/**
 * name: set_sample_volume_6
 * breif: �������������6��
 * param: sample_volume - �����������
 * return: --
 */
void StandardApplication::set_sample_volume_6(const double sample_volume){
	_sample_volume_6=sample_volume;
}

/**
 * name: get_sample_volume_6
 * brief: ��ȡ���������6��
 * param: --
 * return: �������������6��
 */
double StandardApplication::get_sample_volume_6() const{
	return(_sample_volume_6);
}

/**
 * name: set_diluted_sample_volume_6
 * breif: ������ϡ�ͺ����������
 * param: diluted_sample_volume - ��ϡ�ͺ����������
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_6(const double diluted_sample_volume){
	_diluted_sample_volume_6=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_6
 * brief: ��ȡ��ϡ�ͺ��������6��
 * param: --
 * return: ������ϡ�ͺ��������6��
 */
double StandardApplication::get_diluted_sample_volume_6() const{
	return(_diluted_sample_volume_6);
}

/**
 * name: set_diluent_volume_6
 * brief: ������ϡ��Һ�����
 * param: diluent_volume - ��ϡ��Һ�����
 * return: --
 */
void StandardApplication::set_diluent_volume_6(const double diluent_volume){
	_diluent_volume_6=diluent_volume;
}

/**
 * name: get_diluent_volume_6
 * brief: ��ȡ��ϡ��Һ�����
 * param: --
 * return: ������ϡ��Һ�����
 */
double StandardApplication::get_diluent_volume_6() const{
	return(_diluent_volume_6);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��׼��������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ��׼��������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int StandardApplication::is_valid(CString *error_message/*=0*/) const{
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.�����ǰ��׼Һ���1���Ϸ���
	if((_calibrator_code_1<0)||(_calibrator_code_1>999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING432),0,999,999);
		}
		return(-1);
	}
	//3.�����ǰ��׼Һ���2���Ϸ���
	if((_calibrator_code_2<0)||(_calibrator_code_2>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING433),0,998);
		}
		return(-2);
	}
	//4.�����ǰ��׼Һ���3���Ϸ���
	if((_calibrator_code_3<0)||(_calibrator_code_3>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING434),0,998);
		}
		return(-3);
	}
	//5.�����ǰ��׼Һ���4���Ϸ���
	if((_calibrator_code_4<0)||(_calibrator_code_4>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING435),0,998);
		}
		return(-4);
	}
	//6.�����ǰ��׼Һ���5���Ϸ���
	if((_calibrator_code_5<0)||(_calibrator_code_5>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING436),0,998);
		}
		return(-5);
	}
	//7.�����ǰ��׼Һ���6���Ϸ���
	if((_calibrator_code_6<0)||(_calibrator_code_6>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING437),0,998);
		}
		return(-6);
	}
	//8.�����ǰ������1������Ϸ���
	if((_sample_volume_1<1.5)||(_sample_volume_1>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING438),1.5,35.0);
		}
		return(-7);
	}
	//9.�����ǰ��ϡ�ͺ���������1���Ϸ���
	if((!is_zero(_diluted_sample_volume_1))&&((_diluted_sample_volume_1<1.5)||(
		_diluted_sample_volume_1>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING439),0.0,1.5,20.0);
		}
		return(-8);
	}
	//10.�����ǰ��ϡ��Һ���1���Ϸ���
	if((!is_zero(_diluent_volume_1))&&((_diluent_volume_1<20.0)||(
		_diluent_volume_1>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING440),0.0,20.0,270.0);
		}
		return(-9);
	}
	//11.�����ǰ������2������Ϸ���
	if((_sample_volume_2<1.5)||(_sample_volume_2>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING441),1.5,35.0);
		}
		return(-10);
	}
	//12.�����ǰ��ϡ�ͺ���������2���Ϸ���
	if((!is_zero(_diluted_sample_volume_2))&&((_diluted_sample_volume_2<1.5)||(
		_diluted_sample_volume_2>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING442),0.0,1.5,20.0);
		}
		return(-11);
	}
	//13.�����ǰ��ϡ��Һ���2���Ϸ���
	if((!is_zero(_diluent_volume_2))&&((_diluent_volume_2<20.0)||(
		_diluent_volume_2>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING443),0.0,20.0,270.0);
		}
		return(-12);
	}
	//14.�����ǰ������3������Ϸ���
	if((_sample_volume_3<1.5)||(_sample_volume_3>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING444),1.5,35.0);
		}
		return(-13);
	}
	//15.�����ǰ��ϡ�ͺ���������3���Ϸ���
	if((!is_zero(_diluted_sample_volume_3))&&((_diluted_sample_volume_3<1.5)||(
		_diluted_sample_volume_3>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING445),0.0,1.5,20.0);
		}
		return(-14);
	}
	//16.�����ǰ��ϡ��Һ���3���Ϸ���
	if((!is_zero(_diluent_volume_3))&&((_diluent_volume_3<20.0)||(
		_diluent_volume_3>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING446),0.0,20.0,270.0);
		}
		return(-15);
	}
	//17.�����ǰ������4������Ϸ���
	if((_sample_volume_4<1.5)||(_sample_volume_4>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING447),1.5,35.0);
		}
		return(-16);
	}
	//18.�����ǰ��ϡ�ͺ���������4���Ϸ���
	if((!is_zero(_diluted_sample_volume_4))&&((_diluted_sample_volume_4<1.5)||(
		_diluted_sample_volume_4>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING448),0.0,1.5,20.0);
		}
		return(-17);
	}
	//19.�����ǰ��ϡ��Һ���4���Ϸ���
	if((!is_zero(_diluent_volume_4))&&((_diluent_volume_4<20.0)||(
		_diluent_volume_4>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING449),0.0,20.0,270.0);
		}
		return(-18);
	}
	//20.�����ǰ������5������Ϸ���
	if((_sample_volume_5<1.5)||(_sample_volume_5>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING450),1.5,35.0);
		}
		return(-19);
	}
	//21.�����ǰ��ϡ�ͺ���������5���Ϸ���
	if((!is_zero(_diluted_sample_volume_5))&&((_diluted_sample_volume_5<1.5)||(
		_diluted_sample_volume_5>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING451),0.0,1.5,20.0);
		}
		return(-20);
	}
	//22.�����ǰ��ϡ��Һ���5���Ϸ���
	if((!is_zero(_diluent_volume_5))&&((_diluent_volume_5<20.0)||(
		_diluent_volume_5>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING452),0.0,20.0,270.0);
		}
		return(-21);
	}
	//23.�����ǰ������6������Ϸ���
	if((_sample_volume_6<1.5)||(_sample_volume_6>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING453),1.5,35.0);
		}
		return(-22);
	}
	//24.�����ǰ��ϡ�ͺ���������6���Ϸ���
	if((!is_zero(_diluted_sample_volume_6))&&((_diluted_sample_volume_6<1.5)||(
		_diluted_sample_volume_6>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING454),0.0,1.5,20.0);
		}
		return(-23);
	}
	//25.�����ǰ��ϡ��Һ���6���Ϸ���
	if((!is_zero(_diluent_volume_6))&&((_diluent_volume_6<20.0)||(
		_diluent_volume_6>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING455),0.0,20.0,270.0);
		}
		return(-24);
	}
	//26.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * brief: ����ǰ���������������ΪĬ��ֵ��
 * param: --
 * return: --
 */
void StandardApplication::reset_default_value(){
	_calibrator_code_1=1;
	_calibrator_code_2=0;
	_calibrator_code_3=0;
	_calibrator_code_4=0;
	_calibrator_code_5=0;
	_calibrator_code_6=0;
	_sample_volume_1=3.0;
	_diluted_sample_volume_1=0.0;
	_diluent_volume_1=0.0;
	_sample_volume_2=3.0;
	_diluted_sample_volume_2=0.0;
	_diluent_volume_2=0.0;
	_sample_volume_3=3.0;
	_diluted_sample_volume_3=0.0;
	_diluent_volume_3=0.0;
	_sample_volume_4=3.0;
	_diluted_sample_volume_4=0.0;
	_diluent_volume_4=0.0;
	_sample_volume_5=3.0;
	_diluted_sample_volume_5=0.0;
	_diluent_volume_5=0.0;
	_sample_volume_6=3.0;
	_diluted_sample_volume_6=0.0;
	_diluent_volume_6=0.0;
}

/**
 * name: commit
 * brief: ����ǰ����Ŀ��Ϣ�ύ�����ݿ��С�
 * param: item_id - ��Ӧ����Ŀ��ʶ��
 *        method - �ύ�����ݿ�ķ�����1 ���� 2 ���£���
 *        database - ׼���ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int StandardApplication::commit(const int item_id,const int method,Database &database) const{
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
		//3-1.���õ�ǰ��׼�����γ��ύ���ݿ��SQL��䡣
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [standard_application]([item_id],[calibrator_code_1],\
					  [calibrator_code_2],[calibrator_code_3],[calibrator_code_4],\
					  [calibrator_code_5],[calibrator_code_6],[sample_volume_1],\
					  [diluted_sample_volume_1],[diluent_volume_1],[sample_volume_2],\
					  [diluted_sample_volume_2],[diluent_volume_2],[sample_volume_3],\
					  [diluted_sample_volume_3],[diluent_volume_3],[sample_volume_4],\
					  [diluted_sample_volume_4],[diluent_volume_4],[sample_volume_5],\
					  [diluted_sample_volume_5],[diluent_volume_5],[sample_volume_6],\
					  [diluted_sample_volume_6],[diluent_volume_6])VALUES('%d','%d','%d',\
					  '%d','%d','%d','%d','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf',\
					  '%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf')"),
					  item_id,_calibrator_code_1,_calibrator_code_2,_calibrator_code_3,
					  _calibrator_code_4,_calibrator_code_5,_calibrator_code_6,_sample_volume_1,
					  _diluted_sample_volume_1,_diluent_volume_1,_sample_volume_2,_diluted_sample_volume_2,
					  _diluent_volume_2,_sample_volume_3,_diluted_sample_volume_3,_diluent_volume_3,
					  _sample_volume_4,_diluted_sample_volume_4,_diluent_volume_4,_sample_volume_5,
					  _diluted_sample_volume_5,_diluent_volume_5,_sample_volume_6,_diluted_sample_volume_6,
					  _diluent_volume_6);
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
		CString sql(_T(""));
		sql.Format(_T("UPDATE [standard_application] SET [calibrator_code_1]='%d',[calibrator_code_2]='%d',\
					  [calibrator_code_3]='%d',[calibrator_code_4]='%d',[calibrator_code_5]='%d',\
					  [calibrator_code_6]='%d',[sample_volume_1]='%lf',[diluted_sample_volume_1]='%lf',\
					  [diluent_volume_1]='%lf',[sample_volume_2]='%lf',[diluted_sample_volume_2]='%lf',\
					  [diluent_volume_2]='%lf',[sample_volume_3]='%lf',[diluted_sample_volume_3]='%lf',\
					  [diluent_volume_3]='%lf',[sample_volume_4]='%lf',[diluted_sample_volume_4]='%lf',\
					  [diluent_volume_4]='%lf',[sample_volume_5]='%lf',[diluted_sample_volume_5]='%lf',\
					  [diluent_volume_5]='%lf',[sample_volume_6]='%lf',[diluted_sample_volume_6]='%lf',\
					  [diluent_volume_6]='%lf' WHERE [item_id]='%d'"),_calibrator_code_1,_calibrator_code_2,
					  _calibrator_code_3,_calibrator_code_4,_calibrator_code_5,_calibrator_code_6,_sample_volume_1,
					  _diluted_sample_volume_1,_diluent_volume_1,_sample_volume_2,_diluted_sample_volume_2,
					  _diluent_volume_2,_sample_volume_3,_diluted_sample_volume_3,_diluent_volume_3,
					  _sample_volume_4,_diluted_sample_volume_4,_diluent_volume_4,_sample_volume_5,
					  _diluted_sample_volume_5,_diluent_volume_5,_sample_volume_6,_diluted_sample_volume_6,
					  _diluent_volume_6,item_id);
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
 * breif: ��ָ���ļ�¼���и��µ�ǰ�ķ�����Ϣ��
 * param: record - ָ���ļ�¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int StandardApplication::update(MtADORecordset &record){
	//1.������ǰ�������������
	StandardApplication standard;
	_variant_t value;
	long index=257;
	//2.��ָ���ļ�¼���л�ȡЧ׼Һ���1��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	standard._calibrator_code_1=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡЧ׼Һ���2��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	standard._calibrator_code_2=MtADODataConverter::to_int(value);
	//4.��ָ���ļ�¼���л�ȡЧ׼Һ���3��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	standard._calibrator_code_3=MtADODataConverter::to_int(value);
	//5.��ָ���ļ�¼���л�ȡЧ׼Һ���4��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	standard._calibrator_code_4=MtADODataConverter::to_int(value);
	//6.��ָ���ļ�¼���л�ȡЧ׼Һ���5��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	standard._calibrator_code_5=MtADODataConverter::to_int(value);
	//7.��ָ���ļ�¼���л�ȡЧ׼Һ���6��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	standard._calibrator_code_6=MtADODataConverter::to_int(value);

	//8.��ָ���ļ�¼���л�ȡ���������1��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	standard._sample_volume_1=MtADODataConverter::to_double(value);
	//9.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������1��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	standard._diluted_sample_volume_1=MtADODataConverter::to_double(value);
	//10.��ָ���ļ�¼���л�ȡ��ϡ��Һ���1��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	standard._diluent_volume_1=MtADODataConverter::to_double(value);
	//11.��ָ���ļ�¼���л�ȡ���������2��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	standard._sample_volume_2=MtADODataConverter::to_double(value);
	//12.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������2��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	standard._diluted_sample_volume_2=MtADODataConverter::to_double(value);
	//13.��ָ���ļ�¼���л�ȡ��ϡ��Һ���2��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	standard._diluent_volume_2=MtADODataConverter::to_double(value);
	//14.��ָ���ļ�¼���л�ȡ���������3��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	standard._sample_volume_3=MtADODataConverter::to_double(value);
	//15.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������3��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	standard._diluted_sample_volume_3=MtADODataConverter::to_double(value);
	//16.��ָ���ļ�¼���л�ȡ��ϡ��Һ���3��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	standard._diluent_volume_3=MtADODataConverter::to_double(value);
	//17.��ָ���ļ�¼���л�ȡ���������4��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	standard._sample_volume_4=MtADODataConverter::to_double(value);
	//18.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������4��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	standard._diluted_sample_volume_4=MtADODataConverter::to_double(value);
	//19.��ָ���ļ�¼���л�ȡ��ϡ��Һ���4��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	standard._diluent_volume_4=MtADODataConverter::to_double(value);
	//20.��ָ���ļ�¼���л�ȡ���������5��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	standard._sample_volume_5=MtADODataConverter::to_double(value);
	//21.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������5��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	standard._diluted_sample_volume_5=MtADODataConverter::to_double(value);
	//22.��ָ���ļ�¼���л�ȡ��ϡ��Һ���5��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	standard._diluent_volume_5=MtADODataConverter::to_double(value);
	//23.��ָ���ļ�¼���л�ȡ���������6��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	standard._sample_volume_6=MtADODataConverter::to_double(value);
	//24.��ָ���ļ�¼���л�ȡ��ϡ�ͺ��������6��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-23);
	}
	standard._diluted_sample_volume_6=MtADODataConverter::to_double(value);
	//25.��ָ���ļ�¼���л�ȡ��ϡ��Һ���6��
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-24);
	}
	standard._diluent_volume_6=MtADODataConverter::to_double(value);
	//26.�����ǰ��ȡ�ı�׼��Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(standard.is_valid()<0){
		return(-25);
	}
	//27.���浱ǰ�ĴӼ�¼���л�ȡ�Ķ�����Ϣ��
	(*this)=standard;
	//28.�������е��˳ɹ����ء�
	return(0);
}