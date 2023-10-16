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
 * brief: 数组智能指针删除器，负责提供数组型智能指针释放操作。
 * param: pointer - 准备释放的指针。
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
 * brief: 构造函数。
 * param: receive_callback - 指向网口数据接收回调函数。
 *        receive_instance - 指向网口数据接收实例对象。
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
 * brief: 析构函数。
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
 * brief: 关闭当前网口。
 * param: --
 * return: --
 * remark: 此函数不支持多线程。
 */
void MtNetPort::close(){
	//1.关闭网口监听。
	close_monitoring();
	//2.清空类中套接字。
	clear_sockets();
	//3.清除当前保存的端口号以及IP地址。
	set_port(0);
	set_ip(_T(""));
}

/**
 * name: open_server
 * brief: 以服务器的方式打开网口。
 * param: port - 端口号。
 *		  ip - IP地址。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 此函数不支持多线程。
 */
int MtNetPort::open_server(const unsigned short port,const CString &ip){
	//1.判断当前传递参数是否合法。
	if((0==port)||(_T("")==ip)){
		return(-1);
	}
	//2.关闭当前网口。
	close();
	//3.开始网口监听线程，并且判断开启是否成功。
	if(open_monitoring()<0){
		return(-2);
	}
	//4.创建网口监听套接字，并且判断创建是否成功。
	if(listen(port,ip)<0){
		close_monitoring();
		return(-3);
	}
	//5.保存当前的端口号以及IP地址。
	set_port(port);
	set_ip(ip);
	//6.程序运行至此直接成功返回。
	return(0);
}

/**
 * name: open_client
 * brief: 以客户端的方式打开网口。
 * param: port - 端口号。
 *		  ip - IP地址。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 此函数不支持多线程。
 */
int MtNetPort::open_client(const unsigned short port,const CString &ip){
	//1.判断当前传递参数是否合法。
	if((0==port)||(_T("")==ip)){
		return(-1);
	}
	//2.关闭当前网口。
	close();
	//3.开始网口监听线程，并且判断开启是否成功。
	if(open_monitoring()<0){
		return(-2);
	}
	//4.创建网口连接套接字，并且判断创建是否成功。
	if(connect(port,ip)<0){
		close_monitoring();
		return(-3);
	}
	//5.保存当前的端口号以及IP地址。
	set_port(port);
	set_ip(ip);
	//6.程序运行至此直接成功返回。
	return(0);
}

/**
 * name: send
 * brief: 命令指定套接字发送数据。
 * param: socket_id - 套接字ID。
 *        data - 指向数据缓冲区。
 *        size - 数据缓冲区尺寸。
 *        timeout - 发送数据超时时限（当此值为零时，不采用超时发送）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 调用此函数前请确保open_server以及open_client函数已被调用成功。
 */
int MtNetPort::send(const unsigned int socket_id,const unsigned char *data,
	const unsigned int size,const unsigned int timeout/*=0*/){
	//1.判断当前传递参数是否合法。
	if((0==socket_id)||(0==data)||(0==size)){
		return(-1);
	}
	//2.获取当前用来发送数据的套接字。
	PtrToSocket socket=get_socket(socket_id);
	//3.如果获取套接字失败。
	if(!static_cast<bool>(socket)){
		//3-1.如果当前套接字ID等于MAIN_SOCKET_ID，则进行重新连接。
		if(MAIN_SOCKET_ID==socket_id){
			//3-1-1.获取当前存储的端口以及IP。
			const unsigned short port=get_port();
			const CString ip=get_ip();
			//3-1-2.如果端口、IP不合法。
			if((0==port)||(_T("")==ip)){
				return(-2);
			}
			//3-1-3.如果重新启动连接失败。
			if(connect(port,ip)<0){
				return(-3);
			}
			//3-1-4.如果重新启动连接成功。
			else{
				//3-1-4-1.尝试获取用来发送数据的套接字。
				socket=get_socket(socket_id);
				//3-1-4-2.如果获取套接字失败。
				if(!static_cast<bool>(socket)){
					return(-4);
				}
			}
		}
		//3-2.如果当前套接字ID不等于MAIN_SOCKET_ID，则直接返回错误。
		else{
			return(-5);
		}
	}
	//4.如果获取的套接字合法,则进行数据发送。
	//4-1.如果当前不期望采用超时发送。
	if(0==timeout){
		if(socket->send(data,size)<0){
			return(-6);
		}else{
			return(0);
		}
	}
	//4-2.如果当前期望采用超时发送。
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
 * brief: 网口监听线程实现函数，负责监听网口事件，并对各个事件进行响应。
 * param: parameter - 指向传递给线程的参数。
 * return: 此函数一直返回零。
 */
unsigned int __stdcall MtNetPort::monitoring(void *parameter){
	MtNetPort *net_port=static_cast<MtNetPort *>(parameter);
	net_port->monitoring();
	return(0);
}

/**
 * name: listen
 * brief: 启动套接字监听功能，并建立其通讯环境。
 * param: port - 端口号。
 *		  ip - IP地址。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtNetPort::listen(const unsigned short port,const CString &ip){
	//1.创建监听套接字，并且判断创建是否成功。
	PtrToSocket listen_socket(new MtSocket);
	if(!static_cast<bool>(listen_socket)){
		return(-1);
	}
	//2.创建监听套接字，并且判断创建是否成功。
	if(listen_socket->create(FD_ACCEPT|FD_CLOSE)<0){
		return(-2);
	}
	//3.为套接字绑定端口、IP地址。
	if(listen_socket->bind(port,ip)<0){
		return(-3);
	}
	//4.启动套接字监听功能。
	if(listen_socket->listen()<0){
		return(-4);
	}
	//5.设置套接字ID值。
	if(listen_socket->set_id(MAIN_SOCKET_ID)<0){
		return(-5);
	}
	//6.将套接字添加到向量中。
	if(add_socket(listen_socket)<0){
		return(-6);
	}
	//7.设置事件命令监听线程重新等待套接字事件。
	BOOL execute_result=SetEvent(_continue_monitoring_event);
	assert(TRUE==execute_result);
	//8.程序运行到此成功返回。
	return(0);
}

/**
 * name: connect
 * brief: 启动套接字连接功能，并建立其通讯环境。
 * param: port - 端口号。
 *		  ip - IP地址。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtNetPort::connect(const unsigned short port,const CString &ip){
	//1.创建连接套接字，并且判断创建是否成功。
	PtrToSocket connect_socket(new MtSocket);
	if(!static_cast<bool>(connect_socket)){
		return(-1);
	}
	//2.创建连接套接字，并且判断创建是否成功。
	if(connect_socket->create(FD_READ|FD_WRITE|FD_CLOSE)<0){
		return(-2);
	}
	//3.设置连接套接字阻塞关闭，并且判断设置是否成功。
	if(connect_socket->block_close()<0){
		return(-3);
	}
	//4.启动连接，并且判断启动是否成功。
	if(connect_socket->connect(port,ip)<0){
		return(-4);
	}
	//5.设置套接字ID值。
	if(connect_socket->set_id(MAIN_SOCKET_ID)<0){
		return(-5);
	}
	//6.将套接字添加到向量中。
	if(add_socket(connect_socket)<0){
		return(-6);
	}
	//7.设置事件命令监听线程重新等待套接字事件。
	BOOL execute_result=SetEvent(_continue_monitoring_event);
	assert(TRUE==execute_result);
	//8.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_port
 * brief: 设置端口号。
 * param: port - 端口号。
 * return: --
 */
void MtNetPort::set_port(const unsigned short port){
	MtAutoLock<MtLock> lock(_lock);
	_port=port;
}

/**
 * name: get_port
 * brief: 获取端口号。
 * param: --
 * return: 返回端口号。
 */
unsigned short MtNetPort::get_port() const{
	MtAutoLock<MtLock> lock(_lock);
	return(_port);
}

/**
 * name: set_ip
 * brief: 设置IP。
 * param: ip - IP地址。
 * return: --
 */
void MtNetPort::set_ip(const CString &ip){
	MtAutoLock<MtLock> lock(_lock);
	_ip=ip;
}

/**
 * name: get_ip
 * brief: 获取IP。
 * param: --
 * return: 返回IP。
 */
CString MtNetPort::get_ip() const{
	MtAutoLock<MtLock> lock(_lock);
	return(_ip);
}

/**
 * name: add_socket
 * brief: 添加套接字。
 * param: socket - 套接字。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtNetPort::add_socket(PtrToSocket &socket){
	//1.判断当前传递参数是否合法。
	if((!static_cast<bool>(socket))||(0==socket->get_id())){
		return(-1);
	}
	//2.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//3.判断与当前套接字ID相同的套接字是否存在。
	SocketVector::iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket->get_id()));
	//4.如果套接字已经存在，则直接返回错误（避免向量中存储重复的套接字）。
	if(socket_iterator!=_sockets.end()){
		return(-2);
	}
	//5.如果套接字不存在，则添加。
	else{
		_sockets.push_back(socket);
	}
	//6.成程运行到此成功返回。
	return(0);
}

/**
 * name: erase_socket
 * brief: 删除指定的套接字。
 * param: socket_id - 套接字ID。
 * return: --
 */
void MtNetPort::erase_socket(const unsigned int socket_id){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.按照指定的套接字ID，查找套接字。
	SocketVector::const_iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.如果套接字存在，则进行删除操作。
	if(_sockets.end()!=socket_iterator){
		_sockets.erase(socket_iterator);
	}
}

/**
 * name: clear_sockets
 * brief: 清空类中存储的套接字。
 * param: --
 * return: --
 */
void MtNetPort::clear_sockets(){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.清空类中存储的套接字。
	_sockets.clear();
	SocketVector().swap(_sockets);//强制向量释放内存。
}

/**
 * name: does_socket_exist
 * brief: 判断指定的套接字是否存在。
 * param: socket_id - 套接字ID。
 * return: 如果指定的套接字存在则返回TRUE，否则返回FALSE。
 */
BOOL MtNetPort::does_socket_exist(const unsigned int socket_id) const{
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.按照指定的套接字ID，查找套接字。
	SocketVector::const_iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.如果不能成功找到指定套接字。
	if(_sockets.end()==socket_iterator){
		return(FALSE);
	}
	//4.如果成功找到指定套接字。
	else{
		return(TRUE);
	}
}

/**
 * name: wait_socket_events
 * brief: 等待网口套接字事件。
 * param: --
 * return: 如果成功等待到网口监听继续事件，则返回零。
 *         如果成功等待到网口套接字事件，则返回套接字ID。
 *         如果等待失败，则返回值小于零。
 */
int MtNetPort::wait_socket_events(){
	//1.定义临时数据类型。
	typedef std::shared_ptr<HANDLE> PtrToHandle;
	typedef std::shared_ptr<unsigned int> PtrToUint;
	//2.声明当前操作所需变量。
	PtrToHandle socket_events;
	PtrToUint socket_ids;
	unsigned int socke_size=0;
	{
		//3.加锁。
		MtAutoLock<MtLock> lock(_lock);
		//4.获取当前类中保存的套接字数量。
		socke_size=_sockets.size()+1;
		//5.创建网口事件关联句柄数组以及网口套接字ID数组，并且判断是否成功。
		socket_events.reset(new HANDLE[socke_size],
			array_smart_pointer_deletor<HANDLE>);
		socket_ids.reset(new unsigned int[socke_size],
			array_smart_pointer_deletor<unsigned int>);
		//6.如果数组创建失败，则直接返回。
		if((!static_cast<bool>(socket_events))||
			(!static_cast<bool>(socket_ids))){
			return(-1);
		}
		//7.为数组赋值。
		(socket_events.get())[0]=_continue_monitoring_event;
		(socket_ids.get())[0]=0;//当套接字事件为监听继续时，其对应的套接字ID为零（无意义值）。
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
	//8.等待网口事件，并且记录哪个事件发生。
	const DWORD socket_index=WSAWaitForMultipleEvents(
		socke_size,socket_events.get(),FALSE,WSA_INFINITE,FALSE);
	//9.如果等待失败，则直接返回错误。
	if(socket_index>=socke_size){
		return(-3);
	}
	//10.如果等待成功，返回套接字ID。
	return((socket_ids.get())[socket_index]);
}

/**
 * name: get_socket
 * brief: 根据套接字ID获取指定的套接字。
 * param: socket_id - 套接字ID。
 * return: 如果函数执行成功返回指定套接字的智能指针，否则返回空的智能指针。
 */
MtNetPort::PtrToSocket MtNetPort::get_socket(const unsigned int socket_id){
	//1.加锁。
	MtAutoLock<MtLock> lock(_lock);
	//2.按照指定的套接字ID，查找套接字。
	SocketVector::iterator socket_iterator=std::find_if(
		_sockets.begin(),_sockets.end(),MtSocketFinder(socket_id));
	//3.如果不能成功找到指定套接字，直接返回空的套接字智能指针。
	if(_sockets.end()==socket_iterator){
		return(PtrToSocket());
	}
	//4.如果成功找到指定套接字。
	else{
		//4-1.如果当前找到的套接字不合法，则擦掉套接字，并返回。
		if((!static_cast<bool>(*socket_iterator))||
			(0==(*socket_iterator)->get_id())){
			_sockets.erase(socket_iterator);//擦除作废的套接字。
			return(PtrToSocket());
		}
		//4-2.如果当前找到的套接字合法。
		else{
			return(*socket_iterator);
		}
	}
}

/**
 * name: monitoring
 * brief: 负责监听网口事件，并对各个事件进行响应。
 * param: --
 * return: --
 */
void MtNetPort::monitoring(){
	while(TRUE){
		//1.监听网口事件，并且记录监听结果。
		const int socket_id=wait_socket_events();
		//2.如果监听网口事件失败。
		if(socket_id<0){
			//2-1.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//2-2.继续下次循环。
			continue;
		}
		//3.如果当前监听到的事件为网口监听继续事件。
		else if(0==socket_id){
			//3-1.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//3-2.继续下次循环。
			continue;
		}
		//4.如果当前监听到的事件为网口事件。
		else{
			//4-1.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-2.根据当前套接字ID，获取套接字。
			PtrToSocket socket=get_socket(socket_id);
			//4-3.如果获取套接字失败。
			if(!static_cast<bool>(socket)){
				//4-3-1.如果当前希望终止网口监听。
				if(!_is_monitoring){
					return;
				}
				//4-3-2.继续下次循环。
				continue;
			}
			/*
			//4-4.如果获取当前的套接字不合法。
			if(0==socket->get_id()){
				//4-4-1.擦除当前套接字。
				erase_socket(socket_id);
				//4-4-2.如果当前希望终止网口监听。
				if(!_is_monitoring){
					return;
				}
				//4-4-3.继续下次循环。
				continue;
			}
			*/
			//4-5.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-6.获取当前套接字上发生的事件，并且判断获取是否成功。
			WSANETWORKEVENTS socket_events;
			memset(&socket_events,0,sizeof(WSANETWORKEVENTS));
			if(socket->enum_network_events(socket_events)<0){
				//4-6-1.如果当前希望终止网口监听。
				if(!_is_monitoring){
					return;
				}
				//4-6-2.继续下次循环。
				continue;
			}
			//4-7.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-8.如果当前套接字事件为“接受”事件。
			if((socket_events.lNetworkEvents&FD_ACCEPT)&&
				(0==socket_events.iErrorCode[FD_ACCEPT_BIT])){
				//4-8-1.接受一个新的套接字的连接。
				PtrToSocket new_socket=socket->accept();
				//4-8-2.如果接受成功。
				if(static_cast<bool>(new_socket)){
					//4-8-2-1.如果设置新套接字阻塞关闭成功。
					if(new_socket->block_close()>=0){
						add_socket(new_socket);
					}
					//4-8-2-2.如果设置新套接字阻塞关闭失败。
					else{
					}
				}
				//4-8-3.如果接受失败。
				else{
				}
			}//accept
			//4-9.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-10.如果当前套接字事件为“读”事件。
			if((socket_events.lNetworkEvents&FD_READ)&&
				(0==socket_events.iErrorCode[FD_READ_BIT])){
				//4-10-1.获取当前应该接收的数据尺寸。
				int data_size=socket->get_data_size_in_receive_buffer();
				//4-10-2.如果当前获取的应该接收的数据尺寸合法。
				if(data_size>0){
					//4-10-2-1.定义数据类型。
					typedef std::shared_ptr<unsigned char> PtrToUChar;
					//4-10-2-2.创建数据接收缓冲区，并且判断创建是否成功。
					PtrToUChar buffer(new unsigned char[data_size],
						array_smart_pointer_deletor<unsigned char>);
					//4-10-2-3.如果数据接收缓冲区创建成功。
					if(static_cast<bool>(buffer)){
						//4-10-2-3-1.接收数据，并且记录实际接收数据尺寸。
						data_size=socket->receive(buffer.get(),data_size);
						//4-10-2-3-2.如果成功接收数据。
						if(data_size>0){
							if(0!=_receive_callback){
								for(int index=0;index!=data_size;++index){
									_receive_callback(socket_id,(buffer.get())[index],_receive_instance);
								}
							}else{
							}
						}
						//4-10-2-3-3.如果接收数据失败。
						else{
						}
					}
					//4-10-2-4.如果数据接收缓冲区创建失败。
					else{
					}
				}
				//4-10-3.如果当前获取的应该接收的数据尺寸不合法。
				else{
				}
			}//read
			//4-11.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-12.如果当前网口事件为写事件。
			if((socket_events.lNetworkEvents&FD_WRITE)&&
				(0==socket_events.iErrorCode[FD_WRITE_BIT])){
			}
			//4-13.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-14.如果当前网口事件为关闭事件。
			if((socket_events.lNetworkEvents&FD_CLOSE)&&
				(0==socket_events.iErrorCode[FD_CLOSE_BIT])){
				erase_socket(socket_id);
			}
			//4-15.如果当前希望终止网口监听。
			if(!_is_monitoring){
				return;
			}
			//4-16.继续下次循环。
			continue;
		}//else
	}//while
}

/**
 * name: close_monitoring
 * brief: 关闭网口监听。
 * param: --
 * return: --
 */
void MtNetPort::close_monitoring(){
	//1.如果当前网口监听线程存在，则继续线程撤销释放操作。
	if((0!=_monitoring)&&(INVALID_HANDLE_VALUE!=_monitoring)){
		//1-1.设置线程退出标记。
		_is_monitoring=FALSE;
		//1-2.命令线程继续运行，检测线程退出标记。
		BOOL execute_result=SetEvent(_continue_monitoring_event);
		assert(TRUE==execute_result);
		//1-3.等待网口监听线程退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(_monitoring,THREAD_EXIT_TIMEOUT)){
			execute_result=TerminateThread(_monitoring,0);
			assert(TRUE==execute_result);
		}
		//1-4.关闭网口监听线程。
		execute_result=CloseHandle(_monitoring);
		assert(TRUE==execute_result);
	}
	//2.恢复网口监听线程句柄。
	_monitoring=INVALID_HANDLE_VALUE;
	//3.恢复网口监听线程退出标记。
	_is_monitoring=FALSE;
	//4.恢复网口监听线程继续事件。
	// ... ...
}

/**
 * name: open_monitoring
 * brief: 打开网口监听。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtNetPort::open_monitoring(){
	//1.如果网口监听线程已经创建，则直接返回错误。
	if((0!=_monitoring)&&(INVALID_HANDLE_VALUE!=_monitoring)){
		return(-1);
	}
	//2.初始化相关标记变量。
	_is_monitoring=TRUE;
	//3.开启网口监听线程，并且判断开启是否成功。
	_monitoring=reinterpret_cast<HANDLE>(
		_beginthreadex(0,0,monitoring,this,0,0));
	if((0==_monitoring)||(INVALID_HANDLE_VALUE==_monitoring)){
		_is_monitoring=FALSE;
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}