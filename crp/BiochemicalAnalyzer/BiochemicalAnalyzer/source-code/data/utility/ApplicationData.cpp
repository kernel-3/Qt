#include"stdafx.h"
#include"ApplicationData.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"

/**
 * name: ApplicationData
 * breif: ���캯����
 * param: --
 * return: --
 */
ApplicationData::ApplicationData(void)
	:_module_id(0)
	,_specimen_type_id(0)
	,_item_id(0){
}

/**
 * name: ApplicationData
 * breif: ���캯����
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - ������������ͱ�ʶ��
 *        item_id - �������Ŀ��ʶ��
 * return: --
 */
ApplicationData::ApplicationData(const int module_id,
	const int specimen_type_id,const int item_id)
	:_module_id(module_id)
	,_specimen_type_id(specimen_type_id)
	,_item_id(item_id){
}

/**
 * name: ~ApplicationData
 * breif: ����������
 * param: --
 * return: --
 */
ApplicationData::~ApplicationData(void){
}

/**
 * name: set_module_id
 * breif: ����ģ���ʶ��
 * param: module_id - �����ģ���ʶ��
 * return: --
 */
void ApplicationData::set_module_id(const int module_id){
	_module_id=module_id;
}

/**
 * name: get_module_id
 * brief: ��ȡģ���ʶ��
 * param: --
 * return: ����ģ���ʶ��
 */
int ApplicationData::get_module_id() const{
	return(_module_id);
}

/**
 * name: set_specimen_type_id
 * breif: �����������ͱ�ʶ��
 * param: specimen_type_id - ������������ͱ�ʶ��
 * return: --
 */
void ApplicationData::set_specimen_type_id(const int specimen_type_id){
	_specimen_type_id=specimen_type_id;
}

/**
 * name: get_specimen_type_id
 * brief: ��ȡ�������ͱ�ʶ��
 * param: --
 * return: ����ģ���ʶ��
 */
int ApplicationData::get_specimen_type_id() const{
	return(_specimen_type_id);
}

/**
 * name: set_item_id
 * breif: ������Ŀ��ʶ��
 * param: item_id - �������Ŀ��ʶ��
 * return: --
 */
void ApplicationData::set_item_id(const int item_id){
	_item_id=item_id;
}

/**
 * name: get_item_id
 * breif: ��ȡ��Ŀ��ʶ��
 * param: --
 * return: ������Ŀ��ʶ��
 */
int ApplicationData::get_item_id() const{
	return(_item_id);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ������������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ������������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationData::is_valid(CString *error_message) const{
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��յ�ǰ������Ϣ��
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//3.���ģ���ʶ�Ƿ�Ϸ���
	if((_module_id<1)||(_module_id>5)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING243),1,5);
		}
		return(-1);
	}
	//4.����������ͱ�ʶ�Ƿ�Ϸ���
	if((_specimen_type_id<1)||(_specimen_type_id>10)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING244),1,10);
		}
		return(-2);
	}
	//5.�����Ŀ��ʶ�Ƿ�Ϸ���
	if((_item_id<1)||(_item_id>999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING245),1,999);
		}
		return(-3);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * breif: ����ǰ������������ΪĬ��ֵ��
 * param: reagent_code - ������Լ����롣
 * return: --
 */
void ApplicationData::reset_default_value(const int /*reagent_code=0*/){
}

/**
 * name: update
 * breif: ��ָ���ļ�¼�������ظ������ݡ�
 * param: recordset - ����ļ�¼����
 *        column - ����/�����ȡ��ǰ/��һ����¼�����С�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationData::update(MtADORecordset &recordset,int &column){
	//1.������ǰ�������������
	_variant_t value;
	//2.��ȡ��ǰ��¼����ģ���ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	_module_id=MtADODataConverter::to_int(value);
	//3.��ȡ��ǰ��¼�����������ͱ�ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	_specimen_type_id=MtADODataConverter::to_int(value);
	//4.��ȡ��ǰ��¼������Ŀ��ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	_item_id=MtADODataConverter::to_int(value);
	//5.�жϵ�ǰ��ȡ��Ӧ�������Ƿ�Ϸ���
	/*
	if(is_valid()<0){
		return(-4);
	}
	*/
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: �����е������ύ�����ݿ��С�
 * param: commit_means -  ������ύ��ʽ��1 ���� 2 ���£���
 *        database - �����Ŀ�����ݿ����á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationData::commit(
	const int /*commit_means*/,Database & /*database*/) const{
	return(0);
}