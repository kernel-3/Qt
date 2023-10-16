#include"stdafx.h"
#include"HL7OBXSegment.h"
#include"../tool/DataConverter.h"
#include<assert.h>

//初始化全局变量。
const String HL7OBXSegment::SegmentName(Text("OBX"));

/**
 * name: HL7OBXSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7OBXSegment::HL7OBXSegment(void)
	:HL7Segment(SegmentName,18)
	,_segment_id(Text(""))
	,_test_result_type(Text(""))
	,_item_no(Text(""))
	,_item_name(Text(""))
	,_quantitative_test_result(Text(""))
	,_test_result_unit(Text(""))
	/*,_normal_test_result_range[2]*/
	,_abnormal_flags(Text(""))
	,_qualitative_test_result(Text(""))
	,_qualitative_reference_value(Text(""))
	,_test_result_status(Text("F"))
	,_original_test_result(Text(""))
	,_test_date_time(Text(""))
	,_test_department(Text(""))
	,_test_physician(Text("")){
}

/**
 * name: ~HL7OBXSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7OBXSegment::~HL7OBXSegment(void){
}

/**
 * name: set_segment_id
 * brief: 设置段ID。
 * param: segment_id - 段ID。
 * return: --
 */
void HL7OBXSegment::set_segment_id(const String &segment_id){
	_segment_id=segment_id;
}

/**
 * name: get_segment_id
 * brief: 获取段ID。
 * param: --
 * return: 返回段ID。
 */
const String &HL7OBXSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_segment_id_with_number
 * brief: 以数字形式设置段ID。
 * param: segment_id - 段ID。
 * return: --
 */
void HL7OBXSegment::set_segment_id_with_number(const unsigned int segment_id){
	_segment_id=DataConverter::to_string(segment_id);
}

/**
 * name: get_segment_id_with_number
 * brief: 以数字形式获取段ID。
 * param: --
 * return: 如果函数执行成功返回段ID，否则返回零。
 */
const unsigned int HL7OBXSegment::get_segment_id_with_number() const{
	return(DataConverter::to_unsigned_int(_segment_id));
}

/**
 * name: set_test_result_type
 * brief: 设置测试结果类型。
 * param: test_result_type - 测试结果类型。
 * return: --
 */
void HL7OBXSegment::set_test_result_type(const String &test_result_type){
	_test_result_type=test_result_type;
}

/**
 * name: get_test_result_type
 * brief: 获取测试结果类型。
 * param: --
 * return: 返回测试结果类型。
 */
const String &HL7OBXSegment::get_test_result_type() const{
	return(_test_result_type);
}

/**
 * name: set_item_no
 * brief: 设置项目编号。
 * param: item_no - 项目编号。
 * return: --
 */
void HL7OBXSegment::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: 获取项目编号。
 * param: --
 * return: 返回项目编号。
 */
const String &HL7OBXSegment::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: 设置项目名称。
 * param: item_name - 项目名称。
 * return: --
 */
void HL7OBXSegment::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: 获取项目名称。
 * param: --
 * return: 返回项目名称。
 */
const String &HL7OBXSegment::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_quantitative_test_result
 * brief: 设置定量的测试结果。
 * param: quantitative_test_result - 定量的测试结果。
 * return: --
 */
void HL7OBXSegment::set_quantitative_test_result(const String &quantitative_test_result){
	_quantitative_test_result=quantitative_test_result;
}

/**
 * name: get_quantitative_test_result
 * brief: 获取定量的测试结果。
 * param: --
 * return: 返回定量的测试结果。
 */
const String &HL7OBXSegment::get_quantitative_test_result() const{
	return(_quantitative_test_result);
}

/**
 * name: set_test_result_unit
 * brief: 设置错误结果单位。
 * param: test_result_unit - 测试结果单位。
 * return: --
 */
void HL7OBXSegment::set_test_result_unit(const String &test_result_unit){
	_test_result_unit=test_result_unit;
}

/**
 * name: get_test_result_unit
 * brief: 获取测试结果单位。
 * param: --
 * return: 返回错误结果单位。
 */
const String &HL7OBXSegment::get_test_result_unit() const{
	return(_test_result_unit);
}

/**
 * name: set_normal_test_result_range
 * brief: 设置正常测试结果范围。
 * param: index - 索引编号。
 *        normal_test_result_range - 正常测试结果范围。
 * return: --
 */
void HL7OBXSegment::set_normal_test_result_range(
	const unsigned int index,const String &normal_test_result_range){
	assert((index>=0)&&(index<2));
	_normal_test_result_range[index]=normal_test_result_range;
}

/**
 * name: get_normal_test_result_range
 * brief: 获取正常测试结果范围。
 * param: --
 * return: 返回正常测试结果范围。
 */
const String &HL7OBXSegment::get_normal_test_result_range(
	const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_normal_test_result_range[index]);
}

/**
 * name: set_abnormal_flags
 * brief: 设置异常标志。
 * param: abnormal_flags - 异常标志。
 * return: --
 */
void HL7OBXSegment::set_abnormal_flags(const String &abnormal_flags){
	_abnormal_flags=abnormal_flags;
}

/**
 * name: get_abnormal_flags
 * brief: 获取异常标志。
 * param: --
 * return: 返回异常标志。
 */
const String &HL7OBXSegment::get_abnormal_flags() const{
	return(_abnormal_flags);
}

/**
 * name: set_qualitative_test_result
 * brief: 设置定性测试结果。
 * param: qualitative_test_result - 定性测试结果。
 * return: --
 */
void HL7OBXSegment::set_qualitative_test_result(const String &qualitative_test_result){
	_qualitative_test_result=qualitative_test_result;
}

/**
 * name: get_qualitative_test_result
 * brief: 获取定性测试结果。
 * param: --
 * return: 返回定性测试结果。
 */
const String &HL7OBXSegment::get_qualitative_test_result() const{
	return(_qualitative_test_result);
}

/**
 * name: set_qualitative_reference_value
 * brief: 设置定性参考值。
 * param: qualitative_reference_value - 定性参考值。
 * return: --
 */
void HL7OBXSegment::set_qualitative_reference_value(const String &qualitative_reference_value){
	_qualitative_reference_value=qualitative_reference_value;
}

/**
 * name: get_qualitative_reference_value
 * brief: 获取定性参考值。
 * param: --
 * return: 返回定性参考值。
 */
const String &HL7OBXSegment::get_qualitative_reference_value() const{
	return(_qualitative_reference_value);
}

/**
 * name: get_test_result_status
 * brief: 获取测试结果状态。
 * param: --
 * return: 返回测试结果状态。
 */
const String &HL7OBXSegment::get_test_result_status() const{
	return(_test_result_status);
}

/**
 * name: set_original_test_result
 * brief: 设置原始测试结果。
 * param: original_test_result - 原始测试结果。
 * return: --
 */
void HL7OBXSegment::set_original_test_result(const String &original_test_result){
	_original_test_result=original_test_result;
}

/**
 * name: get_original_test_result
 * brief: 获取原始测试结果。
 * param: --
 * return: 返回原始测试结果。
 */
const String &HL7OBXSegment::get_original_test_result() const{
	return(_original_test_result);
}

/**
 * name: set_test_date_time
 * brief: 设置测试日期时间。
 * param: test_date_time - 测试日期时间。
 * return: --
 */
void HL7OBXSegment::set_test_date_time(const String &test_date_time){
	_test_date_time=test_date_time;
}

/**
 * name: get_test_date_time
 * brief: 获取测试日期时间。
 * param: --
 * return: 返回测试日期时间。
 */
const String &HL7OBXSegment::get_test_date_time() const{
	return(_test_date_time);
}

/**
 * name: set_test_department
 * brief: 设置检验科室。
 * param: test_department - 检验科室。
 * return: --
 */
void HL7OBXSegment::set_test_department(const String &test_department){
	_test_department=test_department;
}

/**
 * name: get_test_department
 * brief: 获取检验科室。
 * param: --
 * return: 返回检验科室。
 */
const String &HL7OBXSegment::get_test_department() const{
	return(_test_department);
}

/**
 * name: set_test_physician
 * brief: 设置检验医生。
 * param: test_physician - 检验医生。
 * return: --
 */
void HL7OBXSegment::set_test_physician(const String &test_physician){
	_test_physician=test_physician;
}

/**
 * name: get_test_physician
 * breif: 获取检验医生。
 * param: --
 * return: 返回检验医生。
 */
const String &HL7OBXSegment::get_test_physician() const{
	return(_test_physician);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7OBXSegment::set_field(const unsigned int no,const String &content){
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
	else if(3==no){
		//3-1.如果当前准备设置“域”的内容不合法。
		if((Text("NM")!=content)&&(Text("ST")!=content)){
			return(-3);
		}
		//3-2.设置当前“域”的内容。
		_test_result_type=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备设置“域”的内容不合法。
		if(content.IsEmpty()){
			//unfinished: 此处是否需要判断项目编号为数字？？？
			return(-4);
		}
		//4-2.设置当前“域”的内容。
		_item_no=content;
		//4-3.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){
		//5-1.设置当前“域”的内容。
		_item_name=content;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望设置“段”的第六个“域”。
	else if(6==no){
		//6-1.如果当前准备设置“域”的内容不合法。
		if((Text("NM")==_test_result_type)&&
			(content.IsEmpty())){
			//unfinished: 这里是否应该判断当前测试结果类型为定性时，此值一定为空。
			return(-5);
		}
		//6-2.设置当前“域”的内容。
		_quantitative_test_result=content;
		//6-3.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){
		//7-1.设置当前“域”的内容。
		_test_result_unit=content;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){
		//8-1.声明当前操作所需变量。
		String group_content[2];
		//8-2.提取当前准备设置“域”的内容中的“组”内容。
		if(extract_group_content_from_field_content(
			content,group_content,2)<0){
			return(-6);
		}
		//8-3.判断当前“组”的内容是否合法。
		if(!(((group_content[0].IsEmpty())&&(group_content[1].IsEmpty()))||
			((!group_content[0].IsEmpty())&&(!group_content[1].IsEmpty())))){
			//unfinished: 这里是否应该判断范围的大小顺序，以及是否为数字？？？？
			return(-7);
		}
		//8-4.设置当前“域”的内容。
		_normal_test_result_range[0]=group_content[0];
		_normal_test_result_range[1]=group_content[1];
		//8-5.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备设置“域”的内容不合法。
		if((!content.IsEmpty())&&(Text("L")!=content)&&
			(Text("H")!=content)&&(Text("N")!=content)){
			return(-8);
		}
		//9-2.设置当前“域”的内容。
		_abnormal_flags=content;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//10-1.如果当前准备设置“域”的内容不合法。
		if((Text("ST")==_test_result_type)&&
			(content.IsEmpty())){
			return(-9);
		}
		//10-2.设置当前“域”的内容。
		_qualitative_test_result=content;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望设置“段”的第十一个“域”。
	else if(11==no){
		//11-1.设置当前“域”的内容。
		_qualitative_reference_value=content;
		//11-2.程序运行到此成功返回。
		return(1);
	}
	//12.如果当前期望设置“段”的第十二个“域”。
	else if(12==no){
		//12-1.如果当前准备设置“域”的内容不合法。
		if(Text("F")!=content){
			return(-10);
		}
		//12-2.设置当前“域”的内容。
		//_test_result_status=content;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){
		//unfinished: 此处是否需要判断原始结果为必须，以及其值为数字？？？
		//14-1.设置当前“域”的内容。
		_original_test_result=content;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){
		//15-1.如果当前准备设置“域”的内容不合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-11);
		}
		//15-2.设置当前“域”的内容。
		_test_date_time=content;
		//15-3.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){
		//16-1.设置当前“域”的内容。
		_test_department=content;
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){
		//17-1.设置当前“域”的内容。
		_test_physician=content;
		//17-2.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){//忽略。
		return(0);
	}
	//19.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-12);
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
int HL7OBXSegment::get_field(const unsigned int no,String &content) const{
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
	else if(3==no){
		//3-1.如果当前准备获取“域”的内容不合法。
		if((Text("NM")!=_test_result_type)&&
			(Text("ST")!=_test_result_type)){
			return(-3);
		}
		//3-2.获取当前“域”的内容。
		content=_test_result_type;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.如果当前准备获取“域”的内容不合法。
		if(_item_no.IsEmpty()){
			//unfinished: 此处是否需要判断项目编号为数字？？？
			return(-4);
		}
		//4-2.获取当前“域”的内容。
		content=_item_no;
		//4-3.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){
		//5-1.获取当前“域”的内容。
		content=_item_name;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){
		//6-1.如果当前准备获取“域”的内容不合法。
		if((Text("NM")==_test_result_type)&&
			(_quantitative_test_result.IsEmpty())){
			//unfinished: 这里是否应该判断当前测试结果类型为定性时，此值一定为空。
			return(-5);
		}
		//6-2.获取当前“域”的内容。
		content=_quantitative_test_result;
		//6-3.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){
		//7-1.获取当前“域”的内容。
		content=_test_result_unit;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){
		//8-1.如果当前准备获取“域”的内容不合法。
		if(!(((_normal_test_result_range[0].IsEmpty())&&
			(_normal_test_result_range[1].IsEmpty()))||
			((!_normal_test_result_range[0].IsEmpty())&&
			(!_normal_test_result_range[1].IsEmpty())))){
			//unfinished: 这里是否应该判断范围的大小顺序，以及是否为数字？？？？
			return(-6);
		}
		//8-2.获取当前“域”的内容。
		String content_t(Text(""));
		content_t+=_normal_test_result_range[0];
		content_t+=HL7Segment::GROUP_SEPARATOR;
		content_t+=_normal_test_result_range[1];
		content=content_t;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备获取“域”的内容不合法。
		if((!_abnormal_flags.IsEmpty())&&
			(Text("L")!=_abnormal_flags)&&
			(Text("H")!=_abnormal_flags)&&
			(Text("N")!=_abnormal_flags)){
			return(-7);
		}
		//9-2.获取当前“域”的内容。
		content=_abnormal_flags;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//10-1.如果当前准备获取“域”的内容不合法。
		if((Text("ST")==_test_result_type)&&
			(_qualitative_test_result.IsEmpty())){
			return(-8);
		}
		//10-2.获取当前“域”的内容。
		content=_qualitative_test_result;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){
		//11-1.获取当前“域”的内容。
		content=_qualitative_reference_value;
		//11-2.程序运行到此成功返回。
		return(1);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){
		//12-1.如果当前准备获取“域”的内容不合法。
		if(Text("F")!=_test_result_status){
			return(-9);
		}
		//12-2.获取当前“域”的内容。
		content=_test_result_status;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){
		//unfinished: 此处是否需要判断原始结果为必须，以及其值为数字？？？
		//14-1.获取当前“域”的内容。
		content=_original_test_result;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){
		//15-1.如果当前准备获取“域”的内容不合法。
		if((!_test_date_time.IsEmpty())&&
			((14!=_test_date_time.GetLength())||
			(!DataConverter::is_number(_test_date_time)))){
			return(-10);
		}
		//15-2.获取当前“域”的内容。
		content=_test_date_time;
		//15-3.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){
		//16-1.获取当前“域”的内容。
		content=_test_department;
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){
		//17-1.获取当前“域”的内容。
		content=_test_physician;
		//17-2.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){//忽略。
		return(0);
	}
	//19.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-12);
	}
}