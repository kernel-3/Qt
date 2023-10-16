#include"stdafx.h"
#include"PutTubeInReactionDisc.h"
#include"../../../common/Logs.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/ReactionDisc.h"
#include"../../component/LoadTong.h"
#include"../../component/TubeStorehouse.h"
#include"../../function/timing/Timing.h"
#include"../../function/Functions.h"
#include"../../../export/TestItem.h"
#include<MMSystem.h>

//define
unsigned int PutTubeInReactionDisc::_put_tube_in_failed_times=0;

/**
 * name: PutTubeInReactionDisc
 * breif: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
PutTubeInReactionDisc::PutTubeInReactionDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~PutTubeInReactionDisc
 * breif: 析构函数。
 * param: --
 * return: --
 */
PutTubeInReactionDisc::~PutTubeInReactionDisc(void){
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int PutTubeInReactionDisc::is_valid() const{
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
 * return: 如果函数执行成功返回值等于零，否则返回值不等于零（
 *         如果返回值大于零说明期望更改当前动作状态，如果返回
 *         值小于零说明不期望更改当前动作状态）。
 */
int PutTubeInReactionDisc::execute(const Status status){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作状态处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.设置反应盘上位置传感器状态标志期望值（
		//    此行代码只在自发自收的调试环境中起作用）。
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_having_tube_in_entry_flag_expect_value(ReactionDisc::FLAGE_EMPTY);
		//2-2.发送指令查询反应盘上位置传感器，并且判断查询是否成功。
		if(((((Instrument::instance())->get_components())->get_reaction_disc())->
			inquire_sensor())<0){
			//2-2-1.设置错误编码。
			set_error(ERROR_COMMUNICATION);
			//2-2-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::execute \
函数中，调用 ReactionDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-2-3.程序运行到此直接返回错误
			return(-2);
		}
		//2-3.如果当前检测到反应盘进管位上有管。
		if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
			get_reaction_disc())->get_having_tube_in_entry_flag()){
			//remark: 这里是否需要累积错误次数？？用以判断流程是否需要停止。
			//2-3-1.设置错误编码。
			set_error(ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT);
			//2-3-2.将反应盘上指定管位设置为错误状态。
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_FAILED);
			//2-3-3.书写相关日志。
			CString log(_T(""));
			log.Format(_T("Warning %s（%ld）： 装载抓手放管到反应盘时检测到试管冲突！"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-4.程序运行到此直接返回错误。
			return(-3);
		}
		//2-4.如果当前反应盘进管位上无管。
		else{
			//2-4-1.发送指令命令装载抓手放管。
			if((((Instrument::instance())->get_components())->
				get_load_tong())->put_tube_in()<0){
				//a.设置错误编码。
				set_error(ERROR_UNKNOWN);
				//b.书写日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::execute \
函数中，调用 LoadTong::put_tube_in 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-4);
			}
			//2-4-2.将反应盘上指定管位设置为处理状态。
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_PROCESSING);
			//2-4-3.书写相关日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 装载抓手开始放管。"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-4-4.放管指令一旦发送，则认为装载抓手上已经无管。
			(((Instrument::instance())->get_components())->get_load_tong())->
				set_having_tube_flag(FALSE);
			//2-4-5.程序运行到此成功返回。
			return(0);
		}
	}
	//3.如果当前动作状态处于其它状态。
	else{
		//3-1.设置未知错误状态
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::execute \
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
 * return: 如果函数执行成功返回值等于零，否则返回值不等于零（
 *         如果返回值大于零说明期望更改当前动作状态，如果返回
 *         值小于零说明不期望更改当前动作状态）。
 */
int PutTubeInReactionDisc::complete(const Status status){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.检测放管动作是否完成。
		if(LoadTong::FLAG_IDLE==(((Instrument::instance())->get_components())->
			get_load_tong())->get_put_tube_in_response_flag()){
			//2-1-1.设置反应盘上位置传感器状态标志期望值（此行代码只在自发自收的调试环境中起作用）。
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_having_tube_in_entry_flag_expect_value(ReactionDisc::FLAGE_USED);
			//2-1-2.发送指令检测当前反应盘进管位是否有管。
			if(((((Instrument::instance())->get_components())->get_reaction_disc())->
				inquire_sensor())<0){
				//a.设置错误编码。
				set_error(ERROR_COMMUNICATION);
				//b.书写日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::complete \
函数中，调用 ReactionDisc::inquire_sensor 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-1-3.如果当前反应盘进管位有管，放管成功，则直接成功返回。
			if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->
				get_components())->get_reaction_disc())->
				get_having_tube_in_entry_flag()){
				//a.清除放管失败次数。
				_put_tube_in_failed_times=0;
				//b.设置反应盘上当前孔位状态。
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->get_reaction_disc())->
					set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_WAIT);
				//c.输入相关日志。
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： 装载抓手放管完成。"),(
					COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//d.程序运行到此成功返回。
				return(0);
			}
			//2-1-4.如果当前反应盘进管位无管。
			else{
				//1>.放管失败次数自加。
				++_put_tube_in_failed_times;
				//2>.设置反应盘上相应孔位状态为空。
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->get_reaction_disc())->
					set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_EMPTY);
				//3>.如果放管失败次数超过上限。
				if(_put_tube_in_failed_times>MAX_PUT_TUBE_IN_FAILED_TIMES){
					//3-1>.设置错误编码（如果连续抓管10次都未成功，则认为试管仓无管）。
					set_error(ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE);
					//3-2>.清空试管仓剩余管数。
					(((Instrument::instance())->get_components())->
						get_tube_storehouse())->clear_tube_count();
					//3-3>.书写日志。
					CString log(_T(""));
					log.Format(_T("Warning %s（%ld）： 装载抓手放管时，检测到试管仓无管！"),(
						COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//3-4>.程序运行到此直接返回错误。
					return(1);//当返回值大于等于零的时候，期望当前动作状态变更。
				}
				//4>.如果放管失败次数尚未超过上限。。
				else{
					//4-1>.设置错误编码。
					set_error(ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED);
					//4-2>.书写日志。
					CString log(_T(""));
					log.Format(_T("Warning %s（%ld）： 装载抓手放管后，未能在反应盘进管位检测到反应管！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//4-3>.程序运行到此直接返回错误。
					return(2);//当返回值大于等于零的时候，期望当前动作状态变更。
				}
			}
		}
		//2-2.如果放管动作尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误编码。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::complete \
函数中，检测到装载抓手放管严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
			//2-2-3.如果当前错误次数尚未抵达上限。
			else{
				//a.设置错误编码。
				set_error(ERROR_TIMEOUT_T);
				//b.书写事件、错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 装载抓手放管发生超时！"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-4);
			}
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误状态
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： PutTubeInReactionDisc::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-5);
	}
}