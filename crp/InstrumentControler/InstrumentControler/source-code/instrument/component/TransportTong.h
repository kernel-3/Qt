#pragma once

#include"Component.h"

class MtLock;

/**
 * name: TransportTong
 * breif: 转运抓手类，负责抽象、描述转运抓手，并
 *        提供与转运抓手相关的所有接口。
 * author: yameng_he
 * date: 2016-02-24.
 */
class TransportTong
	:public Component{
//define
public:
	typedef enum{
		STOP_POSITION_REACTION_DISC=0,//反应盘。
		STOP_POSITION_DETECTION_DISC=1,//检测盘。
	}StopPosition;
//construction & destruction
public:
	TransportTong(void);
	virtual ~TransportTong(void);
//interface
public:
	int take_tube_out_of_detection_disc();
	int discard_tube();
	int take_tube_out_of_washing_disc(const StopPosition stop_position);
	int return_tube_to_reaction_disc();
	int put_tube_in_detection_disc();
	int take_tube_out_of_reaction_disc();
	int put_tube_in_washing_disc();
	void set_take_tube_out_of_detection_disc_shake_hand_flag(const Flag flag);
	Flag get_take_tube_out_of_detection_disc_shake_hand_flag() const;
	void set_take_tube_out_of_detection_disc_response_flag(const Flag flag);
	Flag get_take_tube_out_of_detection_disc_response_flag() const;
	void set_discard_tube_shake_hand_flag(const Flag flag);
	Flag get_discard_tube_shake_hand_flag() const;
	void set_discard_tube_response_flag(const Flag flag);
	Flag get_discard_tube_response_flag() const;
	void set_take_tube_out_of_washing_disc_shake_hand_flag(const Flag flag);
	Flag get_take_tube_out_of_washing_disc_shake_hand_flag() const;
	void set_take_tube_out_of_washing_disc_response_flag(const Flag flag);
	Flag get_take_tube_out_of_washing_disc_response_flag() const;
	void set_return_tube_to_reaction_disc_shake_hand_flag(const Flag flag);
	Flag get_return_tube_to_reaction_disc_shake_hand_flag() const;
	void set_return_tube_to_reaction_disc_response_flag(const Flag flag);
	Flag get_return_tube_to_reaction_disc_response_flag() const;
	void set_put_tube_in_detection_disc_shake_hand_flag(const Flag flag);
	Flag get_put_tube_in_detection_disc_shake_hand_flag() const;
	void set_put_tube_in_detection_disc_response_flag(const Flag flag);
	Flag get_put_tube_in_detection_disc_response_flag() const;
	void set_take_tube_out_of_reaction_disc_shake_hand_flag(const Flag flag);
	Flag get_take_tube_out_of_reaction_disc_shake_hand_flag() const;
	void set_take_tube_out_of_reaction_disc_response_flag(const Flag flag);
	Flag get_take_tube_out_of_reaction_disc_response_flag() const;
	void set_put_tube_in_washing_disc_shake_hand_flag(const Flag flag);
	Flag get_put_tube_in_washing_disc_shake_hand_flag() const;
	void set_put_tube_in_washing_disc_response_flag(const Flag flag);
	Flag get_put_tube_in_washing_disc_response_flag() const;
//variables
private:
	MtLock *_lock;
	Flag _take_tube_out_of_detection_disc_shake_hand_flag;
	Flag _take_tube_out_of_detection_disc_response_flag;
	Flag _discard_tube_shake_hand_flag;
	Flag _discard_tube_response_flag;
	Flag _take_tube_out_of_washing_disc_shake_hand_flag;
	Flag _take_tube_out_of_washing_disc_response_flag;
	Flag _return_tube_to_reaction_disc_shake_hand_flag;
	Flag _return_tube_to_reaction_disc_response_flag;
	Flag _put_tube_in_detection_disc_shake_hand_flag;
	Flag _put_tube_in_detection_disc_response_flag;
	Flag _take_tube_out_of_reaction_disc_shake_hand_flag;
	Flag _take_tube_out_of_reaction_disc_response_flag;
	Flag _put_tube_in_washing_disc_shake_hand_flag;
	Flag _put_tube_in_washing_disc_response_flag;
};

