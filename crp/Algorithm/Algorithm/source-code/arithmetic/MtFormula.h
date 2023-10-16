#pragma once

#include"../Symbol"

/**
 * name:　MtFormula
 * brief: 公式类，系统中运行的所有公式均从此类继承。
 * author: yameng_he
 * date: 2015-09-23
 */
class MtFormula {
	//construction & destruction
public:
	explicit MtFormula(const double* x, const double* y,
		const unsigned int size, const unsigned int minimum_size);
	virtual ~MtFormula(void) = 0;
	//interface
public:
	double get_x(const unsigned int index) const;
	double get_y(const unsigned int index) const;
	double get_average_x() const;
	double get_average_y() const;
	unsigned int get_size() const;
	unsigned int get_maximum_x_index() const;
	unsigned int get_minimum_x_index() const;
	unsigned int get_maximum_y_index() const;
	unsigned int get_minimum_y_index() const;
	double get_maximum_x() const;
	double get_minimum_x() const;
	double get_maximum_y() const;
	double get_minimum_y() const;
	//derivation
protected:
	virtual bool is_can_fitted() const;
	//restriction
private:
	MtFormula(const MtFormula&);
	MtFormula& operator=(const MtFormula&);
	//variables
private:
	const double* _x;
	const double* _y;
	unsigned int _size;
	unsigned int _minimum_size;
};