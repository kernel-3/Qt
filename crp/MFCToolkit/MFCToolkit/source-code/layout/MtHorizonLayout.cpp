#include"stdafx.h"
#include"MtHorizonLayout.h"
#include"MtLayoutItem.h"
#include"MtLayoutRect.h"
#include"MtLayoutSpacingItem.h"
#include"MtLayoutStretchItem.h"
#include"MtLayoutFixedLayoutItem.h"
#include"MtLayoutFixedWindowItem.h"

/**
 * name: MtHorizonLayout
 * brief: ���캯����
 * param: --
 * return: --
 */
MtHorizonLayout::MtHorizonLayout(void)
	:MtLayout(){
}

/**
 * name: ~MtHorizonLayout
 * brief: ����������
 * param: --
 * return: --
 */
MtHorizonLayout::~MtHorizonLayout(void){
}

/**
 * name: resize
 * brief: ���µ�����ǰ���ֳߴ硣
 * param: hdwp - �ര�ڳߴ�����ڴ�����
 *        rect - ��ǰ�����³ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::resize(HDWP &hdwp,const IntRect &rect){
	//1.���û�����Ӧ�麯����������ǰ���ֳߴ磬�����жϲ����Ƿ�ɹ���
	if(MtLayout::resize(hdwp,rect)<0){
		return(-1);
	}
	//2.�ۼƵ�ǰ�����У��洢��������������ϵ���Լ��̶��ߴ硣
	//2-1.������ǰ�������������
	unsigned int window_amount=0;
	unsigned int stretch_factor=0;
	unsigned int fixed_size=0;
	//2-2.�ۼƵ�ǰ�����д�������������ϵ���Լ��̶��ߴ硣
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		window_amount+=(*iterator)->get_window_amount();
		stretch_factor+=(*iterator)->get_stretch_factor();
		fixed_size+=(*iterator)->get_fixed_size();
	}
	//2-3.�����ǰ�����д�������Ϊ�㣬��ֱ�ӳɹ����ء�
	/*
	if(0==window_amount){
		return(0);
	}
	*/
	//3.����ര�ڳߴ�����ڴ����������ж������Ƿ�ɹ���
	/*
	HDWP hdwp=::BeginDeferWindowPos(window_amount);
	if(0==hdwp){
		return(-1);
	}
	*/
	//4.���ݵ�ǰ�������׳ߴ磬���㵱ǰ���ֵ���Ч�ߴ磬�����жϼ����Ƿ�ɹ���
	const IntRect valid_rect(_rect->get_left()+static_cast<int>(_margin->get_left()),
		_rect->get_top()+static_cast<int>(_margin->get_top()),
		_rect->get_right()-static_cast<int>(_margin->get_right()),
		_rect->get_bottom()-static_cast<int>(_margin->get_bottom()));
	if(!valid_rect.is_valid()){
		return(-2);
	}
	//5.������ǰ�����еĲ��������ÿһ��ߴ硣
	//5-1.������ǰ�������������
	int width_t=0;
	IntRect rect_t(valid_rect);
	//5-2.������ǰ���������ÿһ��������ĳߴ硣
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		//5-2-1.���ݵ�ǰ����������ϵ�������㵱ǰ��������³ߴ硣
		if(0==stretch_factor){
			width_t=0;
		}else{
			width_t=static_cast<int>(static_cast<double>(valid_rect.get_width()-
				static_cast<int>(fixed_size))/static_cast<double>(stretch_factor)*
				static_cast<double>((*iterator)->get_stretch_factor()));
		}
		if(width_t<0){
			width_t=0;
		}
		rect_t.set_right(rect_t.get_left()+width_t);
		if(!rect_t.is_valid()){
			return(-3);
		}
		//5-2-2.�Բ�������гߴ�����������жϵ����Ƿ�ɹ���
		if((*iterator)->resize(hdwp,rect_t)<0){
			return(-4);
		}
		//5-2-3.���¼��㵱ǰ������ߴ����ʼ�����ꡣ
		rect_t.set_left(((*iterator)->get_rect()).get_right());
	}
	//6.����ȫ�����ڳߴ�,�����жϸ����Ƿ�ɹ���
	/*
	if(!EndDeferWindowPos(hdwp)){
		return(-5);
	}
	*/
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: resize
 * brief: ���µ�����ǰ���ֳߴ硣
 * param: width - ��ȡ�
 *        height - �߶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::resize(const unsigned int width,const unsigned int height){
	//1.���û�����Ӧ�麯����������ǰ���ֳߴ硣
	MtLayout::resize(width,height);
	//2.�ۼƵ�ǰ�����д洢�����������̶��ߴ��Լ�����ϵ����
	//2-1.������ǰ�������������
	unsigned int window_amount=0;
	unsigned int stretch_factor=0;
	unsigned int fixed_size=0;
	//2-2.ͳ�Ƶ�ǰ�����д�������������ϵ���Լ��̶��ߴ硣
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		window_amount+=(*iterator)->get_window_amount();
		stretch_factor+=(*iterator)->get_stretch_factor();
		fixed_size+=(*iterator)->get_fixed_size();
	}
	//2-3.�����ǰ�����д�������Ϊ�㣬��ֱ�ӳɹ����ء�
	/*
	if(0==window_amount){
		return(0);
	}
	*/
	//3.����ര�ڳߴ�����ڴ����������ж������Ƿ�ɹ���
	HDWP hdwp=::BeginDeferWindowPos(window_amount);
	if(0==hdwp){
		return(-1);
	}
	//4.���ݵ�ǰ�������׳ߴ磬���㵱ǰ���ֵ���Ч�ߴ磬�����жϼ����Ƿ�ɹ���
	const IntRect valid_rect(_rect->get_left()+static_cast<int>(_margin->get_left()),
		_rect->get_top()+static_cast<int>(_margin->get_top()),
		_rect->get_right()-static_cast<int>(_margin->get_right()),
		_rect->get_bottom()-static_cast<int>(_margin->get_bottom()));
	if(!valid_rect.is_valid()){
		return(-2);
	}
	//5.������ǰ�����еĲ��������ÿһ��ߴ硣
	//5-1.������ǰ�������������
	int width_t=0;
	IntRect rect(valid_rect);
	//5-2.������ǰ���������ÿһ��������ĳߴ硣
	for(ItemVector::const_iterator iterator=_items.begin();iterator!=_items.end();++iterator){
		//5-2-1.���ݵ�ǰ����������ϵ�������㵱ǰ��������³ߴ硣
		if(0==stretch_factor){
			width_t=0;
		}else{
			width_t=static_cast<int>(static_cast<double>(valid_rect.get_width()-
				static_cast<int>(fixed_size))/static_cast<double>(stretch_factor)*
				static_cast<double>((*iterator)->get_stretch_factor()));
		}
		if(width_t<0){
			width_t=0;
		}
		rect.set_right(rect.get_left()+width_t);
		if(!rect.is_valid()){
			return(-3);
		}
		//5-2-2.�Բ�������гߴ�����������жϵ����Ƿ�ɹ���
		if((*iterator)->resize(hdwp,rect)<0){
			return(-4);
		}
		//5-2-3.���¼��㵱ǰ������ߴ����ʼ�����ꡣ
		rect.set_left(((*iterator)->get_rect()).get_right());
	}
	//6.����ȫ�����ڳߴ�,�����жϸ����Ƿ�ɹ���
	if(!EndDeferWindowPos(hdwp)){
		return(-5);
	}
	//7.�������е��˳ɹ����ء�
	return(0);
}

/*
 * name: add_spacing
 * brief: ��ǰ������׷��һ������
 * param: spacing_size - ����ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::add_spacing(const unsigned int spacing_size){
	//1.����һ������
	PtrToItem item(new MtLayoutSpacingItem(
		MtLayoutSpacingItem::ORIENTATION_HORIZON,spacing_size));
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
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: add_fixed_layout
 * brief: ���һ���̶��ߴ�Ĳ��֡�
 * param: layout - ָ��һ�����֡�
 *        fixed_size - �̶��ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::add_fixed_layout(MtLayout *layout,const unsigned int fixed_size){
	//1.����һ�������
	PtrToItem item(new MtLayoutFixedLayoutItem(layout,
		MtLayoutFixedLayoutItem::ORIENTATION_HORIZON,fixed_size));
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
 * name: add_fixed_window
 * brief: ��ӹ̶��ߴ�Ĵ��ڡ�
 * param: window - ָ�򴰿ڡ�
 *        fixed_size - �̶��ߴ硣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::add_fixed_window(CWnd *window,const unsigned int fixed_size){
	//1.����һ�������
	PtrToItem item(new MtLayoutFixedWindowItem(window,
		MtLayoutFixedWindowItem::ORIENTATION_HORIZON,fixed_size));
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
 * name: set_item_fixed_window
 * brief: ���ò�����̶����ڡ�
 * param: index - ������������
 *        window - ָ��ָ�����ڡ�
 *        fixed_size - ���ڹ̶��ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtHorizonLayout::set_item_fixed_window(
	const unsigned int index,CWnd *window,const unsigned int fixed_size){
	//1.�����ǰ������ų�����Χ����ֱ�ӷ��ش���
	if(index>=_items.size()){
		return(-1);
	}
	//2.����һ�������
	PtrToItem item(new MtLayoutFixedWindowItem(_items[index]->get_rect(),
		window,MtLayoutFixedWindowItem::ORIENTATION_HORIZON,fixed_size));
	//3.�������ʧ�ܣ����ش�����롣
	if(!static_cast<bool>(item)){
		return(-2);
	}
	//4.�����������Ч���򷵻ش�����롣
	if(!item->is_valid()){
		return(-3);
	}
	//5.����ǰ���������洢�����С�
	_items[index]=item;
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}