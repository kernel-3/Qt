#pragma once

#include"HL7Segment.h"

/**
 * name: HL7MSHSegment
 * breif: 描述HL7协议中的“MSH”段，主要负责根据字符串生成
 *        HL7MSHSegment类中数据，以及根据HL7MSHSegment
 *        类中数据生成HL7协议格式的字符串。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7MSHSegment
	:public HL7Segment{
//define
public:
	static const String SegmentName;
//construction & destruction
public:
	HL7MSHSegment(void);
	virtual ~HL7MSHSegment(void);
//interface
public:
	const String &get_separator() const;
	void set_sending_application(const String &sending_application);
	const String &get_sending_application() const;
	void set_sending_facility(const String &sending_facility);
	const String &get_sending_facility() const;
	void set_receiving_application(const String &receiving_application);
	const String &get_receiving_application() const;
	void set_receiving_facility(const String &receiving_facility);
	const String &get_receiving_facility() const;
	void set_message_date_time(const String &message_date_time);
	const String &get_message_date_time() const;
	void set_message_type(const String &message_type);
	const String &get_message_type() const;
	void set_message_control_id(const String &message_control_id);
	const String &get_message_control_id() const;
	const String &get_processing_id() const;
	const String &get_version_id() const;
	void set_accept_acknowledgment_type(const String &accept_acknowledgment_type);
	const String &get_accept_acknowledgment_type() const;
	void set_application_acknowledgment_type(const String &application_acknowledgment_type);
	const String &get_application_acknowledgment_type() const;
	void set_application_acknowledgment_type_with_number(const unsigned int application_acknowledgment_type);
	unsigned int get_application_acknowledgment_type_with_number() const;
	const String &get_character_set() const;
//overrides interface
protected:
	virtual int set_field(const unsigned int no,const String &content);
	virtual int get_field(const unsigned int no,String &content) const;
//variables
private:
	/*const*/ String _separator;//必须
	String _sending_application;
	String _sending_facility;
	String _receiving_application;
	String _receiving_facility;
	String _message_date_time;
	String _message_type;//必须。
	String _message_control_id;//必须。
	/*const*/ String _processing_id;//必须。
	/*const*/ String _version_id;//必须。
	String _accept_acknowledgment_type;
	String _application_acknowledgment_type;
	/*const*/ String _character_set;
};