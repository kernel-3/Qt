#include"stdafx.h"
#include"ApplicationParameter.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"ApplicationAnalysisData.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include<assert.h>

/**
 * name: ApplicationParameter
 * breif: ���캯����
 * param: --
 * return: --
 */
ApplicationParameter::ApplicationParameter(void)
	:_data(new PtrToData[DATA_COUNT]){
	_data[DATA_NAME_ANALYSIS]=PtrToData(new ApplicationAnalysisData);
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
}

/**
 * name: ApplicationParameter
 * breif: ���캯����
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - ������������ͱ�ʶ��
 *        item_id - �������Ŀ��ʶ��
 * return: --
 */
ApplicationParameter::ApplicationParameter(const int module_id,
	const int specimen_type_id,const int item_id)
	:_data(new PtrToData[DATA_COUNT]){
	_data[DATA_NAME_ANALYSIS]=PtrToData(new ApplicationAnalysisData(
		module_id,specimen_type_id,item_id));
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
}

/**
 * name: ~ApplicationParameter
 * breif: ����������
 * param: --
 * return: --
 */
ApplicationParameter::~ApplicationParameter(void){
	delete[] _data;
}

/**
 * name: get_module_id
 * breif: ��ȡģ���ʶ��
 * param: --
 * return: ����ģ���ʶ��
 */
int ApplicationParameter::get_module_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_module_id());
}

/**
 * name: get_specimen_type_id
 * brief: ��ȡ�������ͱ�ʶ��
 * param: --
 * return: �����������ͱ�ʶ��
 */
int ApplicationParameter::get_specimen_type_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_specimen_type_id());
}

/**
 * name: get_item_id
 * breif: ��ȡ��Ŀ��ʶ��
 * param: --
 * return: ������Ŀ��ʶ��
 */
int ApplicationParameter::get_item_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_item_id());
}

/**
 * name: get
 * breif: ����ָ�����������ƻ�ȡӦ�ò�����ָ�������ݡ�
 * param: data_name - ������������ơ�
 * return: �����ȡӦ�ò�����ָ�������ݳɹ�����ָ��ָ
 *         �����ݵ�����ָ�룬���򷵻ؿ�ָ�롣
 */
ApplicationParameter::PtrToCData ApplicationParameter::get(
	const DataName data_name) const{
	assert(static_cast<bool>(_data[data_name]));
	return(_data[data_name]);
}

/**
 * name: modify
 * brief: �޸�ָ�����ݡ�
 * param: data - �����Ӧ�÷������ݡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameter::modify(const ApplicationAnalysisData &data){
	//1.��������Ӧ�÷��������Ƿ�Ϸ���
	if((data.is_valid()<0)||(get_module_id()!=data.get_module_id())||(
		get_specimen_type_id()!=data.get_specimen_type_id())||(
		get_item_id()!=data.get_item_id())){
		return(-1);
	}
	//2.��⵱ǰ�ڴ��д洢����Ӧ�����Ƿ�Ϸ���
	if(!static_cast<bool>(_data[DATA_NAME_ANALYSIS])){
		return(-2);
	}
	//3.�޸��ڴ��е����ݡ�
	(*dynamic_cast<ApplicationAnalysisData*>(
		_data[DATA_NAME_ANALYSIS].get()))=data;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: modify
 * breif: �޸�ָ�����ݡ�
 * param: data_name - ����׼���޸ĵ��������ơ�
 *        data - ����ָ���޸ĺ����ݵ�ָ�롣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameter::modify(
	const DataName data_name,const ApplicationData *data){
	//1.��������޸ĺ�������Ƿ�Ϸ���
	if((0==data)||(data->is_valid()<0)||(get_module_id()!=
		data->get_module_id())||(get_specimen_type_id()!=
		data->get_specimen_type_id())||(get_item_id()!=
		data->get_item_id())){
		return(-1);
	}
	//2.��⵱ǰ�ڴ��д洢����Ӧ�����Ƿ�Ϸ���
	if(!static_cast<bool>(_data[data_name])){
		return(-2);
	}
	//3.�޸�ָ�������ݡ�
	if(DATA_NAME_ANALYSIS==data_name){
		(*dynamic_cast<ApplicationAnalysisData*>(
			_data[data_name].get()))=(*dynamic_cast<
			const ApplicationAnalysisData*>(data));
	}else{
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * breif: �жϵ�ǰ�洢��Ӧ�ò��������Ƿ���Ч��
 * param: error_message - ����Ĵ�����Ϣ����û�д����ǣ����ؿ���Ϣ����
 * return: �����ǰ�洢��Ӧ�ò���������Ч����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameter::is_valid(CString *error_message/*=0*/) const{
	//1.��մ�����Ϣ��
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.����������ȫ�����ݣ������ж������Ƿ���Ч�Ϸ���
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		//2-1.�����ǰ���ݴ���,���ж����Ƿ���Ч�������Чֱ�ӷ��ش���
		if(static_cast<bool>(_data[index])){
			if(_data[index]->is_valid(error_message)<0){
				return(-1);
			}
		}
		//2-2.�����ǰ���ݲ����ڣ���ֱ�ӷ��ش���
		else{
			if(0!=error_message){
				(*error_message)=Theme::instance()->
					get_string(IDS_STRING292);
			}
			return(-2);
		}
	}
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * breif: ���ûָ���ǰ�������ݡ�
 * param: reagent_code - ������Լ���š�
 * return: --
 */
void ApplicationParameter::reset_default_value(const int reagent_code){
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		if(static_cast<bool>(_data[index])){
			if(DATA_NAME_ANALYSIS==index){
				_data[index]->reset_default_value(reagent_code);
			}else{
				_data[index]->reset_default_value();
			}
		}else{
			assert(0);
		}
	}
}

/**
 * name: update
 * breif: ��ָ���ļ�¼�������ظ������ݡ�
 * param: recordset - ָ���ļ�¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameter::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	int column=0;
	//2.����Ӧ�÷������ݣ��������õ�ǰ��¼�����·������ݡ�
	if(!static_cast<bool>(_data[DATA_NAME_ANALYSIS])){
		return(-1);
	}
	if(_data[DATA_NAME_ANALYSIS]->update(recordset,column)<0){
		return(-2);
	}
	//..�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ����ǰ���������ύ�����ݿ��С�
 * param: commit_means - ������ύ��ʽ��1 ���� 2 ���� 3 ɾ������
 *        database - �����Ŀ�����ݿ⡣
 *        is_transaction - ������Ƿ�Ϊ���ݿ������ǡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameter::commit(const int commit_means,
	Database &database,const BOOL is_transaction/*=TRUE*/) const{
	//1.�����ǰ׼���ύ�����������ݿ�����
	if(is_transaction){
		if(database.begin_trans()<0){
			return(-1);
		}
	}
	//2.����ǰ���������ύ�����ݿ��С�
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		if(!static_cast<bool>(_data[index])){
			if(is_transaction){
				database.rollback_trans();
			}
			return(-2);
		}else{
			if(_data[index]->commit(commit_means,database)<0){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-3);
			}
		}
	}
	//3.�����ǰ׼���ύ�����������ݿ�����
	if(is_transaction){
		if(database.commit_trans()<0){
			database.rollback_trans();
			return(-4);
		}
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}