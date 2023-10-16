#include"stdafx.h"
#include"MtBitmap.h"
#include"../tool/MtCharacterSet.h"

/**
 * name: MtBitmap
 * brief: 构造函数，负责对位图进行初始化。
 * param: width - 位图宽度。
 *        height - 位图高度。
 *        pixel_format - 位图格式。
 * return: --
 */
MtBitmap::MtBitmap(const unsigned int width,const unsigned int height,
	const Gdiplus::PixelFormat pixel_format/*=PixelFormat32bppARGB*/)
	:_is_valid(FALSE)
	,_bitmap(width,height,pixel_format){
	if(Gdiplus::Ok==_bitmap.GetLastStatus()){
		_is_valid=TRUE;
		fill();
	}
}

/**
 * name: ~MtBitmap
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtBitmap::~MtBitmap(void){
}

/**
 * name: is_valid
 * brief: 判断当前位图是否有效。
 * param:
 * return: 如果当前位图有效返回TRUE，否则返回FALSE。
 */
BOOL MtBitmap::is_valid() const{
	return(_is_valid);
}

/**
 * name: get_width
 * brief: 获取位图宽度。
 * param: --
 * return: 返回位图宽度。
 */
int MtBitmap::get_width(){
	return(static_cast<int>(_bitmap.GetWidth()));
}

/**
 * name: get_height
 * brief: 获取位图高度。
 * param: --
 * return: 返回位图高度。
 */
int MtBitmap::get_height(){
	return(static_cast<int>(_bitmap.GetHeight()));
}

/**
 * name: create_graphics
 * brief: 为当前位图的创建一个绘图器。
 * param: --
 * return: 返回新创建的绘图器。
 */
MtBitmap::PtrToGraphics MtBitmap::create_graphics(){
	return(PtrToGraphics(new Gdiplus::Graphics(&_bitmap)));
}

/**
 * name: fill
 * brief: 用指定颜色填充位图。
 * param: color_a - 颜色中A分量。
 *        color_r - 颜色中R分量。
 *        color_g - 颜色中G分量。
 *        color_r - 颜色中R分量。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::fill(const unsigned char color_a/*=0*/,const unsigned char color_r/*=0*/,
	const unsigned char color_g/*=0*/,const unsigned char color_b/*=0*/){
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-1);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->Clear(Gdiplus::Color(
		color_a,color_r,color_g,color_b))){
		return(-3);
	}
	return(0);
}

/**
 * name: draw_text
 * brief: 在内存位图指定区域内书写文本。
 * param: text - 书写的文本。
 *        dc - 绘图设备DC。
 *        font - 字体句柄。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        color_a - 文本颜色a分量。
 *        color_r - 文本颜色r分量。
 *        color_g - 文本颜色g分量。
 *        color_b - 文本颜色b分量。
 *        alignment_h - 文本水平停靠方式。
 *        alignment_v - 文本垂直停靠方式。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_text(const CString &text,HDC dc,HFONT font,const int dest_x,
	const int dest_y,const int dest_width,const int dest_height,const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,const unsigned char color_b,
	const Alignment alignment_h/*=ALIGNMENT_CENTER*/,const Alignment alignment_v/*=ALIGNMENT_CENTER*/){
	return(draw_text(text,dc,font,static_cast<float>(dest_x),static_cast<float>(dest_y),
		static_cast<float>(dest_width),static_cast<float>(dest_height),color_a,color_r,
		color_g,color_b,alignment_h,alignment_v));
}

/**
 * name: draw_text
 * brief: 在内存位图指定区域内书写文本。
 * param: text - 书写的文本。
 *        dc - 绘图设备DC。
 *        font - 字体句柄。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        color_a - 文本颜色a分量。
 *        color_r - 文本颜色r分量。
 *        color_g - 文本颜色g分量。
 *        color_b - 文本颜色b分量。
 *        alignment_h - 文本水平停靠方式。
 *        alignment_v - 文本垂直停靠方式。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_text(const CString &text,HDC dc,HFONT font,const float dest_x,
	const float dest_y,const float dest_width,const float dest_height,const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,const unsigned char color_b,
	const Alignment alignment_h/*=ALIGNMENT_CENTER*/,const Alignment alignment_v/*ALIGNMENT_CENTER*/){
	//1.将文本转换为宽字符集表示。
	const CStringW text_w=MtCharacterSet::to_unicode(text);
	//2.创建Gdiplus字体实例。
	Gdiplus::Font text_font(dc,font);
	if(Gdiplus::Ok!=text_font.GetLastStatus()){
		return(-1);
	}
	//3.创建文本书写格式信息。
	Gdiplus::StringFormat text_format;
	if(Gdiplus::Ok!=text_format.GetLastStatus()){
		return(-2);
	}
	if(Gdiplus::Ok!=text_format.SetAlignment(static_cast<
		Gdiplus::StringAlignment>(alignment_h))){
		return(-3);
	}
	if(Gdiplus::Ok!=text_format.SetLineAlignment(static_cast<
		Gdiplus::StringAlignment>(alignment_v))){
		return(-4);
	}
	//4.创建文本书写画刷。
	Gdiplus::SolidBrush text_brush(Gdiplus::Color(color_a,color_r,
		color_g,color_b));
	if(Gdiplus::Ok!=text_brush.GetLastStatus()){
		return(-5);
	}
	//5.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-6);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-7);
	}
	/*
	if(Gdiplus::Ok!=graphics->SetCompositingQuality(
		Gdiplus::CompositingQualityGammaCorrected)){
		return(-8);
	}
	*/
	if(Gdiplus::Ok!=graphics->SetTextRenderingHint(
		Gdiplus::TextRenderingHintAntiAlias)){
		return(-9);
	}
	//6.在内存位图上进行文本绘制。
	if(Gdiplus::Ok!=graphics->DrawString(text_w,text_w.GetLength(),&text_font,
		Gdiplus::RectF(dest_x,dest_y,dest_width,dest_height),&text_format,
		&text_brush)){
		return(-10);
	}
	//7.成功返回。
	return(0);
}

/**
 * name: draw_line
 * brief: 在内存位图上绘制直线。
 * param: color_a - 直线颜色中A分量。
 *        color_r - 直线颜色中R分量。
 *        color_g - 直线颜色中G分量。
 *        color_b - 直线颜色中B分量。
 *        line_width - 指定直线宽度。
 *        begin_x - 直线起始点x坐标。
 *        begin_y - 直线起始点y坐标。
 *        end_x - 直线终点x坐标。
 *        end_y - 直线终点y坐标。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_line(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float line_width,
	const int begin_x,const int begin_y,const int end_x,const int end_y){
	//1.生成画线所需画笔。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,line_width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行内存位图的绘线操作。
	if(Gdiplus::Ok!=graphics->DrawLine(&pen,begin_x,begin_y,end_x,end_y)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: draw_line
 * brief: 在内存位图上绘制直线。
 * param: color_a - 直线颜色中A分量。
 *        color_r - 直线颜色中R分量。
 *        color_g - 直线颜色中G分量。
 *        color_b - 直线颜色中B分量。
 *        line_width - 指定直线宽度。
 *        begin_x - 直线起始点x坐标。
 *        begin_y - 直线起始点y坐标。
 *        end_x - 直线终点x坐标。
 *        end_y - 直线终点y坐标。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_line(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float line_width,
	const float begin_x,const float begin_y,const float end_x,const float end_y){
	//1.生成画线所需画笔。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,line_width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行内存位图的绘线操作。
	if(Gdiplus::Ok!=graphics->DrawLine(&pen,begin_x,begin_y,end_x,end_y)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: draw_rectangle
 * breif: 绘制正方形。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        dest_x - 目标矩形x坐标。
 *        dest_y - 目标矩形y坐标。
 *        dest_width - 目标矩形宽度。
 *        dest_height - 目标矩形高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.生成绘制矩形所需的画笔。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行目标矩形区域绘制，并且判断绘制是否成功。
	if(Gdiplus::Ok!=graphics->DrawRectangle(
		&pen,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: draw_rectangle
 * breif: 绘制正方形。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        dest_x - 目标矩形x坐标。
 *        dest_y - 目标矩形y坐标。
 *        dest_width - 目标矩形宽度。
 *        dest_height - 目标矩形高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height){
	//1.生成绘制矩形所需的画笔。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行目标矩形区域绘制，并且判断绘制是否成功。
	if(Gdiplus::Ok!=graphics->DrawRectangle(
		&pen,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: draw_curve
 * breif: 绘制曲线。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        width - 曲线宽度。
 *        points - 曲线上的点。
 *        count  - 点的数量。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_curve(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float width,
	CPoint *points,const unsigned int count){
	//1.如果当前传递参数不合法，则直接返回错误。
	if((0==points)||(0==count)){
		return(-1);
	}
	//2.生成绘制曲线所需的画笔。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-2);
	}
	//3.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-4);
	}
	//4.进行曲线的绘制，并且判断绘制是否成功。
	if(Gdiplus::Ok!=graphics->DrawCurve
		(&pen,reinterpret_cast<
		Gdiplus::Point*>(points),count)){
		return(-5);
	}
	//5.成功返回。
	return(0);
}

/**
 * name: draw_point
 * breif: 绘制点。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        points - 曲线上的点。
 *        count  - 点的数量。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::draw_point(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,
	CPoint *points,const unsigned int count){
	//1.如果当前传递参数不合法，则直接返回错误。
	if((0==points)||(0==count)){
		return(-1);
	}
	//2.绘制点。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	for(unsigned int i=0;i!=count;++i){
		_bitmap.SetPixel(points[i].x,points[i].y,color);
	}
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: fill_rectangle
 * brief: 用指定颜色填充位图上指定矩形。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        dest_x - 目标矩形x坐标。
 *        dest_y - 目标矩形y坐标。
 *        dest_width - 目标矩形宽度。
 *        dest_height - 目标矩形高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::fill_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.生成填充矩形所需的画刷。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::SolidBrush brush(color);
	if(Gdiplus::Ok!=brush.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行目标矩形区域填充，并且判断填充是否成功。
	if(Gdiplus::Ok!=graphics->FillRectangle(
		&brush,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: fill_rectangle
 * brief: 用指定颜色填充位图上指定矩形。
 * param: color_a - 颜色A分量。
 *        color_r - 颜色R分量。
 *        color_g - 颜色G分量。
 *        color_b - 颜色B分量。
 *        dest_x - 目标矩形x坐标。
 *        dest_y - 目标矩形y坐标。
 *        dest_width - 目标矩形宽度。
 *        dest_height - 目标矩形高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::fill_rectangle(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float dest_x,
	const float dest_y,const float dest_width,const float dest_height){
	//1.生成填充矩形所需的画刷。
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::SolidBrush brush(color);
	if(Gdiplus::Ok!=brush.GetLastStatus()){
		return(-1);
	}
	//2.创建内存位图绘制实例对象。
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.进行目标矩形区域填充，并且判断填充是否成功。
	if(Gdiplus::Ok!=graphics->FillRectangle(
		&brush,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,dest_y)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,dest_y)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,
	const int src_x,const int src_y,const int src_width,const int src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,
		dest_y,src_x,src_y,src_width,src_height,src_unit)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,
	const float src_x,const float src_y,const float src_width,const float src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,
		dest_y,src_x,src_y,src_width,src_height,src_unit)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,
		dest_x,dest_y,dest_width,dest_height)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,
		dest_x,dest_y,dest_width,dest_height)){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,const int dest_width,
	const int dest_height,const int src_x,const int src_y,const int src_width,
	const int src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,Gdiplus::Rect(
		dest_x,dest_y,dest_width,dest_height),src_x,src_y,src_width,
		src_height,src_unit)<0){
		return(-2);
	}
	//3.成功返回。
	return(0);
}

/**
 * name: paste_to_dc
 * brief: 将当前位图黏贴到指定DC设备上。
 * param: dc - 指定DC设备。
 *        dest_x - 目标区域左上角x坐标。
 *        dest_y - 目标区域左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,const float dest_width,
	const float dest_height,const float src_x,const float src_y,const float src_width,
	const float src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.更具DC，生成Graphics实例对象。
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.在指定DC上绘制位图。
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,Gdiplus::RectF(
		dest_x,dest_y,dest_width,dest_height),src_x,src_y,src_width,
		src_height,src_unit)<0){
		return(-2);
	}
	//3.成功返回。
	return(0);
}