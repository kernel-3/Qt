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
 * brief: ���캯����
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
 * brief: ����������
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
 * brief: �򿪿��ƶ˿ڡ�
 * param: --
 * return: ������ƶ˿ڴ򿪳ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ControlPort::open(){
	//1.�رյ�ǰ�˿ڡ�
	close();
	//2.�����˿ڼ����̣߳������жϿ�ʼ�Ƿ�ɹ���
	_monitoring=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&ControlPort::monitoring,this,0,0));
	if((0==_monitoring)||(INVALID_HANDLE_VALUE==_monitoring)){
		_monitoring=0;
		return(-1);
	}
	//3.�򿪵�ǰ�˿ڣ������жϴ��Ƿ�ɹ���
	if(_port->open()<0){
		close();//�رյ�ǰ�˿ڡ�
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: close
 * brief: �رտ��ƶ˿ڡ�
 * param: --
 * return: --
 */
void ControlPort::close(){
	//1.�رյ�ǰ�˿ڡ�
	_port->close();
	//2.�رյ�ǰ���ƶ˿ڵļ����̡߳�
	if(0!=_monitoring){
		//2-1.�����߳��˳���Ǳ�����
		_is_cease=TRUE;
		SetEvent(_cease_event);
		//2-2.�ȴ��߳��˳��������жϵȴ��Ƿ�ɹ���
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_monitoring,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_monitoring,0);
		}
		//2-3.�رռ����߳��ں˶���
		CloseHandle(_monitoring);
		_monitoring=0;
	}
	//3.�����ر�����
	_is_cease=FALSE;
	clear_all_commands();
}

/**
 * name: write
 * breif: ����ƶ˿�дָ�
 * param: command - �����ָ��ָ�������ָ�롣
 *        size - �����ָ������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ControlPort::write(const unsigned char *command,const unsigned int size){
	//1.���û�����Ӧ��������
	if(Port::write(command,size)<0){
		return(-1);
	}
	//2.����ƶ˿�дָ�
	if(_port->write(command,size)<0){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: receive
 * brief: ���ն˿����ݡ�
 * param: data - �����յ������ݡ�
 *        receive_instance - ����Ľ���ʵ����
 * return: --
 */
void __stdcall ControlPort::receive(
	const unsigned char data,void *receive_instance){
	reinterpret_cast<ControlPort*>(receive_instance)->receive(data);
}

/**
 * name: monitoring
 * brief: ���ƶ˿ڼ����̡߳�
 * param: parameter - �������������ָ�롣
 * return: �˺���һֱ�����㡣
 */
unsigned int __stdcall ControlPort::monitoring(void *parameter){
	reinterpret_cast<ControlPort*>(parameter)->monitoring();
	return(0);
}

/**
 * name: receive
 * brief: ���ն˿����ݡ�
 * param: data - �����յ������ݡ�
 * return: --
 */
void ControlPort::receive(const unsigned char data){
	//1.������ǰ�������������
	static std::vector<unsigned char> command_container;
	//2.�����ǰ�յ�����������ʼλ��
	if(Command::START_BIT==data){
		//2-1.�����ǰָ������Ϊ�ա�
		if(command_container.empty()){
			command_container.push_back(data);
			return;
		}
		//2-2.�����ǰָ��������Ϊ�ա�
		else{
			//2-2-1.�����ǰָ���һλ����ʼλ��
			if(Command::START_BIT==command_container[0]){
				//a.�����ǰָ����������С��3��
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.�����ǰָ���������ȴ���3��
				else{
					//b-1.�����ǰָ���������ȣ����ڵ���ָ��Ӧ�г��ȼ�һ��
					if(command_container.size()>=(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.clear();
						command_container.push_back(data);
						return;
					}
					//b-2.�����ǰָ���������ȣ�С��ָ��Ӧ�г��ȼ�һ��
					else{
						command_container.push_back(data);
						return;
					}
				}
			}
			//2-2-2.�����ǰָ���һλ������ʼλ��
			else{
				command_container.clear();
				command_container.push_back(data);
				return;
			}
		}
	}
	//3.�����ǰ�յ��������ǽ���λ��
	else if(Command::END_BIT==data){
		//3-1.�����ǰָ����������Ϊ�ա�
		if(command_container.empty()){
			return;
		}
		//3-2.�����ǰָ���������Ȳ�Ϊ�ա�
		else{
			//3-2-1.�����ǰָ��������λΪ��ʼλ��
			if(Command::START_BIT==command_container[0]){
				//a.�����ǰָ����������С����λ��
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.�����ǰָ���������ȴ��ڵ�����λ��
				else{
					//b-1.�����ǰָ���������ȣ�С��ָ��Ӧ�г��ȼ�һ��
					if(command_container.size()<(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.push_back(data);
						return;
					}
					//b-2.�����ǰָ���������ȣ�����ָ��Ӧ�г��ȼ�һ��
					else if(command_container.size()==(
						static_cast<unsigned int>(
						command_container[2])+4)){
						command_container.push_back(data);
						add_command(command_container.data(),
							command_container.size());
						command_container.clear();
						return;
					}
					//b-3.�����ǰָ���������ȣ�����ָ��Ӧ�г��ȼ�һ��
					else{
						command_container.clear();
						return;
					}
				}
			}
			//3-2-2.�����ǰָ��������λ��Ϊ��ʼλ��
			else{
				command_container.clear();
				return;
			}
		}
	}
	//4.�����ǰ�յ����������������ݡ�
	else{
		//4-1.�����ǰָ������Ϊ�ա�
		if(command_container.empty()){
			return;
		}
		//4-2.�����ǰָ��������Ϊ�ա�
		else{
			//4-2-1.�����ǰָ��������λ����ʼλ��
			if(Command::START_BIT==command_container[0]){
				//a.�����ǰָ����������С����λ��
				if(command_container.size()<3){
					command_container.push_back(data);
					return;
				}
				//b.�����ǰָ���������ȴ��ڵ�����λ��
				else{
					//b-1.�����ǰָ���������ȣ�С�ڵ���ָ��Ӧ�г��ȼ�����
					if(command_container.size()<=(
						static_cast<unsigned int>(
						command_container[2])+3)){
						command_container.push_back(data);
						return;
					}
					//b-2.�����ǰָ���������ȣ�����ָ��Ӧ�г��ȼ�����
					else{
						command_container.clear();
						return;
					}
				}
			}
			//4-2-2.�����ǰָ��������λ������ʼλ��
			else{
				command_container.clear();
				return;
			}
		}
	}
}

/**
 * name: monitoring
 * brief: ���ƶ˿ڼ����߳�ʵ�ֺ�����
 * param: --
 * return: �˺���һֱ�����㡣
 */
void ControlPort::monitoring(){
	//1.������ǰ�������������
	const HANDLE event_array[2]={_cease_event,_command_event};
	//2.��������ѭ����ʵ�ֿ��ƶ˿ڼ�����
	while(true){
		//2-1.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
		if(_is_cease){
			break;
		}
		//2-2.�ȴ��¼����������Ҽ�¼�ȴ������
		const DWORD wait_result=WaitForMultipleObjects(
			2,event_array,FALSE,INFINITE);
		//2-3.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
		if(_is_cease){
			break;
		}
		//2-4.�����ǰ�ȴ�������ֹͣ�¼���
		if(WAIT_OBJECT_0==wait_result){
			if(_is_cease){
				break;
			}else{
				continue;
			}
		}
		//2-5.�����ǰ�ȴ�������ָ���¼���
		else if((WAIT_OBJECT_0+1)==wait_result){
			//2-5-1.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
			if(_is_cease){
				break;
			}
			//2-5-2.�����ǰָ����в�Ϊ�ա�
			while(are_there_many_commands()){
				//a.����һ��ָ�
				PtrToCommand command=pop_command();
				//b.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
				if(_is_cease){
					break;
				}
				//c.����ɹ���ȡ������ָ�
				if(static_cast<bool>(command)){
					command->analysis(*this);
				}
				//d.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
				if(_is_cease){
					break;
				}
			}
			//2-5-3.�����ǰ�û���������ֹͣ��ǰ�����̡߳�
			if(_is_cease){
				break;
			}
		}
		//2-6.�����ǰ�ȴ�����������δ֪�¼���
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
 * brief: �����������������
 * param: command - �����ָ��ָ���ֻ��ָ�����á�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ControlPort::add_command(const PtrToCommand &command){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ָ������в���һ��ָ�
	_commands.push_back(command);
	//3.����ָ���¼���
	SetEvent(_command_event);
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: add_command
 * brief: �����������������
 * param: command - �����ָ��ָ�����������ָ�롣
 *        size - �����ָ������ߴ硣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ControlPort::add_command(const unsigned char *command,const unsigned int size){
	//1.��������Ƿ�Ϸ���
	if((0==command)||(0==size)){
		return(-1);
	}
	//2.����ָ��ָ�������ָ�롣
	PtrToCommand command_pointer(new Command(command,size));
	if(!static_cast<bool>(command_pointer)){
		return(-2);
	}
	//3.��ָ����������ָ�
	if(add_command(command_pointer)<0){
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: pop_command
 * brief: ��ָ������е���һ��ָ�
 * param: --
 * return: �������ִ�гɹ�����ָ��һ��ָ�������ָ�룬���򷵻ؿ�ָ�롣
 */
ControlPort::PtrToCommand ControlPort::pop_command(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰָ�����Ϊ�ա�
	if(_commands.empty()){
		return(PtrToCommand());
	}
	//3.�����ǰָ����в�Ϊ�ա�
	else{
		PtrToCommand command=_commands.front();
		_commands.pop_front();
		return(command);
	}
}

/**
 * name: clear_all_commands
 * breif: ɾ��ȫ�������
 * param: --
 * return: --
 */
void ControlPort::clear_all_commands(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���������С�
	_commands.clear();
}

/**
 * name: are_there_many_commands
 * brief: ��⵱ǰ�Ƿ���һЩָ����ڡ�
 * param: --
 * return: �����ǰ��ָ����ڷ���ֵ�������㣬��������㡣
 */
int ControlPort::are_there_many_commands() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰû��ָ����ڡ�
	if(_commands.empty()){
		return(0);
	}
	//3.�����ǰ��ָ����ڡ�
	else{
		return(1);
	}
}