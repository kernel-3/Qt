#include"stdafx.h"
#include"CalibrationMethods.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"CalibrationMethod.h"

/**
 * name: ~CalibrationMethods
 * brief: ����������
 * param: --
 * return: --
 */
CalibrationMethods::~CalibrationMethods(void){
	delete _lock;
}

/**
 * name: instance
 * brief: ��ȡ/����ϵͳ��Ψһ���귽��������ʵ����
 * param: --
 * return: ����ָ��ϵͳ��Ψһ���귽��������ʵ����ָ�롣
 */
CalibrationMethods *CalibrationMethods::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * breif: ��ȡ��ǰϵͳ�ж��귽����������
 * param: --
 * return: ���ص�ǰϵͳ�ж��귽����������
 */
unsigned int CalibrationMethods::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ص�ǰϵͳ�ж��귽����������
	return(_methods.size());
}

/**
 * name: get_method
 * breif: ��ȡָ���Ķ��귽����
 * param: index - ����Ķ��귽��������
 * return: �������ִ�гɹ�����ָ��ָ���Ķ��귽������ָ�룬���򷵻ؿ�ָ�롣
 */
CalibrationMethods::PtrToCMethod CalibrationMethods::get_method(
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
int CalibrationMethods::update(Database &database){
	//1.������ǰ�������������
	Methods methods;
	const CString command(_T("SELECT * FROM [calibration_method] ORDER BY [id] ASC"));
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
		PtrToMethod method(new CalibrationMethod);
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
 * name: CalibrationMethods
 * brief: ���캯����
 * param: --
 * return: --
 */
CalibrationMethods::CalibrationMethods(void)
	:_lock(new MtLock)
	,_methods(){
}