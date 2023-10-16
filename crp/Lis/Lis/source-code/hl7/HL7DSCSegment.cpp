#include"stdafx.h"
#include"HL7DSCSegment.h"
#include"../tool/DataConverter.h"

//初始化静态变量。
const String HL7DSCSegment::SegmentName(Text("DSC"));

/**
 * name: HL7DSCSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7DSCSegment::HL7DSCSegment(void)
	:HL7Segment(SegmentName,2)
	,_continuation_pointer(Text("")){
}

/**
 * name: ~HL7DSCSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7DSCSegment::~HL7DSCSegment(void){
}

/**
 * name: set_continuation_pointer
 * brief: 设置连续指针。
 * param: continuation_pointer - 连续指针。
 * return: --
 */
void HL7DSCSegment::set_continuation_pointer(const String &continuation_pointer){
	_continuation_pointer=continuation_pointer;
}

/**
 * name: get_continuation_pointer
 * brief: 获取连续指针。
 * param: --
 * return: 返回连续指针。
 */
const String &HL7DSCSegment::get_continuation_pointer() const{
	return(_continuation_pointer);
}

/**
 * name: set_continuation_pointer_with_number
 * brief: 以数字形式设置连续指针。
 * param: continuation_pointer - 连续指针。
 * return: --
 */
void HL7DSCSegment::set_continuation_pointer_with_number(const unsigned int continuation_pointer){
	_continuation_pointer=DataConverter::to_string(continuation_pointer);
}

/**
 * name: get_continuation_pointer_with_number
 * brief: 以数字形式获取连续指针。
 * param: --
 * return: 如果函数执行成功以数字形式返回连续指针，否则返回零。
 */
unsigned int HL7DSCSegment::get_continuation_pointer_with_number() const{
	return(DataConverter::to_unsigned_int(_continuation_pointer));
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7DSCSegment::set_field(const unsigned int no,const String &content){
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
		if((!content.IsEmpty())&&
			(0==DataConverter::to_unsigned_int(content))){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_continuation_pointer=content;
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
int HL7DSCSegment::get_field(const unsigned int no,String &content) const{
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
		if((!_continuation_pointer.IsEmpty())&&
			(0==get_continuation_pointer_with_number())){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_continuation_pointer;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-3);
	}
}