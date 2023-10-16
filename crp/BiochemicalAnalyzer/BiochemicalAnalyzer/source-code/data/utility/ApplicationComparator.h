#pragma once

#include<memory>

class Application;

/**
 * name: ApplicationComparator
 * breif: ��Ŀ��������Ƚ��࣬�����ṩ�����Ƚ�ָ������Ŀ���������
 * author: yameng_he
 * date: 2015-06-17
 */
class ApplicationComparator{
//define
public:
	typedef enum{COMPARE_METHOD_BY_ITEM_ID,
		COMPARE_METHOD_BY_ITEM_NO,}CompareMethod;
	typedef std::shared_ptr<Application> PtrToApp;
//construction & destruction
public:
	ApplicationComparator(const CompareMethod method);
	~ApplicationComparator(void);
//interface
public:
	bool operator()(const PtrToApp &left,const PtrToApp &right) const;
//variables
private:
	CompareMethod _method;
};