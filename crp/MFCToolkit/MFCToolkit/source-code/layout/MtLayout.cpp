#include"stdafx.h"
#include"MtLayout.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutStretchItem.h"
#include"MtLayoutLayoutItem.h"
#include"MtLayoutWindowItem.h"
#include"MtLayoutRect.h"
#include"MtLayoutSize.h"

/**
 * name: MtLayout
 * brief: ���캯����
 * param: --
 * return: --
 */
MtLayout::MtLayout(void)
	:_items()
	,_margin(new UintRect)
	,_rect(new IntRect){
}

/**
 * name: ~MtLayout
 * brief: ����������
 * param: --
 * return: --
 */
MtLayout::~MtLayout(void){
	delete _margin;
	delete _rect;
}

/**
 * name: resize
 * brief: ���µ�����ǰ���ֳߴ硣
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - ��ǰ�����³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::resize(HDWP &hdwp,const IntRect &rect){
	//1.�����ǰ�������Ϸ���ֱ�ӷ��ش���
	if(0==hdwp){
		return(-1);
	}
	if(!rect.is_valid()){
		return(-2);
	}
	//2.��¼��ǰ�����³ߴ硣
	*_rect=rect;
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: resize
 * brief: ���õ�ǰ���ֳߴ硣
 * param: width - ��ȡ�
 *        height - �߶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::resize(const unsigned int width,const unsigned int height){
	_rect->set_rect(0,0,static_cast<int>(width),static_cast<int>(height));
	return(0);
}

/**
 * name: add_stretch
 * brief: ��ǰ������׷��һ�������
 * param: stretch_factor - ����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::add_stretch(const unsigned int stretch_factor){
	//1.����һ�������
	PtrToItem item(new MtLayoutStretchItem(stretch_factor));
	//2.�������ʧ�ܣ����ش�����롣
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.�����������Ч���򷵻ش�����롣
	if(!item->is_valid()){
		return(-2);
	}
	//4.����ǰ���������洢�����С�
	_items.push_back(item);
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: add_layout
 * brief: ��ǰ������׷��һ�����֡�
 * param: layout - ָ�򲼾֡�
 *        stretch_factor - ����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::add_layout(MtLayout *layout,const unsigned int stretch_factor){
	//1.����һ�������
	PtrToItem item(new MtLayoutLayoutItem(layout,stretch_factor));
	//2.�������ʧ�ܣ����ش�����롣
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.�����������Ч���򷵻ش�����롣
	if(!item->is_valid()){
		return(-2);
	}
	//4.����ǰ���������洢�����С�
	_items.push_back(item);
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: add_layout
 * brief: ��ǰ������׷��һ�����ڡ�
 * param: window - ָ�򴰿ڡ�
 *        stretch_factor - ����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::add_window(CWnd *window,const unsigned int stretch_factor){
	//1.����һ�������
	PtrToItem item(new MtLayoutWindowItem(window,stretch_factor));
	//2.�������ʧ�ܣ����ش�����롣
	if(!static_cast<bool>(item)){
		return(-1);
	}
	//3.�����������Ч���򷵻ش�����롣
	if(!item->is_valid()){
		return(-2);
	}
	//4.����ǰ���������洢�����С�
	_items.push_back(item);
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_margin
 * brief: ���ò������ס�
 * param: margin - ���׳ߴ硣
 * return: --
 */
void MtLayout::set_margin(const UintRect &margin){
	(*_margin)=margin;
}

/**
 * name: set_margin
 * brief: ���ò������ס�
 * param: left_margin - ������ס�
 *        top_margin - �������ס�
 *        right_margin - �Ҳ����ס�
 *        bottom_margin - �ײ����ס�
 * return: --
 */
void MtLayout::set_margin(const unsigned int left_margin,
  const unsigned int top_margin,const unsigned int right_margin,
  const unsigned int bottom_margin){
	_margin->set_rect(left_margin,top_margin,right_margin,bottom_margin);
}

/**
 * name: get_margin
 * brief: ��ȡ�������ס�
 * param: --
 * return: ���ز������ס�
 */
const MtLayout::UintRect &MtLayout::get_margin() const{
	return(*_margin);
}

/**
 * name: get_window_amount
 * brief: ��ȡ����������
 * param: --
 * return: ���ش���������
 */
unsigned int MtLayout::get_window_amount() const{
	//1.������ǰ�������������
	unsigned int window_amount=0;
	//2.ͳ�Ʋ��������д��ڸ�����
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		if(!static_cast<bool>(*iterator)){
			continue;
		}else{
			window_amount+=(*iterator)->get_window_amount();
		}
	}
	//3.���ص�ǰ���������д��ڸ�����
	return(window_amount);
}

/**
 * name: get_rect
 * brief: ��ȡ��ǰ���ֳߴ硣
 * param: --
 * return: ���ص�ǰ���ֳߴ硣
 */
const MtLayout::IntRect &MtLayout::get_rect() const{
	return(*_rect);
} 

/**
 * name: get_item_size
 * brief: ��ȡ������ָ������ĳߴ硣
 * param: index - ����������
 *        size - ���صĳߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::get_item_size(const unsigned int index,IntSize &size) const{
	//1.�����ǰ������ų�����Χ����ֱ�ӷ��ش���
	if(index>=_items.size()){
		return(-1);
	}
	//2.�����ǰ����Ϊ�գ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_items[index])){
		return(-2);
	}
	//3.���㵱ǰ����ߴ硣
	size.set_size(_items[index]->get_width(),_items[index]->get_height());
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_item_rect
 * brief: ��ȡ������ָ������ľ��γߴ硣
 * param: index - ����������
 *        rect - ���صľ��γߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::get_item_rect(const unsigned int index,IntRect &rect) const{
	//1.�����ǰ������ų�����Χ����ֱ�ӷ��ش���
	if(index>=_items.size()){
		return(-1);
	}
	//2.�����ǰ����Ϊ�գ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_items[index])){
		return(-2);
	}
	//3.���㵱ǰ����ߴ硣
	rect=_items[index]->get_rect();
	//4.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_item_window
 * brief: ����ָ��������ڡ�
 * param: index - ָ��������������
 *        window - ָ��ָ�����ڡ�
 *        stretch_factor - ����ϵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLayout::set_item_window(const unsigned int index,CWnd *window,const unsigned int stretch_factor){
	//1.�����ǰ������ų�����Χ����ֱ�ӷ��ش���
	if(index>=_items.size()){
		return(-1);
	}
	//2.����һ�������
	PtrToItem item(new MtLayoutWindowItem(_items[index]->get_rect(),window,stretch_factor));
	//3.�������ʧ�ܣ����ش�����롣
	if(!static_cast<bool>(item)){
		return(-2);
	}
	//4.�����������Ч���򷵻ش�����롣
	if(!item->is_valid()){
		return(-3);
	}
	//5.���õ�ǰ�Ӳ�����ڡ�
	_items[index]=item;
	//6.�������е��ˣ��ɹ����ء�
	return(0);
}