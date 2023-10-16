#include"stdafx.h"
#include"MtRegionDivision.h"
#include<assert.h>

/**
 * name: MtRegionDivision
 * brief: 构造函数。
 * param: region_width - 区域宽度。
 *        region_height - 区域高度。
 *        region_rows - 区域行数。
 *        region_cols - 区域列数。
 * return: --
 */
MtRegionDivision::MtRegionDivision(const int region_width,const int region_height,
	const int region_rows,const int region_cols)
	:_region_width(region_width)
	,_region_height(region_height)
	,_region_rows(region_rows)
	,_region_cols(region_cols){
}

/**
 * name: ~MtRegionDivision
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtRegionDivision::~MtRegionDivision(void){
}

/**
 * name: is_valid
 * brief: 判断当前裁剪器是否合法。
 * param: --
 * return: 如果裁剪器合法返回TRUE，否则返回FALSE。
 */
BOOL MtRegionDivision::is_valid() const{
	return(_region_width>0&&_region_height>0&&_region_rows>0&&_region_cols>0);
}

/**
 * name: get_child_region_rect
 * brief: 获取子区域尺寸。
 * param: index - 子资源索引。
 * return: 如果获取子资源尺寸失败，则返回空的CRect对象（调用
 *         CRect::IsRectEmpty判断）。否则返回子资源的尺寸。
 * remark: 调用此函数前，必须确保MtRegionDivision实例对象合
 *		   法（通过调用成员函数is_valid确认）。
 */
CRect MtRegionDivision::get_child_region_rect(const int index) const{
	//1.如果当前索引编号不合法则直接返回空尺寸。
	if((index<0)||(index>=(_region_rows*_region_cols))){
		return(CRect(0,0,0,0));
	}
	//2.计算当前子区域的宽度、高度。
	const int child_region_width=_region_width/_region_cols;
	const int child_region_height=_region_height/_region_rows;
	//3.计算当前子区域的行号、列号。
	int row_no=(index+1)/_region_cols;
	int col_no=(index+1)%_region_cols;
	if(0==col_no){
		row_no-=1;
		col_no=_region_cols-1;
	}else{
		col_no-=1;
	}
	//4.计算子区域的尺寸。
	const int child_region_left=col_no*child_region_width;
	const int child_region_top=row_no*child_region_height;
	const int child_region_right=child_region_left+child_region_width;
	const int child_region_bottom=child_region_top+child_region_height;
	//5.返回子区域的尺寸。
	return(CRect(child_region_left,child_region_top,child_region_right,child_region_bottom));
}

/**
 * name: get_child_region_amount
 * brief: 计算当前子区域的合计数量。
 * param: --
 * return: 返回当前子区域的合计数量。
 */
int MtRegionDivision::get_child_region_amount() const{
	int child_region_amount=_region_rows*_region_cols;
	if(child_region_amount<0){
		child_region_amount=0;
	}
	return(child_region_amount);
}