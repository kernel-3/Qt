#include"stdafx.h"
#include"MtCurveGraph.h"
#include"MtBitmap.h"

/**
 * name: MtCurveGraph
 * breif: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
MtCurveGraph::~MtCurveGraph(void){
}

/**
 * name: set_width
 * breif: �������ߵĿ�ȡ�
 * param: width - ���߿�ȡ�
 * return: --
 */
void MtCurveGraph::set_width(const float width){
	_width=width;
}

/**
 * name: set_color
 * breif: ����������ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
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
 * breif: ��ӵ㡣
 * param: point - �㡣
 * return: --
 */
void MtCurveGraph::add_point(const CPoint &point){
	_points.push_back(point);
}

/**
 * name: add_point
 * breif: ��ӵ㡣
 * param: x - x���ꡣ
 *        y - y���ꡣ
 * return: --
 */
void MtCurveGraph::add_point(const int x,const int y){
	_points.push_back(CPoint(x,y));
}

/**
 * name: clear_points
 * breif: ������еĵ㡣
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
 * breif: ���߻������⺯�����ڴ���Ҫʵ�����߻��ƹ��ܡ�
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 *        dest_area - Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveGraph::draw(const HDC dest_dc,MtBitmap &dest_bitmap,
	const CRect &dest_area){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.�����ǰ�������κε㣬��ֱ�ӷ��ء�
	if(_points.empty()){
		return(0);
	}
	//3.���õ�ǰ�ĵ㣬�������ߵĻ��ƣ������жϻ����Ƿ�ɹ���
	if(dest_bitmap.draw_point(_color_a,_color_r,_color_g,
		_color_b,/*_width,*/&_points[0],_points.size())<0){
		return(-2);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}