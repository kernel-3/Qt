#include"stdafx.h"
#include"Logs.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtLog.h"
#include"CommonData.h"

/**
 * name: ~Logs
 * brief: ����������
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
 * breif: ��ȡϵͳ��Ψһ����־��ʵ������
 * param: --
 * return: ����ϵͳ��Ψһ����־��ʵ������
 */
Logs *Logs::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: write
 * breif: ��ָ�����־�У���дָ������Ϣ��
 * param: name - ����ָ����־�����ơ�
 *        text - �����ָ����Ϣ��
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
 * breif: ���캯����
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
