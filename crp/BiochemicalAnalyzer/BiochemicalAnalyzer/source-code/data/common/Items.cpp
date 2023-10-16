#include"stdafx.h"
#include"Items.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../global/Database.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"Item.h"
#include<assert.h>

/**
 * name: ~Items
 * breif: ����������
 * param: --
 * return: --
 */
Items::~Items(void){
	delete _lock;
}

/**
 * name: Items
 * brief: ���캯����
 * param: --
 * return: --
 */
Items::Items(void)
	:_lock(new MtLock)
	,_items()
	,_items_no(){
}

/**
 * name: instance
 * brief: ��ȡ��ǰ����ϵͳ�е�Ψһʵ����ָ�롣
 * param: --
 * return: ���ص�ǰ����ϵͳ�е�Ψһʵ����ָ�롣
 */
Items *Items::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_count
 * brief: ��ȡ��ǰϵͳ����Ŀ�ĸ�����
 * param: --
 * return: ���ص�ǰϵͳ����Ŀ�ĸ�����
 */
int Items::get_count() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ص�ǰϵͳ����Ŀ�ĸ�����
	return(_items.size());
}

/**
 * name: is_id_existed
 * brief: �����Ŀ��ʶ�Ƿ���ڡ�
 * param: id - �������Ŀ��ʶ��
 * return: �����Ŀ��ʶ���ڷ���ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::is_id_existed(const int id) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ��Ŀ��ʶ�����ڡ�
	if(_items.end()==_items.find(id)){
		return(-1);
	}
	//3.�����ǰ��Ŀ��ʶ���ڡ�
	else{
		return(0);
	}
}

/**
 * name: is_no_existed
 * brief: �����Ŀ����Ƿ���ڡ�
 * param: no - �������Ŀ��š�
 * return: �����Ŀ��Ŵ��ڷ���ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::is_no_existed(const int no) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ��Ŀ��Ų����ڡ�
	if(_items_no.end()==_items_no.find(no)){
		return(-1);
	}
	//3.�����ǰ��Ŀ��Ŵ��ڡ�
	else{
		return(0);
	}
}

/**
 * name: add
 * breif: ��ϵͳ�����һ����Ŀ��
 * param: item - �����ָ����Ŀ������ָ�롣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::add(const PtrToItem &item){
	//1.��������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(item)){
		return(-1);
	}
	if(item->is_valid()<0){
		return(-2);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ڴ����Ƿ��Ѿ����ڶ�Ӧ����Ŀ,����Ѿ�������ֱ�ӷ��ش���
	if(_items.end()!=_items.find(item->get_id())){
		return(-3);
	}
	if(_items_no.end()!=_items_no.find(item->get_no())){
		return(-4);
	}
	//4.��������Ŀ���뵽ϵͳ��Ŀ�洢�����С�
	_items[item->get_id()]=item;
	_items_no[item->get_no()]=item->get_id();
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: modify
 * breif: �޸�ָ������Ŀ��Ϣ��
 * param: item - �����ָ����Ŀ��
 * return: �������ִ�гɹ�����ֵС���㣬���򷵻�ֵ���ڵ����㡣
 */
int Items::modify(const Item &item){
	//1.��������ָ����Ŀ�Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(item.is_valid()<0){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ڴ����Ƿ��Ѿ����ڶ�Ӧ����Ŀ,�����������ֱ�ӷ��ش���
	if(_items.end()==_items.find(item.get_id())){
		return(-2);
	}
	//4.���ָ������Ŀ�Ƿ���ڣ������������ֱ�ӷ��ش���
	if(!static_cast<bool>(_items[item.get_id()])){
		return(-3);
	}
	//5.�޸�ָ������Ŀ��Ϣ��
	(*_items[item.get_id()])=item;
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: remove
 * brief: ɾ��ָ������Ŀ��
 * param: item_id - ָ������Ŀ��ʶ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::remove(const int item_id){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ڴ����Ƿ��Ѿ����ڶ�Ӧ����Ŀ,�����������ֱ�ӷ��ش���
	MItems::iterator iterator=_items.find(item_id);
	if(_items.end()==iterator){
		return(-1);
	}
	//4.������Ŀ��Ϣ������Ч��
	assert(static_cast<bool>(iterator->second));
	//5.�����ڴ����Ƿ��Ѿ����ڶ�Ӧ����Ŀ��ţ������������ֱ�ӷ��ش���
	MItemsNo::iterator no_iterator=_items_no.find((
		iterator->second)->get_no());
	if(_items_no.end()==no_iterator){
		return(-2);
	}
	//6.ɾ��ָ������Ŀ��Ϣ�Լ���Ŀ�����Ϣ��
	_items.erase(iterator);
	_items_no.erase(no_iterator);
	//7.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: get_by_id
 * brief: ͨ����Ŀ��ʶ��ȡ��Ŀ��
 * param: id - �������Ŀ��ʶ��
 * return: �����ȡ��Ŀ�ɹ�������ָ����Ŀ������ָ�룬���򷵻ؿ�ָ�롣
 */
Items::PtrToCItem Items::get_by_id(const int id) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ��Ŀ��ʶ�����ڣ���ֱ�ӷ��ؿ�ָ�롣
	if(_items.end()==_items.find(id)){//log(n)
		return(PtrToCItem());
	}
	//3.������Ӧ����Ŀ��Ϣ��
	return((const_cast<Items*>(this))->_items[id]);
}

/**
 * name: get_by_no
 * brief: ͨ����Ŀ��Ż�ȡ��Ŀ��
 * param: no - �������Ŀ��š�
 * return: �����ȡ��Ŀ�ɹ�������ָ����Ŀ������ָ�룬���򷵻ؿ�ָ�롣
 */
Items::PtrToCItem Items::get_by_no(const int no) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����Ŀ��Ų����ڣ���ֱ�ӷ��ؿ�ָ�롣
	if(_items_no.end()==_items_no.find(no)){//log(n)
		return(PtrToCItem());
	}
	//3.��ȡ��Ŀ��Ŷ�Ӧ����Ŀ��ʶ��
	const int id=const_cast<Items*>(this)->_items_no[no];
	//4.�����Ŀ��ʶ�����ڣ���ֱ�ӷ��ؿ�ָ�롣
	if(_items.end()==_items.find(id)){//log(n)
		return(PtrToCItem());
	}
	//5.������Ӧ����Ŀ��Ϣ��
	return((const_cast<Items*>(this))->_items[id]);
}

/**
 * name: assign_id
 * breif: ����һ����Ŀ��ʶ��
 * param: --
 * return: ���ط������Ŀ��ʶ��
 */
int Items::assign_id() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�������κ���Ŀ��
	if(_items.empty()){
		return(1);
	}
	//3.��ȡ���һ����Ŀ����Ŀ��ʶ����ǰϵͳ��������Ŀ��ʶ����
	return((((--_items.end())->second)->get_id())+1);
}

/**
 * name: update
 * brief: �����ݿ������ظ������ݡ�
 * param: database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::update(Database &database){
	//1.������ǰ�������������
	MItems items;
	MItemsNo items_no;
	const CString command(_T("SELECT * FROM [item] ORDER BY [id] ASC"));
	//2.��ȡ���ݿ�����Ӧ�ļ�¼����
	Database::PtrToRecordset records=database.get_recordset(command);
	if(!static_cast<bool>(records)){
		return(-1);
	}
	//3.������¼�����Ӽ�¼���л�ȡģ����Ϣ��
	while(!records->get_eof()){
		//3-1.�ж������ȡ��¼��β�Ƿ�ɹ���
		if(0!=records->get_last_error_code()){
			return(-2);
		}
		//3-2.������Ŀ��Ϣ�࣬�����жϴ����Ƿ�ɹ���
		PtrToItem item(new Item);
		if(!static_cast<bool>(item)){
			return(-3);
		}
		//3-3.�ӵ�ǰ�ļ�¼���и�����Ŀ��Ϣ��
		if(item->update(*records)<0){
			return(-4);
		}
		//3-4.����ǰ����Ŀ��Ϣ���뵽�����С�
		//a.�������в�����Ŀ��Ϣ��
		if(items.end()==items.find(item->get_id())){
			items[item->get_id()]=item;
		}else{
			return(-5);
		}
		//b.������Ŀ�������Ŀ��ʶ��ӳ�䡣
		if(items_no.end()==items_no.find(item->get_no())){
			items_no[item->get_no()]=item->get_id();
		}else{
			return(-6);
		}
		//3-5.�����¼������һ��λ�á�
		records->move_next();
		if(0!=records->get_last_error_code()){
			return(-7);
		}
	}
	//4.����Ӽ�¼���и��µ���Ŀ��Ϣ��
	//4-1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//4-2.����Ӽ�¼���и��µ���Ŀ��Ϣ��
	_items.swap(items);
	_items_no.swap(items_no);
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: commit
 * breif: ����ǰ���������ύ�����ݿ��С�
 * param: item_id - ָ������Ŀ��ʶ��
 *        commit_means - �ύ��ʽ��1 ���� 2 ���� 3 ɾ������
 *        database - ���ݿ����ʵ����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Items::commit(const int item_id,
	const int commit_means,Database &database) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ҵ�ǰ׼���ύ���ݵ���Ŀ�������жϲ����Ƿ�ɹ���
	MItems::const_iterator iterator=_items.find(item_id);
	if(_items.end()==iterator){
		return(-1);
	}
	//3.���ҵ���Ŀ�������ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
	if((iterator->second)->commit(commit_means,database)<0){
		return(-2);
	}
	//4.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: traverse
 * breif: �����洢��ȫ����Ŀ��
 * param: callback - ����Ļص�������
 * return: --
 */
void Items::traverse(const TraverseCallback &callback) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����洢��ȫ����Ŀ�����ҵ��ñ����ص�������
	for(MItems::const_iterator iterator=_items.begin();
		iterator!=_items.end();++iterator){
		//2-1.���������Ŀ��Ϣ�Ϸ���
		assert(static_cast<bool>(iterator->second));
		//2-2.������Ӧ�Ļص�������
		callback(*iterator->second);
	}
}