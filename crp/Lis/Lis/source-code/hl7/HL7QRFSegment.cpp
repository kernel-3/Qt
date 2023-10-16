#include"stdafx.h"
#include"HL7QRFSegment.h"
#include"../tool/DataConverter.h"

//初始化静态变量。
const String HL7QRFSegment::SegmentName(Text("QRF"));

/**
 * name: HL7QRDSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7QRFSegment::HL7QRFSegment(void)
	:HL7Segment(SegmentName,10)
	,_facility_model(Text(""))
	,_specimen_receipt_start_date_time(Text(""))
	,_specimen_receipt_end_date_time(Text(""))
	,_target_type(Text("RCT"))
	,_target_status(Text("COR"))
	,_date_Time_selection_qualifier(Text("ALL")){
}

/**
 * name: ~HL7QRDSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7QRFSegment::~HL7QRFSegment(void){
}

/**
 * name: set_facility_model
 * brief: 设置设备型号。
 * param: facility_model - 设备型号。
 * return: --
 */
void HL7QRFSegment::set_facility_model(const String &facility_model){
	_facility_model=facility_model;
}

/**
 * name: get_facility_model
 * brief: 获取设备型号。
 * param: --
 * return: 返回设备型号。
 */
const String &HL7QRFSegment::get_facility_model() const{
	return(_facility_model);
}

/**
 * name: set_specimen_receipt_start_date_time
 * brief: 设置查询时的样本接收时间之始。
 * param: specimen_receipt_start_date_time - 查询时的样本接收时间之始。
 * return: --
 */
void HL7QRFSegment::set_specimen_receipt_start_date_time(
	const String &specimen_receipt_start_date_time){
	_specimen_receipt_start_date_time=specimen_receipt_start_date_time;
}

/**
 * name: get_specimen_receipt_start_date_time
 * breif: 获取查询时的样本接收时间之始。
 * param: --
 * return: 返回查询时的样本接收时间之始。 
 */
const String &HL7QRFSegment::get_specimen_receipt_start_date_time() const{
	return(_specimen_receipt_start_date_time);
}

/**
 * name: set_specimen_receipt_end_date_time
 * brief: 设置查询时的样本接收时间之末。
 * param: specimen_receipt_end_date_time - 查询时的样本接收时间之末。
 * return: --
 */
void HL7QRFSegment::set_specimen_receipt_end_date_time(
	const String &specimen_receipt_end_date_time){
	_specimen_receipt_end_date_time=specimen_receipt_end_date_time;
}

/**
 * name: get_specimen_receipt_end_date_time
 * brief: 获取查询时的样本接收时间之末。
 * param: --
 * return: 返回查询时的样本接收时间之末。
 */
const String &HL7QRFSegment::get_specimen_receipt_end_date_time() const{
	return(_specimen_receipt_end_date_time);
}

/**
 * name: get_target_type
 * brief: 获取目标类型。
 * param: --
 * return: 返回目标类型。
 */
const String &HL7QRFSegment::get_target_type() const{
	return(_target_type);
}

/**
 * name: get_target_status
 * brief: 获取目标状态。
 * param: --
 * return: 返回目标状态。
 */
const String &HL7QRFSegment::get_target_status() const{
	return(_target_status);
}

/**
 * name: get_date_Time_selection_qualifier
 * brief: 获取日期/ 时间选择限定符。
 * param: --
 * return: 返回日期/ 时间选择限定符。
 */
const String &HL7QRFSegment::get_date_Time_selection_qualifier() const{
	return(_date_Time_selection_qualifier);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7QRFSegment::set_field(const unsigned int no,const String &content){
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
		if(content.IsEmpty()){
			return(-2);
		}
		//2-2.设置当前“域”的内容。
		_facility_model=content;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备设置“域”的内容不合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-3);
		}
		//3-2.设置当前“域”的内容。
		_specimen_receipt_start_date_time=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备设置“域”的内容不合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-4);
		}
		//4-2.设置当前“域”的内容。
		_specimen_receipt_end_date_time=content;
		//4-3.程序运行到此成功返回。
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
		//7-1.如果当前准备设置“域”的内容不合法。
		if(Text("RCT")!=content){
			return(-5);
		}
		//7-2.设置当前“域”的内容。
		//_target_type=content;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){
		//8-1.如果当前准备设置“域”的内容不合法。
		if(Text("COR")!=content){
			return(-6);
		}
		//8-2.设置当前“域”的内容。
		//_target_status=content;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备设置“域”的内容不合法。
		if(Text("ALL")!=content){
			return(-7);
		}
		//9-2.设置当前“域”的内容。
		//_date_Time_selection_qualifier=content;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){//忽略。
		return(0);
	}
	//11.如果当前设置为的其它“域”，则返回错误。
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
int HL7QRFSegment::get_field(const unsigned int no,String &content) const{
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
		if(_facility_model.IsEmpty()){
			return(-2);
		}
		//2-2.获取当前“域”的内容。
		content=_facility_model;
		//2-3.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.如果当前准备获取“域”的内容不合法。
		if((!_specimen_receipt_start_date_time.IsEmpty())&&
			((14!=_specimen_receipt_start_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_receipt_start_date_time)))){
			return(-3);
		}
		//3-2.获取当前“域”的内容。
		content=_specimen_receipt_start_date_time;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备获取“域”的内容不合法。
		if((!_specimen_receipt_end_date_time.IsEmpty())&&
			((14!=_specimen_receipt_end_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_receipt_end_date_time)))){
			return(-4);
		}
		//4-2.获取当前“域”的内容。
		content=_specimen_receipt_end_date_time;
		//4-3.程序运行到此成功返回。
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
		//7-1.如果当前准备获取“域”的内容不合法。
		if(Text("RCT")!=_target_type){
			return(-5);
		}
		//7-2.获取当前“域”的内容。
		content=_target_type;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){
		//8-1.如果当前准备获取“域”的内容不合法。
		if(Text("COR")!=_target_status){
			return(-6);
		}
		//8-2.获取当前“域”的内容。
		content=_target_status;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备获取“域”的内容不合法。
		if(Text("ALL")!=_date_Time_selection_qualifier){
			return(-7);
		}
		//9-2.获取当前“域”的内容。
		content=_date_Time_selection_qualifier;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){//忽略。
		return(0);
	}
	//11.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-8);
	}
}