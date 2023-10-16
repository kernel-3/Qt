#include"stdafx.h"
#include"GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"

/**
 * name: ~GlobalData
 * brief: ����������
 * param: --
 * return: --
 */
GlobalData::~GlobalData(void){
}

/**
 * name: instance
 * breif: ��ȡϵͳ��Ψһ��ȫ��������ʵ������
 * param: --
 * return: ����ϵͳ��Ψһ��ȫ��������ʵ������
 */
GlobalData *GlobalData::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_master_directory
 * brief: ��ȡ��ǰ������Ŀ¼��
 * param: --
 * return: ���ص�ǰ������Ŀ¼��
 */
const CString &GlobalData::get_master_directory() const{
	return(_master_directory);
}

/**
 * name: GlobalData
 * brief: ���캯����
 * param: --
 * return: --
 */
GlobalData::GlobalData(void)
	:_master_directory(_T("")){
	init();
}

/**
 * name: init
 * breif: �Ե�ǰ����г�ʼ����
 * param: --
 * return: --
 */
void GlobalData::init(){
	//1.�����¼��ǰ������Ŀ¼��
	//1-1.��ȡ��ǰ��������·���������ļ����ƣ���
	TCHAR directory[MAX_PATH];
	memset(directory,0,MAX_PATH*sizeof(TCHAR));
	GetModuleFileName(0,directory,MAX_PATH);
	//1-2.ȥ��·�������������ļ����ơ�
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
	//1-3.��¼��ǰ������Ŀ¼���������ļ����ƣ���
	_master_directory=directory;
}