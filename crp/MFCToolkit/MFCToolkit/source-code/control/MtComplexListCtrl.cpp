#include"stdafx.h"
#include"MtComplexListCtrl.h"
#include"ListItemComment.h"
#include"../graphic/MtBitmap.h"
#include<algorithm>

/**
 * name: MtComplexListCtrl
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtComplexListCtrl::MtComplexListCtrl(void)
	:MtImageListCtrl()
	,_item_comments(){
}

/**
 * name: ~MtComplexListCtrl
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtComplexListCtrl::~MtComplexListCtrl(void){
}

/**
 * name: set_item_color
 * brief: 设置指定列表项颜色。
 * param: item - 列表项。
 *        sub_item - 列表子项。
 *        color_a - 颜色A成分。
 *        color_r - 颜色R成分。
 *        color_g - 颜色G成分。
 *        color_b - 颜色B成分。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtComplexListCtrl::set_item_color(const int item,const int sub_item,
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	//1.判断当前传递参数是否合法，如果不合法直接返回错误。
	if((item<0)||(item>=GetItemCount())){
		return(-1);
	}
	if((sub_item<0)||(sub_item>=(GetHeaderCtrl()->GetItemCount()))){
		return(-2);
	}
	//2.查找注释内容，判断注释内容是否已经存在。
	ItemCommentVector::iterator iterator=std::find_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::
		MODE_BY_ITEM_AND_SUB_ITEM,item,sub_item));
	//3.如果注释内容不存在。
	if(_item_comments.end()==iterator){
		//3-1.创建新的注释内容。
		PtrToItemComment comment(new ListItemComment);
		if(!static_cast<bool>(comment)){
			return(-3);
		}
		//3-2.设置新的注释内容。
		comment->_item=item;
		comment->_sub_item=sub_item;
		comment->_item_color_a=color_a;
		comment->_item_color_r=color_r;
		comment->_item_color_g=color_g;
		comment->_item_color_b=color_b;
		//3-3.加入注释内容。
		_item_comments.push_back(comment);
	}
	//4.如果注释内容存在。
	else{
		(*iterator)->_item_color_a=color_a;
		(*iterator)->_item_color_r=color_r;
		(*iterator)->_item_color_g=color_g;
		(*iterator)->_item_color_b=color_b;
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: set_item_count
 * brief: 设置列表项数量。
 * param: items - 列表项数量。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtComplexListCtrl::set_item_count(const int items){
	//1.判断当前传递参数是否合法。
	if(items<0){
		return(-1);
	}
	//2.获取当前列表中列表项的数量。
	const int current_items=GetItemCount();
	//3.如果新的列表项数量小于当前列表项数量，则删除相应的多出来的列表项的注释内容。
	if(items<current_items){
		if(!_item_comments.empty()){
			ItemCommentVector::iterator iterator=
				std::remove_if(_item_comments.begin(),_item_comments.end(),
				ListItemCommentFinder(ListItemCommentFinder::
				MODE_BY_MIN_ITEM_ANDM_MAX_ITEM,items,current_items-1));
			if(_item_comments.end()!=iterator){
				_item_comments.erase(iterator,_item_comments.end());
			}
		}
	}
	//4.设置当前列表项数量。
	SetItemCount(items);
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: draw_item
 * brief: 虚拟函数，绘制列表项。
 * param: memory_bitmap - 内存位图引用。
 *        item - 列表项。
 *        sub_item - 列表子项。
 *        item_rect - 列表项位置尺寸。
 *        state - 列表项状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 此函数是子类绘制列表项的接口。
 */
int MtComplexListCtrl::draw_item(MtBitmap &memory_bitmap,const int item,
	const int sub_item,const CRect &item_rect,const unsigned int /*state*/){
	//1.判断当前传递参数是否合法。
	if((item<0)||(item>=GetItemCount())){
		return(-1);
	}
	if((sub_item<0)||(sub_item>=(GetHeaderCtrl()->GetItemCount()))){
		return(-2);
	}
	if(item_rect.IsRectEmpty()){
		return(-3);
	}
	//2.如果当前不存在任何列表项注释内容，则直接返回。
	if(_item_comments.empty()){
		return(0);
	}
	//3.判断所需要绘制的列表项注释内容是否存在。
	ItemCommentVector::iterator iterator=std::find_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::
		MODE_BY_ITEM_AND_SUB_ITEM,item,sub_item));
	if(_item_comments.end()==iterator){
		return(0);
	}
	//4.绘制列表项的注释内容。
	CRect item_rect_t(item_rect);
	if(0==sub_item){
		item_rect_t.InflateRect(-2,-1,-2,-2);
	}else{
		item_rect_t.InflateRect(-1,-1,-2,-2);
	}
	if(memory_bitmap.fill_rectangle((*iterator)->_item_color_a,
		(*iterator)->_item_color_r,(*iterator)->_item_color_g,
		(*iterator)->_item_color_b,item_rect_t.left,item_rect_t.top,
		item_rect_t.Width(),item_rect_t.Height())<0){
		return(-4);
	}
	//5.程序运行到此成功返回。
	return(0);
}

BEGIN_MESSAGE_MAP(MtComplexListCtrl,MtImageListCtrl)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM,&MtComplexListCtrl::OnLvnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS,&MtComplexListCtrl::OnLvnDeleteallitems)
END_MESSAGE_MAP()

/**
 * name: OnLvnDeleteitem
 * brief: 列表项删除消息响应函数。
 * param: pNMHDR -
 *        pResult -
 * return: --
 */
void MtComplexListCtrl::OnLvnDeleteitem(NMHDR *pNMHDR,LRESULT *pResult){
	LPNMLISTVIEW pNMLV=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	////////////////////////////////////////////////////////
	//1.如果当前列表项注释内容为空。
	if(_item_comments.empty()){
		return;
	}
	//2.查找需要删除的列表项注释内容。
	ItemCommentVector::iterator iterator=std::remove_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::MODE_BY_ITEM,
		pNMLV->iItem));
	//3.删除当前相应的列表项注释内容。
	if(_item_comments.end()!=iterator){
		_item_comments.erase(iterator,_item_comments.end());
	}
	////////////////////////////////////////////////////////
	*pResult=0;
}

/**
 * name: OnLvnDeleteallitems
 * brief: 列表项全部删除消息响应函数。
 * param: pNMHDR -
 *        pResult -
 * return: --
 */
void MtComplexListCtrl::OnLvnDeleteallitems(NMHDR * /*pNMHDR*/,LRESULT *pResult){
	//LPNMLISTVIEW pNMLV=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	/////////////////////////////////////////////////////////
	//1.如果当前列表项注释内容为空。
	if(_item_comments.empty()){
		return;
	}
	//2.删除当前全部列表项注释内容。
	_item_comments.clear();
	/////////////////////////////////////////////////////////
	*pResult=0;
}
