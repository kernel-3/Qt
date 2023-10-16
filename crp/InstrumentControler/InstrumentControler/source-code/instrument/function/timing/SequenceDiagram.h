#pragma once

#include<memory>
#include<vector>

class Action;

/**
 * name: SequenceDiagram
 * brief: ʱ��ͼ�࣬��������һ��ʱ��ͼ��
 * author: yameng_he
 * date: 2015-12-29.
 */
class SequenceDiagram{
//define
public:
	typedef enum{
		ACTION_ID_REACTION_DISC_ROTATION=1,//��Ӧ����ת������
		ACTION_ID_PUT_TUBE_IN_REACTION_DISC,//�Źܵ���Ӧ�̶�����
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,//���Թܲ�ȡ�ܶ�����
		ACTION_ID_SPECIMEN_ARM_SPIT,//�������¶�����
		ACTION_ID_SPECIMEN_ARM_SUCK,//��������������
		ACTION_ID_SPECIMEN_ARM_WASH,//������ϴ������
		ACTION_ID_SPECIMEN_DISC_ROTATION,//��������ת������
		ACTION_ID_REAGENT_ARM_SPIT,//�Լ����¶�����
		ACTION_ID_REAGENT_ARM_SUCK,//�Լ�����������
		ACTION_ID_REAGENT_ARM_WASH,//�Լ�����ϴ������
		ACTION_ID_REAGENT_DISC_ROTATION,//�Լ�����ת������
		ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,//������ת��������
		ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,//ת��ץ�ִӷ�Ӧ��ȡ�ܶ�����
		ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,//ת��ץ�ֻعܵ���Ӧ�̶�����
		ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,//����ϴ��ȡ�ܶ�����
		ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,//ת��ץ�ַŹܵ���ϴ�̶�����
		ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,//ת��ץ�ַŹܵ�����̶�����
		ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,//�Ӽ����ȡ�ܶ�����
		ACTION_ID_DISCARD_TUBE,//���ܶ�����
		ACTION_ID_WASHING_DISC_WASH,//��ϴ����ϴ������
		ACTION_ID_WASHING_DISC_ROTATION,//��ϴ����ת������
		ACTION_ID_DETECTION_DISC_ROTATION,//�������ת������
		ACTION_ID_DETECT,//��⶯����
	}ActionID;
	typedef std::shared_ptr<Action> PtrToAction;
	typedef std::vector<PtrToAction> Actions;
//construction & destruction
public:
	SequenceDiagram(void);
	~SequenceDiagram(void);
//interface
public:
	int trigger(const unsigned int trigger_time,
		unsigned int &trigger_error,unsigned int &test_item_key);
	int clear(const unsigned int test_item_key);
	int reset();
	PtrToAction get_action(const ActionID id,const unsigned int sub_id);
//implement
private:
	int init();
//restriction
private:
	SequenceDiagram(const SequenceDiagram &);
	SequenceDiagram &operator=(const SequenceDiagram &);
//variables
private:
	Actions _actions;
};