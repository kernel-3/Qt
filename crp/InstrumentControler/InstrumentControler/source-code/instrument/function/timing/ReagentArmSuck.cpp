#include"stdafx.h"
#include"ReagentArmSuck.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/ReagentArm.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReagentArmSuck
 * breif: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
ReagentArmSuck::ReagentArmSuck(		
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_suck_volume(0)
	,_reagent_type(0){
}

/**
 * name: ~ReagentArmSuck
 * breif: ����������
 * param: --
 * return: --
 */
ReagentArmSuck::~ReagentArmSuck(void){
}

/**
 * name: set_suck_volume
 * brief: ������ȡ�����
 * param: volume - �������ȡ�����
 * return: --
 */
void ReagentArmSuck::set_suck_volume(const unsigned int volume){
	_suck_volume=volume;
}

/**
 * name: get_suck_volume
 * brief: ��ȡ��ȡ�����
 * param: --
 * return: ������ȡ�����
 */
unsigned int ReagentArmSuck::get_suck_volume() const{
	return(_suck_volume);
}

/**
 * name: set_reagent_type
 * brief: �����Լ����͡�
 * param: type - ������Լ����͡�
 * return: --
 */
void ReagentArmSuck::set_reagent_type(const unsigned int type){
	_reagent_type=type;
}

/**
 * name: get_reagent_type
 * breif: ��ȡ�Լ����͡�
 * param: --
 * return: �����Լ����͡�
 */
unsigned int ReagentArmSuck::get_reagent_type() const{
	return(_reagent_type);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int ReagentArmSuck::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int clear_result=Action::clear();
	//2.���������Ӧ����������ʧ�ܡ�
	if(clear_result<0){
		return(-1);
	}
	//3.���������Ӧ����������ɹ���
	else if(0==clear_result){
		_suck_volume=0;
		_reagent_type=0;
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
int ReagentArmSuck::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_suck_volume=0;
	_reagent_type=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReagentArmSuck::is_valid() const{
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
		//4-1.��⵱ǰ�����Ƿ�Ϸ���
		if((ReagentArm::REAGENT_TYPE_R1!=_reagent_type)&&
			(ReagentArm::REAGENT_TYPE_R2!=_reagent_type)&&
			(ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_1!=_reagent_type)&&
			(ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_2!=_reagent_type)){
			return(-2);
		}
		//4-2.�������е��ˣ�ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ش���
	else if(STATUS_DEFAULT==get_status()){
		return(-3);//�˶�����֧��Ĭ�϶�����
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
int ReagentArmSuck::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSuck::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����Լ������Լ���
		if((((Instrument::instance())->get_components())->
			get_reagent_arm())->suck(_suck_volume,static_cast<
			ReagentArm::ReagentType>(_reagent_type),TRUE)<0){
			//2-1-1.���ô�����롣
			set_error(ERROR_UNKNOWN);
			//2-1-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� ReagentArmSuck::execute \
�����У����� ReagentArm::suck ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-1-3.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �Լ��ۿ�ʼ��Һ��"),
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
		log.Format(_T("Error %s��%ld���� ReagentArmSuck::execute \
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
int ReagentArmSuck::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReagentArmSuck::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.������Լ������Ѿ��ɹ���ɡ�
		if(ReagentArm::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_reagent_arm())->
			get_suck_response_flag()){
			//2-1-1.�������Լ��߶ȣ��������Լ�������
			//unfinished: �������Լ��߶ȣ��������Լ�������
			//2-1-2.�����־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� �Լ�����Һ�ɹ���ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(
				_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-3.�������е��˳ɹ����ء�
			return(0);
		}
		//2-2.������Լ���δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReagentArmSuck::complete \
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
		log.Format(_T("Error %s��%ld���� ReagentArmSuck::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}