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
 * breif: 析构函数。
 * param: --
 * return: --
 */
Modules::~Modules(void){
	delete _lock;
}

/**
 * name: Modules
 * breif: 构造函数。
 * param: --
 * return: --
 */
Modules::Modules(void)
	:_lock(new MtLock)
	,_modules(){
}

/**
 * name: instance
 * brief: 获取当前类在系统中的唯一实例的指针。
 * param: --
 * return: 返回当前类在系统中的唯一实例的指针。
 */
Modules *Modules::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: 获取模块数量。
 * param: --
 * return: 返回模块数量。
 */
unsigned int Modules::get_count() const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回模块数量。
	return(_modules.size());
}

/**
 * name: get_by_id
 * breif: 根据模块标识获取指定的模块信息。
 * param: id - 输入的模块标识。
 * return: 如果获取指定模块成功返回指定的模块智能指针，否则返回空指针。
 */
Modules::PtrToCModule Modules::get_by_id(const int id) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历查找指定模块信息。
	for(VModules::const_iterator iterator=_modules.begin();
		iterator!=_modules.end();++iterator){
		assert(static_cast<bool>(*iterator));
		if(id==(*iterator)->get_id()){
			return(*iterator);
		}
	}
	//3.程序运行到此直接返回空指针。
	return(PtrToCModule());
}

/**
 * name: get_by_index
 * breif: 根据模块索引编号获取指定的模块信息。
 * param: index - 输入的模块索引编号。
 * return: 如果获取指定模块成功返回指定的模块智能指针，否则返回空指针。
 */
Modules::PtrToCModule Modules::get_by_index(const unsigned int index) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.检测输入是否合法。
	if((index<0)||(index>=(_modules.size()))){
		return(PtrToCModule());
	}
	//3.返回指定的模块信息。
	return(_modules[index]);
}

/**
 * name: update
 * brief: 从数据库中下载更新数据。
 * param: database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Modules::update(Database &database){
	//1.声明当前操作所需变量。
	VModules modules;
	const CString sql(_T("SELECT * FROM [module] ORDER BY [id] ASC"));
	//2.获取数据库中相应的记录集。
	Database::PtrToRecordset records=database.get_recordset(sql);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.遍历记录集，从记录集中获取模块信息。
	while(!records->get_eof()){
		//3-1.判断上面获取记录集尾是否成功。
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.创建模块信息类，并且判断创建是否成功。
		PtrToModule module(new Module);
		if(!static_cast<bool>(module)){
			return(-3);
		}
		//3-3.从当前的记录集中更新模块信息。
		if(module->update(*records)<0){
			return(-4);
		}
		//3-4.将当前的模块信息插入到容器中。
		modules.push_back(module);
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.保存从记录集中更新的模块信息。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的申请参数。
	_modules.swap(modules);
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
int Modules::commit(const int commit_means,Database &database) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.开启数据库事务，并且判断开启是否成功。
	if(database.begin_trans()<0){
		return(-1);
	}
	//3.遍历当前模块信息容器，提交所有的模块信息到数据库中。
	for(VModules::const_iterator iterator=_modules.begin();
		iterator!=_modules.end();++iterator){
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
 * param: module_id - 指定的模块标识。
 *        commit_means - 提交方式（1 插入 2 更新）。
 *        database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Modules::commit(const int module_id,
	const int commit_means,Database &database) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历当前模块信息容器，提交指定的模块信息到数据库中。
	//remark: 因为模块的数量较少，所有采用遍历查找方式，目前性能满足系统需求。
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
	//3.程序运行到此直接返回错误。
	return(-2);
}