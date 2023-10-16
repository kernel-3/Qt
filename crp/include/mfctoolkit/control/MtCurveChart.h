#pragma once

#include"MtChart.h"

class MtCoordinateAxisGraph;
class MtCurveGraph;
class MtPointsGraph;

/**
 * name: MtCurveChart
 * breif: “曲线”图表控件,负责实现曲线图表功能。
 * author: yameng_he
 * date: 2015-10-30
 */
class MFC_TOOLKIT_API MtCurveChart
	:public MtChart{
//construction & destruction
public:
	MtCurveChart(void);
	virtual ~MtCurveChart(void);
//interface
public:
	void set_horizontal_coordinate_range(const double min,
		const double max,const BOOL is_redraw=FALSE);
	void set_vertical_coordinate_range(const double min,
		const double max,const BOOL is_redraw=FALSE);
	void set_horizontal_coordinate_title(const CString &title,
		const BOOL is_redraw=FALSE);
	void set_vertical_coordinate_title(const CString &title,
		const BOOL is_redraw=FALSE);
	void set_curve_width(const float width,const BOOL is_redraw=FALSE);
	void set_curve_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_redraw=FALSE);
	int add_point_to_curve(const double h_coordinate,
		const double v_coordinate,const BOOL is_redraw=FALSE);
	void clear_points_of_curve(const BOOL is_redraw=FALSE);
	void set_point_radius_to_point_set(
		const unsigned int radius,const BOOL is_redraw=FALSE);
	void set_point_color_to_point_set(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_redraw=FALSE);
	int add_point_to_point_set(const double h_coordinate,
		const double v_coordinate,const BOOL is_redraw=FALSE);
	void clear_points_of_point_set(const BOOL is_redraw=FALSE);
	//2017.03.02
	void set_curve_two_width(const float width,const BOOL is_redraw=FALSE);
	void set_curve_two_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_redraw=FALSE);
	int add_point_to_curve_two(const double h_coordinate,
		const double v_coordinate,const BOOL is_redraw=FALSE);
	void clear_points_of_curve_two(const BOOL is_redraw=FALSE);
	void set_point_radius_to_point_two_set(
		const unsigned int radius,const BOOL is_redraw=FALSE);
	void set_point_color_to_point_two_set(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_redraw=FALSE);
	int add_point_to_point_two_set(const double h_coordinate,
		const double v_coordinate,const BOOL is_redraw=FALSE);
	void clear_points_of_point_two_set(const BOOL is_redraw=FALSE);
//overrides
protected:
	int draw(const HDC dest_dc,MtBitmap &dest_bitmap);
	//int draw_two(const HDC dest_dc,MtBitmap &dest_bitmap);
//variables
private:
	MtCoordinateAxisGraph *_coordinates;
	MtCurveGraph *_curve;
	MtCurveGraph *m_curve;
	MtPointsGraph *_point_set;
	MtPointsGraph *m_point_set;
};

