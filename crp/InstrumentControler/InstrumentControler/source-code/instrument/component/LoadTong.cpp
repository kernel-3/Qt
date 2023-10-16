#include"stdafx.h"
#include"LoadTong.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"TubeStorehouse.h"
#include"../communication/Command.h"
#include"../Instrument.h"
#include"../communication/Communications.h"
#include"../communication/ControlPort.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: LoadTong
 * brief: ���캯����
 * param: --
 * return: --
 */
LoadTong::LoadTong(void)
	:Component()
	,_lock(new MtLock)
	,_take_tube_out_shake_hand_flag(FLAG_IDLE)
	,_take_tube_out_response_flag(FLAG_IDLE)
	,_put_tube_in_shake_hand_flag(FLAG_IDLE)
	,_put_tube_in_response_flag(FLAG_IDLE)
	,_having_tube_flag(FALSE){
}

/**
 * name: ~LoadTong
 * brief: ����������
 * param: --
 * return: --
 */
LoadTong::~LoadTong(void){
	delete _lock;
}

/**
 * name: take_tube_out
 * brief: ����װ��ץ�ֵ�ָ��λ��ȡ�ܡ�
 * param: row - ����ָ��ȡ��λ�õ��С�
 *        col - ����ָ��ȡ��λ�õ��С�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LoadTong::take_tube_out(const unsigned int row,const unsigned int col){
	//1.�������Ĳ����Ƿ�Ϸ���
	if((row<1)||(row>TubeStorehouse::ROW_COUNT)){
		return(-1);
	}
	if((col<1)||(col>TubeStorehouse::COL_COUNT)){
		return(-2);
	}
	//2.����װ��ץ��ȡ��ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_load_tong_take_tube_out_command(row,col)<0){
		return(-3);
	}
	//3.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//4.���װ��ץ��ȡ�����ֱ���Լ�װ��ץ��ȡ�ܻظ���ǡ�
	set_take_tube_out_shake_hand_flag(FLAG_BUSY);
	set_take_tube_out_response_flag(FLAG_BUSY);
	//5.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("װ��ץ��ȡ��ָ��"))<0){
		return(-4);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: put_tube_in
 * breif: ����װ��ץ�ַŹܡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int LoadTong::put_tube_in(){
	//1.����װ��ץ�ַŹ�ָ������жϴ����Ƿ�ɹ���
	Command command;
	if(command.generate_load_tong_put_tube_in_command()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(get_control_lock());
	//3.���װ��ץ�ַŹ����ֱ���Լ�װ��ץ�ַŹܻظ���ǡ�
	set_put_tube_in_shake_hand_flag(FLAG_BUSY);
	set_put_tube_in_response_flag(FLAG_BUSY);
	//4.����ָ������ж�ָ����Ƿ�ɹ���
	if(command.send(*(((Instrument::instance())->
		get_communications())->get_control_port()),
		_T("װ��ץ�ַŹ�ָ��"))<0){
		return(-2);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_take_tube_out_shake_hand_flag
 * brief: ����ȡ�����ֱ�ǡ�
 * param: flag - �����ȡ�����ֱ�ǡ�
 * return: --
 */
void LoadTong::set_take_tube_out_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ȡ�����ֱ�ǡ�
	_take_tube_out_shake_hand_flag=flag;
}

/**
 * name: get_take_tube_out_shake_hand_flag
 * brief: ��ȡȡ�����ֱ�ǡ�
 * param: --
 * return: ����ȡ�����ֱ�ǡ�
 */
LoadTong::Flag LoadTong::get_take_tube_out_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ȡ�����ֱ�ǡ�
	return(_take_tube_out_shake_hand_flag);
}

/**
 * name: set_take_tube_out_response_flag
 * brief: ����ȡ�ܻظ���ǡ�
 * param: flag - �����ȡ�ܻظ���ǡ�
 * return: --
 */
void LoadTong::set_take_tube_out_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ȡ����ɱ�ǡ�
	_take_tube_out_response_flag=flag;
}

/**
 * name: get_take_tube_out_finish_flag
 * brief: ��ȡȡ�ܻظ���ʶ��
 * param: --
 * return: ����ȡ�ܻظ���ʶ��
 */
LoadTong::Flag LoadTong::get_take_tube_out_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����ȡ����ɱ�ǡ�
	return(_take_tube_out_response_flag);
}

/**
 * name: set_put_tube_in_shake_hand_flag
 * brief: ���÷Ź����ֱ�ǡ�
 * param: flag - ����ķŹ����ֱ�ǡ�
 * return: --
 */
void LoadTong::set_put_tube_in_shake_hand_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷Ź����ֱ�ǡ�
	_put_tube_in_shake_hand_flag=flag;
}

/**
 * name: get_put_tube_in_shake_hand_flag
 * breif: ��ȡ�Ź����ֱ�ǡ�
 * param: --
 * return: ���طŹ����ֱ�ǡ�
 */
LoadTong::Flag LoadTong::get_put_tube_in_shake_hand_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���طŹ����ֱ�ǡ�
	return(_put_tube_in_shake_hand_flag);
}

/**
 * name: set_put_tube_in_response_flag
 * breif: ���÷Źܻظ���ǡ�
 * param: flag - ����ķŹܻظ���ǡ�
 * return: --
 */
void LoadTong::set_put_tube_in_response_flag(const Flag flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���÷Ź����ֱ�ǡ�
	_put_tube_in_response_flag=flag;
}

/**
 * name: get_put_tube_in_response_flag
 * breif: ��ȡ�Źܻظ���ǡ�
 * param: --
 * return: ���طŹܻظ���ǡ�
 */
LoadTong::Flag LoadTong::get_put_tube_in_response_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���طŹ����ֱ�ǡ�
	return(_put_tube_in_response_flag);
}

/**
 * name: set_having_tube_flag
 * brief: ����װ��ץ���йܱ�ǡ�
 * param: flag - �����װ��ץ���йܱ�ǡ�
 * return: --
 */
void LoadTong::set_having_tube_flag(const BOOL flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����װ��ץ���йܱ�ǡ�
	_having_tube_flag=flag;
}

/**
 * name: get_having_tube_flag
 * brief: ��ȡװ��ץ���йܱ�ǡ�
 * param: --
 * return: ����װ��ץ���йܱ�ǡ�
 */
BOOL LoadTong::get_having_tube_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����״̬ץ���йܱ�ǡ�
	return(_having_tube_flag);
}