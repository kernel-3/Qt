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
 * brief: ��ָ����Ŀ��ʱ��ͼ�������
 * author: yameng_he
 * date: 2016-01-12.
 * param: sequence_diagrams - �����ʱ��ͼ����ָ�롣
 *        sequence_diagram_count - �����ʱ��ͼ������
 *        item_id - �������Ŀ��ʶ��
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
static int clear_item_in_sequence_diagrams(
	SequenceDiagram *sequence_diagrams,
	const unsigned int sequence_diagram_count,
	const CString &item_id){
	//1.��⵱ǰ��������Ƿ�Ϸ���
	if((0==sequence_diagrams)||(
		0==sequence_diagram_count)||(
		_T("")==item_id)){
		return(-1);
	}
	//2.����ʱ��ͼ���飬���ָ����Ŀ��ʱ��ͼ��
	for(unsigned int index=0;index<
		sequence_diagram_count;++index){
		if(sequence_diagrams[index].clear(item_id)<0){
			return(-2);
		}
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: Timing
 * brief: ���캯����
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
 * brief: ����������
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
 * brief: ������ǰʱ��
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Timing::start(){
	//1.����ر������ǰʱ��
	stop();
	//2.������ǰʱ���ܣ������жϿ����Ƿ�ɹ���
	//2-1.������ǰʱ���̣߳������жϿ����Ƿ�ɹ���
	_clock=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::clock,this,CREATE_SUSPENDED,0));
	if((0==_clock)||(INVALID_HANDLE_VALUE==_clock)){
		_clock=0;
		return(-1);
	}
	//2-2.������ǰʱ���̣߳������жϿ����Ƿ�ɹ���
	_timing=reinterpret_cast<HANDLE>(_beginthreadex(
		0,0,&Timing::timing,this,CREATE_SUSPENDED,0));
	if((0==_timing)||(INVALID_HANDLE_VALUE==_timing)){
		_timing=0;
		TerminateThread(_clock,0);
		CloseHandle(_clock);
		_clock=0;
		return(-2);
	}
	//2-3.������ǰ������̡߳�
	const unsigned int timing_thread=ResumeThread(_timing);
	Sleep(100);//����ȴ�100���롣
	const unsigned int clock_thread=ResumeThread(_clock);
	if((1!=timing_thread)||(1!=clock_thread)){
		stop();
		return(-3);
	}
	//3.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: stop
 * brief: ����ֹͣ��ǰ�������е�ʱ��
 * param: --
 * return: --
 */
void Timing::stop(){
	//1.����ʱ��ֹͣ��ǡ�
	if(/*(0!=_clock)||(*/0!=_timing/*)*/){
		_is_cease=TRUE;
	}
	//2.����ʱ���˳��¼���
	/*
	if(0!=_timing){
		SetEvent(_cease_event);
	}
	*/
	//3.�����ǰʱ���̴߳��ڣ����������
	/*
	if(0!=_clock){
		//3-1.����ȴ��߳��˳���ʱ����ǿ�����˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_clock,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_clock,0);
		}
		//3-2.����ǰ�߳���Դ��
		CloseHandle(_clock);
		//3-3.���õ�ǰ�߳̾����
		_clock=0;
	}
	*/
	//4.�����ǰʱ���̴߳��ڣ����������
	if(0!=_timing){
		//4-1.����ȴ��߳��˳���ʱ����ǿ�����˳���
		if(WAIT_OBJECT_0!=WaitForSingleObject(
			_timing,THREAD_EXITING_TIMEOUT)){
			TerminateThread(_timing,0);
		}
		//4-2.����ǰ�߳���Դ��
		CloseHandle(_timing);
		//4-3.���õ�ǰ�߳̾����
		_timing=0;
	}
	//5.�������е��ˣ������߳��˳���Ǳ����Լ����ʱ�ӵδ����顣
	_is_cease=FALSE;
	//clear_all_ticktacks();
}

/**
 * name: clock
 * brief: ʱ���̣߳�����Ϊ��ǰʱ��ʱ��
 * param: parameter - ���뵱ǰ�̵߳Ĳ�����
 * return: ���Ƿ����㡣
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
 * name: clock
 * brief: ʱ�Ӻ��������������ʵ��ʱ���߳�
 *        �ľ�������
 * param: --
 * return: --
 */
/*
void Timing::clock(){
	while(1){
		//1.�����ǰϣ��ʱ��ֹͣ��
		if(_is_cease){
			break;
		}
		//2.���ʼ�յδ�
		add_ticktack();
		//3.�����ǰϣ��ʱ��ֹͣ��
		if(_is_cease){
			break;
		}
		//4.�ȴ��̶���ʱ������ 
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//5.�����ǰϣ��ʱ��ֹͣ��
		if(_is_cease){
			break;
		}
	}
}
*/

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
	//2.ѭ��ʵ��ʱ���ܡ�
	while(1){
		//2-1.�������������ֹ��ǰʱ��
		if(_is_cease){
			break;
		}
		//2-2.ѭ������ʱ��ͼ�Ķ�������������
		while(1){
			//2-2-1.�������������ֹ��ǰʱ��
			if(_is_cease){
				break;
			}
			//2-2-2.������ǰ�������������
			unsigned int trigger_error=0;
			CString trigger_error_item_id=_T("");
			//2-2-3.����ʱ��ͼ�����Ҽ�¼���������
			const int trigger_result=sequence_diagrams[
				sequence_diagram_index].trigger(trigger_time,
					trigger_error,trigger_error_item_id);
			//2-2-4.�������������ֹ��ǰʱ��
			if(_is_cease){
				break;
			}
			//2-2-5.�����ǰ����ʱ��ͼ��������
			if(trigger_result<0){
				//a.�����ǰ����Ϊ������Ч����
				if(Action::ERROR_NOT_VALID==trigger_error){
					//a-1.��д��־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� Timing::timing ��⵽ʱ��ͼ�д�����Ч������"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//a-2.���ǰʱ���߳�����������
					_is_cease=TRUE;
					//a-3.������ǰѭ����
					break;
				}
				//b.�����ǰ����Ϊ��ʱ����
				else if(Action::ERROR_TIMEOUT_T==trigger_error){
					//b-1.��д��־��
					CString log(_T(""));
					log.Format(_T("Warning %s��%ld���� Timing::timing ��⵽ʱ��ͼ�з���������ʱ����"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//b-2.�ȴ�100���롣
					timeBeginPeriod(1);
					Sleep(100);
					timeEndPeriod(1);
					//b-3.�������������ֹ��ǰʱ��
					if(_is_cease){
						break;
					}
					//b-4.���´���ʱ��ͼ�������Ƿ��ܹ������ɹ�����
					else{
						continue;
					}
				}
				//c.�����ǰ����Ϊ���س�ʱ����
				else if(Action::ERROR_SERIOUS_TIMEOUT==trigger_error){
					//c-1.��д��־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� Timing::timing ��⵽ʱ��ͼ�з����������س�ʱ����"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//c-2.���ǰʱ���߳�����������
					_is_cease=TRUE;
					//c-3.������ǰѭ����
					break;
				}
				//..�����ǰ����Ϊ����δ֪����
				else{
					//.-1.��д��־��
					CString log(_T(""));
					log.Format(_T("Error %s��%ld���� Timing::timing ��⵽ʱ��ͼ�з�������δ֪����"),
						(COleDateTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S")),
						timeGetTime());
					Logs::instance()->write(Logs::NAME_ERROR,log);
					//.-2.���ǰʱ���߳�����������
					_is_cease=TRUE;//���ǰʱ���߳�������ֹ��
					//.-3.������ǰѭ����
					break;
				}
			}
			//2-2-6.�����ǰ����ʱ��ͼ�ɹ���
			else{
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
					if(_is_cease){
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
		if(_is_cease){
			break;
		}
		//2-4.�ȴ�1���ӡ�
		timeBeginPeriod(1);
		Sleep(TRIGGER_INTERVAL);
		timeEndPeriod(1);
		//2-5.�������������ֹ��ǰʱ��
		if(_is_cease){
			break;
		}
	}
	////1.������ǰ�������������
	//unsigned int time=0;
	//unsigned int sequence_diagram_index=0;
	//SequenceDiagram *sequence_diagrams=new
	//	SequenceDiagram[SEQUENCE_DIAGRAM_COUNT];
	//if(0==sequence_diagrams){return;}
	//MtAutoDeleter<SequenceDiagram> auto_deleter(
	//	sequence_diagrams,MtAutoDeleter<SequenceDiagram>::
	//	POINTER_TYPE_ARRAY);
	//const HANDLE events[2]={_cease_event,_clock_event};
	////2.����ѭ����ʵ��ʱ��
	//while(1){
	//	//2-1.�����ǰ����ֹͣʱ��
	//	if(_is_cease){
	//		break;
	//	}
	//	//2-2.�ȴ��¼�������
	//	const unsigned int waitting_result=
	//		WaitForMultipleObjects(2,events,FALSE,INFINITE);
	//	//2-3.�����ǰ�ȴ������¼�Ϊֹͣ�¼���
	//	if(WAIT_OBJECT_0==waitting_result){
	//		if(_is_cease){
	//			break;
	//		}else{
	//			continue;
	//		}
	//	}
	//	//2-4.�����ǰ�ȴ������¼�Ϊʱ���¼���
	//	else if(WAIT_OBJECT_0+1==waitting_result){
	//		//2-4-1.�����ǰ����ʱ��ֹͣ��
	//		if(_is_cease){
	//			break;
	//		}
	//		//2-4-2.ѭ������ÿһ��ʱ�ӵδ�ֱ���������Ϊֹ��
	//		while(TICKTACK==pop_ticktack()){
	//			//a.���������ǰʱ���������ֱ��������ǰѭ����
	//			if(_is_cease){
	//				break;
	//			}
	//			//b.������ǰ�������������
	//			int trigger_result=0;
	//			//c.����ʱ��ͼ�������жϴ����Ƿ�ɹ���
	//			while(true){
	//				//c-1.���������ǰʱ���������ֱ��������ǰѭ����
	//				if(_is_cease){
	//					break;
	//				}
	//				//c-2.������ǰ�������������
	//				unsigned int trigger_error=0;
	//				CString trigger_error_item_id=_T("");
	//				//c-3.����ʱ��ͼ�����Ҽ�¼���������
	//				trigger_result=sequence_diagrams[
	//					sequence_diagram_index].trigger(
	//					time,trigger_error,trigger_error_item_id);
	//				//c-4.���������ǰʱ���������ֱ��������ǰѭ����
	//				if(_is_cease){
	//					break;
	//				}
	//				//c-5.�����ǰ����ʱ��ͼʧ�ܡ�
	//				if(trigger_result<0){
	//					//c-5-1.�����ǰ��������Ϊ��ʱ������ֱ����������ѭ����
	//					if(Action::ERROR_TIMEOUT_T==trigger_error){
	//						break;
	//					}
	//					//c-5-2.�����ǰ��������Ϊװ�ص�Ԫ�޹ܴ���
	//					else if(Action::ERROR_IN_TUBE_WITHOUT==trigger_error){
	//						//1>.��ͣ������
	//						//2>.�����Ӧ��Ŀ��ʱ��ͼ������
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//3>.����������ǰ����������
	//						continue;
	//					}
	//					//c-5-3.�����ǰ��������Ϊ����ʱ�Źܳ�ͻ����
	//					else if(Action::ERROR_IN_TUBE_CONFLICT==trigger_error){
	//						//1>.�����ǰ��Ŀ��ʱ��ͼ��
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//2>.����ת��ץ���йܱ�ǡ�
	//						//3>.����������ǰ����������
	//						continue;
	//					}
	//					//c-5-5.�����ǰ��������Ϊ����ʧ�ܡ�
	//					else if(Action::ERROR_IN_TUBE_FAILED==trigger_error){
	//						//1>.���װ��ץ���йܱ�ǡ�
	//						//2>.�����ǰ��Ŀ��ʱ��ͼ��
	//						clear_item_in_sequence_diagrams(sequence_diagrams,
	//							SEQUENCE_DIAGRAM_COUNT,trigger_error_item_id);
	//						//3>.�������ʧ�ܵĴ����������ޡ�
	//						if(/*����ʧ�ܵĴ�����������*/0){
	//							//1.��ͣ������
	//							//2.��ʾ�û��ĲĿ��޹ܡ�
	//						}
	//						//4>.����������ǰ����������
	//						continue;
	//					}
	//					//c-5-6.�����ǰ��������Ϊ��������
	//					else{
	//						_is_cease=TRUE;//���ǰʱ���߳�������ֹ��
	//						break;
	//					}
	//				}
	//				//c-6.�����ǰ����ʱ��ͼ�ɹ���
	//				else{
	//					break;
	//				}
	//				/*
	//				//c-7.���������ǰʱ���������ֱ��������ǰѭ����
	//				if(_is_cease){
	//					break;
	//				}
	//				*/
	//			}
	//			//d.���������ǰʱ���������ֱ��������ǰѭ����
	//			if(_is_cease){
	//				break;
	//			}
	//			//e.�����ǰ����ʱ��ͼʧ�ܡ�
	//			if(trigger_result<0){
	//			}
	//			//f.�����ǰ����ʱ��ͼ�ɹ���
	//			else{
	//				//f-1.ʱ���Լӡ�
	//				time+=CLOCK_INTERVAL;
	//				//f-2.�����ǰʱ����δ�ִ����ڽ���ʱ�䡣
	//				if(time<=TIMING_CYCLE){
	//				}
	//				//f-3.�����ǰʱ���Ѿ��ִ����ڽ���ʱ�䡣
	//				else{
	//					//1��ʱ�����㡣
	//					time=0;
	//					//2������ǰһ��ʱ��
	//					int last_sequence_diagram_index=static_cast<
	//						int>(sequence_diagram_index)-1;
	//					if(last_sequence_diagram_index<0){
	//						last_sequence_diagram_index=SEQUENCE_DIAGRAM_COUNT-1;
	//					}
	//					sequence_diagrams[last_sequence_diagram_index].reset();
	//					//3��ʱ�������
	//					++sequence_diagram_index;
	//					if(sequence_diagram_index>=SEQUENCE_DIAGRAM_COUNT){
	//						sequence_diagram_index=0;
	//					}
	//				}
	//			}
	//			//g.���������ǰʱ���������ֱ��������ǰѭ����
	//			if(_is_cease){
	//				break;
	//			}
	//		}
	//		//2-4-3.�����ǰ����ʱ��ֹͣ��
	//		if(_is_cease){
	//			break;
	//		}
	//	}
	//	//2-5.�����ǰ�ȴ������¼�Ϊ�����¼���
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
 * brief: ���ʱ�ӵδ�
 * param: --
 * return: --
 */
/*
void Timing::add_ticktack(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.���ʱ�ӵδ�
	_ticktacks.push_back(TICKTACK);
	//3.������Ӧ��ʱ���¼���
	SetEvent(_clock_event);
}
*/

/**
 * name: pop_ticktack
 * brief: ����ʱ�ӵδ�
 * param: --
 * return: ��������ɹ����ش��ڵ����㣬���򷵻�ֵС���㡣
 */
/*
int Timing::pop_ticktack(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰʱ�ӵδ����Ϊ�ա�
	if(_ticktacks.empty()){
		return(-1);
	}
	//3.����ʱ�ӵδ�
	const int ticktack=_ticktacks.front();
	_ticktacks.pop_front();
	//4.�������е���ֱ�ӷ���ʱ�ӵδ�ֵ��
	return(ticktack);
}
*/

/**
 * name: clear_all_ticktacks
 * breif: ���ʱ�ӵδ�
 * param: --
 * return: --
 */
/*
void Timing::clear_all_ticktacks(){
	//1.������
	MtAutoLock<MtLock> auto_lock(_lock);
	//2.�����ǰ�洢��ȫ��ʱ�ӵδ�
	if(!_ticktacks.empty()){
		_ticktacks.clear();
	}
}
*/