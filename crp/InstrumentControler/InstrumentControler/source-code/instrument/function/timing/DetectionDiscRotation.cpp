#include"stdafx.h"
#include"DetectionDiscRotation.h"
#include"../../component/Components.h"
#include"../../component/DetectionDisc.h"
#include"../../communication/Command.h"
#include"../../communication/Communications.h"
#include"../../communication/ControlPort.h"
#include"../../Instrument.h"
#include"../../../common/Logs.h"
#include"../../function/Functions.h"
#include"../../function/timing/Timing.h"
#include"../../../export/TestItem.h"
#include<MMSystem.h>

/**
 * name: DetectionDiscRotation
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
DetectionDiscRotation::DetectionDiscRotation(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:Action(id,sub_id,start_time,complete_time)
	,_position(0){
}

/**
 * name: ~DetectionDiscRotation
 * brief: ����������
 * param: --
 * return: --
 */
DetectionDiscRotation::~DetectionDiscRotation(void){
}

/**
 * name: set_position
 * breif: ����λ�á�
 * param: position - �����λ�á�
 * return: --
 */
void DetectionDiscRotation::set_position(const unsigned int position){
	_position=position;
}

/** 
 * name: get_position
 * brief: ��ȡλ�á�
 * param: --
 * return: ����λ�á�
 */
unsigned int DetectionDiscRotation::get_position() const{
	return(_position);
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬
 *         ���򷵻�ֵС���㡣
 */
int DetectionDiscRotation::clear(){
	//1.���û�����Ӧ�����������Ҽ�¼������������
	const int clear_result=Action::clear();
	//2.�����������ʱ����������ֱ�ӷ��ء�
	if(clear_result<0){
		return(-1);
	}
	//3.�������ɹ�����ǰ�������������ǰ����������¼�����ݡ�
	else if(0==clear_result){
		//3-1.�����ǰ�����е����ݡ�
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
int DetectionDiscRotation::reset(){
	//1.���û�����Ӧ�������������жϴ����Ƿ�ɹ���
	if(Action::reset()<0){
		return(-1);
	}
	//2.���õ�ǰ�������ݡ�
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
int DetectionDiscRotation::is_valid() const{
	//1.���û�����Ӧ�����������Ҽ�¼������
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
		//4-1.���λ�÷Ƿ�����ֱ�ӷ��ش���
		if((DetectionDisc::POSITION_ENTRY!=_position)&&(
			DetectionDisc::POSITION_DETECTION!=_position)&&(
			DetectionDisc::POSITION_EXIT!=_position)){
			return(-2);
		}
		//4-2.������ݼ���ɹ�����ֱ�ӳɹ����ء�
		return(0);
	}
	//5.�����ǰΪδ֪�������ֱ�ӷ��ش���
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
int DetectionDiscRotation::execute(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::execute(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� DetectionDiscRotation::execute \
�����У����� Action::execute ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//2-1.������ǰ�������������
		unsigned int hole_no_in_detection_disc=0;
		//2-2.�����ǰ����������ת������λ��
		if(DetectionDisc::POSITION_ENTRY==_position){
			//2-2-1.��ȡ��ǰ������Ͽ��п׺š�
			hole_no_in_detection_disc=(((Instrument::instance())->get_components())->
				get_detection_disc())->get_empty_hole_no();
			//2-2-2.�����ȡ�׺�ʧ�ܣ���ֱ�ӷ��ش���
			if(0==hole_no_in_detection_disc){
				//a.���ô�����롣
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� DetectionDiscRotation::execute \
�����У����� DetectionDisc::get_empty_hole_no ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-2-3.Ϊ��ǰ������Ӧ��Ŀ���ü���̿׺š�
			((((Instrument::instance())->get_functions())->get_timing())->
				get_tested_item(get_test_item_key()))->set_hole_no_in_detection_disc(
				hole_no_in_detection_disc);
		}
		//2-3.�����ǰ����������ת������λ�á�
		else{
			//2-3-1.���õ�ǰ��������Ŀ��ʶ,��ȡ��ǰ��Ŀ��ռ�õĿ׺š�
			hole_no_in_detection_disc=((((Instrument::instance())->get_functions())->
				get_timing())->get_tested_item(get_test_item_key()))->
				get_hole_no_in_detection_disc();
			//2-3-2.�����ȡ�׺�ʧ�ܡ�
			if(0==hole_no_in_detection_disc){
				//a.���ô�����롣
				set_error(ERROR_UNKNOWN);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� DetectionDiscRotation::execute \
�����У����� TestItem::get_hole_no_in_detection_disc ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
					Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-3);
			}
		}
		//2-4.����ָ�����������ת��
		if((((Instrument::instance())->get_components())->
			get_detection_disc())->rotate(hole_no_in_detection_disc,static_cast<
			DetectionDisc::Position>(get_position()))<0){
			//a.���õ�ǰδ֪�����ʶ��
			set_error(ERROR_UNKNOWN);
			//b.��д������־��
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� DetectionDiscRotation::execute \
�����У����� DetectionDisc::rotate ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
				Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
			//c.�������е���ֱ�ӷ��ش���
			return(-4);
		}
		//2-5.��д��־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ����̿�ʼ��ת��"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_EVENT,log);
		//2-6.�������е���ֱ�ӳɹ����ء�
		return(0);
	}
	//3.�����ǰ������������״̬��
	else{
		//3-1.����δ֪�����ʶ��
		set_error(ERROR_UNKNOWN);
		//3-2.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� DetectionDiscRotation::execute \
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
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DetectionDiscRotation::complete(const Status status){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(Action::complete(status)<0){
		//1-1.��д������־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� DetectionDiscRotation::complete \
�����У����� Action::complete ����ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).
			Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�����ǰ����������Ч״̬��
	else if(STATUS_ENABLED==status){
		//2-1.�����ǰ�������ת����ִ����ɡ�
		if(DetectionDisc::FLAG_IDLE==(((Instrument::instance())->
			get_components())->get_detection_disc())->get_rotation_response_flag()){
			//2-1-1.��д��־��
			CString log(_T(""));
			log.Format(_T("Event %s��%ld���� �������ת��ɡ�"),(
				COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_EVENT,log);
			//2-1-2.�������е��˳ɹ����ء�
			return(0);
		}
		//2-2.�����ǰ����̶���ִ����δ��ɡ�
		else{
			//2-2-1.���ӵ�ǰ�������������
			increase_defeats();
			//2-2-2.��⵱ǰ������������Ƿ��ѴＫ�ޡ�
			if(get_defeats()>MAX_DEFEATS){
				//a.���ô����ʶ��
				set_error(ERROR_SERIOUS_TIMEOUT);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Error %s��%ld���� DetectionDiscRotation::complete \
�����У���⵽�������ת���س�ʱ��"),(COleDateTime::GetCurrentTime()).Format(_T(
					"%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_ERROR,log);
				//c.�������е���ֱ�ӷ��ش���
				return(-2);
			}
			//2-2-3.�����ǰ���������δ�ִＫ�ޡ�
			else{
				//a.���ô����ʶ��
				set_error(ERROR_TIMEOUT_T);
				//b.��д������־��
				CString log(_T(""));
				log.Format(_T("Warning %s��%ld���� �������ת������ʱ��"),
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
		log.Format(_T("Error %s��%ld���� DetectionDiscRotation::complete \
�����У���⵽δ֪�Ķ���״̬��"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//3-3.�������е���ֱ�ӷ��ش���
		return(-4);
	}
}