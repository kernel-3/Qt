#include"stdafx.h"
#include"TakeTubeOutOfWashingDisc.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfWashingDisc
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
TakeTubeOutOfWashingDisc::TakeTubeOutOfWashingDisc(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_stop_position(0){
}

/**
 * name: ~TakeTubeOutOfWashingDisc
 * brief: ����������
 * param: --
 * return: --
 */
TakeTubeOutOfWashingDisc::~TakeTubeOutOfWashingDisc(void){
}

/**
 * name: set_stop_position
 * brief: ����ֹͣλ�á�
 * param: stop_position - �����ֹͣλ�á�
 * return: --
 */
void TakeTubeOutOfWashingDisc::set_stop_position(
	const unsigned int stop_position){
	_stop_position=stop_position;
}

/**
 * name: get_stop_position
 * brief: ��ȡֹͣλ�á�
 * param: --
 * return: ����ֹͣλ�á�
 */
unsigned int TakeTubeOutOfWashingDisc::get_stop_position() const{
	return(_stop_position);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: ������Ե�ǰ������������������ش����������
 *         ����ɹ������ǰ�����������㡣
 *         ��������ǰ����ʧ�ܣ��򷵻�С���������
 */
int TakeTubeOutOfWashingDisc::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼������������
	const int clear_result=Action::clear();
	//2.�����������ʱ����������ֱ�ӷ��ء�
	if(clear_result<0){
		return(-1);
	}
	//3.�������ɹ�����ǰ�������������ǰ����������¼�����ݡ�
	else if(0==clear_result){
		//3-1.�����ǰ�����е����ݡ�
		_stop_position=0;
		//3-2.�������е��˳ɹ����ء�
		return(0);
	}
	//4.���������Ӧ���������������������������ֱ�ӷ��ء�
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
int TakeTubeOutOfWashingDisc::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_stop_position=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfWashingDisc::is_valid() const{
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
		//4-1.���ֹͣλ�÷Ƿ�����ֱ�ӷ��ش���
		if((TransportTong::STOP_POSITION_REACTION_DISC!=_stop_position)&&(
			TransportTong::STOP_POSITION_DETECTION_DISC!=_stop_position)){
			return(-2);
		}
		//4-2.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�Ӵ���
	else if(STATUS_DEFAULT==get_status()){
		return(-3);
	}
	//6.�����ǰΪδ֪�������ֱ�ӷ��ش���
	else{
		return(-4);
	}
}

/**
 * name: execute
 * breif: ִ�е�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfWashingDisc::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.������ϴ�̳���λλ�ô�����������ֵ���˺�������ֻ������Է������յĵ���״̬�������ã���
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_having_tube_in_exit_flag_expect_value(
			WashingDisc::FLAGE_USED);
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �����ϴ�̳���λ�Ƿ��йܡ�"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-3.����ָ������ϴ�̳���λ�Ƿ��йܡ�
		if((((Instrument::instance())->get_components())->
			get_washing_disc())->inquire_sensor()<0){
			//2-3-1.���ô�����롣
			set_error(ERROR_COMMUNICATION);
			//2-3-2.��д�����־��
			log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::execute \
�����У����� WashingDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.�������е���ֱ�ӷ��ش���
			return(-2);//��ǰ������״̬�������仯��
		}
		//2-4.��д�����־��
		log.Format(_T("Event %s��%ld���� �����ϴ�̳���λ�Ƿ��йܳɹ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-5.�����ǰ��ϴ�̳���λ�޹ܡ�
		if(WashingDisc::FLAGE_EMPTY==(((Instrument::instance())->
			get_components())->get_washing_disc())->
			get_having_tube_in_exit_flag()){
			//2-5-1.���ô�����롣
			set_error(ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC);
			//2-5-2.������ϴ����Ӧλ���ϵĿ�״̬Ϊ�޹�״̬��
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_hole_state(
				WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_EMPTY);
			//2-5-3.��д�����־��
			log.Format(_T("Warning %s��%ld���� ��⵽��ϴ�̳���λ�޹ܡ�"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-5-4.�������е���ֱ�ӷ��ش���
			return(-3);//��ǰ������״̬�������仯��
		}
		//2-6.�����ǰ��ϴ�̳���λ�йܣ���д�����־��
		log.Format(_T("Event %s��%ld���� ��⵽��ϴ�̳���λ�йܡ�"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-7.���ʹ���ϴ��ȡ��ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->get_transport_tong())->
			take_tube_out_of_washing_disc(static_cast<TransportTong::StopPosition>(
			_stop_position))<0){
			//2-7-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-7-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::execute \
�����У����� TransportTong::take_tube_out_of_washing_disc ����ʧ�ܣ�"),(
				COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-7-3.�������е���ֱ�ӷ��ش���
			return(-4);
		}
		//2-8.��д��־��
		log.Format(_T("Event %s��%ld���� ת��ץ�ִ���ϴ�̿�ʼȡ�ܡ�"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-9.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::execute \
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
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfWashingDisc::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���ת��ץ�ִ���ϴ��ȡ����ɡ�
		if(TransportTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_transport_tong())->
			get_take_tube_out_of_washing_disc_response_flag()){
			//2-1-1.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ת��ץ�ִ���ϴ��ȡ�ܽ�����"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.������ϴ�̳���λ�йܱ�ǵ�����ֵ���˴�����ֻ���Է����յĵ�����������ã���
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_exit_flag_expect_value(
				WashingDisc::FLAGE_EMPTY);
			//2-1-3.��д�����־��
			log.Format(_T("Event %s��%ld���� �����ϴ�̳���λ�Ƿ��йܡ�"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-4.��ȡ�������������ϴ�̳���λ�Ƿ���Ȼ�йܡ�
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->inquire_sensor()<0){
				//a.���ô�����롣
				set_error(ERROR_COMMUNICATION);
				//b.��д��־��
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::complete \
�����У����� WashingDisc::inquire_sensor ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-1-5.��д�����־��
			log.Format(_T("Event %s��%ld���� �����ϴ�̳���λ�Ƿ��йܽ�����"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-6.�����ǰ��ϴ�̳���λ�޹ܡ�
			if(WashingDisc::FLAGE_EMPTY==(((Instrument::instance())->
				get_components())->get_washing_disc())->
				get_having_tube_in_exit_flag()){
				//a.�����ϴ�̳���λλ��״̬��
				(((Instrument::instance())->get_components())->
					get_washing_disc())->set_hole_state(
					WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_EMPTY);
				//b.��д��־��
				log.Format(_T("Event %s��%ld���� ��ϴ�̳���λ�޹ܡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.�������е��˳ɹ����ء�
				return(0);
			}
			//2-1-7.�����ǰ��ϴ�̳���λ�йܡ�
			else{
				//a.���ô�����롣
				set_error(ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED);
				//b.�����ϴ�̳���λλ��״̬��
				(((Instrument::instance())->get_components())->get_washing_disc())->
					set_hole_state(WashingDisc::POSITION_EXIT,WashingDisc::HOLE_STATE_FAILED);
				//c.��д��־��
				log.Format(_T("Warning %s��%ld���� ��ϴ�̳���λ�йܡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//d.�������е���ֱ�ӷ��ش���
				return(1);//���ǰ����״̬�ı䡣
			}
		}
		//2-2.���ת��ץ�ִ���ϴ��ȡ����δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::complete \
�����У���⵽ת��ץ�ִ���ϴ��ȡ�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ת��ץ�ִ���ϴ��ȡ��ʱ������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfWashingDisc::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-5);
	}
}