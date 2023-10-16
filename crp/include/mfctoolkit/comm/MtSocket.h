#pragma once

#include<WinSock2.h>
#include<string>
#include<sstream>
#include<memory>
#include<vector>
#include"../Symbol"

class MtLock;

/**
 * name: MtSocket
 * brief: 套接字类，负责描述一个套接字以及封装套接字相关操作。
 * author: yameng_he
 * date: 2014-12-12
 */
class MFC_TOOLKIT_API MtSocket{
//define
public:
	typedef std::shared_ptr<MtSocket> PtrToSocket;
//construction & destruction
public:
	MtSocket(void);
	~MtSocket(void);
//interface
public:
	void release();
	int create(const long network_events,const int address_family=AF_INET,
		const int socket_type=SOCK_STREAM,const int network_protocol=IPPROTO_IP);
	int attach(const SOCKET socket,const long network_events);
	void detach();
	int bind(const unsigned short network_port,const CString &ip_address=_T(""),
		const int address_family=AF_INET);
	int listen(const int listen_number=SOMAXCONN);
	PtrToSocket accept(const long network_events=FD_READ|FD_WRITE|FD_CLOSE);
	int connect(const unsigned short network_port,const CString &ip_address,
		const int address_family=AF_INET,const unsigned int timeout=2000);
	int enum_network_events(WSANETWORKEVENTS &network_events);
	int block_close();
	WSAEVENT get_socket_event() const;
	int send(const unsigned char *data,const unsigned int size);
	int send(const unsigned char *data,const unsigned int size,const unsigned int timeout);
	int receive(unsigned char *data,const unsigned int size);
	int set_send_buffer_size(const int size);
	int get_send_buffer_size() const;
	int set_receive_buffer_size(const int size);
	int get_receive_buffer_size() const;
	int get_data_size_in_receive_buffer() const;
	int set_id(const unsigned int id);
	unsigned int get_id() const;
//implement
private:
	BOOL is_valid() const;
//restriction
private:
	MtSocket(const MtSocket &);
	MtSocket &operator=(const MtSocket &);
//variables
private:
	MtLock *_lock;
	SOCKET _socket;
	WSAEVENT _event;
	unsigned int _id;
};