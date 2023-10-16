#include"stdafx.h"
#include"MtCoordinateAxisGraph.h"
#include"../env/MtGdiplus.h"
#include"MtBitmap.h"

/**
 * name: MtCoordinateAxisGraph
 * breif: ���캯����
 * param: --
 * return: --
 */
MtCoordinateAxisGraph::MtCoordinateAxisGraph(void)
	:MtGraph()
	,_min_h(0.0)
	,_max_h(100.0)
	,_min_v(0.0)
	,_max_v(100.0)
	,_background_color_a(255)
	,_background_color_r(255)
	,_background_color_g(255)
	,_background_color_b(255)
	,_axis_color_a(255)
	,_axis_color_r(0)
	,_axis_color_g(0)
	,_axis_color_b(0)
	,_grid_color_a(230)
	,_grid_color_r(230)
	,_grid_color_g(230)
	,_grid_color_b(230)
	,_text_color_a(255)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0)
	,_is_grid_visible(TRUE)
	,_horizontal_axis_title(_T("X"))
	,_vertical_axis_title(_T("Y"))
	,_scale_font(new CFont)
	,_title_font(new CFont)
	,_axis_area(0,0,0,0){
	//1.�����̶����塣
	LOGFONT log={15,0,0,0,FW_NORMAL,0,0,0,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,_T("Microsoft Sans Serif")};
	_scale_font->CreateFontIndirect(&log);
	//2.�����������塣
	LOGFONT log_t={20,0,0,0,FW_HEAVY,0,0,0,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,_T("Microsoft Sans Serif")};
	_title_font->CreateFontIndirect(&log_t);
}

/**
 * name: ~MtCoordinateAxisGraph
 * breif: ����������
 * param: --
 * return: --
 */
MtCoordinateAxisGraph::~MtCoordinateAxisGraph(void){
	//1.�ͷſ̶����塣
	if((0!=_scale_font->GetSafeHandle())&&(
		INVALID_HANDLE_VALUE!=_scale_font->GetSafeHandle())){
		_scale_font->DeleteObject();
	}
	delete _scale_font;
	//2.�ͷű������塣
	if((0!=_title_font->GetSafeHandle())&&(
		INVALID_HANDLE_VALUE!=_title_font->GetSafeHandle())){
		_title_font->DeleteObject();
	}
	delete _title_font;
}

/**
 * name: set_horizontal_axis_range
 * brief: ���ú��᷶Χ��
 * param: min - ��Сֵ��
 *        max - ���ֵ��
 * return: --
 */
void MtCoordinateAxisGraph::set_horizontal_axis_range(
	const double min,const double max){
	if(min<max){
		_min_h=min;
		_max_h=max;
	}else{
		_min_h=max;
		_max_h=min;
	}
}

/**
 * name: set_vertical_axis_range
 * breif: �������᷶Χ��
 * param: min - ��Сֵ��
 *        max - ���ֵ��
 * return: --
 */
void MtCoordinateAxisGraph::set_vertical_axis_range(
	const double min,const double max){
	if(min<max){
		_min_v=min;
		_max_v=max;
	}else{
		_min_v=max;
		_max_v=min;
	}
}

/**
 * name: set_background_color
 * breif: ���ñ�����ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtCoordinateAxisGraph::set_background_color(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_background_color_a=color_a;
	_background_color_r=color_r;
	_background_color_g=color_g;
	_background_color_b=color_b;
}

/**
 * name: set_axis_color
 * brief: ���������ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtCoordinateAxisGraph::set_axis_color(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_axis_color_a=color_a;
	_axis_color_r=color_r;
	_axis_color_g=color_g;
	_axis_color_b=color_b;
}

/**
 * name: set_grid_color
 * breif: ����������ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtCoordinateAxisGraph::set_grid_color(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_grid_color_a=color_a;
	_grid_color_r=color_r;
	_grid_color_g=color_g;
	_grid_color_b=color_b;
}

/**
 * name: set_text_color
 * breif: �����ı���ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtCoordinateAxisGraph::set_text_color(
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
}

/**
 * name: show_grid
 * breif: ��ʾ����
 * param: is_visible - ��ǵ�ǰ�����Ƿ���ӡ�
 * return: --
 */
void MtCoordinateAxisGraph::show_grid(const BOOL is_visible){
	_is_grid_visible=is_visible;
}

/**
 * name: set_horizontal_axis_title
 * breif: ���ú�����⡣
 * param: title - ������⡣
 * return: --
 */
void MtCoordinateAxisGraph::set_horizontal_axis_title(
	const CString &title){
	_horizontal_axis_title=title;
}

/**
 * name: set_vertical_axis_title
 * breif: ����������⡣
 * param: title - ������⡣
 * return: --
 */
void MtCoordinateAxisGraph::set_vertical_axis_title(
	const CString &title){
	_vertical_axis_title=title;
}

/**
 * name: convert_horizontal_coordinate_to_pixel_position
 * breif: ��������ֵת��Ϊ����λ�á�
 * param: coordinate - ����ĺ�����ֵ��
 *        position - ���������λ�á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::convert_horizontal_coordinate_to_pixel_position(
	const double coordinate,int &position) const{
	//1.�����ǰ����ĺ�����ֵ��������ϵ��ʵ�ʵ���ʾ��Χ����ֱ�ӷ��ش���
	if((coordinate<_min_h)||(coordinate>_max_h)){
		return(-1);
	}
	//2.�����ǰ����������δȷ������ֱ�ӷ��ش���
	if(_axis_area.IsRectEmpty()){
		return(-2);
	}
	//3.����ÿ������ֵ�������ص�ֵ��
	double pixel_value=static_cast<double>(_axis_area.Width())/(_max_h-_min_h);
	if((fabs(pixel_value)<1.0E-20)||(pixel_value<0.0)){
		return(-3);
	}
	//4.��������ֵ����Ϊ����λ�á�
	position=_axis_area.left+static_cast<int>((coordinate-_min_h)*pixel_value);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: convert_vertical_coordinate_to_pixel_position
 * breif: ��������ֵת��Ϊ����λ�á�
 * param: coordinate - �������������ֵ��
 *        position - ���������λ�á�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::convert_vertical_coordinate_to_pixel_position(
	const double coordinate,int &position) const{
	//1.�����ǰ���������ֵ��������ϵʵ�ʵ���ʾ��Χ����ֱ�ӷ��ش���
	if((coordinate<_min_v)||(coordinate>_max_v)){
		return(-1);
	}
	//2.�����ǰ����������δȷ������ֱ�ӷ��ش���
	if(_axis_area.IsRectEmpty()){
		return(-2);
	}
	//3.����ÿ������ֵ�������ص�ֵ��
	double pixel_value=static_cast<double>(_axis_area.Height())/(_max_v-_min_v);
	if((fabs(pixel_value)<1.0E-20)||(pixel_value<0.0)){
		return(-3);
	}
	//4.��������ֵ����Ϊ����λ�á�
	position=_axis_area.bottom-static_cast<int>((coordinate-_min_v)*pixel_value);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: draw
 * breif: ʵ�ֵ�ǰͼ�εĻ��ơ�
 * param: dest_dc - Ŀ��DC��
 *		  dest_bitmap - Ŀ��λͼ��
 *        dest_area - Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::draw(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CRect &dest_area){
	//1.���û�����Ӧ�������������жϵ����Ƿ�ɹ���
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.�������ߴ磬�����жϼ����Ƿ�ɹ���
	CSize h_axis_title_size(0,0);
	CSize v_axis_title_size(0,0);
	if(calculate_title_size(dest_dc,
		h_axis_title_size,v_axis_title_size)<0){
		return(-2);
	}
	//3.���㵱ǰ�̶ȳߴ磬�����жϼ����Ƿ�ɹ���
	CSize h_axis_scale_size(0,0);
	CSize v_axis_scale_size(0,0);
	if(calculate_scale_size(dest_dc,
		h_axis_scale_size,v_axis_scale_size)<0){
		return(-3);
	}
	//4.���㵱ǰ���������򣬲����жϼ����Ƿ�ɹ���
	CRect axis_area(dest_area);
	axis_area.InflateRect(-MARGIN,-MARGIN,-MARGIN,-MARGIN);
	axis_area.left+=(v_axis_title_size.cx+SPACING+
		v_axis_scale_size.cx+5+SCALE_MARK_SIZE);
	axis_area.bottom-=(SCALE_MARK_SIZE+5+h_axis_scale_size.cy+
		SPACING+h_axis_title_size.cy);
	if(axis_area.IsRectEmpty()){
		return(-4);
	}
	_axis_area=axis_area;
	//5.���������ᡣ
	if(draw_axis(dest_dc,dest_bitmap,
		h_axis_scale_size,v_axis_scale_size)<0){
		return(-5);
	}
	//6.������������⡣
	draw_tilte(dest_dc,dest_bitmap,h_axis_scale_size,
		v_axis_scale_size,h_axis_title_size,v_axis_title_size);
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: draw_axis
 * breif: ���������ᡣ
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 *        h_axis_scale_size - ����̶ȳߴ硣
 *        v_axis_scale_size - ����̶ȳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::draw_axis(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CSize &h_axis_scale_size,
	const CSize &v_axis_scale_size) const{
	/*˽�к�������ʱĬ������������Ϊ�ա�*/
	//1.���������ᱳ����
	if(dest_bitmap.fill_rectangle(_background_color_a,
		_background_color_r,_background_color_g,
		_background_color_b,_axis_area.left,_axis_area.top,
		_axis_area.Width(),_axis_area.Height())<0){
		return(-1);
	}
	//2.���������ᡣ
	if(dest_bitmap.draw_rectangle(_axis_color_a,_axis_color_r,
		_axis_color_g,_axis_color_b,_axis_area.left,_axis_area.top,
		_axis_area.Width(),_axis_area.Height())<0){
		return(-2);
	}
	//3.���ƺ���̶��ߡ��̶��Լ�����
	//3-1.������ǰ�������������
	CRect text_area(0,0,0,0);
	int temp=0;
	int scale_count=(_axis_area.Width()/(h_axis_scale_size.cx+H_SCALE_SPACING));
	int interval=h_axis_scale_size.cx+H_SCALE_SPACING;
	CString text(_T(""));
	//3-2.ѭ�����ƿ̶����Լ��̶ȡ�
	for(int i=0;i<=scale_count;++i){//����̶��������㣬�򲻽����κλ��ơ�
		//3-2-1.�������λ�á�
		temp=_axis_area.left+(i*interval);
		//3-2-2.���ƿ̶��ߡ�
		if(dest_bitmap.draw_line(_axis_color_a,_axis_color_r,_axis_color_g,
			_axis_color_b,1.0,temp,_axis_area.bottom,temp,_axis_area.bottom+
			SCALE_MARK_SIZE)<0){
			return(-3);
		}
		//3-2-3.��������
		if((_is_grid_visible)&&(temp!=_axis_area.left)&&(temp!=_axis_area.right)){
			if(dest_bitmap.draw_line(_grid_color_a,_grid_color_r,_grid_color_g,
				_grid_color_b,1.0,temp,_axis_area.bottom-1,temp,_axis_area.top+1)<0){
				return(-4);
			}
		}
		//3-2-4.���ƿ̶ȡ�
		text_area.left=temp-(h_axis_scale_size.cx/2);
		text_area.top=_axis_area.bottom+SCALE_MARK_SIZE+5;
		text_area.right=text_area.left+h_axis_scale_size.cx;
		text_area.bottom=text_area.top+h_axis_scale_size.cy;
		if(text_area.IsRectEmpty()){
			return(-5);
		}
		text=calculate_horizontal_axis_scale_text(temp);
		if(_T("")==text){
			return(-6);
		}
		if(dest_bitmap.draw_text(text,dest_dc,static_cast<HFONT>(
			_scale_font->GetSafeHandle()),text_area.left,text_area.top,
			text_area.Width(),text_area.Height(),_text_color_a,_text_color_r,
			_text_color_g,_text_color_b)<0){
			return(-7);
		}
	}
	//4.��������̶��Լ��ı���
	//4-1.������ǰ�������������
	scale_count=(_axis_area.Height()/(v_axis_scale_size.cy+V_SCALE_SPACING));
	interval=v_axis_scale_size.cy+V_SCALE_SPACING;
	//4-2.ѭ�����ƿ̶����Լ��̶ȡ�
	for(int i=0;i<=scale_count;++i){//����̶��������㣬�򲻽����κλ��ơ�
		//4-2-1.�������λ�á�
		temp=_axis_area.bottom-(i*interval);
		//4-2-2.���ƿ̶��ߡ�
		if(dest_bitmap.draw_line(_axis_color_a,_axis_color_r,_axis_color_g,
			_axis_color_b,1.0,_axis_area.left,temp,_axis_area.left-
			SCALE_MARK_SIZE,temp)){
			return(-8);
		}
		//4-2-3.��������
		if((_is_grid_visible)&&(temp!=_axis_area.bottom)&&(temp!=_axis_area.top)){
			if(dest_bitmap.draw_line(_grid_color_a,_grid_color_r,_grid_color_g,
				_grid_color_b,1.0,_axis_area.left+1,temp,_axis_area.right-1,temp)<0){
				return(-9);
			}
		}
		//4-2-4.���ƿ̶ȡ�
		text_area.top=temp-(v_axis_scale_size.cy/2);
		text_area.bottom=text_area.top+v_axis_scale_size.cy;
		text_area.right=_axis_area.left-SCALE_MARK_SIZE-5;
		text_area.left=text_area.right-v_axis_scale_size.cx;
		if(text_area.IsRectEmpty()){
			return(-10);
		}
		text=calculate_vertical_axis_scale_text(temp);
		if(_T("")==text){
			return(-11);
		}
		if(dest_bitmap.draw_text(text,dest_dc,static_cast<HFONT>(
			_scale_font->GetSafeHandle()),text_area.left,text_area.top,
			text_area.Width(),text_area.Height(),_text_color_a,_text_color_r,
			_text_color_g,_text_color_b)<0){
			return(-12);
		}
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: draw_tilte
 * breif: ���Ƶ�ǰ����ϵ���⡣
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 *        h_axis_scale_size - ����̶ȳߴ硣
 *        v_axis_scale_size - ����̶ȳߴ硣
 *        h_axis_title_size - �������ߴ硣
 *        v_axis_title_size - �������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::draw_tilte(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CSize &h_axis_scale_size,
	const CSize &v_axis_scale_size,const CSize &h_axis_title_size,
	const CSize &v_axis_title_size) const{
	/*��ʱĬ����������Ϸ�*/
	//1.����������⡣
	//1-1.���������������
	CRect title_area(0,0,0,0);
	title_area.left=_axis_area.left-SCALE_MARK_SIZE-
		v_axis_scale_size.cx-SPACING-v_axis_title_size.cx;
	title_area.right=title_area.left+v_axis_title_size.cx;
	title_area.top=_axis_area.top/*+((_axis_area.Height()-
		v_axis_title_size.cy)/2)*/;
	title_area.bottom=_axis_area.bottom/*title_area.top+v_axis_title_size.cy*/;
	//1-2.����������������Ч��
	if(title_area.IsRectEmpty()){
	}
	//1-3.����������⡣
	else{
		if(dest_bitmap.draw_text(_vertical_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),title_area.left,
			title_area.top,title_area.Width(),title_area.Height(),
			_text_color_a,_text_color_r,_text_color_g,_text_color_b)<0){
			return(-1);
		}
	}
	//2.���ƺ�����⡣
	//2-1.��������������
	title_area.left=_axis_area.left/*+((_axis_area.Width()-h_axis_title_size.cx)/2)*/;
	title_area.right=_axis_area.right/*title_area.left+h_axis_title_size.cx*/;
	title_area.top=_axis_area.bottom+SCALE_MARK_SIZE+SPACING+h_axis_scale_size.cy;
	title_area.bottom=title_area.top+h_axis_title_size.cy;
	//2-2.����������������Ч��
	if(title_area.IsRectEmpty()){
	}
	//2-3.���ƺ�����⡣
	else{
		if(dest_bitmap.draw_text(_horizontal_axis_title,dest_dc,
			static_cast<HFONT>(_title_font->GetSafeHandle()),
			title_area.left,title_area.top,title_area.Width(),
			title_area.Height(),_text_color_a,_text_color_r,
			_text_color_g,_text_color_b)<0){
			return(-2);
		}
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_scale_size
 * breif: ����̶ȳߴ硣
 * param: dest_dc - Ŀ��DC��
 *        h_axis_scale_size - ���صĺ���̶ȳߴ硣
 *        v_axis_scale_size - ���ص�����̶ȳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::calculate_scale_size(const HDC dest_dc,
	CSize &h_axis_scale_size,CSize &v_axis_scale_size) const{
	//1.������ǰ�������������
	CSize size(0,0);
	CString text(_T(""));
	int h_axis_scale_width=0;
	int h_axis_scale_height=0;
	int v_axis_scale_width=0;
	int v_axis_scale_height=0;
	double ranges[4]={_min_h,_max_h,_min_v,_max_v};
	//2.ѭ������ᡢ����̶ȳߴ硣
	for(unsigned int i=0;i!=4;++i){
		//2-1.�γɿ̶ȵ��ı��ַ�����
		text.Format(_T("%.2lf"),ranges[i]);
		//2-2.����̶ȳߴ硣
		if(MtGdiplus::calculate_text_size(text,dest_dc,
			static_cast<HFONT>(_scale_font->GetSafeHandle()),size)<0){
			return(-1);
		}
		//2-3.�����ǰ������Ǻ���̶ȳߴ硣
		if(i<2){
			if(size.cx>h_axis_scale_width){
				h_axis_scale_width=size.cx+5;
			}
			if(size.cy>h_axis_scale_height){
				h_axis_scale_height=size.cy;
			}
		}
		//2-4.�����ǰ�����������̶ȳߴ硣
		else{
			if(size.cx>v_axis_scale_width){
				v_axis_scale_width=size.cx+5;
			}
			if(size.cy>v_axis_scale_height){
				v_axis_scale_height=size.cy;
			}
		}
	}
	//3.Ϊ�ᡢ����̶ȳߴ縳ֵ��
	h_axis_scale_size.cx=h_axis_scale_width;
	h_axis_scale_size.cy=h_axis_scale_height;
	v_axis_scale_size.cx=v_axis_scale_width;
	v_axis_scale_size.cy=v_axis_scale_height;
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_title_size
 * breif: �������ߴ硣
 * parma: dest_dc - Ŀ��DC��
 *        h_axis_title_size - ���صĺ������ߴ硣
 *        v_axis_title_size - ���ص��������ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::calculate_title_size(const HDC dest_dc,
	CSize &h_axis_title_size,CSize &v_axis_title_size) const{
	//1.������ǰ�������������
	CSize size(0,0);
	int h_axis_title_width=0;
	int h_axis_title_height=0;
	int v_axis_title_width=0;
	int v_axis_title_height=0;
	//2.����������ߴ硣
	//2-1.�����ǰ�������Ϊ�ա�
	if(_T("")==_horizontal_axis_title){
		//ʲôҲ������
	}
	//2-2.�����ǰ������ⲻΪ�գ�����������ߴ硣
	else{
		if(MtGdiplus::calculate_text_size(
			_horizontal_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),size)<0){
			return(-1);
		}
		h_axis_title_width=size.cx;
		h_axis_title_height=size.cy;
	}
	//3.�����������ߴ硣
	//3-1.�����ǰ�������Ϊ�ա�
	if(_T("")==_vertical_axis_title){
		//ʲôҲ������
	}
	//3-2.�����ǰ������ⲻΪ�գ������������ߴ硣
	else{
		if(MtGdiplus::calculate_text_size(
			_vertical_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),size)<0){
			return(-2);
		}
		v_axis_title_width=size.cx;
		v_axis_title_height=size.cy;
	}
	//4.Ϊ��ǰ�ᡢ�������ߴ縳ֵ��
	h_axis_title_size.cx=h_axis_title_width;
	h_axis_title_size.cy=h_axis_title_height;
	v_axis_title_size.cx=v_axis_title_width;
	v_axis_title_size.cy=v_axis_title_height;
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: calculate_horizontal_axis_scale
 * breif: �������Ŀ̶ȡ�
 * param: position-ָ����λ�á�
 *        scale - ���صĿ̶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::calculate_horizontal_axis_scale(
	const int position,double &scale) const{
	//1.����ÿ�����������ֵ�������жϼ����Ƿ�ɹ���
	double pixel_value=(_max_h-_min_h)/static_cast<
		double>(_axis_area.Width());
	if(fabs(pixel_value)<(1.0E-20)){
		return(-1);//�����쳣����Ϊÿ���ش����ֵ��Ȼ���㡣
	}
	//2.����̶ȡ�
	scale=_min_h+(static_cast<double>(
		position-_axis_area.left)*pixel_value);
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_horizontal_axis_scale_text
 * breif: �������̶��ı���
 * param: position - ָ����λ�á�
 * return: �������ִ�гɹ����غ���̶��ı������򷵻ؿա�
 */
CString MtCoordinateAxisGraph::calculate_horizontal_axis_scale_text(
	const int position) const{
	double scale=0.0;
	if(calculate_horizontal_axis_scale(position,scale)<0){
		return(_T(""));
	}
	CString text(_T(""));
	text.Format(_T("%.2lf"),scale);
	return(text);
}

/**
 * name: calculate_vertical_axis_scale
 * breif: ��������̶ȡ�
 * param: position - ָ����λ�á�
 *        scale - ���صĿ̶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtCoordinateAxisGraph::calculate_vertical_axis_scale(
	const int position,double &scale) const{
	//1.����ÿ�����������ֵ�������жϼ����Ƿ�ɹ���
	double pixel_value=(_max_v-_min_v)/static_cast<
		double>(_axis_area.Height());
	if(fabs(pixel_value)<(1.0E-20)){
		return(-1);//�����쳣����Ϊÿ���ش����ֵ��Ȼ���㡣
	}
	//2.����̶ȡ�
	scale=_min_v+(static_cast<double>(_axis_area.bottom-
		position)*pixel_value);
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: calculate_vertical_axis_scale_text
 * breif: ��������̶��ı�����
 * param: position - ָ����λ�á�
 * return: �������ִ�гɹ���������̶��ı������򷵻ؿա�
 */
CString MtCoordinateAxisGraph::calculate_vertical_axis_scale_text(
	const int position) const{
	double scale=0.0;
	if(calculate_vertical_axis_scale(position,scale)<0){
		return(_T(""));
	}
	CString text(_T(""));
	text.Format(_T("%.2lf"),scale);
	return(text);
}