#include"stdafx.h"
#include"MagneticBeadDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/MagneticBeadDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

//���徲̬������
unsigned int MagneticBeadDiscRotation::_direction=MagneticBeadDisc::DIRECTION_NEGATIVE;

/**
 * name: MagneticBeadDiscRotation
 * breif: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
MagneticBeadDiscRotation::
	MagneticBeadDiscRotation(	
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_rotation_flag(FALSE)
	,_position_no(0){
}

/**
 * name: ~MagneticBeadDiscRotation
 * brief: ����������
 * param: --
 * return: --
 */
MagneticBeadDiscRotation::
	~MagneticBeadDiscRotation(void){
}

/**
 * name: set_position_no
 * brief: ����λ�úš�
 * param: position_no - �����λ�úš�
 * return: --
 */
void MagneticBeadDiscRotation::set_position_no(
	const int position_no){
	_position_no=position_no;
}

/**
 * name: get_position_no
 * brief: ��ȡλ�úš�
 * param: --
 * return: ����λ�úš�
 */
int MagneticBeadDiscRotation::get_position_no() const{
	return(_position_no);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int MagneticBeadDiscRotation::clear(){
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
int MagneticBeadDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_rotation_flag=FALSE;
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
int MagneticBeadDiscRotation::is_valid() const{
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
		//4-1.���λ�úŷǷ���
		if((_position_no<1)||(_position_no>
			MagneticBeadDisc::POSITION_COUNT)){
			return(-2);
		}
		//4-2.������ݼ���ɹ�����ֱ�ӳɹ����ء�
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
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MagneticBeadDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	if(STATUS_DEFAULT==status){
		//2-1.�����������ת��ǡ�
		_rotation_flag=FALSE;
		//2-2.�����ǰ���������޴���,�򲻽����κ�Ĭ��ת����ֱ�ӳɹ����ء�
		if(0/*unfinished: �����������Ƿ��д���*/){
			return(0);
		}
		//2-3.�����ǰ�����������Լ����������������ת���б������ȡ�
		else{
			//2-3-1.���ݵ�ǰ��ת�����ʶ�����������Ӧ����ת�ķ���
			if(_direction==MagneticBeadDisc::DIRECTION_NEGATIVE){
				_direction=MagneticBeadDisc::DIRECTION_POSITIVE;
			}else{
				_direction=MagneticBeadDisc::DIRECTION_NEGATIVE;
			}
			//2-3-2.��������̻�����ת�������ж���ת�Ƿ�ɹ���
			if((((Instrument::instance())->get_components())->
				get_magnetic_bead_disc())->mix_rotate(static_cast<
				MagneticBeadDisc::Direction>(_direction))<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::execute \
�����У����� MagneticBeadDisc::mix_rotate ����ʧ�ܣ�"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-3-3.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� �����̿�ʼ������ת��"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-4.���ô������Ѿ���ʼ��ת��ǡ�
			_rotation_flag=TRUE;
			//2-3-5.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//3.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//3-1.���������ת�������ж���ת�Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->rotate(_position_no)<0){
			//a.���õ�ǰδ֪�����ʶ��
			set_error(ERROR_UNKNOWN);
			//b.��д������־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::execute \
�����У����� MagneticBeadDisc::rotate ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.�������е���ֱ�ӷ��ش���
			return(-3);
		}
		//3-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �����̿�ʼ��ת��"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
	//4.�����ǰ������������״̬��
	else{
		//4-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//4-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::execute \
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
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MagneticBeadDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	else if(STATUS_DEFAULT==status){
		//2-1.�����ǰ�����̲�δ������ת��
		if(FALSE==_rotation_flag){
			return(0);//�������е��ˣ�ֱ�ӳɹ����ء�
		}
		//2-2.�����ǰ�������Ѿ���ʼ������ת��
		else{
			//2-2-1.�����ǰ�����̻�����ת����ִ����ɡ�
			if(MagneticBeadDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_magnetic_bead_disc())->get_mixing_rotation_response_flag()){
				//a.��д��־��
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� �����̻�����ת��ɡ�"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
					log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::complete \
�����У���⵽�����̻�����ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s��%ld���� �����̻�����ת������ʱ��"),(
						COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
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
		//3-1.�����ǰ��������ת����ִ����ɡ�
		if(MagneticBeadDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_magnetic_bead_disc())->
			get_rotation_response_flag()){
			//3-1-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��������ת��ɡ�"),(COleDateTime::
				GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.�������е��˳ɹ����ء�
			return(0);
		}
		//3-2.�����ǰ��������ת����ִ����δ��ɡ�
		else{
			//3-2-1.���ӵ�ǰ�������������
			increase_defeats();
			//3-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
			if(get_defeats()>MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::complete \
�����У���⵽��������ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ��������ת������ʱ��"),(COleDateTime::
					GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
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
		log.Format(_T("Error %s��%ld���� MagneticBeadDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.�������е���ֱ�ӷ��ش���
		return(-6);
	}
}