#include"stdafx.h"
#include"MtLayoutItem.h"
#include"MtLayout.h"
#include"MtLayoutRect.h"

/**
 * name: MtLayoutItem
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayoutItem::MtLayoutItem(void)
	:_rect(new IntRect(-1,-1,-1,-1)){
}

/**
 * name: MtLayoutItem
 * brief: ���캯����
 * param: rect - ������ߴ硣
 * return: --
 */
MtLayoutItem::MtLayoutItem(const IntRect &rect)
	:_rect(new IntRect(rect)){
}

/**
 * name: ~MtLayoutItem
 * brief: ����������
 * param: --
 * return: --
 */
MtLayoutItem::~MtLayoutItem(void){
	delete _rect;
}

/**
 * name: is_valid
 * brief: �Ƿ�Ϊ��Ч�Ĳ����
 * param: --
 * return: �������ִ�гɹ�����ֵΪTRUE�����򷵻�ֵΪFALSE��
 */
BOOL MtLayoutItem::is_valid() const{
	return(_rect->is_valid());
}

/**
 * name: resize
 * brief: ���µ���������ߴ硣
 * param: hdwp - ���ڳߴ�����ڴ�����
 *        rect - �²��ֳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayoutItem::resize(HDWP &hdwp,const IntRect &rect){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if(0==hdwp){
		return(-1);
	}
	if(!rect.is_valid()){
		return(-2);
	}
	//2.��¼��ǰ������ĳߴ硣
	*_rect=rect;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_width
 * brief: ��ȡ��ǰ�������ȡ�
 * param: --
 * return: ���ص�ǰ�������ȡ�
 */
int MtLayoutItem::get_width() const{
	return(_rect->get_width());
}

/**
 * name: get_height
 * brief: ��ȡ��ǰ������߶ȡ�
 * param: --
 * return: ���ص�ǰ������߶ȡ�
 */
int MtLayoutItem::get_height() const{
	return(_rect->get_height());
}

/**
 * name: get_rect
 * brief: ��ȡ��ǰ������ĳߴ硣
 * param: --
 * return: ���ص�ǰ������ĳߴ硣
 */
const MtLayoutItem::IntRect &MtLayoutItem::get_rect() const{
	return(*_rect);
}