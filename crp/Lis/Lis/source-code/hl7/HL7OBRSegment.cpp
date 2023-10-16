#include"stdafx.h"
#include"HL7OBRSegment.h"

//定义初始化全局变量。
const String HL7OBRSegment::SegmentName(Text("OBR"));

/**
 * name: HL7OBRSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7OBRSegment::HL7OBRSegment(void)
	:HL7Segment(SegmentName,48)
	,_segment_id(Text("1")){
}

/**
 * name: ~HL7OBRSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7OBRSegment::~HL7OBRSegment(void){
}

/**
 * name: get_segment_id
 * breif: 获取“段”的ID。
 * param: --
 * return: 返回“段”的ID。
 */
const String &HL7OBRSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7OBRSegment::set_field(const unsigned int no,const String &content){
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
		//2-1.如果当前准备设置第二个“域”的内容不合法。
		if(content!=_segment_id){
			return(-2);
		}
		//2-1.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的“域”大于第二个。
	else if(no>2){
		return(0);
	}
	//4.如果当前期望设置“段”的“域”为异常“域”。
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
int HL7OBRSegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.获取第二个“域”的内容。
		content=_segment_id;
		//2-2.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的“域”大于第二个。
	else if(no>2){
		return(0);
	}
	//4.如果当前期望获取“段”的“域”为异常“域”。
	else{
		return(-2);
	}
}