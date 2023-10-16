#include"stdafx.h"
#include"MtCurveGraph.h"
#include"MtBitmap.h"

/**
 * name: MtCurveGraph
 * breif: 构造函数。
 * param: --
 * return: --
 */
MtCurveGraph::MtCurveGraph(void)
	:MtGraph()
	,_color_a(255)
	,_color_r(0)
	,_color_g(0)
	,_color_b(255)
	,_width(1.0)
	,_points(){
}

/**
 * name: ~MtCurveGraph
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtCurveGraph::~MtCurveGraph(void){
}

/**
 * name: set_width
 * breif: 设置曲线的宽度。
 * param: width - 曲线宽度。
 * return: --
 */
void MtCurveGraph::set_width(const float width){
	_width=width;
}

/**
 * name: set_color
 * breif: 设置曲线颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
 * return: --
 */
void MtCurveGraph::set_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b){
	_color_a=color_a;
	_color_r=color_r;
	_color_g=color_g;
	_color_b=color_b;
}

/**
 * name: add_point
 * breif: 添加点。
 * param: point - 点。
 * return: --
 */
void MtCurveGraph::add_point(const CPoint &point){
	_points.push_back(point);
}

/**
 * name: add_point
 * breif: 添加点。
 * param: x - x坐标。
 *        y - y坐标。
 * return: --
 */
void MtCurveGraph::add_point(const int x,const int y){
	_points.push_back(CPoint(x,y));
}

/**
 * name: clear_points
 * breif: 清除所有的点。
 * param: --
 * return: --
 */
void MtCurveGraph::clear_points(){
	_points.clear();
	Points points;
	_points.swap(points);
}

/**
 * name: draw
 * breif: 曲线绘制虚拟函数，在此主要实现曲线绘制功能。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 *        dest_area - 目标区域。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCurveGraph::draw(const HDC dest_dc,MtBitmap &dest_bitmap,
	const CRect &dest_area){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.如果当前不存在任何点，则直接返回。
	if(_points.empty()){
		return(0);
	}
	//3.利用当前的点，进行曲线的绘制，并且判断绘制是否成功。
	if(dest_bitmap.draw_point(_color_a,_color_r,_color_g,
		_color_b,/*_width,*/&_points[0],_points.size())<0){
		return(-2);
	}
	//4.程序运行到此成功返回。
	return(0);
}