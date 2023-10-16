#pragma once

#include"HL7Segment.h"

/**
 * name: HL7QRFSegment
 * brief: ����HL7Э���еġ�QRF���Σ���Ҫ��������ַ�������
 *        HL7QRFSegment�������ݣ��Լ�����HL7QRFSegment
 *        ������������HL7Э���ʽ���ַ�����
 * author: yameng_he
 * date: 2015-01-06
 */
class HL7QRFSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construcion & destruction
public:
	HL7QRFSegment(void);
	virtual ~HL7QRFSegment(void);
//interface
public:
	void set_facility_model(const String &facility_model);
	const String &get_facility_model() const;
	void set_specimen_receipt_start_date_time(
		const String &specimen_receipt_start_date_time);
	const String &get_specimen_receipt_start_date_time() const;
	void set_specimen_receipt_end_date_time(
		const String &specimen_receipt_end_date_time);
	const String &get_specimen_receipt_end_date_time() const;
	const String &get_target_type() const;
	const String &get_target_status() const;
	const String &get_date_Time_selection_qualifier() const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	String _facility_model;
	String _specimen_receipt_start_date_time;
	String _specimen_receipt_end_date_time;
	/*const*/ String _target_type;
	/*const*/ String _target_status;
	/*const*/ String _date_Time_selection_qualifier;
};