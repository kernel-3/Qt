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
 * brief: 比较待测项目大小。
 * param: left - 输入指向比较的待测项目的智能指针。
 *        right - 输入指向比较的待测项目的智能指针。
 * return: 如果left小于right返回true，否则返回false。
 * author: yameng_he
 * date: 2016-03-09
 */
static bool ComparePendingTestItem(const Timing::PtrToTestItem &left,
	const Timing::PtrToTestItem &right){
	//1.断言输入参数合法。
	assert(static_cast<bool>(left)&&static_cast<bool>(right));
	//2.返回比较结果。
	return((left->get_key())<(right->get_key()));
}

/**
 * name: clear_test_item_in_sequence_diagrams
 * brief: 将指定的测试项目相关动作从时序图中删除。
 * param: sequence_diagrams - 输入的时序图数组指针。
 *        sequence_diagram_count - 输入的时序图个数。
 *        test_item_key - 输入的测试项目主键。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 * author: yameng_he
 * date: 2016-01-12.
 */
static int clear_test_item_in_sequence_diagrams(SequenceDiagram *sequence_diagrams,
	const unsigned int sequence_diagram_count,const unsigned int test_item_key){
	//1.检测当前输入参数是否合法。
	if((0==sequence_diagrams)||(0==sequence_diagram_count)||(0==test_item_key)){
		return(-1);
	}
	//2.遍历时序图数组，清除指定项目的时序图。
	for(unsigned int index=0;index<sequence_diagram_count;++index){
		if(sequence_diagrams[index].clear(test_item_key)<0){
			return(-2);
		}
	}
	//3.程序运行到此成功返回。
	return(0);
}

//static variables
unsigned int Timing::_test_item_key=1;

/**
 * name: Timing
 * brief: 构造函数。
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
 * brief: 析构函数。
 * param: --
 * return: --
 */
Timing::~Timing(void){
	stop();
	delete _lock;
}

/**
 * name: push_back_pending_test_item
 * brief: 向待测项目队列尾部添加待测项目。
 * param: test_item - 输入的待测项目。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Timing::push_back_pending_test_item(const TestItem &test_item){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.创建测试项目，并且判断创建是否成功。
	PtrToTestItem test_item_pointer(new TestItem(test_item));
	if(!static_cast<bool>(test_item_pointer)){
		return(-1);
	}
	test_item_pointer->set_key(_test_item_key);
	//3.检测当前准备生成的测试项目主键是否冲突。
	if(std::binary_search(_pending_test_item_queue.begin(),
		_pending_test_item_queue.end(),test_item_pointer,
		ComparePendingTestItem)){
		return(-2);
	}
	//4.保存当前待测项目。
	_pending_test_item_queue.push_back(test_item_pointer);
	//5.递增测试项目主键，为下一次添加测试项目做准备。
	++_test_item_key;
	if(_test_item_key>MAXIMUM_TEST_ITEM_KEY){
		_test_item_key=1;
	}
	//6.程序运行到此成功返回。
	return(0);
}

/**
 * name: get_tested_item
 * brief: 获取指定的已测项目。
 * param: tested_item_key - 输入的已测项目主键。
 * return: 如果函数执行成功，返回指定的已测项目，否则返回空指针。
 */
Timing::PtrToTestItem Timing::get_tested_item(
	const unsigned int tested_item_key){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.获取指定的已测项目。
	TestedItemMap::iterator tested_item_iterator=
		_tested_item_map.find(tested_item_key);
	//3.如果指定的已测项目不存在，则直接返回空指针。
	if(_tested_item_map.end()==tested_item_iterator){
		return(PtrToTestItem());
	}
	//4.返回指定的已测项目。
	return(tested_item_iterator->second);
}

/**
 * name: open
 * brief: 打开时序。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 此函数不支持多线程。
 */
int Timing::start(){
	//1.停止当前正在运行的时序。
	stop();
	//2.开启时序，并且判断开启是否成功。
	_timing=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::timing,this,0,0));
	if((0==_timing)||(INVALID_HANDLE_VALUE==_timing)){
		_timing=0;
		return(-1);
	}
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: stop
 * brief: 停止当前设备的时序功能。
 * param: --
 * return: --
 * remark: 此函数不支持多线程。
 */
void Timing::stop(){
	//1.如果当前时序正在运行，则命令其立即停止。
	if(0!=_timing){
		//1-1.命令时序停止。
		set_timing_stopping_flag(TRUE);
		//1-2.等待时序退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_timing,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_timing,0);
		}
		//1-3.关闭当前时序。
		CloseHandle(_timing);
		_timing=0;
	}
	//2.程序运行到此，重置时序标记变量。
	set_timing_stopping_flag(FALSE);
}

/**
 * name: timing
 * brief: 时序线程，负责时序的实现与管理。
 * param: parameter - 输入当前线程的参数。
 * return: 总是返回零。
 */
unsigned int __stdcall Timing::timing(void *parameter){
	Timing *timing=reinterpret_cast<Timing*>(parameter);
	timing->timing();
	return(0);
}

/**
 * name: timing
 * brief: 时序函数，它负责具体实现时序线程
 *        的具体任务。
 * param: --
 * return: --
 */
void Timing::timing(){
	//1.声明当前操作所需变量。
	unsigned int trigger_time=0;
	unsigned int sequence_diagram_index=0;
	SequenceDiagram *sequence_diagrams=new 
		SequenceDiagram[SEQUENCE_DIAGRAM_COUNT];
	MtAutoDeleter<SequenceDiagram> auto_deleter(
		sequence_diagrams,MtAutoDeleter<SequenceDiagram>::
		POINTER_TYPE_ARRAY);
	//2.重置设备相关数据。
	(((Instrument::instance())->get_components())->
		get_washing_disc())->reset_hole_no_in_entry();
	//3.循环实现时序功能。
	while(1){
		//3-1.如果期望关闭时序，则直接跳出时序实现循环。
		if(get_timing_stopping_flag()){
			break;
		}
		//3-2.循环对当前时序图中的动作进行触发。
		while(1){
			//3-2-1.书写相关日志。
			if(0==trigger_time){
				CString log(_T(""));
				log.Format(_T("Event %s（%ld）： ===================时序开始================="),
					(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),timeGetTime());
				Logs::instance()->write(Logs::NAME_EVENT,log);
			}
			//3-2-2.如果期望关闭时序，则直接跳出时序实现循环。
			if(get_timing_stopping_flag()){
				break;
			}
			//3-2-3.触发时序图，并且记录触发结果。
			unsigned int trigger_error=0;
			unsigned int test_item_key=0;
			const int trigger_result=sequence_diagrams[sequence_diagram_index].
				trigger(trigger_time,trigger_error,test_item_key);
			//3-2-4.如果期望关闭时序，则直接跳出时序实现循环。
			if(get_timing_stopping_flag()){
				break;
			}
			//3-2-5.如果当前触发时序图发生错误。
			if(trigger_result<0){
				//3-2-5-1.如果当前触发为动作无效错误。
				if(Action::ERROR_NOT_VALID==trigger_error){
					//a.发送消息，通知主程序时序发生动作无效错误。
					//unfinished: 通知主程序时序发生动作无效错误，命令主程序清理线程。
					//b.命令当前线程立即终止运行。
					set_timing_stopping_flag(TRUE);
					//c.跳出当前循环。
					break;
				}
				//3-2-5-2.如果当前触发为超时错误。
				else if(Action::ERROR_TIMEOUT_T==trigger_error){
					//a.等待100毫秒。
					timeBeginPeriod(1);
					Sleep(100);
					timeEndPeriod(1);
					//b.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//c.重新触发时序图（重试是否能够触发成功）。
					else{
						continue;
					}
				}
				//3-2-5-3.如果当前触发为严重超时错误。
				else if(Action::ERROR_SERIOUS_TIMEOUT==trigger_error){
					//a.发送消息，通知主程序时序发生超时错误。
					//unfinished: 通知主程序时序发生超时错误，命令主程序清理线程。
					//b.命令当前时序线程立即结束。
					set_timing_stopping_flag(TRUE);
					//c.跳出当前循环。
					break;
				}
				//3-2-5-4.如果当前触发为试管仓无管错误。
				else if(Action::ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.设置暂停进样标记。
					//unfinshed: 暂停进样，等待用户添加耗材。
					//c.测试队列索引回退。
					//unfinshed: 测试队列索引回退。
					//d.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//e.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-5.如果当前触发为通讯错误。
				else if(Action::ERROR_COMMUNICATION==trigger_error){
					//a.发送消息，通知主程序时发生通讯错误。
					//unfinished: 通知主程序时序发生通讯错误，命令主程序清理线程。
					//b.命令当前时序线程立即结束。
					set_timing_stopping_flag(TRUE);
					//c.跳出当前循环。
					break;
				}
				//3-2-5-6.如果当前触发为反应盘进管位进管冲突。
				else if(Action::ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.测试队列索引回退。
					//unfinished: 测试队列索引回退，使得下一个周期重新插入当前项目。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-7.如果当前触发为放管进入反应盘进管位失败。
				else if(Action::ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.测试队列索引回退。
					//unfinished: 测试队列索引回退，使得下一个周期重新插入当前项目。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-8.转运抓手清洗盘取管时，检测到检测盘出管位无管。
				else if(Action::ERROR_WITHOUT_TUBE_WHEN_TAKE_TUBE_OUT_OF_WASHING_DISC==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-9.转运抓手清洗盘取管失败错误。
				else if(Action::ERROR_TAKE_TUBE_OUT_FROM_WASHING_DISC_FAILED==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.处理清洗盘出管位废管。
					//unfinished: 处理清洗盘出管位废管。
					//d.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//e.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-10.如果当前触发为回管到反应盘冲突错误。
				else if(Action::ERROR_RETURN_TUBE_TO_RECTION_DISC_FAILED==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-11.如果当前触发为反应盘出管位无管错误。
				else if(Action::ERROR_WITHOUT_TUBE_WHEN_TAKING_TUBE_OUT_OF_REACTION_DISC==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-12.如果当前触发为放管到清洗盘时检测到冲突错误。
				else if(Action::ERROR_PUT_TUBE_IN_WASHING_DISC_CONFLICT==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,SEQUENCE_DIAGRAM_COUNT,
						test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.处理清洗盘进管位上的废管。
					//unfinished: 处理清洗盘进管位上的废管。
					//d.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//e.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-13.如果当前触发为转运抓手反应盘取管失败错误。
				else if(Action::ERROR_TAKE_TUBE_OUT_OF_REACTION_DISC_FAILED==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,SEQUENCE_DIAGRAM_COUNT,
						test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-14.如果当前触发为转运抓手放管到清洗盘失败错误。
				else if(Action::ERROR_PUT_TUBE_IN_WASHING_DISC_FAILED==trigger_error){
					//a.清除当前时序图中指定项目标识的所有动作信息。
					clear_test_item_in_sequence_diagrams(sequence_diagrams,
						SEQUENCE_DIAGRAM_COUNT,test_item_key);
					//b.通知测试队列，此测试项目失败。
					//unfinished: 通知测试队列，此测试项目失败。
					//c.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//d.重新触发时序图。
					else{
						continue;//继续触发当前时刻其它项目的动作。
					}
				}
				//3-2-5-15.如果当前触发为其它未知错误。
				else{
					//a.书写日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： Timing::timing 检测到时序图中发生动作未知错误！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//b.命令当前时序线程立即结束。
					set_timing_stopping_flag(TRUE);//命令当前时序线程立即终止。
					//c.跳出当前循环。
					break;
				}
			}
			//2-2-6.如果当前触发时序图成功。
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

				//a.触发时间自加。
				trigger_time+=TRIGGER_INTERVAL;
				//b.如果当前未抵达周期结束时间。
				if(trigger_time<=TIMING_CYCLE){
					break;//跳出当前的循环触发。
				}
				//c.如果当前时间已经抵达周期结束时间。
				else{
					//c-1.触发时间清零。
					trigger_time=0;
					//c-2.重置前一个时序。
					int last_sequence_diagram_index=static_cast<
						int>(sequence_diagram_index)-1;
					if(last_sequence_diagram_index<0){
						last_sequence_diagram_index=SEQUENCE_DIAGRAM_COUNT-1;
					}
					sequence_diagrams[last_sequence_diagram_index].reset();
					//c-3.时序图递增。
					++sequence_diagram_index;
					if(sequence_diagram_index>=SEQUENCE_DIAGRAM_COUNT){
						sequence_diagram_index=0;
					}
					//c-4.如果期望立即终止当前时序。
					if(get_timing_stopping_flag()){
						break;
					}
					//c-5.马上进入触发时间为零的触发。
					else{
						continue;
					}
				}
			}
		}
		//2-3.如果期望立即终止当前时序。
		if(get_timing_stopping_flag()){
			break;
		}
		//2-4.等待1秒钟。
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//2-5.如果期望立即终止当前时序。
		if(get_timing_stopping_flag()){
			break;
		}
	}
}

/**
 * name: set_timing_stopping_flag
 * brief: 设置时序停止标志。
 * param: flag - 输入的时序停止标志。
 * return: --
 */
void Timing::set_timing_stopping_flag(const BOOL flag){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.设置关闭时序标志。
	_timing_stopping_flag=flag;
}

/**
 * name: get_timing_stopping_flag
 * brief: 获取时序停止标志。
 * param: --
 * return: 返回时序停止标志。
 */
BOOL Timing::get_timing_stopping_flag() const{
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.返回关闭时序标志。
	return(_timing_stopping_flag);
}

/**
 * name: pop_front_pending_test_item
 * brief: 弹出待测队列中的首位待测项目。
 * param: --
 * return: 如果函数执行成功返回指向待测队列中首位待测项目的智能指针，
 *         否则返回空指针。
 */
Timing::PtrToTestItem Timing::pop_front_pending_test_item(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前待测队列为空,则直接返回。
	if(_pending_test_item_queue.empty()){
		return(PtrToTestItem());
	}
	//3.记录当前弹出的待测项目。
	PtrToTestItem pending_test_item=
		_pending_test_item_queue.front();
	//4.弹出当前待测队列中的待测项目。
	_pending_test_item_queue.pop_front();
	//5.返回弹出的待测项目。
	return(pending_test_item);
}

/**
 * name: add_tested_item
 * brief: 向已测项目映射中添加一个已测项目。
 * param: tested_item - 输入指向已测项目的智能指针。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Timing::add_tested_item(PtrToTestItem &tested_item){
	//1.检测输入参数是否合法。
	if(!static_cast<bool>(tested_item)){
		return(-1);
	}
	//2.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//3.检测当前映射中是否已经存在该测试项目。
	if(_tested_item_map.end()!=_tested_item_map.find(
		tested_item->get_key())){
		return(-2);
	}
	//4.在已测项目映射中保存该项目。
	_tested_item_map[tested_item->get_key()]=tested_item;
	//5.程序运行到此成功返回。
	return(0);
}