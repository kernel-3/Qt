#include"stdafx.h"
#include"Logs.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtLog.h"
#include"CommonData.h"

/**
 * name: ~Logs
 * brief: 析构函数。
 * param: --
 * return: --
 */
Logs::~Logs(void){
	delete _command;
	delete _event;
	delete _error;
}

/**
 * name: instance
 * breif: 获取系统中唯一的日志类实例对象。
 * param: --
 * return: 返回系统中唯一的日志类实例对象。
 */
Logs *Logs::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: write
 * breif: 向指令的日志中，书写指定的信息。
 * param: name - 输入指定日志的名称。
 *        text - 输入的指定信息。
 * return: --
 */
void Logs::write(const Name name,const CString &text){
	if(NAME_COMMAND==name){
		_command->write(text);
	}else if(NAME_EVENT==name){
		_event->write(text);
	}else if(NAME_ERROR==name){
		_error->write(text);
	}
}

/**
 * name: Logs
 * breif: 构造函数。
 * param: --
 * return: --
 */
Logs::Logs(void)
	:_command(new MtLog(((CommonData::instance())->
		get_master_directory())+_T("log\\command\\")))
	,_event(new MtLog(((CommonData::instance())->
		get_master_directory())+_T("log\\event\\")))
	,_error(new MtLog(((CommonData::instance())->
		get_master_directory())+_T("log\\error\\"))){
}
