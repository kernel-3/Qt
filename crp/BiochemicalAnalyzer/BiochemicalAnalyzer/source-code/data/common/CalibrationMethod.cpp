#include"stdafx.h"
#include"CalibrationMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: CalibrationMethod
 * breif: 构造函数。
 * param: --
 * return: --
 */
CalibrationMethod::CalibrationMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T("")){
}

/**
 * name: ~CalibrationMethod
 * brief: 析构函数。
 * param: --
 * return: --
 */
CalibrationMethod::~CalibrationMethod(void){
}

/**
 * name: set_id
 * breif: 设置定标方法标识。
 * param: id - 输入的定标方法标识。
 * return: --
 */
void CalibrationMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * brief: 获取定标方法标识。
 * param: --
 * return: 返回定标方法标识。
 */
int CalibrationMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * brief: 设置定标方法名称。
 * param: name - 输入的定标方法名称。
 * return: --
 */
void CalibrationMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * brief: 获取定标方法名称。
 * param: --
 * return: 返回定标方法名称。
 */
CString CalibrationMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: 设置定标方法别名。
 * param: alias - 输入的定标方法别名。
 * return: --
 */
void CalibrationMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * breif: 获取定标方法别名。
 * param: --
 * return: 返回定标方法别名。
 */
CString CalibrationMethod::get_alias() const{
	return(_alias);
}

/**
 * name: is_valid
 * breif: 检测当前定标方法类中数据是否合法。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationMethod::is_valid() const{
	//1.如果当前定标方法标识不合法。
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.如果当前定标方法名称不合法。
	if(_T("")==_name){
		return(-2);
	}
	//3.如果当前定标方法别名不合法。
	if(_T("")==_alias){
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新当前类中数据。
 * param: recordset - 输入的指定记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationMethod::update(MtADORecordset &recordset){
	//1.声明当前操作所需变量。
	//CalibrationMethod calibration_method;
	_variant_t value;
	//2.从指定的记录集中获取定标方法标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*calibration_method.*/_id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取定标方法名称。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*calibration_method.*/_name=MtADODataConverter::to_string(value);
	//4.从指定的记录集中获取定标方法别名。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*calibration_method.*/_alias=MtADODataConverter::to_string(value);
	//5.判断从数据库中加载的定标方法是否合法。
	if(/*calibration_method.*/is_valid()<0){
		return(-4);
	}
	//6.为当前定标方法赋值。
	//(*this)=calibration_method;
	//7.程序运行到此，成功返回。
	return(0);
}