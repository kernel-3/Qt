#include"stdafx.h"
#include"Action.h"
#include"SequenceDiagram.h"

/**
 * name: Action
 * brief: 构造函数。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 *        start_time - 输入的起始时间。
 *        complete_time - 输入的结束时间。
 * return: --
 */
Action::Action(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:_id(id)
	,_sub_id(sub_id)
	,_start_time(start_time)
	,_complete_time(complete_time)
	,_state(STATE_WAIT)
	,_status(STATUS_DISABLED)
	,_error(ERROR_NONE)
	,_defeats(0)
	,_test_item_key(0){
}

/**
 * name: ~Action
 * brief: 析构函数。
 * param: --
 * return: --
 */
Action::~Action(void){
}

/**
 * name: generate_key
 * brief: 根据指定的动作标识、子标识生成动作键。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 * return: 返回生成的动作键。
 */
unsigned int Action::generate_key(
	const unsigned int id,const unsigned int sub_id){
	return(id*1000+sub_id);
}

/**
 * name: get_id
 * brief: 获取当前动作标识。
 * param: --
 * return: 返回当前动作的动作标识。
 */
unsigned int Action::get_id() const{
	return(_id);
}

/**
 * name: get_sub_id
 * breif: 获取当前动作子标识。
 * param: --
 * return: 返回当前动作子标识。
 */
unsigned int Action::get_sub_id() const{
	return(_sub_id);
}

/**
 * name: get_key
 * brief: 获取当前动作的主键。
 * param: --
 * return: 返回当前动作的主键。
 */
unsigned int Action::get_key() const{
	return(generate_key(_id,_sub_id));
}

/**
 * name: get_start_time
 * brief: 获取当前动作的起始时间。
 * param: --
 * return: 返回当前动作的起始时间。
 */
unsigned int Action::get_start_time() const{
	return(_start_time);
}

/**
 * name: get_complete_time
 * brief: 获取当前动作的完成时间。
 * param: --
 * return: 返回当前动作的完成时间。
 */
unsigned int Action::get_complete_time() const{
	return(_complete_time);
}

/**
 * name: set_state
 * brief: 设置当前动作状态。
 * param: state - 输入的当前动作状态。
 * return: --
 */
void Action::set_state(const State state){
	_state=state;
}

/**
 * name: get_state
 * breif: 获取当前动作状态。
 * param: --
 * return: 返回当前动作状态。
 */
Action::State Action::get_state() const{
	return(_state);
}

/**
 * name: set_status
 * brief: 设置当前动作的状态。
 * param: status - 输入的当前动作状态。
 * return: --
 */
void Action::set_status(const Status status){
	_status=status;
}

/**
 * name: get_status
 * breif: 获取当前动作的状态。
 * param: --
 * return: 返回当前动作的状态。
 */
Action::Status Action::get_status() const{
	return(_status);
}

/**
 * name: set_error
 * brief: 设置当前错误。
 * param: error - 输入的错误信息。
 * return: --
 */
void Action::set_error(const Error error){
	_error=error;
}

/**
 * name: get_error
 * brief: 获取当前错误。
 * param: --
 * return: 返回当前错误。
 */
Action::Error Action::get_error() const{
	return(_error);
}

/**
 * name: increase_defeats
 * brief: 增加失败计数。
 * param: --
 * return: --
 */
void Action::increase_defeats(){
	++_defeats;
}

/**
 * name: get_defeats
 * brief: 获取当前动作的失败计数。
 * param: --
 * return: 返回当前动作的失败计数。
 */
unsigned int Action::get_defeats() const{
	return(_defeats);
}

/**
 * name: set_test_item_key
 * brief: 设置测试项目主键。
 * param: test_item_key - 输入的测试项目主键。
 * return: --
 */
void Action::set_test_item_key(const unsigned int &test_item_key){
	_test_item_key=test_item_key;
}

/**
 * name: get_test_item_key
 * breif: 获取测试项目主键。
 * param: --
 * return: 返回测试项目主键。
 */
unsigned int Action::get_test_item_key() const{
	return(_test_item_key);
}

/**
 * name: trigger
 * breif: 动作触发器，用来触发当前动作的执行。
 * param: time - 输入的当前时间。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Action::trigger(const unsigned int time){
	//1.清除当前动作的错误信息。
	_error=ERROR_NONE;
	//2.检测当前动作是否合法。
	if(is_valid()<0){
		_error=ERROR_NOT_VALID;//设置错误编码。
		return(-1);
	}
	//3.如果当前动作处于空状态，则直接返回。
	if(STATUS_DISABLED==_status){
		return(0);
	}
	//4.如果当前动作处于有效、或默认状态，则进行动作的触发操作。
	else if((STATUS_ENABLED==_status)||(STATUS_DEFAULT==_status)){
		//4-1.如果当前动作尚未执行。
		if(STATE_WAIT==_state){
			//4-1-1.如果当前动作尚未抵达动作起始时间。
			if(time<_start_time){
				return(0);
			}
			//4-1-2.如果当前动作已经抵达动作的起始时间。
			else if(time==_start_time){
				//a.执行当前动作，并且记录执行结果。
				const int execute_result=execute(_status);
				//b.如果执行当前动作失败，但希望修改动作状态。
				if(execute_result>0){
					_state=STATE_RUN;
					return(-2);
				}
				//c.如果执行当前动作成功。
				else if(0==execute_result){
					_state=STATE_RUN;//设置当前动作运行状态。
					return(0);
				}
				//c.如果执行当前动作失败，也不希望修改动作状态。
				else{
					//动作的错误信息已经在execute函数中设置。
					return(-3);
				}
			}
			//4-1-3.如果当前动作已经超时。
			else{
				_error=ERROR_UNKNOWN;//设置当前动作的错误信息。
				return(-4);
			}
		}
		//4-2.如果当前动作处于正在执行状态。
		else if(STATE_RUN==_state){
			//4-2-1.如果当前动作尚未抵达动作结束时间。
			if(time<_complete_time){
				return(0);
			}
			//4-2-2.如果当前动作已经抵达动作的结束时间。
			else if(time==_complete_time){
				//a.完成当前动作，并且记录完成结果。
				const int complete_result=complete(_status);
				//b.如果动作完成失败，但期望修改动作状态。
				if(complete_result>0){
					_state=STATE_COMPLETE;
					return(-5);
				}
				//c.如果动作成功完成。
				else if(0==complete_result){
					_state=STATE_COMPLETE;//设置当前动作运行状态。
					return(0);
				}
				//b.如果动作完成失败，也不希望修改动作状态。
				else{
					//动作的错误信息已经在complete函数中设置。
					return(-6);
				}
			}
			//4-2-3.如果当前动作已经超时。
			else{
				_error=ERROR_UNKNOWN;//设置当前动作的错误信息。
				return(-7);
			}
		}
		//4-3.如果当前动作已经执行完毕。
		else if(STATE_COMPLETE==_state){
			return(0);
		}
		//4-4.如果当前动作状态未知。
		else{
			_error=ERROR_UNKNOWN;//设置当前动作的错误信息。
			return(-8);
		}
	}
	//6.如果当前动作处于未知状态，则直接返回错误。
	else{
		_error=ERROR_UNKNOWN;//设置当前动作的错误信息。
		return(-9);
	}
}

/**
 * name: clear
 * breif: 清除当前动作。
 * param: --
 * return: 如果不需要执行清除操作，则返回大于零的数。
 *         如果清除成功返回零。
 *         如果清除失败则返回小于零的数。
 */
int Action::clear(){
	//1.检测当前动作是否合法。
	if(is_valid()<0){
		return(-1);//清除失败。
	}
	//2.如果当前动作处于空或默认状态，则不对当前动作进行清除操作。
	if((STATUS_DISABLED==_status)||(STATUS_DEFAULT==_status)){
		return(1);//忽略清除操作。
	}
	//3.如果当前动作处于有效状态，则对动作进行清除操作。
	else if(STATUS_ENABLED==_status){
		//3-1.如果当前动作已经执行或已经执行完成，则不需要进行清除。
		if((STATE_RUN==_state)||(STATE_COMPLETE==_state)){
			//remark: 已经执行的动作，必须检测动作是否完成，所以不能
			//        执行清除操作。
			//        已经执行完成的动作，就没有必要再清除了。
			return(1);//忽略清除操作。
		}
		//3-2.如果当前动作处于尚未执行状态，则进行清除操作。
		else if(STATE_WAIT==_state){
			//3-2-1.清除当前动作状态。
			_state=STATE_WAIT;
			//3-2-2.清除当前动作所处状态。
			//a.如果当前动作是反应盘旋转或磁珠盘旋转动作。
			if((SequenceDiagram::
				ACTION_ID_REACTION_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_WASHING_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_WASHING_DISC_WASH==_id)){
				_status=STATUS_DEFAULT;
			}
			//b.如果当前动作是其它动作。
			else{
				_status=STATUS_DISABLED;
			}
			//3-2-3.清除错误信息。
			_error=ERROR_NONE;
			//3-2-4.清除失败次数。
			_defeats=0;
			//3-2-5.清除项目主键。
			_test_item_key=0;
			//3-2-6.程序运行到此直接成功返回。
			return(0);//清除成功。
		}
		//3-3.如果当前动作处于其它状态，则直接返回错误。
		else{
			return(-2);//清除失败。
		}
	}
	//4.如果当前动作处于其它状态，则直接返回错误。
	else{
		return(-3);//清除失败。
	}
}

/**
 * name: reset
 * breif: 重置当前动作。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Action::reset(){
	//1.检测当前动作是否合法。
	if(is_valid()<0){
		return(-1);
	}
	//2.重置当前动作状态。
	_state=STATE_WAIT;
	//3.重置当前动作所处状态。
	//3-1.如果当前动作为“反应盘旋转”或“磁珠盘旋转”动作。
	if((SequenceDiagram::
		ACTION_ID_REACTION_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_WASHING_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_WASHING_DISC_WASH==_id)){
		_status=STATUS_DEFAULT;
	}
	//3-2.如果当前动作为其它动作。
	else{
		_status=STATUS_DISABLED;
	}
	//3-3.重置错误信息。
	_error=ERROR_NONE;
	//3-4.重置失败次数。
	_defeats=0;
	//3-5.重置测试项目主键。
	_test_item_key=0;
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前动作是否合法。
 * param: --
 * return: 如果当前动作合法返回值大于等于零，否则返回值小于零。
 */
int Action::is_valid() const{
	//1.检测当前动作标识是否合法。
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.检测当前动作子标识是否合法。
	if((_sub_id<1)||(_sub_id>999)){
		return(-2);
	}
	//3.检测当前动作的起始时间是否合法。
	if((_start_time<0)||(_start_time>30000)){
		return(-3);
	}
	//4.检测当前动作的结束时间是否合法。
	if((_complete_time<0)||(_complete_time>30000)){
		return(-4);
	}
	//5.检测当前动作的起始、结束时间的相互关系是否合法。
	if(_start_time>_complete_time){
		return(-5);
	}
	//6.检测当前动作的状态是否合法。
	if((STATE_WAIT!=_state)&&(STATE_RUN!=_state)&&(
		STATE_COMPLETE!=_state)){
		return(-6);
	}
	//7.检测当前动作的状态是否合法。
	if((STATUS_DISABLED!=_status)&&(STATUS_ENABLED!=_status)&&(
		STATUS_DEFAULT!=_status)){
		return(-7);
	}
	//8.检测当前动作的错误编号是否合法。
	if((ERROR_NONE!=_error)&&(
		ERROR_UNKNOWN!=_error)&&(
		ERROR_NOT_VALID!=_error)&&(
		ERROR_SERIOUS_TIMEOUT!=_error)&&(
		ERROR_TIMEOUT_T!=_error)&&(
		ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE!=_error)&&(
		ERROR_COMMUNICATION!=_error)&&(
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT!=_error)&&(
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED!=_error)){
		return(-8);
	}
	//9.检测当前动作的错误次数是否合法。
	if(_defeats<0){
		return(-9);
	}
	//10.检测当前项目主键是否合法。
	if(STATUS_ENABLED==_status){
		if(0==_test_item_key){
			return(-10);
		}
	}
	//11.程序运行到此成功返回。
	return(0);
}

/**
 * name: execute
 * breif: 执行当前动作。
 * param: status - 输入的当前动作状态。
 * return: 如果函数执行成功返回值等于零，否则返回值不等于零（
 *         如果返回值大于零说明期望更改当前动作状态，如果返回
 *         值小于零说明不期望更改当前动作状态。）。
 */
int Action::execute(const Status /*status*/){
	//1.检测当前动作是否合法。
	if(is_valid()<0){
		//1-1.设置当前错误编码为无效错误。
		_error=ERROR_NOT_VALID;
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.程序运行到此成功返回。
	else{
		return(0);
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
int Action::complete(const Status /*status*/){
	//1.检测当前动作是否合法。
	if(is_valid()<0){
		//1-1.设置当前错误编码为无效错误。
		_error=ERROR_NOT_VALID;
		//1-2.程序运行到此直接返回错误。
		return(-1);
	}
	//2.程序运行到此成功返回。
	else{
		return(0);
	}
}