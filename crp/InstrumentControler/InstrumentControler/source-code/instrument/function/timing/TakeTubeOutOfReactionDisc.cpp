#include"stdafx.h"
#include"TakeTubeOutOfReactionDisc.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/ReactionDisc.h"
#include"../../component/WashingDisc.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/ReactionDisc.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfReactionDisc
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
TakeTubeOutOfReactionDisc::TakeTubeOutOfReactionDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_reserve_reaction_disc_hole_flag(FALSE){
}

/**
 * name: ~TakeTubeOutOfReactionDisc
 * brief: ����������
 * param: --
 * return: --
 */
TakeTubeOutOfReactionDisc::~TakeTubeOutOfReactionDisc(void){
}

/**
 * name: set_reserve_reaction_disc_hole_flag
 * brief: ���ñ�����Ӧ�̿ױ�־��
 * param: flag - ������Ƿ�����Ӧ�̿ױ�־��
 * return: --
 */
void TakeTubeOutOfReactionDisc::set_reserve_reaction_disc_hole_flag(const BOOL flag){
	_reserve_reaction_disc_hole_flag=flag;
}

/**
 * name: get_reserve_reaction_disc_hole_flag
 * brief: ��ȡ������Ӧ�̿ױ�־��
 * param: --
 * return: ���ر�����Ӧ�̿ױ�־��
 */
BOOL TakeTubeOutOfReactionDisc::get_reserve_reaction_disc_hole_flag() const{
	return(_reserve_reaction_disc_hole_flag);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int TakeTubeOutOfReactionDisc::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int clear_result=Action::clear();
	//2.���������Ӧ����������ʧ�ܡ�
	if(clear_result<0){
		return(-1);
	}
	//3.���������Ӧ����������ɹ���
	else if(0==clear_result){
		_reserve_reaction_disc_hole_flag=FALSE;
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
int TakeTubeOutOfReactionDisc::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_reserve_reaction_disc_hole_flag=FALSE;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfReactionDisc::is_valid() const{
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
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ش���
	else if(STATUS_DEFAULT==get_status()){
		return(-2);
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
int TakeTubeOutOfReactionDisc::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���÷�Ӧ�̳���λ�йܱ���Լ���ϴ�̽���λ�йܱ�ǵ�����ֵ���˺���ֻ������Է����յĵ���״̬ʱ�������ã���
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_having_tube_in_exit_flag_expect_value(ReactionDisc::FLAGE_USED);
		(((Instrument::instance())->get_components())->get_washing_disc())->
			set_having_tube_in_entry_flag_expect_value(WashingDisc::FLAGE_EMPTY);
		//2-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ��ⷴӦ�̳���λ����ϴ�̽���λ�Ƿ��йܡ�"),(
			COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.���Ͷ�ȡ��Ӧ�̡���ϴ��λ�ô�����ָ�
		if((((Instrument::instance())->get_components())->
			get_reaction_disc())->inquire_sensor()<0){
			//2-3-1.���ô�����롣
			set_error(ERROR_COMMUNICATION);
			//2-3-2.��д��־��
			log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::execute \
�����У����� ReactionDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-4.�����Ӧ�̳���λ�޹ܣ���ֱ�ӷ��ش���
		if(ReactionDisc::FLAGE_EMPTY==(((Instrument::instance())->
			get_components())->get_reaction_disc())->
			get_having_tube_in_exit_flag()){
			//2-4-1.�����Ӧ�̳���λ״̬��
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_EMPTY);
			//2-4-2.���ô�����롣
			set_error(ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC);
			//2-4-3.��д��־��
			log.Format(_T("Warning %s��%ld���� ��⵽��Ӧ�̳���λ�޹ܣ�"),(
				COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-4-4.�������е���ֱ�ӷ��ش���
			return(-3);
		}
		//2-5.��д�����־��
		log.Format(_T("Event %s��%ld���� ��⵽��Ӧ�̳���λ�йܣ�"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-6.�����ϴ�̽���λ�йܣ���ֱ�ӷ��ش���
		if(WashingDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
			get_washing_disc())->get_having_tube_in_entry_flag()){
			//2-6-1.������ϴ�̽���λλ��״̬��
			(((Instrument::instance())->get_components())->get_washing_disc())->
				set_hole_state(WashingDisc::POSITION_ENTRY,
				WashingDisc::HOLE_STATE_FAILED);
			//2-6-2.����ǰ��Ӧ�̳���λ״̬����Ϊ�Ϲ�״̬��
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
				ReactionDisc::HOLE_STATE_FAILED);
			//2-6-3.���ô�����롣
			set_error(ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT);
			//2-6-4.��д��־��
			log.Format(_T("Warning %s��%ld���� ��⵽��ϴ�̽���λ�йܣ�"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-6-5.�������е���ֱ�ӷ��ش���
			return(-4);
		}
		//2-7.��д��־��
		log.Format(_T("Event %s��%ld����  ��⵽��ϴ�̽���λ�޹ܣ�"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-8.���ʹӷ�Ӧ��ȡ��ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->get_transport_tong())->
			take_tube_out_of_reaction_disc()<0){
			//2-8-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-8-2.��д��־��
			log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::execute \
�����У����� TransportTong::take_tube_out_of_reaction_disc ����ʧ�ܣ�"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-8-3.�������е���ֱ�ӷ��ش���
			return(-5);
		}
		//2-9.���÷�Ӧ�̳���λ�Թ�״̬��
		const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
			get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
			get_hole_no_in_reaction_disc();
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_PROCESSING);
		//2-10.��д��־��
		log.Format(_T("Event %s��%ld���� ת��ץ�ִӷ�Ӧ�̿�ʼȡ�ܡ�"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-11.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::execute \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-6);
	}
}

/**
 * name: complete
 * brief: ��ɵ�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfReactionDisc::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����TakeTubeOutOfReactionDisc::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���ת��ץ�ִӷ�Ӧ��ȡ����ɡ�
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_take_tube_out_of_reaction_disc_response_flag()){
			//2-1-1.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ת��ץ�ִӷ�Ӧ��ȡ����ɡ�"),(
					COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.���÷�Ӧ�̳���λ�йܱ�ǵ�����ֵ���˺���ֻ������Է����յĵ���״̬ʱ�������ã���
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_exit_flag_expect_value(
				ReactionDisc::FLAGE_EMPTY);
			//2-1-3.��д�����־��
			log.Format(_T("Event %s��%ld���� ��ⷴӦ�̳���λ�Ƿ��йܡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.���Ͷ�ȡ��Ӧ��λ�ô�����ָ�
			if((((Instrument::instance())->get_components())->
				get_reaction_disc())->inquire_sensor()<0){
				//2-1-4-1.���ô�����롣
				set_error(ERROR_COMMUNICATION);
				//2-1-4-2.��д��־��
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::complete \
�����У����� ReactionDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//2-1-4-3.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-1-5.�����Ӧ�̳���λ�йܡ�
			if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
				get_reaction_disc())->get_having_tube_in_exit_flag()){
				//a.���÷�Ӧ�̳���λ״̬��
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_FAILED);
				//b.���ô�����롣
				set_error(ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED);
				//c.��д��־��
				log.Format(_T("Warning %s��%ld���� ��⵽��Ӧ�̳���λ�йܣ�"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.�������е���ֱ�ӷ��ش���
				return(1);
			}
			//2-1-6.���÷�Ӧ�̳���λ״̬��
			if(get_reserve_reaction_disc_hole_flag()){
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_RESERVED);
			}else{
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_EMPTY);
			}
			//2-1-7.��д�����־��
			log.Format(_T("Event %s��%ld���� ��⵽��Ӧ�̳���λ�޹ܣ�"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-8.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-2.���ϴ�Լ���δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::complete \
�����У���⵽ת��ץ�ִӷ�Ӧ��ȡ�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
			//2-2-3.�����ǰ���������δ�ִ����ޡ�
			else{
				//a.���ô����ʶ��
				set_error(ERROR_TIMEOUT_T);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� ת��ץ�ִӷ�Ӧ��ȡ��ʱ������ʱ��"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-4);
			}
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfReactionDisc::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}