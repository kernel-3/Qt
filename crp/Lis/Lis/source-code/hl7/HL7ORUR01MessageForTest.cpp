#include"stdafx.h"
#include"HL7ORUR01MessageForTest.h"
#include"HL7PIDSegment.h"
#include"HL7OBRSegment.h"
#include"HL7OBRSegmentForTest.h"
#include"HL7OBXSegment.h"

/**
 * name: HL7ORUR01MessageForTest
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7ORUR01MessageForTest::HL7ORUR01MessageForTest(void)
	:HL7ORUR01Message(){
}

/**
 * name: ~HL7ORUR01MessageForTest
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7ORUR01MessageForTest::~HL7ORUR01MessageForTest(void){
}

/**
 * name: are_segments_available
 * brief: 判断当前消息中所有的段信息是否有效。
 * param: --
 * return: 如果当前消息中所有的段信息均合法则返回值大于等于零，否则返回值小于零。
 */
int HL7ORUR01MessageForTest::are_segments_available() const{
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(HL7ORUR01Message::are_segments_available()<0){
		return(-1);
	}
	//2.判断当前消息第二个段是否有效合法。
	//2-1.获取当前消息的第二个段。
	PtrToCSegment segment=get_segment(2);
	if(!static_cast<bool>(segment)){
		return(-2);
	}
	//2-2.判断当前消息的第二个段是否为PID段。
	if(HL7PIDSegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.判断当前消息第三个段是否有效合法。
	//3-1.获取当前消息的第三个段。
	segment=get_segment(3);
	if(!static_cast<bool>(segment)){
		return(-4);
	}
	//3-2.判断当前消息的第三个段是否为OBR段。
	if(HL7OBRSegment::SegmentName!=segment->get_name()){
		return(-5);
	}
	//4.判断当前消息第四个段是否有效合法。
	//4-1.获取当前消息的第四个段。
	segment=get_segment(4);
	if(!static_cast<bool>(segment)){
		return(-6);
	}
	//4-2.判断当前消息的第四个段是否为OBX段。
	if(HL7OBXSegment::SegmentName!=segment->get_name()){
		return(-7);
	}
	//5.判断当前消息第五个段到第无穷个段是否为OBX段。
	for(unsigned int no=5;no<=size_of_segments();++no){
		//5-1.获取当前消息的第no个段。
		segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//5-2.判断当前消息的第no个段是否为OBX段。
		if(HL7OBXSegment::SegmentName!=segment->get_name()){
			return(-9);
		}
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_segment
 * brief: 设置当前“消息”的指定“段”。
 * param: no - “段”的编号（注意：从1开始计数）。
 *        content - “段”的内容。
 * return: 如果“段”设置成功返回值大于零，如果忽略“段”的设置则返回零，
 *         如果“段”设置失败返回负数。
 */
int HL7ORUR01MessageForTest::set_segment(const unsigned int no,const String &content){
	//1.调用基类相应处理函数,并且判断处理是否完成。
	//1-1.调用基类相应处理函数，并且记录处理结果。
	const int execute_result=HL7ORUR01Message::set_segment(no,content);
	//1-2.如果基类已经处理完成。
	if(execute_result>0){
		return(1);
	}
	//1-3.如果基类处理失败。
	if(execute_result<0){
		return(-1);
	}
	//2.如果当前期望设置第二个段的内容。
	else if(2==no){
		//2-1.创建第二个段实例。
		PtrToSegment segment(new HL7PIDSegment);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7PIDSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-3);
		}
		//2-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-4);
		}
		//2-4.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置第三个段的内容。
	else if(3==no){
		//3-1.创建第三个段实例。
		PtrToSegment segment(new HL7OBRSegmentForTest);
		if(!static_cast<bool>(segment)){
			return(-5);
		}
		//3-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7OBRSegmentForTest*>(
			segment.get())->from_hl7(content)<0){
			return(-6);
		}
		//3-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-7);
		}
		//3-4.程序运行到此成功返回。
		return(1);
	}
	//4~∞.如果当前期望设置第四个到第∞个段的内容。
	else if(4<=no){
		//4-1.创建第四个到第∞个段实例。
		PtrToSegment segment(new HL7OBXSegment);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//4-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7OBXSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-9);
		}
		//4-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-10);
		}
		//4-4.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前设置的段为其它情况，则直接返回错误。
	else{
		return(-11);
	}
}