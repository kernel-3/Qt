#include"stdafx.h"
#include"PutTubeInWashingDisc.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/WashingDisc.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: PutTubeInWashingDisc
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
PutTubeInWashingDisc::PutTubeInWashingDisc(		
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~PutTubeInWashingDisc
 * brief: ����������
 * param: --
 * return: --
 */
PutTubeInWashingDisc::~PutTubeInWashingDisc(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int PutTubeInWashingDisc::is_valid() const{
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
int PutTubeInWashingDisc::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInWashingDisc::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.����ת��ץ�ַŹܵ���ϴ��ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_transport_tong())->put_tube_in_washing_disc()<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� PutTubeInWashingDisc::execute \
�����У����� TransportTong::put_tube_in_washing_disc ����ʧ�ܣ�"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ת��ץ�ֿ�ʼ�Źܵ���ϴ�̡�"),
			(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� PutTubeInWashingDisc::execute \
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
int PutTubeInWashingDisc::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����PutTubeInWashingDisc::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���ת��ץ�ַŹܵ���ϴ����ɡ�
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_put_tube_in_washing_disc_response_flag()){
			//2-1-1.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ת��ץ�ַŹܵ���ϴ����ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.������ϴ�̽���λ�йܱ�־������ֵ���˺���ֻ������Է����յ���ʱ�����ã���
			(((Instrument::instance())->get_components())->get_washing_disc())->
				set_having_tube_in_entry_flag_expect_value(WashingDisc::FLAGE_USED);
			//2-1-3.��д�����־��
			log.Format(_T("Event %s��%ld���� ��ѯ��ϴ�̽���λ�Ƿ��йܡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.����ָ���ȡ��ϴ���ϵ�λ�ô������������ж϶�ȡ�Ƿ�ɹ���
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->inquire_sensor()<0){
				//a.���ô����ʶ��
				set_error(ERROR_COMMUNICATION);
				//b.��д������־��
				log.Format(_T("Error %s��%ld����PutTubeInWashingDisc::complete \
�����У����� WashingDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-1-5.�����ǰ��ϴ�̽���λ�йܡ�
			if(WashingDisc::FLAGE_USED==(((Instrument::instance())->get_components())->
				get_washing_disc())->get_having_tube_in_entry_flag()){
				//a.������ϴ�̽���λ״̬Ϊ�й�״̬��
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_USED);
				//b.��д��־��
				log.Format(_T("Event %s��%ld���� ��ϴ�̽���λ�йܡ�"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.�������е���ֱ�ӳɹ����ء�
				return(0);
			}
			//2-1-6.�����ǰ��ϴ�̽���λδ�ܼ�⵽�Թܡ�
			else{
				//a.������ϴ�̽���λ״̬Ϊ�޹�״̬��
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_ENTRY,WashingDisc::HOLE_STATE_EMPTY);
				//b.���ô�����롣
				set_error(ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED);
				//c.��д�����־��
				log.Format(_T("Warning %s��%ld���� ��ϴ�̽���λ�޹ܡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.�������е���ֱ�ӷ��ش���
				return(1);
			}
		}
		//2-2.���ת��ץ�ֻعܵ���Ӧ����δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� PutTubeInWashingDisc::complete \
�����У���⵽ת��ץ�ַŹܵ���ϴ�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ת��ץ�ַŹܵ���ϴ��ʱ������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� PutTubeInWashingDisc::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}