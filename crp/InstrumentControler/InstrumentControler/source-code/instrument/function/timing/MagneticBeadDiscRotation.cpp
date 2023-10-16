#include"stdafx.h"
#include"MagneticBeadDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/MagneticBeadDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

//定义静态变量。
unsigned int MagneticBeadDiscRotation::_direction=MagneticBeadDisc::DIRECTION_NEGATIVE;

/**
 * name: MagneticBeadDiscRotation
 * breif: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
MagneticBeadDiscRotation::
	MagneticBeadDiscRotation(	
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE)
	,_position_no(0){
}

/**
 * name: ~MagneticBeadDiscRotation
 * brief: 析构函数。
 * param: --
 * return: --
 */
MagneticBeadDiscRotation::
	~MagneticBeadDiscRotation(void){
}

/**
 * name: set_position_no
 * brief: 设置位置号。
 * param: position_no - 输入的位置号。
 * return: --
 */
void MagneticBeadDiscRotation::set_position_no(
	const int position_no){
	_position_no=position_no;
}

/**
 * name: get_position_no
 * brief: 获取位置号。
 * param: --
 * return: 返回位置号。
 */
int MagneticBeadDiscRotation::get_position_no() const{
	return(_position_no);
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，
 *         否则返回值小于零。
 */
int MagneticBeadDiscRotation::clear(){
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
		_position_no=0;
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
int MagneticBeadDiscRotation::reset(){
	//1.调用基类相应处理函数，并且判断处理是否成功。
	if(Action::reset()<0){
		return(-1);
	}
	//2.重置当前动作数据。
	_rotation_flag=FALSE;
	_position_no=0;
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int MagneticBeadDiscRotation::is_valid() const{
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
		//4-1.如果位置号非法。
		if((_position_no<1)||(_position_no>
			MagneticBeadDisc::POSITION_COUNT)){
			return(-2);
		}
		//4-2.如果数据检验成功，则直接成功返回。
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
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MagneticBeadDiscRotation::execute(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::execute(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::execute \
函数中，调用 Action::execute 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	if(STATUS_DEFAULT==status){
		//2-1.清除磁珠盘旋转标记。
		_rotation_flag=FALSE;
		//2-2.如果当前磁珠盘上无磁珠,则不进行任何默认转动，直接成功返回。
		if(0/*unfinished: 检测磁珠盘上是否有磁珠*/){
			return(0);
		}
		//2-3.如果当前磁珠盘上有试剂，则命令磁珠盘旋转进行被动混匀。
		else{
			//2-3-1.根据当前旋转方向标识，计算磁珠盘应该旋转的方向。
			if(_direction==MagneticBeadDisc::DIRECTION_NEGATIVE){
				_direction=MagneticBeadDisc::DIRECTION_POSITIVE;
			}else{
				_direction=MagneticBeadDisc::DIRECTION_NEGATIVE;
			}
			//2-3-2.命令磁珠盘混匀旋转，并且判断旋转是否成功。
			if((((Instrument::instance())->get_components())->
				get_magnetic_bead_disc())->mix_rotate(static_cast<
				MagneticBeadDisc::Direction>(_direction))<0){
				//a.设置当前未知错误标识。
				set_error(ERROR_UNKNOWN);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::execute \
函数中，调用 MagneticBeadDisc::mix_rotate 函数失败！"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.程序运行到此直接返回错误。
				return(-2);
			}
			//2-3-3.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 磁珠盘开始混匀旋转。"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-4.设置磁珠盘已经开始旋转标记。
			_rotation_flag=TRUE;
			//2-3-5.程序运行到此成功返回。
			return(0);
		}
	}
	//3.如果当前动作处于有效状态。
	else if(STATUS_ENABLED==status){
		//3-1.命令磁珠旋转，并且判断旋转是否成功。
		if((((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->rotate(_position_no)<0){
			//a.设置当前未知错误标识。
			set_error(ERROR_UNKNOWN);
			//b.书写错误日志。
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::execute \
函数中，调用 MagneticBeadDisc::rotate 函数失败！"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.程序运行到此直接返回错误。
			return(-3);
		}
		//3-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 磁珠盘开始旋转。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//3-3.程序运行到此成功返回。
		return(0);
	}
	//4.如果当前动作处于其它状态。
	else{
		//4-1.设置未知错误标识。
		set_error(ERROR_UNKNOWN);
		//4-2.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::execute \
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
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MagneticBeadDiscRotation::complete(const Status status){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(Action::complete(status)<0){
		//1-1.书写错误日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::complete \
函数中，调用 Action::complete 函数失败！"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.如果当前动作处于默认状态。
	else if(STATUS_DEFAULT==status){
		//2-1.如果当前磁珠盘并未混匀旋转。
		if(FALSE==_rotation_flag){
			return(0);//程序运行到此，直接成功返回。
		}
		//2-2.如果当前磁珠盘已经开始混匀旋转。
		else{
			//2-2-1.如果当前磁珠盘混匀旋转动作执行完成。
			if(MagneticBeadDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_magnetic_bead_disc())->get_mixing_rotation_response_flag()){
				//a.书写日志。
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： 磁珠盘混匀旋转完成。"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
					log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::complete \
函数中，检测到磁珠盘混匀旋转严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s（%ld）： 磁珠盘混匀旋转发生超时！"),(
						COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
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
		//3-1.如果当前磁珠盘旋转动作执行完成。
		if(MagneticBeadDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_magnetic_bead_disc())->
			get_rotation_response_flag()){
			//3-1-1.书写日志。
			CString log(_T(""));
			log.Format(_T("Event %s（%ld）： 磁珠盘旋转完成。"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.程序运行到此成功返回。
			return(0);
		}
		//3-2.如果当前磁珠盘旋转动作执行尚未完成。
		else{
			//3-2-1.增加当前动作错误次数。
			increase_defeats();
			//3-2-2.检测当前动作错误次数是否已达极限。
			if(get_defeats()>MAX_DEFEATS){
				//a.设置错误标识。
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.书写错误日志。
				CString log(_T(""));
				log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::complete \
函数中，检测到磁珠盘旋转严重超时！"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s（%ld）： 磁珠盘旋转发生超时！"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
		log.Format(_T("Error %s（%ld）： MagneticBeadDiscRotation::complete \
函数中，检测到未知的动作状态！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.程序运行到此直接返回错误。
		return(-6);
	}
}