#pragma once

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class Functions;
class Communications;
class Components;

/**
 * name: Instrument
 * brief: 设备类，描述发光仪设备，并提供与发光仪相关
 *        的所有接口。
 * author: yameng_he
 * date: 2016-01-11.
 */
class Instrument{
//define
public:
	typedef MtSingleton<Instrument,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction 
public:
	~Instrument(void);
//interface
public:
	static Instrument *instance();
//interface
public:
	Functions *get_functions();
	Components *get_components();
	Communications *get_communications();
//construction
private:
	Instrument(void);
//restriction
private:
	Instrument(const Instrument &);
	Instrument &operator=(const Instrument &);
//variables
private:
	Functions *_functions;
	Components *_components;
	Communications *_communications;
};