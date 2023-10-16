#include"stdafx.h"
#include"MtSerialPortParameter.h"

/**
 * name: MtSerialPortParameter
 * brief: 构造函数。
 * param: port - 串口号。
 *        baud_rate - 波特率。
 *        parity - 效验位。
 *        data_bits - 数据位。
 *        stop_bits - 停止位。
 *        flow_control - 流控。
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
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtSerialPortParameter::~MtSerialPortParameter(void){
}

/**
 * name: set_port
 * brief: 设置串口编号。
 * param: port - 串口编号。
 * return: --
 */
void MtSerialPortParameter::set_port(const Port port){
	_port=port;
}

/**
 * name: get_port
 * brief: 获取串口编号。
 * param: --
 * return: 返回串口编号。
 */
MtSerialPortParameter::Port MtSerialPortParameter::get_port() const{
	return(_port);
}

/**
 * name: set_baud_rate
 * brief: 设置串口波特率。
 * param: baud_rate - 波特率。
 * return: --
 */
void MtSerialPortParameter::set_baud_rate(const BaudRate baud_rate){
	_baud_rate=baud_rate;
}

/**
 * name: get_baud_rate
 * brief: 获取串口波特率。
 * param: --
 * return: 返回串口波特率。
 */
MtSerialPortParameter::BaudRate MtSerialPortParameter::get_baud_rate() const{
	return(_baud_rate);
}

/**
 * name: set_parity
 * brief: 设置串口效验方式。
 * param: parity - 效验方式。
 * return: --
 */
void MtSerialPortParameter::set_parity(const Parity parity){
	_parity=parity;
}

/**
 * name: get_parity
 * brief: 获取串口效验方式。
 * param: --
 * return: 返回串口效验方式。
 */
MtSerialPortParameter::Parity MtSerialPortParameter::get_parity() const{
	return(_parity);
}

/**
 * name: set_data_bits
 * brief: 设置串口数据位。
 * param: data_bits - 数据位。
 * return: --
 */
void MtSerialPortParameter::set_data_bits(const DataBits data_bits){
	_data_bits=data_bits;
}

/**
 * name: get_data_bits
 * brief: 获取串口数据位。
 * param: --
 * return: 返回串口数据位。
 */
MtSerialPortParameter::DataBits MtSerialPortParameter::get_data_bits() const{
	return(_data_bits);
}

/**
 * name: set_stop_bits
 * brief: 设置串口停止位。
 * param: stop_bits - 停止位。
 * return: --
 */
void MtSerialPortParameter::set_stop_bits(const StopBits stop_bits){
	_stop_bits=stop_bits;
}

/**
 * name: get_stop_bits
 * brief: 获取串口停止位。
 * param: --
 * return: 返回串口停止位。
 */
MtSerialPortParameter::StopBits MtSerialPortParameter::get_stop_bits() const{
	return(_stop_bits);
}

/**
 * name: set_flow_control
 * brief: 设置串口流控。
 * param: flow_control - 串口流控。
 * return: --
 */
void MtSerialPortParameter::set_flow_control(const FlowControl flow_control){
	_flow_control=flow_control;
}

/**
 * name: get_flow_control
 * brief: 获取串口流控。
 * param: --
 * return: 返回串口流控。
 */
MtSerialPortParameter::FlowControl MtSerialPortParameter::get_flow_control() const{
	return(_flow_control);
}

/**
 * name: get_string_port
 * brief: 获取串口号的字符串描述。
 * param: --
 * return: 返回串口号的字符串描述。
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
 * breif: 将串口参数信息填充到DCB结构体中。
 * param: dcb - 串口参数信息结构体。
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