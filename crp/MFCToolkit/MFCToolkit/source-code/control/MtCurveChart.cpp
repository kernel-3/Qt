#include"stdafx.h"
#include"MtCurveChart.h"
#include"../graphic/MtCoordinateAxisGraph.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtCurveGraph.h"
#include"../graphic/MtPointsGraph.h"

/**
 * name: MtCurveChart
 * breif: ���캯����
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
 * breif: ����������
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
 * breif: ����ˮƽ���귶Χ��
 * param: min - ��Сֵ��
 *        max - ���ֵ��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ���ô�ֱ���귶Χ��
 * param: min - ��Сֵ��
 *        max - ���ֵ��
 *		  is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ����ˮƽ������⡣
 * param: title - ���⡣
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ���ô�ֱ������⡣
 * param: title - ���⡣
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: �������߿�ȡ�
 * param: width - ���߿�ȡ�
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ����������ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * brief: Ϊ��ǰ�������һ���㡣
 * param: h_coordinate - �����ˮƽ����ֵ��
 *        v_coordinate - ����Ĵ�ֱ����ֵ��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveChart::add_point_to_curve(
	const double h_coordinate,const double v_coordinate,
	const BOOL is_redraw/*=FALSE*/){
	//1.�������ˮƽ����ֵ��ת��Ϊ����λ�á�
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.������Ĵ�ֱ����ֵ��ת��Ϊ����λ�á�
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.Ϊ��ǰ������ӵ㡣
	_curve->add_point(h_pixel_position,v_pixel_position);
	//4.��������������»��ƣ�����д����ػ������
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clear_points_of_curve
 * brief: ��������ϵĵ㡣
 * param: is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: Ϊ�㼯���õ�İ뾶��
 * param: radius - ��İ뾶��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: Ϊ�㼯���õ����ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
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
 * brief: Ϊ��ǰ�㼯���һ���㡣
 * param: h_coordinate - �����ˮƽ����ֵ��
 *        v_coordinate - ����Ĵ�ֱ����ֵ��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveChart::add_point_to_point_set(const double h_coordinate,
	const double v_coordinate,const BOOL is_redraw/*=FALSE*/){
	//1.�������ˮƽ����ֵ��ת��Ϊ����λ�á�
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.������Ĵ�ֱ����ֵ��ת��Ϊ����λ�á�
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.Ϊ��ǰ������ӵ㡣
	_point_set->add_point(h_pixel_position,v_pixel_position);
	//4.��������������»��ƣ�����д����ػ������
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clear_points_of_point_set
 * brief: ����㼯�ϵĵ㡣
 * param: is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ����ͼ��������⺯������������ͼ��Ļ��ƾ���
 *        �˺�����ʵ�֡�
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveChart::draw(const HDC dest_dc,MtBitmap &dest_bitmap){
	//1.���û�����ش������������жϴ����Ƿ�ɹ���
	if(MtChart::draw(dest_dc,dest_bitmap)<0){
		return(-1);
	}
	//2.���Ƶ�ǰͼ�����꣬�����жϻ����Ƿ�ɹ���
	if(_coordinates->draw(dest_dc,dest_bitmap,CRect(0,0,
		dest_bitmap.get_width(),dest_bitmap.get_height()))<0){
		return(-2);
	}
	/////////////////////////////
	//3.���Ƶ�ǰͼ���е����ߣ������жϻ����Ƿ�ɹ���
	if(_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-3);
	}
	if(m_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-3);
	}
	//4.���Ƶ�ǰͼ���еĵ㼯�������жϻ����Ƿ�ɹ���
	if(_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-4);
	}
	//4.���Ƶ�ǰͼ���еĵ㼯�������жϻ����Ƿ�ɹ���
	if(m_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
		dest_bitmap.get_height()))<0){
		return(-4);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}
//���by_ghm
/**
 * name: set_curve_two_width
 * breif: ��������2��ȡ�
 * param: width - ���߿�ȡ�
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ��������2��ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * brief: Ϊ��ǰ����2���һ���㡣
 * param: h_coordinate - �����ˮƽ����ֵ��
 *        v_coordinate - ����Ĵ�ֱ����ֵ��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveChart::add_point_to_curve_two(
	const double h_coordinate,const double v_coordinate,
	const BOOL is_redraw/*=FALSE*/){
	//1.�������ˮƽ����ֵ��ת��Ϊ����λ�á�
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.������Ĵ�ֱ����ֵ��ת��Ϊ����λ�á�
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.Ϊ��ǰ������ӵ㡣
	m_curve->add_point(h_pixel_position,v_pixel_position);
	//4.��������������»��ƣ�����д����ػ������
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clear_points_of_curve_two
 * brief: �������2�ϵĵ㡣
 * param: is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: Ϊ�㼯2���õ�İ뾶��
 * param: radius - ��İ뾶��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: Ϊ�㼯2���õ����ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
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
 * brief: Ϊ��ǰ�㼯2���һ���㡣
 * param: h_coordinate - �����ˮƽ����ֵ��
 *        v_coordinate - ����Ĵ�ֱ����ֵ��
 *        is_redraw - �Ƿ��ػ洰�ڡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCurveChart::add_point_to_point_two_set(const double h_coordinate,
	const double v_coordinate,const BOOL is_redraw/*=FALSE*/){
	//1.�������ˮƽ����ֵ��ת��Ϊ����λ�á�
	int h_pixel_position=0;
	int result=_coordinates->
		convert_horizontal_coordinate_to_pixel_position(
		h_coordinate,h_pixel_position);
	if(result<0){
		return(result);
	}
	//2.������Ĵ�ֱ����ֵ��ת��Ϊ����λ�á�
	int v_pixel_position=0;
	result=_coordinates->
		convert_vertical_coordinate_to_pixel_position(
		v_coordinate,v_pixel_position);
	if(result<0){
		return(result);
	}
	//3.Ϊ��ǰ����2��ӵ㡣
	m_point_set->add_point(h_pixel_position,v_pixel_position);
	//4.��������������»��ƣ�����д����ػ������
	if(is_redraw){
		Invalidate(TRUE);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: clear_points_of_point_two_set
 * brief: ����㼯2�ϵĵ㡣
 * param: is_redraw - �Ƿ��ػ洰�ڡ�
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
 * breif: ����ͼ��������⺯������������ͼ��Ļ��ƾ���
 *        �˺�����ʵ�֡�
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
//int MtCurveChart::draw_two(const HDC dest_dc,MtBitmap &dest_bitmap){
//	//1.���û�����ش������������жϴ����Ƿ�ɹ���
//	if(MtChart::draw(dest_dc,dest_bitmap)<0){
//		return(-1);
//	}
//	//2.���Ƶ�ǰͼ�����꣬�����жϻ����Ƿ�ɹ���
//	if(_coordinates->draw(dest_dc,dest_bitmap,CRect(0,0,
//		dest_bitmap.get_width(),dest_bitmap.get_height()))<0){
//		return(-2);
//	}
//	/////////////////////////////
//	//3.���Ƶ�ǰͼ���е����ߣ������жϻ����Ƿ�ɹ���
//	if(m_curve->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
//		dest_bitmap.get_height()))<0){
//		return(-3);
//	}
//	//4.���Ƶ�ǰͼ���еĵ㼯�������жϻ����Ƿ�ɹ���
//	if(m_point_set->draw(dest_dc,dest_bitmap,CRect(0,0,dest_bitmap.get_width(),
//		dest_bitmap.get_height()))<0){
//		return(-4);
//	}
//	//5.�������е��˳ɹ����ء�
//	return(0);
//}

