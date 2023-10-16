#include"stdafx.h"
#include"Module.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"

/**
 * name: Module
 * breif: ���캯����
 * param: --
 * return: --
 */
Module::Module(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T("")){
}

/**
 * name: ~Module
 * breif: ����������
 * param: --
 * return: --
 */
Module::~Module(void){
}

/**
 * name: set_id
 * breif: ����ģ��ID��
 * param: id - ģ��ID��
 * return: --
 */
void Module::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: ��ȡģ��ID��
 * param: --
 * return: ����ģ��ID��
 */
int Module::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * breif: ����ģ�����ơ�
 * param: name - ģ�����ơ�
 * return: --
 */
void Module::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: ��ȡģ�����ơ�
 * param: --
 * return: ����ģ�����ơ�
 */
CString Module::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: ����ģ�������
 * param: alias - ģ�������
 * return: --
 */
void Module::set_alias(const CString alias){
	_alias=alias;
}

/**
 * name: get_alias
 * breif: ��ȡģ�������
 * param: --
 * return: ����ģ�������
 */
CString Module::get_alias() const{
	return(_alias);
}

/**
 * name: is_valid
 * breif: ���鵱ǰģ����Ϣ�Ƿ�Ϸ���
 * param: error_message - ����Ĵ�����Ϣ���޴���ʱ�������Ϣ����
 * return: �����ǰģ����Ϣ�Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Module::is_valid(CString *error_message/*=0*/) const{
	//1.��յ�ǰ������Ϣ��
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.�����ǰģ��ID���Ϸ���
	if((_id<1)||(_id>5)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING484),1,5);
		}
		return(-1);
	}
	//2.�����ǰģ�����Ʋ��Ϸ���
	if(_T("")==_name){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING485);
		}
		return(-2);
	}
	//3.�����ǰģ��������Ϸ���
	if(_T("")==_alias){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING486);
		}
		return(-3);
	}
	//4.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: update
 * breif: �����ݿ������ظ��µ�ǰ�������ݡ�
 * param: recordset - ���ݿ��¼�����á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Module::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	Module module;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡģ��ID��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	module._id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡģ�����ơ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	module._name=MtADODataConverter::to_string(value);
	//4.��ָ���ļ�¼���л�ȡģ�������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	module._alias=MtADODataConverter::to_string(value);
	//5.�жϴ����ݿ��м��ص�ģ����Ϣ�Ƿ�Ϸ���
	if(module.is_valid()<0){
		return(-4);
	}
	//6.Ϊ��ǰ��Ŀ��Ϣ��ֵ��
	(*this)=module;
	//7.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: commit
 * breif: ����ǰ��ģ����Ϣ�ύ�����ݿ��С�
 * param: commit_means - �ύ��ʽ��1 ���� 2 ���£���
 *        database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Module::commit(const int commit_means,Database &database) const{
	//1.�жϵ�ǰ�洢��ģ����Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);
	}
	//2.�γ�ģ����Ϣ�ύ���ݿ��ִ����䡣
	//2-1.������ǰ�������������
	CString command(_T(""));
	//2-2.�����ǰ�ύ��ʽΪInsert��ʽ�ύ��
	if(1==commit_means){
		command.Format(_T("INSERT INTO [module]([id],[name],\
			[alias])VALUES('%d','%s','%s')"),_id,_name,_alias);
	}
	//2-3.�����ǰ�ύ��ʽΪUpdate��ʽ�ύ��
	else if(2==commit_means){
		command.Format(_T("UPDATE [module] SET [name]='%s',\
			[alias]='%s' WHERE [id]='%d'"),_name,_alias,_id);
	}
	//2-4.�����ǰ�ύ��ʽδ֪��
	else{
		return(-2);
	}
	//3.�������ύ���ݿ⡣
	if(database.execute(command)<0){
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}