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
 * brief: 构造函数。
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
 * brief: 析构函数。
 * param: --
 * return: --
 */
RangeApplication::Range::~Range(){
}

/**
 * name: set_lower_age_limit
 * breif: 设置年龄下限。
 * param: lower_age_limit - 年龄下限。
 * return: --
 */
void RangeApplication::Range::set_lower_age_limit(const int lower_age_limit){
	_lower_age_limit=lower_age_limit;
}

/**
 * name: get_lower_age_limit
 * breif: 获取年龄下限。
 * param: --
 * return: 返回年龄下限。
 */
int RangeApplication::Range::get_lower_age_limit() const{
	return(_lower_age_limit);
}

/**
 * name: set_upper_age_limit
 * breif: 设置年龄上限。
 * param: upper_age_limit - 年龄上限。
 * return: --
 */
void RangeApplication::Range::set_upper_age_limit(const int upper_age_limit){
	_upper_age_limit=upper_age_limit;
}

/**
 * name: get_upper_age_limit
 * breif: 获取年龄上限。
 * param: --
 * return: 返回年龄上限。
 */
int RangeApplication::Range::get_upper_age_limit() const{
	return(_upper_age_limit);
}

/**
 * name: set_lower_age_unit_id
 * breif: 设置年龄下限的单位标识。
 * param: lower_age_unit_id - 年龄下限的单位标识。
 * return: --
 */
void RangeApplication::Range::set_lower_age_unit_id(const int lower_age_unit_id){
	_lower_age_unit_id=lower_age_unit_id;
}

/**
 * name: get_lower_age_unit_id
 * breif: 获取年龄下限的单位标识。
 * param: --
 * return: 返回年龄下限的单位标识。
 */
int RangeApplication::Range::get_lower_age_unit_id() const{
	return(_lower_age_unit_id);
}

/**
 * name: set_upper_age_unit_id
 * breif: 设置年龄上限的单位标识。
 * param: upper_age_unit_id - 年龄上限的单位标识。
 * return: --
 */
void RangeApplication::Range::set_upper_age_unit_id(const int upper_age_unit_id){
	_upper_age_unit_id=upper_age_unit_id;
}

/**
 * name: get_upper_age_unit_id
 * breif: 获取年龄上限的单位标识。
 * param: --
 * return: 返回年龄上限的单位标识。
 */
int RangeApplication::Range::get_upper_age_unit_id() const{
	return(_upper_age_unit_id);
}

/**
 * name: set_lower_limit_of_normal_for_males_1
 * breif: 设置男性正常范围的范围1的下限值。
 * param: lower_limit_of_normal_for_males_1 - 男性正常范围的范围1的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_1(
	const double lower_limit_of_normal_for_males_1){
	_lower_limit_of_normal_for_males_1=lower_limit_of_normal_for_males_1;
}

/**
 * name: get_lower_limit_of_normal_for_males_1
 * breif: 获取男性正常范围的范围1的下限值。
 * param: --
 * return: 返回男性正常范围的范围1的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_1() const{
	return(_lower_limit_of_normal_for_males_1);
}

/**
 * name: set_upper_limit_of_normal_for_males_1
 * breif: 设置男性正常范围的范围1的上限值。
 * param: upper_limit_of_normal_for_males_1 - 男性正常范围的范围1的上限值。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_1(
	const double upper_limit_of_normal_for_males_1){
	_upper_limit_of_normal_for_males_1=upper_limit_of_normal_for_males_1;
}

/**
 * name: get_upper_limit_of_normal_for_males_1
 * breif: 获取男性正常范围的范围1的上限值。
 * param: --
 * return: 返回男性正常范围的范围1的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_1() const{
	return(_upper_limit_of_normal_for_males_1);
}

/**
 * name: set_lower_limit_of_normal_for_males_2
 * breif: 设置男性正常范围的范围2的下限值。
 * param: lower_limit_of_normal_for_males_2 - 男性正常范围的范围2的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_2(
	const double lower_limit_of_normal_for_males_2){
	_lower_limit_of_normal_for_males_2=lower_limit_of_normal_for_males_2;
}

/**
 * name: get_lower_limit_of_normal_for_males_2
 * breif: 获取男性正常范围的范围2的下限值。
 * param: --
 * return: 返回男性正常范围的范围2的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_2() const{
	return(_lower_limit_of_normal_for_males_2);
}

/**
 * name: set_upper_limit_of_normal_for_males_2
 * breif: 设置男性正常范围的范围2的上限值。
 * param: upper_limit_of_normal_for_males_2 - 男性正常范围的范围2的上限值。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_2(
	const double upper_limit_of_normal_for_males_2){
	_upper_limit_of_normal_for_males_2=upper_limit_of_normal_for_males_2;
}

/**
 * name: get_upper_limit_of_normal_for_males_2
 * breif: 获取男性正常范围的范围2的上限值。
 * param: --
 * return: 返回男性正常范围的范围2的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_2() const{
	return(_upper_limit_of_normal_for_males_2);
}

/**
 * name: set_lower_limit_of_normal_for_males_3
 * breif: 设置男性正常范围的范围3的下限值。
 * param: lower_limit_of_normal_for_males_3 - 男性正常范围的范围3的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_males_3(
	const double lower_limit_of_normal_for_males_3){
	_lower_limit_of_normal_for_males_3=lower_limit_of_normal_for_males_3;
}

/**
 * name: get_lower_limit_of_normal_for_males_3
 * breif: 获取男性正常范围的范围3的下限值。
 * param: --
 * return: 返回男性正常范围的范围3的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_males_3() const{
	return(_lower_limit_of_normal_for_males_3);
}

/**
 * name: set_upper_limit_of_normal_for_males_3
 * breif: 设置男性正常范围的范围3的上限值。
 * param: upper_limit_of_normal_for_males_3 - 男性正常范围的范围3的上限值。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_males_3(
	const double upper_limit_of_normal_for_males_3){
	_upper_limit_of_normal_for_males_3=upper_limit_of_normal_for_males_3;
}

/**
 * name: get_upper_limit_of_normal_for_males_3
 * breif: 获取男性正常范围的范围3的上限值。
 * param: --
 * return: 返回男性正常范围的范围3的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_males_3() const{
	return(_upper_limit_of_normal_for_males_3);
}

/**
 * name: set_lower_limit_of_normal_for_females_1
 * breif: 设置女性正常范围的范围1的下限值。
 * param: lower_limit_of_normal_for_females_1 - 女性正常范围的范围1的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_1(
	const double lower_limit_of_normal_for_females_1){
	_lower_limit_of_normal_for_females_1=lower_limit_of_normal_for_females_1;
}

/**
 * name: get_lower_limit_of_normal_for_females_1
 * breif: 获取女性正常范围的范围1的下限值。
 * param: --
 * return: 返回女性正常范围的范围1的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_1() const{
	return(_lower_limit_of_normal_for_females_1);
}

/**
 * name: set_upper_limit_of_normal_for_females_1
 * breif: 设置女性正常范围的范围1的上限值。
 * param: upper_limit_of_normal_for_females_1 - 女性正常范围的范围1的上限值。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_1(
	const double upper_limit_of_normal_for_females_1){
	_upper_limit_of_normal_for_females_1=upper_limit_of_normal_for_females_1;
}

/**
 * name: get_upper_limit_of_normal_for_females_1
 * breif: 获取女性正常范围的范围1的上限值。
 * param: --
 * return: 返回女性正常范围的范围1的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_1() const{
	return(_upper_limit_of_normal_for_females_1);
}

/**
 * name: set_lower_limit_of_normal_for_females_2
 * breif: 设置女性正常范围的范围2的下限值。
 * param: lower_limit_of_normal_for_females_2 - 女性正常范围的范围2的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_2(
	const double lower_limit_of_normal_for_females_2){
	_lower_limit_of_normal_for_females_2=lower_limit_of_normal_for_females_2;
}

/**
 * name: get_lower_limit_of_normal_for_females_2
 * breif: 获取女性正常范围的范围2的下限值。
 * param: --
 * return: 返回女性正常范围的范围2的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_2() const{
	return(_lower_limit_of_normal_for_females_2);
}

/**
 * name: set_upper_limit_of_normal_for_females_2
 * breif: 设置女性正常范围的范围2的上限值。
 * param: upper_limit_of_normal_for_females_2 - 女性正常范围的范围2的上限值。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_2(
	const double upper_limit_of_normal_for_females_2){
	_upper_limit_of_normal_for_females_2=upper_limit_of_normal_for_females_2;
}

/**
 * name: get_upper_limit_of_normal_for_females_2
 * breif: 获取女性正常范围的范围2的上限值。
 * param: --
 * return: 返回女性正常范围的范围2的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_2() const{
	return(_upper_limit_of_normal_for_females_2);
}

/**
 * name: set_lower_limit_of_normal_for_females_3
 * breif: 设置女性正常范围的范围3的下限值。
 * param: lower_limit_of_normal_for_females_3 - 女性正常范围的范围3的下限值。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_of_normal_for_females_3(
	const double lower_limit_of_normal_for_females_3){
	_lower_limit_of_normal_for_females_3=lower_limit_of_normal_for_females_3;
}

/**
 * name: get_lower_limit_of_normal_for_females_3
 * breif: 获取女性正常范围的范围3的下限值。
 * param: --
 * return: 返回女性正常范围的范围3的下限值
 */
double RangeApplication::Range::get_lower_limit_of_normal_for_females_3() const{
	return(_lower_limit_of_normal_for_females_3);
}

/**
 * name: set_upper_limit_of_normal_for_females_3
 * breif: 设置女性正常范围的范围3的上限值。
 * param: upper_limit_of_normal_for_females_3 - 女性正常范围的范围3的上限值。
 * return: --s
 */
void RangeApplication::Range::set_upper_limit_of_normal_for_females_3(
	const double upper_limit_of_normal_for_females_3){
	_upper_limit_of_normal_for_females_3=upper_limit_of_normal_for_females_3;
}

/**
 * name: get_upper_limit_of_normal_for_females_3
 * breif: 获取女性正常范围的范围3的上限值。
 * param: --
 * return: 返回女性正常范围的范围3的上限值
 */
double RangeApplication::Range::get_upper_limit_of_normal_for_females_3() const{
	return(_upper_limit_of_normal_for_females_3);
}

/**
 * name: set_default_age
 * brief: 设置默认年龄。
 * param: default_age - 默认年龄。
 * return: --
 */
void RangeApplication::Range::set_default_age(const int default_age){
	_default_age=default_age;
}

/**
 * name: get_default_age
 * breif: 获取默认年龄。
 * param: --
 * return: 返回默认年龄。
 */
int RangeApplication::Range::get_default_age() const{
	return(_default_age);
}

/**
 * name: set_default_sex
 * brief: 设置默认性别。
 * param: default_sex - 默认性别。
 * return: --
 */
void RangeApplication::Range::set_default_sex(const int default_sex){
	_default_sex=default_sex;
}

/**
 * name: get_default_sex
 * breif: 获取默认性别。
 * param: --
 * return: 返回默认性别。
 */
int RangeApplication::Range::get_default_sex() const{
	return(_default_sex);
}

/**
 * name: set_lower_limit_for_repeat_range
 * breif: 设置标准复查范围的下限。
 * param: lower_limit_for_repeat_range - 标准复查范围的下限。
 * return: --
 */
void RangeApplication::Range::set_lower_limit_for_repeat_range(
	const double lower_limit_for_repeat_range){
	_lower_limit_for_repeat_range=lower_limit_for_repeat_range;
}

/**
 * name: get_lower_limit_for_repeat_range
 * breif: 获取标准复查范围的下限。
 * param: --
 * return: 返回标准复查范围的下限。
 */
double RangeApplication::Range::get_lower_limit_for_repeat_range() const{
	return(_lower_limit_for_repeat_range);
}

/**
 * name: set_upper_limit_for_repeat_range
 * breif: 设置标准复查范围的上限。
 * param: upper_limit_for_repeat_range - 标准复查范围的上限。
 * return: --
 */
void RangeApplication::Range::set_upper_limit_for_repeat_range(
	const double upper_limit_for_repeat_range){
	_upper_limit_for_repeat_range=upper_limit_for_repeat_range;
}

/**
 * name: get_upper_limit_for_repeat_range
 * breif: 获取标准复查范围的上限。
 * param: --
 * return: 返回标准复查范围的上限。
 */
double RangeApplication::Range::get_upper_limit_for_repeat_range() const{
	return(_upper_limit_for_repeat_range);
}

/**
 * name: set_is_use_qualitative_table
 * breif: 设置是否使用定性表。
 * param: is_use_qualitative_table - 是否使用定性表（0 不使用，1 使用）。
 * return: --
 */
void RangeApplication::Range::set_is_use_qualitative_table(
	const int is_use_qualitative_table){
	_is_use_qualitative_table=is_use_qualitative_table;
}

/**
 * name: get_is_use_qualitative_table
 * breif: 获取是否使用定性表。
 * param: --
 * return: 返回是否使用定性表。
 */
int RangeApplication::Range::get_is_use_qualitative_table() const{
	return(_is_use_qualitative_table);
}

/**
 * name: set_qualitative_limit_1
 * breif: 设置定性界限1。
 * param: qualitative_limit_1 - 定性界限1。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_1(
	const double qualitative_limit_1){
	_qualitative_limit_1=qualitative_limit_1;
}

/**
 * name: get_qualitative_limit_1
 * breif: 获取定性界限1。
 * param: --
 * return: 返回定性界限1。
 */
double RangeApplication::Range::get_qualitative_limit_1() const{
	return(_qualitative_limit_1);
}

/**
 * name: set_qualitative_limit_text_1
 * brief: 设置定性界限描述字符串1。
 * param: qualitative_limit_text_1 - 定性界限描述字符串1。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_1(
	const CString &qualitative_limit_text_1){
	_qualitative_limit_text_1=qualitative_limit_text_1;
}

/**
 * name: get_qualitative_limit_text_1
 * brief: 获取定性界限描述字符串1。
 * param: --
 * return: 返回定性界限描述字符串1。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_1() const{
	return(_qualitative_limit_text_1);
}

/**
 * name: set_qualitative_limit_2
 * breif: 设置定性界限2。
 * param: qualitative_limit_2 - 定性界限2。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_2(
	const double qualitative_limit_2){
	_qualitative_limit_2=qualitative_limit_2;
}

/**
 * name: get_qualitative_limit_2
 * breif: 获取定性界限2。
 * param: --
 * return: 返回定性界限2。
 */
double RangeApplication::Range::get_qualitative_limit_2() const{
	return(_qualitative_limit_2);
}

/**
 * name: set_qualitative_limit_text_2
 * brief: 设置定性界限描述字符串2。
 * param: qualitative_limit_text_2 - 定性界限描述字符串2。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_2(
	const CString &qualitative_limit_text_2){
	_qualitative_limit_text_2=qualitative_limit_text_2;
}

/**
 * name: get_qualitative_limit_text_2
 * brief: 获取定性界限描述字符串2。
 * param: --
 * return: 返回定性界限描述字符串2。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_2() const{
	return(_qualitative_limit_text_2);
}

/**
 * name: set_qualitative_limit_3
 * breif: 设置定性界限3。
 * param: qualitative_limit_3 - 定性界限3。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_3(
	const double qualitative_limit_3){
	_qualitative_limit_3=qualitative_limit_3;
}

/**
 * name: get_qualitative_limit_3
 * breif: 获取定性界限3。
 * param: --
 * return: 返回定性界限3。
 */
double RangeApplication::Range::get_qualitative_limit_3() const{
	return(_qualitative_limit_3);
}

/**
 * name: set_qualitative_limit_text_3
 * brief: 设置定性界限描述字符串3。
 * param: qualitative_limit_text_3 - 定性界限描述字符串3。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_3(
	const CString &qualitative_limit_text_3){
	_qualitative_limit_text_3=qualitative_limit_text_3;
}

/**
 * name: get_qualitative_limit_text_3
 * brief: 获取定性界限描述字符串3。
 * param: --
 * return: 返回定性界限描述字符串3。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_3() const{
	return(_qualitative_limit_text_3);
}

/**
 * name: set_qualitative_limit_4
 * breif: 设置定性界限4。
 * param: qualitative_limit_4 - 定性界限4。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_4(
	const double qualitative_limit_4){
	_qualitative_limit_4=qualitative_limit_4;
}

/**
 * name: get_qualitative_limit_4
 * breif: 获取定性界限4。
 * param: --
 * return: 返回定性界限4。
 */
double RangeApplication::Range::get_qualitative_limit_4() const{
	return(_qualitative_limit_4);
}

/**
 * name: set_qualitative_limit_text_4
 * brief: 设置定性界限描述字符串4。
 * param: qualitative_limit_text_4 - 定性界限描述字符串4。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_4(
	const CString &qualitative_limit_text_4){
	_qualitative_limit_text_4=qualitative_limit_text_4;
}

/**
 * name: get_qualitative_limit_text_4
 * brief: 获取定性界限描述字符串4。
 * param: --
 * return: 返回定性界限描述字符串4。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_4() const{
	return(_qualitative_limit_text_4);
}

/**
 * name: set_qualitative_limit_5
 * breif: 设置定性界限5。
 * param: qualitative_limit_5 - 定性界限5。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_5(
	const double qualitative_limit_5){
	_qualitative_limit_5=qualitative_limit_5;
}

/**
 * name: get_qualitative_limit_5
 * breif: 获取定性界限5。
 * param: --
 * return: 返回定性界限5。
 */
double RangeApplication::Range::get_qualitative_limit_5() const{
	return(_qualitative_limit_5);
}

/**
 * name: set_qualitative_limit_text_5
 * brief: 设置定性界限描述字符串5。
 * param: qualitative_limit_text_5 - 定性界限描述字符串5。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_5(
	const CString &qualitative_limit_text_5){
	_qualitative_limit_text_5=qualitative_limit_text_5;
}

/**
 * name: get_qualitative_limit_text_5
 * brief: 获取定性界限描述字符串5。
 * param: --
 * return: 返回定性界限描述字符串5。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_5() const{
	return(_qualitative_limit_text_5);
}

/**
 * name: set_qualitative_limit_text_6
 * brief: 设置定性界限描述字符串6。
 * param: qualitative_limit_text_6 - 定性界限描述字符串6。
 * return: --
 */
void RangeApplication::Range::set_qualitative_limit_text_6(
	const CString &qualitative_limit_text_6){
	_qualitative_limit_text_6=qualitative_limit_text_6;
}

/**
 * name: get_qualitative_limit_text_6
 * brief: 获取定性界限描述字符串6。
 * param: --
 * return: 返回定性界限描述字符串6。
 */
const CString &RangeApplication::Range::get_qualitative_limit_text_6() const{
	return(_qualitative_limit_text_6);
}

/**
 * name: is_valid
 * brief: 判断当前分析申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前分析申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int RangeApplication::Range::is_valid(CString *error_message) const{
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.检测当前年龄下限是否合法。
	if((_lower_age_limit<0)||(_lower_age_limit>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING368),0,200);
		}
		return(-6);
	}
	//3.检测当前年龄上限是否合法。
	if((_upper_age_limit<0)||(_upper_age_limit>200)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING369),0,200);
		}
		return(-7);
	}
	//4.检测当前年龄下限单位是否合法。
	if(_lower_age_unit_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING370));
		}
		return(-8);
	}
	//5.检测当前年龄上限单位是否合法。
	if(_upper_age_unit_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING371));
		}
		return(-9);
	}
	//6.检测男性正常范围1的下限值是否合法。
	if((_lower_limit_of_normal_for_males_1<-99999.0)||(
		_lower_limit_of_normal_for_males_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-10);
	}
	//7.检测男性正常范围1的上限值是否合法。
	if((_upper_limit_of_normal_for_males_1<-99999.0)||(
		_upper_limit_of_normal_for_males_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-11);
	}
	//8.检测男性正常范围2的下限值是否合法。
	if((_lower_limit_of_normal_for_males_2<-99999.0)||(
		_lower_limit_of_normal_for_males_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-12);
	}
	//9.检测男性正常范围2的上限值是否合法。
	if((_upper_limit_of_normal_for_males_2<-99999.0)||(
		_upper_limit_of_normal_for_males_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-13);
	}
	//10.检测男性正常范围3的下限值是否合法。
	if((_lower_limit_of_normal_for_males_3<-99999.0)||(
		_lower_limit_of_normal_for_males_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING372),-99999.0,999999.0);
		}
		return(-14);
	}
	//11.检测男性正常范围3的上限值是否合法。
	if((_upper_limit_of_normal_for_males_3<-99999.0)||(
		_upper_limit_of_normal_for_males_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING373),-99999.0,999999.0);
		}
		return(-15);
	}
	//12.检测女性正常范围1的下限值是否合法。
	if((_lower_limit_of_normal_for_females_1<-99999.0)||(
		_lower_limit_of_normal_for_females_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-16);
	}
	//13.检测女性正常范围1的上限值是否合法。
	if((_upper_limit_of_normal_for_females_1<-99999.0)||(
		_upper_limit_of_normal_for_females_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-17);
	}
	//14.检测女性正常范围2的下限值是否合法。
	if((_lower_limit_of_normal_for_females_2<-99999.0)||(
		_lower_limit_of_normal_for_females_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-18);
	}
	//15.检测女性正常范围2的上限值是否合法。
	if((_upper_limit_of_normal_for_females_2<-99999.0)||(
		_upper_limit_of_normal_for_females_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-19);
	}
	//16.检测女性正常范围3的下限值是否合法。
	if((_lower_limit_of_normal_for_females_3<-99999.0)||(
		_lower_limit_of_normal_for_females_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING374),-99999.0,999999.0);
		}
		return(-20);
	}
	//17.检测女性正常范围3的上限值是否合法。
	if((_upper_limit_of_normal_for_females_3<-99999.0)||(
		_upper_limit_of_normal_for_females_3>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(
				IDS_STRING375),-99999.0,999999.0);
		}
		return(-21);
	}
	//18.检测默认年龄是否合法。
	if((1!=_default_age)&&(2!=_default_age)&&(3!=_default_age)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING376));
		}
		return(-22);
	}
	//19.检测默认性别是否合法。
	if(_default_sex<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING377));
		}
		return(-23);
	}
	//20.检测复查范围下限是否合法。
	if((_lower_limit_for_repeat_range<-99999.0)||(
		_lower_limit_for_repeat_range>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING378),
				-99999.0,999999.0);
		}
		return(-24);
	}
	//21.检测复查范围上限是否合法。
	if((_upper_limit_for_repeat_range<-99999.0)||(
		_upper_limit_for_repeat_range>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING379),
				-99999.0,999999.0);
		}
		return(-25);
	}
	//22.检测是否选择定性表是否合法。
	if((0!=_is_use_qualitative_table)&&(1!=_is_use_qualitative_table)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING380));
		}
		return(-26);
	}
	//23.检测定性表界限值是否合法。
	if(_is_use_qualitative_table){
		//23-1.检测定性界限1是否合法。
		if((_qualitative_limit_1<-99999.0)&&(_qualitative_limit_1>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-27);
		}
		//23-2.检测定性界限2是否合法。
		if((_qualitative_limit_2<-99999.0)&&(_qualitative_limit_2>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-28);
		}
		//23-3.检测定性界限3是否合法。
		if((_qualitative_limit_3<-99999.0)&&(_qualitative_limit_3>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-29);
		}
		//23-4.检测定性界限4是否合法。
		if((_qualitative_limit_4<-99999.0)&&(_qualitative_limit_4>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-30);
		}
		//23-5.检测定性界限5是否合法。
		if((_qualitative_limit_5<-99999.0)&&(_qualitative_limit_5>999999.0)){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING381),
					-99999.0,999999.0);
			}
			return(-31);
		}
	}
	//24.检测年龄下限是否大于等于年龄上限。
	if((_lower_age_limit*_lower_age_unit_id)>=(_upper_age_limit*_upper_age_unit_id)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING382));
		}
		return(-32);
	}
	//25.检测男性正常范围1下限是否大于等于男性正常范围1上限。
	if((_lower_limit_of_normal_for_males_1>=_upper_limit_of_normal_for_males_1)||
		(is_zero(_lower_limit_of_normal_for_males_1-_upper_limit_of_normal_for_males_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-33);
	}
	//26.检测男性正常范围2下限是否大于等于男性正常范围2上限。
	if((_lower_limit_of_normal_for_males_2>=_upper_limit_of_normal_for_males_2)||
		(is_zero(_lower_limit_of_normal_for_males_2-_upper_limit_of_normal_for_males_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-34);
	}
	//27.检测男性正常范围3下限是否大于等于男性正常范围3上限。
	if((_lower_limit_of_normal_for_males_3>=_upper_limit_of_normal_for_males_3)||
		(is_zero(_lower_limit_of_normal_for_males_3-_upper_limit_of_normal_for_males_3))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING383));
		}
		return(-35);
	}
	//28.检测女性正常范围1下限是否大于等于女性正常范围1上限。
	if((_lower_limit_of_normal_for_females_1>=_upper_limit_of_normal_for_females_1)||
		(is_zero(_lower_limit_of_normal_for_females_1-_upper_limit_of_normal_for_females_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-36);
	}
	//29.检测女性正常范围2下限是否大于等女性正常范围2上限。
	if((_lower_limit_of_normal_for_females_2>=_upper_limit_of_normal_for_females_2)||
		(is_zero(_lower_limit_of_normal_for_females_2-_upper_limit_of_normal_for_females_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-37);
	}
	//30.检测女性正常范围3下限是否大于等于女性正常范围3上限。
	if((_lower_limit_of_normal_for_females_3>=_upper_limit_of_normal_for_females_3)||
		(is_zero(_lower_limit_of_normal_for_females_3-_upper_limit_of_normal_for_females_3))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING384));
		}
		return(-38);
	}
	//31.检测标准复查范围下限是否大于等于标准复查范围上限。
	if((_lower_limit_for_repeat_range>=_upper_limit_for_repeat_range)||
		(is_zero(_lower_limit_for_repeat_range-_upper_limit_for_repeat_range))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING385));
		}
		return(-39);
	}
	//32.检测定性范围界限是否异常。
	if(_is_use_qualitative_table){
		//32-1.如果定性界限1大于等于定性界限2。
		if((_qualitative_limit_1>=_qualitative_limit_2)||
			(is_zero(_qualitative_limit_1-_qualitative_limit_2))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-40);
		}
		//32-2.如果定性界限2大于等于定性界限3。
		if((_qualitative_limit_2>=_qualitative_limit_3)||
			(is_zero(_qualitative_limit_2-_qualitative_limit_3))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-41);
		}
		//32-3.如果定性界限3大于等于定性界限4。
		if((_qualitative_limit_3>=_qualitative_limit_4)||
			(is_zero(_qualitative_limit_3-_qualitative_limit_4))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-42);
		}
		//32-4.如果定性界限4大于等于定性界限5。
		if((_qualitative_limit_4>=_qualitative_limit_5)||
			(is_zero(_qualitative_limit_4-_qualitative_limit_5))){
			if(0!=error_message){
				error_message->Format(theme->get_string(IDS_STRING386));
			}
			return(-43);
		}
	}
	//33.程序运行到此成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * brief: 将当前范围申请参数重置为默认值。
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
 * breif: 获取当前类中数据提交数据库时的命令字符串。
 * param: format - 格式字符串。
 * return: 如果函数执行成功，返回当前类提交数据库所需的命令字符串，否则返回空字符串。
 */
CString RangeApplication::Range::get_commit_string(const CString &format) const{
	//1.如果当前没有启用定性项目表。
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
	//2.如果当前启用了定性项目表。
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
	//3.如果当前处于其它情况。
	else{
		return(_T(""));
	}
}

/**
 * name: update
 * breif: 从指定的记录集中更新当前的范围信息。
 * param: record_index - 记录集起始索引编号。
 *        record - 指定的记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int RangeApplication::Range::update(long &record_index,MtADORecordset &record){
	//1.如果传递参数非法，则直接返回错误。
	if(record_index<0){
		return(-1);
	}
	//2.声明当前操作所需变量。
	_variant_t value;
	//3.从指定的记录集中获取年龄下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	_lower_age_limit=MtADODataConverter::to_int(value);
	//4.从指定的记录集中获取年龄上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	_upper_age_limit=MtADODataConverter::to_int(value);
	//5.从指定的记录集中获取年龄下限单位。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	_lower_age_unit_id=MtADODataConverter::to_int(value);
	//6.从指定的记录集中获取年龄上限单位。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	_upper_age_unit_id=MtADODataConverter::to_int(value);
	//7.从指定的记录集中获取男性正常范围1的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	_lower_limit_of_normal_for_males_1=MtADODataConverter::to_double(value);
	//8.从指定的记录集中获取男性正常范围1的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	_upper_limit_of_normal_for_males_1=MtADODataConverter::to_double(value);
	//9.从指定的记录集中获取男性正常范围2的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	_lower_limit_of_normal_for_males_2=MtADODataConverter::to_double(value);
	//10.从指定的记录集中获取男性正常范围2的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	_upper_limit_of_normal_for_males_2=MtADODataConverter::to_double(value);
	//11.从指定的记录集中获取男性正常范围3的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	_lower_limit_of_normal_for_males_3=MtADODataConverter::to_double(value);
	//12.从指定的记录集中获取男性正常范围3的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	_upper_limit_of_normal_for_males_3=MtADODataConverter::to_double(value);
	//13.从指定的记录集中获取女性正常范围1的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	_lower_limit_of_normal_for_females_1=MtADODataConverter::to_double(value);
	//14.从指定的记录集中获取女性正常范围1的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	_upper_limit_of_normal_for_females_1=MtADODataConverter::to_double(value);
	//15.从指定的记录集中获取女性正常范围2的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	_lower_limit_of_normal_for_females_2=MtADODataConverter::to_double(value);
	//16.从指定的记录集中获取女性正常范围2的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	_upper_limit_of_normal_for_females_2=MtADODataConverter::to_double(value);
	//17.从指定的记录集中获取女性正常范围3的下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	_lower_limit_of_normal_for_females_3=MtADODataConverter::to_double(value);
	//18.从指定的记录集中获取女性正常范围3的上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	_upper_limit_of_normal_for_females_3=MtADODataConverter::to_double(value);
	//19.从指定的记录集中获取默认年龄。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	_default_age=MtADODataConverter::to_int(value);
	//20.从指定的记录集中获取默认性别。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	_default_sex=MtADODataConverter::to_int(value);
	//21.从指定的记录集中获取标准复查范围下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	_lower_limit_for_repeat_range=MtADODataConverter::to_double(value);
	//22.从指定的记录集中获取标准复查范围上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	_upper_limit_for_repeat_range=MtADODataConverter::to_double(value);
	//23.从指定的记录集中获取是否启用定性表。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	_is_use_qualitative_table=MtADODataConverter::to_int(value);
	//24.如果当前启用了定性表。
	if(1==_is_use_qualitative_table){
		//24-1.从指定的记录集中获取定性界限1的界限值。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-23);
		}
		_qualitative_limit_1=MtADODataConverter::to_double(value);
		//24-2.从指定的记录集中获取定性界限1的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-24);
		}
		_qualitative_limit_text_1=MtADODataConverter::to_string(value);
		//24-3.从指定的记录集中获取定性界限2的界限值。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-25);
		}
		_qualitative_limit_2=MtADODataConverter::to_double(value);
		//24-4.从指定的记录集中获取定性界限2的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-26);
		}
		_qualitative_limit_text_2=MtADODataConverter::to_string(value);
		//24-5.从指定的记录集中获取定性界限3的界限值。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-27);
		}
		_qualitative_limit_3=MtADODataConverter::to_double(value);
		//24-6.从指定的记录集中获取定性界限3的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-28);
		}
		_qualitative_limit_text_3=MtADODataConverter::to_string(value);
		//24-7.从指定的记录集中获取定性界限4的界限值。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-29);
		}
		_qualitative_limit_4=MtADODataConverter::to_double(value);
		//24-8.从指定的记录集中获取定性界限4的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-30);
		}
		_qualitative_limit_text_4=MtADODataConverter::to_string(value);
		//24-9.从指定的记录集中获取定性界限5的界限值。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-31);
		}
		_qualitative_limit_5=MtADODataConverter::to_double(value);
		//24-10.从指定的记录集中获取定性界限5的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-32);
		}
		_qualitative_limit_text_5=MtADODataConverter::to_string(value);
		//24-11.从指定的记录集中获取定性界限6的字符描述。
		value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
		if(0!=record.get_last_error_code()){
			return(-33);
		}
		_qualitative_limit_text_6=MtADODataConverter::to_string(value);
	}
	//25.如果当前尚未启用静态表。
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
	//26.如果当前出现异常情况。
	else{
		return(-34);
	}
	//27.程序运行到此成功返回。
	return(0);
}

/**
 * name: RangeApplication
 * brief: 构造函数。
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
 * brief: 拷贝构造函数。
 * param: source - 拷贝源。
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
 * brief: 析构函数。
 * param: --
 * return: --
 */
RangeApplication::~RangeApplication(void){
	delete[] _ranges;
}

/**
 * name: set_report_name
 * brief: 设置报告名称。
 * param: report_name - 报告名称。
 * return: --
 */
void RangeApplication::set_report_name(const CString &report_name){
	_report_name=report_name;
}

/**
 * name: get_report_name
 * brief: 获取报告名称。
 * param: --
 * return: 返回报告名称。
 */
const CString &RangeApplication::get_report_name() const{
	return(_report_name);
}

/**
 * name: set_control_interval
 * brief: 设置质控间隔。
 * param: control_interval - 质控间隔。
 * return: --
 */
void RangeApplication::set_control_interval(const int control_interval){
	_control_interval=control_interval;
}

/**
 * name: get_control_interval
 * brief: 获取质控间隔。
 * param: --
 * return: 返回质控间隔。
 */
int RangeApplication::get_control_interval() const{
	return(_control_interval);
}

/**
 * name: set_unit_id
 * breif: 设置单位标识。
 * param: unit_id - 单位标识。
 * return: --
 */
void RangeApplication::set_unit_id(const int unit_id){
	_unit_id=unit_id;
}

/**
 * name: get_unit_id
 * breif: 获取单位标识。
 * param: --
 * return: 返回单位标识。
 */
int RangeApplication::get_unit_id() const{
	return(_unit_id);
}

/**
 * name: set_instrument_factor_a
 * breif: 设置设备系数a。
 * param: instrument_factor_a - 设备系统a。
 * return: --
 */
void RangeApplication::set_instrument_factor_a(const double instrument_factor_a){
	_instrument_factor_a=instrument_factor_a;
}

/**
 * name: get_instrument_factor_a
 * breif: 获取设备系数a。
 * param: --
 * return: 返回设备系数a。
 */
double RangeApplication::get_instrument_factor_a() const{
	return(_instrument_factor_a);
}

/**
 * name: set_instrument_factor_b
 * breif: 设置设备系数b。
 * param: instrument_factor_b - 设备系统b。
 * return: --
 */
void RangeApplication::set_instrument_factor_b(const double instrument_factor_b){
	_instrument_factor_b=instrument_factor_b;
}

/**
 * name: get_instrument_factor_b
 * breif: 获取设备系数b。
 * param: --
 * return: 返回设备系数b。
 */
double RangeApplication::get_instrument_factor_b() const{
	return(_instrument_factor_b);
}

/**
 * name: set_data_mode_id
 * brief: 设置数据模式标识。
 * param: data_mode_id - 数据模式标识。
 * return: --
 */
void RangeApplication::set_data_mode_id(const int data_mode_id){
	_data_mode_id=data_mode_id;
}

/**
 * name: get_data_mode_id
 * breif: 获取数据模式标识。
 * param: --
 * return: 返回数据模式标识。
 */
int RangeApplication::get_data_mode_id() const{
	return(_data_mode_id);
}

/**
 * name: set_lower_age_limit
 * breif: 设置年龄下限。
 * param: index - 索引编号。
 *	      lower_age_limit - 年龄下限。
 * return: --
 */
void RangeApplication::set_lower_age_limit(
	const int index,const int lower_age_limit){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_age_limit(lower_age_limit);
}

/**
 * name: get_lower_age_limit
 * breif: 获取年龄下限。
 * param: index - 索引编号。
 * return: 返回年龄下限。
 */
int RangeApplication::get_lower_age_limit(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_age_limit());
}

/**
 * name: set_upper_age_limit
 * breif: 设置年龄上限。
 * param: index - 索引编号。
 *        upper_age_limit - 年龄上限。
 * return: --
 */
void RangeApplication::set_upper_age_limit(
	const int index,const int upper_age_limit){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_age_limit(upper_age_limit);
}

/**
 * name: get_upper_age_limit
 * breif: 获取年龄上限。
 * param: index - 索引编号。
 * return: 返回年龄上限。
 */
int RangeApplication::get_upper_age_limit(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_age_limit());
}

/**
 * name: set_lower_age_unit_id
 * breif: 设置年龄下限的单位标识。
 * param: index - 索引编号。
 *        lower_age_unit_id - 年龄下限的单位标识。
 * return: --
 */
void RangeApplication::set_lower_age_unit_id(
	const int index,const int lower_age_unit_id){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_lower_age_unit_id(lower_age_unit_id);
}

/**
 * name: get_lower_age_unit_id
 * breif: 获取年龄下限的单位标识。
 * param: index - 索引编号。
 * return: 返回年龄下限的单位标识。
 */
int RangeApplication::get_lower_age_unit_id(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_age_unit_id());
}

/**
 * name: set_upper_age_unit_id
 * breif: 设置年龄上限的单位标识。
 * param: index - 索引编号。
 *        upper_age_unit_id - 年龄上限的单位标识。
 * return: --
 */
void RangeApplication::set_upper_age_unit_id(
	const int index,const int upper_age_unit_id){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_upper_age_unit_id(upper_age_unit_id);
}

/**
 * name: get_upper_age_unit_id
 * breif: 获取年龄上限的单位标识。
 * param: index - 索引编号。
 * return: 返回年龄上限的单位标识。
 */
int RangeApplication::get_upper_age_unit_id(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_age_unit_id());
}

/**
 * name: set_lower_limit_of_normal_for_males_1
 * breif: 设置男性正常范围的范围1的下限值。
 * param: index - 索引编号。 
 *        lower_limit_of_normal_for_males_1 - 男性正常范围的范围1的下限值。
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
 * breif: 获取男性正常范围的范围1的下限值。
 * param: index - 索引编号。 
 * return: 返回男性正常范围的范围1的下限值
 */
double RangeApplication::get_lower_limit_of_normal_for_males_1(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_1());
}

/**
 * name: set_upper_limit_of_normal_for_males_1
 * breif: 设置男性正常范围的范围1的上限值。
 * param: index - 索引编号。
 *        upper_limit_of_normal_for_males_1 - 男性正常范围的范围1的上限值。
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
 * breif: 获取男性正常范围的范围1的上限值。
 * param: index - 索引编号。
 * return: 返回男性正常范围的范围1的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_males_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_1());
}

/**
 * name: set_lower_limit_of_normal_for_males_2
 * breif: 设置男性正常范围的范围2的下限值。
 * param: index - 索引编号 
 *        lower_limit_of_normal_for_males_2 - 男性正常范围的范围2的下限值。
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
 * breif: 获取男性正常范围的范围2的下限值。
 * param: index - 索引编号。
 * return: 返回男性正常范围的范围2的下限值。
 */
double RangeApplication::get_lower_limit_of_normal_for_males_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_2());
}

/**
 * name: set_upper_limit_of_normal_for_males_2
 * breif: 设置男性正常范围的范围2的上限值。
 * param: index - 索引编号。 
 *        upper_limit_of_normal_for_males_2 - 男性正常范围的范围2的上限值。
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
 * breif: 获取男性正常范围的范围2的上限值。
 * param: index - 索引编号。 
 * return: 返回男性正常范围的范围2的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_males_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_2());
}

/**
 * name: set_lower_limit_of_normal_for_males_3
 * breif: 设置男性正常范围的范围3的下限值。
 * param: index - 索引编号。 
 *        lower_limit_of_normal_for_males_3 - 男性正常范围的范围3的下限值。
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
 * breif: 获取男性正常范围的范围3的下限值。
 * param: index - 索引编号。
 * return: 返回男性正常范围的范围3的下限值
 */
double RangeApplication::get_lower_limit_of_normal_for_males_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_males_3());
}

/**
 * name: set_upper_limit_of_normal_for_males_3
 * breif: 设置男性正常范围的范围3的上限值。
 * param: index - 索引编号。
 *        upper_limit_of_normal_for_males_3 - 男性正常范围的范围3的上限值。
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
 * breif: 获取男性正常范围的范围3的上限值。
 * param: index - 索引编号。
 * return: 返回男性正常范围的范围3的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_males_3(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_males_3());
}

/**
 * name: set_lower_limit_of_normal_for_females_1
 * breif: 设置女性正常范围的范围1的下限值。
 * param: index - 索引编号。
 *        lower_limit_of_normal_for_females_1 - 女性正常范围的范围1的下限值。
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
 * breif: 获取女性正常范围的范围1的下限值。
 * param: index - 索引编号。
 * return: 返回女性正常范围的范围1的下限值
 */
double RangeApplication::get_lower_limit_of_normal_for_females_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_1());
}

/**
 * name: set_upper_limit_of_normal_for_females_1
 * breif: 设置女性正常范围的范围1的上限值。
 * param: index - 索引编号。 
 *		  upper_limit_of_normal_for_females_1 - 女性正常范围的范围1的上限值。
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
 * breif: 获取女性正常范围的范围1的上限值。
 * param: index - 索引编号。 
 * return: 返回女性正常范围的范围1的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_females_1(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_1());
}

/**
 * name: set_lower_limit_of_normal_for_females_2
 * breif: 设置女性正常范围的范围2的下限值。
 * param: index - 索引编号。
 *        lower_limit_of_normal_for_females_2 - 女性正常范围的范围2的下限值。
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
 * breif: 获取女性正常范围的范围2的下限值。
 * param: index - 索引编号。
 * return: 返回女性正常范围的范围2的下限值
 */
double RangeApplication::get_lower_limit_of_normal_for_females_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_2());
}

/**
 * name: set_upper_limit_of_normal_for_females_2
 * breif: 设置女性正常范围的范围2的上限值。
 * param: index - 索引编号。
 *		  upper_limit_of_normal_for_females_2 - 女性正常范围的范围2的上限值。
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
 * breif: 获取女性正常范围的范围2的上限值。
 * param: index - 索引编号。
 * return: 返回女性正常范围的范围2的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_females_2(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_2());
}

/**
 * name: set_lower_limit_of_normal_for_females_3
 * breif: 设置女性正常范围的范围3的下限值。
 * param: index - 索引编号。
 *        lower_limit_of_normal_for_females_3 - 女性正常范围的范围3的下限值。
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
 * breif: 获取女性正常范围的范围3的下限值。
 * param: index - 索引编号。
 * return: 返回女性正常范围的范围3的下限值
 */
double RangeApplication::get_lower_limit_of_normal_for_females_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_of_normal_for_females_3());
}

/**
 * name: set_upper_limit_of_normal_for_females_3
 * breif: 设置女性正常范围的范围3的上限值。
 * param: index - 索引编号。
 *        upper_limit_of_normal_for_females_3 - 女性正常范围的范围3的上限值。
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
 * breif: 获取女性正常范围的范围3的上限值。
 * param: index - 索引编号。
 * return: 返回女性正常范围的范围3的上限值
 */
double RangeApplication::get_upper_limit_of_normal_for_females_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_of_normal_for_females_3());
}

/**
 * name: set_default_age
 * brief: 设置默认年龄。
 * param: index - 索引编号。
 *		  default_age - 默认年龄。
 * return: --
 */
void RangeApplication::set_default_age(
	const int index,const int default_age){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_default_age(default_age);
}

/**
 * name: get_default_age
 * breif: 获取默认年龄。
 * param: index - 索引编号。
 * return: 返回默认年龄。
 */
int RangeApplication::get_default_age(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_default_age());
}

/**
 * name: set_default_sex
 * brief: 设置默认性别。
 * param: index - 索引编号。 
 *		  default_sex - 默认性别。
 * return: --
 */
void RangeApplication::set_default_sex(
	const int index,const int default_sex){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_default_sex(default_sex);
}

/**
 * name: get_default_sex
 * breif: 获取默认性别。
 * param: index - 索引编号。
 * return: 返回默认性别。
 */
int RangeApplication::get_default_sex(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_default_sex());
}

/**
 * name: set_lower_limit_for_repeat_range
 * breif: 设置标准复查范围的下限。
 * param: index - 索引编号。
 *	      lower_limit_for_repeat_range - 标准复查范围的下限。
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
 * breif: 获取标准复查范围的下限。
 * param: index - 索引编号。
 * return: 返回标准复查范围的下限。
 */
double RangeApplication::get_lower_limit_for_repeat_range(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_lower_limit_for_repeat_range());
}

/**
 * name: set_upper_limit_for_repeat_range
 * breif: 设置标准复查范围的上限。
 * param: index - 索引编号。
 *		  upper_limit_for_repeat_range - 标准复查范围的上限。
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
 * breif: 获取标准复查范围的上限。
 * param: index - 索引编号。
 * return: 返回标准复查范围的上限。
 */
double RangeApplication::get_upper_limit_for_repeat_range(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_upper_limit_for_repeat_range());
}

/**
 * name: set_is_use_qualitative_table
 * breif: 设置是否使用定性表。
 * param: index - 索引编号。
 *        is_use_qualitative_table - 是否使用定性表（0 不使用，1 使用）。
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
 * breif: 获取是否使用定性表。
 * param: index - 索引编号。
 * return: 返回是否使用定性表。
 */
int RangeApplication::get_is_use_qualitative_table(const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_is_use_qualitative_table());
}

/**
 * name: set_qualitative_limit_1
 * breif: 设置定性界限1。
 * param: index - 索引编号。
 *		  qualitative_limit_1 - 定性界限1。
 * return: --
 */
void RangeApplication::set_qualitative_limit_1(
	const int index,const double qualitative_limit_1){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_1(qualitative_limit_1);
}

/**
 * name: get_qualitative_limit_1
 * breif: 获取定性界限1。
 * param: index - 索引编号。
 * return: 返回定性界限1。
 */
double RangeApplication::get_qualitative_limit_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_1());
}

/**
 * name: set_qualitative_limit_text_1
 * brief: 设置定性界限描述字符串1。
 * param: index - 索引编号。
 *		  qualitative_limit_text_1 - 定性界限描述字符串1。
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
 * brief: 获取定性界限描述字符串1。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串1。
 */
const CString &RangeApplication::get_qualitative_limit_text_1(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_1());
}

/**
 * name: set_qualitative_limit_2
 * breif: 设置定性界限2。
 * param: index - 索引编号。
 *	      qualitative_limit_2 - 定性界限2。
 * return: --
 */
void RangeApplication::set_qualitative_limit_2(
	const int index,const double qualitative_limit_2){
	assert((index>=0)&&(index<MAX_RANGES));
	_ranges[index].set_qualitative_limit_2(qualitative_limit_2);
}

/**
 * name: get_qualitative_limit_2
 * breif: 获取定性界限2。
 * param: index - 索引编号。
 * return: 返回定性界限2。
 */
double RangeApplication::get_qualitative_limit_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_2());
}

/**
 * name: set_qualitative_limit_text_2
 * brief: 设置定性界限描述字符串2。
 * param: index - 索引编号。
 *		  qualitative_limit_text_2 - 定性界限描述字符串2。
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
 * brief: 获取定性界限描述字符串2。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串2。
 */
const CString &RangeApplication::get_qualitative_limit_text_2(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_2());
}

/**
 * name: set_qualitative_limit_3
 * breif: 设置定性界限3。
 * param: index - 索引编号。
 *		  qualitative_limit_3 - 定性界限3。
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
 * breif: 获取定性界限3。
 * param: index - 索引编号。
 * return: 返回定性界限3。
 */
double RangeApplication::get_qualitative_limit_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_3());
}

/**
 * name: set_qualitative_limit_text_3
 * brief: 设置定性界限描述字符串3。
 * param: index - 索引编号。
 *		  qualitative_limit_text_3 - 定性界限描述字符串3。
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
 * brief: 获取定性界限描述字符串3。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串3。
 */
const CString &RangeApplication::get_qualitative_limit_text_3(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_3());
}

/**
 * name: set_qualitative_limit_4
 * breif: 设置定性界限4。
 * param: index - 索引编号。
 *		  qualitative_limit_4 - 定性界限4。
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
 * breif: 获取定性界限4。
 * param: index - 索引编号。
 * return: 返回定性界限4。
 */
double RangeApplication::get_qualitative_limit_4(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_4());
}

/**
 * name: set_qualitative_limit_text_4
 * brief: 设置定性界限描述字符串4。
 * param: index - 索引编号。
 *        qualitative_limit_text_4 - 定性界限描述字符串4。
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
 * brief: 获取定性界限描述字符串4。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串4。
 */
const CString &RangeApplication::get_qualitative_limit_text_4(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_4());
}

/**
 * name: set_qualitative_limit_5
 * breif: 设置定性界限5。
 * param: index - 索引编号。
 *		  qualitative_limit_5 - 定性界限5。
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
 * breif: 获取定性界限5。
 * param: index - 索引编号。
 * return: 返回定性界限5。
 */
double RangeApplication::get_qualitative_limit_5(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_5());
}

/**
 * name: set_qualitative_limit_text_5
 * brief: 设置定性界限描述字符串5。
 * param: index - 索引编号。
 *        qualitative_limit_text_5 - 定性界限描述字符串5。
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
 * brief: 获取定性界限描述字符串5。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串5。
 */
const CString &RangeApplication::get_qualitative_limit_text_5(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_5());
}

/**
 * name: set_qualitative_limit_text_6
 * brief: 设置定性界限描述字符串6。
 * param: index - 索引编号。
 *		  qualitative_limit_text_6 - 定性界限描述字符串6。
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
 * brief: 获取定性界限描述字符串6。
 * param: index - 索引编号。
 * return: 返回定性界限描述字符串6。
 */
const CString &RangeApplication::get_qualitative_limit_text_6(
	const int index) const{
	assert((index>=0)&&(index<MAX_RANGES));
	return(_ranges[index].get_qualitative_limit_text_6());
}

/**
 * name: set_lower_limit_for_technical_range_for_class_1
 * breif: 设置样本类型为类型1的复查范围下限。
 * param: lower_limit_for_technical_range_for_class_1 - 样本类型为类型1的复查范围下限。
 * return: --
 */
void RangeApplication::set_lower_limit_for_technical_range_for_class_1(
	const double lower_limit_for_technical_range_for_class_1){
	_lower_limit_for_technical_range_for_class_1=
		lower_limit_for_technical_range_for_class_1;
}

/**
 * name: get_lower_limit_for_technical_range_for_class_1
 * breif: 获取样本类型为类型1的复查范围下限。
 * param: --
 * return: 返回样本类型为类型1的复查范围下限。
 */
double RangeApplication::get_lower_limit_for_technical_range_for_class_1() const{
	return(_lower_limit_for_technical_range_for_class_1);
}

/**
 * name: set_upper_limit_for_technical_range_for_class_1
 * breif: 设置样本类型为类型1的复查范围上限。
 * param: upper_limit_for_technical_range_for_class_1 - 样本类型为类型1的复查范围上限。
 * return: --
 */
void RangeApplication::set_upper_limit_for_technical_range_for_class_1(
	const double upper_limit_for_technical_range_for_class_1){
	_upper_limit_for_technical_range_for_class_1=
		upper_limit_for_technical_range_for_class_1;
}

/**
 * name: get_upper_limit_for_technical_range_for_class_1
 * breif: 获取样本类型为类型1的复查范围上限。
 * param: --
 * return: 返回样本类型为类型1的复查范围上限。
 */
double RangeApplication::get_upper_limit_for_technical_range_for_class_1() const{
	return(_upper_limit_for_technical_range_for_class_1);
}

/**
 * name: set_lower_limit_for_technical_range_for_class_2
 * breif: 设置样本类型为类型2的复查范围下限。
 * param: lower_limit_for_technical_range_for_class_2 - 样本类型为类型2的复查范围下限。
 * return: --
 */
void RangeApplication::set_lower_limit_for_technical_range_for_class_2(
	const double lower_limit_for_technical_range_for_class_2){
	_lower_limit_for_technical_range_for_class_2=
		lower_limit_for_technical_range_for_class_2;
}

/**
 * name: get_lower_limit_for_technical_range_for_class_2
 * breif: 获取样本类型为类型2的复查范围下限。
 * param: --
 * return: 返回样本类型为类型2的复查范围下限。
 */
double RangeApplication::get_lower_limit_for_technical_range_for_class_2() const{
	return(_lower_limit_for_technical_range_for_class_2);
}

/**
 * name: set_upper_limit_for_technical_range_for_class_2
 * breif: 设置样本类型为类型2的复查范围上限。
 * param: upper_limit_for_technical_range_for_class_2 - 样本类型为类型2的复查范围上限。
 * return: --
 */
void RangeApplication::set_upper_limit_for_technical_range_for_class_2(
	const double upper_limit_for_technical_range_for_class_2){
	_upper_limit_for_technical_range_for_class_2=
		upper_limit_for_technical_range_for_class_2;
}

/**
 * name: get_upper_limit_for_technical_range_for_class_2
 * breif: 获取样本类型为类型2的复查范围上限。
 * param: --
 * return: 返回样本类型为类型2的复查范围上限。
 */
double RangeApplication::get_upper_limit_for_technical_range_for_class_2() const{
	return(_upper_limit_for_technical_range_for_class_2);
}

/**
 * name: operator=
 * breif: 重载==操作符。
 * param: source - 拷贝源。
 * return: 返回自身引用。
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
 * brief: 判断当前分析申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前分析申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int RangeApplication::is_valid(CString *error_message/*=0*/) const{
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.检测当前报告名称是否合法。
	//3.检测当前质控间隔是否合法。
	if((-1!=_control_interval)&&((_control_interval<10)||(
		_control_interval>1000))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING363),10,1000);
		}
		return(-1);
	}
	//4.检测当前单位标识是否合法。
	if(_unit_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING364));
		}
		return(-2);
	}
	//5.检测当前设备系数a是否合法。
	if((_instrument_factor_a<(-99999.0))||(_instrument_factor_a>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING365),-99999.0,999999.0);
		}
		return(-3);
	}
	//6.检测当前设备系数b是否合法。
	if((_instrument_factor_b<(-99999.0))||(_instrument_factor_b>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING366),-99999.0,999999.0);
		}
		return(-4);
	}
	//7.检测当前数据模式是否合法。
	if(_data_mode_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING367));
		}
		return(-5);
	}
	//8.检测当前各个样本类型的范围参数是否合法。
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		//8-1.检测当前各个样本类型的范围参数。
		const int result=_ranges[index].is_valid(error_message);
		//8-2.如果当前各个样本类型的范围参数非法。
		if(result<0){
			return(result);
		}
	}
	//9.检测当前样本类型为类型1的增减量复查范围下限是否合法。
	if((_lower_limit_for_technical_range_for_class_1<-99999.0)||
		(_lower_limit_for_technical_range_for_class_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING387),
				-99999.0,999999.0);
		}
		return(-44);
	}
	//10.检测当前样本类型为类型1的增减量复查范围上限是否合法。
	if((_upper_limit_for_technical_range_for_class_1<-99999.0)||
		(_upper_limit_for_technical_range_for_class_1>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING388),
				-99999.0,999999.0);
		}
		return(-45);
	}
	//11.检测当前样本类型为类型2的增减量复查范围下限是否合法。
	if((_lower_limit_for_technical_range_for_class_2<-99999.0)||
		(_lower_limit_for_technical_range_for_class_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING389),
				-99999.0,999999.0);
		}
		return(-46);
	}
	//12.检测当前样本类型为类型2的增减量复查范围上限是否合法。
	if((_upper_limit_for_technical_range_for_class_2<-99999.0)||
		(_upper_limit_for_technical_range_for_class_2>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING390),
				-99999.0,999999.0);
		}
		return(-47);
	}
	//13.检测样本类型为类型1的增减量复查范围下限是否大于等于样本类型为类型1的增减量复查范围上限。
	if((_lower_limit_for_technical_range_for_class_1>=
		_upper_limit_for_technical_range_for_class_1)||
		(is_zero(_lower_limit_for_technical_range_for_class_1-
		_upper_limit_for_technical_range_for_class_1))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING391));
		}
		return(-48);
	}
	//14.检测样本类型为类型2的增减量复查范围下限是否大于等于样本类型为类型2的增减量复查范围上限。
	if((_lower_limit_for_technical_range_for_class_2>=
		_upper_limit_for_technical_range_for_class_2)||
		(is_zero(_lower_limit_for_technical_range_for_class_2-
		_upper_limit_for_technical_range_for_class_2))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING392));
		}
		return(-49);
	}
	//15.程序运行到此成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * brief: 将当前范围申请参数重置为默认值。
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
 * brief: 将当前的项目信息提交的数据库中。
 * param: item_id - 对应的项目标识。
 *        method - 提交到数据库的方法（1 插入 2 更新）。
 *        database - 准备提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int RangeApplication::commit(const int item_id,const int method,Database &database) const{
	//1.判断当前传递的项目标识是否合法。
	if((item_id<1)||(item_id>999)){
		return(-1);
	}
	//2.向数据库提交前需要检测当前范围信息是否合法。
	if(is_valid()<0){
		return(-2);
	}
	//3.如果当前期望以插入的方式将数据提交到数据库中。
	if(1==method){
		//3-1.利用当前范围参数形成提交数据库的SQL语句。
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
		//3-2.执行SQL语句将当前项目信息提交到数据库中。
		if(database.execute(sql)<0){
			return(-4);
		}
		//3-3.程序运行到此成功返回。
		return(0);
	}
	//4.如果当前期望以更新的方式将数据提交到数据库中。
	else if(2==method){
		//4-1.利用当前范围参数形成提交数据库的SQL语句。
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
		//4-2.执行SQL语句将当前项目信息提交到数据库中。
		if(database.execute(sql)<0){
			return(-6);
		}
		//4-3.程序运行到此成功返回。
		return(0);
	}	
	//5.如果当前期望以其它方式将数据提交到数据库中。
	else{
		return(-7);
	}
}

/**
 * name: update
 * breif: 从指定的记录集中更新当前的范围信息。
 * param: record - 指定的记录集。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int RangeApplication::update(MtADORecordset &record){
	//1.声明当前操作所需变量。
	RangeApplication range;
	_variant_t value;
	long record_index=86;
	//2.从指定的记录集中获取报告名称。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	range._report_name=MtADODataConverter::to_string(value);
	//3.从指定的记录集中获取质控间隔。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	range._control_interval=MtADODataConverter::to_int(value);
	//4.从指定的记录集中获取单位信息。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	if(VT_NULL==value.vt){
		range._unit_id=0;
	}else{
		range._unit_id=MtADODataConverter::to_int(value);
	}
	//5.从指定的记录集中获取设备系数a。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	range._instrument_factor_a=MtADODataConverter::to_double(value);
	//6.从指定的记录集中获取设备系数b。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	range._instrument_factor_b=MtADODataConverter::to_double(value);
	//7.从指定的记录集中获取数据模式。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	range._data_mode_id=MtADODataConverter::to_int(value);
	//8.遍历范围素组，获取范围数组中的数据。
	for(unsigned int index=0;index!=MAX_RANGES;++index){
		if((range._ranges[index]).update(record_index,record)<0){
			return(-7);
		}
	}
	//9.从指定的记录集中获取样本类型为类型1的增、减复查范围下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	range._lower_limit_for_technical_range_for_class_1=MtADODataConverter::to_double(value);
	//10.从指定的记录集中获取样本类型为类型1的增、减复查范围上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	range._upper_limit_for_technical_range_for_class_1=MtADODataConverter::to_double(value);
	//11.从指定的记录集中获取样本类型为类型1的增、减复查范围下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	range._lower_limit_for_technical_range_for_class_2=MtADODataConverter::to_double(value);
	//12.从指定的记录集中获取样本类型为类型1的增、减复查范围上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(record_index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	range._upper_limit_for_technical_range_for_class_2=MtADODataConverter::to_double(value);
	//13.如果当前获取的范围信息不合法，则直接返回错误。
	if(range.is_valid()<0){
		return(-12);
	}
	//14.保存当前的从记录集中获取的范围信息。
	(*this)=range;
	//15.程序运行到此成功返回。
	return(0);
}