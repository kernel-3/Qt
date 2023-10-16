#pragma once

class Component;
class ReactionDisc;
class TubeStorehouse;
class LoadTong;
class SpecimenDisc;
class SpecimenArm;
class ReagentArm;
class ReagentDisc;
class MagneticBeadDisc;
class WashingDisc;
class DetectionDisc;
class TransportTong;

/**
 * name: Components
 * brief: 设备组件管理类，负责维护设备中全部的组件。
 * author: yameng_he
 * date: 2016-01-28.
 */
class Components{
//define
public:
	typedef enum{
		COMPONENT_ID_REACTION_DISC,
		COMPONENT_ID_TUBESTOREHOUSE,
		COMPONENT_ID_LOAD_TONG,
		COMPONENT_ID_SPECIMEN_DISC,
		COMPONENT_ID_SPECIMEN_ARM,
		COMPONENT_ID_REAGENT_ARM,
		COMPONENT_ID_REAGENT_DISC,
		COMPONENT_ID_MAGNETIC_BEAD_DISC,
		COMPONENT_ID_WASHING_DISC,
		COMPONENT_ID_DETECTION_DISC,
		COMPONENT_ID_TRANSPORT_TONG,
	}ComponentID;
//construction & destruction
public:
	Components(void);
	~Components(void);
//interface
public:
	ReactionDisc *get_reaction_disc();
	TubeStorehouse *get_tube_storehouse();
	LoadTong *get_load_tong();
	SpecimenDisc *get_specimen_disc();
	SpecimenArm *get_specimen_arm();
	ReagentArm *get_reagent_arm();
	ReagentDisc *get_reagent_disc();
	MagneticBeadDisc *get_magnetic_bead_disc();
	WashingDisc *get_washing_disc();
	DetectionDisc *get_detection_disc();
	TransportTong *get_transport_tong();
//implement
private:
	Component *get_component(const ComponentID component_id);
//restriction
private:
	Components(const Components &);
	Components &operator=(const Components &);
//variables
private:
	Component *_reaction_disc;
	Component *_tube_storehouse;
	Component *_load_tong;
	Component *_specimen_disc;
	Component *_specimen_arm;
	Component *_reagent_arm;
	Component *_reagent_disc;
	Component *_magnetic_bead_disc;
	Component *_washing_disc;
	Component *_detection_disc;
	Component *_transport_tong;
};