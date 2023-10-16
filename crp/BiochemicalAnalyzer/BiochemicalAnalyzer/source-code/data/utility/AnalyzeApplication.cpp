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
 * brief: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
AnalyzeApplication::~AnalyzeApplication(void){
}

/**
 * name: set_diluent_bottle_code
 * brief: ����ϡ��Һƿ�ӱ�š�
 * param: diluent_bottle_code - ϡ��Һƿ�ӱ�š�
 * return: --
 */
void AnalyzeApplication::set_diluent_bottle_code(const int diluent_bottle_code){
	_diluent_bottle_code=diluent_bottle_code;
}

/**
 * name: get_diluent_bottle_code
 * brief: ��ȡϡ��Һƿ�ӱ�š�
 * param: --
 * return: ����ϡ��Һƿ�ӱ�š�
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
 * brief: ���÷�Ӧʱ�䡣
 * param: reaction_time_id - ָ���ķ�Ӧʱ�䡣
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
 * breif: ���ò�����1��
 * param: measurement_point_1 - ������1��
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
 * breif: ���ò�����2��
 * param: measurement_point_2 - ������2��
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
 * breif: ���ò�����3��
 * param: measurement_point_3 - ������3��
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
 * breif: ���ò�����4��
 * param: measurement_point_4 - ������4��
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
 * breif: ���ø�������
 * param: secondary_wavelength_id - ָ���ĸ�������
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
 * breif: ������������
 * param: primary_wavelength_id - ָ������������
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
 * breif: ���÷�Ӧ����ϴ����
 * param: cell_detergent_id - ָ���ķ�Ӧ����ϴ����
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
 * breif: ����˫���ԡ�
 * param: twin_test_id - ָ����˫���ԡ�
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
 * brief: Ϊ����1������ͨ���������
 * param: normal_sample_volume_for_class_1 - ����1��ͨ���������
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
 * breif: Ϊ����1����ϡ�ͺ���ͨ���������
 * param: normal_dilution_sample_volume_for_class_1 - ����1ϡ�ͺ���ͨ���������
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
 * brief: Ϊ����1������ͨϡ��Һ�����
 * param: normal_diluent_volume_for_class_1 - ����1��ͨϡ��Һ�����
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
 * breif: Ϊ����1���ü������������
 * param: decreased_sample_volume_for_class_1 - �������������
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
 * breif: Ϊ����1����ϡ�ͺ�������������
 * param: decreased_dilution_sample_volume_for_class_1 - ϡ�ͺ�������������
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
 * brief: Ϊ����1���ü���ϡ��Һ�����
 * param: decreased_diluent_volume_for_class_1 - ����ϡ��Һ�����
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
 * brief: Ϊ����1�����������������
 * param: increased_sample_volume_for_class_1 - �������������
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
 * brief: Ϊ����1����ϡ�ͺ��������������
 * param: increased_dilution_sample_volume_for_class_1 - ϡ�ͺ��������������
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
 * brief: Ϊ����2������ͨ���������
 * param: normal_sample_volume_for_class_2 - ����2��ͨ���������
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
 * breif: Ϊ����2����ϡ�ͺ���ͨ���������
 * param: normal_dilution_sample_volume_for_class_2 - ����2ϡ�ͺ���ͨ������
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
 * brief: Ϊ����2������ͨϡ��Һ�����
 * param: normal_diluent_volume_for_class_2 - ����2��ͨϡ��Һ�����
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
 * brief: Ϊ����2���ü������������
 * param: decreased_sample_volume_for_class_2 - ����2�������������
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
 * brief: Ϊ����2����ϡ�ͺ�������������
 * param: decreased_dilution_sample_volume_for_class_2 - ����2ϡ�ͺ�������������
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
 * brief: Ϊ����2���ü���ϡ��Һ�����
 * param: decreased_diluent_volume_for_class_2 - ����2����ϡ��Һ�����
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
 * breif: Ϊ����2�����������������
 * param: increased_sample_volume_for_class_2 - ����2�������������
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
 * brief: Ϊ����2����ϡ�ͺ��������������
 * param: increased_dilution_sample_volume_for_class_2 - ����2ϡ�ͺ��������������
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
 * brief: Ϊ����2��������ϡ��Һ�����
 * param: increased_diluent_volume_for_class_2 - ����2����ϡ��Һ�����
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
 * brief: ����R1�Լ������
 * param: r1_reagent_volume - R1�Լ������
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
 * brief: ����R1�Լ�ϡ��Һ�����
 * param: r1_diluent_volume - R1�Լ�ϡ��Һ�����
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
 * breif: ����R1�Լ�ƿ�ӱ�š�
 * param: r1_bottle_code - R1�Լ�ƿ�ӱ�š�
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
 * brief: ����R1�Լ���Ч�ڡ�
 * param: r1_reagent_stability - R1�Լ���Ч�ڡ�
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
 * brief: ����R2�Լ������
 * param: r2_reagent_volume - R2�Լ������
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
 * brief: ����R2�Լ���ϡ��Һ�����
 * param: r2_diluent_volume - R2�Լ���ϡ��Һ�����
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
 * breif: ����R2�Լ�ƿ��š�
 * param: r2_bottle_code - R2�Լ�ƿ��š�
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
 * breif: ����R2�Լ���Ч�ڡ�
 * param: r2_reagent_stability - R2�Լ���Ч�ڡ�
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
 * breif: ����R3�Լ������
 * param: r3_reagent_volume - R3�Լ������
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
 * brief: ����R3�Լ���ϡ��Һ�����
 * param: r3_diluent_volume - R3�Լ���ϡ��Һ�����
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
 * brief: ����R3�Լ�ƿ��š�
 * param: r3_bottle_code - R3�Լ�ƿ��š�
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
 * brief: ����R3�Լ���Ч�ڡ�
 * param: r3_reagent_stability - R3�Լ���Ч�ڡ�
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
 * brief: ����R4�Լ������
 * param: r4_reagent_volume - R4�Լ������
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
 * brief: ����R4ϡ��Һ�����
 * param: r4_diluent_volume - R4ϡ��Һ�����
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
 * breif: ����R4�Լ�ƿ��š�
 * param: r4_bottle_code - R4�Լ�ƿ��š�
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
 * brief: ����R4�Լ���Ч�ڡ�
 * param: r4_reagent_stability - R4�Լ���Ч�ڡ�
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
 * brief: Ϊ����1�������������ֵ��
 * param: absorbance_limit_for_class_1 - ����1�����������ֵ��
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
 * brief: Ϊ����2�������������ֵ��
 * param: absorbance_limit_for_class_2 - ����2�����������ֵ��
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
 * breif: ���ü�����������ֵ�ķ�����
 * param: the_method_used_to_check_the_reaction_absorbance_limit - ������������ֵ�ķ�����
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
 * breif: ����ǰ��������������ֵ��
 * param: prozone_check_distinction_abs_low_limit - ǰ��������������ֵ��
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
 * breif: Ϊ����1����ǰ�����������ȵ�����ֵ��
 * param: prozone_lower_limit_for_class_1 - ����1ǰ�����������ȵ�����ֵ��
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
 * breif: Ϊ����1����ǰ�����������ȵ�����ֵ��
 * param: prozone_upper_limit_for_class_1 - ����1ǰ�����������ȵ�����ֵ��
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
 * breif: Ϊ����2����ǰ�����������ȵ�����ֵ��
 * param: prozone_lower_limit_for_class_2 - ����2ǰ�����������ȵ�����ֵ��
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
 * breif: Ϊ����2����ǰ�����������ȵ�����ֵ��
 * param: prozone_upper_limit_for_class_2 - ����2ǰ�����������ȵ�����ֵ��
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
 * brief: ����ǰ������1��ֵ��
 * param: prozone_check_point_1 - ǰ������1��ֵ��
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
 * brief: ����ǰ������2��ֵ��
 * param: prozone_check_point_2 - ǰ������2��ֵ��
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
 * brief: ����ǰ������3��ֵ��
 * param: prozone_check_point_3 - ǰ������3��ֵ��
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
 * brief: ����ǰ������4��ֵ��
 * param: prozone_check_point_4 - ǰ������4��ֵ��
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
 * brief: Ϊ����1��������Ȳ�ֵ������ֵ��
 * param: check_point_1_abs_difference - ����1������Ȳ�ֵ������ֵ��
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
 * brief: Ϊ����2��������Ȳ�ֵ������ֵ��
 * param: check_point_2_abs_difference - ����2������Ȳ�ֵ������ֵ��
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
 * brief: �жϵ�ǰ������������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ������������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
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
 * brief: ����ǰ���������������ΪĬ��ֵ��
 * param: item_id - ָ������Ŀ��ʶ��
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
 * brief: ����ǰ����Ŀ��Ϣ�ύ�����ݿ��С�
 * param: item_id - ��Ӧ����Ŀ��ʶ��
 *        method - �ύ�����ݿ�ķ�����1 ���� 2 ���£���
 *        database - ׼���ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int AnalyzeApplication::commit(const int item_id,const int method,Database &database) const{
	//1.�жϵ�ǰ���ݵ���Ŀ��ʶ�Ƿ�Ϸ���
	if((item_id<1)||(item_id>999)){
		return(-1);
	}
	//2.�����ݿ��ύǰ��Ҫ��⵱ǰ������Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-2);
	}
	//3.�����ǰ�����Բ���ķ�ʽ�������ύ�����ݿ��С�
	if(1==method){
		//3-1.���õ�ǰ���������γ��ύ���ݿ��SQL��䡣
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
		//3-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-3);
		}
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
	//4.�����ǰ�����Ը��µķ�ʽ�������ύ�����ݿ��С�
	else if(2==method){
		//4-1.���õ�ǰ��Ŀ�����γ��ύ���ݿ��SQL��䡣
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
		//4-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-4);
		}
		//4-3.�������е��˳ɹ����ء�
		return(0);
	}
	//5.�����ǰ������������ʽ�������ύ�����ݿ��С�
	else{
		return(-5);
	}
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ�ķ�����Ϣ��
 * param: record - ָ���ļ�¼����
 * return: �������ִ�г¹�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int AnalyzeApplication::update(MtADORecordset &record){
	//1.������ǰ�������������
	AnalyzeApplication analyze;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡϡ��Һƿ�ӱ�š�
	value=record.get_collect(MtADODataConverter::to_variant_t(6));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	analyze._diluent_bottle_code=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡϡ��Һ��Ч�ڡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(7));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	analyze._diluent_stability=MtADODataConverter::to_int(value);
	//4.��ָ���ļ�¼���л�ȡ����������
	value=record.get_collect(MtADODataConverter::to_variant_t(8));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	analyze._analysis_method_id=MtADODataConverter::to_int(value);
	//5.��ָ���ļ�¼���л�ȡ��Ӧʱ�䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(9));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	analyze._reaction_time_id=MtADODataConverter::to_int(value);
	//6.��ָ���ļ�¼���л�ȡ������1��
	value=record.get_collect(MtADODataConverter::to_variant_t(10));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	analyze._measurement_point_1=MtADODataConverter::to_int(value);
	//7.��ָ���ļ�¼���л�ȡ������2��
	value=record.get_collect(MtADODataConverter::to_variant_t(11));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	analyze._measurement_point_2=MtADODataConverter::to_int(value);
	//8.��ָ���ļ�¼���л�ȡ������3��
	value=record.get_collect(MtADODataConverter::to_variant_t(12));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	analyze._measurement_point_3=MtADODataConverter::to_int(value);
	//9.��ָ���ļ�¼���л�ȡ������4��
	value=record.get_collect(MtADODataConverter::to_variant_t(13));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	analyze._measurement_point_4=MtADODataConverter::to_int(value);
	//10.��ָ���ļ�¼���л�ȡ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(14));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	if(VT_NULL==value.vt){
		analyze._secondary_wavelength_id=0;
	}else{
		analyze._secondary_wavelength_id=MtADODataConverter::to_int(value);
	}
	//11.��ָ���ļ�¼���л�ȡ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(15));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	analyze._primary_wavelength_id=MtADODataConverter::to_int(value);
	//12.��ָ���ļ�¼���л�ȡ��Ӧ����ϴҺ��
	value=record.get_collect(MtADODataConverter::to_variant_t(16));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	analyze._cell_detergent_id=MtADODataConverter::to_int(value);
	//13.��ָ���ļ�¼���л�ȡ˫������Ŀ��ʶ��
	value=record.get_collect(MtADODataConverter::to_variant_t(17));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	if(VT_NULL==value.vt){
		analyze._twin_test_id=0;
	}else{
		analyze._twin_test_id=MtADODataConverter::to_int(value);
	}
	//14.��ָ���ļ�¼���л�ȡ���������������
	value=record.get_collect(MtADODataConverter::to_variant_t(18));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	analyze._normal_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//15.��ָ���ļ�¼���л�ȡ������ϡ�ͺ����������
	value=record.get_collect(MtADODataConverter::to_variant_t(19));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	analyze._normal_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//16.��ָ���ļ�¼���л�ȡ������ϡ��Һ�����
	value=record.get_collect(MtADODataConverter::to_variant_t(20));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	analyze._normal_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//17.��ָ���ļ�¼���л�ȡ���������������
	value=record.get_collect(MtADODataConverter::to_variant_t(21));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	analyze._decreased_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//18.��ָ���ļ�¼���л�ȡ������ϡ�ͺ����������
	value=record.get_collect(MtADODataConverter::to_variant_t(22));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	analyze._decreased_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//19.��ָ���ļ�¼���л�ȡ������ϡ��Һ�����
	value=record.get_collect(MtADODataConverter::to_variant_t(23));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	analyze._decreased_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//20.��ָ���ļ�¼���л�ȡ���������������
	value=record.get_collect(MtADODataConverter::to_variant_t(24));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	analyze._increased_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//21.��ָ���ļ�¼���л�ȡ������ϡ�ͺ����������
	value=record.get_collect(MtADODataConverter::to_variant_t(25));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	analyze._increased_dilution_sample_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//22.��ָ���ļ�¼���л�ȡ������ϡ��Һ�����
	value=record.get_collect(MtADODataConverter::to_variant_t(26));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	analyze._increased_diluent_volume_for_class_1=
		MtADODataConverter::to_double(value);
	//23.��ָ���ļ�¼���л�ȡ�������������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(27));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	analyze._normal_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//24.��ָ���ļ�¼���л�ȡ������ϡ�ͺ��������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(28));
	if(0!=record.get_last_error_code()){
		return(-23);
	}
	analyze._normal_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//25.��ָ���ļ�¼���л�ȡ������ϡ��Һ���������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(29));
	if(0!=record.get_last_error_code()){
		return(-24);
	}
	analyze._normal_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//26.��ָ���ļ�¼���л�ȡ�������������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(30));
	if(0!=record.get_last_error_code()){
		return(-25);
	}
	analyze._decreased_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//27.��ָ���ļ�¼���л�ȡ������ϡ�ͺ��������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(31));
	if(0!=record.get_last_error_code()){
		return(-26);
	}
	analyze._decreased_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//28.��ָ���ļ�¼���л�ȡ������ϡ��Һ���������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(32));
	if(0!=record.get_last_error_code()){
		return(-27);
	}
	analyze._decreased_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//29.��ָ���ļ�¼���л�ȡ�������������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(33));
	if(0!=record.get_last_error_code()){
		return(-28);
	}
	analyze._increased_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//30.��ָ���ļ�¼���л�ȡ������ϡ�ͺ��������������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(34));
	if(0!=record.get_last_error_code()){
		return(-29);
	}
	analyze._increased_dilution_sample_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//31.��ָ���ļ�¼���л�ȡ������ϡ��Һ���������2����
	value=record.get_collect(MtADODataConverter::to_variant_t(35));
	if(0!=record.get_last_error_code()){
		return(-30);
	}
	analyze._increased_diluent_volume_for_class_2=
		MtADODataConverter::to_double(value);
	//32.��ָ���ļ�¼���л�ȡ��R1�Լ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(36));
	if(0!=record.get_last_error_code()){
		return(-31);
	}
	analyze._r1_reagent_volume=MtADODataConverter::to_double(value);
	//33.��ָ���ļ�¼���л�ȡ��R1�Լ�ϡ��Һ�������
	value=record.get_collect(MtADODataConverter::to_variant_t(37));
	if(0!=record.get_last_error_code()){
		return(-32);
	}
	analyze._r1_diluent_volume=MtADODataConverter::to_double(value);
	//34.��ָ���ļ�¼���л�ȡR1�Լ�ƿ�ӱ�š�
	value=record.get_collect(MtADODataConverter::to_variant_t(38));
	if(0!=record.get_last_error_code()){
		return(-33);
	}
	analyze._r1_bottle_code=MtADODataConverter::to_int(value);
	//35.��ָ���ļ�¼���л�ȡR1�Լ���Ч�ڡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(39));
	if(0!=record.get_last_error_code()){
		return(-34);
	}
	analyze._r1_reagent_stability=MtADODataConverter::to_int(value);
	//36.��ָ���ļ�¼���л�ȡ��R2�Լ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(40));
	if(0!=record.get_last_error_code()){
		return(-35);
	}
	analyze._r2_reagent_volume=MtADODataConverter::to_double(value);
	//37.��ָ���ļ�¼���л�ȡ��R2�Լ�ϡ��Һ�������
	value=record.get_collect(MtADODataConverter::to_variant_t(41));
	if(0!=record.get_last_error_code()){
		return(-36);
	}
	analyze._r2_diluent_volume=MtADODataConverter::to_double(value);
	//38.��ָ���ļ�¼���л�ȡR2�Լ�ƿ�ӱ�š�
	value=record.get_collect(MtADODataConverter::to_variant_t(42));
	if(0!=record.get_last_error_code()){
		return(-37);
	}
	analyze._r2_bottle_code=MtADODataConverter::to_int(value);
	//39.��ָ���ļ�¼���л�ȡR2�Լ���Ч�ڡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(43));
	if(0!=record.get_last_error_code()){
		return(-38);
	}
	analyze._r2_reagent_stability=MtADODataConverter::to_int(value);
	//40.��ָ���ļ�¼���л�ȡ��R3�Լ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(44));
	if(0!=record.get_last_error_code()){
		return(-39);
	}
	analyze._r3_reagent_volume=MtADODataConverter::to_double(value);
	//41.��ָ���ļ�¼���л�ȡ��R3�Լ�ϡ��Һ�������
	value=record.get_collect(MtADODataConverter::to_variant_t(45));
	if(0!=record.get_last_error_code()){
		return(-40);
	}
	analyze._r3_diluent_volume=MtADODataConverter::to_double(value);
	//42.��ָ���ļ�¼���л�ȡR3�Լ�ƿ�ӱ�š�
	value=record.get_collect(MtADODataConverter::to_variant_t(46));
	if(0!=record.get_last_error_code()){
		return(-41);
	}
	analyze._r3_bottle_code=MtADODataConverter::to_int(value);
	//43.��ָ���ļ�¼���л�ȡR3�Լ���Ч�ڡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(47));
	if(0!=record.get_last_error_code()){
		return(-42);
	}
	analyze._r3_reagent_stability=MtADODataConverter::to_int(value);
	//44.��ָ���ļ�¼���л�ȡ��R4�Լ��������
	value=record.get_collect(MtADODataConverter::to_variant_t(48));
	if(0!=record.get_last_error_code()){
		return(-43);
	}
	analyze._r4_reagent_volume=MtADODataConverter::to_double(value);
	//45.��ָ���ļ�¼���л�ȡ��R4�Լ�ϡ��Һ�������
	value=record.get_collect(MtADODataConverter::to_variant_t(49));
	if(0!=record.get_last_error_code()){
		return(-44);
	}
	analyze._r4_diluent_volume=MtADODataConverter::to_double(value);
	//46.��ָ���ļ�¼���л�ȡR4�Լ�ƿ�ӱ�š�
	value=record.get_collect(MtADODataConverter::to_variant_t(50));
	if(0!=record.get_last_error_code()){
		return(-45);
	}
	analyze._r4_bottle_code=MtADODataConverter::to_int(value);
	//47.��ָ���ļ�¼���л�ȡR4�Լ���Ч�ڡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(51));
	if(0!=record.get_last_error_code()){
		return(-46);
	}
	analyze._r4_reagent_stability=MtADODataConverter::to_int(value);
	//48.��ָ���ļ�¼���л�ȡ����1�����������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(52));
	if(0!=record.get_last_error_code()){
		return(-47);
	}
	analyze._absorbance_limit_for_class_1=MtADODataConverter::to_int(value);
	//49.��ָ���ļ�¼���л�ȡ����2�����������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(53));
	if(0!=record.get_last_error_code()){
		return(-48);
	}
	analyze._absorbance_limit_for_class_2=MtADODataConverter::to_int(value);
	//50.��ָ���ļ�¼���л�ȡ������������ֵ�ķ�����
	value=record.get_collect(MtADODataConverter::to_variant_t(54));
	if(0!=record.get_last_error_code()){
		return(-49);
	}
	analyze._the_method_used_to_check_the_reaction_absorbance_limit=
		MtADODataConverter::to_int(value);
	//51.��ָ���ļ�¼���л�ȡǰ�������Сֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(55));
	if(0!=record.get_last_error_code()){
		return(-50);
	}
	analyze._prozone_check_distinction_abs_low_limit=
		MtADODataConverter::to_int(value);
	//52.��ָ���ļ�¼���л�ȡ����1ǰ������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(56));
	if(0!=record.get_last_error_code()){
		return(-51);
	}
	analyze._prozone_lower_limit_for_class_1=
		MtADODataConverter::to_int(value);
	//53.��ָ���ļ�¼���л�ȡ����1ǰ������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(57));
	if(0!=record.get_last_error_code()){
		return(-52);
	}
	analyze._prozone_upper_limit_for_class_1=
		MtADODataConverter::to_int(value);
	//54.��ָ���ļ�¼���л�ȡ����2ǰ������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(58));
	if(0!=record.get_last_error_code()){
		return(-53);
	}
	analyze._prozone_lower_limit_for_class_2=
		MtADODataConverter::to_int(value);
	//55.��ָ���ļ�¼���л�ȡ����2ǰ������ֵ��
	value=record.get_collect(MtADODataConverter::to_variant_t(59));
	if(0!=record.get_last_error_code()){
		return(-54);
	}
	analyze._prozone_upper_limit_for_class_2=
		MtADODataConverter::to_int(value);
	//56.��ָ���ļ�¼���л�ȡǰ������1��
	value=record.get_collect(MtADODataConverter::to_variant_t(60));
	if(0!=record.get_last_error_code()){
		return(-55);
	}
	analyze._prozone_check_point_1=
		MtADODataConverter::to_int(value);
	//57.��ָ���ļ�¼���л�ȡǰ������2��
	value=record.get_collect(MtADODataConverter::to_variant_t(61));
	if(0!=record.get_last_error_code()){
		return(-56);
	}
	analyze._prozone_check_point_2=
		MtADODataConverter::to_int(value);
	//58.��ָ���ļ�¼���л�ȡǰ������3��
	value=record.get_collect(MtADODataConverter::to_variant_t(62));
	if(0!=record.get_last_error_code()){
		return(-57);
	}
	analyze._prozone_check_point_3=
		MtADODataConverter::to_int(value);
	//59.��ָ���ļ�¼���л�ȡǰ������4��
	value=record.get_collect(MtADODataConverter::to_variant_t(63));
	if(0!=record.get_last_error_code()){
		return(-58);
	}
	analyze._prozone_check_point_4=
		MtADODataConverter::to_int(value);
	//60.��ָ���ļ�¼���л�ȡ����Ȳ�ֵ����1��
	value=record.get_collect(MtADODataConverter::to_variant_t(64));
	if(0!=record.get_last_error_code()){
		return(-59);
	}
	analyze._check_point_1_abs_difference=
		MtADODataConverter::to_int(value);
	//61.��ָ���ļ�¼���л�ȡ����Ȳ�ֵ����2��
	value=record.get_collect(MtADODataConverter::to_variant_t(65));
	if(0!=record.get_last_error_code()){
		return(-60);
	}
	analyze._check_point_2_abs_difference=
		MtADODataConverter::to_int(value);
	//62.�����ǰ��ȡ�ķ�����Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(analyze.is_valid()<0){
		return(-61);
	}
	//63.���浱ǰ�ĴӼ�¼���л�ȡ�ķ�����Ϣ��
	(*this)=analyze;
	//64.�������е��˳ɹ����ء�
	return(0);
}