#include"stdafx.h"
#include"DetectionDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: DetectionDisc
 * breif: ���캯����
 * param: --
 * return: --
 */
DetectionDisc::DetectionDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_detect_shake_hand_flag(FLAG_IDLE)
	,_detect_response_flag(FLAG_IDLE)
	,_luminous(0){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));
}

/**
 * name: ~DetectionDisc
 * brief: ����������
 * param: --
 * return: --
 */
DetectionDisc::~DetectionDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: ��������ָ������ת��ָ��λ�á�
 * param: hole_no - ����Ŀ׺š�
 *        position - �����λ�á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DetectionDisc::rotate(const unsigned int hole_no,const Position position){
	//1.����������벻�Ϸ�����ֱ�ӷ��ش���
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.�����������תָ������жϴ����Ƿ�ɹ���
	Command command;
	Position position_t(position);
	if(POSITION_EXIT==position_t){//����λ��ʵ���ǽ���λ��
		position_t=POSITION_ENTRY;
	}
	if(command.generate_detection_disc_rotation_command(
		hole_no,static_cast<unsigned int>(position_t))<0){
		return(-2);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.����������ת���ֱ���Լ��������ת��ɱ�ǡ�
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("�������תָ��"))<0){
		return(-3);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: detect
 * breif: �������̼�⡣
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int DetectionDisc::detect(){
	//1.��������̼��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_detection_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�������̼�����ֱ���Լ�����̼��ظ���ǡ�
	set_detect_shake_hand_flag(FLAG_BUSY);
	set_detect_response_flag(FLAG_BUSY);
	set_luminous(0);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("����̼��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_rotation_shake_hand_flag
 * breif: ���ü������ת���ֱ�ǡ�
 * param: flag - �������ת���ֱ�ǡ�
 * return: --
 */
void DetectionDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ü������ת���ֱ�ǡ�
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: ��ȡ�������ת���ֱ�ǡ�
 * param: --
 * return: ���ؼ������ת���ֱ�ǡ�
 */
DetectionDisc::Flag DetectionDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ؼ������ת���ֱ�ǡ�
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: ���ü������ת�ظ���ǡ�
 * param: flag - ����������ת�ظ���ǡ�
 * return: --
 */
void DetectionDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ü������ת�ظ���ǡ�
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: ��ȡ�������ת�ظ���ǡ�
 * param: --
 * return: ���ؼ������ת�ظ���ǡ�
 */
DetectionDisc::Flag DetectionDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ؼ������ת�ظ���ǡ�
	return(_rotation_response_flag);
}

/**
 * name: set_detect_shake_hand_flag
 * brief: ���ü���̼�����ֱ�־��
 * param: flag - ����ļ���̼�����ֱ�־��
 * return: --
 */
void DetectionDisc::set_detect_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ü���̼�����ֱ�־��
	_detect_shake_hand_flag=flag;
}

/**
 * name: get_detect_shake_hand_flag
 * brief: ��ȡ����̼�����ֱ�־��
 * param: --
 * return: ���ؼ���̼�����ֱ�־��
 */
DetectionDisc::Flag DetectionDisc::get_detect_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ؼ���̼�����ֱ�־��
	return(_detect_shake_hand_flag);
}

/**
 * name: set_detect_response_flag
 * brief: ���ü���̼��ظ���־��
 * param: flag - ����ļ���̼��ظ���־��
 * return: --
 */
void DetectionDisc::set_detect_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ü���̼��ظ���־��
	_detect_response_flag=flag;
}

/**
 * name: get_detect_response_flag
 * brief: ��ȡ����̼��ظ���־��
 * param: --
 * return: ���ؼ���̼��ظ���־��
 */
DetectionDisc::Flag DetectionDisc::get_detect_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ؼ���̼��ظ���־��
	return(_detect_response_flag);
}

/**
 * name: set_luminous
 * brief: ���÷���ֵ��
 * param: luminous - ����ķ���ֵ��
 * return: --
 */
void DetectionDisc::set_luminous(const unsigned int luminous){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��������ķ���ֵ��
	_luminous=luminous;
}

/**
 * name: get_luminous
 * breif: ��ȡ����ֵ��
 * param: --
 * return: ���ط���ֵ��
 */
unsigned int DetectionDisc::get_luminous() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ط���ֵ��
	return(_luminous);
}

/**
 * name: set_hole_state
 * breif: ���ü����ָ���׵�״̬��
 * param: hole_no - �����ָ���ס�
 *        state - �����ָ��״̬��
 * return: --
 */
void DetectionDisc::set_hole_state(
	const unsigned int hole_no,const HoleState state){
	//1.�������������Ϸ���ֱ�ӷ��ء�
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return;
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ָ���׵�״̬��
	_hole_state[hole_no-1]=state;
}

/** 
 * name: get_empty_hole_no
 * brief: ��ȡ�տ׺š�
 * param: --
 * return: �����ȡ�տ׺ųɹ����򷵻ؿ׺ţ����򷵻��㡣
 */
unsigned int DetectionDisc::get_empty_hole_no() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ�տ׺š�
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_EMPTY==_hole_state[index]){
			return(index+1);
		}
	}
	//3.�������е���ֱ�ӷ����㡣
	return(0);
}