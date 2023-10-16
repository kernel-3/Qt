#pragma once

#include"../Symbol"

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;

/**
 * name: MtGdiplus
 * brief: GDI+类，负责GDI+库相关功能实现。
 * author: yameng_he
 * date: 2014-05-29
 */
class MFC_TOOLKIT_API MtGdiplus{
//define
public:
	typedef MtSingleton<MtGdiplus,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destructor
public:
	~MtGdiplus(void);
//static interface
public:
	static MtGdiplus *instance();
	static int calculate_text_size(const CString &text,
		const HDC dc,const HFONT font,CSize &size);
//interface
public:
	int initialize();
	void release();
//restrict
private:
	MtGdiplus(const MtGdiplus &);
	MtGdiplus &operator=(const MtGdiplus &);
//constructor
private:
	MtGdiplus(void);
//variables
private:
	unsigned long _token;
};