#include"stdafx.h"
#include"MtCoordinateAxisGraph.h"
#include"../env/MtGdiplus.h"
#include"MtBitmap.h"

/**
 * name: MtCoordinateAxisGraph
 * breif: 构造函数。
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
	//1.创建刻度字体。
	LOGFONT log={15,0,0,0,FW_NORMAL,0,0,0,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,_T("Microsoft Sans Serif")};
	_scale_font->CreateFontIndirect(&log);
	//2.创建标题字体。
	LOGFONT log_t={20,0,0,0,FW_HEAVY,0,0,0,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,_T("Microsoft Sans Serif")};
	_title_font->CreateFontIndirect(&log_t);
}

/**
 * name: ~MtCoordinateAxisGraph
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtCoordinateAxisGraph::~MtCoordinateAxisGraph(void){
	//1.释放刻度字体。
	if((0!=_scale_font->GetSafeHandle())&&(
		INVALID_HANDLE_VALUE!=_scale_font->GetSafeHandle())){
		_scale_font->DeleteObject();
	}
	delete _scale_font;
	//2.释放标题字体。
	if((0!=_title_font->GetSafeHandle())&&(
		INVALID_HANDLE_VALUE!=_title_font->GetSafeHandle())){
		_title_font->DeleteObject();
	}
	delete _title_font;
}

/**
 * name: set_horizontal_axis_range
 * brief: 设置横轴范围。
 * param: min - 最小值。
 *        max - 最大值。
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
 * breif: 设置纵轴范围。
 * param: min - 最小值。
 *        max - 最大值。
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
 * breif: 设置背景颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * brief: 设置轴的颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * breif: 设置网格颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * breif: 设置文本颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * breif: 显示网格。
 * param: is_visible - 标记当前网格是否可视。
 * return: --
 */
void MtCoordinateAxisGraph::show_grid(const BOOL is_visible){
	_is_grid_visible=is_visible;
}

/**
 * name: set_horizontal_axis_title
 * breif: 设置横轴标题。
 * param: title - 横轴标题。
 * return: --
 */
void MtCoordinateAxisGraph::set_horizontal_axis_title(
	const CString &title){
	_horizontal_axis_title=title;
}

/**
 * name: set_vertical_axis_title
 * breif: 设置纵轴标题。
 * param: title - 纵轴标题。
 * return: --
 */
void MtCoordinateAxisGraph::set_vertical_axis_title(
	const CString &title){
	_vertical_axis_title=title;
}

/**
 * name: convert_horizontal_coordinate_to_pixel_position
 * breif: 将横坐标值转换为像素位置。
 * param: coordinate - 输入的横坐标值。
 *        position - 输出的像素位置。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::convert_horizontal_coordinate_to_pixel_position(
	const double coordinate,int &position) const{
	//1.如果当前输入的横坐标值超出坐标系的实际的显示范围，则直接返回错误。
	if((coordinate<_min_h)||(coordinate>_max_h)){
		return(-1);
	}
	//2.如果当前坐标区域尚未确定，则直接返回错误。
	if(_axis_area.IsRectEmpty()){
		return(-2);
	}
	//3.计算每个坐标值代表像素的值。
	double pixel_value=static_cast<double>(_axis_area.Width())/(_max_h-_min_h);
	if((fabs(pixel_value)<1.0E-20)||(pixel_value<0.0)){
		return(-3);
	}
	//4.将横坐标值换算为像素位置。
	position=_axis_area.left+static_cast<int>((coordinate-_min_h)*pixel_value);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: convert_vertical_coordinate_to_pixel_position
 * breif: 将纵坐标值转换为像素位置。
 * param: coordinate - 输入的纵轴坐标值。
 *        position - 输出的像素位置。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::convert_vertical_coordinate_to_pixel_position(
	const double coordinate,int &position) const{
	//1.如果当前输入的坐标值超出坐标系实际的显示范围，则直接返回错误。
	if((coordinate<_min_v)||(coordinate>_max_v)){
		return(-1);
	}
	//2.如果当前坐标区域尚未确定，则直接返回错误。
	if(_axis_area.IsRectEmpty()){
		return(-2);
	}
	//3.计算每个坐标值代表像素的值。
	double pixel_value=static_cast<double>(_axis_area.Height())/(_max_v-_min_v);
	if((fabs(pixel_value)<1.0E-20)||(pixel_value<0.0)){
		return(-3);
	}
	//4.将纵坐标值换算为像素位置。
	position=_axis_area.bottom-static_cast<int>((coordinate-_min_v)*pixel_value);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: draw
 * breif: 实现当前图形的绘制。
 * param: dest_dc - 目标DC。
 *		  dest_bitmap - 目标位图。
 *        dest_area - 目标区域。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::draw(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CRect &dest_area){
	//1.调用基类相应处理函数，并且判断调用是否成功。
	if(MtGraph::draw(dest_dc,dest_bitmap,dest_area)<0){
		return(-1);
	}
	//2.计算标题尺寸，并且判断计算是否成功。
	CSize h_axis_title_size(0,0);
	CSize v_axis_title_size(0,0);
	if(calculate_title_size(dest_dc,
		h_axis_title_size,v_axis_title_size)<0){
		return(-2);
	}
	//3.计算当前刻度尺寸，并且判断计算是否成功。
	CSize h_axis_scale_size(0,0);
	CSize v_axis_scale_size(0,0);
	if(calculate_scale_size(dest_dc,
		h_axis_scale_size,v_axis_scale_size)<0){
		return(-3);
	}
	//4.计算当前坐标轴区域，并且判断计算是否成功。
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
	//5.绘制坐标轴。
	if(draw_axis(dest_dc,dest_bitmap,
		h_axis_scale_size,v_axis_scale_size)<0){
		return(-5);
	}
	//6.绘制坐标轴标题。
	draw_tilte(dest_dc,dest_bitmap,h_axis_scale_size,
		v_axis_scale_size,h_axis_title_size,v_axis_title_size);
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: draw_axis
 * breif: 绘制坐标轴。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 *        h_axis_scale_size - 横轴刻度尺寸。
 *        v_axis_scale_size - 纵轴刻度尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::draw_axis(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CSize &h_axis_scale_size,
	const CSize &v_axis_scale_size) const{
	/*私有函数，此时默认坐标轴区域不为空。*/
	//1.绘制坐标轴背景。
	if(dest_bitmap.fill_rectangle(_background_color_a,
		_background_color_r,_background_color_g,
		_background_color_b,_axis_area.left,_axis_area.top,
		_axis_area.Width(),_axis_area.Height())<0){
		return(-1);
	}
	//2.绘制坐标轴。
	if(dest_bitmap.draw_rectangle(_axis_color_a,_axis_color_r,
		_axis_color_g,_axis_color_b,_axis_area.left,_axis_area.top,
		_axis_area.Width(),_axis_area.Height())<0){
		return(-2);
	}
	//3.绘制横轴刻度线、刻度以及网格。
	//3-1.声明当前操作所需变量。
	CRect text_area(0,0,0,0);
	int temp=0;
	int scale_count=(_axis_area.Width()/(h_axis_scale_size.cx+H_SCALE_SPACING));
	int interval=h_axis_scale_size.cx+H_SCALE_SPACING;
	CString text(_T(""));
	//3-2.循环绘制刻度线以及刻度。
	for(int i=0;i<=scale_count;++i){//如果刻度数量不足，则不进行任何绘制。
		//3-2-1.计算绘制位置。
		temp=_axis_area.left+(i*interval);
		//3-2-2.绘制刻度线。
		if(dest_bitmap.draw_line(_axis_color_a,_axis_color_r,_axis_color_g,
			_axis_color_b,1.0,temp,_axis_area.bottom,temp,_axis_area.bottom+
			SCALE_MARK_SIZE)<0){
			return(-3);
		}
		//3-2-3.绘制网格。
		if((_is_grid_visible)&&(temp!=_axis_area.left)&&(temp!=_axis_area.right)){
			if(dest_bitmap.draw_line(_grid_color_a,_grid_color_r,_grid_color_g,
				_grid_color_b,1.0,temp,_axis_area.bottom-1,temp,_axis_area.top+1)<0){
				return(-4);
			}
		}
		//3-2-4.绘制刻度。
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
	//4.绘制纵轴刻度以及文本。
	//4-1.声明当前操作所需变量。
	scale_count=(_axis_area.Height()/(v_axis_scale_size.cy+V_SCALE_SPACING));
	interval=v_axis_scale_size.cy+V_SCALE_SPACING;
	//4-2.循环绘制刻度线以及刻度。
	for(int i=0;i<=scale_count;++i){//如果刻度数量不足，则不进行任何绘制。
		//4-2-1.计算绘制位置。
		temp=_axis_area.bottom-(i*interval);
		//4-2-2.绘制刻度线。
		if(dest_bitmap.draw_line(_axis_color_a,_axis_color_r,_axis_color_g,
			_axis_color_b,1.0,_axis_area.left,temp,_axis_area.left-
			SCALE_MARK_SIZE,temp)){
			return(-8);
		}
		//4-2-3.绘制网格。
		if((_is_grid_visible)&&(temp!=_axis_area.bottom)&&(temp!=_axis_area.top)){
			if(dest_bitmap.draw_line(_grid_color_a,_grid_color_r,_grid_color_g,
				_grid_color_b,1.0,_axis_area.left+1,temp,_axis_area.right-1,temp)<0){
				return(-9);
			}
		}
		//4-2-4.绘制刻度。
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
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: draw_tilte
 * breif: 绘制当前坐标系标题。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 *        h_axis_scale_size - 横轴刻度尺寸。
 *        v_axis_scale_size - 纵轴刻度尺寸。
 *        h_axis_title_size - 横轴标题尺寸。
 *        v_axis_title_size - 纵轴标题尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::draw_tilte(const HDC dest_dc,
	MtBitmap &dest_bitmap,const CSize &h_axis_scale_size,
	const CSize &v_axis_scale_size,const CSize &h_axis_title_size,
	const CSize &v_axis_title_size) const{
	/*此时默认坐标区域合法*/
	//1.绘制纵轴标题。
	//1-1.计算纵轴标题区域。
	CRect title_area(0,0,0,0);
	title_area.left=_axis_area.left-SCALE_MARK_SIZE-
		v_axis_scale_size.cx-SPACING-v_axis_title_size.cx;
	title_area.right=title_area.left+v_axis_title_size.cx;
	title_area.top=_axis_area.top/*+((_axis_area.Height()-
		v_axis_title_size.cy)/2)*/;
	title_area.bottom=_axis_area.bottom/*title_area.top+v_axis_title_size.cy*/;
	//1-2.如果纵轴标题区域无效。
	if(title_area.IsRectEmpty()){
	}
	//1-3.绘制纵轴标题。
	else{
		if(dest_bitmap.draw_text(_vertical_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),title_area.left,
			title_area.top,title_area.Width(),title_area.Height(),
			_text_color_a,_text_color_r,_text_color_g,_text_color_b)<0){
			return(-1);
		}
	}
	//2.绘制横轴标题。
	//2-1.计算横轴标题区域。
	title_area.left=_axis_area.left/*+((_axis_area.Width()-h_axis_title_size.cx)/2)*/;
	title_area.right=_axis_area.right/*title_area.left+h_axis_title_size.cx*/;
	title_area.top=_axis_area.bottom+SCALE_MARK_SIZE+SPACING+h_axis_scale_size.cy;
	title_area.bottom=title_area.top+h_axis_title_size.cy;
	//2-2.如果横轴标题区域无效。
	if(title_area.IsRectEmpty()){
	}
	//2-3.绘制横轴标题。
	else{
		if(dest_bitmap.draw_text(_horizontal_axis_title,dest_dc,
			static_cast<HFONT>(_title_font->GetSafeHandle()),
			title_area.left,title_area.top,title_area.Width(),
			title_area.Height(),_text_color_a,_text_color_r,
			_text_color_g,_text_color_b)<0){
			return(-2);
		}
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_scale_size
 * breif: 计算刻度尺寸。
 * param: dest_dc - 目标DC。
 *        h_axis_scale_size - 返回的横轴刻度尺寸。
 *        v_axis_scale_size - 返回的纵轴刻度尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::calculate_scale_size(const HDC dest_dc,
	CSize &h_axis_scale_size,CSize &v_axis_scale_size) const{
	//1.声明当前操作所需变量。
	CSize size(0,0);
	CString text(_T(""));
	int h_axis_scale_width=0;
	int h_axis_scale_height=0;
	int v_axis_scale_width=0;
	int v_axis_scale_height=0;
	double ranges[4]={_min_h,_max_h,_min_v,_max_v};
	//2.循环计算横、纵轴刻度尺寸。
	for(unsigned int i=0;i!=4;++i){
		//2-1.形成刻度的文本字符串。
		text.Format(_T("%.2lf"),ranges[i]);
		//2-2.计算刻度尺寸。
		if(MtGdiplus::calculate_text_size(text,dest_dc,
			static_cast<HFONT>(_scale_font->GetSafeHandle()),size)<0){
			return(-1);
		}
		//2-3.如果当前计算的是横轴刻度尺寸。
		if(i<2){
			if(size.cx>h_axis_scale_width){
				h_axis_scale_width=size.cx+5;
			}
			if(size.cy>h_axis_scale_height){
				h_axis_scale_height=size.cy;
			}
		}
		//2-4.如果当前计算的是纵轴刻度尺寸。
		else{
			if(size.cx>v_axis_scale_width){
				v_axis_scale_width=size.cx+5;
			}
			if(size.cy>v_axis_scale_height){
				v_axis_scale_height=size.cy;
			}
		}
	}
	//3.为横、纵轴刻度尺寸赋值。
	h_axis_scale_size.cx=h_axis_scale_width;
	h_axis_scale_size.cy=h_axis_scale_height;
	v_axis_scale_size.cx=v_axis_scale_width;
	v_axis_scale_size.cy=v_axis_scale_height;
	//4.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_title_size
 * breif: 计算标题尺寸。
 * parma: dest_dc - 目标DC。
 *        h_axis_title_size - 返回的横轴标题尺寸。
 *        v_axis_title_size - 返回的纵轴标题尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::calculate_title_size(const HDC dest_dc,
	CSize &h_axis_title_size,CSize &v_axis_title_size) const{
	//1.声明当前操作所需变量。
	CSize size(0,0);
	int h_axis_title_width=0;
	int h_axis_title_height=0;
	int v_axis_title_width=0;
	int v_axis_title_height=0;
	//2.计算横轴标题尺寸。
	//2-1.如果当前横轴标题为空。
	if(_T("")==_horizontal_axis_title){
		//什么也不做。
	}
	//2-2.如果当前横轴标题不为空，计算横轴标题尺寸。
	else{
		if(MtGdiplus::calculate_text_size(
			_horizontal_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),size)<0){
			return(-1);
		}
		h_axis_title_width=size.cx;
		h_axis_title_height=size.cy;
	}
	//3.计算纵轴标题尺寸。
	//3-1.如果当前纵轴标题为空。
	if(_T("")==_vertical_axis_title){
		//什么也不做。
	}
	//3-2.如果当前纵轴标题不为空，计算纵轴标题尺寸。
	else{
		if(MtGdiplus::calculate_text_size(
			_vertical_axis_title,dest_dc,static_cast<
			HFONT>(_title_font->GetSafeHandle()),size)<0){
			return(-2);
		}
		v_axis_title_width=size.cx;
		v_axis_title_height=size.cy;
	}
	//4.为当前横、纵轴标题尺寸赋值。
	h_axis_title_size.cx=h_axis_title_width;
	h_axis_title_size.cy=h_axis_title_height;
	v_axis_title_size.cx=v_axis_title_width;
	v_axis_title_size.cy=v_axis_title_height;
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: calculate_horizontal_axis_scale
 * breif: 计算横轴的刻度。
 * param: position-指定的位置。
 *        scale - 返回的刻度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::calculate_horizontal_axis_scale(
	const int position,double &scale) const{
	//1.计算每像素所代表的值，并且判断计算是否成功。
	double pixel_value=(_max_h-_min_h)/static_cast<
		double>(_axis_area.Width());
	if(fabs(pixel_value)<(1.0E-20)){
		return(-1);//运算异常，因为每像素代表的值竟然是零。
	}
	//2.计算刻度。
	scale=_min_h+(static_cast<double>(
		position-_axis_area.left)*pixel_value);
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_horizontal_axis_scale_text
 * breif: 计算横轴刻度文本。
 * param: position - 指定的位置。
 * return: 如果函数执行成功返回横轴刻度文本，否则返回空。
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
 * breif: 计算纵轴刻度。
 * param: position - 指定的位置。
 *        scale - 返回的刻度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtCoordinateAxisGraph::calculate_vertical_axis_scale(
	const int position,double &scale) const{
	//1.计算每像素所代表的值，并且判断计算是否成功。
	double pixel_value=(_max_v-_min_v)/static_cast<
		double>(_axis_area.Height());
	if(fabs(pixel_value)<(1.0E-20)){
		return(-1);//运算异常，因为每像素代表的值竟然是零。
	}
	//2.计算刻度。
	scale=_min_v+(static_cast<double>(_axis_area.bottom-
		position)*pixel_value);
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: calculate_vertical_axis_scale_text
 * breif: 计算纵轴刻度文本。。
 * param: position - 指定的位置。
 * return: 如果函数执行成功返回纵轴刻度文本，否则返回空。
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