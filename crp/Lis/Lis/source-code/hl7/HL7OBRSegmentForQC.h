#pragma once

#include"HL7OBRSegment.h"

/**
 * name: HL7OBRSegmentForQC
 * brief: 描述HL7协议中的“OBR”段，主要负责根据字符串生成
 *        HL7OBRSegmentForQC类中数据，以及根据
 *        HL7OBRSegmentForQC类中数据生成HL7协议格式的
 *        字符串。HL7OBRSegmentForQC类负责为质控数据生
 *        成“OBR”段信息。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7OBRSegmentForQC
	:public HL7OBRSegment{
//define
public:
	enum{MAX_QC_LIQUID_AMOUNT=20,};
//construction & destruction.
public:
	HL7OBRSegmentForQC(void);
	virtual ~HL7OBRSegmentForQC(void);
//interface
public:
	void set_item_no(const String &item_no);
	const String &get_item_no() const;
	void set_item_name(const String &item_name);
	const String &get_item_name() const;
	void set_universal_service_id(const unsigned int index,
		const String &universal_service_id);
	const String &get_universal_service_id(const unsigned int index) const;
	void set_qc_date_time(const String &qc_date_time);
	const String &get_qc_date_time() const;
	void set_qc_liquid_amount(const String &qc_liquid_amount);
	const String &get_qc_liquid_amount() const;
	void set_qc_liquid_amount_with_number(const unsigned int qc_liquid_amount);
	unsigned int get_qc_liquid_amount_with_number() const;
	void set_qc_liquid_no(const unsigned int index,const String &qc_liquid_no);
	const String &get_qc_liquid_no(const unsigned int index) const;
	void set_qc_liquid_name(const unsigned int index,const String &qc_liquid_name);
	const String &get_qc_liquid_name(const unsigned int index) const;
	void set_qc_liquid_lot_no(const unsigned int index,const String &qc_liquid_lot_no);
	const String &get_qc_liquid_lot_no(const unsigned int index) const;
	void set_qc_liquid_period_of_validity(const unsigned int index,
		const String &qc_liquid_period_of_validity);
	const String &get_qc_liquid_period_of_validity(const unsigned int index) const;
	void set_qc_liquid_concentration_level(const unsigned int index,
		const String &qc_liquid_concentration_level);
	const String &get_qc_liquid_concentration_level(const unsigned int index) const;
	void set_qc_liquid_average_concentration(const unsigned int index,
		const String &qc_liquid_average_concentration);
	const String &get_qc_liquid_average_concentration(const unsigned int index) const;
	void set_qc_liquid_standard_deviation(const unsigned int index,
		const String &qc_liquid_standard_deviation);
	const String &get_qc_liquid_standard_deviation(const unsigned int index) const;
	void set_qc_liquid_test_result_concentration(const unsigned int index,
		const String &qc_liquid_test_result_concentration);
	const String &get_qc_liquid_test_result_concentration(const unsigned int index) const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//implement
private:
	int extract_qc_liquid_information_from_content(const String &content,
		String *qc_liquid_information,const unsigned int qc_liquid_amount,
		const unsigned int qc_liquid_information_type);
	int pack_qc_liquid_information_to_content(const String *qc_liquid_information,
		const unsigned int qc_liquid_amount,const unsigned int qc_liquid_information_type,
		String &content) const;
//variables
private:
	String _item_no;
	String _item_name;
	String _universal_service_id[2];
	String _qc_date_time;
	String _qc_liquid_amount;
	String _qc_liquid_no[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_name[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_lot_no[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_period_of_validity[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_concentration_level[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_average_concentration[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_standard_deviation[MAX_QC_LIQUID_AMOUNT];
	String _qc_liquid_test_result_concentration[MAX_QC_LIQUID_AMOUNT];
};