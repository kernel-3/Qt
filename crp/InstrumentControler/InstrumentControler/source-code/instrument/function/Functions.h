#pragma once

class Function;
class Timing;

/**
 * name: Functions
 * breif: 设备功能管理类，负责管理维护设备的各种功能。
 * author: yameng_he
 * date: 2016-01-25.
 */
class Functions{
//define
public:
	typedef enum{
		FUNCTION_ID_TIMING,
	}FunctionID;
//construction & destruction.
public:
	Functions(void);
	~Functions(void);
//interface
public:
	Timing *get_timing();
//implement
private:
	Function *get_function(const FunctionID function_id);
//restriction
private:
	Functions(const Functions &);
	Functions &operator=(const Functions &);
//variables
private:
	Function *_timing;
};