#include"stdafx.h"
#include"DiscardTube.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TransportTong.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include"../../component/DetectionDisc.h"
#include<MMSystem.h>

/**
 * name: DiscardTube
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
DiscardTube::DiscardTube(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~DiscardTube
 * breif: ����������
 * param: --
 * return: --
 */
DiscardTube::~DiscardTube(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DiscardTube::is_valid() const{
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
int DiscardTube::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� DiscardTube::execute �����У�\
���� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.����ת��ץ�ֶ���ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_transport_tong())->discard_tube()<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� DiscardTube::execute �����У�\
���� TransportTong::discard_tube ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ת��ץ�ֿ�ʼ���ܡ�"),
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
		log.Format(_T("Error %s��%ld���� DiscardTube::execute \
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
int DiscardTube::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����DiscardTube::complete �����У�\
���� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.��ȡ��ǰת��ץ�ֶ��ܻظ���־��
		const TransportTong::Flag response=(((
			Instrument::instance())->get_components())->
			get_transport_tong())->get_discard_tube_response_flag();
		//2-2.���ת��ץ�ֶ���ʱδ�ܼ�⵽���ܶ�����
		if(TransportTong::FLAGE_EMPTY==response){
			//2-2-1.���ü��������Ӧ��״̬Ϊ����״̬��
			const unsigned int hole_no_in_detection_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->get_detection_disc())->
				set_hole_state(hole_no_in_detection_disc,DetectionDisc::HOLE_STATE_FAILED);
			//2-2-2.�����־��
			CString log(_T(""));
			log.Format(_T("Warning %s��%ld���� ת��ץ�ֶ���ʱ���ӹ�λδ�ܼ�⵽�Թܡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-2-3.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-3.���ת��ץ�ֶ���ʱ��⵽���ܶ�����
		else if(TransportTong::FLAGE_USED==response){
			//2-3-1.���ü��������Ӧ��״̬Ϊ��״̬��
			const unsigned int hole_no_in_detection_disc=((((Instrument::instance())->
				get_functions())->get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			(((Instrument::instance())->get_components())->get_detection_disc())->
				set_hole_state(hole_no_in_detection_disc,DetectionDisc::HOLE_STATE_EMPTY);
			//2-3-2.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ת��ץ�ֶ�����ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-3.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-4.���ת��ץ�ֶ��ܳ�ʱ��
		else{
			//2-4-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-4-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� DiscardTube::complete �����У�\
��⵽ת��ץ�ֶ������س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ת��ץ�ֶ���ʱ������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� DiscardTube::complete �����У�\
��⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}