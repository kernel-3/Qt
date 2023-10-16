#include"stdafx.h"
#include"TubeStorehouse.h"
#include"../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../common/Inis.h"
#include"../../common/Logs.h"
#include<MMSystem.h>

/**
 * name: TubeStorehouse
 * brief: ���캯����
 * param: --
 * return: --
 */
TubeStorehouse::TubeStorehouse(void)
	:Component()
	,_lock(new MtLock)
	,_tube_count(0){
	//1.��ȡ��ǰ�ĲĿ��Թ�������
	int tube_count=Inis::instance()->read(
		Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
		_T("TUBE_COUNT"));
	//2.�����ȡֵ�Ƿ�����ָ���Ϸ�ֵ��
	if(tube_count<0){
		tube_count=0;
	}else if(tube_count>static_cast<int>(
		ROW_COUNT*COL_COUNT)){
		tube_count=static_cast<int>(
			ROW_COUNT*COL_COUNT);
	}
	//3.������ļ��ж�ȡ���Թ�������
	_tube_count=static_cast<int>(tube_count);
}

/**
 * name: ~TubeStorehouse
 * brief: ����������
 * param: --
 * return: --
 */
TubeStorehouse::~TubeStorehouse(void){
	delete _lock;
}

/**
 * name: are_there_tubes
 * brief: ��⵱ǰ�ĲĿ����Ƿ��йܡ�
 * param: --
 * return: �����ǰ�ĲĿ����޹ܷ���FALSE��
 *         �����ǰ�ĲĿ����йܷ���TRUE��
 */
BOOL TubeStorehouse::are_there_tubes() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�Թܼ���Ϊ�㣬��ֱ�ӷ��ء�
	if(0==_tube_count){
		return(FALSE);
	}
	//3.�����ǰ�Թܼ�����ʾ�йܡ�
	else{
		return(TRUE);
	}
}

/**
 * name: get_tube_position
 * brief: ��ȡ�ĲĿ��е�ǰ�ܵ�λ�á�
 * param: row - ����Ĺ�λ���е�����Ϣ��
 *        col - ����Ĺ�λ���е�����Ϣ��
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TubeStorehouse::get_tube_position(unsigned int &row,unsigned int &col) const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�ĲĿ��޹ܣ���ֱ�ӷ��ش���
	if(0==_tube_count){
		return(-1);
	}
	//3.�����ǰ�ĲĿ����йܣ�����㵱ǰ�ܵ��С�����Ϣ��
	else{
		//3-1.���ݵ�ǰʣ��ܵ�����������ĲĿ⵱ǰ�ܵ��С���λ�á�
		const unsigned int tube_count=(
			ROW_COUNT*COL_COUNT)-_tube_count+1;
		unsigned int row_t=tube_count/COL_COUNT;
		unsigned int col_t=tube_count%COL_COUNT;
		if(col_t>0){
			++row_t;
		}else if(0==col_t){
			col_t=COL_COUNT;
		}
		//3-2.��¼�ĲĿ⵱ǰ�ܵ��С���λ�á�
		row=row_t;
		col=col_t;
		//3-3.�������е��˳ɹ����ء�
		return(0);
	}
}

/**
 * name: decrease_tube_count
 * brief: ���ٵ�ǰ�ĲĿ��Թܼ�����
 * param: --
 * return: --
 */
void TubeStorehouse::decrease_tube_count(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�ĲĿ��Թܼ���Ϊ�㣨�����ټ�����
	if(0==_tube_count){
	}
	//3.�ݼ���ǰ�ĲĿ��Թܼ�����
	else{
		//3-1.�ݼ���ǰ�ĲĿ��Թܼ�����
		--_tube_count;
		//3-2.����ǰ�ĲĿ��Թܼ�����д�뵽�ļ��С�
		const BOOL write_result=Inis::instance()->write(
			Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
			_T("TUBE_COUNT"),_tube_count);
		//3-3.�����ǰ�ĲĿ��Թܼ����ļ�д��ʧ�ܣ������������־��
		if(!write_result){
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� TubeStorehouse::decrease_tube_count \
�����У����� Inis::write ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
		}
	}
}

/**
 * name: clear_tube_count
 * brief: ����Թܲ�ʣ�������
 * param: --
 * return: --
 */
void TubeStorehouse::clear_tube_count(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�Թܲ��Թܼ���Ϊ�㡣
	if(0==_tube_count){
	}
	//3.�����ǰ�Թܲ��Թܼ�����Ϊ�㡣
	else{
		//3-1.����Թܼ�����
		_tube_count=0;
		//3-2.����ǰ�ĲĿ��Թܼ�����д�뵽�ļ��С�
		const BOOL write_result=Inis::instance()->write(
			Inis::NAME_INSTRUMENT,_T("STOREHOUSE"),
			_T("TUBE_COUNT"),_tube_count);
		//3-3.�����ǰ�ĲĿ��Թܼ����ļ�д��ʧ�ܣ������������־��
		if(!write_result){
			CString log(_T(""));
			log.Format(_T("Error %s��%ld���� TubeStorehouse::clear_tube_count \
�����У����� Inis::write ʧ�ܣ�"),(COleDateTime::GetCurrentTime()).Format(_T(
				"%Y-%m-%d %H:%M:%S")),timeGetTime());
			Logs::instance()->write(Logs::NAME_ERROR,log);
		}
	}
}