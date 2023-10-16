#include"stdafx.h"
#include"Application.h"
#include"Applications.h"
#include"ApplicationFinder.h"
#include"AnalyzeApplication.h"
#include"ApplicationComparator.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../common/Item.h"
#include"../../global/Database.h"
#include"CalibrationApplication.h"
#include"RangeApplication.h"
#include"StandardApplication.h"
#include<algorithm>
#include<assert.h>

/**
 * name: ~Applications
 * breif: ����������
 * param: --
 * return: --
 */
Applications::~Applications(void){
	delete _lock;
}

/**
 * name: instance
 * brief: ��ȡϵͳΨһ��һ�����������ʵ����
 * param: --
 * return: ����ϵͳΨһ��һ�����������ʵ����
 */
Applications *Applications::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_by_item_no
 * brief: ������Ŀ��ţ���ȡ��ǰ����ָ��Ԫ�ء�
 * param: item_no - ��Ŀ��š�
 * return: �������ִ�гɹ�����ֵָ��ָ����Ŀ��ŵ�Ԫ��ָ�룬���򷵻ؿ�ָ�롣
 */
Applications::PtrToCApp Applications::get_by_item_no(const int item_no) const{
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return(PtrToApp());
	}
	//4.������Ŀ��Ų���ָ������Ŀ���������
	//4-1.����ָ������Ŀ���������
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_no,AppFinder::FIND_METHOD_BY_ITEM_NO));
	//4-2.�ж�ָ������Ŀ��������Ƿ���ҳɹ���
	if(_applications.end()==iterator){
		return(PtrToApp());
	}
	//5.���ص�ǰ���ҵ�����Ŀ���������
	return(*iterator);
}

/**
 * name: get_by_item_id
 * brief: ������Ŀ��ʶ����ȡ����ָ��Ԫ�ء�
 * param: item_id - ��Ŀ��ʶ��
 * return: �������ִ�гɹ�����ֵָ��ָ����Ŀ��ʶ��Ԫ��ָ�룬���򷵻ؿ�ָ�롣
 */
Applications::PtrToCApp Applications::get_by_item_id(const int item_id) const{
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return(PtrToApp());
	}
	//4.������Ŀ��Ų���ָ������Ŀ���������
	//4-1.����ָ������Ŀ���������
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	//4-2.�ж�ָ������Ŀ��������Ƿ���ҳɹ���
	if(_applications.end()==iterator){
		return(PtrToApp());
	}
	//5.���ص�ǰ���ҵ�����Ŀ���������
	return(*iterator);
}

/**
 * name: get_by_index
 * brief: ����������ţ���ȡ��ǰ����ָ��Ԫ�ء�
 * param: index - ָ��������š�
 * return: �������ִ�гɹ�����ָ��ָ��������ŵ�Ԫ��ָ�룬���򷵻ؿ�ָ�롣
 */
Applications::PtrToCApp Applications::get_by_index(const unsigned int index) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�жϵ�ǰ�����Ƿ�Ϸ���
	if((index<0)||(index>=_applications.size())){
		return(PtrToApp());
	}
	//3.���ص�ǰָ����������Ŀ���������
	return(_applications[index]);
}

/**
 * name: is_item_id_existing
 * brief: �ж�ָ������Ŀ��ʶ�Ƿ���ڡ�
 * param: item_id - ��Ŀ��ʶ��
 * return: ���ָ������Ŀ��ʶ�Ѿ������򷵻�TRUE�����򷵻�FALSE��
 */
BOOL Applications::is_item_id_existing(const int item_id) const{
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return(FALSE);
	}
	//4.������Ŀ��Ų���ָ������Ŀ���������
	//4-1.����ָ������Ŀ���������
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	//4-2.�ж�ָ������Ŀ��������Ƿ���ҳɹ���
	if(_applications.end()==iterator){
		return(FALSE);
	}
	//5.�������е��˳ɹ����ء�
	return(TRUE);
}

/**
 * name: is_item_no_existing
 * brief: �ж�ָ������Ŀ����Ƿ���ڡ�
 * param: item_no - ��Ŀ��š�
 * return: ���ָ������Ŀ����Ѿ������򷵻�TRUE�����򷵻�FALSE��
 */
BOOL Applications::is_item_no_existing(const int item_no) const{
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return(FALSE);
	}
	//4.������Ŀ��Ų���ָ������Ŀ���������
	//4-1.����ָ������Ŀ���������
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_no,AppFinder::FIND_METHOD_BY_ITEM_NO));
	//4-2.�ж�ָ������Ŀ��������Ƿ���ҳɹ���
	if(_applications.end()==iterator){
		return(FALSE);
	}
	//5.�������е��˳ɹ����ء�
	return(TRUE);
}

/**
 * name: sort_by_item_no
 * brief: ������Ŀ��ţ�������Ԫ�ؽ�������
 * param: --
 * return: --
 */
void Applications::sort_by_item_no(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return;
	}
	//3.�������������Ŀ�������
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_NO));
}

/**
 * name: sort_by_item_id
 * brief: ������Ŀ��ʶ��������Ԫ�ؽ�������
 * param: --
 * return: --
 */
void Applications::sort_by_item_id(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�����������Ϊ�գ���ֱ�ӷ��ء�
	if(_applications.empty()){
		return;
	}
	//3.�������������Ŀ��ʶ����
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_ID));
}

/**
 * name: add
 * brief: ��ǰ�������һ��Ԫ�ء�
 * param: application - ָ������Ԫ�ء�
 *        database - ׼���ύ���ݵ�Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::add(const PtrToApp &application,Database &database){
	//1.�жϵ�ǰ�����Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(application)){
		return(-1);
	}
	//2.����ӵ���������ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
	if(application->commit(Application::COMMIT_METHOD_INSERT,database)<0){
		return(-2);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4.��ָ��������������뵽�����С�
	_applications.push_back(application);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: remove
 * brief: ��ָ�����ݿ���ɾ��ָ������Ŀ��
 * param: item_id - ָ����Ŀ��
 *        database - ָ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::remove(const int item_id,Database &database){
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.������Ŀ��ʶ�ҵ�ָ������Ŀ������������ʧ��ֱ�ӷ��ش���
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.ɾ��ָ�����ݿ�����Ӧ���ݡ�
	//4-1.�������ݿ����񣬲����жϿ����Ƿ�ɹ���
	if(database.begin_trans()<0){
		return(-2);
	}
	//4-2.ɾ�����ݿ�����Ӧ��Ŀ�ķ������������
	CString sql(_T(""));
	sql.Format(_T("DELETE FROM [analyze_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-3);
	}
	//4-3.ɾ�����ݿ�����Ӧ��Ŀ�Ķ������������
	sql.Format(_T("DELETE FROM [calibration_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-4);
	}
	//4-4.ɾ�����ݿ�����Ӧ��Ŀ�ķ�Χ���������
	sql.Format(_T("DELETE FROM [range_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-5);
	}
	//4-5.ɾ�����ݿ�����Ӧ��Ŀ�ı�׼���������
	sql.Format(_T("DELETE FROM [standard_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-6);
	}
	//4-6.ɾ�����ݿ�����Ӧ����Ŀ��Ϣ��
	sql.Format(_T("DELETE FROM [item] WHERE [id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-7);
	}
	//4-7.�ύ���ݿ�����
	if(database.commit_trans()<0){
		database.rollback_trans();
		return(-8);
	}
	//5.ɾ��ָ����Ŀ�����������
	_applications.erase(iterator);
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * brief: ��ָ�������ݿ������ظ������ݡ�
 * param: database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::update(Database &database){
	//1.������ǰ�������������
	VecApps applications;
	const CString sql(_T("SELECT * FROM [item] LEFT JOIN [analyze_application] ON \
		[item].[id]=[analyze_application].[item_id] LEFT JOIN [calibration_application] \
		ON [item].[id]=[calibration_application].[item_id] LEFT JOIN [range_application] \
		ON [item].[id]=[range_application].[item_id] LEFT JOIN [standard_application] ON \
		[item].[id]=[standard_application].[item_id] ORDER BY [item].[id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡ���������Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-1);
		}
		//3-2.������������������жϴ����Ƿ�ɹ���
		PtrToApp application(new Application);
		if(!static_cast<bool>(application)){
			return(-2);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и������������
		if(application->update(*records)<0){
			return(-3);
		}
		//3-4.����ǰ������������뵽�����С�
		applications.push_back(application);
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-4);
		}
	}
	//4.����Ӽ�¼���и��µ����������
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ����������
	_applications.swap(applications);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ��ָ�������ݿ��ύ���ݡ�
 * param: item_id - ׼���ύ���ݵ���Ŀ��ʶ��
 *        item_alias - ���ĵ���Ŀ������
 *        analyze - ���ĵķ������������
 *        database - �ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::commit(const int item_id,const CString &item_alias,
	const AnalyzeApplication &analyze,Database &database){
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.������Ŀ��ʶ�ҵ�ָ������Ŀ������������ʧ��ֱ�ӷ��ش���
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.��¼��ǰ��Ŀ������
	const CString old_item_alias=((*iterator)->get_item()).get_alias();
	//5.���õ�ǰ��Ŀ������
	((*iterator)->get_item()).set_alias(item_alias);
	//6.�����ݿ��ύ��ǰ�޸ĵ�������Ϣ��
	//6-1.����һ������
	if(database.begin_trans()<0){
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-2);
	}
	//6-2.�����ݿ��ύ��Ŀ��Ϣ��
	if(((*iterator)->get_item()).commit(
		Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-3);
	}
	//6-3.�����ݿ��ύ����������
	if(analyze.commit(
		item_id,Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-4);
	}
	//6-4.�����ݿ��ύ���ݡ�
	if(database.commit_trans()<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-5);
	}
	//7.�޸��ڴ��е����ݡ�
	((*iterator)->get_analyze())=analyze;
	//8.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ��ָ�������ݿ��ύ���ݡ�
 * param: item_id - ׼���ύ���ݵ���Ŀ��ʶ��
 *        calibration - ���ĵĶ������������
 *        database - �ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::commit(const int item_id,
	const CalibrationApplication &calibration,Database &database){
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.������Ŀ��ʶ�ҵ�ָ������Ŀ������������ʧ��ֱ�ӷ��ش���
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//5.�����ݿ��ύ��ǰ�޸ĵ�������Ϣ��
	if(calibration.commit(item_id,
		Application::COMMIT_METHOD_UPDATE,database)<0){
		return(-2);
	}
	//6.�޸��ڴ��е����ݡ�
	((*iterator)->get_calibration())=calibration;
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ��ָ�������ݿ��ύ���ݡ�
 * param: item_id - ׼���ύ���ݵ���Ŀ��ʶ��
 *        item_alias - ���ĵ���Ŀ������
 *        range - ���ĵķ�Χ���������
 *        database - �ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::commit(const int item_id,const CString &item_alias,
	const RangeApplication &range,Database &database){
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.������Ŀ��ʶ�ҵ�ָ������Ŀ������������ʧ��ֱ�ӷ��ش���
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.��¼��ǰ��Ŀ������
	const CString old_item_alias=((*iterator)->get_item()).get_alias();
	//5.���õ�ǰ��Ŀ������
	((*iterator)->get_item()).set_alias(item_alias);
	//6.�����ݿ��ύ��ǰ�޸ĵ�������Ϣ��
	//6-1.����һ������
	if(database.begin_trans()<0){
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-2);
	}
	//6-2.�����ݿ��ύ��Ŀ��Ϣ��
	if(((*iterator)->get_item()).commit(
		Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-3);
	}
	//6-3.�����ݿ��ύ����������
	if(range.commit(
		item_id,Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-4);
	}
	//6-4.�����ݿ��ύ���ݡ�
	if(database.commit_trans()<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-5);
	}
	//7.�޸��ڴ��е����ݡ�
	((*iterator)->get_range())=range;
	//8.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ��ָ�������ݿ��ύ���ݡ�
 * param: item_id - ׼���ύ���ݵ���Ŀ��ʶ��
 *        standard - ���ĵı�׼���������
 *        database - �ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Applications::commit(const int item_id,
	const StandardApplication &standard,Database &database){
	//1.���塣
	typedef ApplicationFinder<int> AppFinder;
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.������Ŀ��ʶ�ҵ�ָ������Ŀ������������ʧ��ֱ�ӷ��ش���
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//5.�����ݿ��ύ��ǰ�޸ĵ�������Ϣ��
	if(standard.commit(item_id,
		Application::COMMIT_METHOD_UPDATE,database)<0){
		return(-2);
	}
	//6.�޸��ڴ��е����ݡ�
	((*iterator)->get_standard())=standard;
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_size
 * brief: ��ȡ��ǰ����Ԫ�ظ�����
 * param: --
 * return: ���ص�ǰ����Ԫ�ظ�����
 */
unsigned int Applications::get_size() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ص�ǰ����Ԫ�ظ�����
	return(_applications.size());
}

/**
 * name: assign_item_id
 * breif: ����һ����Ŀ��ʶ����֤�����е���Ŀ��ʶ����ͻ��
 * param: --
 * return: ���ط������Ŀ��ʶ��
 */
int Applications::assign_item_id(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�����������Ϊ�գ���ֱ�ӷ���1��
	if(_applications.empty()){
		return(1);
	}
	//3.�Ե���ǰ���������������Ŀ��ʶ����
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_ID));
	//4.������С����������Ŀ��ʶ����ͻ������Ŀ��ʶ��
	//4-1.��ȡ��ǰ������������ߴ硣
	unsigned int size=_applications.size();
	//4-2.������С����������Ŀ��ʶ����ͻ������Ŀ��ʶ��
	for(int index=1;index<=static_cast<int>(size);/*++index*/){
		//4-2-1.ȷ����ǰ�����������������Ŀ��ʶ�Ϸ���
		assert((_applications[index-1]->get_item()).get_id()>0);
		//4-2-2.����ҵ�һ����С����������Ŀ��ʶ����ͻ������Ŀ��ʶ����ֱ�ӷ��ء�
		if(index!=(_applications[index-1]->get_item()).get_id()){
			return(index);
		}
		//4-2-3.�����´�ѭ����
		++index;
	}
	//5.�������е��ˣ�ֱ�ӷ���������Ŀ��ʶ��
	return(static_cast<int>(size+1));
}

/**
 * name: Applications
 * breif: ���캯����
 * param: --
 * return: --
 */
Applications::Applications(void)
	:_applications()
	,_lock(new MtLock){
}