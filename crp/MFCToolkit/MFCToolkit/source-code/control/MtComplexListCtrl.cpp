#include"stdafx.h"
#include"MtComplexListCtrl.h"
#include"ListItemComment.h"
#include"../graphic/MtBitmap.h"
#include<algorithm>

/**
 * name: MtComplexListCtrl
 * brief: ���캯����
 * param: --
 * return: --
 */
MtComplexListCtrl::MtComplexListCtrl(void)
	:MtImageListCtrl()
	,_item_comments(){
}

/**
 * name: ~MtComplexListCtrl
 * brief: ����������
 * param: --
 * return: --
 */
MtComplexListCtrl::~MtComplexListCtrl(void){
}

/**
 * name: set_item_color
 * brief: ����ָ���б�����ɫ��
 * param: item - �б��
 *        sub_item - �б����
 *        color_a - ��ɫA�ɷ֡�
 *        color_r - ��ɫR�ɷ֡�
 *        color_g - ��ɫG�ɷ֡�
 *        color_b - ��ɫB�ɷ֡�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtComplexListCtrl::set_item_color(const int item,const int sub_item,
	const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���������Ϸ�ֱ�ӷ��ش���
	if((item<0)||(item>=GetItemCount())){
		return(-1);
	}
	if((sub_item<0)||(sub_item>=(GetHeaderCtrl()->GetItemCount()))){
		return(-2);
	}
	//2.����ע�����ݣ��ж�ע�������Ƿ��Ѿ����ڡ�
	ItemCommentVector::iterator iterator=std::find_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::
		MODE_BY_ITEM_AND_SUB_ITEM,item,sub_item));
	//3.���ע�����ݲ����ڡ�
	if(_item_comments.end()==iterator){
		//3-1.�����µ�ע�����ݡ�
		PtrToItemComment comment(new ListItemComment);
		if(!static_cast<bool>(comment)){
			return(-3);
		}
		//3-2.�����µ�ע�����ݡ�
		comment->_item=item;
		comment->_sub_item=sub_item;
		comment->_item_color_a=color_a;
		comment->_item_color_r=color_r;
		comment->_item_color_g=color_g;
		comment->_item_color_b=color_b;
		//3-3.����ע�����ݡ�
		_item_comments.push_back(comment);
	}
	//4.���ע�����ݴ��ڡ�
	else{
		(*iterator)->_item_color_a=color_a;
		(*iterator)->_item_color_r=color_r;
		(*iterator)->_item_color_g=color_g;
		(*iterator)->_item_color_b=color_b;
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: set_item_count
 * brief: �����б���������
 * param: items - �б���������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtComplexListCtrl::set_item_count(const int items){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if(items<0){
		return(-1);
	}
	//2.��ȡ��ǰ�б����б����������
	const int current_items=GetItemCount();
	//3.����µ��б�������С�ڵ�ǰ�б�����������ɾ����Ӧ�Ķ�������б����ע�����ݡ�
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
	//4.���õ�ǰ�б���������
	SetItemCount(items);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: draw_item
 * brief: ���⺯���������б��
 * param: memory_bitmap - �ڴ�λͼ���á�
 *        item - �б��
 *        sub_item - �б����
 *        item_rect - �б���λ�óߴ硣
 *        state - �б���״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �˺�������������б���Ľӿڡ�
 */
int MtComplexListCtrl::draw_item(MtBitmap &memory_bitmap,const int item,
	const int sub_item,const CRect &item_rect,const unsigned int /*state*/){
	//1.�жϵ�ǰ���ݲ����Ƿ�Ϸ���
	if((item<0)||(item>=GetItemCount())){
		return(-1);
	}
	if((sub_item<0)||(sub_item>=(GetHeaderCtrl()->GetItemCount()))){
		return(-2);
	}
	if(item_rect.IsRectEmpty()){
		return(-3);
	}
	//2.�����ǰ�������κ��б���ע�����ݣ���ֱ�ӷ��ء�
	if(_item_comments.empty()){
		return(0);
	}
	//3.�ж�����Ҫ���Ƶ��б���ע�������Ƿ���ڡ�
	ItemCommentVector::iterator iterator=std::find_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::
		MODE_BY_ITEM_AND_SUB_ITEM,item,sub_item));
	if(_item_comments.end()==iterator){
		return(0);
	}
	//4.�����б����ע�����ݡ�
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
	//5.�������е��˳ɹ����ء�
	return(0);
}

BEGIN_MESSAGE_MAP(MtComplexListCtrl,MtImageListCtrl)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM,&MtComplexListCtrl::OnLvnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS,&MtComplexListCtrl::OnLvnDeleteallitems)
END_MESSAGE_MAP()

/**
 * name: OnLvnDeleteitem
 * brief: �б���ɾ����Ϣ��Ӧ������
 * param: pNMHDR -
 *        pResult -
 * return: --
 */
void MtComplexListCtrl::OnLvnDeleteitem(NMHDR *pNMHDR,LRESULT *pResult){
	LPNMLISTVIEW pNMLV=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	////////////////////////////////////////////////////////
	//1.�����ǰ�б���ע������Ϊ�ա�
	if(_item_comments.empty()){
		return;
	}
	//2.������Ҫɾ�����б���ע�����ݡ�
	ItemCommentVector::iterator iterator=std::remove_if(_item_comments.begin(),
		_item_comments.end(),ListItemCommentFinder(ListItemCommentFinder::MODE_BY_ITEM,
		pNMLV->iItem));
	//3.ɾ����ǰ��Ӧ���б���ע�����ݡ�
	if(_item_comments.end()!=iterator){
		_item_comments.erase(iterator,_item_comments.end());
	}
	////////////////////////////////////////////////////////
	*pResult=0;
}

/**
 * name: OnLvnDeleteallitems
 * brief: �б���ȫ��ɾ����Ϣ��Ӧ������
 * param: pNMHDR -
 *        pResult -
 * return: --
 */
void MtComplexListCtrl::OnLvnDeleteallitems(NMHDR * /*pNMHDR*/,LRESULT *pResult){
	//LPNMLISTVIEW pNMLV=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	/////////////////////////////////////////////////////////
	//1.�����ǰ�б���ע������Ϊ�ա�
	if(_item_comments.empty()){
		return;
	}
	//2.ɾ����ǰȫ���б���ע�����ݡ�
	_item_comments.clear();
	/////////////////////////////////////////////////////////
	*pResult=0;
}
