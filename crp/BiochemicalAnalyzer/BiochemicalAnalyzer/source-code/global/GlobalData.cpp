#include"stdafx.h"
#include"GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"

/**
 * name: ~GlobalData
 * brief: 析构函数。
 * param: --
 * return: --
 */
GlobalData::~GlobalData(void){
}

/**
 * name: instance
 * breif: 获取系统中唯一的全局数据类实例对象。
 * param: --
 * return: 返回系统中唯一的全局数据类实例对象。
 */
GlobalData *GlobalData::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_master_directory
 * brief: 获取当前程序主目录。
 * param: --
 * return: 返回当前程序主目录。
 */
const CString &GlobalData::get_master_directory() const{
	return(_master_directory);
}

/**
 * name: GlobalData
 * brief: 构造函数。
 * param: --
 * return: --
 */
GlobalData::GlobalData(void)
	:_master_directory(_T("")){
	init();
}

/**
 * name: init
 * breif: 对当前类进行初始化。
 * param: --
 * return: --
 */
void GlobalData::init(){
	//1.计算记录当前程序主目录。
	//1-1.获取当前程序所在路径（包括文件名称）。
	TCHAR directory[MAX_PATH];
	memset(directory,0,MAX_PATH*sizeof(TCHAR));
	GetModuleFileName(0,directory,MAX_PATH);
	//1-2.去掉路径中所包含的文件名称。
#ifdef _UNICODE
	const int length=wcslen(directory);
#else
	const int length=strlen(directory);
#endif
	for(int index=length-1;index>=0;--index){
		if(_T('\\')==directory[index]){
			break;
		}else{
			directory[index]=0;
		}
	}
	//1-3.记录当前程序主目录（不包括文件名称）。
	_master_directory=directory;
}