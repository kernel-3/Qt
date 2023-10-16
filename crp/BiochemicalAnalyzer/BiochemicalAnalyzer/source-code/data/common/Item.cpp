#include"stdafx.h"
#include"Item.h"
#include"../../global/Database.h"
#include"../../global/Theme.h"
#include"../../../../../include/mfctoolkit/database/MtADORecordset.h"
#include"../../../../../include/mfctoolkit/database/MtADODataConverter.h"
#include"../../../Resource.h"

/**
 * name: Item
 * breif: ���캯����
 * param: --
 * return: --
 */
Item::Item(void)
	:_id(0)
	,_no(0)
	,_name(_T(""))
	,_alias(_T(""))
	,_status(STATUS_UNKNOWN){
}

/**
 * name: ~Item
 * breif: ����������
 * param: --
 * return: --
 */
Item::~Item(void){
}

/**
 * name: set_id
 * breif: ���õ�ǰ��ĿID��
 * param: id - ��ĿID��
 * return: --
 */
void Item::set_id(const int id){
	_id=id;
}

/**
 * name: get_id
 * breif: ��ȡ��ǰ��ĿID��
 * param: --
 * return: ���ص�ǰ��ĿID��
 */
int Item::get_id() const{
	return(_id);
}

/**
 * name: set_no
 * breif: ���õ�ǰ��Ŀ��š�
 * param: no - ��Ŀ��š�
 * return: --
 */
void Item::set_no(const int no){
	_no=no;
}

/**
 * name: get_no
 * breif: ��ȡ��ǰ��Ŀ��š�
 * param: --
 * return: ���ص�ǰ��Ŀ��š�
 */
int Item::get_no() const{
	return(_no);
}

/**
 * name: set_name
 * brief: ���õ�ǰ��Ŀ���ơ�
 * param: name - ��Ŀ���ơ�
 * return: --
 */
void Item::set_name(const CString &name){
	_name=name;
}

/**
 * name: get_name
 * breif: ��ȡ��ǰ��Ŀ���ơ�
 * param: --
 * return: ���ص�ǰ��Ŀ���ơ�
 */
const CString &Item::get_name() const{
	return(_name);
}

/**
 * name: set_alias
 * brief: ���õ�ǰ��Ŀ������
 * param: alias - ��Ŀ������
 * return: --
 */
void Item::set_alias(const CString &alias){
	_alias=alias;
}

/**
 * name: get_alias
 * brief: ��ȡ��ǰ��Ŀ������
 * param: --
 * return: ���ص�ǰ��Ŀ������
 */
const CString &Item::get_alias() const{
	return(_alias);
}

/**
 * name: set_status
 * brief: ���õ�ǰ��Ŀ״̬��
 * param: status - ��Ŀ״̬��
 * return: --
 */
void Item::set_status(const Status status){
	_status=status;
}

/**
 * name: get_status
 * brief: ��ȡ��ǰ��Ŀ״̬��
 * param: --
 * return: ���ص�ǰ��Ŀ״̬��
 */
Item::Status Item::get_status() const{
	return(_status);
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ��Ŀ��Ϣ�Ƿ�Ϸ���
 * param: error_message - ָ������Ĵ�����Ϣ��û�д���ʱ��������ϢΪ�գ���
 * return: �����ǰ��Ŀ��Ϣ�Ϸ��򷵻�ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Item::is_valid(CString *error_message/*=0*/) const{
	//1.��յ�ǰ������Ϣ��
	if(0!=error_message){
		(*error_message)=_T("");
	}
	//2.�����Ŀ��ʶ���Ϸ���
	if((_id<1)||(_id>999)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING177),1,999);
		}
		return(-1);
	}
	//3.�����Ŀ��Ų��Ϸ���
	if((_no<1)||(_no>200)){
		if(0!=error_message){
			error_message->Format(Theme::instance()->
				get_string(IDS_STRING178),1,200);
		}
		return(-2);
	}
	//4.�����Ŀ���Ʋ��Ϸ���
	if(_T("")==_name){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING179);
		}
		return(-3);
	}
	//5.�����Ŀ�������Ϸ���
	if(_T("")==_alias){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING180);
		}
		return(-4);
	}
	//6.�����Ŀ״̬���Ϸ���
	if(STATUS_UNKNOWN==_status){
		if(0!=error_message){
			(*error_message)=Theme::instance()->get_string(
				IDS_STRING181);
		}
		return(-5);
	}
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ����Ŀ��Ϣ��
 * param: record - ָ���ļ�¼����
 * return: �������ִ�г¹�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Item::update(MtADORecordset &record){
	//1.������ǰ�������������
	Item item;
	_variant_t value;
	//2.��ָ���ļ�¼���л�ȡ��ĿID��
	value=record.get_collect(MtADODataConverter::to_variant_t(0));
	if(0!=record.get_last_error_code()){
		return(-1);
	}
	item._id=MtADODataConverter::to_int(value);
	//3.��ָ���ļ�¼���л�ȡ��Ŀ��š�
	value=record.get_collect(MtADODataConverter::to_variant_t(1));
	if(0!=record.get_last_error_code()){
		return(-2);
	}
	item._no=MtADODataConverter::to_int(value);
	//4.��ָ���ļ�¼���л�ȡ��Ŀ���ơ�
	value=record.get_collect(MtADODataConverter::to_variant_t(2));
	if(0!=record.get_last_error_code()){
		return(-3);
	}
	item._name=MtADODataConverter::to_string(value);
	//5.��ָ���ļ�¼���л�ȡ��Ŀ������
	value=record.get_collect(MtADODataConverter::to_variant_t(3));
	if(0!=record.get_last_error_code()){
		return(-4);
	}
	item._alias=MtADODataConverter::to_string(value);
	//6.��ָ���ļ�¼���л�ȡ��Ŀ״̬��
	value=record.get_collect(MtADODataConverter::to_variant_t(4));
	if(0!=record.get_last_error_code()){
		return(-5);
	}
	item._status=static_cast<Status>(MtADODataConverter::to_int(value));
	//7.�����ǰ��ȡ����Ŀ��Ϣ���Ϸ�����ֱ�ӷ��ش���
	if(item.is_valid()<0){
		return(-6);
	}
	//8.Ϊ��ǰ��Ŀ��Ϣ��ֵ��
	(*this)=item;
	//9.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: commit
 * brief: ����ǰ����Ŀ��Ϣ�ύ�����ݿ��С�
 * param: commit_means - �ύ�����ݿ�ķ�����1 ���� 2 ���� 3 ɾ������
 *        database - ׼���ύ��Ŀ�����ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Item::commit(const int commit_means,Database &database) const{
	//1.�����ݿ��ύǰ��Ҫ��⵱ǰ��Ŀ��Ϣ�Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);
	}
	//2.�����ݿ����ύ���ݡ�
	//2-1.������ǰ�������������
	CString command(_T(""));
	//2-2.�����ǰ�����Բ������ʽ�ύ���ݡ�
	if(1==commit_means){
		command.Format(_T("INSERT INTO [item]([id],[no],[name],\
			[alias],[status])VALUES('%d','%d','%s','%s','%d')"),
			_id,_no,_name,_alias,_status);
	}
	//2-3.�����ǰ�����Ը��µ���ʽ�ύ���ݡ�
	else if(2==commit_means){
		command.Format(_T("UPDATE [item] SET [no]='%d',[name]='%s',\
			[alias]='%s',[status]='%d' WHERE [id]='%d'"),
			_no,_name,_alias,_status,_id);
	}
	//2-4.�����ǰ������ɾ������ʽ�ύ���ݡ�
	else if(3==commit_means){
		command.Format(_T("DELETE FROM [item] WHERE [id]='%d'"),_id);
	}
	//2-5.�����ǰ������������ʽ�������ύ�����ݿ��С�
	else{
		return(-2);
	}
	//2-6.�������ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
	if(database.execute(command)<0){
		return(-3);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}