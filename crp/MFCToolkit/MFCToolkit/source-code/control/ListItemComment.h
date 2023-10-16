#pragma once

#include<memory>

/**
 * name: ListItemComment
 * biref: 列表项的注释内容。
 * author: yameng_he
 * date: 2015-03-24
 */
class ListItemComment{
//construction & destruction
public:
	ListItemComment(void);
	virtual ~ListItemComment(void);
//variables
public:
	int _item;
	int _sub_item;
	unsigned char _item_color_a;
	unsigned char _item_color_r;
	unsigned char _item_color_g;
	unsigned char _item_color_b;
};

/**
 * name: ListItemCommentFinder
 * brief: 列表项注释内容查找器。
 * author: yameng_he
 * date: 2015-03-24
 */
class ListItemCommentFinder{
//define
public:
	typedef std::shared_ptr<ListItemComment> PtrToListItemComment;
	typedef enum{MODE_BY_ITEM,MODE_BY_ITEM_AND_SUB_ITEM,
		MODE_BY_MIN_ITEM_ANDM_MAX_ITEM}Mode;
//construction & destruction
public:
	ListItemCommentFinder(const Mode mode,
		const int condition_a,const int condition_b=0);
	~ListItemCommentFinder();
//interface
public:
	bool operator()(const PtrToListItemComment &list_item_comment);
//variables
private:
	Mode _mode;
	int _condition_a;
	int _condition_b;
};