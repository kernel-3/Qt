#include"stdafx.h"
#include"TakeTubeOutOfWashingDisc.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfWashingDisc
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
TakeTubeOutOfWashingDisc::TakeTubeOutOfWashingDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_stop_position(0){
}

/**
 * name: ~TakeTubeOutOfWashingDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
TakeTubeOutOfWashingDisc::~TakeTubeOutOfWashingDisc(void){
}

/**
 * name: set_stop_position
 * brief: 设置停止位置。
 * param: stop_position - 输入的停止位置。
 * return: --
 */
void TakeTubeOutOfWashingDisc::set_stop_position(
	const unsigned int stop_position){
	_stop_position=stop_position;
}

/**
 * name: get_stop_position
 * brief: 获取停止位置。
 * param: --
 * return: 返回停止位置。
 */
unsigned int TakeTubeOutOfWashingDisc::get_stop_position() const{
	return(_stop_position);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果忽略当前动作的清除操作，返回大于零的数。
 *         如果成功清除当前动作，返回零。
 *         如果清除当前动作失败，则返回小于零的数。
 */
int TakeTubeOutOfWashingDisc::clear(){
	//1.调用基类相应清理函数，并且记录基类清理结果。
	const int clear_result=Action::clear();
	//2.如果基类清理时发生错误，则直接返回。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类成功清理当前动作，则清除当前子类中所记录的数据。
	else if(0==clear_result){
		//3-1.清除当前动作中的数据。
		_stop_position=0;
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
int TakeTubeOutOfWashingDisc::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_stop_position=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfWashingDisc::is_valid() const{
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
		//4-1.如果停止位置非法，则直接返回错误。
		if((TransportTong::STOP_POSITION_REACTION_DISC!=_stop_position)&&(
			TransportTong::STOP_POSITION_DETECTION_DISC!=_stop_position)){
			return(-2);
		}
		//4-2.如果数据检验成功，则直接成功返回。
		return(0);
	}
	//5.如果当前动作为默认动作，则不进行数据检验直接错误。
	else if(STATUS_DEFAULT==get_status()){
		return(-3);
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
int TakeTubeOutOfWashingDisc::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.设置清洗盘出管位位置传感器的期望值（此函数调用只在软件自发、自收的调试状态下起作用）。
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_having_tube_in_exit_flag_expect_value(
			WashingDisc::FLAGE_USED);
		//2-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 检测清洗盘出管位是否有管。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.发送指令，检测清洗盘出管位是否有管。
		if((((Instrument::instance())->get_components())->
			get_washing_disc())->inquire_sensor()<0){
			//2-3-1.设置错误编码。
			set_error(ERROR_COMMUNICATION);
			//2-3-2.书写相关日志。
			log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::execute \
函数中，调用 WashingDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.程序运行到此直接返回错误。
			return(-2);//当前动作的状态不发生变化。
		}
		//2-4.书写相关日志。
		log.Format(_T("Event %s（%ld）： 检测清洗盘出管位是否有管成功。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-5.如果当前清洗盘出管位无管。
		if(WashingDisc::FLAGE_EMPTY==(((Instrument::instance())->
			get_components())->get_washing_disc())->
			get_having_tube_in_exit_flag()){
			//2-5-1.设置错误编码。
			set_error(ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC);
			//2-5-2.设置清洗盘相应位置上的孔状态为无管状态。
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_hole_state(
				WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_EMPTY);
			//2-5-3.书写相关日志。
			log.Format(_T("Warning %s（%ld）： 检测到清洗盘出管位无管。"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-5-4.程序运行到此直接返回错误。
			return(-3);//当前动作的状态不发生变化。
		}
		//2-6.如果当前清洗盘出管位有管，书写相关日志。
		log.Format(_T("Event %s（%ld）： 检测到清洗盘出管位有管。"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-7.发送从清洗盘取管指令，并且判断发送是否成功。
		if((((Instrument::instance())->get_components())->get_transport_tong())->
			take_tube_out_of_washing_disc(static_cast<TransportTong::StopPosition>(
			_stop_position))<0){
			//2-7-1.设置错误编码。
			set_error(ERROR_UNKNOWN);
			//2-7-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::execute \
函数中，调用 TransportTong::take_tube_out_of_washing_disc 函数失败！"),(
				COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-7-3.程序运行到此直接返回错误。
			return(-4);
		}
		//2-8.书写日志。
		log.Format(_T("Event %s（%ld）： 转运抓手从清洗盘开始取管。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-9.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::execute \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-5);
	}
}

/**
 * name: complete
 * brief: 完成当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfWashingDisc::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果转运抓手从清洗盘取管完成。
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_take_tube_out_of_washing_disc_response_flag()){
			//2-1-1.输出日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 转运抓手从清洗盘取管结束。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.设置清洗盘出管位有管标记的期望值（此处调用只在自发自收的调试情况下有用）。
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_exit_flag_expect_value(
				WashingDisc::FLAGE_EMPTY);
			//2-1-3.书写相关日志。
			log.Format(_T("Event %s（%ld）： 检测清洗盘出管位是否有管。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.读取传感器，检测清洗盘出管位是否仍然有管。
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->inquire_sensor()<0){
				//a.设置错误编码。
				set_error(ERROR_COMMUNICATION);
				//b.书写日志。
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::complete \
函数中，调用 WashingDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误
				return(-2);
			}
			//2-1-5.书写相关日志。
			log.Format(_T("Event %s（%ld）： 检测清洗盘出管位是否有管结束。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-6.如果当前清洗盘出管位无管。
			if(WashingDisc::FLAGE_EMPTY==(((Instrument::instance())->
				get_components())->get_washing_disc())->
				get_having_tube_in_exit_flag()){
				//a.清空清洗盘出管位位置状态。
				(((Instrument::instance())->get_components())->
					get_washing_disc())->set_hole_state(
					WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_EMPTY);
				//b.书写日志。
				log.Format(_T("Event %s（%ld）： 清洗盘出管位无管。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.程序运行到此成功返回。
				return(0);
			}
			//2-1-7.如果当前清洗盘出官位有管。
			else{
				//a.设置错误编码。
				set_error(ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED);
				//b.清空清洗盘出管位位置状态。
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_FAILED);
				//c.书写日志。
				log.Format(_T("Warning %s（%ld）： 清洗盘出管位有管。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.程序运行到此直接返回错误。
				return(1);//命令当前动作状态改变。
			}
		}
		//2-2.如果转运抓手从清洗盘取管尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::complete \
函数中，检测到转运抓手从清洗盘取管严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s（%ld）： 转运抓手从清洗盘取管时发生超时！"),
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
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfWashingDisc::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-5);
	}
}