#include"stdafx.h"
#include"Port.h"
#include"Command.h"

/**
 * name: Port
 * breif: ���캯����
 * param: --
 * return: --
 */
Port::Port(void){
}

/**
 * name: ~Port
 * brief: ����������
 * param: --
 * return: --
 */
Port::~Port(void){
}

/**
 * name: write
 * brief: ��˿�дָ�
 * param: command - �����ָ��ָ�������ָ�롣
 *        size - �����ָ������ߴ硣
 * return: ���ָ��ͳɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Port::write(const unsigned char *command,const unsigned int size){
	//1.�����������Ƿ�Ϸ���
	if((0==command)||(0==size)){
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	else{
		return(0);
	}
}