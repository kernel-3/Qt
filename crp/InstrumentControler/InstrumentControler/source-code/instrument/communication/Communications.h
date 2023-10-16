#pragma once

class Port;
class ControlPort;

/**
 * name: Communications
 * breif: 设备通信类，负责实现设备的通信功能。
 * author: yameng_he
 * date: 2016-01-26.
 */
class Communications{
//define
public:
	typedef enum{
		PORT_ID_CONTROL,
	}PortID;
//construction & destruction
public:
	Communications(void);
	~Communications(void);
//interface
public:
	ControlPort *get_control_port();
//implement
private:
	Port *get_port(const PortID port_id);
//restriction
private:
	Communications(const Communications &);
	Communications &operator=(const Communications &);
//variables
private:
	Port *_control_port;
};