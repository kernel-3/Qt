#include"stdafx.h"
#include"DilutionMethod.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: DilutionMethod
 * brief: 构造函数。
 * param: --
 * return: --
 */
DilutionMethod::DilutionMethod(void)
	:_id(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_specimen_ratio(0)
	,_diluent_ratio(0){
}

/**
 * name: ~DilutionMethod
 * brief: 析构函数。
 * param: --
 * return: --
 */
DilutionMethod::~DilutionMethod(void){
}

/**
 * name: set_id
 * breif: 设置稀释方法标识。
 * param: id - 输入的稀释方法标识。
 * return: --
 */
void DilutionMethod::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: 获取稀释方法标识。
 * param: --
 * return: 返回稀释方法标识。
 */
int DilutionMethod::get_id() const{
	return(_id);
}

/**
 * name: set_name
 * breif: 设置稀释方法名称。
 * param: name - 输入的稀释方法名称。
 * return: --
 */
void DilutionMethod::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: 获取稀释方法名称。
 * param: --
 * return: 返回稀释方法名称。
 */
CString DilutionMethod::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * breif: 设置稀释方法别名。
 * param: alias - 输入的稀释方法别名。
 * return: --
 */
void DilutionMethod::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: 获取稀释方法别名。
 * param: --
 * return: 返回稀释方法别名。
 */
CString DilutionMethod::get_alias() const{
	return(_alias);
}

/**
 * name: set_specimen_ratio
 * breif: 设置样本比例。
 * param: specimen_ratio - 输入的样本比例。
 * return: --
 */
void DilutionMethod::set_specimen_ratio(const int specimen_ratio){
	_specimen_ratio=specimen_ratio;
}

/**
 * name: get_specimen_ratio
 * brief: 获取样本比例。
 * parma: --
 * return: 返回样本比例。
 */
int DilutionMethod::get_specimen_ratio() const{
	return(_specimen_ratio);
}

/**
 * name: set_diluent_ratio
 * breif: 设置稀释液比例。
 * param: diluent_ratio - 输入的稀释液比例。
 * return: --
 */
void DilutionMethod::set_diluent_ratio(const int diluent_ratio){
	_diluent_ratio=diluent_ratio;
}

/**
 * name: get_diluent_ratio
 * breif: 获取稀释液比例。
 * param: --
 * return: 返回稀释液比例。
 */
int DilutionMethod::get_diluent_ratio() const{
	return(_diluent_ratio);
}

/**
 * name: is_valid
 * brief: 判断当前稀释液方法是否有效。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DilutionMethod::is_valid() const{
	//1.检测当前稀释方法标识是否合法。
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.检测当前稀释方法名称是否合法。
	if(_T("")==_name){
		return(-2);
	}
	//3.检测当前稀释方法别名是否合法。
	if(_T("")==_alias){
		return(-3);
	}
	//4.检测当前样本比例是否合法。
	if((_specimen_ratio<1)||(_specimen_ratio>9999)){
		return(-4);
	}
	//5.检测当前稀释液比例是否合法。
	if((_diluent_ratio<1)||(_diluent_ratio>9999)){
		return(-5);
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新当前类中数据。
 * param: recordset - 输入的指定记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int DilutionMethod::update(MtADORecordset &recordset){
	//1.声明当前操作所需变量。
	//DilutionMethod dilution_method;
	_variant_t value;
	//2.从指定的记录集中获取稀释方法标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=recordset.get_last_error_code()){
		return(-1);
	}
	/*dilution_method.*/_id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取稀释方法名称。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	/*dilution_method.*/_name=MtADODataConverter::to_string(value);
	//4.从指定的记录集中获取稀释方法别名。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	/*dilution_method.*/_alias=MtADODataConverter::to_string(value);
	//5.从指定的记录集中获取稀释方法的样本比例。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	/*dilution_method.*/_specimen_ratio=MtADODataConverter::to_int(value);
	//6.从指定的记录集中获取稀释方法的稀释液比例。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(4));
	if(0!=recordset.get_last_error_code()){
		return(-5);
	}
	/*dilution_method.*/_diluent_ratio=MtADODataConverter::to_int(value);
	//7.判断从数据库中加载的稀释方法是否合法。
	if(/*analysis_method.*/is_valid()<0){
		return(-6);
	}
	//8.为当前分析方法赋值。
	//(*this)=dilution_method;
	//9.程序运行到此，成功返回。
	return(0);
}