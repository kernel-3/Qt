#include"stdafx.h"
#include"ReagentArmSpit.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/ReagentArm.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/ReactionDisc.h"
#include<MMSystem.h>

/**
 * name: ReagentArmSpit
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
ReagentArmSpit::ReagentArmSpit(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_spit_volume(0)
	,_down_steps(0){
}

/**
 * name: ~ReagentArmSpit
 * breif: ����������
 * param: --
 * return: --
 */
ReagentArmSpit::~ReagentArmSpit(void){
}

/**
 * name: set_volume
 * brief: ������Һ�������
 * param: volume - �������Һ�����
 * return: --
 */
void ReagentArmSpit::set_spit_volume(const unsigned int volume){
	_spit_volume=volume;
}

/**
 * name: get_volume
 * breif: ��ȡ��Һ�����
 * param: --
 * return: ������Һ�����
 */
unsigned int ReagentArmSpit::get_spit_volume() const{
	return(_spit_volume);
}

/**
 * name: set_down_steps
 * brief: �����½�������
 * param: steps - ������½�������
 * return: --
 */
void ReagentArmSpit::set_down_steps(const unsigned int steps){
	_down_steps=steps;
}

/**
 * name: get_down_steps
 * brief: ��ȡ�½�������
 * param: --
 * return: �����½�������
 */
unsigned int ReagentArmSpit::get_down_steps() const{
	return(_down_steps);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int ReagentArmSpit::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int clear_result=Action::clear();
	//2.���������Ӧ����������ʧ�ܡ�
	if(clear_result<0){
		return(-1);
	}
	//3.���������Ӧ����������ɹ���
	else if(0==clear_result){
		_spit_volume=0;
		_down_steps=0;
		return(0);
	}
	//4.���������Ӧ�������������������������
	else{
		return(1);
	}
}

/**
 * name: reset
 * breif: ���õ�ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int ReagentArmSpit::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_spit_volume=0;
	_down_steps=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentArmSpit::is_valid() const{
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int result=Action::is_valid();
	//2.���������Ӧ������ʧ�ܣ���ֱ�ӷ�����Ӧ����
	if(result<0){
		return(-1);
	}
	//3.�����ǰ����Ϊ��Ч�������򲻽������ݼ���ֱ�ӷ��ء�
	if(STATUS_DISABLED==get_status()){
		return(0);
	}
	//4.�����ǰ����Ϊ��Ч��������������ݼ��飬�����жϼ����Ƿ�Ϸ���
	else if(STATUS_ENABLED==get_status()){
		//û�б�Ҫ�������Լ��½�������
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ش���
	else if(STATUS_DEFAULT==get_status()){
		return(-2);//�˶�����֧��Ĭ�϶�����
	}
	//6.�����ǰΪδ֪�������ֱ�ӷ��ش���
	else{
		return(-3);
	}
}

/**
 * name: execute
 * breif: ִ�е�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentArmSpit::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSpit::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����Լ�����Һָ�
		if((((Instrument::instance())->get_components())->
			get_reagent_arm())->spit(_spit_volume,_down_steps)<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� ReagentArmSpit::execute \
�����У����� ReagentArm::spit ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.���÷�Ӧ����Ӧ�׵�״̬��
		const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
			get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
			get_hole_no_in_reaction_disc();
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
			ReactionDisc::HOLE_STATE_PROCESSING);
		//2-3.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �Լ��ۿ�ʼ��Һ��"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-4.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSpit::execute \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-3);
	}
}

/**
 * name: complete
 * brief: ��ɵ�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentArmSpit::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSpit::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.����Լ�����Һ��ɡ�
		if(ReagentArm::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_reagent_arm())->get_spit_response_flag()){
			//2-1-1.���÷�Ӧ����Ӧ�׵�״̬��
			unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_hole_state(
				hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_WAIT);
			//2-1-2.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� �Լ�����Һ�ɹ���ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-3.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-2.����Լ�����Һ��δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReagentArmSpit::complete \
�����У���⵽�Լ�����Һ���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-2-3.�����ǰ���������δ�ִ����ޡ�
			else{
				//a.���ô����ʶ��
				set_error(ERROR_TIMEOUT_T);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� �Լ�����Һʱ������ʱ��"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSpit::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}