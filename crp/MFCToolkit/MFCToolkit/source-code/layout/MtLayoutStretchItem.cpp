#include"stdafx.h"
#include"MtLayoutStretchItem.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutStretchItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutStretchItem::MtLayoutStretchItem(void)
	:MtLayoutItem()
	,_stretch_factor(0){
}

/**
 * name: MtLayoutStretchItem
 * brief: ���캯����
 * param: stretch_factor - ����ϵ����
 * return: --
 */
MtLayoutStretchItem::MtLayoutStretchItem(const unsigned int stretch_factor)
	:MtLayoutItem()
	,_stretch_factor(stretch_factor){
}

/**
 * name: ~MtLayoutStretchItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutStretchItem::~MtLayoutStretchItem(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��ʵ�������Ƿ���Ч��
 * param: --
 * return: �����ǰʵ��������Ч����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
BOOL MtLayoutStretchItem::is_valid() const{
	return((MtLayoutItem::is_valid())&&(_stretch_factor>0));
}

/**
 * name: get_window_amount
 * brief: ��ȡ��ǰ������а����Ĵ���������
 * param: --
 * return: ���ص�ǰ������а����Ĵ���������
 */
unsigned int MtLayoutStretchItem::get_window_amount() const{
	return(0);
}

/**
 * name: get_stretch_factor
 * brief: ��ȡ����ϵ����
 * param: --
 * return: ��������ϵ����
 */
unsigned int MtLayoutStretchItem::get_stretch_factor() const{
	return(_stretch_factor);
}

/**
 * name: get_fixed_size
 * brief: ��ȡ��ǰ����������Ĺ̶��ߴ硣
 * param: --
 * return: ���ص�ǰ����������Ĺ̶��ߴ硣
 */
unsigned int MtLayoutStretchItem::get_fixed_size() const{
	return(0);
}

/**
 * name: resize
 * brief: ���µ���������ߴ硣
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - �������³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayoutStretchItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ������Ƿ�����ֱ�ӷ��ش���
	if(!is_valid()){
		return(-1);
	}
	//2.���û�����Ӧ������������¼��ǰ��������³ߴ硣
	if(MtLayoutItem::resize(hdwp,rect)<0){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_stretch_factor
 * brief: ��������ϵ����
 * param: stretch_factor - ����ϵ����
 * return: --
 */
void MtLayoutStretchItem::set_stretch_factor(const unsigned int stretch_factor){
	_stretch_factor=stretch_factor;
}