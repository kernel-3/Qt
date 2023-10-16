#include"stdafx.h"
#include"MtIni.h"
#include"MtLock.h"
#include"MtAutoLock.h"
#include"MtCharacterSet.h"

/**
 * name: MtIni
 * brief: ���캯����
 * param: file_name - �����ini�ļ�·�����ơ�
 * return: --
 */
MtIni::MtIni(const CString &file_path)
	:_lock(new MtLock)
	,_file_path(file_path){
}

/**
 * name: ~MtIni
 * breif: ����������
 * param: --
 * return: --
 */
MtIni::~MtIni(void){
	delete _lock;
}

/**
 * name: read
 * brief: ��ȡָ����ini�ļ���
 * param: section_name - ����Ķ�����
 *        item_name - �����������
 *        default_value - �����Ĭ��ֵ��
 * return: ���ض�ȡ��ֵ��
 */
int MtIni::read(const CString &section_name,
	const CString &item_name,const int default_value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ�������ļ��е���Ӧ���ݡ�
	return(GetPrivateProfileInt(section_name,item_name,
		default_value,_file_path));
}

/**
 * name: read
 * brief: ��ȡָ����ini�ļ���
 * param: section_name - ����Ķ�����
 *        item_name - �����������
 *        default_value - �����Ĭ��ֵ��
 * return: ���ض�ȡ��ֵ��
 */
float MtIni::read(const CString &section_name,
	const CString &item_name,const float default_value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡ�������ļ��е���Ӧ���ݡ�
	return(static_cast<float>(read(section_name,
		item_name,static_cast<double>(default_value))));
}

/**
 * name: read
 * brief: ��ȡָ����ini�ļ���
 * param: section_name - ����Ķ�����
 *        item_name - �����������
 *        default_value - �����Ĭ��ֵ��
 * return: ���ض�ȡ��ֵ��
 */
double MtIni::read(const CString &section_name,
	const CString &item_name,const double default_value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ǰ�������������
	CString default_value_t(_T(""));
	default_value_t.Format(_T("%lf"),default_value);
	//2.��ȡָ���ļ��е�ָ�����ݡ�
	const CString value=read(section_name,item_name,
		default_value_t);
	//3.�������Ϊ�գ��򷵻�Ĭ��ֵ��
	if(_T("")==value){
		return(default_value);
	}
	//4.������ݲ���С�����򷵻�Ĭ��ֵ��
	else if(!MtCharacterSet::is_decimals(value)){
		return(default_value);
	}
	//5.����ȡ������ת��Ϊ���������ء�
	else{
		return(_tstof(value));
	}
}

/**
 * name: read
 * brief: ��ȡָ����ini�ļ���
 * param: section_name - ����Ķ�����
 *        item_name - �����������
 *        default_value - �����Ĭ��ֵ��
 * return: ���ض�ȡ��ֵ��
 */
CString MtIni::read(const CString &section_name,
	const CString &item_name,const CString &default_value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.������ǰ�������������
	TCHAR buffer[MAXIMUM_BUFFER_SIZE];
	memset(buffer,0,MAXIMUM_BUFFER_SIZE*sizeof(TCHAR));
	//3.��ȡ�������ļ��е���Ӧ���ݡ�
	GetPrivateProfileString(section_name,item_name,
		default_value,buffer,MAXIMUM_BUFFER_SIZE,_file_path);
	//4.���������ַ�����
	const CString return_string(buffer);
	//5.�������е���ֱ�ӷ��ء�
	return(return_string);
}

/**
 * name: write
 * brief: д��ָ����ini�ļ���
 * param: section_name - ����Ķ�����
 *        item_name - �����������
 *        value - �����д��ֵ��
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
BOOL MtIni::write(const CString &section_name,
	const CString &item_name,const int value){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��д��ֵת��Ϊ�ַ�����
	CString value_text(_T(""));
	value_text.Format(_T("%ld"),value);
	//3.��ָ��ֵд�뵽�ļ��У����ҷ���д������
	return(WritePrivateProfileString(section_name,
		item_name,value_text,_file_path));
}