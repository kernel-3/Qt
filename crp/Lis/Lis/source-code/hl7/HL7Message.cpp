#include"stdafx.h"
#include"HL7Message.h"
#include"HL7Segment.h"
#include"HL7MSHSegment.h"

//初始化类中静态变量。
const Char HL7Message::START_CHARACTER=0x0B;
const Char HL7Message::FIRST_END_CHARACTER=0x1C;
const Char HL7Message::SECOND_END_CHARACTER=0x0D;

/**
 * name: HL7Message
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7Message::HL7Message(void)
	:_segments(){
}

/**
 * name: ~HL7Message
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7Message::~HL7Message(void){
}

/**
 * name: add_segment
 * breif: 向消息中添加一个“段”。
 * param: segment - 指向一个“段”。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7Message::add_segment(PtrToSegment &segment){
	//1.如果当前传递参数不合法。
	if(!static_cast<bool>(segment)){
		return(-1);
	}
	//2.将当前段插入指定的“段”容器中。
	_segments.push_back(segment);
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: size_of_segments
 * brief: 当前消息中存储“段”的个数。
 * param: --
 * return: 返回消息中存储“段”的个数。
 */
unsigned int HL7Message::size_of_segments() const{
	return(_segments.size());
}

/**
 * name: clear_segments
 * breif:  清理消息中存储的“段”的个数。
 * param: --
 * return: --
 */
void HL7Message::clear_segments(){
	_segments.clear();
}

/**
 * name: get_segment
 * brief: 获取指定的“段”信息。
 * param: no - “段”编号（注意，此编号从1开始）。
 * return: 如果函数执行成功返回指向“段”的智能指针，否则返回空的智能指针。
 */
HL7Message::PtrToCSegment HL7Message::get_segment(
	const unsigned int no) const{
	if((no<1)||(no>_segments.size())){
		return(PtrToCSegment());
	}else{
		return(_segments[no-1]);
	}
}

/**
 * name: from_hl7
 * breif: 根据指定的HL7“消息”语句，生成“消息”类中的相关数据。
 * param: hl7 - HL7“消息”字符串。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7Message::from_hl7(const String &hl7){
	//1.判断当前传递参数是否合法。
	const int size=hl7.GetLength();
	if(size<3){
		return(-1);
	}else if((START_CHARACTER!=hl7[0])||
		(FIRST_END_CHARACTER!=hl7[hl7.GetLength()-2])||
		(SECOND_END_CHARACTER!=hl7[hl7.GetLength()-1])){
		return(-2);
	}
	//2.解析HL7“消息”语句，并且提取“消息”语句中的“段”信息，并为当前“消息”生成“段”的相应实例。
	//2-1.声明当前操作所需变量。
	int start_index=1;
	int end_index=0;
	unsigned int segment_no=0;
	//2-2.遍历当前HL7“消息”语句并提取“段”信息，创建相应的“段”实例，最后判断操作是否成功。
	while(true){
		//2-2-1.计算“段”信息在当前字符串中的位置。
		end_index=hl7.Find(HL7Segment::END_CHARACTER,start_index);
		//2-2-2.如果计算“域”的结束位失败，则直接返回错误。
		if((end_index<0)||(end_index<start_index)){
			return(-3);
		}
		//2-2-3.提取“段”信息字符串。
		const String segment_content=hl7.Mid(
			start_index,end_index-start_index+1);
		//2-2-4.如果当前字符串已经分析完成。
		if(size-1==end_index){
			if((2!=segment_content.GetLength())||
				(FIRST_END_CHARACTER!=segment_content[0])||
				(SECOND_END_CHARACTER!=segment_content[1])){
				return(-4);
			}else{
				break;
			}
		}
		//2-2-5.自增“段”号。
		++segment_no;
		//2-2-6.为当前“消息”设置“段”，并且判断设置是否成功。
		if(set_segment(segment_no,segment_content)<0){
			return(-5);
		}
		//2-2-7.重置提取起始位，准备进行下一次的“段”信息提取。
		start_index=end_index+1;
	}
	//3.判断当前消息中存储的段信息是否有效。
	if(are_segments_available()<0){
		return(-6);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: to_hl7
 * brief: 将当前消息转化成HL7字符串。
 * param: --
 * return: 如果转换成功返回转化后的HL7字符串，否则返回空字符串。
 */
String HL7Message::to_hl7() const{
	//1.获取当前消息中存储的段信息数量，并且判断获取是否成功。
	const unsigned int size=size_of_segments();
	if(size<=0){
		return(Text(""));
	}
	//2.如果当前消息中存储的段信息不合法，则直接返回错误。
	if(are_segments_available()<0){
		return(Text(""));
	}
	//3.声明记录转化后消息HL7字符串的变量。
	String message_hl7(Text(""));
	message_hl7+=START_CHARACTER;
	//4.遍历当前消息中的段信息，并且获取段信息的HL7语句。
	for(unsigned int no=1;no<=size;++no){
		//4-1.获取当前段信息，并且判断获取是否成功。
		PtrToCSegment segment=get_segment(no);
		if(!static_cast<bool>(segment)){
			return(Text(""));
		}
		//4-2.获取当前段的HL7语句，并且判断获取是否成功。
		const String segment_hl7=segment->to_hl7();
		if(segment_hl7.IsEmpty()){
			return(Text(""));
		}
		//4-3.将当前段的HL7语句添加到消息HL7语句中。
		message_hl7+=segment_hl7;
	}
	//5.为当前消息HL7字符串添加消息结束符。
	message_hl7+=FIRST_END_CHARACTER;
	message_hl7+=SECOND_END_CHARACTER;
	//6.程序运行到此直接返回消息HL7字符串。
	return(message_hl7);
}

/**
 * name: are_segments_available
 * brief: 判断当前消息中所有的段信息是否有效。
 * param: --
 * return: 如果当前消息中所有的段信息均合法则返回值大于等于零，否则返回值小于零。
 */
int HL7Message::are_segments_available() const{
	//1.获取当前消息中第一个段。
	PtrToCSegment segment=get_segment(1);
	if(!static_cast<bool>(segment)){
		return(-1);
	}
	//2.判断当前消息中第一个段是否为MSH段（所有消息中，第一个段一定为MSH段）。
	if(HL7MSHSegment::SegmentName!=segment->get_name()){
		return(-2);
	}
	//3.程序运行到此成功返回。
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
int HL7Message::set_segment(const unsigned int no,const String &content){
	//1.如果当前“段”号为一。
	if(1==no){
		//1-1.创建第一个段实例（HL7消息中，第一个段均为MSH段）。
		PtrToSegment segment(new HL7MSHSegment);
		//1-2.判断第一个段实例创建是否成功。
		if(!static_cast<bool>(segment)){
			return(-1);
		}
		//1-2.根据当前段的内容，为指定段生成相关数据。
		if(dynamic_cast<HL7MSHSegment*>(
			segment.get())->from_hl7(content)<0){
			return(-2);
		}
		//1-3.将生成的段，加入到当前消息中。
		if(add_segment(segment)<0){
			return(-3);
		}
		//1-4.程序运行到此成功返回。
		return(1);
	}
	//2.如果当前段号大于一。
	else if(no>1){//忽略。
		return(0);
	}
	//3.如果当前段号为其它异常情况。
	else{
		return(-4);
	}
}