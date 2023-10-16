#include"stdafx.h"
#include"ReactionDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/ReactionDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

//静态变量初始化。
ReactionDiscRotation::Direction ReactionDiscRotation::
	_rotation_direction=ReactionDiscRotation::DIRECTION_POSITIVE;

/**
 * name: ReactionDiscRotation
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
ReactionDiscRotation::ReactionDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE)
	,_hole_no(0)
	,_position(0){
}

/**
 * name: ~ReactionDiscRotation
 * brief: 析构函数。
 * param: --
 * return: --
 */
ReactionDiscRotation::~ReactionDiscRotation(void){
}

/**
 * name: set_hole_no
 * brief: 设置反应盘上的洞号。
 * param: hole_no - 输入的反应盘上的洞号。
 * return: --
 */
void ReactionDiscRotation::set_hole_no(const unsigned int hole_no){
	_hole_no=hole_no;
}

/**
 * name: get_hole_no
 * breif: 获取当前反应盘上的洞号。
 * param: --
 * return: 反应当前反应盘上的洞号。
 */
unsigned int ReactionDiscRotation::get_hole_no() const{
	return(_hole_no);
}

/**
 * name: set_position
 * brief: 设置反应盘上的位置。
 * param: position - 输入的反应盘上的位置。
 * return: --
 */
void ReactionDiscRotation::set_position(const unsigned int position){
	_position=position;
}

/**
 * name: get_position
 * brief: 获取反应盘上的位置。
 * param: --
 * return: 返回反应盘上的位置。
 */
unsigned int ReactionDiscRotation::get_position() const{
	return(_position);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果忽略当前动作的清除操作，返回大于零的数。
 *         如果成功清除当前动作，返回零。
 *         如果清除当前动作失败，则返回小于零的数。
 */
int ReactionDiscRotation::clear(){
	//1.调用基类相应清理函数，并且记录基类清理结果。
	const int clear_result=Action::clear();
	//2.如果基类清理时发生错误，则直接返回。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类成功清理当前动作，则清除当前子类中所记录的数据。
	else if(0==clear_result){
		//3-1.清除当前动作中的数据。
		_rotation_flag=FALSE;
		_hole_no=0;
		_position=0;
		//3-2.程序运行到此成功返回。
		return(0);
	}
	//4.如果基类相应处理函数不期望进行清除操作，则直接返回。
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
int ReactionDiscRotation::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_rotation_flag=FALSE;
	_hole_no=0;
	_position=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int ReactionDiscRotation::is_valid() const{
	//1.调用基类相应处理函数，并且记录处理结果。
	const int result=Action::is_valid();
	//2.如果基类相应处理函数失败，则直接返回相应错误。
	if(result<0){
		return(-1);
	}
	//3.如果当前动作为无效动作，则不进行数据检验直接返回。
	if(STATUS_DISABLED==get_status()){
		return(0);
	}
	//4.如果当前动作为有效动作，则进行数据检验，并且判断检验是否合法。
	else if(STATUS_ENABLED==get_status()){
		//4-1.如果反应盘上洞号非法，则直接返回错误。
		if((_hole_no<1)||(_hole_no>ReactionDisc::HOLE_COUNT)){
			return(-2);
		}
		//4-2.如果反应盘位置非法，则直接返回错误。
		if((ReactionDisc::POSITION_ADD_SPECIMEN!=_position)&&(
			ReactionDisc::POSITION_ADD_REAGENT!=_position)&&(
			ReactionDisc::POSITION_ENTRY!=_position)&&(
			ReactionDisc::POSITION_EXIT!=_position)){
			return(-3);
		}
		//4-3.如果数据检验成功，则直接成功返回。
		return(0);
	}
	//5.如果当前动作为默认动作，则不进行数据检验直接返回。
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
 * return: 如果函数执行成功返回值等于零，否则返回值不等于零（
 *         如果返回值大于零说明期望更改当前动作状态，如果返回
 *         值小于零说明不期望更改当前动作状态。）。
 */
int ReactionDiscRotation::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： ReactionDiscRotation::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	if(STATUS_DEFAULT==status){
		//2-1.清除反应盘旋转标记。
		_rotation_flag=FALSE;
		//2-2.如果当前反应盘上无管,则不进行任何默认转动，直接成功返回。
		if(!((((Instrument::instance())->get_components())
			->get_reaction_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.如果当前反应盘上有管，则命令反应盘旋转进行被动混匀。
		else{
			//2-3-1.根据当前旋转动作标识，计算反应盘应该旋转的位置。
			ReactionDisc::Position position=ReactionDisc::POSITION_EXIT;
			if(DIRECTION_NEGATIVE==_rotation_direction){
				position=ReactionDisc::POSITION_ADD_SPECIMEN;
			}
			//2-3-2.命令反应盘旋转，并且判断旋转是否成功。
			if((((Instrument::instance())->get_components())->
				get_reaction_disc())->rotate(1,position)<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： ReactionDiscRotation::execute \
函数中，调用 ReactionDisc::rotate 函数失败（1）！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-3-3.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 反应盘开始旋转。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-4.反置反应盘旋转标志。
			if(DIRECTION_POSITIVE==_rotation_direction){
				_rotation_direction=DIRECTION_NEGATIVE;
			}else{
				_rotation_direction=DIRECTION_POSITIVE;
			}
			//2-3-5.设置反应盘已经开始旋转标记。
			_rotation_flag=TRUE;
			//2-3-6.程序运行到此成功返回。
			return(0);
		}
	}
	//3.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//3-1.命令反应盘旋转，并且判断旋转是否成功。
		if((((Instrument::instance())->get_components())->
			get_reaction_disc())->rotate(_hole_no,static_cast<
			ReactionDisc::Position>(_position))<0){
			//a.设置当前未知错误标识。
			set_error(ERROR_UNKNOWN);
			//b.书写错误日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： ReactionDiscRotation::execute \
函数中，调用 ReactionDisc::rotate 函数失败（2）！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.程序运行到此直接返回错误。
			return(-3);
		}
		//3-2.程序运行到此成功返回。
		else{
			//3-2-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 反应盘开始旋转。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-2-2.程序运行到此成功返回。
			return(0);
		}
	}
	//4.如果当前动作处于其它状态。
	else{
		//4-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//4-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： ReactionDiscRotation::execute \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.程序运行到此直接返回错误。
		return(-4);
	}
}

/**
 * name: complete
 * brief: 完成当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值等于零，否则返回值不等于零（
 *         如果返回值大于零说明期望更改当前动作状态，如果返回
 *         值小于零说明不期望更改当前动作状态。）。
 */
int ReactionDiscRotation::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： ReactionDiscRotation::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	else if(STATUS_DEFAULT==status){
		//2-1.如果当前反应盘并未旋转。
		if(FALSE==_rotation_flag){
			return(0);//程序运行到此，直接成功返回。
		}
		//2-2.如果当前反应盘已经旋转。
		else{
			//2-2-1.如果当前反应盘旋转动作执行完成。
			if(ReactionDisc::FLAG_IDLE==(((Instrument::instance())->
				get_components())->get_reaction_disc())->
				get_rotation_response_flag()){
				//a.书写日志。
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： 反应盘旋转完成。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//b.程序运行到此成功返回。
				return(0);
			}
			//2-2-2.如果当前反应盘动作执行尚未完成。
			else{
				//2-2-2-1.增加当前动作错误次数。
				increase_defeats();
				//2-2-2-2.检测当前动作错误次数是否已达极限。
				if(get_defeats()>MAX_DEFEATS){
					//a.设置错误标识。
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.书写错误日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： ReactionDiscRotation::complete \
函数中，检测到反应盘旋转严重超时（1）！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s（%ld）： 反应盘旋转发生超时（1）！"),
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
	//3.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//3-1.如果当前反应盘旋转动作执行完成。
		if(ReactionDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_reaction_disc())->
			get_rotation_response_flag()){
			//3-1-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 反应盘旋转完成。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.程序运行到此成功返回。
			return(0);
		}
		//3-2.如果当前反应盘动作执行尚未完成。
		else{
			//3-2-1.增加当前动作错误次数。
			increase_defeats();
			//3-2-2.检测当前动作错误次数是否已达极限。
			if(get_defeats()>MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： ReactionDiscRotation::complete \
函数中，检测到反应盘旋转严重超时（2）！"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-4);
			}
			//3-2-3.如果当前错误次数尚未抵达极限。
			else{
				//a.设置错误标识。
				set_error(ERROR_TIMEOUT_T);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 反应盘旋转发生超时（2）！"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-5);
			}
		}
	}
	//4.如果当前动作处于其它状态。
	else{
		//4-1.设置错误标识。
		set_error(ERROR_UNKNOWN);
		//4-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： ReactionDiscRotation::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.程序运行到此直接返回错误。
		return(-6);
	}
}