#include"stdafx.h"
#include"StandardApplication.h"
#include"../../global/Theme.h"
#include"../../../Resource.h"
#include"../DataCustom.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"

/**
 * name: StandardApplication
 * brief: 标准构造函数。
 * param: --
 * return: --
 */
StandardApplication::StandardApplication(void)
	:_calibrator_code_1(0)
	,_calibrator_code_2(0)
	,_calibrator_code_3(0)
	,_calibrator_code_4(0)
	,_calibrator_code_5(0)
	,_calibrator_code_6(0)
	,_sample_volume_1(0.0)
	,_diluted_sample_volume_1(0.0)
	,_diluent_volume_1(0.0)
	,_sample_volume_2(0.0)
	,_diluted_sample_volume_2(0.0)
	,_diluent_volume_2(0.0)
	,_sample_volume_3(0.0)
	,_diluted_sample_volume_3(0.0)
	,_diluent_volume_3(0.0)
	,_sample_volume_4(0.0)
	,_diluted_sample_volume_4(0.0)
	,_diluent_volume_4(0.0)
	,_sample_volume_5(0.0)
	,_diluted_sample_volume_5(0.0)
	,_diluent_volume_5(0.0)
	,_sample_volume_6(0.0)
	,_diluted_sample_volume_6(0.0)
	,_diluent_volume_6(0.0){
}

/**
 * name: ~StandardApplication
 * brief: 标准析构函数。
 * param: --
 * return: --
 */
StandardApplication::~StandardApplication(void){
}

/**
 * name: set_calibrator_code_1
 * breif: 设置定标液1编号。
 * param: calibrator_code - 定标液1标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_1(const int calibrator_code){
	_calibrator_code_1=calibrator_code;
}

/**
 * name: get_calibrator_code_1
 * breif: 获取定标液1编号。
 * param: --
 * return: 返回定标液1编号。
 */
int StandardApplication::get_calibrator_code_1() const{
	return(_calibrator_code_1);
}

/**
 * name: set_calibrator_code_2
 * breif: 设置定标液2编号。
 * param: calibrator_code - 定标液2标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_2(const int calibrator_code){
	_calibrator_code_2=calibrator_code;
}

/**
 * name: get_calibrator_code_2
 * breif: 获取定标液2编号。
 * param: --
 * return: 返回定标液2编号。
 */
int StandardApplication::get_calibrator_code_2() const{
	return(_calibrator_code_2);
}

/**
 * name: set_calibrator_code_3
 * breif: 设置定标液3编号。
 * param: calibrator_code - 定标液3标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_3(const int calibrator_code){
	_calibrator_code_3=calibrator_code;
}

/**
 * name: get_calibrator_code_3
 * breif: 获取定标液3编号。
 * param: --
 * return: 返回定标液3编号。
 */
int StandardApplication::get_calibrator_code_3() const{
	return(_calibrator_code_3);
}

/**
 * name: set_calibrator_code_4
 * breif: 设置定标液4编号。
 * param: calibrator_code - 定标液4标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_4(const int calibrator_code){
	_calibrator_code_4=calibrator_code;
}

/**
 * name: get_calibrator_code_4
 * breif: 获取定标液4编号。
 * param: --
 * return: 返回定标液4编号。
 */
int StandardApplication::get_calibrator_code_4() const{
	return(_calibrator_code_4);
}

/**
 * name: set_calibrator_code_5
 * breif: 设置定标液5编号。
 * param: calibrator_code - 定标液5标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_5(const int calibrator_code){
	_calibrator_code_5=calibrator_code;
}

/**
 * name: get_calibrator_code_5
 * breif: 获取定标液5编号。
 * param: --
 * return: 返回定标液5编号。
 */
int StandardApplication::get_calibrator_code_5() const{
	return(_calibrator_code_5);
}

/**
 * name: set_calibrator_code_6
 * breif: 设置定标液6编号。
 * param: calibrator_code - 定标液6标号。
 * return: --
 */
void StandardApplication::set_calibrator_code_6(const int calibrator_code){
	_calibrator_code_6=calibrator_code;
}

/**
 * name: get_calibrator_code_6
 * breif: 获取定标液6编号。
 * param: --
 * return: 返回定标液6编号。
 */
int StandardApplication::get_calibrator_code_6() const{
	return(_calibrator_code_6);
}

/**
 * name: set_sample_volume_1
 * breif: 设置吸样本体积1。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_1(const double sample_volume){
	_sample_volume_1=sample_volume;
}

/**
 * name: get_sample_volume_1
 * brief: 获取吸样本体积1。
 * param: --
 * return: 返回吸样本体积1。
 */
double StandardApplication::get_sample_volume_1() const{
	return(_sample_volume_1);
}

/**
 * name: set_diluted_sample_volume_1
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_1(const double diluted_sample_volume){
	_diluted_sample_volume_1=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_1
 * brief: 获取吸稀释后样本体积1。
 * param: --
 * return: 返回吸稀释后样本体积1。
 */
double StandardApplication::get_diluted_sample_volume_1() const{
	return(_diluted_sample_volume_1);
}

/**
 * name: set_diluent_volume_1
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_1(const double diluent_volume){
	_diluent_volume_1=diluent_volume;
}

/**
 * name: get_diluent_volume_1
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_1() const{
	return(_diluent_volume_1);
}

/**
 * name: set_sample_volume_2
 * breif: 设置吸样本体积2。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_2(const double sample_volume){
	_sample_volume_2=sample_volume;
}

/**
 * name: get_sample_volume_2
 * brief: 获取吸样本体积2。
 * param: --
 * return: 返回吸样本体积2。
 */
double StandardApplication::get_sample_volume_2() const{
	return(_sample_volume_2);
}

/**
 * name: set_diluted_sample_volume_2
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_2(const double diluted_sample_volume){
	_diluted_sample_volume_2=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_2
 * brief: 获取吸稀释后样本体积2。
 * param: --
 * return: 返回吸稀释后样本体积2。
 */
double StandardApplication::get_diluted_sample_volume_2() const{
	return(_diluted_sample_volume_2);
}

/**
 * name: set_diluent_volume_2
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_2(const double diluent_volume){
	_diluent_volume_2=diluent_volume;
}

/**
 * name: get_diluent_volume_2
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_2() const{
	return(_diluent_volume_2);
}

/**
 * name: set_sample_volume_3
 * breif: 设置吸样本体积3。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_3(const double sample_volume){
	_sample_volume_3=sample_volume;
}

/**
 * name: get_sample_volume_3
 * brief: 获取吸样本体积3。
 * param: --
 * return: 返回吸样本体积3。
 */
double StandardApplication::get_sample_volume_3() const{
	return(_sample_volume_3);
}

/**
 * name: set_diluted_sample_volume_3
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_3(const double diluted_sample_volume){
	_diluted_sample_volume_3=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_3
 * brief: 获取吸稀释后样本体积3。
 * param: --
 * return: 返回吸稀释后样本体积3。
 */
double StandardApplication::get_diluted_sample_volume_3() const{
	return(_diluted_sample_volume_3);
}

/**
 * name: set_diluent_volume_3
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_3(const double diluent_volume){
	_diluent_volume_3=diluent_volume;
}

/**
 * name: get_diluent_volume_3
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_3() const{
	return(_diluent_volume_3);
}

/**
 * name: set_sample_volume_4
 * breif: 设置吸样本体积4。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_4(const double sample_volume){
	_sample_volume_4=sample_volume;
}

/**
 * name: get_sample_volume_4
 * brief: 获取吸样本体积4。
 * param: --
 * return: 返回吸样本体积4。
 */
double StandardApplication::get_sample_volume_4() const{
	return(_sample_volume_4);
}

/**
 * name: set_diluted_sample_volume_4
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_4(const double diluted_sample_volume){
	_diluted_sample_volume_4=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_4
 * brief: 获取吸稀释后样本体积4。
 * param: --
 * return: 返回吸稀释后样本体积4。
 */
double StandardApplication::get_diluted_sample_volume_4() const{
	return(_diluted_sample_volume_4);
}

/**
 * name: set_diluent_volume_4
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_4(const double diluent_volume){
	_diluent_volume_4=diluent_volume;
}

/**
 * name: get_diluent_volume_4
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_4() const{
	return(_diluent_volume_4);
}

/**
 * name: set_sample_volume_5
 * breif: 设置吸样本体积5。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_5(const double sample_volume){
	_sample_volume_5=sample_volume;
}

/**
 * name: get_sample_volume_5
 * brief: 获取吸样本体积5。
 * param: --
 * return: 返回吸样本体积5。
 */
double StandardApplication::get_sample_volume_5() const{
	return(_sample_volume_5);
}

/**
 * name: set_diluted_sample_volume_5
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_5(const double diluted_sample_volume){
	_diluted_sample_volume_5=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_5
 * brief: 获取吸稀释后样本体积5。
 * param: --
 * return: 返回吸稀释后样本体积5。
 */
double StandardApplication::get_diluted_sample_volume_5() const{
	return(_diluted_sample_volume_5);
}

/**
 * name: set_diluent_volume_5
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_5(const double diluent_volume){
	_diluent_volume_5=diluent_volume;
}

/**
 * name: get_diluent_volume_5
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_5() const{
	return(_diluent_volume_5);
}

/**
 * name: set_sample_volume_6
 * breif: 设置吸样本体积6。
 * param: sample_volume - 吸样本体积。
 * return: --
 */
void StandardApplication::set_sample_volume_6(const double sample_volume){
	_sample_volume_6=sample_volume;
}

/**
 * name: get_sample_volume_6
 * brief: 获取吸样本体积6。
 * param: --
 * return: 返回吸样本体积6。
 */
double StandardApplication::get_sample_volume_6() const{
	return(_sample_volume_6);
}

/**
 * name: set_diluted_sample_volume_6
 * breif: 设置吸稀释后样本体积。
 * param: diluted_sample_volume - 吸稀释后样本体积。
 * return: --
 */
void StandardApplication::set_diluted_sample_volume_6(const double diluted_sample_volume){
	_diluted_sample_volume_6=diluted_sample_volume;
}

/**
 * name: get_diluted_sample_volume_6
 * brief: 获取吸稀释后样本体积6。
 * param: --
 * return: 返回吸稀释后样本体积6。
 */
double StandardApplication::get_diluted_sample_volume_6() const{
	return(_diluted_sample_volume_6);
}

/**
 * name: set_diluent_volume_6
 * brief: 设置吸稀释液体积。
 * param: diluent_volume - 吸稀释液体积。
 * return: --
 */
void StandardApplication::set_diluent_volume_6(const double diluent_volume){
	_diluent_volume_6=diluent_volume;
}

/**
 * name: get_diluent_volume_6
 * brief: 获取吸稀释液体积。
 * param: --
 * return: 返回吸稀释液体积。
 */
double StandardApplication::get_diluent_volume_6() const{
	return(_diluent_volume_6);
}

/**
 * name: is_valid
 * brief: 判断当前标准申请参数是否合法。
 * param: error_message - 指向返回的错误信息的指针（如果为零时，不返回错误信息）。
 * return: 如果当前标准申请参数合法则返回值大于等于零，否则返回值小于零。
 */
int StandardApplication::is_valid(CString *error_message/*=0*/) const{
	//1.声明当前操作所需变量。
	Theme *theme=Theme::instance();
	//2.如果当前标准液编号1不合法。
	if((_calibrator_code_1<0)||(_calibrator_code_1>999)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING432),0,999,999);
		}
		return(-1);
	}
	//3.如果当前标准液标号2不合法。
	if((_calibrator_code_2<0)||(_calibrator_code_2>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING433),0,998);
		}
		return(-2);
	}
	//4.如果当前标准液标号3不合法。
	if((_calibrator_code_3<0)||(_calibrator_code_3>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING434),0,998);
		}
		return(-3);
	}
	//5.如果当前标准液标号4不合法。
	if((_calibrator_code_4<0)||(_calibrator_code_4>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING435),0,998);
		}
		return(-4);
	}
	//6.如果当前标准液标号5不合法。
	if((_calibrator_code_5<0)||(_calibrator_code_5>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING436),0,998);
		}
		return(-5);
	}
	//7.如果当前标准液标号6不合法。
	if((_calibrator_code_6<0)||(_calibrator_code_6>998)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING437),0,998);
		}
		return(-6);
	}
	//8.如果当前吸样本1体积不合法。
	if((_sample_volume_1<1.5)||(_sample_volume_1>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING438),1.5,35.0);
		}
		return(-7);
	}
	//9.如果当前吸稀释后的样本体积1不合法。
	if((!is_zero(_diluted_sample_volume_1))&&((_diluted_sample_volume_1<1.5)||(
		_diluted_sample_volume_1>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING439),0.0,1.5,20.0);
		}
		return(-8);
	}
	//10.如果当前吸稀释液体积1不合法。
	if((!is_zero(_diluent_volume_1))&&((_diluent_volume_1<20.0)||(
		_diluent_volume_1>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING440),0.0,20.0,270.0);
		}
		return(-9);
	}
	//11.如果当前吸样本2体积不合法。
	if((_sample_volume_2<1.5)||(_sample_volume_2>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING441),1.5,35.0);
		}
		return(-10);
	}
	//12.如果当前吸稀释后的样本体积2不合法。
	if((!is_zero(_diluted_sample_volume_2))&&((_diluted_sample_volume_2<1.5)||(
		_diluted_sample_volume_2>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING442),0.0,1.5,20.0);
		}
		return(-11);
	}
	//13.如果当前吸稀释液体积2不合法。
	if((!is_zero(_diluent_volume_2))&&((_diluent_volume_2<20.0)||(
		_diluent_volume_2>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING443),0.0,20.0,270.0);
		}
		return(-12);
	}
	//14.如果当前吸样本3体积不合法。
	if((_sample_volume_3<1.5)||(_sample_volume_3>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING444),1.5,35.0);
		}
		return(-13);
	}
	//15.如果当前吸稀释后的样本体积3不合法。
	if((!is_zero(_diluted_sample_volume_3))&&((_diluted_sample_volume_3<1.5)||(
		_diluted_sample_volume_3>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING445),0.0,1.5,20.0);
		}
		return(-14);
	}
	//16.如果当前吸稀释液体积3不合法。
	if((!is_zero(_diluent_volume_3))&&((_diluent_volume_3<20.0)||(
		_diluent_volume_3>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING446),0.0,20.0,270.0);
		}
		return(-15);
	}
	//17.如果当前吸样本4体积不合法。
	if((_sample_volume_4<1.5)||(_sample_volume_4>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING447),1.5,35.0);
		}
		return(-16);
	}
	//18.如果当前吸稀释后的样本体积4不合法。
	if((!is_zero(_diluted_sample_volume_4))&&((_diluted_sample_volume_4<1.5)||(
		_diluted_sample_volume_4>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING448),0.0,1.5,20.0);
		}
		return(-17);
	}
	//19.如果当前吸稀释液体积4不合法。
	if((!is_zero(_diluent_volume_4))&&((_diluent_volume_4<20.0)||(
		_diluent_volume_4>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING449),0.0,20.0,270.0);
		}
		return(-18);
	}
	//20.如果当前吸样本5体积不合法。
	if((_sample_volume_5<1.5)||(_sample_volume_5>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING450),1.5,35.0);
		}
		return(-19);
	}
	//21.如果当前吸稀释后的样本体积5不合法。
	if((!is_zero(_diluted_sample_volume_5))&&((_diluted_sample_volume_5<1.5)||(
		_diluted_sample_volume_5>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING451),0.0,1.5,20.0);
		}
		return(-20);
	}
	//22.如果当前吸稀释液体积5不合法。
	if((!is_zero(_diluent_volume_5))&&((_diluent_volume_5<20.0)||(
		_diluent_volume_5>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING452),0.0,20.0,270.0);
		}
		return(-21);
	}
	//23.如果当前吸样本6体积不合法。
	if((_sample_volume_6<1.5)||(_sample_volume_6>35.0)){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING453),1.5,35.0);
		}
		return(-22);
	}
	//24.如果当前吸稀释后的样本体积6不合法。
	if((!is_zero(_diluted_sample_volume_6))&&((_diluted_sample_volume_6<1.5)||(
		_diluted_sample_volume_6>20.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING454),0.0,1.5,20.0);
		}
		return(-23);
	}
	//25.如果当前吸稀释液体积6不合法。
	if((!is_zero(_diluent_volume_6))&&((_diluent_volume_6<20.0)||(
		_diluent_volume_6>270.0))){
		if(0!=error_message){
			error_message->Format(theme->get_string(IDS_STRING455),0.0,20.0,270.0);
		}
		return(-24);
	}
	//26.程序运行到此成功返回。
	return(0);
}

/**
 * name: reset_default_value
 * brief: 将当前分析申请参数重置为默认值。
 * param: --
 * return: --
 */
void StandardApplication::reset_default_value(){
	_calibrator_code_1=1;
	_calibrator_code_2=0;
	_calibrator_code_3=0;
	_calibrator_code_4=0;
	_calibrator_code_5=0;
	_calibrator_code_6=0;
	_sample_volume_1=3.0;
	_diluted_sample_volume_1=0.0;
	_diluent_volume_1=0.0;
	_sample_volume_2=3.0;
	_diluted_sample_volume_2=0.0;
	_diluent_volume_2=0.0;
	_sample_volume_3=3.0;
	_diluted_sample_volume_3=0.0;
	_diluent_volume_3=0.0;
	_sample_volume_4=3.0;
	_diluted_sample_volume_4=0.0;
	_diluent_volume_4=0.0;
	_sample_volume_5=3.0;
	_diluted_sample_volume_5=0.0;
	_diluent_volume_5=0.0;
	_sample_volume_6=3.0;
	_diluted_sample_volume_6=0.0;
	_diluent_volume_6=0.0;
}

/**
 * name: commit
 * brief: 将当前的项目信息提交的数据库中。
 * param: item_id - 对应的项目标识。
 *        method - 提交到数据库的方法（1 插入 2 更新）。
 *        database - 准备提交的目标数据库。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int StandardApplication::commit(const int item_id,const int method,Database &database) const{
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
		//3-1.利用当前标准参数形成提交数据库的SQL语句。
		CString sql(_T(""));
		sql.Format(_T("INSERT INTO [standard_application]([item_id],[calibrator_code_1],\
					  [calibrator_code_2],[calibrator_code_3],[calibrator_code_4],\
					  [calibrator_code_5],[calibrator_code_6],[sample_volume_1],\
					  [diluted_sample_volume_1],[diluent_volume_1],[sample_volume_2],\
					  [diluted_sample_volume_2],[diluent_volume_2],[sample_volume_3],\
					  [diluted_sample_volume_3],[diluent_volume_3],[sample_volume_4],\
					  [diluted_sample_volume_4],[diluent_volume_4],[sample_volume_5],\
					  [diluted_sample_volume_5],[diluent_volume_5],[sample_volume_6],\
					  [diluted_sample_volume_6],[diluent_volume_6])VALUES('%d','%d','%d',\
					  '%d','%d','%d','%d','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf',\
					  '%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf','%lf')"),
					  item_id,_calibrator_code_1,_calibrator_code_2,_calibrator_code_3,
					  _calibrator_code_4,_calibrator_code_5,_calibrator_code_6,_sample_volume_1,
					  _diluted_sample_volume_1,_diluent_volume_1,_sample_volume_2,_diluted_sample_volume_2,
					  _diluent_volume_2,_sample_volume_3,_diluted_sample_volume_3,_diluent_volume_3,
					  _sample_volume_4,_diluted_sample_volume_4,_diluent_volume_4,_sample_volume_5,
					  _diluted_sample_volume_5,_diluent_volume_5,_sample_volume_6,_diluted_sample_volume_6,
					  _diluent_volume_6);
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
		CString sql(_T(""));
		sql.Format(_T("UPDATE [standard_application] SET [calibrator_code_1]='%d',[calibrator_code_2]='%d',\
					  [calibrator_code_3]='%d',[calibrator_code_4]='%d',[calibrator_code_5]='%d',\
					  [calibrator_code_6]='%d',[sample_volume_1]='%lf',[diluted_sample_volume_1]='%lf',\
					  [diluent_volume_1]='%lf',[sample_volume_2]='%lf',[diluted_sample_volume_2]='%lf',\
					  [diluent_volume_2]='%lf',[sample_volume_3]='%lf',[diluted_sample_volume_3]='%lf',\
					  [diluent_volume_3]='%lf',[sample_volume_4]='%lf',[diluted_sample_volume_4]='%lf',\
					  [diluent_volume_4]='%lf',[sample_volume_5]='%lf',[diluted_sample_volume_5]='%lf',\
					  [diluent_volume_5]='%lf',[sample_volume_6]='%lf',[diluted_sample_volume_6]='%lf',\
					  [diluent_volume_6]='%lf' WHERE [item_id]='%d'"),_calibrator_code_1,_calibrator_code_2,
					  _calibrator_code_3,_calibrator_code_4,_calibrator_code_5,_calibrator_code_6,_sample_volume_1,
					  _diluted_sample_volume_1,_diluent_volume_1,_sample_volume_2,_diluted_sample_volume_2,
					  _diluent_volume_2,_sample_volume_3,_diluted_sample_volume_3,_diluent_volume_3,
					  _sample_volume_4,_diluted_sample_volume_4,_diluent_volume_4,_sample_volume_5,
					  _diluted_sample_volume_5,_diluent_volume_5,_sample_volume_6,_diluted_sample_volume_6,
					  _diluent_volume_6,item_id);
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
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int StandardApplication::update(MtADORecordset &record){
	//1.声明当前操作所需变量。
	StandardApplication standard;
	_variant_t value;
	long index=257;
	//2.从指定的记录集中获取效准液编号1。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	standard._calibrator_code_1=MtADODataConverter::to_int(value);
	//3.从指定的记录集中获取效准液编号2。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	standard._calibrator_code_2=MtADODataConverter::to_int(value);
	//4.从指定的记录集中获取效准液编号3。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	standard._calibrator_code_3=MtADODataConverter::to_int(value);
	//5.从指定的记录集中获取效准液编号4。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	standard._calibrator_code_4=MtADODataConverter::to_int(value);
	//6.从指定的记录集中获取效准液编号5。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	standard._calibrator_code_5=MtADODataConverter::to_int(value);
	//7.从指定的记录集中获取效准液编号6。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-6);
	}
	standard._calibrator_code_6=MtADODataConverter::to_int(value);

	//8.从指定的记录集中获取吸样本体积1。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-7);
	}
	standard._sample_volume_1=MtADODataConverter::to_double(value);
	//9.从指定的记录集中获取吸稀释后样本体积1。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-8);
	}
	standard._diluted_sample_volume_1=MtADODataConverter::to_double(value);
	//10.从指定的记录集中获取吸稀释液体积1。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-9);
	}
	standard._diluent_volume_1=MtADODataConverter::to_double(value);
	//11.从指定的记录集中获取吸样本体积2。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-10);
	}
	standard._sample_volume_2=MtADODataConverter::to_double(value);
	//12.从指定的记录集中获取吸稀释后样本体积2。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-11);
	}
	standard._diluted_sample_volume_2=MtADODataConverter::to_double(value);
	//13.从指定的记录集中获取吸稀释液体积2。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-12);
	}
	standard._diluent_volume_2=MtADODataConverter::to_double(value);
	//14.从指定的记录集中获取吸样本体积3。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-13);
	}
	standard._sample_volume_3=MtADODataConverter::to_double(value);
	//15.从指定的记录集中获取吸稀释后样本体积3。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-14);
	}
	standard._diluted_sample_volume_3=MtADODataConverter::to_double(value);
	//16.从指定的记录集中获取吸稀释液体积3。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-15);
	}
	standard._diluent_volume_3=MtADODataConverter::to_double(value);
	//17.从指定的记录集中获取吸样本体积4。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-16);
	}
	standard._sample_volume_4=MtADODataConverter::to_double(value);
	//18.从指定的记录集中获取吸稀释后样本体积4。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-17);
	}
	standard._diluted_sample_volume_4=MtADODataConverter::to_double(value);
	//19.从指定的记录集中获取吸稀释液体积4。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-18);
	}
	standard._diluent_volume_4=MtADODataConverter::to_double(value);
	//20.从指定的记录集中获取吸样本体积5。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-19);
	}
	standard._sample_volume_5=MtADODataConverter::to_double(value);
	//21.从指定的记录集中获取吸稀释后样本体积5。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-20);
	}
	standard._diluted_sample_volume_5=MtADODataConverter::to_double(value);
	//22.从指定的记录集中获取吸稀释液体积5。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-21);
	}
	standard._diluent_volume_5=MtADODataConverter::to_double(value);
	//23.从指定的记录集中获取吸样本体积6。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-22);
	}
	standard._sample_volume_6=MtADODataConverter::to_double(value);
	//24.从指定的记录集中获取吸稀释后样本体积6。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-23);
	}
	standard._diluted_sample_volume_6=MtADODataConverter::to_double(value);
	//25.从指定的记录集中获取吸稀释液体积6。
	value=record.get_collect(MtADODataConverter::to_variant_t(index++));
	if(0!=record.get_last_error_code()){
		return(-24);
	}
	standard._diluent_volume_6=MtADODataConverter::to_double(value);
	//26.如果当前获取的标准信息不合法，则直接返回错误。
	if(standard.is_valid()<0){
		return(-25);
	}
	//27.保存当前的从记录集中获取的定标信息。
	(*this)=standard;
	//28.程序运行到此成功返回。
	return(0);
}