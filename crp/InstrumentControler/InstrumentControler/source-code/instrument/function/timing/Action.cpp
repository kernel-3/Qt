#include"stdafx.h"
#include"Action.h"
#include"SequenceDiagram.h"

/**
 * name: Action
 * brief: ���캯����
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 *        start_time - �������ʼʱ�䡣
 *        complete_time - ����Ľ���ʱ�䡣
 * return: --
 */
Action::Action(
	const unsigned int id,
	const unsigned int sub_id,
	const unsigned int start_time,
	const unsigned int complete_time)
	:_id(id)
	,_sub_id(sub_id)
	,_start_time(start_time)
	,_complete_time(complete_time)
	,_state(STATE_WAIT)
	,_status(STATUS_DISABLED)
	,_error(ERROR_NONE)
	,_defeats(0)
	,_test_item_key(0){
}

/**
 * name: ~Action
 * brief: ����������
 * param: --
 * return: --
 */
Action::~Action(void){
}

/**
 * name: generate_key
 * brief: ����ָ���Ķ�����ʶ���ӱ�ʶ���ɶ�������
 * param: id - ����Ķ�����ʶ��
 *        sub_id - ����Ķ����ӱ�ʶ��
 * return: �������ɵĶ�������
 */
unsigned int Action::generate_key(
	const unsigned int id,const unsigned int sub_id){
	return(id*1000+sub_id);
}

/**
 * name: get_id
 * brief: ��ȡ��ǰ������ʶ��
 * param: --
 * return: ���ص�ǰ�����Ķ�����ʶ��
 */
unsigned int Action::get_id() const{
	return(_id);
}

/**
 * name: get_sub_id
 * breif: ��ȡ��ǰ�����ӱ�ʶ��
 * param: --
 * return: ���ص�ǰ�����ӱ�ʶ��
 */
unsigned int Action::get_sub_id() const{
	return(_sub_id);
}

/**
 * name: get_key
 * brief: ��ȡ��ǰ������������
 * param: --
 * return: ���ص�ǰ������������
 */
unsigned int Action::get_key() const{
	return(generate_key(_id,_sub_id));
}

/**
 * name: get_start_time
 * brief: ��ȡ��ǰ��������ʼʱ�䡣
 * param: --
 * return: ���ص�ǰ��������ʼʱ�䡣
 */
unsigned int Action::get_start_time() const{
	return(_start_time);
}

/**
 * name: get_complete_time
 * brief: ��ȡ��ǰ���������ʱ�䡣
 * param: --
 * return: ���ص�ǰ���������ʱ�䡣
 */
unsigned int Action::get_complete_time() const{
	return(_complete_time);
}

/**
 * name: set_state
 * brief: ���õ�ǰ����״̬��
 * param: state - ����ĵ�ǰ����״̬��
 * return: --
 */
void Action::set_state(const State state){
	_state=state;
}

/**
 * name: get_state
 * breif: ��ȡ��ǰ����״̬��
 * param: --
 * return: ���ص�ǰ����״̬��
 */
Action::State Action::get_state() const{
	return(_state);
}

/**
 * name: set_status
 * brief: ���õ�ǰ������״̬��
 * param: status - ����ĵ�ǰ����״̬��
 * return: --
 */
void Action::set_status(const Status status){
	_status=status;
}

/**
 * name: get_status
 * breif: ��ȡ��ǰ������״̬��
 * param: --
 * return: ���ص�ǰ������״̬��
 */
Action::Status Action::get_status() const{
	return(_status);
}

/**
 * name: set_error
 * brief: ���õ�ǰ����
 * param: error - ����Ĵ�����Ϣ��
 * return: --
 */
void Action::set_error(const Error error){
	_error=error;
}

/**
 * name: get_error
 * brief: ��ȡ��ǰ����
 * param: --
 * return: ���ص�ǰ����
 */
Action::Error Action::get_error() const{
	return(_error);
}

/**
 * name: increase_defeats
 * brief: ����ʧ�ܼ�����
 * param: --
 * return: --
 */
void Action::increase_defeats(){
	++_defeats;
}

/**
 * name: get_defeats
 * brief: ��ȡ��ǰ������ʧ�ܼ�����
 * param: --
 * return: ���ص�ǰ������ʧ�ܼ�����
 */
unsigned int Action::get_defeats() const{
	return(_defeats);
}

/**
 * name: set_test_item_key
 * brief: ���ò�����Ŀ������
 * param: test_item_key - ����Ĳ�����Ŀ������
 * return: --
 */
void Action::set_test_item_key(const unsigned int &test_item_key){
	_test_item_key=test_item_key;
}

/**
 * name: get_test_item_key
 * breif: ��ȡ������Ŀ������
 * param: --
 * return: ���ز�����Ŀ������
 */
unsigned int Action::get_test_item_key() const{
	return(_test_item_key);
}

/**
 * name: trigger
 * breif: ����������������������ǰ������ִ�С�
 * param: time - ����ĵ�ǰʱ�䡣
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Action::trigger(const unsigned int time){
	//1.�����ǰ�����Ĵ�����Ϣ��
	_error=ERROR_NONE;
	//2.��⵱ǰ�����Ƿ�Ϸ���
	if(is_valid()<0){
		_error=ERROR_NOT_VALID;//���ô�����롣
		return(-1);
	}
	//3.�����ǰ�������ڿ�״̬����ֱ�ӷ��ء�
	if(STATUS_DISABLED==_status){
		return(0);
	}
	//4.�����ǰ����������Ч����Ĭ��״̬������ж����Ĵ���������
	else if((STATUS_ENABLED==_status)||(STATUS_DEFAULT==_status)){
		//4-1.�����ǰ������δִ�С�
		if(STATE_WAIT==_state){
			//4-1-1.�����ǰ������δ�ִﶯ����ʼʱ�䡣
			if(time<_start_time){
				return(0);
			}
			//4-1-2.�����ǰ�����Ѿ��ִﶯ������ʼʱ�䡣
			else if(time==_start_time){
				//a.ִ�е�ǰ���������Ҽ�¼ִ�н����
				const int execute_result=execute(_status);
				//b.���ִ�е�ǰ����ʧ�ܣ���ϣ���޸Ķ���״̬��
				if(execute_result>0){
					_state=STATE_RUN;
					return(-2);
				}
				//c.���ִ�е�ǰ�����ɹ���
				else if(0==execute_result){
					_state=STATE_RUN;//���õ�ǰ��������״̬��
					return(0);
				}
				//c.���ִ�е�ǰ����ʧ�ܣ�Ҳ��ϣ���޸Ķ���״̬��
				else{
					//�����Ĵ�����Ϣ�Ѿ���execute���������á�
					return(-3);
				}
			}
			//4-1-3.�����ǰ�����Ѿ���ʱ��
			else{
				_error=ERROR_UNKNOWN;//���õ�ǰ�����Ĵ�����Ϣ��
				return(-4);
			}
		}
		//4-2.�����ǰ������������ִ��״̬��
		else if(STATE_RUN==_state){
			//4-2-1.�����ǰ������δ�ִﶯ������ʱ�䡣
			if(time<_complete_time){
				return(0);
			}
			//4-2-2.�����ǰ�����Ѿ��ִﶯ���Ľ���ʱ�䡣
			else if(time==_complete_time){
				//a.��ɵ�ǰ���������Ҽ�¼��ɽ����
				const int complete_result=complete(_status);
				//b.����������ʧ�ܣ��������޸Ķ���״̬��
				if(complete_result>0){
					_state=STATE_COMPLETE;
					return(-5);
				}
				//c.��������ɹ���ɡ�
				else if(0==complete_result){
					_state=STATE_COMPLETE;//���õ�ǰ��������״̬��
					return(0);
				}
				//b.����������ʧ�ܣ�Ҳ��ϣ���޸Ķ���״̬��
				else{
					//�����Ĵ�����Ϣ�Ѿ���complete���������á�
					return(-6);
				}
			}
			//4-2-3.�����ǰ�����Ѿ���ʱ��
			else{
				_error=ERROR_UNKNOWN;//���õ�ǰ�����Ĵ�����Ϣ��
				return(-7);
			}
		}
		//4-3.�����ǰ�����Ѿ�ִ����ϡ�
		else if(STATE_COMPLETE==_state){
			return(0);
		}
		//4-4.�����ǰ����״̬δ֪��
		else{
			_error=ERROR_UNKNOWN;//���õ�ǰ�����Ĵ�����Ϣ��
			return(-8);
		}
	}
	//6.�����ǰ��������δ֪״̬����ֱ�ӷ��ش���
	else{
		_error=ERROR_UNKNOWN;//���õ�ǰ�����Ĵ�����Ϣ��
		return(-9);
	}
}

/**
 * name: clear
 * breif: �����ǰ������
 * param: --
 * return: �������Ҫִ������������򷵻ش����������
 *         �������ɹ������㡣
 *         ������ʧ���򷵻�С���������
 */
int Action::clear(){
	//1.��⵱ǰ�����Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);//���ʧ�ܡ�
	}
	//2.�����ǰ�������ڿջ�Ĭ��״̬���򲻶Ե�ǰ�����������������
	if((STATUS_DISABLED==_status)||(STATUS_DEFAULT==_status)){
		return(1);//�������������
	}
	//3.�����ǰ����������Ч״̬����Զ����������������
	else if(STATUS_ENABLED==_status){
		//3-1.�����ǰ�����Ѿ�ִ�л��Ѿ�ִ����ɣ�����Ҫ���������
		if((STATE_RUN==_state)||(STATE_COMPLETE==_state)){
			//remark: �Ѿ�ִ�еĶ����������⶯���Ƿ���ɣ����Բ���
			//        ִ�����������
			//        �Ѿ�ִ����ɵĶ�������û�б�Ҫ������ˡ�
			return(1);//�������������
		}
		//3-2.�����ǰ����������δִ��״̬����������������
		else if(STATE_WAIT==_state){
			//3-2-1.�����ǰ����״̬��
			_state=STATE_WAIT;
			//3-2-2.�����ǰ��������״̬��
			//a.�����ǰ�����Ƿ�Ӧ����ת���������ת������
			if((SequenceDiagram::
				ACTION_ID_REACTION_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_WASHING_DISC_ROTATION==_id)||(
				SequenceDiagram::
				ACTION_ID_WASHING_DISC_WASH==_id)){
				_status=STATUS_DEFAULT;
			}
			//b.�����ǰ����������������
			else{
				_status=STATUS_DISABLED;
			}
			//3-2-3.���������Ϣ��
			_error=ERROR_NONE;
			//3-2-4.���ʧ�ܴ�����
			_defeats=0;
			//3-2-5.�����Ŀ������
			_test_item_key=0;
			//3-2-6.�������е���ֱ�ӳɹ����ء�
			return(0);//����ɹ���
		}
		//3-3.�����ǰ������������״̬����ֱ�ӷ��ش���
		else{
			return(-2);//���ʧ�ܡ�
		}
	}
	//4.�����ǰ������������״̬����ֱ�ӷ��ش���
	else{
		return(-3);//���ʧ�ܡ�
	}
}

/**
 * name: reset
 * breif: ���õ�ǰ������
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Action::reset(){
	//1.��⵱ǰ�����Ƿ�Ϸ���
	if(is_valid()<0){
		return(-1);
	}
	//2.���õ�ǰ����״̬��
	_state=STATE_WAIT;
	//3.���õ�ǰ��������״̬��
	//3-1.�����ǰ����Ϊ����Ӧ����ת���򡰴�������ת��������
	if((SequenceDiagram::
		ACTION_ID_REACTION_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_MAGNETIC_BEADS_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_WASHING_DISC_ROTATION==_id)||(
		SequenceDiagram::
		ACTION_ID_WASHING_DISC_WASH==_id)){
		_status=STATUS_DEFAULT;
	}
	//3-2.�����ǰ����Ϊ����������
	else{
		_status=STATUS_DISABLED;
	}
	//3-3.���ô�����Ϣ��
	_error=ERROR_NONE;
	//3-4.����ʧ�ܴ�����
	_defeats=0;
	//3-5.���ò�����Ŀ������
	_test_item_key=0;
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: is_valid
 * brief: ��⵱ǰ�����Ƿ�Ϸ���
 * param: --
 * return: �����ǰ�����Ϸ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int Action::is_valid() const{
	//1.��⵱ǰ������ʶ�Ƿ�Ϸ���
	if((_id<1)||(_id>999)){
		return(-1);
	}
	//2.��⵱ǰ�����ӱ�ʶ�Ƿ�Ϸ���
	if((_sub_id<1)||(_sub_id>999)){
		return(-2);
	}
	//3.��⵱ǰ��������ʼʱ���Ƿ�Ϸ���
	if((_start_time<0)||(_start_time>30000)){
		return(-3);
	}
	//4.��⵱ǰ�����Ľ���ʱ���Ƿ�Ϸ���
	if((_complete_time<0)||(_complete_time>30000)){
		return(-4);
	}
	//5.��⵱ǰ��������ʼ������ʱ����໥��ϵ�Ƿ�Ϸ���
	if(_start_time>_complete_time){
		return(-5);
	}
	//6.��⵱ǰ������״̬�Ƿ�Ϸ���
	if((STATE_WAIT!=_state)&&(STATE_RUN!=_state)&&(
		STATE_COMPLETE!=_state)){
		return(-6);
	}
	//7.��⵱ǰ������״̬�Ƿ�Ϸ���
	if((STATUS_DISABLED!=_status)&&(STATUS_ENABLED!=_status)&&(
		STATUS_DEFAULT!=_status)){
		return(-7);
	}
	//8.��⵱ǰ�����Ĵ������Ƿ�Ϸ���
	if((ERROR_NONE!=_error)&&(
		ERROR_UNKNOWN!=_error)&&(
		ERROR_NOT_VALID!=_error)&&(
		ERROR_SERIOUS_TIMEOUT!=_error)&&(
		ERROR_TIMEOUT_T!=_error)&&(
		ERROR_TUBE_STOREHOUSE_WITHOUT_TUBE!=_error)&&(
		ERROR_COMMUNICATION!=_error)&&(
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_CONFLICT!=_error)&&(
		ERROR_PUT_TUBE_IN_REACTION_DISC_ENTRY_FAILED!=_error)){
		return(-8);
	}
	//9.��⵱ǰ�����Ĵ�������Ƿ�Ϸ���
	if(_defeats<0){
		return(-9);
	}
	//10.��⵱ǰ��Ŀ�����Ƿ�Ϸ���
	if(STATUS_ENABLED==_status){
		if(0==_test_item_key){
			return(-10);
		}
	}
	//11.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: execute
 * breif: ִ�е�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬������
 */
int Action::execute(const Status /*status*/){
	//1.��⵱ǰ�����Ƿ�Ϸ���
	if(is_valid()<0){
		//1-1.���õ�ǰ�������Ϊ��Ч����
		_error=ERROR_NOT_VALID;
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	else{
		return(0);
	}
}

/**
 * name: complete
 * brief: ��ɵ�ǰ������
 * param: status - ����ĵ�ǰ����״̬��
 * return: �������ִ�гɹ�����ֵ�����㣬���򷵻�ֵ�������㣨
 *         �������ֵ������˵���������ĵ�ǰ����״̬���������
 *         ֵС����˵�����������ĵ�ǰ����״̬������
 */
int Action::complete(const Status /*status*/){
	//1.��⵱ǰ�����Ƿ�Ϸ���
	if(is_valid()<0){
		//1-1.���õ�ǰ�������Ϊ��Ч����
		_error=ERROR_NOT_VALID;
		//1-2.�������е���ֱ�ӷ��ش���
		return(-1);
	}
	//2.�������е��˳ɹ����ء�
	else{
		return(0);
	}
}