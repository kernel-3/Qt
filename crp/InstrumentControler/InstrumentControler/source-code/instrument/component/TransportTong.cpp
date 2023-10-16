#include"stdafx.h"
#include"TransportTong.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TransportTong
 * breif: ���캯����
 * param: --
 * return: --
 */
TransportTong::TransportTong(void)
	:Component()
	,_lock(new MtLock)
	,_take_tube_out_of_detection_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_detection_disc_response_flag(FLAG_IDLE)
	,_discard_tube_shake_hand_flag(FLAG_IDLE)
	,_discard_tube_response_flag(FLAG_UNKNOWN)
	,_take_tube_out_of_washing_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_washing_disc_response_flag(FLAG_IDLE)
	,_return_tube_to_reaction_disc_shake_hand_flag(FLAG_IDLE)
	,_return_tube_to_reaction_disc_response_flag(FLAG_IDLE)
	,_put_tube_in_detection_disc_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_detection_disc_response_flag(FLAG_IDLE)
	,_take_tube_out_of_reaction_disc_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_of_reaction_disc_response_flag(FLAG_IDLE)
	,_put_tube_in_washing_disc_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_washing_disc_response_flag(FLAG_IDLE){
}

/**
 * name: ~TransportTong
 * breif: ����������
 * param: --
 * return: --
 */
TransportTong::~TransportTong(void){
	delete _lock;
}

/**
 * name: take_tube_out_of_detection_disc
 * brief: ����ת��ץ�ִӼ����ȡ�ܡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::take_tube_out_of_detection_disc(){
	//1.����ת��ץ�ִӼ����ȡ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_take_tube_out_of_detection_disc_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ִӼ����ȡ�����ֱ���Լ�ת��ץ�ִӼ����ȡ�ܻظ���ǡ�
	set_take_tube_out_of_detection_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_detection_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ִӼ����ȡ��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: discard_tube
 * brief: ����ת��ץ�ֶ��ܡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::discard_tube(){
	//1.����ת��ץ�ֶ���ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_discard_tube_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ֶ������ֱ���Լ�ת��ץ�ֶ��ܻظ���ǡ�
	set_discard_tube_shake_hand_flag(FLAG_BUSY);
	set_discard_tube_response_flag(FLAG_UNKNOWN);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ֶ���ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: take_tube_out_of_washing_disc
 * brief: ����ϴ��ȡ�ܡ�
 * param: stop_position - �����ֹͣλ�á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::take_tube_out_of_washing_disc(
	const StopPosition stop_position){
	//1.����ת��ץ�ִ���ϴ��ȡ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_take_tube_out_of_washing_disc_command(
		stop_position)<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ִ���ϴ��ȡ�����ֱ���Լ�ת��ץ�ִ���ϴ��ȡ�ܻظ���ǡ�
	set_take_tube_out_of_washing_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_washing_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ִ���ϴ��ȡ��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: return_tube_to_reaction_disc
 * brief: �عܵ���Ӧ�̡�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::return_tube_to_reaction_disc(){
	//1.����ת��ץ�ֻعܵ���Ӧ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_return_tube_to_reaction_disc_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ֻعܵ���Ӧ�����ֱ���Լ�ת��ץ�ֻعܵ���Ӧ�̻ظ���ǡ�
	set_return_tube_to_reaction_disc_shake_hand_flag(FLAG_BUSY);
	set_return_tube_to_reaction_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ֻعܵ���Ӧ��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: put_tube_in_detection_disc
 * brief: ����ת��ץ�ַŹܵ�����̡�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::put_tube_in_detection_disc(){
	//1.����ת��ץ�ַŹܵ������ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_put_tube_in_detection_disc_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ַŹܵ���������ֱ���Լ�ת��ץ�ַŹܵ�����̻ظ���ǡ�
	set_put_tube_in_detection_disc_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_detection_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ַŹܵ������ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: take_tube_out_of_reaction_disc
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ�ܡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::take_tube_out_of_reaction_disc(){
	//1.����ת��ץ�ִӷ�Ӧ��ȡ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_take_tube_out_of_reaction_disc_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ִӷ�Ӧ��ȡ�����ֱ���Լ�ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���ǡ�
	set_take_tube_out_of_reaction_disc_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_of_reaction_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ִӷ�Ӧ��ȡ��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: put_tube_in_washing_disc
 * brief: ����ת��ץ�ַŹܵ���ϴ�̡�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TransportTong::put_tube_in_washing_disc(){
	//1.����ת��ץ�ַŹܵ���ϴ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_put_tube_in_washing_disc_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���ת��ץ�ַŹܵ���ϴ�����ֱ���Լ�ת��ץ�ַŹܵ���ϴ�̻ظ���ǡ�
	set_put_tube_in_washing_disc_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_washing_disc_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("ת��ץ�ַŹܵ���ϴ��ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_take_tube_out_of_detection_disc_shake_hand_flag
 * breif: ���ôӼ����ȡ�����ֱ�־��
 * param: flag - ����ĴӼ����ȡ�����ֱ�־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_detection_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ôӼ����ȡ�����ֱ�־��
	_take_tube_out_of_detection_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_detection_disc_shake_hand_flag
 * brief: ��ȡ�Ӽ����ȡ�����ֱ�־��
 * param: --
 * return: ���شӼ����ȡ�����ֱ�־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_detection_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���شӼ����ȡ�����ֱ�־��
	return(_take_tube_out_of_detection_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_detection_disc_response_flag
 * brief: ���ôӼ����ȡ�ܻظ���־��
 * param: flag - ����ĴӼ����ȡ�ܻظ���־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_detection_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ôӼ����ȡ�ܻظ���־��
	_take_tube_out_of_detection_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_detection_disc_response_flag
 * brief: ��ȡ�Ӽ����ȡ�ܻظ���־��
 * param: --
 * return: ���شӼ����ȡ�ܻظ���־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_detection_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���شӼ����ȡ�ܻظ���־��
	return(_take_tube_out_of_detection_disc_response_flag);
}

/**
 * name: set_discard_tube_shake_hand_flag
 * brief: ���ö�������ָ�
 * param: flag - ����Ķ�������ָ�
 * return: --
 */
void TransportTong::set_discard_tube_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ö�������ָ�
	_discard_tube_shake_hand_flag=flag;
}

/**
 * name: get_discard_tube_shake_hand_flag
 * brief: ��ȡ��������ָ�
 * param: --
 * return: ���ض�������ָ�
 */
TransportTong::Flag TransportTong::get_discard_tube_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ض�������ָ�
	return(_discard_tube_shake_hand_flag);
}

/**
 * name: set_discard_tube_response_flag
 * brief: ���ö��ܻظ���־��
 * param: flag - ����Ķ��ܻظ���־��
 * return: --
 */
void TransportTong::set_discard_tube_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ö��ܻظ���־��
	_discard_tube_response_flag=flag;
}

/**
 * name: get_discard_tube_response_flag
 * brief: ��ȡ���ܻظ���־��
 * param: --
 * return: ���ض��ܻظ���־��
 */
TransportTong::Flag TransportTong::get_discard_tube_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ض��ܻظ���־��
	return(_discard_tube_response_flag);
}

/**
 * name: set_take_tube_out_of_washing_disc_shake_hand_flag
 * brief: ���ô���ϴ��ȡ�����ֱ�־��
 * param: flag - ����Ĵ���ϴ��ȡ�����ֱ�־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_washing_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô���ϴ��ȡ�����ֱ�־��
	_take_tube_out_of_washing_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_washing_disc_shake_hand_flag
 * brief: ��ȡ����ϴ��ȡ�����ֱ�־��
 * param: --
 * return: ���ش���ϴ��ȡ�����ֱ�־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_washing_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش���ϴ��ȡ�����ֱ�־��
	return(_take_tube_out_of_washing_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_washing_disc_response_flag
 * brief: ���ô���ϴ��ȡ�ܻظ���־��
 * param: flag - ����Ĵ���ϴ��ȡ�ܻظ���־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_washing_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ô���ϴ��ȡ�ܻظ���־��
	_take_tube_out_of_washing_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_washing_disc_response_flag
 * brief: ��ȡ����ϴ��ȡ�ܻظ���־��
 * param: --
 * return: ���ش���ϴ��ȡ�ܻظ���־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_washing_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ش���ϴ��ȡ�ܻظ���־��
	return(_take_tube_out_of_washing_disc_response_flag);
}

/**
 * name: set_return_tube_to_reaction_disc_shake_hand_flag
 * brief: ����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
 * param: flag - �����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
 * return: --
 */
void TransportTong::set_return_tube_to_reaction_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
	_return_tube_to_reaction_disc_shake_hand_flag=flag;
}

/**
 * name: get_return_tube_to_reaction_disc_shake_hand_flag
 * brief: ��ȡת��ץ�ֻعܵ���Ӧ�����ֱ�־��
 * param: --
 * return: ����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
 */
TransportTong::Flag TransportTong::get_return_tube_to_reaction_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
	return(_return_tube_to_reaction_disc_shake_hand_flag);
}


/**
 * name: set_return_tube_to_reaction_disc_response_flag
 * brief: ����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
 * param: flag - �����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
 * return: --
 */
void TransportTong::set_return_tube_to_reaction_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
	_return_tube_to_reaction_disc_response_flag=flag;
}

/**
 * name: get_return_tube_to_reaction_disc_response_flag
 * brief: ��ȡת��ץ�ֻعܵ���Ӧ�̻ظ���־��
 * param: --
 * return: ����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
 */
TransportTong::Flag TransportTong::get_return_tube_to_reaction_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
	return(_return_tube_to_reaction_disc_response_flag);
}

/**
 * name: set_put_tube_in_detection_disc_shake_hand_flag
 * brief: ����ת��ץ�ַŹܵ���������ֱ�־��
 * param: flag - �����ת��ץ�ַŹܵ���������ֱ�־��
 * return: --
 */
void TransportTong::set_put_tube_in_detection_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ַŹܵ���������ֱ�־��
	_put_tube_in_detection_disc_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_detection_disc_shake_hand_flag
 * brief: ��ȡת��ץ�ַŹܵ���������ֱ�־��
 * param: --
 * return: ����ת��ץ�ַŹܵ���������ֱ�־��
 */
TransportTong::Flag TransportTong::get_put_tube_in_detection_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ַŹܵ���������ֱ�־��
	return(_put_tube_in_detection_disc_shake_hand_flag);
}

/**
 * name: set_put_tube_in_detection_disc_response_flag
 * brief: ����ת��ץ�ַŹܵ�����̻ظ���־��
 * param: flag - �����ת��ץ�ַŹܵ�����̻ظ���־��
 * return: --
 */
void TransportTong::set_put_tube_in_detection_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ַŹܵ�����̻ظ���־��
	_put_tube_in_detection_disc_response_flag=flag;
}

/**
 * name: get_put_tube_in_detection_disc_response_flag
 * brief: ��ȡת��ץ�ַŹܵ�����̻ظ���־��
 * param: --
 * return: ����ת��ץ�ַŹܵ�����̻ظ���־��
 */
TransportTong::Flag TransportTong::get_put_tube_in_detection_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ַŹܵ�����̻ظ���־��
	return(_put_tube_in_detection_disc_response_flag);
}

/**
 * name: set_take_tube_out_of_reaction_disc_shake_hand_flag
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
 * param: flag - �����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_reaction_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
	_take_tube_out_of_reaction_disc_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_of_reaction_disc_shake_hand_flag
 * brief: ��ȡת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
 * param: --
 * return: ����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_reaction_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
	return(_take_tube_out_of_reaction_disc_shake_hand_flag);
}

/**
 * name: set_take_tube_out_of_reaction_disc_response_flag
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
 * param: flag - �����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
 * return: --
 */
void TransportTong::set_take_tube_out_of_reaction_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
	_take_tube_out_of_reaction_disc_response_flag=flag;
}

/**
 * name: get_take_tube_out_of_reaction_disc_response_flag
 * brief: ��ȡת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
 * param: --
 * return: ����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
 */
TransportTong::Flag TransportTong::get_take_tube_out_of_reaction_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
	return(_take_tube_out_of_reaction_disc_response_flag);
}

/**
 * name: set_put_tube_in_washing_disc_shake_hand_flag
 * brief: ���÷Źܵ���ϴ�����ֱ�־��
 * param: flag - ����ķŹܵ���ϴ�����ֱ�־��
 * return: --
 */
void TransportTong::set_put_tube_in_washing_disc_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷Źܵ���ϴ�����ֱ�־��
	_put_tube_in_washing_disc_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_washing_disc_shake_hand_flag
 * brief: ��ȡ�Źܵ���ϴ������ָ���־��
 * param: --
 * return: ���طŹܵ���ϴ������ָ���־��
 */
TransportTong::Flag TransportTong::get_put_tube_in_washing_disc_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���طŹܵ���ϴ�����ֱ�־��
	return(_put_tube_in_washing_disc_shake_hand_flag);
}

/**
 * name: set_put_tube_in_washing_disc_response_flag
 * brief: ���÷Źܵ���ϴ�̻ظ���־��
 * param: flag - ����ķŹܵ���ϴ�̻ظ���־��
 * return: --
 */
void TransportTong::set_put_tube_in_washing_disc_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷Źܵ���ϴ�̻ظ���־��
	_put_tube_in_washing_disc_response_flag=flag;
}

/**
 * name: get_put_tube_in_washing_disc_response_flag
 * brief: ��ȡ�Źܵ���ϴ�̻ظ�ָ���־��
 * param: --
 * return: ���طŹܵ���ϴ�̻ظ�ָ���־��
 */
TransportTong::Flag TransportTong::get_put_tube_in_washing_disc_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���طŹܵ���ϴ�̻ظ���־��
	return(_put_tube_in_washing_disc_response_flag);
}