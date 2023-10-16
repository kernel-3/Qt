#pragma once

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class MtIni;

/**
 * name: Inis
 * breif: ini�ļ������࣬����ά��ϵͳ��ȫ����ini�ļ���
 *        ���ṩ��ini�ļ���ص�ȫ���ӿڡ�
 * author: yameng_he
 * date: 2016-02-16.
 */
class Inis{
//define
public:
	typedef enum{NAME_INSTRUMENT,}Name;
	typedef MtSingleton<Inis,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~Inis(void);
//interface
public:
	static Inis *instance();
//interface
public:
	int read(const Name file_name,const CString &section_name,
		const CString &item_name,const int default_value=0);
	BOOL write(const Name file_name,const CString &section_name,
		const CString &item_name,const int value);
//construction
private:
	Inis(void);
//restriction
private:
	Inis(const Inis &);
	Inis &operator=(const Inis &);
//variables
private:
	MtIni *_instrument;
};

