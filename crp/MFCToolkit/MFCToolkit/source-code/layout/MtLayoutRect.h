#pragma once

//#include"../Symbol"

/**
 * name: MtLayoutRect
 * brief: ���־����࣬�����װһ�����ε�������Ϣ��
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
 * brief: ���캯����
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
 * brief: ���캯����
 * param: left - �����ꡣ
 *        top - �������ꡣ
 *        right - �����ꡣ
 *        bottom - �ײ����ꡣ
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
 * brief: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutRect<_Tp>::~MtLayoutRect(){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�Ƿ�Ϊ��Ч���Ρ�
 * param: --
 * return: �����ǰ����Ϊ��Ч�����򷵻�TRUE�����򷵻�FALSE��
 */
template<typename _Tp>
BOOL MtLayoutRect<_Tp>::is_valid() const{
	//1.�����ǰ���������������Ҳ�����򶥲�������ڵײ����꣬����Ϊ���δ���
	if((_left>_right)||(_top>_bottom)){
		return(FALSE);
	}
	//2.�������������ֱ�ӷ���TRUE��
	else{
		return(TRUE);
	}
}

/**
 * name: set_rect
 * brief: ���þ��Ρ�
 * param: left - �����ꡣ
 *        top - �������ꡣ
 *        right - �����ꡣ
 *        bottom - �ײ����ꡣ
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
 * brief: ���������ꡣ
 * param: left - �����ꡣ 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_left(const _Tp left){
	_left=left;
}

/**
 * name: get_left
 * brief: ��ȡ��������Ϣ��
 * param: --
 * return: ������������Ϣ��
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_left() const{
	return(_left);
}

/**
 * name: set_top
 * brief: ���ö������ꡣ
 * param: top - �������ꡣ 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_top(const _Tp top){
	_top=top;
}

/**
 * name: get_top
 * brief: ��ȡ����������Ϣ��
 * param: --
 * return: ���ض���������Ϣ��
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_top() const{
	return(_top);
}

/**
 * name: set_right
 * brief: ���������ꡣ
 * param: right - �����ꡣ 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_right(const _Tp right){
	_right=right;
}

/**
 * name: get_right
 * brief: ��ȡ��������Ϣ��
 * param: --
 * return: ������������Ϣ��
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_right() const{
	return(_right);
}

/**
 * name: set_bottom
 * brief: ���õײ����ꡣ
 * param: bottom - �ײ����ꡣ 
 * return: --
 */
template<typename _Tp>
void MtLayoutRect<_Tp>::set_bottom(const _Tp bottom){
	_bottom=bottom;
}

/**
 * name: get_bottom
 * brief: ��ȡ�ײ�������Ϣ��
 * param: --
 * return: ���صײ�������Ϣ��
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_bottom() const{
	return(_bottom);
}

/**
 * name:  get_width
 * brief: ��ȡ��ǰ��ȡ�
 * param: --
 * return: ���ص�ǰ��ȡ�
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
 * brief: ��ȡ��ǰ�߶ȡ�
 * param: --
 * return: ���ص�ǰ�߶ȡ�
 */
template<typename _Tp>
_Tp MtLayoutRect<_Tp>::get_height() const{
	if(!is_valid()){
		return(0);
	}else{
		return(_bottom-_top);
	}
}