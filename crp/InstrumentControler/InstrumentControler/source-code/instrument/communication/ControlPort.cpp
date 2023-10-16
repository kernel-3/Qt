#include"stdafx.h"
#include"ControlPort.h"
#include"../../../../../include/mfctoolkit/comm/MtSerialPort.h"
#include"../../../../../include/mfctoolkit/comm/MtSerialPortParameter.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"Command.h"
#include<vector>
#include<Process.h>

/**
 * name: ControlPort
 * brief: 构造函数。
 * param: --
 * return: --
 */
ControlPort::ControlPort(void)
	:Port()
	,_port(0)
	,_is_cease(FALSE)
	,_cease_event(CreateEvent(0,FALSE,FALSE,0))
	,_monitoring(0)
	,_lock(new MtLock)
	,_command_event(CreateEvent(0,FALSE,FALSE,0))
	,_commands(){
	_port=new MtSerialPort(MtSerialPortParameter(
		MtSerialPortParameter::PORT_1),receive,this);
}

/**
 * name: ~ControlPort
 * brief: 析构函数。
 * param: --
 * return: --
 */
ControlPort::~ControlPort(void){
	CloseHandle(_cease_event);
	CloseHandle(_command_event);
	delete _lock;
	if(0!=_port){
		delete _port;
	}
}

/**
 * name: open
 * brief: 打开控制端口。
 * param: --
 * return: 如果控制端口打开成功返回值大于等于零，否则返回值小于零。
 */
int ControlPort::open(){
	//1.关闭当前端口。
	close();
	//2.开启端口监听线程，并且判断开始是否成功。
	_monitoring=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&ControlPort::monitoring,this,0,0));
	if((0==_monitoring)||(INVALID_HANDLE_VALUE==_monitoring)){
		_monitoring=0;
		return(-1);
	}
	//3.打开当前端口，并且判断打开是否成功。
	if(_port->open()<0){
		close();//关闭当前端口。
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: close
 * brief: 关闭控制端口。
 * param: --
 * return: --
 */
void ControlPort::close(){
	//1.关闭当前端口。
	_port->close();
	//2.关闭当前控制端口的监听线程。
	if(0!=_monitoring){
		//2-1.设置线程退出标记变量。
		_is_cease=TRUE;
		SetEvent(_cease_event);
		//2-2.等待线程退出，并且判断等待是否成功。
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_monitoring,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_monitoring,0);
		}
		//2-3.关闭监听线程内核对象。
		CloseHandle(_monitoring);
		_monitoring=0;
	}
	//3.清除相关变量。
	_is_cease=FALSE;
	clear_all_commands();
}

/**
 * name: write
 * breif: 向控制端口写指令。
 * param: command - 输入的指向指令数组的指针。
 *        size - 输入的指令数组尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ControlPort::write(const unsigned char *command,const unsigned int size){
	//1.调用基类相应处理函数。
	if(Port::write(command,size)<0){
		return(-1);
	}
	//2.向控制端口写指令。
	if(_port->write(command,size)<0){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: receive
 * brief: 接收端口数据。
 * param: data - 输入收到的数据。
 *        receive_instance - 输入的接收实例。
 * return: --
 */
void __stdcall ControlPort::receive(
	const unsigned char data,void *receive_instance){
	reinterpret_cast<ControlPort*>(receive_instance)->receive(data);
}

/**
 * name: monitoring
 * brief: 控制端口监听线程。
 * param: parameter - 输入的任意类型指针。
 * return: 此函数一直返回零。
 */
unsigned int __stdcall ControlPort::monitoring(void *parameter){
	reinterpret_cast<ControlPort*>(parameter)->monitoring();
	return(0);
}

/**
 * name: receive
 * brief: 接收端口数据。
 * param: data - 输入收到的数据。
 * return: --
 */
void ControlPort::receive(const unsigned char data){
	//1.声明当前操作所需变量。
	static std::vector<unsigned char> command_container;
	//2.如果当前收到的数据是起始位。
	if(Command::START_BIT==data){
		//2-1.如果当前指令容器为空。
		if(command_container.empty()){
			command_container.push_back(data);
			return;
		}
		//2-2.如果当前指令容器不为空。
		else{
			//2-2-1.如果当前指令第一位是起始位。
			if(Command::START_BIT==command_container[0]){
				//a.如果当前指令容器长度小于3。
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.如果当前指令容器长度大于3。
				else{
					//b-1.如果当前指令容器长度，大于等于指令应有长度减一。
					if(command_container.size()>=(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.clear();
						command_container.push_back(data);
						return;
					}
					//b-2.如果当前指令容器长度，小于指令应有长度减一。
					else{
						command_container.push_back(data);
						return;
					}
				}
			}
			//2-2-2.如果当前指令第一位不是起始位。
			else{
				command_container.clear();
				command_container.push_back(data);
				return;
			}
		}
	}
	//3.如果当前收到的数据是结束位。
	else if(Command::END_BIT==data){
		//3-1.如果当前指令容器长度为空。
		if(command_container.empty()){
			return;
		}
		//3-2.如果当前指令容器长度不为空。
		else{
			//3-2-1.如果当前指令容器首位为起始位。
			if(Command::START_BIT==command_container[0]){
				//a.如果当前指令容器长度小于三位。
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.如果当前指令容器长度大于等于三位。
				else{
					//b-1.如果当前指令容器长度，小于指令应有长度减一。
					if(command_container.size()<(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.push_back(data);
						return;
					}
					//b-2.如果当前指令容器长度，等于指令应有长度减一。
					else if(command_container.size()==(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.push_back(data);
						add_command(command_container.data(),
							command_container.size());
						command_container.clear();
						return;
					}
					//b-3.如果当前指令容器长度，大于指令应有长度减一。
					else{
						command_container.clear();
						return;
					}
				}
			}
			//3-2-2.如果当前指令容器首位不为起始位。
			else{
				command_container.clear();
				return;
			}
		}
	}
	//4.如果当前收到的数据是任意数据。
	else{
		//4-1.如果当前指令容器为空。
		if(command_container.empty()){
			return;
		}
		//4-2.如果当前指令容器不为空。
		else{
			//4-2-1.如果当前指令容器首位是起始位。
			if(Command::START_BIT==command_container[0]){
				//a.如果当前指令容器长度小于三位。
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.如果当前指令容器长度大于等于三位。
				else{
					//b-1.如果当前指令容器长度，小于等于指令应有长度减二。
					if(command_container.size()<=(
						static_cast<unsigned int>(
						command_container[2])+3)){
						command_container.push_back(data);
						return;
					}
					//b-2.如果当前指令容器长度，大于指令应有长度减二。
					else{
						command_container.clear();
						return;
					}
				}
			}
			//4-2-2.如果当前指令容器首位不是起始位。
			else{
				command_container.clear();
				return;
			}
		}
	}
}

/**
 * name: monitoring
 * brief: 控制端口监听线程实现函数。
 * param: --
 * return: 此函数一直返回零。
 */
void ControlPort::monitoring(){
	//1.声明当前操作所需变量。
	const HANDLE event_array[2]={_cease_event,_command_event};
	//2.进入无限循环，实现控制端口监听。
	while(true){
		//2-1.如果当前用户期望立即停止当前监听线程。
		if(_is_cease){
			break;
		}
		//2-2.等待事件触发，并且记录等待结果。
		const DWORD wait_result=WaitForMultipleObjects(
			2,event_array,FALSE,INFINITE);
		//2-3.如果当前用户期望立即停止当前监听线程。
		if(_is_cease){
			break;
		}
		//2-4.如果当前等待到的是停止事件。
		if(WAIT_OBJECT_0==wait_result){
			if(_is_cease){
				break;
			}else{
				continue;
			}
		}
		//2-5.如果当前等待到的是指令事件。
		else if((WAIT_OBJECT_0+1)==wait_result){
			//2-5-1.如果当前用户期望立即停止当前监听线程。
			if(_is_cease){
				break;
			}
			//2-5-2.如果当前指令队列不为空。
			while(are_there_many_commands()){
				//a.弹出一条指令。
				PtrToCommand command=pop_command();
				//b.如果当前用户期望立即停止当前监听线程。
				if(_is_cease){
					break;
				}
				//c.如果成功获取弹出的指令。
				if(static_cast<bool>(command)){
					command->analysis(*this);
				}
				//d.如果当前用户期望立即停止当前监听线程。
				if(_is_cease){
					break;
				}
			}
			//2-5-3.如果当前用户期望立即停止当前监听线程。
			if(_is_cease){
				break;
			}
		}
		//2-6.如果当前等待到的是其他未知事件。
		else{
			if(_is_cease){
				break;
			}else{
				continue;
			}
		}
	}
}

/**
 * name: add_command
 * brief: 向命令队列中添加命令。
 * param: command - 输入的指向指令的只能指针引用。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ControlPort::add_command(const PtrToCommand &command){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.向指令队列中插入一条指令。
	_commands.push_back(command);
	//3.启动指令事件。
	SetEvent(_command_event);
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: add_command
 * brief: 向命令队列中添加命令。
 * param: command - 输入的指向指令数组输入的指针。
 *        size - 输入的指令数组尺寸。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ControlPort::add_command(const unsigned char *command,const unsigned int size){
	//1.检测输入是否合法。
	if((0==command)||(0==size)){
		return(-1);
	}
	//2.创建指向指令的智能指针。
	PtrToCommand command_pointer(new Command(command,size));
	if(!static_cast<bool>(command_pointer)){
		return(-2);
	}
	//3.向指令队列中添加指令。
	if(add_command(command_pointer)<0){
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: pop_command
 * brief: 从指令队列中弹出一条指令。
 * param: --
 * return: 如果函数执行成功返回指向一条指令的智能指针，否则返回空指针。
 */
ControlPort::PtrToCommand ControlPort::pop_command(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前指令队列为空。
	if(_commands.empty()){
		return(PtrToCommand());
	}
	//3.如果当前指令队列不为空。
	else{
		PtrToCommand command=_commands.front();
		_commands.pop_front();
		return(command);
	}
}

/**
 * name: clear_all_commands
 * breif: 删除全部的命令。
 * param: --
 * return: --
 */
void ControlPort::clear_all_commands(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.清空命令队列。
	_commands.clear();
}

/**
 * name: are_there_many_commands
 * brief: 检测当前是否有一些指令存在。
 * param: --
 * return: 如果当前有指令存在返回值不等于零，否则等于零。
 */
int ControlPort::are_there_many_commands() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前没有指令存在。
	if(_commands.empty()){
		return(0);
	}
	//3.如果当前有指令存在。
	else{
		return(1);
	}
}