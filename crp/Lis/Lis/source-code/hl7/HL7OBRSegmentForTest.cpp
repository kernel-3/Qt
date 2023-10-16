#include"stdafx.h"
#include"HL7OBRSegmentForTest.h"
#include"../tool/DataConverter.h"
#include<assert.h>

/**
 * name: HL7OBRSegmentForTest
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForTest::HL7OBRSegmentForTest(void)
	:HL7OBRSegment()
	,_specimen_barcode(Text(""))
	,_specimen_no(Text(""))
	//,_universal_service_id(Text(""))
	,_is_emergency(Text(""))
	,_specimen_collect_date_time(Text(""))
	,_specimen_test_date_time(Text(""))
	,_dilution_ratio(Text(""))
	//,_specimen_position(Text(""))
	,_relevant_clinical_info(Text(""))
	,_specimen_received_date_time(Text(""))
	,_specimen_category(Text(""))
	,_submitting_physician(Text(""))
	,_submitting_department(Text(""))
	,_specimen_shape_and_properties(Text(""))
	,_blood_bag_no(Text(""))
	,_physician_in_charge(Text(""))
	,_department_in_charge(Text("")){
}

/**
 * name: ~HL7OBRSegmentForTest
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7OBRSegmentForTest::~HL7OBRSegmentForTest(void){
}

/**
 * name: set_specimen_barcode
 * brief: 设置样本条码。
 * param: specimen_barcode - 样本条码。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_barcode(const String &specimen_barcode){
	_specimen_barcode=specimen_barcode;
}

/**
 * name: get_specimen_barcode
 * brief: 获取样本条码。
 * param: --
 * return: 返回样本条码。
 */
const String &HL7OBRSegmentForTest::get_specimen_barcode() const{
	return(_specimen_barcode);
}

/**
 * name: set_specimen_no
 * brief: 设置样本编号。
 * param: specimen_no - 样本编号。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_no(const String &specimen_no){
	_specimen_no=specimen_no;
}

/**
 * name: get_specimen_no
 * breif: 获取样本编号。
 * param: --
 * return: 返回样本编号。
 */
const String &HL7OBRSegmentForTest::get_specimen_no() const{
	return(_specimen_no);
}

/**
 * name: set_universal_service_id
 * brief: 设置指定的通用服务标识符。
 * param: index - 通用服务标示符索引编号。
 *        universal_service_id - 通用服务标识符。
 * return: --
 */
void HL7OBRSegmentForTest::set_universal_service_id(
	const unsigned int index,const String &universal_service_id){
	assert((index>=0)&&(index<2));
	_universal_service_id[index]=universal_service_id;
}

/**
 * name: get_universal_service_id
 * brief: 获取指定的通用服务标识符。
 * param: index - 通用服务标示符索引编号。
 * return: 返回指定的通用服务标识符。
 */
const String &HL7OBRSegmentForTest::get_universal_service_id(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_universal_service_id[index]);
}

/**
 * name: set_is_emergency
 * brief: 设置是否为急诊。
 * param: is_emergency - 是否为急诊。
 * return: --
 */
void HL7OBRSegmentForTest::set_is_emergency(const String &is_emergency){
	_is_emergency=is_emergency;
}

/**
 * name: get_is_emergency
 * brief: 获取是否为急诊。
 * param: --
 * return: 返回是否为急诊。
 */
const String &HL7OBRSegmentForTest::get_is_emergency() const{
	return(_is_emergency);
}

/**
 * name: set_specimen_collect_date_time
 * brief: 设置样本采集日期时间。
 * param: specimen_collect_date_time - 样本采集日期时间（格式：20150122102330）。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_collect_date_time(const String &specimen_collect_date_time){
	_specimen_collect_date_time=specimen_collect_date_time;
}

/**
 * name: get_specimen_collect_date_time
 * brief: 获取样本采集日期时间。
 * param: --
 * return: 返回样本采集日期时间。
 */
const String &HL7OBRSegmentForTest::get_specimen_collect_date_time() const{
	return(_specimen_collect_date_time);
}

/**
 * name: set_specimen_test_date_time
 * brief: 设置样本测试日期时间。
 * param: specimen_test_date_time - 样本测试日期时间。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_test_date_time(const String &specimen_test_date_time){
	_specimen_test_date_time=specimen_test_date_time;
}

/**
 * name: get_specimen_test_date_time
 * brief: 获取样本测试日期时间。
 * param: --
 * return: 返回样本测试日期时间。
 */
const String &HL7OBRSegmentForTest::get_specimen_test_date_time() const{
	return(_specimen_test_date_time);
}

/**
 * name: set_dilution_ratio
 * breif: 设置稀释倍数。
 * param: dilution_ratio - 稀释倍数。
 * return: --
 */
void HL7OBRSegmentForTest::set_dilution_ratio(const String &dilution_ratio){
	_dilution_ratio=dilution_ratio;
}

/**
 * name: get_dilution_ratio
 * breif: 获取稀释倍数。
 * param: --
 * return: 返回稀释倍数。
 */
const String &HL7OBRSegmentForTest::get_dilution_ratio() const{
	return(_dilution_ratio);
}

/**
 * name: set_specimen_position
 * breif: 设置样本位置。
 * param: index - 索引编号。
 *        specimen_position - 样本位置。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_position(
	const unsigned int index,const String &specimen_position){
	assert((index>=0)&&(index<2));
	_specimen_position[index]=specimen_position;
}

/**
 * name: get_specimen_position
 * breif: 获取样本位置。
 * param: index - 索引编号。
 * return: 返回样本位置。
 */
const String &HL7OBRSegmentForTest::get_specimen_position(const unsigned int index) const{
	assert((index>=0)&&(index<2));
	return(_specimen_position[index]);
}

/**
 * name: set_relevant_clinical_info
 * breif: 设置相关临床信息。
 * param: relevant_clinical_info - 相关临床信息。
 * return: --
 */
void HL7OBRSegmentForTest::set_relevant_clinical_info(const String &relevant_clinical_info){
	_relevant_clinical_info=relevant_clinical_info;
}

/**
 * name: get_relevant_clinical_info
 * breif: 获取相关临床信息。
 * param: --
 * return: 返回相关临床信息。
 */
const String &HL7OBRSegmentForTest::get_relevant_clinical_info() const{
	return(_relevant_clinical_info);
}

/**
 * name: set_specimen_received_date_time
 * brief: 设置样本送检时间。
 * param: specimen_received_date_time - 样本送检时间。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_received_date_time(const String &specimen_received_date_time){
	_specimen_received_date_time=specimen_received_date_time;
}

/**
 * name: get_specimen_received_date_time
 * brief: 获取样本送检时间。
 * param: --
 * return: 返回样本送检时间。
 */
const String &HL7OBRSegmentForTest::get_specimen_received_date_time() const{
	return(_specimen_received_date_time);
}

/**
 * name: set_specimen_category
 * brief: 设置样本类别。
 * param: specimen_category - 样本类别。
 * return: --
 */
void HL7OBRSegmentForTest::set_specimen_category(const String &specimen_category){
	_specimen_category=specimen_category;
}

/**
 * name: get_specimen_category
 * brief: 获取样本类别。
 * param: --
 * return: 返回样本类别。
 */
const String &HL7OBRSegmentForTest::get_specimen_category() const{
	return(_specimen_category);
}

/**
 * name: set_submitting_physician
 * brief: 设置送检医生。
 * param: submitting_physician - 送检医生。
 * return: --
 */
void HL7OBRSegmentForTest::set_submitting_physician(const String &submitting_physician){
	_submitting_physician=submitting_physician;
}

/**
 * name: get_submitting_physician
 * brief: 获取送检医生。
 * param: --
 * return: 返回送检医生。
 */
const String &HL7OBRSegmentForTest::get_submitting_physician() const{
	return(_submitting_physician);
}

/**
 * name: set_submitting_department
 * breif: 设置送检科室。
 * param: submitting_department - 送检科室。
 * return: --
 */
void HL7OBRSegmentForTest::set_submitting_department(const String &submitting_department){
	_submitting_department=submitting_department;
}

/**
 * name: get_submitting_department
 * breif: 获取送检科室。
 * param: --
 * return: 返回送检科室。
 */
const String &HL7OBRSegmentForTest::get_submitting_department() const{
	return(_submitting_department);
}

/**
 * name: set_specimen_shape_and_properties
 * breif: 设置样本性状。
 * param: specimen_shape_and_properties
 * return: 返回送检科室。
 */
void HL7OBRSegmentForTest::set_specimen_shape_and_properties(const String &specimen_shape_and_properties){
	_specimen_shape_and_properties=specimen_shape_and_properties;
}

/**
 * name: get_specimen_shape_and_properties
 * breif: 获取样本性状。
 * param: --
 * return: 返回样本性状。
 */
const String &HL7OBRSegmentForTest::get_specimen_shape_and_properties() const{
	return(_specimen_shape_and_properties);
}

/**
 * name: set_blood_bag_no
 * brief: 设置血袋编号。
 * param: blood_bag_no - 血袋编号。
 * return: --
 */
void HL7OBRSegmentForTest::set_blood_bag_no(const String &blood_bag_no){
	_blood_bag_no=blood_bag_no;
}

/**
 * name: get_blood_bag_no
 * brief: 获取血袋编号。
 * param: --
 * return: 返回血袋编号。
 */
const String &HL7OBRSegmentForTest::get_blood_bag_no() const{
	return(_blood_bag_no);
}

/**
 * name: set_physician_in_charge
 * brief: 设置主治医生。
 * param: physician_in_charge - 主治医生。
 * return: --
 */
void HL7OBRSegmentForTest::set_physician_in_charge(const String &physician_in_charge){
	_physician_in_charge=physician_in_charge;
}

/**
 * name: get_physician_in_charge
 * brief: 获取主治医生。
 * param: --
 * return: 返回主治医生。
 */
const String &HL7OBRSegmentForTest::get_physician_in_charge() const{
	return(_physician_in_charge);
}

/**
 * name: set_department_in_charge
 * breif: 设置责任科室。
 * param: department_in_charge - 责任科室。
 * return: --
 */
void HL7OBRSegmentForTest::set_department_in_charge(const String &department_in_charge){
	_department_in_charge=department_in_charge;
}

/**
 * name: get_department_in_charge
 * breif: 获取责任科室。
 * param: --
 * return: 返回责任科室。
 */
const String &HL7OBRSegmentForTest::get_department_in_charge() const{
	return(_department_in_charge);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7OBRSegmentForTest::set_field(const unsigned int no,const String &content){
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
		//unfinished: 是否需要检测当前样本条码是否为数字？？？
		//3-2.设置当前“域”的内容。
		_specimen_barcode=content;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//unfinished: 是否需要检测当前样本编号是否为数字？？？
		//4-1.设置当前“域”的内容。
		_specimen_no=content;
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
	else if(6==no){
		//6-1.判断当前准备设置“域”的内容是否合法。
		if((!content.IsEmpty())&&(Text("Y")!=content)&&
			(Text("N")!=content)){
			return(-5);
		}
		//6-2.设置当前“域”的内容。
		_is_emergency=content;
		//6-3.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){
		//7-1.判断当前准备设置“域”的内容是否合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-6);
		}
		//7-2.设置当前“域”的内容。
		_specimen_collect_date_time=content;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){
		//8-1.判断当前准备设置“域”的内容是否合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-7);
		}
		//8-2.设置当前“域”的内容。
		_specimen_test_date_time=content;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//unfinished: 这里是否需要判断稀释倍数为数字？？
		//10-1.设置当前“域”的内容。
		_dilution_ratio=content;
		//10-2.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望设置“段”的第十一个“域”。
	else if(11==no){
		//11-1.声明当前操作所需变量。
		String contents[2];
		//11-2.分析当前准备设置“域”的内容，并且判断内容是否合法。
		if(extract_group_content_from_field_content(
			content,contents,2)<0){
			return(-8);
		}
		if((contents[0].IsEmpty())&&(contents[1].IsEmpty())){
		}else if((!contents[0].IsEmpty())&&(!contents[1].IsEmpty())){
			//unfinished: 这里是否需要检测内容为数字？？
		}else{
			return(-9);
		}
		//11-3.设置当前“域”的内容。
		_specimen_position[0]=contents[0];
		_specimen_position[1]=contents[1];
		//11-4.程序运行到此成功返回。
		return(1);
	}
	//12.如果当前期望设置“段”的第十二个“域”。
	else if(12==no){//忽略。
		return(0);
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){
		//14-1.设置当前“域”的内容。
		_relevant_clinical_info=content;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){
		//15-1.判断当前准备设置“域”的内容是否合法。
		if((!content.IsEmpty())&&((14!=content.GetLength())||
			(!DataConverter::is_number(content)))){
			return(-10);
		}
		//15-2.设置当前“域”的内容。
		_specimen_received_date_time=content;
		//15-3.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){
		//16-1.判断当前准备设置“域”的内容是否合法。
		if(content.IsEmpty()){
			return(-11);
		}
		//16-2.设置当前“域”的内容。
		_specimen_category=content;
		//16-3.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){
		//17-1.设置当前“域”的内容。
		_submitting_physician=content;
		//17-1.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){
		//18-1.设置当前“域”的内容。
		_submitting_department=content;
		//18-1.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望设置“段”的第十九个“域”。
	else if(19==no){
		//19-1.设置当前“域”的内容。
		_specimen_shape_and_properties=content;
		//19-1.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望设置“段”的第二十个“域”。
	else if(20==no){
		//20-1.设置当前“域”的内容。
		_blood_bag_no=content;
		//unfinished: 是否应该判断当前血袋编号为数字？？？
		//20-1.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望设置“段”的第二十一个“域”。
	else if(21==no){
		//21-1.设置当前“域”的内容。
		_physician_in_charge=content;
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22.如果当前期望设置“段”的第二十二个“域”。
	else if(22==no){
		//22-1.设置当前“域”的内容。
		_department_in_charge=content;
		//22-2.程序运行到此成功返回。
		return(1);
	}
	//23~48.如果当前期望设置“段”的第二十三到第四十八个“域”。
	else if((no>=23)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前设置为的其它“域”，则返回错误。
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
int HL7OBRSegmentForTest::get_field(const unsigned int no,String &content) const{
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
		if(_specimen_barcode.IsEmpty()){
			return(-2);
		}
		//unfinished: 是否需要检测当前样本条码是否为数字？？？
		//3-2.获取当前“域”的内容。
		content=_specimen_barcode;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//unfinished: 是否需要检测当前样本编号是否为数字？？？
		//4-1.获取当前“域”的内容。
		content=_specimen_no;
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
		content=_universal_service_id[0];
		content+=GROUP_SEPARATOR;
		content+=_universal_service_id[1];
		//5-3.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){
		//6-1.判断当前准备获取“域”的内容是否合法。
		if((!_is_emergency.IsEmpty())&&
			(Text("Y")!=_is_emergency)&&
			(Text("N")!=_is_emergency)){
			return(-4);
		}
		//6-2.获取当前“域”的内容。
		content=_is_emergency;
		//6-3.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){
		//7-1.判断当前准备获取“域”的内容是否合法。
		if((!_specimen_collect_date_time.IsEmpty())&&
			((14!=_specimen_collect_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_collect_date_time)))){
			return(-5);
		}
		//7-2.获取当前“域”的内容。
		content=_specimen_collect_date_time;
		//7-3.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){
		//8-1.判断当前准备获取“域”的内容是否合法。
		if((!_specimen_test_date_time.IsEmpty())&&
			((14!=_specimen_test_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_test_date_time)))){
			return(-6);
		}
		//8-2.获取当前“域”的内容。
		content=_specimen_test_date_time;
		//8-3.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){//忽略。
		return(0);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//unfinished: 这里是否需要判断稀释倍数为数字？？
		//10-1.获取当前“域”的内容。
		content=_dilution_ratio;
		//10-2.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){
		//11-1.分析当前准备获取“域”的内容，并且判断内容是否合法。
		if((_specimen_position[0].IsEmpty())&&
			(_specimen_position[1].IsEmpty())){
		}else if((!_specimen_position[0].IsEmpty())&&
			(!_specimen_position[1].IsEmpty())){
			//unfinished: 这里是否需要检测内容为数字？？
		}else{
			return(-7);
		}
		//11-3.获取当前“域”的内容。
		content=_specimen_position[0];
		content+=GROUP_SEPARATOR;
		content+=_specimen_position[1];
		//11-4.程序运行到此成功返回。
		return(1);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){//忽略。
		return(0);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){//忽略。
		return(0);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){
		//14-1.获取当前“域”的内容。
		content=_relevant_clinical_info;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){
		//15-1.判断当前准备获取“域”的内容是否合法。
		if((!_specimen_received_date_time.IsEmpty())&&
			((14!=_specimen_received_date_time.GetLength())||
			(!DataConverter::is_number(_specimen_received_date_time)))){
			return(-8);
		}
		//15-2.获取当前“域”的内容。
		content=_specimen_received_date_time;
		//15-3.程序运行到此成功返回。
		return(1);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){
		//16-1.判断当前准备获取“域”的内容是否合法。
		if(_specimen_category.IsEmpty()){
			return(-9);
		}
		//16-2.获取当前“域”的内容。
		content=_specimen_category;
		//16-3.程序运行到此成功返回。
		return(1);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){
		//17-1.获取当前“域”的内容。
		content=_submitting_physician;
		//17-1.程序运行到此成功返回。
		return(1);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){
		//18-1.获取当前“域”的内容。
		content=_submitting_department;
		//18-1.程序运行到此成功返回。
		return(1);
	}
	//19.如果当前期望获取“段”的第十九个“域”。
	else if(19==no){
		//19-1.获取当前“域”的内容。
		content=_specimen_shape_and_properties;
		//19-1.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望获取“段”的第二十个“域”。
	else if(20==no){
		//20-1.获取当前“域”的内容。
		content=_blood_bag_no;
		//unfinished: 是否应该判断当前血袋编号为数字？？？
		//20-1.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望获取“段”的第二十一个“域”。
	else if(21==no){
		//21-1.获取当前“域”的内容。
		content=_physician_in_charge;
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22.如果当前期望获取“段”的第二十二个“域”。
	else if(22==no){
		//22-1.获取当前“域”的内容。
		content=_department_in_charge;
		//22-2.程序运行到此成功返回。
		return(1);
	}
	//23~48.如果当前期望获取“段”的第二十三到第四十八个“域”。
	else if((no>=23)&&(no<=48)){//忽略。
		return(0);
	}
	//49.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-10);
	}
}