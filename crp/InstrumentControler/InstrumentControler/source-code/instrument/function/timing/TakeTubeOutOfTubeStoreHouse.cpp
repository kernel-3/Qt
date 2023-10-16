#include"stdafx.h"
#include"TakeTubeOutOfTubeStoreHouse.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TubeStorehouse.h"
#include"../../../common/Logs.h"
#include"../../component/LoadTong.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfTubeStoreHouse
 * breif: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
TakeTubeOutOfTubeStoreHouse::TakeTubeOutOfTubeStoreHouse(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~TakeTubeOutOfTubeStoreHouse
 * brief: 析构函数。
 * param: --
 * return: --
 */
TakeTubeOutOfTubeStoreHouse::~TakeTubeOutOfTubeStoreHouse(void){
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int TakeTubeOutOfTubeStoreHouse::is_valid() const{
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
int TakeTubeOutOfTubeStoreHouse::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果当前装载抓手上有管。
		if((((Instrument::instance())->get_components())->
			get_load_tong())->get_having_tube_flag()){
			return(0);
		}
		//2-2.如果当前试管仓有管。
		else if((((Instrument::instance())->get_components())->
			get_tube_storehouse())->are_there_tubes()){
			//2-2-1.获取当前试管仓试管位置信息，并且判断获取是否成功。
			unsigned int row=0;
			unsigned int col=0;
			if((((Instrument::instance())->get_components())->
				get_tube_storehouse())->get_tube_position(row,col)<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::execute \
函数中，调用 TubeStorehouse::get_tube_position 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-2-2.命令装载抓手取管。
			if((((Instrument::instance())->get_components())->
				get_load_tong())->take_tube_out(row,col)<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）：TakeTubeOutOfTubeStoreHouse::execute \
函数中，调用 LoadTong::take_tube_out 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
			//2-2-3.书写相应日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 装载抓手开始取管。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-2-4.如果装载抓手取管成功，则为当前试管仓减去试管计数。
			//remark: 只要一抓了，就认为此位置上的试管没有了。
			(((Instrument::instance())->get_components())->
				get_tube_storehouse())->decrease_tube_count();
			//2-2-5.程序运行到此成功返回。
			return(0);
		}
		//2-3.如果当前试管仓无管。
		else{
			//2-3-1.设置试管仓无管错误。
			set_error(ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE);
			//2-3-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Warning %s（%ld）： 装载抓手取管时，检测到试管仓无管！"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.程序运行到此直接返回错误。
			return(-4);
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误状态。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::execute \
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
int TakeTubeOutOfTubeStoreHouse::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果当前装载抓手上有管。
		if((((Instrument::instance())->get_components())->
			get_load_tong())->get_having_tube_flag()){
			return(0);
		}
		//2-2.如果装载抓手取管动作完成。
		else if(LoadTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_load_tong())->
			get_take_tube_out_response_flag()){
			//2-2-1.设置装载抓手有管状态。
			(((Instrument::instance())->get_components())->
				get_load_tong())->set_having_tube_flag(TRUE);
			//2-2-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 装载抓手取管完成。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-2-3.程序运行到此成功返回。
			return(0);
		}
		//2-3.如果进管取管动作尚未完成。
		else{
			//2-3-1.自增当前动作的错误次数。
			increase_defeats();
			//2-3-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误编码。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::complete \
函数中，检测到装载抓手取管严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-3-3.如果当前错误次数尚未抵达上限。
			else{
				//a.设置错误编码。
				set_error(ERROR_TIMEOUT_T);
				//b.书写事件、错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 装载抓手取管发生超时！"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
		}
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置错误编码。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： TakeTubeOutOfTubeStoreHouse::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-4);
	}
}