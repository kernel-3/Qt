#pragma once

#include"Application.h"
#include"../common/Item.h"
#include<memory>

/**
 * name: ApplicationFinder
 * breif: ��Ŀ������������࣬�����ṩ��������ָ������Ŀ���������
 * author: yameng_he
 * date: 2015-06-16
 */
template<typename _Tp>
class ApplicationFinder{
//define
public:
	typedef enum{FIND_METHOD_BY_ITEM_NO,
		FIND_METHOD_BY_ITEM_ID,}FindMethod;
	typedef std::shared_ptr<Application> PtrToApp;
//construction & destruction
public:
	ApplicationFinder(const _Tp value,
		const FindMethod method);
	~ApplicationFinder();
//interface
public:
	bool operator()(const PtrToApp &application) const;
//variables
private:
	_Tp _value;
	FindMethod _method;
};

/**
 * name: ApplicationFinder
 * brief: ���캯����
 * param: value - ����������ֵ��
 *        method - ���������ķ�����
 * return: --
 */
template<typename _Tp>
ApplicationFinder<_Tp>::ApplicationFinder(
	const _Tp value,const FindMethod method)
	:_value(value)
	,_method(method){
}

/**
 * name: ~ApplicationFinder
 * brief: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
ApplicationFinder<_Tp>::~ApplicationFinder(){
}

/**
 * name: operator()
 * brief: ����()���������ṩ��Ŀ����������ҹ��ܡ�
 * param: application - ֻ��ָ������Ŀ���������
 * return: �����ǰֵ����ָ����Ŀ��������е���Ӧֵ����true�����򷵻�false��
 */
template<typename _Tp>
bool ApplicationFinder<_Tp>::operator()(const PtrToApp &application) const{
	//1.�����ǰ���ݲ������Ϸ�����ֱ�ӷ���false��
	if(!static_cast<bool>(application)){
		return(false);
	}
	//2.�����ǰ���ҷ���Ϊͨ����Ŀ��Ų��ҡ�
	if(FIND_METHOD_BY_ITEM_NO==_method){
		return(static_cast<int>(_value)==(application->get_item()).get_no());
	}
	//3.�����ǰ���ҷ���Ϊͨ����Ŀ��ʶ���ҡ�
	else if(FIND_METHOD_BY_ITEM_ID==_method){
		return(static_cast<int>(_value)==(application->get_item()).get_id());
	}
	//4.�����ǰ���ҷ���δ֪����ֱ�ӷ���false��
	else{
		return(false);
	}
}