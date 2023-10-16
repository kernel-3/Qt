#include"stdafx.h"
#include"TubeStorehouse.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../common/Inis.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TubeStorehouse
 * brief: 构造函数。
 * param: --
 * return: --
 */
TubeStorehouse::TubeStorehouse(void)
	:Component()
	,_lock(new MtLock)
	,_tube_count(0){
	//1.读取当前耗材库试管数量。
	int tube_count=Inis::instance()->read(
		Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
		_T("TUBE_COUNT"));
	//2.如果读取值非法，则恢复其合法值。
	if(tube_count<0){
		tube_count=0;
	}else if(tube_count>static_cast<int>(
		ROW_COUNT*COL_COUNT)){
		tube_count=static_cast<int>(
			ROW_COUNT*COL_COUNT);
	}
	//3.保存从文件中读取的试管数量。
	_tube_count=static_cast<int>(tube_count);
}

/**
 * name: ~TubeStorehouse
 * brief: 析构函数。
 * param: --
 * return: --
 */
TubeStorehouse::~TubeStorehouse(void){
	delete _lock;
}

/**
 * name: are_there_tubes
 * brief: 检测当前耗材库中是否有管。
 * param: --
 * return: 如果当前耗材库中无管返回FALSE，
 *         如果当前耗材库中有管返回TRUE。
 */
BOOL TubeStorehouse::are_there_tubes() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前试管计数为零，则直接返回。
	if(0==_tube_count){
		return(FALSE);
	}
	//3.如果当前试管计数显示有管。
	else{
		return(TRUE);
	}
}

/**
 * name: get_tube_position
 * brief: 获取耗材库中当前管的位置。
 * param: row - 输出的管位置中的行信息。
 *        col - 输出的管位置中的列信息。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TubeStorehouse::get_tube_position(unsigned int &row,unsigned int &col) const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前耗材库无管，则直接返回错误。
	if(0==_tube_count){
		return(-1);
	}
	//3.如果当前耗材库中有管，则计算当前管的行、列信息。
	else{
		//3-1.根据当前剩余管的数量，计算耗材库当前管的行、列位置。
		const unsigned int tube_count=(
			ROW_COUNT*COL_COUNT)-_tube_count+1;
		unsigned int row_t=tube_count/COL_COUNT;
		unsigned int col_t=tube_count%COL_COUNT;
		if(col_t>0){
			++row_t;
		}else if(0==col_t){
			col_t=COL_COUNT;
		}
		//3-2.记录耗材库当前管的行、列位置。
		row=row_t;
		col=col_t;
		//3-3.程序运行到此成功返回。
		return(0);
	}
}

/**
 * name: decrease_tube_count
 * brief: 减少当前耗材库试管计数。
 * param: --
 * return: --
 */
void TubeStorehouse::decrease_tube_count(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前耗材库试管计数为零（不能再减）。
	if(0==_tube_count){
	}
	//3.递减当前耗材库试管计数。
	else{
		//3-1.递减当前耗材库试管计数。
		--_tube_count;
		//3-2.将当前耗材库试管计数，写入到文件中。
		const BOOL write_result=Inis::instance()->write(
			Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
			_T("TUBE_COUNT"),_tube_count);
		//3-3.如果当前耗材库试管计数文件写入失败，则输出错误日志。
		if(!write_result){
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： TubeStorehouse::decrease_tube_count \
函数中，调用 Inis::write 失败！"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
		}
	}
}

/**
 * name: clear_tube_count
 * brief: 清空试管仓剩余计数。
 * param: --
 * return: --
 */
void TubeStorehouse::clear_tube_count(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前试管仓试管计数为零。
	if(0==_tube_count){
	}
	//3.如果当前试管仓试管计数不为零。
	else{
		//3-1.清空试管计数。
		_tube_count=0;
		//3-2.将当前耗材库试管计数，写入到文件中。
		const BOOL write_result=Inis::instance()->write(
			Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
			_T("TUBE_COUNT"),_tube_count);
		//3-3.如果当前耗材库试管计数文件写入失败，则输出错误日志。
		if(!write_result){
			CString log(_T(""));
			log.Format(_T("Error %s（%ld）： TubeStorehouse::clear_tube_count \
函数中，调用 Inis::write 失败！"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
		}
	}
}