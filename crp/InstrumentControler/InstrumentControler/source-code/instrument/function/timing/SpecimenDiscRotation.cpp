#include"stdafx.h"
#include"SpecimenDiscRotation.h"
#include"../../component/SpecimenDisc.h"
#include"../../../common/Logs.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/SpecimenDisc.h"
#include<MMSystem.h>

/**
 * name: SpecimenDiscRotation
 * breif: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
SpecimenDiscRotation::SpecimenDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rack_no(0)
	,_position_no(0){
}

/**
 * name: ~SpecimenDiscRotation
 * breif: 析构函数。
 * param: --
 * return: --
 */
SpecimenDiscRotation::~SpecimenDiscRotation(void){
}

/**
 * name: set_rack_no
 * breif: 设置架子号。
 * param: rack_no - 输入的架子号。
 * return: --
 */
void SpecimenDiscRotation::set_rack_no(
	const unsigned int rack_no){
	_rack_no=rack_no;
}

/**
 * name: get_rack_no
 * breif: 获取架子号。
 * param: --
 * return: 返回架子号。
 */
unsigned int SpecimenDiscRotation::get_rack_no() const{
	return(_rack_no);
}

/**
 * name: set_position_no
 * brief: 设置位置号。
 * param: position_no - 输入的位置号。
 * return: --
 */
void SpecimenDiscRotation::set_position_no(
	const unsigned int position_no){
	_position_no=position_no;
}

/**
 * name: get_position_no
 * brief: 获取位置号。
 * param: --
 * return: 返回位置号。
 */
unsigned int SpecimenDiscRotation::get_position_no() const{
	return(_position_no);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果不需要执行清除操作，则返回大于零的数。
 *         如果清除成功返回零。
 *         如果清除失败则返回小于零的数。
 */
int SpecimenDiscRotation::clear(){
	//1.调用基类相应清理函数，并且记录清除结果。
	const int clear_result=Action::clear();
	//2.如果当前基类清除失败则直接返回错误。
	if(clear_result<0){
		return(-1);
	}
	//3.如果当前基类清除成功，则清除子类内容。
	else if(0==clear_result){
		_rack_no=0;
		_position_no=0;
		return(0);
	}
	//4.如果当前基类期望忽略清除。
	else{
		return(1);
	}
}

/**
 * name: reset
 * breif: 重置当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int SpecimenDiscRotation::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_rack_no=0;
	_position_no=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int SpecimenDiscRotation::is_valid() const{
	//1.调用基类相应处理函数，则直接返回相应错误。
	if(Action::is_valid()<0){
		return(-1);
	}
	//2.如果当前动作为无效动作，则不进行数据检验直接返回。
	if(STATUS_DISABLED==get_status()){
		return(0);
	}
	//3.如果当前动作为有效动作，则进行数据检验，并且判断检验是否合法。
	else if(STATUS_ENABLED==get_status()){
		//3-1.如果主位置非法，则直接返回错误。
		if((_rack_no<1)||(_rack_no>
			SpecimenDisc::RACK_COUNT)){
			return(-2);
		}
		//3-2.如果子位置非法，则直接返回错误。
		if((_position_no<1)||(_position_no>
			SpecimenDisc::POSITION_COUNT)){
			return(-3);
		}
		//3-3.如果数据检验成功，则直接成功返回。
		return(0);
	}
	//4.如果当前动作为默认动作，则直接返回错误。
	else if(STATUS_DEFAULT==get_status()){
		return(-4);//此动作不支持默认状态。
	}
	//5.如果当前为未知情况，则直接返回错误。
	else{
		return(-5);
	}
}

/**
 * name: execute
 * breif: 执行当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenDiscRotation::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.发送指令命令样本盘旋转。
		if((((Instrument::instance())->get_components())->
			get_specimen_disc())->rotate(_rack_no,_position_no)<0){
			//a.设置当前未知错误标识。
			set_error(ERROR_UNKNOWN);
			//b.书写错误日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::execute \
函数中，调用 SpecimenDisc::rotate 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.程序运行到此直接返回错误。
			return(-2);
		}
		//2-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 样本盘开始旋转。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::execute \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-3);
	}
}

/**
 * name: complete
 * brief: 完成当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SpecimenDiscRotation::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果样本盘旋转完成，则成功返回。
		if(SpecimenDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_specimen_disc())->
			get_rotation_response_flag()){
			//2-1-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 样本盘旋转完成。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.程序运行到此直接成功返回。
			return(0);
		}
		//2-2.如果样本盘旋转尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::complete \
函数中，检测到样本盘旋转严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-2-3.如果当前错误次数尚未抵达上限。
			else{
				//a.设置错误标识。
				set_error(ERROR_TIMEOUT_T);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 样本盘旋转发生超时！"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenDiscRotation::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-4);
	}
}