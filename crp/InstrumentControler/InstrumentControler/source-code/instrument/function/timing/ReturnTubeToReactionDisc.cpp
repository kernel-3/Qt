#include"stdafx.h"
#include"ReturnTubeToReactionDisc.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/ReactionDisc.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/ReactionDisc.h"
#include<MMSystem.h>

/**
 * name: ReturnTubeToReactionDisc
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
ReturnTubeToReactionDisc::ReturnTubeToReactionDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~ReturnTubeToReactionDisc
 * brief: ����������
 * param: --
 * return: --
 */
ReturnTubeToReactionDisc::~ReturnTubeToReactionDisc(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReturnTubeToReactionDisc::is_valid() const{
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
int ReturnTubeToReactionDisc::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//unfinished: ����Ӧ����Ҫ��ⷴӦ�̳���λ�Ƿ��йܣ�����Ŀǰ��ʱ��ͼ����
		//            ��ʹ���ַ�Ӧ�̳���λ�йܣ�Ҳ������Ч�ؽ��д��������Դ�
		//            �������з�Ӧ�̳���λ�йܼ�⡣���������λ��ʱ��Ԥ���ģ���
		//            ʱ�������йܡ�
		//2-1.����ת��ץ�ֻعܵ���Ӧ��ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_transport_tong())->return_tube_to_reaction_disc()<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::execute \
�����У����� TransportTong::return_tube_to_reaction_disc ����ʧ�ܣ�"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.���÷�Ӧ�̳���λ״̬��
		const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
			get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
			get_hole_no_in_reaction_disc();
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
			ReactionDisc::HOLE_STATE_PROCESSING);
		//2-3.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ת��ץ�ֿ�ʼ�عܵ���Ӧ�̡�"),
			(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime());
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
		log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::execute �����У�\
��⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
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
int ReturnTubeToReactionDisc::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����ReturnTubeToReactionDisc::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���ת��ץ�ֻعܵ���Ӧ����ɡ�
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_return_tube_to_reaction_disc_response_flag()){
			//2-1-1.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ת��ץ�ֻعܵ���Ӧ����ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.���÷�Ӧ�̳���λ�йܱ�ǵ�����ֵ���˴�����ֻ���Է����յĵ�����������ã���
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_exit_flag_expect_value(
				ReactionDisc::FLAGE_USED);
			//2-1-3.��д�����־��
			log.Format(_T("Event %s��%ld���� ��ⷴӦ�̳���λ�Ƿ��йܡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.��ȡ����������ⷴӦ�̳���λ�Ƿ��йܡ�
			if((((Instrument::instance())->get_components())->
				get_reaction_disc())->inquire_sensor()<0){
				//a.���ô�����롣
				set_error(ERROR_COMMUNICATION);
				//b.��д��־��
				log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::execute \
�����У����� ReactionDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-1-5.�����Ӧ�̳���λ�йܡ�
			if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->
				get_components())->get_reaction_disc())->
				get_having_tube_in_exit_flag()){
				//2-1-5-1.���÷�Ӧ�̳���λ״̬��
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_WAIT);
				//2-1-5-2.��д��־��
				log.Format(_T("Event %s��%ld���� ��⵽��Ӧ�̳���λ�йܡ�"),(
					COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//2-1-5-3.�������е���ֱ�ӳɹ����ء�
				return(0);
			}
			//2-1-6.�����Ӧ�̳���λ�޹ܡ�
			else{
				//2-1-6-1.���ô�����롣
				set_error(ERROR_RETURN_TUBE_TO_RECTION_DISC_FAILED);
				//2-1-6-2.���ķ�Ӧ�̳���λ״̬��
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->
					get_reaction_disc())->set_hole_state(hole_no_in_reaction_disc,
					ReactionDisc::HOLE_STATE_EMPTY);
				//2-1-6-3.��д������־��
				log.Format(_T("Warning %s��%ld���� ��⵽��Ӧ�̳���λ�޹ܡ�"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//2-1-6-4.�������е���ֱ�ӷ��ء�
				return(1);
			}
		}
		//2-2.���ת��ץ�ֻعܵ���Ӧ����δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//2-2-2-1.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//2-2-2-2.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::complete \
�����У���⵽ת��ץ�ֻعܵ���Ӧ�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//2-2-2-3.�������е���ֱ�ӷ��ش���
				return(-3);
			}
			//2-2-3.�����ǰ���������δ�ִ����ޡ�
			else{
				//2-2-3-1.���ô����ʶ��
				set_error(ERROR_TIMEOUT_T);
				//2-2-3-2.��д������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� ת��ץ�ֻعܵ���Ӧ��ʱ������ʱ��"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//2-2-3-3.�������е���ֱ�ӷ��ش���
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
		log.Format(_T("Error %s��%ld���� ReturnTubeToReactionDisc::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}