#include"stdafx.h"
#include"ApplicationData.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"

/**
 * name: ApplicationData
 * breif: 构造函数。
 * param: --
 * return: --
 */
ApplicationData::ApplicationData(void)
	:_module_id(0)
	,_specimen_type_id(0)
	,_item_id(0){
}

/**
 * name: ApplicationData
 * breif: 构造函数。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本类型标识。
 *        item_id - 输入的项目标识。
 * return: --
 */
ApplicationData::ApplicationData(const int module_id,
	const int specimen_type_id,const int item_id)
	:_module_id(module_id)
	,_specimen_type_id(specimen_type_id)
	,_item_id(item_id){
}

/**
 * name: ~ApplicationData
 * breif: 析构函数。
 * param: --
 * return: --
 */
ApplicationData::~ApplicationData(void){
}

/**
 * name: set_module_id
 * breif: 设置模块标识。
 * param: module_id - 输入的模块标识。
 * return: --
 */
void ApplicationData::set_module_id(const int module_id){
	_module_id=module_id;
}

/**
 * name: get_module_id
 * brief: 获取模块标识。
 * param: --
 * return: 返回模块标识。
 */
int ApplicationData::get_module_id() const{
	return(_module_id);
}

/**
 * name: set_specimen_type_id
 * breif: 设置样本类型标识。
 * param: specimen_type_id - 输入的样本类型标识。
 * return: --
 */
void ApplicationData::set_specimen_type_id(const int specimen_type_id){
	_specimen_type_id=specimen_type_id;
}

/**
 * name: get_specimen_type_id
 * brief: 获取样本类型标识。
 * param: --
 * return: 返回模块标识。
 */
int ApplicationData::get_specimen_type_id() const{
	return(_specimen_type_id);
}

/**
 * name: set_item_id
 * breif: 设置项目标识。
 * param: item_id - 输入的项目标识。
 * return: --
 */
void ApplicationData::set_item_id(const int item_id){
	_item_id=item_id;
}

/**
 * name: get_item_id
 * breif: 获取项目标识。
 * param: --
 * return: 返回项目标识。
 */
int ApplicationData::get_item_id() const{
	return(_item_id);
}

/**
 * name: is_valid
 * brief: 判断当前分析申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前分析申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int ApplicationData::is_valid(CString *error_message) const{
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.清空当前错误信息。
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//3.检测模块标识是否合法。
	if((_module_id<1)||(_module_id>5)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING243),1,5);
		}
		return(-1);
	}
	//4.检测样本类型标识是否合法。
	if((_specimen_type_id<1)||(_specimen_type_id>10)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING244),1,10);
		}
		return(-2);
	}
	//5.检测项目标识是否合法。
	if((_item_id<1)||(_item_id>999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING245),1,999);
		}
		return(-3);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * breif: 将当前类中数据重置为默认值。
 * param: reagent_code - 输入的试剂编码。
 * return: --
 */
void ApplicationData::reset_default_value(const int /*reagent_code=0*/){
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新数据。
 * param: recordset - 输入的记录集。
 *        column - 输入/输出读取当前/下一个记录集的列。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationData::update(MtADORecordset &recordset,int &column){
	//1.声明当前操作所需变量。
	_variant_t value;
	//2.获取当前记录集中模块标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	_module_id=MtADODataConverter::to_int(value);
	//3.获取当前记录集中样本类型标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	_specimen_type_id=MtADODataConverter::to_int(value);
	//4.获取当前记录集中项目标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	_item_id=MtADODataConverter::to_int(value);
	//5.判断当前获取的应用数据是否合法。
	/*
	if(is_valid()<0){
		return(-4);
	}
	*/
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 将类中的数据提交到数据库中。
 * param: commit_means -  输入的提交方式（1 插入 2 更新）。
 *        database - 输入的目标数据库引用。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationData::commit(
	const int /*commit_means*/,Database & /*database*/) const{
	return(0);
}