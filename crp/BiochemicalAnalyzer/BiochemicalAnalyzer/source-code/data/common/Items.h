#pragma once

#include<memory>
#include<map>
#include<functional>

class Item;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**
 * name: Items
 * breif: 项目管理类，负责维护、管理系统中全部的
 *        项目信息。
 * author: yameng_he
 * date: 2015-11-10
 * remark: 因为对于项目信息的操作，查找多于删除以及插入，
 *         因此此处用map（红黑树）实现，所有操作的时间复
 *         杂度均为ln(n)。
 *         因为程序有时需要按项目序号检索项目，不得已建立
 *         项目序号与项目标识的map（红黑树），这样当按照
 *         项目序号查找项目信息的时间复杂度为2ln(n)。
 */
class Items{
//define
public:
	typedef std::shared_ptr<Item> PtrToItem;
	typedef std::shared_ptr<const Item> PtrToCItem;
	typedef std::map<int,PtrToItem> MItems;
	typedef std::map<int,int> MItemsNo;
	typedef MtSingleton<Items,MtLock> Singleton_Instance;
	typedef std::function<void(const Item &)> TraverseCallback;
	friend class Singleton_Instance;
//destruction
public:
	~Items(void);
//interface
public:
	static Items *instance();
//interface
public:
	int get_count() const;
	int is_id_existed(const int id) const;
	int is_no_existed(const int no) const;
	int add(const PtrToItem &item);
	int modify(const Item &item);
	int remove(const int item_id);
	PtrToCItem get_by_id(const int id) const;
	PtrToCItem get_by_no(const int no) const;
	int assign_id() const;
	int update(Database &database);
	int commit(const int item_id,
		const int commit_means,Database &database) const;
	void traverse(const TraverseCallback &callback) const;
//construction
private:
	Items(void);
//restriction
private:
	Items(const Items &);
	Items &operator=(const Items &);
//variables
private:
	MtLock *_lock;
	MItems _items;
	MItemsNo _items_no;
};