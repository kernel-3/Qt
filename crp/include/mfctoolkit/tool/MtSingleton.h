#pragma once

#include"MtAutoLock.h"
#include<memory>

/**
 * name: MtSingleton
 * brief: 单件类，负责辅助实现单件设计模式。
 * author: yameng_he
 * date: 2014-05-29
 */
template<typename _Tp,typename _Lock>
class /*MFC_TOOLKIT_API*/ MtSingleton{
//define
public:
	typedef std::shared_ptr<_Tp> PtrToInstance;
//interface
public:
	static _Tp *instance();
//restrict
private:
	MtSingleton();
	MtSingleton(const MtSingleton &);
	~MtSingleton();
	MtSingleton &operator=(const MtSingleton &);
//variables
private:
	static _Lock _lock;
	static PtrToInstance _instance;
};

//初始化类中静态变量。
template<typename _Tp,typename _Lock>
_Lock MtSingleton<_Tp,_Lock>::_lock;
template<typename _Tp,typename _Lock>
typename MtSingleton<_Tp,_Lock>::PtrToInstance MtSingleton<_Tp,_Lock>::_instance;

/**
 * name: instance
 * brief: 获取指向指定类型的全局唯一的实例对象的指针。
 * param: --
 * return: 返回指向指定类型的全局唯一的实例对象的指针。
 * remark: 单例模式采用Double-Check方式实现，使用时请注意
 *         Double-Check方式的缺陷。
 */
template<typename _Tp,typename _Lock>
_Tp *MtSingleton<_Tp,_Lock>::instance(){
	if(!static_cast<bool>(_instance)){
		MtAutoLock<_Lock> lock(&_lock);
		if(!static_cast<bool>(_instance)){
			_instance.reset(new _Tp);
		}
	}
	return(_instance.get());
}