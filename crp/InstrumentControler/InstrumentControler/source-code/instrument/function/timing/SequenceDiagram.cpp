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
 * brief: ���ֲ��Ҷ�����
 * param: actions - �����ָ�����洢�����ָ�롣
 *        actions_size - ����Ķ����洢����ߴ硣
 *        lower - ����Ķ����洢��������½硣
 *        upper - ����Ķ����洢��������Ͻ硣
 *        action_id - �����ָ��������ʶ��
 *        action_sub_id - �����ָ�������ӱ�ʶ��
 * return: ������ҳɹ�����ָ����Ҷ���������ָ�룬���򷵻ؿ�ָ�롣
 */
static SequenceDiagram::PtrToAction binary_search_action(
	SequenceDiagram::PtrToAction *actions,const unsigned int actions_size,
	const unsigned int lower,const unsigned int upper,
	const SequenceDiagram::ActionID action_id,const unsigned int action_sub_id){
	//1.��⵱ǰ��������Ƿ�Ϸ���
	if((0==actions)||(0==actions_size)||(lower>=actions_size)||(
		upper>=actions_size)||(lower>upper)||(0==action_sub_id)){
		return(SequenceDiagram::PtrToAction());
	}
	//2.�����û��������ҵĶ�����ʶ��
	const unsigned int action_key=Action::generate_key(action_id,action_sub_id);
	//3.ѭ����ʼ���ֲ���ָ���Ķ�����
	unsigned int lower_t=lower;
	unsigned int upper_t=upper;
	while(lower_t<=upper_t){
		//3-1.������ֲ��ҵ��е㡣
		const unsigned int mid=(lower_t+upper_t)/2;
		//3-2.����ɹ��ҵ���ֱ�ӷ��ء�
		if(action_key==actions[mid]->get_key()){
			return(actions[mid]);
		}
		//3-3.����е�Ķ�������С�ڲ��ҵĶ���������
		else if(actions[mid]->get_key()<action_key){
			lower_t=mid+1;
		}
		//3-4.����е�Ķ����������ڲ��ҵĶ���������
		else{
			upper_t=mid-1;
		}
	}
	//4.�������е���ֱ�ӷ��ؿ�ָ�롣
	return(SequenceDiagram::PtrToAction());
}

/**
 * name: SequenceDiagram
 * brief: ���캯����
 * param: --
 * return: --
 */
SequenceDiagram::SequenceDiagram(void)
	:_actions(){
	init();
}

/**
 * name: ~SequenceDiagram
 * breif: ����������
 * param: --
 * return: --
 */
SequenceDiagram::~SequenceDiagram(void){
}

/**
 * name: trigger
 * brief: ������ǰʱ��ͼ��
 * param: trigger_time - ����Ĵ���ʱ�䡣
 *        trigger_error - ����Ĵ�������
 *        test_item_key - ����Ĳ�����Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SequenceDiagram::trigger(const unsigned int trigger_time,
	unsigned int &trigger_error,unsigned int &test_item_key){
	//1.���塣
	typedef std::vector<Actions::iterator> ActionIterators;
	//2.������ǰ�������������
	ActionIterators running_actions;
	ActionIterators watting_actions;
	//3.������ǰʱ��ͼ����ѡ�������еĶ����Լ����ڵȴ��Ķ�����
	for(Actions::iterator iterator=_actions.begin();
		iterator!=_actions.end();++iterator){
		//3-1.�����ǰ���������ڣ���ֱ�ӷ��ش���
		if(!static_cast<bool>(*iterator)){
			//3-1-1.���ô����ǡ�
			trigger_error=Action::ERROR_UNKNOWN;
			//3-1-2.������Ŀ������
			test_item_key=0;
			//3-1-3.�������е���ֱ�ӷ��ش���
			return(-1);
		}
		//3-2.�����ǰ����������Ч״̬��������´�ѭ����
		if(Action::STATUS_DISABLED==(*iterator)->get_status()){
			continue;
		}
		//3-3.�����ǰ��������Ĭ�ϻ���Ч״̬��
		else{
			//3-3-1.�����ǰ��������ִ�С�
			if(Action::STATE_RUN==(*iterator)->get_state()){
				running_actions.push_back(iterator);
			}
			//3-3-2.�����ǰ�������ڵȴ�ִ�С�
			else if(Action::STATE_WAIT==(*iterator)->get_state()){
				watting_actions.push_back(iterator);
			}
			//3-3-3.�����ǰ����ִ����ɡ�
			else{
				continue;
			}
		}
	}
	//4.���ȶ��Ѿ�ִ�еĶ������д�����
	for(ActionIterators::iterator iterator=running_actions.begin();
		iterator!=running_actions.end();++iterator){
		if((*(*iterator))->trigger(trigger_time)<0){
			trigger_error=(*(*iterator))->get_error();
			test_item_key=(*(*iterator))->get_test_item_key();
			return(-2);
		}
	}
	//5.Ȼ�����δִ�еĶ������д�����
	for(ActionIterators::iterator iterator=watting_actions.begin();
		iterator!=watting_actions.end();++iterator){
		if((*(*iterator))->trigger(trigger_time)<0){
			trigger_error=(*(*iterator))->get_error();
			test_item_key=(*(*iterator))->get_test_item_key();
			return(-3);
		}
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clear
 * breif: �����ǰʱ����ָ��������Ŀ�Ķ�����
 * param: test_item_key - ����Ĳ�����Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SequenceDiagram::clear(const unsigned int test_item_key){
	//1.��⵱ǰ��������Ƿ�Ϸ���
	if(0==test_item_key){
		return(-1);
	}
	//2.������ǰʱ���е�ȫ���������Է��������Ķ������������
	for(Actions::iterator iterator=_actions.begin();iterator!=
		_actions.end();++iterator){
		//2-1.�����ǰ���������ڡ�
		if(!static_cast<bool>(*iterator)){
			return(-2);
		}
		//2-2.�����ǰ����������Ч״̬��������Ŀ�����������������ͬ������ж������������
		if((Action::STATUS_ENABLED==(*iterator)->get_status())&&(
			test_item_key==(*iterator)->get_test_item_key())){
			if((*iterator)->clear()<0){
				return(-3);
			}
		}
	}
	//3.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: reset
 * brief: ���õ�ǰʱ��ͼ�еĶ�����Ϣ��
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SequenceDiagram::reset(){
	//1.��������ӳ�䣬�������еĶ�����
	for(Actions::iterator iterator=_actions.begin();
		iterator!=_actions.end();++iterator){
		//1-1.�����ǰ���������ڡ�
		if(!static_cast<bool>(*iterator)){
			return(-1);
		}
		//1-2.���õ�ǰ�����������ж�����Ƿ�ɹ���
		if((*iterator)->reset()<0){
			return(-2);
		}
	}
	//2.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: get_action
 * brief: ��ȡ��ǰʱ��ͼ��ָ���Ķ�����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 * return: �����ǰ������ȡ�����ɹ�������ָ����Ӧ����������ָ�룬
 *         ���򷵻ؿ�ָ�롣
 */
SequenceDiagram::PtrToAction SequenceDiagram::get_action(
	const ActionID id,const unsigned int sub_id){
	//1.�����ǰ�����洢����Ϊ�գ���ֱ�ӷ��ؿ�ָ�롣
	if(_actions.empty()){
		return(PtrToAction());
	}
	//2.���ö��ֲ��ң�����ָ���Ķ��������ҷ��ز��ҽ����
	return(binary_search_action(_actions.data(),
		_actions.size(),0,_actions.size()-1,id,sub_id));
}

/**
 * name: init
 * breif: ��ʼ����ǰʱ��ͼ��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SequenceDiagram::init(){
	//1.������ǰ�������������
	Actions actions;
	//2.������Ӧ����ת������
	//2-1.������ǰ�������������
	const unsigned int reaction_disc_rotation_count=7;
	const unsigned int reaction_disc_rotation_start_times[
		reaction_disc_rotation_count]={3000,7000,13000,17000,
		20000,23000,27000};
	const unsigned int reaction_disc_rotation_complete_times[
		reaction_disc_rotation_count]={4000,8000,14000,18000,
		21000,24000,28000};
	//2-2.ѭ��������Ӧ����ת������������洢����ǰʱ��ͼ�С�
	for(unsigned int index=0;index!=
		reaction_disc_rotation_count;++index){
		//2-2-1.������Ӧ����ת�����������жϴ����Ƿ�ɹ���
		PtrToAction action(new ReactionDiscRotation(
			ACTION_ID_REACTION_DISC_ROTATION,index+1,
			reaction_disc_rotation_start_times[index],
			reaction_disc_rotation_complete_times[index]));
		if(!static_cast<bool>(action)){
			return(-1);
		}
		//2-2-2.���÷�Ӧ����ת����������ݡ�
		action->set_status(Action::STATUS_DEFAULT);
		//debug.
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//((ReactionDiscRotation*)(action.get()))->set_hole_no(1);
		//((ReactionDiscRotation*)(action.get()))->set_position(1);
		//2-2-3.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-2);
		}
		//2-2-4.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//3.�����Źܵ���Ӧ�̶�����
	//3-1.�����Źܵ���Ӧ�̶����������жϴ����Ƿ�ɹ���
	PtrToAction action(new PutTubeInReactionDisc(
		ACTION_ID_PUT_TUBE_IN_REACTION_DISC,1,28000,30000));
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//3-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-4);
	}
	//3-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//4.�������Թܲ�ȡ�ܶ�����
	//4-1.�������Թܲ�ȡ�ܶ����������жϴ����Ƿ�ɹ���
	action.reset(new TakeTubeOutOfTubeStoreHouse(
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,
		1,23000,28000));
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//4-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-6);
	}
	//4-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//5.������������Һ������
	//5-1.������������Һ�����������жϴ����Ƿ�ɹ���
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
	//5-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-8);
	}
	//5-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//6.������������Һ������
	//6-1.������������Һ�����������жϴ����Ƿ�ɹ���
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
	//6-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-10);
	}
	//6-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//7.������������ϴ������
	//7-1.������������ϴ�����������жϴ����Ƿ�ɹ���
	action.reset(new SpecimenArmWash(
		ACTION_ID_SPECIMEN_ARM_WASH,1,11000,15000));
	if(!static_cast<bool>(action)){
		return(-11);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//7-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-12);
	}
	//7-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//8.������������ת������
	//8-1.������������ת�����������жϴ����Ƿ�ɹ���
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
	//8-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-14);
	}
	//8-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//9.�����Լ�����Һ������
	//9-1.������ǰ�������������
	const unsigned int spit_reagent_action_count=3;
	const unsigned int spit_reagent_start_times[
		spit_reagent_action_count]={4000,14000,24000};
	const unsigned int spit_reagent_finish_times[
		spit_reagent_action_count]={7000,17000,27000};
	//9-2.ѭ���������Լ�������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=spit_reagent_action_count;++index){
		//9-2-1.�����Լ�����Һ�����������жϴ����Ƿ�ɹ���
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
		//9-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-16);
		}
		//9-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//10.�����Լ�����Һ������
	//10-1.������ǰ�������������
	const unsigned int suck_reagent_action_count=3;
	const unsigned int suck_reagent_start_times[
		suck_reagent_action_count]={0,10000,20000};
	const unsigned int suck_reagent_finish_times[
		suck_reagent_action_count]={4000,14000,24000};
	//10-2.ѭ�������Լ�����Һ������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=suck_reagent_action_count;++index){
		//10-2-1.�����Լ�����Һ�����������жϴ����Ƿ�ɹ���
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
		//10-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-18);
		}
		//10-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//11.�����Լ�����ϴ������
	//11-1.������ǰ�������������
	const unsigned int wash_reagent_action_count=3;
	const unsigned int wash_reagent_start_times[
		wash_reagent_action_count]={7000,17000,27000};
	const unsigned int wash_reagent_finish_times[
		wash_reagent_action_count]={10000,20000,30000};
	//11-2.ѭ�������Լ�����ϴ������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=wash_reagent_action_count;++index){
		//11-2-1.����ϴ�Լ������������жϴ����Ƿ�ɹ���
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
		//11-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-20);
		}
		//11-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//12.�����Լ�����ת������
	//12-1.������ǰ�������������
	const unsigned int reagent_disc_rotation_action_count=2;
	const unsigned int reagent_disc_rotation_start_times[
		reagent_disc_rotation_action_count]={8000,28000};
	const unsigned int reagent_disc_rotation_finish_times[
		reagent_disc_rotation_action_count]={10000,30000};
	//12-2.ѭ�������Լ�����ת������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=
		reagent_disc_rotation_action_count;++index){
		//12-2-1.�����Լ�����ת�����������жϴ����Ƿ�ɹ���
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
		//12-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-22);
		}
		//12-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//13.����������ת��������
	//13-1.������ǰ�������������
	const unsigned int magnetic_beads_disc_rotation_action_count=12;
	const unsigned int magnetic_beads_disc_rotation_start_times[
		magnetic_beads_disc_rotation_action_count]={1000,3000,5000,
		7000,9000,11000,13000,15000,17000,25000,27000,29000};
	const unsigned int magnetic_beads_disc_rotation_finish_times[
		magnetic_beads_disc_rotation_action_count]={2000,4000,6000,
		8000,10000,12000,14000,16000,20000,26000,28000,30000};
	//13-2.ѭ��������������ת������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=
		magnetic_beads_disc_rotation_action_count;++index){
		//13-2-1.������������ת�����������жϴ����Ƿ�ɹ���
		action.reset(new MagneticBeadDiscRotation(
			ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,index+1,
			magnetic_beads_disc_rotation_start_times[index],
			magnetic_beads_disc_rotation_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-23);
		}
		//13-2-2.���õ�ǰ��������ת�����Ķ���״̬��
		//debug.
		//if(8==index){
			//action->set_status(Action::STATUS_ENABLED);
			//action->set_test_item_key(1);
			//((MagneticBeadDiscRotation*)(action.get()))->set_position_no(1);
		//}else{
		action->set_status(Action::STATUS_DEFAULT);
		//}
		//13-2-3.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-24);
		}
		//13-2-4.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//14.����ת��ץ�ִӷ�Ӧ��ȡ�ܶ�����
	//14-1.����ת��ץ�ִӷ�Ӧ��ȡ�ܶ����������жϴ����Ƿ�ɹ���
	action.reset(new TakeTubeOutOfReactionDisc(
		ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,
		1,21000,23000));
	if(!static_cast<bool>(action)){
		return(-25);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//14-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-26);
	}
	//14-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//15.�����عܵ���Ӧ�̶�����
	//15-1.�����عܵ���Ӧ�̶����������жϴ����Ƿ�ɹ���
	action.reset(new ReturnTubeToReactionDisc(
		ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,1,18000,20000));
	if(!static_cast<bool>(action)){
		return(-27);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//15-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-28);
	}
	//15-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//16.������ϴ��ȡ�ܶ�����
	//16-1.������ϴ��ȡ�ܶ����������жϴ����Ƿ�ɹ���
	action.reset(new TakeTubeOutOfWashingDisc(
		ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1,14000,18000));
	if(!static_cast<bool>(action)){
		return(-29);
	}
	//debug.
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//((TakeTubeOutOfWashingDisc*)(action.get()))->set_stop_position(0);
	//16-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-30);
	}
	//16-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//17.����ת��ץ�ַŹܵ���ϴ�̶�����
	//17-1.����ת��ץ�ַŹܵ���ϴ�̶����������жϴ����Ƿ�ɹ���
	action.reset(new PutTubeInWashingDisc(
		ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,
		1,23000,27000));
	if(!static_cast<bool>(action)){
		return(-31);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//17-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-32);
	}
	//17-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//18.����ת��ץ�ַŹܵ�����̶�����
	//18-1.����ת��ץ�ַŹܵ�����̶����������жϴ����Ƿ�ɹ���
	action.reset(new PutTubeInDetectionDisc(
		ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,1,18000,21000));
	if(!static_cast<bool>(action)){
		return(-33);
	}
	//.debug
	//action->set_status(Action::STATUS_ENABLED);
	//action->set_test_item_key(1);
	//18-2.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-34);
	}
	//18-3.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//19.����ת��ץ�ִӼ����ȡ�ܶ�����
	//19-1.������ǰ�������������
	const unsigned int discarding_tube_fetch_action_count=2;
	const unsigned int discarding_tube_fetch_start_times[
		discarding_tube_fetch_action_count]={0,7000};
	const unsigned int discarding_tube_fetch_finish_times[
		discarding_tube_fetch_action_count]={3000,10000};
	//19-2.ѭ������ת��ץ�ִӼ����ʱȡ�ܶ�����������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=discarding_tube_fetch_action_count;++index){
		//19-2-1.����ת��ץ�ִӼ����ȡ�ܶ����������жϴ����Ƿ�ɹ���
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
		//19-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-36);
		}
		//19-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//20.����ת��ץ�ֶ��ܶ�����
	//20-1.������ǰ�������������
	const unsigned int discarding_tube_place_action_count=2;
	const unsigned int discarding_tube_place_start_times[
		discarding_tube_place_action_count]={3000,10000};
	const unsigned int discarding_tube_place_finish_times[
		discarding_tube_place_action_count]={7000,14000};
	//20-2.ѭ�������ӹ�ʱ�Źܶ�����������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=discarding_tube_place_action_count;++index){
		//20-2-1.����ת��ץ�ֶ��ܶ����������жϴ����Ƿ�ɹ���
		action.reset(new DiscardTube(ACTION_ID_DISCARD_TUBE,index+1,
			discarding_tube_place_start_times[index],
			discarding_tube_place_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-37);
		}
		//.debug
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//20-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-38);
		}
		//20-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//21.������ϴ����ϴ������
	//21-1.������ϴ����ϴ�����������жϴ����Ƿ�ɹ���
	action.reset(new WashingDiscWash(
		ACTION_ID_WASHING_DISC_WASH,1,3000,23000));
	if(!static_cast<bool>(action)){
		return(-39);
	}
	//21-2.���õ�ǰ��ϴ����ϴ����״̬��
	action->set_status(WashingDiscWash::STATUS_DEFAULT);
	//21-3.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-40);
	}
	//21-4.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//22.������ϴ����ת������
	//22-1.������ϴ����ת�����������жϴ����Ƿ�ɹ���
	action.reset(new WashingDiscRotation(
		ACTION_ID_WASHING_DISC_ROTATION,1,0,1000));
	if(!static_cast<bool>(action)){
		return(-41);
	}
	//.debug
	//(((Instrument::instance())->get_components())->
		//get_washing_disc())->set_hole_state(
		//WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_USED);
	//22-2.���õ�ǰ����״̬��
	action->set_status(Action::STATUS_DEFAULT);
	//22-3.��⵱ǰ�����Ƿ�Ϸ���
	if(action->is_valid()<0){
		return(-42);
	}
	//22-4.����ǰ�����洢��ʱ��ͼ�С�
	actions.push_back(action);
	//23.�����������ת������
	//23-1.������ǰ�������������
	const unsigned int detection_disc_rotation_action_count=5;
	const unsigned int detection_disc_rotation_start_times[
		detection_disc_rotation_action_count]={6000,13000,17000,23000,29000};
	const unsigned int detection_disc_rotation_finish_times[
		detection_disc_rotation_action_count]={7000,14000,18000,24000,30000};
	//23-2.ѭ�������������ת������������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=detection_disc_rotation_action_count;++index){
		//23-2-1.�����������ת�����������жϴ����Ƿ�ɹ���
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
		//23-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-44);
		}
		//23-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//24.������⶯����
	//24-1.������ǰ�������������
	const unsigned int detect_action_count=2;
	const unsigned int detect_start_times[
		detect_action_count]={14000,24000};
	const unsigned int detect_finish_times[
		detect_action_count]={17000,27000};
	//24-2.ѭ��������⶯����������洢��ʱ��ͼ�С�
	for(unsigned int index=0;index!=detect_action_count;++index){
		//24-2-1.������⶯���������жϴ����Ƿ�ɹ���
		action.reset(new Detect(ACTION_ID_DETECT,index+1,
			detect_start_times[index],detect_finish_times[index]));
		if(!static_cast<bool>(action)){
			return(-45);
		}
		//debug
		//action->set_status(Action::STATUS_ENABLED);
		//action->set_test_item_key(1);
		//24-2-2.��⵱ǰ�����Ƿ�Ϸ���
		if(action->is_valid()<0){
			return(-46);
		}
		//24-2-3.����ǰ�����洢��ʱ��ͼ�С�
		actions.push_back(action);
	}
	//25.���浱ǰʱ��ͼ���ݡ�
	_actions.swap(actions);
	//26.�������е��˳ɹ����ء�
	return(0);
}