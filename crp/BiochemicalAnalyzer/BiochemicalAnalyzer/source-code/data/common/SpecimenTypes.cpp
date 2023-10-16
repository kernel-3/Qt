#include"stdafx.h"
#include"SpecimenTypes.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"SpecimenType.h"
#include<assert.h>

/**
 * name: ~SpecimenTypes
 * brief: ����������
 * param: --
 * return: --
 */
SpecimenTypes::~SpecimenTypes(void){
	delete _lock;
}

/**
 * name: SpecimenTypes
 * brief: ���캯����
 * param: --
 * return: --
 */
SpecimenTypes::SpecimenTypes(void)
	:_lock(new MtLock)
	,_specimen_types(){
}

/**
 * name: instance
 * breif: ��ȡ��ǰϵͳ��Ψһ���������͹�����ʵ����
 * param: --
 * return: ���ص�ǰϵͳ��Ψһ���������͹�����ʵ����
 */
SpecimenTypes *SpecimenTypes::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: ��ȡ��������������
 * param: --
 * return: ������������������
 */
unsigned int SpecimenTypes::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰ��������������
	return(_specimen_types.size());
}

/**
 * name: get_by_id
 * breif: ���ݱ�ʶ��ȡָ��������������Ϣ��
 * param: id - ������������ͱ�ʶ��
 * return: �����ȡ����������Ϣ�ɹ����򷵻�ָ������������Ϣ��ֻ��ָ�룬����
 *         ���ؿ�ָ�롣 
 */
SpecimenTypes::PtrToCSpecimenType SpecimenTypes::get_by_id(
	const int id) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����������ͣ��ҳ�ָ��������������Ϣ��
	for(VSpecimenTypes::const_iterator iterator=_specimen_types.begin();
		iterator!=_specimen_types.end();++iterator){
		assert(static_cast<bool>(*iterator));
		if(id==(*iterator)->get_id()){
			return(*iterator);
		}
	}
	//3.����������е��ˣ�ֱ�ӷ��ؿ�ָ�롣
	return(PtrToCSpecimenType());
}

/**
 * name: get_by_index
 * breif: ����������ȡָ�����������͡�
 * param: index - �������������������
 * return: �����ȡ����������Ϣ�ɹ����򷵻�ָ������������Ϣ��ֻ��ָ�룬����
 *         ���ؿ�ָ�롣
 */
SpecimenTypes::PtrToCSpecimenType SpecimenTypes::get_by_index(
	const unsigned int index) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������Ƿ�Ϸ���
	if((index<0)&&(index>=_specimen_types.size())){
		return(PtrToCSpecimenType());
	}
	//3.����ָ��������������Ϣ��
	return(_specimen_types[index]);
}

/**
 * name: update
 * brief: �����ݿ������ظ������ݡ�
 * param: database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenTypes::update(Database &database){
	//1.������ǰ�������������
	VSpecimenTypes specimen_types;
	const CString sql(_T("SELECT * FROM [specimen_type] ORDER BY [id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡ����������Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.��������������Ϣ�࣬�����жϴ����Ƿ�ɹ���
		PtrToSpecimenType specimen_type(new SpecimenType);
		if(!static_cast<bool>(specimen_type)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и���ģ����Ϣ��
		if(specimen_type->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰ������������Ϣ���뵽�����С�
		specimen_types.push_back(specimen_type);
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.����Ӽ�¼���и��µ�����������Ϣ��
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ��������Ͳ�����
	_specimen_types.swap(specimen_types);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * breif: ����ǰ���������ύ�����ݿ��С�
 * param: commit_means - �ύ��ʽ��1 ���� 2 ���£���
 *		  database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenTypes::commit(const int commit_means,Database &database) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�������ݿ����񣬲����жϿ����Ƿ�ɹ���
	if(database.begin_trans()<0){
		return(-1);
	}
	//3.������ǰ����������Ϣ�������ύ���е�����������Ϣ�����ݿ��С�
	for(VSpecimenTypes::const_iterator iterator=_specimen_types.begin();
		iterator!=_specimen_types.end();++iterator){
		if((*iterator)->commit(commit_means,database)<0){
			database.rollback_trans();//�ع�����
			return(-2);
		}
	}
	//4.�ύ���ݿ����񣬲����ж��ύ�Ƿ�ɹ���
	if(database.commit_trans()<0){
		database.rollback_trans();//�ع�����
		return(-3);
	}
	//5.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: commit
 * breif: ����ǰ���������ύ�����ݿ��С�
 * param: specimen_type_id - ָ�����������ͱ�ʶ��
 *        commit_means - �ύ��ʽ��1 ���� 2 ���£���
 *        database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenTypes::commit(const int specimen_type_id,
	const int commit_means,Database &database) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ǰ����������Ϣ�������ύָ��������������Ϣ�����ݿ��С�
	//remark: ��Ϊģ����������٣����в��ñ������ҷ�ʽ��Ŀǰ��������ϵͳ����
	for(VSpecimenTypes::const_iterator iterator=_specimen_types.begin();
		iterator!=_specimen_types.end();++iterator){
		if(specimen_type_id==(*iterator)->get_id()){
			if((*iterator)->commit(commit_means,database)<0){
				return(-1);
			}else{
				return(0);
			}
		}
	}
	//3.�������е���ֱ�ӷ��ش���
	return(-2);
}