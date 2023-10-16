#pragma once

#include"Symbol"

class TestItem;

/**
 * name: InstrumentControler
 * brief: 设备控制器，用来控制设备进行各项操作。
 * author: yameng_he
 * date: 2016-03-05
 */
class INSTRUMENT_CONTROLER_API InstrumentControler{
//interface
public:
	static int open_instrument();
	static void close_instrument();
	static int open_timing();
	static void close_timing();
	static int add_pending_test_item_for_timing(
		const TestItem test_item);
//restriction
private:
	InstrumentControler(void);
	InstrumentControler(const InstrumentControler &);
	~InstrumentControler(void);
	InstrumentControler &operator=(const InstrumentControler &);
};