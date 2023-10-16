#include"stdafx.h"
#include"TakeTubeOutOfReactionDisc.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/ReactionDisc.h"
#include"../../component/WashingDisc.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/ReactionDisc.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfReactionDisc
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
TakeTubeOutOfReactionDisc::TakeTubeOutOfReactionDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_reserve_reaction_disc_hole_flag(FALSE){
}

/**
 * name: ~TakeTubeOutOfReactionDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
TakeTubeOutOfReactionDisc::~TakeTubeOutOfReactionDisc(void){
}

/**
 * name: set_reserve_reaction_disc_hole_flag
 * brief: 设置保留反应盘孔标志。
 * param: flag - 输入的是否保留反应盘孔标志。
 * return: --
 */
void TakeTubeOutOfReactionDisc::set_reserve_reaction_disc_hole_flag(const BOOL flag){
	_reserve_reaction_disc_hole_flag=flag;
}

/**
 * name: get_reserve_reaction_disc_hole_flag
 * brief: 获取保留反应盘孔标志。
 * param: --
 * return: 返回保留反应盘孔标志。
 */
BOOL TakeTubeOutOfReactionDisc::get_reserve_reaction_disc_hole_flag() const{
	return(_reserve_reaction_disc_hole_flag);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int TakeTubeOutOfReactionDisc::clear(){
	//1.调用基类相应处理函数，并且记录处理结果。
	const int clear_result=Action::clear();
	//2.如果基类相应处理函数处理失败。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类相应处理函数处理成功。
	else if(0==clear_result){
		_reserve_reaction_disc_hole_flag=FALSE;
		return(0);
	}
	//4.如果基类相应处理函数，期望忽略清除操作。
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
int TakeTubeOutOfReactionDisc::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_reserve_reaction_disc_hole_flag=FALSE;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfReactionDisc::is_valid() const{
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
		return(0);
	}
	//5.如果当前动作为默认动作，则不进行数据检验直接返回错误。
	else if(STATUS_DEFAULT==get_status()){
		return(-2);
	}
	//6.如果当前为未知情况，则直接返回错误。
	else{
		return(-3);
	}
}

/**
 * name: execute
 * breif: 执行当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfReactionDisc::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.设置反应盘出管位有管标记以及清洗盘进管位有管标记的期望值（此函数只在软件自发自收的调试状态时才起作用）。
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_having_tube_in_exit_flag_expect_value(ReactionDisc::FLAGE_USED);
		(((Instrument::instance())->get_components())->get_washing_disc())->
			set_having_tube_in_entry_flag_expect_value(WashingDisc::FLAGE_EMPTY);
		//2-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 检测反应盘出管位、清洗盘进管位是否有管。"),(
			COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.发送读取反应盘、清洗盘位置传感器指令。
		if((((Instrument::instance())->get_components())->
			get_reaction_disc())->inquire_sensor()<0){
			//2-3-1.设置错误编码。
			set_error(ERROR_COMMUNICATION);
			//2-3-2.书写日志。
			log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::execute \
函数中，调用 ReactionDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.程序运行到此直接返回错误。
			return(-2);
		}
		//2-4.如果反应盘出管位无管，则直接返回错误。
		if(ReactionDisc::FLAGE_EMPTY==(((Instrument::instance())->
			get_components())->get_reaction_disc())->
			get_having_tube_in_exit_flag()){
			//2-4-1.清除反应盘出管位状态。
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_EMPTY);
			//2-4-2.设置错误编码。
			set_error(ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC);
			//2-4-3.书写日志。
			log.Format(_T("Warning %s（%ld）： 检测到反应盘出管位无管！"),(
				COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-4-4.程序运行到此直接返回错误。
			return(-3);
		}
		//2-5.书写相关日志。
		log.Format(_T("Event %s（%ld）： 检测到反应盘出管位有管！"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-6.如果清洗盘进管位有管，则直接返回错误。
		if(WashingDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
			get_washing_disc())->get_having_tube_in_entry_flag()){
			//2-6-1.设置清洗盘进管位位置状态。
			(((Instrument::instance())->get_components())->get_washing_disc())->
				set_hole_state(WashingDisc::POSITION_ENTRY,
				WashingDisc::HOLE_STATE_FAILED);
			//2-6-2.将当前反应盘出管位状态设置为废管状态。
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
				ReactionDisc::HOLE_STATE_FAILED);
			//2-6-3.设置错误编码。
			set_error(ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT);
			//2-6-4.书写日志。
			log.Format(_T("Warning %s（%ld）： 检测到清洗盘进管位有管！"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-6-5.程序运行到此直接返回错误。
			return(-4);
		}
		//2-7.书写日志。
		log.Format(_T("Event %s（%ld）：  检测到清洗盘进管位无管！"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-8.发送从反应盘取管指令，并且判断发送是否成功。
		if((((Instrument::instance())->get_components())->get_transport_tong())->
			take_tube_out_of_reaction_disc()<0){
			//2-8-1.设置错误编码。
			set_error(ERROR_UNKNOWN);
			//2-8-2.书写日志。
			log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::execute \
函数中，调用 TransportTong::take_tube_out_of_reaction_disc 函数失败！"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-8-3.程序运行到此直接返回错误。
			return(-5);
		}
		//2-9.设置反应盘出管位试管状态。
		const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
			get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
			get_hole_no_in_reaction_disc();
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_PROCESSING);
		//2-10.书写日志。
		log.Format(_T("Event %s（%ld）： 转运抓手从反应盘开始取管。"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-11.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::execute \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-6);
	}
}

/**
 * name: complete
 * brief: 完成当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfReactionDisc::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）：TakeTubeOutOfReactionDisc::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果转运抓手从反应盘取管完成。
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_take_tube_out_of_reaction_disc_response_flag()){
			//2-1-1.输出日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 转运抓手从反应盘取管完成。"),(
					COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.设置反应盘出管位有管标记的期望值（此函数只在软件自发自收的调试状态时才起作用）。
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_exit_flag_expect_value(
				ReactionDisc::FLAGE_EMPTY);
			//2-1-3.书写相关日志。
			log.Format(_T("Event %s（%ld）： 检测反应盘出管位是否有管。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.发送读取反应盘位置传感器指令。
			if((((Instrument::instance())->get_components())->
				get_reaction_disc())->inquire_sensor()<0){
				//2-1-4-1.设置错误编码。
				set_error(ERROR_COMMUNICATION);
				//2-1-4-2.书写日志。
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::complete \
函数中，调用 ReactionDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//2-1-4-3.程序运行到此直接返回错误。
				return(-2);
			}
			//2-1-5.如果反应盘出管位有管。
			if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
				get_reaction_disc())->get_having_tube_in_exit_flag()){
				//a.设置反应盘出管位状态。
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_FAILED);
				//b.设置错误编码。
				set_error(ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED);
				//c.书写日志。
				log.Format(_T("Warning %s（%ld）： 检测到反应盘出管位有管！"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.程序运行到此直接返回错误。
				return(1);
			}
			//2-1-6.设置反应盘出管位状态。
			if(get_reserve_reaction_disc_hole_flag()){
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_RESERVED);
			}else{
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_EMPTY);
			}
			//2-1-7.书写相关日志。
			log.Format(_T("Event %s（%ld）： 检测到反应盘出管位无管！"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-8.程序运行到此直接成功返回。
			return(0);
		}
		//2-2.如果洗试剂尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::complete \
函数中，检测到转运抓手从反应盘取管严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
			//2-2-3.如果当前错误次数尚未抵达上限。
			else{
				//a.设置错误标识。
				set_error(ERROR_TIMEOUT_T);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 转运抓手从反应盘取管时发生超时！"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-4);
			}
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfReactionDisc::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-5);
	}
}