#include"stdafx.h"
#include"MtPointsGraph.h"
#include"MtBitmap.h"

/**
 * name: MtPointsGraph
 * breif: ���캯����
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
 * breif: ����������
 * param: --
 * return: --
 */
MtPointsGraph::~MtPointsGraph(void){
}

/**
 * name: set_point_shape
 * breif: ���õ����״��
 * param: shape - �����״��
 * return: --
 */
void MtPointsGraph::set_point_shape(const PointShape shape){
	_point_shape=shape;
}

/**
 * name: set_point_radius
 * breif: ���õ�İ뾶��
 * param: radius - ��İ뾶��
 * return: --
 */
void MtPointsGraph::set_point_radius(const unsigned int radius){
	_point_radius=radius;
}

/**
 * name: set_point_color
 * breif: ���õ����ɫ��
 * param: color_a - ��ɫ��a������
 *        color_r - ��ɫ��r������
 *        color_g - ��ɫ��g������
 *        color_b - ��ɫ��b������
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
 * breif: ��ӵ㡣
 * param: point - �㡣
 * return: --
 */
void MtPointsGraph::add_point(const CPoint &point){
	_points.push_back(point);
}

/**
 * name: add_point
 * breif: ��ӵ㡣
 * param: x - x���ꡣ
 *        y - y���ꡣ
 * return: --
 */
void MtPointsGraph::add_point(const int x,const int y){
	_points.push_back(CPoint(x,y));
}

/**
 * name: clear_points
 * breif: ������еĵ㡣
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
 * breif: �㼯�������⺯�����ڴ���Ҫʵ�ֵ㼯���ƹ��ܡ�
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 *        dest_area - Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtPointsGraph::draw(const HDC dest_dc,MtBitmap &dest_bitmap,
	const CRect &dest_area){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.�����ǰ�������κε㣬��ֱ�ӷ��ء�
	if(_points.empty()){
		return(0);
	}
	//3.���õ�ǰ�ĵ㣬���е㼯�Ļ��ƣ������жϻ����Ƿ�ɹ���
	//3-1.��ȡ��ǰ��������
	const unsigned int size=_points.size();
	//3-2.�����㼯����ÿһ�㡣
	for(unsigned int i=0;i!=size;++i){
		//a.��������Ծ������������״��
		if(POINT_SHAPE_RECTANGLE==_point_shape){
			if(dest_bitmap.fill_rectangle(_point_color_a,_point_color_r,
				_point_color_g,_point_color_b,_points[i].x-static_cast<int>(
				_point_radius),_points[i].y-static_cast<int>(_point_radius),
				2*static_cast<int>(_point_radius),2*static_cast<int>(_point_radius))<0){
				return(-2);
			}
		}
		//b.���������Բ�����������״��
		else if(POINT_SHAPE_CIRCLE==_point_shape){
		}
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}