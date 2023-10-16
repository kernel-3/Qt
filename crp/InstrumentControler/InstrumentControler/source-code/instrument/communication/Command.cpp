#include"stdafx.h"
#include"Command.h"
#include"Port.h"
#include"../Instrument.h"
#include"../component/Components.h"
#include"../component/ReactionDisc.h"
#include"../../common/Logs.h"
#include"../component/LoadTong.h"
#include"../component/SpecimenDisc.h"
#include"../component/SpecimenArm.h"
#include"../component/ReagentArm.h"
#include"../component/ReagentDisc.h"
#include"../component/MagneticBeadDisc.h"
#include"../component/WashingDisc.h"
#include"../component/DetectionDisc.h"
#include"../component/TransportTong.h"
#include<MMSystem.h>

/**
 * name: calculate_parity_bit
 * breif: ����У��λ��
 * param: command - �����ָ��ָ�������ָ�롣
 *        length - �����ָ�����볤�ȣ�������У��λ������λ����
 *        parity_bit - ��������У��λ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
static int calculate_parity_bit(const unsigned char *command,
	const unsigned int length,unsigned char &parity_bit){
	//1.�������Ĳ����Ƿ�Ϸ���
	if((0==command)||(0==length)){
		return(-1);
	}
	//2.����ָ�����飬�ۼ�ָ��ͣ�������У��λ��
	unsigned int sum=0;
	for(unsigned int index=0;index<length;++index){
		sum+=command[index];
	}
	parity_bit=static_cast<unsigned char>(sum);
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: Command
 * brief: ���캯����
 * param: --
 * return: --
 */
Command::Command(void)
	:_command(0)
	,_size(0){
}

/**
 * name: Command
 * brief: ���캯����
 * param: command - �����ָ��ָ�������ָ�롣
 *        size - �����ָ������ߴ硣
 * return: --
 */
Command::Command(const unsigned char *command,const unsigned int size)
	:_command(0)
	,_size(0){
	if((0!=command)&&(size>0)){
		_command=new unsigned char[size];
		if(0!=_command){
			_size=size;
			memcpy(_command,command,size*sizeof(unsigned char));
		}
	}
}

/**
 * name: ~Command
 * breif: ����������
 * param: --
 * return: --
 */
Command::~Command(void){
	if(0!=_command){
		delete[] _command;
	}
}

/**
 * name: analysis
 * breif: ��ָ����н�����
 * param: port - �����ָ���˿ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis(Port &port) const{
	//1.��⵱ǰָ���Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(is_valid()<0){
		//1-1.��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld����Command::analysis �����У�\
�յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.�������е��˷��ش���
		return(-1);
	}
	//2.�Ե�ǰָ����н��ͷ�����
	//2-1.�����ǰָ���Ǹ��ϣ�PC->���أ�ָ�
	if(0x25==_command[1]){
		if(analysis_compound_command(port)<0){
			return(-2);
		}else{
			return(0);
		}
	}
	//2-2.�����ǰָ���Ǹ������֣�����->PC��ָ�
	else if(0xA5==_command[1]){
		if(analysis_compound_shake_handle_command()<0){
			return(-3);
		}else{
			return(0);
		}
	}
	//2-3.�����ǰָ���Ǹ��ϻظ�������->PC��ָ�
	else if(0xB5==_command[1]){
		if(analysis_compound_response_command()<0){
			return(-4);
		}else{
			return(0);
		}
	}
	//2-3.�����ǰָ���ǲ�ѯ��PC->���أ�ָ�
	else if(0x0D==_command[1]){
		if(analysis_inquire_command(port)<0){
			return(-5);
		}else{
			return(0);
		}
	}
	//2-4.�����ǰָ���ǲ�ѯ�ظ�������->PC��ָ�
	else if(0x8D==_command[1]){
		if(analysis_inquire_response_command()<0){
			return(-6);
		}else{
			return(0);
		}
	}
	//2-..�����ǰ��δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error Receive %s��%ld����Command::analysis��2�� "),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		log+=get_string();
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//..�������е��˷��ش���
		return(-9);
	}
}

/**
 * name: send
 * brief: ���͵�ǰָ�
 * param: port - �����ָ���˿ڡ�
 *        name - �����ָ�����ơ�
 *        is_logged - ������Ƿ���д��־��ǡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::send(Port &port,const CString &name/*=_T("")*/,
	const BOOL is_logged/*=TRUE*/) const{
	//1.��⵱ǰָ���Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);
	}
	//2.���͵�ǰָ������жϷ����Ƿ�ɹ���
	if(port.write(_command,_size)<0){
		return(-2);
	}
	//3.��д������־��
	if(is_logged){
		CString log(_T(""));
		log.Format(_T("Write %s��%ld���� %s"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime(),get_string());
		if(_T("")!=name){
			log+=_T(" ( ")+name+_T(" )");
		}
		log+=_T("��");
		Logs::instance()->write(Logs::NAME_COMMAND,log);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reaction_disc_rotation_command
 * breif: ���ɷ�Ӧ����תָ�
 * param: hole_no - ����Ŀ׺š�
 *        position - �����λ�á�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reaction_disc_rotation_command(
	const unsigned int hole_no,const unsigned int position){
	//1.������Ӧ����תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=11;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x06;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x03;
	command[7]=static_cast<unsigned char>(hole_no);
	command[8]=static_cast<unsigned char>(position);
	if(calculate_parity_bit(command,size-2,command[9])<0){
		delete[] command;
		return(-2);
	}
	command[10]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_command
 * brief: ����װ��ץ��ȡ��ָ�
 * param: row - ������Թܲ�ȡ����λ�á�
 *        col - ������Թܲ�ȡ����λ�á�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_take_tube_out_command(
	const unsigned int row,const unsigned int col){
	//1.����װ��ץ��ȡ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=11;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x06;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x02;
	command[7]=static_cast<unsigned char>(row);
	command[8]=static_cast<unsigned char>(col);
	if(calculate_parity_bit(command,size-2,command[9])<0){
		delete[] command;
		return(-2);
	}
	command[10]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_inquire_sensors_command
 * brief: ���ɴ�������ѯָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_inquire_sensors_command(){
	//1.������������ѯָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x0D;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x20;
	command[6]=0x04;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_command
 * breif: ����װ��ץ�ַŹ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_put_tube_in_command(){
	//1.����װ��ץ�ַŹ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x01;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_command
 * breif: ������������תָ�
 * param: rack_no - ����ļ��Ӻš�
 *        position_no - �����λ�úš�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_disc_rotation_command(
	const unsigned int rack_no,const unsigned int position_no){
	//1.������������תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=11;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x06;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x07;
	command[7]=static_cast<unsigned char>(rack_no);
	command[8]=static_cast<unsigned char>(position_no);
	if(calculate_parity_bit(command,size-2,command[9])<0){
		delete[] command;
		return(-2);
	}
	command[10]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_suck_command
 * brief: ������������ȡָ�
 * param: suck_volume - �������ȡ�����
 *        cup_type - ��������������͡�
 *        liquid_level_probe_switch - �����Һλ̽�⿪�ء�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_suck_command(const unsigned int suck_volume,
	const unsigned int cup_type,const BOOL liquid_level_probe_switch){
	//1.������������ȡָ������жϴ����Ƿ�ɹ���
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x05;
	command[7]=static_cast<unsigned char>((suck_volume>>8)&0xFF);
	command[8]=static_cast<unsigned char>(suck_volume&0xFF);
	if(liquid_level_probe_switch){
		command[9]=0x01;
	}else{
		command[9]=0x00;
	}
	command[10]=static_cast<unsigned char>(cup_type);
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_spit_command
 * breif: ������������Һָ�
 * param: spit_volume - �������Һ�����
 *        down_steps - ������������½�������
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_spit_command(
	const unsigned int spit_volume,const unsigned int down_steps){
	//1.������������Һָ������жϴ����Ƿ�ɹ���
	const unsigned int size=15;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x0A;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x04;
	command[7]=static_cast<unsigned char>((spit_volume>>8)&0xFF);
	command[8]=static_cast<unsigned char>(spit_volume&0xFF);
	command[9]=static_cast<unsigned char>((down_steps>>24)&0xFF);
	command[10]=static_cast<unsigned char>((down_steps>>16)&0xFF);
	command[11]=static_cast<unsigned char>((down_steps>>8)&0xFF);
	command[12]=static_cast<unsigned char>(down_steps&0xFF);
	if(calculate_parity_bit(command,size-2,command[13])<0){
		delete[] command;
		return(-2);
	}
	command[14]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_wash_command
 * brief: ������������ϴָ�
 * param: outer_wash_time - ����������ϴʱ�䡣
 *        inner_wash_time - ������ڱ���ϴʱ�䡣
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_wash_command(
	const unsigned int outer_wash_time,const unsigned int inner_wash_time){
	//1.������������ϴָ������жϴ����Ƿ�ɹ���
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x06;
	command[7]=static_cast<unsigned char>((outer_wash_time>>8)&0xFF);
	command[8]=static_cast<unsigned char>(outer_wash_time&0xFF);
	command[9]=static_cast<unsigned char>((inner_wash_time>>8)&0xFF);
	command[10]=static_cast<unsigned char>(inner_wash_time&0xFF);
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_suck_command
 * brief: �����Լ�����ȡָ�
 * param: suck_volume - �������ȡ�����
 *        reagent_type - ������Լ����͡�
 *        liquid_level_probe_switch - �����Һλ̽�⿪�ء�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_suck_command(const unsigned int suck_volume,
	const unsigned int reagent_type,const BOOL liquid_level_probe_switch){
	//1.�����Լ�����ȡָ������жϴ����Ƿ�ɹ���
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x09;
	command[7]=static_cast<unsigned char>((suck_volume>>8)&0xFF);
	command[8]=static_cast<unsigned char>(suck_volume&0xFF);
	if(liquid_level_probe_switch){
		command[9]=0x01;
	}else{
		command[9]=0x00;
	}
	command[10]=static_cast<unsigned char>(reagent_type);
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_spit_command
 * brief: �����Լ�����Һָ�
 * param: spit_volume - �������Һ�����
 *        down_steps - ������Լ����½�������
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_spit_command(
	const unsigned int spit_volume,const unsigned int down_steps){
	//1.�����Լ�����Һָ������жϴ����Ƿ�ɹ���
	const unsigned int size=15;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x0A;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x08;
	command[7]=static_cast<unsigned char>((spit_volume>>8)&0xFF);
	command[8]=static_cast<unsigned char>(spit_volume&0xFF);
	command[9]=static_cast<unsigned char>((down_steps>>24)&0xFF);
	command[10]=static_cast<unsigned char>((down_steps>>16)&0xFF);
	command[11]=static_cast<unsigned char>((down_steps>>8)&0xFF);
	command[12]=static_cast<unsigned char>(down_steps&0xFF);
	if(calculate_parity_bit(command,size-2,command[13])<0){
		delete[] command;
		return(-2);
	}
	command[14]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_wash_command
 * brief: �����Լ�����ϴָ�
 * param: outer_wash_time - ����������ϴʱ�䡣
 *        inner_wash_time - ������ڱ���ϴʱ�䡣
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_wash_command(
	const unsigned int outer_wash_time,const unsigned int inner_wash_time){
	//1.�����Լ�����ϴָ������жϴ����Ƿ�ɹ���
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x10;
	command[7]=static_cast<unsigned char>((outer_wash_time>>8)&0xFF);
	command[8]=static_cast<unsigned char>(outer_wash_time&0xFF);
	command[9]=static_cast<unsigned char>((inner_wash_time>>8)&0xFF);
	command[10]=static_cast<unsigned char>(inner_wash_time&0xFF);
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_command
 * brief: �����Լ�����תָ�
 * param: reagent_type - ������Լ����͡�
 *        position_no - �����λ�úš�
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_disc_rotation_command(
	const unsigned int reagent_type,const unsigned int position_no){
	//1.�����Լ�����תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=11;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x06;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x11;
	command[7]=static_cast<unsigned char>(reagent_type);
	command[8]=static_cast<unsigned char>(position_no);
	if(calculate_parity_bit(command,size-2,command[9])<0){
		delete[] command;
		return(-2);
	}
	command[10]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_command
 * brief: ���ɴ�������ת���
 * param: position_no - �����λ�úš�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_rotation_command(
	const unsigned int position_no){
	//1.������������תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=10;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x05;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x12;
	command[7]=static_cast<unsigned char>(position_no);
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_command
 * brief: ���ɴ����̻�����ת���
 * param: direction - �������ת����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_command(
	const unsigned int direction){
	//1.���������̻�����תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=10;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x05;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x25;
	command[7]=static_cast<unsigned char>(direction);
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_rotation_command
 * brief: ������ϴ����תָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_rotation_command(){
	//1.������ϴ����תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x24;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_disc_rotation_command
 * brief: ���ɼ������תָ�
 * param: hole_no - ����Ŀ׺š�
 *        position - �����λ�á�
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_disc_rotation_command(
	const unsigned int hole_no,const unsigned int position){
	//1.������ϴ����תָ������жϴ����Ƿ�ɹ���
	const unsigned int size=11;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x06;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x21;
	command[7]=static_cast<unsigned char>(hole_no);
	command[8]=static_cast<unsigned char>(position);
	if(calculate_parity_bit(command,size-2,command[9])<0){
		delete[] command;
		return(-2);
	}
	command[10]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_command
 * brief: ���ɴӼ����ȡ��ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_detection_disc_command(){
	//1.�����Ӽ����ȡ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x18;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_discard_tube_command
 * brief: ���ɶ���ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_discard_tube_command(){
	//1.�����Ӷ���ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x19;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_wash_command
 * brief: ������ϴ����ϴָ�
 * param: substrate_type - ����ĵ������͡�
 *        substrate_volume - ����ĵ��������
 *        washing_liquid_volume - �������ϴҺ�����
 *        is_washing_position_1_need_washing - ������Ƿ���ϴ��ϴλ��1��־��
 *        is_washing_position_2_need_washing - ������Ƿ���ϴ��ϴλ��2��־��
 *        is_washing_position_3_need_washing - ������Ƿ���ϴ��ϴλ��3��־��
 *        is_washing_position_4_need_washing - ������Ƿ���ϴ��ϴλ��4��־��
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_wash_command(const unsigned int substrate_type,
	const unsigned int substrate_volume,const unsigned int washing_liquid_volume,
	const BOOL is_washing_position_1_need_washing,const BOOL is_washing_position_2_need_washing,
	const BOOL is_washing_position_3_need_washing,const BOOL is_washing_position_4_need_washing){
	//1.������ϴ����ϴָ������жϴ����Ƿ�ɹ���
	const unsigned int size=15;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x0A;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x20;
	command[7]=static_cast<unsigned char>(substrate_type);
	command[8]=static_cast<unsigned char>((substrate_volume>>8)&0xFF);
	command[9]=static_cast<unsigned char>(substrate_volume&0xFF);
	command[10]=static_cast<unsigned char>((washing_liquid_volume>>8)&0xFF);
	command[11]=static_cast<unsigned char>(washing_liquid_volume&0xFF);
	command[12]=0x00;
	if(is_washing_position_1_need_washing){
		command[12]|=0x01;
	}
	if(is_washing_position_2_need_washing){
		command[12]|=0x02;
	}
	if(is_washing_position_3_need_washing){
		command[12]|=0x04;
	}
	if(is_washing_position_4_need_washing){
		command[12]|=0x08;
	}
	if(calculate_parity_bit(command,size-2,command[13])<0){
		delete[] command;
		return(-2);
	}
	command[14]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_command
 * brief: ���ɴ���ϴ��ȡ��ָ�
 * param: stop_position - �����ֹͣλ�á�
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_washing_disc_command(
	const unsigned int stop_position){
	//1.��������ϴ��ȡ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=10;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x05;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x15;
	command[7]=static_cast<unsigned char>(stop_position);
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_command
 * brief: ����ת��ץ�ֻعܵ���Ӧ��ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_return_tube_to_reaction_disc_command(){
	//1.����ת��ץ�ֻعܵ���Ӧ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x14;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_command
 * brief: ����ת��ץ�ַŹܵ������ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_detection_disc_command(){
	//1.����ת��ץ�ּ���̷Ź�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x17;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_command
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ�����
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_reaction_disc_command(){
	//1.����ת��ץ�ִӷ�Ӧ��ȡ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x13;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_command
 * brief: ������ϴץ�ַŹܵ���ϴ��ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_washing_disc_command(){
	//1.����ת��ץ�ַŹܵ���ϴ��ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x16;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_command
 * brief: ���ɼ��ָ�
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_command(){
	//1.�������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x25;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x00;
	command[5]=0x10;
	command[6]=0x23;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰָ���Ƿ�Ϸ���
 * param: --
 * return: �����ǰָ��Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::is_valid() const{
	//1.���ָ��洢�ռ��Ƿ�Ϸ���
	if((0==_command)||(0==_size)){
		return(-1);
	}
	//2.���ָ����Ƿ�������С���ȡ�
	if(_size<MIN_LENGTH){
		return(-2);
	}
	//3.��⵱ǰָ����ʼλ�Ƿ�Ϸ���
	if(Command::START_BIT!=_command[0]){
		return(-3);
	}
	//4.��⵱ǰָ���λ�Ƿ�Ϸ���
	if(_command[2]!=static_cast<unsigned char>(_size-5)){
		return(-4);
	}
	//5.��⵱ǰָ�����λ�Ƿ�Ϸ���
	if(Command::END_BIT!=_command[_size-1]){
		return(-5);
	}
	//6.���У��λ�Ƿ�Ϸ���
	//6-1.����ָ��У��λ��
	unsigned char parity_bit=0;
	if(calculate_parity_bit(
		_command,_size-2,parity_bit)<0){
		return(-6);
	}
	//6-2.���У��λ�Ƿ�Ϸ���
	if(_command[_size-2]!=parity_bit){
		return(-7);
	}
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: analysis_compound_command
 * breif: �Ը���ָ����н�����
 * param: port - �����ָ���˿ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis_compound_command(Port &port) const{
	//1.�����ǰ��װ��ץ�ַŹ�ָ�
	if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x01==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_load_tong_put_tube_in_shake_hand_command()<0){
			return(-1);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-2);
			}else{
				Command response;
				if(response.generate_load_tong_put_tube_in_response_command()<0){
					return(-3);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-4);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//2.�����ǰ��װ��ץ��ȡ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x02==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_load_tong_take_tube_out_shake_hand_command()<0){
			return(-5);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-6);
			}else{
				Command response;
				if(response.generate_load_tong_take_tube_out_response_command()<0){
					return(-7);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-8);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//3.�����ǰ�Ƿ�Ӧ��ת��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x03==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_reaction_disc_rotation_shake_hand_command()<0){
			return(-9);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-10);
			}else{
				Command response;
				if(response.generate_reaction_disc_rotation_response_command()<0){
					return(-11);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-12);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//4.�����ǰ�����������ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x04==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_specimen_arm_spit_shake_hand_command()<0){
			return(-13);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-14);
			}else{
				Command response;
				if(response.generate_specimen_arm_spit_response_command()<0){
					return(-15);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-16);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//5.�����ǰ����������ȡָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x05==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_specimen_arm_suck_shake_hand_command()<0){
			return(-17);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-18);
			}else{
				Command response;
				if(response.generate_specimen_arm_suck_response_command()<0){
					return(-19);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-20);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//6.�����ǰ����������ϴָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x06==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_specimen_arm_wash_shake_hand_command()<0){
			return(-21);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-22);
			}else{
				Command response;
				if(response.generate_specimen_arm_wash_response_command()<0){
					return(-23);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-24);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//7.�����ǰ��������ת��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x07==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_specimen_disc_rotation_shake_hand_command()<0){
			return(-25);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-26);
			}else{
				Command response;
				if(response.generate_specimen_disc_rotation_response_command()<0){
					return(-27);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-28);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//8.�����ǰ���Լ�����Һָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x08==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_reagent_arm_spit_shake_hand_command()<0){
			return(-29);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-30);
			}else{
				Command response;
				if(response.generate_reagent_arm_spit_response_command()<0){
					return(-21);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-32);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//9.�����ǰ���Լ�����ȡָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x09==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_reagent_arm_suck_shake_hand_command()<0){
			return(-33);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-34);
			}else{
				Command response;
				if(response.generate_reagent_arm_suck_response_command()<0){
					return(-35);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-36);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//10.�����ǰ���Լ�����ϴָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x10==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_reagent_arm_wash_shake_hand_command()<0){
			return(-37);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-38);
			}else{
				Command response;
				if(response.generate_reagent_arm_wash_response_command()<0){
					return(-39);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-40);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//11.�����ǰ���Լ�����תָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x11==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_reagent_disc_rotation_shake_hand_command()<0){
			return(-41);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-42);
			}else{
				Command response;
				if(response.generate_reagent_disc_rotation_response_command()<0){
					return(-43);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-44);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//12.�����ǰ�Ǵ�������תָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x12==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_magnetic_bead_disc_rotation_shake_hand_command()<0){
			return(-45);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-46);
			}else{
				Command response;
				if(response.generate_magnetic_bead_disc_rotation_response_command()<0){
					return(-47);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-48);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//13.�����ǰ��ת��ץ�ִӷ�Ӧ��ȡ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x13==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_take_tube_out_of_reaction_disc_shake_hand_command()<0){
			return(-49);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-50);
			}else{
				Command response;
				if(response.generate_take_tube_out_of_reaction_disc_response_command()<0){
					return(-51);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-52);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//14.�����ǰ��ת��ץ�ֻعܵ���Ӧ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x14==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_return_tube_to_reaction_disc_shake_hand_command()<0){
			return(-53);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-54);
			}else{
				Command response;
				if(response.generate_return_tube_to_reaction_disc_response_command()<0){
					return(-55);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-56);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//15.�����ǰ�Ǵ���ϴ��ȡ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x15==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_take_tube_out_of_washing_disc_shake_hand_command()<0){
			return(-57);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-58);
			}else{
				Command response;
				if(response.generate_take_tube_out_of_washing_disc_response_command()<0){
					return(-59);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-60);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//16.�����ǰ��ת��ץ�ַŹܵ���ϴ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x16==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_put_tube_in_washing_disc_shake_hand_command()<0){
			return(-61);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-62);
			}else{
				Command response;
				if(response.generate_put_tube_in_washing_disc_response_command()<0){
					return(-63);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-64);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//17.�����ǰ��ת��ץ�ַŹܵ������ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x17==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_put_tube_in_detection_disc_shake_hand_command()<0){
			return(-65);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-66);
			}else{
				Command response;
				if(response.generate_put_tube_in_detection_disc_response_command()<0){
					return(-67);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-68);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//18.�����ǰ�ǴӼ����ȡ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x18==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_take_tube_out_of_detection_disc_shake_hand_command()<0){
			return(-69);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-70);
			}else{
				Command response;
				if(response.generate_take_tube_out_of_detection_disc_response_command()<0){
					return(-71);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-72);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//19.�����ǰ�Ƕ���ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x19==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_discard_tube_shake_hand_command()<0){
			return(-73);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-74);
			}else{
				Command response;
				if(response.generate_discard_tube_response_command()<0){
					return(-75);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-76);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//20.�����ǰ����ϴ����ϴָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x20==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_washing_disc_wash_shake_hand_command()<0){
			return(-77);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-78);
			}else{
				Command response;
				if(response.generate_washing_disc_wash_response_command()<0){
					return(-79);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-80);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//21.�����ǰ�Ǽ������תָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x21==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_detection_disc_rotation_shake_hand_command()<0){
			return(-81);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-82);
			}else{
				Command response;
				if(response.generate_detection_disc_rotation_response_command()<0){
					return(-83);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-84);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//23.�����ǰ�Ǽ��ָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x23==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_detection_shake_hand_command()<0){
			return(-85);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-86);
			}else{
				Command response;
				if(response.generate_detection_response_command()<0){
					return(-87);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-88);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//24.�����ǰ����ϴ����תָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x24==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_washing_disc_rotation_shake_hand_command()<0){
			return(-89);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-90);
			}else{
				Command response;
				if(response.generate_washing_disc_rotation_response_command()<0){
					return(-91);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-92);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//25.�����ǰ�Ǵ����̻�����תָ�
	else if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x10==_command[5])&&(0x25==_command[6])){
		Command shake_handle;
		if(shake_handle.generate_magnetic_bead_disc_mixing_rotation_shake_hand_command()<0){
			return(-93);
		}else{
			if(shake_handle.send(port,_T(""),FALSE)<0){
				return(-94);
			}else{
				Command response;
				if(response.generate_magnetic_bead_disc_mixing_rotation_response_command()<0){
					return(-95);
				}else{
					if(response.send(port,_T(""),FALSE)<0){
						return(-96);
					}else{
						return(0);
					}
				}
			}
		}
	}
	//..������յ�δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Command::analysis_compound_command \
�������յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..�������е��˷��ش���
		return(-97);
	}
}

/**
 * name: analysis_compound_shake_handle_command
 * breif: �Ը�������ָ����н�����
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis_compound_shake_handle_command() const{
	//1.�����ǰ���յ�����װ��ץ�ַŹ�����ָ�
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x01==_command[6])){
		//1-1.����װ��ץ�ַŹ����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_put_tube_in_shake_hand_flag(
			LoadTong::FLAG_IDLE);
		//1-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��װ��ץ�ַŹ�����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.�������е��˳ɹ����ء�
		return(0);
	}
	//2.�����ǰ���յ�����װ��ץ��ȡ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x02==_command[6])){
		//2-1.����װ��ץ��ȡ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_take_tube_out_shake_hand_flag(
			LoadTong::FLAG_IDLE);
		//2-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��װ��ץ��ȡ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//2-3.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ���յ����Ƿ�Ӧ����ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x03==_command[6])){
		//3-1.���÷�Ӧ����ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_rotation_shake_hand_flag(
			ReactionDisc::FLAG_IDLE);
		//3-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����Ӧ����ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
	//4.�����ǰ���յ�������������Һ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x04==_command[6])){
		//4-1.������������Һ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_spit_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//4-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������Һ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//4-3.�������е��˳ɹ����ء�
		return(0);
	}
	//5.�����ǰ���յ�������������ȡ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x05==_command[6])){
		//5-1.������������ȡ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_suck_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//5-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������Һ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//5-3.�������е��˳ɹ����ء�
		return(0);
	}
	//6.�����ǰ���յ�������������ϴ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x06==_command[6])){
		//6-1.������������ϴ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//6-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ϴ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//6-3.�������е��˳ɹ����ء�
		return(0);
	}
	//7.�����ǰ���յ�������������ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x07==_command[6])){
		//7-1.������������ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_disc())->set_rotation_shake_hand_flag(
			ReactionDisc::FLAG_IDLE);
		//7-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//7-3.�������е��˳ɹ����ء�
		return(0);
	}
	//8.�����ǰ���յ������Լ�����Һ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x08==_command[6])){
		//8-1.�����Լ�����Һ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_spit_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//8-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����Һ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//8-3.�������е��˳ɹ����ء�
		return(0);
	}
	//9.�����ǰ���յ������Լ�����ȡ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x09==_command[6])){
		//9-1.������������ȡ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_suck_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//9-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����Һ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//9-3.�������е��˳ɹ����ء�
		return(0);
	}
	//10.�����ǰ���յ������Լ�����ϴ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x10==_command[6])){
		//10-1.�����Լ�����ϴ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//10-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����ϴ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//10-3.�������е��˳ɹ����ء�
		return(0);
	}
	//11.�����ǰ���յ������Լ�����ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x11==_command[6])){
		//11-1.�����Լ�����ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_reagent_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//11-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//11-3.�������е��˳ɹ����ء�
		return(0);
	}
	//12.�����ǰ���յ����Ǵ�������ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x12==_command[6])){
		//12-1.���ô�������ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//12-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//12-3.�������е��˳ɹ����ء�
		return(0);
	}
	//13.�����ǰ���յ�����ת��ץ�ִӷ�Ӧ��ȡ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x13==_command[6])){
		//13-1.����ת��ץ�ִӷ�Ӧ��ȡ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_reaction_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//13-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִӷ�Ӧ��ȡ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//13-3.�������е��˳ɹ����ء�
		return(0);
	}
	//14.�����ǰ�յ�����ת��ץ�ֻعܵ���Ӧ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x14==_command[6])){
		//14-1.����ת��ץ�ֻعܵ���Ӧ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_return_tube_to_reaction_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//14-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ֻعܵ���Ӧ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//14-3.�������е��˳ɹ����ء�
		return(0);
	}
	//15.�����ǰ�յ����Ǵ���ϴ��ȡ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x15==_command[6])){
		//15-1.���ô���ϴ��ȡ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_washing_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//15-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִ���ϴ��ȡ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//15-3.�������е��˳ɹ����ء�
		return(0);
	}
	//16.�����ǰ�յ�����ת��ץ�ַŹܵ���ϴ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x16==_command[6])){
		//16-1.����ת��ץ�ַŹܵ���ϴ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_washing_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//16-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ַŹܵ���ϴ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//16-3.�������е��˳ɹ����ء�
		return(0);
	}
	//17.�����ǰ�յ�����ת��ץ�ַŹܵ����������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x17==_command[6])){
		//17-1.����ת��ץ�ַŹܵ���������ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_detection_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//17-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ַŹܵ����������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//17-3.�������е��˳ɹ����ء�
		return(0);
	}
	//18.�����ǰ�յ����ǴӼ����ȡ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x18==_command[6])){
		//18-1.���ôӼ����ȡ�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_detection_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//18-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִӼ����ȡ������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//18-3.�������е��˳ɹ����ء�
		return(0);
	}
	//19.�����ǰ�յ����Ƕ�������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x19==_command[6])){
		//19-1.����ת��ץ�ֶ������ֱ�־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->set_discard_tube_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//19-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ֶ�������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//19-3.�������е��˳ɹ����ء�
		return(0);
	}
	//20.�����ǰ�յ�������ϴ����ϴ����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x20==_command[6])){
		//20-1.������ϴ����ϴ���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//20-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����ϴ����ϴ����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//20-3.�������е��˳ɹ����ء�
		return(0);
	}
	//21.�����ǰ�յ����Ǽ������ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x21==_command[6])){
		//21-1.���ü������ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//21-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���������ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//21-3.�������е��˳ɹ����ء�
		return(0);
	}
	//23.�����ǰ�յ����Ǽ������ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x23==_command[6])){
		//23-1.���ü�����ֱ�־��
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_detect_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//23-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//23-3.�������е��˳ɹ����ء�
		return(0);
	}
	//24.�����ǰ�յ�������ϴ����ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x24==_command[6])){
		//24-1.������ϴ����ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//24-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����ϴ����ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//24-3.�������е��˳ɹ����ء�
		return(0);
	}
	//25.�����ǰ�յ����Ǵ����̻�����ת����ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x25==_command[6])){
		//25-1.���ô����̻�����ת���ֱ�־��
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_mixing_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//25-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s�������̻�����ת����ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//25-3.�������е��˳ɹ����ء�
		return(0);
	}
	//..������յ�δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Command::analysis_compound_shake_handle_command \
�����У��յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..�������е��˷��ش���
		return(-1);
	}
}

/**
 * name: analysis_compound_response_command
 * brief: �Ը������ָ����н�����
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis_compound_response_command() const{
	//1.�����ǰ���յ�����װ��ץ�ַŹܻظ�ָ�
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x01==_command[6])){
		//1-1.����װ��ץ�ַŹܻظ���־��
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_put_tube_in_response_flag(
			LoadTong::FLAG_IDLE);
		//1-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��װ��ץ�ַŹܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.�������е��˳ɹ����ء�
		return(0);
	}
	//2.�����ǰ���յ�����װ��ץ��ȡ�ܻظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x02==_command[6])){
		//2-1.����װ��ץ��ȡ�ܻظ���־��
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_take_tube_out_response_flag(
			LoadTong::FLAG_IDLE);
		//2-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��װ��ץ��ȡ�ܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//2-3.�������е��˳ɹ����ء�
		return(0);
	}
	//3.�����ǰ���յ����Ƿ�Ӧ����ת���ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x03==_command[6])){
		//3-1.���÷�Ӧ����ת��ɱ�־��
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//3-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����Ӧ����ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//3-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//4.�����ǰ�յ�������������Һ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x04==_command[6])){
		//4-1.������������Һ�ظ���־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_spit_response_flag(
			SpecimenArm::FLAG_IDLE);
		//4-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������Һ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//4-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//5.�����ǰ�յ�������������ȡ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x05==_command[6])){
		//5-1.������������ȡ�ظ���־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_suck_response_flag(
			SpecimenArm::FLAG_IDLE);
		//5-2.����������Һλ̽��߶ȡ�
		unsigned int height=0;
		height|=_command[7];
		height<<=8;
		height|=_command[8];
		height<<=8;
		height|=_command[9];
		height<<=8;
		height|=_command[10];
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_liquid_level_height(height);
		//5-3.��д�����־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� ��������Һʱ��Һλ�߶�Ϊ%ld��"),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),height);
		Logs::instance()->write(Logs::NAME_EVENT,log);
		log.Format(_T("Receive %s��%ld���� %s����������Һ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//5-4.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//6.�����ǰ���յ�������������ϴ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x06==_command[6])){
		//6-1.���÷�Ӧ����ת��ɱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//6-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ϴ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//6-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//7.�����ǰ���յ�������������ת���ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x07==_command[6])){
		//7-1.���÷�Ӧ����ת��ɱ�־��
		(((Instrument::instance())->get_components())->
			get_specimen_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//7-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ת���ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//7-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//8.�����ǰ�յ������Լ�����Һ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x08==_command[6])){
		//8-1.�����Լ�����Һ�ظ���־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_spit_response_flag(
			SpecimenArm::FLAG_IDLE);
		//8-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����Һ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//8-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//9.�����ǰ�յ������Լ�����ȡ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x09==_command[6])){
		//9-1.�����Լ�����ȡ�ظ���־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_suck_response_flag(
			SpecimenArm::FLAG_IDLE);
		//9-2.�����Լ���Һλ̽��߶ȡ�
		unsigned int height=0;
		height|=_command[7];
		height<<=8;
		height|=_command[8];
		height<<=8;
		height|=_command[9];
		height<<=8;
		height|=_command[10];
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_liquid_level_height(height);
		//9-3.��д�����־��
		CString log(_T(""));
		log.Format(_T("Event %s��%ld���� �Լ�����Һʱ��Һλ�߶�Ϊ%ld��"),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),height);
		Logs::instance()->write(Logs::NAME_EVENT,log);
		log.Format(_T("Receive %s��%ld���� %s���Լ�����Һ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//9-4.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//10.�����ǰ���յ������Լ�����ϴ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x10==_command[6])){
		//10-1.�����Լ�����ϴ�ظ���־��
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//10-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����ϴ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//10-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//11.�����ǰ���յ������Լ�����ת�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x11==_command[6])){
		//11-1.�����Լ�����ת�ظ���־��
		(((Instrument::instance())->get_components())->
			get_reagent_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//11-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���Լ�����ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//11-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//12.�����ǰ���յ����Ǵ�������ת�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x12==_command[6])){
		//12-1.���ô�������ת�ظ���־��
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//12-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����������ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//12-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//13.�����ǰ���յ�����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x13==_command[6])){
		//13-1.����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_reaction_disc_response_flag(
			SpecimenArm::FLAG_IDLE);
		//13-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִӷ�Ӧ��ȡ�ܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//13-3.�������е��˳ɹ����ء�
		return(0);
	}
	//14.�����ǰ���յ���ת��ץ�ֻعܵ���Ӧ�̻ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x14==_command[6])){
		//14-1.����ת��ץ�ֻعܵ���Ӧ�̻ظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_return_tube_to_reaction_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//14-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ֻعܵ���Ӧ�̻ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//14-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//15.�����ǰ���յ����Ǵ���ϴ��ȡ�ܻظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x15==_command[6])){
		//15-1.���ô���ϴ��ȡ�ܻظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_washing_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//15-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִ���ϴ��ȡ�ܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//15-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//16.�����ǰ���յ�����ת��ץ�ַŹܵ���ϴ�̻ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x16==_command[6])){
		//16-1.����ת��ץ�ַŹܵ���ϴ�̻ظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_washing_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//16-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ַŹܵ���ϴ�̻ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//16-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//17.�����ǰ�յ�����ת��ץ�ַŹܵ�����̻ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x17==_command[6])){
		//17-1.����ת��ץ�ַŹܵ�����̻ظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_detection_disc_response_flag(
			SpecimenArm::FLAG_IDLE);
		//17-2.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ַŹܵ�����̻ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//17-3.�������е��˳ɹ����ء�
		return(0);
	}
	//18.�����ǰ���յ����ǴӼ����ȡ�ܻظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x18==_command[6])){
		//18-1.���ôӼ����ȡ�ܻظ���־��
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_detection_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//18-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ִӼ����ȡ�ܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//18-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//19.�����ǰ���յ����Ƕ��ܻظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x19==_command[6])){
		//19-1.���ö��ܻظ���־��
		if(0x00==_command[7]){
			(((Instrument::instance())->get_components())->
				get_transport_tong())->set_discard_tube_response_flag(
				ReactionDisc::FLAGE_EMPTY);
		}else{
			(((Instrument::instance())->get_components())->
				get_transport_tong())->set_discard_tube_response_flag(
				ReactionDisc::FLAGE_USED);
		}
		//19-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s��ת��ץ�ֶ��ܻظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//19-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//20.�����ǰ���յ�������ϴ����ϴ�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x20==_command[6])){
		//20-1.������ϴ����ϴ�ظ�ָ�
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//20-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����ϴ����ϴ�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//20-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//21.�����ǰ���յ����Ǽ������ת�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x21==_command[6])){
		//21-1.���ü������ת�ظ���־��
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//21-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���������ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//21-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//23.�����ǰ�յ����Ǽ��ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x23==_command[6])){
		//23-1.���ü��ظ���־��
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_detect_response_flag(
			SpecimenArm::FLAG_IDLE);
		//23-2.����ظ�ָ���з��صķ���ֵ��
		unsigned int luminous=0;
		luminous|=_command[7];
		luminous<<=8;
		luminous|=_command[8];
		luminous<<=8;
		luminous|=_command[9];
		luminous<<=8;
		luminous|=_command[10];
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_luminous(luminous);
		//23-3.��д��־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s���������ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//23-4.�������е��˳ɹ����ء�
		return(0);
	}
	//24.�����ǰ���յ�������ϴ����ת�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x24==_command[6])){
		//24-1.������ϴ����ת�ظ���־��
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//24-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����ϴ����ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//24-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//25.�����ǰ���յ����Ǵ����̻�����ת�ظ�ָ�
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x25==_command[6])){
		//25-1.���ô����̻�����ת�ظ���־��
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_mixing_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//25-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s�������̻�����ת�ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//25-3.�������е���ֱ�ӷ��ء�
		return(0);
	}
	//..������յ�δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Command::analysis_compound_response_command \
�����У��յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..�������е��˷��ش���
		return(-1);
	}
}

/**
 * name: analysis_inquire_command
 * brief: �Բ�ѯָ����н�����
 * param: port - �����ָ���˿ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis_inquire_command(Port &port) const{
	//1.�����ǰ���յ����ǲ�ѯλ�ô�����ָ�
	if((0x00==_command[3])&&(0x00==_command[4])&&(
		0x20==_command[5])&&(0x04==_command[6])){
		Command sensors_state;
		if(sensors_state.generate_inquire_sensors_response_command()<0){
			return(-1);
		}else if(sensors_state.send(port,_T(""),FALSE)<0){
			return(-2);
		}else{
			return(0);
		}
	}
	//..������յ�δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Command::analysis_inquire_command \
�����У��յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..�������е��˷��ش���
		return(-1);
	}
}

/**
 * name: analysis_inquire_response_command
 * brief: �Բ�ѯ�ظ�ָ����н�����
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::analysis_inquire_response_command() const{
	//1.�����ǰ���յ����ǲ�ѯλ�ô������ظ�ָ�
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x20==_command[5])&&(0x04==_command[6])){
		//1-1.�����ѯλ�ô������ظ�ָ���а����Ĵ�����״̬����������Ӧ�ı�ǡ�
		if(_command[7]&0x01){
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_entry_flag(
				LoadTong::FLAGE_USED);
		}else{
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_entry_flag(
				LoadTong::FLAGE_EMPTY);
		}
		if(_command[7]&0x02){
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_exit_flag(
				LoadTong::FLAGE_USED);
		}else{
			(((Instrument::instance())->get_components())->
				get_reaction_disc())->set_having_tube_in_exit_flag(
				LoadTong::FLAGE_EMPTY);
		}
		if(_command[7]&0x04){
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_entry_flag(
				LoadTong::FLAGE_USED);
		}else{
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_entry_flag(
				LoadTong::FLAGE_EMPTY);
		}
		if(_command[7]&0x08){
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_exit_flag(
				LoadTong::FLAGE_USED);
		}else{
			(((Instrument::instance())->get_components())->
				get_washing_disc())->set_having_tube_in_exit_flag(
				LoadTong::FLAGE_EMPTY);
		}
		//1-2.��д�����־��
		CString log(_T(""));
		log.Format(_T("Receive %s��%ld���� %s����ѯ�������ظ�ָ���"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.�������е��˳ɹ����ء�
		return(0);
	}
	//..������յ�δָ֪�
	else{
		//..��д��־��
		CString log(_T(""));
		log.Format(_T("Error %s��%ld���� Command::analysis_inquire_response_command \
�����У��յ��Ƿ�ָ�%s����"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..�������е��˷��ش���
		return(-1);
	}

}

/**
 * name: generate_reaction_disc_rotation_shake_hand_command
 * breif: ���ɷ�Ӧ����ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reaction_disc_rotation_shake_hand_command(){
	//1.������Ӧ����ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x03;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reaction_disc_rotation_response_command
 * brief: ���ɷ�Ӧ����ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reaction_disc_rotation_response_command(){
	//1.������Ӧ����ת���ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x03;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_shake_hand_command
 * breif: ����װ��ץ��ȡ������ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_take_tube_out_shake_hand_command(){
	//1.������Ӧ����ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x02;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_response_command
 * brief: ����װ��ץ��ȡ�ܻظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_take_tube_out_response_command(){
	//1.����װ��ץ��ȡ�����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x02;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_inquire_sensors_response_command
 * brief: ���ɲ�ѯ�������ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_inquire_sensors_response_command(){
	//1.������ѯ�������ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=10;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0x8D;
	command[2]=0x05;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x20;
	command[6]=0x04;
	command[7]=0x00;
	if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->
		get_components())->get_reaction_disc())->
		get_having_tube_in_entry_flag_expect_value()){
		command[7]|=0x01;
	}
	if(ReactionDisc::FLAGE_USED==(((Instrument::instance())->
		get_components())->get_reaction_disc())->
		get_having_tube_in_exit_flag_expect_value()){
		command[7]|=0x02;
	}
	if(WashingDisc::FLAGE_USED==(((Instrument::instance())->
		get_components())->get_washing_disc())->
		get_having_tube_in_entry_flag_expect_value()){
		command[7]|=0x04;
	}
	if(WashingDisc::FLAGE_USED==(((Instrument::instance())->
		get_components())->get_washing_disc())->
		get_having_tube_in_exit_flag_expect_value()){
		command[7]|=0x08;
	}
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_shake_hand_command
 * brief: ����װ��ץ�ַŹ�����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_put_tube_in_shake_hand_command(){
	//1.����װ��ץ�ַŹ�����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x01;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_response_command
 * brief: ����װ��ץ�ַŹܻظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_load_tong_put_tube_in_response_command(){
	//1.����װ��ץ�ַŹ�����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x01;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_shake_hand_command
 * brief: ������������ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_disc_rotation_shake_hand_command(){
	//1.������������ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x07;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_response_command
 * brief: ������������ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_disc_rotation_response_command(){
	//1.������������ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x07;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_suck_shake_hand_command
 * breif: ������������ȡ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_suck_shake_hand_command(){
	//1.������������ȡ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x05;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_suck_response_command
 * breif: ������������ȡ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_suck_response_command(){
	//1.������������ȡ�ظ�ָ������жϴ����Ƿ�ɹ���
	unsigned int down_steps=1000;
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x05;
	command[10]=down_steps&0xFF;
	down_steps>>=8;
	command[9]=down_steps&0xFF;
	down_steps>>=8;
	command[8]=down_steps&0xFF;
	down_steps>>=8;
	command[7]=down_steps&0xFF;
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_spit_shake_hand_command
 * brief: ������������Һ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_spit_shake_hand_command(){
	//1.������������Һ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x04;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_spit_response_command
 * brief: ������������Һ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_spit_response_command(){
	//1.������������Һ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x04;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_wash_shake_hand_command
 * breif: ������������ϴ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_wash_shake_hand_command(){
	//1.������������ϴ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x06;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_specimen_arm_wash_response_command
 * brief: ������������ϴ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_specimen_arm_wash_response_command(){
	//1.������������ϴ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x06;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_suck_shake_hand_command
 * breif: �����Լ�����ȡ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_suck_shake_hand_command(){
	//1.�����Լ�����ȡ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x09;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_suck_response_command
 * breif: �����Լ�����ȡ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_suck_response_command(){
	//1.�����Լ�����ȡ�ظ�ָ������жϴ����Ƿ�ɹ���
	unsigned int down_steps=1000;
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x09;
	command[10]=down_steps&0xFF;
	down_steps>>=8;
	command[9]=down_steps&0xFF;
	down_steps>>=8;
	command[8]=down_steps&0xFF;
	down_steps>>=8;
	command[7]=down_steps&0xFF;
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_spit_shake_hand_command
 * brief: �����Լ�����Һ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_spit_shake_hand_command(){
	//1.�����Լ�����Һ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x08;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_spit_response_command
 * brief: �����Լ�����Һ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_spit_response_command(){
	//1.�����Լ�����Һ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x08;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_wash_shake_hand_command
 * breif: �����Լ�����ϴ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_wash_shake_hand_command(){
	//1.�����Լ�����ϴ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x10;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_arm_wash_response_command
 * brief: �����Լ�����ϴ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_arm_wash_response_command(){
	//1.�����Լ�����ϴ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x10;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_shake_hand_command
 * brief: �����Լ�����ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_disc_rotation_shake_hand_command(){
	//1.�����Լ�����ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x11;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_response_command
 * breif: �����Լ�����ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_reagent_disc_rotation_response_command(){
	//1.�����Լ�����ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x11;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_shake_hand_command
 * brief: ���ɴ�������ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_rotation_shake_hand_command(){
	//1.������������ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x12;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_response_command
 * breif: ���ɴ�������ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_rotation_response_command(){
	//1.������������ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x12;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_shake_hand_command
 * breif: ���ɴ����̻�����ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_shake_hand_command(){
	//1.���������̻�����ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x25;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_response_command
 * breif: ���ɴ����̻�����ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_response_command(){
	//1.���������̻�����ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x25;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_rotation_shake_hand_command
 * brief: ������ϴ����ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_rotation_shake_hand_command(){
	//1.������ϴ������ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x24;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_rotation_response_command
 * brief: ������ϴ����ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_rotation_response_command(){
	//1.������ϴ������ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x24;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_disc_rotation_shake_hand_command
 * brief: ���ɼ������ת����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_disc_rotation_shake_hand_command(){
	//1.�����������ת����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x21;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_disc_rotation_response_command
 * brief: ���ɼ������ת�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_disc_rotation_response_command(){
	//1.�����������ת�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x21;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_shake_hand_command
 * brief: ���ɴӼ����ȡ������ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_detection_disc_shake_hand_command(){
	//1.�����Ӽ����ȡ������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x18;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_response_command
 * brief: ���ɴӼ����ȡ�ܻظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_detection_disc_response_command(){
	//1.�����Ӽ����ȡ�ܻظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x18;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_discard_tube_shake_hand_command
 * brief: ���ɶ�������ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_discard_tube_shake_hand_command(){
	//1.������������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x19;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_discard_tube_response_command
 * brief: ���ɶ��ܻظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_discard_tube_response_command(){
	//1.�������ܻظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=10;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x05;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x19;
	command[7]=0x01;//Ĭ��Ϊ�йܡ�
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_wash_shake_hand_command
 * brief: ������ϴ����ϴ����ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_wash_shake_hand_command(){
	//1.������ϴ����ϴ����ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x20;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_washing_disc_wash_response_command
 * brief: ������ϴ����ϴ�ظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_washing_disc_wash_response_command(){
	//1.������ϴ����ϴ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x20;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_shake_hand_command
 * brief: ���ɴ���ϴ��ȡ������ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_washing_disc_shake_hand_command(){
	//1.������ϴ����ϴ�ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x15;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_response_command
 * biref: ���ɴ���ϴ��ȡ�ܻظ�ָ�
 * param: --
 * return: ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_washing_disc_response_command(){
	//1.��������ϴ��ȡ�ܻظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x15;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_shake_hand_command
 * brief: ���ɻعܵ���Ӧ������ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_return_tube_to_reaction_disc_shake_hand_command(){
	//1.����ת��ץ�ֻعܵ���Ӧ������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x14;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_response_command
 * brief: ���ɻعܵ���Ӧ�̻ظ�ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_return_tube_to_reaction_disc_response_command(){
	//1.����ת��ץ�ֻعܵ���Ӧ�̻ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x14;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_shake_hand_command
 * brief: ����ת��ץ�ַŹܵ����������ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_detection_disc_shake_hand_command(){
	//1.����ת��ץ�ַŹܵ����������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x17;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_response_command
 * brief: ����ת��ץ�ַŹܵ�����̻ظ�ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_detection_disc_response_command(){
	//1.����ת��ץ�ַŹܵ�����̻ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x17;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_shake_hand_command
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ������ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_reaction_disc_shake_hand_command(){
	//1.����ת��ץ�ִӷ�Ӧ��ȡ������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x13;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_response_command
 * brief: ����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ�ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_take_tube_out_of_reaction_disc_response_command(){
	//1.����ת��ץ�ִӷ�Ӧ��ȡ�ܻظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x13;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_shake_hand_command
 * brief: ����ת��ץ�ַŹܵ���ϴ������ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_washing_disc_shake_hand_command(){
	//1.����ת��ץ�ַŹܵ���ϴ������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x16;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_response_command
 * brief: ����ת��ץ�ַŹܵ���ϴ�̻ظ�ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_put_tube_in_washing_disc_response_command(){
	//1.����ת��ץ�ַŹܵ���ϴ�̻ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x16;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_shake_hand_command
 * brief: ���ɼ������ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_shake_hand_command(){
	//1.�����������ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=9;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xA5;
	command[2]=0x04;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x23;
	if(calculate_parity_bit(command,size-2,command[7])<0){
		delete[] command;
		return(-2);
	}
	command[8]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_detection_response_command
 * breif: ���ɼ��ظ�ָ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Command::generate_detection_response_command(){
	//1.�������ظ�ָ������жϴ����Ƿ�ɹ���
	const unsigned int size=13;
	unsigned char *command=new unsigned char[size];
	if(0==command){
		return(-1);
	}
	command[0]=START_BIT;
	command[1]=0xB5;
	command[2]=0x08;
	command[3]=0x00;
	command[4]=0x01;
	command[5]=0x10;
	command[6]=0x23;
	const unsigned int luminous=1000;
	command[7]=static_cast<unsigned char>((luminous>>24)&0xFF);
	command[8]=static_cast<unsigned char>((luminous>>16)&0xFF);
	command[9]=static_cast<unsigned char>((luminous>>8)&0xFF);
	command[10]=static_cast<unsigned char>(luminous&0xFF);
	if(calculate_parity_bit(command,size-2,command[11])<0){
		delete[] command;
		return(-2);
	}
	command[12]=END_BIT;
	//2.Ϊ��ǰָ�ֵ��
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_string
 * breif: ��ȡָ���ַ�����
 * param: --
 * return: ����ָ���ַ�����
 */
CString Command::get_string() const{
	CString command(_T(""));
	CString temp(_T(""));
	for(unsigned int index=0;index!=_size;++index){
		if(0==index){
			temp.Format(_T("0x%02x"),_command[index]);
		}else{
			temp.Format(_T(" 0x%02x"),_command[index]);
		}
		command+=temp;
	}
	return(command);
}