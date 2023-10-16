#pragma once

#include"../Symbol"
#include<Gdiplus.h>
#include<memory>

class MtBitmap;

/**
 * name: MtImage
 * brief: 图片类，负责封装图片的数据以及实现图片相关功能。
 * author: yameng_he
 * date: 2014-05-26
 */
class MFC_TOOLKIT_API MtImage{
//define
public:
	typedef std::shared_ptr<Gdiplus::Graphics> PtrToGraphics;
//constructor & destructor
public:
	MtImage(const CString &image_path,const BOOL is_color_correction_forbidden=FALSE);
	~MtImage(void);
//interface
public:
	BOOL is_valid() const;
	int get_width();
	int get_height();
	PtrToGraphics create_graphics();
	int paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y);
	int paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y);
	int paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y,
		const int src_x,const int src_y,const int src_width,const int src_height,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y,
		const float src_x,const float src_y,const float src_width,const float src_height,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y,
		const int dest_width,const int dest_height);
	int paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y,
		const float dest_width,const float dest_height);
	int paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y,const int dest_width,
		const int dest_height,const int src_x,const int src_y,const int src_width,
		const int src_height,const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y,const float dest_width,
		const float dest_height,const float src_x,const float src_y,const float src_width,
		const float src_height,const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap_ex(MtBitmap *bitmap,const int dest_x,const int dest_y,
		const int dest_width,const int dest_height,const int src_l_stretch,
		const int src_t_stretch,const int src_r_stretch,const int src_b_stretch,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap_ex(MtBitmap *bitmap,const float dest_x,const float dest_y,
		const float dest_width,const float dest_height,const float src_l_stretch,
		const float src_t_stretch,const float src_r_stretch,const float src_b_stretch,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap_ex(MtBitmap *bitmap,const int dest_x,const int dest_y,const int dest_width,
		const int dest_height,const int src_x,const int src_y,const int src_width,const int src_height,
		const int src_l_stretch,const int src_t_stretch,const int src_r_stretch,const int src_b_stretch,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
	int paste_to_bitmap_ex(MtBitmap *bitmap,const float dest_x,const float dest_y,const float dest_width,
		const float dest_height,const float src_x,const float src_y,const float src_width,const float src_height,
		const float src_l_stretch,const float src_t_stretch,const float src_r_stretch,const float src_b_stretch,
		const Gdiplus::Unit src_unit=Gdiplus::UnitPixel);
//restrict
private:
	MtImage(const MtImage &);
	MtImage &operator=(const MtImage &);
//variables
private:
	BOOL _is_valid;
	Gdiplus::Image _image;
};