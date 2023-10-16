#pragma once

#include"HL7Segment.h"

/**
 * name: HL7PIDSegment
 * brief: 描述HL7协议中的“PID”段，主要负责根据字符串生成
 *        HL7PIDSegment类中数据，以及根据HL7PIDSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7PIDSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction.
public:
	HL7PIDSegment(void);
	virtual ~HL7PIDSegment(void);
//interface
public:
	const String &get_segment_id() const;
	void set_patient_id(const String &patient_id);
	const String &get_patient_id() const;
	void set_medical_record_no(const String &medical_record_no);
	const String &get_medical_record_no() const;
	void set_bed_no(const String &bed_no);
	const String &get_bed_no() const;
	void set_patient_name(const String &patient_name);
	const String &get_patient_name() const;
	void set_impatient_area(const String &impatient_area);
	const String &get_impatient_area() const;
	void set_date_time_of_birth(const String &date_time_of_birth);
	const String &get_date_time_of_birth() const;
	void set_sex(const String &sex);
	const String &get_sex() const;
	void set_blood_type(const String &blood_type);
	const String &get_blood_type() const;
	void set_address(const String &address);
	const String &get_address() const;
	void set_postcode(const String &postcode);
	const String &get_postcode() const;
	void set_phone_number(const String &phone_number);
	const String &get_phone_number() const;
	void set_patient_category(const String &patient_category);
	const String &get_patient_category() const;
	void set_medical_insurance_account(const String &medical_insurance_account);
	const String &get_medical_insurance_account() const;
	void set_charge_type(const String &charge_type);
	const String &get_charge_type() const;
	void set_nation(const String &nation);
	const String &get_nation() const;
	void set_native_place(const String &native_place);
	const String &get_native_place() const;
	void set_comment(const String &comment);
	const String &get_comment() const;
	void set_nationality(const String &nationality);
	const String &get_nationality() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	/*const*/ String _segment_id;
	String _patient_id;
	String _medical_record_no;
	String _bed_no;
	String _patient_name;
	String _impatient_area;
	String _date_time_of_birth;
	String _sex;
	String _blood_type;
	String _address;
	String _postcode;
	String _phone_number;
	String _patient_category;
	String _medical_insurance_account;
	String _charge_type;
	String _nation;
	String _native_place;
	String _comment;
	String _nationality;
};