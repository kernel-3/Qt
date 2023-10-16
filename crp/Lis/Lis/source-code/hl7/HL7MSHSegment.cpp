#include"stdafx.h"
#include"HL7MSHSegment.h"
#include"../tool/DataConverter.h"

//初始化全局变量。
const String HL7MSHSegment::SegmentName(Text("MSH"));

/**
 * name: HL7MSHSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7MSHSegment::HL7MSHSegment(void)
	:HL7Segment(SegmentName,20)
	,_separator(Text("^~\\&"))
	,_sending_application(Text(""))
	,_sending_facility(Text(""))
	,_receiving_application(Text(""))
	,_receiving_facility(Text(""))
	,_message_date_time(Text(""))
	,_message_type(Text(""))
	,_message_control_id(Text(""))
	,_processing_id(Text("P"))
	,_version_id(Text("2.3.1"))
	,_accept_acknowledgment_type(Text(""))
	,_application_acknowledgment_type(Text(""))
	,_character_set(Text("ASCII")){
}

/**
 * name: ~HL7MSHSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7MSHSegment::~HL7MSHSegment(void){
}

/**
 * name: get_separator
 * brief: 获取当前“段”的分隔符。
 * param: --
 * return: 返回当前“段”的分隔符。
 */
const String &HL7MSHSegment::get_separator() const{
	return(_separator);
}

/**
 * name: set_sending_application
 * brief: 设置发送端程序。
 * param: sending_application - 发送端程序。
 * return: --
 */
void HL7MSHSegment::set_sending_application(const String &sending_application){
	_sending_application=sending_application;
}

/**
 * name: get_sending_application
 * brief: 获取发送端程序。
 * param: --
 * return: 返回发送端程序。
 */
const String &HL7MSHSegment::get_sending_application() const{
	return(_sending_application);
}

/**
 * name: set_sending_facility
 * brief: 设置发送端设备。
 * param: sending_facility - 发送端设备。
 * return: --
 */
void HL7MSHSegment::set_sending_facility(const String &sending_facility){
	_sending_facility=sending_facility;
}

/**
 * name: get_sending_facility
 * brief: 获取发送端设备。
 * param: --
 * return: 返回发送端设备。
 */
const String &HL7MSHSegment::get_sending_facility() const{
	return(_sending_facility);
}

/**
 * name: set_receiving_application
 * brief: 设置接收端程序。
 * param: receiving_application - 接收端程序。
 * return: --
 */
void HL7MSHSegment::set_receiving_application(const String &receiving_application){
	_receiving_application=receiving_application;
}

/**
 * name: get_receiving_application
 * brief: 获取接收端程序。
 * param: --
 * return: 返回接收端程序。
 */
const String &HL7MSHSegment::get_receiving_application() const{
	return(_receiving_application);
}

/**
 * name: set_receiving_facility
 * brief: 设置接收端设备。
 * param: receiving_facility - 接收端设备。
 * return: --
 */
void HL7MSHSegment::set_receiving_facility(const String &receiving_facility){
	_receiving_facility=receiving_facility;
}

/**
 * name: get_receiving_facility
 * brief: 获取接收端设备。
 * param: --
 * return: 返回接收端设备。
 */
const String &HL7MSHSegment::get_receiving_facility() const{
	return(_receiving_facility);
}

/**
 * name: set_message_date_time
 * brief: 设置消息的日期时间。
 * param: message_date_time - 消息的日期时间。
 * return: --
 */
void HL7MSHSegment::set_message_date_time(const String &message_date_time){
	_message_date_time=message_date_time;
}

/**
 * name: get_message_date_time
 * brief: 获取消息的日期时间。
 * param: --
 * return: 返回消息的日期时间。
 */
const String &HL7MSHSegment::get_message_date_time() const{
	return(_message_date_time);
}

/**
 * name: set_message_type
 * brief: 设置消息类型。
 * param: message_type - 消息类型。
 * return: --
 */
void HL7MSHSegment::set_message_type(const String &message_type){
	_message_type=message_type;
}

/**
 * name: get_message_type
 * brief: 获取消息类型。
 * param: --
 * return: 返回消息类型。
 */
const String &HL7MSHSegment::get_message_type() const{
	return(_message_type);
}

/**
 * name: set_message_control_id
 * brief: 设置消息控制ID。
 * param: message_control_id - 消息控制ID。
 * return: --
 */
void HL7MSHSegment::set_message_control_id(const String &message_control_id){
	_message_control_id=message_control_id;
}

/**
 * name: get_message_control_id
 * brief: 获取消息控制ID。
 * param: --
 * return: 返回消息控制ID。
 */
const String &HL7MSHSegment::get_message_control_id() const{
	return(_message_control_id);
}

/**
 * name: get_processing_id
 * brief: 获取处理ID。
 * param: --
 * return: 返回处理ID。
 */
const String &HL7MSHSegment::get_processing_id() const{
	return(_processing_id);
}

/**
 * name: get_version_id
 * brief: 获取版本ID。
 * param: --
 * return: 返回版本ID。
 */
const String &HL7MSHSegment::get_version_id() const{
	return(_version_id);
}

/**
 * name: set_accept_acknowledgment_type
 * brief: 设置接收应答类型。此类型仅对于 DSR^Q03 消息有效。
 *        取值为 P ，表示 LIS 系统主动发送的样本信息。其他
 *        值表示响应 LIS 查询的样本信息，可置空。
 * param: accept_acknowledgment_type - 接收应答类型。
 * return: --
 */
void HL7MSHSegment::set_accept_acknowledgment_type(
	const String &accept_acknowledgment_type){
	_accept_acknowledgment_type=accept_acknowledgment_type;
}

/**
 * name: get_accept_acknowledgment_type
 * brief: 获取接收应答类型。此类型仅对于 DSR^Q03 消息有效。
 *        取值为 P ，表示 LIS 系统主动发送的样本信息。其他
 *        值表示响应 LIS 查询的样本信息，可置空。
 * param: --
 * return: 返回接收应答类型。
 */
const String &HL7MSHSegment::get_accept_acknowledgment_type() const{
	return(_accept_acknowledgment_type);
}

/**
 * name: set_application_acknowledgment_type
 * brief: 设置应用程序应答类型。此类型作为发送的结果类
 *		  型。1-病人样本测试结果；2-定标结果；3-质控
 *		  结果。
 * param: application_acknowledgment_type - 应用程序应答类型。
 * return: --
 */
void HL7MSHSegment::set_application_acknowledgment_type(
	const String &application_acknowledgment_type){
	_application_acknowledgment_type=application_acknowledgment_type;
}

/**
 * name: get_application_acknowledgment_type
 * brief: 获取应用程序应答类型。此类型作为发送的结果类
 *		  型。1-病人样本测试结果；2-定标结果；3-质控
 *		  结果。
 * param: --
 * return: 返回应用程序应答类型。
 */
const String &HL7MSHSegment::get_application_acknowledgment_type() const{
	return(_application_acknowledgment_type);
}

/**
 * name: set_application_acknowledgment_type_with_number
 * brief: 用数字形式设置应用程序应答类型。此类型作为发送的结果类
 *		  型。1-病人样本测试结果；2-定标结果；3-质控结果。
 * param: application_acknowledgment_type - 应用程序应答类型。
 * return: --
 */
void HL7MSHSegment::set_application_acknowledgment_type_with_number(
	const unsigned int application_acknowledgment_type){
	_application_acknowledgment_type=DataConverter::to_string(
		application_acknowledgment_type);
}

/**
 * name: get_application_acknowledgment_type_with_number
 * brief: 以数字形式获取应用程序应答类型。此类型作为发送的结果类
 *		  型。1-病人样本测试结果；2-定标结果；3-质控结果。
 * param: --
 * return: 如果函数执行成功返回应用程序应答类型的数字形式，否则返回零。
 */
unsigned int HL7MSHSegment::get_application_acknowledgment_type_with_number() const{
	return(DataConverter::to_unsigned_int(_application_acknowledgment_type));
}

/**
 * name: get_character_set
 * brief: 获取字符集。
 * param: --
 * return: 返回字符集。
 */
const String &HL7MSHSegment::get_character_set() const{
	return(_character_set);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7MSHSegment::set_field(const unsigned int no,const String &content){
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
		//2-1.如果当前设置的第二个“域”合法。
		if(content==_separator){
			return(1);
		}
		//2-2.如果当前设置的第二个“域”不合法。
		else{
			return(-2);
		}
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.设置第三个“域”。
		_sending_application=content;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置第四个“域”。
		_sending_facility=content;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){
		//5-1.设置第五个“域”。
		_receiving_application=content;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望设置“段”的第六个“域”。
	else if(6==no){
		//6-1.设置第六个“域”。
		_receiving_facility=content;
		//6-2.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){
		//7-1.设置第七个“域”。
		_message_date_time=content;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){//忽略。
		return(0);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){
		//9-1.判断当前准备设置“域”的内容是否合法。
		if(content.IsEmpty()){//如果当前内容为空，则直接返回错误。
			return(-3);
		}else /*if(...)*/{//如果内容不合法，则直接返回错误。
			//return(-4);
			//unfinished.
		}
		//9-2.设置第九个“域”。
		_message_type=content;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//10-1.判断当前准备设置“域”的内容是否合法。
		if(content.IsEmpty()){
			return(-5);
		}
		//10-2.设置第十个“域”。
		_message_control_id=content;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望设置“段”的第十一个“域”。
	else if(11==no){
		//11-1.如果当前设置的第十一个“域”合法。
		if(_processing_id==content){
			return(1);
		}
		//11-2.如果当前设置的第十一个“域”不合法。
		else{
			return(-6);
		}
	}
	//12.如果当前期望设置“段”的第十二个“域”。
	else if(12==no){
		//12-1.如果当前设置的第十二个“域”合法。
		if(_version_id==content){
			return(1);
		}
		//12-2.如果当前设置的第十二个“域”不合法。
		else{
			return(-7);
		}
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){//忽略。
		return(0);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){
		//15-1.设置第十五个“域”。
		_accept_acknowledgment_type=content;
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){
		//16-1.如果当前准备设置“域”的内容不合法。
		if((!content.IsEmpty())&&(Text("0")!=content)&&
			(Text("1")!=content)&&(Text("2")!=content)){
			return(-8);
		}
		//16-2.设置第十六个“域”。
		_application_acknowledgment_type=content;
		//16-3.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){
		/*
		//18-1.如果当前准备设置“域”的内容不合法。
		if(_character_set!=content){
			return(-9);
		}
		//18-2.程序运行到此成功返回。
		else{*/
		return(1);
		/*}*/
	}
	//19.如果当前期望设置“段”的第十九个“域”。
	else if(19==no){//忽略。
		return(0);
	}
	//20.如果当前期望设置“段”的第二十个“域”。
	else if(20==no){//忽略。
		return(0);
	}
	//21.如果当前设置为的其它“域”，则直接返回错误。
	else{
		return(-9);
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
int HL7MSHSegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.获取当前“域”的内容。
		content=_separator;
		//2-2.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.获取当前“域”的内容。
		content=_sending_application;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_sending_facility;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){
		//5-1.获取当前“域”的内容。
		content=_receiving_application;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){
		//6-1.获取当前“域”的内容。
		content=_receiving_facility;
		//6-2.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){
		//7-1.获取当前“域”的内容。
		content=_message_date_time;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){//忽略。
		return(0);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){
		//9-1.判断当前“域”的内容是否合法。
		if(_message_type.IsEmpty()){//如果当前内容为空，则直接返回错误。
			return(-2);
		}else/*if(...)*/{//如果内容不合法，则直接返回错误。
			//return(-3);
			//unfinished.
		}
		//9-2.获取当前“域”的内容。
		content=_message_type;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//10-1.判断当前“域”的内容是否合法。
		if(_message_control_id.IsEmpty()){
			return(-4);
		}
		//10-2.获取当前“域”的内容。
		content=_message_control_id;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){
		//11-1.获取当前“域”的内容。
		content=_processing_id;
		//11-2.程序运行到此成功返回。
		return(1);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){
		//12-1.获取当前“域”的内容。
		content=_version_id;
		//12-2.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){//忽略。
		return(0);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){
		//15-1.获取当前“域”的内容。
		content=_accept_acknowledgment_type;
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){
		//16-1.判断当前“域”的内容是否合法。
		if((!_application_acknowledgment_type.IsEmpty())&&
			(Text("0")!=_application_acknowledgment_type)&&
			(Text("1")!=_application_acknowledgment_type)&&
			(Text("2")!=_application_acknowledgment_type)){
			return(-5);
		}
		//16-2.获取当前“域”的内容。
		content=_application_acknowledgment_type;
		//16-3.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){
		//18-1.获取当前“域”的内容。
		content=_character_set;
		//18-2.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望获取“段”的第十九个“域”。
	else if(19==no){//忽略。
		return(0);
	}
	//20.如果当前期望获取“段”的第二十个“域”。
	else if(20==no){//忽略。
		return(0);
	}
	//21.程序运行到此，直接返回错误。。
	else{
		return(-6);
	}
}