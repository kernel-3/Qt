#include"stdafx.h"
#include"RangeApplication.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../../data/DataCustom.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include<assert.h>

/**
 * name: Range
 * brief: ���캯����
 * param: --
 * return: --
 */
RangeApplication::Range::Range()
	:_lower_age_limit(0)
	,_upper_age_limit(0)
	,_lower_age_unit_id(0)
	,_upper_age_unit_id(0)
	,_lower_limit_of_normal_for_males_1(0.0)
	,_upper_limit_of_normal_for_males_1(0.0)
	,_lower_limit_of_normal_for_males_2(0.0)
	,_upper_limit_of_normal_for_males_2(0.0)
	,_lower_limit_of_normal_for_males_3(0.0)
	,_upper_limit_of_normal_for_males_3(0.0)
	,_lower_limit_of_normal_for_females_1(0.0)
	,_upper_limit_of_normal_for_females_1(0.0)
	,_lower_limit_of_normal_for_females_2(0.0)
	,_upper_limit_of_normal_for_females_2(0.0)
	,_lower_limit_of_normal_for_females_3(0.0)
	,_upper_limit_of_normal_for_females_3(0.0)
	,_default_age(0)
	,_default_sex(0)
	,_lower_limit_for_repeat_range(0.0)
	,_upper_limit_for_repeat_range(0.0)
	,_is_use_qualitative_table(0)
	,_qualitative_limit_1(0.0)
	,_qualitative_limit_text_1(_T(""))
	,_qualitative_limit_2(0.0)
	,_qualitative_limit_text_2(_T(""))
	,_qualitative_limit_3(0.0)
	,_qualitative_limit_text_3(_T(""))
	,_qualitative_limit_4(0.0)
	,_qualitative_limit_text_4(_T(""))
	,_qualitative_limit_5(0.0)
	,_qualitative_limit_text_5(_T(""))
	,_qualitative_limit_text_6(_T("")){
}

/**
 * name: ~Range
 * brief: ����������
 * param: --
 * return: --
 */
RangeApplication::Range::~Range(){
}

/**
 * name: set_lower_age_limit
 * breif: �����������ޡ�
 * param: lower_age_limit - �������ޡ�
 * return: --
 */
void RangeApplication::Range::set_lower_age_limit(const int lower_age_limit){
	_lower_age_limit=lower_age_limit;
}

/**
 * name: get_lower_age_limit
 * breif: ��ȡ�������ޡ�
 * param: --
 * return: �����������ޡ�
 */
int RangeApplication::Range::get_lower_age_limit() const{
	return(_lower_age_limit);
}

/**
 * name: set_upper_age_limit
 * breif: �����������ޡ�
 * param: upper_age_limit - �������ޡ�
 * return: --
 */
void RangeApplication::Range::set_upper_age_limit(const int upper_age_limit){
	_upper_age_limit=upper_age_limit;
}

/**
 * name: get_upper_age_limit
 * breif: ��ȡ�������ޡ�
 * param: --
 * return: �����������ޡ�
 */
int RangeApplication::Range::get_upper_age_limit() const{
	return(_upper_age_limit);
}

/**
 * name: set_lower_age_unit_id
 * breif: �����������޵ĵ�λ��ʶ��
 * param: lower_age_unit_id - �������޵ĵ�λ��ʶ��
 * return: --
 */
void RangeApplication::Range::set_lower_age_unit_id(const int lower_age_unit_id){
	_lower_age_unit_id=lower_age_unit_id;
}

/**
 * name: get_lower_age_unit_id
 * breif: ��ȡ�������޵ĵ�λ��ʶ��
 * param: --
 * return: �����������޵ĵ�λ��ʶ��
 */
int RangeApplication::Range::get_lower_age_unit_id() const{
	return(_lower_age_unit_id);
}

/**
 * name: set_upper_age_unit_id
 * breif: �����������޵ĵ�λ��ʶ��
 * param: upper_age_unit_id - �������޵ĵ�λ��ʶ��
 * return: --
 */
void RangeApplication::Range::set_upper_age_unit_id(const int upper_age_unit_id){
	_upper_age_unit_id=upper_age_unit_id;
}

/**
 * name: get_upper_age_unit_id
 * breif: ��ȡ�������޵ĵ�λ��ʶ��
 * param: --
 * return: �����������޵ĵ�λ��ʶ��
 */
int RangeApplication::Range::get_upper_age_unit_id() const{
	return(_upper_age_unit_id);
}

/**
 * name: set_lower_limit_of_normal_for_males_1
 * breif: ��������������Χ�ķ�Χ1������ֵ��
 * param: lower_limit_of_normal_for_males_1 - ����������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_1(
	const double lower_limit_of_normal_for_males_1){
	_lower_limit_of_normal_for_males_1=lower_limit_of_normal_for_males_1;
}

/**
 * name: get_lower_limit_of_normal_for_males_1
 * breif: ��ȡ����������Χ�ķ�Χ1������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_1() const{
	return(_lower_limit_of_normal_for_males_1);
}

/**
 * name: set_upper_limit_of_normal_for_males_1
 * breif: ��������������Χ�ķ�Χ1������ֵ��
 * param: upper_limit_of_normal_for_males_1 - ����������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_1(
	const double upper_limit_of_normal_for_males_1){
	_upper_limit_of_normal_for_males_1=upper_limit_of_normal_for_males_1;
}

/**
 * name: get_upper_limit_of_normal_for_males_1
 * breif: ��ȡ����������Χ�ķ�Χ1������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_1() const{
	return(_upper_limit_of_normal_for_males_1);
}

/**
 * name: set_lower_limit_of_normal_for_males_2
 * breif: ��������������Χ�ķ�Χ2������ֵ��
 * param: lower_limit_of_normal_for_males_2 - ����������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_2(
	const double lower_limit_of_normal_for_males_2){
	_lower_limit_of_normal_for_males_2=lower_limit_of_normal_for_males_2;
}

/**
 * name: get_lower_limit_of_normal_for_males_2
 * breif: ��ȡ����������Χ�ķ�Χ2������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_2() const{
	return(_lower_limit_of_normal_for_males_2);
}

/**
 * name: set_upper_limit_of_normal_for_males_2
 * breif: ��������������Χ�ķ�Χ2������ֵ��
 * param: upper_limit_of_normal_for_males_2 - ����������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_2(
	const double upper_limit_of_normal_for_males_2){
	_upper_limit_of_normal_for_males_2=upper_limit_of_normal_for_males_2;
}

/**
 * name: get_upper_limit_of_normal_for_males_2
 * breif: ��ȡ����������Χ�ķ�Χ2������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_2() const{
	return(_upper_limit_of_normal_for_males_2);
}

/**
 * name: set_lower_limit_of_normal_for_males_3
 * breif: ��������������Χ�ķ�Χ3������ֵ��
 * param: lower_limit_of_normal_for_males_3 - ����������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_3(
	const double lower_limit_of_normal_for_males_3){
	_lower_limit_of_normal_for_males_3=lower_limit_of_normal_for_males_3;
}

/**
 * name: get_lower_limit_of_normal_for_males_3
 * breif: ��ȡ����������Χ�ķ�Χ3������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_3() const{
	return(_lower_limit_of_normal_for_males_3);
}

/**
 * name: set_upper_limit_of_normal_for_males_3
 * breif: ��������������Χ�ķ�Χ3������ֵ��
 * param: upper_limit_of_normal_for_males_3 - ����������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_3(
	const double upper_limit_of_normal_for_males_3){
	_upper_limit_of_normal_for_males_3=upper_limit_of_normal_for_males_3;
}

/**
 * name: get_upper_limit_of_normal_for_males_3
 * breif: ��ȡ����������Χ�ķ�Χ3������ֵ��
 * param: --
 * return: ��������������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_3() const{
	return(_upper_limit_of_normal_for_males_3);
}

/**
 * name: set_lower_limit_of_normal_for_females_1
 * breif: ����Ů��������Χ�ķ�Χ1������ֵ��
 * param: lower_limit_of_normal_for_females_1 - Ů��������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_1(
	const double lower_limit_of_normal_for_females_1){
	_lower_limit_of_normal_for_females_1=lower_limit_of_normal_for_females_1;
}

/**
 * name: get_lower_limit_of_normal_for_females_1
 * breif: ��ȡŮ��������Χ�ķ�Χ1������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_1() const{
	return(_lower_limit_of_normal_for_females_1);
}

/**
 * name: set_upper_limit_of_normal_for_females_1
 * breif: ����Ů��������Χ�ķ�Χ1������ֵ��
 * param: upper_limit_of_normal_for_females_1 - Ů��������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_1(
	const double upper_limit_of_normal_for_females_1){
	_upper_limit_of_normal_for_females_1=upper_limit_of_normal_for_females_1;
}

/**
 * name: get_upper_limit_of_normal_for_females_1
 * breif: ��ȡŮ��������Χ�ķ�Χ1������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_1() const{
	return(_upper_limit_of_normal_for_females_1);
}

/**
 * name: set_lower_limit_of_normal_for_females_2
 * breif: ����Ů��������Χ�ķ�Χ2������ֵ��
 * param: lower_limit_of_normal_for_females_2 - Ů��������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_2(
	const double lower_limit_of_normal_for_females_2){
	_lower_limit_of_normal_for_females_2=lower_limit_of_normal_for_females_2;
}

/**
 * name: get_lower_limit_of_normal_for_females_2
 * breif: ��ȡŮ��������Χ�ķ�Χ2������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_2() const{
	return(_lower_limit_of_normal_for_females_2);
}

/**
 * name: set_upper_limit_of_normal_for_females_2
 * breif: ����Ů��������Χ�ķ�Χ2������ֵ��
 * param: upper_limit_of_normal_for_females_2 - Ů��������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_2(
	const double upper_limit_of_normal_for_females_2){
	_upper_limit_of_normal_for_females_2=upper_limit_of_normal_for_females_2;
}

/**
 * name: get_upper_limit_of_normal_for_females_2
 * breif: ��ȡŮ��������Χ�ķ�Χ2������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_2() const{
	return(_upper_limit_of_normal_for_females_2);
}

/**
 * name: set_lower_limit_of_normal_for_females_3
 * breif: ����Ů��������Χ�ķ�Χ3������ֵ��
 * param: lower_limit_of_normal_for_females_3 - Ů��������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_3(
	const double lower_limit_of_normal_for_females_3){
	_lower_limit_of_normal_for_females_3=lower_limit_of_normal_for_females_3;
}

/**
 * name: get_lower_limit_of_normal_for_females_3
 * breif: ��ȡŮ��������Χ�ķ�Χ3������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_3() const{
	return(_lower_limit_of_normal_for_females_3);
}

/**
 * name: set_upper_limit_of_normal_for_females_3
 * breif: ����Ů��������Χ�ķ�Χ3������ֵ��
 * param: upper_limit_of_normal_for_females_3 - Ů��������Χ�ķ�Χ3������ֵ��
 * return: --s
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_3(
	const double upper_limit_of_normal_for_females_3){
	_upper_limit_of_normal_for_females_3=upper_limit_of_normal_for_females_3;
}

/**
 * name: get_upper_limit_of_normal_for_females_3
 * breif: ��ȡŮ��������Χ�ķ�Χ3������ֵ��
 * param: --
 * return: ����Ů��������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_3() const{
	return(_upper_limit_of_normal_for_females_3);
}

/**
 * name: set_default_age
 * brief: ����Ĭ�����䡣
 * param: default_age - Ĭ�����䡣
 * return: --
 */
void RangeApplication::Range::set_default_age(const int default_age){
	_default_age=default_age;
}

/**
 * name: get_default_age
 * breif: ��ȡĬ�����䡣
 * param: --
 * return: ����Ĭ�����䡣
 */
int RangeApplication::Range::get_default_age() const{
	return(_default_age);
}

/**
 * name: set_default_sex
 * brief: ����Ĭ���Ա�
 * param: default_sex - Ĭ���Ա�
 * return: --
 */
void RangeApplication::Range::set_default_sex(const int default_sex){
	_default_sex=default_sex;
}

/**
 * name: get_default_sex
 * breif: ��ȡĬ���Ա�
 * param: --
 * return: ����Ĭ���Ա�
 */
int RangeApplication::Range::get_default_sex() const{
	return(_default_sex);
}

/**
 * name: set_lower_limit_for_repeat_range
 * breif: ���ñ�׼���鷶Χ�����ޡ�
 * param: lower_limit_for_repeat_range - ��׼���鷶Χ�����ޡ�
 * return: --
 */
void RangeApplication::Range::set_lower_limit_for_repeat_range(
	const double lower_limit_for_repeat_range){
	_lower_limit_for_repeat_range=lower_limit_for_repeat_range;
}

/**
 * name: get_lower_limit_for_repeat_range
 * breif: ��ȡ��׼���鷶Χ�����ޡ�
 * param: --
 * return: ���ر�׼���鷶Χ�����ޡ�
 */
double RangeApplication::Range::get_lower_limit_for_repeat_range() const{
	return(_lower_limit_for_repeat_range);
}

/**
 * name: set_upper_limit_for_repeat_range
 * breif: ���ñ�׼���鷶Χ�����ޡ�
 * param: upper_limit_for_repeat_range - ��׼���鷶Χ�����ޡ�
 * return: --
 */
void RangeApplication::Range::set_upper_limit_for_repeat_range(
	const double upper_limit_for_repeat_range){
	_upper_limit_for_repeat_range=upper_limit_for_repeat_range;
}

/**
 * name: get_upper_limit_for_repeat_range
 * breif: ��ȡ��׼���鷶Χ�����ޡ�
 * param: --
 * return: ���ر�׼���鷶Χ�����ޡ�
 */
double RangeApplication::Range::get_upper_limit_for_repeat_range() const{
	return(_upper_limit_for_repeat_range);
}

/**
 * name: set_is_use_qualitative_table
 * breif: �����Ƿ�ʹ�ö��Ա�
 * param: is_use_qualitative_table - �Ƿ�ʹ�ö��Ա�0 ��ʹ�ã�1 ʹ�ã���
 * return: --
 */
void RangeApplication::Range::set_is_use_qualitative_table(
	const int is_use_qualitative_table){
	_is_use_qualitative_table=is_use_qualitative_table;
}

/**
 * name: get_is_use_qualitative_table
 * breif: ��ȡ�Ƿ�ʹ�ö��Ա�
 * param: --
 * return: �����Ƿ�ʹ�ö��Ա�
 */
int RangeApplication::Range::get_is_use_qualitative_table() const{
	return(_is_use_qualitative_table);
}

/**
 * name: set_qualitative_limit_1
 * breif: ���ö��Խ���1��
 * param: qualitative_limit_1 - ���Խ���1��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_1(
	const double qualitative_limit_1){
	_qualitative_limit_1=qualitative_limit_1;
}

/**
 * name: get_qualitative_limit_1
 * breif: ��ȡ���Խ���1��
 * param: --
 * return: ���ض��Խ���1��
 */
double RangeApplication::Range::get_qualitative_limit_1() const{
	return(_qualitative_limit_1);
}

/**
 * name: set_qualitative_limit_text_1
 * brief: ���ö��Խ��������ַ���1��
 * param: qualitative_limit_text_1 - ���Խ��������ַ���1��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_1(
	const CString &qualitative_limit_text_1){
	_qualitative_limit_text_1=qualitative_limit_text_1;
}

/**
 * name: get_qualitative_limit_text_1
 * brief: ��ȡ���Խ��������ַ���1��
 * param: --
 * return: ���ض��Խ��������ַ���1��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_1() const{
	return(_qualitative_limit_text_1);
}

/**
 * name: set_qualitative_limit_2
 * breif: ���ö��Խ���2��
 * param: qualitative_limit_2 - ���Խ���2��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_2(
	const double qualitative_limit_2){
	_qualitative_limit_2=qualitative_limit_2;
}

/**
 * name: get_qualitative_limit_2
 * breif: ��ȡ���Խ���2��
 * param: --
 * return: ���ض��Խ���2��
 */
double RangeApplication::Range::get_qualitative_limit_2() const{
	return(_qualitative_limit_2);
}

/**
 * name: set_qualitative_limit_text_2
 * brief: ���ö��Խ��������ַ���2��
 * param: qualitative_limit_text_2 - ���Խ��������ַ���2��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_2(
	const CString &qualitative_limit_text_2){
	_qualitative_limit_text_2=qualitative_limit_text_2;
}

/**
 * name: get_qualitative_limit_text_2
 * brief: ��ȡ���Խ��������ַ���2��
 * param: --
 * return: ���ض��Խ��������ַ���2��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_2() const{
	return(_qualitative_limit_text_2);
}

/**
 * name: set_qualitative_limit_3
 * breif: ���ö��Խ���3��
 * param: qualitative_limit_3 - ���Խ���3��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_3(
	const double qualitative_limit_3){
	_qualitative_limit_3=qualitative_limit_3;
}

/**
 * name: get_qualitative_limit_3
 * breif: ��ȡ���Խ���3��
 * param: --
 * return: ���ض��Խ���3��
 */
double RangeApplication::Range::get_qualitative_limit_3() const{
	return(_qualitative_limit_3);
}

/**
 * name: set_qualitative_limit_text_3
 * brief: ���ö��Խ��������ַ���3��
 * param: qualitative_limit_text_3 - ���Խ��������ַ���3��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_3(
	const CString &qualitative_limit_text_3){
	_qualitative_limit_text_3=qualitative_limit_text_3;
}

/**
 * name: get_qualitative_limit_text_3
 * brief: ��ȡ���Խ��������ַ���3��
 * param: --
 * return: ���ض��Խ��������ַ���3��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_3() const{
	return(_qualitative_limit_text_3);
}

/**
 * name: set_qualitative_limit_4
 * breif: ���ö��Խ���4��
 * param: qualitative_limit_4 - ���Խ���4��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_4(
	const double qualitative_limit_4){
	_qualitative_limit_4=qualitative_limit_4;
}

/**
 * name: get_qualitative_limit_4
 * breif: ��ȡ���Խ���4��
 * param: --
 * return: ���ض��Խ���4��
 */
double RangeApplication::Range::get_qualitative_limit_4() const{
	return(_qualitative_limit_4);
}

/**
 * name: set_qualitative_limit_text_4
 * brief: ���ö��Խ��������ַ���4��
 * param: qualitative_limit_text_4 - ���Խ��������ַ���4��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_4(
	const CString &qualitative_limit_text_4){
	_qualitative_limit_text_4=qualitative_limit_text_4;
}

/**
 * name: get_qualitative_limit_text_4
 * brief: ��ȡ���Խ��������ַ���4��
 * param: --
 * return: ���ض��Խ��������ַ���4��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_4() const{
	return(_qualitative_limit_text_4);
}

/**
 * name: set_qualitative_limit_5
 * breif: ���ö��Խ���5��
 * param: qualitative_limit_5 - ���Խ���5��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_5(
	const double qualitative_limit_5){
	_qualitative_limit_5=qualitative_limit_5;
}

/**
 * name: get_qualitative_limit_5
 * breif: ��ȡ���Խ���5��
 * param: --
 * return: ���ض��Խ���5��
 */
double RangeApplication::Range::get_qualitative_limit_5() const{
	return(_qualitative_limit_5);
}

/**
 * name: set_qualitative_limit_text_5
 * brief: ���ö��Խ��������ַ���5��
 * param: qualitative_limit_text_5 - ���Խ��������ַ���5��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_5(
	const CString &qualitative_limit_text_5){
	_qualitative_limit_text_5=qualitative_limit_text_5;
}

/**
 * name: get_qualitative_limit_text_5
 * brief: ��ȡ���Խ��������ַ���5��
 * param: --
 * return: ���ض��Խ��������ַ���5��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_5() const{
	return(_qualitative_limit_text_5);
}

/**
 * name: set_qualitative_limit_text_6
 * brief: ���ö��Խ��������ַ���6��
 * param: qualitative_limit_text_6 - ���Խ��������ַ���6��
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_6(
	const CString &qualitative_limit_text_6){
	_qualitative_limit_text_6=qualitative_limit_text_6;
}

/**
 * name: get_qualitative_limit_text_6
 * brief: ��ȡ���Խ��������ַ���6��
 * param: --
 * return: ���ض��Խ��������ַ���6��
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_6() const{
	return(_qualitative_limit_text_6);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ������������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ������������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int RangeApplication::Range::is_valid(CString *error_message) const{
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��⵱ǰ���������Ƿ�Ϸ���
	if((_lower_age_limit<0)||(_lower_age_limit>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING368),0,200);
		}
		return(-6);
	}
	//3.��⵱ǰ���������Ƿ�Ϸ���
	if((_upper_age_limit<0)||(_upper_age_limit>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING369),0,200);
		}
		return(-7);
	}
	//4.��⵱ǰ�������޵�λ�Ƿ�Ϸ���
	if(_lower_age_unit_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING370));
		}
		return(-8);
	}
	//5.��⵱ǰ�������޵�λ�Ƿ�Ϸ���
	if(_upper_age_unit_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING371));
		}
		return(-9);
	}
	//6.�������������Χ1������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_males_1<-99999.0)||(
		_lower_limit_of_normal_for_males_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-10);
	}
	//7.�������������Χ1������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_males_1<-99999.0)||(
		_upper_limit_of_normal_for_males_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-11);
	}
	//8.�������������Χ2������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_males_2<-99999.0)||(
		_lower_limit_of_normal_for_males_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-12);
	}
	//9.�������������Χ2������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_males_2<-99999.0)||(
		_upper_limit_of_normal_for_males_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-13);
	}
	//10.�������������Χ3������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_males_3<-99999.0)||(
		_lower_limit_of_normal_for_males_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-14);
	}
	//11.�������������Χ3������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_males_3<-99999.0)||(
		_upper_limit_of_normal_for_males_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-15);
	}
	//12.���Ů��������Χ1������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_females_1<-99999.0)||(
		_lower_limit_of_normal_for_females_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-16);
	}
	//13.���Ů��������Χ1������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_females_1<-99999.0)||(
		_upper_limit_of_normal_for_females_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-17);
	}
	//14.���Ů��������Χ2������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_females_2<-99999.0)||(
		_lower_limit_of_normal_for_females_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-18);
	}
	//15.���Ů��������Χ2������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_females_2<-99999.0)||(
		_upper_limit_of_normal_for_females_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-19);
	}
	//16.���Ů��������Χ3������ֵ�Ƿ�Ϸ���
	if((_lower_limit_of_normal_for_females_3<-99999.0)||(
		_lower_limit_of_normal_for_females_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-20);
	}
	//17.���Ů��������Χ3������ֵ�Ƿ�Ϸ���
	if((_upper_limit_of_normal_for_females_3<-99999.0)||(
		_upper_limit_of_normal_for_females_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-21);
	}
	//18.���Ĭ�������Ƿ�Ϸ���
	if((1!=_default_age)&&(2!=_default_age)&&(3!=_default_age)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING376));
		}
		return(-22);
	}
	//19.���Ĭ���Ա��Ƿ�Ϸ���
	if(_default_sex<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING377));
		}
		return(-23);
	}
	//20.��⸴�鷶Χ�����Ƿ�Ϸ���
	if((_lower_limit_for_repeat_range<-99999.0)||(
		_lower_limit_for_repeat_range>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING378),
				-99999.0,999999.0);
		}
		return(-24);
	}
	//21.��⸴�鷶Χ�����Ƿ�Ϸ���
	if((_upper_limit_for_repeat_range<-99999.0)||(
		_upper_limit_for_repeat_range>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING379),
				-99999.0,999999.0);
		}
		return(-25);
	}
	//22.����Ƿ�ѡ���Ա��Ƿ�Ϸ���
	if((0!=_is_use_qualitative_table)&&(1!=_is_use_qualitative_table)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING380));
		}
		return(-26);
	}
	//23.��ⶨ�Ա����ֵ�Ƿ�Ϸ���
	if(_is_use_qualitative_table){
		//23-1.��ⶨ�Խ���1�Ƿ�Ϸ���
		if((_qualitative_limit_1<-99999.0)&&(_qualitative_limit_1>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-27);
		}
		//23-2.��ⶨ�Խ���2�Ƿ�Ϸ���
		if((_qualitative_limit_2<-99999.0)&&(_qualitative_limit_2>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-28);
		}
		//23-3.��ⶨ�Խ���3�Ƿ�Ϸ���
		if((_qualitative_limit_3<-99999.0)&&(_qualitative_limit_3>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-29);
		}
		//23-4.��ⶨ�Խ���4�Ƿ�Ϸ���
		if((_qualitative_limit_4<-99999.0)&&(_qualitative_limit_4>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-30);
		}
		//23-5.��ⶨ�Խ���5�Ƿ�Ϸ���
		if((_qualitative_limit_5<-99999.0)&&(_qualitative_limit_5>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-31);
		}
	}
	//24.������������Ƿ���ڵ����������ޡ�
	if((_lower_age_limit*_lower_age_unit_id)>=(_upper_age_limit*_upper_age_unit_id)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING382));
		}
		return(-32);
	}
	//25.�������������Χ1�����Ƿ���ڵ�������������Χ1���ޡ�
	if((_lower_limit_of_normal_for_males_1>=_upper_limit_of_normal_for_males_1)||
		(is_zero(_lower_limit_of_normal_for_males_1-_upper_limit_of_normal_for_males_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-33);
	}
	//26.�������������Χ2�����Ƿ���ڵ�������������Χ2���ޡ�
	if((_lower_limit_of_normal_for_males_2>=_upper_limit_of_normal_for_males_2)||
		(is_zero(_lower_limit_of_normal_for_males_2-_upper_limit_of_normal_for_males_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-34);
	}
	//27.�������������Χ3�����Ƿ���ڵ�������������Χ3���ޡ�
	if((_lower_limit_of_normal_for_males_3>=_upper_limit_of_normal_for_males_3)||
		(is_zero(_lower_limit_of_normal_for_males_3-_upper_limit_of_normal_for_males_3))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-35);
	}
	//28.���Ů��������Χ1�����Ƿ���ڵ���Ů��������Χ1���ޡ�
	if((_lower_limit_of_normal_for_females_1>=_upper_limit_of_normal_for_females_1)||
		(is_zero(_lower_limit_of_normal_for_females_1-_upper_limit_of_normal_for_females_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-36);
	}
	//29.���Ů��������Χ2�����Ƿ���ڵ�Ů��������Χ2���ޡ�
	if((_lower_limit_of_normal_for_females_2>=_upper_limit_of_normal_for_females_2)||
		(is_zero(_lower_limit_of_normal_for_females_2-_upper_limit_of_normal_for_females_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-37);
	}
	//30.���Ů��������Χ3�����Ƿ���ڵ���Ů��������Χ3���ޡ�
	if((_lower_limit_of_normal_for_females_3>=_upper_limit_of_normal_for_females_3)||
		(is_zero(_lower_limit_of_normal_for_females_3-_upper_limit_of_normal_for_females_3))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-38);
	}
	//31.����׼���鷶Χ�����Ƿ���ڵ��ڱ�׼���鷶Χ���ޡ�
	if((_lower_limit_for_repeat_range>=_upper_limit_for_repeat_range)||
		(is_zero(_lower_limit_for_repeat_range-_upper_limit_for_repeat_range))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING385));
		}
		return(-39);
	}
	//32.��ⶨ�Է�Χ�����Ƿ��쳣��
	if(_is_use_qualitative_table){
		//32-1.������Խ���1���ڵ��ڶ��Խ���2��
		if((_qualitative_limit_1>=_qualitative_limit_2)||
			(is_zero(_qualitative_limit_1-_qualitative_limit_2))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-40);
		}
		//32-2.������Խ���2���ڵ��ڶ��Խ���3��
		if((_qualitative_limit_2>=_qualitative_limit_3)||
			(is_zero(_qualitative_limit_2-_qualitative_limit_3))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-41);
		}
		//32-3.������Խ���3���ڵ��ڶ��Խ���4��
		if((_qualitative_limit_3>=_qualitative_limit_4)||
			(is_zero(_qualitative_limit_3-_qualitative_limit_4))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-42);
		}
		//32-4.������Խ���4���ڵ��ڶ��Խ���5��
		if((_qualitative_limit_4>=_qualitative_limit_5)||
			(is_zero(_qualitative_limit_4-_qualitative_limit_5))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-43);
		}
	}
	//33.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * brief: ����ǰ��Χ�����������ΪĬ��ֵ��
 * param: --
 * return: --
 */
void RangeApplication::Range::reset_default_value(){
	_lower_age_limit=1;
	_upper_age_limit=50;
	_lower_age_unit_id=365;
	_upper_age_unit_id=365;
	_lower_limit_of_normal_for_males_1=-99999.0;
	_upper_limit_of_normal_for_males_1=999999.0;
	_lower_limit_of_normal_for_males_2=-99999.0;
	_upper_limit_of_normal_for_males_2=999999.0;
	_lower_limit_of_normal_for_males_3=-99999.0;
	_upper_limit_of_normal_for_males_3=999999.0;
	_lower_limit_of_normal_for_females_1=-99999.0;
	_upper_limit_of_normal_for_females_1=999999.0;
	_lower_limit_of_normal_for_females_2=-99999.0;
	_upper_limit_of_normal_for_females_2=999999.0;
	_lower_limit_of_normal_for_females_3=-99999.0;
	_upper_limit_of_normal_for_females_3=999999.0;
	_default_age=1;
	_default_sex=1;
	_lower_limit_for_repeat_range=-99999.0;
	_upper_limit_for_repeat_range=999999.0;
	_is_use_qualitative_table=0;
	_qualitative_limit_1=0.0;
	_qualitative_limit_text_1=_T("");
	_qualitative_limit_2=0.0;
	_qualitative_limit_text_2=_T("");
	_qualitative_limit_3=0.0;
	_qualitative_limit_text_3=_T("");
	_qualitative_limit_4=0.0;
	_qualitative_limit_text_4=_T("");
	_qualitative_limit_5=0.0;
	_qualitative_limit_text_5=_T("");
	_qualitative_limit_text_6=_T("");
}

/**
 * name: get_commit_string
 * breif: ��ȡ��ǰ���������ύ���ݿ�ʱ�������ַ�����
 * param: format - ��ʽ�ַ�����
 * return: �������ִ�гɹ������ص�ǰ���ύ���ݿ�����������ַ��������򷵻ؿ��ַ�����
 */
CString RangeApplication::Range::get_commit_string(const CString &format) const{
	//1.�����ǰû�����ö�����Ŀ��
	if(0==_is_use_qualitative_table){
		CString return_string(_T(""));
		return_string.Format(format,_lower_age_limit,_upper_age_limit,_lower_age_unit_id,_upper_age_unit_id,
			_lower_limit_of_normal_for_males_1,_upper_limit_of_normal_for_males_1,_lower_limit_of_normal_for_males_2,
			_upper_limit_of_normal_for_males_2,_lower_limit_of_normal_for_males_3,_upper_limit_of_normal_for_males_3,
			_lower_limit_of_normal_for_females_1,_upper_limit_of_normal_for_females_1,_lower_limit_of_normal_for_females_2,
			_upper_limit_of_normal_for_females_2,_lower_limit_of_normal_for_females_3,_upper_limit_of_normal_for_females_3,
			_default_age,_default_sex,_lower_limit_for_repeat_range,_upper_limit_for_repeat_range,_is_use_qualitative_table,
			0.0,_T(""),0.0,_T(""),0.0,_T(""),0.0,_T(""),0.0,_T(""),_T(""));
		return(return_string);
	}
	//2.�����ǰ�����˶�����Ŀ��
	else if(1==_is_use_qualitative_table){
		CString return_string(_T(""));
		return_string.Format(format,_lower_age_limit,_upper_age_limit,_lower_age_unit_id,_upper_age_unit_id,
			_lower_limit_of_normal_for_males_1,_upper_limit_of_normal_for_males_1,_lower_limit_of_normal_for_males_2,
			_upper_limit_of_normal_for_males_2,_lower_limit_of_normal_for_males_3,_upper_limit_of_normal_for_males_3,
			_lower_limit_of_normal_for_females_1,_upper_limit_of_normal_for_females_1,_lower_limit_of_normal_for_females_2,
			_upper_limit_of_normal_for_females_2,_lower_limit_of_normal_for_females_3,_upper_limit_of_normal_for_females_3,
			_default_age,_default_sex,_lower_limit_for_repeat_range,_upper_limit_for_repeat_range,_is_use_qualitative_table,
			_qualitative_limit_1,_qualitative_limit_text_1,_qualitative_limit_2,_qualitative_limit_text_2,
			_qualitative_limit_3,_qualitative_limit_text_3,_qualitative_limit_4,_qualitative_limit_text_4,
			_qualitative_limit_5,_qualitative_limit_text_5,_qualitative_limit_text_6);
		return(return_string);
	}
	//3.�����ǰ�������������
	else{
		return(_T(""));
	}
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ�ķ�Χ��Ϣ��
 * param: record_index - ��¼����ʼ������š�
 *        record - ָ���ļ�¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int RangeApplication::Range::update(long &record_index,MtADORecordset &record){
	//1.������ݲ����Ƿ�����ֱ�ӷ��ش���
	if(record_index<0){
		return(-1);
	}
	//2.������ǰ�������������
	_variant_t value;
	//3.��ָ���ļ�¼���л�ȡ�������ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	_lower_age_limit=MtADODataConverter::to_int(value);
	//4.��ָ���ļ�¼���л�ȡ�������ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	_upper_age_limit=MtADODataConverter::to_int(value);
	//5.��ָ���ļ�¼���л�ȡ�������޵�λ��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	_lower_age_unit_id=MtADODataConverter::to_int(value);
	//6.��ָ���ļ�¼���л�ȡ�������޵�λ��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	_upper_age_unit_id=MtADODataConverter::to_int(value);
	//7.��ָ���ļ�¼���л�ȡ����������Χ1�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	_lower_limit_of_normal_for_males_1=MtADODataConverter::to_double(value);
	//8.��ָ���ļ�¼���л�ȡ����������Χ1�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	_upper_limit_of_normal_for_males_1=MtADODataConverter::to_double(value);
	//9.��ָ���ļ�¼���л�ȡ����������Χ2�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	_lower_limit_of_normal_for_males_2=MtADODataConverter::to_double(value);
	//10.��ָ���ļ�¼���л�ȡ����������Χ2�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	_upper_limit_of_normal_for_males_2=MtADODataConverter::to_double(value);
	//11.��ָ���ļ�¼���л�ȡ����������Χ3�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	_lower_limit_of_normal_for_males_3=MtADODataConverter::to_double(value);
	//12.��ָ���ļ�¼���л�ȡ����������Χ3�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	_upper_limit_of_normal_for_males_3=MtADODataConverter::to_double(value);
	//13.��ָ���ļ�¼���л�ȡŮ��������Χ1�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	_lower_limit_of_normal_for_females_1=MtADODataConverter::to_double(value);
	//14.��ָ���ļ�¼���л�ȡŮ��������Χ1�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	_upper_limit_of_normal_for_females_1=MtADODataConverter::to_double(value);
	//15.��ָ���ļ�¼���л�ȡŮ��������Χ2�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	_lower_limit_of_normal_for_females_2=MtADODataConverter::to_double(value);
	//16.��ָ���ļ�¼���л�ȡŮ��������Χ2�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	_upper_limit_of_normal_for_females_2=MtADODataConverter::to_double(value);
	//17.��ָ���ļ�¼���л�ȡŮ��������Χ3�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	_lower_limit_of_normal_for_females_3=MtADODataConverter::to_double(value);
	//18.��ָ���ļ�¼���л�ȡŮ��������Χ3�����ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	_upper_limit_of_normal_for_females_3=MtADODataConverter::to_double(value);
	//19.��ָ���ļ�¼���л�ȡĬ�����䡣
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	_default_age=MtADODataConverter::to_int(value);
	//20.��ָ���ļ�¼���л�ȡĬ���Ա�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	_default_sex=MtADODataConverter::to_int(value);
	//21.��ָ���ļ�¼���л�ȡ��׼���鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	_lower_limit_for_repeat_range=MtADODataConverter::to_double(value);
	//22.��ָ���ļ�¼���л�ȡ��׼���鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	_upper_limit_for_repeat_range=MtADODataConverter::to_double(value);
	//23.��ָ���ļ�¼���л�ȡ�Ƿ����ö��Ա�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	_is_use_qualitative_table=MtADODataConverter::to_int(value);
	//24.�����ǰ�����˶��Ա�
	if(1==_is_use_qualitative_table){
		//24-1.��ָ���ļ�¼���л�ȡ���Խ���1�Ľ���ֵ��
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-23);
		}
		_qualitative_limit_1=MtADODataConverter::to_double(value);
		//24-2.��ָ���ļ�¼���л�ȡ���Խ���1���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-24);
		}
		_qualitative_limit_text_1=MtADODataConverter::to_string(value);
		//24-3.��ָ���ļ�¼���л�ȡ���Խ���2�Ľ���ֵ��
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-25);
		}
		_qualitative_limit_2=MtADODataConverter::to_double(value);
		//24-4.��ָ���ļ�¼���л�ȡ���Խ���2���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-26);
		}
		_qualitative_limit_text_2=MtADODataConverter::to_string(value);
		//24-5.��ָ���ļ�¼���л�ȡ���Խ���3�Ľ���ֵ��
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-27);
		}
		_qualitative_limit_3=MtADODataConverter::to_double(value);
		//24-6.��ָ���ļ�¼���л�ȡ���Խ���3���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-28);
		}
		_qualitative_limit_text_3=MtADODataConverter::to_string(value);
		//24-7.��ָ���ļ�¼���л�ȡ���Խ���4�Ľ���ֵ��
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-29);
		}
		_qualitative_limit_4=MtADODataConverter::to_double(value);
		//24-8.��ָ���ļ�¼���л�ȡ���Խ���4���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-30);
		}
		_qualitative_limit_text_4=MtADODataConverter::to_string(value);
		//24-9.��ָ���ļ�¼���л�ȡ���Խ���5�Ľ���ֵ��
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-31);
		}
		_qualitative_limit_5=MtADODataConverter::to_double(value);
		//24-10.��ָ���ļ�¼���л�ȡ���Խ���5���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-32);
		}
		_qualitative_limit_text_5=MtADODataConverter::to_string(value);
		//24-11.��ָ���ļ�¼���л�ȡ���Խ���6���ַ�������
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-33);
		}
		_qualitative_limit_text_6=MtADODataConverter::to_string(value);
	}
	//25.�����ǰ��δ���þ�̬��
	else if(0==_is_use_qualitative_table){
		_qualitative_limit_1=0.0;record_index++;
		_qualitative_limit_text_1=_T("");record_index++;
		_qualitative_limit_2=0.0;record_index++;
		_qualitative_limit_text_2=_T("");record_index++;
		_qualitative_limit_3=0.0;record_index++;
		_qualitative_limit_text_3=_T("");record_index++;
		_qualitative_limit_4=0.0;record_index++;
		_qualitative_limit_text_4=_T("");record_index++;
		_qualitative_limit_5=0.0;record_index++;
		_qualitative_limit_text_5=_T("");record_index++;
		_qualitative_limit_text_6=_T("");record_index++;
	}
	//26.�����ǰ�����쳣�����
	else{
		return(-34);
	}
	//27.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: RangeApplication
 * brief: ���캯����
 * param: --
 * return: --
 */
RangeApplication::RangeApplication(void)
	:_report_name(_T(""))
	,_control_interval(0)
	,_unit_id(0)
	,_instrument_factor_a(0.0)
	,_instrument_factor_b(0.0)
	,_data_mode_id(0)
	,_ranges(new Range[MAX_RANGES])
	,_lower_limit_for_technical_range_for_class_1(0.0)
	,_upper_limit_for_technical_range_for_class_1(0.0)
	,_lower_limit_for_technical_range_for_class_2(0.0)
	,_upper_limit_for_technical_range_for_class_2(0.0){
}

/**
 * name: RangeApplication
 * brief: �������캯����
 * param: source - ����Դ��
 * return: --
 */
RangeApplication::RangeApplication(const RangeApplication &source)
	:_report_name(source._report_name)
	,_control_interval(source._control_interval)
	,_unit_id(source._unit_id)
	,_instrument_factor_a(source._instrument_factor_a)
	,_instrument_factor_b(source._instrument_factor_b)
	,_data_mode_id(source._data_mode_id)
	,_ranges(new Range[MAX_RANGES])
	,_lower_limit_for_technical_range_for_class_1(source._lower_limit_for_technical_range_for_class_1)
	,_upper_limit_for_technical_range_for_class_1(source._upper_limit_for_technical_range_for_class_1)
	,_lower_limit_for_technical_range_for_class_2(source._lower_limit_for_technical_range_for_class_2)
	,_upper_limit_for_technical_range_for_class_2(source._upper_limit_for_technical_range_for_class_2){
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		_ranges[index]=source._ranges[index];
	}
}

/**
 * name: ~RangeApplication
 * brief: ����������
 * param: --
 * return: --
 */
RangeApplication::~RangeApplication(void){
	delete[] _ranges;
}

/**
 * name: set_report_name
 * brief: ���ñ������ơ�
 * param: report_name - �������ơ�
 * return: --
 */
void RangeApplication::set_report_name(const CString &report_name){
	_report_name=report_name;
}

/**
 * name: get_report_name
 * brief: ��ȡ�������ơ�
 * param: --
 * return: ���ر������ơ�
 */
const CString &RangeApplication::get_report_name() const{
	return(_report_name);
}

/**
 * name: set_control_interval
 * brief: �����ʿؼ����
 * param: control_interval - �ʿؼ����
 * return: --
 */
void RangeApplication::set_control_interval(const int control_interval){
	_control_interval=control_interval;
}

/**
 * name: get_control_interval
 * brief: ��ȡ�ʿؼ����
 * param: --
 * return: �����ʿؼ����
 */
int RangeApplication::get_control_interval() const{
	return(_control_interval);
}

/**
 * name: set_unit_id
 * breif: ���õ�λ��ʶ��
 * param: unit_id - ��λ��ʶ��
 * return: --
 */
void RangeApplication::set_unit_id(const int unit_id){
	_unit_id=unit_id;
}

/**
 * name: get_unit_id
 * breif: ��ȡ��λ��ʶ��
 * param: --
 * return: ���ص�λ��ʶ��
 */
int RangeApplication::get_unit_id() const{
	return(_unit_id);
}

/**
 * name: set_instrument_factor_a
 * breif: �����豸ϵ��a��
 * param: instrument_factor_a - �豸ϵͳa��
 * return: --
 */
void RangeApplication::set_instrument_factor_a(const double instrument_factor_a){
	_instrument_factor_a=instrument_factor_a;
}

/**
 * name: get_instrument_factor_a
 * breif: ��ȡ�豸ϵ��a��
 * param: --
 * return: �����豸ϵ��a��
 */
double RangeApplication::get_instrument_factor_a() const{
	return(_instrument_factor_a);
}

/**
 * name: set_instrument_factor_b
 * breif: �����豸ϵ��b��
 * param: instrument_factor_b - �豸ϵͳb��
 * return: --
 */
void RangeApplication::set_instrument_factor_b(const double instrument_factor_b){
	_instrument_factor_b=instrument_factor_b;
}

/**
 * name: get_instrument_factor_b
 * breif: ��ȡ�豸ϵ��b��
 * param: --
 * return: �����豸ϵ��b��
 */
double RangeApplication::get_instrument_factor_b() const{
	return(_instrument_factor_b);
}

/**
 * name: set_data_mode_id
 * brief: ��������ģʽ��ʶ��
 * param: data_mode_id - ����ģʽ��ʶ��
 * return: --
 */
void RangeApplication::set_data_mode_id(const int data_mode_id){
	_data_mode_id=data_mode_id;
}

/**
 * name: get_data_mode_id
 * breif: ��ȡ����ģʽ��ʶ��
 * param: --
 * return: ��������ģʽ��ʶ��
 */
int RangeApplication::get_data_mode_id() const{
	return(_data_mode_id);
}

/**
 * name: set_lower_age_limit
 * breif: �����������ޡ�
 * param: index - ������š�
 *	      lower_age_limit - �������ޡ�
 * return: --
 */
void RangeApplication::set_lower_age_limit(
	const int index,const int lower_age_limit){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_age_limit(lower_age_limit);
}

/**
 * name: get_lower_age_limit
 * breif: ��ȡ�������ޡ�
 * param: index - ������š�
 * return: �����������ޡ�
 */
int RangeApplication::get_lower_age_limit(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_age_limit());
}

/**
 * name: set_upper_age_limit
 * breif: �����������ޡ�
 * param: index - ������š�
 *        upper_age_limit - �������ޡ�
 * return: --
 */
void RangeApplication::set_upper_age_limit(
	const int index,const int upper_age_limit){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_age_limit(upper_age_limit);
}

/**
 * name: get_upper_age_limit
 * breif: ��ȡ�������ޡ�
 * param: index - ������š�
 * return: �����������ޡ�
 */
int RangeApplication::get_upper_age_limit(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_age_limit());
}

/**
 * name: set_lower_age_unit_id
 * breif: �����������޵ĵ�λ��ʶ��
 * param: index - ������š�
 *        lower_age_unit_id - �������޵ĵ�λ��ʶ��
 * return: --
 */
void RangeApplication::set_lower_age_unit_id(
	const int index,const int lower_age_unit_id){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_age_unit_id(lower_age_unit_id);
}

/**
 * name: get_lower_age_unit_id
 * breif: ��ȡ�������޵ĵ�λ��ʶ��
 * param: index - ������š�
 * return: �����������޵ĵ�λ��ʶ��
 */
int RangeApplication::get_lower_age_unit_id(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_age_unit_id());
}

/**
 * name: set_upper_age_unit_id
 * breif: �����������޵ĵ�λ��ʶ��
 * param: index - ������š�
 *        upper_age_unit_id - �������޵ĵ�λ��ʶ��
 * return: --
 */
void RangeApplication::set_upper_age_unit_id(
	const int index,const int upper_age_unit_id){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_age_unit_id(upper_age_unit_id);
}

/**
 * name: get_upper_age_unit_id
 * breif: ��ȡ�������޵ĵ�λ��ʶ��
 * param: index - ������š�
 * return: �����������޵ĵ�λ��ʶ��
 */
int RangeApplication::get_upper_age_unit_id(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_age_unit_id());
}

/**
 * name: set_lower_limit_of_normal_for_males_1
 * breif: ��������������Χ�ķ�Χ1������ֵ��
 * param: index - ������š� 
 *        lower_limit_of_normal_for_males_1 - ����������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_males_1(
	const int index,const double lower_limit_of_normal_for_males_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_males_1(
		lower_limit_of_normal_for_males_1);
}

/**
 * name: get_lower_limit_of_normal_for_males_1
 * breif: ��ȡ����������Χ�ķ�Χ1������ֵ��
 * param: index - ������š� 
 * return: ��������������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::get_lower_limit_of_normal_for_males_1(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_1());
}

/**
 * name: set_upper_limit_of_normal_for_males_1
 * breif: ��������������Χ�ķ�Χ1������ֵ��
 * param: index - ������š�
 *        upper_limit_of_normal_for_males_1 - ����������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::set_upper_limit_of_normal_for_males_1(
	const int index,const double upper_limit_of_normal_for_males_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_males_1(
		upper_limit_of_normal_for_males_1);
}

/**
 * name: get_upper_limit_of_normal_for_males_1
 * breif: ��ȡ����������Χ�ķ�Χ1������ֵ��
 * param: index - ������š�
 * return: ��������������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_males_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_1());
}

/**
 * name: set_lower_limit_of_normal_for_males_2
 * breif: ��������������Χ�ķ�Χ2������ֵ��
 * param: index - ������� 
 *        lower_limit_of_normal_for_males_2 - ����������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_males_2(
	const int index,const double lower_limit_of_normal_for_males_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_males_2(
		lower_limit_of_normal_for_males_2);
}

/**
 * name: get_lower_limit_of_normal_for_males_2
 * breif: ��ȡ����������Χ�ķ�Χ2������ֵ��
 * param: index - ������š�
 * return: ��������������Χ�ķ�Χ2������ֵ��
 */
double RangeApplication::get_lower_limit_of_normal_for_males_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_2());
}

/**
 * name: set_upper_limit_of_normal_for_males_2
 * breif: ��������������Χ�ķ�Χ2������ֵ��
 * param: index - ������š� 
 *        upper_limit_of_normal_for_males_2 - ����������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::set_upper_limit_of_normal_for_males_2(
	const int index,const double upper_limit_of_normal_for_males_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_males_2(
		upper_limit_of_normal_for_males_2);
}

/**
 * name: get_upper_limit_of_normal_for_males_2
 * breif: ��ȡ����������Χ�ķ�Χ2������ֵ��
 * param: index - ������š� 
 * return: ��������������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_males_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_2());
}

/**
 * name: set_lower_limit_of_normal_for_males_3
 * breif: ��������������Χ�ķ�Χ3������ֵ��
 * param: index - ������š� 
 *        lower_limit_of_normal_for_males_3 - ����������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_males_3(
	const int index,const double lower_limit_of_normal_for_males_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_males_3(
		lower_limit_of_normal_for_males_3);
}

/**
 * name: get_lower_limit_of_normal_for_males_3
 * breif: ��ȡ����������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 * return: ��������������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::get_lower_limit_of_normal_for_males_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_3());
}

/**
 * name: set_upper_limit_of_normal_for_males_3
 * breif: ��������������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 *        upper_limit_of_normal_for_males_3 - ����������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::set_upper_limit_of_normal_for_males_3(
	const int index,const double upper_limit_of_normal_for_males_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_males_3(
		upper_limit_of_normal_for_males_3);
}

/**
 * name: get_upper_limit_of_normal_for_males_3
 * breif: ��ȡ����������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 * return: ��������������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_males_3(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_3());
}

/**
 * name: set_lower_limit_of_normal_for_females_1
 * breif: ����Ů��������Χ�ķ�Χ1������ֵ��
 * param: index - ������š�
 *        lower_limit_of_normal_for_females_1 - Ů��������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_females_1(
	const int index,const double lower_limit_of_normal_for_females_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_females_1(
		lower_limit_of_normal_for_females_1);
}

/**
 * name: get_lower_limit_of_normal_for_females_1
 * breif: ��ȡŮ��������Χ�ķ�Χ1������ֵ��
 * param: index - ������š�
 * return: ����Ů��������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::get_lower_limit_of_normal_for_females_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_1());
}

/**
 * name: set_upper_limit_of_normal_for_females_1
 * breif: ����Ů��������Χ�ķ�Χ1������ֵ��
 * param: index - ������š� 
 *		  upper_limit_of_normal_for_females_1 - Ů��������Χ�ķ�Χ1������ֵ��
 * return: --
 */
void RangeApplication::set_upper_limit_of_normal_for_females_1(
	const int index,const double upper_limit_of_normal_for_females_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_females_1(
		upper_limit_of_normal_for_females_1);
}

/**
 * name: get_upper_limit_of_normal_for_females_1
 * breif: ��ȡŮ��������Χ�ķ�Χ1������ֵ��
 * param: index - ������š� 
 * return: ����Ů��������Χ�ķ�Χ1������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_females_1(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_1());
}

/**
 * name: set_lower_limit_of_normal_for_females_2
 * breif: ����Ů��������Χ�ķ�Χ2������ֵ��
 * param: index - ������š�
 *        lower_limit_of_normal_for_females_2 - Ů��������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_females_2(
	const int index,const double lower_limit_of_normal_for_females_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_females_2(
		lower_limit_of_normal_for_females_2);
}

/**
 * name: get_lower_limit_of_normal_for_females_2
 * breif: ��ȡŮ��������Χ�ķ�Χ2������ֵ��
 * param: index - ������š�
 * return: ����Ů��������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::get_lower_limit_of_normal_for_females_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_2());
}

/**
 * name: set_upper_limit_of_normal_for_females_2
 * breif: ����Ů��������Χ�ķ�Χ2������ֵ��
 * param: index - ������š�
 *		  upper_limit_of_normal_for_females_2 - Ů��������Χ�ķ�Χ2������ֵ��
 * return: --
 */
void RangeApplication::set_upper_limit_of_normal_for_females_2(
	const int index,const double upper_limit_of_normal_for_females_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_females_2(
		upper_limit_of_normal_for_females_2);
}

/**
 * name: get_upper_limit_of_normal_for_females_2
 * breif: ��ȡŮ��������Χ�ķ�Χ2������ֵ��
 * param: index - ������š�
 * return: ����Ů��������Χ�ķ�Χ2������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_females_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_2());
}

/**
 * name: set_lower_limit_of_normal_for_females_3
 * breif: ����Ů��������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 *        lower_limit_of_normal_for_females_3 - Ů��������Χ�ķ�Χ3������ֵ��
 * return: --
 */
void RangeApplication::set_lower_limit_of_normal_for_females_3(
	const int index,const double lower_limit_of_normal_for_females_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_of_normal_for_females_3(
		lower_limit_of_normal_for_females_3);
}

/**
 * name: get_lower_limit_of_normal_for_females_3
 * breif: ��ȡŮ��������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 * return: ����Ů��������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::get_lower_limit_of_normal_for_females_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_3());
}

/**
 * name: set_upper_limit_of_normal_for_females_3
 * breif: ����Ů��������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 *        upper_limit_of_normal_for_females_3 - Ů��������Χ�ķ�Χ3������ֵ��
 * return: --s
 */
void RangeApplication::set_upper_limit_of_normal_for_females_3(
	const int index,const double upper_limit_of_normal_for_females_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_of_normal_for_females_3(
		upper_limit_of_normal_for_females_3);
}

/**
 * name: get_upper_limit_of_normal_for_females_3
 * breif: ��ȡŮ��������Χ�ķ�Χ3������ֵ��
 * param: index - ������š�
 * return: ����Ů��������Χ�ķ�Χ3������ֵ
 */
double RangeApplication::get_upper_limit_of_normal_for_females_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_3());
}

/**
 * name: set_default_age
 * brief: ����Ĭ�����䡣
 * param: index - ������š�
 *		  default_age - Ĭ�����䡣
 * return: --
 */
void RangeApplication::set_default_age(
	const int index,const int default_age){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_default_age(default_age);
}

/**
 * name: get_default_age
 * breif: ��ȡĬ�����䡣
 * param: index - ������š�
 * return: ����Ĭ�����䡣
 */
int RangeApplication::get_default_age(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_default_age());
}

/**
 * name: set_default_sex
 * brief: ����Ĭ���Ա�
 * param: index - ������š� 
 *		  default_sex - Ĭ���Ա�
 * return: --
 */
void RangeApplication::set_default_sex(
	const int index,const int default_sex){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_default_sex(default_sex);
}

/**
 * name: get_default_sex
 * breif: ��ȡĬ���Ա�
 * param: index - ������š�
 * return: ����Ĭ���Ա�
 */
int RangeApplication::get_default_sex(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_default_sex());
}

/**
 * name: set_lower_limit_for_repeat_range
 * breif: ���ñ�׼���鷶Χ�����ޡ�
 * param: index - ������š�
 *	      lower_limit_for_repeat_range - ��׼���鷶Χ�����ޡ�
 * return: --
 */
void RangeApplication::set_lower_limit_for_repeat_range(
	const int index,const double lower_limit_for_repeat_range){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_limit_for_repeat_range(
		lower_limit_for_repeat_range);
}

/**
 * name: get_lower_limit_for_repeat_range
 * breif: ��ȡ��׼���鷶Χ�����ޡ�
 * param: index - ������š�
 * return: ���ر�׼���鷶Χ�����ޡ�
 */
double RangeApplication::get_lower_limit_for_repeat_range(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_for_repeat_range());
}

/**
 * name: set_upper_limit_for_repeat_range
 * breif: ���ñ�׼���鷶Χ�����ޡ�
 * param: index - ������š�
 *		  upper_limit_for_repeat_range - ��׼���鷶Χ�����ޡ�
 * return: --
 */
void RangeApplication::set_upper_limit_for_repeat_range(
	const int index,const double upper_limit_for_repeat_range){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_limit_for_repeat_range(
		upper_limit_for_repeat_range);
}

/**
 * name: get_upper_limit_for_repeat_range
 * breif: ��ȡ��׼���鷶Χ�����ޡ�
 * param: index - ������š�
 * return: ���ر�׼���鷶Χ�����ޡ�
 */
double RangeApplication::get_upper_limit_for_repeat_range(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_for_repeat_range());
}

/**
 * name: set_is_use_qualitative_table
 * breif: �����Ƿ�ʹ�ö��Ա�
 * param: index - ������š�
 *        is_use_qualitative_table - �Ƿ�ʹ�ö��Ա�0 ��ʹ�ã�1 ʹ�ã���
 * return: --
 */
void RangeApplication::set_is_use_qualitative_table(
	const int index,const int is_use_qualitative_table){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_is_use_qualitative_table(
		is_use_qualitative_table);
}

/**
 * name: get_is_use_qualitative_table
 * breif: ��ȡ�Ƿ�ʹ�ö��Ա�
 * param: index - ������š�
 * return: �����Ƿ�ʹ�ö��Ա�
 */
int RangeApplication::get_is_use_qualitative_table(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_is_use_qualitative_table());
}

/**
 * name: set_qualitative_limit_1
 * breif: ���ö��Խ���1��
 * param: index - ������š�
 *		  qualitative_limit_1 - ���Խ���1��
 * return: --
 */
void RangeApplication::set_qualitative_limit_1(
	const int index,const double qualitative_limit_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_1(qualitative_limit_1);
}

/**
 * name: get_qualitative_limit_1
 * breif: ��ȡ���Խ���1��
 * param: index - ������š�
 * return: ���ض��Խ���1��
 */
double RangeApplication::get_qualitative_limit_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_1());
}

/**
 * name: set_qualitative_limit_text_1
 * brief: ���ö��Խ��������ַ���1��
 * param: index - ������š�
 *		  qualitative_limit_text_1 - ���Խ��������ַ���1��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_1(
	const int index,const CString &qualitative_limit_text_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_1(
		qualitative_limit_text_1);
}

/**
 * name: get_qualitative_limit_text_1
 * brief: ��ȡ���Խ��������ַ���1��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���1��
 */
const CString &RangeApplication::get_qualitative_limit_text_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_1());
}

/**
 * name: set_qualitative_limit_2
 * breif: ���ö��Խ���2��
 * param: index - ������š�
 *	      qualitative_limit_2 - ���Խ���2��
 * return: --
 */
void RangeApplication::set_qualitative_limit_2(
	const int index,const double qualitative_limit_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_2(qualitative_limit_2);
}

/**
 * name: get_qualitative_limit_2
 * breif: ��ȡ���Խ���2��
 * param: index - ������š�
 * return: ���ض��Խ���2��
 */
double RangeApplication::get_qualitative_limit_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_2());
}

/**
 * name: set_qualitative_limit_text_2
 * brief: ���ö��Խ��������ַ���2��
 * param: index - ������š�
 *		  qualitative_limit_text_2 - ���Խ��������ַ���2��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_2(
	const int index,const CString &qualitative_limit_text_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_2(
		qualitative_limit_text_2);
}

/**
 * name: get_qualitative_limit_text_2
 * brief: ��ȡ���Խ��������ַ���2��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���2��
 */
const CString &RangeApplication::get_qualitative_limit_text_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_2());
}

/**
 * name: set_qualitative_limit_3
 * breif: ���ö��Խ���3��
 * param: index - ������š�
 *		  qualitative_limit_3 - ���Խ���3��
 * return: --
 */
void RangeApplication::set_qualitative_limit_3(
	const int index,const double qualitative_limit_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_3(
		qualitative_limit_3);
}

/**
 * name: get_qualitative_limit_3
 * breif: ��ȡ���Խ���3��
 * param: index - ������š�
 * return: ���ض��Խ���3��
 */
double RangeApplication::get_qualitative_limit_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_3());
}

/**
 * name: set_qualitative_limit_text_3
 * brief: ���ö��Խ��������ַ���3��
 * param: index - ������š�
 *		  qualitative_limit_text_3 - ���Խ��������ַ���3��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_3(
	const int index,const CString &qualitative_limit_text_3){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_3(
		qualitative_limit_text_3);
}

/**
 * name: get_qualitative_limit_text_3
 * brief: ��ȡ���Խ��������ַ���3��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���3��
 */
const CString &RangeApplication::get_qualitative_limit_text_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_3());
}

/**
 * name: set_qualitative_limit_4
 * breif: ���ö��Խ���4��
 * param: index - ������š�
 *		  qualitative_limit_4 - ���Խ���4��
 * return: --
 */
void RangeApplication::set_qualitative_limit_4(
	const int index,const double qualitative_limit_4){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_4(
		qualitative_limit_4);
}

/**
 * name: get_qualitative_limit_4
 * breif: ��ȡ���Խ���4��
 * param: index - ������š�
 * return: ���ض��Խ���4��
 */
double RangeApplication::get_qualitative_limit_4(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_4());
}

/**
 * name: set_qualitative_limit_text_4
 * brief: ���ö��Խ��������ַ���4��
 * param: index - ������š�
 *        qualitative_limit_text_4 - ���Խ��������ַ���4��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_4(
	const int index,const CString &qualitative_limit_text_4){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_4(
		qualitative_limit_text_4);
}

/**
 * name: get_qualitative_limit_text_4
 * brief: ��ȡ���Խ��������ַ���4��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���4��
 */
const CString &RangeApplication::get_qualitative_limit_text_4(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_4());
}

/**
 * name: set_qualitative_limit_5
 * breif: ���ö��Խ���5��
 * param: index - ������š�
 *		  qualitative_limit_5 - ���Խ���5��
 * return: --
 */
void RangeApplication::set_qualitative_limit_5(
	const int index,const double qualitative_limit_5){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_5(
		qualitative_limit_5);
}

/**
 * name: get_qualitative_limit_5
 * breif: ��ȡ���Խ���5��
 * param: index - ������š�
 * return: ���ض��Խ���5��
 */
double RangeApplication::get_qualitative_limit_5(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_5());
}

/**
 * name: set_qualitative_limit_text_5
 * brief: ���ö��Խ��������ַ���5��
 * param: index - ������š�
 *        qualitative_limit_text_5 - ���Խ��������ַ���5��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_5(
	const int index,const CString &qualitative_limit_text_5){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_5(
		qualitative_limit_text_5);
}

/**
 * name: get_qualitative_limit_text_5
 * brief: ��ȡ���Խ��������ַ���5��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���5��
 */
const CString &RangeApplication::get_qualitative_limit_text_5(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_5());
}

/**
 * name: set_qualitative_limit_text_6
 * brief: ���ö��Խ��������ַ���6��
 * param: index - ������š�
 *		  qualitative_limit_text_6 - ���Խ��������ַ���6��
 * return: --
 */
void RangeApplication::set_qualitative_limit_text_6(
	const int index,const CString &qualitative_limit_text_6){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_text_6(
		qualitative_limit_text_6);
}

/**
 * name: get_qualitative_limit_text_6
 * brief: ��ȡ���Խ��������ַ���6��
 * param: index - ������š�
 * return: ���ض��Խ��������ַ���6��
 */
const CString &RangeApplication::get_qualitative_limit_text_6(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_6());
}

/**
 * name: set_lower_limit_for_technical_range_for_class_1
 * breif: ������������Ϊ����1�ĸ��鷶Χ���ޡ�
 * param: lower_limit_for_technical_range_for_class_1 - ��������Ϊ����1�ĸ��鷶Χ���ޡ�
 * return: --
 */
void RangeApplication::set_lower_limit_for_technical_range_for_class_1(
	const double lower_limit_for_technical_range_for_class_1){
	_lower_limit_for_technical_range_for_class_1=
		lower_limit_for_technical_range_for_class_1;
}

/**
 * name: get_lower_limit_for_technical_range_for_class_1
 * breif: ��ȡ��������Ϊ����1�ĸ��鷶Χ���ޡ�
 * param: --
 * return: ������������Ϊ����1�ĸ��鷶Χ���ޡ�
 */
double RangeApplication::get_lower_limit_for_technical_range_for_class_1() const{
	return(_lower_limit_for_technical_range_for_class_1);
}

/**
 * name: set_upper_limit_for_technical_range_for_class_1
 * breif: ������������Ϊ����1�ĸ��鷶Χ���ޡ�
 * param: upper_limit_for_technical_range_for_class_1 - ��������Ϊ����1�ĸ��鷶Χ���ޡ�
 * return: --
 */
void RangeApplication::set_upper_limit_for_technical_range_for_class_1(
	const double upper_limit_for_technical_range_for_class_1){
	_upper_limit_for_technical_range_for_class_1=
		upper_limit_for_technical_range_for_class_1;
}

/**
 * name: get_upper_limit_for_technical_range_for_class_1
 * breif: ��ȡ��������Ϊ����1�ĸ��鷶Χ���ޡ�
 * param: --
 * return: ������������Ϊ����1�ĸ��鷶Χ���ޡ�
 */
double RangeApplication::get_upper_limit_for_technical_range_for_class_1() const{
	return(_upper_limit_for_technical_range_for_class_1);
}

/**
 * name: set_lower_limit_for_technical_range_for_class_2
 * breif: ������������Ϊ����2�ĸ��鷶Χ���ޡ�
 * param: lower_limit_for_technical_range_for_class_2 - ��������Ϊ����2�ĸ��鷶Χ���ޡ�
 * return: --
 */
void RangeApplication::set_lower_limit_for_technical_range_for_class_2(
	const double lower_limit_for_technical_range_for_class_2){
	_lower_limit_for_technical_range_for_class_2=
		lower_limit_for_technical_range_for_class_2;
}

/**
 * name: get_lower_limit_for_technical_range_for_class_2
 * breif: ��ȡ��������Ϊ����2�ĸ��鷶Χ���ޡ�
 * param: --
 * return: ������������Ϊ����2�ĸ��鷶Χ���ޡ�
 */
double RangeApplication::get_lower_limit_for_technical_range_for_class_2() const{
	return(_lower_limit_for_technical_range_for_class_2);
}

/**
 * name: set_upper_limit_for_technical_range_for_class_2
 * breif: ������������Ϊ����2�ĸ��鷶Χ���ޡ�
 * param: upper_limit_for_technical_range_for_class_2 - ��������Ϊ����2�ĸ��鷶Χ���ޡ�
 * return: --
 */
void RangeApplication::set_upper_limit_for_technical_range_for_class_2(
	const double upper_limit_for_technical_range_for_class_2){
	_upper_limit_for_technical_range_for_class_2=
		upper_limit_for_technical_range_for_class_2;
}

/**
 * name: get_upper_limit_for_technical_range_for_class_2
 * breif: ��ȡ��������Ϊ����2�ĸ��鷶Χ���ޡ�
 * param: --
 * return: ������������Ϊ����2�ĸ��鷶Χ���ޡ�
 */
double RangeApplication::get_upper_limit_for_technical_range_for_class_2() const{
	return(_upper_limit_for_technical_range_for_class_2);
}

/**
 * name: operator=
 * breif: ����==��������
 * param: source - ����Դ��
 * return: �����������á�
 */
RangeApplication &RangeApplication::operator=(const RangeApplication &source){
	_report_name=source._report_name;
	_control_interval=source._control_interval;
	_unit_id=source._unit_id;
	_instrument_factor_a=source._instrument_factor_a;
	_instrument_factor_b=source._instrument_factor_b;
	_data_mode_id=source._data_mode_id;
	_lower_limit_for_technical_range_for_class_1=source._lower_limit_for_technical_range_for_class_1;
	_upper_limit_for_technical_range_for_class_1=source._upper_limit_for_technical_range_for_class_1;
	_lower_limit_for_technical_range_for_class_2=source._lower_limit_for_technical_range_for_class_2;
	_upper_limit_for_technical_range_for_class_2=source._upper_limit_for_technical_range_for_class_2;
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		_ranges[index]=source._ranges[index];
	}
	return(*this);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ������������Ƿ�Ϸ���
 * param: error_message - ָ�򷵻صĴ�����Ϣ��ָ�루���Ϊ��ʱ�������ش�����Ϣ����
 * return: �����ǰ������������Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int RangeApplication::is_valid(CString *error_message/*=0*/) const{
	//1.������ǰ�������������
	Theme *theme=Theme::instance();
	//2.��⵱ǰ���������Ƿ�Ϸ���
	//3.��⵱ǰ�ʿؼ���Ƿ�Ϸ���
	if((-1!=_control_interval)&&((_control_interval<10)||(
		_control_interval>1000))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING363),10,1000);
		}
		return(-1);
	}
	//4.��⵱ǰ��λ��ʶ�Ƿ�Ϸ���
	if(_unit_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING364));
		}
		return(-2);
	}
	//5.��⵱ǰ�豸ϵ��a�Ƿ�Ϸ���
	if((_instrument_factor_a<(-99999.0))||(_instrument_factor_a>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING365),-99999.0,999999.0);
		}
		return(-3);
	}
	//6.��⵱ǰ�豸ϵ��b�Ƿ�Ϸ���
	if((_instrument_factor_b<(-99999.0))||(_instrument_factor_b>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING366),-99999.0,999999.0);
		}
		return(-4);
	}
	//7.��⵱ǰ����ģʽ�Ƿ�Ϸ���
	if(_data_mode_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING367));
		}
		return(-5);
	}
	//8.��⵱ǰ�����������͵ķ�Χ�����Ƿ�Ϸ���
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		//8-1.��⵱ǰ�����������͵ķ�Χ������
		const int result=_ranges[index].is_valid(error_message);
		//8-2.�����ǰ�����������͵ķ�Χ�����Ƿ���
		if(result<0){
			return(result);
		}
	}
	//9.��⵱ǰ��������Ϊ����1�����������鷶Χ�����Ƿ�Ϸ���
	if((_lower_limit_for_technical_range_for_class_1<-99999.0)||
		(_lower_limit_for_technical_range_for_class_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING387),
				-99999.0,999999.0);
		}
		return(-44);
	}
	//10.��⵱ǰ��������Ϊ����1�����������鷶Χ�����Ƿ�Ϸ���
	if((_upper_limit_for_technical_range_for_class_1<-99999.0)||
		(_upper_limit_for_technical_range_for_class_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING388),
				-99999.0,999999.0);
		}
		return(-45);
	}
	//11.��⵱ǰ��������Ϊ����2�����������鷶Χ�����Ƿ�Ϸ���
	if((_lower_limit_for_technical_range_for_class_2<-99999.0)||
		(_lower_limit_for_technical_range_for_class_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING389),
				-99999.0,999999.0);
		}
		return(-46);
	}
	//12.��⵱ǰ��������Ϊ����2�����������鷶Χ�����Ƿ�Ϸ���
	if((_upper_limit_for_technical_range_for_class_2<-99999.0)||
		(_upper_limit_for_technical_range_for_class_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING390),
				-99999.0,999999.0);
		}
		return(-47);
	}
	//13.�����������Ϊ����1�����������鷶Χ�����Ƿ���ڵ�����������Ϊ����1�����������鷶Χ���ޡ�
	if((_lower_limit_for_technical_range_for_class_1>=
		_upper_limit_for_technical_range_for_class_1)||
		(is_zero(_lower_limit_for_technical_range_for_class_1-
		_upper_limit_for_technical_range_for_class_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING391));
		}
		return(-48);
	}
	//14.�����������Ϊ����2�����������鷶Χ�����Ƿ���ڵ�����������Ϊ����2�����������鷶Χ���ޡ�
	if((_lower_limit_for_technical_range_for_class_2>=
		_upper_limit_for_technical_range_for_class_2)||
		(is_zero(_lower_limit_for_technical_range_for_class_2-
		_upper_limit_for_technical_range_for_class_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING392));
		}
		return(-49);
	}
	//15.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: reset_default_value
 * brief: ����ǰ��Χ�����������ΪĬ��ֵ��
 * param: --
 * return: --
 */
void RangeApplication::reset_default_value(){
	_report_name=_T("");
	_control_interval=-1;
	_unit_id=0;
	_instrument_factor_a=1.0;
	_instrument_factor_b=0.0;
	_data_mode_id=1;
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		_ranges[index].reset_default_value();
	}
	_lower_limit_for_technical_range_for_class_1=-99999.0;
	_upper_limit_for_technical_range_for_class_1=999999.0;
	_lower_limit_for_technical_range_for_class_2=-99999.0;
	_upper_limit_for_technical_range_for_class_2=999999.0;
}

/**
 * name: commit
 * brief: ����ǰ����Ŀ��Ϣ�ύ�����ݿ��С�
 * param: item_id - ��Ӧ����Ŀ��ʶ��
 *        method - �ύ�����ݿ�ķ�����1 ���� 2 ���£���
 *        database - ׼���ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int RangeApplication::commit(const int item_id,const int method,Database &database) const{
	//1.�жϵ�ǰ���ݵ���Ŀ��ʶ�Ƿ�Ϸ���
	if((item_id<1)||(item_id>999)){
		return(-1);
	}
	//2.�����ݿ��ύǰ��Ҫ��⵱ǰ��Χ��Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-2);
	}
	//3.�����ǰ�����Բ���ķ�ʽ�������ύ�����ݿ��С�
	if(1==method){
		//3-1.���õ�ǰ��Χ�����γ��ύ���ݿ��SQL��䡣
		CString unit_id(_T(""));
		if(0==_unit_id){
			unit_id=_T("null");
		}else{
			unit_id.Format(_T("'%d'"),_unit_id);
		}
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [range_application]([item_id],[report_name],[control_interval],\
					  [unit_id],[instrument_factor_a],[instrument_factor_b],[data_mode_id],[lower_age_limit_1],\
					  [upper_age_limit_1],[lower_age_limit_unit_1],[upper_age_limit_unit_1],\
					  [lower_limit_1_of_normal_for_males_1],[upper_limit_1_of_normal_for_males_1],\
					  [lower_limit_2_of_normal_for_males_1],[upper_limit_2_of_normal_for_males_1],\
					  [lower_limit_3_of_normal_for_males_1],[upper_limit_3_of_normal_for_males_1],\
					  [lower_limit_1_of_normal_for_females_1],[upper_limit_1_of_normal_for_females_1],\
					  [lower_limit_2_of_normal_for_females_1],[upper_limit_2_of_normal_for_females_1],\
					  [lower_limit_3_of_normal_for_females_1],[upper_limit_3_of_normal_for_females_1],\
					  [default_age_1],[default_sex_1],[lower_limit_for_repeat_range_1],\
					  [upper_limit_for_repeat_range_1],[is_use_qualitative_table_1],[qualitative_limit_1_1],\
					  [qualitative_limit_text_1_1],[qualitative_limit_2_1],[qualitative_limit_text_2_1],\
					  [qualitative_limit_3_1],[qualitative_limit_text_3_1],[qualitative_limit_4_1],\
					  [qualitative_limit_text_4_1],[qualitative_limit_5_1],[qualitative_limit_text_5_1],\
					  [qualitative_limit_text_6_1],[lower_age_limit_2],[upper_age_limit_2],[lower_age_limit_unit_2],\
					  [upper_age_limit_unit_2],[lower_limit_1_of_normal_for_males_2],[upper_limit_1_of_normal_for_males_2],\
					  [lower_limit_2_of_normal_for_males_2],[upper_limit_2_of_normal_for_males_2],\
					  [lower_limit_3_of_normal_for_males_2],[upper_limit_3_of_normal_for_males_2],\
					  [lower_limit_1_of_normal_for_females_2],[upper_limit_1_of_normal_for_females_2],\
					  [lower_limit_2_of_normal_for_females_2],[upper_limit_2_of_normal_for_females_2],\
					  [lower_limit_3_of_normal_for_females_2],[upper_limit_3_of_normal_for_females_2],[default_age_2],\
					  [default_sex_2],[lower_limit_for_repeat_range_2],[upper_limit_for_repeat_range_2],\
					  [is_use_qualitative_table_2],[qualitative_limit_1_2],[qualitative_limit_text_1_2],\
					  [qualitative_limit_2_2],[qualitative_limit_text_2_2],[qualitative_limit_3_2],\
					  [qualitative_limit_text_3_2],[qualitative_limit_4_2],[qualitative_limit_text_4_2],\
					  [qualitative_limit_5_2],[qualitative_limit_text_5_2],[qualitative_limit_text_6_2],\
					  [lower_age_limit_3],[upper_age_limit_3],[lower_age_limit_unit_3],[upper_age_limit_unit_3],\
					  [lower_limit_1_of_normal_for_males_3],[upper_limit_1_of_normal_for_males_3],\
					  [lower_limit_2_of_normal_for_males_3],[upper_limit_2_of_normal_for_males_3],\
					  [lower_limit_3_of_normal_for_males_3],[upper_limit_3_of_normal_for_males_3],\
					  [lower_limit_1_of_normal_for_females_3],[upper_limit_1_of_normal_for_females_3],\
					  [lower_limit_2_of_normal_for_females_3],[upper_limit_2_of_normal_for_females_3],\
					  [lower_limit_3_of_normal_for_females_3],[upper_limit_3_of_normal_for_females_3],[default_age_3],\
					  [default_sex_3],[lower_limit_for_repeat_range_3],[upper_limit_for_repeat_range_3],\
					  [is_use_qualitative_table_3],[qualitative_limit_1_3],[qualitative_limit_text_1_3],\
					  [qualitative_limit_2_3],[qualitative_limit_text_2_3],[qualitative_limit_3_3],\
					  [qualitative_limit_text_3_3],[qualitative_limit_4_3],[qualitative_limit_text_4_3],\
					  [qualitative_limit_5_3],[qualitative_limit_text_5_3],[qualitative_limit_text_6_3],\
					  [lower_age_limit_4],[upper_age_limit_4],[lower_age_limit_unit_4],[upper_age_limit_unit_4],\
					  [lower_limit_1_of_normal_for_males_4],[upper_limit_1_of_normal_for_males_4],\
					  [lower_limit_2_of_normal_for_males_4],[upper_limit_2_of_normal_for_males_4],\
					  [lower_limit_3_of_normal_for_males_4],[upper_limit_3_of_normal_for_males_4],\
					  [lower_limit_1_of_normal_for_females_4],[upper_limit_1_of_normal_for_females_4],\
					  [lower_limit_2_of_normal_for_females_4],[upper_limit_2_of_normal_for_females_4],\
					  [lower_limit_3_of_normal_for_females_4],[upper_limit_3_of_normal_for_females_4],\
					  [default_age_4],[default_sex_4],[lower_limit_for_repeat_range_4],[upper_limit_for_repeat_range_4],\
					  [is_use_qualitative_table_4],[qualitative_limit_1_4],[qualitative_limit_text_1_4],\
					  [qualitative_limit_2_4],[qualitative_limit_text_2_4],[qualitative_limit_3_4],\
					  [qualitative_limit_text_3_4],[qualitative_limit_4_4],[qualitative_limit_text_4_4],\
					  [qualitative_limit_5_4],[qualitative_limit_text_5_4],[qualitative_limit_text_6_4],[lower_age_limit_5],\
					  [upper_age_limit_5],[lower_age_limit_unit_5],[upper_age_limit_unit_5],\
					  [lower_limit_1_of_normal_for_males_5],[upper_limit_1_of_normal_for_males_5],\
					  [lower_limit_2_of_normal_for_males_5],[upper_limit_2_of_normal_for_males_5],\
					  [lower_limit_3_of_normal_for_males_5],[upper_limit_3_of_normal_for_males_5],\
					  [lower_limit_1_of_normal_for_females_5],[upper_limit_1_of_normal_for_females_5],\
					  [lower_limit_2_of_normal_for_females_5],[upper_limit_2_of_normal_for_females_5],\
					  [lower_limit_3_of_normal_for_females_5],[upper_limit_3_of_normal_for_females_5],[default_age_5],\
					  [default_sex_5],[lower_limit_for_repeat_range_5],[upper_limit_for_repeat_range_5],\
					  [is_use_qualitative_table_5],[qualitative_limit_1_5],[qualitative_limit_text_1_5],\
					  [qualitative_limit_2_5],[qualitative_limit_text_2_5],[qualitative_limit_3_5],\
					  [qualitative_limit_text_3_5],[qualitative_limit_4_5],[qualitative_limit_text_4_5],\
					  [qualitative_limit_5_5],[qualitative_limit_text_5_5],[qualitative_limit_text_6_5],\
					  [lower_limit_for_technical_range_for_class_1],[upper_limit_for_technical_range_for_class_1],\
					  [lower_limit_for_technical_range_for_class_2],[upper_limit_for_technical_range_for_class_2])\
					  VALUES('%d','%s','%d',%s,'%lf','%lf','%d'"),item_id,_report_name,_control_interval,unit_id,
					  _instrument_factor_a,_instrument_factor_b,_data_mode_id);
		CString temp(_T(""));
		for(unsigned int index=0;index!=MAX_RANGES;++index){
			temp=_T(",'%d','%d','%d','%d','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf',\
					'%d','%d','%lf','%lf','%d','%lf','%s','%lf','%s','%lf','%s','%lf','%s','%lf','%s','%s'");
			temp=_ranges[index].get_commit_string(temp);
			if(_T("")==temp){
				return(-3);
			}else{
				sql+=temp;
			}
		}
		temp.Format(_T(",'%lf','%lf','%lf','%lf')"),_lower_limit_for_technical_range_for_class_1,
			_upper_limit_for_technical_range_for_class_1,_lower_limit_for_technical_range_for_class_2,
			_upper_limit_for_technical_range_for_class_2);
		sql+=temp;
		//3-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-4);
		}
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
	//4.�����ǰ�����Ը��µķ�ʽ�������ύ�����ݿ��С�
	else if(2==method){
		//4-1.���õ�ǰ��Χ�����γ��ύ���ݿ��SQL��䡣
		CString unit_id(_T(""));
		if(0==_unit_id){
			unit_id=_T("null");
		}else{
			unit_id.Format(_T("'%d'"),_unit_id);
		}
		CString sql(_T(""));
		sql.Format(_T("UPDATE [range_application] SET [report_name]='%s',[control_interval]='%d',[unit_id]=%s,\
					  [instrument_factor_a]='%lf',[instrument_factor_b]='%lf',[data_mode_id]='%d'"),_report_name,
					  _control_interval,unit_id,_instrument_factor_a,_instrument_factor_b,_data_mode_id);
		CString temp(_T(""));
		CString index_string(_T(""));
		for(unsigned int index=0;index!=MAX_RANGES;++index){
			temp=_T(",[lower_age_limit_$]='%d',[upper_age_limit_$]='%d',[lower_age_limit_unit_$]='%d',\
					[upper_age_limit_unit_$]='%d',[lower_limit_1_of_normal_for_males_$]='%lf',\
					[upper_limit_1_of_normal_for_males_$]='%lf',[lower_limit_2_of_normal_for_males_$]='%lf',\
					[upper_limit_2_of_normal_for_males_$]='%lf',[lower_limit_3_of_normal_for_males_$]='%lf',\
					[upper_limit_3_of_normal_for_males_$]='%lf',[lower_limit_1_of_normal_for_females_$]='%lf',\
					[upper_limit_1_of_normal_for_females_$]='%lf',[lower_limit_2_of_normal_for_females_$]='%lf',\
					[upper_limit_2_of_normal_for_females_$]='%lf',[lower_limit_3_of_normal_for_females_$]='%lf',\
					[upper_limit_3_of_normal_for_females_$]='%lf',[default_age_$]='%d',[default_sex_$]='%d',\
					[lower_limit_for_repeat_range_$]='%lf',[upper_limit_for_repeat_range_$]='%lf',\
					[is_use_qualitative_table_$]='%d',[qualitative_limit_1_$]='%lf',[qualitative_limit_text_1_$]='%s',\
					[qualitative_limit_2_$]='%lf',[qualitative_limit_text_2_$]='%s',[qualitative_limit_3_$]='%lf',\
					[qualitative_limit_text_3_$]='%s',[qualitative_limit_4_$]='%lf',[qualitative_limit_text_4_$]='%s',\
					[qualitative_limit_5_$]='%lf',[qualitative_limit_text_5_$]='%s',[qualitative_limit_text_6_$]='%s'");
			index_string.Format(_T("%d"),index+1);
			temp.Replace(_T("$"),index_string);
			temp=_ranges[index].get_commit_string(temp);
			if(_T("")==temp){
				return(-5);
			}else{
				sql+=temp;
			}
		}
		temp.Format(_T(",[lower_limit_for_technical_range_for_class_1]='%lf',\
					   [upper_limit_for_technical_range_for_class_1]='%lf',\
					   [lower_limit_for_technical_range_for_class_2]='%lf',\
					   [upper_limit_for_technical_range_for_class_2]='%lf' \
					   WHERE [item_id]='%d'"),_lower_limit_for_technical_range_for_class_1,
					   _upper_limit_for_technical_range_for_class_1,
					   _lower_limit_for_technical_range_for_class_2,
					   _upper_limit_for_technical_range_for_class_2,item_id);
		//4-2.ִ��SQL��佫��ǰ��Ŀ��Ϣ�ύ�����ݿ��С�
		if(database.execute(sql)<0){
			return(-6);
		}
		//4-3.�������е��˳ɹ����ء�
		return(0);
	}	
	//5.�����ǰ������������ʽ�������ύ�����ݿ��С�
	else{
		return(-7);
	}
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ�ķ�Χ��Ϣ��
 * param: record - ָ���ļ�¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int RangeApplication::update(MtADORecordset &record){
	//1.������ǰ�������������
	RangeApplication range;
	_variant_t value;
	long record_index=86;
	//2.��ָ���ļ�¼���л�ȡ�������ơ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	range._report_name=MtADODataConverter::to_string(value);
	//3.��ָ���ļ�¼���л�ȡ�ʿؼ����
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	range._control_interval=MtADODataConverter::to_int(value);
	//4.��ָ���ļ�¼���л�ȡ��λ��Ϣ��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	if(VT_NULL==value.vt){
		range._unit_id=0;
	}else{
		range._unit_id=MtADODataConverter::to_int(value);
	}
	//5.��ָ���ļ�¼���л�ȡ�豸ϵ��a��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	range._instrument_factor_a=MtADODataConverter::to_double(value);
	//6.��ָ���ļ�¼���л�ȡ�豸ϵ��b��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	range._instrument_factor_b=MtADODataConverter::to_double(value);
	//7.��ָ���ļ�¼���л�ȡ����ģʽ��
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	range._data_mode_id=MtADODataConverter::to_int(value);
	//8.������Χ���飬��ȡ��Χ�����е����ݡ�
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		if((range._ranges[index]).update(record_index,record)<0){
			return(-7);
		}
	}
	//9.��ָ���ļ�¼���л�ȡ��������Ϊ����1�����������鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	range._lower_limit_for_technical_range_for_class_1=MtADODataConverter::to_double(value);
	//10.��ָ���ļ�¼���л�ȡ��������Ϊ����1�����������鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	range._upper_limit_for_technical_range_for_class_1=MtADODataConverter::to_double(value);
	//11.��ָ���ļ�¼���л�ȡ��������Ϊ����1�����������鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	range._lower_limit_for_technical_range_for_class_2=MtADODataConverter::to_double(value);
	//12.��ָ���ļ�¼���л�ȡ��������Ϊ����1�����������鷶Χ���ޡ�
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	range._upper_limit_for_technical_range_for_class_2=MtADODataConverter::to_double(value);
	//13.�����ǰ��ȡ�ķ�Χ��Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(range.is_valid()<0){
		return(-12);
	}
	//14.���浱ǰ�ĴӼ�¼���л�ȡ�ķ�Χ��Ϣ��
	(*this)=range;
	//15.�������е��˳ɹ����ء�
	return(0);
}