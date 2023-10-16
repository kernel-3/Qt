#include"stdafx.h"
#include"MagneticBeadDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: MagneticBeadDisc
 * brief: ���캯����
 * param: --
 * return: --
 */
MagneticBeadDisc::MagneticBeadDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_mixing_rotation_shake_hand_flag(FLAG_IDLE)
	,_mixing_rotation_response_flag(FLAG_IDLE){
}

/**
 * name: ~MagneticBeadDisc
 * brief: ����������
 * param: --
 * return: --
 */
MagneticBeadDisc::~MagneticBeadDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: �����������ת��
 * param: position_no - �����λ�úš�
 * return: �������ִ�гɹ�����ֵ���ڵ�������������򷵻�ֵС���㡣
 */
int MagneticBeadDisc::rotate(const unsigned int position_no){
	//1.��������Ƿ�Ϸ���
	if((position_no<1)||(position_no>POSITION_COUNT)){
		return(-1);
	}
	//2.������������תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_magnetic_bead_disc_rotation_command(
		position_no)<0){
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
 * name: mix_rotate
 * brief: ��������̻�����ת��
 * param: direction - �����ת������
 * return: �������ִ�гɹ�����ֵ���ڵ�������������򷵻�ֵС���㡣
 */
int MagneticBeadDisc::mix_rotate(const Direction direction){
	//1.���������̻�����תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_magnetic_bead_disc_mixing_rotation_command(
		static_cast<unsigned int>(direction))<0){
		return(-1);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.��������̻�����ת���ֱ���Լ������̻�����ת�ظ���ǡ�
	set_mixing_rotation_shake_hand_flag(FLAG_BUSY);
	set_mixing_rotation_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("�����̻�����תָ��"))<0){
		return(-2);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: ���ô�������ת���ֱ�־��
 * param: flag - ����Ĵ�������ת���ֱ�־��
 * return: --
 */
void MagneticBeadDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô�������ת���ֱ�־��
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * breif: ��ȡ��������ת���ֱ�־��
 * param: --
 * return: ���ش�������ת���ֱ�־��
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش�������ת���ֱ�־��
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: ���ô�������ת�ظ���־��
 * param: flag - ����Ĵ�������ת�ظ���־��
 * return: --
 */
void MagneticBeadDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô�������ת�ظ���־��
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * breif: ��ȡ��������ת�ظ���־��
 * param: --
 * return: ���ش�������ת�ظ���־��
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش�������ת�ظ���־��
	return(_rotation_response_flag);
}

/**
 * name: set_mixing_rotation_shake_hand_flag
 * brief: ���ô����̻�����ת���ֱ�־��
 * param: flag - ����Ĵ����̻�����ת���ֱ�־��
 * return: --
 */
void MagneticBeadDisc::set_mixing_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô��������������ֱ�־��
	_mixing_rotation_shake_hand_flag=flag;
}

/** 
 * name: get_mixing_rotation_shake_hand_flag
 * brief: ��ȡ�����̻�����ת���ֱ�־��
 * param: --
 * return: ���ش����̻�����ת���ֱ�־��
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_mixing_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش����̻�����ת���ֱ�־��
	return(_mixing_rotation_shake_hand_flag);
}

/**
 * name: set_mixing_rotation_response_flag
 * breif: ���ô����̻�����ת�ظ���־��
 * param: flag - ����Ĵ����̻�����ת�ظ���־��
 * return: --
 */
void MagneticBeadDisc::set_mixing_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô����̻�����ת�ظ���־��
	_mixing_rotation_response_flag=flag;
}

/**
 * name: get_mixing_rotation_response_flag
 * breif: ��ȡ�����̻�����ת�ظ���־��
 * param: --
 * return: ���ش����̻�����ת�ظ���־��
 */
MagneticBeadDisc::Flag MagneticBeadDisc::get_mixing_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش����̻�����ת�ظ���־��
	return(_mixing_rotation_response_flag);
}