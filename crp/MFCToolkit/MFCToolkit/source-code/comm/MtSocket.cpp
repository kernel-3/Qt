#include"StdAfx.h"
#include"MtSocket.h"
#include"../tool/MtLock.h"
#include"../tool/MtAutoLock.h"
#include<assert.h>

/**
 * name: to_multibyte_text
 * brief: �����ֽ��ַ�ת��Ϊ���ֽ��ַ���
 * param: text - �ı���
 * return: ����ת����Ķ��ֽ��ַ���
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
 * brief: ���캯����
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
 * breif: ����������
 * param: --
 * return: --
 */
MtSocket::~MtSocket(void){
	release();
	delete _lock;
}

/**
 * name: release
 * brief: �ͷŵ�ǰ�׽��֡�
 * param: --
 * return: --
 */
void MtSocket::release(){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽����¼������ѱ�����������йرգ������жϹر��Ƿ�ɹ���
	if(WSA_INVALID_EVENT!=_event){
		const BOOL execute_result=WSACloseEvent(_event);
		assert(TRUE==execute_result);
		_event=WSA_INVALID_EVENT;
	}
	//3.�����ǰ�׽��ֶ����ѱ�����������йرգ������жϹر��Ƿ�ɹ���
	if(INVALID_SOCKET!=_socket){
		const int execute_result=closesocket(_socket);
		assert(0==execute_result);
		_socket=INVALID_SOCKET;
	}
}

/**
 * name: create
 * brief: ����һ���׽��֡�
 * param: network_events - �����¼���
 *        address_family - ��ַ�塣
 *        socket_type - �׽������͡�
 *        network_protocol - ����Э�顣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: address_family ȡ����ֵ
 *         ==========================================================================
 *         AF_UNSPEC - δָ����ַ�塣
 *         AF_INET - �������汾4Э�飨IPV4����ַ�塣
 *         AF_NETBIOS - The NetBIOS address family. This 
 *                      address family is only supported 
 *                      if a Windows Sockets provider for 
 *                      NetBIOS is installed.
 *         AF_INET6 - �������汾6Э�飨IPV6����ַ�塣
 *         AF_IRDA - The Infrared Data Association (IrDA) 
 *                   address family. This address family 
 *                   is only supported if the computer has 
 *                   an infrared port and driver installed.
 *         AF_BTM - The Bluetooth address family. This address 
 *                  family is only supported if a Bluetooth 
 *                  adapter is installed on Windows Server 2003 
 *                  or later.
 *         ==========================================================================
 *         socket_type ȡ����ֵ
 *		   ==========================================================================
 *         SOCK_STREAM - TCP/IP֧�ֵ��������͡�
 *         SOCK_DGRAM - UDP֧�ֵ��������͡�
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
 *         network_protocolȡ����ֵ
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
	//1.���ò�������һ���׽��֣������жϴ����Ƿ�ɹ���
	SOCKET temp_socket=socket(address_family,socket_type,network_protocol);
	if(INVALID_SOCKET==temp_socket){
		return(-1);
	}
	//2.Ϊ�׽��ִ���һ���¼��������󣬲����жϴ����Ƿ�ɹ���
	WSAEVENT temp_event=::WSACreateEvent();
	if(WSA_INVALID_EVENT==temp_event){
		const int execute_result=closesocket(temp_socket);
		assert(0==execute_result);
		return(-2);
	}
	//3.Ϊ�׽���ѡ������¼��������ж�ѡ���Ƿ�ɹ���
	if(SOCKET_ERROR==::WSAEventSelect(temp_socket,temp_event,network_events)){
		const int execute_result=closesocket(temp_socket);
		assert(0==execute_result);
		const BOOL execute_result_t=WSACloseEvent(temp_event);
		assert(TRUE==execute_result_t);
		return(-3);
	}
	//4.�ͷŵ�ǰ�׽��֡�
	release();
	//5.���õ�ǰ�׽��֡�
	MtAutoLock<MtLock> lock(_lock);
	_socket=temp_socket;
	_event=temp_event;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: attach
 * brief: ��ָ�����׽��ָ��ӵ���ǰ���С�
 * param: socket - ָ�����׽��֡�
 *        network_events - �����¼���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::attach(const SOCKET socket,const long network_events){
	//1.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(INVALID_SOCKET==socket){
		return(-1);
	}
	//2.Ϊ�׽��ִ��������¼��������жϴ����Ƿ�ɹ���
	WSAEVENT temp_event=WSACreateEvent();
	if(WSA_INVALID_EVENT==temp_event){
		return(-2);
	}
	//3.Ϊ�׽�����ѡ�¼��������ж���ѡ�Ƿ�ɹ���
	if(SOCKET_ERROR==WSAEventSelect(socket,temp_event,network_events)){
		const BOOL execute_result=WSACloseEvent(temp_event);
		assert(TRUE==execute_result);
		return(-3);
	}
	//4.�ͷŵ�ǰ�׽��֡�
	release();
	//5.���õ�ǰ�׽��֡�
	MtAutoLock<MtLock> lock(_lock);
	_socket=socket;
	_event=temp_event;
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: detach
 * brief: �����ӵ����е��׽���ȥ����
 * param: --
 * return: --
 */
void MtSocket::detach(){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽����¼������ѱ�����������йرգ������жϹر��Ƿ�ɹ���
	if(WSA_INVALID_EVENT!=_event){
		const BOOL execute_result=WSACloseEvent(_event);
		assert(TRUE==execute_result);
		_event=WSA_INVALID_EVENT;
	}
	//3.ȥ����ǰ���ӵ����е��׽��֡�
	if(INVALID_SOCKET!=_socket){
		_socket=INVALID_SOCKET;
	}
}

/**
 * name: bind
 * brief: Ϊ��ǰ�׽��ְ�����˿ڡ�IP��ַ�Լ���ַ�塣
 * param: network_port - ����˿ڡ�
 *        ip_address - IP��ַ��
 *        address_family - ��ַ�塣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::bind(const unsigned short network_port,
	const CString & /*ip_address *//*=_T("")*/,const int address_family/*=AF_INET*/){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽�����Ч����ֱ�ӷ��ش�����Ϣ��
	if(!is_valid()){
		return(-1);
	}
	//3.��������˿ڡ�IP��ַ����ַ��������Ϣ��
	sockaddr_in socket_ip_address;
	memset(&socket_ip_address,0,sizeof(socket_ip_address));
	socket_ip_address.sin_family=static_cast<short>(address_family);
	socket_ip_address.sin_port=htons(network_port);
#ifdef _UNICODE
	socket_ip_address.sin_addr.s_addr=inet_addr(to_multibyte_text(ip_address));
#else
	// socket_ip_address.sin_addr.s_addr=inet_addr(ip_address);
#endif
	//4.�����׽��ְ󶨲����������жϰ��Ƿ�ɹ���
	if(0!=::bind(_socket,reinterpret_cast<sockaddr*>(&socket_ip_address),
		sizeof(socket_ip_address))){
		return(-2);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: listen
 * brief: ���ǰ�׽�����������������ܡ�
 * param: listen_number - ָ��һ�μ�����������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::listen(const int listen_number/*=SOMAXCONN*/){
	//1.�����ǰ�������ݲ��Ϸ���
	if(listen_number<=0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ֲ��Ϸ���
	if(!is_valid()){
		return(-2);
	}
	//4.�����׽��ּ������ܣ������ж������Ƿ�ɹ���
	if(SOCKET_ERROR==::listen(_socket,listen_number)){
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: accept
 * brief: ����һ���׽��֡�
 * param: network_events - ���յ����׽��������¼���
 * return: �������ִ�гɹ�����ָ���׽��ֵ�����ָ�룬���򷵻�
 *         �յ�����ָ�롣
 */
MtSocket::PtrToSocket MtSocket::accept(const long network_events/*=FD_READ|FD_WRITE|FD_CLOSE*/){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ֲ��Ϸ�����ֱ�ӷ��ء�
	if(!is_valid()){
		return(PtrToSocket());
	}
	//3.����һ���׽��֣������жϽ����Ƿ�ɹ���
	//3-1.������ǰ�������������
	SOCKADDR_IN socket_address;
	memset(&socket_address,0,sizeof(socket_address));
	int socket_address_size=sizeof(socket_address);
	//3-2.���Խ���һ���׽��֡�
	SOCKET socket=::accept(_socket,(SOCKADDR*)&socket_address,&socket_address_size);
	//3-3.��������׽���ʧ�ܡ�
	if(INVALID_SOCKET==socket){
		return(PtrToSocket());
	}
	//4.���ӽ��յ��׽��ֵ�ָ���׽������У������жϲ����Ƿ�ɹ���
	PtrToSocket pointer_socket(new MtSocket);
	if(pointer_socket->attach(socket,network_events)<0){
		const int execute_result=closesocket(socket);
		assert(0==execute_result);
		return(PtrToSocket());
	}
	//5.�������е���ֱ�ӷ����׽�������ָ�롣
	return(pointer_socket);
}

/**
 * name: connect
 * brief: ����ǰ���׽������ӵ�ָ���ķ������ϡ�
 * param: network_port - �������˿ڡ�
 *        ip_address - ������IP��ַ��
 *        address_family - ��������ַ�塣
 *        timeout - ���ӳ�ʱ��
 * return: ������ӳɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::connect(const unsigned short network_port,const CString & /*ip_address*/,
  const int address_family/*=AF_INET*/,const unsigned int timeout/*=2000*/){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�жϵ�ǰ�׽����Ƿ�Ϸ���
	if(!is_valid()){
		return(-1);
	}
	//3.���÷������˿ڡ�IP��ַ����ַ�塣
	sockaddr_in socket_ip_address;
	memset(&socket_ip_address,0,sizeof(socket_ip_address));
	socket_ip_address.sin_family=static_cast<short>(address_family);
	socket_ip_address.sin_port=htons(network_port);
#ifdef _UNICODE
	socket_ip_address.sin_addr.s_addr=inet_addr(to_multibyte_text(ip_address));
#else
	// socket_ip_address.sin_addr.s_addr=inet_addr(ip_address);
#endif
	//4.�������ӷ�������
	::connect(_socket,reinterpret_cast<LPSOCKADDR>(&socket_ip_address),sizeof(SOCKADDR));
	//5.�������ӷ�������ʱʱ�ޣ��������ӷ��������ж������Ƿ�ɹ���
	timeval timeout_struct;
	timeout_struct.tv_sec=0;
	timeout_struct.tv_usec=timeout;
	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET(_socket,&socket_set);
	if(select(0,0,&socket_set,0,&timeout_struct)<=0){
		return(-4);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: enum_network_events
 * brief: ö�ٵ�ǰ�׽����ϵ������¼���
 * param: network_events - �����¼���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::enum_network_events(WSANETWORKEVENTS &network_events){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ֲ��Ϸ�����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//3.ö�ٵ�ǰ�׽����ϵ������¼���
	if(SOCKET_ERROR==WSAEnumNetworkEvents(_socket,_event,&network_events)){
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: block_close
 * brief: �������ԣ�ʹ���׽��ֹر�ʱ������ֱ���������ݷ�����ϡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::block_close(){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�жϵ�ǰ�׽����Ƿ���Ч��
	if(!is_valid()){
		return(-1);
	}
	//3.�����׽������ԣ�ʹ���׽��ֹر�ʱ������ֱ���������ݷ�����ϡ�
	BOOL value=FALSE;
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_DONTLINGER,
		reinterpret_cast<char*>(&value),sizeof(BOOL))){
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_socket_event
 * brief: ��ȡ��ǰ�׽��������¼�����
 * param: --
 * return: ���ص�ǰ�׽��������¼�����
 */
WSAEVENT MtSocket::get_socket_event() const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����׽��������¼�����
	return(_event);
}

/**
 * name: send
 * brief: ͨ����ǰ�׽��ַ������ݡ�
 * param: data - ָ�����ݻ�������
 *        size - ���ݻ������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::send(const unsigned char *data,const unsigned int size){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ֲ��Ϸ�����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-2);
	}
	//4.���͵�ǰ���ݣ������жϷ����Ƿ�ɹ���
	if(SOCKET_ERROR==::send(_socket,(char*)data,size,0)){
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: send
 * brief: ͨ����ǰ�׽��ַ������ݡ�
 * param: data - ָ�����ݻ�������
 *        size - ���ݻ������ߴ硣
 *        timeout - �������ݵĳ�ʱʱ�䣨��λ�����룩��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::send(const unsigned char *data,const unsigned int size,const unsigned int timeout){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ֲ��Ϸ�����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-2);
	}
	//4.���͵�ǰ���ݣ������жϷ����Ƿ�ɹ���
	if(SOCKET_ERROR==::send(_socket,(char*)data,size,0)){
		return(-3);
	}
	//5.�ȴ����ݷ�����ɣ������ж��Ƿ��ͳ�ʱ��
	//5-1.���ó�ʱ�ṹ�塣
	timeval timeout_struct;
	timeout_struct.tv_sec=0;
	timeout_struct.tv_usec=timeout;
	//5-2.�����׽��ּ���
	fd_set socket_set;
	FD_ZERO(&socket_set);
	FD_SET(_socket,&socket_set);
	//5-3.�ȴ����ͳɹ���ɡ�
	if(select(0,0,&socket_set,0,&timeout_struct)<=0){
		return(-4);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: receive
 * brief: �ӵ�ǰ�׽����н������ݡ�
 * param: data - ָ����ջ�������
 *        size - ���ջ������ߴ硣
 * return: �������ִ�гɹ�����ʵ�ʽ��յ����ݳߴ磬���򷵻�ֵС���㡣
 */
int MtSocket::receive(unsigned char *data,const unsigned int size){
	//1.�����ǰ���ݵĲ������Ϸ�����ֱ�ӷ��ش���
	if((0==data)||(0==size)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ַǷ���
	if(!is_valid()){
		return(-2);
	}
	//4.���׽����н������ݣ������жϽ����Ƿ�ɹ���
	//4-1.���׽����н������ݡ�
	const int received_size=recv(_socket,reinterpret_cast<char *>(data),
		static_cast<int>(size),0);
	//4-2.�������ʧ�ܡ�
	if(received_size<=0){
		return(-3);
	}
	//5.�������е��˳ɹ�����ʵ�ʽ��յ����ݳߴ硣
	return(received_size);
}

/**
 * name: set_send_buffer_size
 * brief: ���õ�ǰ�׽��ַ��ͻ������ߴ硣
 * param: size - ���ͻ������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::set_send_buffer_size(const int size){
	//1.�����ǰ���ݲ����Ƿ�����ֱ�ӷ��ش���
	if(size<=0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-2);
	}
	//4.���õ�ǰ�׽��ֻ������ߴ磬�����ж������Ƿ�ɹ���
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<
		const char *>(&size),sizeof(const int))){
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_send_buffer_size
 * brief: ��ȡ��ǰ�׽��ַ��ͻ������ߴ硣
 * param: --
 * return: �������ִ�гɹ����ص�ǰ�׽��ַ��ͻ������ߴ磬���򷵻�ֵС���㡣
 */
int MtSocket::get_send_buffer_size() const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//3.��ȡ��ǰ�׽��ַ��ͻ������ߴ硣
	//3-1.������ǰ�������������
	int size=0;
	int length=sizeof(int);
	//3-2.��ȡ��ǰ�׽��ַ��ͻ������ߴ磬�����жϻ�ȡ�Ƿ�ɹ���
	if(0!=getsockopt(_socket,SOL_SOCKET,SO_SNDBUF,reinterpret_cast<
		char *>(&size),&length)){
		return(-2);
	}
	//4.�������е��ˣ�ֱ�ӷ��ص�ǰ�׽��ַ��ͻ������ߴ硣
	return(size);
}

/**
 * name: set_receive_buffer_size
 * brief: ���õ�ǰ�׽��ֽ��ջ������ߴ硣
 * param: size - ���ջ������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtSocket::set_receive_buffer_size(const int size){
	//1.�����ǰ���ݲ����Ƿ�����ֱ�ӷ��ش���
	if(size<=0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-2);
	}
	//4.���õ�ǰ�׽��ֽ��ջ������ߴ磬�����ж������Ƿ�ɹ���
	if(0!=setsockopt(_socket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<
		const char *>(&size),sizeof(const int))){
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_receive_buffer_size
 * brief: ��ȡ��ǰ�׽��ֽ��ջ������ߴ硣
 * param: --
 * return: �������ִ�гɹ����ص�ǰ�׽��ֽ��ջ������ߴ磬���򷵻�ֵС���㡣
 */
int MtSocket::get_receive_buffer_size() const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//3.��ȡ��ǰ�׽��ֽ��ջ������ߴ硣
	//3-1.������ǰ�������������
	int size=0;
	int length=sizeof(int);
	//3-2.��ȡ��ǰ�׽��ֽ��ջ������ߴ磬�����жϻ�ȡ�Ƿ�ɹ���
	if(0!=getsockopt(_socket,SOL_SOCKET,SO_RCVBUF,reinterpret_cast<
		char *>(&size),&length)){
		return(-2);
	}
	//4.�������е��ˣ�ֱ�ӷ��ص�ǰ�׽��ֽ��ջ������ߴ硣
	return(size);
}

/**
 * name: get_data_size_in_receive_buffer
 * brief: ��ȡ���ջ����������ݵĳߴ硣
 * param: --
 * return: �������ִ�гɹ����ؽ��ջ����������ݵĳߴ磬���򷵻�ֵС���㡣
 */
int MtSocket::get_data_size_in_receive_buffer() const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ַǷ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//3.��ȡ��ǰ���ջ����������ݵĳߴ硣
	//3-1.������ǰ�������������
	unsigned long size=0;
	//3-2.��ȡ��ǰ���ջ����������ݵĳߴ磬�����жϻ�ȡ�Ƿ�ɹ���
	if(0!=ioctlsocket(_socket,FIONREAD,&size)){
		return(-2);
	}
	//4.�������е��ˣ�ֱ�ӷ��ؽ��ջ����������ݵĳߴ硣
	return(static_cast<int>(size));
}

/**
 * name: set_id
 * brief: �����׽���ID��
 * param: id - ��ǰ�׽���ID��š�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �趨���׽���IDΪ��ʱ��Ϊδ�趨ֵ��Ҳ����˵�׽���ID��
 *         �Ϸ���ΧΪ�����㡣
 */
int MtSocket::set_id(const unsigned int id){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ַǷ���
	if(!is_valid()){
		return(-1);
	}
	//3.���õ�ǰ�׽���ID��
	_id=id;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: get_id
 * brief: ��ȡ�׽���ID��
 * param: --
 * return: �������ִ�гɹ������׽���ID�����򷵻��㡣
 * remark: �趨���׽���IDΪ��ʱ��Ϊδ�趨ֵ��Ҳ����˵�׽���ID��
 *         �Ϸ���ΧΪ�����㡣
 */
unsigned int MtSocket::get_id() const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.�����ǰ�׽��ַǷ���
	if(!is_valid()){
		return(0);
	}
	//3.�����׽���ID��
	return(_id);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�׽����Ƿ�Ϸ���
 * param: --
 * return: ����׽��ֺϷ�����TRUE�����򷵻�FALSE�� 
 */
BOOL MtSocket::is_valid() const{
	return((INVALID_SOCKET!=_socket)&&(WSA_INVALID_EVENT!=_event));
}