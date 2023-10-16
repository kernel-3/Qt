#include"stdafx.h"
#include"HL7QAKSegment.h"

//初始化静态变量。
const String HL7QAKSegment::SegmentName(Text("QAK"));

/**
 * name: HL7QAKSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7QAKSegment::HL7QAKSegment(void)
	:HL7Segment(SegmentName,3)
	,_query_tag(Text("SR"))
	,_query_response_status(Text("")){
}

/**
 * name: ~HL7QAKSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7QAKSegment::~HL7QAKSegment(void){
}

/**
 * name: get_query_tag
 * brief: 获取查询标记。
 * param: --
 * return: 返回查询标记。
 */
const String &HL7QAKSegment::get_query_tag() const{
	return(_query_tag);
}

/**
 * name: set_query_response_status
 * brief: 设置查询应答状态。
 * param: query_response_status - 查询应答状态。
 * return: --
 */
void HL7QAKSegment::set_query_response_status(const String &query_response_status){
	_query_response_status=query_response_status;
}

/**
 * name: get_query_response_status
 * brief: 获取查询应答状态。
 * param: --
 * return: 返回查询应答状态。
 */
const String &HL7QAKSegment::get_query_response_status() const{
	return(_query_response_status);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7QAKSegment::set_field(const unsigned int no,const String &content){
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
		if(Text("SR")!=content){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		//_query_tag=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备设置“域”的内容不合法。
		if((Text("OK")!=content)&&
			(Text("NF")!=content)&&
			(Text("AE")!=content)&&
			(Text("AR")!=content)){
			return(-3);
		}
		//3-2.设置当前“域”的内容。
		_query_response_status=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-4);
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
int HL7QAKSegment::get_field(const unsigned int no,String &content) const{
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
		if(Text("SR")!=_query_tag){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_query_tag;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备获取“域”的内容不合法。
		if((Text("OK")!=_query_response_status)&&
			(Text("NF")!=_query_response_status)&&
			(Text("AE")!=_query_response_status)&&
			(Text("AR")!=_query_response_status)){
			return(-3);
		}
		//3-2.获取当前“域”的内容。
		content=_query_response_status;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-4);
	}
}