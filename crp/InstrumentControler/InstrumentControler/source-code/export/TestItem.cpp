#include"stdafx.h"
#include"TestItem.h"
#include"../instrument/function/timing/Timing.h"
#include"../instrument/function/timing/SequenceDiagram.h"
#include"../instrument/function/timing/ReactionDiscRotation.h"
#include"../instrument/function/timing/TakeTubeOutOfTubeStoreHouse.h"
#include"../instrument/function/timing/PutTubeInReactionDisc.h"
#include"../instrument/function/timing/SpecimenDiscRotation.h"
#include"../instrument/function/timing/SpecimenArmSuck.h"
#include"../instrument/function/timing/SpecimenArmSpit.h"
#include"../instrument/function/timing/SpecimenArmWash.h"
#include"../instrument/function/timing/ReagentDiscRotation.h"
#include"../instrument/function/timing/MagneticBeadDiscRotation.h"
#include"../instrument/function/timing/ReagentArmSuck.h"
#include"../instrument/function/timing/ReagentArmSpit.h"
#include"../instrument/function/timing/ReagentArmWash.h"
#include"../instrument/function/timing/WashingDiscRotation.h"
#include"../instrument/function/timing/DetectionDiscRotation.h"
#include"../instrument/function/timing/TakeTubeOutOfDetectionDisc.h"
#include"../instrument/function/timing/DiscardTube.h"
#include"../instrument/function/timing/WashingDiscWash.h"
#include"../instrument/function/timing/TakeTubeOutOfWashingDisc.h"
#include"../instrument/function/timing/ReturnTubeToReactionDisc.h"
#include"../instrument/function/timing/PutTubeInDetectionDisc.h"
#include"../instrument/function/timing/TakeTubeOutOfReactionDisc.h"
#include"../instrument/function/timing/PutTubeInWashingDisc.h"
#include"../instrument/Instrument.h"
#include"../instrument/component/Components.h"
#include"../instrument/component/ReactionDisc.h"
#include"../instrument/component/ReagentDisc.h"
#include"../instrument/component/ReagentArm.h"
#include"../instrument/component/MagneticBeadDisc.h"
#include"../instrument/component/WashingDisc.h"
#include"../instrument/component/TransportTong.h"
#include"../instrument/component/DetectionDisc.h"
#include"../common/Inis.h"
#include<assert.h>

/**
 * name: TestItem
 * breif: 构造函数。
 * param: --
 * return: --
 */
TestItem::TestItem(void)
	:_key(0)
	,_serial_number(_T(""))
	,_hole_no_in_reaction_disc(0)
	,_complete_time(_T(""))
	,_specimen_volume(0)
	,_specimen_rack_no(0)
	,_specimen_position_no(0)
	,_specimen_cup_type(SPECIMEN_CUP_TYPE_STANDARD)
	,_add_specimen_flag(FALSE)
	,_magnetic_bead_volume(0)
	,_magnetic_bead_position_no(0)
	,_washing_times(0)
	,_detection_incubation_time(0)
	,_hole_no_in_detection_disc(0)
	,_luminous(0)
	,_test_step_count(0){
	memset(_reagent_volume,0,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memset(_reagent_position_no,0,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memset(_incubate_time,0,MAXIMUM_INCUBATION_TIMES*sizeof(unsigned int));
	memset(_substrate_volume,0,SUBSTRATE_TYPE_COUNT*sizeof(unsigned int));
	memset(_test_step,TEST_STEP_UNKNOWN,MAXIMUM_TEST_STEPS*sizeof(TestStep));
}

/**
 * name: TestItem
 * brief: 拷贝构造函数。
 * param: source - 输入的拷贝源实例。
 * return: --
 */
TestItem::TestItem(const TestItem &source)
	:_key(source._key)
	,_serial_number(source._serial_number)
	,_hole_no_in_reaction_disc(source._hole_no_in_reaction_disc)
	,_complete_time(source._complete_time)
	,_specimen_volume(source._specimen_volume)
	,_specimen_rack_no(source._specimen_rack_no)
	,_specimen_position_no(source._specimen_position_no)
	,_specimen_cup_type(source._specimen_cup_type)
	,_add_specimen_flag(source._add_specimen_flag)
	,_magnetic_bead_volume(source._magnetic_bead_volume)
	,_magnetic_bead_position_no(source._magnetic_bead_position_no)
	,_washing_times(source._washing_times)
	,_detection_incubation_time(source._detection_incubation_time)
	,_hole_no_in_detection_disc(source._hole_no_in_detection_disc)
	,_luminous(source._luminous)
	,_test_step_count(source._test_step_count){
	memcpy(_reagent_volume,source._reagent_volume,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_reagent_position_no,source._reagent_position_no,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_incubate_time,source._incubate_time,MAXIMUM_INCUBATION_TIMES*sizeof(unsigned int));
	memcpy(_substrate_volume,source._substrate_volume,SUBSTRATE_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_test_step,source._test_step,MAXIMUM_TEST_STEPS*sizeof(TestStep));
}

/**
 * name: ~TestItem
 * brief: 析构函数。
 * param: --
 * return: --
 */
TestItem::~TestItem(void){
}

/**
 * name: set_key
 * brief: 设置当前测试项目主键。
 * param: key - 输入的当前测试项目主键。
 * return: --
 */
void TestItem::set_key(const unsigned int key){
	_key=key;
}

/**
 * name: get_key
 * brief: 获取当前测试项目主键。
 * param: --
 * return: 返回当前测试项目主键。
 */
unsigned int TestItem::get_key() const{
	return(_key);
}

/**
 * name: set_serial_number
 * brief: 设置测试项目的流水号。
 * param: serial_number - 输入测试项目的流水号。
 * return: --
 */
void TestItem::set_serial_number(const CString serial_number){
	_serial_number=serial_number;
}

/**
 * name: get_serial_number
 * brief: 获取测试项目的流水号。
 * param: --
 * return: 返回测试项目的流水号。
 */
CString TestItem::get_serial_number() const{
	return(_serial_number);
}

/**
 * name: set_hole_no_in_reaction_disc
 * brief: 设置反应盘上的孔号。
 * param: hole_no - 输入的反应盘上的孔号。
 * return: --
 */
void TestItem::set_hole_no_in_reaction_disc(const unsigned int hole_no){
	_hole_no_in_reaction_disc=hole_no;
}

/**
 * name: get_hole_no_in_reaction_disc
 * brief: 获取反应盘上的孔号。
 * param: --
 * return: 返回反应盘上的孔号。
 */
unsigned int TestItem::get_hole_no_in_reaction_disc() const{
	return(_hole_no_in_reaction_disc);
}

/**
 * name: set_complete_time
 * brief: 设置当前项目的完成时间。
 * param: complete_time - 输入的完成时间。
 * return: --
 */
void TestItem::set_complete_time(const CString complete_time){
	_complete_time=complete_time;
}

/**
 * name: get_complete_time
 * brief: 获取当前项目的完成时间。
 * param: --
 * return: 返回当前项目的完成时间。
 */
CString TestItem::get_complete_time() const{
	return(_complete_time);
}

/**
 * name: set_specimen_volume
 * brief: 设置样本体积。
 * param: volume - 输入的样本体积。
 * return: --
 */
void TestItem::set_specimen_volume(const unsigned int volume){
	_specimen_volume=volume;
}

/**
 * name: get_specimen_volume
 * brief: 获取样本体积。
 * param: --
 * return: 返回样本体积。
 */
unsigned int TestItem::get_specimen_volume() const{
	return(_specimen_volume);
}

/**
 * name: set_specimen_rack_no
 * brief: 设置样本架子号。
 * param: rack_no - 输入的样本架子号。
 * return: --
 */
void TestItem::set_specimen_rack_no(const unsigned int rack_no){
	_specimen_rack_no=rack_no;
}

/**
 * name: get_specimen_rack_no
 * brief: 获取样本架子号。
 * param: --
 * return: 返回样本架子号。
 */
unsigned int TestItem::get_specimen_rack_no() const{
	return(_specimen_rack_no);
}

/**
 * name: set_specimen_position_no
 * breif: 设置样本位置号。
 * param: position_no - 输入的样本位置号。
 * return: --
 */
void TestItem::set_specimen_position_no(const unsigned int position_no){
	_specimen_position_no=position_no;
}

/**
 * name: get_specimen_position_no
 * brief: 获取样本位置号。
 * param: --
 * return: 返回样本位置号。
 */
unsigned int TestItem::get_specimen_position_no() const{
	return(_specimen_position_no);
}

/**
 * name: set_specimen_cup_type
 * brief: 设置样本杯类型。
 * param: type - 输入的样本杯类型。
 * return: --
 */
void TestItem::set_specimen_cup_type(const SpecimenCupType type){
	_specimen_cup_type=type;
}

/**
 * name: get_specimen_cup_type
 * brief: 获取样本杯类型。
 * param: --
 * return: 返回样本杯类型。
 */
TestItem::SpecimenCupType TestItem::get_specimen_cup_type() const{
	return(_specimen_cup_type);
}

/**
 * name: set_add_specimen_flag
 * brief: 设置添加样本标志。
 * param: flag - 输入的添加样本标志（FALSE 样本尚未添加 TRUE 样本已经添加）。
 * return: --
 */
void TestItem::set_add_specimen_flag(const BOOL flag){
	_add_specimen_flag=flag;
}

/**
 * name: get_add_specimen_flag
 * brief: 获取添加样本标志。
 * param: --
 * return: 返回添加样本标志（FALSE 样本尚未添加 TRUE 样本已经添加）。
 */
BOOL TestItem::get_add_specimen_flag() const{
	return(_add_specimen_flag);
}

/**
 * name: set_reagent_volume
 * breif: 设置试剂体积。
 * param: reagent_type - 输入的试剂类型。
 *        volume - 输入的试剂体积。
 * return: --
 */
void TestItem::set_reagent_volume(
	const ReagentType reagent_type,const unsigned int volume){
	_reagent_volume[reagent_type-1]=volume;
}

/**
 * name: get_reagent_volume
 * brief: 获取试剂体积。
 * param: reagent_type - 输入的试剂类型。
 * return: 返回试剂体积。
 */
unsigned int TestItem::get_reagent_volume(
	const ReagentType reagent_type) const{
	return(_reagent_volume[reagent_type-1]);
}

/**
 * name: set_reagent_position_no
 * brief: 设置试剂位置号。
 * param: reagent_type - 输入的试剂类型。
 *        position_no - 输入的试剂位置号。
 * return: --
 */
void TestItem::set_reagent_position_no(
	const ReagentType reagent_type,const unsigned int position_no){
	_reagent_position_no[reagent_type-1]=position_no;
}

/**
 * name: get_reagent_position_no
 * brief: 获取试剂位置号。
 * param: reagent_type - 输入的试剂类型。
 * return: 返回试剂位置号。
 */
unsigned int TestItem::get_reagent_position_no(
	const ReagentType reagent_type) const{
	return(_reagent_position_no[reagent_type-1]);
}

/**
 * name: set_magnetic_bead_volume
 * brief: 设置磁珠体积。
 * param: volume - 输入的磁珠体积。
 * return: --
 */
void TestItem::set_magnetic_bead_volume(const unsigned int volume){
	_magnetic_bead_volume=volume;
}

/**
 * name: get_magnetic_bead_volume
 * brief: 获取磁珠体积。
 * param: --
 * return: 返回磁珠体积。
 */
unsigned int TestItem::get_magnetic_bead_volume() const{
	return(_magnetic_bead_volume);
}

/**
 * name: set_magnetic_bead_position_no
 * brief: 设置磁珠位置号。
 * param: position_no - 输入的磁珠位置号。
 * return: --
 */
void TestItem::set_magnetic_bead_position_no(const unsigned int position_no){
	_magnetic_bead_position_no=position_no;
}

/**
 * name: get_magnetic_bead_position_no
 * brief: 获取磁珠位置号。
 * param: --
 * return: 返回磁珠位置号。
 */
unsigned int TestItem::get_magnetic_bead_position_no() const{
	return(_magnetic_bead_position_no);
}

/**
 * name: set_incubate_time
 * brief: 设置温育时间。
 * param: nth - 输入的第n次温育标识（1~MAXIMUM_INCUBATION_TIMES）。
 *        time - 输入的温育时间。
 * return: --
 */
void TestItem::set_incubate_time(const unsigned int nth,const unsigned int time){
	//1.检测输入是否合法。
	assert((nth>=1)&&(nth<=MAXIMUM_INCUBATION_TIMES));
	//2.设置第n次温育的温育时间。
	_incubate_time[nth-1]=time;
}

/**
 * name: get_incubate_time
 * brief: 获取温育时间。
 * param: nth - 输入的第n次温育标识（1~MAXIMUM_INCUBATION_TIMES）。
 * return: 返回温育时间。
 */
unsigned int TestItem::get_incubate_time(const unsigned int nth) const{
	//1.检测输入是否合法。
	assert((nth>=1)&&(nth<=MAXIMUM_INCUBATION_TIMES));
	//2.返回温育时间。
	return(_incubate_time[nth-1]);
}

/**
 * name: set_substrate_volume
 * brief: 设置底物体积。
 * param: substrate_type - 输入的底物类型。
 *        volume - 输入的底物体积。
 * return: --
 */
void TestItem::set_substrate_volume(
	const SubstrateType substrate_type,const unsigned int volume){
	_substrate_volume[substrate_type-1]=volume;
}

/**
 * name: get_substrate_volume
 * brief: 获取底物体积。
 * param: substrate_type - 输入的底物类型。
 * return: 返回底物体积。
 */
unsigned int TestItem::get_substrate_volume(
	const SubstrateType substrate_type) const{
	if(SUBSTRATE_TYPE_BUFFER_SOLUTION==substrate_type){
		return(Inis::instance()->read(Inis::NAME_INSTRUMENT,
			_T("WASHINGDISC"),_T("BUFFER_SOLUTION_VOLUME")));
	}else{
		return(_substrate_volume[substrate_type-1]);
	}
}

/**
 * name: set_detection_incubation_time
 * brief: 设置检测孵育时间。
 * param: time - 输入的检测孵育时间。
 * return: --
 */
void TestItem::set_detection_incubation_time(const unsigned int time){
	_detection_incubation_time=time;
}

/**
 * name: get_detection_incubation_time
 * brief: 获取检测孵育时间。
 * param: --
 * return: 返回检测孵育时间。
 */
unsigned int TestItem::get_detection_incubation_time() const{
	return(_detection_incubation_time);
}

/**
 * name: set_hole_no_in_detection_disc
 * brief: 设置检测盘孔号。
 * param: hole_no - 输入的检测盘孔号。
 * return: --
 */
void TestItem::set_hole_no_in_detection_disc(const unsigned int hole_no){
	_hole_no_in_detection_disc=hole_no;
}

/**
 * name: get_hole_no_in_detection_disc
 * brief: 获取检测盘孔号。
 * param: --
 * return: 返回检测盘孔号。
 */
unsigned int TestItem::get_hole_no_in_detection_disc() const{
	return(_hole_no_in_detection_disc);
}

/**
 * name: set_luminous
 * brief: 设置发光值。
 * param: luminous - 输入的发光值。
 * return: --
 */
void TestItem::set_luminous(const unsigned int luminous){
	_luminous=luminous;
}

/**
 * name: get_luminous
 * brief: 获取发光值。
 * param: --
 * return: 返回发光值。
 */
unsigned int TestItem::get_luminous() const{
	return(_luminous);
}

/**
 * name: add_test_step
 * brief: 为当前测试项目添加测试步骤。
 * param: test_step - 输入的测试步骤。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int TestItem::add_test_step(const TestStep &test_step){
	//1.检测当前步骤总数是否已满，则直接返回错误。
	if(_test_step_count>=MAXIMUM_TEST_STEPS){
		return(-1);
	}
	//2.如果当前输入的测试步骤未知，则直接返回错误。
	if(TEST_STEP_UNKNOWN==test_step){
		return(-2);
	}
	//3.为当前项目添加测试步骤。
	_test_step[_test_step_count]=test_step;
	//4.自增当前测试步骤计数。
	++_test_step_count;
	//5.如果是清洗测试步骤，则增加清洗次数计数。
	if(TEST_STEP_WASH==test_step){
		++_washing_times;
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_sequence_diagram
 * brief: 利用当前测试项目的数据信息生成时序图。
 * param: sequence_diagram - 输入指向时序图的数组指针。
 *        sequence_diagram_count - 输入的时序图计数。
 *        current_sequence_diagram_index - 输入的当前时序图索引。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const unsigned int current_sequence_diagram_index){
	//1.对当前时序进行冲突检测。
	int generate_result=generate_sequence_diagram(sequence_diagram,
		sequence_diagram_count,current_sequence_diagram_index,FALSE);
	if(generate_result<0){
		return(-1);
	}else if(generate_result>0){
		return(1);
	}
	//2.生成时序图。
	generate_result=generate_sequence_diagram(sequence_diagram,
		sequence_diagram_count,current_sequence_diagram_index,TRUE);
	if(0!=generate_result){
		return(-2);
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: operator=
 * brief: 重载“=”操作符。
 * param: source - 输入的赋值源实例。
 * return: 返回当前类实例自身引用。
 */
TestItem &TestItem::operator=(const TestItem &source){
	_key=source._key;
	_serial_number=source._serial_number;
	_hole_no_in_reaction_disc=source._hole_no_in_reaction_disc;
	_complete_time=source._complete_time;
	_specimen_volume=source._specimen_volume;
	_specimen_rack_no=source._specimen_rack_no;
	_specimen_position_no=source._specimen_position_no;
	_specimen_cup_type=source._specimen_cup_type;
	_add_specimen_flag=source._add_specimen_flag;
	_magnetic_bead_volume=source._magnetic_bead_volume;
	_magnetic_bead_position_no=source._magnetic_bead_position_no;
	_washing_times=source._washing_times;
	_detection_incubation_time=source._detection_incubation_time;
	_hole_no_in_detection_disc=source._hole_no_in_detection_disc;
	_luminous=source._luminous;
	_test_step_count=source._test_step_count;
	memcpy(_reagent_volume,source._reagent_volume,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_reagent_position_no,source._reagent_position_no,REAGENT_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_incubate_time,source._incubate_time,MAXIMUM_INCUBATION_TIMES*sizeof(unsigned int));
	memcpy(_substrate_volume,source._substrate_volume,SUBSTRATE_TYPE_COUNT*sizeof(unsigned int));
	memcpy(_test_step,source._test_step,MAXIMUM_TEST_STEPS*sizeof(TestStep));
	return(*this);
}

/**
 * name: get_washing_times
 * brief: 获取清洗次数。
 * param: --
 * return: 返回清洗次数。
 */
unsigned int TestItem::get_washing_times() const{
	return(_washing_times);
}

/**
 * name: generate_sequence_diagram
 * brief: 利用当前测试项目的数据信息生成时序图。
 * param: sequence_diagram - 输入指向时序图的数组指针。
 *        sequence_diagram_count - 输入的时序图计数。
 *        current_sequence_diagram_index - 输入的当前时序图索引。
 *        is_data_generated - 输入的是否为时序图生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const unsigned int current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.如果当前输入参数非法，则直接返回错误。
	if((0==sequence_diagram)||(0==sequence_diagram_count)||(
		current_sequence_diagram_index>=Timing::SEQUENCE_DIAGRAM_COUNT)){
		return(-1);
	}
	//2.如果当前测试项目信息中的测试步骤非法。
	if((0==_test_step_count)||(_test_step_count>MAXIMUM_TEST_STEPS)){
		return(-2);
	}
	//3.遍历当前项目的测试步骤，根据测试步骤对当前时序图进行设置、检测。
	//3-1.声明当前操作所需变量。
	unsigned int liquid_volume_in_reaction_tube=0;//记录在反应盘中的液体体积（加样本、加试剂时使用）。
	unsigned int nth_times_incubate=1;//记录当前第几次孵育。
	unsigned int nth_times_wash=1;//记录当前第几次清洗。
	unsigned int current_sequence_diagram_index_temp=current_sequence_diagram_index;//当前时序图索引。
	//3-2.遍历当前项目的测试步骤，根据测试步骤检测、设置时序图。
	for(unsigned int step_index=0;step_index!=_test_step_count;++step_index){
		//3-2-1.如果当前测试步骤是设备进管。
		if(TEST_STEP_ENTRY_TUBE==_test_step[step_index]){
			//1>.为设备进管生成时序图，并且记录生成结果。
			const int generate_result=generate_entry_tube_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-3);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-2.如果当前测试步骤是添加样本。
		else if(TEST_STEP_ADD_SPECIMEN==_test_step[step_index]){
			//1>.为设备进管生成时序图，并且记录生成结果。
			const int generate_result=generate_add_specimen_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,
				liquid_volume_in_reaction_tube,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-4);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-3.如果当前测试步骤是添加R1试剂。
		else if(TEST_STEP_ADD_R1==_test_step[step_index]){
			//1>.为设备添加试剂R1生成时序图，并且记录生成结果。
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R1,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-5);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-4.如果当前测试步骤是添加R2试剂。
		else if(TEST_STEP_ADD_R2==_test_step[step_index]){
			//1>.为设备添加试剂R2生成时序图，并且记录生成结果。
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R2,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-6);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-5.如果当前测试步骤是添加R3试剂。
		else if(TEST_STEP_ADD_R3==_test_step[step_index]){
			//1>.为设备添加试剂R3生成时序图，并且记录生成结果。
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R3,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-7);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-6.如果当前测试步骤是添加R4试剂。
		else if(TEST_STEP_ADD_R4==_test_step[step_index]){
			//1>.为设备添加试剂R4生成时序图，并且记录生成结果。
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R4,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-8);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-7.如果当前测试步骤是添加磁珠。
		else if(TEST_STEP_ADD_MAGNETIC_BEAD==_test_step[step_index]){
			//1>.为设备添加磁珠生成时序图，并且记录生成结果。
			const int generate_result=generate_add_magnetic_bead_sequence_diagram(
				sequence_diagram,sequence_diagram_count,current_sequence_diagram_index_temp,
				liquid_volume_in_reaction_tube,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-9);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-8.如果当前测试步骤是孵育。
		else if(TEST_STEP_INCUBATE==_test_step[step_index]){
			//1>.为设备孵育生成时序图，并且记录生成结果。
			const int generate_result=generate_incubate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,current_sequence_diagram_index_temp,
				nth_times_incubate,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-10);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-9.如果当前测试步骤是清洗。
		else if(TEST_STEP_WASH==_test_step[step_index]){
			/*
			//1>.对清洗前不是孵育的情况进行容错处理。
			if((step_index>0)&&(TEST_STEP_INCUBATE!=_test_step[step_index-1])){
				++current_sequence_diagram_index_temp;
				if(current_sequence_diagram_index_temp>=sequence_diagram_count){
					current_sequence_diagram_index_temp=0;
				}
			}
			*/
			//2>.为设备清洗生成时序图，并且记录生成结果。
			const int generate_result=generate_wash_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,
				nth_times_wash,is_data_generated);
			//3>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-11);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-10.如果当前测试步骤是加底物AB。
		else if(TEST_STEP_ADD_SUBSTRATE_AB==_test_step[step_index]){
			//1>.为设备添加底物AB生成时序图，并且记录生成结果。
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_AB,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-12);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-11.如果当前测试步骤是加底物C。
		else if(TEST_STEP_ADD_SUBSTRATE_C==_test_step[step_index]){
			//1>.为设备添加底物C生成时序图，并且记录生成结果。
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_C,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-13);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-12.如果当前测试步骤是加缓冲液。
		else if(TEST_STEP_ADD_BUFFER_SOLUTION==_test_step[step_index]){
			//1>.为设备添加缓冲液生成时序图，并且记录生成结果。
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_BUFFER_SOLUTION,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-14);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-13.如果当前测试步骤是回管到反应盘。
		else if(TEST_STEP_RETURN_TUBE==_test_step[step_index]){
			//1>.为设备回管到反应盘生成时序图，并且记录生成结果。
			const int generate_result=generate_return_tube_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-15);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-14.如果当前测试步骤是检测。
		else if(TEST_STEP_DETECT==_test_step[step_index]){
			//1>.为设备检测生成时序图，并且记录生成结果。
			const int generate_result=generate_detect_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.如果生成时序图失败，则返回相应错误。
			if(generate_result<0){
				return(-16);
			}else if(generate_result>0){
				return(1);
			}		
		}
	}
	//4.计算当前项目的结束时间。
	if(is_data_generated){
		//4-1.计算当前项目实际使用的周期数。
		int cycle_count=0;
		if(current_sequence_diagram_index_temp>=current_sequence_diagram_index){
			cycle_count=static_cast<int>(current_sequence_diagram_index_temp)-
				static_cast<int>(current_sequence_diagram_index)+1;
		}else{
			cycle_count=static_cast<int>(current_sequence_diagram_index_temp)+
				static_cast<int>(sequence_diagram_count)-static_cast<int>(
				current_sequence_diagram_index)+1;
		}
		cycle_count-=3;
		if(cycle_count<0){
			return(-17);
		}
		//4-2.计算项目实际的出管时间。
		unsigned int complete_time=cycle_count*Timing::TIMING_CYCLE;
		complete_time+=8000;
		if(get_detection_incubation_time()<=5000){
			complete_time+=27000;
		}else{
			complete_time+=17000;
		}
		complete_time/=1000;
		COleDateTimeSpan date_time_span(0,0,0,complete_time);
		COleDateTime date_time=COleDateTime::GetCurrentTime();
		date_time+=date_time_span;
		//4-3.记录当前项目的结束时间。
		set_complete_time(date_time.Format(_T("%Y-%m-%d %H:%M:%S")));
	}
	//5.程序运行到此直接返回零。
	return(0);
}

/**
 * name: generate_entry_tube_sequence_diagram
 * breif: 为进管测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_entry_tube_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.试管仓取管动作检测、赋值。
	//1-1.获取当前时序中试管仓取管动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.如果当前试管仓取管动作已被占用，则直接返回冲突错误。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.设置试管仓取管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//2.反应盘旋转动作检测、赋值。
	//2-1.获取当前时序图中反应盘旋转动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,7);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.如果当前反应盘旋转动作已被占用，则直接返回冲突错误。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.获取反应盘空闲位置，并且判断获取是否成功。
	const unsigned int hole_no=(((Instrument::instance())->
		get_components())->get_reaction_disc())->get_empty_hole_no();
	if(0==hole_no){
		//remark.如果当前反应盘上没有空闲位置，则按动作冲突处理（下一周期再试）。
		return(1);
	}
	//2-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		//a.设置反应盘旋转动作数据。
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_hole_no(hole_no);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_position(ReactionDisc::POSITION_ENTRY);
		//b.记录当前项目占用的反应盘孔号。
		set_hole_no_in_reaction_disc(hole_no);
	}
	//3.装载抓手放管动作检测、赋值。
	//3-1.获取当前时序图中装载抓手放管动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-3-2.如果当前装载抓手放管动作已被占用，则直接返回冲突错误。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3-3.设置装载抓手放管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.进管动作安排完毕后，需要安排下一个周期的时序。
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_add_specimen_sequence_diagram
 * breif: 为加样测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        liquid_volume_in_reaction_tube - 输入/输出的反应盘内的液体体积。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_add_specimen_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int /*sequence_diagram_count*/,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.样本盘旋转动作检测、赋值。
	//1-1.获取样本旋转动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_DISC_ROTATION,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.如果样本盘旋转动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.设置动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenDiscRotation*>(action.get())->
			set_rack_no(get_specimen_rack_no());
		dynamic_cast<SpecimenDiscRotation*>(action.get())->
			set_position_no(get_specimen_position_no());
	}
	//2.样本臂吸样动作检测、赋值。
	//2-1.获取样本臂吸样动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_ARM_SUCK,1);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.如果样本臂吸样动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置样本臂吸样动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenArmSuck*>(action.get())->
			set_suck_volume(get_specimen_volume());
		dynamic_cast<SpecimenArmSuck*>(action.get())->
			set_cup_type(get_specimen_cup_type());
	}
	//3.反应盘旋转动作检测、赋值。
	//3-1.获取反应盘旋转动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,2);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.如果反应盘旋转动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_hole_no(get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_position(ReactionDisc::POSITION_ADD_SPECIMEN);
	}
	//4.样本臂加样动作检测、赋值。
	//4-1.获取样本臂加样动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_ARM_SPIT,1);
	if(!static_cast<bool>(action)){
		return(-4);
	}
	//4-2.如果样本臂加样动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.设置样本臂加样动作数据。
	if(is_data_generated){
		//a.将当前反应杯内的液体高度转换为电机脉冲步数。
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.设置样本臂加样动作数据。
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenArmSpit*>(action.get())->
			set_spit_volume(get_specimen_volume());
		dynamic_cast<SpecimenArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.累计反应盘中的液体体积。
		liquid_volume_in_reaction_tube+=get_specimen_volume();
	}
	//5.样本臂清洗动作检测、赋值。
	//5-1.获取样本臂清洗动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_SPECIMEN_ARM_WASH,1);
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//5-2.如果样本臂清洗动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.设置样本臂清洗动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//6.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_add_reagent_sequence_diagram
 * breif: 为添加试剂测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        reagent_type - 输入的试剂类型。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        liquid_volume_in_reaction_tube - 输入/输出的反应盘内的液体体积。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_add_reagent_sequence_diagram(
	SequenceDiagram *sequence_diagram,const unsigned int sequence_diagram_count,
	const ReagentType reagent_type,unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,const BOOL is_data_generated){
	//1.声明、计算当前操作所需变量。
	const ReagentDisc::ReagentType reagent_type_in_reagent_disc=(((
		REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type))?(
		ReagentDisc::REAGENT_TYPE_R1):(ReagentDisc::REAGENT_TYPE_R2));
	//2.试剂盘旋转动作检测、赋值。
	//2-1.获取试剂盘旋转动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action;
	if((REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type)){
		int last_sequence_diagram_index=static_cast<int>(
			current_sequence_diagram_index)-1;
		if(last_sequence_diagram_index<0){
			last_sequence_diagram_index=static_cast<int>(
			sequence_diagram_count)-1;
		}
		action=sequence_diagram[last_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_DISC_ROTATION,2);
	}else{
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_DISC_ROTATION,1);
	}
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//2-2.如果试剂盘旋转动作已被占用，则直接返回冲突错误。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置试剂盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentDiscRotation*>(action.get())->
			set_reagent_type(reagent_type_in_reagent_disc);
		dynamic_cast<ReagentDiscRotation*>(action.get())->
			set_position_no(get_reagent_position_no(reagent_type));
	}
	//3.试剂臂吸样动作检测、赋值。
	//3-1.获取试剂臂吸样动作，并且获取是否成功。
	if((REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type)){
		action=sequence_diagram[current_sequence_diagram_index].
			get_action(SequenceDiagram::ACTION_ID_REAGENT_ARM_SUCK,1);
	}else{
		action=sequence_diagram[current_sequence_diagram_index].
			get_action(SequenceDiagram::ACTION_ID_REAGENT_ARM_SUCK,2);
	}
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//3-2.如果试剂臂吸样动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.设置试剂臂吸样动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_reagent_type(reagent_type_in_reagent_disc);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_suck_volume(get_reagent_volume(reagent_type));
	}
	//4.反应盘旋转动作检测、赋值。
	//4-1.获取当前时序中反应盘旋转动作。
	if((REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type)){
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,1);
	}else{
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,3);
	}
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//4-2.如果反应盘旋转动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_ADD_REAGENT);
	}
	//5.试剂臂加样动作检测、赋值。
	//5-1.获取试剂臂加样动作，并且判断获取是否成功。
	if((REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type)){
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_ARM_SPIT,1);
	}else{
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_ARM_SPIT,2);
	}
	if(!static_cast<bool>(action)){
		return(-4);
	}
	//5-2.如果试剂臂加样动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.设置试剂臂加样动作数据。
	if(is_data_generated){
		//a.将当前反应杯内的液体高度转换为电机脉冲步数。
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.试剂臂加样动作数据。
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_spit_volume(get_reagent_volume(reagent_type));
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.累计当前反应管中的液体体积。
		liquid_volume_in_reaction_tube+=get_reagent_volume(reagent_type);
	}
	//6.试剂臂清洗动作检测、赋值。
	//6-1.获取试剂臂清洗动作，并且判断获取是否成功。 
	if((REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type)){
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_ARM_WASH,1);
	}else{
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_REAGENT_ARM_WASH,2);
	}
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//6-2.如果试剂臂清洗动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//6-3.设置试剂臂清洗动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//7.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_add_magnetic_bead_sequence_diagram
 * breif: 为添加磁珠测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        liquid_volume_in_reaction_tube - 输入/输出的反应盘内的液体体积。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_add_magnetic_bead_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int /*sequence_diagram_count*/,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.声明、计算当前操作所需变量。
	ReagentArm::ReagentType magnetic_bead_type=
		ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_1;
	if(MagneticBeadDisc::POSITION_COUNT==get_magnetic_bead_position_no()){
		magnetic_bead_type=ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_2;
	}
	//2.磁珠盘旋转动作检测、赋值。
	//2-1.获取磁珠盘旋转动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
			ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,9);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//2-2.如果磁珠盘旋转动作已被占用，则直接返回冲突错误。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置磁珠盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<MagneticBeadDiscRotation*>(action.get())->
			set_position_no(get_magnetic_bead_position_no());
	}
	//3.试剂臂吸样动作检测、赋值。
	//3-1.获取试剂臂吸样动作，并且获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REAGENT_ARM_SUCK,3);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//3-2>.如果试剂臂吸样动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3>.设置试剂臂吸样动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_reagent_type(magnetic_bead_type);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_suck_volume(get_magnetic_bead_volume());
	}
	//4.反应盘旋转动作检测、赋值。
	//4-1.获取当前时序中反应盘旋转动作。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,6);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//4-2.如果反应盘旋转动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_ADD_REAGENT);
	}
	//5.试剂臂加样动作检测、赋值。
	//5-1.获取试剂臂加样动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REAGENT_ARM_SPIT,3);
	if(!static_cast<bool>(action)){
		return(-4);
	}
	//5-2.如果试剂臂加样动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.设置试剂臂加样动作数据。
	if(is_data_generated){
		//a.将当前反应杯内的液体高度转换为电机脉冲步数。
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.试剂臂加样动作数据。
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_spit_volume(get_magnetic_bead_volume());
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.累计当前反应管中的液体体积。
		liquid_volume_in_reaction_tube+=get_magnetic_bead_volume();
	}
	//6.试剂臂清洗动作检测、赋值。
	//6-1.获取试剂臂清洗动作，并且判断获取是否成功。 
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REAGENT_ARM_WASH,3);
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//6-2.如果试剂臂清洗动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//6-3.设置试剂臂清洗动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//7.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_incubate_sequence_diagram
 * breif: 为孵育测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        nth_times_incubate - 输入/输出的孵育次数。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_incubate_sequence_diagram(
	SequenceDiagram * /*sequence_diagram*/,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	unsigned int &nth_times_incubate,
	const BOOL /*is_data_generated*/){
	//1.获取当前的孵育时间（孵育时间最小一个周期）。
	unsigned int incubate_time=get_incubate_time(nth_times_incubate);
	if(0==incubate_time){//强制排除孵育时间为零的情况。
		incubate_time=Timing::TIMING_CYCLE;
	}
	//2.计算当前温育消耗的周期数（采用四舍五入的计算方式）。
	const unsigned int cycle_count=static_cast<unsigned int>(
		static_cast<double>(incubate_time)/static_cast<double>(
		Timing::TIMING_CYCLE)+0.5)+1;
	//3.更新当前时序图索引序号。
	current_sequence_diagram_index+=cycle_count;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=current_sequence_diagram_index-
			sequence_diagram_count+1;
	}
	//4.设置当前是第几次赋孵育标记变量。
	++nth_times_incubate;
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_wash_sequence_diagram
 * breif: 为清洗测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        nth_times_wash - 输入/输出的清洗次数。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_wash_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	unsigned int &nth_times_wash,
	const BOOL is_data_generated){
	//1.反应盘旋转动作检测、赋值。
	//1-1.获取当前时序中反应盘旋转动作。
	SequenceDiagram::PtrToAction action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,5);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.如果反应盘旋转动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_EXIT);
	}
	//2.反应盘取管动作检测、赋值。
	//2-1.获取反应盘取管动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.如果反应盘取管动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置反应盘取管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfReactionDisc*>(
			action.get())->set_reserve_reaction_disc_hole_flag(
			nth_times_wash!=get_washing_times());
	}
	//3.清洗盘放管动作检测、赋值。
	//3-1.获取清洗盘放管动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.如果清洗盘放管动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.设置清洗盘放管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.累计当前清洗次数。
	++nth_times_wash;
	//5.更新当前时序图索引序号。
	current_sequence_diagram_index+=18;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=current_sequence_diagram_index-
			sequence_diagram_count+1;
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: generate_add_substrate_sequence_diagram
 * breif: 为添加底物测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        substrate_type - 输入的底物类型。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        liquid_volume_in_reaction_tube - 输入/输出的反应盘内的液体体积。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_add_substrate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const SubstrateType substrate_type,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.声明、计算当前操作所需变量。
	WashingDisc::SubstrateType substrate_type_in_wash_disc=
		WashingDisc::SUBSTRATE_TYPE_AB;
	if(SUBSTRATE_TYPE_C==substrate_type){
		substrate_type_in_wash_disc=
			WashingDisc::SUBSTRATE_TYPE_C;
	}else if(SUBSTRATE_TYPE_BUFFER_SOLUTION==substrate_type){
		substrate_type_in_wash_disc=
			WashingDisc::SUBSTRATE_TYPE_BUFFER_SOLUTION;
	}
	//2.对清洗盘清洗动作进行检测、赋值。
	//2-1.获取清洗盘清洗动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_WASHING_DISC_WASH,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//2-2.如果清洗盘清洗动作已被使用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置清洗盘清洗动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<WashingDiscWash*>(action.get())->set_substrate_type(
			substrate_type_in_wash_disc);
		dynamic_cast<WashingDiscWash*>(action.get())->set_substrate_volume(
			get_substrate_volume(substrate_type));
	}
	//3.加底物、缓冲液后，更新反应管中的液体体积。
	liquid_volume_in_reaction_tube=get_substrate_volume(substrate_type);
	//4.更新时序图索引编号。
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_return_tube_sequence_diagram
 * breif: 为反应盘回管测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_return_tube_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.对清洗盘取管动作进行检测、赋值。
	//1-1.获取清洗盘取管动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
			ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.如果清洗盘取管动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.设置清洗盘取管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfWashingDisc*>(action.get())->
			set_stop_position(TransportTong::STOP_POSITION_REACTION_DISC);
	}
	//2.对反应盘旋转动作进行检测、赋值。
	//2-1.获取反应盘旋转动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,4);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.如果反应盘旋转动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置反应盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_EXIT);
	}
	//3.对反应盘回管动作进行检测、赋值。
	//3-1.获取反应盘回管动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.如果反应盘回管动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.设置反应盘回管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.更新时序图索引编号。
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: generate_detect_sequence_diagram
 * breif: 为检测测试步骤生成相应的时序图。
 * param: sequence_diagram - 输入的指向时序图数组的指针。
 *        sequence_diagram_count - 输入的时序图数组数量计数。
 *        current_sequence_diagram_index - 输入/输出的当前使用的时序图索引编号。
 *        is_data_generated - 输入的是否生成数据标志。
 * return: 如果生成时序图成功，则返回值等于零。
 *         如果生成时序图失败，则返回值小于零。
 *         如果生成的时序图与现有时序冲突，则直接返回一。
 */
int TestItem::generate_detect_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.对清洗盘取管动作进行检测、赋值。
	//1-1.获取清洗盘取管动作，并且判断获取是否成功。
	SequenceDiagram::PtrToAction action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.如果清洗盘取管动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.设置清洗盘取管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfWashingDisc*>(action.get())->set_stop_position(
			TransportTong::STOP_POSITION_DETECTION_DISC);
	}
	//2.对检测盘旋转动作进行检测、赋值。
	//2-1.获取检测盘旋转动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,3);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.如果检测盘旋转动作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.设置检测盘旋转动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(get_key());
		dynamic_cast<DetectionDiscRotation*>(action.get())->set_position(
			DetectionDisc::POSITION_ENTRY);
	}
	//3.对检测盘放管动作进行检测、赋值。
	//3-1.获取检测盘放管动作，并且判断获取是否成功。
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.如果检测盘放管作已被占用，则直接返回冲突。
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.设置检测盘放管动作数据。
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(get_key());
	}
	//4.如果检测孵育时间小于等于5秒，则对当前项目立即进行检测。
	if(get_detection_incubation_time()<=5000){
		//4-1.对检测盘旋转动作进行检测、赋值。
		//4-1-1.获取检测盘旋转动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,4);
		if(!static_cast<bool>(action)){
			return(-4);
		}
		//4-1-2.如果检测盘旋转动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//4-1-3.设置检测盘旋转动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_DETECTION);
		}
		//4-2.对检测盘检测动作进行检测、赋值。
		//4-2-1.获取检测盘检测动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECT,2);
		if(!static_cast<bool>(action)){
			return(-5);
		}
		//4-2-2.如果检测盘检测动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//4-2-3.设置检测盘检测动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//5.更新时序图索引编号。
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//6.如果检测孵育时间小于等于5秒，则对当前项目进行扔管。
	if(get_detection_incubation_time()<=5000){
		//6-1.对检测盘旋转动作进行检测、赋值。
		//6-1-1.获取检测盘旋转动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,1);
		if(!static_cast<bool>(action)){
			return(-6);
		}
		//6-1-2.如果检测盘旋转动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-1-3.设置检测盘旋转动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_EXIT);
		}
		//6-2.对转运臂检测盘取管动作进行检测、赋值。
		//6-2-1.获取转运臂取管动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,2);
		if(!static_cast<bool>(action)){
			return(-7);
		}
		//6-2-2.如果转运臂取管动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-2-3.设置转运臂取管动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//6-3.对转运臂丢管动作进行检测、赋值。
		//6-3-1.获取转运臂丢管动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DISCARD_TUBE,2);
		if(!static_cast<bool>(action)){
			return(-8);
		}
		//6-3-2.如果转运臂丢管动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-3-3.设置转运臂丢管动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//7.如果检测孵育时间大于5秒（按30秒算），则对当前项目进行检测、扔管。
	else{
		//7-1.对检测盘旋转动作进行检测、赋值。
		//7-1-1.获取检测盘旋转动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,2);
		if(!static_cast<bool>(action)){
			return(-9);
		}
		//7-1-2.如果检测盘旋转动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-1-3.设置检测盘旋转动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_DETECTION);
		}
		//7-2.对检测盘检测动作进行检测、赋值。
		//7-2-1.获取检测盘检测动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECT,2);
		if(!static_cast<bool>(action)){
			return(-10);
		}
		//7-2-2.如果检测盘检测动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-2-3.设置检测盘检测动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//7-3.对检测盘旋转动作进行检测、赋值。
		//7-3-1.获取检测盘旋转动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,5);
		if(!static_cast<bool>(action)){
			return(-11);
		}
		//7-3-2.如果检测盘旋转动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-3-3.设置检测盘旋转动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_EXIT);
		}
		//7-4.更新时序图索引编号。
		++current_sequence_diagram_index;
		if(current_sequence_diagram_index>=sequence_diagram_count){
			current_sequence_diagram_index=0;
		}
		//7-5.对转运臂检测盘取管动作进行检测、赋值。
		//7-5-1.获取转运臂取管动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,1);
		if(!static_cast<bool>(action)){
			return(-12);
		}
		//7-5-2.如果转运臂取管动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-5-3.设置转运臂取管动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//7-6.对转运臂丢管动作进行检测、赋值。
		//7-6-1.获取转运臂丢管动作，并且判断获取是否成功。
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DISCARD_TUBE,1);
		if(!static_cast<bool>(action)){
			return(-13);
		}
		//7-6-2.如果转运臂丢管动作已被占用，则直接返回冲突。
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-6-3.设置转运臂丢管动作数据。
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//8.程序运行到此成功返回。
	return(0);
}