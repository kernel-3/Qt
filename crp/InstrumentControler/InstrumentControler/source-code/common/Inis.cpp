#include"stdafx.h"
#include"Inis.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/tool/MtIni.h"
#include"CommonData.h"

/**
 * name: ~Inis
 * brief: 析构函数。
 * param: --
 * return: --
 */
Inis::~Inis(void){
	delete _instrument;
}

/**
 * name: instance
 * breif: 获取系统中唯一的ini文件类实例对象。
 * param: --
 * return: 返回系统中唯一的ini文件类实例对象。
 */
Inis *Inis::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: read
 * brief: 读取指定ini文件中的指定内容。
 * param: file_name - 输入的指定的文件名称。
 *        section_name - 输入的段名称。
 *        item_name - 输入的项名称。
 *        default_value - 输入的默认值。
 * return: 返回读取内容。
 */
int Inis::read(const Name file_name,const CString &section_name,
	const CString &item_name,const int default_value/*=0*/){
	//1.如果当前准备读取的文件为设备配置文件。
	if(NAME_INSTRUMENT==file_name){
		return(_instrument->read(section_name,
			item_name,default_value));
	}
	//2.如果当前准备读取的文件未知，则直接返回默认值。
	else{
		return(default_value);
	}
}

/**
 * name: write
 * breif: 向指定的ini文件写入指定的内容。
 * param: file_name - 输入指定的文件名称。
 *        section_name - 输入指定的段名称。
 *        item_name - 输入指定的项名称。
 *        value - 输入准备写入的内容。
 * return: 如果函数执行成功返回TRUE，否则返回FALSE。
 */
BOOL Inis::write(const Name file_name,const CString &section_name,
	const CString &item_name,const int value){
	//1.如果当前准备写入的文件是设备配置文件。
	if(NAME_INSTRUMENT==file_name){
		return(_instrument->write(section_name,item_name,value));
	}
	//2.如果当前准备写入的文件未知，则直接返回错误。
	else{
		return(FALSE);
	}
}

/**
 * name: Inis
 * breif: 构造函数。
 * param: --
 * return: --
 */
Inis::Inis(void)
	:_instrument(new MtIni(((
		CommonData::instance())->
		get_master_directory())+_T(
		"config\\instrument.ini"))){
}