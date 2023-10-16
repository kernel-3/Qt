#pragma once

#include"HL7Segment.h"

/**
 * name: HL7OBXSegment
 * brief: 描述HL7协议中的“OBX”段，主要负责根据字符串生成
 *        HL7OBXSegment类中数据，以及根据HL7OBXSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7OBXSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7OBXSegment(void);
	virtual ~HL7OBXSegment(void);
//interface
public:
	void set_segment_id(const String &segment_id);
	const String &get_segment_id() const;
	void set_segment_id_with_number(const unsigned int segment_id);
	const unsigned int get_segment_id_with_number() const;
	void set_test_result_type(const String &test_result_type);
	const String &get_test_result_type() const;
	void set_item_no(const String &item_no);
	const String &get_item_no() const;
	void set_item_name(const String &item_name);
	const String &get_item_name() const;
	void set_quantitative_test_result(const String &quantitative_test_result);
	const String &get_quantitative_test_result() const;
	void set_test_result_unit(const String &test_result_unit);
	const String &get_test_result_unit() const;
	void set_normal_test_result_range(const unsigned int index,
		const String &normal_test_result_range);
	const String &get_normal_test_result_range(const unsigned int index) const;
	void set_abnormal_flags(const String &abnormal_flags);
	const String &get_abnormal_flags() const;
	void set_qualitative_test_result(const String &qualitative_test_result);
	const String &get_qualitative_test_result() const;
	void set_qualitative_reference_value(const String &qualitative_reference_value);
	const String &get_qualitative_reference_value() const;
	const String &get_test_result_status() const;
	void set_original_test_result(const String &original_test_result);
	const String &get_original_test_result() const;
	void set_test_date_time(const String &test_date_time);
	const String &get_test_date_time() const;
	void set_test_department(const String &test_department);
	const String &get_test_department() const;
	void set_test_physician(const String &test_physician);
	const String &get_test_physician() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _segment_id;
	String _test_result_type;
	String _item_no;
	String _item_name;
	String _quantitative_test_result;
	String _test_result_unit;
	String _normal_test_result_range[2];
	String _abnormal_flags;
	String _qualitative_test_result;
	String _qualitative_reference_value;
	/*const*/ String _test_result_status;
	String _original_test_result;
	String _test_date_time;
	String _test_department;
	String _test_physician;
};