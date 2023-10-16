#include"stdafx.h"
#include"MtSocketFinder.h"
#include"MtSocket.h"
#include<assert.h>

/**
 * name: MtSocketFinder
 * brief: 构造函数。
 * param: socket_id - 套接字ID。
 * return: --
 */
MtSocketFinder::MtSocketFinder(const unsigned int socket_id)
	:_socket_id(socket_id){
}

/**
 * name: ~MtSocketFinder
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtSocketFinder::~MtSocketFinder(void){
}

/**
 * name: operator()
 * brief: 方法类实现。
 * param: socket - 指向套接字。
 * return: 如果比较成功返回true，否则返回false。
 */
bool MtSocketFinder::operator()(const PtrToSocket &socket) const{
	//1.判断当前传递参数是否合法，如果不合法则直接返回false。
	if(!static_cast<bool>(socket)){
		return(false);
	}
	//2.进行比较，并且返回比较结果。
	return(_socket_id==socket->get_id());
}