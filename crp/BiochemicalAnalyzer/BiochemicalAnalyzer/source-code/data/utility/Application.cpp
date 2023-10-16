#include"stdafx.h"
#include"Application.h"
#include"../common/Item.h"
#include"AnalyzeApplication.h"
#include"../../global/Database.h"
#include"CalibrationApplication.h"
#include"RangeApplication.h"
#include"StandardApplication.h"

/**
 * name: Application
 * breif: 构造函数。
 * param: --
 * return: --
 */
Application::Application(void)
	:_item(new Item)
	,_analyze(new AnalyzeApplication)
	,_calibration(new CalibrationApplication)
	,_range(new RangeApplication)
	,_standard(new StandardApplication){
}

/**
 * name: Application
 * breif: 拷贝构造函数。
 * param: source - 拷贝源实例。
 * return: --
 */
Application::Application(const Application &source)
	:_item(new Item(*source._item))
	,_analyze(new AnalyzeApplication(*source._analyze))
	,_calibration(new CalibrationApplication(*source._calibration))
	,_range(new RangeApplication(*source._range))
	,_standard(new StandardApplication(*source._standard)){
}

/**
 * name: ~Application
 * breif: 析构函数。
 * param: --
 * return: --
 */
Application::~Application(void){
	delete _item;
	delete _analyze;
	delete _calibration;
	delete _range;
	delete _standard;
}

/**
 * name: operator=
 * brief: 重载赋值操作符。
 * param: source - 赋值源实例。
 * return: 返回当前实例引用。
 */
Application &Application::operator=(const Application &source){
	*_item=*source._item;
	*_analyze=*source._analyze;
	*_calibration=*source._calibration;
	*_range=*source._range;
	*_standard=*source._standard;
	return(*this);
}

/**
 * name: get_item
 * brief: 获取当前申请参数中的项目信息。
 * param: --
 * return: 返回当前申请参数中的项目信息。
 */
Item &Application::get_item(){
	return(*_item);
}

/**
 * name: get_item
 * brief: 获取当前申请参数中的项目信息。
 * param: --
 * return: 返回当前申请参数中的项目信息。
 */
const Item &Application::get_item() const{
	return(const_cast<Application*>(this)->get_item());
}

/**
 * name: get_analyze
 * brief: 获取当前申请参数中的分析信息。
 * param: --
 * return: 返回当前申请参数中的分析信息。
 */
AnalyzeApplication &Application::get_analyze(){
	return(*_analyze);
}

/**
 * name: get_analyze
 * brief: 获取当前申请参数中的分析信息。
 * param: --
 * return: 返回当前申请参数中的分析信息。
 */
const AnalyzeApplication &Application::get_analyze() const{
	return(const_cast<Application*>(this)->get_analyze());
}

/**
 * name: get_calibration
 * brief: 获取当前申请参数中的定标信息。
 * param: --
 * return: 返回当前申请参数中的定标信息。
 */
CalibrationApplication &Application::get_calibration(){
	return(*_calibration);
}

/**
 * name: get_calibration
 * brief: 获取当前申请参数中的定标信息。
 * param: --
 * return: 返回当前申请参数中的定标信息。
 */
const CalibrationApplication &Application::get_calibration() const{
	return(const_cast<Application*>(this)->get_calibration());
}

/**
 * name: get_range
 * brief: 获取当前申请参数中的范围信息。
 * param: --
 * return: 返回当前申请参数中的范围信息。
 */
RangeApplication &Application::get_range(){
	return(*_range);
}

/**
 * name: get_range
 * brief: 获取当前申请参数中的范围信息。
 * param: --
 * return: 返回当前申请参数中的范围信息。
 */
const RangeApplication &Application::get_range() const{
	return(const_cast<Application*>(this)->get_range());
}

/**
 * name: get_standard
 * brief: 获取申请参数中的标准信息。
 * param: --
 * return: 返回申请参数中的标准信息。
 */
StandardApplication &Application::get_standard(){
	return(*_standard);
}

/**
 * name: get_standard
 * brief: 获取申请参数中的标准信息。
 * param: --
 * return: 返回申请参数中的标准信息。
 */
const StandardApplication &Application::get_standard() const{
	return(const_cast<Application*>(this)->get_standard());
}

/**
 * name: commit
 * brief: 将当前申请参数提交到数据库中。
 * param: method - 提交方法。
 *        database - 指定的数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Application::commit(const CommitMethod &method,Database &database) const{
	//1.开启提交数据任务，并且判断开启是否成功。
	if(database.begin_trans()<0){
		return(-1);
	}
	//2.向数据库提交项目信息，并且判断提交是否成功。
	if(_item->commit(static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-2);
	}
	//3.向数据库提交分析信息，并且判断提交是否成功。
	if(_analyze->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-3);
	}
	//4.向数据库提交定标信息，并且判断提交是否成功。
	if(_calibration->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-4);
	}
	//5.向数据库提交范围信息，并且判断提交是否成功。
	if(_range->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-5);
	}
	//6.向数据库中提交标准信息，并且提交是否成功。
	if(_standard->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-6);
	}
	//7.向数据库提交任务，并且判断提交是否成功。
	if(database.commit_trans()<0){
		database.rollback_trans();
		return(-7);
	}
	//8.程序运行到此成功返回。
	return(0);
}

/**
 * name: update
 * breif: 从指定的记录集中更新当前的申请参数。
 * param: record - 指定的记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Application::update(MtADORecordset &record){
	//1.从指定的记录中更新项目信息。
	if(_item->update(record)<0){
		return(-1);
	}
	//2.从指定的记录中更新分析信息。
	if(_analyze->update(record)<0){
		return(-2);
	}
	//3.从指定的记录中更新定标信息。
	if(_calibration->update(record)<0){
		return(-3);
	}
	//4.从指定的记录中更新范围信息。
	if(_range->update(record)<0){
		return(-4);
	}
	//5.从指定的记录中更新标准信息。
	if(_standard->update(record)<0){
		return(-5);
	}
	//6.程序运行到此成功返回。
	return(0);
}