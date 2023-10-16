#include"stdafx.h"
#include"ApplicationParameters.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"ApplicationParameter.h"
#include"ApplicationAnalysisData.h"
#include"../common/Module.h"
#include"../common/Modules.h"
#include"../common/SpecimenType.h"
#include"../common/SpecimenTypes.h"

/**
 * name: generate_key
 * breif: ����ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ����������
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - ������������ͱ�ʶ��
 *        item_id - �������Ŀ��ʶ��
 * return: �������ɵ�������
 * remark: ���ô����㷨���ɵ�����ֻ��������1λģ���ʶ��
 *         1λ�������ͱ�ʶ�Լ�3λ��Ŀ��ʶ��
 */
static int generate_key(const int module_id,
	const int specimen_type_id,const int item_id){
	return(module_id*10000+specimen_type_id*1000+item_id);
}

/**
 * name: ~ApplicationParameters
 * breif: ����������
 * param: --
 * return: --
 */
ApplicationParameters::~ApplicationParameters(void){
	delete _lock;
}

/**
 * name: ApplicationParameters
 * breif: ���캯����
 * param: --
 * return: --
 */
ApplicationParameters::ApplicationParameters(void)
	:_lock(new MtLock)
	,_parameters(){
}

/**
 * name: instance
 * breif: ��ȡ��ǰ����ϵͳ��Ψһʵ����
 * param: --
 * return: ����ָ��ǰ����ϵͳ��Ψһʵ����ָ�롣
 */
ApplicationParameters *ApplicationParameters::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: add
 * brief: ���һ��������
 * param: parameter - ����Ĳ�����
 * return: ���������ӳɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameters::add(const PtrToParameter &parameter){
	//1.�����������Ƿ�Ϸ���
	if(!static_cast<bool>(parameter)){
		return(-1);
	}
	if(parameter->is_valid()<0){
		return(-2);
	}
	//2.������������ļ�ֵ��
	const int key=generate_key(parameter->get_module_id(),
		parameter->get_specimen_type_id(),parameter->get_item_id());
	//3.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4.�����ֵ�Ѿ����ڣ���ֱ�ӷ�����Ӧ����
	if(_parameters.end()!=_parameters.find(key)){
		return(-3);
	}
	//5.��ӵ�ǰ������
	_parameters[key]=parameter;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get
 * breif: ����ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ��ȡָ����
 *        Ӧ�ò�����Ϣ��
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - ������������ͱ�ʶ��
 *        item_id - �������Ŀ��ʶ��
 * return: �����ȡӦ�ò����ɹ�����ָ��Ӧ�ò���������ָ�룬
 *         ���򷵻ؿ�ָ�롣
 */
ApplicationParameters::PtrToCParameter ApplicationParameters::get(
	const int module_id,const int specimen_type_id,const int item_id) const{
	//1.����Ӧ�ò���������
	const int key=generate_key(module_id,specimen_type_id,item_id);
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ֵ�Ƿ���ڣ�����������򷵻ؿ�ָ�롣
	if(_parameters.end()==_parameters.find(key)){
		return(PtrToCParameter());
	}
	//4.����ָ���Ĳ�����
	return((const_cast<ApplicationParameters*>(this)->_parameters)[key]);
}

/**
 * name: modify
 * brief: �޸�ָ���Ĳ�����
 * param: parameter - �����ָ��������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameters::modify(const ApplicationAnalysisData &parameter){
	//1.����Ӧ�ò���������
	const int key=generate_key(parameter.get_module_id(),
		parameter.get_specimen_type_id(),parameter.get_item_id());
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ֵ�Ƿ���ڣ������������ֱ�ӷ��ش���
	if(_parameters.end()==_parameters.find(key)){
		return(-1);
	}
	//4.���׼���޸ĵĲ����Ƿ���ڣ������������ֱ�ӷ��ش���
	if(!static_cast<bool>(_parameters[key])){
		return(-2);
	}
	//5.��ָ���Ĳ��������޸�,�����ж��޸��Ƿ�ɹ���
	if(_parameters[key]->modify(parameter)<0){
		return(-3);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: remove
 * brief: ɾ��ָ����Ŀ��Ӧ�ò�����
 * param: item_id - �����ָ����Ŀ��ʶ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameters::remove(const int item_id){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰϵͳ�е�ģ���Լ���������������
	const unsigned int module_count=(
		Modules::instance())->get_count();
	const unsigned int specimen_type_count=(
		SpecimenTypes::instance())->get_count();
	if((0==module_count)||(0==specimen_type_count)){
		return(-1);
	}
	//3.����ģ���Լ��������ͣ�ɾ��ָ��ģ�顢���������µ���Ŀ������Ϣ��
	for(unsigned int module_index=0;
		module_index!=module_count;++module_index){
		for(unsigned int specimen_type_index=0;
			specimen_type_index!=specimen_type_count;
			++specimen_type_index){
			//3-1.��ȡ��ǰģ���Լ�����������Ϣ��
			Modules::PtrToCModule module=(Modules::instance())->
				get_by_index(module_index);
			SpecimenTypes::PtrToCSpecimenType specimen_type=
				(SpecimenTypes::instance())->get_by_index(
				specimen_type_index);
			//3-2.�ж�ģ�顢����������Ϣ�Ƿ�Ϸ���
			if((!static_cast<bool>(module))||(
				!static_cast<bool>(specimen_type))){
				return(-2);
			}
			//3-3.���ݵ�ǰ��ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ��������Key��
			const int key=generate_key(module->get_id(),
				specimen_type->get_id(),item_id);
			//3-4.����ָ������Ŀ������������ҳɹ������ɾ��������
			Parameters::iterator iterator=_parameters.find(key);
			if(_parameters.end()==iterator){
				return(-3);
			}else{
				_parameters.erase(iterator);
			}
		}
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * brief: �����ݿ������ظ������ݡ�
 * param: database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameters::update(Database &database){
	//1.������ǰ�������������
	Parameters parameters;
	//remark: �˴��Է���������Ϊ�������ϲ�ѯ����Ϊ���û�з��������������������������塣
	const CString command(_T("SELECT * FROM [analyze_application] ORDER BY \
		[analyze_application].[module_id],[analyze_application].[specimen_type_id],\
		[analyze_application].[item_id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(command);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡӦ�ò�����Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.����Ӧ�ò����������жϴ����Ƿ�ɹ���
		PtrToParameter parameter(new ApplicationParameter);
		if(!static_cast<bool>(parameter)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и������������
		if(parameter->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰ������������뵽�����С�
		const int key=generate_key(parameter->get_module_id(),
			parameter->get_specimen_type_id(),parameter->get_item_id());
		if(parameters.end()!=parameters.find(key)){
			return(-5);
		}
		parameters[key]=parameter;
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-6);
		}
	}
	//4.����Ӽ�¼���и��µ����������
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ����������
	_parameters.swap(parameters);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * breif: �����ݿ��ύָ����Ŀ�Ĳ�����Ϣ��
 * param: item_id - �������Ŀ��ʶ��
 *        commit_means - ������ύ������1 ��� 2 ���� 3 ɾ������
 *        database - �����Ŀ�����ݿ⡣
 *        is_transaction - ������Ƿ�������ʽ�������ݿ��ǡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationParameters::commit(const int item_id,
	const int commit_means,Database &database,
	const BOOL is_transaction/*=TRUE*/) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰϵͳ�е�ģ���Լ���������������
	const unsigned int module_count=(
		Modules::instance())->get_count();
	const unsigned int specimen_type_count=(
		SpecimenTypes::instance())->get_count();
	if((0==module_count)||(0==specimen_type_count)){
		return(-1);
	}
	//3.�����ǰ������ȡ����ʽ�������ݿ����ݣ�
	//  ���������������ʧ����ֱ�ӷ��ش���
	if(is_transaction){
		if(database.begin_trans()<0){
			return(-2);
		}
	}
	//4.����ģ���Լ��������ͣ��ύָ��ģ�顢���������µ���Ŀ������Ϣ�����ݿ��С�
	for(unsigned int module_index=0;module_index!=module_count;
		++module_index){
		for(unsigned int specimen_type_index=0;specimen_type_index!=
			specimen_type_count;++specimen_type_index){
			//4-1.��ȡ��ǰģ���Լ�����������Ϣ��
			Modules::PtrToCModule module=(Modules::instance())->
				get_by_index(module_index);
			SpecimenTypes::PtrToCSpecimenType specimen_type=
				(SpecimenTypes::instance())->get_by_index(
				specimen_type_index);
			//4-2.�жϵ�ǰģ���Լ�������Ϣ�Ƿ�Ϸ���
			if((!static_cast<bool>(module))||(
				!static_cast<bool>(specimen_type))){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-3);
			}
			//4-3.���ݵ�ǰ��ģ���ʶ���������ͱ�ʶ�Լ���Ŀ��ʶ��������Key��
			const int key=generate_key(module->get_id(),
				specimen_type->get_id(),item_id);
			//4-4.����ָ������Ŀ�����������жϲ����Ƿ�ɹ���
			Parameters::const_iterator iterator=_parameters.find(key);
			if(_parameters.end()==iterator){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-4);
			}
			if(!static_cast<bool>(iterator->second)){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-5);
			}
			//4-5.��ָ���Ĳ����ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
			if(iterator->second->commit(commit_means,database,FALSE)<0){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-6);
			}
		}
	}
	//5.�����ǰ����������ʽ�������ݿ⣬�������ݿ��ύ����
	if(is_transaction){
		if(database.commit_trans()<0){
			database.rollback_trans();
			return(-7);
		}
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}