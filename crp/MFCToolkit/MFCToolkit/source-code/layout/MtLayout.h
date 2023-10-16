#pragma once

#include"../Symbol"
#include<memory>
#include<vector>

class MtLayoutItem;
template<typename _Tp>
class MtLayoutRect;
template<typename _Tp>
class MtLayoutSize;

/**
 * name: MtLayout
 * brief: 布局类，是系统中所有种类布局的基类，提供布局的统一操作接口。
 * author: yameng_he
 * date: 2014-11-10
 */
class MFC_TOOLKIT_API MtLayout{
//define
public:
	typedef std::shared_ptr<MtLayoutItem> PtrToItem;
	typedef std::vector<PtrToItem> ItemVector;
	typedef MtLayoutRect<int> IntRect;
	typedef MtLayoutRect<unsigned int> UintRect;
	typedef MtLayoutSize<int> IntSize;
//constructor & destructor
public:
	MtLayout(void);
	virtual ~MtLayout(void);
//interface
public:
	virtual int resize(HDWP &hdwp,const IntRect &rect)=0;
	virtual int resize(const unsigned int width,const unsigned int height)=0;
	virtual int add_spacing(const unsigned int spacing_size)=0;
	virtual int add_fixed_layout(MtLayout *layout,const unsigned int fixed_size)=0;
	virtual int add_fixed_window(CWnd *window,const unsigned int fixed_size)=0;
	int add_stretch(const unsigned int stretch_factor);
	int add_layout(MtLayout *layout,const unsigned int stretch_factor);
	int add_window(CWnd *window,const unsigned int stretch_factor);
	void set_margin(const UintRect &margin);
	void set_margin(const unsigned int left_margin,
		const unsigned int top_margin,const unsigned int right_margin,
		const unsigned int bottom_margin);
	const UintRect &get_margin() const;
	unsigned int get_window_amount() const;
	const IntRect &get_rect() const;
	int get_item_size(const unsigned int index,IntSize &size) const;
	int get_item_rect(const unsigned int index,IntRect &rect) const;
	int set_item_window(const unsigned int index,CWnd *window,const unsigned int stretch_factor);
	virtual int set_item_fixed_window(const unsigned int index,CWnd *window,const unsigned int fixed_size)=0;
//derived
protected:
	ItemVector _items;
	UintRect *_margin;
	IntRect *_rect;
//restrict
private:
	MtLayout(const MtLayout &);
	MtLayout &operator=(const MtLayout &);
};