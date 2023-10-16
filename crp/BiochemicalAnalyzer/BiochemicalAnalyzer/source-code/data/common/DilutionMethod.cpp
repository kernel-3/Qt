#include"stdafx.h"
#include"DilutionMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: DilutionMethod
 * brief: ���캯����
 * param: --
 * return: --
 */
DilutionMethod::DilutionMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_specimen_ratio(0)
	,_diluent_ratio(0){
}

/**
 * name: ~DilutionMethod
 * brief: ����������
 * param: --
 * return: --
 */
DilutionMethod::~DilutionMethod(void){
}

/**
 * name: set_id
 * breif: ����ϡ�ͷ�����ʶ��
 * param: id - �����ϡ�ͷ�����ʶ��
 * return: --
 */
void DilutionMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: ��ȡϡ�ͷ�����ʶ��
 * param: --
 * return: ����ϡ�ͷ�����ʶ��
 */
int DilutionMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * breif: ����ϡ�ͷ������ơ�
 * param: name - �����ϡ�ͷ������ơ�
 * return: --
 */
void DilutionMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: ��ȡϡ�ͷ������ơ�
 * param: --
 * return: ����ϡ�ͷ������ơ�
 */
CString DilutionMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: ����ϡ�ͷ���������
 * param: alias - �����ϡ�ͷ���������
 * return: --
 */
void DilutionMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: ��ȡϡ�ͷ���������
 * param: --
 * return: ����ϡ�ͷ���������
 */
CString DilutionMethod::get_alias() const{
	return(_alias);
}

/**
 * name: set_specimen_ratio
 * breif: ��������������
 * param: specimen_ratio - ���������������
 * return: --
 */
void DilutionMethod::set_specimen_ratio(const int specimen_ratio){
	_specimen_ratio=specimen_ratio;
}

/**
 * name: get_specimen_ratio
 * brief: ��ȡ����������
 * parma: --
 * return: ��������������
 */
int DilutionMethod::get_specimen_ratio() const{
	return(_specimen_ratio);
}

/**
 * name: set_diluent_ratio
 * breif: ����ϡ��Һ������
 * param: diluent_ratio - �����ϡ��Һ������
 * return: --
 */
void DilutionMethod::set_diluent_ratio(const int diluent_ratio){
	_diluent_ratio=diluent_ratio;
}

/**
 * name: get_diluent_ratio
 * breif: ��ȡϡ��Һ������
 * param: --
 * return: ����ϡ��Һ������
 */
int DilutionMethod::get_diluent_ratio() const{
	return(_diluent_ratio);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰϡ��Һ�����Ƿ���Ч��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DilutionMethod::is_valid() const{
	//1.��⵱ǰϡ�ͷ�����ʶ�Ƿ�Ϸ���
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.��⵱ǰϡ�ͷ��������Ƿ�Ϸ���
	if(_T("")==_name){
		return(-2);
	}
	//3.��⵱ǰϡ�ͷ��������Ƿ�Ϸ���
	if(_T("")==_alias){
		return(-3);
	}
	//4.��⵱ǰ���������Ƿ�Ϸ���
	if((_specimen_ratio<1)||(_specimen_ratio>9999)){
		return(-4);
	}
	//5.��⵱ǰϡ��Һ�����Ƿ�Ϸ���
	if((_diluent_ratio<1)||(_diluent_ratio>9999)){
		return(-5);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * breif: ��ָ���ļ�¼�������ظ��µ�ǰ�������ݡ�
 * param: recordset - �����ָ����¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DilutionMethod::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	//DilutionMethod dilution_method;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡϡ�ͷ�����ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*dilution_method.*/_id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡϡ�ͷ������ơ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*dilution_method.*/_name=MtADODataConverter::to_string(value);
	//4.��ָ���ļ�¼���л�ȡϡ�ͷ���������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*dilution_method.*/_alias=MtADODataConverter::to_string(value);
	//5.��ָ���ļ�¼���л�ȡϡ�ͷ���������������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	/*dilution_method.*/_specimen_ratio=MtADODataConverter::to_int(value);
	//6.��ָ���ļ�¼���л�ȡϡ�ͷ�����ϡ��Һ������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(4));
	if(0!=recordset.get_last_error_code()){
		return(-5);
	}
	/*dilution_method.*/_diluent_ratio=MtADODataConverter::to_int(value);
	//7.�жϴ����ݿ��м��ص�ϡ�ͷ����Ƿ�Ϸ���
	if(/*analysis_method.*/is_valid()<0){
		return(-6);
	}
	//8.Ϊ��ǰ����������ֵ��
	//(*this)=dilution_method;
	//9.�������е��ˣ��ɹ����ء�
	return(0);
}