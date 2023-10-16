#include"stdafx.h"
#include"CalibrationApplication.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../data/DataCustom.h"

/**
 * name: CalibrationApplication
 * brief: 构造函数。
 * param: --
 * return: --
 */
CalibrationApplication::CalibrationApplication(void)
	:_calibration_method_id(0)
	,_calibration_method_item_id(0)
	,_point(0)
	,_span_point(0)
	,_weight(0)
	,_blank_time_out(0)
	,_span_time_out(0)
	,_2_point_time_out(0)
	,_full_time_out(0)
	,_lot_no_change_over_calibration_type_id(0)
	,_bottle_change_over_calibration_type_id(0)
	,_sd_limit(0.0)
	,_duplicate_limit_percent(0)
	,_duplicate_limit_abs(0)
	,_sensitivity_range_lower_limit(0.0)
	,_sensitivity_range_upper_limit(0.0)
	,_s1_abs_range_lower_limit(0)
	,_s1_abs_range_upper_limit(0){
}

/**
 * name: ~CalibrationApplication
 * brief: 析构函数。
 * param: --
 * return: --
 */
CalibrationApplication::~CalibrationApplication(void){
}

/**
 * name: set_calibration_method_id
 * brief: 设置效准方法标识。
 * param: calibration_method_id - 效准方法标识。
 * return: --
 */
void CalibrationApplication::set_calibration_method_id(
	const int calibration_method_id){
	_calibration_method_id=calibration_method_id;
}

/**
 * name: get_calibration_method_id
 * brief: 获取效准方法标识。
 * param: --
 * return: 返回效准方法标识。
 */
int CalibrationApplication::get_calibration_method_id() const{
	return(_calibration_method_id);
}

/**
 * name: set_calibration_method_item_id
 * brief: 设置效准方法附属项目标识。
 * param: calibration_method_item_id - 效准方法附属项目标识。
 * return: --
 */
void CalibrationApplication::set_calibration_method_item_id(
	const int calibration_method_item_id){
	_calibration_method_item_id=calibration_method_item_id;
}

/**
 * name: get_calibration_method_item_id
 * brief: 获取效准方法附属项目标识。
 * param: --
 * return: 返回效准方法附属项目标识。
 */
int CalibrationApplication::get_calibration_method_item_id() const{
	return(_calibration_method_item_id);
}

/**
 * name: set_point
 * brief: 设置效准点个数。
 * param: point - 效准点个数。
 * return: --
 */
void CalibrationApplication::set_point(const int point){
	_point=point;
}

/**
 * name: get_point
 * brief: 获取效准点个数。
 * param: --
 * return: 返回效准点个数。
 */
int CalibrationApplication::get_point() const{
	return(_point);
}

/**
 * name: set_span_point
 * brief: 设置量程点。
 * param: span_point - 量程点。
 * return: --
 */
void CalibrationApplication::set_span_point(const int span_point){
	_span_point=span_point;
}

/**
 * name: get_span_point
 * brief: 获取量程点。
 * param: --
 * return: 返回量程点。
 */
int CalibrationApplication::get_span_point() const{
	return(_span_point);
}

/**
 * name: set_weight
 * brief: 设置权重。
 * param: weight - 权重。
 * return: --
 */
void CalibrationApplication::set_weight(const int weight){
	_weight=weight;
}

/**
 * name: get_weight
 * brief: 获取权重。
 * param: --
 * return: 返回权重。
 */
int CalibrationApplication::get_weight() const{
	return(_weight);
}

/**
 * name: set_blank_time_out
 * brief: 设置空白效准超时。
 * param: blank_time_out - 空白效准超时。
 * return: --
 */
void CalibrationApplication::set_blank_time_out(const int blank_time_out){
	_blank_time_out=blank_time_out;
}

/**
 * name: get_blank_time_out
 * brief: 获取空白效准超时。
 * param: --
 * return: 返回空白效准超时。
 */
int CalibrationApplication::get_blank_time_out() const{
	return(_blank_time_out);
}

/**
 * name: set_span_time_out
 * brief: 设置量程效准超时。
 * param: span_time_out - 量程效准超时。
 * return: --
 */
void CalibrationApplication::set_span_time_out(const int span_time_out){
	_span_time_out=span_time_out;
}

/**
 * name: get_span_time_out
 * brief: 获取量程效准超时。
 * param: --
 * return: 返回量程效准超时。
 */
int CalibrationApplication::get_span_time_out() const{
	return(_span_time_out);
}

/**
 * name: set_2_point_time_out
 * brief: 设置两点效准超时。
 * param: two_point_time_out - 两点效准超时。
 * return: --
 */
void CalibrationApplication::set_2_point_time_out(const int two_point_time_out){
	_2_point_time_out=two_point_time_out;
}

/**
 * name: get_2_point_time_out
 * brief: 获取两点效准超时。
 * param: --
 * return: 返回两点效准超时。
 */
int CalibrationApplication::get_2_point_time_out() const{
	return(_2_point_time_out);
}

/**
 * name: set_full_time_out
 * brief: 设置全点效准超时。
 * param: full_time_out - 全点效准超时。
 * return: --
 */
void CalibrationApplication::set_full_time_out(const int full_time_out){
	_full_time_out=full_time_out;
}

/**
 * name: get_full_time_out
 * brief: 获取全点效准超时。
 * param: --
 * return: 返回全点效准超时。
 */
int CalibrationApplication::get_full_time_out() const{
	return(_full_time_out);
}

/**
 * name: set_lot_no_change_over_calibration_type_id
 * brief: 设置批号改变定标类型标识。
 * param: lot_no_change_over_calibration_type_id - 批号改变定标类型标识。
 * return: --
 */
void CalibrationApplication::set_lot_no_change_over_calibration_type_id(
	const int lot_no_change_over_calibration_type_id){
	_lot_no_change_over_calibration_type_id=lot_no_change_over_calibration_type_id;
}

/**
 * name: get_lot_no_change_over_calibration_type_id
 * brief: 获取批号改变定标类型标识。
 * param: --
 * return: 返回批号改变定标类型标识。
 */
int CalibrationApplication::get_lot_no_change_over_calibration_type_id() const{
	return(_lot_no_change_over_calibration_type_id);
}

/**
 * name: set_bottle_change_over_calibration_type_id
 * brief: 设置瓶子改变定标类型标识。
 * param: bottle_change_over_calibration_type_id - 瓶子改变定标类型标识。
 * return: --
 */
void CalibrationApplication::set_bottle_change_over_calibration_type_id(
	const int bottle_change_over_calibration_type_id){
	_bottle_change_over_calibration_type_id=bottle_change_over_calibration_type_id;
}

/**
 * name: get_bottle_change_over_calibration_type_id
 * brief: 获取瓶子改变定标类型标识。
 * param: --
 * return: 返回瓶子改变定标类型标识。
 */
int CalibrationApplication::get_bottle_change_over_calibration_type_id() const{
	return(_bottle_change_over_calibration_type_id);
}

/**
 * name: set_sd_limit
 * brief: 设置SD值界限。
 * param: sd_limit - SD值界限。
 * return: --
 */
void CalibrationApplication::set_sd_limit(const double sd_limit){
	_sd_limit=sd_limit;
}

/**
 * name: get_sd_limit
 * brief: 获取SD值界限。
 * param: --
 * return: 返回SD值界限。
 */
double CalibrationApplication::get_sd_limit() const{
	return(_sd_limit);
}

/**
 * name: set_duplicate_limit_percent
 * brief: 设置参差百分比。
 * param: duplicate_limit_percent - 参差百分比。
 * return: --
 */
void CalibrationApplication::set_duplicate_limit_percent(
	const int duplicate_limit_percent){
	_duplicate_limit_percent=duplicate_limit_percent;
}

/**
 * name: get_duplicate_limit_percent
 * brief: 获取参差百分比。
 * param: --
 * return: 返回参差百分比。
 */
int CalibrationApplication::get_duplicate_limit_percent() const{
	return(_duplicate_limit_percent);
}

/**
 * name: set_duplicate_limit_abs
 * brief: 设置参差吸光度。
 * param: duplicate_limit_abs - 参差吸光度。
 * return: --
 */
void CalibrationApplication::set_duplicate_limit_abs(
	const int duplicate_limit_abs){
	_duplicate_limit_abs=duplicate_limit_abs;
}

/**
 * name: get_duplicate_limit_abs
 * brief: 获取参差吸光度。
 * param: --
 * return: 返回参差吸光度。
 */
int CalibrationApplication::get_duplicate_limit_abs() const{
	return(_duplicate_limit_abs);
}

/**
 * name: set_sensitivity_range_lower_limit
 * brief: 设置灵敏度范围下限。
 * param: sensitivity_range_lower_limit - 灵敏度范围下限。
 * return: --
 */
void CalibrationApplication::set_sensitivity_range_lower_limit(
	const double sensitivity_range_lower_limit){
	_sensitivity_range_lower_limit=sensitivity_range_lower_limit;
}

/**
 * name: get_sensitivity_range_lower_limit
 * brief: 获取灵敏度范围下限。
 * param: --
 * return: 返回灵敏度范围下限。
 */
double CalibrationApplication::get_sensitivity_range_lower_limit() const{
	return(_sensitivity_range_lower_limit);
}

/**
 * name: set_sensitivity_range_upper_limit
 * brief: 设置灵敏度范围上限。
 * param: sensitivity_range_upper_limit - 灵敏度范围上限。
 * return: --
 */
void CalibrationApplication::set_sensitivity_range_upper_limit(
	const double sensitivity_range_upper_limit){
	_sensitivity_range_upper_limit=sensitivity_range_upper_limit;
}

/**
 * name: get_sensitivity_range_upper_limit
 * brief: 获取灵敏度范围上限。
 * param: --
 * return: 返回灵敏度范围上限。
 */
double CalibrationApplication::get_sensitivity_range_upper_limit() const{
	return(_sensitivity_range_upper_limit);
}

/**
 * name: set_s1_abs_range_lower_limit
 * brief: 设置空白吸光度下限。
 * param: s1_abs_range_lower_limit - 空白吸光度下限。
 * return: --
 */
void CalibrationApplication::set_s1_abs_range_lower_limit(
	const int s1_abs_range_lower_limit){
	_s1_abs_range_lower_limit=s1_abs_range_lower_limit;
}

/**
 * name: get_s1_abs_range_lower_limit
 * brief: 获取空白吸光度下限。
 * param: --
 * return: 返回空白吸光度下限。
 */
int CalibrationApplication::get_s1_abs_range_lower_limit() const{
	return(_s1_abs_range_lower_limit);
}

/**
 * name: set_s1_abs_range_upper_limit
 * brief: 设置空白吸光度上限。
 * param: s1_abs_range_upper_limit - 空白吸光度上限。
 * return: --
 */
void CalibrationApplication::set_s1_abs_range_upper_limit(
	const int s1_abs_range_upper_limit){
	_s1_abs_range_upper_limit=s1_abs_range_upper_limit;
}

/**
 * name: get_s1_abs_range_upper_limit
 * brief: 获取空白吸光度上限。
 * param: --
 * return: 返回空白吸光度上限。
 */
int CalibrationApplication::get_s1_abs_range_upper_limit() const{
	return(_s1_abs_range_upper_limit);
}

/**
 * name: is_valid
 * brief: 判断当前分析申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前分析申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int CalibrationApplication::is_valid(CString *error_message/*=0*/) const{
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.如果用户选择的定标类型不合法。
	if(_calibration_method_id<=0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING320));
		}
		return(-1);
	}
	//3.如果用户选择的定标附属项目不合法。
	if(_calibration_method_item_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING321));
		}
		return(-2);
	}
	//4.如果用户输入的定标点不合法。
	if((_point<1)||(_point>6)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING322),1,6);
		}
		return(-3);
	}
	//5.如果用户输入的量程点不合法。
	if((0!=_span_point)&&((_span_point<2)||(_span_point>6))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING323),0,2,6);
		}
		return(-4);
	}
	//6.如果用户输入的权重不合法。
	if((_weight<0)||(_weight>2)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING324),0,2);
		}
		return(-5);
	}
	//7.如果用户输入的空白效准超时时间不合法。
	if((-1!=_blank_time_out)&&((_blank_time_out<1)||(_blank_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING325),1,999);
		}
		return(-6);
	}
	//8.如果用户输入的量程效准超时时间不合法。
	if((-1!=_span_time_out)&&((_span_time_out<1)||(_span_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING326),1,999);
		}
		return(-7);
	}
	//9.如果用户输入的2点效准超时时间不合法。
	if((-1!=_2_point_time_out)&&((_2_point_time_out<1)||(_2_point_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING327),1,999);
		}
		return(-8);
	}
	//10.如果用户输入的全点效准超时时间不合法。
	if((-1!=_full_time_out)&&((_full_time_out<1)||(_full_time_out>999))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING328),1,999);
		}
		return(-9);
	}
	//11.如果选择的试剂批号改变的效准方法不合法。
	if(_lot_no_change_over_calibration_type_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING329));
		}
		return(-10);
	}
	//12.如果选择的试剂瓶号改变的效准方法不合法。
	if(_bottle_change_over_calibration_type_id<0){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING330));
		}
		return(-11);
	}
	//13.如果输入的SD检查的值不合法。
	if((_sd_limit<0.1)||(_sd_limit>999.9)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING331),0.1,999.9);
		}
		return(-12);
	}
	//14.如果输入的参差检查的百分比不合法。
	if((_duplicate_limit_percent<0)||(_duplicate_limit_percent>99)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING332),0,99);
		}
		return(-13);
	}
	//15.如果输入的参差检查的吸光度不合法。
	if((_duplicate_limit_abs<0)||(_duplicate_limit_abs>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING333),0,32000);
		}
		return(-14);
	}
	//16.如果输入的灵敏度检查的下限不合法。
	if((_sensitivity_range_lower_limit<-99999.0)||(
		_sensitivity_range_lower_limit>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING334),-99999.0,999999.0);
		}
		return(-15);
	}
	//17.如果输入的灵敏度检查的上限不合法。
	if((_sensitivity_range_upper_limit<-99999.0)||(
		_sensitivity_range_upper_limit>999999.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING335),-99999.0,999999.0);
		}
		return(-16);
	}
	//18.如果输入的空白吸光度检查的下限不合法。
	if((_s1_abs_range_lower_limit<-32000)||(_s1_abs_range_lower_limit>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING336),-32000,32000);
		}
		return(-17);
	}
	//19.如果输入的空白吸光度检查的上限不合法。
	if((_s1_abs_range_upper_limit<-32000)||(_s1_abs_range_upper_limit>32000)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING337),-32000,32000);
		}
		return(-18);
	}
	//20.如果灵敏度检查的下限大于灵敏度检查的上限。
	if((_sensitivity_range_lower_limit>=_sensitivity_range_upper_limit)||
		is_zero(_sensitivity_range_lower_limit-_sensitivity_range_upper_limit)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING338));
		}
		return(-19);
	}
	//21.如果空白吸光度检查的下限大于空白吸光度检查的上限。
	if(_s1_abs_range_lower_limit>=_s1_abs_range_upper_limit){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING339));
		}
		return(-20);
	}
	//22.程序运行到此成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * brief: 将当前效准申请参数重置为默认值。
 * param: --
 * return: --
 */
void CalibrationApplication::reset_default_value(){
	_calibration_method_id=1;
	_calibration_method_item_id=0;
	_point=1;
	_span_point=0;
	_weight=0;
	_blank_time_out=-1;
	_span_time_out=-1;
	_2_point_time_out=-1;
	_full_time_out=-1;
	_lot_no_change_over_calibration_type_id=0;
	_bottle_change_over_calibration_type_id=0;
	_sd_limit=999.9;
	_duplicate_limit_percent=99;
	_duplicate_limit_abs=32000;
	_sensitivity_range_lower_limit=-99999.0;
	_sensitivity_range_upper_limit=999999.0;
	_s1_abs_range_lower_limit=-32000;
	_s1_abs_range_upper_limit=32000;
}

/**
 * name: commit
 * brief: 将当前的项目信息提交的数据库中。
 * param: item_id - 对应的项目标识。
 *        method - 提交到数据库的方法（1 插入 2 更新）。
 *        database - 准备提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationApplication::commit(
	const int item_id,const int method,Database &database) const{
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
		CString calibration_method_item_id(_T(""));
		if(0==_calibration_method_item_id){
			calibration_method_item_id=_T("null");
		}else{
			calibration_method_item_id.Format(_T("'%d'"),_calibration_method_item_id);
		}
		CString lot_no_change_over_calibration_type_id(_T(""));
		if(0==_lot_no_change_over_calibration_type_id){
			lot_no_change_over_calibration_type_id=_T("null");
		}else{
			lot_no_change_over_calibration_type_id.Format(_T("'%d'"),
				_lot_no_change_over_calibration_type_id);
		}
		CString bottle_change_over_calibration_type_id(_T(""));
		if(0==_bottle_change_over_calibration_type_id){
			bottle_change_over_calibration_type_id=_T("null");
		}else{
			bottle_change_over_calibration_type_id.Format(_T("'%d'"),
				_bottle_change_over_calibration_type_id);
		}
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [calibration_application]([item_id],[calibration_method_id],\
					  [calibration_method_item_id],[points],[span_point],[weight],[blank_time_out],\
					  [span_time_out],[2_point_time_out],[full_time_out],[lot_no_change_over_calibration_type_id],\
					  [bottle_change_over_calibration_type_id],[sd_limit],[duplicate_limit_percent],\
					  [duplicate_limit_abs],[sensitivity_range_lower_limit],[sensitivity_range_upper_limit],\
					  [s1_abs_range_lower_limit],[s1_abs_range_upper_limit])VALUES('%d','%d',%s,'%d','%d','%d',\
					  '%d','%d','%d','%d',%s,%s,'%lf','%d','%d','%lf','%lf','%d','%d')"),
					  item_id,_calibration_method_id,calibration_method_item_id,_point,_span_point,_weight,
					  _blank_time_out,_span_time_out,_2_point_time_out,_full_time_out,
					  lot_no_change_over_calibration_type_id,bottle_change_over_calibration_type_id,
					  _sd_limit,_duplicate_limit_percent,_duplicate_limit_abs,_sensitivity_range_lower_limit,
					  _sensitivity_range_upper_limit,_s1_abs_range_lower_limit,_s1_abs_range_upper_limit);
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
		CString calibration_method_item_id(_T(""));
		if(0==_calibration_method_item_id){
			calibration_method_item_id=_T("null");
		}else{
			calibration_method_item_id.Format(_T("'%d'"),_calibration_method_item_id);
		}
		CString lot_no_change_over_calibration_type_id(_T(""));
		if(0==_lot_no_change_over_calibration_type_id){
			lot_no_change_over_calibration_type_id=_T("null");
		}else{
			lot_no_change_over_calibration_type_id.Format(_T("'%d'"),
				_lot_no_change_over_calibration_type_id);
		}
		CString bottle_change_over_calibration_type_id(_T(""));
		if(0==_bottle_change_over_calibration_type_id){
			bottle_change_over_calibration_type_id=_T("null");
		}else{
			bottle_change_over_calibration_type_id.Format(_T("'%d'"),
				_bottle_change_over_calibration_type_id);
		}
		CString sql(_T(""));
		sql.Format(_T("UPDATE [calibration_application] SET [calibration_method_id]='%d',\
					  [calibration_method_item_id]=%s,[points]='%d',[span_point]='%d',\
					  [weight]='%d',[blank_time_out]='%d',[span_time_out]='%d',\
					  [2_point_time_out]='%d',[full_time_out]='%d',\
					  [lot_no_change_over_calibration_type_id]=%s,[bottle_change_over_calibration_type_id]=%s,\
					  [sd_limit]='%lf',[duplicate_limit_percent]='%d',[duplicate_limit_abs]='%d',\
					  [sensitivity_range_lower_limit]='%lf',[sensitivity_range_upper_limit]='%lf',\
					  [s1_abs_range_lower_limit]='%d',[s1_abs_range_upper_limit]='%d' WHERE [item_id]='%d'"),
					  _calibration_method_id,calibration_method_item_id,_point,_span_point,
					  _weight,_blank_time_out,_span_time_out,_2_point_time_out,_full_time_out,
					  lot_no_change_over_calibration_type_id,bottle_change_over_calibration_type_id,
					  _sd_limit,_duplicate_limit_percent,_duplicate_limit_abs,_sensitivity_range_lower_limit,
					  _sensitivity_range_upper_limit,_s1_abs_range_lower_limit,_s1_abs_range_upper_limit,item_id);
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
 * breif: 从指定的记录集中更新当前的定标信息。
 * param: record - 指定的记录集。
 * return: 如果函数执行陈宫返回值大于等于零，否则返回值小于零。
 */
int CalibrationApplication::update(MtADORecordset &record){
	//1.声明当前操作所需变量。
	CalibrationApplication calibration;
	_variant_t value;
	//2.从指定的记录集中获取定标方法标识。
	value=record.get_collect(MtADODataConverter::to_variant_t(67));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	calibration._calibration_method_id=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取定标方法附属项目标识。
	value=record.get_collect(MtADODataConverter::to_variant_t(68));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	if(VT_NULL==value.vt){
		calibration._calibration_method_item_id=0;
	}else{
		calibration._calibration_method_item_id=MtADODataConverter::to_int(value);
	}
	//4.从指定的记录集中获取效准点的数量。
	value=record.get_collect(MtADODataConverter::to_variant_t(69));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	calibration._point=MtADODataConverter::to_int(value);
	//5.从指定的记录集中获取量程效准点的个数。
	value=record.get_collect(MtADODataConverter::to_variant_t(70));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	calibration._span_point=MtADODataConverter::to_int(value);
	//6.从指定的记录集中获取效准权重。
	value=record.get_collect(MtADODataConverter::to_variant_t(71));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	calibration._weight=MtADODataConverter::to_int(value);
	//7.从指定的记录集中获取空白效准超时时间。
	value=record.get_collect(MtADODataConverter::to_variant_t(72));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	calibration._blank_time_out=MtADODataConverter::to_int(value);
	//8.从指定的记录集中获取量程效准超时时间。
	value=record.get_collect(MtADODataConverter::to_variant_t(73));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	calibration._span_time_out=MtADODataConverter::to_int(value);
	//9.从指定的记录集中获取两点效准超时时间。
	value=record.get_collect(MtADODataConverter::to_variant_t(74));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	calibration._2_point_time_out=MtADODataConverter::to_int(value);
	//10.从指定的记录集中获取全点效准超时时间。
	value=record.get_collect(MtADODataConverter::to_variant_t(75));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	calibration._full_time_out=MtADODataConverter::to_int(value);
	//11.从指定的记录集中获取批号改变时的效准类型标识。
	value=record.get_collect(MtADODataConverter::to_variant_t(76));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	if(VT_NULL==value.vt){
		calibration._lot_no_change_over_calibration_type_id=0;
	}else{
		calibration._lot_no_change_over_calibration_type_id=MtADODataConverter::to_int(value);
	}
	//12.从指定的记录集中获取瓶子改变时的效准类型标识。
	value=record.get_collect(MtADODataConverter::to_variant_t(77));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	if(VT_NULL==value.vt){
		calibration._bottle_change_over_calibration_type_id=0;
	}else{
		calibration._bottle_change_over_calibration_type_id=MtADODataConverter::to_int(value);
	}
	//13.从指定的记录集中获取SD值界限。
	value=record.get_collect(MtADODataConverter::to_variant_t(78));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	calibration._sd_limit=MtADODataConverter::to_double(value);
	//14.从指定的记录集中获取参差百分比。
	value=record.get_collect(MtADODataConverter::to_variant_t(79));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	calibration._duplicate_limit_percent=MtADODataConverter::to_int(value);
	//15.从指定的记录集中获取参差吸光度。
	value=record.get_collect(MtADODataConverter::to_variant_t(80));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	calibration._duplicate_limit_abs=MtADODataConverter::to_int(value);
	//16.从指定的记录集中获取灵敏度下限值。
	value=record.get_collect(MtADODataConverter::to_variant_t(81));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	calibration._sensitivity_range_lower_limit=MtADODataConverter::to_double(value);
	//17.从指定的记录集中获取灵敏度上限值。
	value=record.get_collect(MtADODataConverter::to_variant_t(82));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	calibration._sensitivity_range_upper_limit=MtADODataConverter::to_double(value);
	//18.从指定的记录集中获取空白吸光度范围下限。
	value=record.get_collect(MtADODataConverter::to_variant_t(83));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	calibration._s1_abs_range_lower_limit=MtADODataConverter::to_int(value);
	//19.从指定的记录集中获取空白吸光度范围上限。
	value=record.get_collect(MtADODataConverter::to_variant_t(84));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	calibration._s1_abs_range_upper_limit=MtADODataConverter::to_int(value);
	//20.如果当前获取的定标信息不合法，则直接返回错误。
	if(calibration.is_valid()<0){
		return(-19);
	}
	//21.保存当前的从记录集中获取的定标信息。
	(*this)=calibration;
	//22.程序运行到此成功返回。
	return(0);
}