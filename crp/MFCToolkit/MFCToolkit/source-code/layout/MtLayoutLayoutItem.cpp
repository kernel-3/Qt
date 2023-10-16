#include"stdafx.h"
#include"MtLayoutLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutLayoutItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutLayoutItem::MtLayoutLayoutItem(void)
	:MtLayoutItem()
	,_layout(0)
	,_stretch_factor(0){
}

/**
 * name: MtLayoutLayoutItem
 * brief: ���캯����
 * param: layout - ָ�򲼾֡�
 *        stretch_factor - ����ϵ����
 * return: --
 */
MtLayoutLayoutItem::MtLayoutLayoutItem(MtLayout *layout,const unsigned int stretch_factor)
	:MtLayoutItem()
	,_layout(layout)
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutLayoutItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutLayoutItem::~MtLayoutLayoutItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��ʵ�������Ƿ���Ч��
 * param: --
 * return: �����ǰʵ��������Ч����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
BOOL MtLayoutLayoutItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&
		(_stretch_factor>0)&&(0!=_layout));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ������а����Ĵ���������
 * param: --
 * return: ���ص�ǰ������а����Ĵ���������
 */
unsigned int MtLayoutLayoutItem::get_window_amount() const{
	if(is_valid()){
		return(_layout->get_window_amount());
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
unsigned int MtLayoutLayoutItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ������̶��ߴ硣
 * param: --
 * return: ���ز�����̶��ߴ硣
 */
unsigned int MtLayoutLayoutItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: ���µ���������ߴ硣 
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - �������³ߴ硣
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵС���㡣
 */
int MtLayoutLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ϸ���ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.���ü�¼��ǰ�³ߴ磬�����ж��Ƿ�ɹ���
	if(MtLayoutItem::resize(hdwp,rect)<0){
		return(-2);
	}
	//3.������ǰ���ֳߴ磬�����ж��Ƿ�ɹ���
	if(_layout->resize(hdwp,rect)<0){
		return(-3);
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_layout
 * brief: ���ò��֡�
 * param: layout - ָ�򲼾֡�
 * return: --
 */
void MtLayoutLayoutItem::set_layout(MtLayout *layout){
	_layout=layout;
}

/**
 * name: get_layout
 * brief: ��ȡ���֡�
 * param: --
 * return: ���ز��֡�
 */
MtLayout *MtLayoutLayoutItem::get_layout(){
	return(_layout);
}

/**
 * name: get_layout
 * brief: ��ȡ���֡�
 * param: --
 * return: ���ز��֡�
 */
const MtLayout *MtLayoutLayoutItem::get_layout() const{
	return(const_cast<MtLayoutLayoutItem*>(this)->get_layout());
}

/**
 * name: set_stretch_factor
 * brief: ��������ϵ����
 * param: stretch_factor - ����ϵ����
 * return: --
 */
void MtLayoutLayoutItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}