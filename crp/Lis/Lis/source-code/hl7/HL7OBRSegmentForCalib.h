#pragma once

#include"HL7OBRSegment.h"

/**
 * name: HL7OBRSegmentForCalib
 * brief: 描述HL7协议中的“OBR”段，主要负责根据字符串生成
 *        HL7OBRSegmentForCalib类中数据，以及根据
 *        HL7OBRSegmentForCalib类中数据生成HL7协议格式的
 *        字符串。HL7OBRSegmentForCalib类负责为定标数据生
 *        成“OBR”段信息。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7OBRSegmentForCalib
	:public HL7OBRSegment{
//define
public:
	enum{MAX_CALIBRATION_LIQUID_AMOUNT=20,
		MAX_CALIBRATION_PARAMETER_AMOUNT=20,};
//construction & destruction
public:
	HL7OBRSegmentForCalib(void);
	virtual ~HL7OBRSegmentForCalib(void);
//interface
public:
	void set_item_no(const String &item_no);
	const String &get_item_no() const;
	void set_item_name(const String &item_name);
	const String &get_item_name() const;
	void set_universal_service_id(const unsigned int index,const String &universal_service_id);
	const String &get_universal_service_id(const unsigned int index) const;
	void set_calibration_date_time(const String &calibration_date_time);
	const String &get_calibration_date_time() const;
	void set_calibration_method(const String &calibration_method);
	const String &get_calibration_method() const;
	void set_calibration_method_with_number(const unsigned int calibration_method);
	unsigned int get_calibration_method_with_number() const;
	void set_calibration_liquid_amount(const String &calibration_liquid_amount);
	const String &get_calibration_liquid_amount() const;
	void set_calibration_liquid_amount_with_number(const unsigned int calibration_liquid_amount);
	unsigned int get_calibration_liquid_amount_with_number() const;
	void set_calibration_liquid_no(const unsigned int index,const String &calibration_liquid_no);
	const String &get_calibration_liquid_no(const unsigned int index) const;
	void set_calibration_liquid_name(const unsigned int index,const String &calibration_liquid_name);
	const String &get_calibration_liquid_name(const unsigned int index) const;
	void set_calibration_liquid_lot_no(const unsigned int index,const String &calibration_liquid_lot_no);
	const String &get_calibration_liquid_lot_no(const unsigned int index) const;
	void set_calibration_liquid_period_of_validity(const unsigned int index,
		const String &calibration_liquid_period_of_validity);
	const String &get_calibration_liquid_period_of_validity(const unsigned int index) const;
	void set_calibration_liquid_standard_concentration(
		const unsigned int index,const String &calibration_standard_concentration);
	const String &get_calibration_liquid_standard_concentration(const unsigned int index) const;
	void set_calibration_liquid_concentration_level(const unsigned int index,
		const String &calibration_liquid_concentration_level);
	const String &get_calibration_liquid_concentration_level(const unsigned int index) const;
	void set_calibration_liquid_test_concentration(const unsigned int index,
		const String &calibration_liquid_test_concentration);
	const String &get_calibration_liquid_test_concentration(const unsigned int index) const;
	void set_calibration_parameter_amount(const String &calibration_parameter_amount);
	const String &get_calibration_parameter_amount() const;
	void set_calibration_parameter_amount_with_number(const unsigned int calibration_parameter_amount);
	unsigned int get_calibration_parameter_amount_with_number() const;
	void set_calibration_parameter_value(const unsigned int index,const String &calibration_parameter_value);
	const String &get_calibration_parameter_value(const unsigned int index) const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//implement
public:
	int extract_calibration_liquid_information_from_content(const String &content,
		String *calibration_liquid_information,const unsigned int calibration_liquid_amount,
		const unsigned int calibration_liquid_information_type);
	int pack_calibration_liquid_information_to_content(const String *calibration_liquid_information,
		const unsigned int calibration_liquid_amount,const unsigned int calibration_liquid_information_type,
		String &content) const;
//variables
private:
	String _item_no;
	String _item_name;
	String _universal_service_id[2];
	String _calibration_date_time;
	String _calibration_method;
	String _calibration_liquid_amount;
	String _calibration_liquid_no[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_name[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_lot_no[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_period_of_validity[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_standard_concentration[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_concentration_level[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_liquid_test_concentration[MAX_CALIBRATION_LIQUID_AMOUNT];
	String _calibration_parameter_amount;
	String _calibration_parameter_value[MAX_CALIBRATION_PARAMETER_AMOUNT];
};