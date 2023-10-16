#pragma once

#include"../Symbol"

/**
 * name: MtSerialPortParameter
 * brief: 串口参数类，负责维护管理串口相关参数。
 * author: yameng_he
 * date: 2014-12-10
 */
class MFC_TOOLKIT_API MtSerialPortParameter{
//define
public:
	/**
	 * name: Port
	 * brief: 串口号。
	 * author:
	 * date:
	 */
	typedef enum{
		PORT_1=1,
		PORT_2=2,
		PORT_3=3,
		PORT_4=4,
	}Port;
	/**
	 * name: BaudRate
	 * brief: 波特率。
	 * author:
	 * date:
	 */
	typedef enum{
		BAUD_RATE_110=CBR_110,
		BAUD_RATE_300=CBR_300,
		BAUD_RATE_600=CBR_600,
		BAUD_RATE_1200=CBR_1200,
		BAUD_RATE_2400=CBR_2400,
		BAUD_RATE_4800=CBR_4800,
		BAUD_RATE_9600=CBR_9600,
		BAUD_RATE_14400=CBR_14400,
		BAUD_RATE_19200=CBR_19200,
		BAUD_RATE_38400=CBR_38400,
		BAUD_RATE_56000=CBR_56000,
		BAUD_RATE_57600=CBR_57600,
		BAUD_RATE_115200=CBR_115200,
		BAUD_RATE_128000=CBR_128000,
		BAUD_RATE_256000=CBR_256000,
	}BaudRate;
	/**
	 * name: Parity
	 * brief: 效验方式。
	 * author: 
	 * date:
	 */
	typedef enum{
		_PARITY_NO=NOPARITY,//无效验。
		_PARITY_ODD=ODDPARITY,//奇效验。
		_PARITY_EVEN=EVENPARITY,//偶效验。
		_PARITY_MARK=MARKPARITY,//效验置位（效验位总为1）。
		_PARITY_SPACE=SPACEPARITY,//效验清零（效验位总为0）。
	}Parity;
	/**
	 * name: DataBits
	 * brief: 数据位宽度。
	 * author:
	 * date:
	 */
	typedef enum{
		DATE_BITS_7=7,
		DATE_BITS_8=8,
	}DataBits;
	/**
	 * name: StopBits
	 * brief: 停止位宽度。
	 * author:
	 * date:
	 */
	typedef enum{
		STOP_BITS_1=ONESTOPBIT,//1位停止位。
		STOP_BITS_1_5=ONE5STOPBITS,//1.5位停止位。
		STOP_BITS_2=TWOSTOPBITS,//2位停止位。
	}StopBits;
	/**
	 * name: FlowControl
	 * brief: 串口流控。
	 * author: 
	 * date:
	 */
	typedef enum{
		FLOW_CONTROL_NO,//不使用任何流控。
		FLOW_CONTROL_CTSRTS,//CTSRTS流控。
		FLOW_CONTROL_CTSDTR,//CTSDTR流控。
		FLOW_CONTROL_DSRRTS,//DSRRTS流控。
		FLOW_CONTROL_DSRDTR,//DSRDTR流控。
		FLOW_CONTROL_XONXOFF,//XONXOFF流控。 
	}FlowControl;
//construction & destruction
public:
	explicit MtSerialPortParameter(const Port port,const BaudRate baud_rate=BAUD_RATE_115200,
		const Parity parity=_PARITY_NO,const DataBits data_bits=DATE_BITS_8,
		const StopBits stop_bits=STOP_BITS_1,const FlowControl flow_control=FLOW_CONTROL_NO);
	~MtSerialPortParameter(void);
//interface
public:
	void set_port(const Port port);
	Port get_port() const;
	void set_baud_rate(const BaudRate baud_rate);
	BaudRate get_baud_rate() const;
	void set_parity(const Parity parity);
	Parity get_parity() const;
	void set_data_bits(const DataBits data_bits);
	DataBits get_data_bits() const;
	void set_stop_bits(const StopBits stop_bits);
	StopBits get_stop_bits() const;
	void set_flow_control(const FlowControl flow_control);
	FlowControl get_flow_control() const;
	CString get_string_port() const;
	void fill_dcb(DCB &dcb) const;
//variables
private:
	Port _port;
	BaudRate _baud_rate;
	Parity _parity;
	DataBits _data_bits;
	StopBits _stop_bits;
	FlowControl _flow_control;
};