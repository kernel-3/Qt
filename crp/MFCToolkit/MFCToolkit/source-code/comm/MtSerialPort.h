#pragma once

#include"../Symbol"
#include<deque>

class MtLock;
class MtSerialPortParameter;

/**
 * name: MtSerialPort
 * brief: 串口类，负责串口收、发环境的搭建。
 * author: yameng_he
 * date: 2014-12-11
 */
class MFC_TOOLKIT_API MtSerialPort{
//define
public:
	static const DWORD SERIAL_PORT_EVENT_MASK;
	static const COMMTIMEOUTS SERIAL_PORT_TIMEOUTS;
	typedef std::deque<unsigned char> Buffer;
	typedef void(__stdcall *ReceiveCallback)(const unsigned char,void *receive_instance);
	enum{THREAD_TIMEOUT=5000,SERIAL_PORT_SEND_BUFFER_SIZE=4096,SERIAL_PORT_RECEIVE_BUFFER_SIZE=4096};
//construction & destruction
public:
	explicit MtSerialPort(const MtSerialPortParameter &serial_port_parameter,
		ReceiveCallback receive_callback,void *receive_instance);
	~MtSerialPort(void);
//interface
public:
	void close();
	int open();
	int write(const unsigned char *data,const unsigned int size);
//static implement
private:
	static unsigned int __stdcall monitor(void *argument);
	static unsigned int __stdcall transmitting(void *argument);
//implement
private:
	void monitor();
	void close_monitor();
	int open_monitor();
	void transmitting();
	void close_transmitting();
	int open_transmitting();
	void close(const unsigned int);
	int open(const unsigned int flags);
	int read();
	int write();
	int wait_for_events(DWORD &events);
	int add_data_to_write_buffer(const unsigned char *data,const unsigned int size);
	int get_data_from_write_buffer(unsigned char &data);
	void pop_data_from_write_buffer();
	void clear_write_buffer();
//restriction
private:
	MtSerialPort(const MtSerialPort &);
	MtSerialPort &operator=(const MtSerialPort &);
//variables
private:
	MtSerialPortParameter *_serial_port_parameter;
	MtLock *_serial_port_lock;
	HANDLE _serial_port;
	HANDLE _serial_port_event;
	HANDLE _write_serial_port_event;
	MtLock *_write_buffer_lock;
	HANDLE _write_buffer_event;
	Buffer _write_buffer;
	HANDLE _monitor;
	HANDLE _continue_monitor_event;
	bool _is_abort_monitor;
	HANDLE _transmitting;
	HANDLE _continue_transmitting_event;
	bool _is_abort_transmitting;
	ReceiveCallback _receive_callback;
	void *_receive_instance;
};