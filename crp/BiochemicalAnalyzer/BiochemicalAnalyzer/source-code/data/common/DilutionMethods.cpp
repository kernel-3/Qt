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
 * breif: 析构函数。
 * param: --
 * return: --
 */
DilutionMethods::~DilutionMethods(void){
	delete _lock;
}

/**
 * name: DilutionMethods
 * breif: 构造函数。
 * param: --
 * return: --
 */
DilutionMethods::DilutionMethods(void)
	:_lock(new MtLock)
	,_methods(){
}

/**
 * name: instance
 * brief: 获取/创建系统中唯一稀释方法管理类实例。
 * param: --
 * return: 返回指向系统中唯一稀释方法管理类实例的指针。
 */
DilutionMethods *DilutionMethods::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * breif: 获取当前稀释方法数量。
 * param: --
 * return: 返回当前稀释方法数量。
 */
unsigned int DilutionMethods::get_count() const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回当前系统中稀释方法的数量。
	return(_methods.size());
}

/**
 * name: get_method
 * breif: 获取指定的稀释方法。
 * param: index - 输入的稀释方法索引。
 * return: 如果函数执行成功返回指向指定的稀释方法智能指针，否则返回空指针。
 */
DilutionMethods::PtrToCMethod DilutionMethods::get_method(
	const unsigned int index) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.检测输入是否合法。
	if((index<0)||(index>=_methods.size())){
		return(PtrToCMethod());
	}
	//3.程序运行到此直接返回指定的稀释方法。
	return(_methods[index]);
}

/**
 * name: update
 * brief: 从指定的数据库下载更新当前类中数据。
 * param: database - 输入的指定数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DilutionMethods::update(Database &database){
	//1.声明当前操作所需变量。
	Methods methods;
	const CString command(_T("SELECT * FROM [dilution_method] ORDER BY [id] ASC"));
	//2.获取数据库中相应的记录集。
	Database::PtrToRecordset records=database.get_recordset(command);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.遍历记录集，从记录集中获取模块信息。
	while(!records->get_eof()){
		//3-1.判断上面获取记录集尾是否成功。
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.创建稀释方法类，并且判断创建是否成功。
		PtrToMethod method(new DilutionMethod);
		if(!static_cast<bool>(method)){
			return(-3);
		}
		//3-3.从当前的记录集中更新稀释方法。
		if(method->update(*records)<0){
			return(-4);
		}
		//3-4.将当前稀释方法插入到容器中。
		methods.push_back(method);
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-5);
		}
	}
	//4.保存从记录集中更新的稀释方法。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的稀释方法。
	_methods.swap(methods);
	//5.程序运行到此成功返回。
	return(0);
}