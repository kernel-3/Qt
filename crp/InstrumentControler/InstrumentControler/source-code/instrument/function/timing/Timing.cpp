#include"stdafx.h"
#include"Timing.h"
#include"SequenceDiagram.h"
#include"../../../../../../include/mfctoolkit/tool/MtAutoDeleter.h"
#include"Action.h"
#include"../../../common/Logs.h"
#include"../../Instrument.h"
#include"../../component/Components.h"
#include"../../component/WashingDisc.h"
#include"../../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../export/TestItem.h"
#include<Process.h>
#include<MMSystem.h>
#include<thread>
#include<assert.h>
#include<algorithm>

/**
 * name: ComparePendingTestItem
 * brief: �Ƚϴ�����Ŀ��С��
 * param: left - ����ָ��ȽϵĴ�����Ŀ������ָ�롣
 *        right - ����ָ��ȽϵĴ�����Ŀ������ָ�롣
 * return: ���leftС��right����true�����򷵻�false��
 * author: yameng_he
 * date: 2016-03-09
 */
static bool ComparePendingTestItem(const Timing::PtrToTestItem &left,
	const Timing::PtrToTestItem &right){
	//1.������������Ϸ���
	assert(static_cast<bool>(left)&&static_cast<bool>(right));
	//2.���رȽϽ����
	return((left->get_key())<(right->get_key()));
}

/**
 * name: clear_test_item_in_sequence_diagrams
 * brief: ��ָ���Ĳ�����Ŀ��ض�����ʱ��ͼ��ɾ����
 * param: sequence_diagrams - �����ʱ��ͼ����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ������
 *        test_item_key - ����Ĳ�����Ŀ������
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * author: yameng_he
 * date: 2016-01-12.
 */
static int clear_test_item_in_sequence_diagrams(SequenceDiagram *sequence_diagrams,
	const unsigned int sequence_diagram_count,const unsigned int test_item_key){
	//1.��⵱ǰ��������Ƿ�Ϸ���
	if((0==sequence_diagrams)||(0==sequence_diagram_count)||(0==test_item_key)){
		return(-1);
	}
	//2.����ʱ��ͼ���飬���ָ����Ŀ��ʱ��ͼ��
	for(unsigned int index=0;index<sequence_diagram_count;++index){
		if(sequence_diagrams[index].clear(test_item_key)<0){
			return(-2);
		}
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

//static variables
unsigned int Timing::_test_item_key=1;

/**
 * name: Timing
 * brief: ���캯����
 * param: --
 * return: --
 */
Timing::Timing(void)
	:Function()
	,_timing(0)
	,_lock(new MtLock)
	,_timing_stopping_flag(FALSE)
	,_pending_test_item_queue()
	,_tested_item_map(){
}

/**
 * name: ~Timing
 * brief: ����������
 * param: --
 * return: --
 */
Timing::~Timing(void){
	stop();
	delete _lock;
}

/**
 * name: push_back_pending_test_item
 * brief: �������Ŀ����β����Ӵ�����Ŀ��
 * param: test_item - ����Ĵ�����Ŀ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Timing::push_back_pending_test_item(const TestItem &test_item){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.����������Ŀ�������жϴ����Ƿ�ɹ���
	PtrToTestItem test_item_pointer(new TestItem(test_item));
	if(!static_cast<bool>(test_item_pointer)){
		return(-1);
	}
	test_item_pointer->set_key(_test_item_key);
	//3.��⵱ǰ׼�����ɵĲ�����Ŀ�����Ƿ��ͻ��
	if(std::binary_search(_pending_test_item_queue.begin(),
		_pending_test_item_queue.end(),test_item_pointer,
		ComparePendingTestItem)){
		return(-2);
	}
	//4.���浱ǰ������Ŀ��
	_pending_test_item_queue.push_back(test_item_pointer);
	//5.����������Ŀ������Ϊ��һ����Ӳ�����Ŀ��׼����
	++_test_item_key;
	if(_test_item_key>MAXIMUM_TEST_ITEM_KEY){
		_test_item_key=1;
	}
	//6.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: get_tested_item
 * brief: ��ȡָ�����Ѳ���Ŀ��
 * param: tested_item_key - ������Ѳ���Ŀ������
 * return: �������ִ�гɹ�������ָ�����Ѳ���Ŀ�����򷵻ؿ�ָ�롣
 */
Timing::PtrToTestItem Timing::get_tested_item(
	const unsigned int tested_item_key){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.��ȡָ�����Ѳ���Ŀ��
	TestedItemMap::iterator tested_item_iterator=
		_tested_item_map.find(tested_item_key);
	//3.���ָ�����Ѳ���Ŀ�����ڣ���ֱ�ӷ��ؿ�ָ�롣
	if(_tested_item_map.end()==tested_item_iterator){
		return(PtrToTestItem());
	}
	//4.����ָ�����Ѳ���Ŀ��
	return(tested_item_iterator->second);
}

/**
 * name: open
 * brief: ��ʱ��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �˺�����֧�ֶ��̡߳�
 */
int Timing::start(){
	//1.ֹͣ��ǰ�������е�ʱ��
	stop();
	//2.����ʱ�򣬲����жϿ����Ƿ�ɹ���
	_timing=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::timing,this,0,0));
	if((0==_timing)||(INVALID_HANDLE_VALUE==_timing)){
		_timing=0;
		return(-1);
	}
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: stop
 * brief: ֹͣ��ǰ�豸��ʱ���ܡ�
 * param: --
 * return: --
 * remark: �˺�����֧�ֶ��̡߳�
 */
void Timing::stop(){
	//1.�����ǰʱ���������У�������������ֹͣ��
	if(0!=_timing){
		//1-1.����ʱ��ֹͣ��
		set_timing_stopping_flag(TRUE);
		//1-2.�ȴ�ʱ���˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_timing,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_timing,0);
		}
		//1-3.�رյ�ǰʱ��
		CloseHandle(_timing);
		_timing=0;
	}
	//2.�������е��ˣ�����ʱ���Ǳ�����
	set_timing_stopping_flag(FALSE);
}

/**
 * name: timing
 * brief: ʱ���̣߳�����ʱ���ʵ�������
 * param: parameter - ���뵱ǰ�̵߳Ĳ�����
 * return: ���Ƿ����㡣
 */
unsigned int __stdcall Timing::timing(void *parameter){
	Timing *timing=reinterpret_cast<Timing*>(parameter);
	timing->timing();
	return(0);
}

/**
 * name: timing
 * brief: ʱ���������������ʵ��ʱ���߳�
 *        �ľ�������
 * param: --
 * return: --
 */
void Timing::timing(){
	//1.������ǰ�������������
	unsigned int trigger_time=0;
	unsigned int sequence_diagram_index=0;
	SequenceDiagram *sequence_diagrams=new 
		SequenceDiagram[SEQUENCE_DIAGRAM_COUNT];
	MtAutoDeleter<SequenceDiagram> auto_deleter(
		sequence_diagrams,MtAutoDeleter<SequenceDiagram>::
		POINTER_TYPE_ARRAY);
	//2.�����豸������ݡ�
	(((Instrument::instance())->get_components())->
		get_washing_disc())->reset_hole_no_in_entry();
	//3.ѭ��ʵ��ʱ���ܡ�
	while(1){
		//3-1.��������ر�ʱ����ֱ������ʱ��ʵ��ѭ����
		if(get_timing_stopping_flag()){
			break;
		}
		//3-2.ѭ���Ե�ǰʱ��ͼ�еĶ������д�����
		while(1){
			//3-2-1.��д�����־��
			if(0==trigger_time){
				CString log(_T(""));
				log.Format(_T("Event %s��%ld���� ===================ʱ��ʼ================="),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
			}
			//3-2-2.��������ر�ʱ����ֱ������ʱ��ʵ��ѭ����
			if(get_timing_stopping_flag()){
				break;
			}
			//3-2-3.����ʱ��ͼ�����Ҽ�¼���������
			unsigned int trigger_error=0;
			unsigned int test_item_key=0;
			const int trigger_result=sequence_diagrams[sequence_diagram_index].
				trigger(trigger_time,trigger_error,test_item_key);
			//3-2-4.��������ر�ʱ����ֱ������ʱ��ʵ��ѭ����
			if(get_timing_stopping_flag()){
				break;
			}
			//3-2-5.�����ǰ����ʱ��ͼ��������
			if(trigger_result<0){
				//3-2-5-1.�����ǰ����Ϊ������Ч����
				if(Action::ERROR_NOT_VALID==trigger_error){
					//a.������Ϣ��֪ͨ������ʱ����������Ч����
					//unfinished: ֪ͨ������ʱ����������Ч�������������������̡߳�
					//b.���ǰ�߳�������ֹ���С�
					set_timing_stopping_flag(TRUE);
					//c.������ǰѭ����
					break;
				}
				//3-2-5-2.�����ǰ����Ϊ��ʱ����
				else if(Action::ERROR_TIMEOUT_T==trigger_error){
					//a.�ȴ�100���롣
					timeBeginPeriod(1);
					Sleep(100);
					timeEndPeriod(1);
					//b.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//c.���´���ʱ��ͼ�������Ƿ��ܹ������ɹ�����
					else{
						continue;
					}
				}
				//3-2-5-3.�����ǰ����Ϊ���س�ʱ����
				else if(Action::ERROR_SERIOUS_TIMEOUT==trigger_error){
					//a.������Ϣ��֪ͨ������ʱ������ʱ����
					//unfinished: ֪ͨ������ʱ������ʱ�������������������̡߳�
					//b.���ǰʱ���߳�����������
					set_timing_stopping_flag(TRUE);
					//c.������ǰѭ����
					break;
				}
				//3-2-5-4.�����ǰ����Ϊ�Թܲ��޹ܴ���
				else if(Action::ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.������ͣ������ǡ�
					//unfinshed: ��ͣ�������ȴ��û���ӺĲġ�
					//c.���Զ����������ˡ�
					//unfinshed: ���Զ����������ˡ�
					//d.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//e.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-5.�����ǰ����ΪͨѶ����
				else if(Action::ERROR_COMMUNICATION==trigger_error){
					//a.������Ϣ��֪ͨ������ʱ����ͨѶ����
					//unfinished: ֪ͨ������ʱ����ͨѶ�������������������̡߳�
					//b.���ǰʱ���߳�����������
					set_timing_stopping_flag(TRUE);
					//c.������ǰѭ����
					break;
				}
				//3-2-5-6.�����ǰ����Ϊ��Ӧ�̽���λ���ܳ�ͻ��
				else if(Action::ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.���Զ����������ˡ�
					//unfinished: ���Զ����������ˣ�ʹ����һ���������²��뵱ǰ��Ŀ��
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-7.�����ǰ����Ϊ�Źܽ��뷴Ӧ�̽���λʧ�ܡ�
				else if(Action::ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.���Զ����������ˡ�
					//unfinished: ���Զ����������ˣ�ʹ����һ���������²��뵱ǰ��Ŀ��
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-8.ת��ץ����ϴ��ȡ��ʱ����⵽����̳���λ�޹ܡ�
				else if(Action::ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-9.ת��ץ����ϴ��ȡ��ʧ�ܴ���
				else if(Action::ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.������ϴ�̳���λ�Ϲܡ�
					//unfinished: ������ϴ�̳���λ�Ϲܡ�
					//d.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//e.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-10.�����ǰ����Ϊ�عܵ���Ӧ�̳�ͻ����
				else if(Action::ERROR_RETURN_TUBE_TO_RECTION_DISC_FAILED==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-11.�����ǰ����Ϊ��Ӧ�̳���λ�޹ܴ���
				else if(Action::ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-12.�����ǰ����Ϊ�Źܵ���ϴ��ʱ��⵽��ͻ����
				else if(Action::ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,SEQUENCE_DIAGRAM_COUNT,
						test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.������ϴ�̽���λ�ϵķϹܡ�
					//unfinished: ������ϴ�̽���λ�ϵķϹܡ�
					//d.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//e.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-13.�����ǰ����Ϊת��ץ�ַ�Ӧ��ȡ��ʧ�ܴ���
				else if(Action::ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,SEQUENCE_DIAGRAM_COUNT,
						test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-14.�����ǰ����Ϊת��ץ�ַŹܵ���ϴ��ʧ�ܴ���
				else if(Action::ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED==trigger_error){
					//a.�����ǰʱ��ͼ��ָ����Ŀ��ʶ�����ж�����Ϣ��
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//unfinished: ֪ͨ���Զ��У��˲�����Ŀʧ�ܡ�
					//c.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//d.���´���ʱ��ͼ��
					else{
						continue;//����������ǰʱ��������Ŀ�Ķ�����
					}
				}
				//3-2-5-15.�����ǰ����Ϊ����δ֪����
				else{
					//a.��д��־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� Timing::timing ��⵽ʱ��ͼ�з�������δ֪����"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//b.���ǰʱ���߳�����������
					set_timing_stopping_flag(TRUE);//���ǰʱ���߳�������ֹ��
					//c.������ǰѭ����
					break;
				}
			}
			//2-2-6.�����ǰ����ʱ��ͼ�ɹ���
			else{

				if(22000==trigger_time){
					PtrToTestItem pending_test_item=pop_front_pending_test_item();
					if(static_cast<bool>(pending_test_item)){
						pending_test_item->generate_sequence_diagram(
							sequence_diagrams,Timing::SEQUENCE_DIAGRAM_COUNT,
							sequence_diagram_index);
					}
					add_tested_item(pending_test_item);
				}

				//a.����ʱ���Լӡ�
				trigger_time+=TRIGGER_INTERVAL;
				//b.�����ǰδ�ִ����ڽ���ʱ�䡣
				if(trigger_time<=TIMING_CYCLE){
					break;//������ǰ��ѭ��������
				}
				//c.�����ǰʱ���Ѿ��ִ����ڽ���ʱ�䡣
				else{
					//c-1.����ʱ�����㡣
					trigger_time=0;
					//c-2.����ǰһ��ʱ��
					int last_sequence_diagram_index=static_cast<
						int>(sequence_diagram_index)-1;
					if(last_sequence_diagram_index<0){
						last_sequence_diagram_index=SEQUENCE_DIAGRAM_COUNT-1;
					}
					sequence_diagrams[last_sequence_diagram_index].reset();
					//c-3.ʱ��ͼ������
					++sequence_diagram_index;
					if(sequence_diagram_index>=SEQUENCE_DIAGRAM_COUNT){
						sequence_diagram_index=0;
					}
					//c-4.�������������ֹ��ǰʱ��
					if(get_timing_stopping_flag()){
						break;
					}
					//c-5.���Ͻ��봥��ʱ��Ϊ��Ĵ�����
					else{
						continue;
					}
				}
			}
		}
		//2-3.�������������ֹ��ǰʱ��
		if(get_timing_stopping_flag()){
			break;
		}
		//2-4.�ȴ�1���ӡ�
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//2-5.�������������ֹ��ǰʱ��
		if(get_timing_stopping_flag()){
			break;
		}
	}
}

/**
 * name: set_timing_stopping_flag
 * brief: ����ʱ��ֹͣ��־��
 * param: flag - �����ʱ��ֹͣ��־��
 * return: --
 */
void Timing::set_timing_stopping_flag(const BOOL flag){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ùر�ʱ���־��
	_timing_stopping_flag=flag;
}

/**
 * name: get_timing_stopping_flag
 * brief: ��ȡʱ��ֹͣ��־��
 * param: --
 * return: ����ʱ��ֹͣ��־��
 */
BOOL Timing::get_timing_stopping_flag() const{
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���عر�ʱ���־��
	return(_timing_stopping_flag);
}

/**
 * name: pop_front_pending_test_item
 * brief: ������������е���λ������Ŀ��
 * param: --
 * return: �������ִ�гɹ�����ָ������������λ������Ŀ������ָ�룬
 *         ���򷵻ؿ�ָ�롣
 */
Timing::PtrToTestItem Timing::pop_front_pending_test_item(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�������Ϊ��,��ֱ�ӷ��ء�
	if(_pending_test_item_queue.empty()){
		return(PtrToTestItem());
	}
	//3.��¼��ǰ�����Ĵ�����Ŀ��
	PtrToTestItem pending_test_item=
		_pending_test_item_queue.front();
	//4.������ǰ��������еĴ�����Ŀ��
	_pending_test_item_queue.pop_front();
	//5.���ص����Ĵ�����Ŀ��
	return(pending_test_item);
}

/**
 * name: add_tested_item
 * brief: ���Ѳ���Ŀӳ�������һ���Ѳ���Ŀ��
 * param: tested_item - ����ָ���Ѳ���Ŀ������ָ�롣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Timing::add_tested_item(PtrToTestItem &tested_item){
	//1.�����������Ƿ�Ϸ���
	if(!static_cast<bool>(tested_item)){
		return(-1);
	}
	//2.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.��⵱ǰӳ�����Ƿ��Ѿ����ڸò�����Ŀ��
	if(_tested_item_map.end()!=_tested_item_map.find(
		tested_item->get_key())){
		return(-2);
	}
	//4.���Ѳ���Ŀӳ���б������Ŀ��
	_tested_item_map[tested_item->get_key()]=tested_item;
	//5.�������е��˳ɹ����ء�
	return(0);
}