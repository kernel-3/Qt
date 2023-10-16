#pragma once

#include"MtLayoutItem.h"

/**
 * name: MtLayoutStretchItem
 * brief: 拉伸项，负责为布局提供可拉伸的间隔。
 * author: yameng_he
 * date: 2014-11-12
 */
class MFC_TOOLKIT_API MtLayoutStretchItem
	:public MtLayoutItem{
//constructor & destructor
public:
	MtLayoutStretchItem(void);
	MtLayoutStretchItem(const unsigned int stretch_factor);
	virtual ~MtLayoutStretchItem(void);
//interface
public:
	virtual BOOL is_valid() const;
	virtual unsigned int get_window_amount() const;
	virtual unsigned int get_stretch_factor() const;
	virtual unsigned int get_fixed_size() const;
	virtual int resize(HDWP &hdwp,const IntRect &rect);
	void set_stretch_factor(const unsigned int stretch_factor);
//variables
private:
	unsigned int _stretch_factor;
};