#pragma once

/**
 * name: FittingData
 * breif: 拟合数据类，此类用来存储拟合曲线的数据。
 * author: yameng_he
 * date: 2015-10-31
 */
class FittingData{
//construction & destruction
public:
	FittingData(void);
	FittingData(const double x,const double y);
	~FittingData(void);
//interface
public:
	void set_x(const double x);
	double get_x() const;
	void set_y(const double y);
	double get_y() const;
//variables
private:
	double _x;
	double _y;
};

