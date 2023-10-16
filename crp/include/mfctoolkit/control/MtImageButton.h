#pragma once

#include"../Symbol"
#include<memory>

class MtBitmap;
class MtImage;
class MtRegionDivision;

/**
 * name: MtImageButton
 * brief: 图片按钮，可以设置按钮的前景图片、背景图片，
 *        并且可以设置前景图片、标题的停靠方式。
 * author: yameng_he
 * date: 2014-02-29
 * remark: 图片必须由四幅或六幅表示不同按钮状态的图像拼接而成。
 */
class MFC_TOOLKIT_API MtImageButton
	:public CButton{
	DECLARE_DYNAMIC(MtImageButton)
//define
public:
	enum{IMAGE_MARGIN=5,
		DISABLE_TEXT_COLOR_A=255,DISABLE_TEXT_COLOR_R=100,
		DISABLE_TEXT_COLOR_G=100,DISABLE_TEXT_COLOR_B=100,};
	enum{ALIGNMENT_TOP=0x00,ALIGNMENT_LEFT=0x00,
		ALIGNMENT_RIGHT=0x01,ALIGNMENT_BOTTOM=0x02,
		ALIGNMENT_HCENTER=0x04,ALIGNMENT_VCENTER=0x08};
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
	typedef enum{TYPE_BUTTON,TYPE_CHECK_BOX,TYPE_RADIO_BOX}Type;
//constructor & destructor
public:
	MtImageButton(const Type type=TYPE_BUTTON);
	virtual ~MtImageButton();
//interface
public:
	void set_checked(const BOOL is_checked,const BOOL is_invalidated=TRUE);
	BOOL get_checked() const;
	int load_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	int load_foreground_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_foreground_image(PtrToImage foreground_image,
		const int image_rows,const int image_cols);
	void set_foreground_image_alignment(const unsigned int alignment);
	void set_foreground_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_text_color(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b);
	void set_light_text_color(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b);
//overrides
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT draw_items_info);
	virtual int draw_item(MtBitmap &memory_bitmap,HDC dc,const unsigned int state);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT flags,CPoint point);
	afx_msg void OnMouseHover(UINT flags,CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC * /*dc*/);
//implement
private:
	int update_parent_window();
	int draw_background(MtBitmap &memory_bitmap,const unsigned int state);
	CRect draw_foreground(MtBitmap &memory_bitmap,HDC dc,const unsigned int state);
	int draw_text(MtBitmap &memory_bitmap,const CRect &foreground_image_rect,
		HDC dc,const unsigned int state);
//variables
private:
	Type _type;
	BOOL _is_mouse_tracking;
	BOOL _is_mouse_hover;
	BOOL _is_checked;
	//int _last_state;
	PtrToImage _background_image;
	PtrToRegionDivision _background_image_region_division;
	BOOL _is_background_image_stretched;
	RECT _background_image_stretching_factors;
	PtrToImage _foreground_image;
	PtrToRegionDivision _foreground_image_region_division;
	unsigned int _foreground_image_alignment;
	BOOL _is_foreground_image_stretched;
	RECT _foreground_image_stretching_factors;
	unsigned char _text_color_a;
	unsigned char _text_color_r;
	unsigned char _text_color_g;
	unsigned char _text_color_b;
	unsigned char _light_text_color_a;
	unsigned char _light_text_color_r;
	unsigned char _light_text_color_g;
	unsigned char _light_text_color_b;
};