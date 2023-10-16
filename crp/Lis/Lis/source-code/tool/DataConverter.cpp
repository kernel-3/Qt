#include"stdafx.h"
#include"DataConverter.h"

/**
 * name: is_number
 * brief: 判断指定内容中存储的数据是否为数字。
 * param: content - 指定的内容。
 * return: 如果指定的内容中存储的数据为数字则返回TRUE，否则返回FALSE。
 */
BOOL DataConverter::is_number(const String &content){
	return(is_unsigned_int(content));
}

/**
 * name: is_unsigned_int
 * brief: 判断指定内容中存储的数据是否为无符号整型数据。
 * param: content - 指定的内容。
 * return: 如果指定的内容为无符号整型数据返回TRUE，否则返回FALSE。
 */
BOOL DataConverter::is_unsigned_int(const String &content){
	//1.如果当前传递的字符串为空，则直接返回FALSE。
	if(content.IsEmpty()){
		return(FALSE);
	}
	//2.计算当前字符串长度。
	const unsigned int content_size=content.GetLength();
	//3.遍历字符串，判断字符串中是否全部为数字。
	for(unsigned int index=0;index!=content_size;++index){
		if((Text('0')>content[index])||(Text('9')<content[index])){
			return(FALSE);
		}
	}
	//4.程序运行到此直接返回TRUE。
	return(TRUE);
}

/**
 * name: to_string
 * breif: 将指定的无符号整型内容转换成字符串。
 * param: content - 指定的无符号整型内容。
 * return: 返回转换成的字符串。
 */
String DataConverter::to_string(const unsigned int content){
	String string_content(Text(""));
	string_content.Format(Text("%ld"),content);
	return(string_content);
}

/**
 * name: to_unsigned_int
 * brief: 将指定的内容转换为无符号整型数据。
 * param: content - 指定内容。
 * return: 如果函数执行成功返回转换后的无符号整型数据，否则返回零。
 */
unsigned int DataConverter::to_unsigned_int(const String &content){
	//1.如果当前指定内容中存储的数据并不是无符号整型数据。
	if(!is_unsigned_int(content)){
		return(0);
	}
	//2.如果当前指定内容中存储的数据是无符号整型数据。
	else{
		return(Atoi(content));
	}
}