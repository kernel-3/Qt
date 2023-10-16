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
 * breif: 析构函数。
 * param: --
 * return: --
 */
Applications::~Applications(void){
	delete _lock;
}

/**
 * name: instance
 * brief: 获取系统唯一的一个申请参数类实例。
 * param: --
 * return: 返回系统唯一的一个申请参数类实例。
 */
Applications *Applications::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_by_item_no
 * brief: 根据项目序号，获取当前类中指定元素。
 * param: item_no - 项目序号。
 * return: 如果函数执行成功返回值指向指定项目序号的元素指针，否则返回空指针。
 */
Applications::PtrToCApp Applications::get_by_item_no(const int item_no) const{
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return(PtrToApp());
	}
	//4.根据项目序号查找指定的项目申请参数。
	//4-1.查找指定的项目申请参数。
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_no,AppFinder::FIND_METHOD_BY_ITEM_NO));
	//4-2.判断指定的项目申请参数是否查找成功。
	if(_applications.end()==iterator){
		return(PtrToApp());
	}
	//5.返回当前查找到的项目申请参数。
	return(*iterator);
}

/**
 * name: get_by_item_id
 * brief: 根据项目标识，获取类中指定元素。
 * param: item_id - 项目标识。
 * return: 如果函数执行成功返回值指向指定项目标识的元素指针，否则返回空指针。
 */
Applications::PtrToCApp Applications::get_by_item_id(const int item_id) const{
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return(PtrToApp());
	}
	//4.根据项目序号查找指定的项目申请参数。
	//4-1.查找指定的项目申请参数。
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	//4-2.判断指定的项目申请参数是否查找成功。
	if(_applications.end()==iterator){
		return(PtrToApp());
	}
	//5.返回当前查找到的项目申请参数。
	return(*iterator);
}

/**
 * name: get_by_index
 * brief: 根据索引编号，获取当前类中指定元素。
 * param: index - 指定索引编号。
 * return: 如果函数执行成功返回指向指定索引编号的元素指针，否则返回空指针。
 */
Applications::PtrToCApp Applications::get_by_index(const unsigned int index) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.判断当前参数是否合法。
	if((index<0)||(index>=_applications.size())){
		return(PtrToApp());
	}
	//3.返回当前指定索引的项目申请参数。
	return(_applications[index]);
}

/**
 * name: is_item_id_existing
 * brief: 判断指定的项目标识是否存在。
 * param: item_id - 项目标识。
 * return: 如果指定的项目标识已经存在则返回TRUE、否则返回FALSE。
 */
BOOL Applications::is_item_id_existing(const int item_id) const{
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return(FALSE);
	}
	//4.根据项目序号查找指定的项目申请参数。
	//4-1.查找指定的项目申请参数。
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	//4-2.判断指定的项目申请参数是否查找成功。
	if(_applications.end()==iterator){
		return(FALSE);
	}
	//5.程序运行到此成功返回。
	return(TRUE);
}

/**
 * name: is_item_no_existing
 * brief: 判断指定的项目序号是否存在。
 * param: item_no - 项目序号。
 * return: 如果指定的项目序号已经存在则返回TRUE、否则返回FALSE。
 */
BOOL Applications::is_item_no_existing(const int item_no) const{
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return(FALSE);
	}
	//4.根据项目序号查找指定的项目申请参数。
	//4-1.查找指定的项目申请参数。
	VecApps::const_iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_no,AppFinder::FIND_METHOD_BY_ITEM_NO));
	//4-2.判断指定的项目申请参数是否查找成功。
	if(_applications.end()==iterator){
		return(FALSE);
	}
	//5.程序运行到此成功返回。
	return(TRUE);
}

/**
 * name: sort_by_item_no
 * brief: 根据项目序号，对类中元素进行排序。
 * param: --
 * return: --
 */
void Applications::sort_by_item_no(){
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return;
	}
	//3.对申请参数按项目序号排序。
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_NO));
}

/**
 * name: sort_by_item_id
 * brief: 根据项目标识，对类中元素进行排序。
 * param: --
 * return: --
 */
void Applications::sort_by_item_id(){
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前申请参数容器为空，则直接返回。
	if(_applications.empty()){
		return;
	}
	//3.对申请参数按项目标识排序。
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_ID));
}

/**
 * name: add
 * brief: 向当前类中添加一个元素。
 * param: application - 指定的新元素。
 *        database - 准备提交数据的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::add(const PtrToApp &application,Database &database){
	//1.判断当前参数是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(application)){
		return(-1);
	}
	//2.将添加的申请参数提交到数据库中，并且判断提交是否成功。
	if(application->commit(Application::COMMIT_METHOD_INSERT,database)<0){
		return(-2);
	}
	//3.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4.将指定的申请参数插入到容器中。
	_applications.push_back(application);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: remove
 * brief: 从指定数据库中删除指定的项目。
 * param: item_id - 指定项目。
 *        database - 指定数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::remove(const int item_id,Database &database){
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.根据项目标识找到指定的项目申请参数，如果失败直接返回错误。
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.删除指定数据库中相应数据。
	//4-1.开启数据库任务，并且判断开启是否成功。
	if(database.begin_trans()<0){
		return(-2);
	}
	//4-2.删除数据库中相应项目的分析申请参数。
	CString sql(_T(""));
	sql.Format(_T("DELETE FROM [analyze_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-3);
	}
	//4-3.删除数据库中相应项目的定标申请参数。
	sql.Format(_T("DELETE FROM [calibration_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-4);
	}
	//4-4.删除数据库中相应项目的范围申请参数。
	sql.Format(_T("DELETE FROM [range_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-5);
	}
	//4-5.删除数据库中相应项目的标准申请参数。
	sql.Format(_T("DELETE FROM [standard_application] WHERE [item_id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-6);
	}
	//4-6.删除数据库中相应的项目信息。
	sql.Format(_T("DELETE FROM [item] WHERE [id]='%d'"),item_id);
	if(database.execute(sql)<0){
		database.rollback_trans();
		return(-7);
	}
	//4-7.提交数据库任务。
	if(database.commit_trans()<0){
		database.rollback_trans();
		return(-8);
	}
	//5.删除指定项目的申请参数。
	_applications.erase(iterator);
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * brief: 从指定的数据库中下载更新数据。
 * param: database - 指定的数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::update(Database &database){
	//1.声明当前操作所需变量。
	VecApps applications;
	const CString sql(_T("SELECT * FROM [item] LEFT JOIN [analyze_application] ON \
		[item].[id]=[analyze_application].[item_id] LEFT JOIN [calibration_application] \
		ON [item].[id]=[calibration_application].[item_id] LEFT JOIN [range_application] \
		ON [item].[id]=[range_application].[item_id] LEFT JOIN [standard_application] ON \
		[item].[id]=[standard_application].[item_id] ORDER BY [item].[id] ASC"));
	//2.获取数据库中相应的记录集。
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.遍历记录集，从记录集中获取申请参数信息。
	while(!records->get_eof()){
		//3-1.判断上面获取记录集尾是否成功。
		if(0!=records->get_last_error_code()){
			return(-1);
		}
		//3-2.创建申请参数，并且判断创建是否成功。
		PtrToApp application(new Application);
		if(!static_cast<bool>(application)){
			return(-2);
		}
		//3-3.从当前的记录集中更新申请参数。
		if(application->update(*records)<0){
			return(-3);
		}
		//3-4.将当前的申请参数插入到容器中。
		applications.push_back(application);
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-4);
		}
	}
	//4.保存从记录集中更新的申请参数。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的申请参数。
	_applications.swap(applications);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 向指定的数据库提交数据。
 * param: item_id - 准备提交数据的项目标识。
 *        item_alias - 更改的项目别名。
 *        analyze - 更改的分析申请参数。
 *        database - 提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::commit(const int item_id,const CString &item_alias,
	const AnalyzeApplication &analyze,Database &database){
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.根据项目标识找到指定的项目申请参数，如果失败直接返回错误。
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.记录当前项目别名。
	const CString old_item_alias=((*iterator)->get_item()).get_alias();
	//5.设置当前项目别名。
	((*iterator)->get_item()).set_alias(item_alias);
	//6.向数据库提交当前修改的数据信息。
	//6-1.开启一个任务。
	if(database.begin_trans()<0){
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-2);
	}
	//6-2.向数据库提交项目信息。
	if(((*iterator)->get_item()).commit(
		Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-3);
	}
	//6-3.向数据库提交分析参数。
	if(analyze.commit(
		item_id,Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-4);
	}
	//6-4.向数据库提交数据。
	if(database.commit_trans()<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-5);
	}
	//7.修改内存中的数据。
	((*iterator)->get_analyze())=analyze;
	//8.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 向指定的数据库提交数据。
 * param: item_id - 准备提交数据的项目标识。
 *        calibration - 更改的定标申请参数。
 *        database - 提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::commit(const int item_id,
	const CalibrationApplication &calibration,Database &database){
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.根据项目标识找到指定的项目申请参数，如果失败直接返回错误。
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//5.向数据库提交当前修改的数据信息。
	if(calibration.commit(item_id,
		Application::COMMIT_METHOD_UPDATE,database)<0){
		return(-2);
	}
	//6.修改内存中的数据。
	((*iterator)->get_calibration())=calibration;
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 向指定的数据库提交数据。
 * param: item_id - 准备提交数据的项目标识。
 *        item_alias - 更改的项目别名。
 *        range - 更改的范围申请参数。
 *        database - 提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::commit(const int item_id,const CString &item_alias,
	const RangeApplication &range,Database &database){
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.根据项目标识找到指定的项目申请参数，如果失败直接返回错误。
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//4.记录当前项目别名。
	const CString old_item_alias=((*iterator)->get_item()).get_alias();
	//5.设置当前项目别名。
	((*iterator)->get_item()).set_alias(item_alias);
	//6.向数据库提交当前修改的数据信息。
	//6-1.开启一个任务。
	if(database.begin_trans()<0){
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-2);
	}
	//6-2.向数据库提交项目信息。
	if(((*iterator)->get_item()).commit(
		Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-3);
	}
	//6-3.向数据库提交分析参数。
	if(range.commit(
		item_id,Application::COMMIT_METHOD_UPDATE,database)<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-4);
	}
	//6-4.向数据库提交数据。
	if(database.commit_trans()<0){
		database.rollback_trans();
		((*iterator)->get_item()).set_alias(old_item_alias);
		return(-5);
	}
	//7.修改内存中的数据。
	((*iterator)->get_range())=range;
	//8.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 向指定的数据库提交数据。
 * param: item_id - 准备提交数据的项目标识。
 *        standard - 更改的标准申请参数。
 *        database - 提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Applications::commit(const int item_id,
	const StandardApplication &standard,Database &database){
	//1.定义。
	typedef ApplicationFinder<int> AppFinder;
	//2.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.根据项目标识找到指定的项目申请参数，如果失败直接返回错误。
	VecApps::iterator iterator=std::find_if(
		_applications.begin(),_applications.end(),
		AppFinder(item_id,AppFinder::FIND_METHOD_BY_ITEM_ID));
	if(_applications.end()==iterator){
		return(-1);
	}
	//5.向数据库提交当前修改的数据信息。
	if(standard.commit(item_id,
		Application::COMMIT_METHOD_UPDATE,database)<0){
		return(-2);
	}
	//6.修改内存中的数据。
	((*iterator)->get_standard())=standard;
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_size
 * brief: 获取当前类中元素个数。
 * param: --
 * return: 返回当前类中元素个数。
 */
unsigned int Applications::get_size() const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回当前类中元素个数。
	return(_applications.size());
}

/**
 * name: assign_item_id
 * breif: 分配一个项目标识，保证与已有的项目标识不冲突。
 * param: --
 * return: 返回分配的项目标识。
 */
int Applications::assign_item_id(){
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前申请参数容器为空，则直接返回1。
	if(_applications.empty()){
		return(1);
	}
	//3.对但当前申请参数容器按项目标识排序。
	std::sort(_applications.begin(),_applications.end(),
		ApplicationComparator(ApplicationComparator::
		COMPARE_METHOD_BY_ITEM_ID));
	//4.计算最小且与现有项目标识不冲突的新项目标识。
	//4-1.获取当前申请参数容器尺寸。
	unsigned int size=_applications.size();
	//4-2.计算最小且与现有项目标识不冲突的新项目标识。
	for(int index=1;index<=static_cast<int>(size);/*++index*/){
		//4-2-1.确保当前容器中申请参数的项目标识合法。
		assert((_applications[index-1]->get_item()).get_id()>0);
		//4-2-2.如果找到一个最小且与现有项目标识不冲突的新项目标识，则直接返回。
		if(index!=(_applications[index-1]->get_item()).get_id()){
			return(index);
		}
		//4-2-3.继续下次循环。
		++index;
	}
	//5.程序运行到此，直接返回最大的项目标识。
	return(static_cast<int>(size+1));
}

/**
 * name: Applications
 * breif: 构造函数。
 * param: --
 * return: --
 */
Applications::Applications(void)
	:_applications()
	,_lock(new MtLock){
}