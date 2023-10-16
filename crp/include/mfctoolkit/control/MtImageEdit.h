#pragma once

#include"../Symbol"
#include<memory>

class MtBitmap;
class MtImage;
class MtRegionDivision;

/**
 * name: MtImageEdit
 * brief: 图片编辑框类，实现皮肤编辑框。
 * author: yameng_he
 * date: 2014-08-12
 * remark: 控件背景图片是由两副不同状态的图片拼接而成。
 */
class MFC_TOOLKIT_API MtImageEdit
	:public CEdit{
	DECLARE_DYNAMIC(MtImageEdit)
//define
public:
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::shared_ptr<MtRegionDivision> PtrToRegionDivision;
	static const COLORREF DISABLE_TEXT_COLOR;
//constructor & destructor
public:
	MtImageEdit();
	virtual ~MtImageEdit();
//interface
public:
	int load_background_image(const CString &image_path,
		const int image_rows,const int image_cols);
	int load_background_image(PtrToImage image,
		const int image_rows,const int image_cols);
	void set_background_image_stretching_factors(
		const int stretch_left,const int stretch_top,
		const int stretch_right,const int stretch_bottom);
	void set_text_color(const unsigned char text_color_r,
		const unsigned char text_color_g,const unsigned char text_color_b,
		const BOOL is_invalidated=FALSE);
//overrides
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg HBRUSH CtlColor(CDC *pDC,UINT nCtlColor);
	afx_msg void OnEnChange();
//implement
private:
	int draw_background(MtBitmap &memory_bitmap,const unsigned int state);
//variables
private:
	PtrToImage _background_image;
	PtrToRegionDivision _background_image_region_division;
	BOOL _is_background_image_stretched;
	RECT _background_image_stretching_factors;
	BOOL _is_there_in_focus;
	unsigned char _text_color_r;
	unsigned char _text_color_g;
	unsigned char _text_color_b;
};