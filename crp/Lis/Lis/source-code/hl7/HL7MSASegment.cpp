#include"stdafx.h"
#include"HL7MSASegment.h"

//初始化静态变量。
const String HL7MSASegment::SegmentName(Text("MSA"));

/**
 * name: HL7MSASegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7MSASegment::HL7MSASegment(void)
	:HL7Segment(SegmentName,7)
	,_acknowledgment_code(Text(""))
	,_message_control_id(Text(""))
	,_text_message(Text(""))
	,_error_condition(Text("")){
}

/**
 * name: ~HL7MSASegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7MSASegment::~HL7MSASegment(void){
}

/**
 * name: set_acknowledgment_code
 * brief: 设置确认代码。
 * param: acknowledgment_code - 确认代码(AA 表示接受;AE 表示错误；AR 表示拒绝)。
 * return: --
 */
void HL7MSASegment::set_acknowledgment_code(const String &acknowledgment_code){
	_acknowledgment_code=acknowledgment_code;
}

/**
 * name: get_acknowledgment_code
 * brief: 获取确认代码。
 * param: --
 * return: 返回确认代码(AA 表示接受;AE 表示错误；AR 表示拒绝)。
 */
const String &HL7MSASegment::get_acknowledgment_code() const{
	return(_acknowledgment_code);
}

/**
 * name: set_message_control_id
 * brief: 设置消息控制ID。
 * param: message_control_id - 消息控制ID。
 * return: --
 */
void HL7MSASegment::set_message_control_id(const String &message_control_id){
	_message_control_id=message_control_id;
}

/**
 * name: get_message_control_id
 * brief: 获取消息控制ID。
 * param: --
 * return: 返回消息控制ID。
 */
const String &HL7MSASegment::get_message_control_id() const{
	return(_message_control_id);
}

/**
 * name: set_text_message
 * brief: 设置文本消息。
 * param: text_message - 文本消息。 
 * return: --
 */
void HL7MSASegment::set_text_message(const String &text_message){
	_text_message=text_message;
}

/**
 * name: get_text_message
 * brief: 获取文本消息。
 * param: -- 
 * return: 返回文本消息。
 */
const String &HL7MSASegment::get_text_message() const{
	return(_text_message);
}

/**
 * name: set_error_condition
 * brief: 设置错误条件。
 * param: error_condition - 错误条件。
 * return: --
 */
void HL7MSASegment::set_error_condition(const String &error_condition){
	_error_condition=error_condition;
}

/**
 * name: get_error_condition
 * brief: 获取错误条件。
 * param: --
 * return: 返回错误条件。
 */
const String &HL7MSASegment::get_error_condition() const{
	return(_error_condition);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7MSASegment::set_field(const unsigned int no,const String &content){
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
		if((Text("AA")!=content)&&(Text("AE")!=content)&&
			(Text("AR")!=content)){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_acknowledgment_code=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备设置第三个“域”的内容不合法。
		if(content.IsEmpty()){
			return(-3);
		}
		//3-2.设置当前“域”的内容。
		_message_control_id=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置当前“域”的内容。
		_text_message=content;
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
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){
		//7-1.如果当前准备设置第三个“域”的内容不合法。
		if((Text("0")!=content)&&(Text("100")!=content)&&
			(Text("101")!=content)&&(Text("102")!=content)&&
			(Text("103")!=content)&&(Text("200")!=content)&&
			(Text("201")!=content)&&(Text("202")!=content)&&
			(Text("203")!=content)&&(Text("204")!=content)&&
			(Text("205")!=content)&&(Text("206")!=content)&&
			(Text("207")!=content)){
			return(-4);
		}
		//7-2.设置当前“域”的内容。
		_error_condition=content;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-5);
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
int HL7MSASegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.如果当前“域”的内容不合法。
		if((Text("AA")!=_acknowledgment_code)&&
			(Text("AE")!=_acknowledgment_code)&&
			(Text("AR")!=_acknowledgment_code)){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_acknowledgment_code;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前“域”的内容不合法。
		if(_message_control_id.IsEmpty()){
			return(-3);
		}
		//3-2.获取当前“域”的内容。
		content=_message_control_id;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_text_message;
		//4-5.程序运行到此成功返回。
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
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){
		//7-1.如果当前准备获取第七个“域”的内容不合法。
		if((Text("0")!=_error_condition)&&(Text("100")!=_error_condition)&&
			(Text("101")!=_error_condition)&&(Text("102")!=_error_condition)&&
			(Text("103")!=_error_condition)&&(Text("200")!=_error_condition)&&
			(Text("201")!=_error_condition)&&(Text("202")!=_error_condition)&&
			(Text("203")!=_error_condition)&&(Text("204")!=_error_condition)&&
			(Text("205")!=_error_condition)&&(Text("206")!=_error_condition)&&
			(Text("207")!=_error_condition)){
			return(-4);
		}
		//7-2.获取当前“域”的内容。
		content=_error_condition;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前获取的为其它“域”，则返回错误。
	else{
		return(-5);
	}
}