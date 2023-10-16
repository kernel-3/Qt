#include"stdafx.h"
#include"SequenceDiagram.h"
#include"ReactionDiscRotation.h"
#include"TakeTubeOutOfTubeStoreHouse.h"
#include"PutTubeInReactionDisc.h"
#include"SpecimenDiscRotation.h"
#include"SpecimenArmSuck.h"
#include"SpecimenArmSpit.h"
#include"SpecimenArmWash.h"
#include"ReagentDiscRotation.h"
#include"MagneticBeadDiscRotation.h"
#include"ReagentArmSuck.h"
#include"ReagentArmSpit.h"
#include"ReagentArmWash.h"
#include"WashingDiscRotation.h"
#include"DetectionDiscRotation.h"
#include"TakeTubeOutOfDetectionDisc.h"
#include"DiscardTube.h"
#include"WashingDiscWash.h"
#include"TakeTubeOutOfWashingDisc.h"
#include"ReturnTubeToReactionDisc.h"
#include"PutTubeInDetectionDisc.h"
#include"TakeTubeOutOfReactionDisc.h"
#include"PutTubeInWashingDisc.h"
#include"Detect.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../component/DetectionDisc.h"

/**
 * name: binary_search_action
 * brief: 二分查找动作。
 * param: actions - 输入的指向动作存储数组的指针。
 *        actions_size - 输入的动作存储数组尺寸。
 *        lower - 输入的动作存储数组查找下界。
 *        upper - 输入的动作存储数组查找上界。
 *        action_id - 输入的指定动作标识。
 *        action_sub_id - 输入的指定动作子标识。
 * return: 如果查找成功返回指向查找动作的智能指针，否则返回空指针。
 */
static SequenceDiagram::PtrToAction binary_search_action(
	SequenceDiagram::PtrToAction *actions,const unsigned int actions_size,
	const unsigned int lower,const unsigned int upper,
	const SequenceDiagram::ActionID action_id,const unsigned int action_sub_id){
	//1.检测当前输入参数是否合法。
	if((0==actions)||(0==actions_size)||(lower>=actions_size)||(
		upper>=actions_size)||(lower>upper)||(0==action_sub_id)){
		return(SequenceDiagram::PtrToAction());
	}
	//2.计算用户期望查找的动作标识。
	const unsigned int action_key=Action::generate_key(action_id,action_sub_id);
	//3.循环开始二分查找指定的动作。
	unsigned int lower_t=lower;
	unsigned int upper_t=upper;
	while(lower_t<=upper_t){
		//3-1.计算二分查找的中点。
		const unsigned int mid=(lower_t+upper_t)/2;
		//3-2.如果成功找到则直接返回。
		if(action_key==actions[mid]->get_key()){
			return(actions[mid]);
		}
		//3-3.如果中点的动作主键小于查找的动作主键。
		else if(actions[mid]->get_key()<action_key){
			lower_t=mid+1;
		}
		//3-4.如果中点的动作主键大于查找的动作主键。
		else{
			upper_t=mid-1;
		}
	}
	//4.程序运行到此直接返回空指针。
	return(SequenceDiagram::PtrToAction());
}

/**
 * name: SequenceDiagram
 * brief: 构造函数。
 * param: --
 * return: --
 */
SequenceDiagram::SequenceDiagram(void)
	:_actions(){
	init();
}

/**
 * name: ~SequenceDiagram
 * breif: 析构函数。
 * param: --
 * return: --
 */
SequenceDiagram::~SequenceDiagram(void){
}

/**
 * name: trigger
 * brief: 触发当前时序图。
 * param: trigger_time - 输入的触发时间。
 *        trigger_error - 输出的触发错误。
 *        test_item_key - 输出的测试项目主键。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SequenceDiagram::trigger(const unsigned int trigger_time,
	unsigned int &trigger_error,unsigned int &test_item_key){
	//1.定义。
	typedef std::vector<Actions::iterator> ActionIterators;
	//2.声明当前操作所需变量。
	ActionIterators running_actions;
	ActionIterators watting_actions;
	//3.遍历当前时序图，挑选正在运行的动作以及正在等待的动作。
	for(Actions::iterator iterator=_actions.begin();
		iterator!=_actions.end();++iterator){
		//3-1.如果当前动作不存在，则直接返回错误。
		if(!static_cast<bool>(*iterator)){
			//3-1-1.设置错误标记。
			trigger_error=Action::ERROR_UNKNOWN;
			//3-1-2.设置项目主键。
			test_item_key=0;
			//3-1-3.程序运行到此直接返回错误。
			return(-1);
		}
		//3-2.如果当前动作处于无效状态，则继续下次循环。
		if(Action::STATUS_DISABLED==(*iterator)->get_status()){
			continue;
		}
		//3-3.如果当前动作处于默认或有效状态。
		else{
			//3-3-1.如果当前动作正在执行。
			if(Action::STATE_RUN==(*iterator)->get_state()){
				running_actions.push_back(iterator);
			}
			//3-3-2.如果当前动作正在等待执行。
			else if(Action::STATE_WAIT==(*iterator)->get_state()){
				watting_actions.push_back(iterator);
			}
			//3-3-3.如果当前动作执行完成。
			else{
				continue;
			}
		}
	}
	//4.首先对已经执行的动作进行触发。
	for(ActionIterators::iterator iterator=running_actions.begin();
		iterator!=running_actions.end();++iterator){
		if((*(*iterator))->trigger(trigger_time)<0){
			trigger_error=(*(*iterator))->get_error();
			test_item_key=(*(*iterator))->get_test_item_key();
			return(-2);
		}
	}
	//5.然后对尚未执行的动作进行触发。
	for(ActionIterators::iterator iterator=watting_actions.begin();
		iterator!=watting_actions.end();++iterator){
		if((*(*iterator))->trigger(trigger_time)<0){
			trigger_error=(*(*iterator))->get_error();
			test_item_key=(*(*iterator))->get_test_item_key();
			return(-3);
		}
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: clear
 * breif: 清楚当前时序中指定测试项目的动作。
 * param: test_item_key - 输入的测试项目主键。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SequenceDiagram::clear(const unsigned int test_item_key){
	//1.检测当前输入参数是否合法。
	if(0==test_item_key){
		return(-1);
	}
	//2.遍历当前时序中的全部动作，对符合条件的动作进行清除。
	for(Actions::iterator iterator=_actions.begin();iterator!=
		_actions.end();++iterator){
		//2-1.如果当前动作不存在。
		if(!static_cast<bool>(*iterator)){
			return(-2);
		}
		//2-2.如果当前动作处于有效状态，并且项目主键与输入的主键相同，则进行动作清除操作。
		if((Action::STATUS_ENABLED==(*iterator)->get_status())&&(
			test_item_key==(*iterator)->get_test_item_key())){
			if((*iterator)->clear()<0){
				return(-3);
			}
		}
	}
	//3.程序运行到此，成功返回。
	return(0);
}

/**
 * name: reset
 * brief: 重置当前时序图中的动作信息。
 * param: --
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SequenceDiagram::reset(){
	//1.遍历动作映射，重置所有的动作。
	for(Actions::iterator iterator=_actions.begin();
		iterator!=_actions.end();++iterator){
		//1-1.如果当前动作不存在。
		if(!static_cast<bool>(*iterator)){
			return(-1);
		}
		//1-2.重置当前动作，并且判断清除是否成功。
		if((*iterator)->reset()<0){
			return(-2);
		}
	}
	//2.程序运行到此，成功返回。
	return(0);
}

/**
 * name: get_action
 * brief: 获取当前时序图中指定的动作。
 * param: id - 输入的动作标识。
 *        sub_id - 输入的动作子标识。
 * return: 如果当前函数获取动作成功，返回指向相应动作的智能指针，
 *         否则返回空指针。
 */
SequenceDiagram::PtrToAction SequenceDiagram::get_action(
	const ActionID id,const unsigned int sub_id){
	//1.如果当前动作存储数组为空，则直接返回空指针。
	if(_actions.empty()){
		return(PtrToAction());
	}
	//2.利用二分查找，查找指定的动作，并且返回查找结果。
	return(binary_search_action(_actions.data(),
		_actions.size(),0,_actions.size()-1,id,sub_id));
}

/**
 * name: init
 * breif: 初始化当前时序图。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int SequenceDiagram::init(){
	//1.声明当前操作所需变量。
	Actions actions;
	//2.创建反应盘旋转动作。
	//2-1.声明当前操作所需变量。
	const unsigned int reaction_disc_rotation_count=7;
	const unsigned int reaction_disc_rotation_start_times[
		reaction_disc_rotation_count]={3000,7000,13000,17000,
		20000,23000,27000};
	const unsigned int reaction_disc_rotation_complete_times[
		reaction_disc_rotation_count]={4000,8000,14000,18000,
		21000,24000,28000};
	//2-2.循环创建反应盘旋转动作，并将其存储到当前时序图中。
	for(unsigned int index=0;index!=
		reaction_disc_rotation_count;++index){
		//2-2-1.创建反应盘旋转动作，并且判断创建是否成功。
		PtrToAction action(new ReactionDiscRotation(
			ACTION_ID_REACTION_DISC_ROTATION,index+1,
			reaction_disc_rotation_start_times[index],
			reaction_disc_rotation_complete_times[index]));
		if(!static_cast<bool>(action)){
			return(-1);
		}
		//2-2-2.设置反应盘旋转动作相关数据。
		action->set_status(Action::STATUS_DEFAULT);
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((ReactionDiscRotation*)(action.get()))->set_hole_no(1);
		//((ReactionDiscRotation*)(action.get()))->set_position(1);
		//2-2-3.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-2);
		}
		//2-2-4.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//3.创建放管到反应盘动作。
	//3-1.创建放管到反应盘动作，并且判断创建是否成功。
	PtrToAction action(new PutTubeInReactionDisc(
		ACTION_ID_PUT_TUBE_IN_REACTION_DISC,1,28000,30000));
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//3-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-4);
	}
	//3-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//4.创建从试管仓取管动作。
	//4-1.创建从试管仓取管动作，并且判断创建是否成功。
	action.reset(new TakeTubeOutOfTubeStoreHouse(
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,
		1,23000,28000));
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//4-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-6);
	}
	//4-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//5.创建样本臂吐液动作。
	//5-1.创建样本臂吐液动作，并且判断创建是否成功。
	action.reset(new SpecimenArmSpit(
		ACTION_ID_SPECIMEN_ARM_SPIT,1,8000,11000));
	if(!static_cast<bool>(action)){
		return(-7);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//((SpecimenArmSpit*)(action.get()))->set_spit_volume(50);
	//((SpecimenArmSpit*)(action.get()))->set_down_steps(5000);
	//5-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-8);
	}
	//5-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//6.创建样本臂吸液动作。
	//6-1.创建样本臂吸液动作，并且判断创建是否成功。
	action.reset(new SpecimenArmSuck(
		ACTION_ID_SPECIMEN_ARM_SUCK,1,2000,8000));
	if(!static_cast<bool>(action)){
		return(-9);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//((SpecimenArmSuck*)(action.get()))->set_suck_volume(50);
	//((SpecimenArmSuck*)(action.get()))->set_cup_type(0);
	//6-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-10);
	}
	//6-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//7.创建样本臂清洗动作。
	//7-1.创建样本臂清洗动作，并且判断创建是否成功。
	action.reset(new SpecimenArmWash(
		ACTION_ID_SPECIMEN_ARM_WASH,1,11000,15000));
	if(!static_cast<bool>(action)){
		return(-11);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//7-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-12);
	}
	//7-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//8.创建样本盘旋转动作。
	//8-1.创建样本盘旋转动作，并且判断创建是否成功。
	action.reset(new SpecimenDiscRotation(
		ACTION_ID_SPECIMEN_DISC_ROTATION,1,0,2000));
	if(!static_cast<bool>(action)){
		return(-13);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//((SpecimenDiscRotation*)(action.get()))->set_rack_no(1);
	//((SpecimenDiscRotation*)(action.get()))->set_position_no(1);
	//8-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-14);
	}
	//8-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//9.创建试剂臂吐液动作。
	//9-1.声明当前操作所需变量。
	const unsigned int spit_reagent_action_count=3;
	const unsigned int spit_reagent_start_times[
		spit_reagent_action_count]={4000,14000,24000};
	const unsigned int spit_reagent_finish_times[
		spit_reagent_action_count]={7000,17000,27000};
	//9-2.循环创建加试剂动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=spit_reagent_action_count;++index){
		//9-2-1.创建试剂臂吐液动作，并且判断创建是否成功。
		action.reset(new ReagentArmSpit(
			ACTION_ID_REAGENT_ARM_SPIT,
			index+1,spit_reagent_start_times[index],
			spit_reagent_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-15);
		}
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((ReagentArmSpit*)(action.get()))->set_spit_volume(50);
		//((ReagentArmSpit*)(action.get()))->set_down_steps(1000);
		//9-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-16);
		}
		//9-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//10.创建试剂臂吸液动作。
	//10-1.声明当前操作所需变量。
	const unsigned int suck_reagent_action_count=3;
	const unsigned int suck_reagent_start_times[
		suck_reagent_action_count]={0,10000,20000};
	const unsigned int suck_reagent_finish_times[
		suck_reagent_action_count]={4000,14000,24000};
	//10-2.循环创建试剂臂吸液动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=suck_reagent_action_count;++index){
		//10-2-1.创建试剂臂吸液动作，并且判断创建是否成功。
		action.reset(new ReagentArmSuck(
			ACTION_ID_REAGENT_ARM_SUCK,index+1,
			suck_reagent_start_times[index],
			suck_reagent_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-17);
		}
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((ReagentArmSuck*)(action.get()))->set_suck_volume(50);
		//((ReagentArmSuck*)(action.get()))->set_reagent_type(0);
		//10-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-18);
		}
		//10-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//11.创建试剂臂清洗动作。
	//11-1.声明当前操作所需变量。
	const unsigned int wash_reagent_action_count=3;
	const unsigned int wash_reagent_start_times[
		wash_reagent_action_count]={7000,17000,27000};
	const unsigned int wash_reagent_finish_times[
		wash_reagent_action_count]={10000,20000,30000};
	//11-2.循环创建试剂臂清洗动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=wash_reagent_action_count;++index){
		//11-2-1.创建洗试剂动作，并且判断创建是否成功。
		action.reset(new ReagentArmWash(
			ACTION_ID_REAGENT_ARM_WASH,index+1,
			wash_reagent_start_times[index],
			wash_reagent_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-19);
		}
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//11-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-20);
		}
		//11-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//12.创建试剂盘旋转动作。
	//12-1.声明当前操作所需变量。
	const unsigned int reagent_disc_rotation_action_count=2;
	const unsigned int reagent_disc_rotation_start_times[
		reagent_disc_rotation_action_count]={8000,28000};
	const unsigned int reagent_disc_rotation_finish_times[
		reagent_disc_rotation_action_count]={10000,30000};
	//12-2.循环创建试剂盘旋转动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=
		reagent_disc_rotation_action_count;++index){
		//12-2-1.创建试剂盘旋转动作，并且判断创建是否成功。
		action.reset(new ReagentDiscRotation(
			ACTION_ID_REAGENT_DISC_ROTATION,index+1,
			reagent_disc_rotation_start_times[index],
			reagent_disc_rotation_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-21);
		}
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((ReagentDiscRotation*)(action.get()))->set_reagent_type(0);
		//((ReagentDiscRotation*)(action.get()))->set_position_no(1);
		//12-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-22);
		}
		//12-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//13.创建磁珠盘转动动作。
	//13-1.声明当前操作所需变量。
	const unsigned int magnetic_beads_disc_rotation_action_count=12;
	const unsigned int magnetic_beads_disc_rotation_start_times[
		magnetic_beads_disc_rotation_action_count]={1000,3000,5000,
		7000,9000,11000,13000,15000,17000,25000,27000,29000};
	const unsigned int magnetic_beads_disc_rotation_finish_times[
		magnetic_beads_disc_rotation_action_count]={2000,4000,6000,
		8000,10000,12000,14000,16000,20000,26000,28000,30000};
	//13-2.循环创建磁珠盘旋转动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=
		magnetic_beads_disc_rotation_action_count;++index){
		//13-2-1.创建磁珠盘旋转动作，并且判断创建是否成功。
		action.reset(new MagneticBeadDiscRotation(
			ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,index+1,
			magnetic_beads_disc_rotation_start_times[index],
			magnetic_beads_disc_rotation_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-23);
		}
		//13-2-2.设置当前磁珠盘旋转动作的动作状态。
		//debug.
		//if(8==index){
			//action->set_status(Action::STATUS_ENABLED);
			//action->set_test_item_key(1);
			//((MagneticBeadDiscRotation*)(action.get()))->set_position_no(1);
		//}else{
		action->set_status(Action::STATUS_DEFAULT);
		//}
		//13-2-3.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-24);
		}
		//13-2-4.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//14.创建转运抓手从反应盘取管动作。
	//14-1.创建转运抓手从反应盘取管动作，并且判断创建是否成功。
	action.reset(new TakeTubeOutOfReactionDisc(
		ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,
		1,21000,23000));
	if(!static_cast<bool>(action)){
		return(-25);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//14-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-26);
	}
	//14-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//15.创建回管到反应盘动作。
	//15-1.创建回管到反应盘动作，并且判断创建是否成功。
	action.reset(new ReturnTubeToReactionDisc(
		ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,1,18000,20000));
	if(!static_cast<bool>(action)){
		return(-27);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//15-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-28);
	}
	//15-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//16.创建清洗盘取管动作。
	//16-1.创建清洗盘取管动作，并且判断创建是否成功。
	action.reset(new TakeTubeOutOfWashingDisc(
		ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1,14000,18000));
	if(!static_cast<bool>(action)){
		return(-29);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//((TakeTubeOutOfWashingDisc*)(action.get()))->set_stop_position(0);
	//16-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-30);
	}
	//16-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//17.创建转运抓手放管到清洗盘动作。
	//17-1.创建转运抓手放管到清洗盘动作，并且判断创建是否成功。
	action.reset(new PutTubeInWashingDisc(
		ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,
		1,23000,27000));
	if(!static_cast<bool>(action)){
		return(-31);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//17-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-32);
	}
	//17-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//18.创建转运抓手放管到检测盘动作。
	//18-1.创建转运抓手放管到检测盘动作，并且判断创建是否成功。
	action.reset(new PutTubeInDetectionDisc(
		ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,1,18000,21000));
	if(!static_cast<bool>(action)){
		return(-33);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//18-2.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-34);
	}
	//18-3.将当前动作存储到时序图中。
	actions.push_back(action);
	//19.创建转运抓手从检测盘取管动作。
	//19-1.声明当前操作所需变量。
	const unsigned int discarding_tube_fetch_action_count=2;
	const unsigned int discarding_tube_fetch_start_times[
		discarding_tube_fetch_action_count]={0,7000};
	const unsigned int discarding_tube_fetch_finish_times[
		discarding_tube_fetch_action_count]={3000,10000};
	//19-2.循环创建转运抓手从检测盘时取管动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=discarding_tube_fetch_action_count;++index){
		//19-2-1.创建转运抓手从检测盘取管动作，并且判断创建是否成功。
		action.reset(new TakeTubeOutOfDetectionDisc(
			ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,index+1,
			discarding_tube_fetch_start_times[index],
			discarding_tube_fetch_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-35);
		}
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//19-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-36);
		}
		//19-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//20.创建转运抓手丢管动作。
	//20-1.声明当前操作所需变量。
	const unsigned int discarding_tube_place_action_count=2;
	const unsigned int discarding_tube_place_start_times[
		discarding_tube_place_action_count]={3000,10000};
	const unsigned int discarding_tube_place_finish_times[
		discarding_tube_place_action_count]={7000,14000};
	//20-2.循环创建扔管时放管动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=discarding_tube_place_action_count;++index){
		//20-2-1.创建转运抓手丢管动作，并且判断创建是否成功。
		action.reset(new DiscardTube(ACTION_ID_DISCARD_TUBE,index+1,
			discarding_tube_place_start_times[index],
			discarding_tube_place_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-37);
		}
		//.debug
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//20-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-38);
		}
		//20-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//21.创建清洗盘清洗动作。
	//21-1.创建清洗盘清洗动作，并且判断创建是否成功。
	action.reset(new WashingDiscWash(
		ACTION_ID_WASHING_DISC_WASH,1,3000,23000));
	if(!static_cast<bool>(action)){
		return(-39);
	}
	//21-2.设置当前清洗盘清洗动作状态。
	action->set_status(WashingDiscWash::STATUS_DEFAULT);
	//21-3.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-40);
	}
	//21-4.将当前动作存储到时序图中。
	actions.push_back(action);
	//22.创建清洗盘旋转动作。
	//22-1.创建请洗盘旋转动作，并且判断创建是否成功。
	action.reset(new WashingDiscRotation(
		ACTION_ID_WASHING_DISC_ROTATION,1,0,1000));
	if(!static_cast<bool>(action)){
		return(-41);
	}
	//.debug
	//(((Instrument::instance())->get_components())->
		//get_washing_disc())->set_hole_state(
		//WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_USED);
	//22-2.设置当前动作状态。
	action->set_status(Action::STATUS_DEFAULT);
	//22-3.检测当前动作是否合法。
	if(action->is_valid()<0){
		return(-42);
	}
	//22-4.将当前动作存储到时序图中。
	actions.push_back(action);
	//23.创建检测盘旋转动作。
	//23-1.声明当前操作所需变量。
	const unsigned int detection_disc_rotation_action_count=5;
	const unsigned int detection_disc_rotation_start_times[
		detection_disc_rotation_action_count]={6000,13000,17000,23000,29000};
	const unsigned int detection_disc_rotation_finish_times[
		detection_disc_rotation_action_count]={7000,14000,18000,24000,30000};
	//23-2.循环创建检测盘旋转动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=detection_disc_rotation_action_count;++index){
		//23-2-1.创建检测盘旋转动作，并且判断创建是否成功。
		action.reset(new DetectionDiscRotation(
			ACTION_ID_DETECTION_DISC_ROTATION,index+1,
			detection_disc_rotation_start_times[index],
			detection_disc_rotation_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-43);
		}
		//.debug
		//(((Instrument::instance())->get_components())->
		//	get_detection_disc())->set_hole_state(1,DetectionDisc::HOLE_STATE_USED);
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((DetectionDiscRotation*)(action.get()))->set_position(
			//static_cast<unsigned int>(DetectionDisc::POSITION_ENTRY));
		//23-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-44);
		}
		//23-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//24.创建检测动作。
	//24-1.声明当前操作所需变量。
	const unsigned int detect_action_count=2;
	const unsigned int detect_start_times[
		detect_action_count]={14000,24000};
	const unsigned int detect_finish_times[
		detect_action_count]={17000,27000};
	//24-2.循环创建检测动作，并将其存储到时序图中。
	for(unsigned int index=0;index!=detect_action_count;++index){
		//24-2-1.创建检测动作，并且判断创建是否成功。
		action.reset(new Detect(ACTION_ID_DETECT,index+1,
			detect_start_times[index],detect_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-45);
		}
		//debug
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//24-2-2.检测当前动作是否合法。
		if(action->is_valid()<0){
			return(-46);
		}
		//24-2-3.将当前动作存储到时序图中。
		actions.push_back(action);
	}
	//25.保存当前时序图数据。
	_actions.swap(actions);
	//26.程序运行到此成功返回。
	return(0);
}