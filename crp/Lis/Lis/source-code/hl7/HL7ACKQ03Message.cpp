#include"stdafx.h"
#include"HL7ACKQ03Message.h"
#include"HL7MSASegment.h"
#include"HL7ERRSegment.h"

/**
 * name: HL7ACKQ03Message
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7ACKQ03Message::HL7ACKQ03Message(void)
	:HL7Message(){
}

/**
 * name: ~HL7ACKQ03Message
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7ACKQ03Message::~HL7ACKQ03Message(void){
}

/**
 * name: are_segments_available
 * brief: 判断当前消息中所有的段信息是否有效。
 * param: --
 * return: 如果当前消息中所有的段信息均合法则返回值大于等于零，否则返回值小于零。
 */
int HL7ACKQ03Message::are_segments_available() const{
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(HL7Message::are_segments_available()<0){
		return(-1);
	}
	//2.判断当前消息第二个段是否有效合法。
	//2-1.获取当前消息的第二个段。
	PtrToCSegment segment=get_segment(2);
	if(!static_cast<bool>(segment)){
		return(-2);
	}
	//2-2.判断当前消息的第二个段是否为MSA段。
	if(HL7MSASegment::SegmentName!=segment->get_name()){
		return(-3);
	}
	//3.判断当前消息第三个段是否有效合法。
	//3-1.获取当前消息的第三个段。
	segment=get_segment(3);
	if(!static_cast<bool>(segment)){
		return(-4);
	}
	//3-2.判断当前消息的第三个段是否为ERR段。
	if(HL7ERRSegment::SegmentName!=segment->get_name()){
		return(-5);
	}
	//4.判断当前消息中段的数量是否合法。
	if(3!=size_of_segments()){
		return(-6);
	}
	//5.程序运行到此成功返回。
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
int HL7ACKQ03Message::set_segment(const unsigned int no,const String &content){
	//1.调用基类相应处理函数,并且判断处理是否完成。
	//1-1.调用基类相应处理函数，并且记录处理结果。
	const int execute_result=HL7Message::set_segment(no,content);
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
		PtrToSegment segment(new HL7MSASegment);
		if(!static_cast<bool>(segment)){
			return(-2);
		}
		//2-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7MSASegment*>(
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
		//3-1.创建第二个段实例。
		PtrToSegment segment(new HL7ERRSegment);
		if(!static_cast<bool>(segment)){
			return(-5);
		}
		//3-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7ERRSegment*>(
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
	//4.如果当前设置的段为其它情况，则直接返回错误。
	else{
		return(-8);
	}
}