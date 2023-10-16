#include"stdafx.h"
#include"Modules.h"
#include"Module.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../global/Database.h"
#include<assert.h>

/**
 * name: ~Modules
 * breif: ����������
 * param: --
 * return: --
 */
Modules::~Modules(void){
	delete _lock;
}

/**
 * name: Modules
 * breif: ���캯����
 * param: --
 * return: --
 */
Modules::Modules(void)
	:_lock(new MtLock)
	,_modules(){
}

/**
 * name: instance
 * brief: ��ȡ��ǰ����ϵͳ�е�Ψһʵ����ָ�롣
 * param: --
 * return: ���ص�ǰ����ϵͳ�е�Ψһʵ����ָ�롣
 */
Modules *Modules::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: ��ȡģ��������
 * param: --
 * return: ����ģ��������
 */
unsigned int Modules::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ģ��������
	return(_modules.size());
}

/**
 * name: get_by_id
 * breif: ����ģ���ʶ��ȡָ����ģ����Ϣ��
 * param: id - �����ģ���ʶ��
 * return: �����ȡָ��ģ��ɹ�����ָ����ģ������ָ�룬���򷵻ؿ�ָ�롣
 */
Modules::PtrToCModule Modules::get_by_id(const int id) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������ָ��ģ����Ϣ��
	for(VModules::const_iterator iterator=_modules.begin();
		iterator!=_modules.end();++iterator){
		assert(static_cast<bool>(*iterator));
		if(id==(*iterator)->get_id()){
			return(*iterator);
		}
	}
	//3.�������е���ֱ�ӷ��ؿ�ָ�롣
	return(PtrToCModule());
}

/**
 * name: get_by_index
 * breif: ����ģ��������Ż�ȡָ����ģ����Ϣ��
 * param: index - �����ģ��������š�
 * return: �����ȡָ��ģ��ɹ�����ָ����ģ������ָ�룬���򷵻ؿ�ָ�롣
 */
Modules::PtrToCModule Modules::get_by_index(const unsigned int index) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������Ƿ�Ϸ���
	if((index<0)||(index>=(_modules.size()))){
		return(PtrToCModule());
	}
	//3.����ָ����ģ����Ϣ��
	return(_modules[index]);
}

/**
 * name: update
 * brief: �����ݿ������ظ������ݡ�
 * param: database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Modules::update(Database &database){
	//1.������ǰ�������������
	VModules modules;
	const CString sql(_T("SELECT * FROM [module] ORDER BY [id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡģ����Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.����ģ����Ϣ�࣬�����жϴ����Ƿ�ɹ���
		PtrToModule module(new Module);
		if(!static_cast<bool>(module)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и���ģ����Ϣ��
		if(module->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰ��ģ����Ϣ���뵽�����С�
		modules.push_back(module);
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.����Ӽ�¼���и��µ�ģ����Ϣ��
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ����������
	_modules.swap(modules);
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
int Modules::commit(const int commit_means,Database &database) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�������ݿ����񣬲����жϿ����Ƿ�ɹ���
	if(database.begin_trans()<0){
		return(-1);
	}
	//3.������ǰģ����Ϣ�������ύ���е�ģ����Ϣ�����ݿ��С�
	for(VModules::const_iterator iterator=_modules.begin();
		iterator!=_modules.end();++iterator){
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
 * param: module_id - ָ����ģ���ʶ��
 *        commit_means - �ύ��ʽ��1 ���� 2 ���£���
 *        database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Modules::commit(const int module_id,
	const int commit_means,Database &database) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ǰģ����Ϣ�������ύָ����ģ����Ϣ�����ݿ��С�
	//remark: ��Ϊģ����������٣����в��ñ������ҷ�ʽ��Ŀǰ��������ϵͳ����
	for(VModules::const_iterator iterator=_modules.begin();
		iterator!=_modules.end();++iterator){
		if(module_id==(*iterator)->get_id()){
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