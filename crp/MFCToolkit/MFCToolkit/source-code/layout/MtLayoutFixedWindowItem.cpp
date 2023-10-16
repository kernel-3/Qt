#include"stdafx.h"
#include"MtLayoutFixedWindowItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutFixedWindowItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(void)
	:MtLayoutItem()
	,_window(0)
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutFixedWindowItem
 * brief: ���캯����
 * param: window - ָ��һ�����ڡ�
 *        orientation - ��ǰ�������
 *        fixed_size - ��ǰ������̶��ߴ硣
 * return:
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(CWnd *window,
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem()
	,_window(window)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: MtLayoutFixedWindowItem
 * brief: ���캯����
 * param: rect - ������ߴ硣
 *        window - ָ��һ�����ڡ�
 *        orientation - ��ǰ�������
 *        fixed_size - ��ǰ������̶��ߴ硣
 * return:
 */
MtLayoutFixedWindowItem::MtLayoutFixedWindowItem(const IntRect &rect,CWnd *window,
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem(rect)
	,_window(window)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: ~MtLayoutFixedWindowItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutFixedWindowItem::~MtLayoutFixedWindowItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�̶����ڲ������Ƿ���Ч��
 * param: --
 * return: �����ǰ���ڲ�������Ч����TRUE�����򷵻�FALSE��
 */
BOOL MtLayoutFixedWindowItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(0!=_window)&&
		(0!=_window->GetSafeHwnd())&&
		(INVALID_HANDLE_VALUE!=_window->GetSafeHwnd())&&
		(IsWindow(_window->GetSafeHwnd()))&&
		(ORIENTATION_UNKNOWN!=_orientation)&&(_fixed_size!=0));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ�̶����ڲ������д���������
 * param: --
 * return: ���ص�ǰ�̶����ڲ������д���������
 */
unsigned int MtLayoutFixedWindowItem::get_window_amount() const{
	if(is_valid()){
		return(1);
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: ��ȡ��ǰ�̶����ڲ����������ϵ����
 * param: --
 * return: ���ص�ǰ�̶����ڲ����������ϵ����
 */
unsigned int MtLayoutFixedWindowItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ��ǰ���ڲ�����Ĺ̶��ߴ硣
 * param: --
 * return: ���ص�ǰ���ڲ�����Ĺ̶��ߴ硣
 */
unsigned int MtLayoutFixedWindowItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: ���µ����̶����ڲ�����ĳߴ硣
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - �������³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬����С���㡣
 */
int MtLayoutFixedWindowItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ϊ�Ƿ�����ֱ�ӷ��ء�
	if(!is_valid()){
		return(-1);
	}
	//2.���ݵ�ǰ�̶����ڲ�����ķ������µ����̶����ڲ�����ĳߴ硣
	//2-1.������ǰ�������������
	IntRect rect_t(rect);
	//2-2.���µ�����ǰ�̶����ڲ�����ĳߴ硣
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(_fixed_size));
	}else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(_fixed_size));
	}else{
		return(-2);
	}
	//2-3.�����ǰ����ĳߴ粻�Ϸ�����ֱ�ӷ��ش���
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.���㵱ǰ������ڵ�����ǡ�
	unsigned int flag=SWP_NOZORDER|SWP_NOACTIVATE|
		SWP_NOOWNERZORDER;
	if((_rect->get_left()==rect_t.get_left())&&
		(_rect->get_top()==rect_t.get_top())){
		flag|=SWP_NOMOVE;
	}
	if((_rect->get_width()==rect_t.get_width())&&
		(_rect->get_height()==rect_t.get_height())){
		flag|=SWP_NOSIZE;
	}else{
		flag|=SWP_NOCOPYBITS;
	}
	//4.���û�����Ӧ���������浱ǰ��������³ߴ磬�����жϱ����Ƿ�ɹ���
	const int result=MtLayoutItem::resize(hdwp,rect_t);
	if(result<0){
		return(-4);
	}
	//5.����API������������ǰ�������д��ڳߴ硣
	hdwp=DeferWindowPos(hdwp,_window->GetSafeHwnd(),0,_rect->get_left(),
		_rect->get_top(),_rect->get_width(),_rect->get_height(),flag);
	if(0==hdwp){
		return(-5);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_window
 * brief: ���ô��ڡ�
 * param: window - ָ�򴰿ڡ�
 * return: --
 */
void MtLayoutFixedWindowItem::set_window(CWnd *window){
	_window=window;
}

/**
 * name: get_window
 * brief: ��ȡ���ڡ�
 * param: --
 * return: ���ش��ڡ�
 */
CWnd *MtLayoutFixedWindowItem::get_window(){
	return(_window);
}

/**
 * name: get_window
 * brief: ��ȡ���ڡ�
 * param: --
 * return: ���ش��ڡ�
 */
const CWnd *MtLayoutFixedWindowItem::get_window() const{
	return(const_cast<MtLayoutFixedWindowItem*>(this)->get_window());
}

/**
 * name: set_orientation
 * brief: ���ù̶����ڲ��ַ���
 * param: orientation - ���ù̶����ڲ��ַ���
 * return: --
 */
void MtLayoutFixedWindowItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: ��ȡ�̶����ڲ��ַ���
 * param: --
 * return: ���ع̶����ڲ��ַ���
 */
MtLayoutFixedWindowItem::Orientation MtLayoutFixedWindowItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: ���ù̶����ڲ��ֵĹ̶��ߴ磨��λ�����أ���
 * param: fixed_size - �̶����ڲ��ֵĹ̶��ߴ磨��λ�����أ���
 * return: --
 */
void MtLayoutFixedWindowItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}