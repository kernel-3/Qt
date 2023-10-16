#pragma once

#include"Action.h"

/**
 * name: WashingDiscWash
 * breif: ÇëÏ´ÅÌÇëÏ´¶¯×÷£¨ÇåÏ´Õ¾ÇåÏ´+»ìÔÈ+¼Óµ×Îï£©¡£
 * author: yameng_he
 * date: 2016-01-25.
 */
class WashingDiscWash
	:public Action{
//construction & destruction
public:
	WashingDiscWash(
		const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~WashingDiscWash(void);
//interface
public:
	void set_substrate_type(const unsigned int substrate_type);
	unsigned int get_substrate_type() const;
	void set_substrate_volume(const unsigned int substrate_volume);
	unsigned int get_substrate_volume() const;
//overrides
public:
	virtual int clear();
	virtual int reset();
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status);
	virtual int complete(const Status status);
//variables
private:
	BOOL _washing_flag;
	unsigned int _substrate_type;
	unsigned int _substrate_volume;
};

