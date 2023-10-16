#pragma once

#include"../Symbol"
#include<memory>

class MtSocket;

/**
 * name: MtSocketFinder
 * brief: �����࣬�׽��ֲ������������ṩ
 *        �׽��ֲ��ҹ��ܡ�
 * author: yameng_he
 * date: 2014-12-17
 */
class MFC_TOOLKIT_API MtSocketFinder{
//define
public:
	typedef std::shared_ptr<MtSocket> PtrToSocket;
//construction & destruction
public:
	MtSocketFinder(const unsigned int socket_id);
	~MtSocketFinder(void);
//interface
public:
	bool operator()(const PtrToSocket &socket) const;
//variables
private:
	unsigned int _socket_id;
};