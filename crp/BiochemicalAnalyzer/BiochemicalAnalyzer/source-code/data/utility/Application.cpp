#include"stdafx.h"
#include"Application.h"
#include"../common/Item.h"
#include"AnalyzeApplication.h"
#include"../../global/Database.h"
#include"CalibrationApplication.h"
#include"RangeApplication.h"
#include"StandardApplication.h"

/**
 * name: Application
 * breif: ���캯����
 * param: --
 * return: --
 */
Application::Application(void)
	:_item(new Item)
	,_analyze(new AnalyzeApplication)
	,_calibration(new CalibrationApplication)
	,_range(new RangeApplication)
	,_standard(new StandardApplication){
}

/**
 * name: Application
 * breif: �������캯����
 * param: source - ����Դʵ����
 * return: --
 */
Application::Application(const Application &source)
	:_item(new Item(*source._item))
	,_analyze(new AnalyzeApplication(*source._analyze))
	,_calibration(new CalibrationApplication(*source._calibration))
	,_range(new RangeApplication(*source._range))
	,_standard(new StandardApplication(*source._standard)){
}

/**
 * name: ~Application
 * breif: ����������
 * param: --
 * return: --
 */
Application::~Application(void){
	delete _item;
	delete _analyze;
	delete _calibration;
	delete _range;
	delete _standard;
}

/**
 * name: operator=
 * brief: ���ظ�ֵ��������
 * param: source - ��ֵԴʵ����
 * return: ���ص�ǰʵ�����á�
 */
Application &Application::operator=(const Application &source){
	*_item=*source._item;
	*_analyze=*source._analyze;
	*_calibration=*source._calibration;
	*_range=*source._range;
	*_standard=*source._standard;
	return(*this);
}

/**
 * name: get_item
 * brief: ��ȡ��ǰ��������е���Ŀ��Ϣ��
 * param: --
 * return: ���ص�ǰ��������е���Ŀ��Ϣ��
 */
Item &Application::get_item(){
	return(*_item);
}

/**
 * name: get_item
 * brief: ��ȡ��ǰ��������е���Ŀ��Ϣ��
 * param: --
 * return: ���ص�ǰ��������е���Ŀ��Ϣ��
 */
const Item &Application::get_item() const{
	return(const_cast<Application*>(this)->get_item());
}

/**
 * name: get_analyze
 * brief: ��ȡ��ǰ��������еķ�����Ϣ��
 * param: --
 * return: ���ص�ǰ��������еķ�����Ϣ��
 */
AnalyzeApplication &Application::get_analyze(){
	return(*_analyze);
}

/**
 * name: get_analyze
 * brief: ��ȡ��ǰ��������еķ�����Ϣ��
 * param: --
 * return: ���ص�ǰ��������еķ�����Ϣ��
 */
const AnalyzeApplication &Application::get_analyze() const{
	return(const_cast<Application*>(this)->get_analyze());
}

/**
 * name: get_calibration
 * brief: ��ȡ��ǰ��������еĶ�����Ϣ��
 * param: --
 * return: ���ص�ǰ��������еĶ�����Ϣ��
 */
CalibrationApplication &Application::get_calibration(){
	return(*_calibration);
}

/**
 * name: get_calibration
 * brief: ��ȡ��ǰ��������еĶ�����Ϣ��
 * param: --
 * return: ���ص�ǰ��������еĶ�����Ϣ��
 */
const CalibrationApplication &Application::get_calibration() const{
	return(const_cast<Application*>(this)->get_calibration());
}

/**
 * name: get_range
 * brief: ��ȡ��ǰ��������еķ�Χ��Ϣ��
 * param: --
 * return: ���ص�ǰ��������еķ�Χ��Ϣ��
 */
RangeApplication &Application::get_range(){
	return(*_range);
}

/**
 * name: get_range
 * brief: ��ȡ��ǰ��������еķ�Χ��Ϣ��
 * param: --
 * return: ���ص�ǰ��������еķ�Χ��Ϣ��
 */
const RangeApplication &Application::get_range() const{
	return(const_cast<Application*>(this)->get_range());
}

/**
 * name: get_standard
 * brief: ��ȡ��������еı�׼��Ϣ��
 * param: --
 * return: ������������еı�׼��Ϣ��
 */
StandardApplication &Application::get_standard(){
	return(*_standard);
}

/**
 * name: get_standard
 * brief: ��ȡ��������еı�׼��Ϣ��
 * param: --
 * return: ������������еı�׼��Ϣ��
 */
const StandardApplication &Application::get_standard() const{
	return(const_cast<Application*>(this)->get_standard());
}

/**
 * name: commit
 * brief: ����ǰ��������ύ�����ݿ��С�
 * param: method - �ύ������
 *        database - ָ�������ݿ⡣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Application::commit(const CommitMethod &method,Database &database) const{
	//1.�����ύ�������񣬲����жϿ����Ƿ�ɹ���
	if(database.begin_trans()<0){
		return(-1);
	}
	//2.�����ݿ��ύ��Ŀ��Ϣ�������ж��ύ�Ƿ�ɹ���
	if(_item->commit(static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-2);
	}
	//3.�����ݿ��ύ������Ϣ�������ж��ύ�Ƿ�ɹ���
	if(_analyze->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-3);
	}
	//4.�����ݿ��ύ������Ϣ�������ж��ύ�Ƿ�ɹ���
	if(_calibration->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-4);
	}
	//5.�����ݿ��ύ��Χ��Ϣ�������ж��ύ�Ƿ�ɹ���
	if(_range->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-5);
	}
	//6.�����ݿ����ύ��׼��Ϣ�������ύ�Ƿ�ɹ���
	if(_standard->commit(_item->get_id(),static_cast<int>(method),database)<0){
		database.rollback_trans();
		return(-6);
	}
	//7.�����ݿ��ύ���񣬲����ж��ύ�Ƿ�ɹ���
	if(database.commit_trans()<0){
		database.rollback_trans();
		return(-7);
	}
	//8.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: update
 * breif: ��ָ���ļ�¼���и��µ�ǰ�����������
 * param: record - ָ���ļ�¼����
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Application::update(MtADORecordset &record){
	//1.��ָ���ļ�¼�и�����Ŀ��Ϣ��
	if(_item->update(record)<0){
		return(-1);
	}
	//2.��ָ���ļ�¼�и��·�����Ϣ��
	if(_analyze->update(record)<0){
		return(-2);
	}
	//3.��ָ���ļ�¼�и��¶�����Ϣ��
	if(_calibration->update(record)<0){
		return(-3);
	}
	//4.��ָ���ļ�¼�и��·�Χ��Ϣ��
	if(_range->update(record)<0){
		return(-4);
	}
	//5.��ָ���ļ�¼�и��±�׼��Ϣ��
	if(_standard->update(record)<0){
		return(-5);
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}