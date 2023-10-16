#pragma once

/**
 * name: Action
 * brief: 动作描述类，负责描述设备的一个动作，
 *        虚基类，它是设备全部动作的基类。
 * author: yameng_he
 * date: 2015-12-24
 */
class Action{
//define
public:
	enum{MAX_DEFEATS=5,};
	typedef enum{//动作所处状态。
		STATUS_DISABLED,//无效的，不启用的。
		STATUS_ENABLED,//有效的，激活的。
		STATUS_DEFAULT,//默认的。
	}Status;
	typedef enum{//动作执行状态。
		STATE_WAIT,//等待。
		STATE_RUN,//执行。
		STATE_COMPLETE,//完成。
	}State;
	typedef enum{//错误编码。
		ERROR_NONE,
		ERROR_UNKNOWN,//未知错误。
		ERROR_NOT_VALID,//动作无效。
		ERROR_TIMEOUT_T,//动作超时。
		ERROR_SERIOUS_TIMEOUT,//动作严重超时。
		ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE,//试管仓无管。
		ERROR_COMMUNICATION,//通讯错误。
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT,//放管到反应盘进管位时发生冲突。
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED,//放管到反应盘进管位失败。
		ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC,//从清洗盘取管时,相应位置上无管。
		ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED,//从清洗盘取管失败。
		ERROR_RETURN_TUBE_TO_RECTION_DISC_FAILED,//回管到反应盘失败。
		ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC,//当转运抓手从反应盘取管时，检测反应盘出管位到无管。
		ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT,//转运抓手放管到清洗盘时，检测到冲突。
		ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED,//转运抓手从反应盘取管失败。
		ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED,//转运抓手放管到清洗盘失败。
	}Error;
//construction & destruction
public:
	Action(const unsigned int id,
		const unsigned int sub_id,
		const unsigned int start_time,
		const unsigned int complete_time);
	virtual ~Action(void);
//interface
public:
	static unsigned int generate_key(
		const unsigned int id,const unsigned int sub_id);
//interface
public:
	unsigned int get_id() const;
	unsigned int get_sub_id() const;
	unsigned int get_key() const;
	unsigned int get_start_time() const;
	unsigned int get_complete_time() const;
	void set_state(const State state);
	State get_state() const;
	void set_status(const Status status);
	Status get_status() const;
	void set_error(const Error error);
	Error get_error() const;
	void increase_defeats();
	unsigned int get_defeats() const;
	void set_test_item_key(const unsigned int &test_item_key);
	unsigned int get_test_item_key() const;
	int trigger(const unsigned int time);
//overrides
public:
	virtual int clear();
	virtual int reset();
	virtual int is_valid() const;
//overrides
protected:
	virtual int execute(const Status status)=0;
	virtual int complete(const Status status)=0;
//variables
private:
	const unsigned int _id;
	const unsigned int _sub_id;
	const unsigned int _start_time;
	const unsigned int _complete_time;
	State _state;
	Status _status;
	Error _error;
	unsigned int _defeats;
	unsigned int _test_item_key;
};