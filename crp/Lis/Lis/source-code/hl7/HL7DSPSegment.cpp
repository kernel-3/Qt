#include"stdafx.h"
#include"HL7DSPSegment.h"
#include"../tool/DataConverter.h"

//初始化静态变量。
const String HL7DSPSegment::SegmentName(Text("DSP"));

/**
 * name: HL7DSPSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7DSPSegment::HL7DSPSegment(void)
	:HL7Segment(SegmentName,6)
	,_segment_id(Text(""))
	,_data_content(Text("")){
}

/**
 * name: ~HL7DSPSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7DSPSegment::~HL7DSPSegment(void){
}

/**
 * name: set_segment_id
 * brief: 设置段ID。
 * param: segment_id - 段ID。
 * return: --
 */
void HL7DSPSegment::set_segment_id(const String &segment_id){
	_segment_id=segment_id;
}

/**
 * name: get_segment_id
 * brief: 获取段ID。
 * param: --
 * return: 返回段ID。
 */
const String &HL7DSPSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_segment_id_with_number
 * brief: 以数字形式设置段ID。
 * param: segment_id - 段ID。
 * return: --
 */
void HL7DSPSegment::set_segment_id_with_number(const unsigned int segment_id){
	_segment_id=DataConverter::to_string(segment_id);
}

/**
 * name: get_segment_id_with_number
 * brief: 以数字形式获取段ID。
 * param: --
 * return: 如果函数执行成功返回段ID，否则返回零。
 */
const unsigned int HL7DSPSegment::get_segment_id_with_number() const{
	return(DataConverter::to_unsigned_int(_segment_id));
}

/**
 * name: set_data_content
 * brief: 设置数据内容。
 * param: data_content - 数据内容。
 * return: --
 */
void HL7DSPSegment::set_data_content(const String &data_content){
	_data_content=data_content;
}

/**
 * name: get_data_content
 * brief: 获取数据内容。
 * param: --
 * return: 返回数据内容。
 */
const String &HL7DSPSegment::get_data_content() const{
	return(_data_content);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7DSPSegment::set_field(const unsigned int no,const String &content){
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
		if(0==DataConverter::to_unsigned_int(content)){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_segment_id=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){//忽略。
		return(0);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置当前“域”的内容。
		_data_content=content;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){//忽略。
		return(0);
	}
	//6.如果当前期望设置“段”的第六个“域”。
	else if(6==no){//忽略。
		return(0);
	}
	//7.如果当前设置为的其它“域”，则返回错误。
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
int HL7DSPSegment::get_field(const unsigned int no,String &content) const{
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
		if(0==get_segment_id_with_number()){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_segment_id;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){//忽略。
		return(0);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_data_content;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){//忽略。
		return(0);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){//忽略。
		return(0);
	}
	//7.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-3);
	}
}