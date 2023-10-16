#include"stdafx.h"
#include"HL7OBRSegmentForCalib.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForCalib
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForCalib::HL7OBRSegmentForCalib(void)
	:HL7OBRSegment()
	,_item_no(Text(""))
	,_item_name(Text(""))
	/*,_universal_service_id[2]*/
	,_calibration_date_time(Text(""))
	,_calibration_method(Text(""))
	,_calibration_liquid_amount(Text(""))
	/*,_calibration_liquid_no[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_name[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_lot_no[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_period_of_validity[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_standard_concentration[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_concentration_level[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	/*,_calibration_liquid_test_concentration[MAX_CALIBRATION_LIQUID_AMOUNT]*/
	,_calibration_parameter_amount(Text(""))
	/*,_calibration_parameter_value[MAX_CALIBRATION_PARAMETER_AMOUNT]*/{
}

/**
 * name: ~HL7OBRSegmentForCalib
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForCalib::~HL7OBRSegmentForCalib(void){
}

/**
 * name: set_item_no
 * brief: 设置项目编号。
 * param: item_no - 项目编号。
 * return: --
 */
void HL7OBRSegmentForCalib::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: 获取项目编号。
 * param: --
 * return: 返回项目编号。
 */
const String &HL7OBRSegmentForCalib::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: 设置项目名称。
 * param: item_name - 项目名称。
 * return: --
 */
void HL7OBRSegmentForCalib::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: 获取项目名称。
 * param: --
 * return: 返回项目名称。
 */
const String &HL7OBRSegmentForCalib::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_universal_service_id
 * brief: 设置通用服务标识符。
 * param: index - 索引编号。
 *        universal_service_id - 通用服务标识符。
 * return: --
 */
void HL7OBRSegmentForCalib::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: 获取通用服务标识符。
 * param: index - 索引编号。
 * return: 返回通用服务标识符。
 */
const String &HL7OBRSegmentForCalib::get_universal_service_id(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_calibration_date_time
 * brief: 设置定标日期时间。
 * param: calibration_date_time - 定标日期时间。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_date_time(const String &calibration_date_time){
	_calibration_date_time=calibration_date_time;
}

/**
 * name: get_calibration_date_time
 * brief: 获取定标日期时间。
 * param: --
 * return: 返回定标日期时间。
 */
const String &HL7OBRSegmentForCalib::get_calibration_date_time() const{
	return(_calibration_date_time);
}

/**
 * name: set_calibration_method
 * brief: 设置定标方法。
 * param: calibration_method - 定标方法。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_method(const String &calibration_method){
	_calibration_method=calibration_method;
}

/**
 * name: get_calibration_method
 * brief: 获取定标方法。
 * param: --
 * return: 返回定标方法。
 */
const String &HL7OBRSegmentForCalib::get_calibration_method() const{
	return(_calibration_method);
}

/**
 * name: set_calibration_method_with_number
 * brief: 利用数字设置定标方法。
 * param: calibration_method - 定标方法。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_method_with_number(const unsigned int calibration_method){
	_calibration_method=DataConverter::to_string(calibration_method);
}

/**
 * name: get_calibration_method_with_number
 * breif: 获取定标方法的数字描述。
 * param: --
 * return: 如果函数执行成功返回定标方法的数字描述，否则返回零。
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_method_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_method));
}

/**
 * name: set_calibration_liquid_amount
 * brief: 设置定标液个数。
 * param: calibration_liquid_amount - 定标液个数。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_amount(const String &calibration_liquid_amount){
	_calibration_liquid_amount=calibration_liquid_amount;
}

/**
 * name: get_calibration_liquid_amount
 * brief: 获取定标液个数。
 * param: --
 * return: 返回定标液个数。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_amount() const{
	return(_calibration_liquid_amount);
}

/**
 * name: set_calibration_liquid_amount_with_number
 * breif: 通用数字设置定标液的数量。
 * param: calibration_liquid_amount - 定标液数量。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_amount_with_number(const unsigned int calibration_liquid_amount){
	_calibration_liquid_amount=DataConverter::to_string(calibration_liquid_amount);
}

/**
 * name: get_calibration_liquid_amount_width_number
 * brief: 获取定标液个数的数字描述。
 * param: --
 * return: 如果函数执行成功返回定标液个数的数字描述，否则返回值等于零。
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_liquid_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_liquid_amount));
}

/**
 * name: set_calibration_liquid_no
 * brief: 设置定标液编号。
 * param: index - 索引编号。
 *        calibration_liquid_no - 定标液编号。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_no(
	const unsigned int index,const String &calibration_liquid_no){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_no[index]=calibration_liquid_no;
}

/**
 * name: get_calibration_liquid_no
 * brief: 获取定标液编号。
 * param: index - 索引编号。
 * return: 返回定标液编号。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_no[index]);
}

/**
 * name: set_calibration_liquid_name
 * brief: 设置定标液名称。
 * param: index - 索引编号。
 *        calibration_liquid_name - 定标液名称。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_name(
	const unsigned int index,const String &calibration_liquid_name){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_name[index]=calibration_liquid_name;
}

/**
 * name: get_calibration_liquid_name
 * brief: 获取定标液名称。
 * param: index - 索引编号。
 * return: 返回定标液名称。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_name(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_name[index]);
}

/**
 * name: set_calibration_liquid_lot_no
 * brief: 设置定标液批号。
 * param: index - 索引编号。
 *        calibration_liquid_lot_no - 定标液批号。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_lot_no(
	const unsigned int index,const String &calibration_liquid_lot_no){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_lot_no[index]=calibration_liquid_lot_no;
}

/**
 * name: get_calibration_liquid_lot_no
 * brief: 获取定标液批号。
 * param: index - 索引编号。
 * return: 返回定标液批号。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_lot_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_lot_no[index]);
}

/**
 * name: set_calibration_liquid_period_of_validity
 * brief: 设置定标液有效期。
 * param: index - 索引编号。
 *        calibration_liquid_period_of_validity - 定标液有效期。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_period_of_validity(
	const unsigned int index,const String &calibration_liquid_period_of_validity){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_period_of_validity[index]=calibration_liquid_period_of_validity;
}

/**
 * name: get_calibration_liquid_period_of_validity
 * brief: 获取定标液有效期。
 * param: index - 索引编号。
 * return: 返回定标液有效期。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_period_of_validity(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_period_of_validity[index]);
}

/**
 * name: set_calibration_liquid_standard_concentration
 * brief: 设置定标液标准浓度。
 * param: index - 索引编号。
 *        calibration_standard_concentration - 定标液标准浓度。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_standard_concentration(
	const unsigned int index,const String &calibration_standard_concentration){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_standard_concentration[index]=calibration_standard_concentration;
}

/**
 * name: get_calibration_liquid_standard_concentration
 * brief: 获取定标液标准浓度。
 * param: index - 索引编号。
 * return: 返回定标液标准浓度。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_standard_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_standard_concentration[index]);
}

/**
 * name: set_calibration_liquid_concentration_level
 * brief: 设置定标液浓度水平。
 * param: index - 索引编号。
 *        calibration_liquid_concentration_level - 定标液浓度水平。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_concentration_level(
	const unsigned int index,const String &calibration_liquid_concentration_level){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_concentration_level[index]=calibration_liquid_concentration_level;
}

/**
 * name: get_calibration_liquid_concentration_level
 * brief: 获取定标液浓度水平。
 * param: index - 索引编号。
 * return: 返回定标液浓度水平。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_concentration_level(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_concentration_level[index]);
}

/**
 * name: set_calibration_liquid_test_concentration
 * brief: 设置定标液测试浓度。
 * param: index - 索引编号。
 *        calibration_liquid_test_concentration - 定标液测试浓度。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_liquid_test_concentration(
	const unsigned int index,const String &calibration_liquid_test_concentration){
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	_calibration_liquid_test_concentration[index]=calibration_liquid_test_concentration;
}

/**
 * name: get_calibration_liquid_test_concentration
 * brief: 获取定标液测试浓度。
 * param: index - 索引编号。
 * return: 返回定标液测试浓度。
 */
const String &HL7OBRSegmentForCalib::get_calibration_liquid_test_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_LIQUID_AMOUNT));
	return(_calibration_liquid_test_concentration[index]);
}

/**
 * name: set_calibration_parameter_amount
 * brief: 设置定标参数个数。
 * param: calibration_parameter_amount - 定标参数个数。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_amount(const String &calibration_parameter_amount){
	_calibration_parameter_amount=calibration_parameter_amount;
}

/**
 * name: get_calibration_parameter_amount
 * breif: 获取定标参数个数。
 * param: --
 * return: 返回定标参数个数。
 */
const String &HL7OBRSegmentForCalib::get_calibration_parameter_amount() const{
	return(_calibration_parameter_amount);
}

/**
 * name: set_calibration_parameter_amount_with_number
 * brief: 以数字形式设置定标参数个数。
 * param: calibration_parameter_amount - 定标参数个数。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_amount_with_number(
	const unsigned int calibration_parameter_amount){
	_calibration_parameter_amount=DataConverter::to_string(calibration_parameter_amount);
}

/**
 * name: get_calibration_parameter_amount_with_number
 * brief: 以数字形式获取定标参数个数。
 * param: --
 * return: 如果函数执行成功返回定标参数个数，否则返回零。
 */
unsigned int HL7OBRSegmentForCalib::get_calibration_parameter_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_calibration_parameter_amount));
}

/**
 * name: set_calibration_parameter_value
 * brief: 设置定标参数值。
 * param: index - 索引编号。
 *        calibration_parameter_value - 定标参数值。
 * return: --
 */
void HL7OBRSegmentForCalib::set_calibration_parameter_value(
	const unsigned int index,const String &calibration_parameter_value){
	assert((index>=0)&&(index<MAX_CALIBRATION_PARAMETER_AMOUNT));
	_calibration_parameter_value[index]=calibration_parameter_value;
}

/**
 * name: get_calibration_parameter_value
 * brief: 获取定标参数值。
 * param: index - 索引编号。
 * return: 返回定标参数值。
 */
const String &HL7OBRSegmentForCalib::get_calibration_parameter_value(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_CALIBRATION_PARAMETER_AMOUNT));
	return(_calibration_parameter_value[index]);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7OBRSegmentForCalib::set_field(const unsigned int no,const String &content){
	//1.调用基类相应函数设置指定的“域”，并且判断设置结果。
	//1-1.调用基类相应函数设置指定的“域”。
	const int execute_result=HL7OBRSegment::set_field(no,content);
	//1-2.如果成功设置指定的“域”。
	if(execute_result>0){
		return(1);
	}
	//1-3.如果设置指定的“域”失败。
	else if(execute_result<0){
		return(-1);
	}
	//2.忽略。
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.判断当前准备设置“域”的内容是否合法。
		if(content.IsEmpty()){
			return(-2);
		}
		//unfinished: 是否需要检测当前项目编号是否为数字？？？
		//3-2.设置当前“域”的内容。
		_item_no=content;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置当前“域”的内容。
		_item_name=content;
		//4-2.程序运行的到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){
		//5-1.声明当前操作所需变量。
		String contents[2];
		//5-2.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if(extract_group_content_from_field_content(
			content,contents,2)<0){
			return(-3);
		}
		if((contents[0].IsEmpty())||(contents[1].IsEmpty())){
			return(-4);
		}
		//5-3.设置当前“域”的内容。
		_universal_service_id[0]=contents[0];
		_universal_service_id[1]=contents[1];
		//5-4.程序运行到此成功返回。
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
		//8-1.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-5);
		}
		//8-2.设置当前“域”的内容。
		_calibration_date_time=content;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//10-1.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if((!content.IsEmpty())&&
			(0==DataConverter::to_unsigned_int(content))){
			return(-6);
		}
		//unfinished: 是否应该在此判断定标方法数值是否符合范围???
		//10-2.设置当前“域”的内容。
		_calibration_method=content;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望设置“段”的第十一个“域”。
	else if(11==no){//忽略。
		return(0);
	}
	//12.如果当前期望设置“段”的第十二个“域”。
	else if(12==no){
		//12-1.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if((content.IsEmpty())||
			(0==DataConverter::to_unsigned_int(content))||
			(DataConverter::to_unsigned_int(content)>
			MAX_CALIBRATION_LIQUID_AMOUNT)){
			return(-7);
		}
		//12-2.设置当前“域”的内容。
		_calibration_liquid_amount=content;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){
		//13-1.从指定内容中提取定标液编号信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_no,
			get_calibration_liquid_amount_with_number(),1)<0){
			return(-8);
		}
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){
		//14-1.从指定内容中提取定标液名称信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_name,
			get_calibration_liquid_amount_with_number(),2)<0){
			return(-9);
		}
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){
		//15-1.从指定内容中提取定标液批号信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_lot_no,
			get_calibration_liquid_amount_with_number(),3)<0){
			return(-10);
		}
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){
		//16-1.从指定内容中提取定标液有效期信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_period_of_validity,
			get_calibration_liquid_amount_with_number(),4)<0){
			return(-11);
		}
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){
		//17-1.从指定内容中提取定标液标准浓度信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_standard_concentration,
			get_calibration_liquid_amount_with_number(),5)<0){
			return(-12);
		}
		//17-2.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){
		//18-1.从指定内容中提取定标液浓度水平信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_concentration_level,
			get_calibration_liquid_amount_with_number(),6)<0){
			return(-13);
		}
		//18-2.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望设置“段”的第十九个“域”。
	else if(19==no){
		//19-1.从指定内容中提取定标液浓度水平信息。
		if(extract_calibration_liquid_information_from_content(
			content,_calibration_liquid_test_concentration,
			get_calibration_liquid_amount_with_number(),7)<0){
			return(-14);
		}
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望设置“段”的第二十个“域”。
	else if(20==no){
		//20-1.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if((!content.IsEmpty())&&
			((!DataConverter::is_number(content))||
			(0==DataConverter::to_unsigned_int(content))||
			(DataConverter::to_unsigned_int(content)>
			MAX_CALIBRATION_PARAMETER_AMOUNT))){
			return(-15);
		}
		//20-2.设置当前“域”的内容。
		_calibration_parameter_amount=content;
		//20-3.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望设置“段”的第二十一个“域”。
	else if(21==no){
		//21-1.如果当前系统中记录的定标参数个数为空。
		if(_calibration_parameter_amount.IsEmpty()){
			//21-1-1.如果当前准备设置“域”的内容不为空。
			if(!content.IsEmpty()){
				return(-16);
			}
			//21-1-2.设置当前“域”的内容。
			for(unsigned int index=0;index!=
				MAX_CALIBRATION_PARAMETER_AMOUNT;++index){
				_calibration_parameter_value[index]=Text("");
			}
			//21-1-3.程序运行到此成功返回。
			return(1);
		}
		//21-2.如果当前系统中记录的定标参数个数不为空。
		else{
			//21-2-1.获取当前系统中记录的定标参数个数。
			const unsigned int calibration_parameter_amount=
				get_calibration_parameter_amount_with_number();
			if((0==calibration_parameter_amount)||(calibration_parameter_amount>
				MAX_CALIBRATION_PARAMETER_AMOUNT)){
				return(-17);
			}
			//21-2-2.根据当前系统中记录的定标参数个数创建定标参数值数组。
			String *calibration_parameter_value=new String[calibration_parameter_amount];
			if(0==calibration_parameter_value){
				return(-18);
			}
			//21-2-3.分析当前传递的内容，并且判断分析是否成功。
			if(extract_group_content_from_field_content(content,calibration_parameter_value,
				calibration_parameter_amount)<0){
				delete[] calibration_parameter_value;
				return(-19);
			}
			//21-2-4.统计提取的定标参数，判断有多少个非空内容。
			//21-2-4-1.声明当前操作所需变量。
			unsigned int not_empty_amount=0;
			//21-2-4-2.统计提取的定标参数。
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(!calibration_parameter_value[index].IsEmpty()){
					++not_empty_amount;
				}
			}
			//21-2-4-3.判断当前的统计信息是否合法。
			if(not_empty_amount!=calibration_parameter_amount){
				delete[] calibration_parameter_value;
				return(-20);
			}
			//21-2-5.保存当前定标参数值。
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				_calibration_parameter_value[index]=calibration_parameter_value[index];
			}
			//21-2-6.删除定标参数值存储临时数组。
			delete[] calibration_parameter_value;
			//21-2-7.程序运行到此成功返回。
			return(1);
		}
	}
	//22~48.如果当前期望设置“段”的第二十二至四十八个“域”。
	else if((no>=22)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-21);
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
int HL7OBRSegmentForCalib::get_field(const unsigned int no,String &content) const{
	//1.调用基类相应函数获取指定的“域”，并且判断获取结果。
	//1-1.调用基类相应函数获取指定的“域”。
	const int execute_result=HL7OBRSegment::get_field(no,content);
	//1-2.如果调用基类相应函数成功获取指定的“域”，则直接返回。
	if(execute_result>0){
		return(1);
	}
	//1-3.如果调用基类相应函数获取指定的“域”失败，则直接返回。
	else if(execute_result<0){
		return(-1);
	}
	//2.忽略。
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.判断当前准备获取“域”的内容是否合法。
		if(_item_no.IsEmpty()){
			return(-2);
		}
		//unfinished: 是否需要检测当前项目编号是否为数字？？？
		//3-2.获取当前“域”的内容。
		content=_item_no;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_item_name;
		//4-2.程序运行的到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){
		//5-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((_universal_service_id[0].IsEmpty())||
			(_universal_service_id[1].IsEmpty())){
			return(-3);
		}
		//5-2.获取当前“域”的内容。
		String content_t(Text(""));
		content_t=_universal_service_id[0];
		content_t+=GROUP_SEPARATOR;
		content_t+=_universal_service_id[1];
		content=content_t;
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
		//8-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((!_calibration_date_time.IsEmpty())&&
			((14!=_calibration_date_time.GetLength())||
			(!DataConverter::is_number(_calibration_date_time)))){
			return(-4);
		}
		//8-2.获取当前“域”的内容。
		content=_calibration_date_time;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//10-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((!_calibration_method.IsEmpty())&&
			(0==get_calibration_method_with_number())){
			return(-5);
		}
		//unfinished: 是否应该在此判断定标方法数值是否符合范围???
		//10-2.获取当前“域”的内容。
		content=_calibration_method;
		//10-3.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){//忽略。
		return(0);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){
		//12-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((_calibration_liquid_amount.IsEmpty())||
			(0==get_calibration_liquid_amount_with_number())||
			(get_calibration_liquid_amount_with_number()>
			MAX_CALIBRATION_LIQUID_AMOUNT)){
			return(-6);
		}
		//12-2.获取当前“域”的内容。
		content=_calibration_liquid_amount;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){
		//13-1.从指定内容中提取定标液编号信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_no,
			get_calibration_liquid_amount_with_number(),
			1,content)<0){
			return(-7);
		}
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){
		//14-1.从指定内容中提取定标液名称信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_name,
			get_calibration_liquid_amount_with_number(),
			2,content)<0){
			return(-8);
		}
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){
		//15-1.从指定内容中提取定标液批号信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_lot_no,
			get_calibration_liquid_amount_with_number(),
			3,content)<0){
			return(-9);
		}
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){
		//16-1.从指定内容中提取定标液有效期信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_period_of_validity,
			get_calibration_liquid_amount_with_number(),
			4,content)<0){
			return(-10);
		}
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){
		//17-1.从指定内容中提取定标液标准浓度信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_standard_concentration,
			get_calibration_liquid_amount_with_number(),
			5,content)<0){
			return(-11);
		}
		//17-2.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){
		//18-1.从指定内容中提取定标液浓度水平信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_concentration_level,
			get_calibration_liquid_amount_with_number(),
			6,content)<0){
			return(-12);
		}
		//18-2.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望获取“段”的第十九个“域”。
	else if(19==no){
		//19-1.从指定内容中提取定标液浓度水平信息。
		if(pack_calibration_liquid_information_to_content(
			_calibration_liquid_test_concentration,
			get_calibration_liquid_amount_with_number(),
			7,content)<0){
			return(-13);
		}
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望获取“段”的第二十个“域”。
	else if(20==no){
		//20-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((!_calibration_parameter_amount.IsEmpty())&&
			((!DataConverter::is_number(_calibration_parameter_amount))||
			(0==DataConverter::to_unsigned_int(_calibration_parameter_amount))||
			(DataConverter::to_unsigned_int(_calibration_parameter_amount)>
			MAX_CALIBRATION_PARAMETER_AMOUNT))){
			return(-14);
		}
		//20-2.获取当前“域”的内容。
		content=_calibration_parameter_amount;
		//20-3.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望获取“段”的第二十一个“域”。
	else if(21==no){
		//21-1.如果当前系统中记录的定标参数个数为空。
		if(_calibration_parameter_amount.IsEmpty()){
			//21-1-1.如果当前准备获取“域”的内容不为空。
			for(unsigned int index=0;index!=MAX_CALIBRATION_PARAMETER_AMOUNT;++index){
				if(!_calibration_parameter_value[index].IsEmpty()){
					return(-15);
				}
			}
			//21-1-2.获取当前“域”的内容。
			content=Text("");
			//21-1-3.程序运行到此成功返回。
			return(1);
		}
		//21-2.如果当前系统中记录的定标参数个数不为空。
		else{
			//21-2-1.获取当前系统中记录的定标参数个数。
			const unsigned int calibration_parameter_amount=
				get_calibration_parameter_amount_with_number();
			if((0==calibration_parameter_amount)||(calibration_parameter_amount>
				MAX_CALIBRATION_PARAMETER_AMOUNT)){
				return(-16);
			}
			//21-2-2.统计当前定标参数信息，判断有多少个非空内容。
			//21-2-2-1.声明当前操作所需变量。
			unsigned int not_empty_amount=0;
			//21-2-2-2.统计当前定标参数信息。
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(!_calibration_parameter_value[index].IsEmpty()){
					++not_empty_amount;
				}
			}
			//21-2-2-3.判断当前的统计信息是否合法。
			if(not_empty_amount!=calibration_parameter_amount){
				//unfinished: 这里是否需要判断定标参数是否为数字？？？
				return(-17);
			}
			//21-2-3.利用当前定标参数信息形成指定的内容。
			//21-2-3-1.声明当前操作所需变量。
			String temporary_content(Text(""));
			//21-2-3-2.遍历定标参数数组，形成指定的内容。
			for(unsigned int index=0;index!=calibration_parameter_amount;++index){
				if(0!=index){
					temporary_content+=GROUP_SEPARATOR;
				}
				temporary_content+=_calibration_parameter_value[index];
			}
			//21-2-3-3.获取当前指定“域”的内容。
			content=temporary_content;
			//21-2-4.程序运行到此成功返回。
			return(1);
		}
	}
	//22~48.如果当前期望获取“段”的第二十二至四十八个“域”。
	else if((no>=22)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-18);
	}
}

/**
 * name: extract_calibration_liquid_information_from_content
 * brief: 从指定的内容中提取定标液信息。
 * param: content - 指定的内容。
 *        calibration_liquid_information - 指向定标液信息存储数组。
 *        calibration_liquid_amount - 定标液数量。
 *        calibration_liquid_information_type - 定标液信息类型。
 *        =====================================================
 *          1  定标液编号。
 *          2  定标液名称。
 *          3  定标液批号。
 *          4  定标液有效期。
 *          5  定标液标准浓度。
 *          6  定标液浓度水平。
 *          7  定标液测试浓度。
 *        ======================================================
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 注意此函数假设定标液个数已经成功获取。
 */
int HL7OBRSegmentForCalib::extract_calibration_liquid_information_from_content(
	const String &content,String *calibration_liquid_information,const unsigned int
	calibration_liquid_amount,const unsigned int calibration_liquid_information_type){
	//1.判断当前传递参数是否合法，如果不合法则直接返回错误。
	if((0==calibration_liquid_information)||(0==calibration_liquid_amount)||
		(calibration_liquid_amount>MAX_CALIBRATION_LIQUID_AMOUNT)||
		(calibration_liquid_information_type<1)||
		(calibration_liquid_information_type>7)){
		return(-1);
	}
	//2.根据当前系统记录的定标液数量，创建定标液信息存储数组，并且判断创建是否成功。
	String *calibration_liquid_information_array=new String[calibration_liquid_amount];
	if(0==calibration_liquid_information_array){
		return(-2);
	}
	//3.分析当前传递的内容，并且判断分析是否成功。
	if(extract_group_content_from_field_content(content,calibration_liquid_information_array,
		calibration_liquid_amount)<0){
		delete[] calibration_liquid_information_array;
		return(-3);
	}
	//4.统计定标液信息存储数组中的内容，查看有几个空、几个非空的内容。
	//4-1.声明当前操作所需变量。
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//4-2.统计定标液信息存储数组中的内容。
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(calibration_liquid_information_array[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//4-3.根据统计结果，判断当前定标液存储数组的中内容是否合法。
	//unfinished: 这里是否需要对定标信息中一些数字信息进行数字识别判断。
	if((1==calibration_liquid_information_type)||
		(2==calibration_liquid_information_type)||
		(3==calibration_liquid_information_type)||
		(4==calibration_liquid_information_type)){
		if((empty_amount!=calibration_liquid_amount)&&
			(not_empty_amount!=calibration_liquid_amount)){
			delete[] calibration_liquid_information_array;
			return(-4);
		}else if((calibration_liquid_amount==not_empty_amount)&&
			(4==calibration_liquid_information_type)){			
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((8!=calibration_liquid_information_array[index].GetLength())||
					(!DataConverter::is_number(calibration_liquid_information_array[index]))){
					delete[] calibration_liquid_information_array;
					return(-5);
				}
			}
		}
	}else{
		if(not_empty_amount!=calibration_liquid_amount){
			delete[] calibration_liquid_information_array;
			return(-6);
		}else if(6==calibration_liquid_information_type){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((Text('H')!=calibration_liquid_information_array[index])&&
					(Text('M')!=calibration_liquid_information_array[index])&&
					((Text('L')!=calibration_liquid_information_array[index]))){
					delete[] calibration_liquid_information_array;
					return(-7);
				}
			}
		}
	}
	//5.保存当前获取的定标液信息。
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		calibration_liquid_information[index]=calibration_liquid_information_array[index];
	}
	//6.删除定标液信息存储数组。
	delete[] calibration_liquid_information_array;
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: pack_calibration_liquid_information_to_content
 * brief: 打包当前的定标信息，并且形成指定字符串的内容。
 * param: calibration_liquid_information - 指向定标信息数组。
 *        calibration_liquid_amount - 定标液数量。
 *        calibration_liquid_information_type - 定标信息类型。
 *        =====================================================
 *          1  定标液编号。
 *          2  定标液名称。
 *          3  定标液批号。
 *          4  定标液有效期。
 *          5  定标液标准浓度。
 *          6  定标液浓度水平。
 *          7  定标液测试浓度。
 *        ======================================================
 *        content - 返回的内容。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
 int HL7OBRSegmentForCalib::pack_calibration_liquid_information_to_content(
	 const String *calibration_liquid_information,const unsigned int calibration_liquid_amount,
	const unsigned int calibration_liquid_information_type,String &content) const{
	//1.判断当前传递参数是否合法，如果不合法则直接返回错误。
	if((0==calibration_liquid_information)||(0==calibration_liquid_amount)||
		(calibration_liquid_amount>MAX_CALIBRATION_LIQUID_AMOUNT)||
		(calibration_liquid_information_type<1)||(calibration_liquid_information_type>7)){
		return(-1);
	}
	//2.统计当前定标液信息中，空与非空的数量。
	//2-1.声明当前操作所需变量。
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//2-2.遍历定标液信息存储数组，统计当前定标液信息中的空与非空计数。
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(calibration_liquid_information[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//2-3.根据统计结果，判断当前定标液信息存储数组中的内容是否合法。
	//unfinished: 这里是否需要对定标信息中一些数字信息进行数字识别判断。
	if((1==calibration_liquid_information_type)||
		(2==calibration_liquid_information_type)||
		(3==calibration_liquid_information_type)||
		(4==calibration_liquid_information_type)){
		if((empty_amount!=calibration_liquid_amount)&&
			(not_empty_amount!=calibration_liquid_amount)){
			return(-2);
		}else if((calibration_liquid_amount==not_empty_amount)&&
			(4==calibration_liquid_information_type)){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((8!=calibration_liquid_information[index].GetLength())||
					(!DataConverter::is_number(calibration_liquid_information[index]))){
					return(-3);
				}
			}
		}
	}else{
		if(not_empty_amount!=calibration_liquid_amount){
			return(-4);
		}else if(6==calibration_liquid_information_type){
			for(unsigned int index=0;index!=calibration_liquid_amount;++index){
				if((Text('H')!=calibration_liquid_information[index])&&
					(Text('M')!=calibration_liquid_information[index])&&
					((Text('L')!=calibration_liquid_information[index]))){
					return(-5);
				}
			}
		}
	}
	//3.利用当前定标液信息形成指定的内容。
	//3-1.声明当前操作所需变量。
	String temporary_content(Text(""));
	//3-2.遍历定标信息数组，形成指定的内容。
	for(unsigned int index=0;index!=calibration_liquid_amount;++index){
		if(0!=index){
			temporary_content+=GROUP_SEPARATOR;
		}
		temporary_content+=calibration_liquid_information[index];
	}
	//3-3.设置目标内容。
	content=temporary_content;
	//4.程序运行到此成功返回。
	return(0);
}