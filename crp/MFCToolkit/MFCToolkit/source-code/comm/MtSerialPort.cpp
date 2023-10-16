#include"stdafx.h"
#include"MtSerialPort.h"
#include"MtSerialPortParameter.h"
#include"../tool/MtLock.h"
#include"../tool/MtAutoLock.h"
#include<process.h>
#include<assert.h>

//��ʼ����̬������
const DWORD MtSerialPort::SERIAL_PORT_EVENT_MASK=EV_RXCHAR;
const COMMTIMEOUTS MtSerialPort::SERIAL_PORT_TIMEOUTS={1000,1000,1000,1000,1000};

/**
 * name: MtSerialPort
 * brief: ���캯����
 * param: serial_port_parameter - ���ڲ�����
 *        receive_callback - ָ�򴮿ڽ������ݵĻص�������
 *        receive_instance - ָ�򴮿ڽ������ݵ�ʵ������
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
 * brief: ����������
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
 * brief: �رյ�ǰ���ڡ�
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
 * brief: �򿪵�ǰ���ڡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::open(){
	//1.�򿪴��ڣ������жϴ��ڴ��Ƿ�ɹ���
	if(open(PURGE_RXCLEAR|PURGE_TXCLEAR|
		PURGE_RXABORT|PURGE_TXABORT)<0){
		return(-1);
	}
	//2.�򿪴��ڼ����̣߳������жϴ��Ƿ�ɹ���
	if(open_monitor()<0){
		close(0);
		return(-2);
	}
	//3.�򿪴��ڷ����̣߳������жϴ��Ƿ�ɹ���
	if(open_transmitting()<0){
		close_monitor();
		close(0);
		return(-3);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: write
 * brief: �򴮿�д���ݡ�
 * param: data - ָ�����ݡ�
 *        size - ���ݳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::write(const unsigned char *data,
	const unsigned int size){
	return(add_data_to_write_buffer(data,size));
}

/**
 * name: monitor
 * brief: ���ڼ����߳�ʵ�ֺ�����
 * param: argument - ָ��ǰ���ʵ����
 * return: �˺���һֱ�����㡣
 */
unsigned int __stdcall MtSerialPort::monitor(void *argument){
	MtSerialPort *serial_port=static_cast<MtSerialPort*>(argument);
	serial_port->monitor();
	return(0);
}

/**
 * name: transmitting
 * brief: ���ڷ����߳�ʵ�ֺ�����
 * param: argument - ָ��ǰ���ʵ����
 * return: �˺���һֱ�����㡣
 */
unsigned int __stdcall MtSerialPort::transmitting(void *argument){
	MtSerialPort *serial_port=static_cast<MtSerialPort*>(argument);
	serial_port->transmitting();
	return(0);
}

/**
 * name: monitor
 * brief: ���ڼ����߳�ʵ��ʵ�ֺ�����
 * param: --
 * return: --
 */
void MtSerialPort::monitor(){
	for(;;){
		//1.������ǰ����������
		DWORD events=0;
		//2.�ȴ������¼�������
		const int result=wait_for_events(events);
		//3.����ȴ������¼�����ʧ�ܡ�
		if(result<0){
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//4.����ɹ��ȴ������ڼ����̼߳����¼���
		else if(0==result){
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//5.����ɹ��ȴ��������¼���
		else if(1==result){
			//5-1.�����ǰ�����¼�Ϊ�������¼���
			if(EV_RXCHAR&events){
				if(read()<0){
					//unfinished: �������ʧ���Ƿ�Ӧ���������ڣ�����
				}
			}
			//5-2.�ж��Ƿ�������ǰ�����߳��˳���
			if(_is_abort_monitor){
				break;
			}else{
				continue;
			}
		}
		//6.�����ǰΪ����δ֪�����
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
 * brief: �رյ�ǰ���ڼ����̡߳�
 * param: --
 * return: --
 */
void MtSerialPort::close_monitor(){
	//1.�����ǰ���ڼ����߳��Ѿ��������رմ��ڼ����̡߳�
	if((0!=_monitor)&&(INVALID_HANDLE_VALUE!=_monitor)){
		//1-1.������ֹ���ڼ����̱߳�Ǳ�����
		_is_abort_monitor=true;
		//1-2.֪ͨ���ڼ����߳��˳���
		BOOL execute_result=SetEvent(_continue_monitor_event);
		assert(TRUE==execute_result);
		//1-3.�ȴ����ڼ����߳���ȫ�˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(_monitor,THREAD_TIMEOUT)){
			execute_result=TerminateThread(_monitor,0);
			assert(TRUE==execute_result);
		}
		//1-4.���ڼ����߳��˳��󣬹ر����ڴ�����
		execute_result=CloseHandle(_monitor);
		assert(TRUE==execute_result);
	}
	//2.������ڼ����߳�������ݡ�
	_monitor=INVALID_HANDLE_VALUE;
	_is_abort_monitor=false;
}

/**
 * name: open_monitor
 * brief: �򿪵�ǰ���ڼ����̡߳�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::open_monitor(){
	//1.�����ǰ���ڼ����߳��ѱ�����������йرա�
	close_monitor();
	//2.�������ڼ����̡߳�
	_monitor=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&MtSerialPort::monitor,this,0,0));
	//3.������ڼ����߳�����ʧ�ܡ�
	if(0==_monitor||INVALID_HANDLE_VALUE==_monitor){
		_monitor=INVALID_HANDLE_VALUE;
		return(-1);
	}
	//4.������ڼ����߳������ɹ���
	return(0);
}

/**
 * name: transmitting
 * brief: ���ڷ����߳�ʵ��ʵ�ֺ�����
 * param: --
 * return: --
 */
void MtSerialPort::transmitting(){
	for(;;){
		//1.������ǰ�̼߳����¼����顣
		HANDLE event_array[2]={_continue_transmitting_event,_write_buffer_event};
		//2.�ȴ������¼�������
		const DWORD result=WaitForMultipleObjects(2,event_array,FALSE,INFINITE);
		//3.����ɹ��ȴ������ڷ����̼߳����¼���
		if(0==result){
			if(_is_abort_transmitting){
				break;
			}else{
				continue;
			}
		}
		//4.����ɹ��ȴ���д�������¼���
		else if(1==result){
			//2-2-1.���д������ݷ��Ͳ�����
			if(write()<0){
				//unfinished: ���ڷ���������Ƿ���Ҫ�������ڣ�����
			}
			//2-2-2.�ж��Ƿ�������ǰ�����߳��˳���
			if(_is_abort_transmitting){
				break;
			}else{
				continue;
			}
		}
		//5.�����ǰΪ����δ֪�����
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
 * brief: �رյ�ǰ���ڷ����̡߳�
 * param: --
 * return: --
 */
void MtSerialPort::close_transmitting(){
	//1.�����ǰ���ڷ����߳��Ѿ��������رմ��ڷ����̡߳�
	if((0!=_transmitting)&&(INVALID_HANDLE_VALUE!=_transmitting)){
		//1-1.������ֹ���ڷ����̱߳�Ǳ�����
		_is_abort_transmitting=true;
		//1-2.֪ͨ���ڷ����߳��˳���
		BOOL execute_result=SetEvent(_continue_transmitting_event);
		assert(TRUE==execute_result);
		//1-3.�ȴ����ڷ����߳���ȫ�˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(_transmitting,THREAD_TIMEOUT)){
			execute_result=TerminateThread(_transmitting,0);
			assert(TRUE==execute_result);
		}
		//1-4.���ڷ����߳��˳��󣬹ر����ڴ�����
		execute_result=CloseHandle(_transmitting);
		assert(TRUE==execute_result);
	}
	//2.������ڷ����߳�������ݡ�
	_transmitting=INVALID_HANDLE_VALUE;
	_is_abort_transmitting=false;
	clear_write_buffer();
}

/**
 * name: open_transmitting
 * brief: �򿪵�ǰ���ڷ����̡߳�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::open_transmitting(){
	//1.�����ǰ���ڷ����߳��ѱ�����������йرա�
	close_transmitting();
	//2.�������ڼ����̡߳�
	_transmitting=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&MtSerialPort::transmitting,this,0,0));
	//3.������ڷ����߳�����ʧ�ܡ�
	if(0==_transmitting||INVALID_HANDLE_VALUE==_transmitting){
		_transmitting=INVALID_HANDLE_VALUE;
		return(-1);
	}
	//4.������ڷ����߳������ɹ���
	return(0);
}

/**
 * name: close
 * brief: �رմ��ڡ�
 * param: --
 * return: --
 */
void MtSerialPort::close(const unsigned int){
	//1.������
	MtAutoLock<MtLock> lock(_serial_port_lock);
	//2.������ڴ��ڴ�״̬������йرղ�����
	if((0!=_serial_port)&&(INVALID_HANDLE_VALUE!=_serial_port)){
		const BOOL execute_result=CloseHandle(_serial_port);
		assert(TRUE==execute_result);
	}
	//3.�������������ݡ�
	_serial_port=INVALID_HANDLE_VALUE;
}

/**
 * name: open
 * brief: �򿪴��ڡ�
 * param: flags - ���ڴ򿪱�ǣ�����������ʶ���ڴ�ǰ
 *                ����Ҫ��������ݡ�
 * return: ������ڴ򿪳ɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::open(const unsigned int flags){
	//1.�رյ�ǰ���ڡ�
	close(0);
	//2.������
	MtAutoLock<MtLock> lock(_serial_port_lock);
	//3.�������ڲ�������������жϴ����Ƿ�ɹ���
	HANDLE serial_port=CreateFile(_serial_port_parameter->get_string_port(),
		GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|
		FILE_FLAG_OVERLAPPED,0);
	if(0==serial_port||INVALID_HANDLE_VALUE==serial_port){
		return(-1);
	}
	//4.Ϊ�������ô��ڲ�����
	//4-1.�������崮�ڲ����ṹ�塣
	DCB dcb;
	memset(&dcb,0,sizeof(DCB));
	//4-2.��ȡ��ǰϵͳ��Ĭ�ϵĴ��ڲ����ṹ�壬�����жϻ�ȡ�Ƿ�ɹ���
	if(!GetCommState(serial_port,&dcb)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-2);
	}
	//4-3.���õ�ǰ���ڲ�����䴮�ڲ����ṹ�塣
	_serial_port_parameter->fill_dcb(dcb);
	//4-4.Ϊ��ǰ�������ô��ڲ�����
	if(!SetCommState(serial_port,&dcb)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-3);
	}
	//5.Ϊ�������ó�ʱʱ�ޡ�
	//5-1.�������崮�ڳ�ʱ���ýṹ�塣
	COMMTIMEOUTS serial_port_timeouts(SERIAL_PORT_TIMEOUTS);
	//5-2.Ϊ�������ó�ʱʱ�ޣ������ж������Ƿ�ɹ���
	if(!SetCommTimeouts(serial_port,&serial_port_timeouts)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-4);
	}
	//6.�涨���������¼��������жϹ涨�Ƿ�ɹ���
	if(!SetCommMask(serial_port,SERIAL_PORT_EVENT_MASK)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-5);
	}
	//7.���ô��ڷ��ͻ����������ջ�������С�������ж������Ƿ�ɹ���
	if(!SetupComm(serial_port,SERIAL_PORT_RECEIVE_BUFFER_SIZE,SERIAL_PORT_SEND_BUFFER_SIZE)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-6);
	}
	//8.������ڷ��͡����ջ������Լ�����д������
	if(!PurgeComm(serial_port,flags/*PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT*/)){
		const BOOL execute_result=CloseHandle(serial_port);
		assert(TRUE==execute_result);
		return(-7);
	}
	//9.��¼��ǰ���ھ����
	_serial_port=serial_port;
	//10.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: read
 * brief: �Ӵ����ж�ȡ���ݡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::read(){
	for(;;){
		//1.������
		MtAutoLock<MtLock> lock(_serial_port_lock);
		//2.�����ǰ������δ�򿪣���ֱ�ӷ��ش���
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		//3.�����ǰ���ڴ����һ�ȡ��ǰ����״̬��
		//3-1.������ǰ�������������
		DWORD serial_port_error=0;
		COMSTAT serial_port_state;
		memset(&serial_port_state,0,sizeof(COMSTAT));
		//3-2.�����ǰ���ڴ����һ�ȡ��ǰ����״̬��
		if(!ClearCommError(_serial_port,&serial_port_error,&serial_port_state)){
			return(-2);
		}
		//4.�����ǰ���ڽ��ջ�����Ϊ�գ���ֱ��������ǰѭ����
		if(0==serial_port_state.cbInQue){
			break;
		}
		//5.��ֹ��ǰ���ڽ��еĴ��ڶ�������
		if(!PurgeComm(_serial_port,PURGE_RXABORT)){
			return(-3);
		}
		//6.ִ�д��ڶ�������
		//6-1.����׼�����д��ڶ���������ر�����
		DWORD readed_size=0;
		unsigned char data=0x00;
		OVERLAPPED overlapped;
		memset(&overlapped,0,sizeof(OVERLAPPED));
		overlapped.hEvent=_serial_port_event;
		//6-2.���д��ڶ������������ж϶�ȡ�Ƿ�ɹ���
		if(!ReadFile(_serial_port,&data,sizeof(unsigned char),&readed_size,&overlapped)){
			//6-2-1.��ȡ��ǰ���ڶ�����������Ϣ��
			const DWORD last_error=GetLastError();
			//6-2-2.�����ǰ���ڶ��������ڽ��С�
			if(ERROR_IO_PENDING==last_error){
				if(!GetOverlappedResult(_serial_port,&overlapped,&readed_size,TRUE)){
					return(-4);
				}
			}
			//6-2-3.������ڶ�����������������
			else{
				return(-5);
			}
		}
		//6-3.�����ǰ���ڶ�ȡ�����ݳߴ���Ԥ�ڵĲ�ͬ��
		if(readed_size<sizeof(unsigned char)){
			/*return(-6);*/
			//6-3-1.�����ǰϣ����ֹ�����̡߳�
			if(_is_abort_monitor){
				return(0);
			}
			//6-3-2.�ó�ʱ��Ƭ��
			Sleep(0);
			//6-3-3.�������¶�ȡ��
			continue;
		}
		//7.������ڽ��ջص��������ڣ�����ô��ڽ��ջص�������
		if(0!=_receive_callback){
			_receive_callback(data,_receive_instance);
		}
		//8.�����ǰ������ֹ�����̡߳�
		if(_is_abort_monitor){
			return(0);
		}
	}
	return(1);
}

/**
 * name: write
 * brief: �򴮿�д���ݡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::write(){
	for(;;){
		//1.��ȡ��ǰд���������ݣ����д������Ϊ�գ���ֱ��������ǰѭ����
		unsigned char data=0x00;
		if(get_data_from_write_buffer(data)<0){
			break;
		}
		//2.������
		MtAutoLock<MtLock> lock(_serial_port_lock);
		//3.�����ǰ������δ�򿪡�
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		//4.�����ǰ���ڴ�����Ϣ��
		//4-1.������ǰ�������������
		DWORD serial_port_error=0;
		COMSTAT serial_port_state;
		memset(&serial_port_state,0,sizeof(COMSTAT));
		//4-2.�����ǰ���ڴ�����Ϣ�������ж�����Ƿ�ɹ���
		if(!ClearCommError(_serial_port,&serial_port_error,&serial_port_state)){
			return(-2);
		}
		//5.��ֹ��ǰ����д���������������д��������
		if(!PurgeComm(_serial_port,/*PURGE_TXCLEAR|*/PURGE_TXABORT)){
			return(-3);
		}
		//6.���ô��ڷ������ݣ������жϷ����Ƿ�ɹ���
		//6-1.������ǰ�������������
		DWORD writed_size=0;
		OVERLAPPED overlapped;
		memset(&overlapped,0,sizeof(OVERLAPPED));
		overlapped.hEvent=_write_serial_port_event;
		//6-2.����ڷ������ݣ������жϷ����Ƿ�ɹ���
		if(!WriteFile(_serial_port,&data,sizeof(unsigned char),&writed_size,&overlapped)){
			//6-2-1.��ȡ��ǰ���ڷ�������ʧ�ܵ�ԭ��
			const DWORD last_error=GetLastError();
			//6-2-2.�����ǰ�������ݷ�����δ��ɣ���ȴ�����ɡ�
			if(ERROR_IO_PENDING==last_error){
				if(!GetOverlappedResult(_serial_port,&overlapped,&writed_size,TRUE)){
					return(-4);
				}
			}
			//6-2-3.�����ǰ�������ݷ���ʧ�ܡ�
			else{
				return(-5);
			}
		}
		//6-3.����������ݷ��Ͳ�������
		if(writed_size<sizeof(unsigned char)){
			//6-3-1.�жϵ�ǰ�Ƿ�������ֹ�����̡߳�
			if(_is_abort_transmitting){
				return(0);
			}
			//6-3-2.�ó�ʱ��Ƭ��
			Sleep(0);
			//6-3-3.�������Է������ݡ�
			continue;
		}
		//7.����������ݷ��ͳɹ����ӷ��ͻ������е����ѷ��͵����ݡ�
		pop_data_from_write_buffer();
		//8.�����ǰ������ֹ�����̡߳�
		if(_is_abort_transmitting){
			return(0);
		}
	}
	return(1);
}

/**
 * name: wait_for_events
 * brief: �ȴ������¼���
 * param: events - �����¼���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 *         �����ڼ��������¼�����ʱ������ֵΪ�㣬�����������
 *         �¼�����ʱ����һ��
 */
int MtSerialPort::wait_for_events(DWORD &events){
	//1.������ǰ�������������
	DWORD temp_events=0;
	OVERLAPPED overlapped;
	memset(&overlapped,0,sizeof(OVERLAPPED));
	overlapped.hEvent=_serial_port_event;
	BOOL waitting_result_for_events=FALSE;
	//2.Ϊ���ڰ��¼�֪ͨ�źţ�һ���¼��������
	{
		MtAutoLock<MtLock> lock(_serial_port_lock);
		if(0==_serial_port||INVALID_HANDLE_VALUE==_serial_port){
			return(-1);
		}
		waitting_result_for_events=WaitCommEvent(_serial_port,&temp_events,&overlapped);
	}
	//3.�����ǰ�ȴ������¼�����ʧ�ܡ�
	if(!waitting_result_for_events){
		//3-1.��ȡ������롣
		const DWORD last_error=GetLastError();
		//3-2.�����ǰ�����¼����ڵȴ��С�
		if(ERROR_IO_PENDING==last_error){
			//3-2-1.������ǰ�������������
			HANDLE event_array[2]={_continue_monitor_event,_serial_port_event};
			//3-2-2.�����ȴ������¼���
			const DWORD result=WaitForMultipleObjects(2,event_array,FALSE,INFINITE);
			//3-2-1.���ڼ��������¼�������
			if(WAIT_OBJECT_0==result){
				return(0);
			}
			//3-2-2.��������¼�������
			else if(WAIT_OBJECT_0+1==result){
				MtAutoLock<MtLock> lock(_serial_port_lock);
				if(!GetCommMask(_serial_port,&temp_events)){
					return(-2);
				}
			}
			//3-2-3.���δ֪�¼�������
			else{
				return(-3);
			}
		}
		//3-3.�����ǰ�ȴ������¼�����
		else{
			return(-4);
		}
	}
	//4.��¼��ǰ�ȵ��Ĵ����¼���
	events=temp_events;
	//5.�������е���ֱ�ӳɹ����ء�
	return(1);
}

/**
 * name: add_data_to_write_buffer
 * brief: �������ݵ�д�������С�
 * param: data - ָ�����ݡ�
 *        size - ���ݳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::add_data_to_write_buffer(const unsigned char *data,const unsigned int size){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ�����ش�����Ϣ��
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//3.����ǰ���ݲ��뵽д�������С�
	_write_buffer.insert(_write_buffer.end(),data,data+size);
	//4.���û������źš�
	SetEvent(_write_buffer_event);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_data_from_write_buffer
 * brief: ��д�������л�ȡ��Ҫд�����ݡ�
 * param: data - ���ص�д�������н�Ҫд�����ݡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSerialPort::get_data_from_write_buffer(unsigned char &data){
	//1.������
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.�����ǰд������Ϊ�գ���ֱ�ӷ��ء�
	if(_write_buffer.empty()){
		return(-1);
	}
	//3.��д�������л�ȡ��Ҫд�����ݡ�
	data=_write_buffer.front();
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: pop_data_from_write_buffer
 * brief: ��д�������е������ݡ�
 * param: --
 * return: --
 */
void MtSerialPort::pop_data_from_write_buffer(){
	//1.������
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.�����ǰд������Ϊ�գ���ֱ�ӷ��ء�
	if(_write_buffer.empty()){
	}
	//3.������ǰ��ȡ�����ݡ�
	else{
		_write_buffer.pop_front();
	}
}

/**
 * name: clear_write_buffer
 * brief: ���д��������ȫ�����ݡ�
 * param: --
 * return: --
 */
void MtSerialPort::clear_write_buffer(){
	//1.������
	MtAutoLock<MtLock> lock(_write_buffer_lock);
	//2.���д��������ȫ�����ݡ�
	_write_buffer.clear();
}