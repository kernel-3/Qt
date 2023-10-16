#include"stdafx.h"
#include"ListItemComment.h"

/**
 * name: ListItemComment
 * breif: 构造函数。
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
 * breif: 析构函数。
 * param: --
 * return: --
 */
ListItemComment::~ListItemComment(void){
}

/**
 * name: ListItemCommentFinder
 * brief: 构造函数。
 * param: mode - 查找模式。
 *        condition_a - 查找条件A。
 *        condition_b - 查找条件B。
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
 * breif: 析构函数。
 * param: --
 * return: --
 */
ListItemCommentFinder::~ListItemCommentFinder(){
}

/**
 * name: operator()
 * brief: 为列表项注释内容查找器提供查找方法。
 * param: list_item_comment - 指向匹配的注释内容。
 * return: 如果查找成功返回true，否则返回false。
 */
bool ListItemCommentFinder::operator()(
	const PtrToListItemComment &list_item_comment){
	//1.如果当前传递参数不合法，则直接返回错误。
	if(!static_cast<bool>(list_item_comment)){
		return(false);
	}
	//2.如果当前超找模式为“只根据item查找”。
	if(MODE_BY_ITEM==_mode){
		return(list_item_comment->_item==_condition_a);
	}
	//3.如果当前查找模式为“根据item和sub item查找”。
	else if(MODE_BY_ITEM_AND_SUB_ITEM==_mode){
		return((list_item_comment->_item==_condition_a)&&(
			list_item_comment->_sub_item==_condition_b));
	}
	//4.如果当前查找模式为“根据最大item和最小item查找”。
	else if(MODE_BY_MIN_ITEM_ANDM_MAX_ITEM==_mode){
		//4-1.计算最大、最小值。
		int min=0,max=0;
		if(_condition_a<=_condition_b){
			min=_condition_a;
			max=_condition_b;
		}else{
			min=_condition_b;
			max=_condition_a;
		}
		//4-2.利用最大、最小值进行匹配。
		return((list_item_comment->_item>=min)&&(
			list_item_comment->_item<=max));
	}
	//5.如果当前为其它查找模式。
	return(false);
}