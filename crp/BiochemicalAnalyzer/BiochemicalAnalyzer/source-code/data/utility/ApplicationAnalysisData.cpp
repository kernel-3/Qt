#include"stdafx.h"
#include"ApplicationAnalysisData.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Theme.h"
#include"../../global/Database.h"
#include"../../../Resource.h"

/**
 * name: ApplicationAnalysisData
 * breif: 构造函数。
 * param: --
 * return: --
 */
ApplicationAnalysisData::ApplicationAnalysisData(void)
	:ApplicationData()
	,_analysis_method_id(0)
	,_checkout_incubation_time(0)
	,_incubation_time_1(0)
	,_incubation_time_2(0)
	,_incubation_time_3(0)
	,_incubation_time_4(0)
	,_diluent_code(0)
	,_diluent_stability(0)
	,_dilution_method_id(0)
	,_normal_sample_volume(0)
	,_normal_dilution_sample_volume(0)
	,_normal_diluent_volume(0)
	,_decrease_sample_volume(0)
	,_decrease_dilution_sample_volume(0)
	,_decrease_diluent_volume(0)
	,_increase_sample_volume(0)
	,_increase_dilution_sample_volume(0)
	,_increase_diluent_volume(0)
	,_r1_reagent_volume(0)
	,_r1_diluent_volume(0)
	,_r1_reagent_code(0)
	,_r1_reagent_stability(0)
	,_r2_reagent_volume(0)
	,_r2_diluent_volume(0)
	,_r2_reagent_code(0)
	,_r2_reagent_stability(0)
	,_r3_reagent_volume(0)
	,_r3_diluent_volume(0)
	,_r3_reagent_code(0)
	,_r3_reagent_stability(0)
	,_r4_reagent_volume(0)
	,_r4_diluent_volume(0)
	,_r4_reagent_code(0)
	,_r4_reagent_stability(0)
	,_substrate_1_volume(0)
	,_substrate_1_code(0)
	,_substrate_1_stability(0)
	,_substrate_2_volume(0)
	,_substrate_2_code(0)
	,_substrate_2_stability(0)
	,_substrate_3_volume(0)
	,_substrate_3_code(0)
	,_substrate_3_stability(0)
	,_buffer_solution_volume(0)
	,_buffer_solution_code(0)
	,_buffer_solution_stability(0){
}

/**
 * name: ApplicationAnalysisData
 * breif: 构造函数。
 * param: module_id - 输入的模块标识。
 *        specimen_type_id - 输入的样本标识。
 *        item_id - 输入的项目标识。
 *        item_no - 输入的项目编号。
 * return: --
 */
ApplicationAnalysisData::ApplicationAnalysisData(
	const int module_id,const int specimen_type_id,const int item_id)
	:ApplicationData(module_id,specimen_type_id,item_id)
	,_analysis_method_id(0)
	,_checkout_incubation_time(0)
	,_incubation_time_1(0)
	,_incubation_time_2(0)
	,_incubation_time_3(0)
	,_incubation_time_4(0)
	,_diluent_code(0)
	,_diluent_stability(0)
	,_dilution_method_id(0)
	,_normal_sample_volume(0)
	,_normal_dilution_sample_volume(0)
	,_normal_diluent_volume(0)
	,_decrease_sample_volume(0)
	,_decrease_dilution_sample_volume(0)
	,_decrease_diluent_volume(0)
	,_increase_sample_volume(0)
	,_increase_dilution_sample_volume(0)
	,_increase_diluent_volume(0)
	,_r1_reagent_volume(0)
	,_r1_diluent_volume(0)
	,_r1_reagent_code(0)
	,_r1_reagent_stability(0)
	,_r2_reagent_volume(0)
	,_r2_diluent_volume(0)
	,_r2_reagent_code(0)
	,_r2_reagent_stability(0)
	,_r3_reagent_volume(0)
	,_r3_diluent_volume(0)
	,_r3_reagent_code(0)
	,_r3_reagent_stability(0)
	,_r4_reagent_volume(0)
	,_r4_diluent_volume(0)
	,_r4_reagent_code(0)
	,_r4_reagent_stability(0)
	,_substrate_1_volume(0)
	,_substrate_1_code(0)
	,_substrate_1_stability(0)
	,_substrate_2_volume(0)
	,_substrate_2_code(0)
	,_substrate_2_stability(0)
	,_substrate_3_volume(0)
	,_substrate_3_code(0)
	,_substrate_3_stability(0)
	,_buffer_solution_volume(0)
	,_buffer_solution_code(0)
	,_buffer_solution_stability(0){
}

/**
 * name: ~ApplicationAnalysisData
 * breif: 析构函数。
 * param: --
 * return: --
 */
ApplicationAnalysisData::~ApplicationAnalysisData(void){
}

/**
 * name: set_analysis_method_id
 * breif: 设置分析方法标识。
 * param: analysis_method_id - 分析方法标识。
 * return: --
 */
void ApplicationAnalysisData::set_analysis_method_id(const int analysis_method_id){
	_analysis_method_id=analysis_method_id;
}

/**
 * name: get_analysis_method_id
 * breif: 获取分析方法标识。
 * param: --
 * return: 返回分析方法标识。
 */
int ApplicationAnalysisData::get_analysis_method_id() const{
	return(_analysis_method_id);
}

/**
 * name: set_checkout_incubation_time
 * breif: 设置检测孵育时间。
 * param: checkout_incubation_time - 检测孵育时间。
 * return: --
 */
void ApplicationAnalysisData::set_checkout_incubation_time(
	const int checkout_incubation_time){
	_checkout_incubation_time=checkout_incubation_time;
}

/**
 * name: get_checkout_incubation_time
 * brief: 获取检测孵育时间。
 * param: --
 * return: 返回检测孵育时间。
 */
int ApplicationAnalysisData::get_checkout_incubation_time() const{
	return(_checkout_incubation_time);
}

/**
 * name: set_incubation_time_1
 * breif: 设置孵育时间1。
 * param: incubation_time - 孵育时间。
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_1(const int incubation_time){
	_incubation_time_1=incubation_time;
}

/**
 * name: get_incubation_time_1
 * breif: 获取孵育时间1。
 * param: --
 * return: 返回孵育时间1。
 */
int ApplicationAnalysisData::get_incubation_time_1() const{
	return(_incubation_time_1);
}

/**
 * name: set_incubation_time_2
 * breif: 设置孵育时间2。
 * param: incubation_time - 孵育时间。
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_2(const int incubation_time){
	_incubation_time_2=incubation_time;
}

/**
 * name: get_incubation_time_2
 * breif: 获取孵育时间2。
 * param: --
 * return: 返回孵育时间2。
 */
int ApplicationAnalysisData::get_incubation_time_2() const{
	return(_incubation_time_2);
}

/**
 * name: set_incubation_time_3
 * breif: 设置孵育时间3。
 * param: incubation_time - 孵育时间。
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_3(const int incubation_time){
	_incubation_time_3=incubation_time;
}

/**
 * name: get_incubation_time_3
 * breif: 获取孵育时间3。
 * param: --
 * return: 返回孵育时间3。
 */
int ApplicationAnalysisData::get_incubation_time_3() const{
	return(_incubation_time_3);
}

/**
 * name: set_incubation_time_4
 * breif: 设置孵育时间4。
 * param: incubation_time - 孵育时间。
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_4(const int incubation_time){
	_incubation_time_4=incubation_time;
}

/**
 * name: get_incubation_time_4
 * breif: 获取孵育时间4。
 * param: --
 * return: 返回孵育时间4。
 */
int ApplicationAnalysisData::get_incubation_time_4() const{
	return(_incubation_time_4);
}

/**
 * name: set_diluent_code
 * breif: 设置稀释液编号。
 * param: diluent_code - 稀释液编号。
 * return: --
 */
void ApplicationAnalysisData::set_diluent_code(
	const int diluent_code){
	_diluent_code=diluent_code;
}

/**
 * name: get_diluent_code
 * breif: 获取稀释液编号。
 * param: --
 * return: 返回稀释液编号。
 */
int ApplicationAnalysisData::get_diluent_code() const{
	return(_diluent_code);
}

/**
 * name: set_diluent_stability
 * breif: 设置稀释液效期。
 * param: diluent_stability - 稀释液有效期。
 * return: --
 */
void ApplicationAnalysisData::set_diluent_stability(
	const int diluent_stability){
	_diluent_stability=diluent_stability;
}

/**
 * name: get_diluent_stability
 * breif: 获取稀释液有效期。
 * param: --
 * return: 返回稀释液有效期。
 */
int ApplicationAnalysisData::get_diluent_stability() const{
	return(_diluent_stability);
}

/**
 * name: set_dilution_method_id
 * breif: 设置稀释液方法标识。
 * param: dilution_method_id - 稀释方法标识。
 * return: --
 */
void ApplicationAnalysisData::set_dilution_method_id(
	const int dilution_method_id){
	_dilution_method_id=dilution_method_id;
}

/**
 * name: get_dilution_method_id
 * breif: 获取稀释液方法标识。
 * param: --
 * return: 返回稀释液方法标识。
 */
int ApplicationAnalysisData::get_dilution_method_id() const{
	return(_dilution_method_id);
}

/**
 * name: set_normal_sample_volume
 * breif: 设置常规样本体积。
 * param: normal_sample_volume - 常规样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_normal_sample_volume(
	const int normal_sample_volume){
	_normal_sample_volume=normal_sample_volume;
}

/**
 * name: get_normal_sample_volume
 * breif: 获取常规样本体积。
 * param: --
 * return: 返回常规样本体积。 
 */
int ApplicationAnalysisData::get_normal_sample_volume() const{
	return(_normal_sample_volume);
}

/**
 * name: set_normal_dilution_sample_volume
 * brief: 设置常规稀释样本体积。
 * param: normal_dilution_sample_volume - 常规稀释样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_normal_dilution_sample_volume(
	const int normal_dilution_sample_volume){
	_normal_dilution_sample_volume=normal_dilution_sample_volume;
}

/**
 * name: get_normal_dilution_sample_volume
 * brief: 获取常规稀释样本体积。
 * param: --
 * return: 返回常规稀释样本体积。
 */
int ApplicationAnalysisData::get_normal_dilution_sample_volume() const{
	return(_normal_dilution_sample_volume);
}

/**
 * name: set_normal_diluent_volume
 * brief: 设置常规稀释液体积。
 * param: normal_diluent_volume - 常规稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_normal_diluent_volume(
	const int normal_diluent_volume){
	_normal_diluent_volume=normal_diluent_volume;
}

/**
 * name: get_normal_diluent_volume
 * brief: 获取常规稀释液体积。
 * param: --
 * return: 返回常规稀释液体积。
 */
int ApplicationAnalysisData::get_normal_diluent_volume() const{
	return(_normal_diluent_volume);
}

/**
 * name: set_decrease_sample_volume
 * breif: 设置减量样本体积。
 * param: decrease_sample_volume - 减量样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_decrease_sample_volume(
	const int decrease_sample_volume){
	_decrease_sample_volume=decrease_sample_volume;
}

/**
 * name: get_decrease_sample_volume
 * breif: 获取减量样本体积。
 * param: --
 * return: 返回减量样本体积。 
 */
int ApplicationAnalysisData::get_decrease_sample_volume() const{
	return(_decrease_sample_volume);
}

/**
 * name: set_decrease_dilution_sample_volume
 * brief: 设置减量稀释样本体积。
 * param: decrease_dilution_sample_volume - 减量稀释样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_decrease_dilution_sample_volume(
	const int decrease_dilution_sample_volume){
	_decrease_dilution_sample_volume=decrease_dilution_sample_volume;
}

/**
 * name: get_decrease_dilution_sample_volume
 * brief: 获取减量稀释样本体积。
 * param: --
 * return: 返回减量稀释样本体积。
 */
int ApplicationAnalysisData::get_decrease_dilution_sample_volume() const{
	return(_decrease_dilution_sample_volume);
}

/**
 * name: set_decrease_diluent_volume
 * brief: 设置减量稀释液体积。
 * param: decrease_diluent_volume - 减量稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_decrease_diluent_volume(
	const int decrease_diluent_volume){
	_decrease_diluent_volume=decrease_diluent_volume;
}

/**
 * name: get_decrease_diluent_volume
 * brief: 获取减量稀释液体积。
 * param: --
 * return: 返回减量稀释液体积。
 */
int ApplicationAnalysisData::get_decrease_diluent_volume() const{
	return(_decrease_diluent_volume);
}

/**
 * name: set_increase_sample_volume
 * breif: 设置增量样本体积。
 * param: increase_sample_volume - 增量样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_increase_sample_volume(
	const int increase_sample_volume){
	_increase_sample_volume=increase_sample_volume;
}

/**
 * name: get_increase_sample_volume
 * breif: 获取增量样本体积。
 * param: --
 * return: 返回增量样本体积。 
 */
int ApplicationAnalysisData::get_increase_sample_volume() const{
	return(_increase_sample_volume);
}

/**
 * name: set_increase_dilution_sample_volume
 * brief: 设置增量稀释样本体积。
 * param: increase_dilution_sample_volume - 增量稀释样本体积。
 * return: --
 */
void ApplicationAnalysisData::set_increase_dilution_sample_volume(
	const int increase_dilution_sample_volume){
	_increase_dilution_sample_volume=increase_dilution_sample_volume;
}

/**
 * name: get_increase_dilution_sample_volume
 * brief: 获取增量稀释样本体积。
 * param: --
 * return: 返回增量稀释样本体积。
 */
int ApplicationAnalysisData::get_increase_dilution_sample_volume() const{
	return(_increase_dilution_sample_volume);
}

/**
 * name: set_increase_diluent_volume
 * brief: 设置增量稀释液体积。
 * param: increase_diluent_volume - 增量稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_increase_diluent_volume(
	const int increase_diluent_volume){
	_increase_diluent_volume=increase_diluent_volume;
}

/**
 * name: get_increase_diluent_volume
 * brief: 获取增量稀释液体积。
 * param: --
 * return: 返回增量稀释液体积。
 */
int ApplicationAnalysisData::get_increase_diluent_volume() const{
	return(_increase_diluent_volume);
}

/**
 * name: set_r1_reagent_volume
 * breif: 设置R1试剂体积。
 * param: reagent_volume - 试剂体积。
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_volume(
	const int reagent_volume){
	_r1_reagent_volume=reagent_volume;
}

/**
 * name: get_r1_reagent_volume
 * breif: 获取R1试剂体积。
 * param: --
 * return: 返回R1试剂体积。
 */
int ApplicationAnalysisData::get_r1_reagent_volume() const{
	return(_r1_reagent_volume);
}

/**
 * name: set_r1_diluent_volume
 * breif: 设置R1稀释液体积。
 * param: diluent_volume - 稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_r1_diluent_volume(
	const int diluent_volume){
	_r1_diluent_volume=diluent_volume;
}

/**
 * name: get_r1_diluent_volume
 * breif: 获取R1稀释液体积。
 * param: --
 * return: 返回R1稀释液体积。
 */
int ApplicationAnalysisData::get_r1_diluent_volume() const{
	return(_r1_diluent_volume);
}

/** 
 * name: set_r1_reagent_code
 * breif: 设置R1试剂编号。
 * param: reagent_code - 试剂编号。
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_code(
	const int reagent_code){
	_r1_reagent_code=reagent_code;
}

/**
 * name: get_r1_reagent_code
 * breif: 获取R1试剂编号。
 * param: --
 * return: 返回R1试剂编号。
 */
int ApplicationAnalysisData::get_r1_reagent_code() const{
	return(_r1_reagent_code);
}

/**
 * name: set_r1_reagent_stability
 * brief: 设置R1试剂有效期。
 * param: reagent_stability - 试剂有效期。
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_stability(
	const int reagent_stability){
	_r1_reagent_stability=reagent_stability;
}

/**
 * name: get_r1_reagent_stability
 * breif: 获取R1试剂有效期。
 * param: --
 * return: 返回R1试剂有效期。
 */
int ApplicationAnalysisData::get_r1_reagent_stability() const{
	return(_r1_reagent_stability);
}

/**
 * name: set_r2_reagent_volume
 * breif: 设置R2试剂体积。
 * param: reagent_volume - 试剂体积。
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_volume(
	const int reagent_volume){
	_r2_reagent_volume=reagent_volume;
}

/**
 * name: get_r2_reagent_volume
 * breif: 获取R2试剂体积。
 * param: --
 * return: 返回R2试剂体积。
 */
int ApplicationAnalysisData::get_r2_reagent_volume() const{
	return(_r2_reagent_volume);
}

/**
 * name: set_r2_diluent_volume
 * breif: 设置R2稀释液体积。
 * param: diluent_volume - 稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_r2_diluent_volume(
	const int diluent_volume){
	_r2_diluent_volume=diluent_volume;
}

/**
 * name: get_r2_diluent_volume
 * breif: 获取R2稀释液体积。
 * param: --
 * return: 返回R2稀释液体积。
 */
int ApplicationAnalysisData::get_r2_diluent_volume() const{
	return(_r2_diluent_volume);
}

/** 
 * name: set_r2_reagent_code
 * breif: 设置R2试剂编号。
 * param: reagent_code - 试剂编号。
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_code(
	const int reagent_code){
	_r2_reagent_code=reagent_code;
}

/**
 * name: get_r2_reagent_code
 * breif: 获取R2试剂编号。
 * param: --
 * return: 返回R2试剂编号。
 */
int ApplicationAnalysisData::get_r2_reagent_code() const{
	return(_r2_reagent_code);
}

/**
 * name: set_r2_reagent_stability
 * brief: 设置R2试剂有效期。
 * param: reagent_stability - 试剂有效期。
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_stability(
	const int reagent_stability){
	_r2_reagent_stability=reagent_stability;
}

/**
 * name: get_r2_reagent_stability
 * breif: 获取R2试剂有效期。
 * param: --
 * return: 返回R2试剂有效期。
 */
int ApplicationAnalysisData::get_r2_reagent_stability() const{
	return(_r2_reagent_stability);
}

/**
 * name: set_r3_reagent_volume
 * breif: 设置R3试剂体积。
 * param: reagent_volume - 试剂体积。
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_volume(
	const int reagent_volume){
	_r3_reagent_volume=reagent_volume;
}

/**
 * name: get_r3_reagent_volume
 * breif: 获取R3试剂体积。
 * param: --
 * return: 返回R3试剂体积。
 */
int ApplicationAnalysisData::get_r3_reagent_volume() const{
	return(_r3_reagent_volume);
}

/**
 * name: set_r3_diluent_volume
 * breif: 设置R3稀释液体积。
 * param: diluent_volume - 稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_r3_diluent_volume(
	const int diluent_volume){
	_r3_diluent_volume=diluent_volume;
}

/**
 * name: get_r3_diluent_volume
 * breif: 获取R3稀释液体积。
 * param: --
 * return: 返回R3稀释液体积。
 */
int ApplicationAnalysisData::get_r3_diluent_volume() const{
	return(_r3_diluent_volume);
}

/** 
 * name: set_r3_reagent_code
 * breif: 设置R3试剂编号。
 * param: reagent_code - 试剂编号。
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_code(
	const int reagent_code){
	_r3_reagent_code=reagent_code;
}

/**
 * name: get_r3_reagent_code
 * breif: 获取R3试剂编号。
 * param: --
 * return: 返回R3试剂编号。
 */
int ApplicationAnalysisData::get_r3_reagent_code() const{
	return(_r3_reagent_code);
}

/**
 * name: set_r3_reagent_stability
 * brief: 设置R3试剂有效期。
 * param: reagent_stability - 试剂有效期。
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_stability(
	const int reagent_stability){
	_r3_reagent_stability=reagent_stability;
}

/**
 * name: get_r3_reagent_stability
 * breif: 获取R3试剂有效期。
 * param: --
 * return: 返回R3试剂有效期。
 */
int ApplicationAnalysisData::get_r3_reagent_stability() const{
	return(_r3_reagent_stability);
}

/**
 * name: set_r4_reagent_volume
 * breif: 设置R4试剂体积。
 * param: reagent_volume - 试剂体积。
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_volume(
	const int reagent_volume){
	_r4_reagent_volume=reagent_volume;
}

/**
 * name: get_r4_reagent_volume
 * breif: 获取R4试剂体积。
 * param: --
 * return: 返回R4试剂体积。
 */
int ApplicationAnalysisData::get_r4_reagent_volume() const{
	return(_r4_reagent_volume);
}

/**
 * name: set_r4_diluent_volume
 * breif: 设置R4稀释液体积。
 * param: diluent_volume - 稀释液体积。
 * return: --
 */
void ApplicationAnalysisData::set_r4_diluent_volume(
	const int diluent_volume){
	_r4_diluent_volume=diluent_volume;
}

/**
 * name: get_r4_diluent_volume
 * breif: 获取R4稀释液体积。
 * param: --
 * return: 返回R4稀释液体积。
 */
int ApplicationAnalysisData::get_r4_diluent_volume() const{
	return(_r4_diluent_volume);
}

/** 
 * name: set_r4_reagent_code
 * breif: 设置R4试剂编号。
 * param: reagent_code - 试剂编号。
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_code(
	const int reagent_code){
	_r4_reagent_code=reagent_code;
}

/**
 * name: get_r4_reagent_code
 * breif: 获取R4试剂编号。
 * param: --
 * return: 返回R4试剂编号。
 */
int ApplicationAnalysisData::get_r4_reagent_code() const{
	return(_r4_reagent_code);
}

/**
 * name: set_r4_reagent_stability
 * brief: 设置R4试剂有效期。
 * param: reagent_stability - 试剂有效期。
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_stability(
	const int reagent_stability){
	_r4_reagent_stability=reagent_stability;
}

/**
 * name: get_r4_reagent_stability
 * breif: 获取R4试剂有效期。
 * param: --
 * return: 返回R4试剂有效期。
 */
int ApplicationAnalysisData::get_r4_reagent_stability() const{
	return(_r4_reagent_stability);
}

/**
 * name: set_substrate_1_volume
 * breif: 设置底物1体积。
 * param: substrate_volume - 底物体积。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_volume(
	const int substrate_volume){
	_substrate_1_volume=substrate_volume;
}

/**
 * name: get_substrate_1_volume
 * breif: 获取底物1体积。
 * param: --
 * return: 返回底物1体积。
 */
int ApplicationAnalysisData::get_substrate_1_volume() const{
	return(_substrate_1_volume);
}

/**
 * name: set_substrate_1_code
 * breif: 设置底物1编号。
 * param: substrate_code - 底物1编号。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_code(
	const int substrate_code){
	_substrate_1_code=substrate_code;
}

/**
 * name: get_substrate_1_code
 * breif: 获取底物1编号。
 * param: --
 * return: 返回底物1编号。
 */
int ApplicationAnalysisData::get_substrate_1_code() const{
	return(_substrate_1_code);
}

/**
 * name: set_substrate_1_stability
 * breif: 设置底物1有效期。
 * param: substrate_stability - 底物有效期。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_stability(
	const int substrate_stability){
	_substrate_1_stability=substrate_stability;
}

/**
 * name: get_substrate_1_stability
 * breif: 获取底物1有效期。
 * param: --
 * return: 返回底物1有效期。
 */
int ApplicationAnalysisData::get_substrate_1_stability() const{
	return(_substrate_1_stability);
}

/**
 * name: set_substrate_2_volume
 * breif: 设置底物2体积。
 * param: substrate_volume - 底物体积。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_volume(
	const int substrate_volume){
	_substrate_2_volume=substrate_volume;
}

/**
 * name: get_substrate_2_volume
 * breif: 获取底物2体积。
 * param: --
 * return: 返回底物2体积。
 */
int ApplicationAnalysisData::get_substrate_2_volume() const{
	return(_substrate_2_volume);
}

/**
 * name: set_substrate_2_code
 * breif: 设置底物2编号。
 * param: substrate_code - 底物1编号。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_code(
	const int substrate_code){
	_substrate_2_code=substrate_code;
}

/**
 * name: get_substrate_2_code
 * breif: 获取底物2编号。
 * param: --
 * return: 返回底物2编号。
 */
int ApplicationAnalysisData::get_substrate_2_code() const{
	return(_substrate_2_code);
}

/**
 * name: set_substrate_2_stability
 * breif: 设置底物2有效期。
 * param: substrate_stability - 底物有效期。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_stability(
	const int substrate_stability){
	_substrate_2_stability=substrate_stability;
}

/**
 * name: get_substrate_2_stability
 * breif: 获取底物2有效期。
 * param: --
 * return: 返回底物2有效期。
 */
int ApplicationAnalysisData::get_substrate_2_stability() const{
	return(_substrate_2_stability);
}

/**
 * name: set_substrate_3_volume
 * breif: 设置底物3体积。
 * param: substrate_volume - 底物体积。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_volume(
	const int substrate_volume){
	_substrate_3_volume=substrate_volume;
}

/**
 * name: get_substrate_3_volume
 * breif: 获取底物3体积。
 * param: --
 * return: 返回底物3体积。
 */
int ApplicationAnalysisData::get_substrate_3_volume() const{
	return(_substrate_3_volume);
}

/**
 * name: set_substrate_3_code
 * breif: 设置底物3编号。
 * param: substrate_code - 底物编号。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_code(
	const int substrate_code){
	_substrate_3_code=substrate_code;
}

/**
 * name: get_substrate_3_code
 * breif: 获取底物3编号。
 * param: --
 * return: 返回底物3编号。
 */
int ApplicationAnalysisData::get_substrate_3_code() const{
	return(_substrate_3_code);
}

/**
 * name: set_substrate_3_stability
 * breif: 设置底物3有效期。
 * param: substrate_stability - 底物有效期。
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_stability(
	const int substrate_stability){
	_substrate_3_stability=substrate_stability;
}

/**
 * name: get_substrate_3_stability
 * breif: 获取底物3有效期。
 * param: --
 * return: 返回底物3有效期。
 */
int ApplicationAnalysisData::get_substrate_3_stability() const{
	return(_substrate_3_stability);
}

/**
 * name: set_buffer_solution_volume
 * breif: 设置缓冲液体积。
 * param: buffer_solution_volume - 缓冲液体积。
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_volume(
	const int buffer_solution_volume){
	_buffer_solution_volume=buffer_solution_volume;
}

/**
 * name: get_buffer_solution_volume
 * breif: 获取缓冲液体积。
 * param: --
 * return: 返回缓冲液体积。
 */
int ApplicationAnalysisData::get_buffer_solution_volume() const{
	return(_buffer_solution_volume);
}

/**
 * name: set_buffer_solution_code
 * breif: 设置缓冲液编号。
 * param: buffer_solution_code - 缓冲液编号。
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_code(
	const int buffer_solution_code){
	_buffer_solution_code=buffer_solution_code;
}

/**
 * name: get_buffer_solution_code
 * breif: 获取缓冲液编号。
 * param: --
 * return: 返回缓冲液编号。
 */
int ApplicationAnalysisData::get_buffer_solution_code() const{
	return(_buffer_solution_code);
}

/**
 * name: set_buffer_solution_stability
 * breif: 设置缓冲液有效期。
 * param: buffer_solution_stability - 缓冲液有效期。
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_stability(
	const int buffer_solution_stability){
	_buffer_solution_stability=buffer_solution_stability;
}

/**
 * name: get_buffer_solution_stability
 * breif: 获取缓冲液有效期。
 * param: --
 * return: 返回缓冲液有效期。
 */
int ApplicationAnalysisData::get_buffer_solution_stability() const{
	return(_buffer_solution_stability);
}

/**
 * name: is_valid
 * breif: 当前的分析数据是否合法。
 * param: error_message - 输出的错误信息（无错误时返回空）。
 * return: 如果当前分析数据合法，返回值大于等于零，否则返回值小于零。
 */
int ApplicationAnalysisData::is_valid(CString *error_message/*=0*/) const{
	//1.调用基类相应处理函数。
	const int result=ApplicationData::is_valid(error_message);
	if(result<0){
		return(result);
	}
	//2.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//3.检测分析方法标识是否合法。
	if((_analysis_method_id<1)||(_analysis_method_id>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING246),1,99);
		}
		return(-4);
	}
	//4.检测检测孵育时间是否合法。
	if((_checkout_incubation_time<0)||(_checkout_incubation_time>1800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING247),0,1800);
		}
		return(-5);
	}
	//5.检测第一次孵育时间是否合法。
	if((_incubation_time_1<0)||(_incubation_time_1>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING248),0,3600);
		}
		return(-6);
	}
	//6.检测第二次孵育时间是否合法。
	if((_incubation_time_2<0)||(_incubation_time_2>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING249),0,3600);
		}
		return(-7);
	}
	//7.检测第三次孵育时间是否合法。
	if((_incubation_time_3<0)||(_incubation_time_3>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING250),0,3600);
		}
		return(-8);
	}
	//8.检测第四次孵育时间是否合法。
	if((_incubation_time_4<0)||(_incubation_time_4>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING251),0,3600);
		}
		return(-9);
	}
	//9.检测稀释液编码是否合法。
	if((_diluent_code<401)||(_diluent_code>600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING252),401,600);
		}
		return(-10);
	}
	//10.检测稀释液有效期是否合法。
	if((_diluent_stability<0)||(_diluent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING253),0,365);
		}
		return(-11);
	}
	//11.检测稀释方法标识是否合法。
	if((_dilution_method_id<0)||(_dilution_method_id>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING254),1,99);
		}
		return(-12);
	}
	//12.检测普通样本体积。
	if(((_normal_sample_volume<15)||(_normal_sample_volume>75))&&(
		0!=_normal_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING255),15,75,0);
		}
		return(-13);
	}
	//13.检测普通稀释后样本体积。
	if(((_normal_dilution_sample_volume<15)||(_normal_dilution_sample_volume>75))&&(
		0!=_normal_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING256),15,75,0);
		}
		return(-14);
	}
	//14.检测普通稀释液体积。
	if(((_normal_diluent_volume<25)||(_normal_diluent_volume>150))&&(
		0!=_normal_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING257),25,150,0);
		}
		return(-15);
	}
	//15.检测减量样本体积。
	if(((_decrease_sample_volume<15)||(_decrease_sample_volume>75))&&(
		0!=_decrease_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING258),15,75,0);
		}
		return(-16);
	}
	//16.检测减量稀释后样本体积。
	if(((_decrease_dilution_sample_volume<15)||(_decrease_dilution_sample_volume>75))&&(
		0!=_decrease_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING259),15,75,0);
		}
		return(-17);
	}
	//17.检测减量稀释液体积。
	if(((_decrease_diluent_volume<25)||(_decrease_diluent_volume>150))&&(
		0!=_decrease_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING260),25,150,0);
		}
		return(-18);
	}
	//18.检测增量样本体积。
	if(((_increase_sample_volume<15)||(_increase_sample_volume>75))&&(
		0!=_increase_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING261),15,75,0);
		}
		return(-19);
	}
	//19.检测增量稀释后样本体积。
	if(((_increase_dilution_sample_volume<15)||(_increase_dilution_sample_volume>75))&&(
		0!=_increase_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING262),15,75,0);
		}
		return(-20);
	}
	//20.检测增量稀释液体积。
	if(((_increase_diluent_volume<25)||(_increase_diluent_volume>150))&&(
		0!=_increase_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING263),25,150,0);
		}
		return(-21);
	}
	//21.检测R1试剂体积。
	if(((_r1_reagent_volume<25)||(_r1_reagent_volume>150))&&(
		0!=_r1_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING264),25,150,0);
		}
		return(-22);
	}
	//22.检测R1稀释液体积。
	if(((_r1_diluent_volume<25)||(_r1_diluent_volume>150))&&(
		0!=_r1_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING265),25,150,0);
		}
		return(-23);
	}
	//23.检测R1试剂编号。
	if((_r1_reagent_code<1)||(_r1_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING266),1,200);
		}
		return(-24);
	}
	//24.检测R1试剂有效期。
	if((_r1_reagent_stability<0)||(_r1_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING267),0,365);
		}
		return(-25);
	}
	//25.检测R2试剂体积。
	if(((_r2_reagent_volume<25)||(_r2_reagent_volume>150))&&(
		0!=_r2_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING268),25,150,0);
		}
		return(-26);
	}
	//26.检测R2稀释液体积。
	if(((_r2_diluent_volume<25)||(_r2_diluent_volume>150))&&(
		0!=_r2_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING269),25,150,0);
		}
		return(-27);
	}
	//27.检测R2试剂编号。
	if((_r2_reagent_code<1)||(_r2_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING270),1,200);
		}
		return(-28);
	}
	//28.检测R2试剂有效期。
	if((_r2_reagent_stability<0)||(_r2_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING271),0,365);
		}
		return(-29);
	}
	//29.检测R3试剂体积。
	if(((_r3_reagent_volume<25)||(_r3_reagent_volume>150))&&(
		0!=_r3_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING272),25,150,0);
		}
		return(-30);
	}
	//30.检测R3稀释液体积。
	if(((_r3_diluent_volume<25)||(_r3_diluent_volume>150))&&(
		0!=_r3_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING273),25,150,0);
		}
		return(-31);
	}
	//31.检测R3试剂编号。
	if((_r3_reagent_code<1)||(_r3_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING274),1,200);
		}
		return(-32);
	}
	//32.检测R3试剂有效期。
	if((_r3_reagent_stability<0)||(_r3_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING275),0,365);
		}
		return(-33);
	}
	//33.检测R4试剂体积。
	if(((_r4_reagent_volume<25)||(_r4_reagent_volume>150))&&(
		0!=_r4_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING276),25,150,0);
		}
		return(-34);
	}
	//34.检测R4稀释液体积。
	if(((_r4_diluent_volume<25)||(_r4_diluent_volume>150))&&(
		0!=_r4_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING277),25,150,0);
		}
		return(-35);
	}
	//35.检测R4试剂编号。
	if((_r4_reagent_code<1)||(_r4_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING278),1,200);
		}
		return(-36);
	}
	//36.检测R4试剂有效期。
	if((_r4_reagent_stability<0)||(_r4_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING279),0,365);
		}
		return(-37);
	}
	//37.检测底物1体积。
	if(((_substrate_1_volume<50)||(_substrate_1_volume>400))&&(
		0!=_substrate_1_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING280),50,400,0);
		}
		return(-38);
	}
	//38.检测底物1编码。
	if((_substrate_1_code<601)||(_substrate_1_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING281),601,800);
		}
		return(-39);
	}
	//39.检测底物1有效期。
	if((_substrate_1_stability<0)||(_substrate_1_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING282),0,365);
		}
		return(-40);
	}
	//40.检测底物2体积。
	if(((_substrate_2_volume<50)||(_substrate_2_volume>400))&&(
		0!=_substrate_2_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING283),50,400,0);
		}
		return(-41);
	}
	//41.检测底物2编码。
	if((_substrate_2_code<601)||(_substrate_2_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING284),601,800);
		}
		return(-42);
	}
	//42.检测底物2有效期。
	if((_substrate_2_stability<0)||(_substrate_2_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING285),0,365);
		}
		return(-43);
	}
	//43.检测底物3体积。
	if(((_substrate_3_volume<50)||(_substrate_3_volume>400))&&(
		0!=_substrate_3_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING286),50,400,0);
		}
		return(-44);
	}
	//44.检测底物3编码。
	if((_substrate_3_code<601)||(_substrate_3_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING287),601,800);
		}
		return(-45);
	}
	//45.检测底物3有效期。
	if((_substrate_3_stability<0)||(_substrate_3_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING288),0,365);
		}
		return(-46);
	}
	//46.检测缓冲液体积。
	if(((_buffer_solution_volume<50)||(_buffer_solution_volume>400))&&(
		0!=_buffer_solution_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING289),50,400,0);
		}
		return(-47);
	}
	//47.检测缓冲液编码。
	if((_buffer_solution_code<801)||(_buffer_solution_code>1000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING290),801,1000);
		}
		return(-48);
	}
	//48.检测缓冲液有效期。
	if((_buffer_solution_stability<0)||(_buffer_solution_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING291),0,365);
		}
		return(-49);
	}
	//49.程序运行到此成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * breif: 将当前类中数据重置为默认值。
 * param: reagent_code - 输入的试剂编号。
 * return: --
 */
void ApplicationAnalysisData::reset_default_value(const int reagent_code){
	//1.调用基类相应处理函数。
	ApplicationData::reset_default_value(reagent_code);
	//2.将当前类中数据设置为默认值。
	_analysis_method_id=1;
	_checkout_incubation_time=5;
	_incubation_time_1=600;
	_incubation_time_2=300;
	_incubation_time_3=0;
	_incubation_time_4=0;
	_diluent_code=401;
	_diluent_stability=90;
	_dilution_method_id=0;
	_normal_sample_volume=15;
	_normal_dilution_sample_volume=0;
	_normal_diluent_volume=0;
	_decrease_sample_volume=0;
	_decrease_dilution_sample_volume=0;
	_decrease_diluent_volume=0;
	_increase_sample_volume=0;
	_increase_dilution_sample_volume=0;
	_increase_diluent_volume=0;
	_r1_reagent_volume=50;
	_r1_diluent_volume=0;
	_r1_reagent_code=reagent_code;
	_r1_reagent_stability=90;
	_r2_reagent_volume=50;
	_r2_diluent_volume=0;
	_r2_reagent_code=reagent_code;
	_r2_reagent_stability=90;
	_r3_reagent_volume=0;
	_r3_diluent_volume=0;
	_r3_reagent_code=reagent_code;
	_r3_reagent_stability=90;
	_r4_reagent_volume=50;
	_r4_diluent_volume=0;
	_r4_reagent_code=reagent_code;
	_r4_reagent_stability=90;
	_substrate_1_volume=100;
	_substrate_1_code=601;
	_substrate_1_stability=90;
	_substrate_2_volume=100;
	_substrate_2_code=602;
	_substrate_2_stability=90;
	_substrate_3_volume=0;
	_substrate_3_code=603;
	_substrate_3_stability=90;
	_buffer_solution_volume=0;
	_buffer_solution_code=801;
	_buffer_solution_stability=90;
}

/**
 * name: update
 * breif: 从指定的记录集中下载更新数据。
 * param: recordset - 输入指定的记录集。
 *        column - 输入/输出记录集当前/下一个的列。
 * return: 如果函数执行成功返回回值大于等于零，否则返回值小于零。
 */
int ApplicationAnalysisData::update(MtADORecordset &recordset,int &column){
	//1.调用基类相应处理函数。
	if(ApplicationData::update(recordset,column)<0){
		return(-1);
	}
	//2.声明当前操作所需变量。
	_variant_t value;
	//3.获取记录集中的分析方法标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	_analysis_method_id=MtADODataConverter::to_int(value);
	//4.获取记录集中的检测孵育时间。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	_checkout_incubation_time=MtADODataConverter::to_int(value);
	//5.获取记录集中的第一次孵育时间。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	_incubation_time_1=MtADODataConverter::to_int(value);
	//6.获取记录集中的第二次孵育时间。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-5);
	}
	_incubation_time_2=MtADODataConverter::to_int(value);
	//7.获取记录集中的第三次孵育时间。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-6);
	}
	_incubation_time_3=MtADODataConverter::to_int(value);
	//8.获取记录集中的第四次孵育时间。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-7);
	}
	_incubation_time_4=MtADODataConverter::to_int(value);
	//9.获取记录集中的稀释液编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-8);
	}
	_diluent_code=MtADODataConverter::to_int(value);
	//10.获取记录集中的稀释液有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-9);
	}
	_diluent_stability=MtADODataConverter::to_int(value);
	//11.获取记录集中的稀释方法标识。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-10);
	}
	_dilution_method_id=MtADODataConverter::to_int(value);
	//12.获取记录集中常规样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-11);
	}
	_normal_sample_volume=MtADODataConverter::to_int(value);	
	//13.获取记录集中常规稀释后样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-12);
	}
	_normal_dilution_sample_volume=MtADODataConverter::to_int(value);
	//14.获取记录集中常规稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-13);
	}
	_normal_diluent_volume=MtADODataConverter::to_int(value);
	//15.获取记录集中减量样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-14);
	}
	_decrease_sample_volume=MtADODataConverter::to_int(value);	
	//16.获取记录集中减量稀释后样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-15);
	}
	_decrease_dilution_sample_volume=MtADODataConverter::to_int(value);
	//17.获取记录集中减量稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-16);
	}
	_decrease_diluent_volume=MtADODataConverter::to_int(value);
	//18.获取记录集中增量样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-17);
	}
	_increase_sample_volume=MtADODataConverter::to_int(value);
	//19.获取记录集中增量稀释后样本体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-18);
	}
	_increase_dilution_sample_volume=MtADODataConverter::to_int(value);
	//20.获取记录集中增量稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-19);
	}
	_increase_diluent_volume=MtADODataConverter::to_int(value);
	//21.获取记录集中R1试剂体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-20);
	}
	_r1_reagent_volume=MtADODataConverter::to_int(value);
	//22.获取记录集中R1稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-21);
	}
	_r1_diluent_volume=MtADODataConverter::to_int(value);
	//23.获取记录集中R1试剂编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-22);
	}
	_r1_reagent_code=MtADODataConverter::to_int(value);
	//24.获取记录集中R1试剂有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-23);
	}
	_r1_reagent_stability=MtADODataConverter::to_int(value);
	//25.获取记录集中R2试剂体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-24);
	}
	_r2_reagent_volume=MtADODataConverter::to_int(value);
	//26.获取记录集中R2稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-25);
	}
	_r2_diluent_volume=MtADODataConverter::to_int(value);
	//27.获取记录集中R2试剂编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-26);
	}
	_r2_reagent_code=MtADODataConverter::to_int(value);
	//28.获取记录集中R2试剂有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-27);
	}
	_r2_reagent_stability=MtADODataConverter::to_int(value);
	//29.获取记录集中R3试剂体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-28);
	}
	_r3_reagent_volume=MtADODataConverter::to_int(value);
	//30.获取记录集中R3稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-29);
	}
	_r3_diluent_volume=MtADODataConverter::to_int(value);
	//31.获取记录集中R3试剂编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-30);
	}
	_r3_reagent_code=MtADODataConverter::to_int(value);
	//32.获取记录集中R3试剂有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-31);
	}
	_r3_reagent_stability=MtADODataConverter::to_int(value);
	//33.获取记录集中R4试剂体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-32);
	}
	_r4_reagent_volume=MtADODataConverter::to_int(value);
	//34.获取记录集中R4稀释液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-33);
	}
	_r4_diluent_volume=MtADODataConverter::to_int(value);
	//35.获取记录集中R4试剂编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-34);
	}
	_r4_reagent_code=MtADODataConverter::to_int(value);
	//36.获取记录集中R4试剂有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-35);
	}
	_r4_reagent_stability=MtADODataConverter::to_int(value);
	//37.获取记录集中底物1的体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-36);
	}
	_substrate_1_volume=MtADODataConverter::to_int(value);
	//38.获取记录集中底物1的编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-37);
	}
	_substrate_1_code=MtADODataConverter::to_int(value);
	//39.获取记录集中底物1的有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-38);
	}
	_substrate_1_stability=MtADODataConverter::to_int(value);
	//40.获取记录集中底物2的体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-39);
	}
	_substrate_2_volume=MtADODataConverter::to_int(value);
	//41.获取记录集中底物2的编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-40);
	}
	_substrate_2_code=MtADODataConverter::to_int(value);
	//42.获取记录集中底物2的有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-41);
	}
	_substrate_2_stability=MtADODataConverter::to_int(value);
	//43.获取记录集中底物3的体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-42);
	}
	_substrate_3_volume=MtADODataConverter::to_int(value);
	//44.获取记录集中底物3的编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-43);
	}
	_substrate_3_code=MtADODataConverter::to_int(value);
	//45.获取记录集中底物3的有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-44);
	}
	_substrate_3_stability=MtADODataConverter::to_int(value);
	//46.获取记录集中缓冲液体积。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-45);
	}
	_buffer_solution_volume=MtADODataConverter::to_int(value);
	//47.获取记录集中缓冲液编号。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-46);
	}
	_buffer_solution_code=MtADODataConverter::to_int(value);
	//48.获取记录集中缓冲液有效期。
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-47);
	}
	_buffer_solution_stability=MtADODataConverter::to_int(value);
	//49.检测获取的分析数据是否合法。
	if(is_valid()<0){
		return(-48);
	}
	//50.程序运行到此直接返回。
	return(0);
}

/**
 * name: commit
 * brief: 将类中的数据提交到数据库中。
 * param: commit_means -  输入的提交方式（1 插入 2 更新 3 删除）。
 *        database - 输入的目标数据库引用。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int ApplicationAnalysisData::commit(const int commit_means,Database &database) const{
	//1.调用基类相应处理函数。
	if(ApplicationData::commit(commit_means,database)<0){
		return(-1);
	}
	//2.确保当前准备提交到数据库中的数据合法有效。
	if(is_valid()<0){
		return(-2);
	}
	//3.向数据库中提交数据。
	//3-1.声明当前操作所需变量。
	CString command(_T(""));
	//3-2.如果当前期望以插入的形式提交数据。
	if(1==commit_means){
		command.Format(_T("INSERT INTO [analyze_application]([module_id],\
			[specimen_type_id],[item_id],[analysis_method_id],\
			[checkout_incubation_time],[incubation_time_1],[incubation_time_2],\
			[incubation_time_3],[incubation_time_4],[diluent_code],\
			[diluent_stability],[dilution_method_id],[normal_sample_volume],\
			[normal_dilution_sample_volume],[normal_diluent_volume],\
			[decrease_sample_volume],[decrease_dilution_sample_volume],\
			[decrease_diluent_volume],[increase_sample_volume],\
			[increase_dilution_sample_volume],[increase_diluent_volume],\
			[r1_reagent_volume],[r1_diluent_volume],[r1_reagent_code],\
			[r1_reagent_stability],[r2_reagent_volume],[r2_diluent_volume],\
			[r2_reagent_code],[r2_reagent_stability],[r3_reagent_volume],\
			[r3_diluent_volume],[r3_reagent_code],[r3_reagent_stability],\
			[r4_reagent_volume],[r4_diluent_volume],[r4_reagent_code],\
			[r4_reagent_stability],[substrate_1_volume],[substrate_1_code],\
			[substrate_1_stability],[substrate_2_volume],[substrate_2_code],\
			[substrate_2_stability],[substrate_3_volume],[substrate_3_code],\
			[substrate_3_stability],[buffer_solution_volume],[buffer_solution_code],\
			[buffer_solution_stability])VALUES('%d','%d','%d','%d','%d','%d','%d','%d',\
			'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
			'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
			'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')"),get_module_id(),
			get_specimen_type_id(),get_item_id(),_analysis_method_id,_checkout_incubation_time,
			_incubation_time_1,_incubation_time_2,_incubation_time_3,_incubation_time_4,
			_diluent_code,_diluent_stability,_dilution_method_id,_normal_sample_volume,
			_normal_dilution_sample_volume,_normal_diluent_volume,_decrease_sample_volume,
			_decrease_dilution_sample_volume,_decrease_diluent_volume,_increase_sample_volume,
			_increase_dilution_sample_volume,_increase_diluent_volume,_r1_reagent_volume,
			_r1_diluent_volume,_r1_reagent_code,_r1_reagent_stability,_r2_reagent_volume,
			_r2_diluent_volume,_r2_reagent_code,_r2_reagent_stability,_r3_reagent_volume,
			_r3_diluent_volume,_r3_reagent_code,_r3_reagent_stability,_r4_reagent_volume,
			_r4_diluent_volume,_r4_reagent_code,_r4_reagent_stability,_substrate_1_volume,
			_substrate_1_code,_substrate_1_stability,_substrate_2_volume,_substrate_2_code,
			_substrate_2_stability,_substrate_3_volume,_substrate_3_code,_substrate_3_stability,
			_buffer_solution_volume,_buffer_solution_code,_buffer_solution_stability);
	}
	//3-3.如果当前期望以更新的形式提交数据。
	else if(2==commit_means){
		command.Format(_T("UPDATE [analyze_application] SET [analysis_method_id]='%d',\
			[checkout_incubation_time]='%d',[incubation_time_1]='%d',[incubation_time_2]='%d',\
			[incubation_time_3]='%d',[incubation_time_4]='%d',[diluent_code]='%d',\
			[diluent_stability]='%d',[dilution_method_id]='%d',[normal_sample_volume]='%d',\
			[normal_dilution_sample_volume]='%d',[normal_diluent_volume]='%d',\
			[decrease_sample_volume]='%d',[decrease_dilution_sample_volume]='%d',\
			[decrease_diluent_volume]='%d',[increase_sample_volume]='%d',\
			[increase_dilution_sample_volume]='%d',[increase_diluent_volume]='%d',\
			[r1_reagent_volume]='%d',[r1_diluent_volume]='%d',[r1_reagent_code]='%d',\
			[r1_reagent_stability]='%d',[r2_reagent_volume]='%d',[r2_diluent_volume]='%d',\
			[r2_reagent_code]='%d',[r2_reagent_stability]='%d',[r3_reagent_volume]='%d',\
			[r3_diluent_volume]='%d',[r3_reagent_code]='%d',[r3_reagent_stability]='%d',\
			[r4_reagent_volume]='%d',[r4_diluent_volume]='%d',[r4_reagent_code]='%d',\
			[r4_reagent_stability]='%d',[substrate_1_volume]='%d',[substrate_1_code]='%d',\
			[substrate_1_stability]='%d',[substrate_2_volume]='%d',[substrate_2_code]='%d',\
			[substrate_2_stability]='%d',[substrate_3_volume]='%d',[substrate_3_code]='%d',\
			[substrate_3_stability]='%d',[buffer_solution_volume]='%d',[buffer_solution_code]='%d',\
			[buffer_solution_stability]='%d' WHERE [module_id]='%d' AND [specimen_type_id]='%d' AND \
			[item_id]='%d'"),_analysis_method_id,_checkout_incubation_time,_incubation_time_1,
			_incubation_time_2,_incubation_time_3,_incubation_time_4,_diluent_code,_diluent_stability,
			_dilution_method_id,_normal_sample_volume,_normal_dilution_sample_volume,_normal_diluent_volume,
			_decrease_sample_volume,_decrease_dilution_sample_volume,_decrease_diluent_volume,
			_increase_sample_volume,_increase_dilution_sample_volume,_increase_diluent_volume,
			_r1_reagent_volume,_r1_diluent_volume,_r1_reagent_code,_r1_reagent_stability,_r2_reagent_volume,
			_r2_diluent_volume,_r2_reagent_code,_r2_reagent_stability,_r3_reagent_volume,_r3_diluent_volume,
			_r3_reagent_code,_r3_reagent_stability,_r4_reagent_volume,_r4_diluent_volume,_r4_reagent_code,
			_r4_reagent_stability,_substrate_1_volume,_substrate_1_code,_substrate_1_stability,
			_substrate_2_volume,_substrate_2_code,_substrate_2_stability,_substrate_3_volume,
			_substrate_3_code,_substrate_3_stability,_buffer_solution_volume,_buffer_solution_code,
			_buffer_solution_stability,get_module_id(),get_specimen_type_id(),get_item_id());
	}
	//3-4.如果当前期望以删除的方式将输入提交到数据库中。
	else if(3==commit_means){
		command.Format(_T("DELETE FROM [analyze_application] WHERE [module_id]='%d' AND \
						  [specimen_type_id]='%d' AND [item_id]='%d'"),get_module_id(),
						  get_specimen_type_id(),get_item_id());
	}
	//3-5.如果当前期望以其它方式将数据提交到数据库中。
	else{
		return(-3);
	}
	//3-6.将数据提交到数据库中，并且判断提交是否成功。
	if(database.execute(command)<0){
		return(-4);
	}
	//4.程序运行到此成功返回。
	return(0);
}