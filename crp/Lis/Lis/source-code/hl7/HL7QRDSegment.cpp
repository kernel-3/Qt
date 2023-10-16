#include"stdafx.h"
#include"HL7QRDSegment.h"
#include"../tool/DataConverter.h"

//定义全局变量。
 const String HL7QRDSegment::SegmentName(Text("QRD"));

/**
 * name: HL7QRDSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7QRDSegment::HL7QRDSegment(void)
	:HL7Segment(SegmentName,13)
	,_query_date_time(Text(""))
	,_query_format_code(Text("R"))
	,_query_priority(Text("D"))
	,_query_id(Text(""))
	,_quantity_limited_request(Text("RD"))
	,_specimen_barcode(Text(""))
	,_what_subject_filter(Text("OTH")){
}

/**
 * name: ~HL7QRDSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7QRDSegment::~HL7QRDSegment(void){
}

/**
 * name: set_query_date_time
 * brief: 设置查询产生日期时间。
 * param: query_date_time - 查询日期时间。
 * return: --
 */
void HL7QRDSegment::set_query_date_time(const String &query_date_time){
	_query_date_time=query_date_time;
}

/**
 * name: get_query_date_time
 * brief: 获取查询日期时间。
 * param: --
 * return: 返回查询日期时间。
 */
const String &HL7QRDSegment::get_query_date_time() const{
	return(_query_date_time);
}

/**
 * name: get_query_format_code
 * brief: 获取查询格式代码。
 * param: --
 * return: 返回查询格式代码。
 */
const String &HL7QRDSegment::get_query_format_code() const{
	return(_query_date_time);
}

/**
 * name: get_query_priority
 * brief: 获取查询优先权。
 * param: --
 * return: 返回查询优先权。
 */
const String &HL7QRDSegment::get_query_priority() const{
	return(_query_priority);
}

/**
 * name: set_query_id
 * brief: 设置查询ID。
 * param: query_id - 查询ID。
 * return: --
 */
void HL7QRDSegment::set_query_id(const String &query_id){
	_query_id=query_id;
}

/**
 * name: get_query_id
 * brief: 获取查询ID。
 * param: --
 * return: 返回查询ID。
 */
const String &HL7QRDSegment::get_query_id() const{
	return(_query_id);
}

/**
 * name: get_quantity_limited_request
 * brief: 获取数量限制要求。
 * param: --
 * return: 返回数量限制要求。
 */
const String &HL7QRDSegment::get_quantity_limited_request() const{
	return(_quantity_limited_request);
}

/**
 * name: set_specimen_barcode
 * brief: 设置样本条码。
 * param: specimen_barcode - 样本条码。
 * return: --
 */
void HL7QRDSegment::set_specimen_barcode(const String &specimen_barcode){
	_specimen_barcode=specimen_barcode;
}

/**
 * name: get_specimen_barcode
 * brief: 获取样本条码。
 * param: --
 * return: 返回样本条码。
 */
const String &HL7QRDSegment::get_specimen_barcode() const{
	return(_specimen_barcode);
}

/**
 * name: get_what_subject_filter
 * brief: 获取查询内容过滤符。
 * param: --
 * return: 返回查询内容过滤符。
 */
const String &HL7QRDSegment::get_what_subject_filter() const{
	return(_what_subject_filter);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7QRDSegment::set_field(const unsigned int no,const String &content){
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
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_query_date_time=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备设置“域”的内容不合法。
		if(Text("R")!=content){
			return(-3);
		}
		//3-2.设置当前“域”的内容。
		//_query_format_code=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备设置“域”的内容不合法。
		if(Text("D")!=content){
			return(-4);
		}
		//4-2.设置当前“域”的内容。
		//_query_priority=content;
		//4-3.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){
		//5-1.如果当前准备设置“域”的内容不合法。
		if(content.IsEmpty()){
			return(-5);
		}
		//5-2.设置当前“域”的内容。
		//_query_id=content;
		//5-3.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望设置“段”的第六个“域”。
	else if(6==no){//忽略。
		return(0);
	}
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){//忽略。
		return(0);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){
		//8-1.如果当前准备设置“域”的内容不合法。
		if(Text("RD")!=content){
			return(-6);
		}
		//8-2.设置当前“域”的内容。
		//_quantity_limited_request=content;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){
		//unfinished: 这里是否需要判断条码不为空时必须为数字？？？
		//9-1.设置当前“域”的内容。
		_specimen_barcode=content;
		//9-2.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//10-1.如果当前准备设置“域”的内容不合法。
		if(Text("OTH")!=content){
			return(-7);
		}
		//10-2.设置当前“域”的内容。
		//_what_subject_filter=content;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11~13.如果当前期望设置“段”的第十一个“域”至第十三个“域”。
	else if((no>=11)&&(no<=13)){//忽略。
		return(0);
	}
	//14.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-8);
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
int HL7QRDSegment::get_field(const unsigned int no,String &content) const{
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
		if((!_query_date_time.IsEmpty())&&
			((14!=_query_date_time.GetLength())||
			(!DataConverter::is_number(_query_date_time)))){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_query_date_time;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备获取“域”的内容不合法。
		if(Text("R")!=_query_format_code){
			return(-3);
		}
		//3-2.获取当前“域”的内容。
		content=_query_format_code;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备获取“域”的内容不合法。
		if(Text("D")!=_query_priority){
			return(-4);
		}
		//4-2.获取当前“域”的内容。
		content=_query_priority;
		//4-3.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){
		//5-1.如果当前准备获取“域”的内容不合法。
		if(_query_id.IsEmpty()){
			return(-5);
		}
		//5-2.获取当前“域”的内容。
		content=_query_id;
		//5-3.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){//忽略。
		return(0);
	}
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){//忽略。
		return(0);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){
		//8-1.如果当前准备获取“域”的内容不合法。
		if(Text("RD")!=_quantity_limited_request){
			return(-6);
		}
		//8-2.获取当前“域”的内容。
		content=_quantity_limited_request;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){
		//unfinished: 这里是否需要判断条码不为空时必须为数字？？？
		//9-1.获取当前“域”的内容。
		content=_specimen_barcode;
		//9-2.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//10-1.如果当前准备获取“域”的内容不合法。
		if(Text("OTH")!=_what_subject_filter){
			return(-7);
		}
		//10-2.获取当前“域”的内容。
		content=_what_subject_filter;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11~13.如果当前期望获取“段”的第十一个“域”至第十三个“域”。
	else if((no>=11)&&(no<=13)){//忽略。
		return(0);
	}
	//14.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-8);
	}
}