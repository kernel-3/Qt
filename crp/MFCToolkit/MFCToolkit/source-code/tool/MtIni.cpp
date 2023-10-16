#include"stdafx.h"
#include"MtIni.h"
#include"MtLock.h"
#include"MtAutoLock.h"
#include"MtCharacterSet.h"

/**
 * name: MtIni
 * brief: 构造函数。
 * param: file_name - 输入的ini文件路径名称。
 * return: --
 */
MtIni::MtIni(const CString &file_path)
	:_lock(new MtLock)
	,_file_path(file_path){
}

/**
 * name: ~MtIni
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtIni::~MtIni(void){
	delete _lock;
}

/**
 * name: read
 * brief: 读取指定的ini文件。
 * param: section_name - 输入的段名。
 *        item_name - 输入的项名。
 *        default_value - 输入的默认值。
 * return: 返回读取的值。
 */
int MtIni::read(const CString &section_name,
	const CString &item_name,const int default_value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.读取并返回文件中的相应内容。
	return(GetPrivateProfileInt(section_name,item_name,
		default_value,_file_path));
}

/**
 * name: read
 * brief: 读取指定的ini文件。
 * param: section_name - 输入的段名。
 *        item_name - 输入的项名。
 *        default_value - 输入的默认值。
 * return: 返回读取的值。
 */
float MtIni::read(const CString &section_name,
	const CString &item_name,const float default_value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.读取并返回文件中的相应内容。
	return(static_cast<float>(read(section_name,
		item_name,static_cast<double>(default_value))));
}

/**
 * name: read
 * brief: 读取指定的ini文件。
 * param: section_name - 输入的段名。
 *        item_name - 输入的项名。
 *        default_value - 输入的默认值。
 * return: 返回读取的值。
 */
double MtIni::read(const CString &section_name,
	const CString &item_name,const double default_value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.声明当前操作所需变量。
	CString default_value_t(_T(""));
	default_value_t.Format(_T("%lf"),default_value);
	//2.读取指定文件中的指定内容。
	const CString value=read(section_name,item_name,
		default_value_t);
	//3.如果内容为空，则返回默认值。
	if(_T("")==value){
		return(default_value);
	}
	//4.如果内容不是小数，则返回默认值。
	else if(!MtCharacterSet::is_decimals(value)){
		return(default_value);
	}
	//5.将读取的内容转化为浮点数返回。
	else{
		return(_tstof(value));
	}
}

/**
 * name: read
 * brief: 读取指定的ini文件。
 * param: section_name - 输入的段名。
 *        item_name - 输入的项名。
 *        default_value - 输入的默认值。
 * return: 返回读取的值。
 */
CString MtIni::read(const CString &section_name,
	const CString &item_name,const CString &default_value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.声明当前操作所需变量。
	TCHAR buffer[MAXIMUM_BUFFER_SIZE];
	memset(buffer,0,MAXIMUM_BUFFER_SIZE*sizeof(TCHAR));
	//3.读取并返回文件中的相应内容。
	GetPrivateProfileString(section_name,item_name,
		default_value,buffer,MAXIMUM_BUFFER_SIZE,_file_path);
	//4.创建返回字符串。
	const CString return_string(buffer);
	//5.程序运行到此直接返回。
	return(return_string);
}

/**
 * name: write
 * brief: 写入指定的ini文件。
 * param: section_name - 输入的段名。
 *        item_name - 输入的项名。
 *        value - 输入的写入值。
 * return: 如果函数执行成功返回TRUE，否则返回FALSE。
 */
BOOL MtIni::write(const CString &section_name,
	const CString &item_name,const int value){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.将写入值转化为字符串。
	CString value_text(_T(""));
	value_text.Format(_T("%ld"),value);
	//3.将指定值写入到文件中，并且返回写入结果。
	return(WritePrivateProfileString(section_name,
		item_name,value_text,_file_path));
}