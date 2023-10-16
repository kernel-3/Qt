#pragma once

#include"MtImageListCtrl.h"
#include<vector>

class ListItemComment;

/**
 * name: MtComplexListCtrl
 * brief: 复合列表控件，提供多种功能的列表控件。
 * auhtor: yameng_he
 * date: 2015-03-24
 */
class MFC_TOOLKIT_API MtComplexListCtrl 
	:public MtImageListCtrl{
//define
public:
	typedef std::shared_ptr<ListItemComment> PtrToItemComment;
	typedef std::vector<PtrToItemComment> ItemCommentVector;
//construction & destruction
public:
	MtComplexListCtrl(void);
	virtual ~MtComplexListCtrl(void);
//interface
public:
	int set_item_color(const int item,const int sub_item,
		const unsigned char color_a,const unsigned char color_r,
		const unsigned char color_g,const unsigned char color_b);
	int set_item_count(const int items);
//overrides
protected:
	virtual int draw_item(MtBitmap &memory_bitmap,const int item,
		const int sub_item,const CRect &item_rect,const unsigned int state);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnLvnDeleteallitems(NMHDR *pNMHDR,LRESULT *pResult);
//variables
private:
	ItemCommentVector _item_comments;
};