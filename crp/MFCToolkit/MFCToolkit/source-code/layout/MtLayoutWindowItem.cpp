#include"stdafx.h"
#include"MtLayoutWindowItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutWindowItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(void)
	:MtLayoutItem()
	,_window(0)
	,_stretch_factor(0){
}

/**
 * name: MtLayoutWindowItem
 * brief: ���캯����
 * param: window - ָ�򴰿ڡ�
 *        stretch_factor - ����ϵ����
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(CWnd *window,const unsigned int stretch_factor)
	:MtLayoutItem()
	,_window(window)
	,_stretch_factor(stretch_factor){
}

/**
 * name: MtLayoutWindowItem
 * brief: ���캯����
 * param: rect - ������ߴ硣
 *        window - ָ�򴰿ڡ�
 *        stretch_factor - ����ϵ����
 * return: --
 */
MtLayoutWindowItem::MtLayoutWindowItem(const IntRect &rect,CWnd *window,const unsigned int stretch_factor)
	:MtLayoutItem(rect)
	,_window(window)
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutWindowItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutWindowItem::~MtLayoutWindowItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��ʵ�������Ƿ���Ч��
 * param: --
 * return: �����ǰʵ��������Ч����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
BOOL MtLayoutWindowItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(_stretch_factor>0)&&
		(0!=_window)&&(0!=_window->GetSafeHwnd())&&
		(INVALID_HANDLE_VALUE!=_window->GetSafeHwnd())&&
		(IsWindow(_window->GetSafeHwnd())));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ������а����Ĵ���������
 * param: --
 * return: ���ص�ǰ������а����Ĵ���������
 */
unsigned int MtLayoutWindowItem::get_window_amount() const{
	if(is_valid()){
		return(1);
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: ��ȡ����ϵ����
 * param: --
 * return: ��������ϵ����
 */
unsigned int MtLayoutWindowItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ��ǰ���ڲ�����Ĺ̶��ߴ硣
 * param: --
 * return: ���ص�ǰ���ڲ�����Ĺ̶��ߴ硣
 */
unsigned int MtLayoutWindowItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: ���µ���������ߴ硣
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - �������³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayoutWindowItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ϊ�Ƿ�����ֱ�ӷ��ء�
	if(!is_valid()){
		return(-1);
	}
	//2.���㵱ǰ������ڵ�����ǡ�
	unsigned int flag=SWP_NOZORDER|SWP_NOACTIVATE|
		SWP_NOOWNERZORDER;
	if((_rect->get_left()==rect.get_left())&&
		(_rect->get_top()==rect.get_top())){
		flag|=SWP_NOMOVE;
	}
	if((_rect->get_width()==rect.get_width())&&
		(_rect->get_height()==rect.get_height())){
		flag|=SWP_NOSIZE;
	}else{
		flag|=SWP_NOCOPYBITS;
	}
	//3.���û�����Ӧ���������浱ǰ��������³ߴ磬�����жϱ����Ƿ�ɹ���
	const int result=MtLayoutItem::resize(hdwp,rect);
	if(result<0){
		return(-2);
	}
	//4.����API������������ǰ�������д��ڳߴ硣
	hdwp=DeferWindowPos(hdwp,_window->GetSafeHwnd(),0,_rect->get_left(),
		_rect->get_top(),_rect->get_width(),_rect->get_height(),flag);
	if(0==hdwp){
		return(-3);
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_window
 * brief: ���ô��ڡ�
 * param: window - ָ�򴰿ڡ�
 * return: --
 */
void MtLayoutWindowItem::set_window(CWnd *window){
	_window=window;
}

/**
 * name: get_window
 * brief: ��ȡ���ڡ�
 * param: --
 * return: ���ش��ڡ�
 */
CWnd *MtLayoutWindowItem::get_window(){
	return(_window);
}

/**
 * name: get_window
 * brief: ��ȡ���ڡ�
 * param: --
 * return: ���ش��ڡ�
 */
const CWnd *MtLayoutWindowItem::get_window() const{
	return(const_cast<MtLayoutWindowItem*>(this)->get_window());
}

/**
 * name: set_stretch_factor
 * brief: ��������ϵ����
 * param: stretch_factor - ����ϵ����
 * return: --
 */
void MtLayoutWindowItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}