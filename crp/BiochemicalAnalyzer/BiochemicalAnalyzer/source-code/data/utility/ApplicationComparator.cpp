#include"stdafx.h"
#include"ApplicationComparator.h"
#include"Application.h"
#include"../common/Item.h"
#include<assert.h>

/**
 * name: ApplicationComparator
 * breif: ���캯����
 * param: method - �ȽϷ�����
 * return: --
 */
ApplicationComparator::ApplicationComparator(
	const CompareMethod method)
	:_method(method){
}

/**
 * name: ~ApplicationComparator
 * breif: ����������
 * param: --
 * return: --
 */
ApplicationComparator::~ApplicationComparator(void){
}

/**
 * name: operator()
 * breif: ����()���������ṩ��������ȽϷ�����
 * param: left - ָ���Ƚϵ����������
 *        right - ָ���Ƚϵ����������
 * return: ���leftС��right�򷵻�true�����򷵻�false��
 */
bool ApplicationComparator::operator()(
	const PtrToApp &left,const PtrToApp &right) const{
	//1.ȷ����ǰ�����Ĳ����Ϸ���������Ϸ���Ƚ������壩��
	assert(static_cast<bool>(left)&&static_cast<bool>(right));
	//2.�����ǰ�ıȽϷ���Ϊ��ĿID�Ƚϡ�
	if(COMPARE_METHOD_BY_ITEM_ID==_method){
		return(((left->get_item()).get_id())<
			((right->get_item()).get_id()));
	}
	//3.�����ǰ�ıȽϷ���Ϊ��Ŀ��űȽϡ�
	else if(COMPARE_METHOD_BY_ITEM_NO==_method){
		return(((left->get_item()).get_no())<
			((right->get_item()).get_no()));
	}
	//..����������е�����˵�������쳣.
	else{
		assert(0);//���е��˱�Ϊ�쳣��
		return(false);
	}
}