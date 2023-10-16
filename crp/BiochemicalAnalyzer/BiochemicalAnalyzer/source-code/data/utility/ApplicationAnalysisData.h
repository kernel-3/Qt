#pragma once

#include"ApplicationData.h"

/**
 * name: ApplicationAnalysisData
 * breif: 应用分析数据，它负责维护系统中所有应用分析数据，
 *        并实现所有与其相关的操作。
 * author: yameng_he
 * date: 2015-11-13
 */
class ApplicationAnalysisData
	:public ApplicationData{
//construction & destruction
public:
	ApplicationAnalysisData(void);
	ApplicationAnalysisData(const int module_id,
		const int specimen_type_id,const int item_id);
	virtual ~ApplicationAnalysisData(void);
//interface
public:
	void set_analysis_method_id(const int analysis_method_id);
	int get_analysis_method_id() const;
	void set_checkout_incubation_time(const int checkout_incubation_time);
	int get_checkout_incubation_time() const;
	void set_incubation_time_1(const int incubation_time);
	int get_incubation_time_1() const;
	void set_incubation_time_2(const int incubation_time);
	int get_incubation_time_2() const;
	void set_incubation_time_3(const int incubation_time);
	int get_incubation_time_3() const;
	void set_incubation_time_4(const int incubation_time);
	int get_incubation_time_4() const;
	void set_diluent_code(const int diluent_code);
	int get_diluent_code() const;
	void set_diluent_stability(const int diluent_stability);
	int get_diluent_stability() const;
	void set_dilution_method_id(const int dilution_method_id);
	int get_dilution_method_id() const;
	void set_normal_sample_volume(const int normal_sample_volume);
	int get_normal_sample_volume() const;
	void set_normal_dilution_sample_volume(const int normal_dilution_sample_volume);
	int get_normal_dilution_sample_volume() const;
	void set_normal_diluent_volume(const int normal_diluent_volume);
	int get_normal_diluent_volume() const;
	void set_decrease_sample_volume(const int decrease_sample_volume);
	int get_decrease_sample_volume() const;
	void set_decrease_dilution_sample_volume(const int decrease_dilution_sample_volume);
	int get_decrease_dilution_sample_volume() const;
	void set_decrease_diluent_volume(const int decrease_diluent_volume);
	int get_decrease_diluent_volume() const;
	void set_increase_sample_volume(const int increase_sample_volume);
	int get_increase_sample_volume() const;
	void set_increase_dilution_sample_volume(const int increase_dilution_sample_volume);
	int get_increase_dilution_sample_volume() const;
	void set_increase_diluent_volume(const int increase_diluent_volume);
	int get_increase_diluent_volume() const;
	void set_r1_reagent_volume(const int reagent_volume);
	int get_r1_reagent_volume() const;
	void set_r1_diluent_volume(const int diluent_volume);
	int get_r1_diluent_volume() const;
	void set_r1_reagent_code(const int reagent_code);
	int get_r1_reagent_code() const;
	void set_r1_reagent_stability(const int reagent_stability);
	int get_r1_reagent_stability() const;
	void set_r2_reagent_volume(const int reagent_volume);
	int get_r2_reagent_volume() const;
	void set_r2_diluent_volume(const int diluent_volume);
	int get_r2_diluent_volume() const;
	void set_r2_reagent_code(const int reagent_code);
	int get_r2_reagent_code() const;
	void set_r2_reagent_stability(const int reagent_stability);
	int get_r2_reagent_stability() const;
	void set_r3_reagent_volume(const int reagent_volume);
	int get_r3_reagent_volume() const;
	void set_r3_diluent_volume(const int diluent_volume);
	int get_r3_diluent_volume() const;
	void set_r3_reagent_code(const int reagent_code);
	int get_r3_reagent_code() const;
	void set_r3_reagent_stability(const int reagent_stability);
	int get_r3_reagent_stability() const;
	void set_r4_reagent_volume(const int reagent_volume);
	int get_r4_reagent_volume() const;
	void set_r4_diluent_volume(const int diluent_volume);
	int get_r4_diluent_volume() const;
	void set_r4_reagent_code(const int reagent_code);
	int get_r4_reagent_code() const;
	void set_r4_reagent_stability(const int reagent_stability);
	int get_r4_reagent_stability() const;
	void set_substrate_1_volume(const int substrate_volume);
	int get_substrate_1_volume() const;
	void set_substrate_1_code(const int substrate_code);
	int get_substrate_1_code() const;
	void set_substrate_1_stability(const int substrate_stability);
	int get_substrate_1_stability() const;
	void set_substrate_2_volume(const int substrate_volume);
	int get_substrate_2_volume() const;
	void set_substrate_2_code(const int substrate_code);
	int get_substrate_2_code() const;
	void set_substrate_2_stability(const int substrate_stability);
	int get_substrate_2_stability() const;
	void set_substrate_3_volume(const int substrate_volume);
	int get_substrate_3_volume() const;
	void set_substrate_3_code(const int substrate_code);
	int get_substrate_3_code() const;
	void set_substrate_3_stability(const int substrate_stability);
	int get_substrate_3_stability() const;
	void set_buffer_solution_volume(const int buffer_solution_volume);
	int get_buffer_solution_volume() const;
	void set_buffer_solution_code(const int buffer_solution_code);
	int get_buffer_solution_code() const;
	void set_buffer_solution_stability(const int buffer_solution_stability);
	int get_buffer_solution_stability() const;
//interface
public:
	virtual int is_valid(CString *error_message=0) const;
	virtual void reset_default_value(const int reagent_code);
	virtual int update(MtADORecordset &recordset,int &column);
	virtual int commit(const int commit_means,Database &database) const;
//variables
private:
	int _analysis_method_id;
	int _checkout_incubation_time;
	int _incubation_time_1;
	int _incubation_time_2;
	int _incubation_time_3;
	int _incubation_time_4;
	int _diluent_code;
	int _diluent_stability;
	int _dilution_method_id;
	int _normal_sample_volume;
	int _normal_dilution_sample_volume;
	int _normal_diluent_volume;
	int _decrease_sample_volume;
	int _decrease_dilution_sample_volume;
	int _decrease_diluent_volume;
	int _increase_sample_volume;
	int _increase_dilution_sample_volume;
	int _increase_diluent_volume;
	int _r1_reagent_volume;
	int _r1_diluent_volume;
	int _r1_reagent_code;
	int _r1_reagent_stability;
	int _r2_reagent_volume;
	int _r2_diluent_volume;
	int _r2_reagent_code;
	int _r2_reagent_stability;
	int _r3_reagent_volume;
	int _r3_diluent_volume;
	int _r3_reagent_code;
	int _r3_reagent_stability;
	int _r4_reagent_volume;
	int _r4_diluent_volume;
	int _r4_reagent_code;
	int _r4_reagent_stability;
	int _substrate_1_volume;
	int _substrate_1_code;
	int _substrate_1_stability;
	int _substrate_2_volume;
	int _substrate_2_code;
	int _substrate_2_stability;
	int _substrate_3_volume;
	int _substrate_3_code;
	int _substrate_3_stability;
	int _buffer_solution_volume;
	int _buffer_solution_code;
	int _buffer_solution_stability;
};