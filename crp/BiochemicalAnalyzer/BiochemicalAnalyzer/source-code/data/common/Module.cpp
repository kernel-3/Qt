#include"stdafx.h"
#include"Module.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"

/**
 * name: Module
 * breif: 构造函数。
 * param: --
 * return: --
 */
Module::Module(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T("")){
}

/**
 * name: ~Module
 * breif: 析构函数。
 * param: --
 * return: --
 */
Module::~Module(void){
}

/**
 * name: set_id
 * breif: 设置模块ID。
 * param: id - 模块ID。
 * return: --
 */
void Module::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: 获取模块ID。
 * param: --
 * return: 返回模块ID。
 */
int Module::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * breif: 设置模块名称。
 * param: name - 模块名称。
 * return: --
 */
void Module::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: 获取模块名称。
 * param: --
 * return: 返回模块名称。
 */
CString Module::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: 设置模块别名。
 * param: alias - 模块别名。
 * return: --
 */
void Module::set_alias(const CString alias){
	_alias=alias;
}

/**
 * name: get_alias
 * breif: 获取模块别名。
 * param: --
 * return: 返回模块别名。
 */
CString Module::get_alias() const{
	return(_alias);
}

/**
 * name: is_valid
 * breif: 检验当前模块信息是否合法。
 * param: error_message - 输出的错误信息（无错误时输出空信息）。
 * return: 如果当前模块信息合法返回值大于等于零，否则返回值小于零。
 */
int Module::is_valid(CString *error_message/*=0*/) const{
	//1.清空当前错误信息。
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.如果当前模块ID不合法。
	if((_id<1)||(_id>5)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING484),1,5);
		}
		return(-1);
	}
	//2.如果当前模块名称不合法。
	if(_T("")==_name){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING485);
		}
		return(-2);
	}
	//3.如果当前模块别名不合法。
	if(_T("")==_alias){
		if(0!=error_message){
			(*error_message)=Theme::instance()->
				get_string(IDS_STRING486);
		}
		return(-3);
	}
	//4.程序运行到此直接返回。
	return(0);
}

/**
 * name: update
 * breif: 从数据库中下载更新当前类中数据。
 * param: recordset - 数据库记录集引用。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Module::update(MtADORecordset &recordset){
	//1.声明当前操作所需变量。
	Module module;
	_variant_t value;
	//2.从指定的记录集中获取模块ID。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	module._id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取模块名称。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	module._name=MtADODataConverter::to_string(value);
	//4.从指定的记录集中获取模块别名。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	module._alias=MtADODataConverter::to_string(value);
	//5.判断从数据库中加载的模块信息是否合法。
	if(module.is_valid()<0){
		return(-4);
	}
	//6.为当前项目信息赋值。
	(*this)=module;
	//7.程序运行到此，成功返回。
	return(0);
}

/**
 * name: commit
 * breif: 将当前的模块信息提交到数据库中。
 * param: commit_means - 提交方式（1 插入 2 更新）。
 *        database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Module::commit(const int commit_means,Database &database) const{
	//1.判断当前存储的模块信息是否合法。
	if(is_valid()<0){
		return(-1);
	}
	//2.形成模块信息提交数据库可执行语句。
	//2-1.声明当前操作所需变量。
	CString command(_T(""));
	//2-2.如果当前提交方式为Insert方式提交。
	if(1==commit_means){
		command.Format(_T("INSERT INTO [module]([id],[name],\
			[alias])VALUES('%d','%s','%s')"),_id,_name,_alias);
	}
	//2-3.如果当前提交方式为Update方式提交。
	else if(2==commit_means){
		command.Format(_T("UPDATE [module] SET [name]='%s',\
			[alias]='%s' WHERE [id]='%d'"),_name,_alias,_id);
	}
	//2-4.如果当前提交方式未知。
	else{
		return(-2);
	}
	//3.将数据提交数据库。
	if(database.execute(command)<0){
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}