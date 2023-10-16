#include"stdafx.h"
#include"ReagentDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/ReagentDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReagentDiscRotation
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
ReagentDiscRotation::ReagentDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_reagent_type(0)
	,_position_no(0){
}

/**
 * name: ~ReagentDiscRotation
 * breif: ����������
 * param: --
 * return: --
 */
ReagentDiscRotation::~ReagentDiscRotation(void){
}

/**
 * name: set_reagent_type
 * brief: �����Լ����͡�
 * param: reagent_type - ������Լ����͡�
 * return: --
 */
void ReagentDiscRotation::set_reagent_type(
	const unsigned int reagent_type){
	_reagent_type=reagent_type;
}

/**
 * name: get_reagent_type
 * breif: ��ȡ�Լ����͡�
 * param: --
 * return: �����Լ����͡�
 */
unsigned int ReagentDiscRotation::get_reagent_type() const{
	return(_reagent_type);
}

/**
 * name: set_position_no
 * breif: ����λ�úš�
 * param: position_no - �����λ�úš�
 * return: --
 */
void ReagentDiscRotation::set_position_no(
	const unsigned int position_no){
	_position_no=position_no;
}

/**
 * name: get_position_no
 * brief: ��ȡλ�úš�
 * param: --
 * return: ����λ�úš�
 */
unsigned int ReagentDiscRotation::get_position_no() const{
	return(_position_no);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int ReagentDiscRotation::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼������������
	const int clear_result=Action::clear();
	//2.�����������ʱ����������ֱ�ӷ��ء�
	if(clear_result<0){
		return(-1);
	}
	//3.�������ɹ�����ǰ�������������ǰ����������¼�����ݡ�
	else if(0==clear_result){
		//3-1.�����ǰ�����е����ݡ�
		_reagent_type=0;
		_position_no=0;
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
int ReagentDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_reagent_type=0;
	_position_no=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentDiscRotation::is_valid() const{
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
		//4-1.����Լ����ͷǷ���
		if((ReagentDisc::REAGENT_TYPE_R1!=_reagent_type)&&
			(ReagentDisc::REAGENT_TYPE_R2!=_reagent_type)){
			return(-2);
		}
		//4-2.���λ�úŷǷ���
		if((_position_no<=0)||(_position_no>
			ReagentDisc::POSITION_COUNT)){
			return(-3);
		}
		//4-3.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ش���
	else if(STATUS_DEFAULT==get_status()){
		return(-4);//�˶�����֧��Ĭ�϶�����
	}
	//6.�����ǰΪδ֪�������ֱ�ӷ��ش���
	else{
		return(-5);
	}
}

/**
 * name: execute
 * breif: ִ�е�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����Լ�����תָ�
		if((((Instrument::instance())->get_components())->
			get_reagent_disc())->rotate(static_cast<
			ReagentDisc::ReagentType>(_reagent_type),_position_no)<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� ReagentDiscRotation::execute \
�����У����� ReagentDisc::rotate ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �Լ��̿�ʼ��ת��"),
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
		log.Format(_T("Error %s��%ld���� ReagentDiscRotation::execute \
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
int ReagentDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
		  Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.����Լ�����ת��ɡ�
		if(ReagentDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_reagent_disc())->
			get_rotation_response_flag()){
			//2-1-1.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� �Լ�����ת�ɹ���ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-2.����Լ�����ת��δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReagentDiscRotation::complete \
�����У���⵽�Լ�����ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� �Լ�����תʱ������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� ReagentDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}