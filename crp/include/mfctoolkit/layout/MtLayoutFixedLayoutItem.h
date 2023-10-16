#pragma once

#include"MtLayoutItem.h"

class MtLayout;

/**
 * name: MtLayoutFixedLayoutItem
 * breif: 固定布局布局项类，描述一个固定尺寸布局的布局子项。
 * author: yameng_he
 * date: 2014-11-22
 */
class MFC_TOOLKIT_API MtLayoutFixedLayoutItem
	:public MtLayoutItem{
//define
public:
	typedef enum{ORIENTATION_UNKNOWN,
		ORIENTATION_HORIZON,ORIENTATION_VERTICAL} Orientation;
//constructor & destructor
public:
	MtLayoutFixedLayoutItem(void);
	MtLayoutFixedLayoutItem(MtLayout *layout,
		const Orientation orientation,const unsigned int fixed_size);
	virtual ~MtLayoutFixedLayoutItem(void);
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
	void set_orientation(const Orientation orientation);
	Orientation get_orientation() const;
	void set_fixed_size(const unsigned int fixed_size);
//variables
private:
	MtLayout *_layout;
	Orientation _orientation;
	unsigned int _fixed_size;
};

