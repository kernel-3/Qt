#include"stdafx.h"
#include"DilutionMethods.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"DilutionMethod.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"

/**
 * name: ~DilutionMethods
 * breif: ����������
 * param: --
 * return: --
 */
DilutionMethods::~DilutionMethods(void){
	delete _lock;
}

/**
 * name: DilutionMethods
 * breif: ���캯����
 * param: --
 * return: --
 */
DilutionMethods::DilutionMethods(void)
	:_lock(new MtLock)
	,_methods(){
}

/**
 * name: instance
 * brief: ��ȡ/����ϵͳ��Ψһϡ�ͷ���������ʵ����
 * param: --
 * return: ����ָ��ϵͳ��Ψһϡ�ͷ���������ʵ����ָ�롣
 */
DilutionMethods *DilutionMethods::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * breif: ��ȡ��ǰϡ�ͷ���������
 * param: --
 * return: ���ص�ǰϡ�ͷ���������
 */
unsigned int DilutionMethods::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ص�ǰϵͳ��ϡ�ͷ�����������
	return(_methods.size());
}

/**
 * name: get_method
 * breif: ��ȡָ����ϡ�ͷ�����
 * param: index - �����ϡ�ͷ���������
 * return: �������ִ�гɹ�����ָ��ָ����ϡ�ͷ�������ָ�룬���򷵻ؿ�ָ�롣
 */
DilutionMethods::PtrToCMethod DilutionMethods::get_method(
	const unsigned int index) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������Ƿ�Ϸ���
	if((index<0)||(index>=_methods.size())){
		return(PtrToCMethod());
	}
	//3.�������е���ֱ�ӷ���ָ����ϡ�ͷ�����
	return(_methods[index]);
}

/**
 * name: update
 * brief: ��ָ�������ݿ����ظ��µ�ǰ�������ݡ�
 * param: database - �����ָ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DilutionMethods::update(Database &database){
	//1.������ǰ�������������
	Methods methods;
	const CString command(_T("SELECT * FROM [dilution_method] ORDER BY [id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(command);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡģ����Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.����ϡ�ͷ����࣬�����жϴ����Ƿ�ɹ���
		PtrToMethod method(new DilutionMethod);
		if(!static_cast<bool>(method)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и���ϡ�ͷ�����
		if(method->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰϡ�ͷ������뵽�����С�
		methods.push_back(method);
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.����Ӽ�¼���и��µ�ϡ�ͷ�����
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ�ϡ�ͷ�����
	_methods.swap(methods);
	//5.�������е��˳ɹ����ء�
	return(0);
}