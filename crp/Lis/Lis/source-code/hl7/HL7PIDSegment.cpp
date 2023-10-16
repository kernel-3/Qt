#include"stdafx.h"
#include"HL7PIDSegment.h"

//��ʼ����̬������
const String HL7PIDSegment::SegmentName(Text("PID"));

/**
 * name: HL7PIDSegment
 * brief: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
HL7PIDSegment::~HL7PIDSegment(void){
}

/**
 * name: get_segment_id
 * breif: ��ȡ���Ρ���ID��
 * param: --
 * return: ���ء��Ρ���ID��
 */
const String &HL7PIDSegment::get_segment_id() const{
	return(_segment_id);
}

/**
 * name: set_patient_id
 * breif: ���ò���ID��סԺ�ţ���
 * param: patient_id - ����ID��
 * return: --
 */
void HL7PIDSegment::set_patient_id(const String &patient_id){
	_patient_id=patient_id;
}

/**
 * name: get_patient_id
 * breif: ��ȡ����ID��סԺ�ţ���
 * param: --
 * return: ���ز���ID��
 */
const String &HL7PIDSegment::get_patient_id() const{
	return(_patient_id);
}

/**
 * name: set_medical_record_no
 * breif: ���ò����š�
 * param: medical_record_no - �����š�
 * return: --
 */
void HL7PIDSegment::set_medical_record_no(const String &medical_record_no){
	_medical_record_no=medical_record_no;
}

/**
 * name: get_medical_record_no
 * breif: ��ȡ�����š�
 * param: --
 * return: ���ز����š�
 */
const String &HL7PIDSegment::get_medical_record_no() const{
	return(_medical_record_no);
}

/**
 * name: set_bed_no
 * breif: ���ô��š�
 * param: bed_no - ���š�
 * return: --
 */
void HL7PIDSegment::set_bed_no(const String &bed_no){
	_bed_no=bed_no;
}

/**
 * name: get_bed_no
 * breif: ��ȡ���š�
 * param: --
 * return: ���ش��š�
 */
const String &HL7PIDSegment::get_bed_no() const{
	return(_bed_no);
}

/**
 * name: set_patient_name
 * breif: ���ò������ơ�
 * param: patient_name - �������ơ�
 * return: --
 */
void HL7PIDSegment::set_patient_name(const String &patient_name){
	_patient_name=patient_name;
}

/**
 * name: get_patient_name
 * breif: ��ȡ�������ơ�
 * param: --
 * return: ���ز������ơ�
 */
const String &HL7PIDSegment::get_patient_name() const{
	return(_patient_name);
}

/**
 * name: set_impatient_area
 * breif: ���ò�����
 * param: impatient_area - ������
 * return: --
 */
void HL7PIDSegment::set_impatient_area(const String &impatient_area){
	_impatient_area=impatient_area;
}

/**
 * name: get_impatient_area
 * breif: ��ȡ������
 * param: --
 * return: ���ز�����
 */
const String &HL7PIDSegment::get_impatient_area() const{
	return(_impatient_area);
}

/**
 * name: set_date_time_of_birth
 * brief: ���ó�������ʱ�䡣 
 * param: date_time_of_birth - ��������ʱ�䡣
 * return: --
 */
void HL7PIDSegment::set_date_time_of_birth(const String &date_time_of_birth){
	_date_time_of_birth=date_time_of_birth;
}

/**
 * name: get_date_time_of_birth
 * brief: ��ȡ��������ʱ�䡣 
 * param: --
 * return: ���س�������ʱ�䡣
 */
const String &HL7PIDSegment::get_date_time_of_birth() const{
	return(_date_time_of_birth);
}

/**
 * name: set_sex
 * brief: �����Ա�
 * param: sex - �Ա�
 * return: --
 */
void HL7PIDSegment::set_sex(const String &sex){
	_sex=sex;
}

/**
 * name: get_sex
 * brief: ��ȡ�Ա�
 * param: --
 * return: �����Ա�
 */
const String &HL7PIDSegment::get_sex() const{
	return(_sex);
}

/**
 * name: set_blood_type
 * brief: ����Ѫ�͡�
 * param: blood_type - Ѫ�͡�
 * return: --
 */
void HL7PIDSegment::set_blood_type(const String &blood_type){
	_blood_type=blood_type;
}

/**
 * name: get_blood_type
 * brief: ��ȡѪ�͡�
 * param: --
 * return: ����Ѫ�͡�
 */
const String &HL7PIDSegment::get_blood_type() const{
	return(_blood_type);
}

/**
 * name: set_address
 * brief: ���õ�ַ��
 * param: address - ��ַ��
 * return: --
 */
void HL7PIDSegment::set_address(const String &address){
	_address=address;
}

/**
 * name: get_address
 * brief: ��ȡ��ַ��
 * param: --
 * return: ���ص�ַ��
 */
const String &HL7PIDSegment::get_address() const{
	return(_address);
}

/**
 * name: set_postcode
 * brief: �����ʱࡣ
 * param: postcode - �ʱࡣ
 * return: --
 */
void HL7PIDSegment::set_postcode(const String &postcode){
	_postcode=postcode;
}

/**
 * name: get_postcode
 * brief: ��ȡ�ʱࡣ
 * param: --
 * return: �����ʱࡣ
 */
const String &HL7PIDSegment::get_postcode() const{
	return(_postcode);
}

/**
 * name: set_phone_number
 * brief: ���õ绰���롣
 * param: phone_number - �绰���롣
 * return: --
 */
void HL7PIDSegment::set_phone_number(const String &phone_number){
	_phone_number=phone_number;
}

/**
 * name: get_phone_number
 * brief: ��ȡ�绰���롣
 * param: --
 * return: ���ص绰���롣
 */
const String &HL7PIDSegment::get_phone_number() const{
	return(_phone_number);
}

/**
 * name: set_patient_category
 * brief: ���ò������
 * param: patient_category - �������
 * return: --
 */
void HL7PIDSegment::set_patient_category(const String &patient_category){
	_patient_category=patient_category;
}

/**
 * name: get_patient_category
 * brief: ��ȡ�������
 * param: --
 * return: ���ز������
 */
const String &HL7PIDSegment::get_patient_category() const{
	return(_patient_category);
}

/**
 * name: set_medical_insurance_account
 * brief: ����ҽ���˺š�
 * param: medical_insurance_account - ҽ���˺š�
 * return: --
 */
void HL7PIDSegment::set_medical_insurance_account(const String &medical_insurance_account){
	_medical_insurance_account=medical_insurance_account;
}

/**
 * name: get_medical_insurance_account
 * brief: ��ȡҽ���˺š�
 * param: --
 * return: ����ҽ���˺š�
 */
const String &HL7PIDSegment::get_medical_insurance_account() const{
	return(_medical_insurance_account);
}

/**
 * name: set_charge_type
 * brief: ���ø������͡�
 * param: charge_type - �������͡�
 * return: --
 */
void HL7PIDSegment::set_charge_type(const String &charge_type){
	_charge_type=charge_type;
}

/**
 * name: get_charge_type
 * breif: ��ȡ�������͡�
 * param: --
 * return: --
 */
const String &HL7PIDSegment::get_charge_type() const{
	return(_charge_type);
}

/**
 * name: set_nation
 * breif: �������塣
 * param: nation - ���塣
 * return: --
 */
void HL7PIDSegment::set_nation(const String &nation){
	_nation=nation;
}

/**
 * name: get_nation
 * brief: ��ȡ���塣
 * param: --
 * return: �������塣
 */
const String &HL7PIDSegment::get_nation() const{
	return(_nation);
}

/**
 * name: set_native_place
 * brief: ���ü��ᡣ
 * param: native_place - ���ᡣ
 * return: --
 */
void HL7PIDSegment::set_native_place(const String &native_place){
	_native_place=native_place;
}

/**
 * name: get_native_place
 * brief: ��ȡ���ᡣ
 * param: --
 * return: ���ؼ��ᡣ
 */
const String &HL7PIDSegment::get_native_place() const{
	return(_native_place);
}

/**
 * name: set_comment
 * brief: ���ñ�ע��
 * param: --
 * return: ���ر�ע��
 */
void HL7PIDSegment::set_comment(const String &comment){
	_comment=comment;
}

/**
 * name: get_comment
 * brief: ��ȡ��ע��
 * param: --
 * return: ���ر�ע��
 */
const String &HL7PIDSegment::get_comment() const{
	return(_comment);
}

/**
 * name: set_nationality
 * brief: ���ù�����
 * param: nationality - ������
 * return: --
 */
void HL7PIDSegment::set_nationality(const String &nationality){
	_nationality=nationality;
}

/**
 * name: get_nationality
 * brief: ��ȡ������
 * param: --
 * return: ���ع�����
 */
const String &HL7PIDSegment::get_nationality() const{
	return(_nationality);
}

/**
 * name: set_field
 * brief: ���õ�ǰ���Ρ���ָ����
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���򡱵����ݡ�
 * return: ����������óɹ�����ֵ�����㣬������ԡ��򡱵������򷵻��㣬
 *         �����������ʧ�ܷ��ظ�����
 */
int HL7PIDSegment::set_field(const unsigned int no,const String &content){
	//1.���û�����Ӧ��������ָ���ġ��򡱣������ж����ý����
	//1-1.���û�����Ӧ��������ָ���ġ��򡱡�
	const int execute_result=HL7Segment::set_field(no,content);
	//1-2.����ɹ�����ָ���ġ��򡱡�
	if(execute_result>0){
		return(1);
	}
	//1-3.�������ָ���ġ���ʧ�ܡ�
	else if(execute_result<0){
		return(-1);
	}
	//2.�����ǰ�������á��Ρ��ĵڶ������򡱡�
	else if(2==no){
		//2-1.�����ǰ׼�����õڶ������򡱵����ݲ��Ϸ���
		if(content!=_segment_id){
			return(-2);
		}
		//2-1.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.���õ�ǰ���򡱵����ݡ�
		_patient_id=content;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ�������á��Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.���õ�ǰ���򡱵����ݡ�
		_medical_record_no=content;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ�������á��Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.���õ�������򡱵����ݡ�
		_bed_no=content;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ�������á��Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.���õ��������򡱵����ݡ�
		_patient_name=content;
		//6-2.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ�������á��Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.���õ��߸����򡱵����ݡ�
		_impatient_area=content;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ�������á��Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.���õڰ˸����򡱵����ݡ�
		_date_time_of_birth=content;
		//8-2.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ�������á��Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼�����õھŸ����򡱵����ݲ��Ϸ���
		if((Text("M")!=content)&&(Text("F")!=content)&&
			(Text("O")!=content)&&(Text("U")!=content)){
			return(-3);
		}
		//9-2.���õھŸ����򡱵����ݡ�
		_sex=content;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ�������á��Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.���õ�ʮ�����򡱵����ݡ�
		_blood_type=content;
		//10-2.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ�������á��Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){//���ԡ�
		return(0);
	}
	//12.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.���õ�ʮ�������򡱵����ݡ�
		_address=content;
		//12-2.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.���õ�ʮ�������򡱵����ݡ�
		_postcode=content;
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ�������á��Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.���õ�ʮ�������򡱵����ݡ�
		_phone_number=content;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ�������á��Ρ��ĵ�ʮ������򡱡�
	else if(15==no){//���ԡ�
		return(0);
	}
	//16.�����ǰ�������á��Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){//���ԡ�
		return(0);
	}
	//17.�����ǰ�������á��Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ�������á��Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){//���ԡ�
		return(0);
	}
	//19.�����ǰ�������á��Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.���õ�ʮ�Ÿ����򡱵����ݡ�
		_patient_category=content;
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ�������á��Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.���õڶ�ʮ�����򡱵����ݡ�
		_medical_insurance_account=content;
		//20-2.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ�������á��Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.���õڶ�ʮһ�����򡱵����ݡ�
		_charge_type=content;
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22.�����ǰ�������á��Ρ��ĵڶ�ʮ�������򡱡�
	else if(22==no){//���ԡ�
		return(0);
	}
	//23.�����ǰ�������á��Ρ��ĵڶ�ʮ�������򡱡�
	else if(23==no){
		//23-1.���õڶ�ʮ�������򡱵����ݡ�
		_nation=content;
		//23-2.�������е��˳ɹ����ء�
		return(1);
	}
	//24.�����ǰ�������á��Ρ��ĵڶ�ʮ�ĸ����򡱡�
	else if(24==no){
		//24-1.���õڶ�ʮ�ĸ����򡱵����ݡ�
		_native_place=content;
		//24-2.�������е��˳ɹ����ء�
		return(1);
	}
	//25.�����ǰ�������á��Ρ��ĵڶ�ʮ������򡱡�
	else if(25==no){//���ԡ�
		return(0);
	}
	//26.�����ǰ�������á��Ρ��ĵڶ�ʮ�������򡱡�
	else if(26==no){//���ԡ�
		return(0);
	}
	//27.�����ǰ�������á��Ρ��ĵڶ�ʮ�߸����򡱡�
	else if(27==no){
		//27-1.���õڶ�ʮ�߸����򡱵����ݡ�
		_comment=content;
		//27-2.�������е��˳ɹ����ء�
		return(1);
	}
	//28.�����ǰ�������á��Ρ��ĵڶ�ʮ�˸����򡱡�
	else if(28==no){//���ԡ�
		return(0);
	}
	//29.�����ǰ�������á��Ρ��ĵڶ�ʮ�Ÿ����򡱡�
	else if(29==no){
		//29-1.���õڶ�ʮ�Ÿ����򡱵����ݡ�
		_nationality=content;
		//29-2.�������е��˳ɹ����ء�
		return(1);
	}
	//30.�����ǰ�������á��Ρ��ĵ���ʮ�����򡱡�
	else if(30==no){//���ԡ�
		return(0);
	}
	//31.�����ǰ�������á��Ρ��ĵ���ʮһ�����򡱡�
	else if(31==no){//���ԡ�
		return(0);
	}
	//32.�����ǰ����Ϊ���������򡱣��򷵻ش���
	else{
		return(-4);
	}
}

/**
 * name: get_field
 * brief: ��ȡ���Ρ���ָ�����򡱵����ݡ�
 * param: no - ���򡱵ı�ţ�ע�⣺��1��ʼ��������
 *        content - ���ء��򡱵����ݡ�
 * return: ����������ݻ�ȡ�ɹ�����ֵ�����㣬������ԡ���
 *         ���ݵĻ�ȡ�����򷵻��㣬����������ݵĻ�ȡʧ��
 *         ���ظ�����
 */
int HL7PIDSegment::get_field(const unsigned int no,String &content) const{
	//1.���û�����Ӧ������ȡָ���ġ��򡱣������жϻ�ȡ�����
	//1-1.���û�����Ӧ������ȡָ���ġ��򡱡�
	const int execute_result=HL7Segment::get_field(no,content);
	//1-2.������û�����Ӧ�����ɹ���ȡָ���ġ��򡱣���ֱ�ӷ��ء�
	if(execute_result>0){
		return(1);
	}
	//1-3.������û�����Ӧ������ȡָ���ġ���ʧ�ܣ���ֱ�ӷ��ء�
	else if(execute_result<0){
		return(-1);
	}
	//2.�����ǰ������ȡ���Ρ��ĵڶ������򡱡�
	else if(2==no){
		//2-1.��ȡ�ڶ������򡱵����ݡ�
		content=_segment_id;
		//2-2.�������е��˳ɹ����ء�
		return(1);
	}
	//3.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(3==no){
		//3-1.��ȡ��ǰ���򡱵����ݡ�
		content=_patient_id;
		//3-2.�������е��˳ɹ����ء�
		return(1);
	}
	//4.�����ǰ������ȡ���Ρ��ĵ��ĸ����򡱡�
	else if(4==no){
		//4-1.��ȡ��ǰ���򡱵����ݡ�
		content=_medical_record_no;
		//4-2.�������е��˳ɹ����ء�
		return(1);
	}
	//5.�����ǰ������ȡ���Ρ��ĵ�������򡱡�
	else if(5==no){
		//5-1.��ȡ��������򡱵����ݡ�
		content=_bed_no;
		//5-2.�������е��˳ɹ����ء�
		return(1);
	}
	//6.�����ǰ������ȡ���Ρ��ĵ��������򡱡�
	else if(6==no){
		//6-1.��ȡ���������򡱵����ݡ�
		content=_patient_name;
		//6-2.�������е��˳ɹ����ء�
		return(1);
	}
	//7.�����ǰ������ȡ���Ρ��ĵ��߸����򡱡�
	else if(7==no){
		//7-1.��ȡ���߸����򡱵����ݡ�
		content=_impatient_area;
		//7-2.�������е��˳ɹ����ء�
		return(1);
	}
	//8.�����ǰ������ȡ���Ρ��ĵڰ˸����򡱡�
	else if(8==no){
		//8-1.��ȡ�ڰ˸����򡱵����ݡ�
		content=_date_time_of_birth;
		//8-2.�������е��˳ɹ����ء�
		return(1);
	}
	//9.�����ǰ������ȡ���Ρ��ĵھŸ����򡱡�
	else if(9==no){
		//9-1.�����ǰ׼����ȡ�ھŸ����򡱵����ݲ��Ϸ���
		if((Text("M")!=_sex)&&(Text("F")!=_sex)&&
			(Text("O")!=_sex)&&(Text("U")!=_sex)){
			return(-2);
		}
		//9-2.��ȡ�ھŸ����򡱵����ݡ�
		content=_sex;
		//9-3.�������е��˳ɹ����ء�
		return(1);
	}
	//10.�����ǰ������ȡ���Ρ��ĵ�ʮ�����򡱡�
	else if(10==no){
		//10-1.��ȡ��ʮ�����򡱵����ݡ�
		content=_blood_type;
		//10-2.�������е��˳ɹ����ء�
		return(1);
	}
	//11.�����ǰ������ȡ���Ρ��ĵ�ʮһ�����򡱡�
	else if(11==no){//���ԡ�
		return(0);
	}
	//12.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(12==no){
		//12-1.��ȡ��ʮ�������򡱵����ݡ�
		content=_address;
		//12-2.�������е��˳ɹ����ء�
		return(1);
	}
	//13.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(13==no){
		//13-1.��ȡ��ʮ�������򡱵����ݡ�
		content=_postcode;
		//13-2.�������е��˳ɹ����ء�
		return(1);
	}
	//14.�����ǰ������ȡ���Ρ��ĵ�ʮ�ĸ����򡱡�
	else if(14==no){
		//14-1.��ȡ��ʮ�ĸ����򡱵����ݡ�
		content=_phone_number;
		//14-2.�������е��˳ɹ����ء�
		return(1);
	}
	//15.�����ǰ������ȡ���Ρ��ĵ�ʮ������򡱡�
	else if(15==no){//���ԡ�
		return(0);
	}
	//16.�����ǰ������ȡ���Ρ��ĵ�ʮ�������򡱡�
	else if(16==no){//���ԡ�
		return(0);
	}
	//17.�����ǰ������ȡ���Ρ��ĵ�ʮ�߸����򡱡�
	else if(17==no){//���ԡ�
		return(0);
	}
	//18.�����ǰ������ȡ���Ρ��ĵ�ʮ�˸����򡱡�
	else if(18==no){//���ԡ�
		return(0);
	}
	//19.�����ǰ������ȡ���Ρ��ĵ�ʮ�Ÿ����򡱡�
	else if(19==no){
		//19-1.��ȡ��ʮ�Ÿ����򡱵����ݡ�
		content=_patient_category;
		//19-2.�������е��˳ɹ����ء�
		return(1);
	}
	//20.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�����򡱡�
	else if(20==no){
		//20-1.��ȡ�ڶ�ʮ�����򡱵����ݡ�
		content=_medical_insurance_account;
		//20-2.�������е��˳ɹ����ء�
		return(1);
	}
	//21.�����ǰ������ȡ���Ρ��ĵڶ�ʮһ�����򡱡�
	else if(21==no){
		//21-1.��ȡ�ڶ�ʮһ�����򡱵����ݡ�
		content=_charge_type;
		//21-2.�������е��˳ɹ����ء�
		return(1);
	}
	//22.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�������򡱡�
	else if(22==no){//���ԡ�
		return(0);
	}
	//23.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�������򡱡�
	else if(23==no){
		//23-1.��ȡ�ڶ�ʮ�������򡱵����ݡ�
		content=_nation;
		//23-2.�������е��˳ɹ����ء�
		return(1);
	}
	//24.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�ĸ����򡱡�
	else if(24==no){
		//24-1.��ȡ�ڶ�ʮ�ĸ����򡱵����ݡ�
		content=_native_place;
		//24-2.�������е��˳ɹ����ء�
		return(1);
	}
	//25.�����ǰ������ȡ���Ρ��ĵڶ�ʮ������򡱡�
	else if(25==no){//���ԡ�
		return(0);
	}
	//26.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�������򡱡�
	else if(26==no){//���ԡ�
		return(0);
	}
	//27.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�߸����򡱡�
	else if(27==no){
		//27-1.��ȡ�ڶ�ʮ�߸����򡱵����ݡ�
		content=_comment;
		//27-2.�������е��˳ɹ����ء�
		return(1);
	}
	//28.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�˸����򡱡�
	else if(28==no){//���ԡ�
		return(0);
	}
	//29.�����ǰ������ȡ���Ρ��ĵڶ�ʮ�Ÿ����򡱡�
	else if(29==no){
		//29-1.��ȡ�ڶ�ʮ�Ÿ����򡱵����ݡ�
		content=_nationality;
		//29-2.�������е��˳ɹ����ء�
		return(1);
	}
	//30.�����ǰ������ȡ���Ρ��ĵ���ʮ�����򡱡�
	else if(30==no){//���ԡ�
		return(0);
	}
	//31.�����ǰ������ȡ���Ρ��ĵ���ʮһ�����򡱡�
	else if(31==no){//���ԡ�
		return(0);
	}
	//32.�����ǰ��ȡΪ���������򡱣��򷵻ش���
	else{
		return(-3);
	}
}