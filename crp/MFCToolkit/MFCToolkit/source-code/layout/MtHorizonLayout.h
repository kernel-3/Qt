#pragma once

#include"MtLayout.h"

/**
 * name: MtHorizonLayout
 * brief: 水平布局，负责实现布局管理中的水平布局管理。
 * author: yameng_he
 * date: 2014-11-13
 */
class MFC_TOOLKIT_API MtHorizonLayout
	:public MtLayout{
//constructor & destructor
public:
	MtHorizonLayout(void);
	virtual ~MtHorizonLayout(void);
//interface
public:
	virtual int resize(HDWP &hdwp,const IntRect &rect);
	virtual int resize(const unsigned int width,const unsigned int height);
	virtual int add_spacing(const unsigned int spacing_size);
	virtual int add_fixed_layout(MtLayout *layout,const unsigned int fixed_size);
	virtual int add_fixed_window(CWnd *window,const unsigned int fixed_size);
	virtual int set_item_fixed_window(const unsigned int index,CWnd *window,
		const unsigned int fixed_size);
};
