#include"stdafx.h"
#include"ReactionDisc.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: ReactionDisc
 * breif: ���캯����
 * param: --
 * return: --
 */
ReactionDisc::ReactionDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_having_tube_in_entry_flag(FLAG_UNKNOWN)
	,_having_tube_in_entry_flag_expect_value(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag_expect_value(FLAG_UNKNOWN){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));
}

/**
 * name: ~ReactionDisc
 * breif: ����������
 * param: --
 * return: --
 */
ReactionDisc::~ReactionDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: ���Ӧ��ָ��������ת��ָ��λ�á�
 * param: hole_no - ����ķ�Ӧ�̶��š�
 *        position - ����ķ�Ӧ��λ�á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReactionDisc::rotate(const unsigned int hole_no,const Position position){
	//1.�������Ĳ����Ƿ�Ϸ���
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.������Ӧ����תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_reaction_disc_rotation_command(
		hole_no,static_cast<unsigned int>(position))<0){
		return(-2);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.�����Ӧ����ת���ֱ���Լ���Ӧ����ת��ɱ�ǡ�
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��Ӧ����תָ��"))<0){
		return(-3);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: inquire_sensor
 * brief: ��ѯ��Ӧ���ϵĴ������������жϲ�ѯ�Ƿ�ɹ���
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReactionDisc::inquire_sensor(){
	//1.������ѯ������ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_inquire_sensors_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.�����Ӧ���ϸ�����������־��
	set_having_tube_in_entry_flag(FLAG_UNKNOWN);
	set_having_tube_in_exit_flag(FLAG_UNKNOWN);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��ѯ��Ӧ��λ�ô�����ָ��"))<0){
		return(-2);
	}
	//6.ѭ���ȴ���Ӧ����λ�ô�����״̬���أ������ж��Ƿ�ʱ��
	//6-1.��¼��ǰ��ʼʱ�䡣
	DWORD last_time=timeGetTime();
	//6-2.ѭ����ⷴӦ����λ�ô�����״̬�Ƿ�ɹ����ء�
	while(1){
		//6-2-1.�����Ӧ����λ�ô�����״̬�ɹ����ء�
		if((FLAG_UNKNOWN!=get_having_tube_in_entry_flag())&&(
			FLAG_UNKNOWN!=get_having_tube_in_exit_flag())){
			return(0);
		}
		//6-2-2.�����Ӧ����λ�ô�����״̬��δ���ء�
		else{
			//a.��ȡ��ǰʱ�䡣
			const DWORD current_time=timeGetTime();
			//b.��⵱ǰʱ���Ƿ������
			if(last_time>current_time){
				last_time=current_time;
			}
			//c.�����ǰ����ָ�ʱ����
			if((current_time-last_time)>ANSWER_TIMEOUT){
				return(-3);
			}
			//d.�����ǰ��δ������ʱ��������´�ѭ����
			else{
				//d-1.�ͷ�ʱ��Ƭ��
				timeBeginPeriod(1);
				Sleep(5);
				timeEndPeriod(1);
				//d-2.�����´�ѭ����
				continue;
			}
		}
	}
	//7.�������е���ֱ�ӷ��ش���
	return(-4);
}

/**
 * name: set_rotation_shake_hand_flag
 * brief: ���÷�Ӧ����ת���ֱ�־��
 * param: flag - ����ķ�Ӧ����ת���ֱ�־��
 * return: --
 */
void ReactionDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ñ�ǡ�
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: ��ȡ��Ӧ����ת���ֱ�־��
 * param: --
 * return: ���ط�Ӧ����ת���ֱ�־��
 */
ReactionDisc::Flag ReactionDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ر�ǡ�
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: ���÷�Ӧ����ת�ظ���־��
 * param: flag - ����ķ�Ӧ����ת�ظ���־��
 * return: --
 */
void ReactionDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ñ�ǡ�
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: ��ȡ��Ӧ����ת�ظ���־��
 * param: --
 * return: ���ط�Ӧ����ת�ظ���־��
 */
ReactionDisc::Flag ReactionDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ر�ǡ�
	return(_rotation_response_flag);
}

/**
 * name: set_having_tube_in_entry_flag
 * brief: ���÷�Ӧ�̽���λ�йܱ�־��
 * param: flag - ����ķ�Ӧ�̽���λ�йܱ�־��
 * return: --
 */
void ReactionDisc::set_having_tube_in_entry_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷�Ӧ�̽���λ�йܱ�־��
	_having_tube_in_entry_flag=flag;
}

/**
 * name: get_having_tube_in_entry_flag
 * breif: ��ȡ��Ӧ�̽���λ�йܱ�־��
 * param: --
 * return: ���ط�Ӧ�̽���λ�йܱ�־��
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_entry_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ط�Ӧ�̽���λ�йܱ�־��
	return(_having_tube_in_entry_flag);
}

/**
 * name: set_having_tube_in_entry_flag_expect_value
 * breif: ���÷�Ӧ�̽���λ�йܱ�־������ֵ��
 * param: value - ����ķ�Ӧ�̽���λ�йܱ�־������ֵ��
 * return: --
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
void ReactionDisc::set_having_tube_in_entry_flag_expect_value(const Flag value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷�Ӧ�̽���λ�йܱ�־������ֵ��
	_having_tube_in_entry_flag_expect_value=value;
}

/**
 * name: get_having_tube_in_entry_flag_expect_value
 * brief: ��ȡ��Ӧ�̽���λ�йܱ�־������ֵ��
 * param: --
 * return: ���ط�Ӧ�̽���λ�йܱ�־������ֵ��
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_entry_flag_expect_value() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ط�Ӧ�̽���λ�йܱ�־������ֵ��
	return(_having_tube_in_entry_flag_expect_value);
}

/**
 * name: set_having_tube_in_exit_flag
 * brief: ���÷�Ӧ�̳���λ�йܱ�־��
 * param: flag - ����ķ�Ӧ�̳���λ�йܱ�־��
 * return: --
 */
void ReactionDisc::set_having_tube_in_exit_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷�Ӧ�̳���λ�йܱ�־��
	_having_tube_in_exit_flag=flag;
}

/**
 * name: get_having_tube_in_exit_flag
 * breif: ��ȡ��Ӧ�̳���λ�йܱ�־��
 * param: --
 * return: ���ط�Ӧ�̳���λ�йܱ�־��
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_exit_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ط�Ӧ�̳���λ�йܱ�־��
	return(_having_tube_in_exit_flag);
}

/**
 * name: set_having_tube_in_exit_flag_expect_value
 * breif: ���÷�Ӧ�̳���λ�йܱ�־������ֵ��
 * param: value - ����ķ�Ӧ�̳���λ�йܱ�־������ֵ��
 * return: --
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
void ReactionDisc::set_having_tube_in_exit_flag_expect_value(const Flag value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷�Ӧ�̳���λ�йܱ�־������ֵ��
	_having_tube_in_exit_flag_expect_value=value;
}

/**
 * name: get_having_tube_in_exit_flag_expect_value
 * brief: ��ȡ��Ӧ�̳���λ�йܱ�־������ֵ��
 * param: --
 * return: ���ط�Ӧ�̳���λ�йܱ�־������ֵ��
 */
ReactionDisc::Flag ReactionDisc::get_having_tube_in_exit_flag_expect_value() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ط�Ӧ�̳���λ�йܱ�־������ֵ��
	return(_having_tube_in_exit_flag_expect_value);
}

/**
 * name: are_there_tubes
 * breif: ��⵱ǰ��Ӧ�����Ƿ��йܡ�
 * param: --
 * return: �����ǰ��Ӧ�����йܷ���TRUE�����򷵻�FALSE��
 */
BOOL ReactionDisc::are_there_tubes() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.ѭ��������Ӧ��λ�ã�����Ƿ��йܡ�
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_WAIT==_hole_state[index]){
			//remark: ��Ϊ����Ӧ�̿״���HOLE_STATE_PROCESSING������״̬��ʱ��
			//        ��Ӧ�̿϶��ǲ�������ת�ģ���������û������HOLE_STATE_PROCESSING
			//        ״̬��
			return(TRUE);
		}
	}
	//3.�������е���ֱ�ӷ����޹ܡ�
	return(FALSE);
}

/**
 * name: get_empty_hole_no
 * brief: ��ȡ��ǰ��Ӧ���Ͽտ׵Ŀ׺š�
 * param: --
 * return: �������ִ�гɹ������ص�ǰ��Ӧ���Ͽտ׵Ŀ׺ţ�
 *         ���򷵻��㡣
 */
unsigned int ReactionDisc::get_empty_hole_no() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.ѭ��������Ӧ��λ�ã����㷴Ӧ���Ͽտ׵Ŀ׺š�
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if(HOLE_STATE_EMPTY==_hole_state[index]){
			return(index+1);
		}
	}
	//3.�������е���ֱ�ӷ����㡣
	return(0);
}

/**
 * name: set_hole_state
 * brief: ���÷�Ӧ����ָ���յ�״̬��
 * param: hole_no - �����ָ���׺š�
 *        state - ����Ŀ׵�״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ReactionDisc::set_hole_state(
	const unsigned int hole_no,const HoleState state){
	//1.��������Ƿ�Ϸ���
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ָ���׵�״̬��
	_hole_state[hole_no-1]=state;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: get_hole_state
 * brief: ��ȡ��Ӧ����ָ���׵�״̬��
 * param: hole_no - ����ָ���Ŀ׺š�
 * return: �����ǰ����ִ�гɹ�������ִ�п׵�״̬�����򷵻�δ֪״̬��
 */
ReactionDisc::HoleState ReactionDisc::get_hole_state(
	const unsigned int hole_no) const{
	//1.��������Ƿ�Ϸ���
	if((hole_no<1)||(hole_no>HOLE_COUNT)){
		return(HOLE_STATE_UNKNOWN);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ָ���׵�λ�á�
	return(_hole_state[hole_no-1]);
}