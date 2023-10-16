#include"stdafx.h"
#include"HL7OBRSegmentForQC.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForQC
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForQC::HL7OBRSegmentForQC(void)
	:HL7OBRSegment()
	,_item_no(Text(""))
	,_item_name(Text(""))
	/*,_universal_service_id[2]*/
	,_qc_date_time(Text(""))
	,_qc_liquid_amount(Text(""))
	/*,_qc_liquid_no[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_name[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_lot_no[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_period_of_validity[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_concentration_level[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_average_concentration[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_standard_deviation[MAX_QC_LIQUID_AMOUNT]*/
	/*,_qc_liquid_test_result_concentration[MAX_QC_LIQUID_AMOUNT]*/{
}

/**
 * name: ~HL7OBRSegmentForQC
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForQC::~HL7OBRSegmentForQC(void){
}

/**
 * name: set_item_no
 * brief: 设置项目编号。
 * param: item_no - 项目编号。
 * return: --
 */
void HL7OBRSegmentForQC::set_item_no(const String &item_no){
	_item_no=item_no;
}

/**
 * name: get_item_no
 * brief: 获取项目编号。
 * param: --
 * return: 返回项目编号。
 */
const String &HL7OBRSegmentForQC::get_item_no() const{
	return(_item_no);
}

/**
 * name: set_item_name
 * brief: 设置项目名称。
 * param: item_name - 项目名称。
 * return: --
 */
void HL7OBRSegmentForQC::set_item_name(const String &item_name){
	_item_name=item_name;
}

/**
 * name: get_item_name
 * brief: 获取项目名称。
 * param: --
 * return: 返回项目名称。
 */
const String &HL7OBRSegmentForQC::get_item_name() const{
	return(_item_name);
}

/**
 * name: set_universal_service_id
 * brief: 设置指定的通用服务标识符。
 * param: index - 索引编号。
 *        universal_service_id - 指定的通用服务标识符。
 * return: --
 */
void HL7OBRSegmentForQC::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: 获取指定的通用服务标识符。
 * param: index - 索引编号。
 * return: 返回指定的通用服务标识符。
 */
const String &HL7OBRSegmentForQC::get_universal_service_id(
	const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_qc_date_time
 * brief: 设置指控日期时间（格式：20150128123730）。
 * param: qc_date_time - 指控日期时间（格式：20150128123730）。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_date_time(const String &qc_date_time){
	_qc_date_time=qc_date_time;
}

/**
 * name: get_qc_date_time
 * brief: 获取质控日期时间（格式：20150128123730）。
 * param: --
 * return: 返回质控日期时间（格式：20150128123730）。
 */
const String &HL7OBRSegmentForQC::get_qc_date_time() const{
	return(_qc_date_time);
}

/**
 * name: set_qc_liquid_amount
 * brief: 设置质控液数量。
 * param: qc_liquid_amount - 质控液数量。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_amount(const String &qc_liquid_amount){
	_qc_liquid_amount=qc_liquid_amount;
}

/**
 * name: get_qc_liquid_amount
 * brief: 获取质控液个数。
 * param: --
 * return: 返回质控液个数。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_amount() const{
	return(_qc_liquid_amount);
}

/**
 * name: set_qc_liquid_amount_with_number
 * brief: 以数字的形式设置质控液数量。
 * param: qc_liquid_amount - 质控液数量。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_amount_with_number(const unsigned int qc_liquid_amount){
	_qc_liquid_amount=DataConverter::to_string(qc_liquid_amount);
}

/**
 * name: get_qc_liquid_amount_with_number
 * brief: 获取质控液数量的数字描述。
 * param: --
 * return: 如果函数执行成功返回质控液个数的数字描述，否则返回值等于零。
 */
unsigned int HL7OBRSegmentForQC::get_qc_liquid_amount_with_number() const{
	return(DataConverter::to_unsigned_int(_qc_liquid_amount));
}

/**
 * name: set_qc_liquid_no
 * brief: 设置指定的质控液编号。
 * param: index - 索引编号。
 *        qc_liquid_no - 质控液编号。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_no(const unsigned int index,const String &qc_liquid_no){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_no[index]=qc_liquid_no;
}

/**
 * name: get_qc_liquid_no
 * brief: 获取指定的质控液编号。
 * param: index - 索引编号。
 * return: 返回指定的质控液编号。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_no[index]);
}

/**
 * name: set_qc_liquid_name
 * brief: 设置指定质控液的名称。
 * param: index - 索引编号。
 *        qc_liquid_name - 质控液名称。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_name(
	const unsigned int index,const String &qc_liquid_name){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_name[index]=qc_liquid_name;
}

/**
 * name: get_qc_liquid_name
 * brief: 获取指定的质控液名称。
 * param: index - 索引编号。
 * return: 返回指定的质控液名称。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_name(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_name[index]);
}

/**
 * name: set_qc_liquid_lot_no
 * brief: 设置指定的质控液批号。
 * param: index - 索引编号。
 *        qc_liquid_lot_no - 质控液批号。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_lot_no(const unsigned int index,const String &qc_liquid_lot_no){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_lot_no[index]=qc_liquid_lot_no;
}

/**
 * name: get_qc_liquid_lot_no
 * brief: 获取指定的质控液批号。
 * param: index - 索引编号。
 * return: 返回指定的质控液批号。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_lot_no(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_lot_no[index]);
}

/**
 * name: set_qc_liquid_period_of_validity
 * brief: 设置指定质控液的有效期。
 * param: index - 索引编号。
 *        qc_liquid_period_of_validity - 质控液有效期。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_period_of_validity(
	const unsigned int index,const String &qc_liquid_period_of_validity){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_period_of_validity[index]=qc_liquid_period_of_validity;
}

/**
 * name: get_qc_liquid_period_of_validity
 * brief: 获取指定质控液的有效期。
 * param: index - 索引编号。
 * return: 返回指定质控液的有效期。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_period_of_validity(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_period_of_validity[index]);
}

/**
 * name: set_qc_liquid_concentration_level
 * brief: 设置指定的浓度液浓度水平。
 * param: index - 索引编号。
 *        qc_liquid_concentration_level - 质控液浓度水平。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_concentration_level(
	const unsigned int index,const String &qc_liquid_concentration_level){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_concentration_level[index]=qc_liquid_concentration_level;
}

/**
 * name: get_qc_liquid_concentration_level
 * brief: 获取指定的质控液浓度水平。
 * param: index - 索引编号。
 * return: 返回指定的质控液浓度水平。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_concentration_level(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_concentration_level[index]);
}

/**
 * name: set_qc_liquid_average_concentration
 * brief: 设置指定质控液的平均浓度。
 * param: index - 索引编号。
 *        qc_liquid_average_concentration - 质控液平均浓度。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_average_concentration(
	const unsigned int index,const String &qc_liquid_average_concentration){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_average_concentration[index]=qc_liquid_average_concentration;
}

/**
 * name: get_qc_liquid_average_concentration
 * brief: 获取指定质控液的平均浓度。
 * param: index - 索引编号。
 * return: 返回指定质控液的平均浓度。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_average_concentration(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_average_concentration[index]);
}

/**
 * name: set_qc_liquid_standard_deviation
 * brief: 设置指定质控液的标准差。
 * param: index - 索引编号。
 *        qc_liquid_standard_deviation - 指定质控液的标准差。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_standard_deviation(
	const unsigned int index,const String &qc_liquid_standard_deviation){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_standard_deviation[index]=qc_liquid_standard_deviation;
}

/**
 * name: get_qc_liquid_standard_deviation
 * brief: 获取指定质控液的标准差。
 * param: index - 索引编号。
 * return: 返回指定质控液的标准差。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_standard_deviation(
	const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_standard_deviation[index]);
}

/**
 * name: set_qc_liquid_test_result_concentration
 * brief: 设置指定质控液的测试结果浓度。
 * param: index - 索引编号。
 *        qc_liquid_test_result_concentration - 质控液的测试结果浓度。
 * return: --
 */
void HL7OBRSegmentForQC::set_qc_liquid_test_result_concentration(
	const unsigned int index,const String &qc_liquid_test_result_concentration){
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	_qc_liquid_test_result_concentration[index]=qc_liquid_test_result_concentration;
}

/**
 * name: get_qc_liquid_test_result_concentration
 * brief: 获取指定的质控液测试结果浓度。
 * param: index - 索引编号。
 * return: 返回指定的质控液测试结果浓度。
 */
const String &HL7OBRSegmentForQC::get_qc_liquid_test_result_concentration(const unsigned int index) const{
	assert((index>=0)&&(index<MAX_QC_LIQUID_AMOUNT));
	return(_qc_liquid_test_result_concentration[index]);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7OBRSegmentForQC::set_field(const unsigned int no,const String &content){
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
			//unfinished: 是否需要判断质控液编号为数字？？？
			return(-2);
		}
		//3-2.设置当前“域”的内容。
		_item_no=content;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置当前“域”的内容。
		_item_name=content;
		//4-2.程序运行到此成功返回。
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
		_qc_date_time=content;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){//忽略。
		return(0);
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
			(DataConverter::to_unsigned_int(content)>MAX_QC_LIQUID_AMOUNT)){
				return(-6);
		}
		//12-2.设置当前“域”的内容。
		_qc_liquid_amount=content;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){
		//13-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_no,get_qc_liquid_amount_with_number(),1)<0){
			return(-7);
		}
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){
		//14-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_name,get_qc_liquid_amount_with_number(),2)<0){
			return(-8);
		}
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){
		//15-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_lot_no,get_qc_liquid_amount_with_number(),3)<0){
			return(-9);
		}
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){
		//16-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_period_of_validity,get_qc_liquid_amount_with_number(),4)<0){
			return(-10);
		}
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){
		//18-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_concentration_level,get_qc_liquid_amount_with_number(),5)<0){
			return(-11);
		}
		//18-2.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望设置“段”的第十九个“域”。
	else if(19==no){
		//19-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_average_concentration,get_qc_liquid_amount_with_number(),6)<0){
			return(-12);
		}
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望设置“段”的第二十个“域”。
	else if(20==no){
		//20-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_standard_deviation,get_qc_liquid_amount_with_number(),7)<0){
			return(-13);
		}
		//20-2.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望设置“段”的第二十一个“域”。
	else if(21==no){
		//21-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(extract_qc_liquid_information_from_content(content,
			_qc_liquid_test_result_concentration,get_qc_liquid_amount_with_number(),8)<0){
			return(-14);
		}
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22~48.如果当前期望获取“段”的第二十二至四十八个“域”。
	else if((no>=22)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-15);
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
int HL7OBRSegmentForQC::get_field(const unsigned int no,String &content) const{
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
			//unfinished: 是否需要判断质控液编号为数字？？？
			return(-2);
		}
		//3-2.获取当前“域”的内容。
		content=_item_no;
		//3-3.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_item_name;
		//4-2.程序运行到此成功返回。
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
		if((!_qc_date_time.IsEmpty())&&((14!=_qc_date_time.GetLength())||
			(!DataConverter::is_number(_qc_date_time)))){
			return(-4);
		}
		//8-2.获取当前“域”的内容。
		content=_qc_date_time;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){//忽略。
		return(0);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){//忽略。
		return(0);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){
		//12-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((_qc_liquid_amount.IsEmpty())||
			(0==get_qc_liquid_amount_with_number())||
			(get_qc_liquid_amount_with_number()>MAX_QC_LIQUID_AMOUNT)){
			return(-5);
		}
		//12-2.获取当前“域”的内容。
		content=_qc_liquid_amount;
		//12-3.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){
		//13-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_no,
			get_qc_liquid_amount_with_number(),1,content)<0){
			return(-6);
		}
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){
		//14-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_name,
			get_qc_liquid_amount_with_number(),2,content)<0){
			return(-7);
		}
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){
		//15-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_lot_no,
			get_qc_liquid_amount_with_number(),3,content)<0){
			return(-8);
		}
		//15-2.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){
		//16-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_period_of_validity,
			get_qc_liquid_amount_with_number(),4,content)<0){
			return(-9);
		}
		//16-2.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){
		//18-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_concentration_level,
			get_qc_liquid_amount_with_number(),5,content)<0){
			return(-10);
		}
		//18-2.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望获取“段”的第十九个“域”。
	else if(19==no){
		//19-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_average_concentration,
			get_qc_liquid_amount_with_number(),6,content)<0){
			return(-11);
		}
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望获取“段”的第二十个“域”。
	else if(20==no){
		//20-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_standard_deviation,
			get_qc_liquid_amount_with_number(),7,content)<0){
			return(-12);
		}
		//20-2.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望获取“段”的第二十一个“域”。
	else if(21==no){
		//21-1.从指定的内容中提取“域”的内容，并且判断提取是否成功。
		if(pack_qc_liquid_information_to_content(_qc_liquid_test_result_concentration,
			get_qc_liquid_amount_with_number(),8,content)<0){
			return(-13);
		}
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22~48.如果当前期望获取“段”的第二十二至四十八个“域”。
	else if((no>=22)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-14);
	}
}

/**
 * name: extract_qc_liquid_information_from_content
 * brief: 从指定内容中，提取质控液信息。
 * param: content - 指定的内容。
 *        qc_liquid_information - 指向质控液信息存储数组。
 *        qc_liquid_amount - 质控液数量。
 *        qc_liquid_information_type - 质控液信息类型。
 *        ================================================
 *						  1  质控液编号。
 *                        2  质控液名称。
 *                        3  质控液批号。
 *                        4  质控液有效期。
 *                        5  质控液浓度水平。
 *                        6  质控液平均浓度。
 *                        7  质控液标准差。
 *                        8  质控液测试结果浓度。
 *        ================================================
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7OBRSegmentForQC::extract_qc_liquid_information_from_content(
	const String &content,String *qc_liquid_information,const unsigned int 
	qc_liquid_amount,const unsigned int qc_liquid_information_type){
	//1.判断当前传递参数是否合法。
	if((0==qc_liquid_information)||(0==qc_liquid_amount)||(qc_liquid_amount>
		MAX_QC_LIQUID_AMOUNT)||(qc_liquid_information_type<1)||(
		qc_liquid_information_type>8)){
		return(-1);
	}
	//2.根据当前质控液个数，创建质控液信息临时存储空间，并且判断创建是否成功。
	String *qc_liquid_information_temp=new String[qc_liquid_amount];
	if(0==qc_liquid_information_temp){
		return(-2);
	}
	//3.分析指定的内容，从中提取指定的质控液信息，并且判断分析是否成功。
	if(extract_group_content_from_field_content(content,
		qc_liquid_information_temp,qc_liquid_amount)<0){
		delete[] qc_liquid_information_temp;
		return(-3);
	}
	//4.统计质控液信息中空、与非空的数量，从而判断获取的质控液信息是否合法。
	//4-1.声明当前操作所需变量。
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//4-2.遍历质控液信息存储临时数组，并且统计质控液信息空与非空的数量。
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(qc_liquid_information_temp[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//4-3.根据空、非空的统计数量，判断当前获取的质控液信息是否合法。
	//unfinished: 这里是否需要对定标信息中一些数字信息进行数字识别判断。
	if((1==qc_liquid_information_type)||(2==qc_liquid_information_type)||
		(3==qc_liquid_information_type)||(4==qc_liquid_information_type)){
		if((empty_amount!=qc_liquid_amount)&&
			(not_empty_amount!=qc_liquid_amount)){
			delete[] qc_liquid_information_temp;
			return(-4);
		}else if((qc_liquid_amount==not_empty_amount)&&
			(4==qc_liquid_information_type)){			
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((8!=qc_liquid_information_temp[index].GetLength())||
					(!DataConverter::is_number(qc_liquid_information_temp[index]))){
					delete[] qc_liquid_information_temp;
					return(-5);
				}
			}
		}
	}else{
		if(not_empty_amount!=qc_liquid_amount){
			delete[] qc_liquid_information_temp;
			return(-6);
		}else if(5==qc_liquid_information_type){
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((Text('H')!=qc_liquid_information_temp[index])&&
					(Text('M')!=qc_liquid_information_temp[index])&&
					((Text('L')!=qc_liquid_information_temp[index]))){
					delete[] qc_liquid_information_temp;
					return(-7);
				}
			}
		}
	}
	//5.将当前获取的临时质控液信息存储到质控液信息存储数组中。
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		qc_liquid_information[index]=qc_liquid_information_temp[index];
	}
	//6.删除质控液信息存储临时数组。
	delete[] qc_liquid_information_temp;
	//7.程序运行到此成功返回。
	return(1);
}

/**
 * name: pack_qc_liquid_information_to_content
 * brief: 将当前的质控液信息打包生成指定的内容。
 * param: qc_liquid_information - 指向质控液信息存储数组。
 *        qc_liquid_amount - 质控液数量。
 *        qc_liquid_information_type - 质控液类型。
 *        ================================================
 *						  1  质控液编号。
 *                        2  质控液名称。
 *                        3  质控液批号。
 *                        4  质控液有效期。
 *                        5  质控液浓度水平。
 *                        6  质控液平均浓度。
 *                        7  质控液标准差。
 *                        8  质控液测试结果浓度。
 *        ================================================
 *        content - 返回生成的内容。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7OBRSegmentForQC::pack_qc_liquid_information_to_content(
	const String *qc_liquid_information,const unsigned int qc_liquid_amount,
	const unsigned int qc_liquid_information_type,String &content) const{
	//1.判断当前传递参数是否合法，如果不合法则直接返回错误。
	if((0==qc_liquid_information)||(0==qc_liquid_amount)||(qc_liquid_amount>
		MAX_QC_LIQUID_AMOUNT)||(qc_liquid_information_type<1)||(
		qc_liquid_information_type>8)){
		return(-1);
	}
	//2.统计质控液信息中空、与非空的数量，从而判断获取的质控液信息是否合法。
	//2-1.声明当前操作所需变量。
	unsigned int empty_amount=0;
	unsigned int not_empty_amount=0;
	//2-2.遍历质控液信息存储数组，并且统计质控液信息空与非空的数量。
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(qc_liquid_information[index].IsEmpty()){
			++empty_amount;
		}else{
			++not_empty_amount;
		}
	}
	//2-3.根据空、非空的统计数量，判断当前获取的质控液信息是否合法。
	//unfinished: 这里是否需要对质控信息中一些数字信息进行数字识别判断。
	if((1==qc_liquid_information_type)||(2==qc_liquid_information_type)||
		(3==qc_liquid_information_type)||(4==qc_liquid_information_type)){
		if((empty_amount!=qc_liquid_amount)&&
			(not_empty_amount!=qc_liquid_amount)){
			return(-2);
		}else if((qc_liquid_amount==not_empty_amount)&&(
			4==qc_liquid_information_type)){			
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((8!=qc_liquid_information[index].GetLength())||
					(!DataConverter::is_number(qc_liquid_information[index]))){
					return(-3);
				}
			}
		}
	}else{
		if(not_empty_amount!=qc_liquid_amount){
			return(-4);
		}else if(5==qc_liquid_information_type){
			for(unsigned int index=0;index!=qc_liquid_amount;++index){
				if((Text('H')!=qc_liquid_information[index])&&
					(Text('M')!=qc_liquid_information[index])&&
					((Text('L')!=qc_liquid_information[index]))){
					return(-5);
				}
			}
		}
	}
	//3.利用当前质控液信息形成指定的内容。
	//3-1.声明当前操作所需变量。
	String content_t(Text(""));
	//3-2.遍历定标信息数组，形成指定的内容。
	for(unsigned int index=0;index!=qc_liquid_amount;++index){
		if(0!=index){
			content_t+=GROUP_SEPARATOR;
		}
		content_t+=qc_liquid_information[index];
	}
	//3-3.设置目标内容。
	content=content_t;
	//4.程序运行到此成功返回。
	return(0);
}