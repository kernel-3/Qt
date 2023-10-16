#pragma once

#include"MtGraph.h"
#include<vector>

/**
 * name: MtPointsGraph
 * breif: 点集图形类，负责点集的绘制以及数据的存储。
 * author: yameng_he
 * date: 2015-11-08
 */
class MFC_TOOLKIT_API MtPointsGraph
	:public MtGraph{
//define
public:
	typedef std::vector<CPoint> Points;
	typedef enum{POINT_SHAPE_RECTANGLE,POINT_SHAPE_CIRCLE,}PointShape;
//construction & destruction
public:
	MtPointsGraph(void);
	virtual ~MtPointsGraph(void);
//interface
public:
	void set_point_shape(const PointShape shape);
	void set_point_radius(const unsigned int radius);
	void set_point_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b);
	void add_point(const CPoint &point);
	void add_point(const int x,const int y);
	void clear_points();
//overrides
public:
	virtual int draw(const HDC dest_dc,MtBitmap &dest_bitmap,
		const CRect &dest_area);
//variables
private:
	PointShape _point_shape;
	unsigned int _point_radius;
	unsigned char _point_color_a;
	unsigned char _point_color_r;
	unsigned char _point_color_g;
	unsigned char _point_color_b;
	Points _points;
};
