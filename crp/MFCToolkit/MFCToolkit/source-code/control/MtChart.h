#pragma once

#include"../Symbol"
#include<memory>

class MtBitmap;

/**
 * name: MtChart
 * breif: 图表控件，它是所有图表控件（例如：柱状图、曲线图、饼状图等等）的基类。
 *        抽象类，不能实例化。
 * author: yameng_he
 * date: 2015-10-27
 */
class MFC_TOOLKIT_API MtChart
	:public CWnd{
	DECLARE_DYNAMIC(MtChart)
//define
public:
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
//construction & destruction
public:
	MtChart();
	virtual ~MtChart();
//interface
public:
	void set_background_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b);
	void set_border_color(const unsigned char color_a,
		const unsigned char color_r,const unsigned char color_g,
		const unsigned char color_b);
//overrides
protected:
	virtual int draw(const HDC dest_dc,MtBitmap &dest_bitmap)=0;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
//implement
private:
	static int register_class();
//variables
public:
	static const CString CLASS_NAME;
//variables
private:
	unsigned char _background_color_a;
	unsigned char _background_color_r;
	unsigned char _background_color_g;
	unsigned char _background_color_b;
	unsigned char _border_color_a;
	unsigned char _border_color_r;
	unsigned char _border_color_g;
	unsigned char _border_color_b;
};