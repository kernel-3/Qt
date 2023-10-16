#include"stdafx.h"
#include"ApplicationAnalysisData.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../global/Theme.h"
#include"../../global/Database.h"
#include"../../../Resource.h"

/**
 * name: ApplicationAnalysisData
 * breif: ���캯����
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
 * breif: ���캯����
 * param: module_id - �����ģ���ʶ��
 *        specimen_type_id - �����������ʶ��
 *        item_id - �������Ŀ��ʶ��
 *        item_no - �������Ŀ��š�
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
 * breif: ����������
 * param: --
 * return: --
 */
ApplicationAnalysisData::~ApplicationAnalysisData(void){
}

/**
 * name: set_analysis_method_id
 * breif: ���÷���������ʶ��
 * param: analysis_method_id - ����������ʶ��
 * return: --
 */
void ApplicationAnalysisData::set_analysis_method_id(const int analysis_method_id){
	_analysis_method_id=analysis_method_id;
}

/**
 * name: get_analysis_method_id
 * breif: ��ȡ����������ʶ��
 * param: --
 * return: ���ط���������ʶ��
 */
int ApplicationAnalysisData::get_analysis_method_id() const{
	return(_analysis_method_id);
}

/**
 * name: set_checkout_incubation_time
 * breif: ���ü�����ʱ�䡣
 * param: checkout_incubation_time - ������ʱ�䡣
 * return: --
 */
void ApplicationAnalysisData::set_checkout_incubation_time(
	const int checkout_incubation_time){
	_checkout_incubation_time=checkout_incubation_time;
}

/**
 * name: get_checkout_incubation_time
 * brief: ��ȡ������ʱ�䡣
 * param: --
 * return: ���ؼ�����ʱ�䡣
 */
int ApplicationAnalysisData::get_checkout_incubation_time() const{
	return(_checkout_incubation_time);
}

/**
 * name: set_incubation_time_1
 * breif: ���÷���ʱ��1��
 * param: incubation_time - ����ʱ�䡣
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_1(const int incubation_time){
	_incubation_time_1=incubation_time;
}

/**
 * name: get_incubation_time_1
 * breif: ��ȡ����ʱ��1��
 * param: --
 * return: ���ط���ʱ��1��
 */
int ApplicationAnalysisData::get_incubation_time_1() const{
	return(_incubation_time_1);
}

/**
 * name: set_incubation_time_2
 * breif: ���÷���ʱ��2��
 * param: incubation_time - ����ʱ�䡣
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_2(const int incubation_time){
	_incubation_time_2=incubation_time;
}

/**
 * name: get_incubation_time_2
 * breif: ��ȡ����ʱ��2��
 * param: --
 * return: ���ط���ʱ��2��
 */
int ApplicationAnalysisData::get_incubation_time_2() const{
	return(_incubation_time_2);
}

/**
 * name: set_incubation_time_3
 * breif: ���÷���ʱ��3��
 * param: incubation_time - ����ʱ�䡣
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_3(const int incubation_time){
	_incubation_time_3=incubation_time;
}

/**
 * name: get_incubation_time_3
 * breif: ��ȡ����ʱ��3��
 * param: --
 * return: ���ط���ʱ��3��
 */
int ApplicationAnalysisData::get_incubation_time_3() const{
	return(_incubation_time_3);
}

/**
 * name: set_incubation_time_4
 * breif: ���÷���ʱ��4��
 * param: incubation_time - ����ʱ�䡣
 * return: --
 */
void ApplicationAnalysisData::set_incubation_time_4(const int incubation_time){
	_incubation_time_4=incubation_time;
}

/**
 * name: get_incubation_time_4
 * breif: ��ȡ����ʱ��4��
 * param: --
 * return: ���ط���ʱ��4��
 */
int ApplicationAnalysisData::get_incubation_time_4() const{
	return(_incubation_time_4);
}

/**
 * name: set_diluent_code
 * breif: ����ϡ��Һ��š�
 * param: diluent_code - ϡ��Һ��š�
 * return: --
 */
void ApplicationAnalysisData::set_diluent_code(
	const int diluent_code){
	_diluent_code=diluent_code;
}

/**
 * name: get_diluent_code
 * breif: ��ȡϡ��Һ��š�
 * param: --
 * return: ����ϡ��Һ��š�
 */
int ApplicationAnalysisData::get_diluent_code() const{
	return(_diluent_code);
}

/**
 * name: set_diluent_stability
 * breif: ����ϡ��ҺЧ�ڡ�
 * param: diluent_stability - ϡ��Һ��Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_diluent_stability(
	const int diluent_stability){
	_diluent_stability=diluent_stability;
}

/**
 * name: get_diluent_stability
 * breif: ��ȡϡ��Һ��Ч�ڡ�
 * param: --
 * return: ����ϡ��Һ��Ч�ڡ�
 */
int ApplicationAnalysisData::get_diluent_stability() const{
	return(_diluent_stability);
}

/**
 * name: set_dilution_method_id
 * breif: ����ϡ��Һ������ʶ��
 * param: dilution_method_id - ϡ�ͷ�����ʶ��
 * return: --
 */
void ApplicationAnalysisData::set_dilution_method_id(
	const int dilution_method_id){
	_dilution_method_id=dilution_method_id;
}

/**
 * name: get_dilution_method_id
 * breif: ��ȡϡ��Һ������ʶ��
 * param: --
 * return: ����ϡ��Һ������ʶ��
 */
int ApplicationAnalysisData::get_dilution_method_id() const{
	return(_dilution_method_id);
}

/**
 * name: set_normal_sample_volume
 * breif: ���ó������������
 * param: normal_sample_volume - �������������
 * return: --
 */
void ApplicationAnalysisData::set_normal_sample_volume(
	const int normal_sample_volume){
	_normal_sample_volume=normal_sample_volume;
}

/**
 * name: get_normal_sample_volume
 * breif: ��ȡ�������������
 * param: --
 * return: ���س������������ 
 */
int ApplicationAnalysisData::get_normal_sample_volume() const{
	return(_normal_sample_volume);
}

/**
 * name: set_normal_dilution_sample_volume
 * brief: ���ó���ϡ�����������
 * param: normal_dilution_sample_volume - ����ϡ�����������
 * return: --
 */
void ApplicationAnalysisData::set_normal_dilution_sample_volume(
	const int normal_dilution_sample_volume){
	_normal_dilution_sample_volume=normal_dilution_sample_volume;
}

/**
 * name: get_normal_dilution_sample_volume
 * brief: ��ȡ����ϡ�����������
 * param: --
 * return: ���س���ϡ�����������
 */
int ApplicationAnalysisData::get_normal_dilution_sample_volume() const{
	return(_normal_dilution_sample_volume);
}

/**
 * name: set_normal_diluent_volume
 * brief: ���ó���ϡ��Һ�����
 * param: normal_diluent_volume - ����ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_normal_diluent_volume(
	const int normal_diluent_volume){
	_normal_diluent_volume=normal_diluent_volume;
}

/**
 * name: get_normal_diluent_volume
 * brief: ��ȡ����ϡ��Һ�����
 * param: --
 * return: ���س���ϡ��Һ�����
 */
int ApplicationAnalysisData::get_normal_diluent_volume() const{
	return(_normal_diluent_volume);
}

/**
 * name: set_decrease_sample_volume
 * breif: ���ü������������
 * param: decrease_sample_volume - �������������
 * return: --
 */
void ApplicationAnalysisData::set_decrease_sample_volume(
	const int decrease_sample_volume){
	_decrease_sample_volume=decrease_sample_volume;
}

/**
 * name: get_decrease_sample_volume
 * breif: ��ȡ�������������
 * param: --
 * return: ���ؼ������������ 
 */
int ApplicationAnalysisData::get_decrease_sample_volume() const{
	return(_decrease_sample_volume);
}

/**
 * name: set_decrease_dilution_sample_volume
 * brief: ���ü���ϡ�����������
 * param: decrease_dilution_sample_volume - ����ϡ�����������
 * return: --
 */
void ApplicationAnalysisData::set_decrease_dilution_sample_volume(
	const int decrease_dilution_sample_volume){
	_decrease_dilution_sample_volume=decrease_dilution_sample_volume;
}

/**
 * name: get_decrease_dilution_sample_volume
 * brief: ��ȡ����ϡ�����������
 * param: --
 * return: ���ؼ���ϡ�����������
 */
int ApplicationAnalysisData::get_decrease_dilution_sample_volume() const{
	return(_decrease_dilution_sample_volume);
}

/**
 * name: set_decrease_diluent_volume
 * brief: ���ü���ϡ��Һ�����
 * param: decrease_diluent_volume - ����ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_decrease_diluent_volume(
	const int decrease_diluent_volume){
	_decrease_diluent_volume=decrease_diluent_volume;
}

/**
 * name: get_decrease_diluent_volume
 * brief: ��ȡ����ϡ��Һ�����
 * param: --
 * return: ���ؼ���ϡ��Һ�����
 */
int ApplicationAnalysisData::get_decrease_diluent_volume() const{
	return(_decrease_diluent_volume);
}

/**
 * name: set_increase_sample_volume
 * breif: �����������������
 * param: increase_sample_volume - �������������
 * return: --
 */
void ApplicationAnalysisData::set_increase_sample_volume(
	const int increase_sample_volume){
	_increase_sample_volume=increase_sample_volume;
}

/**
 * name: get_increase_sample_volume
 * breif: ��ȡ�������������
 * param: --
 * return: ����������������� 
 */
int ApplicationAnalysisData::get_increase_sample_volume() const{
	return(_increase_sample_volume);
}

/**
 * name: set_increase_dilution_sample_volume
 * brief: ��������ϡ�����������
 * param: increase_dilution_sample_volume - ����ϡ�����������
 * return: --
 */
void ApplicationAnalysisData::set_increase_dilution_sample_volume(
	const int increase_dilution_sample_volume){
	_increase_dilution_sample_volume=increase_dilution_sample_volume;
}

/**
 * name: get_increase_dilution_sample_volume
 * brief: ��ȡ����ϡ�����������
 * param: --
 * return: ��������ϡ�����������
 */
int ApplicationAnalysisData::get_increase_dilution_sample_volume() const{
	return(_increase_dilution_sample_volume);
}

/**
 * name: set_increase_diluent_volume
 * brief: ��������ϡ��Һ�����
 * param: increase_diluent_volume - ����ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_increase_diluent_volume(
	const int increase_diluent_volume){
	_increase_diluent_volume=increase_diluent_volume;
}

/**
 * name: get_increase_diluent_volume
 * brief: ��ȡ����ϡ��Һ�����
 * param: --
 * return: ��������ϡ��Һ�����
 */
int ApplicationAnalysisData::get_increase_diluent_volume() const{
	return(_increase_diluent_volume);
}

/**
 * name: set_r1_reagent_volume
 * breif: ����R1�Լ������
 * param: reagent_volume - �Լ������
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_volume(
	const int reagent_volume){
	_r1_reagent_volume=reagent_volume;
}

/**
 * name: get_r1_reagent_volume
 * breif: ��ȡR1�Լ������
 * param: --
 * return: ����R1�Լ������
 */
int ApplicationAnalysisData::get_r1_reagent_volume() const{
	return(_r1_reagent_volume);
}

/**
 * name: set_r1_diluent_volume
 * breif: ����R1ϡ��Һ�����
 * param: diluent_volume - ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_r1_diluent_volume(
	const int diluent_volume){
	_r1_diluent_volume=diluent_volume;
}

/**
 * name: get_r1_diluent_volume
 * breif: ��ȡR1ϡ��Һ�����
 * param: --
 * return: ����R1ϡ��Һ�����
 */
int ApplicationAnalysisData::get_r1_diluent_volume() const{
	return(_r1_diluent_volume);
}

/** 
 * name: set_r1_reagent_code
 * breif: ����R1�Լ���š�
 * param: reagent_code - �Լ���š�
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_code(
	const int reagent_code){
	_r1_reagent_code=reagent_code;
}

/**
 * name: get_r1_reagent_code
 * breif: ��ȡR1�Լ���š�
 * param: --
 * return: ����R1�Լ���š�
 */
int ApplicationAnalysisData::get_r1_reagent_code() const{
	return(_r1_reagent_code);
}

/**
 * name: set_r1_reagent_stability
 * brief: ����R1�Լ���Ч�ڡ�
 * param: reagent_stability - �Լ���Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_r1_reagent_stability(
	const int reagent_stability){
	_r1_reagent_stability=reagent_stability;
}

/**
 * name: get_r1_reagent_stability
 * breif: ��ȡR1�Լ���Ч�ڡ�
 * param: --
 * return: ����R1�Լ���Ч�ڡ�
 */
int ApplicationAnalysisData::get_r1_reagent_stability() const{
	return(_r1_reagent_stability);
}

/**
 * name: set_r2_reagent_volume
 * breif: ����R2�Լ������
 * param: reagent_volume - �Լ������
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_volume(
	const int reagent_volume){
	_r2_reagent_volume=reagent_volume;
}

/**
 * name: get_r2_reagent_volume
 * breif: ��ȡR2�Լ������
 * param: --
 * return: ����R2�Լ������
 */
int ApplicationAnalysisData::get_r2_reagent_volume() const{
	return(_r2_reagent_volume);
}

/**
 * name: set_r2_diluent_volume
 * breif: ����R2ϡ��Һ�����
 * param: diluent_volume - ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_r2_diluent_volume(
	const int diluent_volume){
	_r2_diluent_volume=diluent_volume;
}

/**
 * name: get_r2_diluent_volume
 * breif: ��ȡR2ϡ��Һ�����
 * param: --
 * return: ����R2ϡ��Һ�����
 */
int ApplicationAnalysisData::get_r2_diluent_volume() const{
	return(_r2_diluent_volume);
}

/** 
 * name: set_r2_reagent_code
 * breif: ����R2�Լ���š�
 * param: reagent_code - �Լ���š�
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_code(
	const int reagent_code){
	_r2_reagent_code=reagent_code;
}

/**
 * name: get_r2_reagent_code
 * breif: ��ȡR2�Լ���š�
 * param: --
 * return: ����R2�Լ���š�
 */
int ApplicationAnalysisData::get_r2_reagent_code() const{
	return(_r2_reagent_code);
}

/**
 * name: set_r2_reagent_stability
 * brief: ����R2�Լ���Ч�ڡ�
 * param: reagent_stability - �Լ���Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_r2_reagent_stability(
	const int reagent_stability){
	_r2_reagent_stability=reagent_stability;
}

/**
 * name: get_r2_reagent_stability
 * breif: ��ȡR2�Լ���Ч�ڡ�
 * param: --
 * return: ����R2�Լ���Ч�ڡ�
 */
int ApplicationAnalysisData::get_r2_reagent_stability() const{
	return(_r2_reagent_stability);
}

/**
 * name: set_r3_reagent_volume
 * breif: ����R3�Լ������
 * param: reagent_volume - �Լ������
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_volume(
	const int reagent_volume){
	_r3_reagent_volume=reagent_volume;
}

/**
 * name: get_r3_reagent_volume
 * breif: ��ȡR3�Լ������
 * param: --
 * return: ����R3�Լ������
 */
int ApplicationAnalysisData::get_r3_reagent_volume() const{
	return(_r3_reagent_volume);
}

/**
 * name: set_r3_diluent_volume
 * breif: ����R3ϡ��Һ�����
 * param: diluent_volume - ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_r3_diluent_volume(
	const int diluent_volume){
	_r3_diluent_volume=diluent_volume;
}

/**
 * name: get_r3_diluent_volume
 * breif: ��ȡR3ϡ��Һ�����
 * param: --
 * return: ����R3ϡ��Һ�����
 */
int ApplicationAnalysisData::get_r3_diluent_volume() const{
	return(_r3_diluent_volume);
}

/** 
 * name: set_r3_reagent_code
 * breif: ����R3�Լ���š�
 * param: reagent_code - �Լ���š�
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_code(
	const int reagent_code){
	_r3_reagent_code=reagent_code;
}

/**
 * name: get_r3_reagent_code
 * breif: ��ȡR3�Լ���š�
 * param: --
 * return: ����R3�Լ���š�
 */
int ApplicationAnalysisData::get_r3_reagent_code() const{
	return(_r3_reagent_code);
}

/**
 * name: set_r3_reagent_stability
 * brief: ����R3�Լ���Ч�ڡ�
 * param: reagent_stability - �Լ���Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_r3_reagent_stability(
	const int reagent_stability){
	_r3_reagent_stability=reagent_stability;
}

/**
 * name: get_r3_reagent_stability
 * breif: ��ȡR3�Լ���Ч�ڡ�
 * param: --
 * return: ����R3�Լ���Ч�ڡ�
 */
int ApplicationAnalysisData::get_r3_reagent_stability() const{
	return(_r3_reagent_stability);
}

/**
 * name: set_r4_reagent_volume
 * breif: ����R4�Լ������
 * param: reagent_volume - �Լ������
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_volume(
	const int reagent_volume){
	_r4_reagent_volume=reagent_volume;
}

/**
 * name: get_r4_reagent_volume
 * breif: ��ȡR4�Լ������
 * param: --
 * return: ����R4�Լ������
 */
int ApplicationAnalysisData::get_r4_reagent_volume() const{
	return(_r4_reagent_volume);
}

/**
 * name: set_r4_diluent_volume
 * breif: ����R4ϡ��Һ�����
 * param: diluent_volume - ϡ��Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_r4_diluent_volume(
	const int diluent_volume){
	_r4_diluent_volume=diluent_volume;
}

/**
 * name: get_r4_diluent_volume
 * breif: ��ȡR4ϡ��Һ�����
 * param: --
 * return: ����R4ϡ��Һ�����
 */
int ApplicationAnalysisData::get_r4_diluent_volume() const{
	return(_r4_diluent_volume);
}

/** 
 * name: set_r4_reagent_code
 * breif: ����R4�Լ���š�
 * param: reagent_code - �Լ���š�
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_code(
	const int reagent_code){
	_r4_reagent_code=reagent_code;
}

/**
 * name: get_r4_reagent_code
 * breif: ��ȡR4�Լ���š�
 * param: --
 * return: ����R4�Լ���š�
 */
int ApplicationAnalysisData::get_r4_reagent_code() const{
	return(_r4_reagent_code);
}

/**
 * name: set_r4_reagent_stability
 * brief: ����R4�Լ���Ч�ڡ�
 * param: reagent_stability - �Լ���Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_r4_reagent_stability(
	const int reagent_stability){
	_r4_reagent_stability=reagent_stability;
}

/**
 * name: get_r4_reagent_stability
 * breif: ��ȡR4�Լ���Ч�ڡ�
 * param: --
 * return: ����R4�Լ���Ч�ڡ�
 */
int ApplicationAnalysisData::get_r4_reagent_stability() const{
	return(_r4_reagent_stability);
}

/**
 * name: set_substrate_1_volume
 * breif: ���õ���1�����
 * param: substrate_volume - ���������
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_volume(
	const int substrate_volume){
	_substrate_1_volume=substrate_volume;
}

/**
 * name: get_substrate_1_volume
 * breif: ��ȡ����1�����
 * param: --
 * return: ���ص���1�����
 */
int ApplicationAnalysisData::get_substrate_1_volume() const{
	return(_substrate_1_volume);
}

/**
 * name: set_substrate_1_code
 * breif: ���õ���1��š�
 * param: substrate_code - ����1��š�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_code(
	const int substrate_code){
	_substrate_1_code=substrate_code;
}

/**
 * name: get_substrate_1_code
 * breif: ��ȡ����1��š�
 * param: --
 * return: ���ص���1��š�
 */
int ApplicationAnalysisData::get_substrate_1_code() const{
	return(_substrate_1_code);
}

/**
 * name: set_substrate_1_stability
 * breif: ���õ���1��Ч�ڡ�
 * param: substrate_stability - ������Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_1_stability(
	const int substrate_stability){
	_substrate_1_stability=substrate_stability;
}

/**
 * name: get_substrate_1_stability
 * breif: ��ȡ����1��Ч�ڡ�
 * param: --
 * return: ���ص���1��Ч�ڡ�
 */
int ApplicationAnalysisData::get_substrate_1_stability() const{
	return(_substrate_1_stability);
}

/**
 * name: set_substrate_2_volume
 * breif: ���õ���2�����
 * param: substrate_volume - ���������
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_volume(
	const int substrate_volume){
	_substrate_2_volume=substrate_volume;
}

/**
 * name: get_substrate_2_volume
 * breif: ��ȡ����2�����
 * param: --
 * return: ���ص���2�����
 */
int ApplicationAnalysisData::get_substrate_2_volume() const{
	return(_substrate_2_volume);
}

/**
 * name: set_substrate_2_code
 * breif: ���õ���2��š�
 * param: substrate_code - ����1��š�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_code(
	const int substrate_code){
	_substrate_2_code=substrate_code;
}

/**
 * name: get_substrate_2_code
 * breif: ��ȡ����2��š�
 * param: --
 * return: ���ص���2��š�
 */
int ApplicationAnalysisData::get_substrate_2_code() const{
	return(_substrate_2_code);
}

/**
 * name: set_substrate_2_stability
 * breif: ���õ���2��Ч�ڡ�
 * param: substrate_stability - ������Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_2_stability(
	const int substrate_stability){
	_substrate_2_stability=substrate_stability;
}

/**
 * name: get_substrate_2_stability
 * breif: ��ȡ����2��Ч�ڡ�
 * param: --
 * return: ���ص���2��Ч�ڡ�
 */
int ApplicationAnalysisData::get_substrate_2_stability() const{
	return(_substrate_2_stability);
}

/**
 * name: set_substrate_3_volume
 * breif: ���õ���3�����
 * param: substrate_volume - ���������
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_volume(
	const int substrate_volume){
	_substrate_3_volume=substrate_volume;
}

/**
 * name: get_substrate_3_volume
 * breif: ��ȡ����3�����
 * param: --
 * return: ���ص���3�����
 */
int ApplicationAnalysisData::get_substrate_3_volume() const{
	return(_substrate_3_volume);
}

/**
 * name: set_substrate_3_code
 * breif: ���õ���3��š�
 * param: substrate_code - �����š�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_code(
	const int substrate_code){
	_substrate_3_code=substrate_code;
}

/**
 * name: get_substrate_3_code
 * breif: ��ȡ����3��š�
 * param: --
 * return: ���ص���3��š�
 */
int ApplicationAnalysisData::get_substrate_3_code() const{
	return(_substrate_3_code);
}

/**
 * name: set_substrate_3_stability
 * breif: ���õ���3��Ч�ڡ�
 * param: substrate_stability - ������Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_substrate_3_stability(
	const int substrate_stability){
	_substrate_3_stability=substrate_stability;
}

/**
 * name: get_substrate_3_stability
 * breif: ��ȡ����3��Ч�ڡ�
 * param: --
 * return: ���ص���3��Ч�ڡ�
 */
int ApplicationAnalysisData::get_substrate_3_stability() const{
	return(_substrate_3_stability);
}

/**
 * name: set_buffer_solution_volume
 * breif: ���û���Һ�����
 * param: buffer_solution_volume - ����Һ�����
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_volume(
	const int buffer_solution_volume){
	_buffer_solution_volume=buffer_solution_volume;
}

/**
 * name: get_buffer_solution_volume
 * breif: ��ȡ����Һ�����
 * param: --
 * return: ���ػ���Һ�����
 */
int ApplicationAnalysisData::get_buffer_solution_volume() const{
	return(_buffer_solution_volume);
}

/**
 * name: set_buffer_solution_code
 * breif: ���û���Һ��š�
 * param: buffer_solution_code - ����Һ��š�
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_code(
	const int buffer_solution_code){
	_buffer_solution_code=buffer_solution_code;
}

/**
 * name: get_buffer_solution_code
 * breif: ��ȡ����Һ��š�
 * param: --
 * return: ���ػ���Һ��š�
 */
int ApplicationAnalysisData::get_buffer_solution_code() const{
	return(_buffer_solution_code);
}

/**
 * name: set_buffer_solution_stability
 * breif: ���û���Һ��Ч�ڡ�
 * param: buffer_solution_stability - ����Һ��Ч�ڡ�
 * return: --
 */
void ApplicationAnalysisData::set_buffer_solution_stability(
	const int buffer_solution_stability){
	_buffer_solution_stability=buffer_solution_stability;
}

/**
 * name: get_buffer_solution_stability
 * breif: ��ȡ����Һ��Ч�ڡ�
 * param: --
 * return: ���ػ���Һ��Ч�ڡ�
 */
int ApplicationAnalysisData::get_buffer_solution_stability() const{
	return(_buffer_solution_stability);
}

/**
 * name: is_valid
 * breif: ��ǰ�ķ��������Ƿ�Ϸ���
 * param: error_message - ����Ĵ�����Ϣ���޴���ʱ���ؿգ���
 * return: �����ǰ�������ݺϷ�������ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationAnalysisData::is_valid(CString *error_message/*=0*/) const{
	//1.���û�����Ӧ��������
	const int result=ApplicationData::is_valid(error_message);
	if(result<0){
		return(result);
	}
	//2.������ǰ�������������
	Theme *theme=Theme::instance();
	//3.������������ʶ�Ƿ�Ϸ���
	if((_analysis_method_id<1)||(_analysis_method_id>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING246),1,99);
		}
		return(-4);
	}
	//4.��������ʱ���Ƿ�Ϸ���
	if((_checkout_incubation_time<0)||(_checkout_incubation_time>1800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING247),0,1800);
		}
		return(-5);
	}
	//5.����һ�η���ʱ���Ƿ�Ϸ���
	if((_incubation_time_1<0)||(_incubation_time_1>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING248),0,3600);
		}
		return(-6);
	}
	//6.���ڶ��η���ʱ���Ƿ�Ϸ���
	if((_incubation_time_2<0)||(_incubation_time_2>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING249),0,3600);
		}
		return(-7);
	}
	//7.�������η���ʱ���Ƿ�Ϸ���
	if((_incubation_time_3<0)||(_incubation_time_3>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING250),0,3600);
		}
		return(-8);
	}
	//8.�����Ĵη���ʱ���Ƿ�Ϸ���
	if((_incubation_time_4<0)||(_incubation_time_4>3600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING251),0,3600);
		}
		return(-9);
	}
	//9.���ϡ��Һ�����Ƿ�Ϸ���
	if((_diluent_code<401)||(_diluent_code>600)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING252),401,600);
		}
		return(-10);
	}
	//10.���ϡ��Һ��Ч���Ƿ�Ϸ���
	if((_diluent_stability<0)||(_diluent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING253),0,365);
		}
		return(-11);
	}
	//11.���ϡ�ͷ�����ʶ�Ƿ�Ϸ���
	if((_dilution_method_id<0)||(_dilution_method_id>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING254),1,99);
		}
		return(-12);
	}
	//12.�����ͨ���������
	if(((_normal_sample_volume<15)||(_normal_sample_volume>75))&&(
		0!=_normal_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING255),15,75,0);
		}
		return(-13);
	}
	//13.�����ͨϡ�ͺ����������
	if(((_normal_dilution_sample_volume<15)||(_normal_dilution_sample_volume>75))&&(
		0!=_normal_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING256),15,75,0);
		}
		return(-14);
	}
	//14.�����ͨϡ��Һ�����
	if(((_normal_diluent_volume<25)||(_normal_diluent_volume>150))&&(
		0!=_normal_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING257),25,150,0);
		}
		return(-15);
	}
	//15.���������������
	if(((_decrease_sample_volume<15)||(_decrease_sample_volume>75))&&(
		0!=_decrease_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING258),15,75,0);
		}
		return(-16);
	}
	//16.������ϡ�ͺ����������
	if(((_decrease_dilution_sample_volume<15)||(_decrease_dilution_sample_volume>75))&&(
		0!=_decrease_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING259),15,75,0);
		}
		return(-17);
	}
	//17.������ϡ��Һ�����
	if(((_decrease_diluent_volume<25)||(_decrease_diluent_volume>150))&&(
		0!=_decrease_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING260),25,150,0);
		}
		return(-18);
	}
	//18.����������������
	if(((_increase_sample_volume<15)||(_increase_sample_volume>75))&&(
		0!=_increase_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING261),15,75,0);
		}
		return(-19);
	}
	//19.�������ϡ�ͺ����������
	if(((_increase_dilution_sample_volume<15)||(_increase_dilution_sample_volume>75))&&(
		0!=_increase_dilution_sample_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING262),15,75,0);
		}
		return(-20);
	}
	//20.�������ϡ��Һ�����
	if(((_increase_diluent_volume<25)||(_increase_diluent_volume>150))&&(
		0!=_increase_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING263),25,150,0);
		}
		return(-21);
	}
	//21.���R1�Լ������
	if(((_r1_reagent_volume<25)||(_r1_reagent_volume>150))&&(
		0!=_r1_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING264),25,150,0);
		}
		return(-22);
	}
	//22.���R1ϡ��Һ�����
	if(((_r1_diluent_volume<25)||(_r1_diluent_volume>150))&&(
		0!=_r1_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING265),25,150,0);
		}
		return(-23);
	}
	//23.���R1�Լ���š�
	if((_r1_reagent_code<1)||(_r1_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING266),1,200);
		}
		return(-24);
	}
	//24.���R1�Լ���Ч�ڡ�
	if((_r1_reagent_stability<0)||(_r1_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING267),0,365);
		}
		return(-25);
	}
	//25.���R2�Լ������
	if(((_r2_reagent_volume<25)||(_r2_reagent_volume>150))&&(
		0!=_r2_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING268),25,150,0);
		}
		return(-26);
	}
	//26.���R2ϡ��Һ�����
	if(((_r2_diluent_volume<25)||(_r2_diluent_volume>150))&&(
		0!=_r2_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING269),25,150,0);
		}
		return(-27);
	}
	//27.���R2�Լ���š�
	if((_r2_reagent_code<1)||(_r2_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING270),1,200);
		}
		return(-28);
	}
	//28.���R2�Լ���Ч�ڡ�
	if((_r2_reagent_stability<0)||(_r2_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING271),0,365);
		}
		return(-29);
	}
	//29.���R3�Լ������
	if(((_r3_reagent_volume<25)||(_r3_reagent_volume>150))&&(
		0!=_r3_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING272),25,150,0);
		}
		return(-30);
	}
	//30.���R3ϡ��Һ�����
	if(((_r3_diluent_volume<25)||(_r3_diluent_volume>150))&&(
		0!=_r3_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING273),25,150,0);
		}
		return(-31);
	}
	//31.���R3�Լ���š�
	if((_r3_reagent_code<1)||(_r3_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING274),1,200);
		}
		return(-32);
	}
	//32.���R3�Լ���Ч�ڡ�
	if((_r3_reagent_stability<0)||(_r3_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING275),0,365);
		}
		return(-33);
	}
	//33.���R4�Լ������
	if(((_r4_reagent_volume<25)||(_r4_reagent_volume>150))&&(
		0!=_r4_reagent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING276),25,150,0);
		}
		return(-34);
	}
	//34.���R4ϡ��Һ�����
	if(((_r4_diluent_volume<25)||(_r4_diluent_volume>150))&&(
		0!=_r4_diluent_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING277),25,150,0);
		}
		return(-35);
	}
	//35.���R4�Լ���š�
	if((_r4_reagent_code<1)||(_r4_reagent_code>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING278),1,200);
		}
		return(-36);
	}
	//36.���R4�Լ���Ч�ڡ�
	if((_r4_reagent_stability<0)||(_r4_reagent_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING279),0,365);
		}
		return(-37);
	}
	//37.������1�����
	if(((_substrate_1_volume<50)||(_substrate_1_volume>400))&&(
		0!=_substrate_1_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING280),50,400,0);
		}
		return(-38);
	}
	//38.������1���롣
	if((_substrate_1_code<601)||(_substrate_1_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING281),601,800);
		}
		return(-39);
	}
	//39.������1��Ч�ڡ�
	if((_substrate_1_stability<0)||(_substrate_1_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING282),0,365);
		}
		return(-40);
	}
	//40.������2�����
	if(((_substrate_2_volume<50)||(_substrate_2_volume>400))&&(
		0!=_substrate_2_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING283),50,400,0);
		}
		return(-41);
	}
	//41.������2���롣
	if((_substrate_2_code<601)||(_substrate_2_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING284),601,800);
		}
		return(-42);
	}
	//42.������2��Ч�ڡ�
	if((_substrate_2_stability<0)||(_substrate_2_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING285),0,365);
		}
		return(-43);
	}
	//43.������3�����
	if(((_substrate_3_volume<50)||(_substrate_3_volume>400))&&(
		0!=_substrate_3_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING286),50,400,0);
		}
		return(-44);
	}
	//44.������3���롣
	if((_substrate_3_code<601)||(_substrate_3_code>800)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING287),601,800);
		}
		return(-45);
	}
	//45.������3��Ч�ڡ�
	if((_substrate_3_stability<0)||(_substrate_3_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING288),0,365);
		}
		return(-46);
	}
	//46.��⻺��Һ�����
	if(((_buffer_solution_volume<50)||(_buffer_solution_volume>400))&&(
		0!=_buffer_solution_volume)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING289),50,400,0);
		}
		return(-47);
	}
	//47.��⻺��Һ���롣
	if((_buffer_solution_code<801)||(_buffer_solution_code>1000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING290),801,1000);
		}
		return(-48);
	}
	//48.��⻺��Һ��Ч�ڡ�
	if((_buffer_solution_stability<0)||(_buffer_solution_stability>365)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING291),0,365);
		}
		return(-49);
	}
	//49.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * breif: ����ǰ������������ΪĬ��ֵ��
 * param: reagent_code - ������Լ���š�
 * return: --
 */
void ApplicationAnalysisData::reset_default_value(const int reagent_code){
	//1.���û�����Ӧ��������
	ApplicationData::reset_default_value(reagent_code);
	//2.����ǰ������������ΪĬ��ֵ��
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
 * breif: ��ָ���ļ�¼�������ظ������ݡ�
 * param: recordset - ����ָ���ļ�¼����
 *        column - ����/�����¼����ǰ/��һ�����С�
 * return: �������ִ�гɹ����ػ�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationAnalysisData::update(MtADORecordset &recordset,int &column){
	//1.���û�����Ӧ��������
	if(ApplicationData::update(recordset,column)<0){
		return(-1);
	}
	//2.������ǰ�������������
	_variant_t value;
	//3.��ȡ��¼���еķ���������ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-2);
	}
	_analysis_method_id=MtADODataConverter::to_int(value);
	//4.��ȡ��¼���еļ�����ʱ�䡣
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-3);
	}
	_checkout_incubation_time=MtADODataConverter::to_int(value);
	//5.��ȡ��¼���еĵ�һ�η���ʱ�䡣
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-4);
	}
	_incubation_time_1=MtADODataConverter::to_int(value);
	//6.��ȡ��¼���еĵڶ��η���ʱ�䡣
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-5);
	}
	_incubation_time_2=MtADODataConverter::to_int(value);
	//7.��ȡ��¼���еĵ����η���ʱ�䡣
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-6);
	}
	_incubation_time_3=MtADODataConverter::to_int(value);
	//8.��ȡ��¼���еĵ��Ĵη���ʱ�䡣
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-7);
	}
	_incubation_time_4=MtADODataConverter::to_int(value);
	//9.��ȡ��¼���е�ϡ��Һ��š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-8);
	}
	_diluent_code=MtADODataConverter::to_int(value);
	//10.��ȡ��¼���е�ϡ��Һ��Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-9);
	}
	_diluent_stability=MtADODataConverter::to_int(value);
	//11.��ȡ��¼���е�ϡ�ͷ�����ʶ��
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-10);
	}
	_dilution_method_id=MtADODataConverter::to_int(value);
	//12.��ȡ��¼���г������������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-11);
	}
	_normal_sample_volume=MtADODataConverter::to_int(value);	
	//13.��ȡ��¼���г���ϡ�ͺ����������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-12);
	}
	_normal_dilution_sample_volume=MtADODataConverter::to_int(value);
	//14.��ȡ��¼���г���ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-13);
	}
	_normal_diluent_volume=MtADODataConverter::to_int(value);
	//15.��ȡ��¼���м������������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-14);
	}
	_decrease_sample_volume=MtADODataConverter::to_int(value);	
	//16.��ȡ��¼���м���ϡ�ͺ����������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-15);
	}
	_decrease_dilution_sample_volume=MtADODataConverter::to_int(value);
	//17.��ȡ��¼���м���ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-16);
	}
	_decrease_diluent_volume=MtADODataConverter::to_int(value);
	//18.��ȡ��¼�����������������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-17);
	}
	_increase_sample_volume=MtADODataConverter::to_int(value);
	//19.��ȡ��¼��������ϡ�ͺ����������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-18);
	}
	_increase_dilution_sample_volume=MtADODataConverter::to_int(value);
	//20.��ȡ��¼��������ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-19);
	}
	_increase_diluent_volume=MtADODataConverter::to_int(value);
	//21.��ȡ��¼����R1�Լ������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-20);
	}
	_r1_reagent_volume=MtADODataConverter::to_int(value);
	//22.��ȡ��¼����R1ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-21);
	}
	_r1_diluent_volume=MtADODataConverter::to_int(value);
	//23.��ȡ��¼����R1�Լ���š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-22);
	}
	_r1_reagent_code=MtADODataConverter::to_int(value);
	//24.��ȡ��¼����R1�Լ���Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-23);
	}
	_r1_reagent_stability=MtADODataConverter::to_int(value);
	//25.��ȡ��¼����R2�Լ������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-24);
	}
	_r2_reagent_volume=MtADODataConverter::to_int(value);
	//26.��ȡ��¼����R2ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-25);
	}
	_r2_diluent_volume=MtADODataConverter::to_int(value);
	//27.��ȡ��¼����R2�Լ���š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-26);
	}
	_r2_reagent_code=MtADODataConverter::to_int(value);
	//28.��ȡ��¼����R2�Լ���Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-27);
	}
	_r2_reagent_stability=MtADODataConverter::to_int(value);
	//29.��ȡ��¼����R3�Լ������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-28);
	}
	_r3_reagent_volume=MtADODataConverter::to_int(value);
	//30.��ȡ��¼����R3ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-29);
	}
	_r3_diluent_volume=MtADODataConverter::to_int(value);
	//31.��ȡ��¼����R3�Լ���š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-30);
	}
	_r3_reagent_code=MtADODataConverter::to_int(value);
	//32.��ȡ��¼����R3�Լ���Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-31);
	}
	_r3_reagent_stability=MtADODataConverter::to_int(value);
	//33.��ȡ��¼����R4�Լ������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-32);
	}
	_r4_reagent_volume=MtADODataConverter::to_int(value);
	//34.��ȡ��¼����R4ϡ��Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-33);
	}
	_r4_diluent_volume=MtADODataConverter::to_int(value);
	//35.��ȡ��¼����R4�Լ���š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-34);
	}
	_r4_reagent_code=MtADODataConverter::to_int(value);
	//36.��ȡ��¼����R4�Լ���Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-35);
	}
	_r4_reagent_stability=MtADODataConverter::to_int(value);
	//37.��ȡ��¼���е���1�������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-36);
	}
	_substrate_1_volume=MtADODataConverter::to_int(value);
	//38.��ȡ��¼���е���1�ı�š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-37);
	}
	_substrate_1_code=MtADODataConverter::to_int(value);
	//39.��ȡ��¼���е���1����Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-38);
	}
	_substrate_1_stability=MtADODataConverter::to_int(value);
	//40.��ȡ��¼���е���2�������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-39);
	}
	_substrate_2_volume=MtADODataConverter::to_int(value);
	//41.��ȡ��¼���е���2�ı�š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-40);
	}
	_substrate_2_code=MtADODataConverter::to_int(value);
	//42.��ȡ��¼���е���2����Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-41);
	}
	_substrate_2_stability=MtADODataConverter::to_int(value);
	//43.��ȡ��¼���е���3�������
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-42);
	}
	_substrate_3_volume=MtADODataConverter::to_int(value);
	//44.��ȡ��¼���е���3�ı�š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-43);
	}
	_substrate_3_code=MtADODataConverter::to_int(value);
	//45.��ȡ��¼���е���3����Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-44);
	}
	_substrate_3_stability=MtADODataConverter::to_int(value);
	//46.��ȡ��¼���л���Һ�����
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-45);
	}
	_buffer_solution_volume=MtADODataConverter::to_int(value);
	//47.��ȡ��¼���л���Һ��š�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-46);
	}
	_buffer_solution_code=MtADODataConverter::to_int(value);
	//48.��ȡ��¼���л���Һ��Ч�ڡ�
	value=recordset.get_collect(MtADODataConverter::to_variant_t(column++));
	if(0!=recordset.get_last_error_code()){
		return(-47);
	}
	_buffer_solution_stability=MtADODataConverter::to_int(value);
	//49.����ȡ�ķ��������Ƿ�Ϸ���
	if(is_valid()<0){
		return(-48);
	}
	//50.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: commit
 * brief: �����е������ύ�����ݿ��С�
 * param: commit_means -  ������ύ��ʽ��1 ���� 2 ���� 3 ɾ������
 *        database - �����Ŀ�����ݿ����á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int ApplicationAnalysisData::commit(const int commit_means,Database &database) const{
	//1.���û�����Ӧ��������
	if(ApplicationData::commit(commit_means,database)<0){
		return(-1);
	}
	//2.ȷ����ǰ׼���ύ�����ݿ��е����ݺϷ���Ч��
	if(is_valid()<0){
		return(-2);
	}
	//3.�����ݿ����ύ���ݡ�
	//3-1.������ǰ�������������
	CString command(_T(""));
	//3-2.�����ǰ�����Բ������ʽ�ύ���ݡ�
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
	//3-3.�����ǰ�����Ը��µ���ʽ�ύ���ݡ�
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
	//3-4.�����ǰ������ɾ���ķ�ʽ�������ύ�����ݿ��С�
	else if(3==commit_means){
		command.Format(_T("DELETE FROM [analyze_application] WHERE [module_id]='%d' AND \
						  [specimen_type_id]='%d' AND [item_id]='%d'"),get_module_id(),
						  get_specimen_type_id(),get_item_id());
	}
	//3-5.�����ǰ������������ʽ�������ύ�����ݿ��С�
	else{
		return(-3);
	}
	//3-6.�������ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
	if(database.execute(command)<0){
		return(-4);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}