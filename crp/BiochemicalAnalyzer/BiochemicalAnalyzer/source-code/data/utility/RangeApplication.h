#pragma once

class Database;
class MtADORecordset;

/**
 * name: RangeApplication
 * brief: 范围申请参数类，负责描述一个项目中包含范围相关的申请参数。
 * author: yameng_he
 * date: 2015-07-06
 */
class RangeApplication{
//define
public:
	/**
	 * name: Range
	 * breif: 范围参数类，负责描述一个项目中范围申请参数中的范围参数。
	 * author: yameng_he
	 * date: 2015-07-06
	 */
	class Range{
	//construction & destruction
	public:
		Range();
		~Range();
	//interface
	public:
		void set_lower_age_limit(const int lower_age_limit);
		int get_lower_age_limit() const;
		void set_upper_age_limit(const int upper_age_limit);
		int get_upper_age_limit() const;
		void set_lower_age_unit_id(const int lower_age_unit_id);
		int get_lower_age_unit_id() const;
		void set_upper_age_unit_id(const int upper_age_unit_id);
		int get_upper_age_unit_id() const;
		void set_lower_limit_of_normal_for_males_1(const double lower_limit_of_normal_for_males_1);
		double get_lower_limit_of_normal_for_males_1() const;
		void set_upper_limit_of_normal_for_males_1(const double upper_limit_of_normal_for_males_1);
		double get_upper_limit_of_normal_for_males_1() const;
		void set_lower_limit_of_normal_for_males_2(const double lower_limit_of_normal_for_males_2);
		double get_lower_limit_of_normal_for_males_2() const;
		void set_upper_limit_of_normal_for_males_2(const double upper_limit_of_normal_for_males_2);
		double get_upper_limit_of_normal_for_males_2() const;
		void set_lower_limit_of_normal_for_males_3(const double lower_limit_of_normal_for_males_3);
		double get_lower_limit_of_normal_for_males_3() const;
		void set_upper_limit_of_normal_for_males_3(const double upper_limit_of_normal_for_males_3);
		double get_upper_limit_of_normal_for_males_3() const;
		void set_lower_limit_of_normal_for_females_1(const double lower_limit_of_normal_for_females_1);
		double get_lower_limit_of_normal_for_females_1() const;
		void set_upper_limit_of_normal_for_females_1(const double upper_limit_of_normal_for_females_1);
		double get_upper_limit_of_normal_for_females_1() const;
		void set_lower_limit_of_normal_for_females_2(const double lower_limit_of_normal_for_females_2);
		double get_lower_limit_of_normal_for_females_2() const;
		void set_upper_limit_of_normal_for_females_2(const double upper_limit_of_normal_for_females_2);
		double get_upper_limit_of_normal_for_females_2() const;
		void set_lower_limit_of_normal_for_females_3(const double lower_limit_of_normal_for_females_3);
		double get_lower_limit_of_normal_for_females_3() const;
		void set_upper_limit_of_normal_for_females_3(const double upper_limit_of_normal_for_females_3);
		double get_upper_limit_of_normal_for_females_3() const;
		void set_default_age(const int default_age);
		int get_default_age() const;
		void set_default_sex(const int default_sex);
		int get_default_sex() const;
		void set_lower_limit_for_repeat_range(const double lower_limit_for_repeat_range);
		double get_lower_limit_for_repeat_range() const;
		void set_upper_limit_for_repeat_range(const double upper_limit_for_repeat_range);
		double get_upper_limit_for_repeat_range() const;
		void set_is_use_qualitative_table(const int is_use_qualitative_table);
		int get_is_use_qualitative_table() const;
		void set_qualitative_limit_1(const double qualitative_limit_1);
		double get_qualitative_limit_1() const;
		void set_qualitative_limit_text_1(const CString &qualitative_limit_text_1);
		const CString &get_qualitative_limit_text_1() const;
		void set_qualitative_limit_2(const double qualitative_limit_2);
		double get_qualitative_limit_2() const;
		void set_qualitative_limit_text_2(const CString &qualitative_limit_text_2);
		const CString &get_qualitative_limit_text_2() const;
		void set_qualitative_limit_3(const double qualitative_limit_3);
		double get_qualitative_limit_3() const;
		void set_qualitative_limit_text_3(const CString &qualitative_limit_text_3);
		const CString &get_qualitative_limit_text_3() const;
		void set_qualitative_limit_4(const double qualitative_limit_4);
		double get_qualitative_limit_4() const;
		void set_qualitative_limit_text_4(const CString &qualitative_limit_text_4);
		const CString &get_qualitative_limit_text_4() const;
		void set_qualitative_limit_5(const double qualitative_limit_5);
		double get_qualitative_limit_5() const;
		void set_qualitative_limit_text_5(const CString &qualitative_limit_text_5);
		const CString &get_qualitative_limit_text_5() const;
		void set_qualitative_limit_text_6(const CString &qualitative_limit_text_6);
		const CString &get_qualitative_limit_text_6() const;
		int is_valid(CString *error_message) const;
		void reset_default_value();
		CString get_commit_string(const CString &format) const;
		int update(long &record_index,MtADORecordset &record);
	//variables
	private:
		int _lower_age_limit;
		int _upper_age_limit;
		int _lower_age_unit_id;
		int _upper_age_unit_id;
		double _lower_limit_of_normal_for_males_1;
		double _upper_limit_of_normal_for_males_1;
		double _lower_limit_of_normal_for_males_2;
		double _upper_limit_of_normal_for_males_2;
		double _lower_limit_of_normal_for_males_3;
		double _upper_limit_of_normal_for_males_3;
		double _lower_limit_of_normal_for_females_1;
		double _upper_limit_of_normal_for_females_1;
		double _lower_limit_of_normal_for_females_2;
		double _upper_limit_of_normal_for_females_2;
		double _lower_limit_of_normal_for_females_3;
		double _upper_limit_of_normal_for_females_3;
		int _default_age;
		int _default_sex;
		double _lower_limit_for_repeat_range;
		double _upper_limit_for_repeat_range;
		int _is_use_qualitative_table;
		double _qualitative_limit_1;
		CString _qualitative_limit_text_1;
		double _qualitative_limit_2;
		CString _qualitative_limit_text_2;
		double _qualitative_limit_3;
		CString _qualitative_limit_text_3;
		double _qualitative_limit_4;
		CString _qualitative_limit_text_4;
		double _qualitative_limit_5;
		CString _qualitative_limit_text_5;
		CString _qualitative_limit_text_6;
	};
	enum{MAX_RANGES=5,};
//construction & destruction
public:
	RangeApplication(void);
	RangeApplication(const RangeApplication &source);
	~RangeApplication(void);
//interface
public:
	void set_report_name(const CString &report_name);
	const CString &get_report_name() const;
	void set_control_interval(const int control_interval);
	int get_control_interval() const;
	void set_unit_id(const int unit_id);
	int get_unit_id() const;
	void set_instrument_factor_a(const double instrument_factor_a);
	double get_instrument_factor_a() const;
	void set_instrument_factor_b(const double instrument_factor_b);
	double get_instrument_factor_b() const;
	void set_data_mode_id(const int data_mode_id);
	int get_data_mode_id() const;
	void set_lower_age_limit(const int index,const int lower_age_limit);
	int get_lower_age_limit(const int index) const;
	void set_upper_age_limit(const int index,const int upper_age_limit);
	int get_upper_age_limit(const int index) const;
	void set_lower_age_unit_id(const int index,const int lower_age_unit_id);
	int get_lower_age_unit_id(const int index) const;
	void set_upper_age_unit_id(const int index,const int upper_age_unit_id);
	int get_upper_age_unit_id(const int index) const;
	void set_lower_limit_of_normal_for_males_1(const int index,const double lower_limit_of_normal_for_males_1);
	double get_lower_limit_of_normal_for_males_1(const int index) const;
	void set_upper_limit_of_normal_for_males_1(const int index,const double upper_limit_of_normal_for_males_1);
	double get_upper_limit_of_normal_for_males_1(const int index) const;
	void set_lower_limit_of_normal_for_males_2(const int index,const double lower_limit_of_normal_for_males_2);
	double get_lower_limit_of_normal_for_males_2(const int index) const;
	void set_upper_limit_of_normal_for_males_2(const int index,const double upper_limit_of_normal_for_males_2);
	double get_upper_limit_of_normal_for_males_2(const int index) const;
	void set_lower_limit_of_normal_for_males_3(const int index,const double lower_limit_of_normal_for_males_3);
	double get_lower_limit_of_normal_for_males_3(const int index) const;
	void set_upper_limit_of_normal_for_males_3(const int index,const double upper_limit_of_normal_for_males_3);
	double get_upper_limit_of_normal_for_males_3(const int index) const;
	void set_lower_limit_of_normal_for_females_1(const int index,const double lower_limit_of_normal_for_females_1);
	double get_lower_limit_of_normal_for_females_1(const int index) const;
	void set_upper_limit_of_normal_for_females_1(const int index,const double upper_limit_of_normal_for_females_1);
	double get_upper_limit_of_normal_for_females_1(const int index) const;
	void set_lower_limit_of_normal_for_females_2(const int index,const double lower_limit_of_normal_for_females_2);
	double get_lower_limit_of_normal_for_females_2(const int index) const;
	void set_upper_limit_of_normal_for_females_2(const int index,const double upper_limit_of_normal_for_females_2);
	double get_upper_limit_of_normal_for_females_2(const int index) const;
	void set_lower_limit_of_normal_for_females_3(const int index,const double lower_limit_of_normal_for_females_3);
	double get_lower_limit_of_normal_for_females_3(const int index) const;
	void set_upper_limit_of_normal_for_females_3(const int index,const double upper_limit_of_normal_for_females_3);
	double get_upper_limit_of_normal_for_females_3(const int index) const;
	void set_default_age(const int index,const int default_age);
	int get_default_age(const int index) const;
	void set_default_sex(const int index,const int default_sex);
	int get_default_sex(const int index) const;
	void set_lower_limit_for_repeat_range(const int index,const double lower_limit_for_repeat_range);
	double get_lower_limit_for_repeat_range(const int index) const;
	void set_upper_limit_for_repeat_range(const int index,const double upper_limit_for_repeat_range);
	double get_upper_limit_for_repeat_range(const int index) const;
	void set_is_use_qualitative_table(const int index,const int is_use_qualitative_table);
	int get_is_use_qualitative_table(const int index) const;
	void set_qualitative_limit_1(const int index,const double qualitative_limit_1);
	double get_qualitative_limit_1(const int index) const;
	void set_qualitative_limit_text_1(const int index,const CString &qualitative_limit_text_1);
	const CString &get_qualitative_limit_text_1(const int index) const;
	void set_qualitative_limit_2(const int index,const double qualitative_limit_2);
	double get_qualitative_limit_2(const int index) const;
	void set_qualitative_limit_text_2(const int index,const CString &qualitative_limit_text_2);
	const CString &get_qualitative_limit_text_2(const int index) const;
	void set_qualitative_limit_3(const int index,const double qualitative_limit_3);
	double get_qualitative_limit_3(const int index) const;
	void set_qualitative_limit_text_3(const int index,const CString &qualitative_limit_text_3);
	const CString &get_qualitative_limit_text_3(const int index) const;
	void set_qualitative_limit_4(const int index,const double qualitative_limit_4);
	double get_qualitative_limit_4(const int index) const;
	void set_qualitative_limit_text_4(const int index,const CString &qualitative_limit_text_4);
	const CString &get_qualitative_limit_text_4(const int index) const;
	void set_qualitative_limit_5(const int index,const double qualitative_limit_5);
	double get_qualitative_limit_5(const int index) const;
	void set_qualitative_limit_text_5(const int index,const CString &qualitative_limit_text_5);
	const CString &get_qualitative_limit_text_5(const int index) const;
	void set_qualitative_limit_text_6(const int index,const CString &qualitative_limit_text_6);
	const CString &get_qualitative_limit_text_6(const int index) const;
	void set_lower_limit_for_technical_range_for_class_1(
		const double lower_limit_for_technical_range_for_class_1);
	double get_lower_limit_for_technical_range_for_class_1() const;
	void set_upper_limit_for_technical_range_for_class_1(
		const double upper_limit_for_technical_range_for_class_1);
	double get_upper_limit_for_technical_range_for_class_1() const;
	void set_lower_limit_for_technical_range_for_class_2(
		const double lower_limit_for_technical_range_for_class_2);
	double get_lower_limit_for_technical_range_for_class_2() const;
	void set_upper_limit_for_technical_range_for_class_2(
		const double upper_limit_for_technical_range_for_class_2);
	double get_upper_limit_for_technical_range_for_class_2() const;
	RangeApplication &operator=(const RangeApplication &source);
	int is_valid(CString *error_message=0) const;
	void reset_default_value();
	int commit(const int item_id,const int method,Database &database) const;
	int update(MtADORecordset &record);
//variables
private:
	CString _report_name;
	int _control_interval;
	int _unit_id;
	double _instrument_factor_a;
	double _instrument_factor_b;
	int _data_mode_id;
	Range *_ranges;
	double _lower_limit_for_technical_range_for_class_1;
	double _upper_limit_for_technical_range_for_class_1;
	double _lower_limit_for_technical_range_for_class_2;
	double _upper_limit_for_technical_range_for_class_2;
};