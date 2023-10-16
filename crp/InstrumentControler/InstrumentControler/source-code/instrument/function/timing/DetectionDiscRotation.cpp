#include"stdafx.h"
#include"DetectionDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/DetectionDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include<MMSystem.h>

/**
 * name: DetectionDiscRotation
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
DetectionDiscRotation::DetectionDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_position(0){
}

/**
 * name: ~DetectionDiscRotation
 * brief: 析构函数。
 * param: --
 * return: --
 */
DetectionDiscRotation::~DetectionDiscRotation(void){
}

/**
 * name: set_position
 * breif: 设置位置。
 * param: position - 输入的位置。
 * return: --
 */
void DetectionDiscRotation::set_position(const unsigned int position){
	_position=position;
}

/** 
 * name: get_position
 * brief: 获取位置。
 * param: --
 * return: 返回位置。
 */
unsigned int DetectionDiscRotation::get_position() const{
	return(_position);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int DetectionDiscRotation::clear(){
	//1.调用基类相应清理函数，并且记录基类清理结果。
	const int clear_result=Action::clear();
	//2.如果基类清理时发生错误，则直接返回。
	if(clear_result<0){
		return(-1);
	}
	//3.如果基类成功清理当前动作，则清除当前子类中所记录的数据。
	else if(0==clear_result){
		//3-1.清除当前动作中的数据。
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
int DetectionDiscRotation::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
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
int DetectionDiscRotation::is_valid() const{
	//1.调用基类相应处理函数，并且记录处理结果
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
		//4-1.如果位置非法，则直接返回错误。
		if((DetectionDisc::POSITION_ENTRY!=_position)&&(
			DetectionDisc::POSITION_DETECTION!=_position)&&(
			DetectionDisc::POSITION_EXIT!=_position)){
			return(-2);
		}
		//4-2.如果数据检验成功，则直接成功返回。
		return(0);
	}
	//5.如果当前为未知情况，则直接返回错误。
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
int DetectionDiscRotation::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： DetectionDiscRotation::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//2-1.声明当前操作所需变量。
		unsigned int hole_no_in_detection_disc=0;
		//2-2.如果当前命令检测盘旋转到进管位。
		if(DetectionDisc::POSITION_ENTRY==_position){
			//2-2-1.获取当前检测盘上空闲孔号。
			hole_no_in_detection_disc=(((Instrument::instance())->get_components())->
				get_detection_disc())->get_empty_hole_no();
			//2-2-2.如果获取孔号失败，则直接返回错误。
			if(0==hole_no_in_detection_disc){
				//a.设置错误编码。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： DetectionDiscRotation::execute \
函数中，调用 DetectionDisc::get_empty_hole_no 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-2-3.为当前动作对应项目设置检测盘孔号。
			((((Instrument::instance())->get_functions())->get_timing())->
				get_tested_item(get_test_item_key()))->set_hole_no_in_detection_disc(
				hole_no_in_detection_disc);
		}
		//2-3.如果当前命令检测盘旋转到其它位置。
		else{
			//2-3-1.利用当前动作的项目标识,获取当前项目所占用的孔号。
			hole_no_in_detection_disc=((((Instrument::instance())->get_functions())->
				get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			//2-3-2.如果获取孔号失败。
			if(0==hole_no_in_detection_disc){
				//a.设置错误编码。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： DetectionDiscRotation::execute \
函数中，调用 TestItem::get_hole_no_in_detection_disc 函数失败！"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-3);
			}
		}
		//2-4.发送指令，命令检测盘旋转。
		if((((Instrument::instance())->get_components())->
			get_detection_disc())->rotate(hole_no_in_detection_disc,static_cast<
			DetectionDisc::Position>(get_position()))<0){
			//a.设置当前未知错误标识。
			set_error(ERROR_UNKNOWN);
			//b.书写错误日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： DetectionDiscRotation::execute \
函数中，调用 DetectionDisc::rotate 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.程序运行到此直接返回错误。
			return(-4);
		}
		//2-5.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 检测盘开始旋转。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-6.程序运行到此直接成功返回。
		return(0);
	}
	//3.如果当前动作处于其它状态。
	else{
		//3-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//3-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： DetectionDiscRotation::execute \
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
int DetectionDiscRotation::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： DetectionDiscRotation::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//2-1.如果当前检测盘旋转动作执行完成。
		if(DetectionDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_detection_disc())->get_rotation_response_flag()){
			//2-1-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 检测盘旋转完成。"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.程序运行到此成功返回。
			return(0);
		}
		//2-2.如果当前检测盘动作执行尚未完成。
		else{
			//2-2-1.增加当前动作错误次数。
			increase_defeats();
			//2-2-2.检测当前动作错误次数是否已达极限。
			if(get_defeats()>MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： DetectionDiscRotation::complete \
函数中，检测到检测盘旋转严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-2-3.如果当前错误次数尚未抵达极限。
			else{
				//a.设置错误标识。
				set_error(ERROR_TIMEOUT_T);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Warning %s（%ld）： 检测盘旋转发生超时！"),
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
		log.Format(_T("Error %s（%ld）： DetectionDiscRotation::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.程序运行到此直接返回错误。
		return(-4);
	}
}