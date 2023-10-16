#pragma once

#include"../Symbol"
#include<memory>

class MtImage;
class MtBitmap;
class MtRegionDivision;
class MtImageHeaderCtrl;

/**
 * name: MtImageListCtrl
 * brief: 图片列表控件，自绘列表框的实现。
 * author: yameng_he
 * date: 2015-03-21
 * log:  目前版本的列表控件中存在如下问题。
 *       1 ）列表控件初始化时如果不重新挑用MoveWindows函数，则对于
 *           列表控件行高的设置无效（2015-03-25）。
 */
class MFC_TOOLKIT_API MtImageListCtrl
	:public CListCtrl{
	DECLARE_DYNAMIC(MtImageListCtrl)
//define
public:
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
	enum{ALIGNMENT_TOP=0x00,ALIGNMENT_LEFT=0x00,
		ALIGNMENT_RIGHT=0x01,ALIGNMENT_BOTTOM=0x02,
		ALIGNMENT_HCENTER=0x04,ALIGNMENT_VCENTER=0x08};
//construction & destruction
public:
	MtImageListCtrl();
	virtual ~MtImageListCtrl();
//interface
public:
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
	void set_item_light_text_color(const unsigned char &color_a,
		const unsigned char &color_r,const unsigned char &color_g,
		const unsigned char &color_b);
	void set_item_text_alignment(const unsigned int alignment);
	unsigned int get_item_text_alignment() const;
	void set_item_row_height(const unsigned int height);
	unsigned int get_item_row_height() const;
	int load_header_item_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_header_item_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_header_item_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_header_item_text_color(const unsigned char &color_a,
		const unsigned char &color_r,const unsigned char &color_g,
		const unsigned char &color_b);
	void set_header_item_text_alignment(const unsigned int alignment);
	unsigned int get_header_item_text_alignment() const;
//overrides
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int draw_item(MtBitmap &memory_bitmap,const int item,const int sub_item,
		const CRect &item_rect,const unsigned int state);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
//implement
private:
	int draw_item_background(MtBitmap &memory_bitmap,
		const CRect &item_rect,const unsigned int state);
	int draw_item_text(MtBitmap &memory_bitmap,const CString &text,
		const CRect &rect,const unsigned int state,HDC dc);
//variables
private:
	PtrToImage _item_background_image;
	PtrToRegionDivision _item_background_image_region_division;
	BOOL _is_item_background_image_stretched;
	RECT _item_background_image_stretching_factors;
	unsigned char _item_text_color_a;
	unsigned char _item_text_color_r;
	unsigned char _item_text_color_g;
	unsigned char _item_text_color_b;
	unsigned char _item_light_text_color_a;
	unsigned char _item_light_text_color_r;
	unsigned char _item_light_text_color_g;
	unsigned char _item_light_text_color_b;
	unsigned int _item_text_alignment;
	unsigned int _item_row_height;
	MtImageHeaderCtrl *_header;
};