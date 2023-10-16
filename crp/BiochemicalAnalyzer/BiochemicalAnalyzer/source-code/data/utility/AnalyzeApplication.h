#pragma once

class Database;
class MtADORecordset;

/**
 * name: AnalyzeApplication
 * brief: 分析申请参数类，负责描述一个项目中包含分析相关的申请参数。
 * author: yameng_he
 * date: 2015-06-12
 */
class AnalyzeApplication{
//construction & destruction
public:
	AnalyzeApplication(void);
	~AnalyzeApplication(void);
//interface
public:
	void set_diluent_bottle_code(const int diluent_bottle_code);
	int get_diluent_bottle_code() const;
	void set_diluent_stability(const int diluent_stability);
	int get_diluent_stability() const;
	void set_analysis_method_id(const int analysis_method_id);
	int get_analysis_method_id() const;
	void set_reaction_time_id(const int reaction_time_id);
	int get_reaction_time_id() const;
	void set_measurement_point_1(const int measurement_point_1);
	int get_measurement_point_1() const;
	void set_measurement_point_2(const int measurement_point_2);
	int get_measurement_point_2() const;
	void set_measurement_point_3(const int measurement_point_3);
	int get_measurement_point_3() const;
	void set_measurement_point_4(const int measurement_point_4);
	int get_measurement_point_4() const;
	void set_secondary_wavelength_id(const int secondary_wavelength_id);
	int get_secondary_wavelength_id() const;
	void set_primary_wavelength_id(const int primary_wavelength_id);
	int get_primary_wavelength_id() const;
	void set_cell_detergent_id(const int cell_detergent_id);
	int get_cell_detergent_id() const;
	void set_twin_test_id(const int twin_test_id);
	int get_twin_test_id() const;
	void set_normal_sample_volume_for_class_1(const double normal_sample_volume_for_class_1);
	double get_normal_sample_volume_for_class_1() const;
	void set_normal_dilution_sample_volume_for_class_1(const double normal_dilution_sample_volume_for_class_1);
	double get_normal_dilution_sample_volume_for_class_1() const;
	void set_normal_diluent_volume_for_class_1(const double normal_diluent_volume_for_class_1);
	double get_normal_diluent_volume_for_class_1() const;
	void set_decreased_sample_volume_for_class_1(const double decreased_sample_volume_for_class_1);
	double get_decreased_sample_volume_for_class_1() const;
	void set_decreased_dilution_sample_volume_for_class_1(const double decreased_dilution_sample_volume_for_class_1);
	double get_decreased_dilution_sample_volume_for_class_1() const;
	void set_decreased_diluent_volume_for_class_1(const double decreased_diluent_volume_for_class_1);
	double get_decreased_diluent_volume_for_class_1() const;
	void set_increased_sample_volume_for_class_1(const double increased_sample_volume_for_class_1);
	double get_increased_sample_volume_for_class_1() const;
	void set_increased_dilution_sample_volume_for_class_1(const double increased_dilution_sample_volume_for_class_1);
	double get_increased_dilution_sample_volume_for_class_1() const;
	void set_increased_diluent_volume_for_class_1(const double increased_diluent_volume_for_class_1);
	double get_increased_diluent_volume_for_class_1() const;
	void set_normal_sample_volume_for_class_2(const double normal_sample_volume_for_class_2);
	double get_normal_sample_volume_for_class_2() const;
	void set_normal_dilution_sample_volume_for_class_2(const double normal_dilution_sample_volume_for_class_2);
	double get_normal_dilution_sample_volume_for_class_2() const;
	void set_normal_diluent_volume_for_class_2(const double normal_diluent_volume_for_class_2);
	double get_normal_diluent_volume_for_class_2() const;
	void set_decreased_sample_volume_for_class_2(const double decreased_sample_volume_for_class_2);
	double get_decreased_sample_volume_for_class_2() const;
	void set_decreased_dilution_sample_volume_for_class_2(const double decreased_dilution_sample_volume_for_class_2);
	double get_decreased_dilution_sample_volume_for_class_2() const;
	void set_decreased_diluent_volume_for_class_2(const double decreased_diluent_volume_for_class_2);
	double get_decreased_diluent_volume_for_class_2() const;
	void set_increased_sample_volume_for_class_2(const double increased_sample_volume_for_class_2);
	double get_increased_sample_volume_for_class_2() const;
	void set_increased_dilution_sample_volume_for_class_2(const double increased_dilution_sample_volume_for_class_2);
	double get_increased_dilution_sample_volume_for_class_2() const;
	void set_increased_diluent_volume_for_class_2(const double increased_diluent_volume_for_class_2);
	double get_increased_diluent_volume_for_class_2() const;
	void set_r1_reagent_volume(const double r1_reagent_volume);
	double get_r1_reagent_volume() const;
	void set_r1_diluent_volume(const double r1_diluent_volume);
	double get_r1_diluent_volume() const;
	void set_r1_bottle_code(const int r1_bottle_code);
	int get_r1_bottle_code() const;
	void set_r1_reagent_stability(const int r1_reagent_stability);
	int get_r1_reagent_stability() const;
	void set_r2_reagent_volume(const double r2_reagent_volume);
	double get_r2_reagent_volume() const;
	void set_r2_diluent_volume(const double r2_diluent_volume);
	double get_r2_diluent_volume() const;
	void set_r2_bottle_code(const int r2_bottle_code);
	int get_r2_bottle_code() const;
	void set_r2_reagent_stability(const int r2_reagent_stability);
	int get_r2_reagent_stability() const;
	void set_r3_reagent_volume(const double r3_reagent_volume);
	double get_r3_reagent_volume() const;
	void set_r3_diluent_volume(const double r3_diluent_volume);
	double get_r3_diluent_volume() const;
	void set_r3_bottle_code(const int r3_bottle_code);
	int get_r3_bottle_code() const;
	void set_r3_reagent_stability(const int r3_reagent_stability);
	int get_r3_reagent_stability() const;
	void set_r4_reagent_volume(const double r4_reagent_volume);
	double get_r4_reagent_volume() const;
	void set_r4_diluent_volume(const double r4_diluent_volume);
	double get_r4_diluent_volume() const;
	void set_r4_bottle_code(const int r4_bottle_code);
	int get_r4_bottle_code() const;
	void set_r4_reagent_stability(const int r4_reagent_stability);
	int get_r4_reagent_stability() const;
	void set_absorbance_limit_for_class_1(const int absorbance_limit_for_class_1);
	int get_absorbance_limit_for_class_1() const;
	void set_absorbance_limit_for_class_2(const int absorbance_limit_for_class_2);
	int get_absorbance_limit_for_class_2() const;
	void set_the_method_used_to_check_the_reaction_absorbance_limit(const int the_method_used_to_check_the_reaction_absorbance_limit);
	int get_the_method_used_to_check_the_reaction_absorbance_limit() const;
	void set_prozone_check_distinction_abs_low_limit(const int prozone_check_distinction_abs_low_limit);
	int get_prozone_check_distinction_abs_low_limit() const;
	void set_prozone_lower_limit_for_class_1(const int prozone_lower_limit_for_class_1);
	int get_prozone_lower_limit_for_class_1() const;
	void set_prozone_upper_limit_for_class_1(const int prozone_upper_limit_for_class_1);
	int get_prozone_upper_limit_for_class_1() const;
	void set_prozone_lower_limit_for_class_2(const int prozone_lower_limit_for_class_2);
	int get_prozone_lower_limit_for_class_2() const;
	void set_prozone_upper_limit_for_class_2(const int prozone_upper_limit_for_class_2);
	int get_prozone_upper_limit_for_class_2() const;
	void set_prozone_check_point_1(const int prozone_check_point_1);
	int get_prozone_check_point_1() const;
	void set_prozone_check_point_2(const int prozone_check_point_2);
	int get_prozone_check_point_2() const;
	void set_prozone_check_point_3(const int prozone_check_point_3);
	int get_prozone_check_point_3() const;
	void set_prozone_check_point_4(const int prozone_check_point_4);
	int get_prozone_check_point_4() const;
	void set_check_point_1_abs_difference(const int check_point_1_abs_difference);
	int get_check_point_1_abs_difference() const;
	void set_check_point_2_abs_difference(const int check_point_2_abs_difference);
	int get_check_point_2_abs_difference() const;
	int is_valid(CString *error_message=0) const;
	void reset_default_value(const int item_id);
	int commit(const int item_id,const int method,Database &database) const;
	int update(MtADORecordset &record);
//variables
private:
	int _diluent_bottle_code;
	int _diluent_stability;
	int _analysis_method_id;
	int _reaction_time_id;
	int _measurement_point_1;
	int _measurement_point_2;
	int _measurement_point_3;
	int _measurement_point_4;
	int _secondary_wavelength_id;
	int _primary_wavelength_id;
	int _cell_detergent_id;
	int _twin_test_id;
	double _normal_sample_volume_for_class_1;
	double _normal_dilution_sample_volume_for_class_1;
	double _normal_diluent_volume_for_class_1;
	double _decreased_sample_volume_for_class_1;
	double _decreased_dilution_sample_volume_for_class_1;
	double _decreased_diluent_volume_for_class_1;
	double _increased_sample_volume_for_class_1;
	double _increased_dilution_sample_volume_for_class_1;
	double _increased_diluent_volume_for_class_1;
	double _normal_sample_volume_for_class_2;
	double _normal_dilution_sample_volume_for_class_2;
	double _normal_diluent_volume_for_class_2;
	double _decreased_sample_volume_for_class_2;
	double _decreased_dilution_sample_volume_for_class_2;
	double _decreased_diluent_volume_for_class_2;
	double _increased_sample_volume_for_class_2;
	double _increased_dilution_sample_volume_for_class_2;
	double _increased_diluent_volume_for_class_2;
	double _r1_reagent_volume;
	double _r1_diluent_volume;
	int _r1_bottle_code;
	int _r1_reagent_stability;
	double _r2_reagent_volume;
	double _r2_diluent_volume;
	int _r2_bottle_code;
	int _r2_reagent_stability;
	double _r3_reagent_volume;
	double _r3_diluent_volume;
	int _r3_bottle_code;
	int _r3_reagent_stability;
	double _r4_reagent_volume;
	double _r4_diluent_volume;
	int _r4_bottle_code;
	int _r4_reagent_stability;
	int _absorbance_limit_for_class_1;
	int _absorbance_limit_for_class_2;
	int _the_method_used_to_check_the_reaction_absorbance_limit;
	int _prozone_check_distinction_abs_low_limit;
	int _prozone_lower_limit_for_class_1;
	int _prozone_upper_limit_for_class_1;
	int _prozone_lower_limit_for_class_2;
	int _prozone_upper_limit_for_class_2;
	int _prozone_check_point_1;
	int _prozone_check_point_2;
	int _prozone_check_point_3;
	int _prozone_check_point_4;
	int _check_point_1_abs_difference;
	int _check_point_2_abs_difference;
};