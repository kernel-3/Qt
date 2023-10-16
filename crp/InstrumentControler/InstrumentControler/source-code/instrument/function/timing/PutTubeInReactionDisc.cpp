#include"stdafx.h"
#include"PutTubeInReactionDisc.h"
#include"../../../common/Logs.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/ReactionDisc.h"
#include"../../component/LoadTong.h"
#include"../../component/TubeStorehouse.h"
#include"../../function/timing/Timing.h"
#include"../../function/Functions.h"
#include"../../../export/TestItem.h"
#include<MMSystem.h>

//define
unsigned int PutTubeInReactionDisc::_put_tube_in_failed_times=0;

/**
 * name: PutTubeInReactionDisc
 * breif: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
PutTubeInReactionDisc::PutTubeInReactionDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~PutTubeInReactionDisc
 * breif: ����������
 * param: --
 * return: --
 */
PutTubeInReactionDisc::~PutTubeInReactionDisc(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int PutTubeInReactionDisc::is_valid() const{
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
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬����
 */
int PutTubeInReactionDisc::execute(const Status status){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����״̬������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���÷�Ӧ����λ�ô�����״̬��־����ֵ��
		//    ���д���ֻ���Է����յĵ��Ի����������ã���
		(((Instrument::instance())->get_components())->get_reaction_disc())->
			set_having_tube_in_entry_flag_expect_value(ReactionDisc::FLAGE_EMPTY);
		//2-2.����ָ���ѯ��Ӧ����λ�ô������������жϲ�ѯ�Ƿ�ɹ���
		if(((((Instrument::instance())->get_components())->get_reaction_disc())->
			inquire_sensor())<0){
			//2-2-1.���ô�����롣
			set_error(ERROR_COMMUNICATION);
			//2-2-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::execute \
�����У����� ReactionDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-2-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-3.�����ǰ��⵽��Ӧ�̽���λ���йܡ�
		if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
			get_reaction_disc())->get_having_tube_in_entry_flag()){
			//remark: �����Ƿ���Ҫ�ۻ�����������������ж������Ƿ���Ҫֹͣ��
			//2-3-1.���ô�����롣
			set_error(ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT);
			//2-3-2.����Ӧ����ָ����λ����Ϊ����״̬��
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_FAILED);
			//2-3-3.��д�����־��
			CString log(_T(""));
			log.Format(_T("Warning %s��%ld���� װ��ץ�ַŹܵ���Ӧ��ʱ��⵽�Թܳ�ͻ��"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-4.�������е���ֱ�ӷ��ش���
			return(-3);
		}
		//2-4.�����ǰ��Ӧ�̽���λ���޹ܡ�
		else{
			//2-4-1.����ָ������װ��ץ�ַŹܡ�
			if((((Instrument::instance())->get_components())->
				get_load_tong())->put_tube_in()<0){
				//a.���ô�����롣
				set_error(ERROR_UNKNOWN);
				//b.��д��־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::execute \
�����У����� LoadTong::put_tube_in ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-4);
			}
			//2-4-2.����Ӧ����ָ����λ����Ϊ����״̬��
			const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_reaction_disc();
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_PROCESSING);
			//2-4-3.��д�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� װ��ץ�ֿ�ʼ�Źܡ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-4-4.�Ź�ָ��һ�����ͣ�����Ϊװ��ץ�����Ѿ��޹ܡ�
			(((Instrument::instance())->get_components())->get_load_tong())->
				set_having_tube_flag(FALSE);
			//2-4-5.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//3.�����ǰ����״̬��������״̬��
	else{
		//3-1.����δ֪����״̬
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::execute \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}

/**
 * name: complete
 * brief: ��ɵ�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬����
 */
int PutTubeInReactionDisc::complete(const Status status){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���Źܶ����Ƿ���ɡ�
		if(LoadTong::FLAG_IDLE==(((Instrument::instance())->get_components())->
			get_load_tong())->get_put_tube_in_response_flag()){
			//2-1-1.���÷�Ӧ����λ�ô�����״̬��־����ֵ�����д���ֻ���Է����յĵ��Ի����������ã���
			(((Instrument::instance())->get_components())->get_reaction_disc())->
				set_having_tube_in_entry_flag_expect_value(ReactionDisc::FLAGE_USED);
			//2-1-2.����ָ���⵱ǰ��Ӧ�̽���λ�Ƿ��йܡ�
			if(((((Instrument::instance())->get_components())->get_reaction_disc())->
				inquire_sensor())<0){
				//a.���ô�����롣
				set_error(ERROR_COMMUNICATION);
				//b.��д��־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::complete \
�����У����� ReactionDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-1-3.�����ǰ��Ӧ�̽���λ�йܣ��Źܳɹ�����ֱ�ӳɹ����ء�
			if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->
				get_components())->get_reaction_disc())->
				get_having_tube_in_entry_flag()){
				//a.����Ź�ʧ�ܴ�����
				_put_tube_in_failed_times=0;
				//b.���÷�Ӧ���ϵ�ǰ��λ״̬��
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->get_reaction_disc())->
					set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_WAIT);
				//c.���������־��
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� װ��ץ�ַŹ���ɡ�"),(
					COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//d.�������е��˳ɹ����ء�
				return(0);
			}
			//2-1-4.�����ǰ��Ӧ�̽���λ�޹ܡ�
			else{
				//1>.�Ź�ʧ�ܴ����Լӡ�
				++_put_tube_in_failed_times;
				//2>.���÷�Ӧ������Ӧ��λ״̬Ϊ�ա�
				const unsigned int hole_no_in_reaction_disc=((((Instrument::instance())->
					get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
					get_hole_no_in_reaction_disc();
				(((Instrument::instance())->get_components())->get_reaction_disc())->
					set_hole_state(hole_no_in_reaction_disc,ReactionDisc::HOLE_STATE_EMPTY);
				//3>.����Ź�ʧ�ܴ����������ޡ�
				if(_put_tube_in_failed_times>MAX_PUT_TUBE_IN_FAILED_TIMES){
					//3-1>.���ô�����루�������ץ��10�ζ�δ�ɹ�������Ϊ�Թܲ��޹ܣ���
					set_error(ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE);
					//3-2>.����Թܲ�ʣ�������
					(((Instrument::instance())->get_components())->
						get_tube_storehouse())->clear_tube_count();
					//3-3>.��д��־��
					CString log(_T(""));
					log.Format(_T("Warning %s��%ld���� װ��ץ�ַŹ�ʱ����⵽�Թܲ��޹ܣ�"),(
						COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//3-4>.�������е���ֱ�ӷ��ش���
					return(1);//������ֵ���ڵ������ʱ��������ǰ����״̬�����
				}
				//4>.����Ź�ʧ�ܴ�����δ�������ޡ���
				else{
					//4-1>.���ô�����롣
					set_error(ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED);
					//4-2>.��д��־��
					CString log(_T(""));
					log.Format(_T("Warning %s��%ld���� װ��ץ�ַŹܺ�δ���ڷ�Ӧ�̽���λ��⵽��Ӧ�ܣ�"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//4-3>.�������е���ֱ�ӷ��ش���
					return(2);//������ֵ���ڵ������ʱ��������ǰ����״̬�����
				}
			}
		}
		//2-2.����Źܶ�����δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô�����롣
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::complete \
�����У���⵽װ��ץ�ַŹ����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
			//2-2-3.�����ǰ���������δ�ִ����ޡ�
			else{
				//a.���ô�����롣
				set_error(ERROR_TIMEOUT_T);
				//b.��д�¼���������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� װ��ץ�ַŹܷ�����ʱ��"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-4);
			}
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪����״̬
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInReactionDisc::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}