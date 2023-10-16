#include"stdafx.h"
#include"Items.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"Item.h"
#include<assert.h>

/**
 * name: ~Items
 * breif: 析构函数。
 * param: --
 * return: --
 */
Items::~Items(void){
	delete _lock;
}

/**
 * name: Items
 * brief: 构造函数。
 * param: --
 * return: --
 */
Items::Items(void)
	:_lock(new MtLock)
	,_items()
	,_items_no(){
}

/**
 * name: instance
 * brief: 获取当前类在系统中的唯一实例的指针。
 * param: --
 * return: 返回当前类在系统中的唯一实例的指针。
 */
Items *Items::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: 获取当前系统中项目的个数。
 * param: --
 * return: 返回当前系统中项目的个数。
 */
int Items::get_count() const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回当前系统中项目的个数。
	return(_items.size());
}

/**
 * name: is_id_existed
 * brief: 检测项目标识是否存在。
 * param: id - 输入的项目标识。
 * return: 如果项目标识存在返回值大于等于零，否则返回值小于零。
 */
int Items::is_id_existed(const int id) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前项目标识不存在。
	if(_items.end()==_items.find(id)){
		return(-1);
	}
	//3.如果当前项目标识存在。
	else{
		return(0);
	}
}

/**
 * name: is_no_existed
 * brief: 检测项目序号是否存在。
 * param: no - 输入的项目序号。
 * return: 如果项目序号存在返回值大于等于零，否则返回值小于零。
 */
int Items::is_no_existed(const int no) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前项目序号不存在。
	if(_items_no.end()==_items_no.find(no)){
		return(-1);
	}
	//3.如果当前项目序号存在。
	else{
		return(0);
	}
}

/**
 * name: add
 * breif: 向系统中添加一个项目。
 * param: item - 输入的指向项目的智能指针。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Items::add(const PtrToItem &item){
	//1.检测输入是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(item)){
		return(-1);
	}
	if(item->is_valid()<0){
		return(-2);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测内存中是否已经存在对应的项目,如果已经存在则直接返回错误。
	if(_items.end()!=_items.find(item->get_id())){
		return(-3);
	}
	if(_items_no.end()!=_items_no.find(item->get_no())){
		return(-4);
	}
	//4.将输入项目插入到系统项目存储容器中。
	_items[item->get_id()]=item;
	_items_no[item->get_no()]=item->get_id();
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: modify
 * breif: 修改指定的项目信息。
 * param: item - 输入的指定项目。
 * return: 如果函数执行成功返回值小于零，否则返回值大于等于零。
 */
int Items::modify(const Item &item){
	//1.检测输入的指定项目是否合法，如果不合法则直接返回错误。
	if(item.is_valid()<0){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测内存中是否已经存在对应的项目,如果不存在则直接返回错误。
	if(_items.end()==_items.find(item.get_id())){
		return(-2);
	}
	//4.检测指定的项目是否存在，如果不存在则直接返回错误。
	if(!static_cast<bool>(_items[item.get_id()])){
		return(-3);
	}
	//5.修改指定的项目信息。
	(*_items[item.get_id()])=item;
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: remove
 * brief: 删除指定的项目。
 * param: item_id - 指定的项目标识。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Items::remove(const int item_id){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测内存中是否已经存在对应的项目,如果不存在则直接返回错误。
	MItems::iterator iterator=_items.find(item_id);
	if(_items.end()==iterator){
		return(-1);
	}
	//4.断言项目信息存在有效。
	assert(static_cast<bool>(iterator->second));
	//5.检索内存中是否已经存在对应的项目序号，如果不存在则直接返回错误。
	MItemsNo::iterator no_iterator=_items_no.find((
		iterator->second)->get_no());
	if(_items_no.end()==no_iterator){
		return(-2);
	}
	//6.删除指定的项目信息以及项目序号信息。
	_items.erase(iterator);
	_items_no.erase(no_iterator);
	//7.程序运行到此直接返回。
	return(0);
}

/**
 * name: get_by_id
 * brief: 通过项目标识获取项目。
 * param: id - 输入的项目标识。
 * return: 如果获取项目成功，返回指向项目的智能指针，否则返回空指针。
 */
Items::PtrToCItem Items::get_by_id(const int id) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前项目标识不存在，则直接返回空指针。
	if(_items.end()==_items.find(id)){//log(n)
		return(PtrToCItem());
	}
	//3.返回相应的项目信息。
	return((const_cast<Items*>(this))->_items[id]);
}

/**
 * name: get_by_no
 * brief: 通过项目序号获取项目。
 * param: no - 输入的项目序号。
 * return: 如果获取项目成功，返回指向项目的智能指针，否则返回空指针。
 */
Items::PtrToCItem Items::get_by_no(const int no) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果项目序号不存在，则直接返回空指针。
	if(_items_no.end()==_items_no.find(no)){//log(n)
		return(PtrToCItem());
	}
	//3.获取项目序号对应的项目标识。
	const int id=const_cast<Items*>(this)->_items_no[no];
	//4.如果项目标识不存在，则直接返回空指针。
	if(_items.end()==_items.find(id)){//log(n)
		return(PtrToCItem());
	}
	//5.返回相应的项目信息。
	return((const_cast<Items*>(this))->_items[id]);
}

/**
 * name: assign_id
 * breif: 分配一个项目标识。
 * param: --
 * return: 返回分配的项目标识。
 */
int Items::assign_id() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前不存在任何项目。
	if(_items.empty()){
		return(1);
	}
	//3.获取最后一个项目的项目标识（当前系统中最大的项目标识）。
	return((((--_items.end())->second)->get_id())+1);
}

/**
 * name: update
 * brief: 从数据库中下载更新数据。
 * param: database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Items::update(Database &database){
	//1.声明当前操作所需变量。
	MItems items;
	MItemsNo items_no;
	const CString command(_T("SELECT * FROM [item] ORDER BY [id] ASC"));
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
		//3-2.创建项目信息类，并且判断创建是否成功。
		PtrToItem item(new Item);
		if(!static_cast<bool>(item)){
			return(-3);
		}
		//3-3.从当前的记录集中更新项目信息。
		if(item->update(*records)<0){
			return(-4);
		}
		//3-4.将当前的项目信息插入到容器中。
		//a.向容器中插入项目信息。
		if(items.end()==items.find(item->get_id())){
			items[item->get_id()]=item;
		}else{
			return(-5);
		}
		//b.建立项目编号与项目标识的映射。
		if(items_no.end()==items_no.find(item->get_no())){
			items_no[item->get_no()]=item->get_id();
		}else{
			return(-6);
		}
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-7);
		}
	}
	//4.保存从记录集中更新的项目信息。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的项目信息。
	_items.swap(items);
	_items_no.swap(items_no);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * breif: 将当前类中数据提交到数据库中。
 * param: item_id - 指定的项目标识。
 *        commit_means - 提交方式（1 插入 2 更新 3 删除）。
 *        database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Items::commit(const int item_id,
	const int commit_means,Database &database) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.查找当前准备提交数据的项目，并且判断查找是否成功。
	MItems::const_iterator iterator=_items.find(item_id);
	if(_items.end()==iterator){
		return(-1);
	}
	//3.将找到项目的数据提交到数据库中，并且判断提交是否成功。
	if((iterator->second)->commit(commit_means,database)<0){
		return(-2);
	}
	//4.程序运行到此直接返回。
	return(0);
}

/**
 * name: traverse
 * breif: 遍历存储的全部项目。
 * param: callback - 输入的回调函数。
 * return: --
 */
void Items::traverse(const TraverseCallback &callback) const{
	//1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.遍历存储的全部项目，并且调用遍历回调函数。
	for(MItems::const_iterator iterator=_items.begin();
		iterator!=_items.end();++iterator){
		//2-1.这里断言项目信息合法。
		assert(static_cast<bool>(iterator->second));
		//2-2.调用相应的回调函数。
		callback(*iterator->second);
	}
}