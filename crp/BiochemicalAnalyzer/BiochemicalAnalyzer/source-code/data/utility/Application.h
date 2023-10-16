#pragma once

class Item;
class AnalyzeApplication;
class Database;
class MtADORecordset;
class CalibrationApplication;
class RangeApplication;
class StandardApplication;

/**
 * name: Application
 * brief: ��������࣬��������һ����Ŀ�����������������
 *        ���������������������Χ��������׼�����ȵȣ���
 * author: yameng_he
 * date: 2015-06-15
 */
class Application{
//define
public:
	typedef enum{COMMIT_METHOD_INSERT=1,
		COMMIT_METHOD_UPDATE=2,}CommitMethod;
//construction & destruction
public:
	Application(void);
	Application(const Application &source);
	~Application(void);
//interface
public:
	Application &operator=(const Application &source);
	Item &get_item();
	const Item &get_item() const;
	AnalyzeApplication &get_analyze();
	const AnalyzeApplication &get_analyze() const;
	CalibrationApplication &get_calibration();
	const CalibrationApplication &get_calibration() const;
	RangeApplication &get_range();
	const RangeApplication &get_range() const;
	StandardApplication &get_standard();
	const StandardApplication &get_standard() const;
	int commit(const CommitMethod &method,Database &database) const;
	int update(MtADORecordset &record);
//variables
private:
	Item *_item;
	AnalyzeApplication *_analyze;
	CalibrationApplication *_calibration;
	RangeApplication *_range;
	StandardApplication *_standard;
};