#include"stdafx.h"
#include"MtADORecordset.h"
#include"MtADOConnection.h"
#include<assert.h>

/**
 * name: MtADORecordset
 * brief: ���캯����
 * param: --
 * return: --
 */
MtADORecordset::MtADORecordset(void)
	:_last_error_code(0)
	,_last_error_message(_T(""))
	,_recordset(0){
	create_instance();
}

/**
 * name: ~MtADORecordset
 * brief: ����������
 * param: --
 * return: --
 */
MtADORecordset::~MtADORecordset(void){
	release_instance();
}

/**
 * name: set_absolute_page
 * brief: ָ����ǰ��¼���ڵ�ҳ��
 * param: page - ҳ�š�
 * return: --
 * note: ���û򷵻ش� 1 �� Recordset ���� (PageCount) ����ҳ���ĳ�����ֵ�����߷������³�����
 *       ����                   ˵�� 
 *       ======================================================================================
 *       AdPosUnknown          Recordset Ϊ�գ���ǰλ��δ֪�������ṩ�߲�֧�� AbsolutePage ���ԡ� 
 *       AdPosBOF              ��ǰ��¼ָ��λ�� BOF���� BOF ����Ϊ True���� 
 *       AdPosEOF              ��ǰ��¼ָ��λ�� EOF���� EOF ����Ϊ True���� 
 *       ======================================================================================
 * remark: ʹ�� AbsolutePage ���Կ�ʶ��ǰ��¼���ڵ�ҳ�롣ʹ�� PageSize ���Կɽ� Recordset 
 *         �����߼�����Ϊһϵ�е�ҳ��ÿҳ�ļ�¼������ PageSize�����ҳ���⣬��ҳ��¼�����٣�����
 *         ���߱���֧�ָ����Ե���Ӧ���ܲ���ʹ�ø����ԡ��� AbsolutePosition ����һ����AbsolutePage 
 *         �� 1 ��ʼ���ڵ�ǰ��¼Ϊ Recordset �еĵ�һ����¼ʱ���� 1�����ø����Կ��ƶ����ض�ҳ�ĵ�һ��
 *         ��¼���� PageCount �����пɻ����ҳ����
 */
void MtADORecordset::set_absolute_page(const ADODB::PositionEnum page){
	clear_last_error();
	try{
		_recordset->PutAbsolutePage(page);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: set_absolute_page
 * brief: ָ����ǰ��¼���ڵ�ҳ��
 * param: page - ҳ�š�
 * return: ���ص�ǰ��¼���ڵ�ҳ��
 * note: ���û򷵻ش� 1 �� Recordset ���� (PageCount) ����ҳ���ĳ�����ֵ�����߷������³�����
 *       ����                   ˵�� 
 *       ======================================================================================
 *       AdPosUnknown          Recordset Ϊ�գ���ǰλ��δ֪�������ṩ�߲�֧�� AbsolutePage ���ԡ� 
 *       AdPosBOF              ��ǰ��¼ָ��λ�� BOF���� BOF ����Ϊ True���� 
 *       AdPosEOF              ��ǰ��¼ָ��λ�� EOF���� EOF ����Ϊ True���� 
 *       ======================================================================================
 * remark: ʹ�� AbsolutePage ���Կ�ʶ��ǰ��¼���ڵ�ҳ�롣ʹ�� PageSize ���Կɽ� Recordset 
 *         �����߼�����Ϊһϵ�е�ҳ��ÿҳ�ļ�¼������ PageSize�����ҳ���⣬��ҳ��¼�����٣�����
 *         ���߱���֧�ָ����Ե���Ӧ���ܲ���ʹ�ø����ԡ��� AbsolutePosition ����һ����AbsolutePage 
 *         �� 1 ��ʼ���ڵ�ǰ��¼Ϊ Recordset �еĵ�һ����¼ʱ���� 1�����ø����Կ��ƶ����ض�ҳ�ĵ�һ��
 *         ��¼���� PageCount �����пɻ����ҳ����
 */
ADODB::PositionEnum MtADORecordset::get_absolute_page() const{
	clear_last_error();
	try{
		return(_recordset->GetAbsolutePage());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adPosUnknown);
	}
}

/**
 * name: set_absolute_position
 * brief: ���õ�ǰ��¼�����λ�á�
 * param: position - λ����š�
 * return: --
 * note: ���û򷵻ش� 1 �� Recordset ���� (PageCount) ����ҳ���ĳ�����ֵ�����߷������³�����
 *       ����                               ˵�� 
 *       =============================================================================================
 *       AdPosUnknown                      Recordset Ϊ�գ���ǰλ��δ֪�������ṩ�߲�֧�� AbsolutePage ���ԡ� 
 *       AdPosBOF                          ��ǰ��¼ָ��λ�� BOF���� BOF ����Ϊ True���� 
 *       adPosEOF                          ��ǰ��¼ָ��λ�� EOF���� EOF ����Ϊ True���� 
 *       =============================================================================================
 * remark: ʹ�� AbsolutePosition ���Կɸ������� Recordset �е����λ���ƶ�����¼����ȷ����ǰ��¼�����λ�á��ṩ��
 *         ����֧�ָ����Ե���Ӧ���ܲ���ʹ�ø����ԡ�ͬ AbsolutePage ����һ����AbsolutePosition �� 1 ��ʼ�����ڵ�ǰ
 *         ��¼Ϊ Recordset �еĵ�һ����¼ʱ���� 1���� RecordCount ���Կɻ�� Recordset ������ܼ�¼�������� AbsolutePosition 
 *         ����ʱ����ʹ������ָ��λ�ڵ�ǰ�����еļ�¼��ADO Ҳ��ʹ����ָ���ļ�¼��ʼ���¼�¼�����¼��ػ��档CacheSize 
 *         ���Ծ����ü�¼��Ĵ�С��
 *         ע��: ���ܽ� AbsolutePosition ������Ϊ����ļ�¼���ʹ�á�ɾ��ǰ��ļ�¼ʱ��������¼�ĵ�ǰλ�ý������ı䡣
 *         ��� Recordset �������²�ѯ�����´򿪣����޷���֤������¼����ͬ�� AbsolutePosition����ǩ��Ȼ�Ǳ��ֺͷ�
 *         �ظ���λ�õ��Ƽ���ʽ���������������͵� Recordset ����Ķ�λʱ��Ψһ�ķ�ʽ��
 */
void MtADORecordset::set_absolute_position(const ADODB::PositionEnum position){
	clear_last_error();
	try{
		_recordset->PutAbsolutePosition(position);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_absolute_position
 * brief: ��ȡ��ǰ��¼�����λ�á�
 * param: --
 * return: ���ص�ǰ��¼�����λ�á�
 * note: ���û򷵻ش� 1 �� Recordset ���� (PageCount) ����ҳ���ĳ�����ֵ�����߷������³�����
 *       ����                               ˵�� 
 *       =============================================================================================
 *       AdPosUnknown                      Recordset Ϊ�գ���ǰλ��δ֪�������ṩ�߲�֧�� AbsolutePage ���ԡ� 
 *       AdPosBOF                          ��ǰ��¼ָ��λ�� BOF���� BOF ����Ϊ True���� 
 *       adPosEOF                          ��ǰ��¼ָ��λ�� EOF���� EOF ����Ϊ True���� 
 *       =============================================================================================
 * remark: ʹ�� AbsolutePosition ���Կɸ������� Recordset �е����λ���ƶ�����¼����ȷ����ǰ��¼�����λ�á��ṩ��
 *         ����֧�ָ����Ե���Ӧ���ܲ���ʹ�ø����ԡ�ͬ AbsolutePage ����һ����AbsolutePosition �� 1 ��ʼ�����ڵ�ǰ
 *         ��¼Ϊ Recordset �еĵ�һ����¼ʱ���� 1���� RecordCount ���Կɻ�� Recordset ������ܼ�¼�������� AbsolutePosition 
 *         ����ʱ����ʹ������ָ��λ�ڵ�ǰ�����еļ�¼��ADO Ҳ��ʹ����ָ���ļ�¼��ʼ���¼�¼�����¼��ػ��档CacheSize 
 *         ���Ծ����ü�¼��Ĵ�С��
 *         ע��: ���ܽ� AbsolutePosition ������Ϊ����ļ�¼���ʹ�á�ɾ��ǰ��ļ�¼ʱ��������¼�ĵ�ǰλ�ý������ı䡣
 *         ��� Recordset �������²�ѯ�����´򿪣����޷���֤������¼����ͬ�� AbsolutePosition����ǩ��Ȼ�Ǳ��ֺͷ�
 *         �ظ���λ�õ��Ƽ���ʽ���������������͵� Recordset ����Ķ�λʱ��Ψһ�ķ�ʽ��
 */
ADODB::PositionEnum MtADORecordset::get_absolute_position() const{
	clear_last_error();
	try{
		return(_recordset->GetAbsolutePosition());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adPosUnknown);
	}
}

/**
 * name: get_active_command
 * brief: ��ȡ������ Recordset ����� Command ����
 * param: --
 * return: ���ع����� Recordset ����� Command ����
 * remark: ActiveCommand ����Ϊֻ�������û��ʹ�� Command ���󴴽���ǰ 
 *         Recordset�������� Null �������á������ֻ�н�� Recordset ����
 *         ���ʹ�ø����Բ��ҹ����� Command ����
 */
ADODB::_CommandPtr MtADORecordset::get_active_command() const{
	clear_last_error();
	try{
		return(_recordset->GetActiveCommand());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_active_connection
 * breif: ����ָ���� Command �� Recordset ����ǰ������ Connection ����
 * param: connection - Connection ����
 * return: --
 * note: ʹ�� ActiveConnection ���Կ�ȷ�������Ͻ�ִ��ָ�� Command ������ָ�� 
 *       Recordset �� Connection ����
 * remark: ���ڴ򿪵� Recordset ������� Source ���Ա�����Ϊ��Ч Command ����� Recordset ����
 *         ActiveConnection ����Ϊֻ�������򣬸�����Ϊ��/д�����Խ�����������Ϊ��Ч�� Connection ����
 *         ������Ϊ��Ч�������ַ�������ʱ���ṩ�߿�ʹ�øö��崴���µ� Connection ���󣬲������ӡ����⣬
 *         �ṩ�߿��Խ�����������Ϊ�µ� Connection �����Ա������ṩ������չ������Ϣ�� Connection �����
 *         ִ������������ʹ�� Open ������ ActiveConnection ������ Recordset ����ActiveConnection 
 *         ���Խ��̳иò�����ֵ������� Recordset ����� Source ��������Ϊ��Ч Command ���������Recordset �� 
 *         ActiveConnection ���Խ��̳� Command ����� ActiveConnection ���Ե����á�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��ֻ�ܽ�����������Ϊ�����ַ�����Microsoft 
 *         Visual Basic �� VBScript �У�Nothing�� 
 */
void MtADORecordset::set_active_connection(ADODB::_ConnectionPtr connection){
	clear_last_error();
	try{
		_recordset->PutActiveConnection(_variant_t(connection));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_active_connection
 * breif: ��ȡָ���� Command �� Recordset ����ǰ������ Connection ����
 * param: --
 * return: ����ָ���� Command �� Recordset ����ǰ������ Connection ����
 * note: ʹ�� ActiveConnection ���Կ�ȷ�������Ͻ�ִ��ָ�� Command ������ָ�� 
 *       Recordset �� Connection ����
 * remark: ���ڴ򿪵� Recordset ������� Source ���Ա�����Ϊ��Ч Command ����� Recordset ����
 *         ActiveConnection ����Ϊֻ�������򣬸�����Ϊ��/д�����Խ�����������Ϊ��Ч�� Connection ����
 *         ������Ϊ��Ч�������ַ�������ʱ���ṩ�߿�ʹ�øö��崴���µ� Connection ���󣬲������ӡ����⣬
 *         �ṩ�߿��Խ�����������Ϊ�µ� Connection �����Ա������ṩ������չ������Ϣ�� Connection �����
 *         ִ������������ʹ�� Open ������ ActiveConnection ������ Recordset ����ActiveConnection 
 *         ���Խ��̳иò�����ֵ������� Recordset ����� Source ��������Ϊ��Ч Command ���������Recordset �� 
 *         ActiveConnection ���Խ��̳� Command ����� ActiveConnection ���Ե����á�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��ֻ�ܽ�����������Ϊ�����ַ�����Microsoft 
 *         Visual Basic �� VBScript �У�Nothing�� 
 */
ADODB::_ConnectionPtr MtADORecordset::get_active_connection() const{
	clear_last_error();
	try{
		return(_recordset->GetActiveConnection());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_bof
 * breif: ��ȡ��ǰ��¼λ���Ƿ�λ��Recordset����ĵ�һ����¼֮ǰ��
 * param: --
 * return: ���ص�ǰ��¼λ���Ƿ�λ��Recordset����ĵ�һ����¼֮ǰ��
 * remark: ʹ�� BOF �� EOF ���Կ�ȷ�� Recordset �����Ƿ������¼�����ߴ�һ����¼�ƶ�����һ����¼ʱ�Ƿ񳬳�
 *         Recordset ��������ơ������ǰ��¼λ�ڵ�һ����¼֮ǰ��BOF ���Խ����� True (-1)�������ǰ��¼Ϊ
 *         ��һ����¼��λ������򽫷��� False (0)�������ǰ��¼λ�� Recordset ��������һ����¼֮�� EOF 
 *         ���Խ����� True������ǰ��¼Ϊ Recordset ��������һ����¼��λ����ǰ���򽫷��� False����� BOF 
 *         �� EOF ����Ϊ True����û�е�ǰ��¼�������û�м�¼�� Recordset ����BOF �� EOF ���Խ�����Ϊ 
 *         True���� Recordset ����� RecordCount ��������Ϊ�㡣�����ٰ���һ����¼�� Recordset ����ʱ��
 *         ��һ����¼Ϊ��ǰ��¼���� BOF �� EOF ����Ϊ False�����ɾ�� Recordset �����б���������¼��BOF 
 *         �� EOF ���Խ����� False��ֱ�����°��ŵ�ǰ��¼��
 */
BOOL MtADORecordset::get_bof() const{
	clear_last_error();
	try{
		if(0==_recordset->GetadoBOF()){
			return(FALSE);
		}else{
			return(TRUE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: get_eof
 * breif: ��ȡ��ǰ��¼λ���Ƿ�λ��Recordset��������һ����¼֮��
 * param: --
 * return: ���ص�ǰ��¼λ���Ƿ�λ��Recordset��������һ����¼֮��
 * remark: ʹ�� BOF �� EOF ���Կ�ȷ�� Recordset �����Ƿ������¼�����ߴ�һ����¼�ƶ�����һ����¼ʱ�Ƿ񳬳�
 *         Recordset ��������ơ������ǰ��¼λ�ڵ�һ����¼֮ǰ��BOF ���Խ����� True (-1)�������ǰ��¼Ϊ
 *         ��һ����¼��λ������򽫷��� False (0)�������ǰ��¼λ�� Recordset ��������һ����¼֮�� EOF 
 *         ���Խ����� True������ǰ��¼Ϊ Recordset ��������һ����¼��λ����ǰ���򽫷��� False����� BOF 
 *         �� EOF ����Ϊ True����û�е�ǰ��¼�������û�м�¼�� Recordset ����BOF �� EOF ���Խ�����Ϊ 
 *         True���� Recordset ����� RecordCount ��������Ϊ�㡣�����ٰ���һ����¼�� Recordset ����ʱ��
 *         ��һ����¼Ϊ��ǰ��¼���� BOF �� EOF ����Ϊ False�����ɾ�� Recordset �����б���������¼��BOF 
 *         �� EOF ���Խ����� False��ֱ�����°��ŵ�ǰ��¼��
 */
BOOL MtADORecordset::get_eof() const{
	clear_last_error();
	try{
		if(0==_recordset->GetadoEOF()){
			return(FALSE);
		}else{
			return(TRUE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: set_bookmark
 * breif: ����Ψһ��ʶ Recordset �����е�ǰ��¼����ǩ�����߽� Recordset 
 *        ����ĵ�ǰ��¼����Ϊ����Ч��ǩ����ʶ�ļ�¼��
 * param: bookmark - ��ǩ��
 * return: --
 * remark: ʹ�� Bookmark ���Կɱ��浱ǰ��¼��λ�ò���ʱ���ص��ü�¼����ǩ
 *         ֻ����֧����ǩ���ܵ� Recordset ������ʹ�á��� Recordset ����ʱ��
 *         ��ÿ����¼����Ψһ����ǩ��Ҫ���浱ǰ��¼����ǩ���뽫 Bookmark ����
 *         ��ֵ����һ���������ƶ���������¼��Ҫ���ٷ��ص��ü�¼���뽫�� Recordset 
 *         ����� Bookmark ��������Ϊ�ñ�����ֵ���û������޷��鿴��ǩ��ֵ��Ҳͬ��
 *         �޷�����ǩֱ�ӽ��бȽϣ�ָ��ͬһ��¼��������ǩ��ֵ���ܲ�ͬ�������ʹ�� Clone 
 *         �������� Recordset ��һ����������ԭʼ�ĺ͸��Ƶ� Recordset ���� Bookmark 
 *         ����������ͬ�������滻ʹ�á����ǣ��޷��滻ʹ�ò�ͬ Recordset �������ǩ��
 *         ��ʹ��Щ��ǩ��ͨ��ͬһ����Դ��������ġ�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��Bookmark ����ʼ����Ч��
 */
void MtADORecordset::set_bookmark(const _variant_t &bookmark){
	clear_last_error();
	try{
		_recordset->PutBookmark(bookmark);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_bookmark
 * breif: ��ȡΨһ��ʶ Recordset �����е�ǰ��¼����ǩ�����߽� Recordset 
 *        ����ĵ�ǰ��¼����Ϊ����Ч��ǩ����ʶ�ļ�¼��
 * param: --
 * return: ���ؼ�����Ч��ǩ�ı����ͱ��ʽ��
 * remark: ʹ�� Bookmark ���Կɱ��浱ǰ��¼��λ�ò���ʱ���ص��ü�¼����ǩ
 *         ֻ����֧����ǩ���ܵ� Recordset ������ʹ�á��� Recordset ����ʱ��
 *         ��ÿ����¼����Ψһ����ǩ��Ҫ���浱ǰ��¼����ǩ���뽫 Bookmark ����
 *         ��ֵ����һ���������ƶ���������¼��Ҫ���ٷ��ص��ü�¼���뽫�� Recordset 
 *         ����� Bookmark ��������Ϊ�ñ�����ֵ���û������޷��鿴��ǩ��ֵ��Ҳͬ��
 *         �޷�����ǩֱ�ӽ��бȽϣ�ָ��ͬһ��¼��������ǩ��ֵ���ܲ�ͬ�������ʹ�� Clone 
 *         �������� Recordset ��һ����������ԭʼ�ĺ͸��Ƶ� Recordset ���� Bookmark 
 *         ����������ͬ�������滻ʹ�á����ǣ��޷��滻ʹ�ò�ͬ Recordset �������ǩ��
 *         ��ʹ��Щ��ǩ��ͨ��ͬһ����Դ��������ġ�
 *        ��Զ�����ݷ��� �ڿͻ��� (ADOR) Recordset ������ʹ��ʱ��Bookmark ����ʼ����Ч��
 */
_variant_t MtADORecordset::get_bookmark() const{
	clear_last_error();
	try{
		return(_recordset->GetBookmark());
	}catch(const _com_error &error){
		record_last_error(error);
		return(_variant_t());
	}
}

/**
 * name: set_catch_size
 * brief: ���û����ڱ����ڴ��е� Recordset ����ļ�¼����
 * param: size - ����ߴ�
 * return: --
 * remark: ʹ�� CacheSize ���Կɿ����ṩ���ڻ�����������ļ�¼����Ŀ�����ɿ���һ�λָ��������ڴ�ļ�¼����
 *         ���磬��� CacheSize Ϊ 10���״δ� Recordset ������ṩ�߽�ǰ�� 10 ����¼���뱾���ڴ档
 *         ���� Recordset �������ƶ�ʱ���ṩ�߷��ر����ڴ滺�����е����ݣ�һ���ƶ��������������ļ�¼��
 *         �ṩ�߱㽫����Դ������ 10 ����¼�ָ������档������ Recordset ����Ĵ���ڵ��������Ե�ֵ��
 *         ���Ǹ��ĸ�ֵֻӰ����������Դ���뻺��ļ�¼����ֻ��������ֵ��������Ļ����еĵ�ǰ���ݡ����Ҫ
 *         �����ļ�¼�� CacheSize ָ�����٣��ṩ�߽���������ļ�¼������������󡣲����� CacheSize ��
 *         ��Ϊ�㣬���򽫷��ش��󡣴ӻ���ָ��ļ�¼����ӳ�����û�������Դͬʱ�����ĸ��ġ�����ǿ�ж����л���
 *         ���ݽ��и��£���ʹ�� Resync ������
 */
void MtADORecordset::set_catch_size(const long size){
	clear_last_error();
	try{
		_recordset->PutCacheSize(size);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_catch_size
 * brief: ��ȡ�����ڱ����ڴ��е� Recordset ����ļ�¼����
 * param: --
 * return: ���ػ����ڱ����ڴ��е� Recordset ����ļ�¼����
 * remark: ʹ�� CacheSize ���Կɿ����ṩ���ڻ�����������ļ�¼����Ŀ�����ɿ���һ�λָ��������ڴ�ļ�¼����
 *         ���磬��� CacheSize Ϊ 10���״δ� Recordset ������ṩ�߽�ǰ�� 10 ����¼���뱾���ڴ档
 *         ���� Recordset �������ƶ�ʱ���ṩ�߷��ر����ڴ滺�����е����ݣ�һ���ƶ��������������ļ�¼��
 *         �ṩ�߱㽫����Դ������ 10 ����¼�ָ������档������ Recordset ����Ĵ���ڵ��������Ե�ֵ��
 *         ���Ǹ��ĸ�ֵֻӰ����������Դ���뻺��ļ�¼����ֻ��������ֵ��������Ļ����еĵ�ǰ���ݡ����Ҫ
 *         �����ļ�¼�� CacheSize ָ�����٣��ṩ�߽���������ļ�¼������������󡣲����� CacheSize ��
 *         ��Ϊ�㣬���򽫷��ش��󡣴ӻ���ָ��ļ�¼����ӳ�����û�������Դͬʱ�����ĸ��ġ�����ǿ�ж����л���
 *         ���ݽ��и��£���ʹ�� Resync ������
 */
long MtADORecordset::get_catch_size() const{
	clear_last_error();
	try{
		return(_recordset->GetCacheSize());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_cursor_location
 * brief: �����α�����λ�á�
 * param: location - �α�����λ�á�
 * return: --
 * note: ���û򷵻ؿ�����Ϊ����ĳ�������ĳ�����ֵ��
 *       ����                     ˵�� 
 *       =============================================================================
 *       adUseNone               û��ʹ���α���񡣣��ó����ѹ�ʱ����ֻΪ�������ݲų��֣��� 
 *       adUseClient             ʹ���ɱ����α���ṩ�Ŀͻ����αꡣ�����α����ͨ������ʹ�õ�
 *                               ��๦�ܿ��������������ṩ���α��޷�ʹ�õģ����ʹ�ø����ö�
 *                               ����Щ��Ҫ���õĹ������кô��ġ�AdUseClient �����������ԣ�
 *                               Ҳ֧��ͬ��� adUseClientBatch�� 
 *       adUseServer             Ĭ��ֵ��ʹ�������ṩ�ߵĻ����������ṩ���αꡣ��Щ�α���ʱ��
 *                               �������������û�������Դ�����ĸ��ľ��ж���������ԡ����ǣ�
 *                               Microsoft Client Cursor Provider�����ѶϿ������ļ�¼����
 *                               ��ĳЩ�����޷��ɷ��������α�ģ�⣬ͨ�������ý��޷�ʹ����Щ���ܡ� 
 *       ==============================================================================
 * remark: �����������ڿ������ṩ�ߵĸ����α���н���ѡ��ͨ��������ѡ��ʹ�ÿͻ����α���λ�ڷ������ϵ�ĳ���α�⡣
 *         ���������ý��������Ѿ����ú�Ž�����������Ӱ�졣���� CursorLocation ���Բ���Ӱ�����е����ӡ����� Connection 
 *         ��رյ� Recordset ������Ϊ��/д�����Դ򿪵� Recordset ������Ϊֻ������ Execute �������ص��α�̳и����á�
 *         Recordset ���Զ�����֮�����������м̳и����á�
 *        ��Զ�����ݷ��� �����ڿͻ��� (ADOR) Recordset �� Connection ����ʱ��ֻ�ܽ� CursorLocation ��������Ϊ 
 *         adUseClient��
 */
void MtADORecordset::set_cursor_location(const ADODB::CursorLocationEnum location){
	clear_last_error();
	try{
		_recordset->PutCursorLocation(location);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_cursor_location
 * brief: ��ȡ�α�����λ�á�
 * param: --
 * return: �����α�����λ�á�
 * note: ���û򷵻ؿ�����Ϊ����ĳ�������ĳ�����ֵ��
 *       ����                     ˵�� 
 *       =============================================================================
 *       adUseNone               û��ʹ���α���񡣣��ó����ѹ�ʱ����ֻΪ�������ݲų��֣��� 
 *       adUseClient             ʹ���ɱ����α���ṩ�Ŀͻ����αꡣ�����α����ͨ������ʹ�õ�
 *                               ��๦�ܿ��������������ṩ���α��޷�ʹ�õģ����ʹ�ø����ö�
 *                               ����Щ��Ҫ���õĹ������кô��ġ�AdUseClient �����������ԣ�
 *                               Ҳ֧��ͬ��� adUseClientBatch�� 
 *       adUseServer             Ĭ��ֵ��ʹ�������ṩ�ߵĻ����������ṩ���αꡣ��Щ�α���ʱ��
 *                               �������������û�������Դ�����ĸ��ľ��ж���������ԡ����ǣ�
 *                               Microsoft Client Cursor Provider�����ѶϿ������ļ�¼����
 *                               ��ĳЩ�����޷��ɷ��������α�ģ�⣬ͨ�������ý��޷�ʹ����Щ���ܡ� 
 *       ===============================================================================
 * remark: �����������ڿ������ṩ�ߵĸ����α���н���ѡ��ͨ��������ѡ��ʹ�ÿͻ����α���λ�ڷ������ϵ�ĳ���α�⡣
 *         ���������ý��������Ѿ����ú�Ž�����������Ӱ�졣���� CursorLocation ���Բ���Ӱ�����е����ӡ����� Connection 
 *         ��رյ� Recordset ������Ϊ��/д�����Դ򿪵� Recordset ������Ϊֻ������ Execute �������ص��α�̳и����á�
 *         Recordset ���Զ�����֮�����������м̳и����á�
 *        ��Զ�����ݷ��� �����ڿͻ��� (ADOR) Recordset �� Connection ����ʱ��ֻ�ܽ� CursorLocation ��������Ϊ 
 *                       adUseClient��
 */
ADODB::CursorLocationEnum MtADORecordset::get_cursor_location() const{
	clear_last_error();
	try{
		return(_recordset->GetCursorLocation());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adUseNone);
	}
}

/**
 * name: set_cursor_type
 * brief: ������Recordset������ʹ�õ��α����͡�
 * param: type - �α����͡�
 * return: --
 * note: ���û򷵻�����ĳ��CursorTypeEnumֵ��
 *       ����                         ˵�� 
 *       =============================================================================================
 *       AdOpenForwardOnly           ����ǰ�α꣬Ĭ��ֵ������ֻ���ڼ�¼����ǰ�����⣬�뾲̬�α���ͬ��
 *                                   ��ֻ��Ҫ�ڼ�¼���е����ƶ�ʱ��ʹ������������ܡ� 
 *       AdOpenKeyset                �����αꡣ���ܴ����ļ�¼�����ܷ��������û�ɾ���ļ�¼�������޷�
 *                                   �鿴�����û���ӵļ�¼�⣬�����α��붯̬�α����ơ���Ȼ���Կ���
 *                                   �����û����ĵ����ݡ� 
 *       AdOpenDynamic               ��̬�αꡣ���Կ��������û���������ӡ����ĺ�ɾ���������ڼ�¼����
 *                                   �����������͵��ƶ������������ṩ�߲�֧�ֵ���ǩ������ 
 *       AdOpenStatic                ��̬�αꡣ���������������ݻ����ɱ���ļ�¼���ϵľ�̬���������⣬
 *                                   �������û���������ӡ����Ļ�ɾ�����ɼ��� 
 *       ==============================================================================================
 * remark: ʹ�� CursorType ���Կ�ָ���� Recordset ����ʱӦ��ʹ�õ��α����͡�Recordset �ر�ʱ CursorType ����Ϊ��/д��
 *         �� Recordset ��ʱ������Ϊֻ��������� CursorLocation ��������Ϊ adUseClient ��ֻ֧�� adUseStatic �����á�
 *         ��������˲�֧�ֵ�ֵ�����ᵼ�´��󣬽�ʹ����ӽ�֧�ֵ� CursorType������ṩ�߲�֧����������α����ͣ��ṩ�߿��ܻ�
 *         ���������α����͡��� Recordset ����ʱ�������� CursorType ����ʹ֮��ʵ��ʹ�õ��α�ƥ�䡣Ҫ��֤�����α��ָ�����ܣ�
 *         ��ʹ�� Supports �������ر� Recordset ��CursorType ���Խ��ָ�Ϊ��������á�
 *         �±�˵��ÿ���α�����������ṩ�߹��ܣ��� Supports ����������ʶ���� 
 *         ====================================================================================================
 *         ���ڸ� CursorType ��ĳRecordset                 ����������Щ������ Supports �������뷵�� True 
 *         AdOpenForwardOnly                              �� 
 *         AdOpenKeyset                                  AdBookmark��adHoldRecords��adMovePrevious��adResync 
 *         AdOpenDynamic                                 adMovePrevious 
 *         AdOpenStatic                                  adBookmark, adHoldRecords, adMovePrevious, adResync 
 *         ====================================================================================================
 *         ע��: ���ܶ��ڶ�̬�α�ͽ���ǰ�α� Supports(adUpdateBatch) �������棬���������������Ӧʹ�ü����α��̬�αꡣ
 *              �뽫 LockType ��������Ϊ adLockBatchOptimistic��Ȼ�� CursorLocation ��������Ϊ adUseClient ������
 *              ��������Ҫ�� OLE DB �α����
 *        ��Զ�����ݷ��� �����ڿͻ��� (ADOR) Recordset ����ʱ��ֻ�ܽ� CursorType ��������Ϊ adOpenStatic��
 */
void MtADORecordset::set_cursor_type(const ADODB::CursorTypeEnum type){
	clear_last_error();
	try{
		_recordset->PutCursorType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_cursor_type
 * brief: ��ȡ��Recordset������ʹ�õ��α����͡�
 * param: --
 * return: ������Recordset������ʹ�õ��α����͡�
 * note: ���û򷵻�����ĳ��CursorTypeEnumֵ��
 *       ����                         ˵�� 
 *       =============================================================================================
 *       AdOpenForwardOnly           ����ǰ�α꣬Ĭ��ֵ������ֻ���ڼ�¼����ǰ�����⣬�뾲̬�α���ͬ��
 *                                   ��ֻ��Ҫ�ڼ�¼���е����ƶ�ʱ��ʹ������������ܡ� 
 *       AdOpenKeyset                �����αꡣ���ܴ����ļ�¼�����ܷ��������û�ɾ���ļ�¼�������޷�
 *                                   �鿴�����û���ӵļ�¼�⣬�����α��붯̬�α����ơ���Ȼ���Կ���
 *                                   �����û����ĵ����ݡ� 
 *       AdOpenDynamic               ��̬�αꡣ���Կ��������û���������ӡ����ĺ�ɾ���������ڼ�¼����
 *                                   �����������͵��ƶ������������ṩ�߲�֧�ֵ���ǩ������ 
 *       AdOpenStatic                ��̬�αꡣ���������������ݻ����ɱ���ļ�¼���ϵľ�̬���������⣬
 *                                   �������û���������ӡ����Ļ�ɾ�����ɼ��� 
 *       ==============================================================================================
 * remark: ʹ�� CursorType ���Կ�ָ���� Recordset ����ʱӦ��ʹ�õ��α����͡�Recordset �ر�ʱ CursorType ����Ϊ��/д��
 *         �� Recordset ��ʱ������Ϊֻ��������� CursorLocation ��������Ϊ adUseClient ��ֻ֧�� adUseStatic �����á�
 *         ��������˲�֧�ֵ�ֵ�����ᵼ�´��󣬽�ʹ����ӽ�֧�ֵ� CursorType������ṩ�߲�֧����������α����ͣ��ṩ�߿��ܻ�
 *         ���������α����͡��� Recordset ����ʱ�������� CursorType ����ʹ֮��ʵ��ʹ�õ��α�ƥ�䡣Ҫ��֤�����α��ָ�����ܣ�
 *         ��ʹ�� Supports �������ر� Recordset ��CursorType ���Խ��ָ�Ϊ��������á�
 *         �±�˵��ÿ���α�����������ṩ�߹��ܣ��� Supports ����������ʶ���� 
 *         ====================================================================================================
 *         ���ڸ� CursorType ��ĳRecordset                 ����������Щ������ Supports �������뷵�� True 
 *         AdOpenForwardOnly                              �� 
 *         AdOpenKeyset                                  AdBookmark��adHoldRecords��adMovePrevious��adResync 
 *         AdOpenDynamic                                 adMovePrevious 
 *         AdOpenStatic                                  adBookmark, adHoldRecords, adMovePrevious, adResync 
 *         ====================================================================================================
 *         ע��: ���ܶ��ڶ�̬�α�ͽ���ǰ�α� Supports(adUpdateBatch) �������棬���������������Ӧʹ�ü����α��̬�αꡣ
 *              �뽫 LockType ��������Ϊ adLockBatchOptimistic��Ȼ�� CursorLocation ��������Ϊ adUseClient ������
 *              ��������Ҫ�� OLE DB �α����
 *        ��Զ�����ݷ��� �����ڿͻ��� (ADOR) Recordset ����ʱ��ֻ�ܽ� CursorType ��������Ϊ adOpenStatic��
 */
ADODB::CursorTypeEnum MtADORecordset::get_cursor_type() const{
	clear_last_error();
	try{
		return(_recordset->GetCursorType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adOpenForwardOnly);
	}
}

/**
 * name: set_data_member 
 * breif: ���ô� DataSource ���������õĶ����м��������ݳ�Ա�����ơ�
 * param: member - ��Ա���ơ�
 * return: --
 * remark: ����������ͨ�������ݻ������������ݰ󶨿ؼ��������ݻ��������������ݼ��ϣ�����Դ����
 *         �����ݼ��ϰ���������ʾΪ Recordset ������������������ݳ�Ա����DataMember �� 
 *         DataSource ���Ա�����ͬʹ�á�DataMember ���Ծ������� DataSource ������ָ����
 *         �ĸ�������Ϊ Recordset ������ȡ���������ø�����ǰ����ر� Recordset �������
 *         ������ DataSource ����ǰû������ DataMember ���ԣ������� DataSource ������ָ
 *         ���Ķ�����ʶ�� DataMember ���ƣ���������������ϸ��Ϣ������ġ�Data Access SDK��
 *         �ġ�Control Writer���������ݡ�
 */
void MtADORecordset::set_data_member(const CString &member){
	clear_last_error();
	try{
		_recordset->PutDataMember(static_cast<_bstr_t>(member));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_data_member 
 * breif: ��ȡ�� DataSource ���������õĶ����м��������ݳ�Ա�����ơ�
 * param: --
 * return: ���ش� DataSource ���������õĶ����м��������ݳ�Ա�����ơ�
 * remark: ����������ͨ�������ݻ������������ݰ󶨿ؼ��������ݻ��������������ݼ��ϣ�����Դ����
 *         �����ݼ��ϰ���������ʾΪ Recordset ������������������ݳ�Ա����DataMember �� 
 *         DataSource ���Ա�����ͬʹ�á�DataMember ���Ծ������� DataSource ������ָ����
 *         �ĸ�������Ϊ Recordset ������ȡ���������ø�����ǰ����ر� Recordset �������
 *         ������ DataSource ����ǰû������ DataMember ���ԣ������� DataSource ������ָ
 *         ���Ķ�����ʶ�� DataMember ���ƣ���������������ϸ��Ϣ������ġ�Data Access SDK��
 *         �ġ�Control Writer���������ݡ�
 */
CString MtADORecordset::get_data_member() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_recordset->GetDataMember()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: get_data_source
 * brief: ָ�������������ݽ�����ʾΪ Recordset ����Ķ���
 * param: --
 * return: ����ָ�������������ݽ�����ʾΪ Recordset ����Ķ���
 * remark: ����������ͨ�������ݻ������������ݰ󶨿ؼ��������ݻ��������������ݼ��ϣ�����Դ����
 *         �����ݼ��ϰ���������ʾΪRecordset������������������ݳ�Ա����DataMember �� 
 *         DataSource ���Ա�����ͬʹ�á������õĶ������ִ�� IDataSource �ӿڣ����ұ���
 *         ���� IRowset �ӿڡ���ϸ��Ϣ������ġ�Data Access SDK���ġ�Control Writer������
 *         ���ݡ�
 */
IUnknownPtr MtADORecordset::get_data_source() const{
	clear_last_error();
	try{
		return(_recordset->GetDataSource());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_edit_mode
 * brief: ��ȡ��ǰ��¼�ı༭״̬��
 * param: --
 * return: ���ص�ǰ��¼�ı༭״̬��
 * note: ��������ĳ�� EditModeEnum ֵ��
 *       ����                     ˵�� 
 *       =============================================================================================
 *       AdEditNone              ָʾ��ǰû�б༭������ 
 *       AdEditInProgress        ָʾ��ǰ��¼�е������ѱ��޸ĵ�δ���档 
 *       AdEditAdd               ָʾ AddNew �����ѱ����ã��Ҹ��ƻ������еĵ�ǰ��¼����δ���浽���ݿ��е��¼�¼ �� 
 *       AdEditDelete            ָʾ��ǰ��¼�ѱ�ɾ���� 
 *       =============================================================================================
 * remark: ADO ά���뵱ǰ��¼�����ı༭��������������ָʾ�Ƿ�Ըû�������˸��ģ����Ƿ��Ѵ������µļ�¼��ʹ�� EditMode 
 *         ���Կ�ȷ����ǰ��¼�ı༭״̬������༭���̱��жϣ����ԶԹ���ĸ��Ľ��в��ԣ���ȷ���Ƿ���Ҫʹ�� Update ������ 
 *         CancelUpdate �������йز�ͬ�༭������ EditMode ���Ե���ϸ˵������ο� AddNew ������
 */
ADODB::EditModeEnum MtADORecordset::get_edit_mode() const{
	clear_last_error();
	try{
		return(_recordset->GetEditMode());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adEditNone);
	}
}

/**
 * name: set_filter
 * brief: Ϊ Recordset �е�����ָ��ɸѡ������
 * param: filter - ָ����ɸѡ������
 * return: --
 * note: ���û򷵻ر�����ֵ����ֵ��������ĳ�����ݣ� 
 *       �����ַ��� �� ��һ�������� AND �� OR ���������ӵ��Ӿ���ɵ��ַ�����
 *       ��ǩ���� �� ָ�� Recordset �����м�¼��Ψһ��ǩֵ���顣
 *       ����ĳ�� FilterGroupEnum ֵ������ ˵�� 
 *       AdFilterNone ɾ����ǰɸѡ�������ָ��鿴�����м�¼�� 
 *       AdFilterPendingRecords ����ֻ�鿴�Ѹ�������δ���͵��������ļ�¼��ֻ��Ӧ����������ģʽ�� 
 *       AdFilterAffectedRecords ����ֻ�鿴��һ�� Delete��Resync��UpdateBatch �� CancelBatch ������Ӱ��ļ�¼�� 
 *       AdFilterFetchedRecords ����鿴��ǰ�������еļ�¼������һ�δ����ݿ��м�����¼�ĵ��ý���� 
 *       AdFilterConflictingRecords ����鿴����һ����������ʧ�ܵļ�¼�� 
 * remark: ʹ�� Filter ���Կ�ѡ���Ե����� Recordset �����еļ�¼����ɸѡ�� Recordset ����Ϊ��ǰ�αꡣ�⽫Ӱ����ڵ�
 *         ǰ�α귵��ֵ���������ԣ��� AbsolutePosition��AbsolutePage��RecordCount �� PageCount����Ϊ�� Filter ����
 *         ����Ϊ�ض�ֵ�ɽ���ǰ��¼�ƶ���������ֵ�ĵ�һ����¼�������ַ����� FieldName-Operator-Value ��ʽ���硰LastName = 
 *         'Smith'�������Ӿ���ɡ����Դ����õ����� AND���硰LastName = 'Smith' AND FirstName = 'John'������ OR���硰LastName = 
 *         'Smith' OR LastName = 'Jones'�����Ӿ����Ӷ��ɵĻ���Ӿ䡣���������ַ�������ѭ���¹��� FieldName ����Ϊ Recordset ��
 *         ����Ч�ֶ���������ֶ��������ո񣬱����÷����Ž��ֶ�����������Operator ����ʹ�õĲ�����Ϊ��<��>��<=��>=��<>��= �� LIKE��
 *         Value ���������ֶ�ֵ���� 'Smith'��#8/24/95#��12.345 �� $50.00�����бȽϵ�ֵ���ַ���ʹ�õ����Ŷ�����ʹ�þ��� (#)���������֣�
 *         ����ʹ��С���㡢���ҷ��źͿ�ѧ����������� Operator Ϊ LIKE��Value ���ʹ��ͨ�����ֻ����ʹ���Ǻ� (*) �Ͱٷֺ� (%) ͨ�����
 *         ���ұ���Ϊ�ַ�����β�ַ���Value ����Ϊ Null��AND �� OR �ڼ�����û���Ⱥ�֮�֡���ʹ�����Ž��Ӿ���顣������������ʾ�������Ƚ��� 
 *         OR ���ӵ��Ӿ���飬Ȼ�󽫸����� and ���ӵ������Ӿ䡣(LastName = 'Smith' OR LastName = 'Jones') AND FirstName = 'John'
 *         ��֮�෴�����Թ���������ʽ��ɸѡ��(LastName = 'Smith' AND FirstName = 'John') OR (LastName = 'Jones' AND FirstName = 
 *         'John')�� LIKE �Ӿ��У�������ʽ�Ŀ�ͷ�ͽ�βʹ��ͨ������� LastName Like '*mit*'��������ֻ�ڽ�βʹ��ͨ������磬LastName Like 
 *         'Smit*'�� �� ͨ��������鿴�����磩�ϴε��� UpdateBatch ����ʱ�ܵ�Ӱ��ļ�¼��ɸѡ����ʹ����������ģʽʱ�������ĵ�����¼��ͻ����
 *         �ڽ�������� Filter ���Ա�����ܻ�����������ݷ�����ͻ����ĳ��¼�ѱ������û�ɾ������ʧ�ܡ��ڴ�����£��ṩ�߽����ض� Errors ���ϵ�
 *         ���浫��ֹͣ����ִ�С�ֻ����������Ҫ�ļ�¼�Ϸ�����ͻʱ�Ų�������ʱ����ʹ�� Status ���Կɶ�λ������ͻ�ļ�¼���� Filter ��������Ϊ
 *         �㳤���ַ��� ("") ��ʹ�� adFilterNone ��������ͬ��Ч����һ������ Filter ���ԣ���ǰ��¼λ�ý��ƶ��� Recordset ����ɸѡ��¼�Ӽ���
 *         �ĵ�һ����¼�����Ƶأ���� Filter ���Ժ󣬵�ǰ��¼λ�ý��ƶ��� Recordset �ĵ�һ����¼���йؿ��� Filter ����һ��ʹ�ô����������ǩ
 *         ֵ�Ľ��ͣ���ο� Bookmark ���ԡ�
 */
void MtADORecordset::set_filter(const _variant_t &filter){
	clear_last_error();
	try{
		_recordset->PutFilter(filter);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_filter
 * brief: ��ȡ Recordset �е�����ָ��ɸѡ������
 * param: filter - ָ����ɸѡ������
 * return: ���� Recordset �е�����ָ��ɸѡ������
 * note: ���û򷵻ر�����ֵ����ֵ��������ĳ�����ݣ� 
 *       �����ַ��� �� ��һ�������� AND �� OR ���������ӵ��Ӿ���ɵ��ַ�����
 *       ��ǩ���� �� ָ�� Recordset �����м�¼��Ψһ��ǩֵ���顣
 *       ����ĳ�� FilterGroupEnum ֵ������ ˵�� 
 *       AdFilterNone ɾ����ǰɸѡ�������ָ��鿴�����м�¼�� 
 *       AdFilterPendingRecords ����ֻ�鿴�Ѹ�������δ���͵��������ļ�¼��ֻ��Ӧ����������ģʽ�� 
 *       AdFilterAffectedRecords ����ֻ�鿴��һ�� Delete��Resync��UpdateBatch �� CancelBatch ������Ӱ��ļ�¼�� 
 *       AdFilterFetchedRecords ����鿴��ǰ�������еļ�¼������һ�δ����ݿ��м�����¼�ĵ��ý���� 
 *       AdFilterConflictingRecords ����鿴����һ����������ʧ�ܵļ�¼�� 
 * remark: ʹ�� Filter ���Կ�ѡ���Ե����� Recordset �����еļ�¼����ɸѡ�� Recordset ����Ϊ��ǰ�αꡣ�⽫Ӱ����ڵ�
 *         ǰ�α귵��ֵ���������ԣ��� AbsolutePosition��AbsolutePage��RecordCount �� PageCount����Ϊ�� Filter ����
 *         ����Ϊ�ض�ֵ�ɽ���ǰ��¼�ƶ���������ֵ�ĵ�һ����¼�������ַ����� FieldName-Operator-Value ��ʽ���硰LastName = 
 *         'Smith'�������Ӿ���ɡ����Դ����õ����� AND���硰LastName = 'Smith' AND FirstName = 'John'������ OR���硰LastName = 
 *         'Smith' OR LastName = 'Jones'�����Ӿ����Ӷ��ɵĻ���Ӿ䡣���������ַ�������ѭ���¹��� FieldName ����Ϊ Recordset ��
 *         ����Ч�ֶ���������ֶ��������ո񣬱����÷����Ž��ֶ�����������Operator ����ʹ�õĲ�����Ϊ��<��>��<=��>=��<>��= �� LIKE��
 *         Value ���������ֶ�ֵ���� 'Smith'��#8/24/95#��12.345 �� $50.00�����бȽϵ�ֵ���ַ���ʹ�õ����Ŷ�����ʹ�þ��� (#)���������֣�
 *         ����ʹ��С���㡢���ҷ��źͿ�ѧ����������� Operator Ϊ LIKE��Value ���ʹ��ͨ�����ֻ����ʹ���Ǻ� (*) �Ͱٷֺ� (%) ͨ�����
 *         ���ұ���Ϊ�ַ�����β�ַ���Value ����Ϊ Null��AND �� OR �ڼ�����û���Ⱥ�֮�֡���ʹ�����Ž��Ӿ���顣������������ʾ�������Ƚ��� 
 *         OR ���ӵ��Ӿ���飬Ȼ�󽫸����� and ���ӵ������Ӿ䡣(LastName = 'Smith' OR LastName = 'Jones') AND FirstName = 'John'
 *         ��֮�෴�����Թ���������ʽ��ɸѡ��(LastName = 'Smith' AND FirstName = 'John') OR (LastName = 'Jones' AND FirstName = 
 *         'John')�� LIKE �Ӿ��У�������ʽ�Ŀ�ͷ�ͽ�βʹ��ͨ������� LastName Like '*mit*'��������ֻ�ڽ�βʹ��ͨ������磬LastName Like 
 *         'Smit*'�� �� ͨ��������鿴�����磩�ϴε��� UpdateBatch ����ʱ�ܵ�Ӱ��ļ�¼��ɸѡ����ʹ����������ģʽʱ�������ĵ�����¼��ͻ����
 *         �ڽ�������� Filter ���Ա�����ܻ�����������ݷ�����ͻ����ĳ��¼�ѱ������û�ɾ������ʧ�ܡ��ڴ�����£��ṩ�߽����ض� Errors ���ϵ�
 *         ���浫��ֹͣ����ִ�С�ֻ����������Ҫ�ļ�¼�Ϸ�����ͻʱ�Ų�������ʱ����ʹ�� Status ���Կɶ�λ������ͻ�ļ�¼���� Filter ��������Ϊ
 *         �㳤���ַ��� ("") ��ʹ�� adFilterNone ��������ͬ��Ч����һ������ Filter ���ԣ���ǰ��¼λ�ý��ƶ��� Recordset ����ɸѡ��¼�Ӽ���
 *         �ĵ�һ����¼�����Ƶأ���� Filter ���Ժ󣬵�ǰ��¼λ�ý��ƶ��� Recordset �ĵ�һ����¼���йؿ��� Filter ����һ��ʹ�ô����������ǩ
 *         ֵ�Ľ��ͣ���ο� Bookmark ���ԡ�
 */
_variant_t MtADORecordset::get_filter() const{
	clear_last_error();
	try{
		return(_recordset->GetFilter());
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: set_lock_type
 * brief: ���ñ༭�����жԼ�¼ʹ�õ��������͡�
 * param: type - �������͡�
 * return: --
 * note: ���û򷵻�����ĳ�� LockTypeEnum ��ֵ��
 *       ����                          ˵��
 *       ===============================================================================================================
 *       adLockReadOnly               Ĭ��ֵ��ֻ�����޷��������ݡ� 
 *       adLockPessimistic            ����ʽ��¼���������������ṩ��ִ�б�Ҫ�Ĳ���ȷ���ɹ��༭��¼��
 *                                    ͨ�����ñ༭ʱ������������Դ�ļ�¼�ķ�ʽ�� 
 *       adLockOptimistic             ����ʽ��¼���������������ṩ��ʹ�ÿ���ʽ������ֻ�ڵ��� Update ����ʱ������¼�� 
 *       adLockBatchOptimistic        ����ʽ�����¡���������������ģʽ�෴��������ģʽ�� 
 *       ===============================================================================================================
 * remark: �� Recordset ǰ���� LockType ���Կ�ָ����ʱ�ṩ��Ӧ��ʹ�õ��������͡���ȡ�����Կɷ����ڴ򿪵� Recordset 
 *         ����������ʹ�õ��������͡�Recordset �ر�ʱ LockType ����Ϊ��/д����ʱ������Ϊֻ�����ṩ�߿��ܲ�֧�����е���
 *         �����͡����ĳ�ṩ�߲�֧������� LockType ���ã����滻Ϊ�������͵�������Ҫȷ�� Recordset ������õ�ʵ������
 *         ���ܣ���ͨ�� adUpdate �� adUpdateBatch ʹ�� Supports ��������� CursorLocation ���Ա�����Ϊ adUseClient��
 *         ����֧�� adLockPessimistic ���á����ò�֧�ֵ�ֵ�������������Ϊ��ʱ��ʹ��֧�ֵ���ӽ��� LockType ��ֵ��
 */
void MtADORecordset::set_lock_type(const ADODB::LockTypeEnum type){
	clear_last_error();
	try{
		_recordset->PutLockType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_lock_type
 * brief: ��ȡ�༭�����жԼ�¼ʹ�õ��������͡�
 * param: --
 * return: ��ȡ�༭�����жԼ�¼ʹ�õ��������͡�
 * note: ���û򷵻�����ĳ�� LockTypeEnum ��ֵ��
 *       ����                          ˵��
 *       ===============================================================================================================
 *       adLockReadOnly               Ĭ��ֵ��ֻ�����޷��������ݡ� 
 *       adLockPessimistic            ����ʽ��¼���������������ṩ��ִ�б�Ҫ�Ĳ���ȷ���ɹ��༭��¼��
 *                                    ͨ�����ñ༭ʱ������������Դ�ļ�¼�ķ�ʽ�� 
 *       adLockOptimistic             ����ʽ��¼���������������ṩ��ʹ�ÿ���ʽ������ֻ�ڵ��� Update ����ʱ������¼�� 
 *       adLockBatchOptimistic        ����ʽ�����¡���������������ģʽ�෴��������ģʽ�� 
 *       ===============================================================================================================
 * remark: �� Recordset ǰ���� LockType ���Կ�ָ����ʱ�ṩ��Ӧ��ʹ�õ��������͡���ȡ�����Կɷ����ڴ򿪵� Recordset 
 *         ����������ʹ�õ��������͡�Recordset �ر�ʱ LockType ����Ϊ��/д����ʱ������Ϊֻ�����ṩ�߿��ܲ�֧�����е���
 *         �����͡����ĳ�ṩ�߲�֧������� LockType ���ã����滻Ϊ�������͵�������Ҫȷ�� Recordset ������õ�ʵ������
 *         ���ܣ���ͨ�� adUpdate �� adUpdateBatch ʹ�� Supports ��������� CursorLocation ���Ա�����Ϊ adUseClient��
 *         ����֧�� adLockPessimistic ���á����ò�֧�ֵ�ֵ�������������Ϊ��ʱ��ʹ��֧�ֵ���ӽ��� LockType ��ֵ��
 */
ADODB::LockTypeEnum MtADORecordset::get_lock_type() const{
	clear_last_error();
	try{
		return(_recordset->GetLockType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adLockReadOnly);
	}
}

/**
 * name: set_marshal_options
 * brief: ����Ҫ�����ȷ��ط������ļ�¼��
 * param: options - Ҫ�����ȷ��ط������ļ�¼��
 * return: ����Ҫ�����ȷ��ط������ļ�¼��
 * note: ���û򷵻�����ĳ�����ĳ�����ֵ��
 *       ����                       ˵�� 
 *       =================================================================
 *       AdMarshalAll              Ĭ��ֵ�����������н����ص��������� 
 *       AdMarshalModifiedOnly     ����ֻ�����޸ĵ��з��ص���������
 *       =================================================================
 * remark: ��ʹ�ÿͻ��� (ADOR) Recordset ʱ�����ڿͻ��˱��޸ĵļ�¼��ͨ�����������ȡ��ļ���д���м��� Web ��������
 *         ������ָԽ���̻߳���̱߽��װ�ͷ��ͽӿڷ��������Ĺ��̡������޸ĵ�Զ������ͨ�����ȱ����»��м��� Web ������ʱ��
 *         ���� MarshalOptions ���Կ���������ܡ�
 *        ��Զ�����ݷ��� ������ֻ���ڿͻ��� (ADOR) Recordset ��ʹ�á�
 */
void MtADORecordset::set_marshal_options(const ADODB::MarshalOptionsEnum options){
	clear_last_error();
	try{
		_recordset->PutMarshalOptions(options);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_marshal_options
 * brief: ��ȡҪ�����ȷ��ط������ļ�¼��
 * param: --
 * return: ����Ҫ�����ȷ��ط������ļ�¼��
 * note: ���û򷵻�����ĳ�����ĳ�����ֵ��
 *       ����                       ˵�� 
 *       =================================================================
 *       AdMarshalAll              Ĭ��ֵ�����������н����ص��������� 
 *       AdMarshalModifiedOnly     ����ֻ�����޸ĵ��з��ص���������
 *       =================================================================
 * remark: ��ʹ�ÿͻ��� (ADOR) Recordset ʱ�����ڿͻ��˱��޸ĵļ�¼��ͨ�����������ȡ��ļ���д���м��� Web ��������
 *         ������ָԽ���̻߳���̱߽��װ�ͷ��ͽӿڷ��������Ĺ��̡������޸ĵ�Զ������ͨ�����ȱ����»��м��� Web ������ʱ��
 *         ���� MarshalOptions ���Կ���������ܡ�
 *        ��Զ�����ݷ��� ������ֻ���ڿͻ��� (ADOR) Recordset ��ʹ�á�
 */
ADODB::MarshalOptionsEnum MtADORecordset::get_marshal_options() const{
	clear_last_error();
	try{
		return(_recordset->GetMarshalOptions());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adMarshalAll);
	}
}

/**
 * name: set_max_records
 * brief: ����ͨ����ѯ���� Recordset �ļ�¼�������Ŀ��
 * param: records - ����¼����
 * return: --
 * note: ���û򷵻س�����ֵ��Ĭ��ֵΪ�㣨û�����ƣ���
 * remark: ʹ�� MaxRecords ���Կɶ��ṩ�ߴ�����Դ���صļ�¼���������ơ�
 *         �����Ե�Ĭ������Ϊ�㣬�����ṩ�߷�����������ļ�¼��Recordset �ر�ʱ��
 *         MaxRecords ����Ϊ��/д����ʱΪֻ����
 */
void MtADORecordset::set_max_records(const long records){
	clear_last_error();
	try{
		_recordset->PutMaxRecords(records);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_max_records
 * brief: ��ȡͨ����ѯ���� Recordset �ļ�¼�������Ŀ��
 * param: --
 * return: ����ͨ����ѯ���� Recordset �ļ�¼�������Ŀ��
 * note: ���û򷵻س�����ֵ��Ĭ��ֵΪ�㣨û�����ƣ���
 * remark: ʹ�� MaxRecords ���Կɶ��ṩ�ߴ�����Դ���صļ�¼���������ơ�
 *         �����Ե�Ĭ������Ϊ�㣬�����ṩ�߷�����������ļ�¼��Recordset �ر�ʱ��
 *         MaxRecords ����Ϊ��/д����ʱΪֻ����
 */
long MtADORecordset::get_max_records() const{
	clear_last_error();
	try{
		return(_recordset->GetMaxRecords());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_page_count
 * brief: ��ȡ Recordset �������������ҳ����
 * param: --
 * return: ���� Recordset �������������ҳ����
 * note: ���س�����ֵ��
 * remark: ʹ�� PageCount ���Կ�ȷ�� Recordset ���������ݵ�ҳ����
 *         ��ҳ���Ǵ�С���� PageSize �������õļ�¼�顣��ʹ���ҳ��������
 *         ���ڼ�¼���� PageSize ֵ�٣���ҳҲ����Ϊ PageCount ֵ�еĸ���ҳ���м�����
 *         ��� Recordset ����֧�ָ����ԣ���ֵΪ-1 �Ա��� PageCount �޷�ȷ������
 *         ��ҳ�Ĺ��ܵ���ϸ��Ϣ������� PageSize �� AbsolutePage ���ԡ�
 */
long MtADORecordset::get_page_count() const{
	clear_last_error();
	try{
		return(_recordset->GetPageCount());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_page_size
 * brief: ���� Recordset ��һҳ�������ļ�¼����
 * param: size - һҳ�������ļ�¼����
 * return: --
 * note: ���û򷵻س�����ֵ����ֵָʾĳҳ�ϵļ�¼����Ĭ��ֵΪ 10��
 * remark: ʹ�� PageSize ���Կ�ȷ������߼�����ҳ�ļ�¼��������
 *         ҳ�Ĵ�С����ʹ�� AbsolutePage �����ƶ����ض�ҳ�ĵ�һ����¼��
 *         ����ϣ�������û������ݽ��з�ҳʱ���������� Web-�����������зǳ����ã�
 *         ��������ĳһʱ�̲鿴һ�������ļ�¼����ʱ�������ø����ԣ���ֵ��������
 *         ���ض�ҳ��һ����¼��λ�á�
 */
void MtADORecordset::set_page_size(const long size){
	clear_last_error();
	try{
		_recordset->PutPageSize(size);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_page_size
 * brief: ��ȡ Recordset ��һҳ�������ļ�¼����
 * param: --
 * return: ���� Recordset ��һҳ�������ļ�¼����
 * note: ���û򷵻س�����ֵ����ֵָʾĳҳ�ϵļ�¼����Ĭ��ֵΪ 10��
 * remark: ʹ�� PageSize ���Կ�ȷ������߼�����ҳ�ļ�¼��������
 *         ҳ�Ĵ�С����ʹ�� AbsolutePage �����ƶ����ض�ҳ�ĵ�һ����¼��
 *         ����ϣ�������û������ݽ��з�ҳʱ���������� Web-�����������зǳ����ã�
 *         ��������ĳһʱ�̲鿴һ�������ļ�¼����ʱ�������ø����ԣ���ֵ��������
 *         ���ض�ҳ��һ����¼��λ�á�
 */
long MtADORecordset::get_page_size() const{
	clear_last_error();
	try{
		return(_recordset->GetPageSize());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_record_count
 * brief: ��ȡ Recordset �����м�¼�ĵ�ǰ��Ŀ��
 * param: --
 * return: ���� Recordset �����м�¼�ĵ�ǰ��Ŀ��
 * note: ���س�����ֵ��
 * remark: ʹ�� RecordCount ���Կ�ȷ�� Recordset �����м�¼����Ŀ��ADO �޷�ȷ����¼��ʱ��
 *         ��������ṩ�߻��α����Ͳ�֧�� RecordCount��������Է��� �C1�����ѹرյ� Recordset �ϵ� RecordCount ���Խ���������
 *         ��� Recordset ����֧�ֽ��ƶ�λ����ǩ���� Supports (adApproxPosition) �� Supports (adBookmark) ���Է��� True����
 *         �����Ƿ���ȫ����ֵ����ֵ��Ϊ Recordset �м�¼�ľ�ȷ��Ŀ����� Recordset ����֧�ֽ��ƶ�λ�������Կ������ڱ��������
 *         ��¼���м����ͼ����Է��ؾ�ȷ RecordCount ֵ������������Դ��Recordset ������α����ͻ�Ӱ���Ƿ��ܹ�ȷ����¼����Ŀ���Խ�
 *         ��ǰ�α꣬RecordCount ���Խ����� -1���Ծ�̬������α귵��ʵ�ʼ������Զ�̬�α�ȡ��������Դ���� -1 ��ʵ�ʼ�����
 */
long MtADORecordset::get_record_count() const{
	clear_last_error();
	try{
		return(_recordset->GetRecordCount());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_sort
 * brief: ָ��һ������ Recordset ��֮������ֶ�������ָ���������ǽ�����ֶν�������
 * param: sort - �����ַ�����
 * return: --
 * note: ���û򷵻���֮������ö��ŷָ����ֶ����ַ��������е�ÿ�������� Recordset �е� Field��
 *       ����ѡ�����ո������ָ���ֶ�����˳��Ĺؼ��� ASC �� DESC�� 
 * remark: ʵ�������ݲ�û���������У�ֻ�Ǽ򵥵ذ������˳����з��ʡ���� CursorLocation ���Ա�����Ϊ 
 *         adUseClient�����������в����ڣ���Ϊ Sort ������ָ����ÿ���ֶδ�����ʱ�������� Sort ����
 *         ����Ϊ���ַ�����ʹ������Ϊԭʼ˳�򣬲�ɾ����ʱ�������ִ�����������ɾ����������ؼ��� ASC �� 
 *         DESC ������ͻ���ֶ��޷�����Ϊ��ASC����DESC������ͨ���ڷ��� Recordset �Ĳ�ѯ��ʹ�� AS �ؼ��֣�
 *         ����ʹ�÷������Ƴ�ͻ���ֶ����ñ�����
 */
void MtADORecordset::set_sort(const CString &sort){
	clear_last_error();
	try{
		_recordset->PutSort(static_cast<LPCTSTR>(sort));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_sort
 * brief: ��ȡһ������ Recordset ��֮������ֶ�������ָ���������ǽ�����ֶν�������
 * param: --
 * return: ����һ������ Recordset ��֮������ֶ�������ָ���������ǽ�����ֶν�������
 * note: ���û򷵻���֮������ö��ŷָ����ֶ����ַ��������е�ÿ�������� Recordset �е� Field��
 *       ����ѡ�����ո������ָ���ֶ�����˳��Ĺؼ��� ASC �� DESC�� 
 * remark: ʵ�������ݲ�û���������У�ֻ�Ǽ򵥵ذ������˳����з��ʡ���� CursorLocation ���Ա�����Ϊ 
 *         adUseClient�����������в����ڣ���Ϊ Sort ������ָ����ÿ���ֶδ�����ʱ�������� Sort ����
 *         ����Ϊ���ַ�����ʹ������Ϊԭʼ˳�򣬲�ɾ����ʱ�������ִ�����������ɾ����������ؼ��� ASC �� 
 *         DESC ������ͻ���ֶ��޷�����Ϊ��ASC����DESC������ͨ���ڷ��� Recordset �Ĳ�ѯ��ʹ�� AS �ؼ��֣�
 *         ����ʹ�÷������Ƴ�ͻ���ֶ����ñ�����
 */
CString MtADORecordset::get_sort() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_recordset->GetSort()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_source
 * brief: ָʾ Recordset ���������ݵ���Դ��Command ����SQL ��䡢������ƻ�洢���̣���
 * param: source - ���ݵ���Դ��
 * return: --
 * note: �����ַ���ֵ�� Command �������á��������ַ���ֵ��
 * remark: ʹ�� Source ����ָ�� Recordset ���������Դ���� Recordset ����ʹ��������֮һ��
 *         Command ���������SQL ��䡢�洢���̻������ơ�Source ���Զ��ڹرյ� Recordset 
 *         �ǿɶ�/д�ģ����ڴ򿪵� Recordset ��ֻ���ġ�������� Source ����Ϊ Command ����
 *         Recordset ����� ActiveConnection ���Խ��̳�ָ�� Command ����� ActiveConnection 
 *         ���Ե�ֵ�����ǣ���ȡ Source ���Խ������� Command ���󣬶��ǽ� Command ����� CommandText 
 *         ���Է��ص����� Source ���Եĵط������ Source ������һ�� SQL ��䡢�洢���̻������ƣ�
 *         �����ͨ������ Open ����������Ӧ�� Options �������Ż����ܡ�
 */
void MtADORecordset::set_source(const CString &source){
	clear_last_error();
	try{
		_recordset->PutSource(static_cast<LPCTSTR>(source));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_source
 * brief: ��ȡ Recordset ���������ݵ���Դ��Command ����SQL ��䡢������ƻ�洢���̣���
 * param: --
 * return: ���� Recordset ���������ݵ���Դ��Command ����SQL ��䡢������ƻ�洢���̣���
 * note: �����ַ���ֵ�� Command �������á��������ַ���ֵ��
 * remark: ʹ�� Source ����ָ�� Recordset ���������Դ���� Recordset ����ʹ��������֮һ��
 *         Command ���������SQL ��䡢�洢���̻������ơ�Source ���Զ��ڹرյ� Recordset 
 *         �ǿɶ�/д�ģ����ڴ򿪵� Recordset ��ֻ���ġ�������� Source ����Ϊ Command ����
 *         Recordset ����� ActiveConnection ���Խ��̳�ָ�� Command ����� ActiveConnection 
 *         ���Ե�ֵ�����ǣ���ȡ Source ���Խ������� Command ���󣬶��ǽ� Command ����� CommandText 
 *         ���Է��ص����� Source ���Եĵط������ Source ������һ�� SQL ��䡢�洢���̻������ƣ�
 *         �����ͨ������ Open ����������Ӧ�� Options �������Ż����ܡ�
 */
_variant_t MtADORecordset::get_source() const{
	clear_last_error();
	try{
		return(_recordset->GetSource());
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: get_state
 * brief: ��ȡ��ǰ Recordset ����״̬��
 * param: --
 * return: ���ص�ǰ Recordset ����״̬��
 * note: �����п�Ӧ�ö���˵�������״̬�Ǵ򿪻��ǹرա���ִ���첽������ Recordset ����
 *       ˵����ǰ�Ķ���״̬�����ӡ�ִ�л��ǻ�ȡ��
 *       �������г���֮һ�ĳ�����ֵ��
 *       ����                                    ˵�� 
 *       ========================================================================================
 *       AdStateClosed                          Ĭ�ϣ�ָʾ�����ǹرյġ� 
 *       AdStateOpen                            ָʾ�����Ǵ򿪵ġ� 
 *       AdStateConnecting                      ָʾ Recordset �����������ӡ� 
 *       AdStateExecuting                       ָʾ Recordset ��������ִ����� 
 *       AdStateFetching                        ָʾ Recordset ����������ڱ���ȡ�� 
 *       ========================================================================================
 * remark: ������ʱʹ�� State ����ȷ��ָ������ĵ�ǰ״̬����������ֻ���ġ�Recordset ����� State ���Կ��������ֵ��
 *         ���磬�������ִ����䣬�����Խ��� adStateOpen �� adStateExecuting �����ֵ��
 */
long MtADORecordset::get_state() const{
	clear_last_error();
	try{
		return(_recordset->GetState());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adStateClosed);
	}
}

/**
 * name: get_status
 * brief: ��ȡ�й������»��������������ĵ�ǰ��¼��״̬��
 * param: --
 * return: �����й������»��������������ĵ�ǰ��¼��״̬��
 * note: ��������һ������ RecordStatusEnum ֵ֮�͡�
 *       ����                                ˵�� 
 *       ===============================================================================================
 *       AdRecOK                            �ɹ��ظ��¼�¼�� 
 *       AdRecNew                           ��¼���½��ġ� 
 *       AdRecModified                      ��¼���޸ġ� 
 *       AdRecDeleted                       ��¼��ɾ���� 
 *       AdRecUnmodified                    ��¼û���޸ġ� 
 *       AdRecInvalid                       ������ǩ��Ч����¼û�б��档 
 *       AdRecMultipleChanges               ����Ӱ������¼����˼�¼δ�����档 
 *       AdRecPendingChanges                ���ڼ�¼���ù���Ĳ��룬���δ�����档 
 *       AdRecCanceled                      ���ڲ�����ȡ����δ�����¼�� 
 *       AdRecCantRelease                   �������м�¼������û�б����¼�¼�� 
 *       AdRecConcurrencyViolation          ���ڿ���ʽ������ʹ���У���¼δ�����档 
 *       AdRecIntegrityViolation            �����û�Υ��������Լ������¼δ�����档 
 *       AdRecMaxChangesExceeded            ���ڴ��ڹ��������ģ���¼δ�����档 
 *       AdRecObjectOpen                    ������򿪵Ĵ�������ͻ����¼δ�����档 
 *       AdRecOutOfMemory                   ���ڼ�����ڴ治�㣬��¼δ�����档 
 *       AdRecPermissionDenied              �����û�û���㹻��Ȩ�ޣ���¼δ�����档 
 *       AdRecSchemaViolation               ���ڼ�¼Υ���������ݿ�Ľṹ�����δ�����档 
 *       AdRecDBDeleted                     ��¼�Ѿ�������Դ��ɾ���� 
 *       =================================================================================================
 *remark: ʹ�� Status ���Բ鿴���������б��޸ĵļ�¼����Щ���ı�����Ҳ��ʹ�� Status ���Բ鿴��������ʱʧ�ܼ�¼��״̬��
 *        ���磬���� Recordset ����� Resync��UpdateBatch �� CancelBatch �������������� Recordset ����� Filter 
 *        ����Ϊ��ǩ���顣ʹ�ø����ԣ��ɼ��ָ����¼Ϊ��ʧ�ܲ�����������
 */
long MtADORecordset::get_status() const{
	clear_last_error();
	try{
		return(_recordset->GetStatus());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adRecOK);
	}
}

/**
 * name: set_stay_in_sync
 * brief: �ڷּ� Recordset ������ָʾ������λ�ø���ʱ���Ի����Ӽ�¼�������Ӽ������������Ƿ����ġ�
 * param�� is_stay_in_sync - �Ƿ���ġ�
 * return: --
 * note: ���û򷵻ز�����ֵ���������Ϊ True���� Recordset ���������λ��ʱ�Ӽ������£��������Ϊ False��
 *       ���Ӽ�������������ǰ�Ӽ������ݶ����ܸ� Recordset �����Ƿ������λ�á�
 * remark: ������Ӧ���ڷּ���¼���������� MSDataShape �ṩ��֧�ֵļ�¼�������ұ����ڸ� Recordset �����ò��ܼ����� 
 *         Recordset�������Լ򻯷ּ���¼���Ķ�λ��
 */
void MtADORecordset::set_stay_in_sync(const BOOL is_stay_in_sync){
	clear_last_error();
	try{
		const short stay_in_sync=((TRUE==is_stay_in_sync)?-1:0);
		_recordset->PutStayInSync(stay_in_sync);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_stay_in_sync
 * brief: ��ȡ�ڷּ� Recordset ������ָʾ������λ�ø���ʱ���Ի����Ӽ�¼�������Ӽ������������Ƿ����ġ�
 * param�� --
 * return: �����ڷּ� Recordset ������ָʾ������λ�ø���ʱ���Ի����Ӽ�¼�������Ӽ������������Ƿ����ġ�
 * note: ���û򷵻ز�����ֵ���������Ϊ True���� Recordset ���������λ��ʱ�Ӽ������£��������Ϊ False��
 *       ���Ӽ�������������ǰ�Ӽ������ݶ����ܸ� Recordset �����Ƿ������λ�á�
 * remark: ������Ӧ���ڷּ���¼���������� MSDataShape �ṩ��֧�ֵļ�¼�������ұ����ڸ� Recordset �����ò��ܼ����� 
 *         Recordset�������Լ򻯷ּ���¼���Ķ�λ��
 */
BOOL MtADORecordset::get_stay_in_sync() const{
	clear_last_error();
	try{
		if(-1==_recordset->GetStayInSync()){
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
 * name: get_fileds
 * brief: ��ȡ��ǰ��¼���е��ֶ���Ϣ��
 * param: --
 * return: ���ص�ǰ��¼���е��ֶ���Ϣ��
 */
ADODB::FieldsPtr MtADORecordset::get_fileds() const{
	clear_last_error();
	try{
		return(_recordset->GetFields());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_properties
 * brief: ��ȡ��ǰ��¼��������Ϣ��
 * param: --
 * return: ���ص�ǰ��¼��������Ϣ��
 */
ADODB::PropertiesPtr MtADORecordset::get_properties() const{
	clear_last_error();
	try{
		return(_recordset->GetProperties());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: add_new
 * brief: �����ɸ��� Recordset ������¼�¼��
 * param: field_list -  ��ѡ���¼�¼���ֶεĵ������ơ�һ�����ƻ����λ�á�
 *        values - ��ѡ���¼�¼���ֶεĵ�����һ��ֵ����� Fields �����飬
 *                 ��ô Values Ҳ����������ͬ��Ա�������飬���򽫷�������
 *                 �ֶ����ƵĴ��������ÿ�������е��ֶ�ֵ�Ĵ�����ƥ�䡣
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� AddNew ���������ͳ�ʼ���¼�¼��ͨ�� adAddNew ʹ�� Supports ��������֤�Ƿ��ܹ�����¼��ӵ���ǰ�� Recordset ����
 *         �ڵ��� AddNew �������¼�¼����Ϊ��ǰ��¼�����ڵ��� Update �������������Ϊ��ǰ��¼����� Recordset ����֧����ǩ��
 *         ���ƶ���������¼ʱ���޷����¼�¼���з��ʡ��Ƿ���Ҫ���� Requery ���������¼�¼��ȡ������ʹ�õ��α����͡�����ڱ༭��ǰ��¼
 *         ������¼�¼ʱ���� AddNew��ADO ������ Update ���������κθ��Ĳ������¼�¼��AddNew ��������Ϊȡ���� Recordset ����ĸ�
 *         ��ģʽ�Լ��Ƿ��� Fields �� Values ����������������ģʽ������ Update ����ʱ�ṩ�߻�����������д���������Դ���£����ò�
 *         �������� AddNew �����ɽ� EditMode ��������Ϊ adEditAdd���ṩ�߽��κ��ֶ�ֵ�ĸ��Ļ����ڱ��ء����� Update �����ɽ��¼�¼
 *         ���ݵ����ݿⲢ�� EditMode ��������Ϊ adEditNone����������� Fields �� Values ������ADO ���������¼�¼���ݵ����ݿ⣨��
 *         ����� Update������ EditMode ����ֵû�иı� (adEditNone)����������ģʽ���ṩ�߻��������Ĳ�ֻ�ڵ��� UpdateBatch ʱ��
 *         ��д���������Դ���£����ò��������� AddNew �����ɽ� EditMode ��������Ϊ adEditAdd���ṩ�߽��κ��ֶ�ֵ�ĸ��Ļ����ڱ��ء�
 *         ���� Update �����ɽ��µļ�¼��ӵ���ǰ��¼������ EditMode ��������Ϊ adEditNone�����ڵ��� UpdateBatch ����֮ǰ�ṩ��
 *         �������Ĵ��ݵ��������ݿ⡣������� Fields �� Values ������ADO ���¼�¼���͸��ṩ���Ա㻺�棻��Ҫ���� UpdateBatch ������
 *         �¼�¼���ݵ��������ݿ⡣
 *         ��� Unique Table ��̬���Ա����ã����� Recordset �ǶԶ����ִ�� JOIN �����Ľ������ô��AddNew ����ֻ�ܽ��ֶβ��뵽�� 
 *         Unique Table �����������ı��С�
 */
HRESULT MtADORecordset::add_new(const _variant_t &field_list/*=vtMissing*/,const _variant_t &values/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->AddNew(field_list,values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel
 * brief: ȡ��ִ�й�����첽 Execute �� Open �����ĵ��á�
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Cancel ������ִֹ���첽 Execute �� Open �������ã���ͨ�� adAsyncConnect��adAsyncExecute
 *         �� adAsyncFetch ѡ����ø÷��������������ͼ��ֹ�ķ�����û��ʹ�� adAsyncExecute���� Cancel ����
 *         ������ʱ����
 *         �±���ʾ���ض����Ͷ�����ʹ�� Cancel ����ʱ����ֹ������
 *         �������Ϊ                                       ����ֹ�Ը÷�������һ���첽���� 
 *         =======================================================================================
 *         Command                                         Execute 
 *         Connection                                      Execute �� Open 
 *         Recordset                                       Open 
 *         =======================================================================================
 */
HRESULT MtADORecordset::cancel(){
	clear_last_error();
	try{
		return(_recordset->Cancel());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel_bantch
 * brief: ȡ������������¡�
 * param: affect_records - ��ѡ�� AffectEnum ֵ������ CancelBatch ������Ӱ���¼����Ŀ����Ϊ���г���֮һ��
 *        ����                                         ˵�� 
 *        =========================================================================================================
 *        AdAffectCurrent                             ��ȡ����ǰ��¼�Ĺ�����¡� 
 *        AdAffectGroup                               �����㵱ǰ Filter �������õļ�¼ȡ��������¡�ʹ�ø�ѡ��ʱ��
 *                                                    ���뽫 Filter ��������Ϊ�Ϸ���Ԥ���峣��֮һ�� 
 *        AdAffectAll                                 Ĭ��ֵ��ȡ�� Recordset ���������м�¼�Ĺ�����£������ɵ�ǰ Filter 
 *                                                    �������������ص��κμ�¼�� 
 *        =========================================================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� CancelBatch ������ȡ��������ģʽ�¼�¼�������й���ĸ��¡������¼��������������ģʽ�����ò��� adAffectCurrent �� 
 *         CancelBatch ����������������� CancelBatch ʱ���ڱ༭��ǰ��¼������¼�¼���� ADO ���ȵ��� CancelUpdate ����ȡ����
 *         ���ѱ�������޸ģ�Ȼ��ȡ����¼���й�������и��ġ��п����� CancelBatch ���ú��ر���������¼�¼ʱ�޷�ȷ����ǰ��¼��Ϊ�ˣ�
 *         �� CancelBatch ���ú󽫵�ǰ��¼λ������Ϊ��¼���е���֪λ�������ǵġ�����ɵ��� MoveFirst ���������������������ݳ�ͻ��
 *         ���¼�ѱ������û�ɾ����������ȡ���������ʧ�ܣ����ṩ�߽��� Errors ���Ϸ��ؾ��棬������ֹ�����ִ�С�ֻ�е���������ļ�¼��
 *         ������ͻʱ�ŷ�������ʱ����ʹ�� Filter ���� (adFilterAffectedRecords) �� Status ���Կ��ԶԳ�ͻ��¼���ж�λ��
 */
HRESULT MtADORecordset::cancel_bantch(const ADODB::AffectEnum affect_records/*=ADODB::adAffectAll*/){
	clear_last_error();
	try{
		return(_recordset->CancelBatch(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel_update
 * breif: ȡ���ڵ��� Update ����ǰ�Ե�ǰ��¼���¼�¼�������κθ��ġ�
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� CancelUpdate ������ȡ���Ե�ǰ��¼�������κθ��Ļ��������ӵļ�¼���ڵ��� Update ������
 *         �޷������Ե�ǰ��¼���¼�¼�����ĸ��ģ����Ǹ����ǿ����� RollbackTrans �����ؾ�������һ���֣�����
 *         �ǿ����� CancelBatch ����ȡ���������µ�һ���֡�����ڵ��� CancelUpdate ����ʱ����¼�¼������� 
 *         AddNew ֮ǰ�ĵ�ǰ��¼���ٴγ�Ϊ��ǰ��¼�������δ���ĵ�ǰ��¼������¼�¼������ CancelUpdate ����
 *         ����������
 */
HRESULT MtADORecordset::cancel_update(){
	clear_last_error();
	try{
		return(_recordset->CancelUpdate());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: clone
 * brief: ���������� Recordset ������ͬ�ĸ��� Recordset ���󡣿�ѡ��ָ���ø���Ϊֻ����
 * param: type - ��ѡ��LockTypeEnum ֵ��ָ��ԭʼ Recordset ���������ͻ�ֻ�� Recordset��
 *               ����                           ˵�� 
 *               ======================================================================
 *               AdLockUnspecified              Ĭ��ֵ��ʹ����ԭʼ������ͬ���������ʹ��������� 
 *               AdLockReadOnly                 ��������Ϊֻ���� 
 *               ======================================================================
 * return: ���� Recordset �������á�
 * remark: ʹ�� Clone �����ɴ������ Recordset ���󸱱��������ϣ���ڸ����ļ�¼���б��������ǰ��¼ʮ�����á�
 *         ʹ�� Clone ������ʹ�����ʼ������ͬ�Ķ��崴���ʹ��� Recordset ����Ҫ��Ч�öࡣ�´��������ĵ�ǰ
 *         ��¼������Ϊ�׼�¼�������α�������Σ���ĳ�� Recordset �����������޸��������и����ж��ǿɼ��ġ�����
 *         һ����ԭʼ Recordset ��ִ���� Requery��������������ԭʼ Recordset ͬ�����ر�ԭʼ Recordset ʱ
 *         �����ر����ĸ��������ر�ĳ������Ҳ�����ر�ԭʼ Recordset ���κ������������û�ֻ������֧����ǩ�� 
 *         Recordset ������ǩֵ�ǿɽ����ģ�Ҳ����˵������һ�� Recordset �������ǩ���ÿ��������κθ����е�
 *         ��ͬ��¼��
 */
ADODB::_RecordsetPtr MtADORecordset::clone(const ADODB::LockTypeEnum type){
	clear_last_error();
	try{
		return(_recordset->Clone(type));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: close
 * brief: �رմ򿪵Ķ����κ���ض���
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Close �����ɹر� Connection ����� Recordset �����Ա��ͷ����й�����ϵͳ��Դ��
 *         �رն��󲢷ǽ������ڴ���ɾ�������Ը��������������ò����ڴ˺��ٴδ򿪡�Ҫ��������ڴ���
 *         ��ȫɾ�����ɽ������������Ϊ Nothing��
 *         Connection
 *         ʹ�� Close �����ر� Connection �����ͬʱ��Ҳ���ر���������������κλ Recordset ����
 *         �����ڹرյ� Connection ����������� Command ���󽫱��־ñ������������� Connection ���������
 *         ������ ActiveConnection ���Խ�������Ϊ Nothing��ͬʱ��Command ����� Parameters ���Ͻ����
 *         �κ��ṩ�߶���Ĳ��������������� Open �������½�������ͬ����Դ����������Դ�����ӣ��ر� Connection 
 *         ����󣬵����κ���Ҫ���������Դ���ӵķ��������������󡣵��������д򿪵� Recordset ����ʱ���ر� 
 *         Connection ���󽫻ؾ����� Recordset ����Ĺ�����ġ���������й�������ʽ�ر� Connection ����
 *         ���� Close ���������������������������й����� Connection ���󳬳���Χ����ô ADO ���Զ��ؾ�����
 *         Recordset
 *         ʹ�� Close �����ر� Recordset �����ͬʱ�����ͷŹ��������ݺͿ����Ѿ�ͨ�����ض� Recordset ��������ݽ���
 *         �Ķ������ʡ����ɵ��� Open �������´򿪾�����ͬ���Ի����޸����Ե� Recordset���� Recordset ����رպ󣬵�
 *         ���κ���Ҫ��α�ķ����������������������������ģʽ�½��б༭������ Close ��������������Ӧ���ȵ��� 
 *         Update �� CancelUpdate ������������������ڼ�ر� Recordset ���������ϴ� UpdateBatch ��������������
 *         �޸Ľ�ȫ����ʧ�����ʹ�� Clone ���������Ѵ򿪵� Recordset ����ĸ������ر�ԭʼ Recordset ���丱������Ӱ��
 *         �κ�����������
 */
HRESULT MtADORecordset::close(){
	clear_last_error();
	try{
		return(_recordset->Close());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: compare_bookmarks
 * brief: �Ƚ�������ǩ�������������ֵ��˵����
 * param: bookmark_left - ��ǩ1��
 *        bookmark_right - ��ǩ2��
 * return: ���ص�ֵָʾ��ǩ�������������¼�������λ�á��ɷ�������ֵ��
 *         ����                                ˵�� 
 *         ======================================================================
 *         AdCompareLessThan                   ��һ����ǩ�ڵڶ���֮ǰ�� 
 *         AdCompareEqual                      ��ǩ��ͬ�� 
 *         AdCompareGreaterThan                ��һ����ǩ�ڵڶ���֮�� 
 *         AdCompareNotEqual                   ��ǩ����ͬ����δ���� 
 *         AdCompareNotComparable              �޷��Ƚ���ǩ�� 
 *         ======================================================================
 * remark: ��ǩ����Ӧ������ͬ�� Recordset ���󣬻����� Recordset ������  clone���޷��ɿ��ر�
 *         �����Բ�ͬ Recordset �������ǩ����ʹ���ǵĴ�����Դ��������ʹ�õ�������ͬ��ͬʱ��������
 *         �����ṩ�߲�֧�ֱȽϵ� Recordset ����Ҳ�޷��Ƚ���ǩ����ǩΨһ��ʶ Recordset �����е��С�
 *         ʹ�õ�ǰ�е� Bookmark ���Կ��Ի��������ǩ����Ч����ʽ�������ǩ����������
 */
ADODB::CompareEnum MtADORecordset::compare_bookmarks(
	const _variant_t &bookmark_left,const _variant_t &bookmark_right){
	clear_last_error();
	try{
		return(_recordset->CompareBookmarks(bookmark_left,bookmark_right));
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adCompareNotComparable);
	}
}

/**
 * name: deletes
 * brief: ɾ����ǰ��¼���¼�顣
 * param: affect_records - AffectEnum ֵ��ȷ�� Delete ������Ӱ��ļ�¼��Ŀ����ֵ���������г���֮һ��
 *                         ����                               ˵��
 *                         ===============================================================================
 *                         AdAffectCurrent                    Ĭ�ϡ���ɾ����ǰ��¼�� 
 *                         AdAffectGroup                      ɾ�����㵱ǰ Filter �������õļ�¼��Ҫʹ�ø�ѡ�
 *                                                            ���뽫 Filter ��������Ϊ��Ч��Ԥ���峣��֮һ�� 
 *                         adAffectAll                        ɾ�����м�¼�� 
 *                         adAffectAllChapters                ɾ�������Ӽ���¼�� 
 *                         ===============================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Delete �����ɽ� Recordset �����еĵ�ǰ��¼��һ���¼���Ϊɾ������� Recordset ��������ɾ����¼����������
 *         ʹ����������ģʽ�������ݿ��н�������ɾ���������¼�����Ϊ�ӻ���ɾ����ʵ�ʵ�ɾ�����ڵ��� UpdateBatch ����ʱ���С���
 *         ʹ�� Filter ���Կɲ鿴��ɾ���ļ�¼��������ɾ���ļ�¼�м����ֶ�ֵ����������ɾ����ǰ��¼�����ƶ���������¼֮ǰ��ɾ��
 *         �ļ�¼������Ϊ��ǰ��¼��һ���뿪��ɾ����¼�����޷��ٴη������������������Ƕ��ɾ�������� RollbackTrans �����ָ���ɾ���ļ�¼��
 *         �������������ģʽ������� CancelBatch ����ȡ��һ����һ�����ɾ�����������������ݳ�ͻ������ɾ����¼ʧ�ܣ����¼�ѱ������û�
 *         ɾ���������ṩ���� Errors ���Ϸ��ؾ��浫����ֹ����ִ�У�ֻ���������������ļ�¼�Ϸ�����ͻʱ�Ż��������ʱ����
 *         ��� Unique Table ��̬���Ա����ã����� Recordset �ǶԶ����ִ�� JOIN �����Ľ������ô��Delete ��������ɾ�� Unique Table 
 *         �����������ı��е��С�
 */
HRESULT MtADORecordset::deletes(const ADODB::AffectEnum affect_records/*=ADODB::adAffectCurrent*/){
	clear_last_error();
	try{
		return(_recordset->Delete(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: find
 * brief: ���� Recordset ������ָ����׼�ļ�¼����������׼�����¼��λ���������ҵ��ļ�¼�ϣ�����λ�ý������ڼ�¼����ĩβ��
 * param: criteria - �ַ���������ָ�������������������Ƚϲ�������ֵ����䡣
 *        skip_rows - ��ѡ��������ֵ����Ĭ��ֵΪ�㣬��ָ����ǰ�л� start ��ǩ��λ���Կ�ʼ������
 *        search_direction - ��ѡ�� SearchDirectionEnum ֵ��ָ������Ӧ�ӵ�ǰ�л�����һ����Ч�п�ʼ����ֵ��Ϊ adSearchForward �� 
 *                           adSearchBackward���������ڼ�¼���Ŀ�ʼ����ĩβ������ searchDirection ֵ������
 *        start - ��ѡ����������ǩ�����������Ŀ�ʼλ�á�
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: criteria �еġ��Ƚϲ������������ǡ�>�������ڣ�����<����С�ڣ�����=�������ڣ�����>=�������ڻ���ڣ�����<=����С�ڻ���ڣ�����<>���������ڣ���
 *         ��like����ģʽƥ�䣩�� criteria �е�ֵ�������ַ������������������ڡ��ַ���ֵ�Ե����ŷֽ磨�硰state = 'WA'����������ֵ�ԡ�#��������
 *         �Ǻţ��ֽ磨�硰start_date > #7/22/97#�������硰�Ƚϲ�������Ϊ��like�������ַ�����ֵ�����԰�����*����ĳ�ַ��ɳ���һ�λ��Σ����ߡ�_����
 *         ĳ�ַ�ֻ����һ�Σ������硰state like M_*���� Maine �� Massachusetts ƥ�䡣����
 */
HRESULT MtADORecordset::find(const CString &criteria,const long skip_rows,
	const ADODB::SearchDirectionEnum search_direction,const _variant_t &start/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->Find(
			static_cast<LPCTSTR>(criteria),skip_rows,search_direction,start));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: get_rows
 * brief: �� Recordset ����Ķ����¼�ָ��������С�
 * param: rows - ��ѡ�������ͱ��ʽ��ָ��Ҫ������¼����Ĭ��ֵΪ adGetRowsRest (-1)��
 *        start - ��ѡ���ַ��������ͣ�����õ��� GetRows ������ʼ���ļ�¼����ǩ��Ҳ��ʹ������ BookmarkEnum ֵ��
 *                ����                                  ˵�� 
 *                ====================================================================================
 *                AdBookmarkCurrent                     �ӵ�ǰ��¼��ʼ�� 
 *                AdBookmarkFirst                       ���׼�¼��ʼ�� 
 *                AdBookmarkLast                        ��β��¼��ʼ�� 
 *                ====================================================================================
 *        fields - ��ѡ�������ͣ��������ֶ�����˳��λ�á��ֶ��������˳��λ�úš�ADO ��������Щ�ֶ��е����ݡ�
 * return: ���ض�ά���顣
 * remark: ʹ�� GetRows �����ɽ���¼�� Recordset ���Ƶ���ά�����С���һ���±��ʶ�ֶΣ��ڶ������ʶ��¼�š��� GetRows 
 *         ������������ʱ����������Զ���������ȷ��С�������ָ�� Rows ������ֵ��GetRows �������Զ����� Recordset ����
 *         �е����м�¼���������ļ�¼�ȿ��ü�¼�࣬�� GetRows �����ؿ��ü�¼������� Recordset ����֧����ǩ�������ͨ
 *         �����͸ü�¼�� Bookmark ����ֵ����ָ�� GetRows ���������ĸ���¼��ʼ�������ݡ���Ҫ���� GetRows ���÷��ص��ֶΣ�
 *         ������� Fields �����д��͵����ֶ���/��Ż����ֶ���/������顣�ڵ��� GetRows ����һ��δ��ȡ�ļ�¼��Ϊ��ǰ��¼��
 *         �������û�и���ļ�¼���� EOF ��������Ϊ True��
 */
_variant_t MtADORecordset::get_rows(
	const long rows,const _variant_t start/*=vtMissing*/,const _variant_t &fields/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->GetRows(rows,start,fields));
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: move
 * brief: �ƶ� Recordset �����е�ǰ��¼��λ�á�
 * param: records - �����ų����ͱ��ʽ��ָ����ǰ��¼λ���ƶ��ļ�¼����
 *        start - ��ѡ���ַ���������ͣ����ڼ�����ǩ��Ҳ��Ϊ���� BookmarkEnum ֵ֮һ��
 *                ����                              ˵�� 
 *                ===================================================================
 *                AdBookmarkCurrent                 Ĭ�ϡ��ӵ�ǰ��¼��ʼ�� 
 *                AdBookmarkFirst                   ���׼�¼��ʼ�� 
 *                AdBookmarkLast                    ��β��¼��ʼ�� 
 *                ===================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ���� Recordset ����֧�� Move ��������� NumRecords ���������㣬��ǰ��¼λ�ý���ǰ�ƶ������¼����ĩβ����
 *         ��� NumRecords С���㣬��ǰ��¼λ������ƶ������¼���Ŀ�ʼ������� Move ���ý���ǰ��¼λ���ƶ����׼�¼֮ǰ��
 *         �� ADO ����ǰ��¼�����ڼ�¼����BOF Ϊ True�����׼�¼֮ǰ���� BOF �����Ѿ�Ϊ True ʱ��ͼ����ƶ�������������
 *         �� Move ���ý���ǰ��¼λ���ƶ���β��¼֮���� ADO ����ǰ��¼�����ڼ�¼����EOF Ϊ True����β��¼֮���� EOF 
 *         �����Ѿ�Ϊ True ʱ��ͼ��ǰ�ƶ����������󡣴ӿյ� Recordset ������� Move ��������������������� Start ������
 *         ���ƶ�����ڸ���ǩ�ļ�¼���ٶ� Recordset ����֧����ǩ�������û��ָ�������ƶ�����ڵ�ǰ��¼�����ʹ�� CacheSize 
 *         �����ڱ��ػ��������ṩ�ߵļ�¼�����ڴ��ͽ���ǰ��¼λ���ƶ�����ǰ����ļ�¼��֮��� NumRecords ����ʱ�� ADO ������
 *         ����Ŀ���¼��ʼ�����µļ�¼�顣CacheSize ���Ծ����¼�����¼��Ĵ�С����Ŀ���¼�Ǽ������ĵ�һ����¼����� Recordset 
 *         �����ǽ���ǰ�ģ����û���Ȼ���Դ���С����� NumRecords ������ֻҪĿ�����ѻ����¼�ĵ�ǰ�����У������ Move ���ý���ǰ
 *         ��¼λ���ƶ�����һ���ѻ����¼��ǰһ����¼��������������˿�ʹ�ü�¼���棬����֧�ֽ���ǰ�������ṩ����֧����ȫ����������
 *         ����ļ�¼�����ص��ڴ棬���Ӧ���ⲻ��Ҫ�ػ�������¼����ʹ����ǰ Recordset ����֧�����ַ�ʽ������ƶ������κν���ǰ�� 
 *         Recordset �����ϵ��� MovePrevious �����Խ���������
 */
HRESULT MtADORecordset::move(const long records,const ADODB::BookmarkEnum start/*=ADODB::adBookmarkCurrent*/){
	clear_last_error();
	try{
		return(_recordset->Move(records,start));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_first
 * brief: ��ָ�� Recordset �������ƶ�����һ����¼��ʹ�ü�¼��Ϊ��ǰ��¼��
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� MoveFirst ��������ǰ��¼λ���ƶ��� Recordset �еĵ�һ����¼��
 *         ʹ�� MoveLast ��������ǰ��¼λ���ƶ��� Recordset �е����һ����¼��Recordset �������֧����ǩ��������ƶ���
 *         ������ø÷�������������
 *         ʹ�� MoveNext ��������ǰ��¼��ǰ�ƶ�һ����¼���� Recordset �ĵײ�����������һ����¼�ǵ�ǰ��¼���ҵ��� MoveNext ������
 *         �� ADO ����ǰ��¼���õ� Recordset ��EOF Ϊ True����β��¼֮�󡣵� EOF �����Ѿ�Ϊ True ʱ��ͼ��ǰ�ƶ�����������
 *         ʹ�� MovePrevious ��������ǰ��¼λ������ƶ�һ����¼�����¼���Ķ�������Recordset �������֧����ǩ������α��ƶ���
 *         ���򷽷����ý�������������׼�¼�ǵ�ǰ��¼���ҵ��� MovePrevious �������� ADO ����ǰ��¼������ Recordset ��BOF Ϊ True����
 *         �׼�¼֮ǰ���� BOF ����Ϊ True ʱ����ƶ�������������� Recordset ����֧����ǩ������α��ƶ����� MovePrevious ����������
 *         ����
 *         �����¼���ǽ���ǰ�ģ������û�ϣ��֧����ǰ���������������ʹ�� CacheSize ���Դ�����¼���棬ͨ�� Move ����֧������α��ƶ���
 *         ���ڻ����¼�Ǽ��ص��ڴ��еģ�����Ӧ���ⲻ��Ҫ�ػ���̫���¼�����Ե��ý���ǰ Recordset ����� MoveFirst ��������������ʹ��
 *         ��������ִ������ Recordset ��������
 */
HRESULT MtADORecordset::move_first(){
	clear_last_error();
	try{
		return(_recordset->MoveFirst());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_last
 * brief: ��ָ�� Recordset �������ƶ������һ����¼��ʹ�ü�¼��Ϊ��ǰ��¼��
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� MoveFirst ��������ǰ��¼λ���ƶ��� Recordset �еĵ�һ����¼��
 *         ʹ�� MoveLast ��������ǰ��¼λ���ƶ��� Recordset �е����һ����¼��Recordset �������֧����ǩ��������ƶ���
 *         ������ø÷�������������
 *         ʹ�� MoveNext ��������ǰ��¼��ǰ�ƶ�һ����¼���� Recordset �ĵײ�����������һ����¼�ǵ�ǰ��¼���ҵ��� MoveNext ������
 *         �� ADO ����ǰ��¼���õ� Recordset ��EOF Ϊ True����β��¼֮�󡣵� EOF �����Ѿ�Ϊ True ʱ��ͼ��ǰ�ƶ�����������
 *         ʹ�� MovePrevious ��������ǰ��¼λ������ƶ�һ����¼�����¼���Ķ�������Recordset �������֧����ǩ������α��ƶ���
 *         ���򷽷����ý�������������׼�¼�ǵ�ǰ��¼���ҵ��� MovePrevious �������� ADO ����ǰ��¼������ Recordset ��BOF Ϊ True����
 *         �׼�¼֮ǰ���� BOF ����Ϊ True ʱ����ƶ�������������� Recordset ����֧����ǩ������α��ƶ����� MovePrevious ����������
 *         ����
 *         �����¼���ǽ���ǰ�ģ������û�ϣ��֧����ǰ���������������ʹ�� CacheSize ���Դ�����¼���棬ͨ�� Move ����֧������α��ƶ���
 *         ���ڻ����¼�Ǽ��ص��ڴ��еģ�����Ӧ���ⲻ��Ҫ�ػ���̫���¼�����Ե��ý���ǰ Recordset ����� MoveFirst ��������������ʹ��
 *         ��������ִ������ Recordset ��������
 */
HRESULT MtADORecordset::move_last(){
	clear_last_error();
	try{
		return(_recordset->MoveLast());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_next
 * brief: ��ָ�� Recordset �������ƶ�����һ����¼��ʹ�ü�¼��Ϊ��ǰ��¼��
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� MoveFirst ��������ǰ��¼λ���ƶ��� Recordset �еĵ�һ����¼��
 *         ʹ�� MoveLast ��������ǰ��¼λ���ƶ��� Recordset �е����һ����¼��Recordset �������֧����ǩ��������ƶ���
 *         ������ø÷�������������
 *         ʹ�� MoveNext ��������ǰ��¼��ǰ�ƶ�һ����¼���� Recordset �ĵײ�����������һ����¼�ǵ�ǰ��¼���ҵ��� MoveNext ������
 *         �� ADO ����ǰ��¼���õ� Recordset ��EOF Ϊ True����β��¼֮�󡣵� EOF �����Ѿ�Ϊ True ʱ��ͼ��ǰ�ƶ�����������
 *         ʹ�� MovePrevious ��������ǰ��¼λ������ƶ�һ����¼�����¼���Ķ�������Recordset �������֧����ǩ������α��ƶ���
 *         ���򷽷����ý�������������׼�¼�ǵ�ǰ��¼���ҵ��� MovePrevious �������� ADO ����ǰ��¼������ Recordset ��BOF Ϊ True����
 *         �׼�¼֮ǰ���� BOF ����Ϊ True ʱ����ƶ�������������� Recordset ����֧����ǩ������α��ƶ����� MovePrevious ����������
 *         ����
 *         �����¼���ǽ���ǰ�ģ������û�ϣ��֧����ǰ���������������ʹ�� CacheSize ���Դ�����¼���棬ͨ�� Move ����֧������α��ƶ���
 *         ���ڻ����¼�Ǽ��ص��ڴ��еģ�����Ӧ���ⲻ��Ҫ�ػ���̫���¼�����Ե��ý���ǰ Recordset ����� MoveFirst ��������������ʹ��
 *         ��������ִ������ Recordset ��������
 */
HRESULT MtADORecordset::move_next(){
	clear_last_error();
	try{
		return(_recordset->MoveNext());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_previous
 * brief: ��ָ�� Recordset �������ƶ���ǰһ����¼��ʹ�ü�¼��Ϊ��ǰ��¼��
 * param: --
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� MoveFirst ��������ǰ��¼λ���ƶ��� Recordset �еĵ�һ����¼��
 *         ʹ�� MoveLast ��������ǰ��¼λ���ƶ��� Recordset �е����һ����¼��Recordset �������֧����ǩ��������ƶ���
 *         ������ø÷�������������
 *         ʹ�� MoveNext ��������ǰ��¼��ǰ�ƶ�һ����¼���� Recordset �ĵײ�����������һ����¼�ǵ�ǰ��¼���ҵ��� MoveNext ������
 *         �� ADO ����ǰ��¼���õ� Recordset ��EOF Ϊ True����β��¼֮�󡣵� EOF �����Ѿ�Ϊ True ʱ��ͼ��ǰ�ƶ�����������
 *         ʹ�� MovePrevious ��������ǰ��¼λ������ƶ�һ����¼�����¼���Ķ�������Recordset �������֧����ǩ������α��ƶ���
 *         ���򷽷����ý�������������׼�¼�ǵ�ǰ��¼���ҵ��� MovePrevious �������� ADO ����ǰ��¼������ Recordset ��BOF Ϊ True����
 *         �׼�¼֮ǰ���� BOF ����Ϊ True ʱ����ƶ�������������� Recordset ����֧����ǩ������α��ƶ����� MovePrevious ����������
 *         ����
 *         �����¼���ǽ���ǰ�ģ������û�ϣ��֧����ǰ���������������ʹ�� CacheSize ���Դ�����¼���棬ͨ�� Move ����֧������α��ƶ���
 *         ���ڻ����¼�Ǽ��ص��ڴ��еģ�����Ӧ���ⲻ��Ҫ�ػ���̫���¼�����Ե��ý���ǰ Recordset ����� MoveFirst ��������������ʹ��
 *         ��������ִ������ Recordset ��������
 */
HRESULT MtADORecordset::move_previous(){
	clear_last_error();
	try{
		return(_recordset->MovePrevious());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: next_record
 * brief: �����ǰ Recordset ����ͨ����ǰִ���������з�����һ����¼����
 * param: affect_records - ��ѡ�������ͱ������ṩ�����䷵�ص�ǰ������Ӱ��ļ�¼��Ŀ��
 *                         ע�⣺ �ò����������ܲ���Ӱ��ļ�¼����Ŀ�����������������
 *                         Recordset ��ѡ����䷵�ؼ�¼�ļ�����
 * return: ���� Recordset �������﷨ģ���У�recordset1 �� recordset2 ��������ͬ�� Recordset ���󣬻��߿���ʹ�ò�ͬ�Ķ���
 * remark: ʹ�� NextRecordset �������ظ��������������һ������Ľ���������Ƿ��ض��������Ѵ洢���̽�������ʹ�� Command �� 
 *         Execute �������� Recordset �� Open �����򿪻��ڸ���������䣨���硰SELECT * FROM table1;SELECT * FROM table2������ 
 *         Recordset ������ ADO ��ִ�е�һ�������������ص�����¼������Ҫ��������к�������Ľ��������� NextRecordset ������
 *         ֻҪ�������Ľ�������Ұ����������� Recordset δ������̱߽���ȣ��� NextRecordset �������������� Recordset ����
 *         ����з�������û�з��ؼ�¼���򷵻ص� Recordset ����Ϊ�գ���ȷ�� BOF �� EOF ��Ϊ True ������¿���֤�������������ǰ���
 *         ��������ɹ�ִ�У��򷵻ص� Recordset ���󽫹رգ�ͨ������ Recordset �� State ���Կ��Բ���������������û�������Ľ������
 *         ��¼����������Ϊ Nothing��
 *        ��Զ�����ݷ��� NextRecordset �����Կͻ��˵� Recordset ���󲻿��á��������������ģʽ�½��б༭������ NextRecordset ����
 *         ����������Ӧ���ȵ��� Update �� CancelUpdate �����������Ҫͨ����д Parameters ���ϻ���ͨ��ʹ��ԭ�е� Open �� Execute 
 *         ���ô�������Ϊ��������еĶ������Ͳ�����������ڼ��ϻ������еĴ�����������������������и�������Ĵ�����ͬ���ڶ�ȡ�������ֵ
 *         ֮ǰ�����ȡ���н�����ڵ��� NextRecordset ����ʱ��ADO ��ִ������е���һ���������ڵ���ִ�������������֮ǰ��ʽ�ر� Recordset
 *         ������ ADO ��ִ����������
 */
ADODB::_RecordsetPtr MtADORecordset::next_record(VARIANT *affect_records){
	clear_last_error();
	try{
		return(_recordset->NextRecordset(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: open
 * brief: ���αꡣ
 * param: source - ��ѡ�������ͣ����� Command ����ı�������SQL ��䡢�������洢���̵��û�־� Recordset �ļ�����
 *        active_connection - ��ѡ�������ͣ�������Ч Connection ��������������ַ��������� ConnectionString ������
 *        cursor_type - ��ѡ��CursorTypeEnum ֵ��ȷ���ṩ�ߴ� Recordset ʱӦ��ʹ�õ��α����͡���Ϊ���г���֮һ��
 *                      ���� CursorType ���Կɻ����Щ���õĶ��壩��
 *                      ����                                          ˵�� 
 *                      ====================================================================================
 *                      AdOpenForwardOnly                            ��Ĭ��ֵ���򿪽���ǰ�����αꡣ 
 *                      AdOpenKeyset                                  �򿪼��������αꡣ 
 *                      AdOpenDynamic                                 �򿪶�̬�����αꡣ 
 *                      AdOpenStatic                                  �򿪾�̬�����αꡣ 
 *                      ====================================================================================
 *        lock_type - ��ѡ��ȷ���ṩ�ߴ� Recordset ʱӦ��ʹ�õ����������������͵� LockTypeEnum ֵ����Ϊ���г���֮һ��
 *                    �μ� LockType ���Կɻ����ϸ��Ϣ����
 *                    ����                                            ˵�� 
 *                    =================================================================================================
 *                    AdLockReadOnly                                ��Ĭ��ֵ��ֻ�� �� ���ܸı����ݡ� 
 *                    AdLockPessimistic                             ����ʽ����������� �� �ṩ�����ȷ���ɹ��༭��¼����Ĺ�����
 *                                                                  ͨ��ͨ���ڱ༭ʱ������������Դ�ļ�¼�� 
 *                    AdLockOptimistic                              ����ʽ����������� �� �ṩ��ʹ�ÿ���ʽ������ֻ�ڵ���Update 
 *                                                                  ����ʱ��������¼�� 
 *                    AdLockBatchOptimistic                         ����ʽ�����¡�����������ģʽ������������ģʽ��ԣ��� 
 *                    ==================================================================================================
 *        options - ��ѡ��������ֵ������ָʾ�ṩ����μ��� Source ���������������Ĳ��� Command ���󣩣������ǰ���� Recordset ���ļ�
 *                  �лָ� Recordset����Ϊ���г���֮һ���μ� CommandType ���Կɻ�ø��б���ǰ�����������ϸ˵������
 *                  ����                                         ˵��
 *                  =======================================================================================================
 *                  adCmdText                                   ָʾ�ṩ��Ӧ�ý� Source ��Ϊ������ı����������㡣 
 *                  adCmdTable                                  ָʾ ADO ���� SQL ��ѯ�Ա���� Source �������ı��з��������С� 
 *                  adCmdTableDirect                            ָʾ�ṩ�߸��Ĵ��� Source �������ı��з��������С� 
 *                  adCmdStoredProc                             ָʾ�ṩ��Ӧ�ý� Source ��Ϊ�洢���̡� 
 *                  adCmdUnknown                                ָʾ Source �����е���������Ϊδ֪�� 
 *                  adCmdFile                                   ָʾӦ���� Source ���������ļ��лָ�����������ģ�Recordset�� 
 *                  adAsyncExecute                              ָʾӦ�첽ִ�� Source�� 
 *                  adAsyncFetch                                ָʾ����ȡ Initial Fetch Size ������ָ���ĳ�ʼ������Ӧ���첽
 *                                                              ��ȡ����ʣ����С�������������δ��ȡ����Ҫ���߳̽�������ֱ��������
 *                                                              ���á� 
 *                  adAsyncFetchNonBlocking                     ָʾ��Ҫ�߳�����ȡ�ڼ��δ��������������������δ��ȡ����ǰ���Զ���
 *                                                              ���ļ�ĩβ��
 *                  ========================================================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Recordset ����� Open �����ɴ򿪴����������ѯ���������ǰ����� Recordset �м�¼���αꡣʹ�ÿ�ѡ�� Source ����ָ��ʹ��
 *         ��������֮һ������Դ��Command ���������SQL ��䡢�洢���̡��������������ļ�·������
 *         ��� Source ���ļ�·������������������·������c:\dir\file.rst���������·������..\file.rst������ URL����http://files/file.rst������
 *         ActiveConnection ������Ӧ�� ActiveConnection ���ԣ���ָ�����ĸ������д� Recordset ����������͸ò��������Ӷ��壬�� ADO ʹ
 *         ��ָ���Ĳ����������ӡ������ڴ� Recordset ֮����ĸ����Ե�ֵ�Ա㽫���·��͵������ṩ�ߡ����߿��Խ�����������Ϊ Nothing���� 
 *         Microsoft Visual Basic �У��Ա㽫 Recordset �������ṩ�߶Ͽ�������ֱ�Ӷ�Ӧ�� Recordset �������ԵĲ�����Source��CursorType �� 
 *         LockType�������������ԵĹ�ϵ���£� �� Recordset �����֮ǰ�����Ƕ�/д��������ִ�� Open ����ʱ������Ӧ�Ĳ���������ʹ���������á�
 *         ������Ͳ�����������������Ӧ���������ã������ò���ֵ�����������á��ڴ� Recordset �������Щ���Խ���Ϊֻ���� ע��: ������ Source 
 *         ���Ա�����Ϊ��Ч Command ����� Recordset ���󣬼�ʹ Recordset ����û�д򿪣�ActiveConnection ����Ҳ��ֻ���ġ������ Source 
 *         �����д��� Command ������ͬʱ���� ActiveConnection ��������ô����������Command ����� ActiveConnection ���Ա����Ѿ�����Ϊ
 *         ��Ч�� Connection ������������ַ���������� Source �����д��͵Ĳ��� Command ������ô����ʹ�� Options �����Ż��� Source ����
 *         �ļ��㡣���û�ж��� Options �����ܽ��ή�ͣ�ԭ���� ADO ��������ṩ����ȷ�������Ƿ�Ϊ SQL ��䡢�洢���̻�����������ȷ�����õ� 
 *         Source ���ͣ���������� Options ������ָʾ ADO ֱ��������صĴ��롣��� Options ������ƥ�� Source ���ͣ����������������������
 *         Recordset ���������ӣ�Options ������Ĭ��ֵ��Ϊ adCmdFile�����ǳ־� Recordset ����ĵ���������������Դû�з��ؼ�¼����ô�ṩ�߽�
 *         BOF �� EOF ����ͬʱ����Ϊ True�����Ҳ����嵱ǰ��¼λ�á�����α�����������Ȼ���Խ���������ӵ��ÿ� Recordset �����ڴ򿪵� 
 *         Recordset ��������ɲ���ʱ����ʹ�� Close �����ͷ��κ���ص�ϵͳ��Դ���رն��󲢷ǽ������ڴ���ɾ�������Ը��������������ò������Ժ�ʹ
 *         �� Open �����ٴν���򿪡�Ҫ��������ڴ�����ȫɾ�����ɽ������������Ϊ Nothing�������� ActiveConnection ����֮ǰ���ò����������� 
 *         Open����ͨ�����ֶ�׷�ӵ� Recordset Fields ���ϴ��� Recordset ��ʵ��������Ѿ��� CursorLocation ��������Ϊ adUseClient���Ϳ���
 *         ��������;��֮һ�첽�����С�����ʹ�õķ����ǽ� Options ����Ϊ adAsyncFetch�����ߣ�����ʹ���� Properties �����еġ��첽�м��ϴ���
 *         ��̬���ԣ������δ�� Options ��������Ϊ adAsyncFetch������ܶ�ʧ��صı������¼���
 *         ע��: �� MSRemote �ṩ���еı�����ȡ����ͨ�� Open ������ Options �����õ�֧�֡�
 */
HRESULT MtADORecordset::open(const _variant_t &source,const _variant_t &active_connection,
	const ADODB::CursorTypeEnum cursor_type,ADODB::LockTypeEnum lock_type,const long options){
	clear_last_error();
	try{
		return(_recordset->Open(source,active_connection,cursor_type,lock_type,options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: requery
 * brief: ͨ������ִ�ж��������ڵĲ�ѯ������ Recordset �����е����ݡ�
 * param: options - ��ѡ��ָʾӰ��ò���ѡ���λ���Ρ�����ò�������Ϊ adAsyncExecute��
 *                  ��ò������첽ִ�в���������ʱ���� RecordsetChangeComplete �¼���
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ͨ�����·���ԭʼ����ٴμ������ݣ���ʹ�� Requery ����ˢ����������Դ�� Recordset �����ȫ�����ݡ�
 *         ���ø÷���������̵��� Close �� Open ������������ڱ༭��ǰ��¼��������¼�¼������������ Recordset 
 *         ������ڼ䣬�����α����ʣ�CursorType��LockType��MaxRecords �ȣ�������Ϊֻ������� Requery ����ֻ��
 *         ˢ�µ�ǰ�αꡣҪ����ĳ���α����Բ��鿴���������ʹ�� Close ����ʹ�����ٴγ�Ϊ��/д��Ȼ����Ը����������ò�
 *         �ҵ��� Open �������´��αꡣ
 */
HRESULT MtADORecordset::requery(const long options){
	clear_last_error();
	try{
		return(_recordset->Requery(options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: resync
 * brief: �ӻ������ݿ�ˢ�µ�ǰ Recordset �����е����ݡ�
 * param: affect_records - ��ѡ��AffectEnum ֵ������ Resync ������Ӱ��ļ�¼��Ŀ������Ϊ���г���֮һ��
 *                         ����                                        ˵�� 
 *                         ==================================================================================
 *                         AdAffectCurrent                             ֻˢ�µ�ǰ��¼�� 
 *                         AdAffectGroup                               ˢ�����㵱ǰ Filter �������õļ�¼��
 *                                                                     ֻ�н� Filter ��������Ϊ��ЧԤ���峣
 *                                                                     ��֮һ����ʹ�ø�ѡ� 
 *                         AdAffectAll                                 Ĭ��ֵ��ˢ�� Recordset �����е����м�¼��
 *                                                                     �������ڵ�ǰ Filter �������ö����صļ�¼�� 
 *                         adAffectAllChapters                         ˢ�������Ӽ���¼�� 
 *                         ==================================================================================
 *        resync_values - ��ѡ��ResyncEnum ֵ��ָ���Ƿ񸲸ǻ���ֵ����Ϊ���г���֮һ��
 *                        ����                                          ˵�� 
 *                        ====================================================================================
 *                        AdResyncAllValues                            Ĭ��ֵ���������ݣ�ȡ������ĸ��¡� 
 *                        AdResyncUnderlyingValues                     ���������ݣ���ȡ������ĸ��¡� 
 *                        ====================================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Resync ��������ǰ Recordset �еļ�¼����������ݿ�����ͬ��������ʹ�þ�̬�����ǰ���α굫ϣ�������������ݿ��еĸĶ�
 *         ʱʮ�����á������ CursorLocation ��������Ϊ adUseClient���� Resync ���Է�ֻ���� Recordset ������á��� Requery ��
 *         ����ͬ��Resync ����������ִ�� Recordset ����Ļ�����������������ݿ��е��¼�¼�����ɼ��������������������ݳ�ͻ������
 *         ���û��ѽ���¼ɾ������ʹ����ͬ���ĳ���ʧ�ܣ����ṩ�߽����淵�ص� Errors ���ϲ��Ҳ�������ʱ����ʹ�� Filter ���� (
 *         adFilterConflictingRecords) �� Status ���Կ����ҵ�������ͻ�ļ�¼��
 *        ��Զ�����ݷ���Resync �����ڿͻ��� Recordset ����Ч��
 *         ��������� Unique Table �� Resync Command ��̬���ԣ����� Recordset �ǶԶ����ִ�� JOIN �����Ľ������ô��Resync ����
 *         ������ Unique Table �����������ı�ִ���� Resync Command �������������Ĳ�����
 */
HRESULT MtADORecordset::resync(const ADODB::AffectEnum affect_records,const ADODB::ResyncEnum resync_values){
	clear_last_error();
	try{
		return(_recordset->Resync(affect_records,resync_values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: save
 * brief: �� Recordset ���棨�־ã����ļ��С�
 * param: file_name - ��ѡ���ļ�������·���������ڱ��� Recordset��
 *        persist_format - ��ѡ��PersistFormatEnum ֵ��ָ������ Recordset ��ʹ�õĸ�ʽ�����������µ�ĳ��������
 *                         ����                                         ˵��
 *                         ===========================================================================================
 *                         adPersistADTG                              ��Ĭ�ϣ�ʹ��ר�õġ�Advanced Data Tablegram����ʽ���档 
 *                         adPersistXML                                ʹ�� XML ��ʽ���档 
 *                         ===========================================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ֻ�ܶԴ򿪵� Recordset ���� Save ���������ʹ�� Open �������� FileName �ָ� Recordset��
 *         ��� Filter ����Ӱ�� Recordset����ֻ���澭��ɸѡ���С���� Recordset �Ƿּ��ṹ�ģ���ô�����浱ǰ�� Recordset ��
 *         ������ Recordset������������һ�� Recordset���ڵ�һ�α��� Recordset ʱָ�� FileName����������� Save ʱ��Ӧ����
 *         FileName�����򽫲�������ʱ����������ʹ���µ� FileName ���� Save����ô Recordset �����浽�µ��ļ��У������ļ���
 *         ԭʼ�ļ����Ǵ򿪵ġ�Save ���ر� Recordset �� FileName���Ӷ����Լ���ʹ�� Recordset ���������µĸ��ġ��� Recordset 
 *         �ر�֮ǰ FileName �����ִ򿪣������ʱ������Ӧ�ó�����Զ�ȡ������д�� FileName�����ڰ�ȫ��ԭ�򣬶��� Microsoft Internet
 *         Explorer ִ�еĽű���Save ����������ʹ�õ͵ĺ��Զ���İ�ȫ���á��йذ�ȫ�������ϸ���ͣ������ �� 
 *         http://www.microsoft.com/data/techmat.htm �ϵİ�Ƥ����⡰Security Issues in the Microsoft Internet Explorer����
 *         ������ڽ����첽 Recordset ��ȡ��ִ�л���²���ʱ���� Save �������� Save ������ȴ�״̬��ֱ���첽������ɡ�
 *         �� Save ������ɺ󣬵�ǰ��λ�ý���Ϊ Recordset �����С�Ҫ�õ���ѽ����Ӧʹ�� Save �� CursorLocation ��������Ϊ adUseClient��
 *         ��������ṩ�߲�֧�����ڱ��� Recordset ��������蹦�ܣ���ͻ����α꽫�ṩ�ù��ܡ�
 */ 
HRESULT MtADORecordset::save(const CString &file_name,const ADODB::PersistFormatEnum persist_format){
	clear_last_error();
	try{
		return(_recordset->Save(
			static_cast<_bstr_t>(static_cast<LPCTSTR>(file_name)),persist_format));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: supports
 * brief: ȷ��ָ���� Recordset �����Ƿ�֧���ض����͵Ĺ��ܡ�
 * param: options - �����ͱ��ʽ������һ���������� CursorOptionEnum ֵ��
 *                  ����                                    ˵�� 
 *                  =====================================================================================================
 *                  adAddNew                                ��ʹ�� AddNew ��������¼�¼�� 
 *                  adApproxPosition                        �ɶ�ȡ������ AbsolutePosition �� AbsolutePage �����ԡ� 
 *                  adBookmark                              ��ʹ�� Bookmark ���Ի�ö��ض���¼�ķ��ʡ� 
 *                  adDelete                                ����ʹ�� Delete ����ɾ����¼�� 
 *                  AdHoldRecords                           ���Լ��������¼���߸�����һ������λ�ö������ύ���й���ĸ��ġ� 
 *                  AdMovePrevious                          ��ʹ�� MoveFirst �� MovePrevious �������Լ� Move �� GetRows 
 *                                                          ��������ǰ��¼λ������ƶ�������ʹ����ǩ�� 
 *                  AdResync                                ͨ�� Resync ������ʹ���ڻ��������ݿ��пɼ������ݸ����αꡣ 
 *                  AdUpdate                                ��ʹ�� Update �����޸����е����ݡ� 
 *                  AdUpdateBatch                           ����ʹ�������£�UpdateBatch �� CancelBatch �������������鴫����ṩ�ߡ� 
 *                  AdIndex                                 ����ʹ�� Index �������������� 
 *                  AdSeek                                  ����ʹ�� Seek ������λ Recordset �е��С� 
 *                  =======================================================================================================
 * return: ����ָ���� Recordset �����Ƿ�֧���ض����͵Ĺ��ܡ�
 * remark: ʹ�� Supports ����ȷ�� Recordset ������֧�ֵĹ������͡���� Recordset ����֧������Ӧ������ CursorOptions �еĹ��ܣ�
 *         ��ô Supports �������� True�����򷵻� False��
 *         ע��: ���� Supports �����ɶԸ����Ĺ��ܷ��� True���������ܱ�֤�ṩ�߿���ʹ���������л����¾���Ч��Supports ����ֻ�����ṩ��
 *         �Ƿ�֧��ָ���Ĺ��ܣ��ٶ�����ĳЩ�����������磬Supports ��������ָʾ Recordset ����֧�ָ��£���ʹ�α���ڶ����ĺϲ���������
 *         ��ĳЩ����Ȼ�޷����¡�
 */
BOOL MtADORecordset::supports(const ADODB::CursorOptionEnum options){
	clear_last_error();
	try{
		if(-1==_recordset->Supports(options)){
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
 * name: update
 * brief: ����� Recordset ����ĵ�ǰ��¼���������и��ġ�
 * param: fields - ��ѡ�������ͣ����������ƣ�����������飬������Ҫ�޸ĵ��ֶΣ�һ�����������Ƽ����λ�á� 
 *        values - ��ѡ�������ͣ�������ֵ������������飬�����¼�¼���ֶΣ�����������ֵ��
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ʹ�� Update ���������Ե��� AddNew ������������м�¼���κ��ֶ�ֵ�������������и��ġ�Recordset �������֧�ָ��¡�
 *         Ҫ�����ֶ�ֵ�����������ĳ������� Ϊ Field ����� Value ���Ը�ֵ�������� Update �������� Update �����д����ֶ�
 *         ����ֵ��Ϊ�������� Update �����д����ֶ��������ֵ���顣 ��ʹ���ֶκ�ֵ������ʱ�����������б��������������Ԫ�أ�ͬ
 *         ʱ�ֶ����Ĵ������ƥ���ֶ�ֵ�Ĵ����ֶκ�ֵ������������ƥ�佫����������� Recordset ����֧�������£���ô������
 *         ���� UpdateBatch ����֮ǰ��һ��������¼�Ķ���Ķ������ڱ��ء�����ڵ��� UpdateBatch ����ʱ���ڱ༭��ǰ��¼����
 *         ����µļ�¼����ô ADO ���Զ����� Update �����Ա��ڽ������Ĵ��͵��ṩ��֮ǰ�������ĸ��ġ�����ڵ��� Update ����
 *         ֮ǰ�ƶ���������ӻ�༭�ļ�¼����ô ADO ���Զ����� Update �Ա㱣����ġ����ϣ��ȡ���Ե�ǰ��¼�������κθ��Ļ��߷�
 *         ������ӵļ�¼���������� CancelUpdate �������ڵ��� Update ������ǰ��¼��Ϊ��ǰ��¼����������� Unique Table 
 *         ��̬���ԣ����� Recordset �ǶԶ����ִ�� JOIN �����Ľ������ô��Update �������޷����¶������κ���Ҫ�ؼ��֡����⣬
 *         Update ֻ�ܸ����� Unique Table ������ָ���ı��е��ֶΡ�
 */
HRESULT MtADORecordset::update(
	const _variant_t &fields/*=vtMissing*/,const _variant_t &values/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->Update(fields,values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: update_batch
 * brief: �����й����������д����̡�
 * param: affect_records - ��ѡ��AffectEnum ֵ������ UpdateBatch ������Ӱ��ļ�¼��Ŀ������Ϊ���³���֮һ��
 *                         ����                                  ˵�� 
 *                         ============================================================================================
 *                         adAffectCurrent                      ֻд�뵱ǰ��¼�Ĺ�����ġ� 
 *                         adAffectGroup                        д�����㵱ǰ Filter �������õļ�¼�������Ĺ�����ġ�
 *                                                              ���뽫 Filter ��������Ϊĳ����Ч��Ԥ���峣������ʹ�ø�ѡ� 
 *                         adAffectAll                          ��Ĭ��ֵ����д�� Recordset ���������м�¼�Ĺ�����ģ�������
 *                                                              �ڵ�ǰ Filter �������ö����ص��κμ�¼�� 
 *                         adAffectAllChapters                  д�������Ӽ��Ĺ�����ġ� 
 *                         ============================================================================================
 * return: ���غ���ִ���Ƿ�ɹ�������ʹ��SUCCEEDED���FAILED�����жϣ���
 * remark: ��������ģʽ�޸� Recordset ����ʱ��ʹ�� UpdateBatch �����ɽ� Recordset �����е����и��Ĵ��ݵ��������ݿ⡣��� Recordset ����
 *         ֧�������£���ô���Խ�һ��������¼�Ķ��ظ��Ļ����ڱ��أ�Ȼ���ٵ��� UpdateBatch ����������ڵ��� UpdateBatch ����ʱ���ڱ༭��ǰ
 *         ��¼��������µļ�¼����ô�ڽ������´��͵��ṩ��֮ǰ��ADO ���Զ����� Update ��������Ե�ǰ��¼�����й�����ġ�
 *         ע�⣺ ֻ�ܶԼ�����̬�α�ʹ�������¡�
 *         �����������������ݳ�ͻ�����¶����л������¼�Ĵ��͸���ʧ�ܣ��������û��ѽ���¼ɾ��������ô�ṩ�߽��Ѿ��淵�ظ� Errors ���ϣ�������
 *         ����ʱ����ʹ�� Filter ���� (adFilterAffectedRecords) �� Status ���Կ����ҵ�������ͻ�ļ�¼��Ҫȡ�����й���������£���ʹ�� 
 *         CancelBatch ��������������� Unique Table �� Update Resync ��̬���ԣ����� Recordset �ǶԶ����ִ�� JOIN �����Ľ������ô��
 *         ȡ���� Update Resync ���ԣ�ִ�� UpdateBatch ���������Ե��� Resync ������
 */
HRESULT MtADORecordset::update_batch(const ADODB::AffectEnum affect_records){
	clear_last_error();
	try{
		return(_recordset->UpdateBatch(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: put_collect
 * brief: ���ü�¼����ָ����¼����ֵ��
 * param: index - ���š�
 *        value - ��ֵ��
 * return: --
 */
void MtADORecordset::put_collect(const _variant_t &index,const _variant_t &value){
	clear_last_error();
	try{
		_recordset->PutCollect(index,value);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_collect
 * brief: ��ȡ��¼����ָ����¼����ֵ��
 * param: index - ���š�
 * return: ������ֵ��
 */
_variant_t MtADORecordset::get_collect(const _variant_t &index){
	clear_last_error();
	try{
		return(_recordset->GetCollect(index));
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: is_null_value_in_collect
 * brief: �жϵ�ǰ��¼����ָ�����Ƿ�Ϊ�ա�
 * param: index - ���š�
 * return: ���ص�ǰ��¼����ָ�����Ƿ�Ϊ�ա�
 */
BOOL MtADORecordset::is_null_value_in_collect(const _variant_t &index){
	//1.��ȡָ�����е�ֵ,�����жϻ�ȡ�Ƿ�ɹ���
	const _variant_t value=get_collect(index);
	if(0!=get_last_error_code()){
		return(FALSE);
	}
	//2.�ж�ֵ�Ƿ�Ϊ�գ����ҷ��ؽ����
	if(VT_NULL==value.vt){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: get_last_error_code
 * brief: ��ȡ����Ĵ�����롣
 * param: --
 * return: ��������Ĵ�����롣
 */
long MtADORecordset::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: ��ȡ����Ĵ�����Ϣ��
 * param: --
 * return: ��������Ĵ�����Ϣ��
 */
CString MtADORecordset::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: create_instance
 * brief: ����ʵ����
 * param: --
 * return: --
 */
void MtADORecordset::create_instance(){
	const HRESULT result=
		_recordset.CreateInstance(_T("ADODB.Recordset"));
	assert((SUCCEEDED(result))&&(0!=_recordset));
}

/**
 * name: release_instance
 * brief: �ͷ�ʵ����
 * param: --
 * return: --
 */
void MtADORecordset::release_instance(){
	if(0!=_recordset){
		const long state=get_state();
		assert(0==get_last_error_code());
		if(ADODB::adStateOpen==state){
			close();
			assert(0==get_last_error_code());
		}
		_recordset.Release();
		_recordset=0;
	}
}

/**
 * name: clear_last_error
 * brief: ������������Ϣ��
 * param: --
 * return: --
 */
void MtADORecordset::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: ��¼���������Ϣ��
 * param: error - ���������Ϣ��
 * return: --
 */
void MtADORecordset::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}