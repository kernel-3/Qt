#include"stdafx.h"
#include"Port.h"
#include"Command.h"

/**
 * name: Port
 * breif: 构造函数。
 * param: --
 * return: --
 */
Port::Port(void){
}

/**
 * name: ~Port
 * brief: 析构函数。
 * param: --
 * return: --
 */
Port::~Port(void){
}

/**
 * name: write
 * brief: 向端口写指令。
 * param: command - 输入的指向指令数组的指针。
 *        size - 输入的指令数组尺寸。
 * return: 如果指令发送成功返回值大于等于零，否则返回值小于零。
 */
int Port::write(const unsigned char *command,const unsigned int size){
	//1.检测参数输入是否合法。
	if((0==command)||(0==size)){
		return(-1);
	}
	//2.程序运行到此成功返回。
	else{
		return(0);
	}
}