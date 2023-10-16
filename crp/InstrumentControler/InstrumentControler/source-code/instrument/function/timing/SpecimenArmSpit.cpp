#include"stdafx.h"
#include"SpecimenArmSpit.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/SpecimenArm.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/ReactionDisc.h"
#include<MMSystem.h>

/**
 * name: SpecimenArmSpit
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
SpecimenArmSpit::SpecimenArmSpit(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_spit_volume(0)
	,_down_steps(0){
}

/**
 * name: ~SpecimenArmSpit
 * breif: 析构函数。
 * param: --
 * return: --
 */
SpecimenArmSpit::~SpecimenArmSpit(void){
}

/**
 * name: set_volume
 * brief: 设置吐液的体积。
 * param: volume - 输入的吐液体积。
 * return: --
 */
void SpecimenArmSpit::set_spit_volume(const unsigned int volume){
	_spit_volume=volume;
}

/**
 * name: get_volume
 * breif: 获取吐液体积。
 * param: --
 * return: 返回吐液体积。
 */
unsigned int SpecimenArmSpit::get_spit_volume() const{
	return(_spit_volume);
}

/**
 * name: set_down_steps
 * brief: 设置下降步数。
 * param: down_steps - 输入的下降步数。
 * return: --
 */
void SpecimenArmSpit::set_down_steps(const unsigned int down_steps){
	_down_steps=down_steps;
}

/**
 * name: get_down_steps
 * brief: 获取下降步数。
 * param: --
 * return: 返回下降步数。
 */
unsigned int SpecimenArmSpit::get_down_steps() const{
	return(_down_steps);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int SpecimenArmSpit::clear(){
	//1.调用基类相应处理函数，并且记录处理结果。
	const int clear_result=Action::clear();
	//2.如果基类相应处理函数处理失败。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类相应处理函数处理成功。
	else if(0==clear_result){
		_spit_volume=0;
		_down_steps=0;
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
int SpecimenArmSpit::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_spit_volume=0;
	_down_steps=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int SpecimenArmSpit::is_valid() const{
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
		//没有必要检测体积以及下降步数。
		return(0);
	}
	//5.如果当前动作为默认动作，则不进行数据检验直接返回错误。
	else if(STATUS_DEFAULT==get_status()){
		return(-2);//此动作不支持默认动作。
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
int SpecimenArmSpit::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenArmSpit::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.发送样本臂吐液指令。
		if((((Instrument::instance())->get_components())->
			get_specimen_arm())->spit(_spit_volume,_down_steps)<0){
			//2-1-1.设置错误编码。
			set_error(ERROR_UNKNOWN);
			//2-1-2.书写日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： SpecimenArmSpit::execute \
函数中，调用 SpecimenArm::spit 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.程序运行到此直接返回错误。
			return(-2);
		}
		//2-2.设置反应盘相应孔的状态。
		const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
			get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
			get_hole_no_in_reaction_disc();
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_PROCESSING);
		//2-3.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 样本臂开始吐液。"),(
			COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-4.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenArmSpit::execute \
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
int SpecimenArmSpit::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenArmSpit::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.程序运行到此返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	if(STATUS_ENABLED==status){
		//2-1.如果样本臂吐液完成。
		if(SpecimenArm::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_specimen_arm())->get_spit_response_flag()){
			//2-1-1.设置反应盘相应孔的状态。
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
				ReactionDisc::HOLE_STATE_WAIT);
			//2-1-2.设置当前动作对应项目的加样完成标记。
			((((Instrument::instance())->get_functions())->get_timing())->
				get_tested_item(get_test_item_key()))->set_add_specimen_flag(TRUE);
			//2-1-3.输出日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 样本臂吐液成功完成。"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.程序运行到此直接成功返回。
			return(0);
		}
		//2-2.如果样本臂吐液尚未完成。
		else{
			//2-2-1.自增当前动作的错误次数。
			increase_defeats();
			//2-2-2.如果当前错误次数已达上限。
			if(get_defeats()>=MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： SpecimenArmSpit::complete \
函数中，检测到样本臂吐液严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s（%ld）： 样本臂吐液时发生超时！"),
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
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： SpecimenArmSpit::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-4);
	}
}