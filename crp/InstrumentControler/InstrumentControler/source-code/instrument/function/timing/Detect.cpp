#include"stdafx.h"
#include"Detect.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/DetectionDisc.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include<MMSystem.h>

/**
 * name: Detect
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
Detect::Detect(const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~Action
 * brief: ����������
 * param: --
 * return: --
 */
Detect::~Detect(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Detect::is_valid() const{
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
int Detect::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Detect::execute �����У�\
���� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.���ͼ������ָ������жϷ����Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_detection_disc())->detect()<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� Detect::execute �����У����� \
DetectionDisc::detect ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ����̿�ʼ��⡣"),
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
		log.Format(_T("Error %s��%ld���� Detect::execute �����У�\
��⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
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
int Detect::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����Detect::complete �����У�\
���� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�������̼����ɡ�
		if(DetectionDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_detection_disc())->
			get_detect_response_flag()){
			//2-1-1.���浱ǰ��⵽�ķ���ֵ��
			((((Instrument::instance())->get_functions())->get_timing())->
				get_tested_item(get_test_item_key()))->set_luminous((((
				Instrument::instance())->get_components())->get_detection_disc())->
				get_luminous());
			//2-1-2.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ����̼����ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-3.�������е��˳ɹ����ء�
			return(0);
		}
		//2-2.�������̼����δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� Detect::complete �����У�\
��⵽����̼�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ����̼��ʱ������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� Detect::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}