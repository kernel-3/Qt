#include"stdafx.h"
#include"Timing.h"
#include"SequenceDiagram.h"
#include"../../../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../../../include/mfctoolkit/tool/MtAutoLock.h"
#include"../../../../../../include/mfctoolkit/tool/MtAutoDeleter.h"
#include"Action.h"
#include"../../../common/Logs.h"
#include<Process.h>
#include<MMSystem.h>
#include<thread>


/**
 * name: clear_item_in_sequence_diagrams
 * brief: 将指定项目从时序图中清除。
 * author: yameng_he
 * date: 2016-01-12.
 * param: sequence_diagrams - 输入的时序图数组指针。
 *        sequence_diagram_count - 输入的时序图计数。
 *        item_id - 输入的项目标识。
 * return: 如果当前函数执行成功返回值大于等于零，否则返回值小于零。
 */
static int clear_item_in_sequence_diagrams(
	SequenceDiagram *sequence_diagrams,
	const unsigned int sequence_diagram_count,
	const CString &item_id){
	//1.检测当前输入参数是否合法。
	if((0==sequence_diagrams)||(
		0==sequence_diagram_count)||(
		_T("")==item_id)){
		return(-1);
	}
	//2.遍历时序图数组，清除指定项目的时序图。
	for(unsigned int index=0;index<
		sequence_diagram_count;++index){
		if(sequence_diagrams[index].clear(item_id)<0){
			return(-2);
		}
	}
	//3.程序运行到此成功返回。
	return(0);
}

/**
 * name: Timing
 * brief: 构造函数。
 * param: --
 * return: --
 */
Timing::Timing(void)
	:_clock(0)
	,_timing(0)
	,_is_cease(FALSE)
	,_cease_event(CreateEvent(0,FALSE,FALSE,0))
	,_lock(new MtLock)
	,_clock_event(CreateEvent(0,FALSE,FALSE,0))
	,_ticktacks(){
}

/**
 * name: ~Timing
 * brief: 析构函数。
 * param: --
 * return: --
 */
Timing::~Timing(void){
	stop();
	CloseHandle(_cease_event);
	CloseHandle(_clock_event);
	delete _lock;
}

/**
 * name: start
 * brief: 启动当前时序。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int Timing::start(){
	//1.如果关闭清除当前时序。
	stop();
	//2.开启当前时序功能，并且判断开启是否成功。
	//2-1.开启当前时钟线程，并且判断开启是否成功。
	_clock=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::clock,this,CREATE_SUSPENDED,0));
	if((0==_clock)||(INVALID_HANDLE_VALUE==_clock)){
		_clock=0;
		return(-1);
	}
	//2-2.开启当前时序线程，并且判断开启是否成功。
	_timing=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::timing,this,CREATE_SUSPENDED,0));
	if((0==_timing)||(INVALID_HANDLE_VALUE==_timing)){
		_timing=0;
		TerminateThread(_clock,0);
		CloseHandle(_clock);
		_clock=0;
		return(-2);
	}
	//2-3.启动当前挂起的线程。
	const unsigned int timing_thread=ResumeThread(_timing);
	Sleep(100);//故意等待100毫秒。
	const unsigned int clock_thread=ResumeThread(_clock);
	if((1!=timing_thread)||(1!=clock_thread)){
		stop();
		return(-3);
	}
	//3.程序运行到此直接成功返回。
	return(0);
}

/**
 * name: stop
 * brief: 立即停止当前正在运行的时序。
 * param: --
 * return: --
 */
void Timing::stop(){
	//1.设置时序停止标记。
	if(/*(0!=_clock)||(*/0!=_timing/*)*/){
		_is_cease=TRUE;
	}
	//2.设置时序退出事件。
	/*
	if(0!=_timing){
		SetEvent(_cease_event);
	}
	*/
	//3.如果当前时钟线程存在，则进行清理。
	/*
	if(0!=_clock){
		//3-1.如果等待线程退出超时，则强制其退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_clock,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_clock,0);
		}
		//3-2.清理当前线程资源。
		CloseHandle(_clock);
		//3-3.重置当前线程句柄。
		_clock=0;
	}
	*/
	//4.如果当前时序线程存在，则进行清理。
	if(0!=_timing){
		//4-1.如果等待线程退出超时，则强制其退出。
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_timing,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_timing,0);
		}
		//4-2.清理当前线程资源。
		CloseHandle(_timing);
		//4-3.重置当前线程句柄。
		_timing=0;
	}
	//5.程序运行到此，重置线程退出标记变量以及清除时钟滴答数组。
	_is_cease=FALSE;
	//clear_all_ticktacks();
}

/**
 * name: clock
 * brief: 时钟线程，负责为当前时序报时。
 * param: parameter - 输入当前线程的参数。
 * return: 总是返回零。
 */
/*
unsigned int __stdcall Timing::clock(void *parameter){
	Timing *timing=reinterpret_cast<Timing*>(parameter);
	timing->clock();
	return(0);
}
*/

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
 * name: clock
 * brief: 时钟函数，它负责具体实现时钟线程
 *        的具体任务。
 * param: --
 * return: --
 */
/*
void Timing::clock(){
	while(1){
		//1.如果当前希望时钟停止。
		if(_is_cease){
			break;
		}
		//2.添加始终滴答。
		add_ticktack();
		//3.如果当前希望时钟停止。
		if(_is_cease){
			break;
		}
		//4.等待固定的时间间隔。 
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//5.如果当前希望时钟停止。
		if(_is_cease){
			break;
		}
	}
}
*/

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
	//2.循环实现时序功能。
	while(1){
		//2-1.如果期望立即终止当前时序。
		if(_is_cease){
			break;
		}
		//2-2.循环进行时序图的动作触发操作。
		while(1){
			//2-2-1.如果期望立即终止当前时序。
			if(_is_cease){
				break;
			}
			//2-2-2.声明当前操作所需变量。
			unsigned int trigger_error=0;
			CString trigger_error_item_id=_T("");
			//2-2-3.触发时序图，并且记录触发结果。
			const int trigger_result=sequence_diagrams[
				sequence_diagram_index].trigger(trigger_time,
					trigger_error,trigger_error_item_id);
			//2-2-4.如果期望立即终止当前时序。
			if(_is_cease){
				break;
			}
			//2-2-5.如果当前触发时序图发生错误。
			if(trigger_result<0){
				//a.如果当前触发为动作无效错误。
				if(Action::ERROR_NOT_VALID==trigger_error){
					//a-1.书写日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： Timing::timing 检测到时序图中存在无效动作！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//a-2.命令当前时序线程立即结束。
					_is_cease=TRUE;
					//a-3.跳出当前循环。
					break;
				}
				//b.如果当前触发为超时错误。
				else if(Action::ERROR_TIMEOUT_T==trigger_error){
					//b-1.书写日志。
					CString log(_T(""));
					log.Format(_T("Warning %s（%ld）： Timing::timing 检测到时序图中发生动作超时错误！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//b-2.等待100毫秒。
					timeBeginPeriod(1);
					Sleep(100);
					timeEndPeriod(1);
					//b-3.如果期望立即终止当前时序。
					if(_is_cease){
						break;
					}
					//b-4.重新触发时序图（重试是否能够触发成功）。
					else{
						continue;
					}
				}
				//c.如果当前触发为严重超时错误。
				else if(Action::ERROR_SERIOUS_TIMEOUT==trigger_error){
					//c-1.书写日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： Timing::timing 检测到时序图中发生动作严重超时错误！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c-2.命令当前时序线程立即结束。
					_is_cease=TRUE;
					//c-3.跳出当前循环。
					break;
				}
				//..如果当前触发为其它未知错误。
				else{
					//.-1.书写日志。
					CString log(_T(""));
					log.Format(_T("Error %s（%ld）： Timing::timing 检测到时序图中发生动作未知错误！"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//.-2.命令当前时序线程立即结束。
					_is_cease=TRUE;//命令当前时序线程立即终止。
					//.-3.跳出当前循环。
					break;
				}
			}
			//2-2-6.如果当前触发时序图成功。
			else{
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
					if(_is_cease){
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
		if(_is_cease){
			break;
		}
		//2-4.等待1秒钟。
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//2-5.如果期望立即终止当前时序。
		if(_is_cease){
			break;
		}
	}
	////1.声明当前操作所需变量。
	//unsigned int time=0;
	//unsigned int sequence_diagram_index=0;
	//SequenceDiagram *sequence_diagrams=new
	//	SequenceDiagram[SEQUENCE_DIAGRAM_COUNT];
	//if(0==sequence_diagrams){return;}
	//MtAutoDeleter<SequenceDiagram> auto_deleter(
	//	sequence_diagrams,MtAutoDeleter<SequenceDiagram>::
	//	POINTER_TYPE_ARRAY);
	//const HANDLE events[2]={_cease_event,_clock_event};
	////2.无限循环，实现时序。
	//while(1){
	//	//2-1.如果当前期望停止时序。
	//	if(_is_cease){
	//		break;
	//	}
	//	//2-2.等待事件触发。
	//	const unsigned int waitting_result=
	//		WaitForMultipleObjects(2,events,FALSE,INFINITE);
	//	//2-3.如果当前等待到的事件为停止事件。
	//	if(WAIT_OBJECT_0==waitting_result){
	//		if(_is_cease){
	//			break;
	//		}else{
	//			continue;
	//		}
	//	}
	//	//2-4.如果当前等待到的事件为时钟事件。
	//	else if(WAIT_OBJECT_0+1==waitting_result){
	//		//2-4-1.如果当前期望时序停止。
	//		if(_is_cease){
	//			break;
	//		}
	//		//2-4-2.循环处理每一个时钟滴答，直到处理完成为止。
	//		while(TICKTACK==pop_ticktack()){
	//			//a.如果期望当前时序结束，则直接跳出当前循环。
	//			if(_is_cease){
	//				break;
	//			}
	//			//b.声明当前操作所需变量。
	//			int trigger_result=0;
	//			//c.触发时序图，并且判断触发是否成功。
	//			while(true){
	//				//c-1.如果期望当前时序结束，则直接跳出当前循环。
	//				if(_is_cease){
	//					break;
	//				}
	//				//c-2.声明当前操作所需变量。
	//				unsigned int trigger_error=0;
	//				CString trigger_error_item_id=_T("");
	//				//c-3.触发时序图，并且记录触发结果。
	//				trigger_result=sequence_diagrams[
	//					sequence_diagram_index].trigger(
	//					time,trigger_error,trigger_error_item_id);
	//				//c-4.如果期望当前时序结束，则直接跳出当前循环。
	//				if(_is_cease){
	//					break;
	//				}
	//				//c-5.如果当前触发时序图失败。
	//				if(trigger_result<0){
	//					//c-5-1.如果当前触发错误为超时错误，则直接跳出触发循环。
	//					if(Action::ERROR_TIMEOUT_T==trigger_error){
	//						break;
	//					}
	//					//c-5-2.如果当前触发错误为装载单元无管错误。
	//					else if(Action::ERROR_IN_TUBE_WITHOUT==trigger_error){
	//						//1>.暂停进样。
	//						//2>.清除相应项目的时序图动作。
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//3>.继续触发当前其它动作。
	//						continue;
	//					}
	//					//c-5-3.如果当前触发错误为进管时放管冲突错误。
	//					else if(Action::ERROR_IN_TUBE_CONFLICT==trigger_error){
	//						//1>.清除当前项目的时序图。
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//2>.设置转载抓手有管标记。
	//						//3>.继续触发当前其它动作。
	//						continue;
	//					}
	//					//c-5-5.如果当前触发错误为进管失败。
	//					else if(Action::ERROR_IN_TUBE_FAILED==trigger_error){
	//						//1>.清除装载抓手有管标记。
	//						//2>.清除当前项目的时序图。
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//3>.如果进管失败的次数大于上限。
	//						if(/*进管失败的次数大于上限*/0){
	//							//1.暂停进样。
	//							//2.提示用户耗材库无管。
	//						}
	//						//4>.继续触发当前其它动作。
	//						continue;
	//					}
	//					//c-5-6.如果当前触发错误为其它错误。
	//					else{
	//						_is_cease=TRUE;//命令当前时序线程立即终止。
	//						break;
	//					}
	//				}
	//				//c-6.如果当前触发时序图成功。
	//				else{
	//					break;
	//				}
	//				/*
	//				//c-7.如果期望当前时序结束，则直接跳出当前循环。
	//				if(_is_cease){
	//					break;
	//				}
	//				*/
	//			}
	//			//d.如果期望当前时序结束，则直接跳出当前循环。
	//			if(_is_cease){
	//				break;
	//			}
	//			//e.如果当前触发时序图失败。
	//			if(trigger_result<0){
	//			}
	//			//f.如果当前触发时序图成功。
	//			else{
	//				//f-1.时间自加。
	//				time+=CLOCK_INTERVAL;
	//				//f-2.如果当前时间尚未抵达周期结束时间。
	//				if(time<=TIMING_CYCLE){
	//				}
	//				//f-3.如果当前时间已经抵达周期结束时间。
	//				else{
	//					//1）时间清零。
	//					time=0;
	//					//2）重置前一个时序。
	//					int last_sequence_diagram_index=static_cast<
	//						int>(sequence_diagram_index)-1;
	//					if(last_sequence_diagram_index<0){
	//						last_sequence_diagram_index=SEQUENCE_DIAGRAM_COUNT-1;
	//					}
	//					sequence_diagrams[last_sequence_diagram_index].reset();
	//					//3）时序递增。
	//					++sequence_diagram_index;
	//					if(sequence_diagram_index>=SEQUENCE_DIAGRAM_COUNT){
	//						sequence_diagram_index=0;
	//					}
	//				}
	//			}
	//			//g.如果期望当前时序结束，则直接跳出当前循环。
	//			if(_is_cease){
	//				break;
	//			}
	//		}
	//		//2-4-3.如果当前期望时序停止。
	//		if(_is_cease){
	//			break;
	//		}
	//	}
	//	//2-5.如果当前等待到的事件为其它事件。
	//	else{
	//		if(_is_cease){
	//			break;
	//		}else{
	//			continue;
	//		}
	//	}
	//}
}

/**
 * name: add_ticktack
 * brief: 添加时钟滴答。
 * param: --
 * return: --
 */
/*
void Timing::add_ticktack(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.添加时钟滴答。
	_ticktacks.push_back(TICKTACK);
	//3.设置相应的时钟事件。
	SetEvent(_clock_event);
}
*/

/**
 * name: pop_ticktack
 * brief: 弹出时钟滴答。
 * param: --
 * return: 如果弹出成功返回大于等于零，否则返回值小于零。
 */
/*
int Timing::pop_ticktack(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.如果当前时钟滴答队列为空。
	if(_ticktacks.empty()){
		return(-1);
	}
	//3.弹出时钟滴答。
	const int ticktack=_ticktacks.front();
	_ticktacks.pop_front();
	//4.程序运行到此直接返回时钟滴答值。
	return(ticktack);
}
*/

/**
 * name: clear_all_ticktacks
 * breif: 清除时钟滴答。
 * param: --
 * return: --
 */
/*
void Timing::clear_all_ticktacks(){
	//1.上锁。
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.清除当前存储的全部时钟滴答。
	if(!_ticktacks.empty()){
		_ticktacks.clear();
	}
}
*/