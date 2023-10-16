#pragma once

#include"MtLayoutItem.h"

/**
 * name: MtLayoutFixedWindowItem
 * brief: 固定窗口布局项类，负责实现一个固定尺寸的窗口布局项。
 * author: yameng_he
 * date: 2014-11-21
 */
class MFC_TOOLKIT_API MtLayoutFixedWindowItem
	:public MtLayoutItem{
//define
public:
	typedef enum{ORIENTATION_UNKNOWN,
		ORIENTATION_HORIZON,ORIENTATION_VERTICAL} Orientation;
//constructor & destructor
public:
	MtLayoutFixedWindowItem(void);
	MtLayoutFixedWindowItem(CWnd *window,const Orientation orientation,
		const unsigned int fixed_size);
	MtLayoutFixedWindowItem(const IntRect &rect,CWnd *window,
		const Orientation orientation,const unsigned int fixed_size);
	virtual ~MtLayoutFixedWindowItem(void);
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
	void set_orientation(const Orientation orientation);
	Orientation get_orientation() const;
	void set_fixed_size(const unsigned int fixed_size);
//variables
private:
	CWnd *_window;
	Orientation _orientation;
	unsigned int _fixed_size;
};