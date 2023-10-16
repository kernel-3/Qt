#include"stdafx.h"
#include"MtSerialPort.h"
#include"MtSerialPortParameter.h"
#include"../tool/MtLock.h"
#include"../tool/MtAutoLock.h"
#include<process.h>
#include<assert.h>

//初始化静态变量。
const DWORD MtSerialPort::SERIAL_PORT_EVENT_MASK=EV_RXCHAR;
const COMMTIMEOUTS MtSerialPort::SERIAL_PORT_TIMEOUTS={1000,1000,1000,1000,1000};

/**
 * name: MtSerialPort
 * brief: 构造函数。
 * param: serial_port_parameter - 串口参数。
 *        receive_callback - 指向串口接收数据的回调函数。
 *        receive_instance - 指向串口接收数据的实例对象。
 * return: --
 */
MtSerialPort::MtSerialPort(const MtSerialPortParameter &serial_port_parameter,
  ReceiveCallback receive_callback,void *receive_instance)
	:_serial_port_parameter(new MtSerialPortParameter(serial_port_parameter))
	,_serial_port_lock(new MtLock)
	,_serial_port(INVALID_HANDLE_VALUE)
	,_serial_port_event(CreateEvent(0,TRUE,FALSE,0))
	,_write_serial_port_event(CreateEvent(0,TRUE,FALSE,0))
	,_write_buffer_lock(new MtLock)
	,_write_buffer_event(CreateEvent(0,FALSE,FALSE,0))
	,_write_buffer()
	,_monitor(INVALID_HANDLE_VALUE)
	,_continue_monitor_event(CreateEvent(0,FALSE,FALSE,0))
	,_is_abort_monitor(false)
	,_transmitting(INVALID_HANDLE_VALUE)
	,_continue_transmitting_event(CreateEvent(0,FALSE,FALSE,0))
	,_is_abort_transmitting(false)
	,_receive_callback(receive_callback)
	,_receive_instance(receive_instance){
	assert((0!=_serial_port_event)&&(INVALID_HANDLE_VALUE!=_serial_port_event)&&
		(0!=_write_serial_port_event)&&(INVALID_HANDLE_VALUE!=_write_serial_port_event)&&
		(0!=_write_buffer_event)&&(INVALID_HANDLE_VALUE!=_write_buffer_event)&&
		(0!=_continue_monitor_event)&&(INVALID_HANDLE_VALUE!=_continue_monitor_event)&&
		(0!=_continue_transmitting_event)&&(INVALID_HANDLE_VALUE!=_continue_transmitting_event));
}

/**
 * name: ~MtSerialPort
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtSerialPort::~MtSerialPort(void){
	close();
	CloseHandle(_continue_transmitting_event);
	CloseHandle(_continue_monitor_event);
	CloseHandle(_write_buffer_event);
	CloseHandle(_write_serial_port_event);
	CloseHandle(_serial_port_event);
	delete _write_buffer_lock;
	delete _serial_port_lock;
	delete _serial_port_parameter;
}

/**
 * name: close
 * brief: 关闭当前串口。
 * param: --
 * return: --
 */
void MtSerialPort::close(){
	close_transmitting();
	close_monitor();
	close(0);
}

/**
 * name: open
 * brief: 打开当前串口。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::open(){
	//1.打开串口，并且判断串口打开是否成功。
	if(open(PURGE_RXCLEAR|PURGE_TXCLEAR|
		PURGE_RXABORT|PURGE_TXABORT)<0){
		return(-1);
	}
	//2.打开串口监听线程，并且判断打开是否成功。
	if(open_monitor()<0){
		close(0);
		return(-2);
	}
	//3.打开串口发送线程，并且判断打开是否成功。
	if(open_transmitting()<0){
		close_monitor();
		close(0);
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: write
 * brief: 向串口写数据。
 * param: data - 指向数据。
 *        size - 数据尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::write(const unsigned char *data,
	const unsigned int size){
	return(add_data_to_write_buffer(data,size));
}

/**
 * name: monitor
 * brief: 串口监听线程实现函数。
 * param: argument - 指向当前类的实例。
 * return: 此函数一直返回零。
 */
unsigned int __stdcall MtSerialPort::monitor(void *argument){
	MtSerialPort *serial_port=static_cast<MtSerialPort*>(argument);
	serial_port->monitor();
	return(0);
}

/**
 * name: transmitting
 * brief: 串口发送线程实现函数。
 * param: argument - 指向当前类的实例。
 * return: 此函数一直返回零。
 */
unsigned int __stdcall MtSerialPort::transmitting(void *argument){
	MtSerialPort *serial_port=static_cast<MtSerialPort*>(argument);
	serial_port->transmitting();
	return(0);
}

/**
 * name: monitor
 * brief: 串口监听线程实际实现函数。
 * param: --
 * return: --
 */
void MtSerialPort::monitor(){
	for(;;){
		//1.声明当前操作变量。
		DWORD events=0;
		//2.等待串口事件发生。
		const int result=wait_for_events(events);
		//3.如果等待串口事件触发失败。
		if(result<0){
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//4.如果成功等待到串口监听线程继续事件。
		else if(0==result){
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//5.如果成功等待到串口事件。
		else if(1==result){
			//5-1.如果当前串口事件为“读”事件。
			if(EV_RXCHAR&events){
				if(read()<0){
					//unfinished: 如果接收失败是否应该重启串口？？？
				}
			}
			//5-2.判断是否期望当前监听线程退出。
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//6.如果当前为其它未知情况。
		else{
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
	}
}

/**
 * name: close_monitor
 * brief: 关闭当前串口监听线程。
 * param: --
 * return: --
 */
void MtSerialPort::close_monitor(){
	//1.如果当前串口监听线程已经创建，关闭串口监听线程。
	if((0!=_monitor)&&(INVALID_HANDLE_VALUE!=_monitor)){
		//1-1.设置终止串口监听线程标记变量。
		_is_abort_monitor=true;
		//1-2.通知串口监听线程退出。
		BOOL execute_result=SetEvent(_continue_monitor_event);
		assert(TRUE==execute_result);
		//1-3.等待串口监听线程完全退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(_monitor,THREAD_TIMEOUT)){
			execute_result=TerminateThread(_monitor,0);
			assert(TRUE==execute_result);
		}
		//1-4.串口监听线程退出后，关闭其内存句柄。
		execute_result=CloseHandle(_monitor);
		assert(TRUE==execute_result);
	}
	//2.清除串口监听线程相关数据。
	_monitor=INVALID_HANDLE_VALUE;
	_is_abort_monitor=false;
}

/**
 * name: open_monitor
 * brief: 打开当前串口监听线程。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::open_monitor(){
	//1.如果当前串口监听线程已被创建，则进行关闭。
	close_monitor();
	//2.启动串口监听线程。
	_monitor=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&MtSerialPort::monitor,this,0,0));
	//3.如果串口监听线程启动失败。
	if(0==_monitor||INVALID_HANDLE_VALUE==_monitor){
		_monitor=INVALID_HANDLE_VALUE;
		return(-1);
	}
	//4.如果串口监听线程启动成功。
	return(0);
}

/**
 * name: transmitting
 * brief: 串口发送线程实际实现函数。
 * param: --
 * return: --
 */
void MtSerialPort::transmitting(){
	for(;;){
		//1.创建当前线程监听事件数组。
		HANDLE event_array[2]={_continue_transmitting_event,_write_buffer_event};
		//2.等待监听事件触发。
		const DWORD result=WaitForMultipleObjects(2,event_array,FALSE,INFINITE);
		//3.如果成功等待到串口发送线程继续事件。
		if(0==result){
			if(_is_abort_transmitting){
				break;
			}else{
				continue;
			}
		}
		//4.如果成功等待到写缓冲区事件。
		else if(1==result){
			//2-2-1.进行串口数据发送操作。
			if(write()<0){
				//unfinished: 串口发生错误后，是否需要重启串口？？？
			}
			//2-2-2.判断是否期望当前发送线程退出。
			if(_is_abort_transmitting){
				break;
			}else{
				continue;
			}
		}
		//5.如果当前为其它未知情况。
		else{
			if(_is_abort_transmitting){
				break;
			}else{
				continue;
			}
		}
	}
}

/**
 * name: close_transmitting
 * brief: 关闭当前串口发送线程。
 * param: --
 * return: --
 */
void MtSerialPort::close_transmitting(){
	//1.如果当前串口发送线程已经创建，关闭串口发送线程。
	if((0!=_transmitting)&&(INVALID_HANDLE_VALUE!=_transmitting)){
		//1-1.设置终止串口发送线程标记变量。
		_is_abort_transmitting=true;
		//1-2.通知串口发送线程退出。
		BOOL execute_result=SetEvent(_continue_transmitting_event);
		assert(TRUE==execute_result);
		//1-3.等待串口发送线程完全退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(_transmitting,THREAD_TIMEOUT)){
			execute_result=TerminateThread(_transmitting,0);
			assert(TRUE==execute_result);
		}
		//1-4.串口发送线程退出后，关闭其内存句柄。
		execute_result=CloseHandle(_transmitting);
		assert(TRUE==execute_result);
	}
	//2.清除串口发送线程相关数据。
	_transmitting=INVALID_HANDLE_VALUE;
	_is_abort_transmitting=false;
	clear_write_buffer();
}

/**
 * name: open_transmitting
 * brief: 打开当前串口发送线程。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::open_transmitting(){
	//1.如果当前串口发送线程已被创建，则进行关闭。
	close_transmitting();
	//2.启动串口监听线程。
	_transmitting=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&MtSerialPort::transmitting,this,0,0));
	//3.如果串口发送线程启动失败。
	if(0==_transmitting||INVALID_HANDLE_VALUE==_transmitting){
		_transmitting=INVALID_HANDLE_VALUE;
		return(-1);
	}
	//4.如果串口发送线程启动成功。
	return(0);
}

/**
 * name: close
 * brief: 关闭串口。
 * param: --
 * return: --
 */
void MtSerialPort::close(const unsigned int){
	//1.加锁。
	MtAutoLock<MtLock> lock(_serial_port_lock);
	//2.如果串口处于打开状态，则进行关闭操作。
	if((0!=_serial_port)&&(INVALID_HANDLE_VALUE!=_serial_port)){
		const BOOL execute_result=CloseHandle(_serial_port);
		assert(TRUE==execute_result);
	}
	//3.清除串口相关数据。
	_serial_port=INVALID_HANDLE_VALUE;
}

/**
 * name: open
 * brief: 打开串口。
 * param: flags - 串口打开标记，这里用来标识串口打开前
 *                所需要清理的内容。
 * return: 如果串口打开成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::open(const unsigned int flags){
	//1.关闭当前串口。
	close(0);
	//2.上锁。
	MtAutoLock<MtLock> lock(_serial_port_lock);
	//3.创建串口操作句柄，并且判断创建是否成功。
	HANDLE serial_port=CreateFile(_serial_port_parameter->get_string_port(),
		GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|
		FILE_FLAG_OVERLAPPED,0);
	if(0==serial_port||INVALID_HANDLE_VALUE==serial_port){
		return(-1);
	}
	//4.为串口设置串口参数。
	//4-1.声明定义串口参数结构体。
	DCB dcb;
	memset(&dcb,0,sizeof(DCB));
	//4-2.获取当前系统中默认的串口参数结构体，并且判断获取是否成功。
	if(!GetCommState(serial_port,&dcb)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-2);
	}
	//4-3.利用当前串口参数填充串口参数结构体。
	_serial_port_parameter->fill_dcb(dcb);
	//4-4.为当前串口设置串口参数。
	if(!SetCommState(serial_port,&dcb)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-3);
	}
	//5.为串口设置超时时限。
	//5-1.声明定义串口超时设置结构体。
	COMMTIMEOUTS serial_port_timeouts(SERIAL_PORT_TIMEOUTS);
	//5-2.为串口设置超时时限，并且判断设置是否成功。
	if(!SetCommTimeouts(serial_port,&serial_port_timeouts)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-4);
	}
	//6.规定监听串口事件，并且判断规定是否成功。
	if(!SetCommMask(serial_port,SERIAL_PORT_EVENT_MASK)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-5);
	}
	//7.设置串口发送缓冲区、接收缓冲区大小，并且判断设置是否成功。
	if(!SetupComm(serial_port,SERIAL_PORT_RECEIVE_BUFFER_SIZE,SERIAL_PORT_SEND_BUFFER_SIZE)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-6);
	}
	//8.清除串口发送、接收缓冲区以及读、写操作。
	if(!PurgeComm(serial_port,flags/*PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT*/)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-7);
	}
	//9.记录当前串口句柄。
	_serial_port=serial_port;
	//10.程序运行到此成功返回。
	return(0);
}

/**
 * name: read
 * brief: 从串口中读取数据。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::read(){
	for(;;){
		//1.加锁。
		MtAutoLock<MtLock> lock(_serial_port_lock);
		//2.如果当前串口尚未打开，则直接返回错误。
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		//3.清除当前串口错误并且获取当前串口状态。
		//3-1.声明当前操作所需变量。
		DWORD serial_port_error=0;
		COMSTAT serial_port_state;
		memset(&serial_port_state,0,sizeof(COMSTAT));
		//3-2.清除当前串口错误并且获取当前串口状态。
		if(!ClearCommError(_serial_port,&serial_port_error,&serial_port_state)){
			return(-2);
		}
		//4.如果当前串口接收缓冲区为空，则直接跳出当前循环。
		if(0==serial_port_state.cbInQue){
			break;
		}
		//5.终止当前正在进行的串口读操作。
		if(!PurgeComm(_serial_port,PURGE_RXABORT)){
			return(-3);
		}
		//6.执行串口读操作。
		//6-1.声明准备进行串口读操作的相关变量。
		DWORD readed_size=0;
		unsigned char data=0x00;
		OVERLAPPED overlapped;
		memset(&overlapped,0,sizeof(OVERLAPPED));
		overlapped.hEvent=_serial_port_event;
		//6-2.进行串口读操作，并且判断读取是否成功。
		if(!ReadFile(_serial_port,&data,sizeof(unsigned char),&readed_size,&overlapped)){
			//6-2-1.获取当前串口读操作错误信息。
			const DWORD last_error=GetLastError();
			//6-2-2.如果当前串口读操作正在进行。
			if(ERROR_IO_PENDING==last_error){
				if(!GetOverlappedResult(_serial_port,&overlapped,&readed_size,TRUE)){
					return(-4);
				}
			}
			//6-2-3.如果串口读操作发生其它错误。
			else{
				return(-5);
			}
		}
		//6-3.如果当前串口读取的数据尺寸与预期的不同。
		if(readed_size<sizeof(unsigned char)){
			/*return(-6);*/
			//6-3-1.如果当前希望终止监听线程。
			if(_is_abort_monitor){
				return(0);
			}
			//6-3-2.让出时间片。
			Sleep(0);
			//6-3-3.尝试重新读取。
			continue;
		}
		//7.如果串口接收回调函数存在，则调用串口接收回调函数。
		if(0!=_receive_callback){
			_receive_callback(data,_receive_instance);
		}
		//8.如果当前期望终止监听线程。
		if(_is_abort_monitor){
			return(0);
		}
	}
	return(1);
}

/**
 * name: write
 * brief: 向串口写数据。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::write(){
	for(;;){
		//1.获取当前写缓冲区数据，如果写缓冲区为空，则直接跳出当前循环。
		unsigned char data=0x00;
		if(get_data_from_write_buffer(data)<0){
			break;
		}
		//2.加锁。
		MtAutoLock<MtLock> lock(_serial_port_lock);
		//3.如果当前串口尚未打开。
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		//4.清除当前串口错误信息。
		//4-1.声明当前操作所需变量。
		DWORD serial_port_error=0;
		COMSTAT serial_port_state;
		memset(&serial_port_state,0,sizeof(COMSTAT));
		//4-2.清除当前串口错误信息，并且判断清除是否成功。
		if(!ClearCommError(_serial_port,&serial_port_error,&serial_port_state)){
			return(-2);
		}
		//5.终止当前串口写操作并且清除串口写缓冲区。
		if(!PurgeComm(_serial_port,/*PURGE_TXCLEAR|*/PURGE_TXABORT)){
			return(-3);
		}
		//6.利用串口发送数据，并且判断发送是否成功。
		//6-1.声明当前操作所需变量。
		DWORD writed_size=0;
		OVERLAPPED overlapped;
		memset(&overlapped,0,sizeof(OVERLAPPED));
		overlapped.hEvent=_write_serial_port_event;
		//6-2.命令串口发送数据，并且判断发送是否成功。
		if(!WriteFile(_serial_port,&data,sizeof(unsigned char),&writed_size,&overlapped)){
			//6-2-1.获取当前串口发送数据失败的原因。
			const DWORD last_error=GetLastError();
			//6-2-2.如果当前串口数据发送尚未完成，则等待其完成。
			if(ERROR_IO_PENDING==last_error){
				if(!GetOverlappedResult(_serial_port,&overlapped,&writed_size,TRUE)){
					return(-4);
				}
			}
			//6-2-3.如果当前串口数据发送失败。
			else{
				return(-5);
			}
		}
		//6-3.如果串口数据发送不完整。
		if(writed_size<sizeof(unsigned char)){
			//6-3-1.判断当前是否期望终止发送线程。
			if(_is_abort_transmitting){
				return(0);
			}
			//6-3-2.让出时间片。
			Sleep(0);
			//6-3-3.继续尝试发送数据。
			continue;
		}
		//7.如果串口数据发送成功，从发送缓冲区中弹出已发送的数据。
		pop_data_from_write_buffer();
		//8.如果当前期望终止发送线程。
		if(_is_abort_transmitting){
			return(0);
		}
	}
	return(1);
}

/**
 * name: wait_for_events
 * brief: 等待串口事件。
 * param: events - 串口事件。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 *         当串口监听继续事件触发时，返回值为零，如果串口其它
 *         事件触发时返回一。
 */
int MtSerialPort::wait_for_events(DWORD &events){
	//1.声明当前操作所需变量。
	DWORD temp_events=0;
	OVERLAPPED overlapped;
	memset(&overlapped,0,sizeof(OVERLAPPED));
	overlapped.hEvent=_serial_port_event;
	BOOL waitting_result_for_events=FALSE;
	//2.为串口绑定事件通知信号（一个事件句柄）。
	{
		MtAutoLock<MtLock> lock(_serial_port_lock);
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		waitting_result_for_events=WaitCommEvent(_serial_port,&temp_events,&overlapped);
	}
	//3.如果当前等待串口事件触发失败。
	if(!waitting_result_for_events){
		//3-1.获取错误编码。
		const DWORD last_error=GetLastError();
		//3-2.如果当前串口事件正在等待中。
		if(ERROR_IO_PENDING==last_error){
			//3-2-1.声明当前操作所需变量。
			HANDLE event_array[2]={_continue_monitor_event,_serial_port_event};
			//3-2-2.继续等待串口事件。
			const DWORD result=WaitForMultipleObjects(2,event_array,FALSE,INFINITE);
			//3-2-1.串口监听继续事件触发。
			if(WAIT_OBJECT_0==result){
				return(0);
			}
			//3-2-2.如果串口事件触发。
			else if(WAIT_OBJECT_0+1==result){
				MtAutoLock<MtLock> lock(_serial_port_lock);
				if(!GetCommMask(_serial_port,&temp_events)){
					return(-2);
				}
			}
			//3-2-3.如果未知事件触发。
			else{
				return(-3);
			}
		}
		//3-3.如果当前等待串口事件出错。
		else{
			return(-4);
		}
	}
	//4.记录当前等到的串口事件。
	events=temp_events;
	//5.程序运行到此直接成功返回。
	return(1);
}

/**
 * name: add_data_to_write_buffer
 * brief: 增加数据到写缓冲区中。
 * param: data - 指向数据。
 *        size - 数据尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::add_data_to_write_buffer(const unsigned char *data,const unsigned int size){
	//1.如果当前传递的参数不合法，则直接返回相关错误信息。
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//3.将当前数据插入到写缓冲区中。
	_write_buffer.insert(_write_buffer.end(),data,data+size);
	//4.设置缓冲区信号。
	SetEvent(_write_buffer_event);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_data_from_write_buffer
 * brief: 从写缓冲区中获取将要写的数据。
 * param: data - 返回的写缓冲区中将要写的数据。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSerialPort::get_data_from_write_buffer(unsigned char &data){
	//1.加锁。
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.如果当前写缓冲区为空，则直接返回。
	if(_write_buffer.empty()){
		return(-1);
	}
	//3.从写缓冲区中获取将要写的数据。
	data=_write_buffer.front();
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: pop_data_from_write_buffer
 * brief: 从写缓冲区中弹出数据。
 * param: --
 * return: --
 */
void MtSerialPort::pop_data_from_write_buffer(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.如果当前写缓冲区为空，则直接返回。
	if(_write_buffer.empty()){
	}
	//3.弹出当前获取的数据。
	else{
		_write_buffer.pop_front();
	}
}

/**
 * name: clear_write_buffer
 * brief: 清除写缓冲区中全部数据。
 * param: --
 * return: --
 */
void MtSerialPort::clear_write_buffer(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.清除写缓冲区中全部数据。
	_write_buffer.clear();
}