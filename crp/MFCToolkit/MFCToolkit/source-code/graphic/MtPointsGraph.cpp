#include"stdafx.h"
#include"MtPointsGraph.h"
#include"MtBitmap.h"

/**
 * name: MtPointsGraph
 * breif: 构造函数。
 * param: --
 * return: --
 */
MtPointsGraph::MtPointsGraph(void)
	:MtGraph()
	,_point_shape(POINT_SHAPE_RECTANGLE)
	,_point_radius(4)
	,_point_color_a(255)
	,_point_color_r(0)
	,_point_color_g(0)
	,_point_color_b(255)
	,_points(){
}

/**
 * name: ~MtPointsGraph
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtPointsGraph::~MtPointsGraph(void){
}

/**
 * name: set_point_shape
 * breif: 设置点的形状。
 * param: shape - 点的形状。
 * return: --
 */
void MtPointsGraph::set_point_shape(const PointShape shape){
	_point_shape=shape;
}

/**
 * name: set_point_radius
 * breif: 设置点的半径。
 * param: radius - 点的半径。
 * return: --
 */
void MtPointsGraph::set_point_radius(const unsigned int radius){
	_point_radius=radius;
}

/**
 * name: set_point_color
 * breif: 设置点的颜色。
 * param: color_a - 颜色的a分量。
 *        color_r - 颜色的r分量。
 *        color_g - 颜色的g分量。
 *        color_b - 颜色的b分量。
 * return: --
 */
void MtPointsGraph::set_point_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b){
	_point_color_a=color_a;
	_point_color_r=color_r;
	_point_color_g=color_g;
	_point_color_b=color_b;
}

/**
 * name: add_point
 * breif: 添加点。
 * param: point - 点。
 * return: --
 */
void MtPointsGraph::add_point(const CPoint &point){
	_points.push_back(point);
}

/**
 * name: add_point
 * breif: 添加点。
 * param: x - x坐标。
 *        y - y坐标。
 * return: --
 */
void MtPointsGraph::add_point(const int x,const int y){
	_points.push_back(CPoint(x,y));
}

/**
 * name: clear_points
 * breif: 清除所有的点。
 * param: --
 * return: --
 */
void MtPointsGraph::clear_points(){
	_points.clear();
	Points points;
	_points.swap(points);
}

/**
 * name: draw
 * breif: 点集绘制虚拟函数，在此主要实现点集绘制功能。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 *        dest_area - 目标区域。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtPointsGraph::draw(const HDC dest_dc,MtBitmap &dest_bitmap,
	const CRect &dest_area){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.如果当前不存在任何点，则直接返回。
	if(_points.empty()){
		return(0);
	}
	//3.利用当前的点，进行点集的绘制，并且判断绘制是否成功。
	//3-1.获取当前点数量。
	const unsigned int size=_points.size();
	//3-2.遍历点集绘制每一点。
	for(unsigned int i=0;i!=size;++i){
		//a.如果期望以矩形描述点的形状。
		if(POINT_SHAPE_RECTANGLE==_point_shape){
			if(dest_bitmap.fill_rectangle(_point_color_a,_point_color_r,
				_point_color_g,_point_color_b,_points[i].x-static_cast<int>(
				_point_radius),_points[i].y-static_cast<int>(_point_radius),
				2*static_cast<int>(_point_radius),2*static_cast<int>(_point_radius))<0){
				return(-2);
			}
		}
		//b.如果期望以圆形描述点的形状。
		else if(POINT_SHAPE_CIRCLE==_point_shape){
		}
	}
	//4.程序运行到此成功返回。
	return(0);
}