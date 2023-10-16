#pragma once

/**
 * name: Action
 * brief: ���������࣬���������豸��һ��������
 *        ����࣬�����豸ȫ�������Ļ��ࡣ
 * author: yameng_he
 * date: 2015-12-24
 */
class Action{
//define
public:
	enum{MAX_DEFEATS=5,};
	typedef enum{//��������״̬��
		STATUS_DISABLED,//��Ч�ģ������õġ�
		STATUS_ENABLED,//��Ч�ģ�����ġ�
		STATUS_DEFAULT,//Ĭ�ϵġ�
	}Status;
	typedef enum{//����ִ��״̬��
		STATE_WAIT,//�ȴ���
		STATE_RUN,//ִ�С�
		STATE_COMPLETE,//��ɡ�
	}State;
	typedef enum{//������롣
		ERROR_NONE,
		ERROR_UNKNOWN,//δ֪����
		ERROR_NOT_VALID,//������Ч��
		ERROR_TIMEOUT_T,//������ʱ��
		ERROR_SERIOUS_TIMEOUT,//�������س�ʱ��
		ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE,//�Թܲ��޹ܡ�
		ERROR_COMMUNICATION,//ͨѶ����
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT,//�Źܵ���Ӧ�̽���λʱ������ͻ��
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED,//�Źܵ���Ӧ�̽���λʧ�ܡ�
		ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC,//����ϴ��ȡ��ʱ,��Ӧλ�����޹ܡ�
		ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED,//����ϴ��ȡ��ʧ�ܡ�
		ERROR_RETURN_TUBE_TO_RECTION_DISC_FAILED,//�عܵ���Ӧ��ʧ�ܡ�
		ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC,//��ת��ץ�ִӷ�Ӧ��ȡ��ʱ����ⷴӦ�̳���λ���޹ܡ�
		ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT,//ת��ץ�ַŹܵ���ϴ��ʱ����⵽��ͻ��
		ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED,//ת��ץ�ִӷ�Ӧ��ȡ��ʧ�ܡ�
		ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED,//ת��ץ�ַŹܵ���ϴ��ʧ�ܡ�
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