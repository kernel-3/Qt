#pragma once

#include"Component.h"

class MtLock;

/**
 * name: LoadTong
 * brief: 装载抓手类，负责抽象描述装载抓手，
 *        并且提供对装载抓手所有功能接口的
 *        封装。
 * author: yameng_he
 * date: 2016-02-16.
 */
class LoadTong:
	public Component{
//construction & destruction
public:
	LoadTong(void);
	virtual ~LoadTong(void);
//interface
public:
	int take_tube_out(const unsigned int row,const unsigned int col);
	int put_tube_in();
	void set_take_tube_out_shake_hand_flag(const Flag flag);
	Flag get_take_tube_out_shake_hand_flag() const;
	void set_take_tube_out_response_flag(const Flag flag);
	Flag get_take_tube_out_response_flag() const;
	void set_put_tube_in_shake_hand_flag(const Flag flag);
	Flag get_put_tube_in_shake_hand_flag() const;
	void set_put_tube_in_response_flag(const Flag flag);
	Flag get_put_tube_in_response_flag() const;
	void set_having_tube_flag(const BOOL flag);
	BOOL get_having_tube_flag() const;
//variables
private:
	MtLock *_lock;
	Flag _take_tube_out_shake_hand_flag;
	Flag _take_tube_out_response_flag;
	Flag _put_tube_in_shake_hand_flag;
	Flag _put_tube_in_response_flag;
	BOOL _having_tube_flag;
};

