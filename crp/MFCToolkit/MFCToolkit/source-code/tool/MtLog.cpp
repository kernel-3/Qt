#include"stdafx.h"
#include"MtLog.h"
#include"MtLock.h"
#include"MtAutoLock.h"
#include<memory>

/**
 * name: MtLog
 * breif: 构造函数。
 * param: directory - 输入的日志路径。
 * return: --
 */
MtLog::MtLog(const CString &directory)
	:_lock(new MtLock)
	,_directory(directory)
	,_file(){
}

/**
 * name: ~MtLog
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtLog::~MtLog(void){
	close();
	delete _lock;
}

/**
 * name: write
 * brief: 向日志文件中书写内容。
 * param: text - 输入书写的内容。
 * return: --
 */
void MtLog::write(const CString &text){
	//1.如果输入的内容为空，则直接返回。
	if(_T("")==text){
		return;
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.如果文件出错，则进行清理操作。
	if((_file.bad())||(_file.fail())){
		_file.clear();
	}
	//4.如果文件尚未打开，则进行打开操作。
	if(!_file.is_open()){
		if(open(FALSE)<0){
			_file.clear();
		}
	}
	//6.如果文件成功打开，则进行日志内容书写。
	if(_file.is_open()){
		_file<<text<<std::endl;
	}
}

/**
 * name: open
 * breif: 打开当前日志。
 * param: is_locked - 输入的是否上锁标记。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtLog::open(const BOOL is_locked/*=TRUE*/){
	//1.关闭当前日志。
	close(is_locked);
	//2.定义。
	typedef std::auto_ptr<MtAutoLock<
		MtLock>> PtrToAutoLock;
	//3.上锁。
	PtrToAutoLock auto_lock;
	if(is_locked){
		auto_lock.reset(new MtAutoLock<MtLock>(_lock));
	}
	//4.计算当前日志文件名称。
	const CString name=(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d.log"));
	//5.判断当前文件流是否有错误，如果有则进行清除操作。
	if(_file.bad()||_file.fail()){
		_file.clear();
	}
	//6.设置当前语言域。
	std::locale old=std::locale::global(std::locale(""));
	//7.打开日志文件。
	_file.open(_directory+name,std::ios_base::out|std::ios_base::app);
	//8.恢复当前语言域。
	std::locale::global(old);
	//9.检测当前日志文件打开是否成功。
	if(_file.fail()){
		return(-1);
	}
	//10.程序运行到此成功返回。
	return(0);
}

/**
 * name: close
 * brief: 关闭当前日志。
 * param: is_locked - 输入的是否上锁标记。
 * return: --
 */
void MtLog::close(const BOOL is_locked/*=TRUE*/){
	//1.定义。
	typedef std::auto_ptr<MtAutoLock<
		MtLock>> PtrToAutoLock;
	//2.上锁。
	PtrToAutoLock auto_lock;
	if(is_locked){
		auto_lock.reset(new MtAutoLock<MtLock>(_lock));
	}
	//3.判断当前文件流是否有错误，如果有则进行清除操作。
	if(_file.bad()||_file.fail()){
		_file.clear();
	}
	//4.如果当前文件流处于打开状态，则进行关闭操作。
	if(_file.is_open()){
		//4-1.强制刷新缓冲区。
		_file.flush();
		//4-2.如果当前文件流是否有错误，如果有则进行清除操作。
		if(_file.bad()||_file.fail()){
			_file.clear();
		}
		//4-3.关闭当前文件流。
		_file.close();
	}
}
