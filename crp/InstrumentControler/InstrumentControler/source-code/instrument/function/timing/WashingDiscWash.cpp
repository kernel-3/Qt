#include"stdafx.h"
#include"WashingDiscWash.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: WashingDiscWash
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
WashingDiscWash::WashingDiscWash(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_washing_flag(FALSE)
	,_substrate_type(0)
	,_substrate_volume(0){
}

/**
 * name: ~WashingDiscWash
 * brief: 析构函数。
 * param: --
 * return: --
 */
WashingDiscWash::~WashingDiscWash(void){
}

/**
 * name: set_substrate_type
 * brief: 设置底物类型。
 * param: substrate_type - 输入的底物类型。
 * return: --
 */
void WashingDiscWash::set_substrate_type(const unsigned int substrate_type){
	_substrate_type=substrate_type;
}

/**
 * name: get_substrate_type
 * breif: 获取底物类型。
 * param: --
 * return: 返回底物类型。
 */
unsigned int WashingDiscWash::get_substrate_type() const{
	return(_substrate_type);
}

/**
 * name: set_substrate_volume
 * brief: 设置底物体积。
 * param: substrate_volume - 输入的底物体积。
 * return: --
 */
void WashingDiscWash::set_substrate_volume(const unsigned int substrate_volume){
	_substrate_volume=substrate_volume;
}

/**
 * name: get_substrate_volume
 * brief: 获取底物体积。
 * param: --
 * return: 返回底物体积。
 */
unsigned int WashingDiscWash::get_substrate_volume() const{
	return(_substrate_volume);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果忽略当前动作的清除操作，返回大于零的数。
 *         如果成功清除当前动作，返回零。
 *         如果清除当前动作失败，则返回小于零的数。
 */
int WashingDiscWash::clear(){
	//1.调用基类相应清理函数，并且记录基类清理结果。
	const int clear_result=Action::clear();
	//2.如果基类清理时发生错误，则直接返回。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类成功清理当前动作，则清除当前子类中所记录的数据。
	else if(0==clear_result){
		//3-1.清除当前动作中的数据。
		_washing_flag=FALSE;
		_substrate_type=0;
		_substrate_volume=0;
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
int WashingDiscWash::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_washing_flag=FALSE;
	_substrate_type=0;
	_substrate_volume=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int WashingDiscWash::is_valid() const{
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
		//4-1.如果底物类型非法，则直接返回错误。
		if((WashingDisc::SUBSTRATE_TYPE_AB!=_substrate_type)&&(
			WashingDisc::SUBSTRATE_TYPE_C!=_substrate_type)&&(
			WashingDisc::SUBSTRATE_TYPE_BUFFER_SOLUTION!=_substrate_type)){
			return(-2);
		}
		//4-2.这里暂不对底物体积进行验证。
		//4-3.如果数据检验成功，则直接成功返回。
		return(0);
	}
	//5.如果当前动作为默认动作，则不进行数据检验直接返回。
	else if(STATUS_DEFAULT==get_status()){
		return(0);
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
 *         值小于零说明不期望更改当前动作状态。）。
 */
int WashingDiscWash::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscWash::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	if(STATUS_DEFAULT==status){
		//2-1.清除清洗盘清洗标记。
		_washing_flag=FALSE;
		//2-2.如果当前清洗盘上无管,则不进行任何默认清洗操作，直接成功返回。
		if(!((((Instrument::instance())->get_components())
			->get_washing_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.如果当前清洗盘上有管，则命令清洗盘进行清洗。
		else{
			//2-3-1.命令清洗盘清洗，并且判断清洗是否成功。
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->wash()<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： WashingDiscWash::execute \
函数中，调用 WashingDisc::wash 函数失败（1）！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-3-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 清洗盘开始清洗。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-3.设置清洗盘已经开始清洗标记。
			_washing_flag=TRUE;
			//2-3-4.程序运行到此成功返回。
			return(0);
		}
	}
	//3.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//3-1.命令清洗盘开始清洗，并且判断清洗是否成功。
		if((((Instrument::instance())->get_components())->
			get_washing_disc())->wash(static_cast<WashingDisc::
			SubstrateType>(_substrate_type),_substrate_volume)<0){
			//a.设置当前未知错误标识。
			set_error(ERROR_UNKNOWN);
			//b.书写错误日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： WashingDiscWash::execute \
函数中，调用 WashingDisc::wash 函数失败（2）！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.程序运行到此直接返回错误。
			return(-3);
		}
		//3-2.程序运行到此成功返回。
		else{
			//3-2-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 清洗盘开始清洗。"),
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
		log.Format(_T("Error %s（%ld）： WashingDiscWash::execute \
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
int WashingDiscWash::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： WashingDiscWash::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	else if(STATUS_DEFAULT==status){
		//2-1.如果当前清洗盘并未清洗。
		if(FALSE==_washing_flag){
			return(0);//程序运行到此，直接成功返回。
		}
		//2-2.如果当前清洗盘已经清洗。
		else{
			//2-2-1.如果当前清洗盘旋清洗作执行完成。
			if(WashingDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_washing_disc())->get_wash_response_flag()){
				//a.书写日志。
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： 清洗盘清洗完成。"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//b.程序运行到此成功返回。
				return(0);
			}
			//2-2-2.如果当前清洗盘清洗动作执行尚未完成。
			else{
				//2-2-2-1.增加当前动作错误次数。
				increase_defeats();
				//2-2-2-2.检测当前动作错误次数是否已达极限。
				if(get_defeats()>MAX_DEFEATS){
					//a.设置错误标识。
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.书写错误日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： WashingDiscWash::complete \
函数中，检测到清洗盘清洗严重超时（1）！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s（%ld）： 清洗盘清洗发生超时（1）！"),
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
		//3-1.如果当前清洗盘清洗动作执行完成。
		if(WashingDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_washing_disc())->
			get_wash_response_flag()){
			//3-1-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 清洗盘清洗完成。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.程序运行到此成功返回。
			return(0);
		}
		//3-2.如果当前清洗盘动作执行尚未完成。
		else{
			//3-2-1.增加当前动作错误次数。
			increase_defeats();
			//3-2-2.检测当前动作错误次数是否已达极限。
			if(get_defeats()>MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： WashingDiscWash::complete \
函数中，检测到清洗盘清洗严重超时（2）！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s（%ld）： 清洗盘清洗发生超时（2）！"),
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
		log.Format(_T("Error %s（%ld）： WashingDiscWash::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.程序运行到此直接返回错误。
		return(-6);
	}
}