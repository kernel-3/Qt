#include"stdafx.h"
#include"AnalysisMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: AnalysisMethod
 * breif: 构造函数。
 * param: --
 * return: --
 */
AnalysisMethod::AnalysisMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_expression(_T("")){
}

/**
 * name: ~AnalysisMethod
 * breif: 析构函数。
 * param: --
 * return: --
 */
AnalysisMethod::~AnalysisMethod(void){
}

/**
 * name: set_id
 * brief: 设置分析方法标识。
 * param: id - 输入的分析方法标识。
 * return: --
 */
void AnalysisMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * brief: 获取分析方法标识。
 * param: --
 * return: 返回分析方法标识。
 */
int AnalysisMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * brief: 设置分析方法名称。
 * param: name - 输入的分析方法名称。
 * return: --
 */
void AnalysisMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * brief: 获取分析方法名称。
 * param: --
 * return: 返回分析方法名称。
 */
CString AnalysisMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: 设置分析方法别名。
 * param: alias - 输入的分析方法别名。
 * return: --
 */
void AnalysisMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: 获取分析方法别名。
 * param: --
 * return: 返回分析方法别名。
 */
CString AnalysisMethod::get_alias() const{
	return(_alias);
}

/**
 * name: set_expression
 * brief: 设置分析方法表达式。
 * param: expression - 输入的分析方法表达式。
 * return: --
 */
void AnalysisMethod::set_expression(const CString &expression){
	_expression=expression;
}

/**
 * name: get_expression
 * brief: 获取分析方法表达式。
 * param: --
 * return: 返回分析方法表达式。
 */
CString AnalysisMethod::get_expression() const{
	return(_expression);
}

/**
 * name: is_valid
 * breif: 检测当前分析方法类中数据是否合法。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int AnalysisMethod::is_valid() const{
	//1.如果当前分析方法标识不合法。
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.如果当前分析方法名称不合法。
	if(_T("")==_name){
		return(-2);
	}
	//3.如果当前分析方法别名不合法。
	if(_T("")==_alias){
		return(-3);
	}
	//4.如果当前分析方法公式不合法。
	if(_T("")==_expression){
		return(-4);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新当前类中数据。
 * param: recordset - 输入的指定记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int AnalysisMethod::update(MtADORecordset &recordset){
	//1.声明当前操作所需变量。
	//AnalysisMethod analysis_method;
	_variant_t value;
	//2.从指定的记录集中获取分析方法标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*analysis_method.*/_id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取分析方法名称。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*analysis_method.*/_name=MtADODataConverter::to_string(value);
	//4.从指定的记录集中获取分析方法别名。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*analysis_method.*/_alias=MtADODataConverter::to_string(value);
	//5.从指定的记录集中获取分析方法公式。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	/*analysis_method.*/_expression=MtADODataConverter::to_string(value);
	//6.判断从数据库中加载的分析方法是否合法。
	if(/*analysis_method.*/is_valid()<0){
		return(-5);
	}
	//7.为当前分析方法赋值。
	//(*this)=analysis_method;
	//8.程序运行到此，成功返回。
	return(0);
}