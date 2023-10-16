#include"stdafx.h"
#include"ReagentDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReagentDisc
 * brief: ���캯����
 * param: --
 * return: --
 */
ReagentDisc::ReagentDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~ReagentDisc
 * breif: ����������
 * param: --
 * return: --
 */
ReagentDisc::~ReagentDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: �����Լ�����ת��
 * param: type - ������Լ����͡�
 *        position_no - �����λ�úš�
 * return: �������ִ�гɹ�����ֵ���ڵ�������������򷵻�ֵС���㡣
 */
int ReagentDisc::rotate(const ReagentType type,const unsigned int position_no){
	//1.��������Ƿ�Ϸ���
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-1);
	}
	//2.�����Լ�����תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_reagent_disc_rotation_command(
		static_cast<unsigned int>(type),position_no)<0){
		return(-2);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.����Լ�����ת���ֱ���Լ��Լ�����ת��ɱ�ǡ�
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("�Լ�����תָ��"))<0){
		return(-3);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: �����Լ�����ת���ֱ�־��
 * param: flag - ������Լ�����ת���ֱ�־��
 * return: --
 */
void ReagentDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����Լ�����ת���ֱ�־��
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * breif: ��ȡ�Լ�����ת���ֱ�־��
 * param: --
 * return: �����Լ�����ת���ֱ�־��
 */
ReagentDisc::Flag ReagentDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����Լ�����ת���ֱ�־��
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: �����Լ�����ת�ظ���־��
 * param: flag - ������Լ�����ת�ظ���־��
 * return: --
 */
void ReagentDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����Լ�����ת�ظ���־��
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: ��ȡ�Լ�����ת�ظ���־��
 * param: --
 * return: �����Լ�����ת�ظ���־��
 */
ReagentDisc::Flag ReagentDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����Լ�����ת�ظ���־��
	return(_rotation_response_flag);
}