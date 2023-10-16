#pragma once

#include<memory>
#include<vector>

class AnalysisMethod;
class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Database;

/**
 * name: AnalysisMethods
 * breif: �������������࣬����ά��ϵͳ��ȫ���ķ�������
 *        ���ṩ�����������صĽӿڡ�
 * author: yameng_he
 * date: 2015-11-30
 */
class AnalysisMethods{
//define
public:
	typedef std::shared_ptr<AnalysisMethod> PtrToMethod;
	typedef std::shared_ptr<const AnalysisMethod> PtrToCMethod;
	typedef std::vector<PtrToMethod> Methods;
	typedef MtSingleton<AnalysisMethods,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~AnalysisMethods(void);
//interface
public:
	static AnalysisMethods *instance();
//interface
public:
	unsigned int get_count() const;
	PtrToCMethod get_method(const unsigned int index) const;
	int update(Database &database);
//construction
private:
	AnalysisMethods(void);
//restriction
private:
	AnalysisMethods(const AnalysisMethods &);
	AnalysisMethods &operator=(const AnalysisMethods &);
//variables
private:
	MtLock *_lock;
	Methods _methods;
};

