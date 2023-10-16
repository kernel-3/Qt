#include"stdafx.h"
#include"MtSerialPortParameter.h"

/**
 * name: MtSerialPortParameter
 * brief: ���캯����
 * param: port - ���ںš�
 *        baud_rate - �����ʡ�
 *        parity - Ч��λ��
 *        data_bits - ����λ��
 *        stop_bits - ֹͣλ��
 *        flow_control - ���ء�
 * return: --
 */
MtSerialPortParameter::MtSerialPortParameter(
	const Port port,const BaudRate baud_rate/*=BAUDRATE_38400*/,
	const Parity parity/*=_PARITY_EVEN*/,const DataBits data_bits/*=DATEBITS_8*/,
	const StopBits stop_bits/*=STOPBITS_1*/,const FlowControl flow_control/*=FLOWCONTROL_NO*/)
	:_port(port)
	,_baud_rate(baud_rate)
	,_parity(parity)
	,_data_bits(data_bits)
	,_stop_bits(stop_bits)
	,_flow_control(flow_control){
}

/**
 * name: ~MtSerialPortParameter
 * breif: ����������
 * param: --
 * return: --
 */
MtSerialPortParameter::~MtSerialPortParameter(void){
}

/**
 * name: set_port
 * brief: ���ô��ڱ�š�
 * param: port - ���ڱ�š�
 * return: --
 */
void MtSerialPortParameter::set_port(const Port port){
	_port=port;
}

/**
 * name: get_port
 * brief: ��ȡ���ڱ�š�
 * param: --
 * return: ���ش��ڱ�š�
 */
MtSerialPortParameter::Port MtSerialPortParameter::get_port() const{
	return(_port);
}

/**
 * name: set_baud_rate
 * brief: ���ô��ڲ����ʡ�
 * param: baud_rate - �����ʡ�
 * return: --
 */
void MtSerialPortParameter::set_baud_rate(const BaudRate baud_rate){
	_baud_rate=baud_rate;
}

/**
 * name: get_baud_rate
 * brief: ��ȡ���ڲ����ʡ�
 * param: --
 * return: ���ش��ڲ����ʡ�
 */
MtSerialPortParameter::BaudRate MtSerialPortParameter::get_baud_rate() const{
	return(_baud_rate);
}

/**
 * name: set_parity
 * brief: ���ô���Ч�鷽ʽ��
 * param: parity - Ч�鷽ʽ��
 * return: --
 */
void MtSerialPortParameter::set_parity(const Parity parity){
	_parity=parity;
}

/**
 * name: get_parity
 * brief: ��ȡ����Ч�鷽ʽ��
 * param: --
 * return: ���ش���Ч�鷽ʽ��
 */
MtSerialPortParameter::Parity MtSerialPortParameter::get_parity() const{
	return(_parity);
}

/**
 * name: set_data_bits
 * brief: ���ô�������λ��
 * param: data_bits - ����λ��
 * return: --
 */
void MtSerialPortParameter::set_data_bits(const DataBits data_bits){
	_data_bits=data_bits;
}

/**
 * name: get_data_bits
 * brief: ��ȡ��������λ��
 * param: --
 * return: ���ش�������λ��
 */
MtSerialPortParameter::DataBits MtSerialPortParameter::get_data_bits() const{
	return(_data_bits);
}

/**
 * name: set_stop_bits
 * brief: ���ô���ֹͣλ��
 * param: stop_bits - ֹͣλ��
 * return: --
 */
void MtSerialPortParameter::set_stop_bits(const StopBits stop_bits){
	_stop_bits=stop_bits;
}

/**
 * name: get_stop_bits
 * brief: ��ȡ����ֹͣλ��
 * param: --
 * return: ���ش���ֹͣλ��
 */
MtSerialPortParameter::StopBits MtSerialPortParameter::get_stop_bits() const{
	return(_stop_bits);
}

/**
 * name: set_flow_control
 * brief: ���ô������ء�
 * param: flow_control - �������ء�
 * return: --
 */
void MtSerialPortParameter::set_flow_control(const FlowControl flow_control){
	_flow_control=flow_control;
}

/**
 * name: get_flow_control
 * brief: ��ȡ�������ء�
 * param: --
 * return: ���ش������ء�
 */
MtSerialPortParameter::FlowControl MtSerialPortParameter::get_flow_control() const{
	return(_flow_control);
}

/**
 * name: get_string_port
 * brief: ��ȡ���ںŵ��ַ���������
 * param: --
 * return: ���ش��ںŵ��ַ���������
 */
CString MtSerialPortParameter::get_string_port() const{
	TCHAR port_string_array[25];
	memset(port_string_array,0,25*sizeof(TCHAR));
#ifdef _UNICODE
	::swprintf(port_string_array,25,_T("\\\\?\\COM%ld"),_port);
#else
	::sprintf_s(port_string_array,25,_T("\\\\?\\COM%ld"),_port);
#endif
	CString port_string=port_string_array;
	return(port_string);
}

/**
 * name: fill_dcb
 * breif: �����ڲ�����Ϣ��䵽DCB�ṹ���С�
 * param: dcb - ���ڲ�����Ϣ�ṹ�塣
 * return: --
 */
void MtSerialPortParameter::fill_dcb(DCB &dcb) const{
	dcb.BaudRate=static_cast<DWORD>(_baud_rate);
	dcb.Parity=static_cast<BYTE>(_parity);
	dcb.ByteSize=static_cast<BYTE>(_data_bits);
	dcb.StopBits=static_cast<BYTE>(_stop_bits);
	dcb.fDsrSensitivity=0;
	if(FLOW_CONTROL_NO==_flow_control){
		dcb.fOutxCtsFlow=0;
		dcb.fOutxDsrFlow=0;
		dcb.fOutX=0;
		dcb.fInX=0;
	}else if(FLOW_CONTROL_CTSRTS==_flow_control){
		dcb.fOutxCtsFlow=1;
		dcb.fOutxDsrFlow=0;
		dcb.fRtsControl=RTS_CONTROL_HANDSHAKE;
		dcb.fOutX=0;
		dcb.fInX=0;
	}else if(FLOW_CONTROL_CTSDTR==_flow_control){
		dcb.fOutxCtsFlow=1;
		dcb.fOutxDsrFlow=0;
		dcb.fDtrControl=DTR_CONTROL_HANDSHAKE;
		dcb.fOutX=0;
		dcb.fInX=0;
	}else if(FLOW_CONTROL_DSRRTS==_flow_control){
		dcb.fOutxCtsFlow=0;
		dcb.fOutxDsrFlow=1;
		dcb.fRtsControl=RTS_CONTROL_HANDSHAKE;
		dcb.fOutX=0;
		dcb.fInX=0;
	}else if(FLOW_CONTROL_DSRDTR==_flow_control){
		dcb.fOutxCtsFlow=0;
		dcb.fOutxDsrFlow=1;
		dcb.fDtrControl=DTR_CONTROL_HANDSHAKE;
		dcb.fOutX=0;
		dcb.fInX=0;
	}else/*if(FLOWCONTROL_XONXOFF==_flow_control)*/{
		dcb.fOutxCtsFlow=0;
		dcb.fOutxDsrFlow=0;
		dcb.fOutX=1;
		dcb.fInX=1;
		dcb.XonChar=0x11;
		dcb.XoffChar=0x13;
		dcb.XoffLim=100;
		dcb.XonLim=100;
	}
}