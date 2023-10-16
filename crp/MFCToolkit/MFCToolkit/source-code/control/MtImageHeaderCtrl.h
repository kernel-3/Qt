#pragma once

#include"../Symbol"
#include<memory>

class MtImage;
class MtBitmap;
class MtRegionDivision;

/**
 * name: MtImageHeaderCtrl
 * brief: 图片标题窗口，用来实现列表框的标题窗口。
 * author: yameng_he
 * date: 2015-03-19
 */
class MFC_TOOLKIT_API MtImageHeaderCtrl
	:public CHeaderCtrl{
	DECLARE_DYNAMIC(MtImageHeaderCtrl)
//define
public:
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
	enum{ALIGNMENT_TOP=0x00,ALIGNMENT_LEFT=0x00,
		ALIGNMENT_RIGHT=0x01,ALIGNMENT_BOTTOM=0x02,
		ALIGNMENT_HCENTER=0x04,ALIGNMENT_VCENTER=0x08};
//construction & destruction
public:
	MtImageHeaderCtrl();
	virtual ~MtImageHeaderCtrl();
//interface
public:
	void set_height(const unsigned int height);
	unsigned int get_height() const;
	int load_item_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_item_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_item_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_item_text_color(const unsigned char &color_a,
		const unsigned char &color_r,const unsigned char &color_g,
		const unsigned char &color_b);
	void set_item_text_alignment(const unsigned int alignment);
	unsigned int get_item_text_alignment() const;
//overrides
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg LRESULT OnLayout(WPARAM wParam,LPARAM lParam);
//implement
private:
	int draw_item_background(MtBitmap &memory_bitmap,
		const CRect &item_rect,const unsigned int state);
	int draw_item_text(MtBitmap &memory_bitmap,const CString &text,
		const CRect &rect,HDC dc);
//variables
private:
	unsigned int _height;
	PtrToImage _item_background_image;
	PtrToRegionDivision _item_background_image_region_division;
	BOOL _is_item_background_image_stretched;
	RECT _item_background_image_stretching_factors;
	unsigned char _item_text_color_a;
	unsigned char _item_text_color_r;
	unsigned char _item_text_color_g;
	unsigned char _item_text_color_b;
	unsigned int _item_text_alignment;
};