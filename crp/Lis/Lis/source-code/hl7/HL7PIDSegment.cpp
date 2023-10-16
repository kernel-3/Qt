#include"stdafx.h"
#include"HL7PIDSegment.h"

//初始化静态变量。
const String HL7PIDSegment::SegmentName(Text("PID"));

/**
 * name: HL7PIDSegment
 * brief: 构造函数。
 * param: --
 * return: --
 */
HL7PIDSegment::HL7PIDSegment(void)
	:HL7Segment(SegmentName,31)
	,_segment_id(Text("1"))
	,_patient_id(Text(""))
	,_medical_record_no(Text(""))
	,_bed_no(Text(""))
	,_patient_name(Text(""))
	,_impatient_area(Text(""))
	,_date_time_of_birth(Text(""))
	,_sex(Text(""))
	,_blood_type(Text(""))
	,_address(Text(""))
	,_postcode(Text(""))
	,_phone_number(Text(""))
	,_patient_category(Text(""))
	,_medical_insurance_account(Text(""))
	,_charge_type(Text(""))
	,_nation(Text(""))
	,_native_place(Text(""))
	,_comment(Text(""))
	,_nationality(Text("")){
}

/**
 * name: ~HL7PIDSegment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7PIDSegment::~HL7PIDSegment(void){
}

/**
 * name: get_segment_id
 * breif: 获取“段”的ID。
 * param: --
 * return: 返回“段”的ID。
 */
const String &HL7PIDSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_patient_id
 * breif: 设置病人ID（住院号）。
 * param: patient_id - 病人ID。
 * return: --
 */
void HL7PIDSegment::set_patient_id(const String &patient_id){
	_patient_id=patient_id;
}

/**
 * name: get_patient_id
 * breif: 获取病人ID（住院号）。
 * param: --
 * return: 返回病人ID。
 */
const String &HL7PIDSegment::get_patient_id() const{
	return(_patient_id);
}

/**
 * name: set_medical_record_no
 * breif: 设置病历号。
 * param: medical_record_no - 病历号。
 * return: --
 */
void HL7PIDSegment::set_medical_record_no(const String &medical_record_no){
	_medical_record_no=medical_record_no;
}

/**
 * name: get_medical_record_no
 * breif: 获取病历号。
 * param: --
 * return: 返回病历号。
 */
const String &HL7PIDSegment::get_medical_record_no() const{
	return(_medical_record_no);
}

/**
 * name: set_bed_no
 * breif: 设置床号。
 * param: bed_no - 床号。
 * return: --
 */
void HL7PIDSegment::set_bed_no(const String &bed_no){
	_bed_no=bed_no;
}

/**
 * name: get_bed_no
 * breif: 获取床号。
 * param: --
 * return: 返回床号。
 */
const String &HL7PIDSegment::get_bed_no() const{
	return(_bed_no);
}

/**
 * name: set_patient_name
 * breif: 设置病人名称。
 * param: patient_name - 病人名称。
 * return: --
 */
void HL7PIDSegment::set_patient_name(const String &patient_name){
	_patient_name=patient_name;
}

/**
 * name: get_patient_name
 * breif: 获取病人名称。
 * param: --
 * return: 返回病人名称。
 */
const String &HL7PIDSegment::get_patient_name() const{
	return(_patient_name);
}

/**
 * name: set_impatient_area
 * breif: 设置病区。
 * param: impatient_area - 病区。
 * return: --
 */
void HL7PIDSegment::set_impatient_area(const String &impatient_area){
	_impatient_area=impatient_area;
}

/**
 * name: get_impatient_area
 * breif: 获取病区。
 * param: --
 * return: 返回病区。
 */
const String &HL7PIDSegment::get_impatient_area() const{
	return(_impatient_area);
}

/**
 * name: set_date_time_of_birth
 * brief: 设置出生日期时间。 
 * param: date_time_of_birth - 出生日期时间。
 * return: --
 */
void HL7PIDSegment::set_date_time_of_birth(const String &date_time_of_birth){
	_date_time_of_birth=date_time_of_birth;
}

/**
 * name: get_date_time_of_birth
 * brief: 获取出生日期时间。 
 * param: --
 * return: 返回出生日期时间。
 */
const String &HL7PIDSegment::get_date_time_of_birth() const{
	return(_date_time_of_birth);
}

/**
 * name: set_sex
 * brief: 设置性别。
 * param: sex - 性别。
 * return: --
 */
void HL7PIDSegment::set_sex(const String &sex){
	_sex=sex;
}

/**
 * name: get_sex
 * brief: 获取性别。
 * param: --
 * return: 返回性别。
 */
const String &HL7PIDSegment::get_sex() const{
	return(_sex);
}

/**
 * name: set_blood_type
 * brief: 设置血型。
 * param: blood_type - 血型。
 * return: --
 */
void HL7PIDSegment::set_blood_type(const String &blood_type){
	_blood_type=blood_type;
}

/**
 * name: get_blood_type
 * brief: 获取血型。
 * param: --
 * return: 返回血型。
 */
const String &HL7PIDSegment::get_blood_type() const{
	return(_blood_type);
}

/**
 * name: set_address
 * brief: 设置地址。
 * param: address - 地址。
 * return: --
 */
void HL7PIDSegment::set_address(const String &address){
	_address=address;
}

/**
 * name: get_address
 * brief: 获取地址。
 * param: --
 * return: 返回地址。
 */
const String &HL7PIDSegment::get_address() const{
	return(_address);
}

/**
 * name: set_postcode
 * brief: 设置邮编。
 * param: postcode - 邮编。
 * return: --
 */
void HL7PIDSegment::set_postcode(const String &postcode){
	_postcode=postcode;
}

/**
 * name: get_postcode
 * brief: 获取邮编。
 * param: --
 * return: 返回邮编。
 */
const String &HL7PIDSegment::get_postcode() const{
	return(_postcode);
}

/**
 * name: set_phone_number
 * brief: 设置电话号码。
 * param: phone_number - 电话号码。
 * return: --
 */
void HL7PIDSegment::set_phone_number(const String &phone_number){
	_phone_number=phone_number;
}

/**
 * name: get_phone_number
 * brief: 获取电话号码。
 * param: --
 * return: 返回电话号码。
 */
const String &HL7PIDSegment::get_phone_number() const{
	return(_phone_number);
}

/**
 * name: set_patient_category
 * brief: 设置病人类别。
 * param: patient_category - 病人类别。
 * return: --
 */
void HL7PIDSegment::set_patient_category(const String &patient_category){
	_patient_category=patient_category;
}

/**
 * name: get_patient_category
 * brief: 获取病人类别。
 * param: --
 * return: 返回病人类别。
 */
const String &HL7PIDSegment::get_patient_category() const{
	return(_patient_category);
}

/**
 * name: set_medical_insurance_account
 * brief: 设置医保账号。
 * param: medical_insurance_account - 医保账号。
 * return: --
 */
void HL7PIDSegment::set_medical_insurance_account(const String &medical_insurance_account){
	_medical_insurance_account=medical_insurance_account;
}

/**
 * name: get_medical_insurance_account
 * brief: 获取医保账号。
 * param: --
 * return: 返回医保账号。
 */
const String &HL7PIDSegment::get_medical_insurance_account() const{
	return(_medical_insurance_account);
}

/**
 * name: set_charge_type
 * brief: 设置付费类型。
 * param: charge_type - 付费类型。
 * return: --
 */
void HL7PIDSegment::set_charge_type(const String &charge_type){
	_charge_type=charge_type;
}

/**
 * name: get_charge_type
 * breif: 获取付费类型。
 * param: --
 * return: --
 */
const String &HL7PIDSegment::get_charge_type() const{
	return(_charge_type);
}

/**
 * name: set_nation
 * breif: 设置民族。
 * param: nation - 民族。
 * return: --
 */
void HL7PIDSegment::set_nation(const String &nation){
	_nation=nation;
}

/**
 * name: get_nation
 * brief: 获取民族。
 * param: --
 * return: 返回民族。
 */
const String &HL7PIDSegment::get_nation() const{
	return(_nation);
}

/**
 * name: set_native_place
 * brief: 设置籍贯。
 * param: native_place - 籍贯。
 * return: --
 */
void HL7PIDSegment::set_native_place(const String &native_place){
	_native_place=native_place;
}

/**
 * name: get_native_place
 * brief: 获取籍贯。
 * param: --
 * return: 返回籍贯。
 */
const String &HL7PIDSegment::get_native_place() const{
	return(_native_place);
}

/**
 * name: set_comment
 * brief: 设置备注。
 * param: --
 * return: 返回备注。
 */
void HL7PIDSegment::set_comment(const String &comment){
	_comment=comment;
}

/**
 * name: get_comment
 * brief: 获取备注。
 * param: --
 * return: 返回备注。
 */
const String &HL7PIDSegment::get_comment() const{
	return(_comment);
}

/**
 * name: set_nationality
 * brief: 设置国籍。
 * param: nationality - 国籍。
 * return: --
 */
void HL7PIDSegment::set_nationality(const String &nationality){
	_nationality=nationality;
}

/**
 * name: get_nationality
 * brief: 获取国籍。
 * param: --
 * return: 返回国籍。
 */
const String &HL7PIDSegment::get_nationality() const{
	return(_nationality);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7PIDSegment::set_field(const unsigned int no,const String &content){
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
		if(content!=_segment_id){
			return(-2);
		}
		//2-1.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望设置“段”的第三个“域”。
	else if(3==no){
		//3-1.设置当前“域”的内容。
		_patient_id=content;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望设置“段”的第四个“域”。
	else if(4==no){
		//4-1.设置当前“域”的内容。
		_medical_record_no=content;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望设置“段”的第五个“域”。
	else if(5==no){
		//5-1.设置第五个“域”的内容。
		_bed_no=content;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望设置“段”的第六个“域”。
	else if(6==no){
		//6-1.设置第六个“域”的内容。
		_patient_name=content;
		//6-2.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望设置“段”的第七个“域”。
	else if(7==no){
		//7-1.设置第七个“域”的内容。
		_impatient_area=content;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望设置“段”的第八个“域”。
	else if(8==no){
		//8-1.设置第八个“域”的内容。
		_date_time_of_birth=content;
		//8-2.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望设置“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备设置第九个“域”的内容不合法。
		if((Text("M")!=content)&&(Text("F")!=content)&&
			(Text("O")!=content)&&(Text("U")!=content)){
			return(-3);
		}
		//9-2.设置第九个“域”的内容。
		_sex=content;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望设置“段”的第十个“域”。
	else if(10==no){
		//10-1.设置第十个“域”的内容。
		_blood_type=content;
		//10-2.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望设置“段”的第十一个“域”。
	else if(11==no){//忽略。
		return(0);
	}
	//12.如果当前期望设置“段”的第十二个“域”。
	else if(12==no){
		//12-1.设置第十二个“域”的内容。
		_address=content;
		//12-2.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望设置“段”的第十三个“域”。
	else if(13==no){
		//13-1.设置第十三个“域”的内容。
		_postcode=content;
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望设置“段”的第十四个“域”。
	else if(14==no){
		//14-1.设置第十三个“域”的内容。
		_phone_number=content;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望设置“段”的第十五个“域”。
	else if(15==no){//忽略。
		return(0);
	}
	//16.如果当前期望设置“段”的第十六个“域”。
	else if(16==no){//忽略。
		return(0);
	}
	//17.如果当前期望设置“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望设置“段”的第十八个“域”。
	else if(18==no){//忽略。
		return(0);
	}
	//19.如果当前期望设置“段”的第十九个“域”。
	else if(19==no){
		//19-1.设置第十九个“域”的内容。
		_patient_category=content;
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望设置“段”的第二十个“域”。
	else if(20==no){
		//20-1.设置第二十个“域”的内容。
		_medical_insurance_account=content;
		//20-2.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望设置“段”的第二十一个“域”。
	else if(21==no){
		//21-1.设置第二十一个“域”的内容。
		_charge_type=content;
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22.如果当前期望设置“段”的第二十二个“域”。
	else if(22==no){//忽略。
		return(0);
	}
	//23.如果当前期望设置“段”的第二十三个“域”。
	else if(23==no){
		//23-1.设置第二十三个“域”的内容。
		_nation=content;
		//23-2.程序运行到此成功返回。
		return(1);
	}
	//24.如果当前期望设置“段”的第二十四个“域”。
	else if(24==no){
		//24-1.设置第二十四个“域”的内容。
		_native_place=content;
		//24-2.程序运行到此成功返回。
		return(1);
	}
	//25.如果当前期望设置“段”的第二十五个“域”。
	else if(25==no){//忽略。
		return(0);
	}
	//26.如果当前期望设置“段”的第二十六个“域”。
	else if(26==no){//忽略。
		return(0);
	}
	//27.如果当前期望设置“段”的第二十七个“域”。
	else if(27==no){
		//27-1.设置第二十七个“域”的内容。
		_comment=content;
		//27-2.程序运行到此成功返回。
		return(1);
	}
	//28.如果当前期望设置“段”的第二十八个“域”。
	else if(28==no){//忽略。
		return(0);
	}
	//29.如果当前期望设置“段”的第二十九个“域”。
	else if(29==no){
		//29-1.设置第二十九个“域”的内容。
		_nationality=content;
		//29-2.程序运行到此成功返回。
		return(1);
	}
	//30.如果当前期望设置“段”的第三十个“域”。
	else if(30==no){//忽略。
		return(0);
	}
	//31.如果当前期望设置“段”的第三十一个“域”。
	else if(31==no){//忽略。
		return(0);
	}
	//32.如果当前设置为的其它“域”，则返回错误。
	else{
		return(-4);
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
int HL7PIDSegment::get_field(const unsigned int no,String &content) const{
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
		//2-1.获取第二个“域”的内容。
		content=_segment_id;
		//2-2.程序运行到此成功返回。
		return(1);
	}
	//3.如果当前期望获取“段”的第三个“域”。
	else if(3==no){
		//3-1.获取当前“域”的内容。
		content=_patient_id;
		//3-2.程序运行到此成功返回。
		return(1);
	}
	//4.如果当前期望获取“段”的第四个“域”。
	else if(4==no){
		//4-1.获取当前“域”的内容。
		content=_medical_record_no;
		//4-2.程序运行到此成功返回。
		return(1);
	}
	//5.如果当前期望获取“段”的第五个“域”。
	else if(5==no){
		//5-1.获取第五个“域”的内容。
		content=_bed_no;
		//5-2.程序运行到此成功返回。
		return(1);
	}
	//6.如果当前期望获取“段”的第六个“域”。
	else if(6==no){
		//6-1.获取第六个“域”的内容。
		content=_patient_name;
		//6-2.程序运行到此成功返回。
		return(1);
	}
	//7.如果当前期望获取“段”的第七个“域”。
	else if(7==no){
		//7-1.获取第七个“域”的内容。
		content=_impatient_area;
		//7-2.程序运行到此成功返回。
		return(1);
	}
	//8.如果当前期望获取“段”的第八个“域”。
	else if(8==no){
		//8-1.获取第八个“域”的内容。
		content=_date_time_of_birth;
		//8-2.程序运行到此成功返回。
		return(1);
	}
	//9.如果当前期望获取“段”的第九个“域”。
	else if(9==no){
		//9-1.如果当前准备获取第九个“域”的内容不合法。
		if((Text("M")!=_sex)&&(Text("F")!=_sex)&&
			(Text("O")!=_sex)&&(Text("U")!=_sex)){
			return(-2);
		}
		//9-2.获取第九个“域”的内容。
		content=_sex;
		//9-3.程序运行到此成功返回。
		return(1);
	}
	//10.如果当前期望获取“段”的第十个“域”。
	else if(10==no){
		//10-1.获取第十个“域”的内容。
		content=_blood_type;
		//10-2.程序运行到此成功返回。
		return(1);
	}
	//11.如果当前期望获取“段”的第十一个“域”。
	else if(11==no){//忽略。
		return(0);
	}
	//12.如果当前期望获取“段”的第十二个“域”。
	else if(12==no){
		//12-1.获取第十二个“域”的内容。
		content=_address;
		//12-2.程序运行到此成功返回。
		return(1);
	}
	//13.如果当前期望获取“段”的第十三个“域”。
	else if(13==no){
		//13-1.获取第十三个“域”的内容。
		content=_postcode;
		//13-2.程序运行到此成功返回。
		return(1);
	}
	//14.如果当前期望获取“段”的第十四个“域”。
	else if(14==no){
		//14-1.获取第十四个“域”的内容。
		content=_phone_number;
		//14-2.程序运行到此成功返回。
		return(1);
	}
	//15.如果当前期望获取“段”的第十五个“域”。
	else if(15==no){//忽略。
		return(0);
	}
	//16.如果当前期望获取“段”的第十六个“域”。
	else if(16==no){//忽略。
		return(0);
	}
	//17.如果当前期望获取“段”的第十七个“域”。
	else if(17==no){//忽略。
		return(0);
	}
	//18.如果当前期望获取“段”的第十八个“域”。
	else if(18==no){//忽略。
		return(0);
	}
	//19.如果当前期望获取“段”的第十九个“域”。
	else if(19==no){
		//19-1.获取第十九个“域”的内容。
		content=_patient_category;
		//19-2.程序运行到此成功返回。
		return(1);
	}
	//20.如果当前期望获取“段”的第二十个“域”。
	else if(20==no){
		//20-1.获取第二十个“域”的内容。
		content=_medical_insurance_account;
		//20-2.程序运行到此成功返回。
		return(1);
	}
	//21.如果当前期望获取“段”的第二十一个“域”。
	else if(21==no){
		//21-1.获取第二十一个“域”的内容。
		content=_charge_type;
		//21-2.程序运行到此成功返回。
		return(1);
	}
	//22.如果当前期望获取“段”的第二十二个“域”。
	else if(22==no){//忽略。
		return(0);
	}
	//23.如果当前期望获取“段”的第二十三个“域”。
	else if(23==no){
		//23-1.获取第二十三个“域”的内容。
		content=_nation;
		//23-2.程序运行到此成功返回。
		return(1);
	}
	//24.如果当前期望获取“段”的第二十四个“域”。
	else if(24==no){
		//24-1.获取第二十四个“域”的内容。
		content=_native_place;
		//24-2.程序运行到此成功返回。
		return(1);
	}
	//25.如果当前期望获取“段”的第二十五个“域”。
	else if(25==no){//忽略。
		return(0);
	}
	//26.如果当前期望获取“段”的第二十六个“域”。
	else if(26==no){//忽略。
		return(0);
	}
	//27.如果当前期望获取“段”的第二十七个“域”。
	else if(27==no){
		//27-1.获取第二十七个“域”的内容。
		content=_comment;
		//27-2.程序运行到此成功返回。
		return(1);
	}
	//28.如果当前期望获取“段”的第二十八个“域”。
	else if(28==no){//忽略。
		return(0);
	}
	//29.如果当前期望获取“段”的第二十九个“域”。
	else if(29==no){
		//29-1.获取第二十九个“域”的内容。
		content=_nationality;
		//29-2.程序运行到此成功返回。
		return(1);
	}
	//30.如果当前期望获取“段”的第三十个“域”。
	else if(30==no){//忽略。
		return(0);
	}
	//31.如果当前期望获取“段”的第三十一个“域”。
	else if(31==no){//忽略。
		return(0);
	}
	//32.如果当前获取为的其它“域”，则返回错误。
	else{
		return(-3);
	}
}