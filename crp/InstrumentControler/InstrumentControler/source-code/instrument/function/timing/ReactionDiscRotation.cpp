#include"stdafx.h"
#include"ReactionDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/ReactionDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

//��̬������ʼ����
ReactionDiscRotation::Direction ReactionDiscRotation::
	_rotation_direction=ReactionDiscRotation::DIRECTION_POSITIVE;

/**
 * name: ReactionDiscRotation
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
ReactionDiscRotation::ReactionDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE)
	,_hole_no(0)
	,_position(0){
}

/**
 * name: ~ReactionDiscRotation
 * brief: ����������
 * param: --
 * return: --
 */
ReactionDiscRotation::~ReactionDiscRotation(void){
}

/**
 * name: set_hole_no
 * brief: ���÷�Ӧ���ϵĶ��š�
 * param: hole_no - ����ķ�Ӧ���ϵĶ��š�
 * return: --
 */
void ReactionDiscRotation::set_hole_no(const unsigned int hole_no){
	_hole_no=hole_no;
}

/**
 * name: get_hole_no
 * breif: ��ȡ��ǰ��Ӧ���ϵĶ��š�
 * param: --
 * return: ��Ӧ��ǰ��Ӧ���ϵĶ��š�
 */
unsigned int ReactionDiscRotation::get_hole_no() const{
	return(_hole_no);
}

/**
 * name: set_position
 * brief: ���÷�Ӧ���ϵ�λ�á�
 * param: position - ����ķ�Ӧ���ϵ�λ�á�
 * return: --
 */
void ReactionDiscRotation::set_position(const unsigned int position){
	_position=position;
}

/**
 * name: get_position
 * brief: ��ȡ��Ӧ���ϵ�λ�á�
 * param: --
 * return: ���ط�Ӧ���ϵ�λ�á�
 */
unsigned int ReactionDiscRotation::get_position() const{
	return(_position);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: ������Ե�ǰ������������������ش����������
 *         ����ɹ������ǰ�����������㡣
 *         ��������ǰ����ʧ�ܣ��򷵻�С���������
 */
int ReactionDiscRotation::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼������������
	const int clear_result=Action::clear();
	//2.�����������ʱ����������ֱ�ӷ��ء�
	if(clear_result<0){
		return(-1);
	}
	//3.�������ɹ�����ǰ�������������ǰ����������¼�����ݡ�
	else if(0==clear_result){
		//3-1.�����ǰ�����е����ݡ�
		_rotation_flag=FALSE;
		_hole_no=0;
		_position=0;
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
int ReactionDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_rotation_flag=FALSE;
	_hole_no=0;
	_position=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReactionDiscRotation::is_valid() const{
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
		//4-1.�����Ӧ���϶��ŷǷ�����ֱ�ӷ��ش���
		if((_hole_no<1)||(_hole_no>ReactionDisc::HOLE_COUNT)){
			return(-2);
		}
		//4-2.�����Ӧ��λ�÷Ƿ�����ֱ�ӷ��ش���
		if((ReactionDisc::POSITION_ADD_SPECIMEN!=_position)&&(
			ReactionDisc::POSITION_ADD_REAGENT!=_position)&&(
			ReactionDisc::POSITION_ENTRY!=_position)&&(
			ReactionDisc::POSITION_EXIT!=_position)){
			return(-3);
		}
		//4-3.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ء�
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
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬������
 */
int ReactionDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReactionDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	if(STATUS_DEFAULT==status){
		//2-1.�����Ӧ����ת��ǡ�
		_rotation_flag=FALSE;
		//2-2.�����ǰ��Ӧ�����޹�,�򲻽����κ�Ĭ��ת����ֱ�ӳɹ����ء�
		if(!((((Instrument::instance())->get_components())
			->get_reaction_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.�����ǰ��Ӧ�����йܣ������Ӧ����ת���б������ȡ�
		else{
			//2-3-1.���ݵ�ǰ��ת������ʶ�����㷴Ӧ��Ӧ����ת��λ�á�
			ReactionDisc::Position position=ReactionDisc::POSITION_EXIT;
			if(DIRECTION_NEGATIVE==_rotation_direction){
				position=ReactionDisc::POSITION_ADD_SPECIMEN;
			}
			//2-3-2.���Ӧ����ת�������ж���ת�Ƿ�ɹ���
			if((((Instrument::instance())->get_components())->
				get_reaction_disc())->rotate(1,position)<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReactionDiscRotation::execute \
�����У����� ReactionDisc::rotate ����ʧ�ܣ�1����"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-3-3.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��Ӧ�̿�ʼ��ת��"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-4.���÷�Ӧ����ת��־��
			if(DIRECTION_POSITIVE==_rotation_direction){
				_rotation_direction=DIRECTION_NEGATIVE;
			}else{
				_rotation_direction=DIRECTION_POSITIVE;
			}
			//2-3-5.���÷�Ӧ���Ѿ���ʼ��ת��ǡ�
			_rotation_flag=TRUE;
			//2-3-6.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//3.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//3-1.���Ӧ����ת�������ж���ת�Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_reaction_disc())->rotate(_hole_no,static_cast<
			ReactionDisc::Position>(_position))<0){
			//a.���õ�ǰδ֪�����ʶ��
			set_error(ERROR_UNKNOWN);
			//b.��д������־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� ReactionDiscRotation::execute \
�����У����� ReactionDisc::rotate ����ʧ�ܣ�2����"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.�������е���ֱ�ӷ��ش���
			return(-3);
		}
		//3-2.�������е��˳ɹ����ء�
		else{
			//3-2-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��Ӧ�̿�ʼ��ת��"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-2-2.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//4.�����ǰ������������״̬��
	else{
		//4-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//4-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReactionDiscRotation::execute \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}

/**
 * name: complete
 * brief: ��ɵ�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬������
 */
int ReactionDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReactionDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	else if(STATUS_DEFAULT==status){
		//2-1.�����ǰ��Ӧ�̲�δ��ת��
		if(FALSE==_rotation_flag){
			return(0);//�������е��ˣ�ֱ�ӳɹ����ء�
		}
		//2-2.�����ǰ��Ӧ���Ѿ���ת��
		else{
			//2-2-1.�����ǰ��Ӧ����ת����ִ����ɡ�
			if(ReactionDisc::FLAG_IDLE==(((Instrument::instance())->
				get_components())->get_reaction_disc())->
				get_rotation_response_flag()){
				//a.��д��־��
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� ��Ӧ����ת��ɡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//b.�������е��˳ɹ����ء�
				return(0);
			}
			//2-2-2.�����ǰ��Ӧ�̶���ִ����δ��ɡ�
			else{
				//2-2-2-1.���ӵ�ǰ�������������
				increase_defeats();
				//2-2-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
				if(get_defeats()>MAX_DEFEATS){
					//a.���ô����ʶ��
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.��д������־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� ReactionDiscRotation::complete \
�����У���⵽��Ӧ����ת���س�ʱ��1����"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s��%ld���� ��Ӧ����ת������ʱ��1����"),
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
	//3.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//3-1.�����ǰ��Ӧ����ת����ִ����ɡ�
		if(ReactionDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_reaction_disc())->
			get_rotation_response_flag()){
			//3-1-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��Ӧ����ת��ɡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.�������е��˳ɹ����ء�
			return(0);
		}
		//3-2.�����ǰ��Ӧ�̶���ִ����δ��ɡ�
		else{
			//3-2-1.���ӵ�ǰ�������������
			increase_defeats();
			//3-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
			if(get_defeats()>MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� ReactionDiscRotation::complete \
�����У���⵽��Ӧ����ת���س�ʱ��2����"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-4);
			}
			//3-2-3.�����ǰ���������δ�ִＫ�ޡ�
			else{
				//a.���ô����ʶ��
				set_error(ERROR_TIMEOUT_T);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� ��Ӧ����ת������ʱ��2����"),
					(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-5);
			}
		}
	}
	//4.�����ǰ������������״̬��
	else{
		//4-1.���ô����ʶ��
		set_error(ERROR_UNKNOWN);
		//4-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� ReactionDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.�������е���ֱ�ӷ��ش���
		return(-6);
	}
}