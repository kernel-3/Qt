#include"stdafx.h"
#include"MtGraph.h"

/**
 * name: MtGraph
 * breif: 构造函数。
 * param: --
 * return: --
 */
MtGraph::MtGraph(void){
}

/**
 * name: ~MtGraph
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtGraph::~MtGraph(void){
}

/**
 * name: draw
 * breif: 图形绘制实现。
 * param: dest_dc - 目标DC。
 *		  dest_bitmap - 目标位图。
 *        dest_area - 目标区域。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtGraph::draw(const HDC /*dest_dc*/,
	MtBitmap & /*dest_bitmap*/,const CRect & /*dest_area*/){
	return(0);
}