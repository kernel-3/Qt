#include"stdafx.h"
#include"SpecimenDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: SpecimenDisc
 * brief: ���캯����
 * param: --
 * return: --
 */
SpecimenDisc::SpecimenDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_handle_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~SpecimenDisc
 * breif: ����������
 * param: --
 * return: --
 */
SpecimenDisc::~SpecimenDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: ����������ָ�������ϵ�λ����ת������λ��
 * param: rack_no - ������������ϼ��Ӻš�
 *        position_no - �������������λ�úš�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenDisc::rotate(const unsigned int rack_no,
	const unsigned int position_no){
	//1.�������Ĳ����Ƿ�Ϸ���
	if((rack_no<1)||(rack_no>RACK_COUNT)){
		return(-1);
	}
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-2);
	}
	//2.������Ӧ����תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_specimen_disc_rotation_command(
		rack_no,position_no)<0){
		return(-2);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.�����������ת���ֱ���Լ���������ת��ɱ�ǡ�
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��������תָ��"))<0){
		return(-3);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: ������ת���ֱ�־��
 * param: flag - �������ת���ֱ�־��
 * return: --
 */
void SpecimenDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ת���ֱ�־��
	_rotation_shake_handle_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: ��ȡ��ת���ֱ�־��
 * param: --
 * return: ������ת���ֱ�־��
 */
SpecimenDisc::Flag SpecimenDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ת���ֱ�־��
	return(_rotation_shake_handle_flag);
}

/**
 * name: set_rotation_response_flag
 * breif: ������ת�ظ���־��
 * param: --
 * return: --
 */
void SpecimenDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ת�ظ���־��
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: ��ȡ��ת�ظ���־��
 * param: --
 * return: ������ת�ظ���־��
 */
SpecimenDisc::Flag SpecimenDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ת�ظ���־��
	return(_rotation_response_flag);
}