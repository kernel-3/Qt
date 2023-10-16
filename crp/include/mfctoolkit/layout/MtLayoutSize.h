#pragma once

//#include"../Symbol"

/**
 * name: MtLayoutSize
 * brief: 布局尺寸，负责维护布局的尺寸信息。
 * author: yameng_he
 * date: 2014-11-15
 */
template<typename _Tp>
class /*MFC_TOOLKIT_API*/ MtLayoutSize{
//constructor & destructor
public:
	MtLayoutSize();
	MtLayoutSize(const _Tp width,const _Tp height);
	~MtLayoutSize();
//interface
public:
	void set_size(const _Tp width,const _Tp _height);
	_Tp get_width() const;
	_Tp get_height() const;
//variables
private:
	_Tp _width;
	_Tp _height;
};

/**
 * name: MtLayoutSize
 * brief: 构造函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutSize<_Tp>::MtLayoutSize()
	:_width(0)
	,_height(0){
}

/**
 * name: MtLayoutSize
 * brief: 构造函数。
 * param: width - 宽度。
 *            height - 高度。
 * return: --
 */
template<typename _Tp>
MtLayoutSize<_Tp>::MtLayoutSize(const _Tp width,const _Tp height)
	:_width(width)
	,_height(height){
}

/**
 * name: ~MtLayoutSize
 * brief: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutSize<_Tp>::~MtLayoutSize(){
}

/**
 * name: set_size
 * brief: 设置宽度。
 * param: width - 宽度。
 *        height - 高度。
 * return: --
 */
template<typename _Tp>
void MtLayoutSize<_Tp>::set_size(const _Tp width,const _Tp height){
	_width=width;
	_height=height;
}

/**
 * name: get_width
 * brief: 获取宽度。
 * param: --
 * return: 返回宽度。
 */
template<typename _Tp>
_Tp MtLayoutSize<_Tp>::get_width() const{
	return(_width);
}

/**
 * name: get_height
 * brief: 获取高度。
 * param: --
 * return: 返回高度。
 */
template<typename _Tp>
_Tp MtLayoutSize<_Tp>::get_height() const{
	return(_height);
}