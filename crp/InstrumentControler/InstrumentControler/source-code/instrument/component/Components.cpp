#include"stdafx.h"
#include"Components.h"
#include"ReactionDisc.h"
#include"TubeStorehouse.h"
#include"LoadTong.h"
#include"SpecimenDisc.h"
#include"SpecimenArm.h"
#include"ReagentArm.h"
#include"ReagentDisc.h"
#include"MagneticBeadDisc.h"
#include"WashingDisc.h"
#include"DetectionDisc.h"
#include"TransportTong.h"

/**
 * name: Components
 * brief: 构造函数。
 * param: --
 * return: --
 */
Components::Components(void)
	:_reaction_disc(new ReactionDisc)
	,_tube_storehouse(new TubeStorehouse)
	,_load_tong(new LoadTong)
	,_specimen_disc(new SpecimenDisc)
	,_specimen_arm(new SpecimenArm)
	,_reagent_arm(new ReagentArm)
	,_reagent_disc(new ReagentDisc)
	,_magnetic_bead_disc(new MagneticBeadDisc)
	,_washing_disc(new WashingDisc)
	,_detection_disc(new DetectionDisc)
	,_transport_tong(new TransportTong){
}

/**
 * name: ~Components
 * brief: 析构函数。
 * param: --
 * return: --
 */
Components::~Components(void){
	delete _reaction_disc;
	delete _tube_storehouse;
	delete _load_tong;
	delete _specimen_disc;
	delete _specimen_arm;
	delete _reagent_arm;
	delete _reagent_disc;
	delete _magnetic_bead_disc;
	delete _washing_disc;
	delete _detection_disc;
	delete _transport_tong;
}

/**
 * name: get_reaction_disc
 * breif: 获取反应盘。
 * param: --
 * return: 返回反应盘。
 */
ReactionDisc *Components::get_reaction_disc(){
	return(dynamic_cast<ReactionDisc*>(get_component(
		COMPONENT_ID_REACTION_DISC)));
}

/**
 * name: get_tube_storehouse
 * brief: 获取试管仓。
 * param: --
 * return: 返回试管仓。
 */
TubeStorehouse *Components::get_tube_storehouse(){
	return(dynamic_cast<TubeStorehouse*>(get_component(
		COMPONENT_ID_TUBESTOREHOUSE)));
}

/**
 * name: get_load_tong
 * brief: 获取装载抓手。
 * param: --
 * return: 返回装载抓手。
 */
LoadTong *Components::get_load_tong(){
	return(dynamic_cast<LoadTong*>(get_component(
		COMPONENT_ID_LOAD_TONG)));
}

/**
 * name: get_specimen_disc
 * breif: 获取样本盘。
 * param: --
 * return: 返回样本盘。
 */
SpecimenDisc *Components::get_specimen_disc(){
	return(dynamic_cast<SpecimenDisc*>(get_component(
		COMPONENT_ID_SPECIMEN_DISC)));
}

/**
 * name: get_specimen_arm
 * brief: 获取样本臂。
 * param: --
 * return: 返回样本臂。
 */
SpecimenArm *Components::get_specimen_arm(){
	return(dynamic_cast<SpecimenArm*>(get_component(
		COMPONENT_ID_SPECIMEN_ARM)));
}

/**
 * name: get_reagent_arm
 * brief: 获取试剂臂。
 * param: --
 * return: 返回试剂臂。
 */
ReagentArm *Components::get_reagent_arm(){
	return(dynamic_cast<ReagentArm*>(get_component(
		COMPONENT_ID_REAGENT_ARM)));
}

/**
 * name: get_reagent_disc
 * brief: 获取试剂盘。
 * param: --
 * return: 返回试剂盘。
 */
ReagentDisc *Components::get_reagent_disc(){
	return(dynamic_cast<ReagentDisc*>(get_component(
		COMPONENT_ID_REAGENT_DISC)));
}

/**
 * name: get_magnetic_bead_disc
 * breif: 获取磁珠盘。
 * param: --
 * return: 返回磁珠盘。
 */
MagneticBeadDisc *Components::get_magnetic_bead_disc(){
	return(dynamic_cast<MagneticBeadDisc*>(get_component(
		COMPONENT_ID_MAGNETIC_BEAD_DISC)));
}

/**
 * name: get_washing_disc
 * breif: 获取清洗盘。
 * param: --
 * return: 返回清洗盘。
 */
WashingDisc *Components::get_washing_disc(){
	return(dynamic_cast<WashingDisc*>(get_component(
		COMPONENT_ID_WASHING_DISC)));
}

/**
 * name: get_detection_disc
 * brief: 获取检测盘。
 * param: --
 * return: 返回检测盘。
 */
DetectionDisc *Components::get_detection_disc(){
	return(dynamic_cast<DetectionDisc*>(get_component(
		COMPONENT_ID_DETECTION_DISC)));
}

/**
 * name: get_transport_tong
 * brief: 获取转运抓手。
 * param: --
 * return: 返回转运抓手。
 */
TransportTong *Components::get_transport_tong(){
	return(dynamic_cast<TransportTong*>(get_component(
		COMPONENT_ID_TRANSPORT_TONG)));
}

/**
 * name: get_component
 * brief: 获取指定的组件。
 * param: component_id - 输入指定组件的标识。
 * return: 如果获取组件成功返回指向组件的指针，
 *         否则返回空指针。
 */
Component *Components::get_component(const ComponentID component_id){
	switch(component_id){
	case COMPONENT_ID_REACTION_DISC:
		return(_reaction_disc);
	case COMPONENT_ID_TUBESTOREHOUSE:
		return(_tube_storehouse);
	case COMPONENT_ID_LOAD_TONG:
		return(_load_tong);
	case COMPONENT_ID_SPECIMEN_DISC:
		return(_specimen_disc);
	case COMPONENT_ID_SPECIMEN_ARM:
		return(_specimen_arm);
	case COMPONENT_ID_REAGENT_ARM:
		return(_reagent_arm);
	case COMPONENT_ID_REAGENT_DISC:
		return(_reagent_disc);
	case COMPONENT_ID_MAGNETIC_BEAD_DISC:
		return(_magnetic_bead_disc);
	case COMPONENT_ID_WASHING_DISC:
		return(_washing_disc);
	case COMPONENT_ID_DETECTION_DISC:
		return(_detection_disc);
	case COMPONENT_ID_TRANSPORT_TONG:
		return(_transport_tong);
	default:
		return(0);
	}
}