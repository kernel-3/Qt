#include"stdafx.h"
#include"CalibrationMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: CalibrationMethod
 * breif: ���캯����
 * param: --
 * return: --
 */
CalibrationMethod::CalibrationMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T("")){
}

/**
 * name: ~CalibrationMethod
 * brief: ����������
 * param: --
 * return: --
 */
CalibrationMethod::~CalibrationMethod(void){
}

/**
 * name: set_id
 * breif: ���ö��귽����ʶ��
 * param: id - ����Ķ��귽����ʶ��
 * return: --
 */
void CalibrationMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * brief: ��ȡ���귽����ʶ��
 * param: --
 * return: ���ض��귽����ʶ��
 */
int CalibrationMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * brief: ���ö��귽�����ơ�
 * param: name - ����Ķ��귽�����ơ�
 * return: --
 */
void CalibrationMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * brief: ��ȡ���귽�����ơ�
 * param: --
 * return: ���ض��귽�����ơ�
 */
CString CalibrationMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: ���ö��귽��������
 * param: alias - ����Ķ��귽��������
 * return: --
 */
void CalibrationMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * breif: ��ȡ���귽��������
 * param: --
 * return: ���ض��귽��������
 */
CString CalibrationMethod::get_alias() const{
	return(_alias);
}

/**
 * name: is_valid
 * breif: ��⵱ǰ���귽�����������Ƿ�Ϸ���
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int CalibrationMethod::is_valid() const{
	//1.�����ǰ���귽����ʶ���Ϸ���
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.�����ǰ���귽�����Ʋ��Ϸ���
	if(_T("")==_name){
		return(-2);
	}
	//3.�����ǰ���귽���������Ϸ���
	if(_T("")==_alias){
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * breif: ��ָ���ļ�¼�������ظ��µ�ǰ�������ݡ�
 * param: recordset - �����ָ����¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int CalibrationMethod::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	//CalibrationMethod calibration_method;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡ���귽����ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*calibration_method.*/_id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡ���귽�����ơ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*calibration_method.*/_name=MtADODataConverter::to_string(value);
	//4.��ָ���ļ�¼���л�ȡ���귽��������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*calibration_method.*/_alias=MtADODataConverter::to_string(value);
	//5.�жϴ����ݿ��м��صĶ��귽���Ƿ�Ϸ���
	if(/*calibration_method.*/is_valid()<0){
		return(-4);
	}
	//6.Ϊ��ǰ���귽����ֵ��
	//(*this)=calibration_method;
	//7.�������е��ˣ��ɹ����ء�
	return(0);
}