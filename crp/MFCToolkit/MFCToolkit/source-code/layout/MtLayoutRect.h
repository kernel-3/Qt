#pragma once

//#include"../Symbol"

/**
 * name: MtLayoutRect
 * brief: 布局矩形类，负责封装一个矩形的坐标信息。
 * author: yameng_he
 * date: 2014-11-12
 */
template<typename _Tp>
class /*MFC_TOOLKIT_API*/ MtLayoutRect{
//constructor & destructor
public:
	MtLayoutRect();
	MtLayoutRect(const _Tp left,const _Tp top,
		const _Tp right,const _Tp bottom);
	~MtLayoutRect();
//interface
public:
	BOOL is_valid() const;
	void set_rect(const _Tp left,const _Tp top,
		const _Tp right,const _Tp bottom);
	void set_left(const _Tp left);
	_Tp get_left() const;
	void set_top(const _Tp top);
	_Tp get_top() const;
	void set_right(const _Tp right);
	_Tp get_right() const;
	void set_bottom(const _Tp bottom);
	_Tp get_bottom() const;
	_Tp get_width() const;
	_Tp get_height() const;
//variables
private:
	_Tp _left;
	_Tp _top;
	_Tp _right;
	_Tp _bottom;
};

/**
 * name: MtLayoutRect
 * brief: 构造函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutRect<_Tp>::MtLayoutRect()
	:_left(0)
	,_top(0)
	,_right(0)
	,_bottom(0){
}

/**
 * name: MtLayoutRect
 * brief: 构造函数。
 * param: left - 左坐标。
 *        top - 顶部坐标。
 *        right - 右坐标。
 *        bottom - 底部坐标。
 * return: --
 */
template<typename _Tp>
MtLayoutRect<_Tp>::MtLayoutRect(
	const _Tp left,const _Tp top,
	const _Tp right,const _Tp bottom)
	:_left(left)
	,_top(top)
	,_right(right)
	,_bottom(bottom){
}

/**
 * name: MtLayoutRect
 * brief: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutRect<_Tp>::~MtLayoutRect(){
}

/**
 * name: is_valid
 * brief: 判断当前是否为有效矩形。
 * param: --
 * return: 如果当前矩形为有效矩形则返回TRUE，否则返回FALSE。
 */
template<typename _Tp>
BOOL MtLayoutRect<_Tp>::is_valid() const{
	//1.如果当前矩形左侧坐标大于右侧坐标或顶部坐标大于底部坐标，则认为矩形错误。
	if((_left>_right)||(_top>_bottom)){
		return(FALSE);
	}
	//2.如果矩形无误，则直接返回TRUE。
	else{
		return(TRUE);
	}
}

/**
 * name: set_rect
 * brief: 设置矩形。
 * param: left - 左坐标。
 *        top - 顶部坐标。
 *        right - 右坐标。
 *        bottom - 底部坐标。
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_rect(const _Tp left,const _Tp top,
	const _Tp right,const _Tp bottom){
	_left=left;
	_top=top;
	_right=right;
	_bottom=bottom;
}

/**
 * name: set_left
 * brief: 设置左坐标。
 * param: left - 左坐标。 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_left(const _Tp left){
	_left=left;
}

/**
 * name: get_left
 * brief: 获取左坐标信息。
 * param: --
 * return: 返回左坐标信息。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_left() const{
	return(_left);
}

/**
 * name: set_top
 * brief: 设置顶部坐标。
 * param: top - 顶部坐标。 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_top(const _Tp top){
	_top=top;
}

/**
 * name: get_top
 * brief: 获取顶部坐标信息。
 * param: --
 * return: 返回顶部坐标信息。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_top() const{
	return(_top);
}

/**
 * name: set_right
 * brief: 设置右坐标。
 * param: right - 右坐标。 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_right(const _Tp right){
	_right=right;
}

/**
 * name: get_right
 * brief: 获取右坐标信息。
 * param: --
 * return: 返回右坐标信息。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_right() const{
	return(_right);
}

/**
 * name: set_bottom
 * brief: 设置底部坐标。
 * param: bottom - 底部坐标。 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_bottom(const _Tp bottom){
	_bottom=bottom;
}

/**
 * name: get_bottom
 * brief: 获取底部坐标信息。
 * param: --
 * return: 返回底部坐标信息。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_bottom() const{
	return(_bottom);
}

/**
 * name:  get_width
 * brief: 获取当前宽度。
 * param: --
 * return: 返回当前宽度。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_width() const{
	if(!is_valid()){
		return(0);
	}else{
		return(_right-_left);
	}
}

/**
 * name: get_height
 * brief: 获取当前高度。
 * param: --
 * return: 返回当前高度。
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_height() const{
	if(!is_valid()){
		return(0);
	}else{
		return(_bottom-_top);
	}
}