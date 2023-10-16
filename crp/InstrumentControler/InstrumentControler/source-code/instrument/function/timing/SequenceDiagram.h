#pragma once

#include<memory>
#include<vector>

class Action;

/**
 * name: SequenceDiagram
 * brief: 时序图类，负责描述一副时序图。
 * author: yameng_he
 * date: 2015-12-29.
 */
class SequenceDiagram{
//define
public:
	typedef enum{
		ACTION_ID_REACTION_DISC_ROTATION=1,//反应盘旋转动作。
		ACTION_ID_PUT_TUBE_IN_REACTION_DISC,//放管到反应盘动作。
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,//从试管仓取管动作。
		ACTION_ID_SPECIMEN_ARM_SPIT,//样本臂吐动作。
		ACTION_ID_SPECIMEN_ARM_SUCK,//样本臂吸动作。
		ACTION_ID_SPECIMEN_ARM_WASH,//样本臂洗动作。
		ACTION_ID_SPECIMEN_DISC_ROTATION,//样本盘旋转动作。
		ACTION_ID_REAGENT_ARM_SPIT,//试剂臂吐动作。
		ACTION_ID_REAGENT_ARM_SUCK,//试剂臂吸动作。
		ACTION_ID_REAGENT_ARM_WASH,//试剂臂清洗动作。
		ACTION_ID_REAGENT_DISC_ROTATION,//试剂盘旋转动作。
		ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,//磁珠盘转动动作。
		ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,//转运抓手从反应盘取管动作。
		ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,//转运抓手回管到反应盘动作。
		ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,//从清洗盘取管动作。
		ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,//转运抓手放管到清洗盘动作。
		ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,//转运抓手放管到检测盘动作。
		ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,//从检测盘取管动作。
		ACTION_ID_DISCARD_TUBE,//丢管动作。
		ACTION_ID_WASHING_DISC_WASH,//清洗盘清洗动作。
		ACTION_ID_WASHING_DISC_ROTATION,//清洗盘旋转动作。
		ACTION_ID_DETECTION_DISC_ROTATION,//检测盘旋转动作。
		ACTION_ID_DETECT,//检测动作。
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