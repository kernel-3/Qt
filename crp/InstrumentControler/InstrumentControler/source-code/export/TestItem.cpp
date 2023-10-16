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
 * breif: ���캯����
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
 * brief: �������캯����
 * param: source - ����Ŀ���Դʵ����
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
 * brief: ����������
 * param: --
 * return: --
 */
TestItem::~TestItem(void){
}

/**
 * name: set_key
 * brief: ���õ�ǰ������Ŀ������
 * param: key - ����ĵ�ǰ������Ŀ������
 * return: --
 */
void TestItem::set_key(const unsigned int key){
	_key=key;
}

/**
 * name: get_key
 * brief: ��ȡ��ǰ������Ŀ������
 * param: --
 * return: ���ص�ǰ������Ŀ������
 */
unsigned int TestItem::get_key() const{
	return(_key);
}

/**
 * name: set_serial_number
 * brief: ���ò�����Ŀ����ˮ�š�
 * param: serial_number - ���������Ŀ����ˮ�š�
 * return: --
 */
void TestItem::set_serial_number(const CString serial_number){
	_serial_number=serial_number;
}

/**
 * name: get_serial_number
 * brief: ��ȡ������Ŀ����ˮ�š�
 * param: --
 * return: ���ز�����Ŀ����ˮ�š�
 */
CString TestItem::get_serial_number() const{
	return(_serial_number);
}

/**
 * name: set_hole_no_in_reaction_disc
 * brief: ���÷�Ӧ���ϵĿ׺š�
 * param: hole_no - ����ķ�Ӧ���ϵĿ׺š�
 * return: --
 */
void TestItem::set_hole_no_in_reaction_disc(const unsigned int hole_no){
	_hole_no_in_reaction_disc=hole_no;
}

/**
 * name: get_hole_no_in_reaction_disc
 * brief: ��ȡ��Ӧ���ϵĿ׺š�
 * param: --
 * return: ���ط�Ӧ���ϵĿ׺š�
 */
unsigned int TestItem::get_hole_no_in_reaction_disc() const{
	return(_hole_no_in_reaction_disc);
}

/**
 * name: set_complete_time
 * brief: ���õ�ǰ��Ŀ�����ʱ�䡣
 * param: complete_time - ��������ʱ�䡣
 * return: --
 */
void TestItem::set_complete_time(const CString complete_time){
	_complete_time=complete_time;
}

/**
 * name: get_complete_time
 * brief: ��ȡ��ǰ��Ŀ�����ʱ�䡣
 * param: --
 * return: ���ص�ǰ��Ŀ�����ʱ�䡣
 */
CString TestItem::get_complete_time() const{
	return(_complete_time);
}

/**
 * name: set_specimen_volume
 * brief: �������������
 * param: volume - ��������������
 * return: --
 */
void TestItem::set_specimen_volume(const unsigned int volume){
	_specimen_volume=volume;
}

/**
 * name: get_specimen_volume
 * brief: ��ȡ���������
 * param: --
 * return: �������������
 */
unsigned int TestItem::get_specimen_volume() const{
	return(_specimen_volume);
}

/**
 * name: set_specimen_rack_no
 * brief: �����������Ӻš�
 * param: rack_no - ������������Ӻš�
 * return: --
 */
void TestItem::set_specimen_rack_no(const unsigned int rack_no){
	_specimen_rack_no=rack_no;
}

/**
 * name: get_specimen_rack_no
 * brief: ��ȡ�������Ӻš�
 * param: --
 * return: �����������Ӻš�
 */
unsigned int TestItem::get_specimen_rack_no() const{
	return(_specimen_rack_no);
}

/**
 * name: set_specimen_position_no
 * breif: ��������λ�úš�
 * param: position_no - ���������λ�úš�
 * return: --
 */
void TestItem::set_specimen_position_no(const unsigned int position_no){
	_specimen_position_no=position_no;
}

/**
 * name: get_specimen_position_no
 * brief: ��ȡ����λ�úš�
 * param: --
 * return: ��������λ�úš�
 */
unsigned int TestItem::get_specimen_position_no() const{
	return(_specimen_position_no);
}

/**
 * name: set_specimen_cup_type
 * brief: �������������͡�
 * param: type - ��������������͡�
 * return: --
 */
void TestItem::set_specimen_cup_type(const SpecimenCupType type){
	_specimen_cup_type=type;
}

/**
 * name: get_specimen_cup_type
 * brief: ��ȡ���������͡�
 * param: --
 * return: �������������͡�
 */
TestItem::SpecimenCupType TestItem::get_specimen_cup_type() const{
	return(_specimen_cup_type);
}

/**
 * name: set_add_specimen_flag
 * brief: �������������־��
 * param: flag - ��������������־��FALSE ������δ��� TRUE �����Ѿ���ӣ���
 * return: --
 */
void TestItem::set_add_specimen_flag(const BOOL flag){
	_add_specimen_flag=flag;
}

/**
 * name: get_add_specimen_flag
 * brief: ��ȡ���������־��
 * param: --
 * return: �������������־��FALSE ������δ��� TRUE �����Ѿ���ӣ���
 */
BOOL TestItem::get_add_specimen_flag() const{
	return(_add_specimen_flag);
}

/**
 * name: set_reagent_volume
 * breif: �����Լ������
 * param: reagent_type - ������Լ����͡�
 *        volume - ������Լ������
 * return: --
 */
void TestItem::set_reagent_volume(
	const ReagentType reagent_type,const unsigned int volume){
	_reagent_volume[reagent_type-1]=volume;
}

/**
 * name: get_reagent_volume
 * brief: ��ȡ�Լ������
 * param: reagent_type - ������Լ����͡�
 * return: �����Լ������
 */
unsigned int TestItem::get_reagent_volume(
	const ReagentType reagent_type) const{
	return(_reagent_volume[reagent_type-1]);
}

/**
 * name: set_reagent_position_no
 * brief: �����Լ�λ�úš�
 * param: reagent_type - ������Լ����͡�
 *        position_no - ������Լ�λ�úš�
 * return: --
 */
void TestItem::set_reagent_position_no(
	const ReagentType reagent_type,const unsigned int position_no){
	_reagent_position_no[reagent_type-1]=position_no;
}

/**
 * name: get_reagent_position_no
 * brief: ��ȡ�Լ�λ�úš�
 * param: reagent_type - ������Լ����͡�
 * return: �����Լ�λ�úš�
 */
unsigned int TestItem::get_reagent_position_no(
	const ReagentType reagent_type) const{
	return(_reagent_position_no[reagent_type-1]);
}

/**
 * name: set_magnetic_bead_volume
 * brief: ���ô��������
 * param: volume - ����Ĵ��������
 * return: --
 */
void TestItem::set_magnetic_bead_volume(const unsigned int volume){
	_magnetic_bead_volume=volume;
}

/**
 * name: get_magnetic_bead_volume
 * brief: ��ȡ���������
 * param: --
 * return: ���ش��������
 */
unsigned int TestItem::get_magnetic_bead_volume() const{
	return(_magnetic_bead_volume);
}

/**
 * name: set_magnetic_bead_position_no
 * brief: ���ô���λ�úš�
 * param: position_no - ����Ĵ���λ�úš�
 * return: --
 */
void TestItem::set_magnetic_bead_position_no(const unsigned int position_no){
	_magnetic_bead_position_no=position_no;
}

/**
 * name: get_magnetic_bead_position_no
 * brief: ��ȡ����λ�úš�
 * param: --
 * return: ���ش���λ�úš�
 */
unsigned int TestItem::get_magnetic_bead_position_no() const{
	return(_magnetic_bead_position_no);
}

/**
 * name: set_incubate_time
 * brief: ��������ʱ�䡣
 * param: nth - ����ĵ�n��������ʶ��1~MAXIMUM_INCUBATION_TIMES����
 *        time - ���������ʱ�䡣
 * return: --
 */
void TestItem::set_incubate_time(const unsigned int nth,const unsigned int time){
	//1.��������Ƿ�Ϸ���
	assert((nth>=1)&&(nth<=MAXIMUM_INCUBATION_TIMES));
	//2.���õ�n������������ʱ�䡣
	_incubate_time[nth-1]=time;
}

/**
 * name: get_incubate_time
 * brief: ��ȡ����ʱ�䡣
 * param: nth - ����ĵ�n��������ʶ��1~MAXIMUM_INCUBATION_TIMES����
 * return: ��������ʱ�䡣
 */
unsigned int TestItem::get_incubate_time(const unsigned int nth) const{
	//1.��������Ƿ�Ϸ���
	assert((nth>=1)&&(nth<=MAXIMUM_INCUBATION_TIMES));
	//2.��������ʱ�䡣
	return(_incubate_time[nth-1]);
}

/**
 * name: set_substrate_volume
 * brief: ���õ��������
 * param: substrate_type - ����ĵ������͡�
 *        volume - ����ĵ��������
 * return: --
 */
void TestItem::set_substrate_volume(
	const SubstrateType substrate_type,const unsigned int volume){
	_substrate_volume[substrate_type-1]=volume;
}

/**
 * name: get_substrate_volume
 * brief: ��ȡ���������
 * param: substrate_type - ����ĵ������͡�
 * return: ���ص��������
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
 * brief: ���ü�����ʱ�䡣
 * param: time - ����ļ�����ʱ�䡣
 * return: --
 */
void TestItem::set_detection_incubation_time(const unsigned int time){
	_detection_incubation_time=time;
}

/**
 * name: get_detection_incubation_time
 * brief: ��ȡ������ʱ�䡣
 * param: --
 * return: ���ؼ�����ʱ�䡣
 */
unsigned int TestItem::get_detection_incubation_time() const{
	return(_detection_incubation_time);
}

/**
 * name: set_hole_no_in_detection_disc
 * brief: ���ü���̿׺š�
 * param: hole_no - ����ļ���̿׺š�
 * return: --
 */
void TestItem::set_hole_no_in_detection_disc(const unsigned int hole_no){
	_hole_no_in_detection_disc=hole_no;
}

/**
 * name: get_hole_no_in_detection_disc
 * brief: ��ȡ����̿׺š�
 * param: --
 * return: ���ؼ���̿׺š�
 */
unsigned int TestItem::get_hole_no_in_detection_disc() const{
	return(_hole_no_in_detection_disc);
}

/**
 * name: set_luminous
 * brief: ���÷���ֵ��
 * param: luminous - ����ķ���ֵ��
 * return: --
 */
void TestItem::set_luminous(const unsigned int luminous){
	_luminous=luminous;
}

/**
 * name: get_luminous
 * brief: ��ȡ����ֵ��
 * param: --
 * return: ���ط���ֵ��
 */
unsigned int TestItem::get_luminous() const{
	return(_luminous);
}

/**
 * name: add_test_step
 * brief: Ϊ��ǰ������Ŀ��Ӳ��Բ��衣
 * param: test_step - ����Ĳ��Բ��衣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int TestItem::add_test_step(const TestStep &test_step){
	//1.��⵱ǰ���������Ƿ���������ֱ�ӷ��ش���
	if(_test_step_count>=MAXIMUM_TEST_STEPS){
		return(-1);
	}
	//2.�����ǰ����Ĳ��Բ���δ֪����ֱ�ӷ��ش���
	if(TEST_STEP_UNKNOWN==test_step){
		return(-2);
	}
	//3.Ϊ��ǰ��Ŀ��Ӳ��Բ��衣
	_test_step[_test_step_count]=test_step;
	//4.������ǰ���Բ��������
	++_test_step_count;
	//5.�������ϴ���Բ��裬��������ϴ����������
	if(TEST_STEP_WASH==test_step){
		++_washing_times;
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_sequence_diagram
 * brief: ���õ�ǰ������Ŀ��������Ϣ����ʱ��ͼ��
 * param: sequence_diagram - ����ָ��ʱ��ͼ������ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ������
 *        current_sequence_diagram_index - ����ĵ�ǰʱ��ͼ������
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const unsigned int current_sequence_diagram_index){
	//1.�Ե�ǰʱ����г�ͻ��⡣
	int generate_result=generate_sequence_diagram(sequence_diagram,
		sequence_diagram_count,current_sequence_diagram_index,FALSE);
	if(generate_result<0){
		return(-1);
	}else if(generate_result>0){
		return(1);
	}
	//2.����ʱ��ͼ��
	generate_result=generate_sequence_diagram(sequence_diagram,
		sequence_diagram_count,current_sequence_diagram_index,TRUE);
	if(0!=generate_result){
		return(-2);
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: operator=
 * brief: ���ء�=����������
 * param: source - ����ĸ�ֵԴʵ����
 * return: ���ص�ǰ��ʵ���������á�
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
 * brief: ��ȡ��ϴ������
 * param: --
 * return: ������ϴ������
 */
unsigned int TestItem::get_washing_times() const{
	return(_washing_times);
}

/**
 * name: generate_sequence_diagram
 * brief: ���õ�ǰ������Ŀ��������Ϣ����ʱ��ͼ��
 * param: sequence_diagram - ����ָ��ʱ��ͼ������ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ������
 *        current_sequence_diagram_index - ����ĵ�ǰʱ��ͼ������
 *        is_data_generated - ������Ƿ�Ϊʱ��ͼ�������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const unsigned int current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.�����ǰ��������Ƿ�����ֱ�ӷ��ش���
	if((0==sequence_diagram)||(0==sequence_diagram_count)||(
		current_sequence_diagram_index>=Timing::SEQUENCE_DIAGRAM_COUNT)){
		return(-1);
	}
	//2.�����ǰ������Ŀ��Ϣ�еĲ��Բ���Ƿ���
	if((0==_test_step_count)||(_test_step_count>MAXIMUM_TEST_STEPS)){
		return(-2);
	}
	//3.������ǰ��Ŀ�Ĳ��Բ��裬���ݲ��Բ���Ե�ǰʱ��ͼ�������á���⡣
	//3-1.������ǰ�������������
	unsigned int liquid_volume_in_reaction_tube=0;//��¼�ڷ�Ӧ���е�Һ������������������Լ�ʱʹ�ã���
	unsigned int nth_times_incubate=1;//��¼��ǰ�ڼ��η�����
	unsigned int nth_times_wash=1;//��¼��ǰ�ڼ�����ϴ��
	unsigned int current_sequence_diagram_index_temp=current_sequence_diagram_index;//��ǰʱ��ͼ������
	//3-2.������ǰ��Ŀ�Ĳ��Բ��裬���ݲ��Բ����⡢����ʱ��ͼ��
	for(unsigned int step_index=0;step_index!=_test_step_count;++step_index){
		//3-2-1.�����ǰ���Բ������豸���ܡ�
		if(TEST_STEP_ENTRY_TUBE==_test_step[step_index]){
			//1>.Ϊ�豸��������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_entry_tube_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-3);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-2.�����ǰ���Բ��������������
		else if(TEST_STEP_ADD_SPECIMEN==_test_step[step_index]){
			//1>.Ϊ�豸��������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_specimen_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,
				liquid_volume_in_reaction_tube,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-4);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-3.�����ǰ���Բ��������R1�Լ���
		else if(TEST_STEP_ADD_R1==_test_step[step_index]){
			//1>.Ϊ�豸����Լ�R1����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R1,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-5);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-4.�����ǰ���Բ��������R2�Լ���
		else if(TEST_STEP_ADD_R2==_test_step[step_index]){
			//1>.Ϊ�豸����Լ�R2����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R2,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-6);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-5.�����ǰ���Բ��������R3�Լ���
		else if(TEST_STEP_ADD_R3==_test_step[step_index]){
			//1>.Ϊ�豸����Լ�R3����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R3,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-7);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-6.�����ǰ���Բ��������R4�Լ���
		else if(TEST_STEP_ADD_R4==_test_step[step_index]){
			//1>.Ϊ�豸����Լ�R4����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_reagent_sequence_diagram(
				sequence_diagram,sequence_diagram_count,REAGENT_TYPE_R4,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-8);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-7.�����ǰ���Բ�������Ӵ��顣
		else if(TEST_STEP_ADD_MAGNETIC_BEAD==_test_step[step_index]){
			//1>.Ϊ�豸��Ӵ�������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_magnetic_bead_sequence_diagram(
				sequence_diagram,sequence_diagram_count,current_sequence_diagram_index_temp,
				liquid_volume_in_reaction_tube,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-9);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-8.�����ǰ���Բ����Ƿ�����
		else if(TEST_STEP_INCUBATE==_test_step[step_index]){
			//1>.Ϊ�豸��������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_incubate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,current_sequence_diagram_index_temp,
				nth_times_incubate,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-10);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-9.�����ǰ���Բ�������ϴ��
		else if(TEST_STEP_WASH==_test_step[step_index]){
			/*
			//1>.����ϴǰ���Ƿ�������������ݴ���
			if((step_index>0)&&(TEST_STEP_INCUBATE!=_test_step[step_index-1])){
				++current_sequence_diagram_index_temp;
				if(current_sequence_diagram_index_temp>=sequence_diagram_count){
					current_sequence_diagram_index_temp=0;
				}
			}
			*/
			//2>.Ϊ�豸��ϴ����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_wash_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,
				nth_times_wash,is_data_generated);
			//3>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-11);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-10.�����ǰ���Բ����Ǽӵ���AB��
		else if(TEST_STEP_ADD_SUBSTRATE_AB==_test_step[step_index]){
			//1>.Ϊ�豸��ӵ���AB����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_AB,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-12);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-11.�����ǰ���Բ����Ǽӵ���C��
		else if(TEST_STEP_ADD_SUBSTRATE_C==_test_step[step_index]){
			//1>.Ϊ�豸��ӵ���C����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_C,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-13);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-12.�����ǰ���Բ����Ǽӻ���Һ��
		else if(TEST_STEP_ADD_BUFFER_SOLUTION==_test_step[step_index]){
			//1>.Ϊ�豸��ӻ���Һ����ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_add_substrate_sequence_diagram(
				sequence_diagram,sequence_diagram_count,SUBSTRATE_TYPE_BUFFER_SOLUTION,
				current_sequence_diagram_index_temp,liquid_volume_in_reaction_tube,
				is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-14);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-13.�����ǰ���Բ����ǻعܵ���Ӧ�̡�
		else if(TEST_STEP_RETURN_TUBE==_test_step[step_index]){
			//1>.Ϊ�豸�عܵ���Ӧ������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_return_tube_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-15);
			}else if(generate_result>0){
				return(1);
			}
		}
		//3-2-14.�����ǰ���Բ����Ǽ�⡣
		else if(TEST_STEP_DETECT==_test_step[step_index]){
			//1>.Ϊ�豸�������ʱ��ͼ�����Ҽ�¼���ɽ����
			const int generate_result=generate_detect_sequence_diagram(
				sequence_diagram,sequence_diagram_count,
				current_sequence_diagram_index_temp,is_data_generated);
			//2>.�������ʱ��ͼʧ�ܣ��򷵻���Ӧ����
			if(generate_result<0){
				return(-16);
			}else if(generate_result>0){
				return(1);
			}		
		}
	}
	//4.���㵱ǰ��Ŀ�Ľ���ʱ�䡣
	if(is_data_generated){
		//4-1.���㵱ǰ��Ŀʵ��ʹ�õ���������
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
		//4-2.������Ŀʵ�ʵĳ���ʱ�䡣
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
		//4-3.��¼��ǰ��Ŀ�Ľ���ʱ�䡣
		set_complete_time(date_time.Format(_T("%Y-%m-%d %H:%M:%S")));
	}
	//5.�������е���ֱ�ӷ����㡣
	return(0);
}

/**
 * name: generate_entry_tube_sequence_diagram
 * breif: Ϊ���ܲ��Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_entry_tube_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.�Թܲ�ȡ�ܶ�����⡢��ֵ��
	//1-1.��ȡ��ǰʱ�����Թܲ�ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
		ACTION_ID_TAKE_TUBE_OUT_OF_TUBE_STOREHOUSE,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.�����ǰ�Թܲ�ȡ�ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ����
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.�����Թܲ�ȡ�ܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//2.��Ӧ����ת������⡢��ֵ��
	//2-1.��ȡ��ǰʱ��ͼ�з�Ӧ����ת�����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,7);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.�����ǰ��Ӧ����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ����
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.��ȡ��Ӧ�̿���λ�ã������жϻ�ȡ�Ƿ�ɹ���
	const unsigned int hole_no=(((Instrument::instance())->
		get_components())->get_reaction_disc())->get_empty_hole_no();
	if(0==hole_no){
		//remark.�����ǰ��Ӧ����û�п���λ�ã��򰴶�����ͻ������һ�������ԣ���
		return(1);
	}
	//2-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		//a.���÷�Ӧ����ת�������ݡ�
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_hole_no(hole_no);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_position(ReactionDisc::POSITION_ENTRY);
		//b.��¼��ǰ��Ŀռ�õķ�Ӧ�̿׺š�
		set_hole_no_in_reaction_disc(hole_no);
	}
	//3.װ��ץ�ַŹܶ�����⡢��ֵ��
	//3-1.��ȡ��ǰʱ��ͼ��װ��ץ�ַŹܶ����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-3-2.�����ǰװ��ץ�ַŹܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ����
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3-3.����װ��ץ�ַŹܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.���ܶ���������Ϻ���Ҫ������һ�����ڵ�ʱ��
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_add_specimen_sequence_diagram
 * breif: Ϊ�������Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        liquid_volume_in_reaction_tube - ����/����ķ�Ӧ���ڵ�Һ�������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_add_specimen_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int /*sequence_diagram_count*/,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.��������ת������⡢��ֵ��
	//1-1.��ȡ������ת�����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_DISC_ROTATION,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.�����������ת�����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.���ö������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenDiscRotation*>(action.get())->
			set_rack_no(get_specimen_rack_no());
		dynamic_cast<SpecimenDiscRotation*>(action.get())->
			set_position_no(get_specimen_position_no());
	}
	//2.����������������⡢��ֵ��
	//2-1.��ȡ���������������������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_ARM_SUCK,1);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.������������������ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.���������������������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenArmSuck*>(action.get())->
			set_suck_volume(get_specimen_volume());
		dynamic_cast<SpecimenArmSuck*>(action.get())->
			set_cup_type(get_specimen_cup_type());
	}
	//3.��Ӧ����ת������⡢��ֵ��
	//3-1.��ȡ��Ӧ����ת�����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,2);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.�����Ӧ����ת�����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_hole_no(get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->
			set_position(ReactionDisc::POSITION_ADD_SPECIMEN);
	}
	//4.�����ۼ���������⡢��ֵ��
	//4-1.��ȡ�����ۼ��������������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_SPECIMEN_ARM_SPIT,1);
	if(!static_cast<bool>(action)){
		return(-4);
	}
	//4-2.��������ۼ��������ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.���������ۼ����������ݡ�
	if(is_data_generated){
		//a.����ǰ��Ӧ���ڵ�Һ��߶�ת��Ϊ������岽����
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.���������ۼ����������ݡ�
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<SpecimenArmSpit*>(action.get())->
			set_spit_volume(get_specimen_volume());
		dynamic_cast<SpecimenArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.�ۼƷ�Ӧ���е�Һ�������
		liquid_volume_in_reaction_tube+=get_specimen_volume();
	}
	//5.��������ϴ������⡢��ֵ��
	//5-1.��ȡ��������ϴ�����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_SPECIMEN_ARM_WASH,1);
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//5-2.�����������ϴ�����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.������������ϴ�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//6.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_add_reagent_sequence_diagram
 * breif: Ϊ����Լ����Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        reagent_type - ������Լ����͡�
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        liquid_volume_in_reaction_tube - ����/����ķ�Ӧ���ڵ�Һ�������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_add_reagent_sequence_diagram(
	SequenceDiagram *sequence_diagram,const unsigned int sequence_diagram_count,
	const ReagentType reagent_type,unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,const BOOL is_data_generated){
	//1.���������㵱ǰ�������������
	const ReagentDisc::ReagentType reagent_type_in_reagent_disc=(((
		REAGENT_TYPE_R1==reagent_type)||(REAGENT_TYPE_R3==reagent_type))?(
		ReagentDisc::REAGENT_TYPE_R1):(ReagentDisc::REAGENT_TYPE_R2));
	//2.�Լ�����ת������⡢��ֵ��
	//2-1.��ȡ�Լ�����ת�����������жϻ�ȡ�Ƿ�ɹ���
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
	//2-2.����Լ�����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ����
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.�����Լ�����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentDiscRotation*>(action.get())->
			set_reagent_type(reagent_type_in_reagent_disc);
		dynamic_cast<ReagentDiscRotation*>(action.get())->
			set_position_no(get_reagent_position_no(reagent_type));
	}
	//3.�Լ�������������⡢��ֵ��
	//3-1.��ȡ�Լ����������������һ�ȡ�Ƿ�ɹ���
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
	//3-2.����Լ������������ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.�����Լ��������������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_reagent_type(reagent_type_in_reagent_disc);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_suck_volume(get_reagent_volume(reagent_type));
	}
	//4.��Ӧ����ת������⡢��ֵ��
	//4-1.��ȡ��ǰʱ���з�Ӧ����ת������
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
	//4-2.�����Ӧ����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_ADD_REAGENT);
	}
	//5.�Լ��ۼ���������⡢��ֵ��
	//5-1.��ȡ�Լ��ۼ��������������жϻ�ȡ�Ƿ�ɹ���
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
	//5-2.����Լ��ۼ��������ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.�����Լ��ۼ����������ݡ�
	if(is_data_generated){
		//a.����ǰ��Ӧ���ڵ�Һ��߶�ת��Ϊ������岽����
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.�Լ��ۼ����������ݡ�
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_spit_volume(get_reagent_volume(reagent_type));
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.�ۼƵ�ǰ��Ӧ���е�Һ�������
		liquid_volume_in_reaction_tube+=get_reagent_volume(reagent_type);
	}
	//6.�Լ�����ϴ������⡢��ֵ��
	//6-1.��ȡ�Լ�����ϴ�����������жϻ�ȡ�Ƿ�ɹ��� 
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
	//6-2.����Լ�����ϴ�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//6-3.�����Լ�����ϴ�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//7.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_add_magnetic_bead_sequence_diagram
 * breif: Ϊ��Ӵ�����Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        liquid_volume_in_reaction_tube - ����/����ķ�Ӧ���ڵ�Һ�������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_add_magnetic_bead_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int /*sequence_diagram_count*/,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.���������㵱ǰ�������������
	ReagentArm::ReagentType magnetic_bead_type=
		ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_1;
	if(MagneticBeadDisc::POSITION_COUNT==get_magnetic_bead_position_no()){
		magnetic_bead_type=ReagentArm::REAGENT_TYPE_MAGNETIC_BEAD_2;
	}
	//2.��������ת������⡢��ֵ��
	//2-1.��ȡ��������ת�����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
			ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION,9);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//2-2.�����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ����
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.���ô�������ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<MagneticBeadDiscRotation*>(action.get())->
			set_position_no(get_magnetic_bead_position_no());
	}
	//3.�Լ�������������⡢��ֵ��
	//3-1.��ȡ�Լ����������������һ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REAGENT_ARM_SUCK,3);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//3-2>.����Լ������������ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3>.�����Լ��������������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_reagent_type(magnetic_bead_type);
		dynamic_cast<ReagentArmSuck*>(action.get())->
			set_suck_volume(get_magnetic_bead_volume());
	}
	//4.��Ӧ����ת������⡢��ֵ��
	//4-1.��ȡ��ǰʱ���з�Ӧ����ת������
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,6);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//4-2.�����Ӧ����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//4-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_ADD_REAGENT);
	}
	//5.�Լ��ۼ���������⡢��ֵ��
	//5-1.��ȡ�Լ��ۼ��������������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REAGENT_ARM_SPIT,3);
	if(!static_cast<bool>(action)){
		return(-4);
	}
	//5-2.����Լ��ۼ��������ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//5-3.�����Լ��ۼ����������ݡ�
	if(is_data_generated){
		//a.����ǰ��Ӧ���ڵ�Һ��߶�ת��Ϊ������岽����
		const double liquid_height_in_reaction_tube=static_cast<
			double>(liquid_volume_in_reaction_tube)/(3.1415926*9.0);
		const double liquid_pulse_in_reaction_tube=
			liquid_height_in_reaction_tube*157.48;
		unsigned int motor_down_steps=0;
		if(liquid_pulse_in_reaction_tube>=0.0){
			motor_down_steps=static_cast<unsigned int>(
				liquid_pulse_in_reaction_tube);
		}
		//b.�Լ��ۼ����������ݡ�
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_spit_volume(get_magnetic_bead_volume());
		dynamic_cast<ReagentArmSpit*>(action.get())->
			set_down_steps(motor_down_steps);
		//c.�ۼƵ�ǰ��Ӧ���е�Һ�������
		liquid_volume_in_reaction_tube+=get_magnetic_bead_volume();
	}
	//6.�Լ�����ϴ������⡢��ֵ��
	//6-1.��ȡ�Լ�����ϴ�����������жϻ�ȡ�Ƿ�ɹ��� 
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_REAGENT_ARM_WASH,3);
	if(!static_cast<bool>(action)){
		return(-5);
	}
	//6-2.����Լ�����ϴ�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//6-3.�����Լ�����ϴ�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//7.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_incubate_sequence_diagram
 * breif: Ϊ�������Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        nth_times_incubate - ����/����ķ���������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_incubate_sequence_diagram(
	SequenceDiagram * /*sequence_diagram*/,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	unsigned int &nth_times_incubate,
	const BOOL /*is_data_generated*/){
	//1.��ȡ��ǰ�ķ���ʱ�䣨����ʱ����Сһ�����ڣ���
	unsigned int incubate_time=get_incubate_time(nth_times_incubate);
	if(0==incubate_time){//ǿ���ų�����ʱ��Ϊ��������
		incubate_time=Timing::TIMING_CYCLE;
	}
	//2.���㵱ǰ�������ĵ���������������������ļ��㷽ʽ����
	const unsigned int cycle_count=static_cast<unsigned int>(
		static_cast<double>(incubate_time)/static_cast<double>(
		Timing::TIMING_CYCLE)+0.5)+1;
	//3.���µ�ǰʱ��ͼ������š�
	current_sequence_diagram_index+=cycle_count;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=current_sequence_diagram_index-
			sequence_diagram_count+1;
	}
	//4.���õ�ǰ�ǵڼ��θ�������Ǳ�����
	++nth_times_incubate;
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_wash_sequence_diagram
 * breif: Ϊ��ϴ���Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        nth_times_wash - ����/�������ϴ������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_wash_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	unsigned int &nth_times_wash,
	const BOOL is_data_generated){
	//1.��Ӧ����ת������⡢��ֵ��
	//1-1.��ȡ��ǰʱ���з�Ӧ����ת������
	SequenceDiagram::PtrToAction action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_REACTION_DISC_ROTATION,5);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.�����Ӧ����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_EXIT);
	}
	//2.��Ӧ��ȡ�ܶ�����⡢��ֵ��
	//2-1.��ȡ��Ӧ��ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.�����Ӧ��ȡ�ܶ����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.���÷�Ӧ��ȡ�ܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfReactionDisc*>(
			action.get())->set_reserve_reaction_disc_hole_flag(
			nth_times_wash!=get_washing_times());
	}
	//3.��ϴ�̷Źܶ�����⡢��ֵ��
	//3-1.��ȡ��ϴ�̷Źܶ����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_WAHSING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.�����ϴ�̷Źܶ����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.������ϴ�̷Źܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.�ۼƵ�ǰ��ϴ������
	++nth_times_wash;
	//5.���µ�ǰʱ��ͼ������š�
	current_sequence_diagram_index+=18;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=current_sequence_diagram_index-
			sequence_diagram_count+1;
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: generate_add_substrate_sequence_diagram
 * breif: Ϊ��ӵ�����Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        substrate_type - ����ĵ������͡�
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        liquid_volume_in_reaction_tube - ����/����ķ�Ӧ���ڵ�Һ�������
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_add_substrate_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	const SubstrateType substrate_type,
	unsigned int &current_sequence_diagram_index,
	unsigned int &liquid_volume_in_reaction_tube,
	const BOOL is_data_generated){
	//1.���������㵱ǰ�������������
	WashingDisc::SubstrateType substrate_type_in_wash_disc=
		WashingDisc::SUBSTRATE_TYPE_AB;
	if(SUBSTRATE_TYPE_C==substrate_type){
		substrate_type_in_wash_disc=
			WashingDisc::SUBSTRATE_TYPE_C;
	}else if(SUBSTRATE_TYPE_BUFFER_SOLUTION==substrate_type){
		substrate_type_in_wash_disc=
			WashingDisc::SUBSTRATE_TYPE_BUFFER_SOLUTION;
	}
	//2.����ϴ����ϴ�������м�⡢��ֵ��
	//2-1.��ȡ��ϴ����ϴ�����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_WASHING_DISC_WASH,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//2-2.�����ϴ����ϴ�����ѱ�ʹ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.������ϴ����ϴ�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<WashingDiscWash*>(action.get())->set_substrate_type(
			substrate_type_in_wash_disc);
		dynamic_cast<WashingDiscWash*>(action.get())->set_substrate_volume(
			get_substrate_volume(substrate_type));
	}
	//3.�ӵ������Һ�󣬸��·�Ӧ���е�Һ�������
	liquid_volume_in_reaction_tube=get_substrate_volume(substrate_type);
	//4.����ʱ��ͼ������š�
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_return_tube_sequence_diagram
 * breif: Ϊ��Ӧ�̻عܲ��Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_return_tube_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.����ϴ��ȡ�ܶ������м�⡢��ֵ��
	//1-1.��ȡ��ϴ��ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[
		current_sequence_diagram_index].get_action(SequenceDiagram::
			ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.�����ϴ��ȡ�ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.������ϴ��ȡ�ܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfWashingDisc*>(action.get())->
			set_stop_position(TransportTong::STOP_POSITION_REACTION_DISC);
	}
	//2.�Է�Ӧ����ת�������м�⡢��ֵ��
	//2-1.��ȡ��Ӧ����ת�����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_REACTION_DISC,4);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.�����Ӧ����ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.���÷�Ӧ����ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_hole_no(
			get_hole_no_in_reaction_disc());
		dynamic_cast<ReactionDiscRotation*>(action.get())->set_position(
			ReactionDisc::POSITION_EXIT);
	}
	//3.�Է�Ӧ�̻عܶ������м�⡢��ֵ��
	//3-1.��ȡ��Ӧ�̻عܶ����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_RETURN_TUBE_TO_REACTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.�����Ӧ�̻عܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.���÷�Ӧ�̻عܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
	}
	//4.����ʱ��ͼ������š�
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//5.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: generate_detect_sequence_diagram
 * breif: Ϊ�����Բ���������Ӧ��ʱ��ͼ��
 * param: sequence_diagram - �����ָ��ʱ��ͼ�����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ��������������
 *        current_sequence_diagram_index - ����/����ĵ�ǰʹ�õ�ʱ��ͼ������š�
 *        is_data_generated - ������Ƿ��������ݱ�־��
 * return: �������ʱ��ͼ�ɹ����򷵻�ֵ�����㡣
 *         �������ʱ��ͼʧ�ܣ��򷵻�ֵС���㡣
 *         ������ɵ�ʱ��ͼ������ʱ���ͻ����ֱ�ӷ���һ��
 */
int TestItem::generate_detect_sequence_diagram(
	SequenceDiagram *sequence_diagram,
	const unsigned int sequence_diagram_count,
	unsigned int &current_sequence_diagram_index,
	const BOOL is_data_generated){
	//1.����ϴ��ȡ�ܶ������м�⡢��ֵ��
	//1-1.��ȡ��ϴ��ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
	SequenceDiagram::PtrToAction action=sequence_diagram[current_sequence_diagram_index].
		get_action(SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_WASHING_DISC,1);
	if(!static_cast<bool>(action)){
		return(-1);
	}
	//1-2.�����ϴ��ȡ�ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//1-3.������ϴ��ȡ�ܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(_key);
		dynamic_cast<TakeTubeOutOfWashingDisc*>(action.get())->set_stop_position(
			TransportTong::STOP_POSITION_DETECTION_DISC);
	}
	//2.�Լ������ת�������м�⡢��ֵ��
	//2-1.��ȡ�������ת�����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,3);
	if(!static_cast<bool>(action)){
		return(-2);
	}
	//2-2.����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//2-3.���ü������ת�������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(get_key());
		dynamic_cast<DetectionDiscRotation*>(action.get())->set_position(
			DetectionDisc::POSITION_ENTRY);
	}
	//3.�Լ���̷Źܶ������м�⡢��ֵ��
	//3-1.��ȡ����̷Źܶ����������жϻ�ȡ�Ƿ�ɹ���
	action=sequence_diagram[current_sequence_diagram_index].get_action(
		SequenceDiagram::ACTION_ID_PUT_TUBE_IN_DETECTION_DISC,1);
	if(!static_cast<bool>(action)){
		return(-3);
	}
	//3-2.�������̷Ź����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
	if(Action::STATUS_ENABLED==action->get_status()){
		return(1);
	}
	//3-3.���ü���̷Źܶ������ݡ�
	if(is_data_generated){
		action->set_status(Action::STATUS_ENABLED);
		action->set_test_item_key(get_key());
	}
	//4.���������ʱ��С�ڵ���5�룬��Ե�ǰ��Ŀ�������м�⡣
	if(get_detection_incubation_time()<=5000){
		//4-1.�Լ������ת�������м�⡢��ֵ��
		//4-1-1.��ȡ�������ת�����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,4);
		if(!static_cast<bool>(action)){
			return(-4);
		}
		//4-1-2.����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//4-1-3.���ü������ת�������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_DETECTION);
		}
		//4-2.�Լ���̼�⶯�����м�⡢��ֵ��
		//4-2-1.��ȡ����̼�⶯���������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECT,2);
		if(!static_cast<bool>(action)){
			return(-5);
		}
		//4-2-2.�������̼�⶯���ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//4-2-3.���ü���̼�⶯�����ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//5.����ʱ��ͼ������š�
	++current_sequence_diagram_index;
	if(current_sequence_diagram_index>=sequence_diagram_count){
		current_sequence_diagram_index=0;
	}
	//6.���������ʱ��С�ڵ���5�룬��Ե�ǰ��Ŀ�����ӹܡ�
	if(get_detection_incubation_time()<=5000){
		//6-1.�Լ������ת�������м�⡢��ֵ��
		//6-1-1.��ȡ�������ת�����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,1);
		if(!static_cast<bool>(action)){
			return(-6);
		}
		//6-1-2.����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-1-3.���ü������ת�������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_EXIT);
		}
		//6-2.��ת�˱ۼ����ȡ�ܶ������м�⡢��ֵ��
		//6-2-1.��ȡת�˱�ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,2);
		if(!static_cast<bool>(action)){
			return(-7);
		}
		//6-2-2.���ת�˱�ȡ�ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-2-3.����ת�˱�ȡ�ܶ������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//6-3.��ת�˱۶��ܶ������м�⡢��ֵ��
		//6-3-1.��ȡת�˱۶��ܶ����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DISCARD_TUBE,2);
		if(!static_cast<bool>(action)){
			return(-8);
		}
		//6-3-2.���ת�˱۶��ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//6-3-3.����ת�˱۶��ܶ������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//7.���������ʱ�����5�루��30���㣩����Ե�ǰ��Ŀ���м�⡢�ӹܡ�
	else{
		//7-1.�Լ������ת�������м�⡢��ֵ��
		//7-1-1.��ȡ�������ת�����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,2);
		if(!static_cast<bool>(action)){
			return(-9);
		}
		//7-1-2.����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-1-3.���ü������ת�������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_DETECTION);
		}
		//7-2.�Լ���̼�⶯�����м�⡢��ֵ��
		//7-2-1.��ȡ����̼�⶯���������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECT,2);
		if(!static_cast<bool>(action)){
			return(-10);
		}
		//7-2-2.�������̼�⶯���ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-2-3.���ü���̼�⶯�����ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//7-3.�Լ������ת�������м�⡢��ֵ��
		//7-3-1.��ȡ�������ת�����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DETECTION_DISC_ROTATION,5);
		if(!static_cast<bool>(action)){
			return(-11);
		}
		//7-3-2.����������ת�����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-3-3.���ü������ת�������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
			dynamic_cast<DetectionDiscRotation*>(action.get())->
				set_position(DetectionDisc::POSITION_EXIT);
		}
		//7-4.����ʱ��ͼ������š�
		++current_sequence_diagram_index;
		if(current_sequence_diagram_index>=sequence_diagram_count){
			current_sequence_diagram_index=0;
		}
		//7-5.��ת�˱ۼ����ȡ�ܶ������м�⡢��ֵ��
		//7-5-1.��ȡת�˱�ȡ�ܶ����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_TAKE_TUBE_OUT_OF_DETECTION_DISC,1);
		if(!static_cast<bool>(action)){
			return(-12);
		}
		//7-5-2.���ת�˱�ȡ�ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-5-3.����ת�˱�ȡ�ܶ������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
		//7-6.��ת�˱۶��ܶ������м�⡢��ֵ��
		//7-6-1.��ȡת�˱۶��ܶ����������жϻ�ȡ�Ƿ�ɹ���
		action=sequence_diagram[current_sequence_diagram_index].get_action(
			SequenceDiagram::ACTION_ID_DISCARD_TUBE,1);
		if(!static_cast<bool>(action)){
			return(-13);
		}
		//7-6-2.���ת�˱۶��ܶ����ѱ�ռ�ã���ֱ�ӷ��س�ͻ��
		if(Action::STATUS_ENABLED==action->get_status()){
			return(1);
		}
		//7-6-3.����ת�˱۶��ܶ������ݡ�
		if(is_data_generated){
			action->set_status(Action::STATUS_ENABLED);
			action->set_test_item_key(get_key());
		}
	}
	//8.�������е��˳ɹ����ء�
	return(0);
}