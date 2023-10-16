#pragma once

#include"../Symbol"

/**
 * name: MtRegionDivision
 * brief: 区域分割器，负责对一整块区域根据行、列划分出子区域。
 * author: yameng_he
 * date: 2014-06-03
 */
class MFC_TOOLKIT_API MtRegionDivision{
//constructor & destructor
public:
	MtRegionDivision(const int region_width,const int region_height,
		const int region_rows,const int region_cols);
	~MtRegionDivision(void);
//interface
public:
	BOOL is_valid() const;
	CRect get_child_region_rect(const int index) const;
	int get_child_region_amount() const;
//variables
private:
	int _region_width;
	int _region_height;
	int _region_rows;
	int _region_cols;
};