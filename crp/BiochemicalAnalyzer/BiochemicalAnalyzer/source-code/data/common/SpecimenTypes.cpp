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
 * brief: 析构函数。
 * param: --
 * return: --
 */
SpecimenTypes::~SpecimenTypes(void){
	delete _lock;
}

/**
 * name: SpecimenTypes
 * brief: 构造函数。
 * param: --
 * return: --
 */
SpecimenTypes::SpecimenTypes(void)
	:_lock(new MtLock)
	,_specimen_types(){
}

/**
 * name: instance
 * breif: 获取当前系统中唯一的样本类型管理类实例。
 * param: --
 * return: 返回当前系统中唯一的样本类型管理类实例。
 */
SpecimenTypes *SpecimenTypes::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: 获取样本类型数量。
 * param: --
 * return: 返回样本类型数量。
 */
unsigned int SpecimenTypes::get_count() const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前样本类型数量。
	return(_specimen_types.size());
}

/**
 * name: get_by_id
 * breif: 根据标识获取指定的样本类型信息。
 * param: id - 输入的样本类型标识。
 * return: 如果获取样本类型信息成功，则返回指向样本类型信息的只能指针，否则
 *         返回空指针。 
 */
SpecimenTypes::PtrToCSpecimenType SpecimenTypes::get_by_id(
	const int id) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历样本类型，找出指定的样本类型信息。
	for(VSpecimenTypes::const_iterator iterator=_specimen_types.begin();
		iterator!=_specimen_types.end();++iterator){
		assert(static_cast<bool>(*iterator));
		if(id==(*iterator)->get_id()){
			return(*iterator);
		}
	}
	//3.如果程序运行到此，直接返回空指针。
	return(PtrToCSpecimenType());
}

/**
 * name: get_by_index
 * breif: 根据索引获取指定的样本类型。
 * param: index - 输入的样本类型索引。
 * return: 如果获取样本类型信息成功，则返回指向样本类型信息的只能指针，否则
 *         返回空指针。
 */
SpecimenTypes::PtrToCSpecimenType SpecimenTypes::get_by_index(
	const unsigned int index) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.检测输入是否合法。
	if((index<0)&&(index>=_specimen_types.size())){
		return(PtrToCSpecimenType());
	}
	//3.返回指定的样本类型信息。
	return(_specimen_types[index]);
}

/**
 * name: update
 * brief: 从数据库中下载更新数据。
 * param: database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenTypes::update(Database &database){
	//1.声明当前操作所需变量。
	VSpecimenTypes specimen_types;
	const CString sql(_T("SELECT * FROM [specimen_type] ORDER BY [id] ASC"));
	//2.获取数据库中相应的记录集。
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.遍历记录集，从记录集中获取样本类型信息。
	while(!records->get_eof()){
		//3-1.判断上面获取记录集尾是否成功。
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.创建样本类型信息类，并且判断创建是否成功。
		PtrToSpecimenType specimen_type(new SpecimenType);
		if(!static_cast<bool>(specimen_type)){
			return(-3);
		}
		//3-3.从当前的记录集中更新模块信息。
		if(specimen_type->update(*records)<0){
			return(-4);
		}
		//3-4.将当前的样本类型信息插入到容器中。
		specimen_types.push_back(specimen_type);
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.保存从记录集中更新的样本类型信息。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的样本类型参数。
	_specimen_types.swap(specimen_types);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * breif: 将当前类中数据提交到数据库中。
 * param: commit_means - 提交方式（1 插入 2 更新）。
 *		  database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenTypes::commit(const int commit_means,Database &database) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.开启数据库事务，并且判断开启是否成功。
	if(database.begin_trans()<0){
		return(-1);
	}
	//3.遍历当前样本类型信息容器，提交所有的样本类型信息到数据库中。
	for(VSpecimenTypes::const_iterator iterator=_specimen_types.begin();
		iterator!=_specimen_types.end();++iterator){
		if((*iterator)->commit(commit_means,database)<0){
			database.rollback_trans();//回滚事务。
			return(-2);
		}
	}
	//4.提交数据库事务，并且判断提交是否成功。
	if(database.commit_trans()<0){
		database.rollback_trans();//回滚事务。
		return(-3);
	}
	//5.程序运行到此直接返回。
	return(0);
}

/**
 * name: commit
 * breif: 将当前类中数据提交到数据库中。
 * param: specimen_type_id - 指定的样本类型标识。
 *        commit_means - 提交方式（1 插入 2 更新）。
 *        database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenTypes::commit(const int specimen_type_id,
	const int commit_means,Database &database) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历当前样本类型信息容器，提交指定的样本类型信息到数据库中。
	//remark: 因为模块的数量较少，所有采用遍历查找方式，目前性能满足系统需求。
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
	//3.程序运行到此直接返回错误。
	return(-2);
}