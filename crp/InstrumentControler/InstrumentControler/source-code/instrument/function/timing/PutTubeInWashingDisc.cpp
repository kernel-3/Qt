#include"stdafx.h"
#include"PutTubeInWashingDisc.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/WashingDisc.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: PutTubeInWashingDisc
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
PutTubeInWashingDisc::PutTubeInWashingDisc(		
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~PutTubeInWashingDisc
 * brief: 析构函数。
 * param: --
 * return: --
 */
PutTubeInWashingDisc::~PutTubeInWashingDisc(void){
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int PutTubeInWashingDisc::is_valid() const{
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
int PutTubeInWashingDisc::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： PutTubeInWashingDisc::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.发送转运抓手放管到清洗盘指令，并且判断发送是否成功。
		if((((Instrument::instance())->get_components())->
			get_transport_tong())->put_tube_in_washing_disc()<0){
			//2-1-1.设置错误编码。
			set_error(ERROR_UNKNOWN);
			//2-1-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： PutTubeInWashingDisc::execute \
函数中，调用 TransportTong::put_tube_in_washing_disc 函数失败！"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.程序运行到此直接返回错误。
			return(-2);
		}
		//2-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 转运抓手开始放管到清洗盘。"),
			(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
		log.Format(_T("Error %s（%ld）： PutTubeInWashingDisc::execute \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
int PutTubeInWashingDisc::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）：PutTubeInWashingDisc::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果转运抓手放管到清洗盘完成。
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_put_tube_in_washing_disc_response_flag()){
			//2-1-1.输出日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 转运抓手放管到清洗盘完成。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.设置清洗盘进管位有管标志的期望值（此函数只在软件自发自收调试时起作用）。
			(((Instrument::instance())->get_components())->get_washing_disc())->
				set_having_tube_in_entry_flag_expect_value(WashingDisc::FLAGE_USED);
			//2-1-3.书写相关日志。
			log.Format(_T("Event %s（%ld）： 查询清洗盘进管位是否有管。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.发送指令读取清洗盘上的位置传感器，并且判断读取是否成功。
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->inquire_sensor()<0){
				//a.设置错误标识。
				set_error(ERROR_COMMUNICATION);
				//b.书写错误日志。
				log.Format(_T("Error %s（%ld）：PutTubeInWashingDisc::complete \
函数中，调用 WashingDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-1-5.如果当前清洗盘进管位有管。
			if(WashingDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
				get_washing_disc())->get_having_tube_in_entry_flag()){
				//a.设置清洗盘进管位状态为有管状态。
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_USED);
				//b.书写日志。
				log.Format(_T("Event %s（%ld）： 清洗盘进管位有管。"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.程序运行到此直接成功返回。
				return(0);
			}
			//2-1-6.如果当前清洗盘进管位未能检测到试管。
			else{
				//a.设置清洗盘进管位状态为无管状态。
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_EMPTY);
				//b.设置错误编码。
				set_error(ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED);
				//c.书写相关日志。
				log.Format(_T("Warning %s（%ld）： 清洗盘进管位无管。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.程序运行到此直接返回错误。
				return(1);
			}
		}
		//2-2.如果转运抓手回管到反应盘尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： PutTubeInWashingDisc::complete \
函数中，检测到转运抓手放管到清洗盘严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s（%ld）： 转运抓手放管到清洗盘时发生超时！"),
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
		log.Format(_T("Error %s（%ld）： PutTubeInWashingDisc::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-5);
	}
}