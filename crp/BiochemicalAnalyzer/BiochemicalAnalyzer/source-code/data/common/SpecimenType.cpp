#include"stdafx.h"
#include"SpecimenType.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: SpecimenType
 * brief: ���캯����
 * param: --
 * return: --
 */
SpecimenType::SpecimenType(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T("")){
}

/**
 * name: ~SpecimenType
 * brief: ����������
 * param: --
 * return: --
 */
SpecimenType::~SpecimenType(void){
}

/**
 * name: set_id
 * breif: �����������ͱ�ʶ��
 * param: id - �������ͱ�ʶ��
 * return: --
 */
void SpecimenType::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * brief: ��ȡ�������ͱ�ʶ��
 * parma: --
 * return: �����������ͱ�ʶ��
 */
int SpecimenType::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * breif: ���������������ơ�
 * param: name - �����������ơ�
 * return: --
 */
void SpecimenType::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: ��ȡ�����������ơ�
 * param: --
 * return: ���������������ơ�
 */
CString SpecimenType::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: �����������ͱ�����
 * param: alias - �������ͱ�����
 * return: --
 */
void SpecimenType::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * breif: ��ȡ�������ͱ�����
 * param: --
 * return: �����������ͱ�����
 */
CString SpecimenType::get_alias() const{
	return(_alias);
}

/**
 * name: is_valid
 * breif: �жϵ�ǰ����������Ϣ�Ƿ���Ч��
 * param: error_message - ����Ĵ�����Ϣ���޴���ʱ��������ϢΪ�գ���
 * return: �����ǰ����������Ϣ��Ч���򷵻�ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int SpecimenType::is_valid(CString *error_message/*=0*/) const{
	//1.��յ�ǰ������Ϣ��
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.�����ǰ�������ͱ�ʶ�Ƿ���
	if((_id<1)||(_id>10)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING487),1,10);
		}
		return(-1);
	}
	//2.�����ǰ�����������ƷǷ���
	if(_T("")==_name){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING488);
		}
		return(-2);
	}
	//3.�����ǰ�������ͱ����Ƿ���
	if(_T("")==_alias){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING489);
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
int SpecimenType::update(MtADORecordset &recordset){
	//1.������ǰ�������������
	SpecimenType specimen_type;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡ��������ID��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	specimen_type._id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡ�����������ơ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	specimen_type._name=MtADODataConverter::to_string(value);
	//4.��ָ���ļ�¼���л�ȡ�������ͱ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	specimen_type._alias=MtADODataConverter::to_string(value);
	//5.�жϴ����ݿ��м��ص�����������Ϣ�Ƿ�Ϸ���
	if(specimen_type.is_valid()<0){
		return(-4);
	}
	//6.Ϊ��ǰ����������Ϣ��ֵ��
	(*this)=specimen_type;
	//7.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: commit
 * breif: ����ǰ������������Ϣ�ύ�����ݿ��С�
 * param: commit_means - �ύ��ʽ��1 ���� 2 ���£���
 *        database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenType::commit(const int commit_means,Database &database) const{
	//1.�жϵ�ǰ�洢������������Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);
	}
	//2.�γ�ģ����Ϣ�ύ���ݿ��ִ����䡣
	//2-1.������ǰ�������������
	CString command(_T(""));
	//2-2.�����ǰ�ύ��ʽΪInsert��ʽ�ύ��
	if(1==commit_means){
		command.Format(_T("INSERT INTO [specimen_type]([id],[name],\
			[alias])VALUES('%d','%s','%s')"),_id,_name,_alias);
	}
	//2-3.�����ǰ�ύ��ʽΪUpdate��ʽ�ύ��
	else if(2==commit_means){
		command.Format(_T("UPDATE [specimen_type] SET [name]='%s',\
			[alias]='%s' WHERE [id]='%d'"),_name,_alias,_id);
	}
	//2-4.�����ǰ�ύ��ʽδ֪��
	else{
		return(-2);
	}
	//2-5.�������ύ���ݿ⡣
	if(database.execute(command)<0){
		return(-3);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}