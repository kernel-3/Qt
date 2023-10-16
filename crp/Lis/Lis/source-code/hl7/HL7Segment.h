#pragma once

/**
 * name: HL7Segment
 * brief: 描述HL7协议中，“消息”的“段”信息。抽象类，
 *        它是系统中所有“段”信息的基类。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7Segment{
//define
public:
	static const Char END_CHARACTER;
	static const Char FIELD_SEPARATOR;
	static const Char GROUP_SEPARATOR;
//construction & destruction
public:
	HL7Segment(const String &name,const unsigned int field_amount);
	virtual ~HL7Segment(void);
//interface
public:
	const String &get_name() const;
	unsigned int get_field_amount() const;
	int from_hl7(const String &hl7);
	String to_hl7() const;
//interfaceD
protected:
	int extract_group_content_from_field_content(const String &field_content,
		String *group_content,const unsigned int group_content_amount) const;
//overrides
protected:
	virtual int set_field(const unsigned int no,const String &content)=0;
	virtual int get_field(const unsigned int no,String &content) const=0;
//variables
private:
	const String _name;
	const unsigned int _field_amount;
};