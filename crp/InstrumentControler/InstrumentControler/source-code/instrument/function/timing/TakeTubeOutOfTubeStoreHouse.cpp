#include"stdafx.h"
#include"TakeTubeOutOfTubeStoreHouse.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/TubeStorehouse.h"
#include"../../../common/Logs.h"
#include"../../component/LoadTong.h"
#include<MMSystem.h>

/**
 * name: TakeTubeOutOfTubeStoreHouse
 * breif: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
TakeTubeOutOfTubeStoreHouse::TakeTubeOutOfTubeStoreHouse(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time){
}

/**
 * name: ~TakeTubeOutOfTubeStoreHouse
 * brief: ����������
 * param: --
 * return: --
 */
TakeTubeOutOfTubeStoreHouse::~TakeTubeOutOfTubeStoreHouse(void){
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TakeTubeOutOfTubeStoreHouse::is_valid() const{
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
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬����
 */
int TakeTubeOutOfTubeStoreHouse::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����ǰװ��ץ�����йܡ�
		if((((Instrument::instance())->get_components())->
			get_load_tong())->get_having_tube_flag()){
			return(0);
		}
		//2-2.�����ǰ�Թܲ��йܡ�
		else if((((Instrument::instance())->get_components())->
			get_tube_storehouse())->are_there_tubes()){
			//2-2-1.��ȡ��ǰ�Թܲ��Թ�λ����Ϣ�������жϻ�ȡ�Ƿ�ɹ���
			unsigned int row=0;
			unsigned int col=0;
			if((((Instrument::instance())->get_components())->
				get_tube_storehouse())->get_tube_position(row,col)<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::execute \
�����У����� TubeStorehouse::get_tube_position ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-2-2.����װ��ץ��ȡ�ܡ�
			if((((Instrument::instance())->get_components())->
				get_load_tong())->take_tube_out(row,col)<0){
				//a.���õ�ǰδ֪�����ʶ��
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld����TakeTubeOutOfTubeStoreHouse::execute \
�����У����� LoadTong::take_tube_out ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
					_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
			//2-2-3.��д��Ӧ��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� װ��ץ�ֿ�ʼȡ�ܡ�"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-2-4.���װ��ץ��ȡ�ܳɹ�����Ϊ��ǰ�Թּܲ�ȥ�Թܼ�����
			//remark: ֻҪһץ�ˣ�����Ϊ��λ���ϵ��Թ�û���ˡ�
			(((Instrument::instance())->get_components())->
				get_tube_storehouse())->decrease_tube_count();
			//2-2-5.�������е��˳ɹ����ء�
			return(0);
		}
		//2-3.�����ǰ�Թܲ��޹ܡ�
		else{
			//2-3-1.�����Թܲ��޹ܴ���
			set_error(ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE);
			//2-3-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Warning %s��%ld���� װ��ץ��ȡ��ʱ����⵽�Թܲ��޹ܣ�"),
				(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
				timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//2-3-3.�������е���ֱ�ӷ��ش���
			return(-4);
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪����״̬��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::execute \
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
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬����
 */
int TakeTubeOutOfTubeStoreHouse::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е��˷��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	if(STATUS_ENABLED==status){
		//2-1.�����ǰװ��ץ�����йܡ�
		if((((Instrument::instance())->get_components())->
			get_load_tong())->get_having_tube_flag()){
			return(0);
		}
		//2-2.���װ��ץ��ȡ�ܶ�����ɡ�
		else if(LoadTong::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_load_tong())->
			get_take_tube_out_response_flag()){
			//2-2-1.����װ��ץ���й�״̬��
			(((Instrument::instance())->get_components())->
				get_load_tong())->set_having_tube_flag(TRUE);
			//2-2-2.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� װ��ץ��ȡ����ɡ�"),
				(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-2-3.�������е��˳ɹ����ء�
			return(0);
		}
		//2-3.�������ȡ�ܶ�����δ��ɡ�
		else{
			//2-3-1.������ǰ�����Ĵ��������
			increase_defeats();
			//2-3-2.�����ǰ��������Ѵ����ޡ�
			if(get_defeats()>=MAX_DEFEATS){
				//a.���ô�����롣
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::complete \
�����У���⵽װ��ץ��ȡ�����س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-3-3.�����ǰ���������δ�ִ����ޡ�
			else{
				//a.���ô�����롣
				set_error(ERROR_TIMEOUT_T);
				//b.��д�¼���������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� װ��ץ��ȡ�ܷ�����ʱ��"),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
					timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
		}
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.���ô�����롣
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� TakeTubeOutOfTubeStoreHouse::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}