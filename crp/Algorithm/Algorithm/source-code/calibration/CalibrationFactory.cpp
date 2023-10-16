#include"stdafx.h"
#include"CalibrationFactory.h"
#include <algorithm>
#include"../arithmetic/MtMatrix.h"
#include"../arithmetic/MtSimpleLinearFitting.h"
#include"../arithmetic/MtSimpleLinearFormula.h"
#include"../arithmetic/MtPolynomialFitting.h"
#include"../arithmetic/MtPolynomialFormula.h"
#include"../arithmetic/MtLMFitting.h"
#include"LogitLog4P.h"
#include"LogitLog5P.h"
#include<math.h>
#include<float.h>

#define MINI_VALUE		0.001
const double CalibrationFactory::TINY = 1.0E-40;


/**
 * name: calibrate
 * breif: 定标实现。
 * param: calibration_type - 输入的定标类型。
 *        calibration_method - 输入的定标方法。
 *        experiment_method - 输入的试验方法。
 *        coordinates_type - 输入的坐标类型。
 *        is_s0_participation - 输入的s0点是否参与拟合标记。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *        size - 输入的数组尺寸。
 *        a - 输出的定标拟合的a参数。
 *        b - 输出的定标拟合的b参数。
 *        c - 输出的定标拟合的c参数。
 *        d - 输出的定标拟合的d参数。
 *        R - 输出的定标拟合的决定系数。
 *        D - 输出的最大相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::calibrate(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation,
	double* x, double* y, const unsigned int size,
	double* parameters, int parameters_size,
	double& R, double& xbase, double& ybase, double& xration) {
	//1.判断输入的参数是否合法，如果不合法则直接返回错误。
	//1-1.目前只支持多点定标，一点、两点定标尚未支持。
	if (CALIBRATION_TYPE_MULTIPOINT != calibration_type) {
		return(-1);
	}
	//1-2.log(x)-logit(y)的坐标类型，只适用于与竞争法类似的减函数。
	if ((EXPERIMENT_METHOD_COMPETITION != experiment_method) &&
		(COORDINATES_TYPE_LOGX_LOGITY == coordinates_type)) {
		return(-2);
	}
	//1-3.当坐标类型为log(x)-logit(y)、log(x)-log(y)以及log(x)-y时，
	//    s0点不能参与拟合（浓度为零时log运算无意义）。
	if (((COORDINATES_TYPE_LOGX_LOGITY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_LOGY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == coordinates_type)) &&
		(true == is_s0_participation)) {
		return(-3);
	}
	//1-4.检测当前输入的待拟合数据数组是否合法（目前支持6点定标）。
	if ((0 == x) || (0 == y)) {
		return(-4);
	}
	/*if((x[0]>x[1])||(x[1]>x[2])||(x[2]>x[3])||(
		x[3]>x[4])||(x[4]>x[5])){
		return(-5);
	}
	if(EXPERIMENT_METHOD_COMPETITION==experiment_method){
		if((y[0]<y[1])||(y[1]<y[2])||(y[2]<y[3])||
			(y[3]<y[4])||(y[4]<y[5])){
			return(-6);
		}
	}else{
		if((y[0]>y[1])||(y[1]>y[2])||(y[2]>y[3])||
			(y[3]>y[4])||(y[4]>y[5])){
			return(-7);
		}
	}*/
	//2.根据不同的坐标类型，对输入待拟合数据进行坐标转换。
	auto i = std::min_element(x, x + size);
	double xmin = *i;
	double ymin = *(y + (i - x));

	if (fabs(xmin) < 0.000001)
	{
		if (i - x > 0)//reverse
			--i;
		else
			++i;
	}

	xration = 1.;
	while (*i < 1.)
	{
		std::transform(x, x + size, x, [](double v) {
			return 10. * v;
			});
		xration *= 10.;
	}


	if (convert_x_y_coordinates(coordinates_type, x, y, size) < 0) {
		return(-8);
	}
	//3.根据输入的定标方法，实现相应的定标。
	switch (calibration_method) {
		//3-1.如果当前采用线性定标。
	case CALIBRATION_METHOD_LINEAR:
		if (linear_calibrate(is_s0_participation,
			x, y, size, parameters, parameters_size, R, xbase) < 0) {
			return(-9);
		}
		break;
		//3-2.如果当前采用三次多项式定标。
	case CALIBRATION_METHOD_CUBIC_POLYNOMIAL:
		if (cubic_polynomial_calibrate(
			is_s0_participation,
			x, y, size,
			parameters, parameters_size, R, xbase) < 0) {
			return(-10);
		}
		break;
		//3-3.如果当前采用4参数定标。
	case CALIBRATION_METHOD_LOGIT_LOG4P:
		if (logit_log4P_calibrate(
			is_s0_participation,
			x, y, size,
			parameters, parameters_size, R, xbase) < 0) {
			return(-11);
		}
		break;
	case CALIBRATION_METHOD_LOGIT_LOG5P:
		if (logit_log5P_calibrate(
			is_s0_participation,
			x, y, size,
			parameters, parameters_size, R, xbase, ybase) < 0)
			return -13;
		//3-4.程序运行到此直接返回错误。
		break;
	default:
		return(-12);
	}

	xbase = 0.;
	if (coordinates_type == CoordinatesType::COORDINATES_TYPE_LOGX_LOGITY
		|| coordinates_type == COORDINATES_TYPE_LOGX_LOGY
		|| coordinates_type == COORDINATES_TYPE_LOGX_Y)
		xbase = 1.;

	auto ret = calculate_luminous(calibration_type, calibration_method, experiment_method, coordinates_type, is_s0_participation
		, parameters, parameters_size, 1.0, xbase, 0, ybase);
	if (ret < 0)
	{
		if (experiment_method == EXPERIMENT_METHOD_COMPETITION)
			ybase = exp(parameters[1]); //A
		else
			ybase = exp(parameters[0]); //D
	}

	if (fabs(xmin) < 0.000001)
	{
		if (experiment_method != ExperimentMethod::EXPERIMENT_METHOD_COMPETITION)
		{
			if (ymin > ybase)
				ybase = ymin;
		}
		else if (ymin < ybase)//reverse
			ybase = ymin;
	}
	calculate_concentration(calibration_type, calibration_method, experiment_method, coordinates_type, is_s0_participation
		, parameters, parameters_size, 1., 0, ybase + 0.01, ybase, xbase);

	return 0;
}

/**
 * name: calculate_concentration
 * breif: 计算浓度。
 * param: calibration_type - 输入的定标类型。
 *        calibration_method - 输入的定标方法。
 *        experiment_method - 输入的试验方法。
 *        coordinates_type - 输入的坐标类型。
 *        is_s0_participation - 输入的s0点是否参与拟合标记。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *        size - 输入的数组尺寸。
 *        lum - 输入的发光值。
 *        conc - 输出的浓度值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::calculate_concentration(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation,
	const double* parameters, int parameters_size,
	double xration, double xbase, double ybase,
	const double lum, double& conc) {
	//1.判断输入的参数是否合法，如果不合法则直接返回错误。
	//1-1.目前只支持多点定标，一点、两点定标尚未支持。
	if (CALIBRATION_TYPE_MULTIPOINT != calibration_type) {
		return(-1);
	}
	//1-2.log(x)-logit(y)的坐标类型，只适用于与竞争法类似的减函数。
	if ((EXPERIMENT_METHOD_COMPETITION != experiment_method) && (
		COORDINATES_TYPE_LOGX_LOGITY == coordinates_type)) {
		return(-2);
	}
	//1-3.当坐标类型为log(x)-logit(y)、log(x)-log(y)以及log(x)-y时，
	//    s0点不能参与拟合（浓度为零时log运算无意义）。
	if (((COORDINATES_TYPE_LOGX_LOGITY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_LOGY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == coordinates_type)) && (
			true == is_s0_participation)) {
		return(-3);
	}

	if (experiment_method != ExperimentMethod::EXPERIMENT_METHOD_COMPETITION)
	{
		if (lum < ybase)
			return 0.;
	}
	else if (lum >= ybase)
		return 0.;

	//5.如果当前是三次多项式拟合，则计算浓度的靶值。
	//5-1.声明当前操作所需变量。
										//<0 靶值浓度小于待测浓度 >0 靶值浓度大于待测浓度）。
	//  并对输入的发光值进行坐标变换。
	//6-1.声明当前操作所需变量。
	double lum_t = lum;
	//6-3.根据当前坐标类型，对输入的发光值（abs）进行转换。
	if (convert_x_y_coordinates(coordinates_type,
		lum_t, lum_t) < 0) {
		return(-17);
	}
	//7.根据当前指定的定标方法，反算浓度。
	switch (calibration_method) {
		//7-1.如果当前定标方法为线性定标。
	case CALIBRATION_METHOD_LINEAR:
	{
		if (linear_calculate_concentration(
			coordinates_type, parameters, parameters_size, lum_t, conc) < 0) {
			return(-18);
		}
		break;
	}
	//7-2.如果当前定标方法为三次多项式定标。
	case CALIBRATION_METHOD_CUBIC_POLYNOMIAL:
	{
		if (cubic_polynomial_calculate_concentration(
			coordinates_type, parameters, parameters_size, lum_t, conc) < 0) {
			return(-19);
		}
		break;
	}
	//7-3.如果当前定标方法为四参数定标。
	case CALIBRATION_METHOD_LOGIT_LOG4P:
	{
		if (logit_log4P_calculate_concentration(
			coordinates_type,
			parameters, parameters_size,
			lum_t, conc) < 0) {
			return(-20);
		}
		break;

	}
	case CALIBRATION_METHOD_LOGIT_LOG5P:
		if (logit_log5P_calculate_concentration(
			coordinates_type,
			parameters, parameters_size,
			lum_t, conc) < 0)
			return -22;
		break;
		//7-4.程序运行到此直接返回错误。
	default:
		return(-21);
	}

	conc = (conc - xbase) / xration;
	return 0;
}

/**
 * name: calculate_luminous
 * breif: 计算发光值。
 * param: calibration_type - 输入的定标类型。
 *        calibration_method - 输入的定标方法。
 *        experiment_method - 输入的试验方法。
 *        coordinates_type - 输入的坐标类型。
 *        is_s0_participation - 输入的s0点是否参与拟合标记。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *        size - 输入的数组尺寸。
 *        conc - 输入的浓度值。
 *        lum - 输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::calculate_luminous(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation,
	const double* parameters, int parameters_size, double xration, double xbase,
	const double conc, double& lum) {
	//1.判断输入的参数是否合法，如果不合法则直接返回错误。
	//1-1.目前只支持多点定标，一点、两点定标尚未支持。
	if (CALIBRATION_TYPE_MULTIPOINT != calibration_type) {
		return(-1);
	}
	//1-2.log(x)-logit(y)的坐标类型，只适用于与竞争法类似的减函数。
	if ((EXPERIMENT_METHOD_COMPETITION != experiment_method) &&
		(COORDINATES_TYPE_LOGX_LOGITY == coordinates_type)) {
		return(-2);
	}
	//1-3.当坐标类型为log(x)-logit(y)、log(x)-log(y)以及log(x)-y时，
	//    s0点不能参与拟合（浓度为零时log运算无意义）。
	if (((COORDINATES_TYPE_LOGX_LOGITY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_LOGY == coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == coordinates_type)) && (
			true == is_s0_participation)) {
		return(-3);
	}

	/*if((x[0]>x[1])||(x[1]>x[2])||(x[2]>x[3])||(
		x[3]>x[4])||(x[4]>x[5])){
		return(-5);
	}
	if(EXPERIMENT_METHOD_COMPETITION==experiment_method){
		if((y[0]<y[1])||(y[1]<y[2])||(y[2]<y[3])||
			(y[3]<y[4])||(y[4]<y[5])){
			return(-6);
		}
	}else{
		if((y[0]>y[1])||(y[1]>y[2])||(y[2]>y[3])||
			(y[3]>y[4])||(y[4]>y[5])){
			return(-7);
		}
	}*/
	//2.检测当前浓度是否超出检测范围，如果超出检测范围则计算超出检测范围类型。
	//2-1.声明当前操作所需变量。
	//2-2.如果当前待计算点在s0点左侧。
	//if(conc<x[0]){
	//	beyond_detection_range_type=1;
	//}
	////2-3.如果当前待计算点在s0~s1之间。
	//else if((!is_s0_participation)&&
	//	(conc>=x[0])&&(conc<x[1])){
	//	beyond_detection_range_type=2;
	//}
	////2-3.如果当前待计算点在s5右侧。
	//else if(conc>x[5]){
	//	beyond_detection_range_type=3;
	//}
	//3.如果当前输入的发光值在s0左侧，则无需计算发光值（此时认为发光值为0），直接成功返回。
	// ( 注： 此处这样处理是否合适？？？？)
	/*
	if(1==beyond_detection_range_type){
		//3-1.此时认为发光值为0.0。
		lum=0.0;
		//3-2.程序运行到此直接成功返回。
		return(0);
	}
	*/
	//4.根据当前待测点是否超出范围计算相应的s1、s2、s4、s5点的发光值。
	//4-1.声明当前操作所需变量。
		//5.存储当前s0点的发光值。
	//6.对x、y数组以及输入的浓度进行坐标变换。
	//6-1.声明当前操作所需变量。
	double conc_t = conc * xration + xbase;
	//6-3.根据当前坐标类型，对输入的浓度进行坐标转换。
	if (convert_x_y_coordinates(coordinates_type, conc_t) < 0) {
		return(-16);
	}

	if (fabs(conc_t) < TINY)
		conc_t = MINI_VALUE;

	//7.根据当前指定的定标方法，计算发光值。
	switch (calibration_method) {
		//7-1.如果当前定标方法为线性定标。
	case CALIBRATION_METHOD_LINEAR:
	{
		if (linear_calculate_luminous(
			coordinates_type, parameters, parameters_size, conc_t, lum) < 0) {
			return(-17);
		}
		break;
	}
	//7-2.如果当前定标方法为三次多项式定标。
	case CALIBRATION_METHOD_CUBIC_POLYNOMIAL:
	{
		if (cubic_polynomial_calculate_luminous(
			coordinates_type, parameters, parameters_size, conc_t, lum) < 0) {
			return(-18);
		}
		break;
	}
	//7-3.如果当前定标方法为四参数定标。
	case CALIBRATION_METHOD_LOGIT_LOG4P:
	{
		if (logit_log4P_calculate_luminous(
			coordinates_type, parameters, parameters_size, conc_t, lum) < 0) {
			return(-19);
		}
		break;
	}
	case CALIBRATION_METHOD_LOGIT_LOG5P:
		if (logit_log5P_calculate_luminous(
			coordinates_type, parameters, parameters_size, conc_t, lum) < 0)
			return -21;
		break;
		//7-4.程序运行到此直接返回错误。
	default:
		return(-20);
	}

	return 0;
}

/**
 * name: convert_x_y_coordinates
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的期望转换成的目标坐标类型。
 *        lum_0 - 输入的s0点的发光值（在x-y坐标系下的发光值）。
 *        lum - 输入/输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::convert_x_y_coordinates(
	const CoordinatesType target_coordinates_type,
	const double lum_0, double& lum) {
	//1.如果当前期望转换成x-y类型或log(x)-y类型的坐标，则什么也不做，
	//  直接返回（此时发光值不用进行变换）。
	if ((COORDINATES_TYPE_X_Y == target_coordinates_type) || (
		COORDINATES_TYPE_LOGX_Y == target_coordinates_type)) {
		return(0);
	}
	//2.如果当前期望转换的目标坐标类型为log(x)-logit(y)。
	if (COORDINATES_TYPE_LOGX_LOGITY == target_coordinates_type) {
		//2-1.如果当前输入的发光值大于等于s0点的发光值。
		if ((fabs(lum - lum_0) < TINY) || (lum >= lum_0)) {
			lum = lum_0 - 1.0;
		}
		//2-2.对发光值进行坐标变换。
		lum = log(lum / (lum_0 - lum));
		//3-3.如果变换失败则直接返回错误。
		if (_isnan(lum)) {
			return(-1);
		}
		//3-4.程序运行到此直接成功返回。
		return(0);
	}
	//3.如果当前期望转换的目标坐标类型为log(x)-log(y)或x-log(y)。
	else if ((COORDINATES_TYPE_LOGX_LOGY == target_coordinates_type) ||
		(COORDINATES_TYPE_X_LOGY == target_coordinates_type)) {
		//3-1.如果当前输入的发光值小于或等于零。
		if ((fabs(lum) < TINY) || (lum < 0.0)) {
			lum = 0.001;
		}
		//3-2.对发光值进行坐标变换。
		lum = log(lum);
		//3-3.如果变换失败则直接返回错误。
		if (_isnan(lum)) {
			return(-2);
		}
		//3-4.程序运行到此直接成功返回。
		return(0);
	}
	//5.程序运行到此直接返回错误。
	else {
		return(-3);
	}
}

/**
 * name: convert_x_y_coordinates
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的目标坐标类型。
 *        conc - 输入/输出的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::convert_x_y_coordinates(
	const CoordinatesType target_coordinates_type, double& conc) {
	//1.如果当前目标类型为x-y或x-log(y)，则不进行任何变换，直接成功返回。
	if ((COORDINATES_TYPE_X_Y == target_coordinates_type) || (
		COORDINATES_TYPE_X_LOGY == target_coordinates_type)) {
		return(0);
	}
	//2.如果当前目标类型为log(x)-logit(y)、log(x)-log(y)或log(x)-y，
	//  则对输入的浓度进行坐标变换。
	else if ((COORDINATES_TYPE_LOGX_LOGITY == target_coordinates_type) ||
		(COORDINATES_TYPE_LOGX_LOGY == target_coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == target_coordinates_type)) {
		//2-1.如果输入的浓度小于等于零。
		if (conc < TINY)
			conc = MINI_VALUE;
		else
			//2-2.对输入的浓度进行坐标变换。
			conc = log(conc);
		if (_isnan(conc)) {
			return(-1);
		}
		//2-3.程序运行到此直接成功返回。
		return(0);
	}
	//3.程序运行到此直接返回错误。
	else {
		return(-2);
	}
}

/**
 * name: convert_to_x_y_coordinates
 * biref: 进行坐标变换，将指定类型坐标转换为x-y类型的坐标。
 * param: current_coordinates_type - 输入的当前坐标类型。
 *        conc - 输入/输出的浓度值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::convert_to_x_y_coordinates(
	const CoordinatesType current_coordinates_type, double& conc) {
	//1.如果当前坐标系为x-y或x-log(y)，则直接成功返回（此时x不需要进行坐标转换）。
	if ((COORDINATES_TYPE_X_Y == current_coordinates_type) ||
		(COORDINATES_TYPE_X_LOGY == current_coordinates_type)) {
		return(0);
	}
	//2.如果当前坐标系统为log(x)-logit(y)、log(x)-log(y)以及log(x)-y，
	//  则对浓度进行坐标转换。
	else if ((COORDINATES_TYPE_LOGX_LOGITY == current_coordinates_type) ||
		(COORDINATES_TYPE_LOGX_LOGY == current_coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == current_coordinates_type)) {
		//2-1.对浓度进行坐标变换。
		conc = exp(conc);
		//2-2.如果变换失败，则直接返回错误。
		if (_isnan(conc)) {
			return(-1);
		}
		//2-3.程序运行到此直接成功返回。
		return(0);
	}
	//3.程序运行到此直接返回错误。
	else {
		return(-2);
	}
}

/**
 * name: convert_to_x_y_coordinates
 * biref: 进行坐标变换，将指定类型坐标转换为x-y类型的坐标。
 * param: current_coordinates_type - 输入的当前坐标类型。
 *        lum_0 - 输入的s0点的发光值（在x-y坐标系下的发光值）。
 *        lum - 输入/输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::convert_to_x_y_coordinates(
	const CoordinatesType current_coordinates_type,
	const double lum_0, double& lum) {
	//1.如果当前坐标系为x-y或log(x)-y，则直接成功返回。
	if ((COORDINATES_TYPE_X_Y == current_coordinates_type) ||
		(COORDINATES_TYPE_LOGX_Y == current_coordinates_type)) {
		return(0);
	}
	//2.如果当前坐标系统为log(x)-logit(y)、则对发光值进行坐标转换。
	else if (COORDINATES_TYPE_LOGX_LOGITY == current_coordinates_type) {
		lum = exp(lum);
		if (_isnan(lum)) {
			return(-1);
		}
		if (fabs(1.0 + lum) < TINY) {
			return(-2);
		}
		lum = (lum * lum_0) / (1.0 + lum);
		return(0);
	}
	//3.如果当前坐标系统为log(x)-log(y)或x-log(y)，则对发光值进行坐标转换。
	else if ((COORDINATES_TYPE_LOGX_LOGY == current_coordinates_type) ||
		(COORDINATES_TYPE_X_LOGY == current_coordinates_type)) {
		lum = exp(lum);
		if (_isnan(lum)) {
			return(-3);
		}
		return(0);
	}
	//4.程序运行到此直接返回错误。
	else {
		return(-4);
	}
}

/**
 * name: convert_x_y_coordinates
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的期望转换成的目标坐标类型。
 *        is_s0_participation - 输入的s0是否参与拟合标志。
 *        x - 输入/输出的x数组指针。
 *        y - 输入/输出的y数组指针。
 *        size - 输入/输出的数组尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::convert_x_y_coordinates(
	const CoordinatesType target_coordinates_type,
	double* x, double* y, const unsigned int size) {
	//1.因为输入的参数在调用函数中已经经过验证，所以此处不做验证处理。
	//2.如果当前期望转换为x-y类型坐标，则无需变换,直接成功返回。
	if (COORDINATES_TYPE_X_Y == target_coordinates_type) {
		for (int i = 0; i < size; ++i)
		{
			if (fabs(x[i]) < TINY)
				x[i] = MINI_VALUE;
			if (fabs(y[i]) < TINY)
				y[i] = MINI_VALUE;
		}
		return(0);
	}
	//3.遍历x、y数组，进行坐标变换。
	//3-1.声明当前操作所需变量。
	const double y_0 = y[0];
	//3-2.遍历x、y数组，进行坐标变换。
	for (unsigned int i = 0; i < size; ++i) {
		//3-2-1.如果当前期望转换成log(x)-logit(y)类型坐标。
		if (COORDINATES_TYPE_LOGX_LOGITY ==
			target_coordinates_type) {
			if (fabs(x[i]) < TINY)
				x[i] = MINI_VALUE;
			x[i] = log(x[i]);
			if (_isnan(x[i])) {
				return(-1);
			}
			if (fabs(y_0 - y[i]) < TINY) {
				y[i] = y_0 - 1.0;
			}
			if ((fabs(y_0 - y[i]) < TINY) || ((
				y_0 - y[i]) < 0.0)) {
				return(-2);
			}
			y[i] = log(y[i] / (y_0 - y[i]));
			if (_isnan(y[i])) {
				return(-3);
			}
			if (x[i] < TINY)
				x[i] = MINI_VALUE;
			if (y[i] < TINY)
				y[i] = MINI_VALUE;
		}
		//3-2-2.如果当前期望转换成log(x)-log(y)类型坐标。
		else if (COORDINATES_TYPE_LOGX_LOGY ==
			target_coordinates_type) {
			if (fabs(x[i]) < TINY)
				x[i] = MINI_VALUE;
			else
				x[i] = log(x[i]);
			if (_isnan(x[i])) {
				return(-4);
			}
			if (fabs(y[i]) < TINY)
				y[i] = 0.001;
			y[i] = log(y[i]);
			if (_isnan(y[i])) {
				return(-5);
			}

			if (x[i] < TINY)
				x[i] = MINI_VALUE;
			if (y[i] < TINY)
				y[i] = MINI_VALUE;
		}
		//3-2-3.如果当前期望转换成log(x)-y类型坐标。
		else if (COORDINATES_TYPE_LOGX_Y == target_coordinates_type) {
			if (fabs(x[i]) < TINY)
				x[i] = MINI_VALUE;
			else
				x[i] = log(x[i]);
			if (_isnan(x[i])) {
				return(-6);
			}
			if (x[i] < TINY)
				x[i] = MINI_VALUE;
		}
		//3-2-4.如果当前期望转换成x-log(y)类型坐标。
		else if (COORDINATES_TYPE_X_LOGY == target_coordinates_type) {
			if (fabs(y[i]) < TINY)
				y[i] = MINI_VALUE;
			y[i] = log(y[i]);
			if (_isnan(y[i])) {
				return(-7);
			}
			if (y[i] < TINY)
				y[i] = MINI_VALUE;
		}
		//3-2-5.如果当前期望转换成其它未知类型坐标，则直接返回错误。
		else {
			return(-8);
		}
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: linear_calibrate
 * breif: 线性定标。
 * param: is_s0_participation - 输入的s0是否参与拟合标记。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *		  size - 输入的数组尺寸。
 *        a - 输出的定标拟合的a参数。
 *        b - 输出的定标拟合的b参数。
 *        R - 输出的定标拟合的决定系数。
 *        D - 输出的最大相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::linear_calibrate(
	const bool is_s0_participation,
	double* x, double* y, const unsigned int size,
	double* parameters, int parameters_size,
	double& R, double& D) {

	if (parameters_size < 2)
		return -2;
	//1.根据s0是否参与拟合，计算参与拟合x、y输入的起始位置。
	unsigned int i = 0;
	if (!is_s0_participation) {
		i = 1;
	}
	//2.对x、y进行线性回归，并且判断回归是否成功。
	MtSimpleLinearFormula formula(x + i, y + i, size - i);
	MtSimpleLinearFitting solver(formula);
	if (solver.fit() < 0) {
		return(-1);
	}
	//3.存储当前参数。
	parameters[0] = (formula.get_parameters()).get_element(0, 0);
	parameters[1] = (formula.get_parameters()).get_element(1, 0);
	R = formula.get_correlation_coefficient();
	D = formula.get_maximum_relative_deviation();
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: cubic_polynomial_calibrate
 * breif: 三次多项式拟合。
 * param: is_s0_participation - 输入的s0是否参与拟合标记。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *		  size - 输入的数组尺寸。
 *        a - 输出的定标拟合的a参数。
 *        b - 输出的定标拟合的b参数。
 *        c - 输出的定标拟合的c参数。
 *        d - 输出的定标拟合的d参数。
 *        R - 输出的定标拟合的决定系数。
 *        D - 输出的最大相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::cubic_polynomial_calibrate(
	const unsigned int is_s0_participation,
	double* x, double* y, const unsigned int size,
	double* parameters, int parameters_size,
	double& R, double& D) {
	//1.根据s0是否参与拟合，计算参与拟合x、y输入的起始位置。
	if (parameters_size < 4)
		return -2;
	unsigned int i = 0;
	if (!is_s0_participation) {
		i = 1;
	}
	//2.对x、y进行多项式拟合，并且判断拟合是否成功。
	MtPolynomialFormula formula(x + i, y + i, size - i, 3);
	MtPolynomialFitting solver(formula);
	if (solver.fit() < 0) {
		return(-1);
	}
	//3.存储当前参数。
	parameters[0] = (formula.get_parameters()).get_element(0, 0);
	parameters[1] = (formula.get_parameters()).get_element(1, 0);
	parameters[2] = (formula.get_parameters()).get_element(2, 0);
	parameters[3] = (formula.get_parameters()).get_element(3, 0);
	R = formula.get_correlation_coefficient();
	D = formula.get_maximum_relative_deviation();
	//4.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: logit_log4P_calibrate
 * breif: logit-log4P四参数拟合。
 * param: is_s0_participation - 输入的s0是否参与拟合标记。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *		  size - 输入的数组尺寸。
 *        a - 输出的定标拟合的a参数。
 *        b - 输出的定标拟合的b参数。
 *        c - 输出的定标拟合的c参数。
 *        d - 输出的定标拟合的d参数。
 *        R - 输出的定标拟合的决定系数。
 *        D - 输出的定标拟合的最大相对偏差。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::logit_log4P_calibrate(
	const unsigned int is_s0_participation,
	double* x, double* y, const unsigned int size,
	double* parameters, int parameters_size,
	double& R, double& D) {
	if (parameters_size < 4)
		return -2;
	//1.根据s0是否参与拟合，计算参与拟合x、y输入的起始位置。
	unsigned int i = 0;
	if (!is_s0_participation) {
		i = 1;
	}
	else {
		if (fabs(x[0]) < TINY) {
			x[0] = 0.001;
		}
	}
	//1.对四参数公式进行拟合，并且判断拟合是否成功。
	LogitLog4P formula(x + i, y + i, size - i);
	MtLMFitting slover(formula);
	if (slover.fit() < 0) {
		return(-1);
	}
	//2.为拟合参数赋值。
	parameters[0] = (formula.get_parameters()).get_element(0, 0);
	parameters[1] = (formula.get_parameters()).get_element(1, 0);
	parameters[2] = (formula.get_parameters()).get_element(2, 0);
	parameters[3] = (formula.get_parameters()).get_element(3, 0);
	R = formula.get_correlation_coefficient();
	D = formula.get_maximum_relative_deviation();
	//3.程序运行到此，直接成功返回。
	return(0);
}

/**
 * name: linear_calculate_concentration
 * breif: 使用线性拟合公式来计算浓度。
 * param: coordinates_type - 输入的坐标系类型。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        lum - 输入的发光值（经过坐标转换后的发光值）。
 *        conc - 输出的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::linear_calculate_concentration(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double lum, double& conc) {
	if (parameters_size != 2)
		return -4;
	//1.创建线性公式的参数矩阵，并且判断创建是否成功。
	MtSimpleLinearFormula::DMat parameters;
	if (parameters.create(2, 1) < 0) {
		return(-1);
	}
	parameters.set_element(0, 0, par[0]);
	parameters.set_element(1, 0, par[1]);
	//2.利用当前输入的发光值反算浓度，并且判断反算是否成功。
	if (MtSimpleLinearFormula::calculate_x(
		parameters, lum, conc) < 0) {
		return(-2);
	}
	//3.对计算出的浓度进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, conc) < 0) {
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: cubic_polynomial_calculate_concentration
 * breif: 使用三次多项式拟合出来的公式计算浓度。
 * param: coordinates_type - 输入的坐标系类型。
 *        beyond_detection_range_type - 输入的当前发光值超出范围类型(0-没有超出范围;1-在s0左侧;2-在s0到s1之间;3-在s5右侧)。
 *        x - 输入的x数组指针（经过坐标转换的）。
 *        y - 输入的y数组指针（经过坐标转换的）。
 *		  size - 输入的数组尺寸。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        target_conc - 输入的浓度靶值（经过坐标转换后的发光值）。
 *        target_conc_relative_position - 输入的靶值相对位置（<0 靶值浓度小于计算浓度，==0 靶值浓度等于计算浓度，>0 靶值浓度大于计算浓度）。
 *        s0_conc - 输入的s0点的计算浓度（经过坐标转换后的发光值）。
 *        s1_conc - 输入的s1点的计算浓度（经过坐标转换后的发光值）。
 *        s3_conc - 输入的s3点的计算浓度（经过坐标转换后的发光值）。
 *        s4_conc - 输入的s4点的计算浓度（经过坐标转换后的发光值）。
 *        lum - 输入的发光值（经过坐标转换后的发光值）。
 *        conc - 输出的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::cubic_polynomial_calculate_concentration(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double lum, double& conc) {
	if (parameters_size != 4)
		return -8;
	//1.创建三次多项式参数矩阵，并且判断创建是否成功。
	MtPolynomialFormula::DMat parameters;
	if (parameters.create(4, 1) < 0) {
		return(-1);
	}
	for (int i = 0; i < 4; ++i)
		parameters.set_element(i, 0, par[i]);
	//2.如果当前输入发光值处于s0~s1之间。
			//4-1.根据当前的发光值计算浓度，并且判断计算是否成功。
	if (MtPolynomialFormula::calculate_x(parameters,
		lum, conc) < 0) {
		return(-6);
	}
	//5.对计算出的浓度进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, conc) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。
	return(0);
}

/**
 * name: logit_log4P_calculate_concentration
 * breif: 使用logit-log4P四参数拟合出来的公式计算浓度。
 * param: coordinates_type - 输入的坐标系类型。
 *        beyond_detection_range_type - 输入的当前发光值超出范围类型(0-没有超出范围;1-在s0左侧;2-在s0到s1之间;3-在s5右侧)。
 *        x - 输入的x数组指针（经过坐标转换的）。
 *        y - 输入的y数组指针（经过坐标转换的）。
 *		  size - 输入的数组尺寸。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        s0_conc - 输入的s0点的计算浓度（经过坐标转换后的发光值）。
 *        s1_conc - 输入的s1点的计算浓度（经过坐标转换后的发光值）。
 *        s3_conc - 输入的s3点的计算浓度（经过坐标转换后的发光值）。
 *        s4_conc - 输入的s4点的计算浓度（经过坐标转换后的发光值）。
 *        lum - 输入的发光值（经过坐标转换后的发光值）。
 *        conc - 输出的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::logit_log4P_calculate_concentration(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double lum, double& conc) {
	if (parameters_size != 4)
		return -8;
	//1.创建四参数矩阵，并且判断创建是否成功。
	LogitLog4P::DMat parameters;
	if (parameters.create(4, 1) < 0) {
		return(-1);
	}
	for (int i = 0; i < 4; ++i)
		parameters.set_element(i, 0, par[i]);
	//2.如果当前输入发光值处于s0~s1之间。
	//if(2==beyond_detection_range_type){
	//	//2-1.计算s0与s1直线方程中的斜率。
	//	if(fabs(s0_conc-s1_conc)<TINY){
	//		return(-2);
	//	}
	//	const double k=(y[0]-y[1])/(s0_conc-s1_conc);
	//	if(fabs(k)<TINY){
	//		return(-3);
	//	}
	//	//2-2.计算s0与s1直线方程中的截距。
	//	const double b_t=y[0]-k*s0_conc;
	//	//2-3.计算浓度。
	//	conc=(lum-b_t)/k;
	//}
	////3.如果当前输入发光值处于s5右侧。
	//else if(3==beyond_detection_range_type){
	//	//3-1.计算s4与s5直线方程中的斜率。
	//	if(fabs(s4_conc-s5_conc)<TINY){
	//		return(-4);
	//	}
	//	const double k=(y[4]-y[5])/(s4_conc-s5_conc);
	//	if(fabs(k)<TINY){
	//		return(-5);
	//	}
	//	//3-2.计算s4与s5直线方程中的截距。
	//	const double b_t=y[4]-k*s4_conc;
	//	//3-3.计算浓度。
	//	conc=(lum-b_t)/k;
	//}	
	////4.如果当前输入发光值处于可计算范围内。
	//else
	{
		//4-1.根据当前的发光值计算浓度，并且判断计算是否成功。
		if (LogitLog4P::calculate_x(parameters, lum, conc) < 0) {
			return(-6);
		}
	}
	//5.对计算出的浓度进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, conc) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。
	return(0);
}

/**
 * name: linear_calculate_luminous
 * breif: 使用线性拟合公式来计算发光值。
 * param: coordinates_type - 输入的坐标系类型。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        lum_0 - 输入的s0点的发光值（x-y坐标系下的值）。
 *        conc - 输入的浓度（经过坐标转换后的浓度）。
 *        lum - 输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::linear_calculate_luminous(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double conc, double& lum) {
	if (parameters_size != 2)
		return -4;
	//1.创建线性公式的参数矩阵，并且判断创建是否成功。
	MtSimpleLinearFormula::DMat parameters;
	if (parameters.create(2, 1) < 0) {
		return(-1);
	}
	parameters.set_element(0, 0, par[0]);
	parameters.set_element(1, 0, par[1]);
	//2.利用当前输入的发光值反算浓度，并且判断反算是否成功。
	if (MtSimpleLinearFormula::calculate_y(
		parameters, conc, lum) < 0) {
		return(-2);
	}
	//3.对计算出的发光值进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, lum, lum) < 0) {
		return(-3);
	}
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: cubic_polynomial_calculate_luminous
 * breif: 使用三次多项式拟合出来的公式计算发光值。
 * param: coordinates_type - 输入的坐标系类型。
 *        beyond_detection_range_type - 输入的当前发光值超出范围类型(0-没有超出范围;1-在s0左侧;2-在s0到s1之间;3-在s5右侧)。
 *        x - 输入的x数组指针（经过坐标转换的）。
 *        y - 输入的y数组指针（经过坐标转换的）。
 *		  size - 输入的数组尺寸。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        s0_lum - 输入的s0点的计算发光值（经过坐标转换后的发光值）。
 *        s1_lum - 输入的s1点的计算发光值（经过坐标转换后的发光值）。
 *        s3_lum - 输入的s3点的计算发光值（经过坐标转换后的发光值）。
 *        s4_lum - 输入的s4点的计算发光值（经过坐标转换后的发光值）。
 *        lum_0 - 输入的s0点的发光值(x-y坐标系下的发光值)。
 *        conc - 输入的浓度（经过坐标转换后的浓度）。
 *        lum - 输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::cubic_polynomial_calculate_luminous(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double conc, double& lum) {
	if (parameters_size != 4)
		return -8;
	//1.创建三次多项式参数矩阵，并且判断创建是否成功。
	MtPolynomialFormula::DMat parameters;
	if (parameters.create(4, 1) < 0) {
		return(-1);
	}

	for (int i = 0; i < 4; ++i)
		parameters.set_element(i, 0, par[i]);
	//2.如果当前计算点小于s0或处于s0~s1之间。
			//4-1.根据当前的浓度计算发光值，并且判断计算是否成功。
	if (MtPolynomialFormula::calculate_y(
		parameters, conc, lum) < 0) {
		return(-6);
	}
	//5.对计算出的发光值进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, lum, lum) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。
	return(0);
}

/**
 * name: logit_log4P_calculate_luminous
 * breif: 使用四参数拟合出来的公式计算发光值。
 * param: coordinates_type - 输入的坐标系类型。
 *        beyond_detection_range_type - 输入的当前发光值超出范围类型(0-没有超出范围;1-在s0左侧;2-在s0到s1之间;3-在s5右侧)。
 *        x - 输入的x数组指针（经过坐标转换的）。
 *        y - 输入的y数组指针（经过坐标转换的）。
 *		  size - 输入的数组尺寸。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        s0_lum - 输入的s0点的计算发光值（经过坐标转换后的发光值）。
 *        s1_lum - 输入的s1点的计算发光值（经过坐标转换后的发光值）。
 *        s3_lum - 输入的s3点的计算发光值（经过坐标转换后的发光值）。
 *        s4_lum - 输入的s4点的计算发光值（经过坐标转换后的发光值）。
 *        lum_0 - 输入的s0点的发光值(x-y坐标系下的发光值)。
 *        conc - 输入的浓度（经过坐标转换后的浓度）。
 *        lum - 输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int CalibrationFactory::logit_log4P_calculate_luminous(
	const CoordinatesType coordinates_type,
	const double* par, int parameters_size,
	const double conc, double& lum) {
	if (parameters_size != 4)
		return -8;

	//1.创建四参数矩阵，并且判断创建是否成功。
	LogitLog4P::DMat parameters;
	if (parameters.create(4, 1) < 0) {
		return(-1);
	}

	for (int i = 0; i < 4; ++i)
		parameters.set_element(i, 0, par[i]);
	//2.如果当前计算点小于s0或处于s0~s1之间。
	//if((1==beyond_detection_range_type)||
	//	(2==beyond_detection_range_type)){
	//	//2-1.计算s0与s1直线方程中的斜率。
	//	if(fabs(x[0]-x[1])<TINY){
	//		return(-2);
	//	}
	//	const double k=(s0_lum-s1_lum)/(x[0]-x[1]);
	//	if(fabs(k)<TINY){
	//		return(-3);
	//	}
	//	//2-2.计算s0与s1直线方程中的截距。
	//	const double b_t=s0_lum-k*x[0];
	//	//2-3.计算发光值。
	//	lum=k*conc+b_t;
	//}
	////3.如果当前计算点处于s5右侧。
	//else if(3==beyond_detection_range_type){
	//	//3-1.计算s4与s5直线方程中的斜率。
	//	if(fabs(x[4]-x[5])<TINY){
	//		return(-4);
	//	}
	//	const double k=(s4_lum-s5_lum)/(x[4]-x[5]);
	//	if(fabs(k)<TINY){
	//		return(-5);
	//	}
	//	//3-2.计算s4与s5直线方程中的截距。
	//	const double b_t=s4_lum-k*x[4];
	//	//3-3.计算发光值。
	//	lum=k*conc+b_t;
	//}
	////4.如果当前输入浓度处于可计算范围内。
	//else
		//4-1.使得当前输入的浓度合法。
	double conc_t = conc;
	if (fabs(conc_t) < TINY) {
		conc_t = 0.001;
	}
	//4-2.根据当前的浓度计算发光值，并且判断计算是否成功。
	if (LogitLog4P::calculate_y(parameters, conc_t, lum) < 0) {
		return(-6);
	}
	//5.对计算出的发光值进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, lum, lum) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。
	return(0);
}

int CalibrationFactory::logit_log5P_calibrate(const unsigned int is_s0_participation, double* x
	, double* y, const unsigned int size, double* parameters, int parameters_size, double& R, double& xbase, double& ybase)
{
	if (parameters_size < 5)
		return -2;
	//1.根据s0是否参与拟合，计算参与拟合x、y输入的起始位置。
	unsigned int i = 0;
	/*if (!is_s0_participation) {
		i = 1;
	}
	else {*/
	//}
	//}
	//1.对四参数公式进行拟合，并且判断拟合是否成功。
	LogitLog5P formula(x + i, y + i, size - i);
	MtLMFitting slover(formula);
	auto ret = slover.fit();
	if (ret < 0) {
		return(-1);
	}
	//2.为拟合参数赋值。
	parameters[0] = (formula.get_parameters()).get_element(0, 0);
	parameters[1] = (formula.get_parameters()).get_element(1, 0);
	parameters[2] = (formula.get_parameters()).get_element(2, 0);
	parameters[3] = (formula.get_parameters()).get_element(3, 0);
	parameters[4] = (formula.get_parameters()).get_element(4, 0);
	R = formula.get_correlation_coefficient();



	return 0;
}

/// <summary>
/// logit-log 5p curve fit
/// </summary>
/// <param name="coordinates_type"></param>
/// <param name="par">a,b,c,d,e</param>
/// <param name="parameters_size">par size=5</param>
/// <param name="lum">luminous intensity</param>
/// <param name="conc">concentration</param>
/// <returns>error:0,no error</returns>
int CalibrationFactory::logit_log5P_calculate_concentration(const CoordinatesType coordinates_type
	, const double* par, int parameters_size, const double lum, double& conc)
{
	if (parameters_size != 5)
		return -8;

	//1.创建四参数矩阵，并且判断创建是否成功。
	LogitLog4P::DMat parameters;
	if (parameters.create(5, 1) < 0) {
		return(-1);
	}

	for (int i = 0; i < 5; ++i)
		parameters.set_element(i, 0, par[i]);

	//4-2.根据当前的浓度计算发光值，并且判断计算是否成功。
	if (LogitLog5P::calculate_x(parameters, lum, conc) < 0) {
		return(-6);
	}
	//5.对计算出的发光值进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, conc, conc) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。

	return 0;
}

int CalibrationFactory::logit_log5P_calculate_luminous(const CoordinatesType coordinates_type
	, const double* par, int parameters_size, const double conc, double& lum)
{
	if (parameters_size != 5)
		return -8;

	//1.创建四参数矩阵，并且判断创建是否成功。
	LogitLog5P::DMat parameters;
	if (parameters.create(5, 1) < 0) {
		return(-1);
	}

	for (int i = 0; i < 5; ++i)
		parameters.set_element(i, 0, par[i]);

	//4-2.根据当前的浓度计算发光值，并且判断计算是否成功。
	if (LogitLog5P::calculate_y(parameters, conc, lum) < 0) {
		return(-6);
	}
	//5.对计算出的发光值进行坐标变换，将其换算到x-y类型的坐标系下。
	if (convert_to_x_y_coordinates(coordinates_type, lum, lum) < 0) {
		return(-7);
	}
	//6.程序运行到此直接返回。

	return 0;
}

/***********************************************************************
 *                            纯C接口                                   *
 ***********************************************************************/

 /**
  * name: calibrate
  * breif: 定标实现。
  * param: calibration_type - 输入的定标类型。
  *        calibration_method - 输入的定标方法。
  *        experiment_method - 输入的试验方法。
  *        coordinates_type - 输入的坐标类型。
  *        is_s0_participation - 输入的s0点是否参与拟合标记。
  *        x - 输入的x数组指针。
  *        y - 输入的y数组指针。
  *        size - 输入的数组尺寸。
  *        a - 输出的定标拟合的a参数。
  *        b - 输出的定标拟合的b参数。
  *        c - 输出的定标拟合的c参数。
  *        d - 输出的定标拟合的d参数。
  *        R - 输出的定标拟合的决定系数。
  *        D - 输出的最大相对偏差。
  * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
  */
int __stdcall calibrate(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation, double* x, double* y,
	const unsigned int size,
	double* parameters, int parameters_size
	, double& R, double& xbase, double& ybase, double& xration) {
	return CalibrationFactory::calibrate(calibration_type,
		calibration_method, experiment_method, coordinates_type,
		is_s0_participation, x, y, size, parameters, parameters_size, R, xbase, ybase, xration);
}

/**
 * name: calculate_concentration
 * breif: 计算浓度。
 * param: calibration_type - 输入的定标类型。
 *        calibration_method - 输入的定标方法。
 *        experiment_method - 输入的试验方法。
 *        coordinates_type - 输入的坐标类型。
 *        is_s0_participation - 输入的s0点是否参与拟合标记。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *        size - 输入的数组尺寸。
 *        lum - 输入的发光值。
 *        conc - 输出的浓度值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall calculate_concentration(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation,
	const double* parameters, int parameters_size,
	double xration, double xbase, double ybase,
	const double lum, double& conc) {
	return CalibrationFactory::calculate_concentration(
		calibration_type, calibration_method, experiment_method,
		coordinates_type, is_s0_participation, parameters, parameters_size
		, xration, xbase, ybase
		, lum, conc);
}

/**
 * name: calculate_luminous
 * breif: 计算发光值。
 * param: calibration_type - 输入的定标类型。
 *        calibration_method - 输入的定标方法。
 *        experiment_method - 输入的试验方法。
 *        coordinates_type - 输入的坐标类型。
 *        is_s0_participation - 输入的s0点是否参与拟合标记。
 *        a - 输入的参数a。
 *        b - 输入的参数b。
 *        c - 输入的参数c。
 *        d - 输入的参数d。
 *        x - 输入的x数组指针。
 *        y - 输入的y数组指针。
 *        size - 输入的数组尺寸。
 *        conc - 输入的浓度值。
 *        lum - 输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall calculate_luminous(
	const CalibrationType calibration_type,
	const CalibrationMethod calibration_method,
	const ExperimentMethod experiment_method,
	const CoordinatesType coordinates_type,
	const bool is_s0_participation,
	const double* parameters, int parameters_size, double xration, double xbase,
	const double conc, double& lum) {
	return(CalibrationFactory::calculate_luminous(
		calibration_type, calibration_method,
		experiment_method, coordinates_type,
		is_s0_participation, parameters, parameters_size, xration, xbase,
		conc, lum));
}

/**
 * name: convert_x_y_coordinates_a
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的期望转换成的目标坐标类型。
 *        lum_0 - 输入的s0点的发光值（在x-y坐标系下的发光值）。
 *        lum - 输入/输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall convert_x_y_coordinates_a(
	const CoordinatesType target_coordinates_type,
	const double lum_0, double& lum) {
	return(CalibrationFactory::convert_x_y_coordinates(
		target_coordinates_type, lum_0, lum));
}

/**
 * name: convert_x_y_coordinates_b
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的目标坐标类型。
 *        conc - 输入/输出的浓度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall convert_x_y_coordinates_b(
	const CoordinatesType target_coordinates_type, double& conc) {
	return(CalibrationFactory::convert_x_y_coordinates(
		target_coordinates_type, conc));
}

/**
 * name: convert_to_x_y_coordinates
 * biref: 进行坐标变换，将指定类型坐标转换为x-y类型的坐标。
 * param: current_coordinates_type - 输入的当前坐标类型。
 *        conc - 输入/输出的浓度值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall convert_to_x_y_coordinates_a(
	const CoordinatesType current_coordinates_type, double& conc) {
	return(CalibrationFactory::convert_to_x_y_coordinates(
		current_coordinates_type, conc));
}

/**
 * name: convert_to_x_y_coordinates_b
 * biref: 进行坐标变换，将指定类型坐标转换为x-y类型的坐标。
 * param: current_coordinates_type - 输入的当前坐标类型。
 *        lum_0 - 输入的s0点的发光值（在x-y坐标系下的发光值）。
 *        lum - 输入/输出的发光值。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall convert_to_x_y_coordinates_b(
	const CoordinatesType current_coordinates_type, const double lum_0,
	double& lum) {
	return(CalibrationFactory::convert_to_x_y_coordinates(
		current_coordinates_type, lum_0, lum));
}

/**
 * name: convert_x_y_coordinates
 * biref: 进行坐标变换，将x-y类型坐标转换为指定类型的坐标。
 * param: target_coordinates_type - 输入的期望转换成的目标坐标类型。
 *        is_s0_participation - 输入的s0是否参与拟合标志。
 *        x - 输入/输出的x数组指针。
 *        y - 输入/输出的y数组指针。
 *        size - 输入/输出的数组尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int __stdcall convert_x_y_coordinates(
	const CoordinatesType target_coordinates_type,
	double* x, double* y, const unsigned int size) {
	return(CalibrationFactory::convert_x_y_coordinates(
		target_coordinates_type, x, y, size));
}
