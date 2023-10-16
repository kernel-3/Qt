#include"stdafx.h"
#include"MtLog.h"
#include"MtLock.h"
#include"MtAutoLock.h"
#include<memory>

/**
 * name: MtLog
 * breif: ���캯����
 * param: directory - �������־·����
 * return: --
 */
MtLog::MtLog(const CString &directory)
	:_lock(new MtLock)
	,_directory(directory)
	,_file(){
}

/**
 * name: ~MtLog
 * breif: ����������
 * param: --
 * return: --
 */
MtLog::~MtLog(void){
	close();
	delete _lock;
}

/**
 * name: write
 * brief: ����־�ļ�����д���ݡ�
 * param: text - ������д�����ݡ�
 * return: --
 */
void MtLog::write(const CString &text){
	//1.������������Ϊ�գ���ֱ�ӷ��ء�
	if(_T("")==text){
		return;
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.����ļ�������������������
	if((_file.bad())||(_file.fail())){
		_file.clear();
	}
	//4.����ļ���δ�򿪣�����д򿪲�����
	if(!_file.is_open()){
		if(open(FALSE)<0){
			_file.clear();
		}
	}
	//6.����ļ��ɹ��򿪣��������־������д��
	if(_file.is_open()){
		_file<<text<<std::endl;
	}
}

/**
 * name: open
 * breif: �򿪵�ǰ��־��
 * param: is_locked - ������Ƿ�������ǡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtLog::open(const BOOL is_locked/*=TRUE*/){
	//1.�رյ�ǰ��־��
	close(is_locked);
	//2.���塣
	typedef std::auto_ptr<MtAutoLock<
		MtLock>> PtrToAutoLock;
	//3.������
	PtrToAutoLock auto_lock;
	if(is_locked){
		auto_lock.reset(new MtAutoLock<MtLock>(_lock));
	}
	//4.���㵱ǰ��־�ļ����ơ�
	const CString name=(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d.log"));
	//5.�жϵ�ǰ�ļ����Ƿ��д����������������������
	if(_file.bad()||_file.fail()){
		_file.clear();
	}
	//6.���õ�ǰ������
	std::locale old=std::locale::global(std::locale(""));
	//7.����־�ļ���
	_file.open(_directory+name,std::ios_base::out|std::ios_base::app);
	//8.�ָ���ǰ������
	std::locale::global(old);
	//9.��⵱ǰ��־�ļ����Ƿ�ɹ���
	if(_file.fail()){
		return(-1);
	}
	//10.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: close
 * brief: �رյ�ǰ��־��
 * param: is_locked - ������Ƿ�������ǡ�
 * return: --
 */
void MtLog::close(const BOOL is_locked/*=TRUE*/){
	//1.���塣
	typedef std::auto_ptr<MtAutoLock<
		MtLock>> PtrToAutoLock;
	//2.������
	PtrToAutoLock auto_lock;
	if(is_locked){
		auto_lock.reset(new MtAutoLock<MtLock>(_lock));
	}
	//3.�жϵ�ǰ�ļ����Ƿ��д����������������������
	if(_file.bad()||_file.fail()){
		_file.clear();
	}
	//4.�����ǰ�ļ������ڴ�״̬������йرղ�����
	if(_file.is_open()){
		//4-1.ǿ��ˢ�»�������
		_file.flush();
		//4-2.�����ǰ�ļ����Ƿ��д����������������������
		if(_file.bad()||_file.fail()){
			_file.clear();
		}
		//4-3.�رյ�ǰ�ļ�����
		_file.close();
	}
}
