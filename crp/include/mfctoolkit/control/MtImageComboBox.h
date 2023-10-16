#pragma once

#include"../Symbol"
#include<memory>

class MtBitmap;
class MtImage;
class MtRegionDivision;

/**
 * name: MtImageComboBox
 * brief: 图片下拉框，负责利用图片对下拉框控件
 *        进行美化。
 * author: yameng_he
 * date: 2014-07-01
 * remark: 控件背景图片必须由四幅表示不同状态的图像拼接而成，而列表框
 *         图片应由两幅不同状态的图片拼接而成。
 *         使用此类时，需将下拉框控件Hasing String属性设置为TRUE，
 *         Owner Draw属性设置为Variable，而Type属性设置为Drop List。
 * note:   目前尚不能使用语句对下拉框进行CBS_OWNERDRAWFIXED以及
 *         CBS_OWNERDRAWVARIABLE风格进行修改，需要上网查询其实现
 *         方法。
 */
class MFC_TOOLKIT_API MtImageComboBox
	:public CComboBox{
	DECLARE_DYNAMIC(MtImageComboBox)
//define
public:
	enum{TEXT_MARGIN=1,
		DISABLE_TEXT_COLOR_A=255,DISABLE_TEXT_COLOR_R=100,
		DISABLE_TEXT_COLOR_G=100,DISABLE_TEXT_COLOR_B=100,};
	enum{ALIGNMENT_TOP=0x00,ALIGNMENT_LEFT=0x00,
		ALIGNMENT_RIGHT=0x01,ALIGNMENT_BOTTOM=0x02,
		ALIGNMENT_HCENTER=0x04,ALIGNMENT_VCENTER=0x08};
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
//constructor & destructor
public:
	MtImageComboBox();
	virtual ~MtImageComboBox();
//interface
public:
	int load_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_text_alignment(const unsigned int alignment);
	void set_text_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_invalidate=FALSE);
	int load_list_box_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_list_box_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_list_box_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_list_box_text_alignment(const unsigned int alignment);
	void set_list_box_text_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b,const BOOL is_invalidate=FALSE);
//overrides
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnMouseHover(UINT nFlags,CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg HBRUSH CtlColor(CDC *pDC,UINT/*nCtlColor*/);
	afx_msg void OnCbnDropdown();
	afx_msg void OnCbnCloseup();
//implement
private:
	int draw_background(MtBitmap &memory_bitmap,const unsigned int state);
	int draw_text(MtBitmap &memory_bitmap,const unsigned int state,const HDC dc);
	int draw_list_box_background(MtBitmap &memory_bitmap,const unsigned int state);
	int draw_list_box_text(MtBitmap &memory_bitmap,const HDC dc,const CString &text);
//variables
private:
	BOOL _is_mouse_tracking;
	BOOL _is_mouse_hover;
	BOOL _is_list_box_visible;
	PtrToImage _background_image;
	PtrToRegionDivision _background_image_region_division;
	BOOL _is_background_image_stretched;
	RECT _background_image_stretching_factors;
	unsigned int _text_alignment;
	unsigned char _text_color_a;
	unsigned char _text_color_r;
	unsigned char _text_color_g;
	unsigned char _text_color_b;
	PtrToImage _list_box_background_image;
	PtrToRegionDivision _list_box_background_image_slicer;
	BOOL _is_list_box_background_image_stretched;
	RECT _list_box_background_image_stretching_factors;
	unsigned int _list_box_text_alignment;
	unsigned char _list_box_text_color_a;
	unsigned char _list_box_text_color_r;
	unsigned char _list_box_text_color_g;
	unsigned char _list_box_text_color_b;
};