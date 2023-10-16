#pragma once

class Command;

/**
 * name: Port
 * breif: 端口类，它是所有通信端口的基类，负责实现
 *        对通信端口的抽象与描述。
 * author: yameng_he
 * date: 2016-01-27.
 */
class Port{
//construction & destruction
public:
	Port(void);
	virtual ~Port(void);
//overrides
public:
	virtual int write(const unsigned char *command,const unsigned int size)=0;
//restriction
private:
	Port(const Port &);
	Port &operator=(const Port &);
};