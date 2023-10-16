#pragma once

#include"../Symbol"
#include<Gdiplus.h>
#include<memory>

class MtImage;

/**
 * name: MtBitmap
 * brief: 位图类，维护一幅位图的数据以及位图相关的功能。
 * author: yameng_he
 * date: 2014-05-26
 */
class MFC_TOOLKIT_API MtBitmap{
//define
public:
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	typedef std::shared_ptr<Gdiplus::Graphics> PtrToGraphics;
	typedef enum{ALIGNMENT_NEAR=Gdiplus::StringAlignmentNear,
		ALIGNMENT_CENTER=Gdiplus::StringAlignmentCenter,
		ALIGNMENT_FAR=Gdiplus::StringAlignmentFar}Alignment;
//constructor & destructor
public:
	MtBitmap(const unsigned int width,const unsigned int height,
		const Gdiplus::PixelFormat pixel_format=PixelFormat32bppARGB);
	~MtBitmap(void);
//interface
public:
	BOOL is_valid() const;
	int get_width();
	int get_height();
	PtrToGraphics create_graphics();
	int fill(const unsigned char color_a=0,const unsigned char color_r=0,
		const unsigned char color_g=0,const unsigned char color_b=0);
	int draw_text(const CString &text,HDC dc,HFONT font,const int dest_x,
		const int dest_y,const int dest_width,const int dest_height,
		const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,
		const Alignment alignment_h=ALIGNMENT_CENTER,
		const Alignment alignment_v=ALIGNMENT_CENTER);
	int draw_text(const CString &text,HDC dc,HFONT font,const float dest_x,
		const float dest_y,const float dest_width,const float dest_height,
		const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,
		const Alignment alignment_h=ALIGNMENT_CENTER,
		const Alignment alignment_v=ALIGNMENT_CENTER);
	int draw_line(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const float line_width,
		const int begin_x,const int begin_y,const int end_x,const int end_y);
	int draw_line(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const float line_width,
		const float begin_x,const float begin_y,const float end_x,const float end_y);
	int draw_rectangle(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const int dest_x,
		const int dest_y,const int dest_width,const int dest_height);
	int draw_rectangle(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const float dest_x,
		const float dest_y,const float dest_width,const float dest_height);
	int draw_curve(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const float width,
		CPoint *points,const unsigned int count);
	int draw_point(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,
		CPoint *points,const unsigned int count);
	int fill_rectangle(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const int dest_x,
		const int dest_y,const int dest_width,const int dest_height);
	int fill_rectangle(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b,const float dest_x,
		const float dest_y,const float dest_width,const float dest_height);
	int paste_to_dc(HDC dc,const int dest_x,const int dest_y);
	int paste_to_dc(HDC dc,const float dest_x,const float dest_y);
	int paste_to_dc(HDC dc,const int dest_x,const int dest_y,
		const int src_x,const int src_y,const int src_width,const int src_height,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_dc(HDC dc,const float dest_x,const float dest_y,
		const float src_x,const float src_y,const float src_width,const float src_height,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_dc(HDC dc,const int dest_x,const int dest_y,
		const int dest_width,const int dest_height);
	int paste_to_dc(HDC dc,const float dest_x,const float dest_y,
		const float dest_width,const float dest_height);
	int paste_to_dc(HDC dc,const int dest_x,const int dest_y,const int dest_width,
		const int dest_height,const int src_x,const int src_y,const int src_width,
		const int src_height,const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_dc(HDC dc,const float dest_x,const float dest_y,const float dest_width,
		const float dest_height,const float src_x,const float src_y,const float src_width,
		const float src_height,const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
//restrict
private:
	MtBitmap(const MtBitmap &);
	MtBitmap &operator=(const MtBitmap &);
//variables
private:
	BOOL _is_valid;
	Gdiplus::Bitmap _bitmap;
};