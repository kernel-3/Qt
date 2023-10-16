#pragma once

#include"MtLayoutItem.h"

class MtLayout;

/**
 * name: MtLayoutLayoutItem
 * brief: 布局项，此类中封装一个子布局的信息。
 * author: yameng_he
 * date: 2014-11-12
 */
class MFC_TOOLKIT_API MtLayoutLayoutItem
	:public MtLayoutItem{
//constructor & destructor
public:
	MtLayoutLayoutItem(void);
	MtLayoutLayoutItem(MtLayout *layout,const unsigned int stretch_factor);
	virtual ~MtLayoutLayoutItem(void);
//interface
public:
	virtual BOOL is_valid() const;
	virtual unsigned int get_window_amount() const;
	virtual unsigned int get_stretch_factor() const;
	virtual unsigned int get_fixed_size() const;
	virtual int resize(HDWP &hdwp,const IntRect &rect);
	void set_layout(MtLayout *layout);
	MtLayout *get_layout();
	const MtLayout *get_layout() const;
	void set_stretch_factor(const unsigned int stretch_factor);
//variables
private:
	MtLayout *_layout;
	unsigned int _stretch_factor;
};