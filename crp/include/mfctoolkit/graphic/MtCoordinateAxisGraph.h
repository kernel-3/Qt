#pragma once

#include"MtGraph.h"

/**
 * name: MtCoordinateAxisGraph
 * breif: 坐标轴图形类，负责存储坐标轴数据，并且
 *        实现绘制坐标轴的功能。
 * author: yameng_he
 * date: 2015-10-28
 */
class MFC_TOOLKIT_API MtCoordinateAxisGraph
	:public MtGraph{
//define
public:
	enum{MARGIN=20,SPACING=15,SCALE_MARK_SIZE=5,
		 H_SCALE_SPACING=10,V_SCALE_SPACING=30,};
//construction & destruction
public:
	MtCoordinateAxisGraph(void);
	virtual ~MtCoordinateAxisGraph(void);
//interface
public:
	void set_horizontal_axis_range(const double min,const double max);
	void set_vertical_axis_range(const double min,const double max);
	void set_background_color(const unsigned char color_a,
		const unsigned char color_r,
		const unsigned char color_g,
		const unsigned char color_b);
	void set_axis_color(const unsigned char color_a,
		const unsigned char color_r,
		const unsigned char color_g,
		const unsigned char color_b);
	void set_grid_color(const unsigned char color_a,
		const unsigned char color_r,
		const unsigned char color_g,
		const unsigned char color_b);
	void set_text_color(const unsigned char color_a,
		const unsigned char color_r,
		const unsigned char color_g,
		const unsigned char color_b);
	void show_grid(const BOOL is_visible);
	void set_horizontal_axis_title(const CString &title);
	void set_vertical_axis_title(const CString &title);
	int convert_horizontal_coordinate_to_pixel_position(
		const double coordinate,int &position) const;
	int convert_vertical_coordinate_to_pixel_position(
		const double coordinate,int &position) const;
//interface
public:
	virtual int draw(const HDC dest_dc,
		MtBitmap &dest_bitmap,const CRect &dest_area);
//implement
private:
	int draw_axis(const HDC dest_dc,MtBitmap &dest_bitmap,
		const CSize &h_axis_scale_size,const CSize &v_axis_scale_size) const;
	int draw_tilte(const HDC dest_dc,MtBitmap &dest_bitmap,
		const CSize &h_axis_scale_size,const CSize &v_axis_scale_size,
		const CSize &h_axis_tile_size,const CSize &v_axis_title_size) const;
	int calculate_scale_size(const HDC dest_dc,
		CSize &h_axis_scale_size,CSize &v_axis_scale_size) const;
	int calculate_title_size(const HDC dest_dc,
		CSize &h_axis_title_size,CSize &v_axis_title_size) const;
	int calculate_horizontal_axis_scale(const int position,double &scale) const;
	CString calculate_horizontal_axis_scale_text(const int position) const;
	int calculate_vertical_axis_scale(const int position,double &scale) const;
	CString calculate_vertical_axis_scale_text(const int pixel_position) const;
//variables
private:
	double _min_h;
	double _max_h;
	double _min_v;
	double _max_v;
	unsigned char _background_color_a;
	unsigned char _background_color_r;
	unsigned char _background_color_g;
	unsigned char _background_color_b;
	unsigned char _axis_color_a;
	unsigned char _axis_color_r;
	unsigned char _axis_color_g;
	unsigned char _axis_color_b;
	unsigned char _grid_color_a;
	unsigned char _grid_color_r;
	unsigned char _grid_color_g;
	unsigned char _grid_color_b;
	unsigned char _text_color_a;
	unsigned char _text_color_r;
	unsigned char _text_color_g;
	unsigned char _text_color_b;
	BOOL _is_grid_visible;
	CString _horizontal_axis_title;
	CString _vertical_axis_title;
	CFont *_scale_font;
	CFont *_title_font;
	CRect _axis_area;
};

