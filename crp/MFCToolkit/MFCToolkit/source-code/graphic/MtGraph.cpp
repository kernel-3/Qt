#include"stdafx.h"
#include"MtGraph.h"

/**
 * name: MtGraph
 * breif: ���캯����
 * param: --
 * return: --
 */
MtGraph::MtGraph(void){
}

/**
 * name: ~MtGraph
 * brief: ����������
 * param: --
 * return: --
 */
MtGraph::~MtGraph(void){
}

/**
 * name: draw
 * breif: ͼ�λ���ʵ�֡�
 * param: dest_dc - Ŀ��DC��
 *		  dest_bitmap - Ŀ��λͼ��
 *        dest_area - Ŀ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtGraph::draw(const HDC /*dest_dc*/,
	MtBitmap & /*dest_bitmap*/,const CRect & /*dest_area*/){
	return(0);
}