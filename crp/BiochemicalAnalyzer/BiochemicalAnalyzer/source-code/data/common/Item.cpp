#include"stdafx.h"
#include"Item.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../../Resource.h"

/**
 * name: Item
 * breif: 构造函数。
 * param: --
 * return: --
 */
Item::Item(void)
	:_id(0)
	,_no(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_status(STATUS_UNKNOWN){
}

/**
 * name: ~Item
 * breif: 析构函数。
 * param: --
 * return: --
 */
Item::~Item(void){
}

/**
 * name: set_id
 * breif: 设置当前项目ID。
 * param: id - 项目ID。
 * return: --
 */
void Item::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: 获取当前项目ID。
 * param: --
 * return: 返回当前项目ID。
 */
int Item::get_id() const{
	return(_id);
}

/**
 * name: set_no
 * breif: 设置当前项目序号。
 * param: no - 项目序号。
 * return: --
 */
void Item::set_no(const int no){
	_no=no;
}

/**
 * name: get_no
 * breif: 获取当前项目序号。
 * param: --
 * return: 返回当前项目序号。
 */
int Item::get_no() const{
	return(_no);
}

/**
 * name: set_name
 * brief: 设置当前项目名称。
 * param: name - 项目名称。
 * return: --
 */
void Item::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: 获取当前项目名称。
 * param: --
 * return: 返回当前项目名称。
 */
const CString &Item::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * brief: 设置当前项目别名。
 * param: alias - 项目别名。
 * return: --
 */
void Item::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: 获取当前项目别名。
 * param: --
 * return: 返回当前项目别名。
 */
const CString &Item::get_alias() const{
	return(_alias);
}

/**
 * name: set_status
 * brief: 设置当前项目状态。
 * param: status - 项目状态。
 * return: --
 */
void Item::set_status(const Status status){
	_status=status;
}

/**
 * name: get_status
 * brief: 获取当前项目状态。
 * param: --
 * return: 返回当前项目状态。
 */
Item::Status Item::get_status() const{
	return(_status);
}

/**
 * name: is_valid
 * brief: 判断当前项目信息是否合法。
 * param: error_message - 指向输出的错误信息（没有错误时，错误信息为空）。
 * return: 如果当前项目信息合法则返回值大于等于零，否则返回值小于零。
 */
int Item::is_valid(CString *error_message/*=0*/) const{
	//1.清空当前错误信息。
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.如果项目标识不合法。
	if((_id<1)||(_id>999)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING177),1,999);
		}
		return(-1);
	}
	//3.如果项目序号不合法。
	if((_no<1)||(_no>200)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING178),1,200);
		}
		return(-2);
	}
	//4.如果项目名称不合法。
	if(_T("")==_name){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING179);
		}
		return(-3);
	}
	//5.如果项目别名不合法。
	if(_T("")==_alias){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING180);
		}
		return(-4);
	}
	//6.如果项目状态不合法。
	if(STATUS_UNKNOWN==_status){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING181);
		}
		return(-5);
	}
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * breif: 从指定的记录集中更新当前的项目信息。
 * param: record - 指定的记录集。
 * return: 如果函数执行陈宫返回值大于等于零，否则返回值小于零。
 */
int Item::update(MtADORecordset &record){
	//1.声明当前操作所需变量。
	Item item;
	_variant_t value;
	//2.从指定的记录集中获取项目ID。
	value=record.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	item._id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取项目序号。
	value=record.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	item._no=MtADODataConverter::to_int(value);
	//4.从指定的记录集中获取项目名称。
	value=record.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	item._name=MtADODataConverter::to_string(value);
	//5.从指定的记录集中获取项目别名。
	value=record.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	item._alias=MtADODataConverter::to_string(value);
	//6.从指定的记录集中获取项目状态。
	value=record.get_collect(MtADODataConverter::to_variant_t(4));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	item._status=static_cast<Status>(MtADODataConverter::to_int(value));
	//7.如果当前获取的项目信息不合法，则直接返回错误。
	if(item.is_valid()<0){
		return(-6);
	}
	//8.为当前项目信息赋值。
	(*this)=item;
	//9.程序运行到此，成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 将当前的项目信息提交的数据库中。
 * param: commit_means - 提交到数据库的方法（1 插入 2 更新 3 删除）。
 *        database - 准备提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Item::commit(const int commit_means,Database &database) const{
	//1.向数据库提交前需要检测当前项目信息是否合法。
	if(is_valid()<0){
		return(-1);
	}
	//2.向数据库中提交数据。
	//2-1.声明当前操作所需变量。
	CString command(_T(""));
	//2-2.如果当前期望以插入的形式提交数据。
	if(1==commit_means){
		command.Format(_T("INSERT INTO [item]([id],[no],[name],\
			[alias],[status])VALUES('%d','%d','%s','%s','%d')"),
			_id,_no,_name,_alias,_status);
	}
	//2-3.如果当前期望以更新的形式提交数据。
	else if(2==commit_means){
		command.Format(_T("UPDATE [item] SET [no]='%d',[name]='%s',\
			[alias]='%s',[status]='%d' WHERE [id]='%d'"),
			_no,_name,_alias,_status,_id);
	}
	//2-4.如果当前期望以删除的形式提交数据。
	else if(3==commit_means){
		command.Format(_T("DELETE FROM [item] WHERE [id]='%d'"),_id);
	}
	//2-5.如果当前期望以其它方式将数据提交到数据库中。
	else{
		return(-2);
	}
	//2-6.将数据提交到数据库中，并且判断提交是否成功。
	if(database.execute(command)<0){
		return(-3);
	}
	//3.程序运行到此成功返回。
	return(0);
}