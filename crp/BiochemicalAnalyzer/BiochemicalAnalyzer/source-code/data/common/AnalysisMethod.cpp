#include"stdafx.h"
#include"AnalysisMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: AnalysisMethod
 * breif: ���캯����
 * param: --
 * return: --
 */
AnalysisMethod::AnalysisMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_expression(_T("")){
}

/**
 * name: ~AnalysisMethod
 * breif: ����������
 * param: --
 * return: --
 */
AnalysisMethod::~AnalysisMethod(void){
}

/**
 * name: set_id
 * brief: ���÷���������ʶ��
 * param: id - ����ķ���������ʶ��
 * return: --
 */
void AnalysisMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * brief: ��ȡ����������ʶ��
 * param: --
 * return: ���ط���������ʶ��
 */
int AnalysisMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * brief: ���÷����������ơ�
 * param: name - ����ķ����������ơ�
 * return: --
 */
void AnalysisMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * brief: ��ȡ�����������ơ�
 * param: --
 * return: ���ط����������ơ�
 */
CString AnalysisMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: ���÷�������������
 * param: alias - ����ķ�������������
 * return: --
 */
void AnalysisMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: ��ȡ��������������
 * param: --
 * return: ���ط�������������
 */
CString AnalysisMethod::get_alias() const{
	return(_alias);
}

/**
 * name: set_expression
 * brief: ���÷����������ʽ��
 * param: expression - ����ķ����������ʽ��
 * return: --
 */
void AnalysisMethod::set_expression(const CString &expression){
	_expression=expression;
}

/**
 * name: get_expression
 * brief: ��ȡ�����������ʽ��
 * param: --
 * return: ���ط����������ʽ��
 */
CString AnalysisMethod::get_expression() const{
	return(_expression);
}

/**
 * name: is_valid
 * breif: ��⵱ǰ�����������������Ƿ�Ϸ���
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int AnalysisMethod::is_valid() const{
	//1.�����ǰ����������ʶ���Ϸ���
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.�����ǰ�����������Ʋ��Ϸ���
	if(_T("")==_name){
		return(-2);
	}
	//3.�����ǰ���������������Ϸ���
	if(_T("")==_alias){
		return(-3);
	}
	//4.�����ǰ����������ʽ���Ϸ���
	if(_T("")==_expression){
		return(-4);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * breif: ��ָ���ļ�¼�������ظ��µ�ǰ�������ݡ�
 * param: recordset - �����ָ����¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int AnalysisMethod::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	//AnalysisMethod analysis_method;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡ����������ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*analysis_method.*/_id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡ�����������ơ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*analysis_method.*/_name=MtADODataConverter::to_string(value);
	//4.��ָ���ļ�¼���л�ȡ��������������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*analysis_method.*/_alias=MtADODataConverter::to_string(value);
	//5.��ָ���ļ�¼���л�ȡ����������ʽ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	/*analysis_method.*/_expression=MtADODataConverter::to_string(value);
	//6.�жϴ����ݿ��м��صķ��������Ƿ�Ϸ���
	if(/*analysis_method.*/is_valid()<0){
		return(-5);
	}
	//7.Ϊ��ǰ����������ֵ��
	//(*this)=analysis_method;
	//8.�������е��ˣ��ɹ����ء�
	return(0);
}