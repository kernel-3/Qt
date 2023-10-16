#include"stdafx.h"
#include"ApplicationParameters.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"ApplicationParameter.h"
#include"ApplicationAnalysisData.h"
#include"../common/Module.h"
#include"../common/Modules.h"
#include"../common/SpecimenType.h"
#include"../common/SpecimenTypes.h"

/**
 * name: generate_key
 * breif: 根据模块标识、样本类型标识以及项目标识生成主键。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本类型标识。
 *        item_id - 输入的项目标识。
 * return: 返回生成的主键。
 * remark: 采用此种算法生成的主键只能适用于1位模块标识、
 *         1位样本类型标识以及3位项目标识。
 */
static int generate_key(const int module_id,
	const int specimen_type_id,const int item_id){
	return(module_id*10000+specimen_type_id*1000+item_id);
}

/**
 * name: ~ApplicationParameters
 * breif: 析构函数。
 * param: --
 * return: --
 */
ApplicationParameters::~ApplicationParameters(void){
	delete _lock;
}

/**
 * name: ApplicationParameters
 * breif: 构造函数。
 * param: --
 * return: --
 */
ApplicationParameters::ApplicationParameters(void)
	:_lock(new MtLock)
	,_parameters(){
}

/**
 * name: instance
 * breif: 获取当前类在系统中唯一实例。
 * param: --
 * return: 返回指向当前类在系统中唯一实例的指针。
 */
ApplicationParameters *ApplicationParameters::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: add
 * brief: 添加一个参数。
 * param: parameter - 输入的参数。
 * return: 如果参数添加成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameters::add(const PtrToParameter &parameter){
	//1.检测输入参数是否合法。
	if(!static_cast<bool>(parameter)){
		return(-1);
	}
	if(parameter->is_valid()<0){
		return(-2);
	}
	//2.计算输入参数的键值。
	const int key=generate_key(parameter->get_module_id(),
		parameter->get_specimen_type_id(),parameter->get_item_id());
	//3.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4.如果键值已经存在，则直接返回相应错误。
	if(_parameters.end()!=_parameters.find(key)){
		return(-3);
	}
	//5.添加当前参数。
	_parameters[key]=parameter;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: get
 * breif: 根据模块标识、样本类型标识以及项目标识获取指定的
 *        应用参数信息。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本类型标识。
 *        item_id - 输入的项目标识。
 * return: 如果获取应用参数成功返回指向应用参数的智能指针，
 *         否则返回空指针。
 */
ApplicationParameters::PtrToCParameter ApplicationParameters::get(
	const int module_id,const int specimen_type_id,const int item_id) const{
	//1.生成应用参数主键。
	const int key=generate_key(module_id,specimen_type_id,item_id);
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测键值是否存在，如果不存在则返回空指针。
	if(_parameters.end()==_parameters.find(key)){
		return(PtrToCParameter());
	}
	//4.返回指定的参数。
	return((const_cast<ApplicationParameters*>(this)->_parameters)[key]);
}

/**
 * name: modify
 * brief: 修改指定的参数。
 * param: parameter - 输入的指定参数。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameters::modify(const ApplicationAnalysisData &parameter){
	//1.生成应用参数主键。
	const int key=generate_key(parameter.get_module_id(),
		parameter.get_specimen_type_id(),parameter.get_item_id());
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测键值是否存在，如果不存在则直接返回错误。
	if(_parameters.end()==_parameters.find(key)){
		return(-1);
	}
	//4.检测准备修改的参数是否存在，如果不存在则直接返回错误。
	if(!static_cast<bool>(_parameters[key])){
		return(-2);
	}
	//5.对指定的参数进行修改,并且判断修改是否成功。
	if(_parameters[key]->modify(parameter)<0){
		return(-3);
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: remove
 * brief: 删除指定项目的应用参数。
 * param: item_id - 输入的指定项目标识。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameters::remove(const int item_id){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前系统中的模块以及样本类型数量。
	const unsigned int module_count=(
		Modules::instance())->get_count();
	const unsigned int specimen_type_count=(
		SpecimenTypes::instance())->get_count();
	if((0==module_count)||(0==specimen_type_count)){
		return(-1);
	}
	//3.遍历模块以及样本类型，删除指定模块、样本类型下的项目参数信息。
	for(unsigned int module_index=0;
		module_index!=module_count;++module_index){
		for(unsigned int specimen_type_index=0;
			specimen_type_index!=specimen_type_count;
			++specimen_type_index){
			//3-1.获取当前模块以及样本类型信息。
			Modules::PtrToCModule module=(Modules::instance())->
				get_by_index(module_index);
			SpecimenTypes::PtrToCSpecimenType specimen_type=
				(SpecimenTypes::instance())->get_by_index(
				specimen_type_index);
			//3-2.判断模块、样本类型信息是否合法。
			if((!static_cast<bool>(module))||(
				!static_cast<bool>(specimen_type))){
				return(-2);
			}
			//3-3.根据当前的模块标识、样本类型标识以及项目标识计算生成Key。
			const int key=generate_key(module->get_id(),
				specimen_type->get_id(),item_id);
			//3-4.查找指定的项目参数，如果查找成功则进行删除操作。
			Parameters::iterator iterator=_parameters.find(key);
			if(_parameters.end()==iterator){
				return(-3);
			}else{
				_parameters.erase(iterator);
			}
		}
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * brief: 从数据库中下载更新数据。
 * param: database - 数据库操作实例。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameters::update(Database &database){
	//1.声明当前操作所需变量。
	Parameters parameters;
	//remark: 此处以分析参数作为主表联合查询，因为如果没有分析参数，其它参数都毫无意义。
	const CString command(_T("SELECT * FROM [analyze_application] ORDER BY \
		[analyze_application].[module_id],[analyze_application].[specimen_type_id],\
		[analyze_application].[item_id] ASC"));
	//2.获取数据库中相应的记录集。
	Database::PtrToRecordset records=database.get_recordset(command);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.遍历记录集，从记录集中获取应用参数信息。
	while(!records->get_eof()){
		//3-1.判断上面获取记录集尾是否成功。
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.创建应用参数，并且判断创建是否成功。
		PtrToParameter parameter(new ApplicationParameter);
		if(!static_cast<bool>(parameter)){
			return(-3);
		}
		//3-3.从当前的记录集中更新申请参数。
		if(parameter->update(*records)<0){
			return(-4);
		}
		//3-4.将当前的申请参数插入到容器中。
		const int key=generate_key(parameter->get_module_id(),
			parameter->get_specimen_type_id(),parameter->get_item_id());
		if(parameters.end()!=parameters.find(key)){
			return(-5);
		}
		parameters[key]=parameter;
		//3-5.命令记录集下移一个位置。
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-6);
		}
	}
	//4.保存从记录集中更新的申请参数。
	//4-1.加锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.保存从记录集中更新的申请参数。
	_parameters.swap(parameters);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: commit
 * breif: 向数据库提交指定项目的参数信息。
 * param: item_id - 输入的项目标识。
 *        commit_means - 输入的提交方法（1 添加 2 更新 3 删除）。
 *        database - 输入的目标数据库。
 *        is_transaction - 输入的是否以事务方式操作数据库标记。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationParameters::commit(const int item_id,
	const int commit_means,Database &database,
	const BOOL is_transaction/*=TRUE*/) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取当前系统中的模块以及样本类型数量。
	const unsigned int module_count=(
		Modules::instance())->get_count();
	const unsigned int specimen_type_count=(
		SpecimenTypes::instance())->get_count();
	if((0==module_count)||(0==specimen_type_count)){
		return(-1);
	}
	//3.如果当前期望采取事务方式处理数据库数据，
	//  则开启事务，如果开启失败则直接返回错误。
	if(is_transaction){
		if(database.begin_trans()<0){
			return(-2);
		}
	}
	//4.遍历模块以及样本类型，提交指定模块、样本类型下的项目参数信息到数据库中。
	for(unsigned int module_index=0;module_index!=module_count;
		++module_index){
		for(unsigned int specimen_type_index=0;specimen_type_index!=
			specimen_type_count;++specimen_type_index){
			//4-1.获取当前模块以及样本类型信息。
			Modules::PtrToCModule module=(Modules::instance())->
				get_by_index(module_index);
			SpecimenTypes::PtrToCSpecimenType specimen_type=
				(SpecimenTypes::instance())->get_by_index(
				specimen_type_index);
			//4-2.判断当前模块以及样本信息是否合法。
			if((!static_cast<bool>(module))||(
				!static_cast<bool>(specimen_type))){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-3);
			}
			//4-3.根据当前的模块标识、样本类型标识以及项目标识计算生成Key。
			const int key=generate_key(module->get_id(),
				specimen_type->get_id(),item_id);
			//4-4.查找指定的项目参数，并且判断查找是否成功。
			Parameters::const_iterator iterator=_parameters.find(key);
			if(_parameters.end()==iterator){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-4);
			}
			if(!static_cast<bool>(iterator->second)){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-5);
			}
			//4-5.将指定的参数提交到数据库中，并且判断提交是否成功。
			if(iterator->second->commit(commit_means,database,FALSE)<0){
				if(is_transaction){
					database.rollback_trans();
				}
				return(-6);
			}
		}
	}
	//5.如果当前期望以事务方式操作数据库，则向数据库提交事务。
	if(is_transaction){
		if(database.commit_trans()<0){
			database.rollback_trans();
			return(-7);
		}
	}
	//6.程序运行到此成功返回。
	return(0);
}