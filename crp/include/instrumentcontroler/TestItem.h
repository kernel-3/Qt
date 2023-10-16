#pragma once

#include"Symbol"

class SequenceDiagram;

/**
 * name: TestItem
 * brief: 测试项目类，负责描述一个测试项目，维护并管理
 *        与测试项目相关的全部数据，提供与测试项目相关
 *        的全部接口。
 * author: yameng_he
 * date: 2016-02-29.
 */
class INSTRUMENT_CONTROLER_API TestItem{
//define
public:
	typedef enum{
		TEST_STEP_UNKNOWN=0,
		TEST_STEP_ENTRY_TUBE,
		TEST_STEP_ADD_SPECIMEN,
		TEST_STEP_ADD_R1,
		TEST_STEP_ADD_R2,
		TEST_STEP_ADD_R3,
		TEST_STEP_ADD_R4,
		TEST_STEP_ADD_MAGNETIC_BEAD,
		TEST_STEP_INCUBATE,
		TEST_STEP_WASH,
		TEST_STEP_ADD_SUBSTRATE_AB,
		TEST_STEP_ADD_SUBSTRATE_C,
		TEST_STEP_ADD_BUFFER_SOLUTION,
		TEST_STEP_RETURN_TUBE,
		TEST_STEP_DETECT,
	}TestStep;
	typedef enum{
		SPECIMEN_CUP_TYPE_STANDARD=0,
		SPECIMEN_CUP_TYPE_TUBE=1,
		SPECIMEN_CUP_TYPE_MICROSCALE=2,
	}SpecimenCupType;
	typedef enum{
		REAGENT_TYPE_R1=1,
		REAGENT_TYPE_R2=2,
		REAGENT_TYPE_R3=3,
		REAGENT_TYPE_R4=4,
	}ReagentType;
	typedef enum{
		SUBSTRATE_TYPE_AB=1,
		SUBSTRATE_TYPE_C=2,
		SUBSTRATE_TYPE_BUFFER_SOLUTION=3,
	}SubstrateType;
	enum{REAGENT_TYPE_COUNT=10,MAXIMUM_INCUBATION_TIMES=10,
		SUBSTRATE_TYPE_COUNT=10,MAXIMUM_TEST_STEPS=50,};
//construction & destruction
public:
	TestItem(void);
	TestItem(const TestItem &source);
	~TestItem(void);
//interface
public:
	void set_key(const unsigned int key);
	unsigned int get_key() const;
	void set_serial_number(const CString serial_number);
	CString get_serial_number() const;
	void set_hole_no_in_reaction_disc(const unsigned int hole_no);
	unsigned int get_hole_no_in_reaction_disc() const;
	void set_complete_time(const CString complete_time);
	CString get_complete_time() const;
	void set_specimen_volume(const unsigned int volume);
	unsigned int get_specimen_volume() const;
	void set_specimen_rack_no(const unsigned int rack_no);
	unsigned int get_specimen_rack_no() const;
	void set_specimen_position_no(const unsigned int position_no);
	unsigned int get_specimen_position_no() const;
	void set_specimen_cup_type(const SpecimenCupType type);
	SpecimenCupType get_specimen_cup_type() const;
	void set_add_specimen_flag(const BOOL flag);
	BOOL get_add_specimen_flag() const;
	void set_reagent_volume(const ReagentType reagent_type,const unsigned int volume);
	unsigned int get_reagent_volume(const ReagentType reagent_type) const;
	void set_reagent_position_no(const ReagentType reagent_type,const unsigned int position_no);
	unsigned int get_reagent_position_no(const ReagentType reagent_type) const;
	void set_magnetic_bead_volume(const unsigned int volume);
	unsigned int get_magnetic_bead_volume() const;
	void set_magnetic_bead_position_no(const unsigned int position_no);
	unsigned int get_magnetic_bead_position_no() const;
	void set_incubate_time(const unsigned int nth,const unsigned int time);
	unsigned int get_incubate_time(const unsigned int nth) const;
	void set_substrate_volume(const SubstrateType substrate_type,const unsigned int volume);
	unsigned int get_substrate_volume(const SubstrateType substrate_type) const;
	void set_detection_incubation_time(const unsigned int time);
	unsigned int get_detection_incubation_time() const;
	void set_hole_no_in_detection_disc(const unsigned int hole_no);
	unsigned int get_hole_no_in_detection_disc() const;
	void set_luminous(const unsigned int luminous);
	unsigned int get_luminous() const;
	int add_test_step(const TestStep &test_step);
	int generate_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		const unsigned int current_sequence_diagram_index);
//overrides
public:
	TestItem &operator=(const TestItem &source);
//implement
private:
	unsigned int get_washing_times() const;
	int generate_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		const unsigned int current_sequence_diagram_index,
		const BOOL is_data_generated);
	int generate_entry_tube_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		const BOOL is_data_generated);
	int generate_add_specimen_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		unsigned int &liquid_volume_in_reaction_tube,
		const BOOL is_data_generated);
	int generate_add_reagent_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		const ReagentType reagent_type,
		unsigned int &current_sequence_diagram_index,
		unsigned int &liquid_volume_in_reaction_tube,
		const BOOL is_data_generated);
	int generate_add_magnetic_bead_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		unsigned int &liquid_volume_in_reaction_tube,
		const BOOL is_data_generated);
	int generate_incubate_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		unsigned int &nth_times_incubate,
		const BOOL is_data_generated);
	int generate_wash_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		unsigned int &nth_times_wash,
		const BOOL is_data_generated);
	int generate_add_substrate_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		const SubstrateType substrate_type,
		unsigned int &current_sequence_diagram_index,
		unsigned int &liquid_volume_in_reaction_tube,
		const BOOL is_data_generated);
	int generate_return_tube_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		const BOOL is_data_generated);
	int generate_detect_sequence_diagram(
		SequenceDiagram *sequence_diagram,
		const unsigned int sequence_diagram_count,
		unsigned int &current_sequence_diagram_index,
		const BOOL is_data_generated);
//variables
private:
	//test item
	unsigned int _key;
	CString _serial_number;
	unsigned int _hole_no_in_reaction_disc;
	CString _complete_time;
	//specimen
	unsigned int _specimen_volume;
	unsigned int _specimen_rack_no;
	unsigned int _specimen_position_no;
	SpecimenCupType _specimen_cup_type;
	BOOL _add_specimen_flag;
	//reagent
	unsigned int _reagent_volume[REAGENT_TYPE_COUNT];
	unsigned int _reagent_position_no[REAGENT_TYPE_COUNT];
	//magnetic bead
	unsigned int _magnetic_bead_volume;
	unsigned int _magnetic_bead_position_no;
	//incubation
	unsigned int _incubate_time[MAXIMUM_INCUBATION_TIMES];
	//washing
	unsigned int _washing_times;
	//substrate
	unsigned int _substrate_volume[SUBSTRATE_TYPE_COUNT];
	//detection
	unsigned int _detection_incubation_time;
	unsigned int _hole_no_in_detection_disc;
	unsigned int _luminous;
	//test steps
	unsigned int _test_step_count;
	TestStep _test_step[MAXIMUM_TEST_STEPS];
};
