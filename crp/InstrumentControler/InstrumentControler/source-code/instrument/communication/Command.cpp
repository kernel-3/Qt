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
 * breif: 计算校验位。
 * param: command - 输入的指向指令数组的指针。
 *        length - 输入的指令输入长度（不包括校验位、结束位）。
 *        parity_bit - 输出计算的校验位。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
static int calculate_parity_bit(const unsigned char *command,
	const unsigned int length,unsigned char &parity_bit){
	//1.检测输入的参数是否合法。
	if((0==command)||(0==length)){
		return(-1);
	}
	//2.遍历指令数组，累计指令和，并计算校验位。
	unsigned int sum=0;
	for(unsigned int index=0;index<length;++index){
		sum+=command[index];
	}
	parity_bit=static_cast<unsigned char>(sum);
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: Command
 * brief: 构造函数。
 * param: --
 * return: --
 */
Command::Command(void)
	:_command(0)
	,_size(0){
}

/**
 * name: Command
 * brief: 构造函数。
 * param: command - 输入的指向指令数组的指针。
 *        size - 输入的指令数组尺寸。
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
 * breif: 析构函数。
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
 * breif: 对指令进行解析。
 * param: port - 输入的指令传输端口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis(Port &port) const{
	//1.检测当前指令是否合法，如果不合法则直接返回错误。
	if(is_valid()<0){
		//1-1.书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）：Command::analysis 函数中，\
收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(
			_T("%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//1-2.程序运行到此返回错误。
		return(-1);
	}
	//2.对当前指令进行解释分析。
	//2-1.如果当前指令是复合（PC->主控）指令。
	if(0x25==_command[1]){
		if(analysis_compound_command(port)<0){
			return(-2);
		}else{
			return(0);
		}
	}
	//2-2.如果当前指令是复合握手（主控->PC）指令。
	else if(0xA5==_command[1]){
		if(analysis_compound_shake_handle_command()<0){
			return(-3);
		}else{
			return(0);
		}
	}
	//2-3.如果当前指令是复合回复（主控->PC）指令。
	else if(0xB5==_command[1]){
		if(analysis_compound_response_command()<0){
			return(-4);
		}else{
			return(0);
		}
	}
	//2-3.如果当前指令是查询（PC->主控）指令。
	else if(0x0D==_command[1]){
		if(analysis_inquire_command(port)<0){
			return(-5);
		}else{
			return(0);
		}
	}
	//2-4.如果当前指令是查询回复（主控->PC）指令。
	else if(0x8D==_command[1]){
		if(analysis_inquire_response_command()<0){
			return(-6);
		}else{
			return(0);
		}
	}
	//2-..如果当前是未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error Receive %s（%ld）：Command::analysis（2） "),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime());
		log+=get_string();
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//..程序运行到此返回错误。
		return(-9);
	}
}

/**
 * name: send
 * brief: 发送当前指令。
 * param: port - 输入的指令传输端口。
 *        name - 输入的指令名称。
 *        is_logged - 输入的是否书写日志标记。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::send(Port &port,const CString &name/*=_T("")*/,
	const BOOL is_logged/*=TRUE*/) const{
	//1.检测当前指令是否合法。
	if(is_valid()<0){
		return(-1);
	}
	//2.发送当前指令，并且判断发送是否成功。
	if(port.write(_command,_size)<0){
		return(-2);
	}
	//3.书写发送日志。
	if(is_logged){
		CString log(_T(""));
		log.Format(_T("Write %s（%ld）： %s"),(COleDateTime::
			GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime(),get_string());
		if(_T("")!=name){
			log+=_T(" ( ")+name+_T(" )");
		}
		log+=_T("。");
		Logs::instance()->write(Logs::NAME_COMMAND,log);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reaction_disc_rotation_command
 * breif: 生成反应盘旋转指令。
 * param: hole_no - 输入的孔号。
 *        position - 输入的位置。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reaction_disc_rotation_command(
	const unsigned int hole_no,const unsigned int position){
	//1.创建反应盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_command
 * brief: 生成装载抓手取管指令。
 * param: row - 输入的试管仓取管行位置。
 *        col - 输入的试管仓取管列位置。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_take_tube_out_command(
	const unsigned int row,const unsigned int col){
	//1.创建装载抓手取管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_inquire_sensors_command
 * brief: 生成传感器查询指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_inquire_sensors_command(){
	//1.创建传感器查询指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_command
 * breif: 生成装载抓手放管指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_put_tube_in_command(){
	//1.创建装载抓手放管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_command
 * breif: 生成样本盘旋转指令。
 * param: rack_no - 输入的架子号。
 *        position_no - 输入的位置号。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_disc_rotation_command(
	const unsigned int rack_no,const unsigned int position_no){
	//1.创建样本盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_suck_command
 * brief: 生成样本臂吸取指令。
 * param: suck_volume - 输入的吸取体积。
 *        cup_type - 输入的样本杯类型。
 *        liquid_level_probe_switch - 输入的液位探测开关。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_suck_command(const unsigned int suck_volume,
	const unsigned int cup_type,const BOOL liquid_level_probe_switch){
	//1.创建样本臂吸取指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_spit_command
 * breif: 生成样本臂吐液指令。
 * param: spit_volume - 输入的吐液体积。
 *        down_steps - 输入的样本臂下降步数。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_spit_command(
	const unsigned int spit_volume,const unsigned int down_steps){
	//1.创建样本臂吐液指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_wash_command
 * brief: 生成样本臂清洗指令。
 * param: outer_wash_time - 输入的外壁清洗时间。
 *        inner_wash_time - 输入的内壁清洗时间。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_wash_command(
	const unsigned int outer_wash_time,const unsigned int inner_wash_time){
	//1.创建样本臂清洗指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_suck_command
 * brief: 生成试剂臂吸取指令。
 * param: suck_volume - 输入的吸取体积。
 *        reagent_type - 输入的试剂类型。
 *        liquid_level_probe_switch - 输入的液位探测开关。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_suck_command(const unsigned int suck_volume,
	const unsigned int reagent_type,const BOOL liquid_level_probe_switch){
	//1.创建试剂臂吸取指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_spit_command
 * brief: 生成试剂臂吐液指令。
 * param: spit_volume - 输入的吐液体积。
 *        down_steps - 输入的试剂臂下降步数。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_spit_command(
	const unsigned int spit_volume,const unsigned int down_steps){
	//1.创建试剂臂吐液指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_wash_command
 * brief: 生成试剂臂清洗指令。
 * param: outer_wash_time - 输入的外壁清洗时间。
 *        inner_wash_time - 输入的内壁清洗时间。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_wash_command(
	const unsigned int outer_wash_time,const unsigned int inner_wash_time){
	//1.创建试剂臂清洗指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_command
 * brief: 生成试剂盘旋转指令。
 * param: reagent_type - 输入的试剂类型。
 *        position_no - 输入的位置号。
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_disc_rotation_command(
	const unsigned int reagent_type,const unsigned int position_no){
	//1.创建试剂盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_command
 * brief: 生成磁珠盘旋转命令。
 * param: position_no - 输入的位置号。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_rotation_command(
	const unsigned int position_no){
	//1.创建磁珠盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_command
 * brief: 生成磁珠盘混匀旋转命令。
 * param: direction - 输入的旋转方向。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_command(
	const unsigned int direction){
	//1.创建磁珠盘混匀旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_rotation_command
 * brief: 生成清洗盘旋转指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_rotation_command(){
	//1.创建清洗盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_disc_rotation_command
 * brief: 生成检测盘旋转指令。
 * param: hole_no - 输入的孔号。
 *        position - 输入的位置。
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_disc_rotation_command(
	const unsigned int hole_no,const unsigned int position){
	//1.创建清洗盘旋转指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_command
 * brief: 生成从检测盘取管指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_detection_disc_command(){
	//1.创建从检测盘取管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_discard_tube_command
 * brief: 生成丢管指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_discard_tube_command(){
	//1.创建从丢管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_wash_command
 * brief: 生成清洗盘清洗指令。
 * param: substrate_type - 输入的底物类型。
 *        substrate_volume - 输入的底物体积。
 *        washing_liquid_volume - 输入的清洗液体积。
 *        is_washing_position_1_need_washing - 输入的是否清洗清洗位置1标志。
 *        is_washing_position_2_need_washing - 输入的是否清洗清洗位置2标志。
 *        is_washing_position_3_need_washing - 输入的是否清洗清洗位置3标志。
 *        is_washing_position_4_need_washing - 输入的是否清洗清洗位置4标志。
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_wash_command(const unsigned int substrate_type,
	const unsigned int substrate_volume,const unsigned int washing_liquid_volume,
	const BOOL is_washing_position_1_need_washing,const BOOL is_washing_position_2_need_washing,
	const BOOL is_washing_position_3_need_washing,const BOOL is_washing_position_4_need_washing){
	//1.创建清洗盘清洗指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_command
 * brief: 生成从清洗盘取管指令。
 * param: stop_position - 输入的停止位置。
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_washing_disc_command(
	const unsigned int stop_position){
	//1.创建从清洗盘取管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_command
 * brief: 生成转运抓手回管到反应盘指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_return_tube_to_reaction_disc_command(){
	//1.创建转运抓手回管到反应盘指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_command
 * brief: 生成转运抓手放管到检测盘指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_detection_disc_command(){
	//1.创建转运抓手检测盘放管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_command
 * brief: 生成转运抓手从反应盘取管命令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_reaction_disc_command(){
	//1.创建转运抓手从反应盘取管指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_command
 * brief: 生成清洗抓手放管到清洗盘指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_washing_disc_command(){
	//1.创建转运抓手放管到清洗盘指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_command
 * brief: 生成检测指令。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_command(){
	//1.创建检测指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: is_valid
 * brief: 检测当前指令是否合法。
 * param: --
 * return: 如果当前指令合法返回值大于等于零，否则返回值小于零。
 */
int Command::is_valid() const{
	//1.检测指令存储空间是否合法。
	if((0==_command)||(0==_size)){
		return(-1);
	}
	//2.检测指令长度是否满足最小长度。
	if(_size<MIN_LENGTH){
		return(-2);
	}
	//3.检测当前指令起始位是否合法。
	if(Command::START_BIT!=_command[0]){
		return(-3);
	}
	//4.检测当前指令长度位是否合法。
	if(_command[2]!=static_cast<unsigned char>(_size-5)){
		return(-4);
	}
	//5.检测当前指令结束位是否合法。
	if(Command::END_BIT!=_command[_size-1]){
		return(-5);
	}
	//6.检测校验位是否合法。
	//6-1.计算指令校验位。
	unsigned char parity_bit=0;
	if(calculate_parity_bit(
		_command,_size-2,parity_bit)<0){
		return(-6);
	}
	//6-2.检测校验位是否合法。
	if(_command[_size-2]!=parity_bit){
		return(-7);
	}
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: analysis_compound_command
 * breif: 对复合指令进行解析。
 * param: port - 输入的指令传输端口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis_compound_command(Port &port) const{
	//1.如果当前是装载抓手放管指令。
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
	//2.如果当前是装载抓手取管指令。
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
	//3.如果当前是反应盘转动指令。
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
	//4.如果当前是样本臂添加指令。
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
	//5.如果当前是样本臂吸取指令。
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
	//6.如果当前是样本臂清洗指令。
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
	//7.如果当前是样本盘转动指令。
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
	//8.如果当前是试剂臂吐液指令。
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
	//9.如果当前是试剂臂吸取指令。
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
	//10.如果当前是试剂臂清洗指令。
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
	//11.如果当前是试剂盘旋转指令。
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
	//12.如果当前是磁珠盘旋转指令。
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
	//13.如果当前是转运抓手从反应盘取管指令。
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
	//14.如果当前是转运抓手回管到反应盘指令。
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
	//15.如果当前是从清洗盘取管指令。
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
	//16.如果当前是转运抓手放管到清洗盘指令。
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
	//17.如果当前是转运抓手放管到检测盘指令。
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
	//18.如果当前是从检测盘取管指令。
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
	//19.如果当前是丢管指令。
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
	//20.如果当前是清洗盘清洗指令。
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
	//21.如果当前是检测盘旋转指令。
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
	//23.如果当前是检测指令。
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
	//24.如果当前是清洗盘旋转指令。
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
	//25.如果当前是磁珠盘混匀旋转指令。
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
	//..如果接收到未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： Command::analysis_compound_command \
函数，收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..程序运行到此返回错误。
		return(-97);
	}
}

/**
 * name: analysis_compound_shake_handle_command
 * breif: 对复合握手指令进行解析。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis_compound_shake_handle_command() const{
	//1.如果当前接收到的是装载抓手放管握手指令。
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x01==_command[6])){
		//1-1.设置装载抓手放管握手标志。
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_put_tube_in_shake_hand_flag(
			LoadTong::FLAG_IDLE);
		//1-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（装载抓手放管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.程序运行到此成功返回。
		return(0);
	}
	//2.如果当前接收到的是装载抓手取管握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x02==_command[6])){
		//2-1.设置装载抓手取管握手标志。
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_take_tube_out_shake_hand_flag(
			LoadTong::FLAG_IDLE);
		//2-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（装载抓手取管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//2-3.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前接收到的是反应盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x03==_command[6])){
		//3-1.设置反应盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_rotation_shake_hand_flag(
			ReactionDisc::FLAG_IDLE);
		//3-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（反应盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//3-3.程序运行到此成功返回。
		return(0);
	}
	//4.如果当前接收到的是样本臂吐液握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x04==_command[6])){
		//4-1.设置样本臂吐液握手标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_spit_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//4-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本臂吐液握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//4-3.程序运行到此成功返回。
		return(0);
	}
	//5.如果当前接收到的是样本臂吸取握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x05==_command[6])){
		//5-1.设置样本臂吸取握手标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_suck_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//5-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本臂吸液握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//5-3.程序运行到此成功返回。
		return(0);
	}
	//6.如果当前接收到的是样本臂清洗握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x06==_command[6])){
		//6-1.设置样本臂清洗握手标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//6-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本臂清洗握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//6-3.程序运行到此成功返回。
		return(0);
	}
	//7.如果当前接收到的是样本盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x07==_command[6])){
		//7-1.设置样本盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_specimen_disc())->set_rotation_shake_hand_flag(
			ReactionDisc::FLAG_IDLE);
		//7-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//7-3.程序运行到此成功返回。
		return(0);
	}
	//8.如果当前接收到的是试剂臂吐液握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x08==_command[6])){
		//8-1.设置试剂臂吐液握手标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_spit_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//8-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂臂吐液握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//8-3.程序运行到此成功返回。
		return(0);
	}
	//9.如果当前接收到的是试剂臂吸取握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x09==_command[6])){
		//9-1.设置样本臂吸取握手标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_suck_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//9-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂臂吸液握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//9-3.程序运行到此成功返回。
		return(0);
	}
	//10.如果当前接收到的是试剂臂清洗握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x10==_command[6])){
		//10-1.设置试剂臂清洗握手标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//10-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂臂清洗握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//10-3.程序运行到此成功返回。
		return(0);
	}
	//11.如果当前接收到的是试剂盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x11==_command[6])){
		//11-1.设置试剂盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_reagent_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//11-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//11-3.程序运行到此成功返回。
		return(0);
	}
	//12.如果当前接收到的是磁珠盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x12==_command[6])){
		//12-1.设置磁珠盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//12-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（磁珠盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//12-3.程序运行到此成功返回。
		return(0);
	}
	//13.如果当前接收到的是转运抓手从反应盘取管握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x13==_command[6])){
		//13-1.设置转运抓手从反应盘取管握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_reaction_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//13-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从反应盘取管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//13-3.程序运行到此成功返回。
		return(0);
	}
	//14.如果当前收到的是转运抓手回管到反应盘握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x14==_command[6])){
		//14-1.设置转运抓手回管到反应盘握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_return_tube_to_reaction_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//14-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手回管到反应盘握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//14-3.程序运行到此成功返回。
		return(0);
	}
	//15.如果当前收到的是从清洗盘取管握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x15==_command[6])){
		//15-1.设置从清洗盘取管握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_washing_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//15-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从清洗盘取管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//15-3.程序运行到此成功返回。
		return(0);
	}
	//16.如果当前收到的是转运抓手放管到清洗盘握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x16==_command[6])){
		//16-1.设置转运抓手放管到清洗盘握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_washing_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//16-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手放管到清洗盘握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//16-3.程序运行到此成功返回。
		return(0);
	}
	//17.如果当前收到的是转运抓手放管到检测盘握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x17==_command[6])){
		//17-1.设置转运抓手放管到检测盘握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_detection_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//17-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手放管到检测盘握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//17-3.程序运行到此成功返回。
		return(0);
	}
	//18.如果当前收到的是从检测盘取管握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x18==_command[6])){
		//18-1.设置从检测盘取管握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_detection_disc_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//18-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从检测盘取管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//18-3.程序运行到此成功返回。
		return(0);
	}
	//19.如果当前收到的是丢管握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x19==_command[6])){
		//19-1.设置转运抓手丢管握手标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->set_discard_tube_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//19-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手丢管握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//19-3.程序运行到此成功返回。
		return(0);
	}
	//20.如果当前收到的是清洗盘清洗握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x20==_command[6])){
		//20-1.设置清洗盘清洗握手标志。
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_wash_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//20-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（清洗盘清洗握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//20-3.程序运行到此成功返回。
		return(0);
	}
	//21.如果当前收到的是检测盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x21==_command[6])){
		//21-1.设置检测盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//21-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（检测盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//21-3.程序运行到此成功返回。
		return(0);
	}
	//23.如果当前收到的是检测握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x23==_command[6])){
		//23-1.设置检测握手标志。
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_detect_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//23-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（检测握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//23-3.程序运行到此成功返回。
		return(0);
	}
	//24.如果当前收到的是清洗盘旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x24==_command[6])){
		//24-1.设置清洗盘旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//24-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（清洗盘旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//24-3.程序运行到此成功返回。
		return(0);
	}
	//25.如果当前收到的是磁珠盘混匀旋转握手指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x25==_command[6])){
		//25-1.设置磁珠盘混匀旋转握手标志。
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_mixing_rotation_shake_hand_flag(
			SpecimenArm::FLAG_IDLE);
		//25-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（磁珠盘混匀旋转握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//25-3.程序运行到此成功返回。
		return(0);
	}
	//..如果接收到未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： Command::analysis_compound_shake_handle_command \
函数中，收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
			timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..程序运行到此返回错误。
		return(-1);
	}
}

/**
 * name: analysis_compound_response_command
 * brief: 对复合完成指令进行解析。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis_compound_response_command() const{
	//1.如果当前接收到的是装载抓手放管回复指令。
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x01==_command[6])){
		//1-1.设置装载抓手放管回复标志。
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_put_tube_in_response_flag(
			LoadTong::FLAG_IDLE);
		//1-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（装载抓手放管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.程序运行到此成功返回。
		return(0);
	}
	//2.如果当前接收到的是装载抓手取管回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x02==_command[6])){
		//2-1.设置装载抓手取管回复标志。
		(((Instrument::instance())->get_components())->
			get_load_tong())->set_take_tube_out_response_flag(
			LoadTong::FLAG_IDLE);
		//2-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（装载抓手取管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//2-3.程序运行到此成功返回。
		return(0);
	}
	//3.如果当前接收到的是反应盘旋转完成指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x03==_command[6])){
		//3-1.设置反应盘旋转完成标志。
		(((Instrument::instance())->get_components())->
			get_reaction_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//3-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（反应盘旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//3-3.程序运行到此直接返回。
		return(0);
	}
	//4.如果当前收到的是样本臂吐液回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x04==_command[6])){
		//4-1.设置样本臂吐液回复标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_spit_response_flag(
			SpecimenArm::FLAG_IDLE);
		//4-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本臂吐液回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//4-3.程序运行到此直接返回。
		return(0);
	}
	//5.如果当前收到的是样本臂吸取回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x05==_command[6])){
		//5-1.设置样本臂吸取回复标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_suck_response_flag(
			SpecimenArm::FLAG_IDLE);
		//5-2.设置样本臂液位探测高度。
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
		//5-3.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 样本臂吸液时，液位高度为%ld。"),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),height);
		Logs::instance()->write(Logs::NAME_EVENT,log);
		log.Format(_T("Receive %s（%ld）： %s（样本臂吸液回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//5-4.程序运行到此直接返回。
		return(0);
	}
	//6.如果当前接收到的是样本臂清洗回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x06==_command[6])){
		//6-1.设置反应盘旋转完成标志。
		(((Instrument::instance())->get_components())->
			get_specimen_arm())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//6-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本臂清洗回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//6-3.程序运行到此直接返回。
		return(0);
	}
	//7.如果当前接收到的是样本盘旋转完成指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x07==_command[6])){
		//7-1.设置反应盘旋转完成标志。
		(((Instrument::instance())->get_components())->
			get_specimen_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//7-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（样本盘旋转完成指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//7-3.程序运行到此直接返回。
		return(0);
	}
	//8.如果当前收到的是试剂臂吐液回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x08==_command[6])){
		//8-1.设置试剂臂吐液回复标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_spit_response_flag(
			SpecimenArm::FLAG_IDLE);
		//8-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂臂吐液回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//8-3.程序运行到此直接返回。
		return(0);
	}
	//9.如果当前收到的是试剂臂吸取回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x09==_command[6])){
		//9-1.设置试剂臂吸取回复标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_suck_response_flag(
			SpecimenArm::FLAG_IDLE);
		//9-2.设置试剂臂液位探测高度。
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
		//9-3.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Event %s（%ld）： 试剂臂吸液时，液位高度为%ld。"),(
			COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),height);
		Logs::instance()->write(Logs::NAME_EVENT,log);
		log.Format(_T("Receive %s（%ld）： %s（试剂臂吸液回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//9-4.程序运行到此直接返回。
		return(0);
	}
	//10.如果当前接收到的是试剂臂清洗回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x10==_command[6])){
		//10-1.设置试剂臂清洗回复标志。
		(((Instrument::instance())->get_components())->
			get_reagent_arm())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//10-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂臂清洗回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//10-3.程序运行到此直接返回。
		return(0);
	}
	//11.如果当前接收到的是试剂盘旋转回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x11==_command[6])){
		//11-1.设置试剂盘旋转回复标志。
		(((Instrument::instance())->get_components())->
			get_reagent_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//11-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（试剂盘旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//11-3.程序运行到此直接返回。
		return(0);
	}
	//12.如果当前接收到的是磁珠盘旋转回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x12==_command[6])){
		//12-1.设置磁珠盘旋转回复标志。
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//12-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（磁珠盘旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//12-3.程序运行到此直接返回。
		return(0);
	}
	//13.如果当前接收到的是转运抓手从反应盘取管回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x13==_command[6])){
		//13-1.设置转运抓手从反应盘取管回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_reaction_disc_response_flag(
			SpecimenArm::FLAG_IDLE);
		//13-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从反应盘取管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//13-3.程序运行到此成功返回。
		return(0);
	}
	//14.如果当前接收到的转运抓手回管到反应盘回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x14==_command[6])){
		//14-1.设置转运抓手回管到反应盘回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_return_tube_to_reaction_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//14-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手回管到反应盘回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//14-3.程序运行到此直接返回。
		return(0);
	}
	//15.如果当前接收到的是从清洗盘取管回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x15==_command[6])){
		//15-1.设置从清洗盘取管回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_washing_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//15-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从清洗盘取管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//15-3.程序运行到此直接返回。
		return(0);
	}
	//16.如果当前接收到的是转运抓手放管到清洗盘回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x16==_command[6])){
		//16-1.设置转运抓手放管到清洗盘回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_washing_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//16-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手放管到清洗盘回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//16-3.程序运行到此直接返回。
		return(0);
	}
	//17.如果当前收到的是转运抓手放管到检测盘回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x17==_command[6])){
		//17-1.设置转运抓手放管到检测盘回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_put_tube_in_detection_disc_response_flag(
			SpecimenArm::FLAG_IDLE);
		//17-2.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手放管到检测盘回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//17-3.程序运行到此成功返回。
		return(0);
	}
	//18.如果当前接收到的是从检测盘取管回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x18==_command[6])){
		//18-1.设置从检测盘取管回复标志。
		(((Instrument::instance())->get_components())->
			get_transport_tong())->
			set_take_tube_out_of_detection_disc_response_flag(
			ReactionDisc::FLAG_IDLE);
		//18-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手从检测盘取管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//18-3.程序运行到此直接返回。
		return(0);
	}
	//19.如果当前接收到的是丢管回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x19==_command[6])){
		//19-1.设置丢管回复标志。
		if(0x00==_command[7]){
			(((Instrument::instance())->get_components())->
				get_transport_tong())->set_discard_tube_response_flag(
				ReactionDisc::FLAGE_EMPTY);
		}else{
			(((Instrument::instance())->get_components())->
				get_transport_tong())->set_discard_tube_response_flag(
				ReactionDisc::FLAGE_USED);
		}
		//19-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（转运抓手丢管回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//19-3.程序运行到此直接返回。
		return(0);
	}
	//20.如果当前接收到的是清洗盘清洗回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x20==_command[6])){
		//20-1.设置清洗盘清洗回复指令。
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_wash_response_flag(
			ReactionDisc::FLAG_IDLE);
		//20-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（清洗盘清洗回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//20-3.程序运行到此直接返回。
		return(0);
	}
	//21.如果当前接收到的是检测盘旋转回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x21==_command[6])){
		//21-1.设置检测盘旋转回复标志。
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//21-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（检测盘旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//21-3.程序运行到此直接返回。
		return(0);
	}
	//23.如果当前收到的是检测回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x23==_command[6])){
		//23-1.设置检测回复标志。
		(((Instrument::instance())->get_components())->
			get_detection_disc())->set_detect_response_flag(
			SpecimenArm::FLAG_IDLE);
		//23-2.计算回复指令中返回的发光值。
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
		//23-3.书写日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（检测握手指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//23-4.程序运行到此成功返回。
		return(0);
	}
	//24.如果当前接收到的是清洗盘旋转回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x24==_command[6])){
		//24-1.设置清洗盘旋转回复标志。
		(((Instrument::instance())->get_components())->
			get_washing_disc())->set_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//24-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（清洗盘旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//24-3.程序运行到此直接返回。
		return(0);
	}
	//25.如果当前接收到的是磁珠盘混匀旋转回复指令。
	else if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x10==_command[5])&&(0x25==_command[6])){
		//25-1.设置磁珠盘混匀旋转回复标志。
		(((Instrument::instance())->get_components())->
			get_magnetic_bead_disc())->set_mixing_rotation_response_flag(
			ReactionDisc::FLAG_IDLE);
		//25-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（磁珠盘混匀旋转回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//25-3.程序运行到此直接返回。
		return(0);
	}
	//..如果接收到未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： Command::analysis_compound_response_command \
函数中，收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..程序运行到此返回错误。
		return(-1);
	}
}

/**
 * name: analysis_inquire_command
 * brief: 对查询指令进行解析。
 * param: port - 输入的指令传输端口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis_inquire_command(Port &port) const{
	//1.如果当前接收到的是查询位置传感器指令。
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
	//..如果接收到未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： Command::analysis_inquire_command \
函数中，收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..程序运行到此返回错误。
		return(-1);
	}
}

/**
 * name: analysis_inquire_response_command
 * brief: 对查询回复指令进行解析。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::analysis_inquire_response_command() const{
	//1.如果当前接收到的是查询位置传感器回复指令。
	if((0x00==_command[3])&&(0x01==_command[4])&&(
		0x20==_command[5])&&(0x04==_command[6])){
		//1-1.计算查询位置传感器回复指令中包含的传感器状态，并设置相应的标记。
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
		//1-2.书写相关日志。
		CString log(_T(""));
		log.Format(_T("Receive %s（%ld）： %s（查询传感器回复指令）。"),
			(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_COMMAND,log);
		//1-3.程序运行到此成功返回。
		return(0);
	}
	//..如果接收到未知指令。
	else{
		//..书写日志。
		CString log(_T(""));
		log.Format(_T("Error %s（%ld）： Command::analysis_inquire_response_command \
函数中，收到非法指令（%s）！"),(COleDateTime::GetCurrentTime()).Format(_T(
			"%Y-%m-%d %H:%M:%S")),timeGetTime(),get_string());
		Logs::instance()->write(Logs::NAME_ERROR,log);
		//..程序运行到此返回错误。
		return(-1);
	}

}

/**
 * name: generate_reaction_disc_rotation_shake_hand_command
 * breif: 生成反应盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reaction_disc_rotation_shake_hand_command(){
	//1.创建反应盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reaction_disc_rotation_response_command
 * brief: 生成反应盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reaction_disc_rotation_response_command(){
	//1.创建反应盘旋转完成指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_shake_hand_command
 * breif: 生成装载抓手取管握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_take_tube_out_shake_hand_command(){
	//1.创建反应盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_take_tube_out_response_command
 * brief: 生成装载抓手取管回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_take_tube_out_response_command(){
	//1.创建装载抓手取管完成指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_inquire_sensors_response_command
 * brief: 生成查询传感器回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_inquire_sensors_response_command(){
	//1.创建查询传感器回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_shake_hand_command
 * brief: 生成装载抓手放管握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_put_tube_in_shake_hand_command(){
	//1.创建装载抓手放管握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_load_tong_put_tube_in_response_command
 * brief: 生成装载抓手放管回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_load_tong_put_tube_in_response_command(){
	//1.创建装载抓手放管握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_shake_hand_command
 * brief: 生成样本盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_disc_rotation_shake_hand_command(){
	//1.创建样本盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_disc_rotation_response_command
 * brief: 生成样本盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_disc_rotation_response_command(){
	//1.创建样本盘旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_suck_shake_hand_command
 * breif: 创建样本臂吸取握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_suck_shake_hand_command(){
	//1.创建样本臂吸取握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_suck_response_command
 * breif: 创建样本臂吸取回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_suck_response_command(){
	//1.创建样本臂吸取回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_spit_shake_hand_command
 * brief: 生成样本臂吐液握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_spit_shake_hand_command(){
	//1.创建样本臂吐液握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_spit_response_command
 * brief: 生成样本臂吐液回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_spit_response_command(){
	//1.创建样本臂吐液回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_wash_shake_hand_command
 * breif: 生成样本臂清洗握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_wash_shake_hand_command(){
	//1.创建样本臂清洗握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_specimen_arm_wash_response_command
 * brief: 生成样本臂清洗回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_specimen_arm_wash_response_command(){
	//1.创建样本臂清洗回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_suck_shake_hand_command
 * breif: 创建试剂臂吸取握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_suck_shake_hand_command(){
	//1.创建试剂臂吸取握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_suck_response_command
 * breif: 创建试剂臂吸取回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_suck_response_command(){
	//1.创建试剂臂吸取回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_spit_shake_hand_command
 * brief: 生成试剂臂吐液握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_spit_shake_hand_command(){
	//1.创建试剂臂吐液握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_spit_response_command
 * brief: 生成试剂臂吐液回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_spit_response_command(){
	//1.创建试剂臂吐液回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_wash_shake_hand_command
 * breif: 生成试剂臂清洗握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_wash_shake_hand_command(){
	//1.创建试剂臂清洗握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_arm_wash_response_command
 * brief: 生成试剂臂清洗回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_arm_wash_response_command(){
	//1.创建试剂臂清洗回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_shake_hand_command
 * brief: 生成试剂盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_disc_rotation_shake_hand_command(){
	//1.创建试剂盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_reagent_disc_rotation_response_command
 * breif: 生成试剂盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_reagent_disc_rotation_response_command(){
	//1.创建试剂盘旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_shake_hand_command
 * brief: 生成磁珠盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_rotation_shake_hand_command(){
	//1.创建磁珠盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_rotation_response_command
 * breif: 生成磁珠盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_rotation_response_command(){
	//1.创建磁珠盘旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_shake_hand_command
 * breif: 生成磁珠盘混匀旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_shake_hand_command(){
	//1.创建磁珠盘混匀旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_magnetic_bead_disc_mixing_rotation_response_command
 * breif: 生成磁珠盘混匀旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_magnetic_bead_disc_mixing_rotation_response_command(){
	//1.创建磁珠盘混匀旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_rotation_shake_hand_command
 * brief: 生成清洗盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_rotation_shake_hand_command(){
	//1.创建清洗盘盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_rotation_response_command
 * brief: 生成清洗盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_rotation_response_command(){
	//1.创建清洗盘盘旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_disc_rotation_shake_hand_command
 * brief: 生成检测盘旋转握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_disc_rotation_shake_hand_command(){
	//1.创建检测盘旋转握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_disc_rotation_response_command
 * brief: 生成检测盘旋转回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_disc_rotation_response_command(){
	//1.创建检测盘旋转回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_shake_hand_command
 * brief: 生成从检测盘取管握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_detection_disc_shake_hand_command(){
	//1.创建从检测盘取管握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_detection_disc_response_command
 * brief: 生成从检测盘取管回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_detection_disc_response_command(){
	//1.创建从检测盘取管回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_discard_tube_shake_hand_command
 * brief: 生成丢管握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_discard_tube_shake_hand_command(){
	//1.创建丢管握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_discard_tube_response_command
 * brief: 生成丢管回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_discard_tube_response_command(){
	//1.创建丢管回复指令，并且判断创建是否成功。
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
	command[7]=0x01;//默认为有管。
	if(calculate_parity_bit(command,size-2,command[8])<0){
		delete[] command;
		return(-2);
	}
	command[9]=END_BIT;
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_wash_shake_hand_command
 * brief: 生成清洗盘清洗握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_wash_shake_hand_command(){
	//1.创建清洗盘清洗握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_washing_disc_wash_response_command
 * brief: 生成清洗盘清洗回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_washing_disc_wash_response_command(){
	//1.创建清洗盘清洗回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_shake_hand_command
 * brief: 生成从清洗盘取管握手指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_washing_disc_shake_hand_command(){
	//1.创建清洗盘清洗回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_washing_disc_response_command
 * biref: 生成从清洗盘取管回复指令。
 * param: --
 * return: 函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_washing_disc_response_command(){
	//1.创建从清洗盘取管回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_shake_hand_command
 * brief: 生成回管到反应盘握手指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_return_tube_to_reaction_disc_shake_hand_command(){
	//1.创建转运抓手回管到反应盘握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_return_tube_to_reaction_disc_response_command
 * brief: 生成回管到反应盘回复指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_return_tube_to_reaction_disc_response_command(){
	//1.创建转运抓手回管到反应盘回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_shake_hand_command
 * brief: 生成转运抓手放管到检测盘握手指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_detection_disc_shake_hand_command(){
	//1.创建转运抓手放管到检测盘握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_detection_disc_response_command
 * brief: 生成转运抓手放管到检测盘回复指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_detection_disc_response_command(){
	//1.创建转运抓手放管到检测盘回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_shake_hand_command
 * brief: 生成转运抓手从反应盘取管握手指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_reaction_disc_shake_hand_command(){
	//1.创建转运抓手从反应盘取管握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_take_tube_out_of_reaction_disc_response_command
 * brief: 生成转运抓手从反应盘取管回复指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_take_tube_out_of_reaction_disc_response_command(){
	//1.创建转运抓手从反应盘取管回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_shake_hand_command
 * brief: 生成转运抓手放管到清洗盘握手指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_washing_disc_shake_hand_command(){
	//1.创建转运抓手放管到清洗盘握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_put_tube_in_washing_disc_response_command
 * brief: 生成转运抓手放管到清洗盘回复指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_put_tube_in_washing_disc_response_command(){
	//1.创建转运抓手放管到清洗盘回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_shake_hand_command
 * brief: 生成检测握手指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_shake_hand_command(){
	//1.创建检测握手指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_detection_response_command
 * breif: 生成检测回复指令。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Command::generate_detection_response_command(){
	//1.创建检测回复指令，并且判断创建是否成功。
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
	//2.为当前指令赋值。
	if(0!=_command){
		delete[] _command;
	}
	_command=command;
	_size=size;
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_string
 * breif: 获取指令字符串。
 * param: --
 * return: 返回指令字符串。
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