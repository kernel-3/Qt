#pragma once

#include"../Symbol"

template<typename _Tp>
class MtLayoutRect;

/**
 * name: MtLayoutItem
 * brief: 布局项类，负责存储一个布局中某一个单元的相关信息。
 * author: yameng_he
 * date: 2014-11-10
 */
class MFC_TOOLKIT_API MtLayoutItem{
//define
public:
	typedef MtLayoutRect<int> IntRect;
//constructor & destructor
public:
	MtLayoutItem(void);
	MtLayoutItem(const IntRect &rect);
	virtual ~MtLayoutItem(void);
//interface
public:
	virtual BOOL is_valid() const=0;
	virtual unsigned int get_window_amount() const=0;
	virtual unsigned int get_stretch_factor() const=0;
	virtual unsigned int get_fixed_size() const=0;
	virtual int resize(HDWP &hdwp,const IntRect &rect)=0;
	int get_width() const;
	int get_height() const;
	const IntRect &get_rect() const;
//derived
protected:
	IntRect *_rect;
//restrict
private:
	MtLayoutItem(const MtLayoutItem &);
	MtLayoutItem &operator=(const MtLayoutItem &);
}; 