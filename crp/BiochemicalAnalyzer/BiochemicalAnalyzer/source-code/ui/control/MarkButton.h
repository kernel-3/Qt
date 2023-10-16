#pragma once

#include"../../../../../include/mfctoolkit/control/MtImageButton.h"

/**
 * name: MarkButton
 * brief: 标记按钮，可以显示指定标记的按钮。
 * author: yameng_he
 * date: 2015-03-06
 */
class MarkButton
	:public MtImageButton{
	DECLARE_DYNAMIC(MarkButton)
//define
public:
	enum{MARK_TEXT_MARGIN=3,};
//construction & destruction
public:
	MarkButton();
	virtual ~MarkButton();
//interface
public:
	void set_mark_text(const CString &mark_text);
	void set_mark_text_alignment(const unsigned int mark_text_alignment);
	void set_mark_text_color(const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b);
//overrides
protected:
	virtual void PreSubclassWindow();
	virtual int draw_item(MtBitmap &memory_bitmap,HDC dc,const unsigned int state);
	DECLARE_MESSAGE_MAP()
//implement
private:
	int draw_mark_text(MtBitmap &memory_bitmap,HDC dc,const unsigned int state);
//variables
private:
	CString _mark_text;
	CFont _mark_text_font;
	unsigned int _mark_text_alignment;
	unsigned char _mark_text_color_a;
	unsigned char _mark_text_color_r;
	unsigned char _mark_text_color_g;
	unsigned char _mark_text_color_b;
};