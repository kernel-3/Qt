#include"stdafx.h"
#include"HL7ERRSegment.h"

//初始化静态全局变量。
const String HL7ERRSegment::SegmentName(Text("ERR"));

/**
 * name: HL7ERRSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7ERRSegment::HL7ERRSegment(void)
	:HL7Segment(SegmentName,2)
	,_error_code_and_location(Text("")){
}

/**
 * name: ~HL7ERRSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7ERRSegment::~HL7ERRSegment(void){
}

/**
 * name: set_error_code_and_location
 * brief: 设置错误代码与位置。
 * param: error_code_and_location - 错误代码与位置。
 * return: --
 */
void HL7ERRSegment::set_error_code_and_location(
	const String &error_code_and_location){
	_error_code_and_location=error_code_and_location;
}

/**
 * name: get_error_code_and_location
 * brief: 获取错误代码与位置。
 * param: --
 * return: 返回错误代码与位置。
 */
const String &HL7ERRSegment::get_error_code_and_location() const{
	return(_error_code_and_location);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7ERRSegment::set_field(const unsigned int no,const String &content){
	//1.调用基类相应函数设置指定的“域”，并且判断设置结果。
	//1-1.调用基类相应函数设置指定的“域”。
	const int execute_result=HL7Segment::set_field(no,content);
	//1-2.如果成功设置指定的“域”。
	if(execute_result>0){
		return(1);
	}
	//1-3.如果设置指定的“域”失败。
	else if(execute_result<0){
		return(-1);
	}
	//2.如果当前期望设置“段”的第二个“域”。
	else if(2==no){
		//2-1.如果当前准备设置“域”的内容不合法。
		if((Text("0")!=content)&&(Text("100")!=content)&&
			(Text("101")!=content)&&(Text("102")!=content)&&
			(Text("103")!=content)&&(Text("200")!=content)&&
			(Text("201")!=content)&&(Text("202")!=content)&&
			(Text("203")!=content)&&(Text("204")!=content)&&
			(Text("205")!=content)&&(Text("206")!=content)&&
			(Text("207")!=content)){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_error_code_and_location=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-3);
	}
}

/**
 * name: get_field
 * brief: 获取“段”中指定“域”的内容。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - 返回“域”的内容。
 * return: 如果“域”内容获取成功返回值大于零，如果忽略“域”
 *         内容的获取设置则返回零，如果“域”内容的获取失败
 *         返回负数。
 */
int HL7ERRSegment::get_field(const unsigned int no,String &content) const{
	//1.调用基类相应函数获取指定的“域”，并且判断获取结果。
	//1-1.调用基类相应函数获取指定的“域”。
	const int execute_result=HL7Segment::get_field(no,content);
	//1-2.如果调用基类相应函数成功获取指定的“域”，则直接返回。
	if(execute_result>0){
		return(1);
	}
	//1-3.如果调用基类相应函数获取指定的“域”失败，则直接返回。
	else if(execute_result<0){
		return(-1);
	}
	//2.如果当前期望获取“段”的第二个“域”。
	else if(2==no){
		//2-1.如果当前准备获取“域”的内容不合法。
		if((Text("0")!=_error_code_and_location)&&
			(Text("100")!=_error_code_and_location)&&
			(Text("101")!=_error_code_and_location)&&
			(Text("102")!=_error_code_and_location)&&
			(Text("103")!=_error_code_and_location)&&
			(Text("200")!=_error_code_and_location)&&
			(Text("201")!=_error_code_and_location)&&
			(Text("202")!=_error_code_and_location)&&
			(Text("203")!=_error_code_and_location)&&
			(Text("204")!=_error_code_and_location)&&
			(Text("205")!=_error_code_and_location)&&
			(Text("206")!=_error_code_and_location)&&
			(Text("207")!=_error_code_and_location)){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_error_code_and_location;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-3);
	}
}