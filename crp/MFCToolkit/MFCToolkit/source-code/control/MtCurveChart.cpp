#include"stdafx.h"
#include"MtCurveChart.h"
#include"../graphic/MtCoordinateAxisGraph.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtCurveGraph.h"
#include"../graphic/MtPointsGraph.h"

/**
 * name: MtCurveChart
 * breif: 构造函数。
 * param: --
 * return: --
 */
MtCurveChart::MtCurveChart(void)
	:MtChart()
	,_coordinates(new MtCoordinateAxisGraph)
	,_curve(new MtCurveGraph)
	,_point_set(new MtPointsGraph)
    ,m_curve(new MtCurveGraph)
	,m_point_set(new MtPointsGraph){
}

/**
 * name: ~MtCurveChart
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtCurveChart::~MtCurveChart(void){
	delete _coordinates;
	delete _curve;
	delete _point_set;
	delete m_curve;
	delete m_point_set;
}

/**
 * name: set_horizontal_coordinate_range
 * breif: 设置水平坐标范围。
 * param: min - 最小值。
 *        max - 最大值。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_horizontal_coordinate_range(
	const double min,const double max,const BOOL is_redraw/*=FALSE*/){
	_coordinates->set_horizontal_axis_range(min,max);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_vertical_coordinate_range
 * breif: 设置垂直坐标范围。
 * param: min - 最小值。
 *        max - 最大值。
 *		  is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_vertical_coordinate_range(
	const double min,const double max,const BOOL is_redraw/*=FALSE*/){
	_coordinates->set_vertical_axis_range(min,max);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_horizontal_coordinate_title
 * breif: 设置水平坐标标题。
 * param: title - 标题。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_horizontal_coordinate_title(
	const CString &title,const BOOL is_redraw/*=FALSE*/){
	_coordinates->set_horizontal_axis_title(title);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_vertical_coordinate_title
 * breif: 设置垂直坐标标题。
 * param: title - 标题。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_vertical_coordinate_title(
	const CString &title,const BOOL is_redraw/*=FALSE*/){
	_coordinates->set_vertical_axis_title(title);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_curve_width
 * breif: 设置曲线宽度。
 * param: width - 曲线宽度。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_curve_width(
	const float width,const BOOL is_redraw/*=FALSE*/){
	_curve->set_width(width);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_curve_color
 * breif: 设置曲线颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_curve_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_redraw/*=FALSE*/){
	_curve->set_color(color_a,color_r,color_g,color_b);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: add_point_to_curve
 * brief: 为当前曲线添加一个点。
 * param: h_coordinate - 输入的水平坐标值。
 *        v_coordinate - 输入的垂直坐标值。
 *        is_redraw - 是否重绘窗口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveChart::add_point_to_curve(
	const double h_coordinate,const double v_coordinate,
	const BOOL is_redraw/*=FALSE*/){
	//1.将输入的水平坐标值，转换为像素位置。
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.将输入的垂直坐标值，转换为像素位置。
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.为当前曲线添加点。
	_curve->add_point(h_pixel_position,v_pixel_position);
	//4.如果期望窗口重新绘制，则进行窗口重绘操作。
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: clear_points_of_curve
 * brief: 清除曲线上的点。
 * param: is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::clear_points_of_curve(
	const BOOL is_redraw/*=FALSE*/){
	_curve->clear_points();
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_point_radius_to_point_set
 * breif: 为点集设置点的半径。
 * param: radius - 点的半径。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_point_radius_to_point_set(
	const unsigned int radius,const BOOL is_redraw/*=FALSE*/){
	_point_set->set_point_radius(radius);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_point_color_to_point_set
 * breif: 为点集设置点的颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
 * return: --
 */
void MtCurveChart::set_point_color_to_point_set(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,
	const BOOL is_redraw/*=FALSE*/){
	_point_set->set_point_color(color_a,color_r,color_g,color_b);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: add_point_to_point_set
 * brief: 为当前点集添加一个点。
 * param: h_coordinate - 输入的水平坐标值。
 *        v_coordinate - 输入的垂直坐标值。
 *        is_redraw - 是否重绘窗口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveChart::add_point_to_point_set(const double h_coordinate,
	const double v_coordinate,const BOOL is_redraw/*=FALSE*/){
	//1.将输入的水平坐标值，转换为像素位置。
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.将输入的垂直坐标值，转换为像素位置。
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.为当前曲线添加点。
	_point_set->add_point(h_pixel_position,v_pixel_position);
	//4.如果期望窗口重新绘制，则进行窗口重绘操作。
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: clear_points_of_point_set
 * brief: 清除点集上的点。
 * param: is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::clear_points_of_point_set(
	const BOOL is_redraw/*=FALSE*/){
	_point_set->clear_points();
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: draw
 * breif: 曲线图表绘制虚拟函数，所有曲线图标的绘制均从
 *        此函数中实现。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveChart::draw(const HDC dest_dc,MtBitmap &dest_bitmap){
	//1.调用基类相关处理函数，并且判断处理是否成功。
	if(MtChart::draw(dest_dc,dest_bitmap)<0){
		return(-1);
	}
	//2.绘制当前图表坐标，并且判断绘制是否成功。
	if(_coordinates->draw(dest_dc,dest_bitmap,CRect(0,0,
		dest_bitmap.get_width(),dest_bitmap.get_height()))<0){
		return(-2);
	}
	/////////////////////////////
	//3.绘制当前图表中的曲线，并且判断绘制是否成功。
	if(_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-3);
	}
	if(m_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-3);
	}
	//4.绘制当前图表中的点集，并且判断绘制是否成功。
	if(_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-4);
	}
	//4.绘制当前图表中的点集，并且判断绘制是否成功。
	if(m_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-4);
	}
	//5.程序运行到此成功返回。
	return(0);
}
//添加by_ghm
/**
 * name: set_curve_two_width
 * breif: 设置曲线2宽度。
 * param: width - 曲线宽度。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_curve_two_width(
	const float width,const BOOL is_redraw/*=FALSE*/){
	m_curve->set_width(width);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_curve_two_color
 * breif: 设置曲线2颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_curve_two_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_redraw/*=FALSE*/){
	m_curve->set_color(color_a,color_r,color_g,color_b);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: add_point_to_curve_two
 * brief: 为当前曲线2添加一个点。
 * param: h_coordinate - 输入的水平坐标值。
 *        v_coordinate - 输入的垂直坐标值。
 *        is_redraw - 是否重绘窗口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveChart::add_point_to_curve_two(
	const double h_coordinate,const double v_coordinate,
	const BOOL is_redraw/*=FALSE*/){
	//1.将输入的水平坐标值，转换为像素位置。
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.将输入的垂直坐标值，转换为像素位置。
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.为当前曲线添加点。
	m_curve->add_point(h_pixel_position,v_pixel_position);
	//4.如果期望窗口重新绘制，则进行窗口重绘操作。
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: clear_points_of_curve_two
 * brief: 清除曲线2上的点。
 * param: is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::clear_points_of_curve_two(
	const BOOL is_redraw/*=FALSE*/){
	m_curve->clear_points();
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_point_radius_to_point_two_set
 * breif: 为点集2设置点的半径。
 * param: radius - 点的半径。
 *        is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::set_point_radius_to_point_two_set(
	const unsigned int radius,const BOOL is_redraw/*=FALSE*/){
	m_point_set->set_point_radius(radius);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: set_point_color_to_point_two_set
 * breif: 为点集2设置点的颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
 * return: --
 */
void MtCurveChart::set_point_color_to_point_two_set(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,
	const BOOL is_redraw/*=FALSE*/){
	m_point_set->set_point_color(color_a,color_r,color_g,color_b);
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: add_point_to_point_set
 * brief: 为当前点集2添加一个点。
 * param: h_coordinate - 输入的水平坐标值。
 *        v_coordinate - 输入的垂直坐标值。
 *        is_redraw - 是否重绘窗口。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveChart::add_point_to_point_two_set(const double h_coordinate,
	const double v_coordinate,const BOOL is_redraw/*=FALSE*/){
	//1.将输入的水平坐标值，转换为像素位置。
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.将输入的垂直坐标值，转换为像素位置。
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.为当前曲线2添加点。
	m_point_set->add_point(h_pixel_position,v_pixel_position);
	//4.如果期望窗口重新绘制，则进行窗口重绘操作。
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: clear_points_of_point_two_set
 * brief: 清除点集2上的点。
 * param: is_redraw - 是否重绘窗口。
 * return: --
 */
void MtCurveChart::clear_points_of_point_two_set(
	const BOOL is_redraw/*=FALSE*/){
	m_point_set->clear_points();
	if(is_redraw){
		Invalidate(TRUE);
	}
}

/**
 * name: draw
 * breif: 曲线图表绘制虚拟函数，所有曲线图标的绘制均从
 *        此函数中实现。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
//int MtCurveChart::draw_two(const HDC dest_dc,MtBitmap &dest_bitmap){
//	//1.调用基类相关处理函数，并且判断处理是否成功。
//	if(MtChart::draw(dest_dc,dest_bitmap)<0){
//		return(-1);
//	}
//	//2.绘制当前图表坐标，并且判断绘制是否成功。
//	if(_coordinates->draw(dest_dc,dest_bitmap,CRect(0,0,
//		dest_bitmap.get_width(),dest_bitmap.get_height()))<0){
//		return(-2);
//	}
//	/////////////////////////////
//	//3.绘制当前图表中的曲线，并且判断绘制是否成功。
//	if(m_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
//		dest_bitmap.get_height()))<0){
//		return(-3);
//	}
//	//4.绘制当前图表中的点集，并且判断绘制是否成功。
//	if(m_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
//		dest_bitmap.get_height()))<0){
//		return(-4);
//	}
//	//5.程序运行到此成功返回。
//	return(0);
//}

