#include"stdafx.h"
#include"WashingDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: WashingDiscRotation
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
WashingDiscRotation::WashingDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE){
}

/**
 * name: ~WashingDiscRotation
 * brief: ����������
 * param: --
 * return: --
 */
WashingDiscRotation::~WashingDiscRotation(void){
}

/**
 * name: reset
 * breif: ���õ�ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int WashingDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_rotation_flag=FALSE;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int WashingDiscRotation::is_valid() const{
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int result=Action::is_valid();
	//2.���������Ӧ������ʧ�ܣ���ֱ�ӷ�����Ӧ����
	if(result<0){
		return(-1);
	}
	//3.�����ǰ����Ϊ��Ч��������ֱ�ӷ��ش���
	if(STATUS_DISABLED==get_status()){
		return(-2);
	}
	//4.�����ǰ����Ϊ��Ч��������ֱ�ӷ��ش���
	else if(STATUS_ENABLED==get_status()){
		return(-3);
	}
	//5.�����ǰ����ΪĬ�϶�������ɹ����ء�
	else if(STATUS_DEFAULT==get_status()){
		return(0);
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
int WashingDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	if(STATUS_DEFAULT==status){
		//2-1.�����ϴ����ת��ǡ�
		_rotation_flag=FALSE;
		//2-2.�����ǰ��ϴ�����޹�,�򲻽����κ���ת��ֱ�ӳɹ����ء�
		if(!((((Instrument::instance())->get_components())
			->get_washing_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.�����ǰ��ϴ�����йܣ���������ϴ����ת��
		else{
			//2-3-1.������ϴ����ת�������ж���ת�Ƿ�ɹ���
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->rotate()<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� WashingDiscRotation::execute \
�����У����� WashingDisc::rotate ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-3-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��ϴ�̿�ʼ��ת��"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-3.������ϴ���Ѿ���ʼ��ת��ǡ�
			_rotation_flag=TRUE;
			//2-3-4.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscRotation::execute \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
int WashingDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	else if(STATUS_DEFAULT==status){
		//2-1.�����ǰ��ϴ�̲�δ��ת��
		if(FALSE==_rotation_flag){
			return(0);//�������е��ˣ�ֱ�ӳɹ����ء�
		}
		//2-2.�����ǰ��ϴ���Ѿ���ת��
		else{
			//2-2-1.�����ǰ��ϴ����ת����ִ����ɡ�
			if(WashingDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_washing_disc())->get_rotation_response_flag()){
				//a.��ϴ��ת����ɺ󣬵�������λ�׺š�
				(((Instrument::instance())->get_components())->
					get_washing_disc())->decrease_hole_no_in_entry();
				//b.��д��־��
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� ��ϴ����ת��ɡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//c.�������е��˳ɹ����ء�
				return(0);
			}
			//2-2-2.�����ǰ��ϴ�̶���ִ����δ��ɡ�
			else{
				//2-2-2-1.���ӵ�ǰ�������������
				increase_defeats();
				//2-2-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
				if(get_defeats()>MAX_DEFEATS){
					//a.���ô����ʶ��
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.��д������־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� WashingDiscRotation::complete \
�����У���⵽��ϴ����ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
						"%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c.�������е���ֱ�ӷ��ش���
					return(-2);
				}
				//2-2-2-3.�����ǰ���������δ�ִＫ�ޡ�
				else{
					//a.���ô����ʶ��
					set_error(ERROR_TIMEOUT_T);
					//b.��д������־��
					CString log(_T(""));
					log.Format(_T("Warning %s��%ld���� ��ϴ����ת������ʱ��"),
						(COleDateTime::GetCurrentTime()).Format(
						_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
					Logs::instance()->write(Logs::NAME_EVENT,log);
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c.�������е���ֱ�ӷ��ش���
					return(-3);
				}
			}
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.���ô����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}