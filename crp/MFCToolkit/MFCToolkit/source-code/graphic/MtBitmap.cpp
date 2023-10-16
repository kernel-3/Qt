#include"stdafx.h"
#include"MtBitmap.h"
#include"../tool/MtCharacterSet.h"

/**
 * name: MtBitmap
 * brief: ���캯���������λͼ���г�ʼ����
 * param: width - λͼ��ȡ�
 *        height - λͼ�߶ȡ�
 *        pixel_format - λͼ��ʽ��
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
 * brief: ����������
 * param: --
 * return: --
 */
MtBitmap::~MtBitmap(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰλͼ�Ƿ���Ч��
 * param:
 * return: �����ǰλͼ��Ч����TRUE�����򷵻�FALSE��
 */
BOOL MtBitmap::is_valid() const{
	return(_is_valid);
}

/**
 * name: get_width
 * brief: ��ȡλͼ��ȡ�
 * param: --
 * return: ����λͼ��ȡ�
 */
int MtBitmap::get_width(){
	return(static_cast<int>(_bitmap.GetWidth()));
}

/**
 * name: get_height
 * brief: ��ȡλͼ�߶ȡ�
 * param: --
 * return: ����λͼ�߶ȡ�
 */
int MtBitmap::get_height(){
	return(static_cast<int>(_bitmap.GetHeight()));
}

/**
 * name: create_graphics
 * brief: Ϊ��ǰλͼ�Ĵ���һ����ͼ����
 * param: --
 * return: �����´����Ļ�ͼ����
 */
MtBitmap::PtrToGraphics MtBitmap::create_graphics(){
	return(PtrToGraphics(new Gdiplus::Graphics(&_bitmap)));
}

/**
 * name: fill
 * brief: ��ָ����ɫ���λͼ��
 * param: color_a - ��ɫ��A������
 *        color_r - ��ɫ��R������
 *        color_g - ��ɫ��G������
 *        color_r - ��ɫ��R������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
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
 * brief: ���ڴ�λͼָ����������д�ı���
 * param: text - ��д���ı���
 *        dc - ��ͼ�豸DC��
 *        font - ��������
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        color_a - �ı���ɫa������
 *        color_r - �ı���ɫr������
 *        color_g - �ı���ɫg������
 *        color_b - �ı���ɫb������
 *        alignment_h - �ı�ˮƽͣ����ʽ��
 *        alignment_v - �ı���ֱͣ����ʽ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
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
 * brief: ���ڴ�λͼָ����������д�ı���
 * param: text - ��д���ı���
 *        dc - ��ͼ�豸DC��
 *        font - ��������
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        color_a - �ı���ɫa������
 *        color_r - �ı���ɫr������
 *        color_g - �ı���ɫg������
 *        color_b - �ı���ɫb������
 *        alignment_h - �ı�ˮƽͣ����ʽ��
 *        alignment_v - �ı���ֱͣ����ʽ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_text(const CString &text,HDC dc,HFONT font,const float dest_x,
	const float dest_y,const float dest_width,const float dest_height,const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,const unsigned char color_b,
	const Alignment alignment_h/*=ALIGNMENT_CENTER*/,const Alignment alignment_v/*ALIGNMENT_CENTER*/){
	//1.���ı�ת��Ϊ���ַ�����ʾ��
	const CStringW text_w=MtCharacterSet::to_unicode(text);
	//2.����Gdiplus����ʵ����
	Gdiplus::Font text_font(dc,font);
	if(Gdiplus::Ok!=text_font.GetLastStatus()){
		return(-1);
	}
	//3.�����ı���д��ʽ��Ϣ��
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
	//4.�����ı���д��ˢ��
	Gdiplus::SolidBrush text_brush(Gdiplus::Color(color_a,color_r,
		color_g,color_b));
	if(Gdiplus::Ok!=text_brush.GetLastStatus()){
		return(-5);
	}
	//5.�����ڴ�λͼ����ʵ������
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
	//6.���ڴ�λͼ�Ͻ����ı����ơ�
	if(Gdiplus::Ok!=graphics->DrawString(text_w,text_w.GetLength(),&text_font,
		Gdiplus::RectF(dest_x,dest_y,dest_width,dest_height),&text_format,
		&text_brush)){
		return(-10);
	}
	//7.�ɹ����ء�
	return(0);
}

/**
 * name: draw_line
 * brief: ���ڴ�λͼ�ϻ���ֱ�ߡ�
 * param: color_a - ֱ����ɫ��A������
 *        color_r - ֱ����ɫ��R������
 *        color_g - ֱ����ɫ��G������
 *        color_b - ֱ����ɫ��B������
 *        line_width - ָ��ֱ�߿�ȡ�
 *        begin_x - ֱ����ʼ��x���ꡣ
 *        begin_y - ֱ����ʼ��y���ꡣ
 *        end_x - ֱ���յ�x���ꡣ
 *        end_y - ֱ���յ�y���ꡣ
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_line(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float line_width,
	const int begin_x,const int begin_y,const int end_x,const int end_y){
	//1.���ɻ������軭�ʡ�
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,line_width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.�����ڴ�λͼ�Ļ��߲�����
	if(Gdiplus::Ok!=graphics->DrawLine(&pen,begin_x,begin_y,end_x,end_y)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: draw_line
 * brief: ���ڴ�λͼ�ϻ���ֱ�ߡ�
 * param: color_a - ֱ����ɫ��A������
 *        color_r - ֱ����ɫ��R������
 *        color_g - ֱ����ɫ��G������
 *        color_b - ֱ����ɫ��B������
 *        line_width - ָ��ֱ�߿�ȡ�
 *        begin_x - ֱ����ʼ��x���ꡣ
 *        begin_y - ֱ����ʼ��y���ꡣ
 *        end_x - ֱ���յ�x���ꡣ
 *        end_y - ֱ���յ�y���ꡣ
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_line(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float line_width,
	const float begin_x,const float begin_y,const float end_x,const float end_y){
	//1.���ɻ������軭�ʡ�
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,line_width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.�����ڴ�λͼ�Ļ��߲�����
	if(Gdiplus::Ok!=graphics->DrawLine(&pen,begin_x,begin_y,end_x,end_y)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: draw_rectangle
 * breif: ���������Ρ�
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        dest_x - Ŀ�����x���ꡣ
 *        dest_y - Ŀ�����y���ꡣ
 *        dest_width - Ŀ����ο�ȡ�
 *        dest_height - Ŀ����θ߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.���ɻ��ƾ�������Ļ��ʡ�
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.����Ŀ�����������ƣ������жϻ����Ƿ�ɹ���
	if(Gdiplus::Ok!=graphics->DrawRectangle(
		&pen,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: draw_rectangle
 * breif: ���������Ρ�
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        dest_x - Ŀ�����x���ꡣ
 *        dest_y - Ŀ�����y���ꡣ
 *        dest_width - Ŀ����ο�ȡ�
 *        dest_height - Ŀ����θ߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height){
	//1.���ɻ��ƾ�������Ļ��ʡ�
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.����Ŀ�����������ƣ������жϻ����Ƿ�ɹ���
	if(Gdiplus::Ok!=graphics->DrawRectangle(
		&pen,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: draw_curve
 * breif: �������ߡ�
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        width - ���߿�ȡ�
 *        points - �����ϵĵ㡣
 *        count  - ���������
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_curve(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float width,
	CPoint *points,const unsigned int count){
	//1.�����ǰ���ݲ������Ϸ�����ֱ�ӷ��ش���
	if((0==points)||(0==count)){
		return(-1);
	}
	//2.���ɻ�����������Ļ��ʡ�
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::Pen pen(color,width);
	if(Gdiplus::Ok!=pen.GetLastStatus()){
		return(-2);
	}
	//3.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-4);
	}
	//4.�������ߵĻ��ƣ������жϻ����Ƿ�ɹ���
	if(Gdiplus::Ok!=graphics->DrawCurve
		(&pen,reinterpret_cast<
		Gdiplus::Point*>(points),count)){
		return(-5);
	}
	//5.�ɹ����ء�
	return(0);
}

/**
 * name: draw_point
 * breif: ���Ƶ㡣
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        points - �����ϵĵ㡣
 *        count  - ���������
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::draw_point(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,
	CPoint *points,const unsigned int count){
	//1.�����ǰ���ݲ������Ϸ�����ֱ�ӷ��ش���
	if((0==points)||(0==count)){
		return(-1);
	}
	//2.���Ƶ㡣
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	for(unsigned int i=0;i!=count;++i){
		_bitmap.SetPixel(points[i].x,points[i].y,color);
	}
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: fill_rectangle
 * brief: ��ָ����ɫ���λͼ��ָ�����Ρ�
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        dest_x - Ŀ�����x���ꡣ
 *        dest_y - Ŀ�����y���ꡣ
 *        dest_width - Ŀ����ο�ȡ�
 *        dest_height - Ŀ����θ߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::fill_rectangle(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.��������������Ļ�ˢ��
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::SolidBrush brush(color);
	if(Gdiplus::Ok!=brush.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.����Ŀ�����������䣬�����ж�����Ƿ�ɹ���
	if(Gdiplus::Ok!=graphics->FillRectangle(
		&brush,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: fill_rectangle
 * brief: ��ָ����ɫ���λͼ��ָ�����Ρ�
 * param: color_a - ��ɫA������
 *        color_r - ��ɫR������
 *        color_g - ��ɫG������
 *        color_b - ��ɫB������
 *        dest_x - Ŀ�����x���ꡣ
 *        dest_y - Ŀ�����y���ꡣ
 *        dest_width - Ŀ����ο�ȡ�
 *        dest_height - Ŀ����θ߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::fill_rectangle(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b,const float dest_x,
	const float dest_y,const float dest_width,const float dest_height){
	//1.��������������Ļ�ˢ��
	Gdiplus::Color color(color_a,color_r,color_g,color_b);
	Gdiplus::SolidBrush brush(color);
	if(Gdiplus::Ok!=brush.GetLastStatus()){
		return(-1);
	}
	//2.�����ڴ�λͼ����ʵ������
	PtrToGraphics graphics=create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	//3.����Ŀ�����������䣬�����ж�����Ƿ�ɹ���
	if(Gdiplus::Ok!=graphics->FillRectangle(
		&brush,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	//4.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,dest_y)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,dest_y)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,
	const int src_x,const int src_y,const int src_width,const int src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,
		dest_y,src_x,src_y,src_width,src_height,src_unit)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,
	const float src_x,const float src_y,const float src_width,const float src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,dest_x,
		dest_y,src_x,src_y,src_width,src_height,src_unit)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,
		dest_x,dest_y,dest_width,dest_height)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,
		dest_x,dest_y,dest_width,dest_height)){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const int dest_x,const int dest_y,const int dest_width,
	const int dest_height,const int src_x,const int src_y,const int src_width,
	const int src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,Gdiplus::Rect(
		dest_x,dest_y,dest_width,dest_height),src_x,src_y,src_width,
		src_height,src_unit)<0){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}

/**
 * name: paste_to_dc
 * brief: ����ǰλͼ�����ָ��DC�豸�ϡ�
 * param: dc - ָ��DC�豸��
 *        dest_x - Ŀ���������Ͻ�x���ꡣ
 *        dest_y - Ŀ���������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtBitmap::paste_to_dc(HDC dc,const float dest_x,const float dest_y,const float dest_width,
	const float dest_height,const float src_x,const float src_y,const float src_width,
	const float src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	//1.����DC������Graphicsʵ������
	Gdiplus::Graphics graphics(dc);
	if(Gdiplus::Ok!=graphics.GetLastStatus()){
		return(-1);
	}
	//2.��ָ��DC�ϻ���λͼ��
	if(Gdiplus::Ok!=graphics.DrawImage(&_bitmap,Gdiplus::RectF(
		dest_x,dest_y,dest_width,dest_height),src_x,src_y,src_width,
		src_height,src_unit)<0){
		return(-2);
	}
	//3.�ɹ����ء�
	return(0);
}