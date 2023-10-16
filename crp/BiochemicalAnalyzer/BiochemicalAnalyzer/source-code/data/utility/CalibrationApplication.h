#pragma once

class Database;
class MtADORecordset;

/**
 * name: CalibrationApplication
 * brief: 效准申请参数类，负责描述一个效准申请参数。
 * author: yameng_he
 * date: 2015-07-02
 */
class CalibrationApplication{
//construction & destruction
public:
	CalibrationApplication(void);
	~CalibrationApplication(void);
//interface
public:
	void set_calibration_method_id(const int calibration_method_id);
	int get_calibration_method_id() const;
	void set_calibration_method_item_id(const int calibration_method_item_id);
	int get_calibration_method_item_id() const;
	void set_point(const int point);
	int get_point() const;
	void set_span_point(const int span_point);
	int get_span_point() const;
	void set_weight(const int weight);
	int get_weight() const;
	void set_blank_time_out(const int blank_time_out);
	int get_blank_time_out() const;
	void set_span_time_out(const int span_time_out);
	int get_span_time_out() const;
	void set_2_point_time_out(const int two_point_time_out);
	int get_2_point_time_out() const;
	void set_full_time_out(const int full_time_out);
	int get_full_time_out() const;
	void set_lot_no_change_over_calibration_type_id(
		const int lot_no_change_over_calibration_type_id);
	int get_lot_no_change_over_calibration_type_id() const;
	void set_bottle_change_over_calibration_type_id(
		const int bottle_change_over_calibration_type_id);
	int get_bottle_change_over_calibration_type_id() const;
	void set_sd_limit(const double sd_limit);
	double get_sd_limit() const;
	void set_duplicate_limit_percent(const int duplicate_limit_percent);
	int get_duplicate_limit_percent() const;
	void set_duplicate_limit_abs(const int duplicate_limit_abs);
	int get_duplicate_limit_abs() const;
	void set_sensitivity_range_lower_limit(const double sensitivity_range_lower_limit);
	double get_sensitivity_range_lower_limit() const;
	void set_sensitivity_range_upper_limit(const double sensitivity_range_upper_limit);
	double get_sensitivity_range_upper_limit() const;
	void set_s1_abs_range_lower_limit(const int s1_abs_range_lower_limit);
	int get_s1_abs_range_lower_limit() const;
	void set_s1_abs_range_upper_limit(const int s1_abs_range_upper_limit);
	int get_s1_abs_range_upper_limit() const;
	int is_valid(CString *error_message=0) const;
	void reset_default_value();
	int commit(const int item_id,const int method,Database &database) const;
	int update(MtADORecordset &record);
//variables
private:
	int _calibration_method_id;
	int _calibration_method_item_id;
	int _point;
	int _span_point;
	int _weight;
	int _blank_time_out;
	int _span_time_out;
	int _2_point_time_out;
	int _full_time_out;
	int _lot_no_change_over_calibration_type_id;
	int _bottle_change_over_calibration_type_id;
	double _sd_limit;
	int _duplicate_limit_percent;
	int _duplicate_limit_abs;
	double _sensitivity_range_lower_limit;
	double _sensitivity_range_upper_limit;
	int _s1_abs_range_lower_limit;
	int _s1_abs_range_upper_limit;
};