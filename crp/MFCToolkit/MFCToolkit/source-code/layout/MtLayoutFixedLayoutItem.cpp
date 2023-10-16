#include"stdafx.h"
#include"MtLayoutFixedLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutFixedLayoutItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutFixedLayoutItem::MtLayoutFixedLayoutItem(void)
	:MtLayoutItem()
	,_layout(0)
	,_orientation(ORIENTATION_UNKNOWN)
	,_fixed_size(0){
}

/**
 * name: MtLayoutFixedLayoutItem
 * brief: ���캯����
 * param: layout - ����ָ�롣
 *        orientation - �̶����ֵĲ������
 *        fixed_size - �̶����ֵĲ�����̶��ߴ硣
 * return: --
 */
MtLayoutFixedLayoutItem::MtLayoutFixedLayoutItem(MtLayout *layout,
	const Orientation orientation,const unsigned int fixed_size)
	:_layout(layout)
	,_orientation(orientation)
	,_fixed_size(fixed_size){
}

/**
 * name: MtLayoutFixedLayoutItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutFixedLayoutItem::~MtLayoutFixedLayoutItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�̶����ֵĲ������Ƿ���Ч��
 * param: --
 * return: �����ǰ�̶����ֵĲ�������Ч�򷵻�TRUE�����򷵻�FALSE��
 */
BOOL MtLayoutFixedLayoutItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(ORIENTATION_UNKNOWN!=_orientation)&&
		(0!=_fixed_size)&&(0!=_layout));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ�̶����ֵĲ������а������ڵ�������
 * param: --
 * return: ���ص�ǰ�̶����ֵĲ������а������ڵ�������
 */
unsigned int MtLayoutFixedLayoutItem::get_window_amount() const{
	if(is_valid()){
		return(_layout->get_window_amount());
	}else{
		return(0);
	}
}

/**
 * name: get_stretch_factor
 * brief: ��ȡ��ǰ�̶����ֵĲ����������ϵ����
 * param: --
 * return: ���ص�ǰ�̶����ֵĲ����������ϵ����
 */
unsigned int MtLayoutFixedLayoutItem::get_stretch_factor() const{
	return(0);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ��ǰ�̶����ֵĲ�����Ĺ̶��ߴ硣
 * param: --
 * return: ���ص�ǰ�̶����ֵĲ�����Ĺ̶��ߴ硣
 */
unsigned int MtLayoutFixedLayoutItem::get_fixed_size() const{
	return(_fixed_size);
}

/**
 * name: resize
 * brief: ���µ�����ǰ�̶����ֵĲ�����Ĺ̶��ߴ硣
 * param: hdwp - �����ര�ڳߴ�ʱ�ڴ�����
 *        rect - �����³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayoutFixedLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ϸ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.���ݵ�ǰ�̶����ֵĲ�����򣬼��㲼�ֵ������ʵ�ʳߴ硣
	//2-1.������ǰ�������������
	IntRect rect_t(rect);
	//2-2.���ݵ�ǰ�̶����ֵĲ�����ķ��򣬼���ʵ�ʵĲ�����ߴ硣
	if(ORIENTATION_HORIZON==_orientation){
		rect_t.set_right(rect_t.get_left()+static_cast<int>(_fixed_size));
	}else if(ORIENTATION_VERTICAL==_orientation){
		rect_t.set_bottom(rect_t.get_top()+static_cast<int>(_fixed_size));
	}else{
		return(-2);
	}
	//2-3.�������Ĳ��ֳߴ粻�Ϸ�����ֱ�ӷ��ش���
	if(!rect_t.is_valid()){
		return(-3);
	}
	//3.���ü�¼��ǰ�³ߴ磬�����ж��Ƿ�ɹ���
	if(MtLayoutItem::resize(hdwp,rect_t)<0){
		return(-4);
	}
	//4.������ǰ���ֳߴ磬�����ж��Ƿ�ɹ���
	if(_layout->resize(hdwp,rect_t)<0){
		return(-5);
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_layout
 * brief: ���ò��֡�
 * param: layout - ָ�򲼾֡�
 * return: --
 */
void MtLayoutFixedLayoutItem::set_layout(MtLayout *layout){
	_layout=layout;
}

/**
 * name: get_layout
 * brief: ��ȡ���֡�
 * param: --
 * return: ���ز��֡�
 */
MtLayout *MtLayoutFixedLayoutItem::get_layout(){
	return(_layout);
}

/**
 * name: get_layout
 * brief: ��ȡ���֡�
 * param: --
 * return: ���ز��֡�
 */
const MtLayout *MtLayoutFixedLayoutItem::get_layout() const{
	return(const_cast<MtLayoutFixedLayoutItem*>(this)->get_layout());
}

/**
 * name: set_orientation
 * brief: ���ù̶����ڲ��ַ���
 * param: orientation - ���ù̶����ڲ��ַ���
 * return: --
 */
void MtLayoutFixedLayoutItem::set_orientation(const Orientation orientation){
	_orientation=orientation;
}

/**
 * name: get_orientation
 * brief: ��ȡ�̶����ڲ��ַ���
 * param: --
 * return: ���ع̶����ڲ��ַ���
 */
MtLayoutFixedLayoutItem::Orientation MtLayoutFixedLayoutItem::get_orientation() const{
	return(_orientation);
}

/**
 * name: set_fixed_size
 * brief: ���ù̶����ڲ��ֵĹ̶��ߴ磨��λ�����أ���
 * param: fixed_size - �̶����ڲ��ֵĹ̶��ߴ磨��λ�����أ���
 * return: --
 */
void MtLayoutFixedLayoutItem::set_fixed_size(const unsigned int fixed_size){
	_fixed_size=fixed_size;
}