#include"stdafx.h"
#include"AnalyzeApplication.h"
#include"../DataCustom.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"

/**
 * name: AnalyzeApplication
 * brief: 构造函数。
 * param: --
 * return: --
 */
AnalyzeApplication::AnalyzeApplication(void)
	:_diluent_bottle_code(0)
	,_diluent_stability(0)
	,_analysis_method_id(0)
	,_reaction_time_id(0)
	,_measurement_point_1(0)
	,_measurement_point_2(0)
	,_measurement_point_3(0)
	,_measurement_point_4(0)
	,_secondary_wavelength_id(0)
	,_primary_wavelength_id(0)
	,_cell_detergent_id(0)
	,_twin_test_id(0)
	,_normal_sample_volume_for_class_1(0.0)
	,_normal_dilution_sample_volume_for_class_1(0.0)
	,_normal_diluent_volume_for_class_1(0.0)
	,_decreased_sample_volume_for_class_1(0.0)
	,_decreased_dilution_sample_volume_for_class_1(0.0)
	,_decreased_diluent_volume_for_class_1(0.0)
	,_increased_sample_volume_for_class_1(0.0)
	,_increased_dilution_sample_volume_for_class_1(0.0)
	,_increased_diluent_volume_for_class_1(0.0)
	,_normal_sample_volume_for_class_2(0.0)
	,_normal_dilution_sample_volume_for_class_2(0.0)
	,_normal_diluent_volume_for_class_2(0.0)
	,_decreased_sample_volume_for_class_2(0.0)
	,_decreased_dilution_sample_volume_for_class_2(0.0)
	,_decreased_diluent_volume_for_class_2(0.0)
	,_increased_sample_volume_for_class_2(0.0)
	,_increased_dilution_sample_volume_for_class_2(0.0)
	,_increased_diluent_volume_for_class_2(0.0)
	,_r1_reagent_volume(0.0)
	,_r1_diluent_volume(0.0)
	,_r1_bottle_code(0)
	,_r1_reagent_stability(0)
	,_r2_reagent_volume(0.0)
	,_r2_diluent_volume(0.0)
	,_r2_bottle_code(0)
	,_r2_reagent_stability(0)
	,_r3_reagent_volume(0.0)
	,_r3_diluent_volume(0.0)
	,_r3_bottle_code(0)
	,_r3_reagent_stability(0)
	,_r4_reagent_volume(0.0)
	,_r4_diluent_volume(0.0)
	,_r4_bottle_code(0)
	,_r4_reagent_stability(0)
	,_absorbance_limit_for_class_1(0)
	,_absorbance_limit_for_class_2(0)
	,_the_method_used_to_check_the_reaction_absorbance_limit(0)
	,_prozone_check_distinction_abs_low_limit(0)
	,_prozone_lower_limit_for_class_1(0)
	,_prozone_upper_limit_for_class_1(0)
	,_prozone_lower_limit_for_class_2(0)
	,_prozone_upper_limit_for_class_2(0)
	,_prozone_check_point_1(0)
	,_prozone_check_point_2(0)
	,_prozone_check_point_3(0)
	,_prozone_check_point_4(0)
	,_check_point_1_abs_difference(0)
	,_check_point_2_abs_difference(0){
}

/**
 * name: ~AnalyzeApplication
 * brief: 析构函数。
 * param: --
 * return: --
 */
AnalyzeApplication::~AnalyzeApplication(void){
}

/**
 * name: set_diluent_bottle_code
 * brief: 设置稀释液瓶子编号。
 * param: diluent_bottle_code - 稀释液瓶子编号。
 * return: --
 */
void AnalyzeApplication::set_diluent_bottle_code(const int diluent_bottle_code){
	_diluent_bottle_code=diluent_bottle_code;
}

/**
 * name: get_diluent_bottle_code
 * brief: 获取稀释液瓶子编号。
 * param: --
 * return: 返回稀释液瓶子编号。
 */
int AnalyzeApplication::get_diluent_bottle_code() const{
	return(_diluent_bottle_code);
}

void AnalyzeApplication::set_diluent_stability(const int diluent_stability){
	_diluent_stability=diluent_stability;
}

int AnalyzeApplication::get_diluent_stability() const{
	return(_diluent_stability);
}

void AnalyzeApplication::set_analysis_method_id(const int analysis_method_id){
	_analysis_method_id=analysis_method_id;
}

int AnalyzeApplication::get_analysis_method_id() const{
	return(_analysis_method_id);
}

/**
 * name: set_reaction_time_id
 * brief: 设置反应时间。
 * param: reaction_time_id - 指定的反应时间。
 * return: --
 */
void AnalyzeApplication::set_reaction_time_id(const int reaction_time_id){
	_reaction_time_id=reaction_time_id;
}

int AnalyzeApplication::get_reaction_time_id() const{
	return(_reaction_time_id);
}

/**
 * name: set_measurement_point_1
 * breif: 设置测量点1。
 * param: measurement_point_1 - 测量点1。
 * return: --
 */
void AnalyzeApplication::set_measurement_point_1(const int measurement_point_1){
	_measurement_point_1=measurement_point_1;
}

int AnalyzeApplication::get_measurement_point_1() const{
	return(_measurement_point_1);
}

/**
 * name: set_measurement_point_2
 * breif: 设置测量点2。
 * param: measurement_point_2 - 测量点2。
 * return: --
 */
void AnalyzeApplication::set_measurement_point_2(const int measurement_point_2){
	_measurement_point_2=measurement_point_2;
}

int AnalyzeApplication::get_measurement_point_2() const{
	return(_measurement_point_2);
}

/**
 * name: set_measurement_point_3
 * breif: 设置测量点3。
 * param: measurement_point_3 - 测量点3。
 * return: --
 */
void AnalyzeApplication::set_measurement_point_3(const int measurement_point_3){
	_measurement_point_3=measurement_point_3;
}

int AnalyzeApplication::get_measurement_point_3() const{
	return(_measurement_point_3);
}

/**
 * name: set_measurement_point_4
 * breif: 设置测量点4。
 * param: measurement_point_4 - 测量点4。
 * return: --
 */
void AnalyzeApplication::set_measurement_point_4(const int measurement_point_4){
	_measurement_point_4=measurement_point_4;
}

int AnalyzeApplication::get_measurement_point_4() const{
	return(_measurement_point_4);
}

/**
 * name: set_secondary_wavelength_id
 * breif: 设置副波长。
 * param: secondary_wavelength_id - 指定的副波长。
 * return: --
 */
void AnalyzeApplication::set_secondary_wavelength_id(const int secondary_wavelength_id){
	_secondary_wavelength_id=secondary_wavelength_id;
}

int AnalyzeApplication::get_secondary_wavelength_id() const{
	return(_secondary_wavelength_id);
}

/**
 * name: set_primary_wavelength_id
 * breif: 设置主波长。
 * param: primary_wavelength_id - 指定的主波长。
 * return: --
 */
void AnalyzeApplication::set_primary_wavelength_id(const int primary_wavelength_id){
	_primary_wavelength_id=primary_wavelength_id;
}

int AnalyzeApplication::get_primary_wavelength_id() const{
	return(_primary_wavelength_id);
}

/**
 * name: set_cell_detergent_id
 * breif: 设置反应杯清洗剂。
 * param: cell_detergent_id - 指定的反应被清洗剂。
 * return: --
 */
void AnalyzeApplication::set_cell_detergent_id(const int cell_detergent_id){
	_cell_detergent_id=cell_detergent_id;
}

int AnalyzeApplication::get_cell_detergent_id() const{
	return(_cell_detergent_id);
}

/**
 * name: set_twin_test_id
 * breif: 设置双测试。
 * param: twin_test_id - 指定的双测试。
 * return: --
 */
void AnalyzeApplication::set_twin_test_id(const int twin_test_id){
	_twin_test_id=twin_test_id;
}

int AnalyzeApplication::get_twin_test_id() const{
	return(_twin_test_id);
}

/**
 * name: set_normal_sample_volume_for_class_1
 * brief: 为类型1设置普通样本体积。
 * param: normal_sample_volume_for_class_1 - 类型1普通样本体积。
 * return: --
 */
void AnalyzeApplication::set_normal_sample_volume_for_class_1(
	const double normal_sample_volume_for_class_1){
	_normal_sample_volume_for_class_1=normal_sample_volume_for_class_1;
}

double AnalyzeApplication::get_normal_sample_volume_for_class_1() const{
	return(_normal_sample_volume_for_class_1);
}

/**
 * name: set_normal_dilution_sample_volume_for_class_1
 * breif: 为类型1设置稀释后普通样本体积。
 * param: normal_dilution_sample_volume_for_class_1 - 类型1稀释后普通样本体积。
 * return: --
 */
void AnalyzeApplication::set_normal_dilution_sample_volume_for_class_1(
	const double normal_dilution_sample_volume_for_class_1){
	_normal_dilution_sample_volume_for_class_1=normal_dilution_sample_volume_for_class_1;
}

double AnalyzeApplication::get_normal_dilution_sample_volume_for_class_1() const{
	return(_normal_dilution_sample_volume_for_class_1);
}

/**
 * name: set_normal_diluent_volume_for_class_1
 * brief: 为类型1设置普通稀释液体积。
 * param: normal_diluent_volume_for_class_1 - 类型1普通稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_normal_diluent_volume_for_class_1(
	const double normal_diluent_volume_for_class_1){
	_normal_diluent_volume_for_class_1=normal_diluent_volume_for_class_1;
}

double AnalyzeApplication::get_normal_diluent_volume_for_class_1() const{
	return(_normal_diluent_volume_for_class_1);
}

/**
 * name: set_decreased_sample_volume_for_class_1
 * breif: 为类型1设置减量样本体积。
 * param: decreased_sample_volume_for_class_1 - 减量样本体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_sample_volume_for_class_1(
	const double decreased_sample_volume_for_class_1){
	_decreased_sample_volume_for_class_1=decreased_sample_volume_for_class_1;
}

double AnalyzeApplication::get_decreased_sample_volume_for_class_1() const{
	return(_decreased_sample_volume_for_class_1);
}

/**
 * name: set_decreased_dilution_sample_volume_for_class_1
 * breif: 为类型1设置稀释后减量样本体积。
 * param: decreased_dilution_sample_volume_for_class_1 - 稀释后减量样本体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_dilution_sample_volume_for_class_1(
	const double decreased_dilution_sample_volume_for_class_1){
	_decreased_dilution_sample_volume_for_class_1=decreased_dilution_sample_volume_for_class_1;
}

double AnalyzeApplication::get_decreased_dilution_sample_volume_for_class_1() const{
	return(_decreased_dilution_sample_volume_for_class_1);
}

/**
 * name: set_decreased_diluent_volume_for_class_1
 * brief: 为类型1设置减量稀释液体积。
 * param: decreased_diluent_volume_for_class_1 - 减量稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_diluent_volume_for_class_1(
	const double decreased_diluent_volume_for_class_1){
	_decreased_diluent_volume_for_class_1=decreased_diluent_volume_for_class_1;
}

double AnalyzeApplication::get_decreased_diluent_volume_for_class_1() const{
	return(_decreased_diluent_volume_for_class_1);
}

/**
 * name: set_increased_sample_volume_for_class_1
 * brief: 为类型1设置增量样本体积。
 * param: increased_sample_volume_for_class_1 - 增量样本体积。
 * return: --
 */
void AnalyzeApplication::set_increased_sample_volume_for_class_1(
	const double increased_sample_volume_for_class_1){
	_increased_sample_volume_for_class_1=increased_sample_volume_for_class_1;
}

double AnalyzeApplication::get_increased_sample_volume_for_class_1() const{
	return(_increased_sample_volume_for_class_1);
}

/**
 * name: set_increased_dilution_sample_volume_for_class_1
 * brief: 为类型1设置稀释后增量样本体积。
 * param: increased_dilution_sample_volume_for_class_1 - 稀释后增量样本体积。
 * return: --
 */
void AnalyzeApplication::set_increased_dilution_sample_volume_for_class_1(
	const double increased_dilution_sample_volume_for_class_1){
	_increased_dilution_sample_volume_for_class_1=increased_dilution_sample_volume_for_class_1;
}

double AnalyzeApplication::get_increased_dilution_sample_volume_for_class_1() const{
	return(_increased_dilution_sample_volume_for_class_1);
}

void AnalyzeApplication::set_increased_diluent_volume_for_class_1(
	const double increased_diluent_volume_for_class_1){
	_increased_diluent_volume_for_class_1=increased_diluent_volume_for_class_1;
}

double AnalyzeApplication::get_increased_diluent_volume_for_class_1() const{
	return(_increased_diluent_volume_for_class_1);
}

/**
 * name: set_normal_sample_volume_for_class_2
 * brief: 为类型2设置普通样本体积。
 * param: normal_sample_volume_for_class_2 - 类型2普通样本体积。
 * return: --
 */
void AnalyzeApplication::set_normal_sample_volume_for_class_2(
	const double normal_sample_volume_for_class_2){
	_normal_sample_volume_for_class_2=normal_sample_volume_for_class_2;
}

double AnalyzeApplication::get_normal_sample_volume_for_class_2() const{
	return(_normal_sample_volume_for_class_2);
}

/**
 * name: set_normal_dilution_sample_volume_for_class_2
 * breif: 为类型2设置稀释后普通样本体积。
 * param: normal_dilution_sample_volume_for_class_2 - 类型2稀释后普通样本。
 * return: --
 */
void AnalyzeApplication::set_normal_dilution_sample_volume_for_class_2(
	const double normal_dilution_sample_volume_for_class_2){
	_normal_dilution_sample_volume_for_class_2=normal_dilution_sample_volume_for_class_2;
}

double AnalyzeApplication::get_normal_dilution_sample_volume_for_class_2() const{
	return(_normal_dilution_sample_volume_for_class_2);
}

/**
 * name: set_normal_diluent_volume_for_class_2
 * brief: 为类型2设置普通稀释液体积。
 * param: normal_diluent_volume_for_class_2 - 类型2普通稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_normal_diluent_volume_for_class_2(
	const double normal_diluent_volume_for_class_2){
	_normal_diluent_volume_for_class_2=normal_diluent_volume_for_class_2;
}

double AnalyzeApplication::get_normal_diluent_volume_for_class_2() const{
	return(_normal_diluent_volume_for_class_2);
}

/**
 * name: set_decreased_sample_volume_for_class_2
 * brief: 为类型2设置减量样本体积。
 * param: decreased_sample_volume_for_class_2 - 类型2减量样本体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_sample_volume_for_class_2(
	const double decreased_sample_volume_for_class_2){
	_decreased_sample_volume_for_class_2=decreased_sample_volume_for_class_2;
}

double AnalyzeApplication::get_decreased_sample_volume_for_class_2() const{
	return(_decreased_sample_volume_for_class_2);
}

/**
 * name: set_decreased_dilution_sample_volume_for_class_2
 * brief: 为类型2设置稀释后减量样本体积。
 * param: decreased_dilution_sample_volume_for_class_2 - 类型2稀释后减量样本体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_dilution_sample_volume_for_class_2(
	const double decreased_dilution_sample_volume_for_class_2){
	_decreased_dilution_sample_volume_for_class_2=decreased_dilution_sample_volume_for_class_2;
}

double AnalyzeApplication::get_decreased_dilution_sample_volume_for_class_2() const{
	return(_decreased_dilution_sample_volume_for_class_2);
}

/**
 * name: set_decreased_diluent_volume_for_class_2
 * brief: 为类型2设置减量稀释液体积。
 * param: decreased_diluent_volume_for_class_2 - 类型2减量稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_decreased_diluent_volume_for_class_2(
	const double decreased_diluent_volume_for_class_2){
	_decreased_diluent_volume_for_class_2=decreased_diluent_volume_for_class_2;
}

double AnalyzeApplication::get_decreased_diluent_volume_for_class_2() const{
	return(_decreased_diluent_volume_for_class_2);
}

/**
 * name: set_increased_sample_volume_for_class_2
 * breif: 为类型2设置增量样本体积。
 * param: increased_sample_volume_for_class_2 - 类型2增量样本体积。
 * return: --
 */
void AnalyzeApplication::set_increased_sample_volume_for_class_2(
	const double increased_sample_volume_for_class_2){
	_increased_sample_volume_for_class_2=increased_sample_volume_for_class_2;
}

double AnalyzeApplication::get_increased_sample_volume_for_class_2() const{
	return(_increased_sample_volume_for_class_2);
}

/**
 * name: set_increased_dilution_sample_volume_for_class_2
 * brief: 为类型2设置稀释后增量样本体积。
 * param: increased_dilution_sample_volume_for_class_2 - 类型2稀释后增量样本体积。
 * return: --
 */
void AnalyzeApplication::set_increased_dilution_sample_volume_for_class_2(
	const double increased_dilution_sample_volume_for_class_2){
	_increased_dilution_sample_volume_for_class_2=increased_dilution_sample_volume_for_class_2;
}

double AnalyzeApplication::get_increased_dilution_sample_volume_for_class_2() const{
	return(_increased_dilution_sample_volume_for_class_2);
}

/**
 * name: set_increased_diluent_volume_for_class_2
 * brief: 为类型2设置增量稀释液体积。
 * param: increased_diluent_volume_for_class_2 - 类型2增量稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_increased_diluent_volume_for_class_2(
	const double increased_diluent_volume_for_class_2){
	_increased_diluent_volume_for_class_2=increased_diluent_volume_for_class_2;
}

double AnalyzeApplication::get_increased_diluent_volume_for_class_2() const{
	return(_increased_diluent_volume_for_class_2);
}

/**
 * name: set_r1_reagent_volume
 * brief: 设置R1试剂体积。
 * param: r1_reagent_volume - R1试剂体积。
 * return: --
 */
void AnalyzeApplication::set_r1_reagent_volume(const double r1_reagent_volume){
	_r1_reagent_volume=r1_reagent_volume;
}

double AnalyzeApplication::get_r1_reagent_volume() const{
	return(_r1_reagent_volume);
}

/**
 * name: set_r1_diluent_volume
 * brief: 设置R1试剂稀释液体积。
 * param: r1_diluent_volume - R1试剂稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_r1_diluent_volume(const double r1_diluent_volume){
	_r1_diluent_volume=r1_diluent_volume;
}

double AnalyzeApplication::get_r1_diluent_volume() const{
	return(_r1_diluent_volume);
}

/**
 * name: set_r1_bottle_code
 * breif: 设置R1试剂瓶子编号。
 * param: r1_bottle_code - R1试剂瓶子编号。
 * return: --
 */
void AnalyzeApplication::set_r1_bottle_code(const int r1_bottle_code){
	_r1_bottle_code=r1_bottle_code;
}

int AnalyzeApplication::get_r1_bottle_code() const{
	return(_r1_bottle_code);
}

/**
 * name: set_r1_reagent_stability
 * brief: 设置R1试剂有效期。
 * param: r1_reagent_stability - R1试剂有效期。
 * return: --
 */
void AnalyzeApplication::set_r1_reagent_stability(const int r1_reagent_stability){
	_r1_reagent_stability=r1_reagent_stability;
}

int AnalyzeApplication::get_r1_reagent_stability() const{
	return(_r1_reagent_stability);
}

/**
 * name: set_r2_reagent_volume
 * brief: 设置R2试剂体积。
 * param: r2_reagent_volume - R2试剂体积。
 * return: --
 */
void AnalyzeApplication::set_r2_reagent_volume(const double r2_reagent_volume){
	_r2_reagent_volume=r2_reagent_volume;
}

double AnalyzeApplication::get_r2_reagent_volume() const{
	return(_r2_reagent_volume);
}

/**
 * name: set_r2_diluent_volume
 * brief: 设置R2试剂的稀释液体积。
 * param: r2_diluent_volume - R2试剂的稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_r2_diluent_volume(const double r2_diluent_volume){
	_r2_diluent_volume=r2_diluent_volume;
}

double AnalyzeApplication::get_r2_diluent_volume() const{
	return(_r2_diluent_volume);
}

/**
 * name: set_r2_bottle_code
 * breif: 设置R2试剂瓶编号。
 * param: r2_bottle_code - R2试剂瓶编号。
 * return: --
 */
void AnalyzeApplication::set_r2_bottle_code(const int r2_bottle_code){
	_r2_bottle_code=r2_bottle_code;
}

int AnalyzeApplication::get_r2_bottle_code() const{
	return(_r2_bottle_code);
}

/**
 * name: set_r2_reagent_stability
 * breif: 设置R2试剂有效期。
 * param: r2_reagent_stability - R2试剂有效期。
 * return: --
 */
void AnalyzeApplication::set_r2_reagent_stability(const int r2_reagent_stability){
	_r2_reagent_stability=r2_reagent_stability;
}

int AnalyzeApplication::get_r2_reagent_stability() const{
	return(_r2_reagent_stability);
}

/**
 * name: set_r3_reagent_volume
 * breif: 设置R3试剂体积。
 * param: r3_reagent_volume - R3试剂体积。
 * return: --
 */
void AnalyzeApplication::set_r3_reagent_volume(const double r3_reagent_volume){
	_r3_reagent_volume=r3_reagent_volume;
}

double AnalyzeApplication::get_r3_reagent_volume() const{
	return(_r3_reagent_volume);
}

/**
 * name: set_r3_diluent_volume
 * brief: 设置R3试剂的稀释液体积。
 * param: r3_diluent_volume - R3试剂的稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_r3_diluent_volume(const double r3_diluent_volume){
	_r3_diluent_volume=r3_diluent_volume;
}

double AnalyzeApplication::get_r3_diluent_volume() const{
	return(_r3_diluent_volume);
}

/**
 * name: set_r3_bottle_code
 * brief: 设置R3试剂瓶编号。
 * param: r3_bottle_code - R3试剂瓶编号。
 * return: --
 */
void AnalyzeApplication::set_r3_bottle_code(const int r3_bottle_code){
	_r3_bottle_code=r3_bottle_code;
}

int AnalyzeApplication::get_r3_bottle_code() const{
	return(_r3_bottle_code);
}

/**
 * name: set_r3_reagent_stability
 * brief: 设置R3试剂有效期。
 * param: r3_reagent_stability - R3试剂有效期。
 * return: --
 */
void AnalyzeApplication::set_r3_reagent_stability(const int r3_reagent_stability){
	_r3_reagent_stability=r3_reagent_stability;
}

int AnalyzeApplication::get_r3_reagent_stability() const{
	return(_r3_reagent_stability);
}

/**
 * name: set_r4_reagent_volume
 * brief: 设置R4试剂体积。
 * param: r4_reagent_volume - R4试剂体积。
 * return: --
 */
void AnalyzeApplication::set_r4_reagent_volume(const double r4_reagent_volume){
	_r4_reagent_volume=r4_reagent_volume;
}

double AnalyzeApplication::get_r4_reagent_volume() const{
	return(_r4_reagent_volume);
}

/**
 * name: set_r4_diluent_volume
 * brief: 设置R4稀释液体积。
 * param: r4_diluent_volume - R4稀释液体积。
 * return: --
 */
void AnalyzeApplication::set_r4_diluent_volume(const double r4_diluent_volume){
	_r4_diluent_volume=r4_diluent_volume;
}

double AnalyzeApplication::get_r4_diluent_volume() const{
	return(_r4_diluent_volume);
}

/**
 * name: set_r4_bottle_code
 * breif: 设置R4试剂瓶编号。
 * param: r4_bottle_code - R4试剂瓶编号。
 * return: --
 */
void AnalyzeApplication::set_r4_bottle_code(const int r4_bottle_code){
	_r4_bottle_code=r4_bottle_code;
}

int AnalyzeApplication::get_r4_bottle_code() const{
	return(_r4_bottle_code);
}

/**
 * name: set_r4_reagent_stability
 * brief: 设置R4试剂有效期。
 * param: r4_reagent_stability - R4试剂有效期。
 * return: --
 */
void AnalyzeApplication::set_r4_reagent_stability(const int r4_reagent_stability){
	_r4_reagent_stability=r4_reagent_stability;
}

int AnalyzeApplication::get_r4_reagent_stability() const{
	return(_r4_reagent_stability);
}

/**
 * name: set_absorbance_limit_for_class_1
 * brief: 为类型1设置吸光度限制值。
 * param: absorbance_limit_for_class_1 - 类型1的吸光度限制值。
 * return: --
 */
void AnalyzeApplication::set_absorbance_limit_for_class_1(const int absorbance_limit_for_class_1){
	_absorbance_limit_for_class_1=absorbance_limit_for_class_1;
}

int AnalyzeApplication::get_absorbance_limit_for_class_1() const{
	return(_absorbance_limit_for_class_1);
}

/**
 * name: set_absorbance_limit_for_class_2
 * brief: 为类型2设置吸光度限制值。
 * param: absorbance_limit_for_class_2 - 类型2的吸光度限制值。
 * return: --
 */
void AnalyzeApplication::set_absorbance_limit_for_class_2(const int absorbance_limit_for_class_2){
	_absorbance_limit_for_class_2=absorbance_limit_for_class_2;
}

int AnalyzeApplication::get_absorbance_limit_for_class_2() const{
	return(_absorbance_limit_for_class_2);
}

/**
 * name: set_the_method_used_to_check_the_reaction_absorbance_limit
 * breif: 设置检测吸光度限制值的方法。
 * param: the_method_used_to_check_the_reaction_absorbance_limit - 检测吸光度限制值的方法。
 * return: --
 */
void AnalyzeApplication::set_the_method_used_to_check_the_reaction_absorbance_limit(
	const int the_method_used_to_check_the_reaction_absorbance_limit){
	_the_method_used_to_check_the_reaction_absorbance_limit=the_method_used_to_check_the_reaction_absorbance_limit;
}

int AnalyzeApplication::get_the_method_used_to_check_the_reaction_absorbance_limit() const{
	return(_the_method_used_to_check_the_reaction_absorbance_limit);
}

/**
 * name: set_prozone_check_distinction_abs_low_limit
 * breif: 设置前带检测吸光度下限值。
 * param: prozone_check_distinction_abs_low_limit - 前带检测吸光度下限值。
 * return: --
 */
void AnalyzeApplication::set_prozone_check_distinction_abs_low_limit(
	const int prozone_check_distinction_abs_low_limit){
	_prozone_check_distinction_abs_low_limit=prozone_check_distinction_abs_low_limit;
}

int AnalyzeApplication::get_prozone_check_distinction_abs_low_limit() const{
	return(_prozone_check_distinction_abs_low_limit);
}

/**
 * name: set_prozone_lower_limit_for_class_1
 * breif: 为类型1设置前带检测中吸光度的下限值。
 * param: prozone_lower_limit_for_class_1 - 类型1前带检测中吸光度的下限值。
 * return: --
 */
void AnalyzeApplication::set_prozone_lower_limit_for_class_1(const int prozone_lower_limit_for_class_1){
	_prozone_lower_limit_for_class_1=prozone_lower_limit_for_class_1;
}

int AnalyzeApplication::get_prozone_lower_limit_for_class_1() const{
	return(_prozone_lower_limit_for_class_1);
}

/**
 * name: set_prozone_upper_limit_for_class_1
 * breif: 为类型1设置前带检测中吸光度的上限值。
 * param: prozone_upper_limit_for_class_1 - 类型1前带检测中吸光度的上限值。
 * return: --
 */
void AnalyzeApplication::set_prozone_upper_limit_for_class_1(const int prozone_upper_limit_for_class_1){
	_prozone_upper_limit_for_class_1=prozone_upper_limit_for_class_1;
}

int AnalyzeApplication::get_prozone_upper_limit_for_class_1() const{
	return(_prozone_upper_limit_for_class_1);
}

/**
 * name: set_prozone_lower_limit_for_class_2
 * breif: 为类型2设置前带检测中吸光度的下限值。
 * param: prozone_lower_limit_for_class_2 - 类型2前带检测中吸光度的下限值。
 * return: --
 */
void AnalyzeApplication::set_prozone_lower_limit_for_class_2(const int prozone_lower_limit_for_class_2){
	_prozone_lower_limit_for_class_2=prozone_lower_limit_for_class_2;
}

int AnalyzeApplication::get_prozone_lower_limit_for_class_2() const{
	return(_prozone_lower_limit_for_class_2);
}

/**
 * name: set_prozone_upper_limit_for_class_2
 * breif: 为类型2设置前带检测中吸光度的上限值。
 * param: prozone_upper_limit_for_class_2 - 类型2前带检测中吸光度的上限值。
 * return: --
 */
void AnalyzeApplication::set_prozone_upper_limit_for_class_2(const int prozone_upper_limit_for_class_2){
	_prozone_upper_limit_for_class_2=prozone_upper_limit_for_class_2;
}

int AnalyzeApplication::get_prozone_upper_limit_for_class_2() const{
	return(_prozone_upper_limit_for_class_2);
}

/**
 * name: set_prozone_check_point_1
 * brief: 设置前带检测点1的值。
 * param: prozone_check_point_1 - 前带检测点1的值。
 * return: --
 */
void AnalyzeApplication::set_prozone_check_point_1(const int prozone_check_point_1){
	_prozone_check_point_1=prozone_check_point_1;
}

int AnalyzeApplication::get_prozone_check_point_1() const{
	return(_prozone_check_point_1);
}

/**
 * name: set_prozone_check_point_2
 * brief: 设置前带检测点2的值。
 * param: prozone_check_point_2 - 前带检测点2的值。
 * return: --
 */
void AnalyzeApplication::set_prozone_check_point_2(const int prozone_check_point_2){
	_prozone_check_point_2=prozone_check_point_2;
}

int AnalyzeApplication::get_prozone_check_point_2() const{
	return(_prozone_check_point_2);
}

/**
 * name: set_prozone_check_point_3
 * brief: 设置前带检测点3的值。
 * param: prozone_check_point_3 - 前带检测点3的值。
 * return: --
 */
void AnalyzeApplication::set_prozone_check_point_3(const int prozone_check_point_3){
	_prozone_check_point_3=prozone_check_point_3;
}

int AnalyzeApplication::get_prozone_check_point_3() const{
	return(_prozone_check_point_3);
}

/**
 * name: set_prozone_check_point_4
 * brief: 设置前带检测点4的值。
 * param: prozone_check_point_4 - 前带检测点4的值。
 * return: --
 */
void AnalyzeApplication::set_prozone_check_point_4(const int prozone_check_point_4){
	_prozone_check_point_4=prozone_check_point_4;
}

int AnalyzeApplication::get_prozone_check_point_4() const{
	return(_prozone_check_point_4);
}

/**
 * name: set_check_point_1_abs_difference
 * brief: 为检测点1设置吸光度差值的限制值。
 * param: check_point_1_abs_difference - 检测点1的吸光度差值的限制值。
 * return: --
 */
void AnalyzeApplication::set_check_point_1_abs_difference(const int check_point_1_abs_difference){
	_check_point_1_abs_difference=check_point_1_abs_difference;
}

int AnalyzeApplication::get_check_point_1_abs_difference() const{
	return(_check_point_1_abs_difference);
}

/**
 * name: set_check_point_2_abs_difference
 * brief: 为检测点2设置吸光度差值的限制值。
 * param: check_point_2_abs_difference - 检测点2的吸光度差值的限制值。
 * return: --
 */
void AnalyzeApplication::set_check_point_2_abs_difference(const int check_point_2_abs_difference){
	_check_point_2_abs_difference=check_point_2_abs_difference;
}

int AnalyzeApplication::get_check_point_2_abs_difference() const{
	return(_check_point_2_abs_difference);
}

/**
 * name: is_valid
 * brief: 判断当前分析申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前分析申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int AnalyzeApplication::is_valid(CString *error_message/*=0*/) const{
	Theme *theme=Theme::instance();
	if((_diluent_bottle_code<0)||(_diluent_bottle_code>99999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING243),0,99999);
		}
		return(-1);
	}
	if((_diluent_stability<0)||(_diluent_stability>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING244),0,99);
		}
		return(-2);
	}
	if(_analysis_method_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING245));
		}
		return(-3);
	}
	if(_reaction_time_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING246));
		}
		return(-4);
	}
	if((_measurement_point_1<0)||(_measurement_point_1>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING247),0,35);
		}
		return(-5);
	}
	if((_measurement_point_2<0)||(_measurement_point_2>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING248),0,35);
		}
		return(-6);
	}
	if((_measurement_point_3<0)||(_measurement_point_3>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING249),0,35);
		}
		return(-7);
	}
	if((_measurement_point_4<0)||(_measurement_point_4>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING250),0,35);
		}
		return(-8);
	}
	if(_secondary_wavelength_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING251));
		}
		return(-9);
	}
	if(_primary_wavelength_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING252));
		}
		return(-10);
	}
	if(_cell_detergent_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING253));
		}
		return(-11);
	}
	if(_twin_test_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING254));
		}
		return(-12);
	}
	if((_normal_sample_volume_for_class_1<1.5)||(
		_normal_sample_volume_for_class_1>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING255),1.5,35.0);
		}
		return(-13);
	}
	if((!is_zero(_normal_dilution_sample_volume_for_class_1))&&
		((_normal_dilution_sample_volume_for_class_1<1.5)||
		(_normal_dilution_sample_volume_for_class_1>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING256),0.0,1.5,20.0);
		}
		return(-14);
	}
	if((!is_zero(_normal_diluent_volume_for_class_1))&&
		((_normal_diluent_volume_for_class_1<20.0)||
		(_normal_diluent_volume_for_class_1>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING257),0.0,20.0,270.0);
		}
		return(-15);
	}
	if((_decreased_sample_volume_for_class_1<1.5)||(
		_decreased_sample_volume_for_class_1>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING258),1.5,35.0);
		}
		return(-16);
	}
	if((!is_zero(_decreased_dilution_sample_volume_for_class_1))&&
		((_decreased_dilution_sample_volume_for_class_1<1.5)||
		(_decreased_dilution_sample_volume_for_class_1>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING259),0.0,1.5,20.0);
		}
		return(-17);
	}
	if((!is_zero(_decreased_diluent_volume_for_class_1))&&
		((_decreased_diluent_volume_for_class_1<20.0)||
		(_decreased_diluent_volume_for_class_1>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING260),0.0,20.0,270.0);
		}
		return(-18);
	}
	if((_increased_sample_volume_for_class_1<1.5)||(
		_increased_sample_volume_for_class_1>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING261),1.5,35.0);
		}
		return(-19);
	}
	if((!is_zero(_increased_dilution_sample_volume_for_class_1))&&
		((_increased_dilution_sample_volume_for_class_1<1.5)||
		(_increased_dilution_sample_volume_for_class_1>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING262),0.0,1.5,20.0);
		}
		return(-20);
	}
	if((!is_zero(_increased_diluent_volume_for_class_1))&&
		((_increased_diluent_volume_for_class_1<20.0)||
		(_increased_diluent_volume_for_class_1>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING263),0.0,20.0,270.0);
		}
		return(-21);
	}
	if((_normal_sample_volume_for_class_2<1.5)||(
		_normal_sample_volume_for_class_2>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING264),1.5,35.0);
		}
		return(-22);
	}
	if((!is_zero(_normal_dilution_sample_volume_for_class_2))&&
		((_normal_dilution_sample_volume_for_class_2<1.5)||
		(_normal_dilution_sample_volume_for_class_2>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING265),0.0,1.5,20.0);
		}
		return(-23);
	}
	if((!is_zero(_normal_diluent_volume_for_class_2))&&
		((_normal_diluent_volume_for_class_2<20.0)||
		(_normal_diluent_volume_for_class_2>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING266),0.0,20.0,270.0);
		}
		return(-24);
	}
	if((_decreased_sample_volume_for_class_2<1.5)||(
		_decreased_sample_volume_for_class_2>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING267),1.5,35.0);
		}
		return(-25);
	}
	if((!is_zero(_decreased_dilution_sample_volume_for_class_2))&&
		((_decreased_dilution_sample_volume_for_class_2<1.5)||
		(_decreased_dilution_sample_volume_for_class_2>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING268),0.0,1.5,20.0);
		}
		return(-26);
	}
	if((!is_zero(_decreased_diluent_volume_for_class_2))&&
		((_decreased_diluent_volume_for_class_2<20.0)||
		(_decreased_diluent_volume_for_class_2>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING269),0.0,20.0,270.0);
		}
		return(-27);
	}
	if((_increased_sample_volume_for_class_2<1.5)||(
		_increased_sample_volume_for_class_2>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING270),1.5,35.0);
		}
		return(-28);
	}
	if((!is_zero(_increased_dilution_sample_volume_for_class_2))&&
		((_increased_dilution_sample_volume_for_class_2<1.5)||
		(_increased_dilution_sample_volume_for_class_2>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING271),0.0,1.5,20.0);
		}
		return(-29);
	}
	if((!is_zero(_increased_diluent_volume_for_class_2))&&
		((_increased_diluent_volume_for_class_2<20.0)||
		(_increased_diluent_volume_for_class_2>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING272),0.0,20.0,270.0);
		}
		return(-30);
	}
	if((!is_zero(_r1_reagent_volume))&&((_r1_reagent_volume<20.0)||(
		_r1_reagent_volume>270.0))/*&&(!is_zero(_r1_reagent_volume-999.0))*/){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING273),0.0,20.0,270.0);
		}
		return(-31);
	}
	if((!is_zero(_r1_diluent_volume))&&((_r1_diluent_volume<20.0)||(
		_r1_diluent_volume>250.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING274),0.0,20.0,250.0);
		}
		return(-32);
	}
	if((_r1_bottle_code<1)||(_r1_bottle_code>99999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING275),1,99999);
		}
		return(-33);
	}
	if((_r1_reagent_stability<0)||(_r1_reagent_stability>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING276),0,99);
		}
		return(-34);
	}
	if((!is_zero(_r2_reagent_volume))&&((_r2_reagent_volume<20.0)||(
		_r2_reagent_volume>270.0))/*&&(!is_zero(_r2_reagent_volume-999.0))*/){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING277),0.0,20.0,270.0);
		}
		return(-35);
	}
	if((!is_zero(_r2_diluent_volume))&&((_r2_diluent_volume<20.0)||(
		_r2_diluent_volume>250.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING278),0.0,20.0,250.0);
		}
		return(-36);
	}
	if((_r2_bottle_code<1)||(_r2_bottle_code>99999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING279),1,99999);
		}
		return(-37);
	}
	if((_r2_reagent_stability<0)||(_r2_reagent_stability>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING280),0,99);
		}
		return(-38);
	}
	if((!is_zero(_r3_reagent_volume))&&((_r3_reagent_volume<20.0)||(
		_r3_reagent_volume>270.0))/*&&(!is_zero(_r3_reagent_volume-999.0))*/){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING281),0.0,20.0,270.0);
		}
		return(-39);
	}
	if((!is_zero(_r3_diluent_volume))&&((_r3_diluent_volume<20.0)||(
		_r3_diluent_volume>250.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING282),0.0,20.0,250.0);
		}
		return(-40);
	}
	if((_r3_bottle_code<1)||(_r3_bottle_code>99999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING283),1,99999);
		}
		return(-41);
	}
	if((_r3_reagent_stability<0)||(_r3_reagent_stability>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING284),0,99);
		}
		return(-42);
	}
	if((!is_zero(_r4_reagent_volume))&&((_r4_reagent_volume<20.0)||(
		_r4_reagent_volume>270.0))/*&&(!is_zero(_r4_reagent_volume-999.0))*/){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING285),0.0,20.0,270.0);
		}
		return(-43);
	}
	if((!is_zero(_r4_diluent_volume))&&((_r4_diluent_volume<20.0)||(
		_r4_diluent_volume>250.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING286),0.0,20.0,250.0);
		}
		return(-44);
	}
	if((_r4_bottle_code<1)||(_r4_bottle_code>99999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING287),1,99999);
		}
		return(-45);
	}
	if((_r4_reagent_stability<0)||(_r4_reagent_stability>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING288),0,99);
		}
		return(-46);
	}
	if((_absorbance_limit_for_class_1<0)||(_absorbance_limit_for_class_1>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING289),0,32000);
		}
		return(-47);
	}
	if((_absorbance_limit_for_class_2<0)||(_absorbance_limit_for_class_2>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING290),0,32000);
		}
		return(-48);
	}
	if((_the_method_used_to_check_the_reaction_absorbance_limit<1)||(
		_the_method_used_to_check_the_reaction_absorbance_limit>2)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING291));
		}
		return(-49);
	}
	if((_prozone_check_distinction_abs_low_limit<0)||(
		_prozone_check_distinction_abs_low_limit>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING292),0,200);
		}
		return(-50);
	}
	if((_prozone_lower_limit_for_class_1<-32000)||(
		_prozone_lower_limit_for_class_1>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING293),-32000,32000);
		}
		return(-51);
	}
	if((_prozone_upper_limit_for_class_1<-32000)||(
		_prozone_upper_limit_for_class_1>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING294),-32000,32000);
		}
		return(-52);
	}
	if((_prozone_lower_limit_for_class_2<-32000)||(
		_prozone_lower_limit_for_class_2>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING295),-32000,32000);
		}
		return(-53);
	}
	if((_prozone_upper_limit_for_class_2<-32000)||(
		_prozone_upper_limit_for_class_2>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING296),-32000,32000);
		}
		return(-54);
	}
	if((_prozone_check_point_1<0)||(_prozone_check_point_1>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING297),0,35);
		}
		return(-55);
	}
	if((_prozone_check_point_2<0)||(_prozone_check_point_2>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING298),0,35);
		}
		return(-56);
	}
	if((_prozone_check_point_3<0)||(_prozone_check_point_3>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING299),0,35);
		}
		return(-57);
	}
	if((_prozone_check_point_4<0)||(_prozone_check_point_4>35)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING300),0,35);
		}
		return(-58);
	}
	if((_check_point_1_abs_difference<-1)||(_check_point_1_abs_difference>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING301),0,32000);
		}
		return(-59);
	}
	if((_check_point_2_abs_difference<-1)||(_check_point_2_abs_difference>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING302),0,32000);
		}
		return(-60);
	}
	if(_prozone_lower_limit_for_class_1>=_prozone_upper_limit_for_class_1){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING303));
		}
		return(-61);
	}
	if(_prozone_lower_limit_for_class_2>=_prozone_upper_limit_for_class_2){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING304));
		}
		return(-62);
	}
	return(0);
}

/**
 * name: reset_default_value
 * brief: 将当前分析申请参数重置为默认值。
 * param: item_id - 指定的项目标识。
 * return: --
 */
void AnalyzeApplication::reset_default_value(const int item_id){
	_diluent_bottle_code=400;
	_diluent_stability=99;
	_analysis_method_id=1;
	_reaction_time_id=35;
	_measurement_point_1=35;
	_measurement_point_2=0;
	_measurement_point_3=0;
	_measurement_point_4=0;
	_secondary_wavelength_id=405;
	_primary_wavelength_id=340;
	_cell_detergent_id=1;
	_twin_test_id=0;
	_normal_sample_volume_for_class_1=3.0;
	_normal_dilution_sample_volume_for_class_1=0.0;
	_normal_diluent_volume_for_class_1=0.0;
	_decreased_sample_volume_for_class_1=3.0;
	_decreased_dilution_sample_volume_for_class_1=0.0;
	_decreased_diluent_volume_for_class_1=0.0;
	_increased_sample_volume_for_class_1=3.0;
	_increased_dilution_sample_volume_for_class_1=0.0;
	_increased_diluent_volume_for_class_1=0.0;
	_normal_sample_volume_for_class_2=3.0;
	_normal_dilution_sample_volume_for_class_2=0.0;
	_normal_diluent_volume_for_class_2=0.0;
	_decreased_sample_volume_for_class_2=3.0;
	_decreased_dilution_sample_volume_for_class_2=0.0;
	_decreased_diluent_volume_for_class_2=0.0;
	_increased_sample_volume_for_class_2=3.0;
	_increased_dilution_sample_volume_for_class_2=0.0;
	_increased_diluent_volume_for_class_2=0.0;
	_r1_reagent_volume=250.0;
	_r1_diluent_volume=0.0;
	_r1_bottle_code=item_id;
	_r1_reagent_stability=99;
	_r2_reagent_volume=0.0;
	_r2_diluent_volume=0.0;
	_r2_bottle_code=item_id;
	_r2_reagent_stability=99;
	_r3_reagent_volume=0.0;
	_r3_diluent_volume=0.0;
	_r3_bottle_code=item_id;
	_r3_reagent_stability=99;
	_r4_reagent_volume=0.0;
	_r4_diluent_volume=0.0;
	_r4_bottle_code=item_id;
	_r4_reagent_stability=99;
	_absorbance_limit_for_class_1=32000;
	_absorbance_limit_for_class_2=32000;
	_the_method_used_to_check_the_reaction_absorbance_limit=2;
	_prozone_check_distinction_abs_low_limit=100;
	_prozone_lower_limit_for_class_1=-32000;
	_prozone_upper_limit_for_class_1=32000;
	_prozone_lower_limit_for_class_2=-32000;
	_prozone_upper_limit_for_class_2=32000;
	_prozone_check_point_1=0;
	_prozone_check_point_2=0;
	_prozone_check_point_3=0;
	_prozone_check_point_4=0;
	_check_point_1_abs_difference=-1;
	_check_point_2_abs_difference=-1;
}

/**
 * name: commit
 * brief: 将当前的项目信息提交的数据库中。
 * param: item_id - 对应的项目标识。
 *        method - 提交到数据库的方法（1 插入 2 更新）。
 *        database - 准备提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int AnalyzeApplication::commit(const int item_id,const int method,Database &database) const{
	//1.判断当前传递的项目标识是否合法。
	if((item_id<1)||(item_id>999)){
		return(-1);
	}
	//2.向数据库提交前需要检测当前分析信息是否合法。
	if(is_valid()<0){
		return(-2);
	}
	//3.如果当前期望以插入的方式将数据提交到数据库中。
	if(1==method){
		//3-1.利用当前分析参数形成提交数据库的SQL语句。
		CString secondary_wavelength_id(_T(""));
		if(0==_secondary_wavelength_id){
			secondary_wavelength_id=_T("null");
		}else{
			secondary_wavelength_id.Format(
				_T("'%d'"),_secondary_wavelength_id);
		}
		CString twin_test_id(_T(""));
		if(0==_twin_test_id){
			twin_test_id=_T("null");
		}else{
			twin_test_id.Format(_T("'%d'"),_twin_test_id);
		}
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [analyze_application]([item_id],[diluent_bottle_code],\
					  [diluent_stability],[analysis_method_id],[reaction_time_id],\
					  [measurement_point_1],[measurement_point_2],[measurement_point_3],\
					  [measurement_point_4],[secondary_wavelength_id],[primary_wavelength_id],\
					  [cell_detergent_id],[twin_test_id],[normal_sample_volume_for_class_1],\
					  [normal_dilution_sample_volume_for_class_1],[normal_diluent_volume_for_class_1],\
					  [decreased_sample_volume_for_class_1],[decreased_dilution_sample_volume_for_class_1],\
					  [decreased_diluent_volume_for_class_1],[increased_sample_volume_for_class_1],\
					  [increased_dilution_sample_volume_for_class_1],[increased_diluent_volume_for_class_1],\
					  [normal_sample_volume_for_class_2],[normal_dilution_sample_volume_for_class_2],\
					  [normal_diluent_volume_for_class_2],[decreased_sample_volume_for_class_2],\
					  [decreased_dilution_sample_volume_for_class_2],[decreased_diluent_volume_for_class_2],\
					  [increased_sample_volume_for_class_2],[increased_dilution_sample_volume_for_class_2],\
					  [increased_diluent_volume_for_class_2],[r1_reagent_volume],[r1_diluent_volume],\
					  [r1_bottle_code],[r1_reagent_stability],[r2_reagent_volume],[r2_diluent_volume],\
					  [r2_bottle_code],[r2_reagent_stability],[r3_reagent_volume],[r3_diluent_volume],\
					  [r3_bottle_code],[r3_reagent_stability],[r4_reagent_volume],[r4_diluent_volume],\
					  [r4_bottle_code],[r4_reagent_stability],[absorbance_limit_for_class_1],\
					  [absorbance_limit_for_class_2],[the_method_used_to_check_the_reaction_absorbance_limit],\
					  [prozone_check_distinction_abs_low_limit],[prozone_lower_limit_for_class_1],\
					  [prozone_upper_limit_for_class_1],[prozone_lower_limit_for_class_2],\
					  [prozone_upper_limit_for_class_2],[prozone_check_point_1],[prozone_check_point_2],\
					  [prozone_check_point_3],[prozone_check_point_4],[check_point_1_abs_difference],\
					  [check_point_2_abs_difference])VALUES('%d','%d','%d','%d','%d','%d','%d','%d','%d',\
					  %s,'%d','%d',%s,'%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf',\
					  '%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%d','%d','%lf','%lf','%d','%d',\
					  '%lf','%lf','%d','%d','%lf','%lf','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
					  '%d','%d','%d','%d','%d','%d')"),item_id,_diluent_bottle_code,_diluent_stability,
					  _analysis_method_id,_reaction_time_id,_measurement_point_1,_measurement_point_2,
					  _measurement_point_3,_measurement_point_4,secondary_wavelength_id,_primary_wavelength_id,
					  _cell_detergent_id,twin_test_id,_normal_sample_volume_for_class_1,
					  _normal_dilution_sample_volume_for_class_1,_normal_diluent_volume_for_class_1,
					  _decreased_sample_volume_for_class_1,_decreased_dilution_sample_volume_for_class_1,
					  _decreased_diluent_volume_for_class_1,_increased_sample_volume_for_class_1,
					  _increased_dilution_sample_volume_for_class_1,_increased_diluent_volume_for_class_1,
					  _normal_sample_volume_for_class_2,_normal_dilution_sample_volume_for_class_2,
					  _normal_diluent_volume_for_class_2,_decreased_sample_volume_for_class_2,
					  _decreased_dilution_sample_volume_for_class_2,_decreased_diluent_volume_for_class_2,
					  _increased_sample_volume_for_class_2,_increased_dilution_sample_volume_for_class_2,
					  _increased_diluent_volume_for_class_2,_r1_reagent_volume,_r1_diluent_volume,_r1_bottle_code,
					  _r1_reagent_stability,_r2_reagent_volume,_r2_diluent_volume,_r2_bottle_code,_r2_reagent_stability,
					  _r3_reagent_volume,_r3_diluent_volume,_r3_bottle_code,_r3_reagent_stability,_r4_reagent_volume,
					  _r4_diluent_volume,_r4_bottle_code,_r4_reagent_stability,_absorbance_limit_for_class_1,
					  _absorbance_limit_for_class_2,_the_method_used_to_check_the_reaction_absorbance_limit,
					  _prozone_check_distinction_abs_low_limit,_prozone_lower_limit_for_class_1,
					  _prozone_upper_limit_for_class_1,_prozone_lower_limit_for_class_2,_prozone_upper_limit_for_class_2,
					  _prozone_check_point_1,_prozone_check_point_2,_prozone_check_point_3,_prozone_check_point_4,
					  _check_point_1_abs_difference,_check_point_2_abs_difference);
		//3-2.执行SQL语句将当前项目信息提交到数据库中。
		if(database.execute(sql)<0){
			return(-3);
		}
		//3-3.程序运行到此成功返回。
		return(0);
	}
	//4.如果当前期望以更新的方式将数据提交到数据库中。
	else if(2==method){
		//4-1.利用当前项目参数形成提交数据库的SQL语句。
		CString secondary_wavelength_id(_T(""));
		if(0==_secondary_wavelength_id){
			secondary_wavelength_id=_T("null");
		}else{
			secondary_wavelength_id.Format(
				_T("'%d'"),_secondary_wavelength_id);
		}
		CString twin_test_id(_T(""));
		if(0==_twin_test_id){
			twin_test_id=_T("null");
		}else{
			twin_test_id.Format(_T("'%d'"),_twin_test_id);
		}
		CString sql(_T(""));
		sql.Format(_T("UPDATE [analyze_application] SET [diluent_bottle_code]='%d',[diluent_stability]='%d',\
					  [analysis_method_id]='%d',[reaction_time_id]='%d',[measurement_point_1]='%d',\
					  [measurement_point_2]='%d',[measurement_point_3]='%d',[measurement_point_4]='%d',\
					  [secondary_wavelength_id]=%s,[primary_wavelength_id]='%d',[cell_detergent_id]='%d',\
					  [twin_test_id]=%s,[normal_sample_volume_for_class_1]='%lf',\
					  [normal_dilution_sample_volume_for_class_1]='%lf',[normal_diluent_volume_for_class_1]='%lf',\
					  [decreased_sample_volume_for_class_1]='%lf',[decreased_dilution_sample_volume_for_class_1]='%lf',\
					  [decreased_diluent_volume_for_class_1]='%lf',[increased_sample_volume_for_class_1]='%lf',\
					  [increased_dilution_sample_volume_for_class_1]='%lf',[increased_diluent_volume_for_class_1]='%lf',\
					  [normal_sample_volume_for_class_2]='%lf',[normal_dilution_sample_volume_for_class_2]='%lf',\
					  [normal_diluent_volume_for_class_2]='%lf',[decreased_sample_volume_for_class_2]='%lf',\
					  [decreased_dilution_sample_volume_for_class_2]='%lf',[decreased_diluent_volume_for_class_2]='%lf',\
					  [increased_sample_volume_for_class_2]='%lf',[increased_dilution_sample_volume_for_class_2]='%lf',\
					  [increased_diluent_volume_for_class_2]='%lf',[r1_reagent_volume]='%lf',[r1_diluent_volume]='%lf',\
					  [r1_bottle_code]='%d',[r1_reagent_stability]='%d',[r2_reagent_volume]='%lf',[r2_diluent_volume]='%lf',\
					  [r2_bottle_code]='%d',[r2_reagent_stability]='%d',[r3_reagent_volume]='%lf',[r3_diluent_volume]='%lf',\
					  [r3_bottle_code]='%d',[r3_reagent_stability]='%d',[r4_reagent_volume]='%lf',[r4_diluent_volume]='%lf',\
					  [r4_bottle_code]='%d',[r4_reagent_stability]='%d',[absorbance_limit_for_class_1]='%d',\
					  [absorbance_limit_for_class_2]='%d',[the_method_used_to_check_the_reaction_absorbance_limit]='%d',\
					  [prozone_check_distinction_abs_low_limit]='%d',[prozone_lower_limit_for_class_1]='%d',\
					  [prozone_upper_limit_for_class_1]='%d',[prozone_lower_limit_for_class_2]='%d',\
					  [prozone_upper_limit_for_class_2]='%d',[prozone_check_point_1]='%d',[prozone_check_point_2]='%d',\
					  [prozone_check_point_3]='%d',[prozone_check_point_4]='%d',[check_point_1_abs_difference]='%d',\
					  [check_point_2_abs_difference]='%d' WHERE [item_id]='%d'"),_diluent_bottle_code,_diluent_stability,
					  _analysis_method_id,_reaction_time_id,_measurement_point_1,_measurement_point_2,_measurement_point_3,
					  _measurement_point_4,secondary_wavelength_id,_primary_wavelength_id,_cell_detergent_id,twin_test_id,
					  _normal_sample_volume_for_class_1,_normal_dilution_sample_volume_for_class_1,
					  _normal_diluent_volume_for_class_1,_decreased_sample_volume_for_class_1,
					  _decreased_dilution_sample_volume_for_class_1,_decreased_diluent_volume_for_class_1,
					  _increased_sample_volume_for_class_1,_increased_dilution_sample_volume_for_class_1,
					  _increased_diluent_volume_for_class_1,_normal_sample_volume_for_class_2,
					  _normal_dilution_sample_volume_for_class_2,_normal_diluent_volume_for_class_2,
					  _decreased_sample_volume_for_class_2,_decreased_dilution_sample_volume_for_class_2,
					  _decreased_diluent_volume_for_class_2,_increased_sample_volume_for_class_2,
					  _increased_dilution_sample_volume_for_class_2,_increased_diluent_volume_for_class_2,
					  _r1_reagent_volume,_r1_diluent_volume,_r1_bottle_code,_r1_reagent_stability,_r2_reagent_volume,
					  _r2_diluent_volume,_r2_bottle_code,_r2_reagent_stability,_r3_reagent_volume,_r3_diluent_volume,
					  _r3_bottle_code,_r3_reagent_stability,_r4_reagent_volume,_r4_diluent_volume,_r4_bottle_code,
					  _r4_reagent_stability,_absorbance_limit_for_class_1,_absorbance_limit_for_class_2,
					  _the_method_used_to_check_the_reaction_absorbance_limit,_prozone_check_distinction_abs_low_limit,
					  _prozone_lower_limit_for_class_1,_prozone_upper_limit_for_class_1,_prozone_lower_limit_for_class_2,
					  _prozone_upper_limit_for_class_2,_prozone_check_point_1,_prozone_check_point_2,_prozone_check_point_3,
					  _prozone_check_point_4,_check_point_1_abs_difference,_check_point_2_abs_difference,item_id);
		//4-2.执行SQL语句将当前项目信息提交到数据库中。
		if(database.execute(sql)<0){
			return(-4);
		}
		//4-3.程序运行到此成功返回。
		return(0);
	}
	//5.如果当前期望以其它方式将数据提交到数据库中。
	else{
		return(-5);
	}
}

/**
 * name: update
 * breif: 从指定的记录集中更新当前的分析信息。
 * param: record - 指定的记录集。
 * return: 如果函数执行陈宫返回值大于等于零，否则返回值小于零。
 */
int AnalyzeApplication::update(MtADORecordset &record){
	//1.声明当前操作所需变量。
	AnalyzeApplication analyze;
	_variant_t value;
	//2.从指定的记录集中获取稀释液瓶子编号。
	value=record.get_collect(MtADODataConverter::to_variant_t(6));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	analyze._diluent_bottle_code=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取稀释液有效期。
	value=record.get_collect(MtADODataConverter::to_variant_t(7));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	analyze._diluent_stability=MtADODataConverter::to_int(value);
	//4.从指定的记录集中获取分析方法。
	value=record.get_collect(MtADODataConverter::to_variant_t(8));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	analyze._analysis_method_id=MtADODataConverter::to_int(value);
	//5.从指定的记录集中获取反应时间。
	value=record.get_collect(MtADODataConverter::to_variant_t(9));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	analyze._reaction_time_id=MtADODataConverter::to_int(value);
	//6.从指定的记录集中获取测量点1。
	value=record.get_collect(MtADODataConverter::to_variant_t(10));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	analyze._measurement_point_1=MtADODataConverter::to_int(value);
	//7.从指定的记录集中获取测量点2。
	value=record.get_collect(MtADODataConverter::to_variant_t(11));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	analyze._measurement_point_2=MtADODataConverter::to_int(value);
	//8.从指定的记录集中获取测量点3。
	value=record.get_collect(MtADODataConverter::to_variant_t(12));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	analyze._measurement_point_3=MtADODataConverter::to_int(value);
	//9.从指定的记录集中获取测量点4。
	value=record.get_collect(MtADODataConverter::to_variant_t(13));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	analyze._measurement_point_4=MtADODataConverter::to_int(value);
	//10.从指定的记录集中获取副波长。
	value=record.get_collect(MtADODataConverter::to_variant_t(14));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	if(VT_NULL==value.vt){
		analyze._secondary_wavelength_id=0;
	}else{
		analyze._secondary_wavelength_id=MtADODataConverter::to_int(value);
	}
	//11.从指定的记录集中获取副波长。
	value=record.get_collect(MtADODataConverter::to_variant_t(15));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	analyze._primary_wavelength_id=MtADODataConverter::to_int(value);
	//12.从指定的记录集中获取反应盘清洗液。
	value=record.get_collect(MtADODataConverter::to_variant_t(16));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	analyze._cell_detergent_id=MtADODataConverter::to_int(value);
	//13.从指定的记录集中获取双测试项目标识。
	value=record.get_collect(MtADODataConverter::to_variant_t(17));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	if(VT_NULL==value.vt){
		analyze._twin_test_id=0;
	}else{
		analyze._twin_test_id=MtADODataConverter::to_int(value);
	}
	//14.从指定的记录集中获取常规吸样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(18));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	analyze._normal_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//15.从指定的记录集中获取常规吸稀释后样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(19));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	analyze._normal_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//16.从指定的记录集中获取常规吸稀释液体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(20));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	analyze._normal_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//17.从指定的记录集中获取减量吸样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(21));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	analyze._decreased_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//18.从指定的记录集中获取减量吸稀释后样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(22));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	analyze._decreased_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//19.从指定的记录集中获取减量吸稀释液体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(23));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	analyze._decreased_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//20.从指定的记录集中获取增量吸样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(24));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	analyze._increased_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//21.从指定的记录集中获取增量吸稀释后样本体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(25));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	analyze._increased_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//22.从指定的记录集中获取增量吸稀释液体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(26));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	analyze._increased_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//23.从指定的记录集中获取常规吸样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(27));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	analyze._normal_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//24.从指定的记录集中获取常规吸稀释后样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(28));
	if(0!=record.get_last_error_code()){
		return(-23);
	}
	analyze._normal_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//25.从指定的记录集中获取常规吸稀释液体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(29));
	if(0!=record.get_last_error_code()){
		return(-24);
	}
	analyze._normal_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//26.从指定的记录集中获取减量吸样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(30));
	if(0!=record.get_last_error_code()){
		return(-25);
	}
	analyze._decreased_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//27.从指定的记录集中获取减量吸稀释后样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(31));
	if(0!=record.get_last_error_code()){
		return(-26);
	}
	analyze._decreased_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//28.从指定的记录集中获取减量吸稀释液体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(32));
	if(0!=record.get_last_error_code()){
		return(-27);
	}
	analyze._decreased_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//29.从指定的记录集中获取增量吸样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(33));
	if(0!=record.get_last_error_code()){
		return(-28);
	}
	analyze._increased_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//30.从指定的记录集中获取增量吸稀释后样本体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(34));
	if(0!=record.get_last_error_code()){
		return(-29);
	}
	analyze._increased_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//31.从指定的记录集中获取增量吸稀释液体积（类型2）。
	value=record.get_collect(MtADODataConverter::to_variant_t(35));
	if(0!=record.get_last_error_code()){
		return(-30);
	}
	analyze._increased_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//32.从指定的记录集中获取吸R1试剂的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(36));
	if(0!=record.get_last_error_code()){
		return(-31);
	}
	analyze._r1_reagent_volume=MtADODataConverter::to_double(value);
	//33.从指定的记录集中获取吸R1试剂稀释液的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(37));
	if(0!=record.get_last_error_code()){
		return(-32);
	}
	analyze._r1_diluent_volume=MtADODataConverter::to_double(value);
	//34.从指定的记录集中获取R1试剂瓶子编号。
	value=record.get_collect(MtADODataConverter::to_variant_t(38));
	if(0!=record.get_last_error_code()){
		return(-33);
	}
	analyze._r1_bottle_code=MtADODataConverter::to_int(value);
	//35.从指定的记录集中获取R1试剂有效期。
	value=record.get_collect(MtADODataConverter::to_variant_t(39));
	if(0!=record.get_last_error_code()){
		return(-34);
	}
	analyze._r1_reagent_stability=MtADODataConverter::to_int(value);
	//36.从指定的记录集中获取吸R2试剂的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(40));
	if(0!=record.get_last_error_code()){
		return(-35);
	}
	analyze._r2_reagent_volume=MtADODataConverter::to_double(value);
	//37.从指定的记录集中获取吸R2试剂稀释液的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(41));
	if(0!=record.get_last_error_code()){
		return(-36);
	}
	analyze._r2_diluent_volume=MtADODataConverter::to_double(value);
	//38.从指定的记录集中获取R2试剂瓶子编号。
	value=record.get_collect(MtADODataConverter::to_variant_t(42));
	if(0!=record.get_last_error_code()){
		return(-37);
	}
	analyze._r2_bottle_code=MtADODataConverter::to_int(value);
	//39.从指定的记录集中获取R2试剂有效期。
	value=record.get_collect(MtADODataConverter::to_variant_t(43));
	if(0!=record.get_last_error_code()){
		return(-38);
	}
	analyze._r2_reagent_stability=MtADODataConverter::to_int(value);
	//40.从指定的记录集中获取吸R3试剂的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(44));
	if(0!=record.get_last_error_code()){
		return(-39);
	}
	analyze._r3_reagent_volume=MtADODataConverter::to_double(value);
	//41.从指定的记录集中获取吸R3试剂稀释液的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(45));
	if(0!=record.get_last_error_code()){
		return(-40);
	}
	analyze._r3_diluent_volume=MtADODataConverter::to_double(value);
	//42.从指定的记录集中获取R3试剂瓶子编号。
	value=record.get_collect(MtADODataConverter::to_variant_t(46));
	if(0!=record.get_last_error_code()){
		return(-41);
	}
	analyze._r3_bottle_code=MtADODataConverter::to_int(value);
	//43.从指定的记录集中获取R3试剂有效期。
	value=record.get_collect(MtADODataConverter::to_variant_t(47));
	if(0!=record.get_last_error_code()){
		return(-42);
	}
	analyze._r3_reagent_stability=MtADODataConverter::to_int(value);
	//44.从指定的记录集中获取吸R4试剂的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(48));
	if(0!=record.get_last_error_code()){
		return(-43);
	}
	analyze._r4_reagent_volume=MtADODataConverter::to_double(value);
	//45.从指定的记录集中获取吸R4试剂稀释液的体积。
	value=record.get_collect(MtADODataConverter::to_variant_t(49));
	if(0!=record.get_last_error_code()){
		return(-44);
	}
	analyze._r4_diluent_volume=MtADODataConverter::to_double(value);
	//46.从指定的记录集中获取R4试剂瓶子编号。
	value=record.get_collect(MtADODataConverter::to_variant_t(50));
	if(0!=record.get_last_error_code()){
		return(-45);
	}
	analyze._r4_bottle_code=MtADODataConverter::to_int(value);
	//47.从指定的记录集中获取R4试剂有效期。
	value=record.get_collect(MtADODataConverter::to_variant_t(51));
	if(0!=record.get_last_error_code()){
		return(-46);
	}
	analyze._r4_reagent_stability=MtADODataConverter::to_int(value);
	//48.从指定的记录集中获取类型1的吸光度限制值。
	value=record.get_collect(MtADODataConverter::to_variant_t(52));
	if(0!=record.get_last_error_code()){
		return(-47);
	}
	analyze._absorbance_limit_for_class_1=MtADODataConverter::to_int(value);
	//49.从指定的记录集中获取类型2的吸光度限制值。
	value=record.get_collect(MtADODataConverter::to_variant_t(53));
	if(0!=record.get_last_error_code()){
		return(-48);
	}
	analyze._absorbance_limit_for_class_2=MtADODataConverter::to_int(value);
	//50.从指定的记录集中获取检测吸光度限制值的方法。
	value=record.get_collect(MtADODataConverter::to_variant_t(54));
	if(0!=record.get_last_error_code()){
		return(-49);
	}
	analyze._the_method_used_to_check_the_reaction_absorbance_limit=
		MtADODataConverter::to_int(value);
	//51.从指定的记录集中获取前带检测最小值。
	value=record.get_collect(MtADODataConverter::to_variant_t(55));
	if(0!=record.get_last_error_code()){
		return(-50);
	}
	analyze._prozone_check_distinction_abs_low_limit=
		MtADODataConverter::to_int(value);
	//52.从指定的记录集中获取类型1前带检测低值。
	value=record.get_collect(MtADODataConverter::to_variant_t(56));
	if(0!=record.get_last_error_code()){
		return(-51);
	}
	analyze._prozone_lower_limit_for_class_1=
		MtADODataConverter::to_int(value);
	//53.从指定的记录集中获取类型1前带检测高值。
	value=record.get_collect(MtADODataConverter::to_variant_t(57));
	if(0!=record.get_last_error_code()){
		return(-52);
	}
	analyze._prozone_upper_limit_for_class_1=
		MtADODataConverter::to_int(value);
	//54.从指定的记录集中获取类型2前带检测低值。
	value=record.get_collect(MtADODataConverter::to_variant_t(58));
	if(0!=record.get_last_error_code()){
		return(-53);
	}
	analyze._prozone_lower_limit_for_class_2=
		MtADODataConverter::to_int(value);
	//55.从指定的记录集中获取类型2前带检测高值。
	value=record.get_collect(MtADODataConverter::to_variant_t(59));
	if(0!=record.get_last_error_code()){
		return(-54);
	}
	analyze._prozone_upper_limit_for_class_2=
		MtADODataConverter::to_int(value);
	//56.从指定的记录集中获取前带检测点1。
	value=record.get_collect(MtADODataConverter::to_variant_t(60));
	if(0!=record.get_last_error_code()){
		return(-55);
	}
	analyze._prozone_check_point_1=
		MtADODataConverter::to_int(value);
	//57.从指定的记录集中获取前带检测点2。
	value=record.get_collect(MtADODataConverter::to_variant_t(61));
	if(0!=record.get_last_error_code()){
		return(-56);
	}
	analyze._prozone_check_point_2=
		MtADODataConverter::to_int(value);
	//58.从指定的记录集中获取前带检测点3。
	value=record.get_collect(MtADODataConverter::to_variant_t(62));
	if(0!=record.get_last_error_code()){
		return(-57);
	}
	analyze._prozone_check_point_3=
		MtADODataConverter::to_int(value);
	//59.从指定的记录集中获取前带检测点4。
	value=record.get_collect(MtADODataConverter::to_variant_t(63));
	if(0!=record.get_last_error_code()){
		return(-58);
	}
	analyze._prozone_check_point_4=
		MtADODataConverter::to_int(value);
	//60.从指定的记录集中获取吸光度差值检测点1。
	value=record.get_collect(MtADODataConverter::to_variant_t(64));
	if(0!=record.get_last_error_code()){
		return(-59);
	}
	analyze._check_point_1_abs_difference=
		MtADODataConverter::to_int(value);
	//61.从指定的记录集中获取吸光度差值检测点2。
	value=record.get_collect(MtADODataConverter::to_variant_t(65));
	if(0!=record.get_last_error_code()){
		return(-60);
	}
	analyze._check_point_2_abs_difference=
		MtADODataConverter::to_int(value);
	//62.如果当前获取的分析信息不合法，则直接返回错误。
	if(analyze.is_valid()<0){
		return(-61);
	}
	//63.保存当前的从记录集中获取的分析信息。
	(*this)=analyze;
	//64.程序运行到此成功返回。
	return(0);
}