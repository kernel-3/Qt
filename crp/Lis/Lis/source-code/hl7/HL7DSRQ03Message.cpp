#include"stdafx.h"
#include"HL7DSRQ03Message.h"
#include"HL7MSASegment.h"
#include"HL7ERRSegment.h"
#include"HL7QAKSegment.h"
#include"HL7QRDSegment.h"
#include"HL7QRFSegment.h"
#include"HL7DSPSegment.h"
#include"HL7DSCSegment.h"

/**
 * name: HL7DSRQ03Message
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7DSRQ03Message::HL7DSRQ03Message(void)
	:HL7Message(){
}

/**
 * name: ~HL7DSRQ03Message
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7DSRQ03Message::~HL7DSRQ03Message(void){
}

/**
 * name: are_segments_available
 * brief: 判断当前消息中所有的段信息是否有效。
 * param: --
 * return: 如果当前消息中所有的段信息均合法则返回值大于等于零，否则返回值小于零。
 */
int HL7DSRQ03Message::are_segments_available() const{
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
	//2-2.判断当前消息的第二个段是否为PID段。
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
	//4.判断当前消息第四个段是否有效合法。
	//4-1.获取当前消息的第四个段。
	segment=get_segment(4);
	if(!static_cast<bool>(segment)){
		return(-6);
	}
	//4-2.判断当前消息的第四个段是否为QAK段。
	if(HL7QAKSegment::SegmentName!=segment->get_name()){
		return(-7);
	}
	//5.判断当前消息第五个段是否有效合法。
	//5-1.获取当前消息的第五个段。
	segment=get_segment(5);
	if(!static_cast<bool>(segment)){
		return(-8);
	}
	//5-2.判断当前消息的第四个段是否为QRD段。
	if(HL7QRDSegment::SegmentName!=segment->get_name()){
		return(-9);
	}
	//6.判断当前消息第六个段是否有效合法。
	//6-1.获取当前消息的第六个段。
	segment=get_segment(6);
	if(!static_cast<bool>(segment)){
		return(-10);
	}
	//6-2.判断当前消息的第六个段是否为QRF段。
	if(HL7QRFSegment::SegmentName!=segment->get_name()){
		return(-11);
	}
	//7~37.判断当前消息的第七个段至第三十七个段是否合法有效。
	for(unsigned int no=7;no<=37;++no){
		//7~37-1.获取当前消息的第no个段。
		segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(-12);
		}
		//7~37-2.判断当前消息的第no个段是否为DSP段。
		if(HL7DSPSegment::SegmentName!=segment->get_name()){
			return(-13);
		}
	}
	//38.判断当前消息的第三十八个段是否合法有效。
	//38-1.获取当前消息的第三十八个段。
	segment=get_segment(38);
	if(!static_cast<bool>(segment)){
		return(-14);
	}
	//38-2.判断当前消息的第三十八个段是否为DSC段。
	if(HL7DSCSegment::SegmentName!=segment->get_name()){
		return(-15);
	}
	//39.判断当前消息中段的数量是否合法。
	if(38!=size_of_segments()){
		return(-16);
	}
	//40.程序运行到此成功返回。
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
int HL7DSRQ03Message::set_segment(const unsigned int no,const String &content){
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
		//3-1.创建第三个段实例。
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
	//4.如果当前期望设置第四个段的内容。
	else if(4==no){
		//4-1.创建第四个段实例。
		PtrToSegment segment(new HL7QAKSegment);
		if(!static_cast<bool>(segment)){
			return(-8);
		}
		//4-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7QAKSegment*>(
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
	//5.如果当前期望设置第五个段的内容。
	else if(5==no){
		//5-1.创建第五个段实例。
		PtrToSegment segment(new HL7QRDSegment);
		if(!static_cast<bool>(segment)){
			return(-11);
		}
		//5-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7QRDSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-12);
		}
		//5-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-13);
		}
		//5-4.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望设置第六个段的内容。
	else if(6==no){
		//6-1.创建第六个段实例。
		PtrToSegment segment(new HL7QRFSegment);
		if(!static_cast<bool>(segment)){
			return(-14);
		}
		//6-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7QRFSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-15);
		}
		//6-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-16);
		}
		//6-4.程序运行到此成功返回。
		return(1);
	}
	//7~37.如果当前期望设置第七到第三十七个段的内容。
	else if((no>=7)&&(no<=37)){
		//7-1.创建第no个段实例。
		PtrToSegment segment(new HL7DSPSegment);
		if(!static_cast<bool>(segment)){
			return(-17);
		}
		//7-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7DSPSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-18);
		}
		//7-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-19);
		}
		//7-4.程序运行到此成功返回。
		return(1);
	}
	//38.如果当前期望设置第三十八个段的内容。
	else if(38==no){
		//38-1.创建第三十八个段实例。
		PtrToSegment segment(new HL7DSCSegment);
		if(!static_cast<bool>(segment)){
			return(-20);
		}
		//38-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7DSCSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-21);
		}
		//38-3.将当前段插入到当前消息中。
		if(add_segment(segment)<0){
			return(-22);
		}
		//38-4.程序运行到此成功返回。
		return(1);
	}
	//39.如果当前设置的段为其它情况，则直接返回错误。
	else{
		return(-23);
	}
}