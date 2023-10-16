#include"stdafx.h"
#include"Functions.h"
#include"timing/Timing.h"

/**
 * name: Functions
 * brief: ���캯����
 * param: --
 * return: --
 */
Functions::Functions(void)
	:_timing(new Timing){
}

/**
 * name: ~Functions
 * breif: ����������
 * param: --
 * return: --
 */
Functions::~Functions(void){
	delete _timing;
}

/**
 * name: get_timing
 * brief: ��ȡʱ���ܡ�
 * param: --
 * return: ����ʱ���ܡ�
 */
Timing *Functions::get_timing(){
	return(dynamic_cast<Timing*>(get_function(
		FUNCTION_ID_TIMING)));
}

/**
 * name: get_function
 * brief: ��ȡָ���Ĺ��ܡ�
 * param: function_id - ����Ĺ��ܱ�ʶ��
 * return: �������ִ�гɹ�����ָ��ָ�����ܵ�ָ�룬����
 *         ���ؿ�ָ�롣
 */
Function *Functions::get_function(const FunctionID function_id){
	//1.�����ǰ������ȡʱ���ܣ���ֱ�ӷ���ʱ���ܡ�
	if(FUNCTION_ID_TIMING==function_id){
		return(_timing);
	}
	//..�����ǰ������ȡ�������ܣ���ֱ�ӷ��ؿ�ָ�롣
	else{
		return(0);
	}
}