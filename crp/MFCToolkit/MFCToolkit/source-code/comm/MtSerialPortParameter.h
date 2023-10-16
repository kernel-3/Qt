#pragma once

#include"../Symbol"

/**
 * name: MtSerialPortParameter
 * brief: ���ڲ����࣬����ά����������ز�����
 * author: yameng_he
 * date: 2014-12-10
 */
class MFC_TOOLKIT_API MtSerialPortParameter{
//define
public:
	/**
	 * name: Port
	 * brief: ���ںš�
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
	 * brief: �����ʡ�
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
	 * brief: Ч�鷽ʽ��
	 * author: 
	 * date:
	 */
	typedef enum{
		_PARITY_NO=NOPARITY,//��Ч�顣
		_PARITY_ODD=ODDPARITY,//��Ч�顣
		_PARITY_EVEN=EVENPARITY,//żЧ�顣
		_PARITY_MARK=MARKPARITY,//Ч����λ��Ч��λ��Ϊ1����
		_PARITY_SPACE=SPACEPARITY,//Ч�����㣨Ч��λ��Ϊ0����
	}Parity;
	/**
	 * name: DataBits
	 * brief: ����λ��ȡ�
	 * author:
	 * date:
	 */
	typedef enum{
		DATE_BITS_7=7,
		DATE_BITS_8=8,
	}DataBits;
	/**
	 * name: StopBits
	 * brief: ֹͣλ��ȡ�
	 * author:
	 * date:
	 */
	typedef enum{
		STOP_BITS_1=ONESTOPBIT,//1λֹͣλ��
		STOP_BITS_1_5=ONE5STOPBITS,//1.5λֹͣλ��
		STOP_BITS_2=TWOSTOPBITS,//2λֹͣλ��
	}StopBits;
	/**
	 * name: FlowControl
	 * brief: �������ء�
	 * author: 
	 * date:
	 */
	typedef enum{
		FLOW_CONTROL_NO,//��ʹ���κ����ء�
		FLOW_CONTROL_CTSRTS,//CTSRTS���ء�
		FLOW_CONTROL_CTSDTR,//CTSDTR���ء�
		FLOW_CONTROL_DSRRTS,//DSRRTS���ء�
		FLOW_CONTROL_DSRDTR,//DSRDTR���ء�
		FLOW_CONTROL_XONXOFF,//XONXOFF���ء� 
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