#include"stdafx.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutSpacingItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutSpacingItem::MtLayoutSpacingItem(void)
	:MtLayoutItem()
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutSpacingItem
 * brief: ���캯����
 * param: orientation - ����
 *        fixed_size - �̶��ߴ硣
 * return: --
 */
MtLayoutSpacingItem::MtLayoutSpacingItem(
	const Orientation orientation,const unsigned int fixed_size)
	:MtLayoutItem()
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: ~MtLayoutSpacingItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutSpacingItem::~MtLayoutSpacingItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��ʵ�������Ƿ���Ч��
 * param: --
 * return: �����ǰʵ��������Ч����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
BOOL MtLayoutSpacingItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(ORIENTATION_UNKNOWN!=_orientation)&&(0!=_fixed_size));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ������а����Ĵ���������
 * param: --
 * return: ���ص�ǰ������а����Ĵ���������
 */
unsigned int MtLayoutSpacingItem::get_window_amount() const{
	return(0);
}

/**
 * name: get_stretch_factor
 * brief: ��ȡ����ϵ����
 * param: --
 * return: ��������ϵ����
 */
unsigned int MtLayoutSpacingItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ�����Ĺ̶��ߴ硣
 * param: --
 * return: ���ؼ����Ĺ̶��ߴ硣
 */
unsigned int MtLayoutSpacingItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: ���µ���������ĳߴ硣
 * param: hdwp - �ര�ڵ����ߴ��ڴ�����
 *        rect - �������³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayoutSpacingItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ϸ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.���㵱ǰ�������³ߴ硣
	//2-1.������ǰ�������������
	IntRect rect_t(rect);
	//2-2.�����ǰ������Ϊˮƽ����
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(
			get_fixed_size()));
	}
	//2-3.�����ǰ������Ϊ��ֱ����
	else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(
			get_fixed_size()));
	}
	//2-4.�����ǰ������δ֪��
	else{
		return(-2);
	}
	//2-5.�����ǰ������³ߴ粻�Ϸ�����ֱ�ӷ��ش���
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.���û�����Ӧ�����������жϵ����Ƿ�ɹ���������ຯ��ֻ���ڼ�������Ƿ�Ϸ�����
	const int result=MtLayoutItem::resize(hdwp,rect_t);
	if(result<0){
		return(-4);
	}
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_orientation
 * brief: ���ü������
 * param: orientation - ���ü������
 * return: --
 */
void MtLayoutSpacingItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: ��ȡ�������
 * param: --
 * return: ���ؼ������
 */
MtLayoutSpacingItem::Orientation MtLayoutSpacingItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: ���ù̶��ߴ磨��λ�����أ���
 * param: fixed_size - ����Ĺ̶��ߴ磨��λ�����أ���
 * return: --
 */
void MtLayoutSpacingItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}