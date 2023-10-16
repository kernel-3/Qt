#pragma once

#include"HL7OBRSegment.h"

/**
 * name: HL7OBRSegmentForTest
 * brief: 描述HL7协议中的“OBR”段，主要负责根据字符串生成
 *        HL7OBRSegmentForTest类中数据，以及根据
 *        HL7OBRSegmentForTest类中数据生成HL7协议格式的
 *        字符串。HL7OBRSegmentForTest类负责为测试生成“OBR”
 *        段信息。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7OBRSegmentForTest
	:public HL7OBRSegment{
//construction & destruction
public:
	HL7OBRSegmentForTest(void);
	virtual ~HL7OBRSegmentForTest(void);
//interface
public:
	void set_specimen_barcode(const String &specimen_barcode);
	const String &get_specimen_barcode() const;
	void set_specimen_no(const String &specimen_no);
	const String &get_specimen_no() const;
	void set_universal_service_id(const unsigned int index,const String &universal_service_id);
	const String &get_universal_service_id(const unsigned int index) const;
	void set_is_emergency(const String &is_emergency);
	const String &get_is_emergency() const;
	void set_specimen_collect_date_time(const String &specimen_collect_date_time);
	const String &get_specimen_collect_date_time() const;
	void set_specimen_test_date_time(const String &specimen_test_date_time);
	const String &get_specimen_test_date_time() const;
	void set_dilution_ratio(const String &dilution_ratio);
	const String &get_dilution_ratio() const;
	void set_specimen_position(const unsigned int index,const String &specimen_position);
	const String &get_specimen_position(const unsigned int index) const;
	void set_relevant_clinical_info(const String &relevant_clinical_info);
	const String &get_relevant_clinical_info() const;
	void set_specimen_received_date_time(const String &specimen_received_date_time);
	const String &get_specimen_received_date_time() const;
	void set_specimen_category(const String &specimen_category);
	const String &get_specimen_category() const;
	void set_submitting_physician(const String &submitting_physician);
	const String &get_submitting_physician() const;
	void set_submitting_department(const String &submitting_department);
	const String &get_submitting_department() const;
	void set_specimen_shape_and_properties(const String &specimen_shape_and_properties);
	const String &get_specimen_shape_and_properties() const;
	void set_blood_bag_no(const String &blood_bag_no);
	const String &get_blood_bag_no() const;
	void set_physician_in_charge(const String &physician_in_charge);
	const String &get_physician_in_charge() const;
	void set_department_in_charge(const String &department_in_charge);
	const String &get_department_in_charge() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _specimen_barcode;
	String _specimen_no;
	String _universal_service_id[2];
	String _is_emergency;
	String _specimen_collect_date_time;
	String _specimen_test_date_time;
	String _dilution_ratio;
	String _specimen_position[2];
	String _relevant_clinical_info;
	String _specimen_received_date_time;
	String _specimen_category;
	String _submitting_physician;
	String _submitting_department;
	String _specimen_shape_and_properties;
	String _blood_bag_no;
	String _physician_in_charge;
	String _department_in_charge;
};