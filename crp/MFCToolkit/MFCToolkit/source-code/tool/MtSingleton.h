#pragma once

#include"MtAutoLock.h"
#include<memory>

/**
 * name: MtSingleton
 * brief: �����࣬������ʵ�ֵ������ģʽ��
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

//��ʼ�����о�̬������
template<typename _Tp,typename _Lock>
_Lock MtSingleton<_Tp,_Lock>::_lock;
template<typename _Tp,typename _Lock>
typename MtSingleton<_Tp,_Lock>::PtrToInstance MtSingleton<_Tp,_Lock>::_instance;

/**
 * name: instance
 * brief: ��ȡָ��ָ�����͵�ȫ��Ψһ��ʵ�������ָ�롣
 * param: --
 * return: ����ָ��ָ�����͵�ȫ��Ψһ��ʵ�������ָ�롣
 * remark: ����ģʽ����Double-Check��ʽʵ�֣�ʹ��ʱ��ע��
 *         Double-Check��ʽ��ȱ�ݡ�
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