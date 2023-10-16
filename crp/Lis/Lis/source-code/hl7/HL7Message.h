#pragma once

#include<memory>
#include<vector>

class HL7Segment;

/**
 * name: HL7Message
 * brief: 描述HL7协议中，“消息”信息。抽象类，它是
 *        系统中所有“消息”信息的基类。
 * author: yameng_he
 * date: 2014-12-19
 */
class HL7Message{
//define
public:
	static const Char START_CHARACTER;
	static const Char FIRST_END_CHARACTER;
	static const Char SECOND_END_CHARACTER;
	typedef std::shared_ptr<HL7Segment> PtrToSegment;
	typedef std::shared_ptr<const HL7Segment> PtrToCSegment;
	typedef std::vector<PtrToSegment> SegmentVector;
//construction & destruction
public:
	HL7Message(void);
	virtual ~HL7Message(void);
//interface
public:
	int add_segment(PtrToSegment &segment);
	unsigned int size_of_segments() const;
	void clear_segments();
	PtrToCSegment get_segment(const unsigned int no) const;
	int from_hl7(const String &hl7);
	String to_hl7() const;
//overrides
protected:
	virtual int are_segments_available() const=0;
	virtual int set_segment(const unsigned int no,const String &content)=0;
//variables
private:
	SegmentVector _segments;
};