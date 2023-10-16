#include"stdafx.h"
#include"ApplicationParameter.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"ApplicationAnalysisData.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include<assert.h>

/**
 * name: ApplicationParameter
 * breif: 构造函数。
 * param: --
 * return: --
 */
ApplicationParameter::ApplicationParameter(void)
	:_data(new PtrToData[DATA_COUNT]){
	_data[DATA_NAME_ANALYSIS]=PtrToData(new ApplicationAnalysisData);
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
}

/**
 * name: ApplicationParameter
 * breif: 构造函数。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本类型标识。
 *        item_id - 输入的项目标识。
 * return: --
 */
ApplicationParameter::ApplicationParameter(const int module_id,
	const int specimen_type_id,const int item_id)
	:_data(new PtrToData[DATA_COUNT]){
	_data[DATA_NAME_ANALYSIS]=PtrToData(new ApplicationAnalysisData(
		module_id,specimen_type_id,item_id));
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
}

/**
 * name: ~ApplicationParameter
 * breif: 析构函数。
 * param: --
 * return: --
 */
ApplicationParameter::~ApplicationParameter(void){
	delete[] _data;
}

/**
 * name: get_module_id
 * breif: 获取模块标识。
 * param: --
 * return: 返回模块标识。
 */
int ApplicationParameter::get_module_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_module_id());
}

/**
 * name: get_specimen_type_id
 * brief: 获取样本类型标识。
 * param: --
 * return: 返回样本类型标识。
 */
int ApplicationParameter::get_specimen_type_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_specimen_type_id());
}

/**
 * name: get_item_id
 * breif: 获取项目标识。
 * param: --
 * return: 返回项目标识。
 */
int ApplicationParameter::get_item_id() const{
	assert(static_cast<bool>(_data[DATA_NAME_ANALYSIS]));
	return(_data[DATA_NAME_ANALYSIS]->get_item_id());
}

/**
 * name: get
 * breif: 根据指定的数据名称获取应用参数中指定的数据。
 * param: data_name - 输入的数据名称。
 * return: 如果获取应用参数中指定的数据成功返回指向指
 *         定数据的智能指针，否则返回空指针。
 */
ApplicationParameter::PtrToCData ApplicationParameter::get(
	const DataName data_name) const{
	assert(static_cast<bool>(_data[data_name]));
	return(_data[data_name]);
}

/**
 * name: modify
 * brief: 修改指定数据。
 * param: data - 输入的应用分析数据。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameter::modify(const ApplicationAnalysisData &data){
	//1.检测输入的应用分析数据是否合法。
	if((data.is_valid()<0)||(get_module_id()!=data.get_module_id())||(
		get_specimen_type_id()!=data.get_specimen_type_id())||(
		get_item_id()!=data.get_item_id())){
		return(-1);
	}
	//2.检测当前内存中存储的相应数据是否合法。
	if(!static_cast<bool>(_data[DATA_NAME_ANALYSIS])){
		return(-2);
	}
	//3.修改内存中的数据。
	(*dynamic_cast<ApplicationAnalysisData*>(
		_data[DATA_NAME_ANALYSIS].get()))=data;
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: modify
 * breif: 修改指定数据。
 * param: data_name - 输入准备修改的数据名称。
 *        data - 输入指向修改后数据的指针。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameter::modify(
	const DataName data_name,const ApplicationData *data){
	//1.检测输入修改后的数据是否合法。
	if((0==data)||(data->is_valid()<0)||(get_module_id()!=
		data->get_module_id())||(get_specimen_type_id()!=
		data->get_specimen_type_id())||(get_item_id()!=
		data->get_item_id())){
		return(-1);
	}
	//2.检测当前内存中存储的相应数据是否合法。
	if(!static_cast<bool>(_data[data_name])){
		return(-2);
	}
	//3.修改指定的数据。
	if(DATA_NAME_ANALYSIS==data_name){
		(*dynamic_cast<ApplicationAnalysisData*>(
			_data[data_name].get()))=(*dynamic_cast<
			const ApplicationAnalysisData*>(data));
	}else{
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: is_valid
 * breif: 判断当前存储的应用参数数据是否有效。
 * param: error_message - 输出的错误消息（当没有错误是，返回空消息）。
 * return: 如果当前存储的应用参数数据有效返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameter::is_valid(CString *error_message/*=0*/) const{
	//1.清空错误信息。
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.遍历参数中全部数据，并且判断数据是否有效合法。
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		//2-1.如果当前数据存在,则判断其是否有效，如果无效直接返回错误。
		if(static_cast<bool>(_data[index])){
			if(_data[index]->is_valid(error_message)<0){
				return(-1);
			}
		}
		//2-2.如果当前数据不存在，则直接返回错误。
		else{
			if(0!=error_message){
				(*error_message)=Theme::instance()->
					get_string(IDS_STRING292);
			}
			return(-2);
		}
	}
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * breif: 重置恢复当前类中数据。
 * param: reagent_code - 输入的试剂编号。
 * return: --
 */
void ApplicationParameter::reset_default_value(const int reagent_code){
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		if(static_cast<bool>(_data[index])){
			if(DATA_NAME_ANALYSIS==index){
				_data[index]->reset_default_value(reagent_code);
			}else{
				_data[index]->reset_default_value();
			}
		}else{
			assert(0);
		}
	}
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新数据。
 * param: recordset - 指定的记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameter::update(MtADORecordset &recordset){
	//1.声明当前操作所需变量。
	int column=0;
	//2.创建应用分析数据，并且利用当前记录集更新分析数据。
	if(!static_cast<bool>(_data[DATA_NAME_ANALYSIS])){
		return(-1);
	}
	if(_data[DATA_NAME_ANALYSIS]->update(recordset,column)<0){
		return(-2);
	}
	//..程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * brief: 将当前类中数据提交到数据库中。
 * param: commit_means - 输入的提交方式（1 插入 2 更新 3 删除）。
 *        database - 输入的目标数据库。
 *        is_transaction - 输入的是否为数据库事务标记。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameter::commit(const int commit_means,
	Database &database,const BOOL is_transaction/*=TRUE*/) const{
	//1.如果当前准备提交的数据是数据库事务。
	if(is_transaction){
		if(database.begin_trans()<0){
			return(-1);
		}
	}
	//2.将当前类中数据提交到数据库中。
	for(unsigned int index=0;index!=DATA_COUNT;++index){
		if(!static_cast<bool>(_data[index])){
			if(is_transaction){
				database.rollback_trans();
			}
			return(-2);
		}else{
			if(_data[index]->commit(commit_means,database)<0){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-3);
			}
		}
	}
	//3.如果当前准备提交的数据是数据库事务。
	if(is_transaction){
		if(database.commit_trans()<0){
			database.rollback_trans();
			return(-4);
		}
	}
	//4.程序运行到此成功返回。
	return(0);
}