#pragma once

#include<memory>

class Application;

/**
 * name: ApplicationComparator
 * breif: 项目申请参数比较类，负责提供方法比较指定的项目申请参数。
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