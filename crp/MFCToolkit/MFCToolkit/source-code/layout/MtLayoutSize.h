#pragma once

//#include"../Symbol"

/**
 * name: MtLayoutSize
 * brief: ���ֳߴ磬����ά�����ֵĳߴ���Ϣ��
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
 * brief: ���캯����
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
 * brief: ���캯����
 * param: width - ��ȡ�
 *            height - �߶ȡ�
 * return: --
 */
template<typename _Tp>
MtLayoutSize<_Tp>::MtLayoutSize(const _Tp width,const _Tp height)
	:_width(width)
	,_height(height){
}

/**
 * name: ~MtLayoutSize
 * brief: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtLayoutSize<_Tp>::~MtLayoutSize(){
}

/**
 * name: set_size
 * brief: ���ÿ�ȡ�
 * param: width - ��ȡ�
 *        height - �߶ȡ�
 * return: --
 */
template<typename _Tp>
void MtLayoutSize<_Tp>::set_size(const _Tp width,const _Tp height){
	_width=width;
	_height=height;
}

/**
 * name: get_width
 * brief: ��ȡ��ȡ�
 * param: --
 * return: ���ؿ�ȡ�
 */
template<typename _Tp>
_Tp MtLayoutSize<_Tp>::get_width() const{
	return(_width);
}

/**
 * name: get_height
 * brief: ��ȡ�߶ȡ�
 * param: --
 * return: ���ظ߶ȡ�
 */
template<typename _Tp>
_Tp MtLayoutSize<_Tp>::get_height() const{
	return(_height);
}