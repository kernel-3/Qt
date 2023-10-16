#pragma once

#include"../Symbol"

/************************************************************************************************
 *                                     C++接口                                                  *
 ************************************************************************************************/

 /**
  * name: CalibrationFactory
  * breif: 定标工厂，负责实现各种定标算法。
  * author: yameng_he
  * date: 2015-10-21
  */
class ALGORITHM_API CalibrationFactory {
	//define
public:
	typedef enum {
		CALIBRATION_TYPE_MULTIPOINT = 0,//多点定标。
		CALIBRATION_ONE_POINT = 1,//一点定标。
		CALIBRATION_TWO_POINT = 2,//两点定标。
	}CalibrationType;
	typedef enum {
		CALIBRATION_METHOD_LINEAR = 0,//线性。
		CALIBRATION_METHOD_CUBIC_POLYNOMIAL = 4,//三次多项式。
		CALIBRATION_METHOD_LOGIT_LOG4P = 5,//四参数。
		CALIBRATION_METHOD_LOGIT_LOG5P = 6,
	}CalibrationMethod;
	typedef enum {
		EXPERIMENT_METHOD_SANDWICH = 0,//夹心法。
		EXPERIMENT_METHOD_COMPETITION = 1,//竞争法。
		EXPERIMENT_METHOD_INDIRECT = 2,//间接法。
		EXPERIMENT_METHOD_CAPTURE = 3,//捕获法。
	}ExperimentMethod;
	typedef enum {
		COORDINATES_TYPE_LOGX_LOGITY = 0,//log(x)-logit(y)
		COORDINATES_TYPE_LOGX_LOGY = 1,//log(x)-log(y)
		COORDINATES_TYPE_X_Y = 2,//x-y
		COORDINATES_TYPE_LOGX_Y = 3,//log(x)-y
		COORDINATES_TYPE_X_LOGY = 4,//x-log(y)
	}CoordinatesType;
	static const double TINY;
	//interface
public:
	//定标实现（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
	static int calibrate(
		const CalibrationType calibration_type,//输入的定标类型。
		const CalibrationMethod calibration_method,//输入的定标方法。
		const ExperimentMethod experiment_method,//输入的试验方法。
		const CoordinatesType coordinates_type,//输入的坐标类型。
		const bool is_s0_participation,//标记s0点是否参与拟合。
		double* x, double* y, const unsigned int size,//输入的x、y数组，以及数组尺寸。
		double*, int,
		double& R, double& xbase, double& ybase, double& xration);//R是决定系数、D是最大相对偏差。
	//浓度计算（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
	static int calculate_concentration(
		const CalibrationType calibration_type,//输入的定标类型。
		const CalibrationMethod calibration_method,//输入的定标方法。
		const ExperimentMethod experiment_method,//输入的试验方法。
		const CoordinatesType coordinates_type,//输入的坐标类型。
		const bool is_s0_participation,//标记s0点是否参与拟合。
		const double* params, int params_size,
		double xration, double xbase, double ybase,
		const double lum, double& conc);//lum - 输入的发光值。 conc - 输出的浓度。
	//发光值计算（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
	static int calculate_luminous(
		const CalibrationType calibration_type,//输入的定标类型。
		const CalibrationMethod calibration_method,//输入的定标方法。
		const ExperimentMethod experiment_method,//输入的试验方法。
		const CoordinatesType coordinates_type,//输入的坐标类型。
		const bool is_s0_participation,//标记s0点是否参与拟合。
		const double*, int, double xration, double xbase,
		const double conc, double& lum);//conc - 输入的浓度 lum - 输出的发光值。
	//坐标变换。
	static int convert_x_y_coordinates(const CoordinatesType
		target_coordinates_type, const double lum_0, double& lum);
	static int convert_x_y_coordinates(const CoordinatesType
		target_coordinates_type, double& conc);
	static int convert_to_x_y_coordinates(const CoordinatesType
		current_coordinates_type, double& conc);
	static int convert_to_x_y_coordinates(const CoordinatesType
		current_coordinates_type, const double lum_0, double& lum);
	static int convert_x_y_coordinates(
		const CoordinatesType target_coordinates_type,
		double* x, double* y, const unsigned int size);
	//implement
private:
	static int linear_calibrate(
		const bool is_s0_participation,
		double* x, double* y, const unsigned int size,
		double* parameters, int parameters_size,
		double& R, double& D);
	static int cubic_polynomial_calibrate(
		const unsigned int is_s0_participation,
		double* x, double* y, const unsigned int size,
		double* parameters, int parameters_size,
		double& R, double& D);
	static int logit_log4P_calibrate(
		const unsigned int is_s0_participation,
		double* x, double* y, const unsigned int size,
		double* parameters, int parameters_size,
		double& R, double& D);
	static int linear_calculate_concentration(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double lum, double& conc);
	static int cubic_polynomial_calculate_concentration(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double lum, double& conc);
	static int logit_log4P_calculate_concentration(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double lum, double& conc);
	static int linear_calculate_luminous(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double conc, double& lum);
	static int cubic_polynomial_calculate_luminous(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double conc, double& lum);
	static int logit_log4P_calculate_luminous(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double conc, double& lum);
	static int logit_log5P_calibrate(
		const unsigned int is_s0_participation,
		double* x, double* y, const unsigned int size,
		double* parameters, int parameters_size,
		double& R, double& xbase, double& ybase);
	static int logit_log5P_calculate_concentration(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double lum, double& conc);
	static int logit_log5P_calculate_luminous(
		const CoordinatesType coordinates_type,
		const double* parameters, int parameters_size,
		const double conc, double& lum);


	//restriction
private:
	CalibrationFactory(void);
	CalibrationFactory(const CalibrationFactory&);
	~CalibrationFactory(void);
	CalibrationFactory& operator=(const CalibrationFactory&);
};

/************************************************************************************************
 *                                     纯C接口                                                   *
 ************************************************************************************************/
 //定义
typedef CalibrationFactory::CalibrationType CalibrationType;
typedef CalibrationFactory::CalibrationMethod CalibrationMethod;
typedef CalibrationFactory::ExperimentMethod ExperimentMethod;
typedef CalibrationFactory::CoordinatesType CoordinatesType;
//纯C接口
//定标实现（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
extern"C" ALGORITHM_API int __stdcall calibrate(
	const CalibrationType calibration_type,//输入的定标类型。
	const CalibrationMethod calibration_method,//输入的定标方法。
	const ExperimentMethod experiment_method,//输入的试验方法。
	const CoordinatesType coordinates_type,//输入的坐标类型。
	const bool is_s0_participation,//标记s0点是否参与拟合。
	double* x, double* y, const unsigned int size,//输入的x、y数组，以及数组尺寸。
	double* parameters, int parameters_size,//输出函数拟合的参数a，b，c，d（线性拟合中只用到a,b）。
	double& R, double& xbase, double& ybase, double& xration);//R是决定系数、D是最大相对偏差。
//浓度计算（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
extern"C" ALGORITHM_API int __stdcall calculate_concentration(
	const CalibrationType calibration_type,//输入的定标类型。
	const CalibrationMethod calibration_method,//输入的定标方法。
	const ExperimentMethod experiment_method,//输入的试验方法。
	const CoordinatesType coordinates_type,//输入的坐标类型。
	const bool is_s0_participation,//标记s0点是否参与拟合。
	const double* parameters, int parameters_size,
	double xration, double xbase, double ybase,
	const double lum, double& conc);//lum - 输入的发光值。 conc - 输出的浓度。
//发光值计算（如果函数执行成功返回值大于等于零，否则返回负数标识错误）。
extern"C" ALGORITHM_API int __stdcall calculate_luminous(
	const CalibrationType calibration_type,//输入的定标类型。
	const CalibrationMethod calibration_method,//输入的定标方法。
	const ExperimentMethod experiment_method,//输入的试验方法。
	const CoordinatesType coordinates_type,//输入的坐标类型。
	const bool is_s0_participation,//标记s0点是否参与拟合。
	const double* parameters, int parameters_size, double xration, double xbase,
	const double conc, double& lum);//conc - 输入的浓度 lum - 输出的发光值。
//坐标变换。
extern"C" ALGORITHM_API int __stdcall convert_x_y_coordinates_a(
	const CoordinatesType target_coordinates_type, const double lum_0, double& lum);
extern"C" ALGORITHM_API int __stdcall convert_x_y_coordinates_b(
	const CoordinatesType target_coordinates_type, double& conc);
extern"C" ALGORITHM_API int __stdcall convert_to_x_y_coordinates_a(
	const CoordinatesType current_coordinates_type, double& conc);
extern"C" ALGORITHM_API int __stdcall convert_to_x_y_coordinates_b(
	const CoordinatesType current_coordinates_type, const double lum_0, double& lum);
extern"C" ALGORITHM_API int __stdcall convert_x_y_coordinates(
	const CoordinatesType target_coordinates_type, double* x, double* y, const unsigned int size);
