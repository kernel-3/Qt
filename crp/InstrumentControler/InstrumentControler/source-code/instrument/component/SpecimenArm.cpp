#include"stdafx.h"
#include"SpecimenArm.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include"../../common/Inis.h"
#include<MMSystem.h>

/**
 * name: SpecimenArm
 * brief: ���캯����
 * param: --
 * return: --
 */
SpecimenArm::SpecimenArm(void)
	:_lock(new MtLock)
	,_suck_shake_hand_flag(FLAG_IDLE)
	,_suck_response_flag(FLAG_IDLE)
	,_liquid_level_height(0)
	,_spit_shake_hand_flag(FLAG_IDLE)
	,_spit_response_flag(FLAG_IDLE)
	,_wash_shake_hand_flag(FLAG_IDLE)
	,_wash_response_flags(FLAG_IDLE){
}

/**
 * name: ~SpecimenArm
 * brief: ����������
 * param: --
 * return: --
 */
SpecimenArm::~SpecimenArm(void){
	delete _lock;
}

/**
 * name: suck
 * brief: ������������Һ��
 * param: suck_volume - �������ȡ�������λ��΢������
 *        cup_type - ��������������͡�
 *        liquid_level_probe_switch - �����Һλ̽�⿪�ء�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenArm::suck(const unsigned int suck_volume,
	const CupType cup_type,const BOOL liquid_level_probe_switch/*=TRUE*/){
	//1.������������Һָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_specimen_arm_suck_command(
		suck_volume,static_cast<unsigned int>(cup_type),
		liquid_level_probe_switch)<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�����������Һ���ֱ���Լ���������Һ�ظ���ǡ�
	set_suck_shake_hand_flag(FLAG_BUSY);
	set_suck_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��������Һָ��"))<0){
		return(-2);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: spit
 * brief: ������������Һ��
 * param: spit_volume - �������Һ�����
 *        down_steps - ������������½�������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenArm::spit(const unsigned int spit_volume,const unsigned int down_steps){
	//1.������������Һָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_specimen_arm_spit_command(
		spit_volume,down_steps)<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�����������Һ���ֱ���Լ���������Һ�ظ���ǡ�
	set_spit_shake_hand_flag(FLAG_BUSY);
	set_spit_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��������Һָ��"))<0){
		return(-2);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: wash
 * brief: ������������ϴ��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int SpecimenArm::wash(){
	//1.������������ϴָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_specimen_arm_wash_command(
		get_outer_wash_time(),get_inner_wash_time())<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�����������ϴ���ֱ���Լ���������ϴ�ظ���ǡ�
	set_wash_shake_hand_flag(FLAG_BUSY);
	set_wash_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��������ϴָ��"))<0){
		return(-2);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_suck_shake_hand_flag
 * breif: ������ȡ���ֱ�־��
 * param: flag - �������ȡ���ֱ�־��
 * return: --
 */
void SpecimenArm::set_suck_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ȡ���ֱ�־��
	_suck_shake_hand_flag=flag;
}

/**
 * name: get_suck_shake_hand_flag
 * breif: ��ȡ��ȡ���ֱ�־��
 * param: --
 * return: ������ȡ���ֱ�־��
 */
SpecimenArm::Flag SpecimenArm::get_suck_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ȡ���ֱ�־��
	return(_suck_shake_hand_flag);
}

/**
 * name: set_suck_response_flag
 * brief: ������ȡ�ظ���־��
 * param: --
 * return: --
 */
void SpecimenArm::set_suck_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ȡ�ظ���־��
	_suck_response_flag=flag;
}

/**
 * name: get_suck_response_flag
 * breif: ��ȡ��ȡ�ظ���־��
 * param: --
 * return: ������ȡ�ظ���־��
 */
SpecimenArm::Flag SpecimenArm::get_suck_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ȡ�ظ���־��
	return(_suck_response_flag);
}

/**
 * name: set_liquid_level_height
 * brief: ����Һλ�߶ȡ�
 * param: height - �����Һλ�߶ȡ�
 * return: --
 */
void SpecimenArm::set_liquid_level_height(const unsigned int height){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����Һλ�߶ȡ�
	_liquid_level_height=height;
}

/**
 * name: get_liquid_level_height
 * brief: ��ȡҺλ�߶ȡ�
 * param: --
 * return: ����Һλ�߶ȡ�
 */
unsigned int SpecimenArm::get_liquid_level_height() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����Һλ�߶ȡ�
	return(_liquid_level_height);
}

/**
 * name: set_spit_shake_hand_flag
 * brief: ������Һ���ֱ�־��
 * param: flag - �����������ֱ�־��
 * return: --
 */
void SpecimenArm::set_spit_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����������ֱ�־��
	_spit_shake_hand_flag=flag;
}

/**
 * name: get_spit_shake_hand_flag
 * brief: ��ȡ��Һ���ֱ�־��
 * param: --
 * return: ������Һ���ֱ�־��
 */
SpecimenArm::Flag SpecimenArm::get_spit_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����������ֱ�־��
	return(_spit_shake_hand_flag);
}

/**
 * name: set_spit_response_flag
 * brief: ������Һ�ظ���־��
 * param: flag - �������ӻظ���־��
 * return: --
 */
void SpecimenArm::set_spit_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������Һ�ظ���־��
	_spit_response_flag=flag;
}

/**
 * name: get_spit_response_flag
 * brief: ��ȡ��Һ�ظ���־��
 * param: --
 * return: ������Һ�ظ���־��
 */
SpecimenArm::Flag SpecimenArm::get_spit_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������Һ�ظ���־��
	return(_spit_response_flag);
}

/**
 * name: set_wash_shake_hand_flag
 * brief: ������ϴ���ֱ�־��
 * param: flag - �������ϴ���ֱ�־��
 * return: --
 */
void SpecimenArm::set_wash_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ���ֱ�־��
	_wash_shake_hand_flag=flag;
}

/**
 * name: get_wash_shake_hand_flag
 * brief: ��ȡ��ϴ���ֱ�־��
 * param: --
 * return: ������ϴ���ֱ�־��
 */
SpecimenArm::Flag SpecimenArm::get_wash_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ���ֱ�־��
	return(_wash_shake_hand_flag);
}

/**
 * name: set_wash_response_flag
 * brief: ������ϴ�ظ���־��
 * param: flag - �������ϴ�ظ���־��
 * return: --
 */
void SpecimenArm::set_wash_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�ظ���־��
	_wash_response_flags=flag;
}

/**
 * name: get_wash_response_flag
 * brief: ��ȡ��ϴ�ظ���־��
 * param: --
 * return: ������ϴ�ظ���־��
 */
SpecimenArm::Flag SpecimenArm::get_wash_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�ظ���־��
	return(_wash_response_flags);
}

/**
 * name: get_outer_wash_time
 * brief: ��ȡ�����ϴʱ�䡣
 * param: --
 * return: ���������ϴʱ�䡣
 */
unsigned int SpecimenArm::get_outer_wash_time() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰ�����ļ��б���������ϴʱ�䡣
	int wash_time=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("SPECIMENARM"),_T("OUTER_WASH_TIME"));
	if(wash_time<0){
		wash_time=0;
	}else if(wash_time>5000){
		wash_time=5000;
	}
	//3.�������е���ֱ�ӷ��������ϴʱ�䡣
	return(static_cast<unsigned int>(wash_time));
}

/**
 * name: get_inner_wash_time
 * brief: ��ȡ�ڱ���ϴʱ�䡣
 * param: --
 * return: �����ڱ���ϴʱ�䡣
 */
unsigned int SpecimenArm::get_inner_wash_time() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰ�����ļ��б���ı���ϴʱ�䡣
	int wash_time=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("SPECIMENARM"),_T("INNER_WASH_TIME"));
	if(wash_time<0){
		wash_time=0;
	}else if(wash_time>5000){
		wash_time=5000;
	}
	//3.�������е���ֱ�ӷ��������ϴʱ�䡣
	return(static_cast<unsigned int>(wash_time));
}