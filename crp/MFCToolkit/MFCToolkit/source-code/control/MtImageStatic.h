#pragma once

#include"../Symbol"
#include<memory>

class MtBitmap;
class MtImage;
class MtRegionDivision;

/**
 * name: MtImageStatic
 * brief: 图片Static控件，负责利用图片
 *        实现Static控件的美化。
 * author: yameng_he
 * date: 2014-06-26
 */
class MFC_TOOLKIT_API MtImageStatic
	:public CStatic{
	DECLARE_DYNAMIC(MtImageStatic)
//define
public:
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
	enum{ALIGNMENT_TOP=0x00,ALIGNMENT_LEFT=0x00,
		ALIGNMENT_RIGHT=0x01,ALIGNMENT_BOTTOM=0x02,
		ALIGNMENT_HCENTER=0x04,ALIGNMENT_VCENTER=0x08};
	enum{WINDOW_MARGIN=3};
//constructor & destructor
public:
	MtImageStatic();
	virtual ~MtImageStatic();
//interface
public:
	int load_background_image(const CString &image_path,
		const int image_rows=1,const int image_cols=1);
	int load_background_image(PtrToImage image,
		const int image_rows=1,const int image_cols=1);
	void set_background_image_stretching_factors(const int stretch_left,
		const int stretch_top,const int stretch_right,const int stretch_bottom);
	void clear_background_image_stretching_factors();
	void set_background_image_index(const int index,const BOOL is_invalidate=TRUE);
	void set_text(const CString &text,const BOOL is_invalidate=FALSE);
	CString get_text();
	void set_text_alignment(const unsigned int alignment);
	unsigned int get_text_alignment() const;
	void set_text_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_invalidate=FALSE);
//overrides
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSize(UINT nType,int cx,int cy);
//implement
private:
	int invalidate_parent_window();
	int draw_background(MtBitmap &memory_bitmap);
	int draw_text(MtBitmap &memory_bitmap,const HDC dc);
//variables
private:
	CString _text;
	PtrToImage _background_image;
	PtrToRegionDivision _background_image_region_division;
	BOOL _is_background_image_stretched;
	RECT _background_image_stretching_factors;
	int _background_image_index;
	unsigned int _text_alignment;
	unsigned char _text_color_a;
	unsigned char _text_color_r;
	unsigned char _text_color_g;
	unsigned char _text_color_b;
};