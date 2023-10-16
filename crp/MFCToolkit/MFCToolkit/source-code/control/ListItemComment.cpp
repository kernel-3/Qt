#include"stdafx.h"
#include"ListItemComment.h"

/**
 * name: ListItemComment
 * breif: ���캯����
 * param: --
 * return: --
 */
ListItemComment::ListItemComment(void)
	:_item(0)
	,_sub_item(0)
	,_item_color_a(0)
	,_item_color_r(0)
	,_item_color_g(0)
	,_item_color_b(0){
}

/**
 * name: ~ListItemComment
 * breif: ����������
 * param: --
 * return: --
 */
ListItemComment::~ListItemComment(void){
}

/**
 * name: ListItemCommentFinder
 * brief: ���캯����
 * param: mode - ����ģʽ��
 *        condition_a - ��������A��
 *        condition_b - ��������B��
 * return: --
 */
ListItemCommentFinder::ListItemCommentFinder(
	const Mode mode,const int condition_a,const int condition_b/*=0*/)
	:_mode(mode)
	,_condition_a(condition_a)
	,_condition_b(condition_b){
}

/**
 * name: ~ListItemCommentFinder
 * breif: ����������
 * param: --
 * return: --
 */
ListItemCommentFinder::~ListItemCommentFinder(){
}

/**
 * name: operator()
 * brief: Ϊ�б���ע�����ݲ������ṩ���ҷ�����
 * param: list_item_comment - ָ��ƥ���ע�����ݡ�
 * return: ������ҳɹ�����true�����򷵻�false��
 */
bool ListItemCommentFinder::operator()(
	const PtrToListItemComment &list_item_comment){
	//1.�����ǰ���ݲ������Ϸ�����ֱ�ӷ��ش���
	if(!static_cast<bool>(list_item_comment)){
		return(false);
	}
	//2.�����ǰ����ģʽΪ��ֻ����item���ҡ���
	if(MODE_BY_ITEM==_mode){
		return(list_item_comment->_item==_condition_a);
	}
	//3.�����ǰ����ģʽΪ������item��sub item���ҡ���
	else if(MODE_BY_ITEM_AND_SUB_ITEM==_mode){
		return((list_item_comment->_item==_condition_a)&&(
			list_item_comment->_sub_item==_condition_b));
	}
	//4.�����ǰ����ģʽΪ���������item����Сitem���ҡ���
	else if(MODE_BY_MIN_ITEM_ANDM_MAX_ITEM==_mode){
		//4-1.���������Сֵ��
		int min=0,max=0;
		if(_condition_a<=_condition_b){
			min=_condition_a;
			max=_condition_b;
		}else{
			min=_condition_b;
			max=_condition_a;
		}
		//4-2.���������Сֵ����ƥ�䡣
		return((list_item_comment->_item>=min)&&(
			list_item_comment->_item<=max));
	}
	//5.�����ǰΪ��������ģʽ��
	return(false);
}