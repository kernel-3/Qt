#include"stdafx.h"
#include"WashingDiscWash.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: WashingDiscWash
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
WashingDiscWash::WashingDiscWash(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_washing_flag(FALSE)
	,_substrate_type(0)
	,_substrate_volume(0){
}

/**
 * name: ~WashingDiscWash
 * brief: ����������
 * param: --
 * return: --
 */
WashingDiscWash::~WashingDiscWash(void){
}

/**
 * name: set_substrate_type
 * brief: ���õ������͡�
 * param: substrate_type - ����ĵ������͡�
 * return: --
 */
void WashingDiscWash::set_substrate_type(const unsigned int substrate_type){
	_substrate_type=substrate_type;
}

/**
 * name: get_substrate_type
 * breif: ��ȡ�������͡�
 * param: --
 * return: ���ص������͡�
 */
unsigned int WashingDiscWash::get_substrate_type() const{
	return(_substrate_type);
}

/**
 * name: set_substrate_volume
 * brief: ���õ��������
 * param: substrate_volume - ����ĵ��������
 * return: --
 */
void WashingDiscWash::set_substrate_volume(const unsigned int substrate_volume){
	_substrate_volume=substrate_volume;
}

/**
 * name: get_substrate_volume
 * brief: ��ȡ���������
 * param: --
 * return: ���ص��������
 */
unsigned int WashingDiscWash::get_substrate_volume() const{
	return(_substrate_volume);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: ������Ե�ǰ������������������ش����������
 *         ����ɹ������ǰ�����������㡣
 *         ��������ǰ����ʧ�ܣ��򷵻�С���������
 */
int WashingDiscWash::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼������������
	const int clear_result=Action::clear();
	//2.�����������ʱ����������ֱ�ӷ��ء�
	if(clear_result<0){
		return(-1);
	}
	//3.�������ɹ�����ǰ�������������ǰ����������¼�����ݡ�
	else if(0==clear_result){
		//3-1.�����ǰ�����е����ݡ�
		_washing_flag=FALSE;
		_substrate_type=0;
		_substrate_volume=0;
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
int WashingDiscWash::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
	_washing_flag=FALSE;
	_substrate_type=0;
	_substrate_volume=0;
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int WashingDiscWash::is_valid() const{
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
		//4-1.����������ͷǷ�����ֱ�ӷ��ش���
		if((WashingDisc::SUBSTRATE_TYPE_AB!=_substrate_type)&&(
			WashingDisc::SUBSTRATE_TYPE_C!=_substrate_type)&&(
			WashingDisc::SUBSTRATE_TYPE_BUFFER_SOLUTION!=_substrate_type)){
			return(-2);
		}
		//4-2.�����ݲ��Ե������������֤��
		//4-3.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰ����ΪĬ�϶������򲻽������ݼ���ֱ�ӷ��ء�
	else if(STATUS_DEFAULT==get_status()){
		return(0);
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
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬������
 */
int WashingDiscWash::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscWash::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	if(STATUS_DEFAULT==status){
		//2-1.�����ϴ����ϴ��ǡ�
		_washing_flag=FALSE;
		//2-2.�����ǰ��ϴ�����޹�,�򲻽����κ�Ĭ����ϴ������ֱ�ӳɹ����ء�
		if(!((((Instrument::instance())->get_components())
			->get_washing_disc())->are_there_tubes())){
			return(0);
		}
		//2-3.�����ǰ��ϴ�����йܣ���������ϴ�̽�����ϴ��
		else{
			//2-3-1.������ϴ����ϴ�������ж���ϴ�Ƿ�ɹ���
			if((((Instrument::instance())->get_components())->
				get_washing_disc())->wash()<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� WashingDiscWash::execute \
�����У����� WashingDisc::wash ����ʧ�ܣ�1����"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-3-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��ϴ�̿�ʼ��ϴ��"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-3-3.������ϴ���Ѿ���ʼ��ϴ��ǡ�
			_washing_flag=TRUE;
			//2-3-4.�������е��˳ɹ����ء�
			return(0);
		}
	}
	//3.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//3-1.������ϴ�̿�ʼ��ϴ�������ж���ϴ�Ƿ�ɹ���
		if((((Instrument::instance())->get_components())->
			get_washing_disc())->wash(static_cast<WashingDisc::
			SubstrateType>(_substrate_type),_substrate_volume)<0){
			//a.���õ�ǰδ֪�����ʶ��
			set_error(ERROR_UNKNOWN);
			//b.��д������־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� WashingDiscWash::execute \
�����У����� WashingDisc::wash ����ʧ�ܣ�2����"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.�������е���ֱ�ӷ��ش���
			return(-3);
		}
		//3-2.�������е��˳ɹ����ء�
		else{
			//3-2-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��ϴ�̿�ʼ��ϴ��"),
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
		log.Format(_T("Error %s��%ld���� WashingDiscWash::execute \
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
int WashingDiscWash::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� WashingDiscWash::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ��������Ĭ��״̬��
	else if(STATUS_DEFAULT==status){
		//2-1.�����ǰ��ϴ�̲�δ��ϴ��
		if(FALSE==_washing_flag){
			return(0);//�������е��ˣ�ֱ�ӳɹ����ء�
		}
		//2-2.�����ǰ��ϴ���Ѿ���ϴ��
		else{
			//2-2-1.�����ǰ��ϴ������ϴ��ִ����ɡ�
			if(WashingDisc::FLAG_IDLE==(((
				Instrument::instance())->get_components())->
				get_washing_disc())->get_wash_response_flag()){
				//a.��д��־��
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� ��ϴ����ϴ��ɡ�"),
					(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				//b.�������е��˳ɹ����ء�
				return(0);
			}
			//2-2-2.�����ǰ��ϴ����ϴ����ִ����δ��ɡ�
			else{
				//2-2-2-1.���ӵ�ǰ�������������
				increase_defeats();
				//2-2-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
				if(get_defeats()>MAX_DEFEATS){
					//a.���ô����ʶ��
					set_error(ERROR_SERIOUS_TIMEOUT);
					//b.��д������־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� WashingDiscWash::complete \
�����У���⵽��ϴ����ϴ���س�ʱ��1����"),(COleDateTime::GetCurrentTime()).Format(_T(
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
					log.Format(_T("Warning %s��%ld���� ��ϴ����ϴ������ʱ��1����"),
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
		//3-1.�����ǰ��ϴ����ϴ����ִ����ɡ�
		if(WashingDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_washing_disc())->
			get_wash_response_flag()){
			//3-1-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� ��ϴ����ϴ��ɡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//3-1-2.�������е��˳ɹ����ء�
			return(0);
		}
		//3-2.�����ǰ��ϴ�̶���ִ����δ��ɡ�
		else{
			//3-2-1.���ӵ�ǰ�������������
			increase_defeats();
			//3-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
			if(get_defeats()>MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� WashingDiscWash::complete \
�����У���⵽��ϴ����ϴ���س�ʱ��2����"),(COleDateTime::GetCurrentTime()).Format(_T(
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
				log.Format(_T("Warning %s��%ld���� ��ϴ����ϴ������ʱ��2����"),
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
		log.Format(_T("Error %s��%ld���� WashingDiscWash::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//4-3.�������е���ֱ�ӷ��ش���
		return(-6);
	}
}