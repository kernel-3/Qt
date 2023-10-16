#include"stdafx.h"
#include"Inis.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtIni.h"
#include"CommonData.h"

/**
 * name: ~Inis
 * brief: ����������
 * param: --
 * return: --
 */
Inis::~Inis(void){
	delete _instrument;
}

/**
 * name: instance
 * breif: ��ȡϵͳ��Ψһ��ini�ļ���ʵ������
 * param: --
 * return: ����ϵͳ��Ψһ��ini�ļ���ʵ������
 */
Inis *Inis::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: read
 * brief: ��ȡָ��ini�ļ��е�ָ�����ݡ�
 * param: file_name - �����ָ�����ļ����ơ�
 *        section_name - ����Ķ����ơ�
 *        item_name - ����������ơ�
 *        default_value - �����Ĭ��ֵ��
 * return: ���ض�ȡ���ݡ�
 */
int Inis::read(const Name file_name,const CString &section_name,
	const CString &item_name,const int default_value/*=0*/){
	//1.�����ǰ׼����ȡ���ļ�Ϊ�豸�����ļ���
	if(NAME_INSTRUMENT==file_name){
		return(_instrument->read(section_name,
			item_name,default_value));
	}
	//2.�����ǰ׼����ȡ���ļ�δ֪����ֱ�ӷ���Ĭ��ֵ��
	else{
		return(default_value);
	}
}

/**
 * name: write
 * breif: ��ָ����ini�ļ�д��ָ�������ݡ�
 * param: file_name - ����ָ�����ļ����ơ�
 *        section_name - ����ָ���Ķ����ơ�
 *        item_name - ����ָ���������ơ�
 *        value - ����׼��д������ݡ�
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
BOOL Inis::write(const Name file_name,const CString &section_name,
	const CString &item_name,const int value){
	//1.�����ǰ׼��д����ļ����豸�����ļ���
	if(NAME_INSTRUMENT==file_name){
		return(_instrument->write(section_name,item_name,value));
	}
	//2.�����ǰ׼��д����ļ�δ֪����ֱ�ӷ��ش���
	else{
		return(FALSE);
	}
}

/**
 * name: Inis
 * breif: ���캯����
 * param: --
 * return: --
 */
Inis::Inis(void)
	:_instrument(new MtIni(((
		CommonData::instance())->
		get_master_directory())+_T(
		"config\\instrument.ini"))){
}