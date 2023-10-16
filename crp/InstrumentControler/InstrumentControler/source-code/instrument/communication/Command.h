#pragma once

class Port;

/**
 * name: Command
 * brief: 指令类，负责抽象描述一条指令。
 * author: yameng_he
 * date: 2016-01-26.
 */
class Command{
//define
public:
	enum{START_BIT=0x68,END_BIT=0x16,MIN_LENGTH=9,};
//construction & destruction
public:
	Command(void);
	Command(const unsigned char *command,const unsigned int size);
	~Command(void);
//interface
public:
	//指令操作。
	int analysis(Port &port) const;
	int send(Port &port,const CString &name=_T(""),
		const BOOL is_logged=TRUE) const;
	//指令生成。
	int generate_reaction_disc_rotation_command(
		const unsigned int hole_no,
		const unsigned int position);
	int generate_load_tong_take_tube_out_command(
		const unsigned int row,
		const unsigned int col);
	int generate_inquire_sensors_command();
	int generate_load_tong_put_tube_in_command();
	int generate_specimen_disc_rotation_command(
		const unsigned int rack_no,const unsigned int position_no);
	int generate_specimen_arm_suck_command(const unsigned int suck_volume,
		const unsigned int cup_type,const BOOL liquid_level_probe_switch);
	int generate_specimen_arm_spit_command(const unsigned int spit_volume,
		const unsigned int down_steps);
	int generate_specimen_arm_wash_command(const unsigned int outer_wash_time,
		const unsigned int inner_wash_time);
	int generate_reagent_arm_suck_command(const unsigned int suck_volume,
		const unsigned int reagent_type,const BOOL liquid_level_probe_switch);
	int generate_reagent_arm_spit_command(const unsigned int spit_volume,
		const unsigned int down_steps);
	int generate_reagent_arm_wash_command(const unsigned int outer_wash_time,
		const unsigned int inner_wash_time);
	int generate_reagent_disc_rotation_command(const unsigned int reagent_type,
		const unsigned int position_no);
	int generate_magnetic_bead_disc_rotation_command(const unsigned int position_no);
	int generate_magnetic_bead_disc_mixing_rotation_command(const unsigned int direction);
	int generate_washing_disc_rotation_command();
	int generate_detection_disc_rotation_command(
		const unsigned int hole_no,const unsigned int position);
	int generate_take_tube_out_of_detection_disc_command();
	int generate_discard_tube_command();
	int generate_washing_disc_wash_command(const unsigned int substrate_type,
		const unsigned int substrate_volume,const unsigned int washing_liquid_volume,
		const BOOL is_washing_position_1_need_washing,const BOOL is_washing_position_2_need_washing,
		const BOOL is_washing_position_3_need_washing,const BOOL is_washing_position_4_need_washing);
	int generate_take_tube_out_of_washing_disc_command(const unsigned int stop_position);
	int generate_return_tube_to_reaction_disc_command();
	int generate_put_tube_in_detection_disc_command();
	int generate_take_tube_out_of_reaction_disc_command();
	int generate_put_tube_in_washing_disc_command();
	int generate_detection_command();
//implement
private:
	int is_valid() const;
	int analysis_compound_command(Port &port) const;
	int analysis_compound_shake_handle_command() const;
	int analysis_compound_response_command() const;
	int analysis_inquire_command(Port &port) const;
	int analysis_inquire_response_command() const;
	int generate_reaction_disc_rotation_shake_hand_command();
	int generate_reaction_disc_rotation_response_command();
	int generate_load_tong_take_tube_out_shake_hand_command();
	int generate_load_tong_take_tube_out_response_command();
	int generate_inquire_sensors_response_command();
	int generate_load_tong_put_tube_in_shake_hand_command();
	int generate_load_tong_put_tube_in_response_command();
	int generate_specimen_disc_rotation_shake_hand_command();
	int generate_specimen_disc_rotation_response_command();
	int generate_specimen_arm_suck_shake_hand_command();
	int generate_specimen_arm_suck_response_command();
	int generate_specimen_arm_spit_shake_hand_command();
	int generate_specimen_arm_spit_response_command();
	int generate_specimen_arm_wash_shake_hand_command();
	int generate_specimen_arm_wash_response_command();
	int generate_reagent_arm_suck_shake_hand_command();
	int generate_reagent_arm_suck_response_command();
	int generate_reagent_arm_spit_shake_hand_command();
	int generate_reagent_arm_spit_response_command();
	int generate_reagent_arm_wash_shake_hand_command();
	int generate_reagent_arm_wash_response_command();
	int generate_reagent_disc_rotation_shake_hand_command();
	int generate_reagent_disc_rotation_response_command();
	int generate_magnetic_bead_disc_rotation_shake_hand_command();
	int generate_magnetic_bead_disc_rotation_response_command();
	int generate_magnetic_bead_disc_mixing_rotation_shake_hand_command();
	int generate_magnetic_bead_disc_mixing_rotation_response_command();
	int generate_washing_disc_rotation_shake_hand_command();
	int generate_washing_disc_rotation_response_command();
	int generate_detection_disc_rotation_shake_hand_command();
	int generate_detection_disc_rotation_response_command();
	int generate_take_tube_out_of_detection_disc_shake_hand_command();
	int generate_take_tube_out_of_detection_disc_response_command();
	int generate_discard_tube_shake_hand_command();
	int generate_discard_tube_response_command();
	int generate_washing_disc_wash_shake_hand_command();
	int generate_washing_disc_wash_response_command();
	int generate_take_tube_out_of_washing_disc_shake_hand_command();
	int generate_take_tube_out_of_washing_disc_response_command();
	int generate_return_tube_to_reaction_disc_shake_hand_command();
	int generate_return_tube_to_reaction_disc_response_command();
	int generate_put_tube_in_detection_disc_shake_hand_command();
	int generate_put_tube_in_detection_disc_response_command();
	int generate_take_tube_out_of_reaction_disc_shake_hand_command();
	int generate_take_tube_out_of_reaction_disc_response_command();
	int generate_put_tube_in_washing_disc_shake_hand_command();
	int generate_put_tube_in_washing_disc_response_command();
	int generate_detection_shake_hand_command();
	int generate_detection_response_command();
	CString get_string() const;
//restriction
private:
	Command(const Command &);
	Command &operator=(const Command &);
//variables
private:
	unsigned int _size;
	unsigned char *_command;
};

