#include"stdafx.h"
#include"AnalysisMethods.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"AnalysisMethod.h"

/**
 * name: ~AnalysisMethods
 * brief: ����������
 * param: --
 * return: --
 */
AnalysisMethods::~AnalysisMethods(void){
	delete _lock;
}

/**
 * name: instance
 * brief: ��ȡ/����ϵͳ��Ψһ��������������ʵ����
 * param: --
 * return: ����ָ��ϵͳ��Ψһ��������������ʵ����ָ�롣
 */
AnalysisMethods *AnalysisMethods::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * breif: ��ȡ��ǰϵͳ�з���������������
 * param: --
 * return: ���ص�ǰϵͳ�з���������������
 */
unsigned int AnalysisMethods::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ص�ǰϵͳ�з���������������
	return(_methods.size());
}

/**
 * name: get_method
 * breif: ��ȡָ���ķ���������
 * param: index - ����ķ�������������
 * return: �������ִ�гɹ�����ָ��ָ���ķ�����������ָ�룬���򷵻ؿ�ָ�롣
 */
AnalysisMethods::PtrToCMethod AnalysisMethods::get_method(
	const unsigned int index) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������Ƿ�Ϸ���
	if((index<0)||(index>=_methods.size())){
		return(PtrToCMethod());
	}
	//3.�������е���ֱ�ӷ���ָ���ķ���������
	return(_methods[index]);
}

/**
 * name: update
 * brief: ��ָ�������ݿ����ظ��µ�ǰ�������ݡ�
 * param: database - �����ָ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int AnalysisMethods::update(Database &database){
	//1.������ǰ�������������
	Methods methods;
	const CString command(_T("SELECT * FROM [analysis_method] ORDER BY [id] ASC"));
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
		//3-2.�������������࣬�����жϴ����Ƿ�ɹ���
		PtrToMethod method(new AnalysisMethod);
		if(!static_cast<bool>(method)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и��·���������
		if(method->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰ�����������뵽�����С�
		methods.push_back(method);
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.����Ӽ�¼���и��µķ���������
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µķ���������
	_methods.swap(methods);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: AnalysisMethods
 * breif: ���캯����
 * param: --
 * return: --
 */
AnalysisMethods::AnalysisMethods(void)
	:_lock(new MtLock)
	,_methods(){
}