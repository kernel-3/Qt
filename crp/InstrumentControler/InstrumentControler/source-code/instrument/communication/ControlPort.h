#pragma once

#include"Port.h"
#include<memory>
#include<deque>

class MtSerialPort;
class Command;
class MtLock;

/**
 * name: ControlPort
 * brief: 控制端口类，通过此端口类控制设备。
 * author: yameng_he
 * date: 2016-01-26.
 */
class ControlPort
	:public Port{
//define
public:
	enum{THREAD_EXITING_TIMEOUT=5000,};
	typedef std::shared_ptr<Command> PtrToCommand;
	typedef std::deque<PtrToCommand> CommandQueue;
//construction & destruction
public:
	ControlPort(void);
	virtual ~ControlPort(void);
//interface
public:
	int open();
	void close();
//overrides
public:
	virtual int write(const unsigned char *command,const unsigned int size);
//implement
private:
	static void __stdcall receive(const unsigned char data,void *receive_instance);
	static unsigned int __stdcall monitoring(void *parameter);
//implement
private:
	void receive(unsigned char data);
	void monitoring();
	int add_command(const PtrToCommand &command);
	int add_command(const unsigned char *command,const unsigned int size);
	PtrToCommand pop_command();
	void clear_all_commands();
	int are_there_many_commands() const;
//variables
private:
	MtSerialPort *_port;
	BOOL _is_cease;
	HANDLE _cease_event;
	HANDLE _monitoring;
	MtLock *_lock;
	HANDLE _command_event;
	CommandQueue _commands;
};

