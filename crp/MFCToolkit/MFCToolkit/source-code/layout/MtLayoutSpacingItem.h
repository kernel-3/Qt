#pragma once

#include"MtLayoutItem.h"

/**
 * name: MtLayoutSpacingItem
 * brief: 间隔项，负责为布局提供固定的间隔尺寸。
 * author: yameng_he
 * date: 2014-11-12
 */
class MFC_TOOLKIT_API MtLayoutSpacingItem
	:public MtLayoutItem{
//define
public:
	typedef enum{ORIENTATION_UNKNOWN,
		ORIENTATION_HORIZON,ORIENTATION_VERTICAL} Orientation;
//constructor & destructor
public:
	MtLayoutSpacingItem(void);
	MtLayoutSpacingItem(const Orientation orientation,
		const unsigned int fixed_size);
	virtual ~MtLayoutSpacingItem(void);
//interface
public:
	virtual BOOL is_valid() const;
	virtual unsigned int get_window_amount() const;
	virtual unsigned int get_stretch_factor() const;
	virtual unsigned int get_fixed_size() const;
	virtual int resize(HDWP &hdwp,const IntRect &rect);
	void set_orientation(const Orientation orientation);
	Orientation get_orientation() const;
	void set_fixed_size(const unsigned int fixed_size);
//variables
private:
	Orientation _orientation;
	unsigned int _fixed_size;
};