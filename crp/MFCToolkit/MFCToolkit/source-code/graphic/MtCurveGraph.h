#pragma once

#include"MtGraph.h"
#include<vector>

/**
 * name: MtCurveGraph
 * breif: 曲线图类，负责曲线数据的存储以及绘制。
 * author: yameng_he
 * date: 2015-10-30
 */
class MFC_TOOLKIT_API MtCurveGraph
	:public MtGraph{
//define
public:
	typedef std::vector<CPoint> Points;
//construction & destruction
public:
	MtCurveGraph(void);
	virtual ~MtCurveGraph(void);
//interface
public:
	void set_width(const float width);
	void set_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b);
	void add_point(const CPoint &point);
	void add_point(const int x,const int y);
	void clear_points();
//overrides
public:
	virtual int draw(const HDC dest_dc,
		MtBitmap &dest_bitmap,const CRect &dest_area);
//variables
private:
	float _width;
	unsigned char _color_a;
	unsigned char _color_r;
	unsigned char _color_g;
	unsigned char _color_b;
	Points _points;
};