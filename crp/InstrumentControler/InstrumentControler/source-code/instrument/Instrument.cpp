#include"stdafx.h"
#include"Instrument.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtAutoDeleter.h"
#include"Communication/Communications.h"
#include"Communication/ControlPort.h"
#include"component/Components.h"
#include"function/Functions.h"
#include"component/ReactionDisc.h"

/**
 * name: ~Instrument
 * breif: ����������
 * param: --
 * return: --
 */
Instrument::~Instrument(void){
	delete _functions;
	delete _components;
	delete _communications;
}

/**
 * name: instance
 * brief: Ϊ��ǰ�ഴ��ϵͳ��Ψһʵ����
 * param: --
 * return: ����ϵͳ��ָ��ǰ���Ψһʵ��ָ�롣
 */
Instrument *Instrument::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_functions
 * brief: ��ȡ�豸�еĹ����ࡣ
 * param: --
 * return: �����豸�еĹ����ࡣ
 */
Functions *Instrument::get_functions(){
	return(_functions);
}

/**
 * name: get_components
 * brief: ��ȡ��ǰ�豸�е���������ࡣ
 * param: --
 * return: ���ص�ǰ�豸�е���������ࡣ
 */
Components *Instrument::get_components(){
	return(_components);
}

/**
 * name: get_communications
 * breif: ��ȡ��ǰ�豸�е�ͨѶ�����ࡣ
 * param: --
 * return: ���ص�ǰ�豸�е�ͨѶ�����ࡣ
 */
Communications *Instrument::get_communications(){
	return(_communications);
}

/**
 * name: Instrument
 * brief: ���캯����
 * param: --
 * return: --
 */
Instrument::Instrument(void)
	:_functions(new Functions)
	,_components(new Components)
	,_communications(new Communications){
}