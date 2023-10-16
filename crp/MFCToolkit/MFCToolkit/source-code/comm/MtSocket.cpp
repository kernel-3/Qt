#include"StdAfx.h"
#include"MtSocket.h"
#include"../tool/MtLock.h"
#include"../tool/MtAutoLock.h"
#include<assert.h>

/**
 * name: to_multibyte_text
 * brief: 将宽字节字符转换为多字节字符。
 * param: text - 文本。
 * return: 返回转换后的多字节字符。
 */
static CStringA to_multibyte_text(const CStringW &text){
	const CStringA origin_local=setlocale(LC_ALL,NULL);
	setlocale(LC_ALL,"chs");
	const wchar_t *origin_text=text;
	const unsigned int text_size=text.GetLength()*sizeof(wchar_t)+1;
	char *multibyte_text_buffer=new char[text_size];
	memset(multibyte_text_buffer,0,text_size);
	unsigned int multibyte_text_size=0;
	wcstombs_s(&multibyte_text_size,multibyte_text_buffer,text_size,origin_text,text_size);
	const CStringA multibyte_text=multibyte_text_buffer;
	delete[] multibyte_text_buffer;
	setlocale(LC_ALL,origin_local);
	return(multibyte_text);
}

/**
 * name: MtSocket
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtSocket::MtSocket(void)
	:_lock(new MtLock)
	,_socket(INVALID_SOCKET)
	,_event(WSA_INVALID_EVENT)
	,_id(0){
}

/**
 * name: MtSocket
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtSocket::~MtSocket(void){
	release();
	delete _lock;
}

/**
 * name: release
 * brief: 释放当前套接字。
 * param: --
 * return: --
 */
void MtSocket::release(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字事件对象已被创建，则进行关闭，并且判断关闭是否成功。
	if(WSA_INVALID_EVENT!=_event){
		const BOOL execute_result=WSACloseEvent(_event);
		assert(TRUE==execute_result);
		_event=WSA_INVALID_EVENT;
	}
	//3.如果当前套接字对象已被创建，则进行关闭，并且判断关闭是否成功。
	if(INVALID_SOCKET!=_socket){
		const int execute_result=closesocket(_socket);
		assert(0==execute_result);
		_socket=INVALID_SOCKET;
	}
}

/**
 * name: create
 * brief: 创建一个套接字。
 * param: network_events - 网络事件。
 *        address_family - 地址族。
 *        socket_type - 套接字类型。
 *        network_protocol - 网络协议。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: address_family 取如下值
 *         ==========================================================================
 *         AF_UNSPEC - 未指定地址族。
 *         AF_INET - 因特网版本4协议（IPV4）地址族。
 *         AF_NETBIOS - The NetBIOS address family. This 
 *                      address family is only supported 
 *                      if a Windows Sockets provider for 
 *                      NetBIOS is installed.
 *         AF_INET6 - 因特网版本6协议（IPV6）地址族。
 *         AF_IRDA - The Infrared Data Association (IrDA) 
 *                   address family. This address family 
 *                   is only supported if the computer has 
 *                   an infrared port and driver installed.
 *         AF_BTM - The Bluetooth address family. This address 
 *                  family is only supported if a Bluetooth 
 *                  adapter is installed on Windows Server 2003 
 *                  or later.
 *         ==========================================================================
 *         socket_type 取如下值
 *		   ==========================================================================
 *         SOCK_STREAM - TCP/IP支持的数据类型。
 *         SOCK_DGRAM - UDP支持的数据类型。
 *         SOCK_RAW - Provides a raw socket that allows an application 
 *                    to manipulate the next upper-layer protocol header. 
 *                    To manipulate the IPv4 header, the IP_HDRINCL socket 
 *                    option must be set on the socket. To manipulate the 
 *                    IPv6 header, the IPV6_HDRINCL socket option must be 
 *                    set on the socket. 
 *         SOCK_RDM - Provides a reliable message datagram. An example of this 
 *                    type is the Pragmatic General Multicast (PGM) multicast 
 *                    protocol implementation in Windows, often referred to as 
 *                    reliable multicast programming. 
 *         SOCK_SEQPACKET - Provides a pseudo-stream packet based on datagrams. 
 *         ==========================================================================
 *         network_protocol取如下值
 *         ==========================================================================
 *         IPPROTO_TCP - The Transmission Control Protocol (TCP). This is a possible 
 *                       value when the af parameter is AF_INET or AF_INET6 and the 
 *                       type parameter is SOCK_STREAM. 
 *         IPPROTO_UDP - The User Datagram Protocol (UDP). This is a possible value 
 *                       when the af parameter is AF_INET or AF_INET6 and the type 
 *                       parameter is SOCK_DGRAM. 
 *         IPPROTO_RM - The PGM protocol for reliable multicast. This is a possible 
 *                      value when the af parameter is AF_INET and the type parameter
 *                      is SOCK_RDM. On the Windows SDK released for Windows Vista and 
 *                      later, this value is also called IPPROTO_PGM.
 *         ==========================================================================
 */
int MtSocket::create(const long network_events,const int address_family/*=AF_INET*/,
				   const int socket_type/*=SOCK_STREAM*/,const int network_protocol/*=IPPROTO_IP*/){
	//1.利用参数创建一个套接字，并且判断创建是否成功。
	SOCKET temp_socket=socket(address_family,socket_type,network_protocol);
	if(INVALID_SOCKET==temp_socket){
		return(-1);
	}
	//2.为套接字创建一个事件监听对象，并且判断创建是否成功。
	WSAEVENT temp_event=::WSACreateEvent();
	if(WSA_INVALID_EVENT==temp_event){
		const int execute_result=closesocket(temp_socket);
		assert(0==execute_result);
		return(-2);
	}
	//3.为套接字选配监听事件，并且判断选配是否成功。
	if(SOCKET_ERROR==::WSAEventSelect(temp_socket,temp_event,network_events)){
		const int execute_result=closesocket(temp_socket);
		assert(0==execute_result);
		const BOOL execute_result_t=WSACloseEvent(temp_event);
		assert(TRUE==execute_result_t);
		return(-3);
	}
	//4.释放当前套接字。
	release();
	//5.重置当前套接字。
	MtAutoLock<MtLock> lock(_lock);
	_socket=temp_socket;
	_event=temp_event;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: attach
 * brief: 将指定的套接字附加到当前类中。
 * param: socket - 指定的套接字。
 *        network_events - 监听事件。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::attach(const SOCKET socket,const long network_events){
	//1.如果当前套接字非法，直接返回错误。
	if(INVALID_SOCKET==socket){
		return(-1);
	}
	//2.为套接字创建监听事件，并且判断创建是否成功。
	WSAEVENT temp_event=WSACreateEvent();
	if(WSA_INVALID_EVENT==temp_event){
		return(-2);
	}
	//3.为套接字配选事件，并且判断配选是否成功。
	if(SOCKET_ERROR==WSAEventSelect(socket,temp_event,network_events)){
		const BOOL execute_result=WSACloseEvent(temp_event);
		assert(TRUE==execute_result);
		return(-3);
	}
	//4.释放当前套接字。
	release();
	//5.重置当前套接字。
	MtAutoLock<MtLock> lock(_lock);
	_socket=socket;
	_event=temp_event;
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: detach
 * brief: 将附加到类中的套接字去除。
 * param: --
 * return: --
 */
void MtSocket::detach(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字事件对象已被创建，则进行关闭，并且判断关闭是否成功。
	if(WSA_INVALID_EVENT!=_event){
		const BOOL execute_result=WSACloseEvent(_event);
		assert(TRUE==execute_result);
		_event=WSA_INVALID_EVENT;
	}
	//3.去除当前附加到类中的套接字。
	if(INVALID_SOCKET!=_socket){
		_socket=INVALID_SOCKET;
	}
}

/**
 * name: bind
 * brief: 为当前套接字绑定网络端口、IP地址以及地址族。
 * param: network_port - 网络端口。
 *        ip_address - IP地址。
 *        address_family - 地址族。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::bind(const unsigned short network_port,
	const CString & /*ip_address *//*=_T("")*/,const int address_family/*=AF_INET*/){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字无效，则直接返回错误信息。
	if(!is_valid()){
		return(-1);
	}
	//3.设置网络端口、IP地址、地址族等相关信息。
	sockaddr_in socket_ip_address;
	memset(&socket_ip_address,0,sizeof(socket_ip_address));
	socket_ip_address.sin_family=static_cast<short>(address_family);
	socket_ip_address.sin_port=htons(network_port);
#ifdef _UNICODE
	socket_ip_address.sin_addr.s_addr=inet_addr(to_multibyte_text(ip_address));
#else
	// socket_ip_address.sin_addr.s_addr=inet_addr(ip_address);
#endif
	//4.进行套接字绑定操作，并且判断绑定是否成功。
	if(0!=::bind(_socket,reinterpret_cast<sockaddr*>(&socket_ip_address),
		sizeof(socket_ip_address))){
		return(-2);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: listen
 * brief: 命令当前套接字启动网络监听功能。
 * param: listen_number - 指定一次监听的数量。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::listen(const int listen_number/*=SOMAXCONN*/){
	//1.如果当前参数传递不合法。
	if(listen_number<=0){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字不合法。
	if(!is_valid()){
		return(-2);
	}
	//4.启动套接字监听功能，并且判断启动是否成功。
	if(SOCKET_ERROR==::listen(_socket,listen_number)){
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: accept
 * brief: 接收一个套接字。
 * param: network_events - 接收到的套接字网络事件。
 * return: 如果函数执行成功返回指向套接字的智能指针，否则返回
 *         空的智能指针。
 */
MtSocket::PtrToSocket MtSocket::accept(const long network_events/*=FD_READ|FD_WRITE|FD_CLOSE*/){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字不合法，则直接返回。
	if(!is_valid()){
		return(PtrToSocket());
	}
	//3.接收一个套接字，并且判断接收是否成功。
	//3-1.声明当前操作所需变量。
	SOCKADDR_IN socket_address;
	memset(&socket_address,0,sizeof(socket_address));
	int socket_address_size=sizeof(socket_address);
	//3-2.尝试接收一个套接字。
	SOCKET socket=::accept(_socket,(SOCKADDR*)&socket_address,&socket_address_size);
	//3-3.如果接收套接字失败。
	if(INVALID_SOCKET==socket){
		return(PtrToSocket());
	}
	//4.附加接收的套接字到指定套接字类中，并且判断操作是否成功。
	PtrToSocket pointer_socket(new MtSocket);
	if(pointer_socket->attach(socket,network_events)<0){
		const int execute_result=closesocket(socket);
		assert(0==execute_result);
		return(PtrToSocket());
	}
	//5.程序运行到此直接返回套接字智能指针。
	return(pointer_socket);
}

/**
 * name: connect
 * brief: 将当前的套接字连接到指定的服务器上。
 * param: network_port - 服务器端口。
 *        ip_address - 服务器IP地址。
 *        address_family - 服务器地址族。
 *        timeout - 连接超时。
 * return: 如果连接成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::connect(const unsigned short network_port,const CString & /*ip_address*/,
  const int address_family/*=AF_INET*/,const unsigned int timeout/*=2000*/){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.判断当前套接字是否合法。
	if(!is_valid()){
		return(-1);
	}
	//3.设置服务器端口、IP地址、地址族。
	sockaddr_in socket_ip_address;
	memset(&socket_ip_address,0,sizeof(socket_ip_address));
	socket_ip_address.sin_family=static_cast<short>(address_family);
	socket_ip_address.sin_port=htons(network_port);
#ifdef _UNICODE
	socket_ip_address.sin_addr.s_addr=inet_addr(to_multibyte_text(ip_address));
#else
	// socket_ip_address.sin_addr.s_addr=inet_addr(ip_address);
#endif
	//4.尝试连接服务器。
	::connect(_socket,reinterpret_cast<LPSOCKADDR>(&socket_ip_address),sizeof(SOCKADDR));
	//5.设置连接服务器超时时限，并且连接服务器，判断连接是否成功。
	timeval timeout_struct;
	timeout_struct.tv_sec=0;
	timeout_struct.tv_usec=timeout;
	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET(_socket,&socket_set);
	if(select(0,0,&socket_set,0,&timeout_struct)<=0){
		return(-4);
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: enum_network_events
 * brief: 枚举当前套接字上的网络事件。
 * param: network_events - 网络事件。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::enum_network_events(WSANETWORKEVENTS &network_events){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字不合法，则直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//3.枚举当前套接字上的网络事件。
	if(SOCKET_ERROR==WSAEnumNetworkEvents(_socket,_event,&network_events)){
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: block_close
 * brief: 设置属性，使得套接字关闭时阻塞，直到所有数据发送完毕。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::block_close(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.判断当前套接字是否有效。
	if(!is_valid()){
		return(-1);
	}
	//3.设置套接字属性，使得套接字关闭时阻塞，直到所有数据发送完毕。
	BOOL value=FALSE;
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_DONTLINGER,
		reinterpret_cast<char*>(&value),sizeof(BOOL))){
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_socket_event
 * brief: 获取当前套接字网络事件对象。
 * param: --
 * return: 返回当前套接字网络事件对象。
 */
WSAEVENT MtSocket::get_socket_event() const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.返回套接字网络事件对象。
	return(_event);
}

/**
 * name: send
 * brief: 通过当前套接字发送数据。
 * param: data - 指向数据缓冲区。
 *        size - 数据缓冲区尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::send(const unsigned char *data,const unsigned int size){
	//1.如果当前传递的参数不合法，则直接返回错误。
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字不合法，则直接返回错误。
	if(!is_valid()){
		return(-2);
	}
	//4.发送当前数据，并且判断发送是否成功。
	if(SOCKET_ERROR==::send(_socket,(char*)data,size,0)){
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: send
 * brief: 通过当前套接字发送数据。
 * param: data - 指向数据缓冲区。
 *        size - 数据缓冲区尺寸。
 *        timeout - 发送数据的超时时间（单位：毫秒）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::send(const unsigned char *data,const unsigned int size,const unsigned int timeout){
	//1.如果当前传递的参数不合法，则直接返回错误。
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字不合法，则直接返回错误。
	if(!is_valid()){
		return(-2);
	}
	//4.发送当前数据，并且判断发送是否成功。
	if(SOCKET_ERROR==::send(_socket,(char*)data,size,0)){
		return(-3);
	}
	//5.等待数据发送完成，并且判断是否发送超时。
	//5-1.设置超时结构体。
	timeval timeout_struct;
	timeout_struct.tv_sec=0;
	timeout_struct.tv_usec=timeout;
	//5-2.设置套接字集。
	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET(_socket,&socket_set);
	//5-3.等待发送成功完成。
	if(select(0,0,&socket_set,0,&timeout_struct)<=0){
		return(-4);
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: receive
 * brief: 从当前套接字中接收数据。
 * param: data - 指向接收缓冲区。
 *        size - 接收缓冲区尺寸。
 * return: 如果函数执行成功返回实际接收的数据尺寸，否则返回值小于零。
 */
int MtSocket::receive(unsigned char *data,const unsigned int size){
	//1.如果当前传递的参数不合法，则直接返回错误。
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字非法。
	if(!is_valid()){
		return(-2);
	}
	//4.从套接字中接收数据，并且判断接收是否成功。
	//4-1.从套接字中接收数据。
	const int received_size=recv(_socket,reinterpret_cast<char *>(data),
		static_cast<int>(size),0);
	//4-2.如果接收失败。
	if(received_size<=0){
		return(-3);
	}
	//5.程序运行到此成功返回实际接收的数据尺寸。
	return(received_size);
}

/**
 * name: set_send_buffer_size
 * brief: 设置当前套接字发送缓冲区尺寸。
 * param: size - 发送缓冲区尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::set_send_buffer_size(const int size){
	//1.如果当前传递参数非法，则直接返回错误。
	if(size<=0){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字非法，直接返回错误。
	if(!is_valid()){
		return(-2);
	}
	//4.设置当前套接字缓冲区尺寸，并且判断设置是否成功。
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<
		const char *>(&size),sizeof(const int))){
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_send_buffer_size
 * brief: 获取当前套接字发送缓冲区尺寸。
 * param: --
 * return: 如果函数执行成功返回当前套接字发送缓冲区尺寸，否则返回值小于零。
 */
int MtSocket::get_send_buffer_size() const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字非法，直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//3.获取当前套接字发送缓冲区尺寸。
	//3-1.声明当前操作所需变量。
	int size=0;
	int length=sizeof(int);
	//3-2.获取当前套接字发送缓冲区尺寸，并且判断获取是否成功。
	if(0!=getsockopt(_socket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<
		char *>(&size),&length)){
		return(-2);
	}
	//4.程序运行到此，直接返回当前套接字发送缓冲区尺寸。
	return(size);
}

/**
 * name: set_receive_buffer_size
 * brief: 设置当前套接字接收缓冲区尺寸。
 * param: size - 接收缓冲区尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtSocket::set_receive_buffer_size(const int size){
	//1.如果当前传递参数非法，则直接返回错误。
	if(size<=0){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.如果当前套接字非法，直接返回错误。
	if(!is_valid()){
		return(-2);
	}
	//4.设置当前套接字接收缓冲区尺寸，并且判断设置是否成功。
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<
		const char *>(&size),sizeof(const int))){
		return(-3);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_receive_buffer_size
 * brief: 获取当前套接字接收缓冲区尺寸。
 * param: --
 * return: 如果函数执行成功返回当前套接字接收缓冲区尺寸，否则返回值小于零。
 */
int MtSocket::get_receive_buffer_size() const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字非法，直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//3.获取当前套接字接收缓冲区尺寸。
	//3-1.声明当前操作所需变量。
	int size=0;
	int length=sizeof(int);
	//3-2.获取当前套接字接收缓冲区尺寸，并且判断获取是否成功。
	if(0!=getsockopt(_socket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<
		char *>(&size),&length)){
		return(-2);
	}
	//4.程序运行到此，直接返回当前套接字接收缓冲区尺寸。
	return(size);
}

/**
 * name: get_data_size_in_receive_buffer
 * brief: 获取接收缓冲区中数据的尺寸。
 * param: --
 * return: 如果函数执行成功返回接收缓冲区中数据的尺寸，否则返回值小于零。
 */
int MtSocket::get_data_size_in_receive_buffer() const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字非法，直接返回错误。
	if(!is_valid()){
		return(-1);
	}
	//3.获取当前接收缓冲区中数据的尺寸。
	//3-1.声明当前操作所需变量。
	unsigned long size=0;
	//3-2.获取当前接收缓冲区中数据的尺寸，并且判断获取是否成功。
	if(0!=ioctlsocket(_socket,FIONREAD,&size)){
		return(-2);
	}
	//4.程序运行到此，直接返回接收缓冲区中数据的尺寸。
	return(static_cast<int>(size));
}

/**
 * name: set_id
 * brief: 设置套接字ID。
 * param: id - 当前套接字ID编号。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 设定当套接字ID为零时，为未设定值，也就是说套接字ID的
 *         合法范围为大于零。
 */
int MtSocket::set_id(const unsigned int id){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字非法。
	if(!is_valid()){
		return(-1);
	}
	//3.设置当前套接字ID。
	_id=id;
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: get_id
 * brief: 获取套接字ID。
 * param: --
 * return: 如果函数执行成功返回套接字ID，否则返回零。
 * remark: 设定当套接字ID为零时，为未设定值，也就是说套接字ID的
 *         合法范围为大于零。
 */
unsigned int MtSocket::get_id() const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.如果当前套接字非法。
	if(!is_valid()){
		return(0);
	}
	//3.返回套接字ID。
	return(_id);
}

/**
 * name: is_valid
 * brief: 判断当前套接字是否合法。
 * param: --
 * return: 如果套接字合法返回TRUE、否则返回FALSE。 
 */
BOOL MtSocket::is_valid() const{
	return((INVALID_SOCKET!=_socket)&&(WSA_INVALID_EVENT!=_event));
}