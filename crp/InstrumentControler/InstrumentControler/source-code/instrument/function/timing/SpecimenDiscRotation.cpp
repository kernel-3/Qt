#include"stdafx.h"
#include"SpecimenDiscRotation.h"
#include"../../component/SpecimenDisc.h"
#include"../../../common/Logs.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/SpecimenDisc.h"
#include<MMSystem.h>

/**
 * name: SpecimenDiscRotation
 * breif: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
SpecimenDiscRotation::SpecimenDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rack_no(0)
	,_position_no(0){
}

/**
 * name: ~SpecimenDiscRotation
 * breif: ����������
 * param: --
 * return: --
 */
SpecimenDiscRotation::~SpecimenDiscRotation(void){
}

/**
 * name: set_rack_no
 * breif: ���ü��Ӻš�
 * param: rack_no - ����ļ��Ӻš�
 * return: --
 */
void SpecimenDiscRotation::set_rack_no(
	const unsigned int rack_no){
	_rack_no=rack_no;
}

/**
 * name: get_rack_no
 * breif: ��ȡ���Ӻš�
 * param: --
 * return: ���ؼ��Ӻš�
 */
unsigned int SpecimenDiscRotation::get_rack_no() const{
	return(_rack_no);
}

/**
 * name: set_position_no
 * brief: ����λ�úš�
 * param: position_no - �����λ�úš�
 * return: --
 */
void SpecimenDiscRotation::set_position_no(
	const unsigned int position_no){
	_position_no=position_no;
}

/**
 * name: get_position_no
 * brief: ��ȡλ�úš�
 * param: --
 * return: ����λ�úš�
 */
unsigned int SpecimenDiscRotation::get_position_no() const{
	return(_position_no);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �������Ҫִ������������򷵻ش����������
 *         �������ɹ������㡣
 *         ������ʧ���򷵻�С���������
 */
int SpecimenDiscRotation::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼��������
	const int clear_result=Action::clear();
	//2.�����ǰ�������ʧ����ֱ�ӷ��ش���
	if(clear_result<0){
		return(-1);
	}
	//3.�����ǰ��������ɹ���������������ݡ�
	else if(0==clear_result){
		_rack_no=0;
		_position_no=0;
		return(0);
	}
	//4.�����ǰ�����������������
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
int SpecimenDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_rack_no=0;
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
int SpecimenDiscRotation::is_valid() const{
	//1.���û�����Ӧ����������ֱ�ӷ�����Ӧ����
	if(Action::is_valid()<0){
		return(-1);
	}
	//2.�����ǰ����Ϊ��Ч�������򲻽������ݼ���ֱ�ӷ��ء�
	if(STATUS_DISABLED==get_status()){
		return(0);
	}
	//3.�����ǰ����Ϊ��Ч��������������ݼ��飬�����жϼ����Ƿ�Ϸ���
	else if(STATUS_ENABLED==get_status()){
		//3-1.�����λ�÷Ƿ�����ֱ�ӷ��ش���
		if((_rack_no<1)||(_rack_no>
			SpecimenDisc::RACK_COUNT)){
			return(-2);
		}
		//3-2.�����λ�÷Ƿ�����ֱ�ӷ��ش���
		if((_position_no<1)||(_position_no>
			SpecimenDisc::POSITION_COUNT)){
			return(-3);
		}
		//3-3.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//4.�����ǰ����ΪĬ�϶�������ֱ�ӷ��ش���
	else if(STATUS_DEFAULT==get_status()){
		return(-4);//�˶�����֧��Ĭ��״̬��
	}
	//5.�����ǰΪδ֪�������ֱ�ӷ��ش���
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
int SpecimenDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-1.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.����ָ��������������ת��
		if((((Instrument::instance())->get_components())->
			get_specimen_disc())->rotate(_rack_no,_position_no)<0){
			//a.���õ�ǰδ֪�����ʶ��
			set_error(ERROR_UNKNOWN);
			//b.��д������־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::execute \
�����У����� SpecimenDisc::rotate ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.�������е���ֱ�ӷ��ش���
			return(-2);
		}
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �����̿�ʼ��ת��"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
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
		log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::execute \
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
int SpecimenDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����������ת��ɣ���ɹ����ء�
		if(SpecimenDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_specimen_disc())->
			get_rotation_response_flag()){
			//2-1-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��������ת��ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.�������е���ֱ�ӳɹ����ء�
			return(0);
		}
		//2-2.�����������ת��δ��ɡ�
		else{
			//2-2-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-2-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::complete \
�����У���⵽��������ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ��������ת������ʱ��"),
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
		//3-1.���ô����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� SpecimenDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}