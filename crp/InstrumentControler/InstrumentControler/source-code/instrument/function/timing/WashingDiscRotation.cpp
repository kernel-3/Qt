#include"stdafx.h"
#include"WashingDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: WashingDiscRotation
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
WashingDiscRotation::WashingDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE){
}

/**
 * name: ~WashingDiscRotation
 * brief: 析构函数。
 * param: --
 * return: --
 */
WashingDiscRotation::~WashingDiscRotation(void){
}

/**
 * name: reset
 * breif: 重置当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int WashingDiscRotation::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_rotation_flag=FALSE;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int WashingDiscRotation::is_valid() const{
	//1.调用基类相应处理函数，并且记录处理结果。
	const int result=Action::is_valid();
	//2.如果基类相应处理函数失败，则直接返回相应错误。
	if(result<0){
		return(-1);
	}
	//3.如果当前动作为无效动作，则直接返回错误。
	if(STATUS_DISABLED==get_status()){
		return(-2);
	}
	//4.如果当前动作为有效动作，则直接返回错误。
	else if(STATUS_ENABLED==get_status()){
		return(-3);
	}
	//5.如果当前动作为默认动作，则成功返回。
	else if(STATUS_DEFAULT==get_status()){
		return(0);
	}
	//6.如果当前为未知情况，则直接返回错误。
	else{
		return(-4);
	}
}

/**
 * name: execute
 * breif: 执行当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int WashingDiscRotation::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscRotation::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	if(STATUS_DEFAULT==status){
		//2-1.清除清洗盘旋转标记。
		_rotation_flag=FALSE;
		//2-2.如果当前清洗盘上无管,则不进行任何旋转，直接成功返回。
		if(!((((Instrument::instance())->get_components())
			->get_washing_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.如果当前清洗盘上有管，则命令清洗盘旋转。
		else{
			//2-3-1.命令清洗盘旋转，并且判断旋转是否成功。
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->rotate()<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： WashingDiscRotation::execute \
函数中，调用 WashingDisc::rotate 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-3-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 清洗盘开始旋转。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-3.设置清洗盘已经开始旋转标记。
			_rotation_flag=TRUE;
			//2-3-4.程序运行到此成功返回。
			return(0);
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscRotation::execute \
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
int WashingDiscRotation::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscRotation::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	else if(STATUS_DEFAULT==status){
		//2-1.如果当前清洗盘并未旋转。
		if(FALSE==_rotation_flag){
			return(0);//程序运行到此，直接成功返回。
		}
		//2-2.如果当前清洗盘已经旋转。
		else{
			//2-2-1.如果当前清洗盘旋转动作执行完成。
			if(WashingDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_washing_disc())->get_rotation_response_flag()){
				//a.清洗盘转动完成后，调整进管位孔号。
				(((Instrument::instance())->get_components())->
					get_washing_disc())->decrease_hole_no_in_entry();
				//b.书写日志。
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： 清洗盘旋转完成。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.程序运行到此成功返回。
				return(0);
			}
			//2-2-2.如果当前清洗盘动作执行尚未完成。
			else{
				//2-2-2-1.增加当前动作错误次数。
				increase_defeats();
				//2-2-2-2.检测当前动作错误次数是否已达极限。
				if(get_defeats()>MAX_DEFEATS){
					//a.设置错误标识。
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.书写错误日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： WashingDiscRotation::complete \
函数中，检测到清洗盘旋转严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
						"%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c.程序运行到此直接返回错误。
					return(-2);
				}
				//2-2-2-3.如果当前错误次数尚未抵达极限。
				else{
					//a.设置错误标识。
					set_error(ERROR_TIMEOUT_T);
					//b.书写错误日志。
					CString log(_T(""));
					log.Format(_T("Warning %s（%ld）： 清洗盘旋转发生超时！"),
						(COleDateTime::GetCurrentTime()).Format(
						_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c.程序运行到此直接返回错误。
					return(-3);
				}
			}
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscRotation::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-4);
	}
}