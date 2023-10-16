#include"stdafx.h"
#include"MtNetPort.h"
#include"../tool/MtLock.h"
#include"MtSocket.h"
#include"../tool/MtAutoLock.h"
#include"MtSocketFinder.h"
#include<assert.h>
#include<algorithm>

/**
 * name: array_smart_pointer_deletor
 * brief: ��������ָ��ɾ�����������ṩ����������ָ���ͷŲ�����
 * param: pointer - ׼���ͷŵ�ָ�롣
 * return: --
 */
template<typename _Tp>
static void array_smart_pointer_deletor(_Tp *pointer){
	if(0!=pointer){
		delete[] pointer;
	}
}

/**
 * name: MtNetPort
 * brief: ���캯����
 * param: receive_callback - ָ���������ݽ��ջص�������
 *        receive_instance - ָ���������ݽ���ʵ������
 * return: --
 */
MtNetPort::MtNetPort(ReceiveCallback receive_callback,void *receive_instance)
	:_lock(new MtLock)
	,_port(0)
	,_ip(_T(""))
	,_sockets()
	,_monitoring(INVALID_HANDLE_VALUE)
	,_continue_monitoring_event(CreateEvent(0,FALSE,FALSE,0))
	,_is_monitoring(FALSE)
	,_receive_callback(receive_callback)
	,_receive_instance(receive_instance){
	assert(0!=_lock);
	assert((0!=_continue_monitoring_event)&&(
		INVALID_HANDLE_VALUE!=_continue_monitoring_event));
	WSADATA wsa_data;
	int execute_result=WSAStartup(MAKEWORD(2,2),&wsa_data);
	assert(0==execute_result);
}

/**
 * name: ~MtNetPort
 * brief: ����������
 * param: --
 * return: --
 */
MtNetPort::~MtNetPort(void){
	close();
	BOOL execute_result=CloseHandle(_continue_monitoring_event);
	assert(TRUE==execute_result);
	delete _lock;
	int execute_result_t=WSACleanup();
	assert(0==execute_result_t);
}

/**
 * name: close
 * brief: �رյ�ǰ���ڡ�
 * param: --
 * return: --
 * remark: �˺�����֧�ֶ��̡߳�
 */
void MtNetPort::close(){
	//1.�ر����ڼ�����
	close_monitoring();
	//2.��������׽��֡�
	clear_sockets();
	//3.�����ǰ����Ķ˿ں��Լ�IP��ַ��
	set_port(0);
	set_ip(_T(""));
}

/**
 * name: open_server
 * brief: �Է������ķ�ʽ�����ڡ�
 * param: port - �˿ںš�
 *		  ip - IP��ַ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �˺�����֧�ֶ��̡߳�
 */
int MtNetPort::open_server(const unsigned short port,const CString &ip){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((0==port)||(_T("")==ip)){
		return(-1);
	}
	//2.�رյ�ǰ���ڡ�
	close();
	//3.��ʼ���ڼ����̣߳������жϿ����Ƿ�ɹ���
	if(open_monitoring()<0){
		return(-2);
	}
	//4.�������ڼ����׽��֣������жϴ����Ƿ�ɹ���
	if(listen(port,ip)<0){
		close_monitoring();
		return(-3);
	}
	//5.���浱ǰ�Ķ˿ں��Լ�IP��ַ��
	set_port(port);
	set_ip(ip);
	//6.������������ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: open_client
 * brief: �Կͻ��˵ķ�ʽ�����ڡ�
 * param: port - �˿ںš�
 *		  ip - IP��ַ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �˺�����֧�ֶ��̡߳�
 */
int MtNetPort::open_client(const unsigned short port,const CString &ip){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((0==port)||(_T("")==ip)){
		return(-1);
	}
	//2.�رյ�ǰ���ڡ�
	close();
	//3.��ʼ���ڼ����̣߳������жϿ����Ƿ�ɹ���
	if(open_monitoring()<0){
		return(-2);
	}
	//4.�������������׽��֣������жϴ����Ƿ�ɹ���
	if(connect(port,ip)<0){
		close_monitoring();
		return(-3);
	}
	//5.���浱ǰ�Ķ˿ں��Լ�IP��ַ��
	set_port(port);
	set_ip(ip);
	//6.������������ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: send
 * brief: ����ָ���׽��ַ������ݡ�
 * param: socket_id - �׽���ID��
 *        data - ָ�����ݻ�������
 *        size - ���ݻ������ߴ硣
 *        timeout - �������ݳ�ʱʱ�ޣ�����ֵΪ��ʱ�������ó�ʱ���ͣ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: ���ô˺���ǰ��ȷ��open_server�Լ�open_client�����ѱ����óɹ���
 */
int MtNetPort::send(const unsigned int socket_id,const unsigned char *data,
	const unsigned int size,const unsigned int timeout/*=0*/){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((0==socket_id)||(0==data)||(0==size)){
		return(-1);
	}
	//2.��ȡ��ǰ�����������ݵ��׽��֡�
	PtrToSocket socket=get_socket(socket_id);
	//3.�����ȡ�׽���ʧ�ܡ�
	if(!static_cast<bool>(socket)){
		//3-1.�����ǰ�׽���ID����MAIN_SOCKET_ID��������������ӡ�
		if(MAIN_SOCKET_ID==socket_id){
			//3-1-1.��ȡ��ǰ�洢�Ķ˿��Լ�IP��
			const unsigned short port=get_port();
			const CString ip=get_ip();
			//3-1-2.����˿ڡ�IP���Ϸ���
			if((0==port)||(_T("")==ip)){
				return(-2);
			}
			//3-1-3.���������������ʧ�ܡ�
			if(connect(port,ip)<0){
				return(-3);
			}
			//3-1-4.��������������ӳɹ���
			else{
				//3-1-4-1.���Ի�ȡ�����������ݵ��׽��֡�
				socket=get_socket(socket_id);
				//3-1-4-2.�����ȡ�׽���ʧ�ܡ�
				if(!static_cast<bool>(socket)){
					return(-4);
				}
			}
		}
		//3-2.�����ǰ�׽���ID������MAIN_SOCKET_ID����ֱ�ӷ��ش���
		else{
			return(-5);
		}
	}
	//4.�����ȡ���׽��ֺϷ�,��������ݷ��͡�
	//4-1.�����ǰ���������ó�ʱ���͡�
	if(0==timeout){
		if(socket->send(data,size)<0){
			return(-6);
		}else{
			return(0);
		}
	}
	//4-2.�����ǰ�������ó�ʱ���͡�
	else{
		if(socket->send(data,size,timeout)<0){
			return(-7);
		}else{
			return(0);
		}
	}
}

/**
 * name: monitoring
 * brief: ���ڼ����߳�ʵ�ֺ�����������������¼������Ը����¼�������Ӧ��
 * param: parameter - ָ�򴫵ݸ��̵߳Ĳ�����
 * return: �˺���һֱ�����㡣
 */
unsigned int __stdcall MtNetPort::monitoring(void *parameter){
	MtNetPort *net_port=static_cast<MtNetPort *>(parameter);
	net_port->monitoring();
	return(0);
}

/**
 * name: listen
 * brief: �����׽��ּ������ܣ���������ͨѶ������
 * param: port - �˿ںš�
 *		  ip - IP��ַ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtNetPort::listen(const unsigned short port,const CString &ip){
	//1.���������׽��֣������жϴ����Ƿ�ɹ���
	PtrToSocket listen_socket(new MtSocket);
	if(!static_cast<bool>(listen_socket)){
		return(-1);
	}
	//2.���������׽��֣������жϴ����Ƿ�ɹ���
	if(listen_socket->create(FD_ACCEPT|FD_CLOSE)<0){
		return(-2);
	}
	//3.Ϊ�׽��ְ󶨶˿ڡ�IP��ַ��
	if(listen_socket->bind(port,ip)<0){
		return(-3);
	}
	//4.�����׽��ּ������ܡ�
	if(listen_socket->listen()<0){
		return(-4);
	}
	//5.�����׽���IDֵ��
	if(listen_socket->set_id(MAIN_SOCKET_ID)<0){
		return(-5);
	}
	//6.���׽�����ӵ������С�
	if(add_socket(listen_socket)<0){
		return(-6);
	}
	//7.�����¼���������߳����µȴ��׽����¼���
	BOOL execute_result=SetEvent(_continue_monitoring_event);
	assert(TRUE==execute_result);
	//8.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: connect
 * brief: �����׽������ӹ��ܣ���������ͨѶ������
 * param: port - �˿ںš�
 *		  ip - IP��ַ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtNetPort::connect(const unsigned short port,const CString &ip){
	//1.���������׽��֣������жϴ����Ƿ�ɹ���
	PtrToSocket connect_socket(new MtSocket);
	if(!static_cast<bool>(connect_socket)){
		return(-1);
	}
	//2.���������׽��֣������жϴ����Ƿ�ɹ���
	if(connect_socket->create(FD_READ|FD_WRITE|FD_CLOSE)<0){
		return(-2);
	}
	//3.���������׽��������رգ������ж������Ƿ�ɹ���
	if(connect_socket->block_close()<0){
		return(-3);
	}
	//4.�������ӣ������ж������Ƿ�ɹ���
	if(connect_socket->connect(port,ip)<0){
		return(-4);
	}
	//5.�����׽���IDֵ��
	if(connect_socket->set_id(MAIN_SOCKET_ID)<0){
		return(-5);
	}
	//6.���׽�����ӵ������С�
	if(add_socket(connect_socket)<0){
		return(-6);
	}
	//7.�����¼���������߳����µȴ��׽����¼���
	BOOL execute_result=SetEvent(_continue_monitoring_event);
	assert(TRUE==execute_result);
	//8.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_port
 * brief: ���ö˿ںš�
 * param: port - �˿ںš�
 * return: --
 */
void MtNetPort::set_port(const unsigned short port){
	MtAutoLock<MtLock> lock(_lock);
	_port=port;
}

/**
 * name: get_port
 * brief: ��ȡ�˿ںš�
 * param: --
 * return: ���ض˿ںš�
 */
unsigned short MtNetPort::get_port() const{
	MtAutoLock<MtLock> lock(_lock);
	return(_port);
}

/**
 * name: set_ip
 * brief: ����IP��
 * param: ip - IP��ַ��
 * return: --
 */
void MtNetPort::set_ip(const CString &ip){
	MtAutoLock<MtLock> lock(_lock);
	_ip=ip;
}

/**
 * name: get_ip
 * brief: ��ȡIP��
 * param: --
 * return: ����IP��
 */
CString MtNetPort::get_ip() const{
	MtAutoLock<MtLock> lock(_lock);
	return(_ip);
}

/**
 * name: add_socket
 * brief: ����׽��֡�
 * param: socket - �׽��֡�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtNetPort::add_socket(PtrToSocket &socket){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((!static_cast<bool>(socket))||(0==socket->get_id())){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> lock(_lock);
	//3.�ж��뵱ǰ�׽���ID��ͬ���׽����Ƿ���ڡ�
	SocketVector::iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket->get_id()));
	//4.����׽����Ѿ����ڣ���ֱ�ӷ��ش��󣨱��������д洢�ظ����׽��֣���
	if(socket_iterator!=_sockets.end()){
		return(-2);
	}
	//5.����׽��ֲ����ڣ�����ӡ�
	else{
		_sockets.push_back(socket);
	}
	//6.�ɳ����е��˳ɹ����ء�
	return(0);
}

/**
 * name: erase_socket
 * brief: ɾ��ָ�����׽��֡�
 * param: socket_id - �׽���ID��
 * return: --
 */
void MtNetPort::erase_socket(const unsigned int socket_id){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.����ָ�����׽���ID�������׽��֡�
	SocketVector::const_iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.����׽��ִ��ڣ������ɾ��������
	if(_sockets.end()!=socket_iterator){
		_sockets.erase(socket_iterator);
	}
}

/**
 * name: clear_sockets
 * brief: ������д洢���׽��֡�
 * param: --
 * return: --
 */
void MtNetPort::clear_sockets(){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.������д洢���׽��֡�
	_sockets.clear();
	SocketVector().swap(_sockets);//ǿ�������ͷ��ڴ档
}

/**
 * name: does_socket_exist
 * brief: �ж�ָ�����׽����Ƿ���ڡ�
 * param: socket_id - �׽���ID��
 * return: ���ָ�����׽��ִ����򷵻�TRUE�����򷵻�FALSE��
 */
BOOL MtNetPort::does_socket_exist(const unsigned int socket_id) const{
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.����ָ�����׽���ID�������׽��֡�
	SocketVector::const_iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.������ܳɹ��ҵ�ָ���׽��֡�
	if(_sockets.end()==socket_iterator){
		return(FALSE);
	}
	//4.����ɹ��ҵ�ָ���׽��֡�
	else{
		return(TRUE);
	}
}

/**
 * name: wait_socket_events
 * brief: �ȴ������׽����¼���
 * param: --
 * return: ����ɹ��ȴ������ڼ��������¼����򷵻��㡣
 *         ����ɹ��ȴ��������׽����¼����򷵻��׽���ID��
 *         ����ȴ�ʧ�ܣ��򷵻�ֵС���㡣
 */
int MtNetPort::wait_socket_events(){
	//1.������ʱ�������͡�
	typedef std::shared_ptr<HANDLE> PtrToHandle;
	typedef std::shared_ptr<unsigned int> PtrToUint;
	//2.������ǰ�������������
	PtrToHandle socket_events;
	PtrToUint socket_ids;
	unsigned int socke_size=0;
	{
		//3.������
		MtAutoLock<MtLock> lock(_lock);
		//4.��ȡ��ǰ���б�����׽���������
		socke_size=_sockets.size()+1;
		//5.���������¼�������������Լ������׽���ID���飬�����ж��Ƿ�ɹ���
		socket_events.reset(new HANDLE[socke_size],
			array_smart_pointer_deletor<HANDLE>);
		socket_ids.reset(new unsigned int[socke_size],
			array_smart_pointer_deletor<unsigned int>);
		//6.������鴴��ʧ�ܣ���ֱ�ӷ��ء�
		if((!static_cast<bool>(socket_events))||
			(!static_cast<bool>(socket_ids))){
			return(-1);
		}
		//7.Ϊ���鸳ֵ��
		(socket_events.get())[0]=_continue_monitoring_event;
		(socket_ids.get())[0]=0;//���׽����¼�Ϊ��������ʱ�����Ӧ���׽���IDΪ�㣨������ֵ����
		for(unsigned int index=1;index!=socke_size;++index){
			const PtrToSocket &socket=_sockets[index-1];
			if((!static_cast<bool>(socket))||(0==socket->get_id())){
				return(-2);
			}else{
				(socket_events.get())[index]=socket->get_socket_event();
				(socket_ids.get())[index]=socket->get_id();
			}
		}
	}
	//8.�ȴ������¼������Ҽ�¼�ĸ��¼�������
	const DWORD socket_index=WSAWaitForMultipleEvents(
		socke_size,socket_events.get(),FALSE,WSA_INFINITE,FALSE);
	//9.����ȴ�ʧ�ܣ���ֱ�ӷ��ش���
	if(socket_index>=socke_size){
		return(-3);
	}
	//10.����ȴ��ɹ��������׽���ID��
	return((socket_ids.get())[socket_index]);
}

/**
 * name: get_socket
 * brief: �����׽���ID��ȡָ�����׽��֡�
 * param: socket_id - �׽���ID��
 * return: �������ִ�гɹ�����ָ���׽��ֵ�����ָ�룬���򷵻ؿյ�����ָ�롣
 */
MtNetPort::PtrToSocket MtNetPort::get_socket(const unsigned int socket_id){
	//1.������
	MtAutoLock<MtLock> lock(_lock);
	//2.����ָ�����׽���ID�������׽��֡�
	SocketVector::iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.������ܳɹ��ҵ�ָ���׽��֣�ֱ�ӷ��ؿյ��׽�������ָ�롣
	if(_sockets.end()==socket_iterator){
		return(PtrToSocket());
	}
	//4.����ɹ��ҵ�ָ���׽��֡�
	else{
		//4-1.�����ǰ�ҵ����׽��ֲ��Ϸ���������׽��֣������ء�
		if((!static_cast<bool>(*socket_iterator))||
			(0==(*socket_iterator)->get_id())){
			_sockets.erase(socket_iterator);//�������ϵ��׽��֡�
			return(PtrToSocket());
		}
		//4-2.�����ǰ�ҵ����׽��ֺϷ���
		else{
			return(*socket_iterator);
		}
	}
}

/**
 * name: monitoring
 * brief: ������������¼������Ը����¼�������Ӧ��
 * param: --
 * return: --
 */
void MtNetPort::monitoring(){
	while(TRUE){
		//1.���������¼������Ҽ�¼���������
		const int socket_id=wait_socket_events();
		//2.������������¼�ʧ�ܡ�
		if(socket_id<0){
			//2-1.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//2-2.�����´�ѭ����
			continue;
		}
		//3.�����ǰ���������¼�Ϊ���ڼ��������¼���
		else if(0==socket_id){
			//3-1.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//3-2.�����´�ѭ����
			continue;
		}
		//4.�����ǰ���������¼�Ϊ�����¼���
		else{
			//4-1.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-2.���ݵ�ǰ�׽���ID����ȡ�׽��֡�
			PtrToSocket socket=get_socket(socket_id);
			//4-3.�����ȡ�׽���ʧ�ܡ�
			if(!static_cast<bool>(socket)){
				//4-3-1.�����ǰϣ����ֹ���ڼ�����
				if(!_is_monitoring){
					return;
				}
				//4-3-2.�����´�ѭ����
				continue;
			}
			/*
			//4-4.�����ȡ��ǰ���׽��ֲ��Ϸ���
			if(0==socket->get_id()){
				//4-4-1.������ǰ�׽��֡�
				erase_socket(socket_id);
				//4-4-2.�����ǰϣ����ֹ���ڼ�����
				if(!_is_monitoring){
					return;
				}
				//4-4-3.�����´�ѭ����
				continue;
			}
			*/
			//4-5.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-6.��ȡ��ǰ�׽����Ϸ������¼��������жϻ�ȡ�Ƿ�ɹ���
			WSANETWORKEVENTS socket_events;
			memset(&socket_events,0,sizeof(WSANETWORKEVENTS));
			if(socket->enum_network_events(socket_events)<0){
				//4-6-1.�����ǰϣ����ֹ���ڼ�����
				if(!_is_monitoring){
					return;
				}
				//4-6-2.�����´�ѭ����
				continue;
			}
			//4-7.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-8.�����ǰ�׽����¼�Ϊ�����ܡ��¼���
			if((socket_events.lNetworkEvents&FD_ACCEPT)&&
				(0==socket_events.iErrorCode[FD_ACCEPT_BIT])){
				//4-8-1.����һ���µ��׽��ֵ����ӡ�
				PtrToSocket new_socket=socket->accept();
				//4-8-2.������ܳɹ���
				if(static_cast<bool>(new_socket)){
					//4-8-2-1.����������׽��������رճɹ���
					if(new_socket->block_close()>=0){
						add_socket(new_socket);
					}
					//4-8-2-2.����������׽��������ر�ʧ�ܡ�
					else{
					}
				}
				//4-8-3.�������ʧ�ܡ�
				else{
				}
			}//accept
			//4-9.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-10.�����ǰ�׽����¼�Ϊ�������¼���
			if((socket_events.lNetworkEvents&FD_READ)&&
				(0==socket_events.iErrorCode[FD_READ_BIT])){
				//4-10-1.��ȡ��ǰӦ�ý��յ����ݳߴ硣
				int data_size=socket->get_data_size_in_receive_buffer();
				//4-10-2.�����ǰ��ȡ��Ӧ�ý��յ����ݳߴ�Ϸ���
				if(data_size>0){
					//4-10-2-1.�����������͡�
					typedef std::shared_ptr<unsigned char> PtrToUChar;
					//4-10-2-2.�������ݽ��ջ������������жϴ����Ƿ�ɹ���
					PtrToUChar buffer(new unsigned char[data_size],
						array_smart_pointer_deletor<unsigned char>);
					//4-10-2-3.������ݽ��ջ����������ɹ���
					if(static_cast<bool>(buffer)){
						//4-10-2-3-1.�������ݣ����Ҽ�¼ʵ�ʽ������ݳߴ硣
						data_size=socket->receive(buffer.get(),data_size);
						//4-10-2-3-2.����ɹ��������ݡ�
						if(data_size>0){
							if(0!=_receive_callback){
								for(int index=0;index!=data_size;++index){
									_receive_callback(socket_id,(buffer.get())[index],_receive_instance);
								}
							}else{
							}
						}
						//4-10-2-3-3.�����������ʧ�ܡ�
						else{
						}
					}
					//4-10-2-4.������ݽ��ջ���������ʧ�ܡ�
					else{
					}
				}
				//4-10-3.�����ǰ��ȡ��Ӧ�ý��յ����ݳߴ粻�Ϸ���
				else{
				}
			}//read
			//4-11.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-12.�����ǰ�����¼�Ϊд�¼���
			if((socket_events.lNetworkEvents&FD_WRITE)&&
				(0==socket_events.iErrorCode[FD_WRITE_BIT])){
			}
			//4-13.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-14.�����ǰ�����¼�Ϊ�ر��¼���
			if((socket_events.lNetworkEvents&FD_CLOSE)&&
				(0==socket_events.iErrorCode[FD_CLOSE_BIT])){
				erase_socket(socket_id);
			}
			//4-15.�����ǰϣ����ֹ���ڼ�����
			if(!_is_monitoring){
				return;
			}
			//4-16.�����´�ѭ����
			continue;
		}//else
	}//while
}

/**
 * name: close_monitoring
 * brief: �ر����ڼ�����
 * param: --
 * return: --
 */
void MtNetPort::close_monitoring(){
	//1.�����ǰ���ڼ����̴߳��ڣ�������̳߳����ͷŲ�����
	if((0!=_monitoring)&&(INVALID_HANDLE_VALUE!=_monitoring)){
		//1-1.�����߳��˳���ǡ�
		_is_monitoring=FALSE;
		//1-2.�����̼߳������У�����߳��˳���ǡ�
		BOOL execute_result=SetEvent(_continue_monitoring_event);
		assert(TRUE==execute_result);
		//1-3.�ȴ����ڼ����߳��˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(_monitoring,THREAD_EXIT_TIMEOUT)){
			execute_result=TerminateThread(_monitoring,0);
			assert(TRUE==execute_result);
		}
		//1-4.�ر����ڼ����̡߳�
		execute_result=CloseHandle(_monitoring);
		assert(TRUE==execute_result);
	}
	//2.�ָ����ڼ����߳̾����
	_monitoring=INVALID_HANDLE_VALUE;
	//3.�ָ����ڼ����߳��˳���ǡ�
	_is_monitoring=FALSE;
	//4.�ָ����ڼ����̼߳����¼���
	// ... ...
}

/**
 * name: open_monitoring
 * brief: �����ڼ�����
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtNetPort::open_monitoring(){
	//1.������ڼ����߳��Ѿ���������ֱ�ӷ��ش���
	if((0!=_monitoring)&&(INVALID_HANDLE_VALUE!=_monitoring)){
		return(-1);
	}
	//2.��ʼ����ر�Ǳ�����
	_is_monitoring=TRUE;
	//3.�������ڼ����̣߳������жϿ����Ƿ�ɹ���
	_monitoring=reinterpret_cast<HANDLE>(
		_beginthreadex(0,0,monitoring,this,0,0));
	if((0==_monitoring)||(INVALID_HANDLE_VALUE==_monitoring)){
		_is_monitoring=FALSE;
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}