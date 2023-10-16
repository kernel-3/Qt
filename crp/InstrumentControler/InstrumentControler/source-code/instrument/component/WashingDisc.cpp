#include"stdafx.h"
#include"WashingDisc.h"
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
 * name: WashingDisc
 * brief: ���캯����
 * param: --
 * return: --
 */
WashingDisc::WashingDisc(void)
	:Component()
	,_lock(new MtLock)
	,_rotation_shake_hand_flag(FLAG_IDLE)
	,_rotation_response_flag(FLAG_IDLE)
	,_wash_shake_hand_flag(FLAG_IDLE)
	,_wash_response_flag(FLAG_IDLE)
	,_having_tube_in_entry_flag(FLAG_UNKNOWN)
	,_having_tube_in_entry_flag_expect_value(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag(FLAG_UNKNOWN)
	,_having_tube_in_exit_flag_expect_value(FLAG_UNKNOWN)
	,_hole_no_in_entry(1){
	memset(_hole_state,HOLE_STATE_EMPTY,
		HOLE_COUNT*sizeof(HoleState));//����������״̬�豸Ϊ�ա�
}

/**
 * name: ~WashingDisc
 * brief: ����������
 * param: --
 * return: --
 */
WashingDisc::~WashingDisc(void){
	delete _lock;
}

/**
 * name: rotate
 * brief: ������ϴ����ת��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int WashingDisc::rotate(){
	//1.������ϴ����תָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_washing_disc_rotation_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�����ϴ����ת���ֱ���Լ���ϴ����ת��ɱ�ǡ�
	set_rotation_shake_hand_flag(FLAG_BUSY);
	set_rotation_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��ϴ����תָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: wash
 * brief: ������ϴ����ϴ��
 * param: substrate_type - ����ĵ������͡�
 *        substrate_volume - ����ĵ��������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int WashingDisc::wash(const SubstrateType substrate_type/*=SUBSTRATE_TYPE_NONE*/,
	const unsigned int substrate_volume/*=0*/){
	//1.������ϴ����ϴ���������
	const unsigned int washing_liquid_volume=get_washing_liquid_volume();
	const BOOL is_washing_position_1_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_1))?TRUE:FALSE);
	const BOOL is_washing_position_2_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_2))?TRUE:FALSE);
	const BOOL is_washing_position_3_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_3))?TRUE:FALSE);
	const BOOL is_washing_position_4_need_washing=((HOLE_STATE_USED==
		get_hole_state(POSITION_WASHING_4))?TRUE:FALSE);
	//2.������ϴ����ϴָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_washing_disc_wash_command(
		static_cast<unsigned int>(substrate_type),substrate_volume,washing_liquid_volume,
		is_washing_position_1_need_washing,is_washing_position_2_need_washing,
		is_washing_position_3_need_washing,is_washing_position_4_need_washing)<0){
		return(-1);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.�����ϴ����ϴ���ֱ���Լ���ϴ����ϴ��ɱ�ǡ�
	set_wash_shake_hand_flag(FLAG_BUSY);
	set_wash_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��ϴ����ϴָ��"))<0){
		return(-2);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: inquire_sensor
 * brief: ��ѯ��ϴ���ϵĴ������������жϲ�ѯ�Ƿ�ɹ���
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int WashingDisc::inquire_sensor(){
	//1.������ѯ������ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_inquire_sensors_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.�����ϴ���ϸ�����������־��
	set_having_tube_in_entry_flag(FLAG_UNKNOWN);
	set_having_tube_in_exit_flag(FLAG_UNKNOWN);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("��ѯ�豸�ϵ�λ�ô�����ָ��"))<0){
		return(-2);
	}
	//5.ѭ���ȴ���ϴ����λ�ô�����״̬���أ������ж��Ƿ�ʱ��
	//5-1.��¼��ǰ��ʼʱ�䡣
	DWORD last_time=timeGetTime();
	//5-2.ѭ�������ϴ����λ�ô�����״̬�Ƿ�ɹ����ء�
	while(1){
		//5-2-1.�����ϴ����λ�ô�����״̬�ɹ����ء�
		if((FLAG_UNKNOWN!=get_having_tube_in_entry_flag())&&(
			FLAG_UNKNOWN!=get_having_tube_in_exit_flag())){
			return(0);
		}
		//5-2-2.�����ϴ����λ�ô�����״̬��δ���ء�
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
	//6.�������е���ֱ�ӷ��ش���
	return(-4);
}

/**
 * name: set_rotation_shake_hand_flag
 * breif: ������ϴ����ת���ֱ�ǡ�
 * param: flag - �������ת���ֱ�ǡ�
 * return: --
 */
void WashingDisc::set_rotation_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ����ת���ֱ�ǡ�
	_rotation_shake_hand_flag=flag;
}

/**
 * name: get_rotation_shake_hand_flag
 * brief: ��ȡ��ϴ����ת���ֱ�ǡ�
 * param: --
 * return: ������ϴ����ת���ֱ�ǡ�
 */
WashingDisc::Flag WashingDisc::get_rotation_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ����ת���ֱ�ǡ�
	return(_rotation_shake_hand_flag);
}

/**
 * name: set_rotation_response_flag
 * brief: ������ϴ����ת�ظ���ǡ�
 * param: flag - ������ϴ����ת�ظ���ǡ�
 * return: --
 */
void WashingDisc::set_rotation_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ����ת�ظ���ǡ�
	_rotation_response_flag=flag;
}

/**
 * name: get_rotation_response_flag
 * brief: ��ȡ��ϴ����ת�ظ���ǡ�
 * param: --
 * return: ������ϴ����ת�ظ���ǡ�
 */
WashingDisc::Flag WashingDisc::get_rotation_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ����ת�ظ���ǡ�
	return(_rotation_response_flag);
}

/**
 * name: set_wash_shake_hand_flag
 * brief: ������ϴ���ֱ�־��
 * param: flag - �������ϴ���ֱ�־��
 * return: --
 */
void WashingDisc::set_wash_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ���ֱ�־��
	_wash_shake_hand_flag=flag;
}

/**
 * name: get_wash_shake_hand_flag
 * breif: ��ȡ��ϴ���ֱ�־��
 * param: --
 * return: ������ϴ���ֱ�־��
 */
WashingDisc::Flag WashingDisc::get_wash_shake_hand_flag() const{
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
void WashingDisc::set_wash_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�ظ���־��
	_wash_response_flag=flag;
}

/**
 * name: get_wash_response_flag
 * brief: ��ȡ��ϴ�ظ���־��
 * param: --
 * return: ������ϴ�ظ���־��
 */
WashingDisc::Flag WashingDisc::get_wash_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�ظ���־��
	return(_wash_response_flag);
}

/**
 * name: set_having_tube_in_entry_flag
 * breif: ������ϴ�̽���λ�йܱ�־��
 * param: flag - �������ϴ�̽���λ�йܱ�־��
 * return: --
 */
void WashingDisc::set_having_tube_in_entry_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־��
	_having_tube_in_entry_flag=flag;
}

/**
 * name: get_having_tube_in_entry_flag
 * brief: ��ȡ��ϴ�̽���λ�йܱ�־��
 * param: --
 * return: ������ϴ�̽���λ�йܱ�־��
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_entry_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־��
	return(_having_tube_in_entry_flag);
}

/**
 * name: set_having_tube_in_entry_flag_expect_value
 * breif: ������ϴ�̽���λ�йܱ�־������ֵ��
 * param: value - ����ķ�Ӧ�̽���λ�йܱ�־������ֵ��
 * return: --
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
void WashingDisc::set_having_tube_in_entry_flag_expect_value(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־������ֵ��
	_having_tube_in_entry_flag_expect_value=flag;
}

/**
 * name: get_having_tube_in_entry_flag_expect_value
 * brief: ��ȡ��ϴ�̽���λ�йܱ�־������ֵ��
 * param: --
 * return: ������ϴ�̽���λ�йܱ�־������ֵ��
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_entry_flag_expect_value() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־������ֵ��
	return(_having_tube_in_entry_flag_expect_value);
}

/**
 * name: set_having_tube_in_exit_flag
 * brief: ������ϴ�̳���λ�йܱ�־��
 * param: flag - �������ϴ�̳���λ�йܱ�־��
 * return: --
 */
void WashingDisc::set_having_tube_in_exit_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̳���λ�йܱ�־��
	_having_tube_in_exit_flag=flag;
}

/**
 * name: get_having_tube_in_exit_flag
 * brief: ��ȡ��ϴ�̳���λ�йܱ�־��
 * param: --
 * return: ������ϴ�̳���λ�йܱ�־��
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_exit_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̳���λ�йܱ�־��
	return(_having_tube_in_exit_flag);
}

/**
 * name: set_having_tube_in_exit_flag_expect_value
 * brief: ������ϴ�̳���λ�йܱ�־������ֵ��
 * param: flag - �������ϴ�̳���λ�йܱ�־������ֵ��
 * return: --
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
void WashingDisc::set_having_tube_in_exit_flag_expect_value(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־������ֵ��
	_having_tube_in_exit_flag_expect_value=flag;
}

/**
 * name: get_having_tube_in_exit_flag_expect_value
 * brief: ��ȡ��ϴ�̳���λ�йܱ�־������ֵ��
 * param: --
 * return: ������ϴ�̳���λ�йܱ�־������ֵ��
 * remark: �˺���ֻ���Է����յĵ��Ի����������á�
 */
WashingDisc::Flag WashingDisc::get_having_tube_in_exit_flag_expect_value() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�йܱ�־������ֵ��
	return(_having_tube_in_exit_flag_expect_value);
}

/**
 * name: reset_hole_no_in_entry
 * brief: ������ϴ�̽���λ�׺š�
 * param: --
 * return: --
 */
void WashingDisc::reset_hole_no_in_entry(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ�̽���λ�׺š�
	_hole_no_in_entry=1;
}

/**
 * name: decrease_hole_no_in_entry
 * breif: �ݼ���ϴ�̽���λ�׺š�
 * param: --
 * return: --
 */
void WashingDisc::decrease_hole_no_in_entry(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�ݼ���ϴ�̽���λ�׺š�
	if(_hole_no_in_entry<=1){
		_hole_no_in_entry=29;
	}else{
		--_hole_no_in_entry;
	}
}

/**
 * name: are_there_tubes
 * brief: �����ϴ�����Ƿ��йܡ�
 * param: --
 * return: �����ϴ�����йܷ���TRUE�����򷵻�FALSE��
 */
BOOL WashingDisc::are_there_tubes() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ���ϵĿף��������Ƿ��йܡ�
	for(unsigned int index=0;index!=HOLE_COUNT;++index){
		if((HOLE_STATE_USED==_hole_state[index])||
			(HOLE_STATE_FAILED==_hole_state[index])){
			return(TRUE);
		}
	}
	//3.�������е��ˣ�����Ϊ��ϴ�����޹ܡ�
	return(FALSE);
}

/**
 * name: set_hole_state
 * brief: ������ϴ��ָ��λ�õĿ�״̬��
 * param: position - �����ָ��λ�á�
 *        state - ����Ŀ�״̬��
 * return: --
 */
void WashingDisc::set_hole_state(
	const Position position,const HoleState state){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ��ָ��λ�õĿ�״̬��
	_hole_state[get_hole_no(position)-1]=state;
}

/**
 * name: get_hole_state
 * brief: ��ȡ��ϴ��ָ��λ�õĿ�״̬��
 * param: position - �����ָ��λ�á�
 * return: ������ϴ��ָ��λ�õĿ�״̬��
 */
WashingDisc::HoleState WashingDisc::get_hole_state(
	const Position position) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ϴ��ָ��λ�õĿ�״̬��
	return(_hole_state[get_hole_no(position)-1]);
}

/**
 * name: get_hole_no
 * breif: ��ȡָ��λ���ϵĿ׺š�
 * param: position - �����ָ��λ�á�
 * return: ����ָ��λ���ϵĿ׺š�
 */
unsigned int WashingDisc::get_hole_no(const Position position) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ǰ�������������
	unsigned int hole_no=_hole_no_in_entry;
	//3.�����ǰ������ȡ��ϴ�̵�һ��ϴλ�ϵĿ׺š�
	if(POSITION_WASHING_1==position){
		hole_no+=5;
	}
	//4.�����ǰ������ȡ��ϴ�̵ڶ���ϴλ�ϵĿ׺š�
	else if(POSITION_WASHING_2==position){
		hole_no+=9;
	}
	//5.�����ǰ��ȡ��ϴ�̵�����ϴλ�ϵĿ׺š�
	else if(POSITION_WASHING_3==position){
		hole_no+=13;
	}
	//6.�����ǰ��ȡ��ϴ�̵�����ϴλ�ϵĿ׺š�
	else if(POSITION_WASHING_4==position){
		hole_no+=17;
	}
	//7.�����ǰ��ȡ��ϴ�̵���λ�ϵĿ׺š�
	else if(POSITION_SUBSTRATE==position){
		hole_no+=18;
	}
	//8.�����ǰ��ȡ��ϴ�̳���λ�ϵĿ׺š�
	else if(POSITION_EXIT==position){
		hole_no+=19;
	}
	//9.���׺��޶��ںϷ���Χ�ڡ�
	if(hole_no>HOLE_COUNT){
		hole_no=hole_no-HOLE_COUNT;
	}
	//10.�������е���ֱ�ӷ��ؿ׺š�
	return(hole_no);
}

/**
 * name: get_washing_liquid_volume
 * brief: ��ȡ��ϴҺ�����
 * param: --
 * return: ������ϴҺ�����
 */
unsigned int WashingDisc::get_washing_liquid_volume() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ��ǰ�����ļ��б������ϴҺ�����
	int washing_liquid_volume=Inis::instance()->read(Inis::NAME_INSTRUMENT,
		_T("WASHINGDISC"),_T("WASHING_LIQUID_VOLUME"));
	if(washing_liquid_volume<0){
		washing_liquid_volume=0;
	}else if(washing_liquid_volume>1000){
		washing_liquid_volume=1000;
	}
	//3.���ص�ǰ��ȡ����ϴҺ�����
	return(static_cast<unsigned int>(washing_liquid_volume));
}