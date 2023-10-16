#pragma once

#include"MtLayoutItem.h"

/**
 * name: MtLayoutWindowItem
 * brief: 布局项，此类中封装一个子窗口的信息。
 * author: yameng_he
 * date: 2014-11-12
 */
class MFC_TOOLKIT_API MtLayoutWindowItem
	:public MtLayoutItem{
//constructor & destructor
public:
	MtLayoutWindowItem(void);
	MtLayoutWindowItem(CWnd *window,const unsigned int stretch_factor);
	MtLayoutWindowItem(const IntRect &rect,CWnd *window,const unsigned int stretch_factor);
	virtual ~MtLayoutWindowItem(void);
//interface
public:
	virtual BOOL is_valid() const;
	virtual unsigned int get_window_amount() const;
	virtual unsigned int get_stretch_factor() const;
	virtual unsigned int get_fixed_size() const;
	virtual int resize(HDWP &hdwp,const IntRect &rect);
	void set_window(CWnd *window);
	CWnd *get_window();
	const CWnd *get_window() const;
	void set_stretch_factor(const unsigned int stretch_factor);
//variables
private:
	CWnd *_window;
	unsigned int _stretch_factor;
};