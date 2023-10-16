#pragma once

/**
 * name: DataConverter
 * brief: 数据转换器，负责实现各种数据间的类型转换。
 * author: yameng_he
 * date: 2015-01-26
 */
class DataConverter{
//interface
public:
	static BOOL is_number(const String &content);
	static BOOL is_unsigned_int(const String &content);
	static String to_string(const unsigned int content);
	static unsigned int to_unsigned_int(const String &content);
//restriction
private:
	DataConverter(void);
	DataConverter(const DataConverter &);
	~DataConverter(void);
	DataConverter &operator=(const DataConverter &);
};