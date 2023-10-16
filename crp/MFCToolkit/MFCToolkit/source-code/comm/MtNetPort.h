#pragma once

#include"../Symbol"
#include<vector>
#include<memory>

class MtLock;
class MtSocket;

/**
 * name: MtNetPort
 * brief: 网口类，负责网口收、发环境的搭建。
 * author: yameng_he
 * date: 2014-12-17
 */
class MFC_TOOLKIT_API MtNetPort{
//define
public:
	typedef std::shared_ptr<MtSocket> PtrToSocket;
	typedef std::vector<PtrToSocket> SocketVector;
	typedef void(__stdcall *ReceiveCallback)(const unsigned int,const unsigned char,void *);
	enum{THREAD_EXIT_TIMEOUT=5000,MAIN_SOCKET_ID=1,};
//construction & destruction
public:
	explicit MtNetPort(ReceiveCallback receive_callback,void *receive_instance);
	~MtNetPort(void);
//interface
public:
	void close();
	int open_server(const unsigned short port,const CString &ip);
	int open_client(const unsigned short port,const CString &ip);
	int send(const unsigned int socket_id,const unsigned char *data,
		const unsigned int size,const unsigned int timeout=0);
//static implement
private:
	static unsigned int __stdcall monitoring(void *parameter);
//implement
private:
	int listen(const unsigned short port,const CString &ip);
	int connect(const unsigned short port,const CString &ip);
	void set_port(const unsigned short port);
	unsigned short get_port() const;
	void set_ip(const CString &ip);
	CString get_ip() const;
	int add_socket(PtrToSocket &socket);
	void erase_socket(const unsigned int socket_id);
	void clear_sockets();
	BOOL does_socket_exist(const unsigned int socket_id) const;
	int wait_socket_events();
	PtrToSocket get_socket(const unsigned int socket_id);
	void monitoring();
	void close_monitoring();
	int open_monitoring();
//restriction
private:
	MtNetPort(const MtNetPort &);
	MtNetPort &operator=(const MtNetPort &);
//variables
private:
	MtLock *_lock;
	unsigned short _port;
	CString _ip;
	SocketVector _sockets;
	HANDLE _monitoring;
	HANDLE _continue_monitoring_event;
	BOOL _is_monitoring;
	ReceiveCallback _receive_callback;
	void *_receive_instance;
};