#include"stdafx.h"
#include"MtADOCommand.h"
#include<assert.h>

/**
 * name: MtADOCommand
 * brief: ���캯����
 * param: --
 * return: --
 */
MtADOCommand::MtADOCommand(void)
	:_last_error_code(0)
	,_last_error_message(_T(""))
	,_command(0){
	create_instance();
}

/**
 * name: ~MtADOCommand
 * brief: ����������
 * param: --
 * return: --
 */
MtADOCommand::~MtADOCommand(void){
	release_instance();
}

/**
 * name: set_active_connection
 * breif: ָʾָ���� Command �� Recordset ����ǰ������ Connection ����
 * param: connection - �����˶������ӻ� Connection ������ַ�����Ĭ�������Ϊ Null �������á�
 * return: --
 * note: ʹ�� ActiveConnection ���Կ�ȷ�������Ͻ�ִ��ָ�� Command ������ָ�� Recordset �� Connection ����
 * remark: ���� Command ����ActiveConnection ����Ϊ��/д���ڽ�����������Ϊ�򿪵� Connection �������Ч�����ַ���֮ǰ��
 *         ��ͼ���� Command ����� Execute ��������������Microsoft Visual Basic   �� ActiveConnection ��������Ϊ 
 *         Nothing ��ʹ Command �����뵱ǰ Connection �����������ʹ�ṩ���ͷ�����Դ�����й�������Դ��Ȼ�󣬿���ʹ Command 
 *         ��������ͬ�� Connection ��������� Connection ���������ĳЩ�ṩ���������������ô�һ�� Connection ���ĵ���һ��
 *         Connection�����������Ƚ�����������Ϊ Nothing����� Command ����� Parameter ���ϰ����ṩ���ṩ�Ĳ�������ô���罫 
 *         ActiveConnection ��������Ϊ Nothing ������Ϊ���� Connection ���󣬽�������ϡ�����ֹ����� Parameter ����ʹ��
 *         ��Щ������� Command ����� Parameters ���ϣ��� ActiveConnection ��������Ϊ Nothing ������ Connection ����
 *         ����Ӱ�� Parameters ���ϡ��ر��� Command ����������� Connection ���󽫰� ActiveConnection ��������Ϊ Nothing��
 *         ������������Ϊ�ѹرյ� Connection ���󽫲�������
 *         Recordset
 *         ���ڴ򿪵� Recordset ������� Source ���Ա�����Ϊ��Ч Command ����� Recordset ����ActiveConnection ����Ϊֻ����
 *         ���򣬸�����Ϊ��/д�����Խ�����������Ϊ��Ч�� Connection ���󣬻�����Ϊ��Ч�������ַ�������ʱ���ṩ�߿�ʹ�øö��崴���µ� 
 *         Connection ���󣬲������ӡ����⣬�ṩ�߿��Խ�����������Ϊ�µ� Connection �����Ա������ṩ������չ������Ϣ�� Connection 
 *         �����ִ������������ʹ�� Open ������ ActiveConnection ������ Recordset ����ActiveConnection ���Խ��̳иò�����ֵ��
 *         ����� Recordset ����� Source ��������Ϊ��Ч Command ���������Recordset �� ActiveConnection ���Խ��̳� Command �����
 *         ActiveConnection ���Ե����á�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��ֻ�ܽ�����������Ϊ�����ַ�����Microsoft Visual Basic �� VBScript
 *         �У�Nothing
 */
void MtADOCommand::set_active_connection(const _variant_t &connection){
	clear_last_error();
	try{
		_command->PutActiveConnection(connection);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_active_connection
 * breif: ָʾָ���� Command �� Recordset ����ǰ������ Connection ����
 * param: connection - �����˶������ӻ� Connection ������ַ�����Ĭ�������Ϊ Null �������á�
 * return: ����ָʾָ���� Command �� Recordset ����ǰ������ Connection ����
 * note: ʹ�� ActiveConnection ���Կ�ȷ�������Ͻ�ִ��ָ�� Command ������ָ�� Recordset �� Connection ����
 * remark: ���� Command ����ActiveConnection ����Ϊ��/д���ڽ�����������Ϊ�򿪵� Connection �������Ч�����ַ���֮ǰ��
 *         ��ͼ���� Command ����� Execute ��������������Microsoft Visual Basic   �� ActiveConnection ��������Ϊ 
 *         Nothing ��ʹ Command �����뵱ǰ Connection �����������ʹ�ṩ���ͷ�����Դ�����й�������Դ��Ȼ�󣬿���ʹ Command 
 *         ��������ͬ�� Connection ��������� Connection ���������ĳЩ�ṩ���������������ô�һ�� Connection ���ĵ���һ��
 *         Connection�����������Ƚ�����������Ϊ Nothing����� Command ����� Parameter ���ϰ����ṩ���ṩ�Ĳ�������ô���罫 
 *         ActiveConnection ��������Ϊ Nothing ������Ϊ���� Connection ���󣬽�������ϡ�����ֹ����� Parameter ����ʹ��
 *         ��Щ������� Command ����� Parameters ���ϣ��� ActiveConnection ��������Ϊ Nothing ������ Connection ����
 *         ����Ӱ�� Parameters ���ϡ��ر��� Command ����������� Connection ���󽫰� ActiveConnection ��������Ϊ Nothing��
 *         ������������Ϊ�ѹرյ� Connection ���󽫲�������
 *         Recordset
 *         ���ڴ򿪵� Recordset ������� Source ���Ա�����Ϊ��Ч Command ����� Recordset ����ActiveConnection ����Ϊֻ����
 *         ���򣬸�����Ϊ��/д�����Խ�����������Ϊ��Ч�� Connection ���󣬻�����Ϊ��Ч�������ַ�������ʱ���ṩ�߿�ʹ�øö��崴���µ� 
 *         Connection ���󣬲������ӡ����⣬�ṩ�߿��Խ�����������Ϊ�µ� Connection �����Ա������ṩ������չ������Ϣ�� Connection 
 *         �����ִ������������ʹ�� Open ������ ActiveConnection ������ Recordset ����ActiveConnection ���Խ��̳иò�����ֵ��
 *         ����� Recordset ����� Source ��������Ϊ��Ч Command ���������Recordset �� ActiveConnection ���Խ��̳� Command �����
 *         ActiveConnection ���Ե����á�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��ֻ�ܽ�����������Ϊ�����ַ�����Microsoft Visual Basic �� VBScript
 *         �У�Nothing
 */
ADODB::_ConnectionPtr MtADOCommand::get_active_connection() const{
	clear_last_error();
	try{
		return(_command->GetActiveConnection());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_command_text
 * brief: ���ð����ṩ������� SOL ��䡢������ƻ�洢�Ĺ��̵��ã����ַ���ֵ��Ĭ��ֵΪ ""���㳤���ַ�������
 * param: command_text - �ṩ�����
 * return: --
 * remark: ʹ�� CommandText ���Կ����û򷵻� Command ������ı���ͨ����������Ϊ SQL ��䣬��Ҳ�������ṩ��ʶ����κ��������͵�
 *         ������䣨��洢�Ĺ��̵��ã���SQL ���������ṩ�߲�ѯ�������֧�ֵ��ض��﷨��汾��������� CommandText ����ʱ�� Command 
 *         ����� Prepared ��������Ϊ True������ Command ����󶨵��򿪵����ӣ����ڵ��� Execute �� Open ����ʱ ADO ��׼����ѯ������
 *         �ṩ�߱����ѱ���Ĳ�ѯ��ʽ����ȡ���� CommandType ���Ե����ã�ADO ���ܸı� CommandText ���ԡ�����ʱ�Ķ� CommandText ����
 *         �鿴��ִ�й����� ADO ��Ҫʹ�õ�ʵ�������ı���
 */
void MtADOCommand::set_command_text(const CString &command_text){
	clear_last_error();
	try{
		_command->PutCommandText(static_cast<LPCTSTR>(command_text));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_text
 * brief: ��ȡ�����ṩ������� SOL ��䡢������ƻ�洢�Ĺ��̵��ã����ַ���ֵ��Ĭ��ֵΪ ""���㳤���ַ�������
 * param: command_text - �ṩ�����
 * return: ���ذ����ṩ������� SOL ��䡢������ƻ�洢�Ĺ��̵��ã����ַ���ֵ��Ĭ��ֵΪ ""���㳤���ַ�������
 * remark: ʹ�� CommandText ���Կ����û򷵻� Command ������ı���ͨ����������Ϊ SQL ��䣬��Ҳ�������ṩ��ʶ����κ��������͵�
 *         ������䣨��洢�Ĺ��̵��ã���SQL ���������ṩ�߲�ѯ�������֧�ֵ��ض��﷨��汾��������� CommandText ����ʱ�� Command 
 *         ����� Prepared ��������Ϊ True������ Command ����󶨵��򿪵����ӣ����ڵ��� Execute �� Open ����ʱ ADO ��׼����ѯ������
 *         �ṩ�߱����ѱ���Ĳ�ѯ��ʽ����ȡ���� CommandType ���Ե����ã�ADO ���ܸı� CommandText ���ԡ�����ʱ�Ķ� CommandText ����
 *         �鿴��ִ�й����� ADO ��Ҫʹ�õ�ʵ�������ı���
 */
CString MtADOCommand::get_command_text() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_command->GetCommandText()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_command_timeout
 * brief: ���ó�����ֵ����ֵָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��Ĭ��ֵΪ 30��
 * param: timeout - ָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��
 * return: --
 * remark: ʹ�� Connection ����� Command �ϵ� CommandTimeout ���ԣ�������������ӵ������������ع��ز������ӳٶ�ȡ�� Execute �������á�
 *         ����� CommandTimeout ���������õ�ʱ������û���������ִ�У�����������Ȼ�� ADO ��ȡ����������������������Ϊ�㣬ADO ����
 *         ���ڵȴ�ֱ������ִ����ϡ���ȷ������д�������ṩ�ߺ�����Դ֧�� CommandTimeout ���ܡ�Connection ����� CommandTimeout ����
 *         �������ͬ Connection �� Command ����� CommandTimeout ���ò���Ӱ�죬�� Command ����� CommandTimeout ���Բ��̳� 
 *         Connection ����� CommandTimeout ��ֵ���� Connection �����ϣ��� Connection ��CommandTimeout ���Խ����ֶ�/д��
 */
void MtADOCommand::set_command_timeout(const long timeout){
	clear_last_error();
	try{
		_command->PutCommandTimeout(timeout);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_timeout
 * brief: ��ȡ������ֵ����ֵָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��Ĭ��ֵΪ 30��
 * param: --
 * return: ���س�����ֵ����ֵָʾ�ȴ�����ִ�е�ʱ�䣨��λΪ�룩��Ĭ��ֵΪ 30��
 * remark: ʹ�� Connection ����� Command �ϵ� CommandTimeout ���ԣ�������������ӵ������������ع��ز������ӳٶ�ȡ�� Execute �������á�
 *         ����� CommandTimeout ���������õ�ʱ������û���������ִ�У�����������Ȼ�� ADO ��ȡ����������������������Ϊ�㣬ADO ����
 *         ���ڵȴ�ֱ������ִ����ϡ���ȷ������д�������ṩ�ߺ�����Դ֧�� CommandTimeout ���ܡ�Connection ����� CommandTimeout ����
 *         �������ͬ Connection �� Command ����� CommandTimeout ���ò���Ӱ�죬�� Command ����� CommandTimeout ���Բ��̳� 
 *         Connection ����� CommandTimeout ��ֵ���� Connection �����ϣ��� Connection ��CommandTimeout ���Խ����ֶ�/д��
 */
long MtADOCommand::get_command_timeout() const{
	clear_last_error();
	try{
		return(_command->GetCommandTimeout());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_command_type
 * breif: ���� Command ��������͡�
 * param: type - ָʾ Command ��������͡�
 *               ����                               ˵�� 
 *               =======================================================================================================
 *               AdCmdText                          �� CommandText ��Ϊ�����洢���̵��õ��ı���������м��㡣 
 *               AdCmdTable                         �� CommandText ��Ϊ����ȫ�����ڲ����ɵ� SQL ��ѯ���صı������ƽ��м��㡣 
 *               AdCmdTableDirect                   �� CommandText ��Ϊ����ȫ�����صı������ƽ��м��㡣 
 *               AdCmdStoredProc                    �� CommandText ��Ϊ�洢���������м��㡣 
 *               AdCmdUnknown                       Ĭ��ֵ��CommandText �����е���������δ֪�� 
 *               adCmdFile                          �� CommandText ��Ϊ�־� Recordset �ļ������м��㡣 
 *               AdExecuteNoRecords                 ָʾ CommandText Ϊ�������е������洢���̣����磬�������ݵ������������������У�
 *                                                  �򽫶�����Щ���Ҳ������ء��������� adCmdText �� adCmdStoredProc ������ϡ� 
 *               ========================================================================================================
 * return: --
 * remark: ʹ�� CommandType ���Կ��Ż� CommandText ���Եļ��㡣��� CommandType ���Ե�ֵ���� adCmdUnknown��Ĭ��ֵ����ϵͳ�����ܽ��ή�ͣ�
 *         ��Ϊ ADO ��������ṩ����ȷ�� CommandText ������ SQL ��䡢���Ǵ洢���̻������ơ����֪������ʹ�õ���������ͣ���ͨ������ 
 *         CommandType ����ָ�� ADO ֱ��ת����ش��롣��� CommandType ������ CommandText �����е��������Ͳ�ƥ�䣬���� Execute ����ʱ��
 *         ��������adExecuteNoRecords ����ͨ����С���ڲ�������������ܡ��ó���������ʹ�ã��������� adCmdText �� adCmdStoredProc ��ϣ�
 *         �� adCmdText+adExecuteNoRecords��һ��ʹ�á������ Recordset.Open һ��ʹ�� adExecuteNoRecords�����߸÷���ʹ�� Command ����
 *         ������������
 */
void MtADOCommand::set_command_type(const ADODB::CommandTypeEnum type){
	clear_last_error();
	try{
		_command->PutCommandType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_command_type
 * breif: ��ȡ Command ��������͡�
 * param: --
 * return: ���� Command ��������͡�
 *         ����                               ˵�� 
 *         =======================================================================================================
 *         AdCmdText                          �� CommandText ��Ϊ�����洢���̵��õ��ı���������м��㡣 
 *         AdCmdTable                         �� CommandText ��Ϊ����ȫ�����ڲ����ɵ� SQL ��ѯ���صı������ƽ��м��㡣 
 *         AdCmdTableDirect                   �� CommandText ��Ϊ����ȫ�����صı������ƽ��м��㡣 
 *         AdCmdStoredProc                    �� CommandText ��Ϊ�洢���������м��㡣 
 *         AdCmdUnknown                       Ĭ��ֵ��CommandText �����е���������δ֪�� 
 *         adCmdFile                          �� CommandText ��Ϊ�־� Recordset �ļ������м��㡣 
 *         AdExecuteNoRecords                 ָʾ CommandText Ϊ�������е������洢���̣����磬�������ݵ������������������У�
 *                                            �򽫶�����Щ���Ҳ������ء��������� adCmdText �� adCmdStoredProc ������ϡ� 
 *         ========================================================================================================
 * remark: ʹ�� CommandType ���Կ��Ż� CommandText ���Եļ��㡣��� CommandType ���Ե�ֵ���� adCmdUnknown��Ĭ��ֵ����ϵͳ�����ܽ��ή�ͣ�
 *         ��Ϊ ADO ��������ṩ����ȷ�� CommandText ������ SQL ��䡢���Ǵ洢���̻������ơ����֪������ʹ�õ���������ͣ���ͨ������ 
 *         CommandType ����ָ�� ADO ֱ��ת����ش��롣��� CommandType ������ CommandText �����е��������Ͳ�ƥ�䣬���� Execute ����ʱ��
 *         ��������adExecuteNoRecords ����ͨ����С���ڲ�������������ܡ��ó���������ʹ�ã��������� adCmdText �� adCmdStoredProc ��ϣ�
 *         �� adCmdText+adExecuteNoRecords��һ��ʹ�á������ Recordset.Open һ��ʹ�� adExecuteNoRecords�����߸÷���ʹ�� Command ����
 *         ������������
 */
ADODB::CommandTypeEnum MtADOCommand::get_command_type() const{
	clear_last_error();
	try{
		return(_command->GetCommandType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adCmdText);
	}
}

/** 
 * name: set_name
 * brief: ���ö������ơ�
 * param: name - �������ơ�
 * return: --
 * remark: ʹ�� Name ���Կɽ����Ƹ���  Command��Field��Parameter �� Property ���󣬻�������ǵ����ơ����ڻ�û��׷�ӵ� Parameters ����
 *         �е� Parameter ����Name ����Ϊ��/д�������Ѿ�׷�ӵ� Parameter �����Լ�������������Name ����Ϊֻ�����ڼ��������Ʋ���Ψһ��
 *         ���԰��������������������  Name ���ԣ��ڴ�֮�������ֱ��ʹ���������ö������磬��� rstMain.Properties(20).Name Ϊ 
 *         Updatability��������󽫸���������Ϊ rstMain.Properties("Updatability")��
 */
void MtADOCommand::set_name(const CString &name){
	clear_last_error();
	try{
		_command->PutName(static_cast<LPCTSTR>(name));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/** 
 * name: get_name
 * brief: ��ȡ�������ơ�
 * param: --
 * return: ���ض������ơ�
 * remark: ʹ�� Name ���Կɽ����Ƹ���  Command��Field��Parameter �� Property ���󣬻�������ǵ����ơ����ڻ�û��׷�ӵ� Parameters ����
 *         �е� Parameter ����Name ����Ϊ��/д�������Ѿ�׷�ӵ� Parameter �����Լ�������������Name ����Ϊֻ�����ڼ��������Ʋ���Ψһ��
 *         ���԰��������������������  Name ���ԣ��ڴ�֮�������ֱ��ʹ���������ö������磬��� rstMain.Properties(20).Name Ϊ 
 *         Updatability��������󽫸���������Ϊ rstMain.Properties("Updatability")��
 */
CString MtADOCommand::get_name() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_command->GetName()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_prepared
 * brief: ����ָʾִ��ǰ�Ƿ񱣴�����ı���汾��
 * param: yes_or_no - ָʾִ��ǰ�Ƿ񱣴�����ı���汾��
 * return: --
 * remark: ʹ�� Prepared ���Կ�ʹ�ṩ�����״�ִ�� Command ����ǰ���� CommandText ������ָ������׼���ã��ѱ��룩�Ĳ�ѯ�汾��
 *         �����Իή�������״�ִ�е��ٶȣ����ṩ�߶�������б�����ں�̵�����ִ�����ṩ�߿�ʹ���ѱ��������汾������������
 *         ��ִ�����ܡ����������Ϊ False���ṩ�߽�ֱ��ִ�� Command ���������������汾������ṩ�߲�֧������׼������������
 *         ����Ϊ True ʱҲ�����ش������û�з��ش�����ֻ��Ҫ����׼����������󲢽� Prepared ��������Ϊ False ���ɡ�
 */
void MtADOCommand::set_prepared(const BOOL yes_or_no){
	clear_last_error();
	try{
		const short prepared=((TRUE==yes_or_no)?(-1):0);
		_command->PutPrepared(prepared);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_prepared
 * brief: ��ȡָʾִ��ǰ�Ƿ񱣴�����ı���汾��
 * param: --
 * return: ����ָʾִ��ǰ�Ƿ񱣴�����ı���汾��
 * remark: ʹ�� Prepared ���Կ�ʹ�ṩ�����״�ִ�� Command ����ǰ���� CommandText ������ָ������׼���ã��ѱ��룩�Ĳ�ѯ�汾��
 *         �����Իή�������״�ִ�е��ٶȣ����ṩ�߶�������б�����ں�̵�����ִ�����ṩ�߿�ʹ���ѱ��������汾������������
 *         ��ִ�����ܡ����������Ϊ False���ṩ�߽�ֱ��ִ�� Command ���������������汾������ṩ�߲�֧������׼������������
 *         ����Ϊ True ʱҲ�����ش������û�з��ش�����ֻ��Ҫ����׼����������󲢽� Prepared ��������Ϊ False ���ɡ�
 */
BOOL MtADOCommand::get_prepared() const{
	clear_last_error();
	try{
		if(-1==_command->GetPrepared()){
			return(TRUE);
		}else{
			return(FALSE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: get_state
 * brief: ��ȡ��ǰ Command ����״̬��
 * param: --
 * return: ���ص�ǰ Command ����״̬��
 *         ����                                    ˵�� 
 *         ================================================================================================
 *         AdStateClosed                           Ĭ�ϣ�ָʾ�����ǹرյġ� 
 *         AdStateOpen                             ָʾ�����Ǵ򿪵ġ� 
 *         AdStateConnecting                       ָʾ Recordset �����������ӡ� 
 *         AdStateExecuting                        ָʾ Recordset ��������ִ����� 
 *         AdStateFetching                         ָʾ Recordset ����������ڱ���ȡ�� 
 *         ================================================================================================
 * remark: ������ʱʹ�� State ����ȷ��ָ������ĵ�ǰ״̬����������ֻ���ġ�
 *         Recordset ����� State ���Կ��������ֵ�����磬�������ִ����䣬�����Խ��� adStateOpen �� adStateExecuting �����ֵ��
 */
long MtADOCommand::get_state() const{
	clear_last_error();
	try{
		return(_command->GetState());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adStateClosed);
	}
}

/**
 * name: get_parameters
 * brief: ��ȡ Command ����Ĳ�����Ϣ��
 * param: --
 * return: ���� Command ����Ĳ�����Ϣ��
 */
ADODB::ParametersPtr MtADOCommand::get_parameters() const{
	clear_last_error();
	try{
		return(_command->GetParameters());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_properties
 * brief: ��ȡ Command �����������Ϣ��
 * param: --
 * return: ���� Command �����������Ϣ��
 */
ADODB::PropertiesPtr MtADOCommand::get_properties() const{
	clear_last_error();
	try{
		return(_command->GetProperties());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: cancel
 * brief: ȡ��ִ�й�����첽 Execute �� Open �����ĵ��á�
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Cancel ������ִֹ���첽 Execute �� Open �������ã���ͨ�� adAsyncConnect��adAsyncExecute �� adAsyncFetch 
 *         ѡ����ø÷��������������ͼ��ֹ�ķ�����û��ʹ�� adAsyncExecute���� Cancel ����������ʱ�����±���ʾ���ض����Ͷ�����
 *         ʹ�� Cancel ����ʱ����ֹ������
 *         �������Ϊ                                              ����ֹ�Ը÷�������һ���첽���� 
 *         ========================================================================================================
 *         Command                                                Execute 
 *         Connection                                             Execute �� Open 
 *         Recordset                                              Open 
 *         ========================================================================================================
 */
HRESULT MtADOCommand::cancel(){
	clear_last_error();
	try{
		return(_command->Cancel());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: create_parameter
 * breif: ʹ��ָ�����Դ����µ� Parameter ����
 * param: name - ��ѡ���ַ��������� Parameter �������ơ�
 *        data_type - ��ѡ��������ֵ��ָ�� Parameter �����������͡�������Ч������μ� Type ���ԡ�
 *        diretion - ��ѡ��������ֵ��ָ�� Parameter �������͡�������Ч������μ� Direction ���ԡ�
 *        size - ��ѡ��������ֵ��ָ������ֵ��󳤶ȣ����ַ����ֽ���Ϊ��λ����
 *        value - ��ѡ�������ͣ�ָ�� Parameter �����ֵ��
 * return: ����ʹ��ָ�����Դ����µ� Parameter ����
 * remark: ʹ�� CreateParameter ��������ָ�������ơ����͡����򡢴�С��ֵ�����µ� Parameter ����
 *         �ڲ����д��͵�����ֵ����д����Ӧ�� Parameter ���ԡ��÷����޷��Զ��� Parameter ����׷�ӵ� Command ����� Parameter ���ϣ�
 *         �����Ϳ������ø������ԡ������ Parameter ����׷�ӵ����ϣ��� ADO ��ʹ�ø������Ե�ֵ��Ч������� Type ������ָ���ɱ䳤�ȵ���
 *         �����ͣ���ô�ڽ���׷�ӵ� Parameters ����֮ǰ���봫�� Size ������������ Parameter ����� Size ���ԣ����򽫲�������
 */
ADODB::_ParameterPtr MtADOCommand::create_parameter(const CString &name,const ADODB::DataTypeEnum data_type,
	const ADODB::ParameterDirectionEnum diretion,const long size,const _variant_t &value/*=vtMissing*/){
	clear_last_error();
	try{
		return(_command->CreateParameter(
			static_cast<LPCTSTR>(name),data_type,diretion,size,value));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: execute
 * breif: ִ���� CommandText ������ָ���Ĳ�ѯ��SQL ����洢���̡�
 * param: affect_records - ��ѡ�������ͱ������ṩ�����䷵�ز�����Ӱ��ļ�¼��Ŀ��RecordsAffected ������Ӧ���ڲ�����ѯ��洢���̡�
 *                         RecordsAffected �������ɷ��ؽ���Ĳ�ѯ��洢���������صļ�¼��Ŀ����ϸ��Ϣ����ʹ�� RecordCount ���ԡ�
 *        parameters - ��ѡ�����������飬ʹ�� SQL ��䴫�͵Ĳ���ֵ�����øò�������ʱ�����������������ȷֵ����
 *        options - ��ѡ��������ֵ��ָʾ�ṩ����μ��� Command ����� CommandText ���ԡ���ֵ��Ϊ���г���֮һ��
 *                  ����                                   ˵�� 
 *                  =================================================================================================
 *                  AdCmdText                             ָʾ�ṩ��Ӧ��������ı����壨�� SQL ��䣩������ CommandText�� 
 *                  AdCmdTable                            ָʾ ADO Ӧ���� SQL ��ѯ�Ա�� CommandText �����ı��з��������С� 
 *                  AdCmdTableDirect                      ָʾ�ṩ��Ӧ�� CommandText �����ı��з��������С� 
 *                  AdCmdStoredProc                       ָʾ�ṩ��Ӧ���洢���̼��� CommandText�� 
 *                  AdCmdUnknown                          ָʾ CommandText �е���������δ֪�� 
 *                  adAsyncExecute                        ָʾ����Ӧ�첽ִ�С� 
 *                  adAsyncFetch                          ָʾ���� CacheSize ����ָ���ĳ�ʼ����֮���ʣ����Ӧʹ���첽��ȡ�� 
 *                  ==================================================================================================
 * return: ������Ӧ�� Recordset ����
 * remark: ʹ�� Command ����� Execute ������ִ���ڶ���� CommandText ������ָ���Ĳ�ѯ����� CommandText ����ָ�����з��ز�ѯ��
 *         ִ�����������κν�������洢���µ� Recordset �����С����������ǰ��з��ز�ѯ�����ṩ�߷��عرյ� Recordset ����ĳ
 *         ЩӦ�ó�������������Ը÷���ֵ���������Ҫ�κ� Recordset���������ѯ���в�������ʹ�� Command �����в����ĵ�ǰֵ������ͨ
 *         �� Execute ���ô��͵Ĳ����������ǡ������ڵ��� Execute ����ʱͨ��ʡ��ĳЩ��������ֵ�����ǲ����Ӽ���ָ�������Ĵ��������ڷ�
 *         ���б����͵Ĵ�����ͬ�����磬����� 4 ��������ࣩ��������ϣ��ֻΪ��һ���͵��ĸ�����������ֵ������Խ� Array(var1,,,var4) 
 *         ��Ϊ Parameters �������͡�ע��: �� Parameters �����д���ʱ�����������������ȷ��ֵ���ò��������󽫷��� ExecuteComplete 
 *         �¼���
 */
ADODB::_RecordsetPtr MtADOCommand::execute(VARIANT *affect_records,VARIANT *parameters,const long options){
	clear_last_error();
	try{
		return(_command->Execute(affect_records,parameters,options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_last_error_code
 * brief: ��ȡ����Ĵ�����롣
 * param: --
 * return: ��������Ĵ�����롣
 */
long MtADOCommand::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: ��ȡ����Ĵ���������
 * param: --
 * return: ��������Ĵ���������
 */
CString MtADOCommand::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: create_instance
 * brief: ����ʵ����
 * param: --
 * return: --
 */
void MtADOCommand::create_instance(){
	const HRESULT result=
		_command.CreateInstance(_T("ADODB.Command"));
	assert((SUCCEEDED(result))&&(0!=_command));
}

/**
 * name: release_instance
 * brief: �ͷ�ʵ����
 * param: --
 * return: --
 */
void MtADOCommand::release_instance(){
	if(0!=_command){
		_command.Release();
		_command=0;
	}
}

/**
 * name: clear_last_error
 * brief: ������������Ϣ��
 * param: --
 * return: --
 */
void MtADOCommand::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: ��¼���������Ϣ��
 * param: error - ���������Ϣ��
 * return: --
 */
void MtADOCommand::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}