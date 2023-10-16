#include"stdafx.h"
#include"MtSocketFinder.h"
#include"MtSocket.h"
#include<assert.h>

/**
 * name: MtSocketFinder
 * brief: ���캯����
 * param: socket_id - �׽���ID��
 * return: --
 */
MtSocketFinder::MtSocketFinder(const unsigned int socket_id)
	:_socket_id(socket_id){
}

/**
 * name: ~MtSocketFinder
 * brief: ����������
 * param: --
 * return: --
 */
MtSocketFinder::~MtSocketFinder(void){
}

/**
 * name: operator()
 * brief: ������ʵ�֡�
 * param: socket - ָ���׽��֡�
 * return: ����Ƚϳɹ�����true�����򷵻�false��
 */
bool MtSocketFinder::operator()(const PtrToSocket &socket) const{
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���������Ϸ���ֱ�ӷ���false��
	if(!static_cast<bool>(socket)){
		return(false);
	}
	//2.���бȽϣ����ҷ��رȽϽ����
	return(_socket_id==socket->get_id());
}